#version 330
#define MAX_LIGHTS 10
#define POINT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define SPOTLIGHT 3

in vec3 outWorldNormal;
in vec3 outWorldPos;
in vec2 outUv;
in mat3 outTBN;


/*The color map is named diffuse, but when normal map is used the proper name is albedo:
Albedo maps are the pure color of an object,
while diffuse is both color as well as shaded with some diffuse lighting.*/
struct Material {
	bool usesDiffuseMap;
	bool usesNormalMap;
	sampler2D diffuseTexUnit;
	sampler2D normalTexUnit;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct Light {
	int type;
	bool enabled;

    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;

	//POINT_LIGHT, SPOTLIGHT
	vec3 pos;
	//POINT_LIGHT (possibly SPOTLIGHT as well)  
	float constAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	//DIRECTIONAL_LIGHT, SPOTLIGHT
	vec3 direction;
	//SPOTLIGHT
	float cutOff; //cosine of the angle between the direction and one bound of the cone
};

uniform Material material; 
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;
uniform vec3 camPos;

out vec4 fragColor;

vec4 calcAmbient(Light light) {
	return light.ambientColor * material.ambient;
}

vec4 calcDiffuse(Light light, vec3 lightDir, vec3 normal, vec4 fragTexColor) {
	float dotProduct = max(dot(lightDir, normal), 0.0);
	// vector multiplication is component-wise (e.g., (v1, v2) * (u1, u2) = (v1 * u1, v2 * u2))
	return dotProduct * fragTexColor * material.diffuse * light.diffuseColor;
}

vec4 calcSpecular(Light light, vec3 lightDir, vec3 normal, vec3 viewDir) {
	vec3 reflectDir = reflect(-lightDir, normal); ////-lightDir, because the vector must point towards the fragment's position
	float dotProduct = max(dot(viewDir, reflectDir), 0.0);
	return pow(dotProduct, material.shininess) * material.specular * light.specularColor;
}

vec4 calcLight(Light light, vec3 lightDir, vec3 normal, vec3 viewDir, vec4 fragTexColor) {
	vec4 ambient = calcAmbient(light);
	vec4 diffuse = calcDiffuse(light, lightDir, normal, fragTexColor);
	vec4 specular = calcSpecular(light, lightDir, normal, viewDir);
	return (ambient + diffuse + specular);
}


float calcAttenuation(Light light, vec3 fragPos) {
	float distance = length(light.pos - fragPos);
	float attenuation = 1.0 / (
		light.constAttenuation +
		light.linearAttenuation * distance +
		light.quadraticAttenuation * (distance * distance)
		);
	return attenuation;
}



vec4 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 fragTexColor) {
	vec3 lightDir = normalize(light.pos - fragPos);
	vec4 resultColor = calcLight(light, lightDir, normal, viewDir, fragTexColor);

	float attenuation = calcAttenuation(light, fragPos);
	return resultColor * attenuation;
}

vec4 calcDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec4 fragTexColor) {
	//light dir is given as pointing away from the light source, so it's negated now to point away from the frag
	vec3 lightDir = normalize(-light.direction); 
	return calcLight(light, lightDir, normal, viewDir, fragTexColor);
}

vec4 calcSpotlight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 fragTexColor) {
	vec3 lightDir = normalize(light.pos - fragPos);
	float angleCosine = dot(lightDir, normalize(-light.direction));

	vec4 ambient = calcAmbient(light);
	if(angleCosine > light.cutOff) {
		float bias = 0.4;
		float intensity = ((angleCosine - light.cutOff) + bias) / ((1 - light.cutOff) + bias);

		vec4 diffuse = calcDiffuse(light, lightDir, normal, fragTexColor);
		vec4 specular = calcSpecular(light, lightDir, normal, viewDir);
		vec4 resultColor = ambient + (diffuse + specular) * intensity;

		float attenuation = calcAttenuation(light, fragPos);
		return resultColor * attenuation;
	}
	else {
		return ambient;
	}
}


void main () {
	vec4 fragTexColor = vec4(1.0, 1.0, 1.0, 1.0);
	if(material.usesDiffuseMap == true) {
		fragTexColor = texture(material.diffuseTexUnit, outUv);
	}

	vec3 normal = normalize(outWorldNormal);
	if(material.usesNormalMap) {
		vec3 encodedNormal  = texture(material.normalTexUnit, outUv).rgb;
		encodedNormal = 2.0 * encodedNormal - 1.0; //RGB to vector
		//encodedNormal = normalize (encodedNormal*vec3(1,1,intensity)); //intensity

		normal = normalize(outTBN * encodedNormal);
	}

	vec3 viewDir = normalize(camPos - outWorldPos);
	
	vec4 resultColor = vec4(0.0,0.0,0.0,0.0);
	for(int i = 0; i < lightCount; i++) {
		if(lights[i].enabled) {
			switch (lights[i].type) {
				case POINT_LIGHT:
					resultColor += calcPointLight(lights[i], normal, outWorldPos, viewDir, fragTexColor);
					break;
				case DIRECTIONAL_LIGHT:
					resultColor += calcDirectionalLight(lights[i], normal, viewDir, fragTexColor);
					break;
				case SPOTLIGHT:
					resultColor += calcSpotlight(lights[i], normal, outWorldPos, viewDir, fragTexColor);
					break;
			}
		}
	}

	//make the alpha component 1.0
	fragColor = (resultColor * vec4(1.0, 1.0, 1.0, 0.0)) + vec4(0.0, 0.0, 0.0, 1.0);
};
#version 330

in vec4 outColor;
in vec2 outUv;

struct Material {
	bool usesDiffuseMap;
	sampler2D diffuseTexUnit;
    vec4 diffuse;
};

uniform Material material; 
//I assume lights should be completely ignored in constant shader. 

out vec4 fragColor;

void main () {

	if(material.usesDiffuseMap == true) {
		//I multiply the texture by the diffuse property of the material to be consistent with other shaders
		fragColor = texture(material.diffuseTexUnit, outUv) * material.diffuse;
	}
	else {
		fragColor = material.diffuse;
	}
		
};
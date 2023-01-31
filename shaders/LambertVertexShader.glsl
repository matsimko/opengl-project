#version 330

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUv;
layout(location=3) in vec3 aTangent;

out vec3 outWorldNormal;
out vec3 outWorldPos; 
out vec2 outUv;
out mat3 outTBN;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);

	vec4 worldPos = modelMatrix * vec4(aPos, 1.0);
	outWorldPos = vec3(worldPos); //worldPos.xyz

	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix))); //this could be sent as a uniform variable
	//Gram–Schmidt orthonormalization
	vec3 _normal = normalize(aNormal);
    vec3 _tangent = normalize(aTangent);
    _tangent = normalize(_tangent - dot(_tangent, _normal) * _normal);
    vec3 _bitangent = cross(_normal, _tangent);
	
	//TBN Matrix
	vec3 T = normalize(vec3(normalMatrix * _tangent));
 	vec3 B = normalize(vec3(normalMatrix * _bitangent));
	vec3 N = normalize(vec3(normalMatrix * _normal));
	outTBN = mat3(T, B, N);

	outWorldNormal = normalMatrix * aNormal;
	outUv = aUv;
};
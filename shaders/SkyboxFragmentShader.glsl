#version 330

in vec3 outPos;

struct Material {
	samplerCube diffuseTexUnit;
}; 
uniform Material material;  

out vec4 fragColor;

void main () {
	fragColor = texture(material.diffuseTexUnit, outPos);
};
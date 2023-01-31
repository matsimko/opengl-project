#version 330

struct Material {
	vec4 diffuse;
}; 
uniform Material material;  

out vec4 fragColor;

void main () {
	fragColor = material.diffuse;
};
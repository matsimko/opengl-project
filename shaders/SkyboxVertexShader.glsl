#version 330
layout(location = 0) in vec3 aPos;

out vec3 outPos;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {

	gl_Position = projectionMatrix * viewMatrix * vec4(aPos, 1.0);
	outPos = aPos;
};

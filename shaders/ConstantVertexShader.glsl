#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location=2) in vec2 aUv;

out vec4 outColor;
out vec2 outUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
	outColor = vec4(aColor, 1.0);

	outUv = aUv;
};

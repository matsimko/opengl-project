#version 330
layout(location = 0) in vec3 aPos;

uniform mat4 ortographicMatrix;

void main() {

	gl_Position = ortographicMatrix * vec4(aPos, 1.0);
};

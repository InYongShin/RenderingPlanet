#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexCoord;

void main() {
	gl_Position = vec4(inPosition, 1.0f);
}
#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 texCoord;

void main()
{
	gl_Position = vec4(inPosition, 1.0);
}
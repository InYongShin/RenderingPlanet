#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexCoord;

out vec3 worldPos;
out vec2 texCoord;

void main()
{
	worldPos = inPosition;
	texCoord = inTexCoord;

	gl_Position =  vec4(inPosition, 1.0);
}
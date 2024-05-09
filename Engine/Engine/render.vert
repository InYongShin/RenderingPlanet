#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 modelMat = mat4(1.0);

void main()
{
	worldPos = vec3(modelMat * vec4(inPosition, 1.0));
	normal = inNormal;
	texCoord = inTexCoord;

	gl_Position = vec4(worldPos, 1.0);
}
#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 3) in vec3 inColor;

out vec3 worldPos;
out vec3 normal;

out vec3 terrainColor;

uniform mat4 modelMat = mat4(1.0);
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
	worldPos = vec3(modelMat * vec4(inPosition, 1.0));
	normal = vec3(modelMat * vec4(inNormal, 0.0));

	terrainColor = inColor;

	gl_Position = projMat * viewMat * vec4(worldPos, 1.0);
}
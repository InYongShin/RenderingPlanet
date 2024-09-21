#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 modelMat = mat4(1.0);
uniform mat4 viewMat;
uniform mat4 projMat;

uniform sampler2D heightMap;

void main()
{
	worldPos = vec3(modelMat * vec4(inPosition, 1.0));
	normal = vec3(modelMat * vec4(inNormal, 0.0));
	texCoord = inTexCoord;

	float height = texture(heightMap, texCoord).r * 2.5;
	vec3 heightOffset = normal * height;
	vec3 offsetPos = worldPos + heightOffset;

	gl_Position = projMat * viewMat * vec4(offsetPos, 1.0);
}
#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

out vec3 terrainColor;

uniform mat4 modelMat = mat4(1.0);
uniform mat4 viewMat;
uniform mat4 projMat;

uniform sampler2D heightMap;

void main()
{
	worldPos = vec3(modelMat * vec4(inPosition, 1.0));
	normal = vec3(modelMat * vec4(inNormal, 0.0));
	texCoord = inTexCoord;

	float height = texture(heightMap, texCoord).r;
	vec3 heightOffset = normal * height * 25.0;
	worldPos = worldPos + heightOffset;

	float heightDX = (texture(heightMap, texCoord + vec2(0.01, 0.0)).r - height) * 100.0;
	float heightDZ = (texture(heightMap, texCoord + vec2(0.0, 0.01)).r - height) * 100.0;

	vec3 gradient = normalize(vec3(-heightDX, 1.0, -heightDZ));

	normal = gradient;

	float colorWeight = smoothstep(0.2, 0.7, height);
	terrainColor = mix(vec3(0.65, 0.42, 0.3), vec3(0.0, 1.0, 0.0), colorWeight);

	gl_Position = projMat * viewMat * vec4(worldPos, 1.0);
}
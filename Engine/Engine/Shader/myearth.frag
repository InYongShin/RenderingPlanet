#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;

in vec3 terrainColor;

uniform vec3 lightPosition;

void main(void)
{
	vec3 ambient = terrainColor * 0.1;
	vec3 diffuse = terrainColor * 0.9;

	vec3 l = normalize(lightPosition - worldPos);
	vec3 n = normalize(normal);

	float cosTheta = max(0.0, dot(n, l));

	vec3 color = ambient + diffuse * cosTheta;

	fragColor = vec4(color, 1.0);
}
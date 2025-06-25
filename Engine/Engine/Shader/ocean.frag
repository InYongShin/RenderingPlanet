#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;
// in vec2 texCoord;

uniform vec3 lightPosition;

void main(void)
{
	vec3 l = normalize(lightPosition - worldPos);
	vec3 n = normalize(normal);

	float cosTheta = max(0.2, dot(n, l));

	vec3 color = vec3(0.0, 0.5, 1.0) * cosTheta;

	fragColor = vec4(color, 0.95);
}


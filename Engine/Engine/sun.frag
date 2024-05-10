#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

void main(void)
{
	vec3 diffuse = vec3(1.0, 0.0, 0.0);
	vec3 color = diffuse;
	fragColor = vec4(color, 1.0);
}


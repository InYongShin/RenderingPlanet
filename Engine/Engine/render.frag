#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

void main(void)
{
	fragColor = vec4(0.0, 1.0, 0.0, 1.0);
}

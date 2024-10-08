#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D tex;

void main(void)
{
	vec3 diffuse = texture(tex, texCoord).rgb;
	vec3 color = diffuse;

	fragColor = vec4(color, 1.0);
}


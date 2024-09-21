#version 410 core

out vec4 fragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPosition;
uniform float lightPower;

uniform sampler2D tex;

void main(void)
{
	// vec3 diffuse = vec3(0.0, 1.0, 0.0);
	vec3 diffuse = 0.6 * texture(tex, texCoord).rgb;
	vec3 ambient = 0.4 * diffuse;

	vec3 l = normalize(lightPosition - worldPos);
	vec3 n = normalize(normal);

	float cosTheta = max(0.0, dot(n, l));

	vec3 color = ambient + diffuse * lightPower * cosTheta;

	fragColor = vec4(color, 1.0);
}


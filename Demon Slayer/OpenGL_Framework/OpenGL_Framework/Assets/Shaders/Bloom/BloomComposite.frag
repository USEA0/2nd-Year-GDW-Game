#version 420

layout(binding = 0) uniform sampler2D uScene;
layout(binding = 1) uniform sampler2D uBloom;

in vec2 texcoord;

out vec3 outColor;

void main()
{
	vec3 colorA = texture(uScene, texcoord).rgb;
	vec3 colorB = texture(uBloom, texcoord).rgb;
	outColor = 1.0 - (1.0 - colorA) * (1.0 - colorB);
}
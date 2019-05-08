#version 420

layout(binding = 0) uniform sampler2D uTex; 
layout(binding = 10) uniform sampler3D uLUT;

uniform float LUTsize;
uniform float uAmount;

in vec2 texcoord;

out vec3 outColor;

void main()
{
	vec3 applyLut;
	vec3 rawColor = texture(uTex, texcoord).rgb;

	vec3 scale = vec3((LUTsize - 1.0) / LUTsize);
	vec3 offset = vec3(1.0 / (2.0 * LUTsize));

	applyLut = texture(uLUT, scale * rawColor + offset).rgb;

	vec3 finalColor = mix(rawColor, applyLut, uAmount);

	outColor = finalColor;
}
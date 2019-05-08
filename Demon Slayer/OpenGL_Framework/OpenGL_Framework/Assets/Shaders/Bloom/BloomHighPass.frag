#version 420

layout(binding = 0) uniform sampler2D uTex;
layout(binding = 1) uniform sampler2D noLight;

uniform float uThreshold;
uniform bool uActive;

in vec2 texcoord;

out vec3 outColor;

void main()
{
	vec3 color = texture(uTex, texcoord).rgb;

	float  luminance = (color.r + color.g + color.b) / 3.0;

	if(luminance > uThreshold && texture(noLight, texcoord).a != 1.0 && uActive)
	{
		outColor = color - uThreshold;
	}
	else
	{
		outColor = vec3(0.0, 0.0, 0.0);
	}
}
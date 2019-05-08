#version 420

layout(binding = 0) uniform sampler2D uTex;

in vec2 texcoord;
in float frag_alpha;

layout(location = 0) out vec4 outColor;
layout(location = 3) out vec4 noLight;

void main()
{
	vec4 color = texture(uTex, vec2(texcoord.x, texcoord.y * - 1)).rgba;

	if(color.g >= 0.9 && color.r < color.g && color.b < color.g)
		discard;

	outColor = color;
	outColor.a *= frag_alpha;
	noLight = vec4(0.5f,0.5f,0.5f,0.5f);
}
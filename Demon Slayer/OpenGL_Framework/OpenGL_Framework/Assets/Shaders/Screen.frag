#version 420

layout(binding = 0) uniform sampler2D uTex;
uniform float uIndex = 0.0;

in vec2 texcoord;

layout(location = 0) out vec4 outColor;

void main()
{
	if(uIndex == 0 || uIndex == 14)
		outColor = texture(uTex, vec2(texcoord.x, texcoord.y));
	else
		outColor = texture(uTex, vec2(texcoord.x, texcoord.y * -1));
}
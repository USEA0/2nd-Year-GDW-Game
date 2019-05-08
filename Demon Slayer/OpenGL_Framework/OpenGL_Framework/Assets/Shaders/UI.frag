#version 420

layout(binding = 0) uniform sampler2D uTex;

in vec2 texcoord;

layout(location = 0) out vec4 outColor;
layout(location = 3) out vec4 noLight;

void main()
{
	vec4 color = texture(uTex, texcoord);

	if(color.g > color.r && color.g > color.b)
		discard;

	outColor = color;
	noLight = vec4(1.0f,1.0f,1.0f,1.0f);
}
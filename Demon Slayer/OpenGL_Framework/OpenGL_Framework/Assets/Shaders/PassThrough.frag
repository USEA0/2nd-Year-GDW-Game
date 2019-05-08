#version 420

layout(binding = 0) uniform sampler2D uTex;
layout(binding = 1) uniform sampler2D uTexEmissive;
layout(binding = 2) uniform sampler2D uTexSpecular;

in vec2 texcoord;
in vec3 norm;
in vec3 pos;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outPosition;
layout(location = 3) out vec4 noLight;
layout(location = 4) out vec4 outEmissive;

void main()
{
	//Standard color output
	outColor.rgb = texture(uTex, texcoord).rgb;
	outColor.a = 1.0;

	//Pack normals
	outNormal = vec4(normalize(norm) * 0.5 + 0.5, 1.0);
	
	outEmissive = texture(uTexEmissive, texcoord);

	//View space positions, no need to pack
	outPosition = vec4(pos, 1.0);
	noLight = vec4(0.0f,0.0f,0.0f,0.0f);
}
#version 420

uniform vec2 uPixelSize;

layout(binding = 0) uniform sampler2D uTex;
layout(binding = 1) uniform sampler2D uTexDepth;
layout(binding = 2) uniform sampler2D noLight;

uniform float uBlurClamp = 1.0;  // max blur amount
uniform float uBias = 1.0; // Aperture
uniform float uFocus = 0.5;  // Focus

in vec2 texcoord;
out vec4 outColor;

void main()
{
	float depth = texture(uTexDepth, texcoord).r;
	
	vec4 col = vec4(0, 0, 0, 1);
	vec2 dofblur;
	
	float factor = abs(depth - uFocus);
	
	dofblur = vec2(clamp(factor * (uBias - 0.004f), 0.0, uBlurClamp));
			
	col.rgb += texture(uTex, texcoord + vec2(0.0, - 4.0 * dofblur.y * uPixelSize .y)).rgb * 0.06;
	col.rgb += texture(uTex, texcoord + vec2(0.0, - 3.0 * dofblur.y * uPixelSize .y)).rgb * 0.09;
	col.rgb += texture(uTex, texcoord + vec2(0.0, - 2.0 * dofblur.y * uPixelSize .y)).rgb * 0.12;
	col.rgb += texture(uTex, texcoord + vec2(0.0, -       dofblur.y * uPixelSize .y)).rgb * 0.15;
	col.rgb += texture(uTex, texcoord												).rgb * 0.16;
	col.rgb += texture(uTex, texcoord + vec2(0.0,         dofblur.y * uPixelSize .y)).rgb * 0.15;
	col.rgb += texture(uTex, texcoord + vec2(0.0,   2.0 * dofblur.y * uPixelSize .y)).rgb * 0.12;
	col.rgb += texture(uTex, texcoord + vec2(0.0,   3.0 * dofblur.y * uPixelSize .y)).rgb * 0.09;
	col.rgb += texture(uTex, texcoord + vec2(0.0,   4.0 * dofblur.y * uPixelSize .y)).rgb * 0.06;

	if(texture(noLight, texcoord).a == 0.0)
	{
		outColor = col;
	}
	else
	{
		outColor = texture(uTex, texcoord);
	}
}
#version 420

layout(binding = 0) uniform sampler2D uTex;
uniform float uPixelSize; //1.0 / window_height

in vec2 texcoord;

out vec3 outColor;

void main()
{
	//Sample pixels in a vertical column
	//Weights add up to 1
	outColor = vec3(0.0, 0.0, 0.0);
	
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y - 4.0 * uPixelSize)).rgb * 0.06;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y - 3.0 * uPixelSize)).rgb * 0.09;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y - 2.0 * uPixelSize)).rgb * 0.12;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y -		  uPixelSize)).rgb * 0.15;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y					)).rgb * 0.16;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y +		  uPixelSize)).rgb * 0.15;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y + 2.0 * uPixelSize)).rgb * 0.12;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y + 3.0 * uPixelSize)).rgb * 0.09;
	outColor += texture(uTex, vec2(texcoord.x, texcoord.y + 4.0 * uPixelSize)).rgb * 0.06;
}
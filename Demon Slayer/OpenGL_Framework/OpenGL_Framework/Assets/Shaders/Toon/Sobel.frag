#version 420

layout(binding = 0) uniform sampler2D uNormalMap;
layout(binding = 1) uniform sampler2D uDepthMap;
uniform vec2 uPixelSize;
uniform bool uToonShading;

in vec2 texcoord;

out float outEdge;

float Sobel_Normal_Horizontal(sampler2D texmap, vec2 texcoord)
{
	vec3 sum = vec3(0.0);

	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y + uPixelSize.y)).rgb;
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y)).rgb * 2.0;
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y - uPixelSize.y)).rgb;

	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y + uPixelSize.y)).rgb;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y)).rgb * 2.0;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y - uPixelSize.y)).rgb;

	float edgeFactor = dot(sum, sum);

	if(edgeFactor < 0.7)
		return 1.0;
	else
		return 0.0;
}

float Sobel_Normal_Vertical(sampler2D texmap, vec2 texcoord)
{
	vec3 sum = vec3(0.0);

	sum += texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y + uPixelSize.y)).rgb;
	sum += texture(texmap, vec2(texcoord.x, texcoord.y + uPixelSize.y)).rgb * 2.0;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y + uPixelSize.y)).rgb;
	
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y - uPixelSize.y)).rgb;
	sum -= texture(texmap, vec2(texcoord.x, texcoord.y - uPixelSize.y)).rgb * 2.0;
	sum -= texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y - uPixelSize.y)).rgb;

	float edgeFactor = dot(sum, sum);

	if(edgeFactor < 0.7)
		return 1.0;
	else
		return 0.0;
}

float Sobel_Depth_Horizontal(sampler2D texmap, vec2 texcoord)
{
	float sum = 0.0;

	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y + uPixelSize.y)).r;
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y)).r * 2.0;
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y - uPixelSize.y)).r;

	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y + uPixelSize.y)).r;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y)).r * 2.0;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y - uPixelSize.y)).r;

	if(sum < 0.05)
		return 1.0;
	else
		return 0.0;
}

float Sobel_Depth_Vertical(sampler2D texmap, vec2 texcoord)
{
	float sum = 0.0;

	sum += texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y + uPixelSize.y)).r;
	sum += texture(texmap, vec2(texcoord.x, texcoord.y + uPixelSize.y)).r * 2.0;
	sum += texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y + uPixelSize.y)).r;
	
	sum -= texture(texmap, vec2(texcoord.x - uPixelSize.x, texcoord.y - uPixelSize.y)).r;
	sum -= texture(texmap, vec2(texcoord.x, texcoord.y - uPixelSize.y)).r * 2.0;
	sum -= texture(texmap, vec2(texcoord.x + uPixelSize.x, texcoord.y - uPixelSize.y)).r;
	
	if(sum < 0.05)
		return 1.0;
	else
		return 0.0;
}

void main()
{
	if(uToonShading)
	{
		float depthSobel = Sobel_Depth_Horizontal(uDepthMap, texcoord) * Sobel_Depth_Vertical(uDepthMap, texcoord);
		float normalSobel = Sobel_Normal_Horizontal(uNormalMap, texcoord) * Sobel_Normal_Vertical(uNormalMap, texcoord);

		outEdge = depthSobel * normalSobel;
	}
	else
		outEdge = 1.0;
}
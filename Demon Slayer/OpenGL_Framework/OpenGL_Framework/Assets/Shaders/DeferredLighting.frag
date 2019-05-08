#version 420

uniform	mat4 ViewToShadowMap;

uniform vec3 LightDirection;
uniform vec4 LightPosition2;
uniform vec4 LightPosition3;
uniform bool uToonShading;
uniform float uLightning;

//color
const vec3 LightAmbient = vec3(0.4f, 0.4f, 0.4f);
const vec3 LightDiffuse = vec3(0.3f, 0.3f, 0.3f);
const vec3 LightSpecular = vec3(0.5f, 0.5f, 0.5f);
const float LightSpecularExponent = 100.0f;

const vec3 LightDiffuse2 = vec3(0.3f, 0.1f, 0.0f);
const vec3 LightSpecular2 = vec3(0.9f, 0.55f, 0.0f);
const float LightSpecularExponent2 = 10.0f;
const float Attenuation_Constant2 = 1.0f;
const float Attenuation_Linear2 = 0.1f;
const float Attenuation_Quadratic2 = 0.01f;

const vec3 LightDiffuse3 = vec3(0.3f, 0.1f, 0.0f);
const vec3 LightSpecular3 = vec3(0.9f, 0.55f, 0.0f);
const float LightSpecularExponent3 = 10.0f;
const float Attenuation_Constant3 = 1.0f;
const float Attenuation_Linear3 = 0.1f;
const float Attenuation_Quadratic3 = 0.01f;

layout (binding = 0)uniform sampler2D uTex;
layout (binding = 1)uniform sampler2D uShadowMap;
layout (binding = 2)uniform sampler2D uNormalMap;
layout (binding = 3)uniform sampler2D uPositionMap;
layout (binding = 4)uniform sampler2D noLight;
layout (binding = 5)uniform sampler2D uEdgeMap;
layout (binding = 6)uniform sampler2D uToonTex;
layout (binding = 7) uniform sampler2D uTexEmissive;

in vec2 texcoord;

out vec4 outColor;


void main()
{
	//Get Data
	vec3 textureColor = texture(uTex, texcoord).rgb;
	float lightning = uLightning;
	if(texture(noLight, texcoord).a == 0.0)
	{
		vec3 normal = texture(uNormalMap, texcoord).xyz * 2.0 - 1.0;
		vec3 pos = texture(uPositionMap, texcoord).xyz;

		if(length(pos) == 0.0)
		{
			discard;
		}

		//Determine if there is shadow
		vec4 shadowCoord = ViewToShadowMap * vec4(pos, 1.0);

		//Where is current point in shadow map
		//Depth
		float shadowDepth = texture(uShadowMap, shadowCoord.xy).r;
		float shadowAmount = 1;
		if(shadowDepth < shadowCoord.z - 0.00022f)
		{
			//Shadow
			shadowAmount = 0.1;
			lightning = 1.0;
		}

		vec3 eye = normalize(-pos);

		float NdotL = dot(normal, LightDirection);
		
	
		outColor.rbg = textureColor * LightAmbient * shadowAmount;
			
		if(NdotL > 0.0)
		{
			// Calculate diffuse contribution
			outColor.rgb += LightDiffuse * NdotL;

			// Blinn-Phong half vector
			float NdotHV = max(dot(normal, normalize(LightDirection + normalize(-pos))), 0.0);

			// Calculate specular contribution
			outColor.rgb += LightSpecular * pow(NdotHV, LightSpecularExponent) * shadowAmount;
		}
		outColor.rgb *= lightning;

		vec3 lightVec2 = LightPosition2.xyz - pos;
		float dist2 = length(lightVec2);
		vec3 lightDir2 = lightVec2 / dist2;
		float NdotL2 = dot(normal, lightDir2);
	
		if(NdotL2 > 0.0)
		{
			float attenuation2 = 1.0 / (Attenuation_Constant2 + (Attenuation_Linear2 * dist2) + (Attenuation_Quadratic2 * dist2 * dist2));
			outColor.rgb += LightDiffuse2 * NdotL2 * attenuation2;
			float NdotHV2 = max(dot(normal, normalize(lightDir2 + normalize(-pos))), 0.0);
			outColor.rgb += LightSpecular2 * pow(NdotHV2, LightSpecularExponent2) * attenuation2;
		}
	
		vec3 lightVec3 = LightPosition3.xyz - pos;
		float dist3 = length(lightVec3);
		vec3 lightDir3 = lightVec3 / dist3;
		float NdotL3 = dot(normal, lightDir3);
	
		if(NdotL3 > 0.0)
		{
			float attenuation3 = 1.0 / (Attenuation_Constant3 + (Attenuation_Linear3 * dist3) + (Attenuation_Quadratic3 * dist3 * dist3));
			outColor.rgb += LightDiffuse3 * NdotL3 * attenuation3;
			float NdotHV3 = max(dot(normal, normalize(lightDir3 + normalize(-pos))), 0.0);
			outColor.rgb += LightSpecular3 * pow(NdotHV3, LightSpecularExponent3) * attenuation3;
		}

		
		float rim = 1.0 - max(dot(eye, normal), 0.0);
		outColor.rgb += pow(smoothstep(0.0, 1.0, rim),7.0) * shadowAmount;

		float edgeFactor = texture(uEdgeMap, texcoord).r;
		float blocky;
		if(uToonShading)
			blocky = clamp(texture(uToonTex, vec2(clamp(NdotL, 0.0, 1.0), 0.5)).r * 2.5, 0.0, 1.0);
		else
			blocky = 1.0;

		outColor.rgb *= textureColor.rgb * edgeFactor * blocky;
		outColor.a = 1.0;
		
		outColor.rgb += texture(uTexEmissive, texcoord).rgb;

	}
	else
	{
		outColor.rgb = textureColor.rgb;
		outColor.a = 1.0;
	}
}
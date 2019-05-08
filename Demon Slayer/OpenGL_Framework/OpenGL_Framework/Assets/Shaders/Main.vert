#version 420

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout(location = 0) in vec3 in_vert;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

layout(location = 3) in vec3 in_vert2;
layout(location = 4) in vec2 in_uv2;
layout(location = 5) in vec3 in_normal2;

uniform float T = 0.0f;

out vec2 texcoord;
out vec3 norm;
out vec3 pos;

void main()
{
	texcoord = vec2(in_uv.x, in_uv.y * -1);

	vec3 newPos;
	newPos = mix(in_vert, in_vert2, T);

	vec3 newNorm;
	newNorm = mix(in_normal, in_normal2, T);
	
	norm = mat3(uView) * mat3(uModel) * newNorm;

	vec4 viewSpace = uView * uModel * vec4(newPos, 1.0f);

	gl_Position = uProj * viewSpace;

	pos = viewSpace.xyz;
}
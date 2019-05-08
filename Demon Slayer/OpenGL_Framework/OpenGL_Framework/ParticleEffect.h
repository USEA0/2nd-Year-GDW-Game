#pragma once

#include <vector>
#include "Matrix.h"
#include "Texture.h"

struct ParticleList
{
	vec3 *Positions = nullptr;
	vec3 *Velocities = nullptr;
	float *Size = nullptr;
	float *Alpha = nullptr;
	float *Ages = nullptr;
	float *Lifetimes = nullptr;
};

class ParticleEffect
{
public:
	ParticleEffect();
	~ParticleEffect();

	bool Init(const std::string &textureFile, unsigned int maxParticles, unsigned int rate);

	void update(float elapsed);
	void render();

	mat4 Transform;

	vec2 RangeX = vec2(-10.0f, 10.0f);
	vec2 RangeY = vec2(0.0f, 10.0f);
	vec2 RangeZ = vec2(-10.0f, 10.0f);
	vec2 RangeVelocity = vec2(0.1f, 1.0f);
	vec2 RangeLifetime = vec2(7.0f, 9.5f);
	//Lerp variables are dynamic based on lifetime of particle
	vec2 LerpAlpha = vec2(0.5f, 0.0f);
	vec2 LerpSize = vec2(0.0f, 1.0f);

private:
	ParticleList _Particles;
	Texture _Texture;

	int _Rate = 0;
	unsigned int _MaxParticles = 0;
	unsigned int _NumCurrentParticles = 0;

	GLuint _VAO;
	GLuint _VBO_Position = 0;
	GLuint _VBO_Size = 0;
	GLuint _VBO_Alpha = 0;
};
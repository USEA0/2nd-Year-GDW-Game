#include "ParticleEffect.h"
#include <iostream>

#define BUFFER_OFFSET(i)((char *)0+(i))

ParticleEffect::ParticleEffect()
{
}

ParticleEffect::~ParticleEffect()
{
	if (_VAO != GL_NONE)
	{
		glDeleteVertexArrays(1, &_VAO);
	}

	if (_VBO_Position != GL_NONE)
	{
		glDeleteBuffers(1, &_VBO_Position);
	}

	if (_VBO_Size != GL_NONE)
	{
		glDeleteBuffers(1, &_VBO_Size);
	}

	if (_VBO_Alpha != GL_NONE)
	{
		glDeleteBuffers(1, &_VBO_Alpha);
	}

	if (_Particles.Positions != nullptr)
	{
		delete[] _Particles.Positions;
		delete[] _Particles.Velocities;
		delete[] _Particles.Alpha;
		delete[] _Particles.Ages;
		delete[] _Particles.Lifetimes;
		delete[] _Particles.Size;
	}
}

bool ParticleEffect::Init(const std::string & textureFile, unsigned int maxParticles, unsigned int rate)
{
	_Texture.Load(textureFile);
	_Texture.SetNearestFilter();

	_MaxParticles = maxParticles;
	_Rate = rate;

	_Particles.Positions = new vec3[_MaxParticles];
	_Particles.Velocities = new vec3[_MaxParticles];
	_Particles.Alpha = new float[_MaxParticles];
	_Particles.Ages = new float[_MaxParticles];
	_Particles.Lifetimes = new float[_MaxParticles];
	_Particles.Size = new float[_MaxParticles];

	//Setup OpenGL memory
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO_Position);
	glGenBuffers(1, &_VBO_Size);
	glGenBuffers(1, &_VBO_Alpha);

	glBindVertexArray(_VAO);

	glEnableVertexAttribArray(0);	//Vertex
	glEnableVertexAttribArray(1);	//Size
	glEnableVertexAttribArray(2);	//Alpha

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _MaxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Size);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _MaxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Alpha);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _MaxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)2, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
	return true;
}

void ParticleEffect::update(float deltaTime)
{
	int NumToSpawn = _Rate;

	//Create new Particles
	while (_NumCurrentParticles < _MaxParticles && NumToSpawn > 0)
	{
		_Particles.Alpha[_NumCurrentParticles] = LerpAlpha.x;
		_Particles.Ages[_NumCurrentParticles] = 0.0f;
		_Particles.Lifetimes[_NumCurrentParticles] = RandomRangef(RangeLifetime.x, RangeLifetime.y);
		_Particles.Size[_NumCurrentParticles] = LerpSize.x;
		_Particles.Positions[_NumCurrentParticles] = vec3(RandomRangef(RangeX.x, RangeX.y), RandomRangef(RangeY.x, RangeY.y), RandomRangef(RangeZ.x, RangeZ.y));

		//Send the particle in a random direction, with a velocity between our range
		_Particles.Velocities[_NumCurrentParticles] = vec3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		_Particles.Velocities[_NumCurrentParticles].Normalize();
		_Particles.Velocities[_NumCurrentParticles] *= RandomRangef(RangeVelocity.x, RangeVelocity.y);

		_NumCurrentParticles++;
		NumToSpawn--;
	}

	//Update existing particles
	for (unsigned i = 0; i < _NumCurrentParticles; i++)
	{
		_Particles.Ages[i] += deltaTime;
		
		if (_Particles.Ages[i] > _Particles.Lifetimes[i])
		{
			//Remove the particle by replacing it with the one at the top of the stack
			_Particles.Alpha[i] = _Particles.Alpha[_NumCurrentParticles - 1];
			_Particles.Ages[i] = _Particles.Ages[_NumCurrentParticles - 1];
			_Particles.Lifetimes[i] = _Particles.Lifetimes[_NumCurrentParticles - 1];
			_Particles.Positions[i] = _Particles.Positions[_NumCurrentParticles - 1];
			_Particles.Size[i] = _Particles.Size[_NumCurrentParticles - 1];
			_Particles.Velocities[i] = _Particles.Velocities[_NumCurrentParticles - 1];

			_NumCurrentParticles--;
			continue;
		}

		_Particles.Positions[i] += _Particles.Velocities[i] * deltaTime;

		float interp = _Particles.Ages[i] / _Particles.Lifetimes[i];

		_Particles.Alpha[i] = lerp(LerpAlpha.x, LerpAlpha.y, interp);
		_Particles.Size[i] = lerp(LerpSize.x, LerpSize.y, interp);
	}

	//Update OpenGL on the changes

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Position);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _NumCurrentParticles, &_Particles.Positions[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Size);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * _NumCurrentParticles, &_Particles.Size[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Alpha);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * _NumCurrentParticles, &_Particles.Alpha[0]);

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
}

void ParticleEffect::render()
{
	if (_NumCurrentParticles == 0)
	{
		return;
	}

	_Texture.bind(0);

	glBindVertexArray(_VAO);
	glDrawArrays(GL_POINTS, 0, _NumCurrentParticles);
	glBindVertexArray(GL_NONE);

	_Texture.unbind(0);
}

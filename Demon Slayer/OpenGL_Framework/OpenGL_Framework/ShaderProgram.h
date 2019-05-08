#pragma once

#include "GL\glew.h"

#include "Vector.h"
#include "Mesh.h"
#include "ParticleEffect.h"
#include <string>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	// Loads a vertex shader and a fragment shader, and places them in a program
	bool Load(const std::string&vertFile, const std::string &fragFile);
	bool Load(const std::string&vertFile, const std::string &fragFile, const std::string &geomFile);
	bool IsLoaded() const;

	bool reload();
	bool reloadGeom();
	// Clear all data from OpenGL
	void unload();
	bool LinkProgram();

	// Use/Detach the shader from use
	void bind() const;
	void unbind();

	void addMesh(Mesh* mesh) { meshes.push_back(mesh); }
	void addParticle(ParticleEffect* mesh) { particles.push_back(mesh); }

	void draw();
	void drawParticles();
	void drawNoTex();

	// Requires a relink before OpenGL registers the change
	void AddAttribute(unsigned int index, const std::string &attribName);

	// Returns -1 if the attribute does not exist
	int GetAttribLocation(const std::string &attribName);

	// Returns -1 if uniform does not exist
	int GetUniformLocation(const std::string &uniformName);

	// Send data to shaders
	void SendUniform(const std::string &name, int integer);
	void SendUniform(const std::string &name, unsigned int unsigned_integer);
	void SendUniform(const std::string &name, float scalar);
	void SendUniform(const std::string &name, const vec2 &vector);
	void SendUniform(const std::string &name, const vec3 &vector);
	void SendUniform(const std::string &name, const vec4 &vector);
	void SendUniformMat3(const std::string &name, float *matrix, bool transpose);
	void SendUniformMat4(const std::string &name, float *matrix, bool transpose);

private:
	bool _IsInit = false;
	GLuint _VertexShader = 0;
	GLuint _FragShader = 0;
	GLuint _GeomShader = 0;
	GLuint _Program = 0;

	std::string vertexFilename;
	std::string fragFilename;
	std::string geomFilename;

	std::vector<Mesh*> meshes;
	std::vector<ParticleEffect*> particles;

	std::string ReadFile(const std::string &fileName) const;
	bool CompileShader(GLuint shader) const;
	void OutputShaderLog(GLuint shader) const;
	void OutputProgramLog() const;
};
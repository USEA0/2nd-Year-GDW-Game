#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include "Math.h"
#include "Transform.h"
#include "Texture.h"

class Mesh : public Transform
{
public:
	Mesh();
	~Mesh();

	// Load a mesh and send it to OpenGL
	bool LoadFromFile(const std::string &file);
	bool SetAnimations(int frame1, int frame2);
	bool SetNextAnimation(int frame);
	bool PlayNextAnimation();

	void SetTexture(Texture* tex) { Tex = tex; }
	void SetTextures(Texture* tex, Texture* texEmissive) { Tex = tex; TexEmissive = texEmissive; }
	void setCulling(bool a) { culling = a; }

	// Release data from OpenGL (VRAM)
	void Unload();

	unsigned int GetNumFrames() const;
	unsigned int GetNumFaces() const;
	unsigned int GetNumVertices() const;

	void drawNoTex() const;
	void draw() const;

	float interp = 0;
	int animIndex = 0;
	int lastAnim = 0;

	// OpenGL ready data
	std::vector<std::vector<float>>unPackedVertexData;
	std::vector<std::vector<float>>unPackedTextureData;
	std::vector<std::vector<float>>unPackedNormalData;
private:

	// OpenGL buffers and objects
	GLuint VBO_Vertices = 0;
	GLuint VBO_UVs = 0;
	GLuint VBO_Normals = 0;
	GLuint VBO_Vertices2 = 0;
	GLuint VBO_UVs2 = 0;
	GLuint VBO_Normals2 = 0;
	GLuint VAO = 0;

	bool culling = true;

	Texture* Tex;
	Texture* TexEmissive;

	std::string filename;

	int _NumFrames = 0;
	unsigned int _NumFaces = 0;
	unsigned int _NumVertices = 0;
};
#pragma once
#include <GL\glew.h>
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture();

	bool Load(const std::string &file);
	bool Load3D(const std::string &file);
	void unload();

	void bind(int textureSlot) const;
	void unbind(int textureSlot) const;

	void bind3D(int textureSlot) const;
	void unbind3D(int textureSlot) const;

	void SetNearestFilter();

	int getLUTsize() { return LUTsize; }
	// Handle to the texture object
	GLuint TexObj = GL_NONE;
	unsigned int LUTsize = 0;
};

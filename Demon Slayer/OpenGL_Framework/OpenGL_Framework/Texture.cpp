#include "Texture.h"
#include "SOIL/SOIL.h"
#include "Vector.h"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>

Texture::~Texture()
{
	unload();
}

bool Texture::Load(const std::string &file)
{
	TexObj = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (TexObj == 0)
	{
		std::cout << file << " failed to load.\n" << SOIL_last_result() << '\n';
		return false;
	}

	// Modify texture
	glBindTexture(GL_TEXTURE_2D, TexObj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // u axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // v axis

	return true;
}

bool Texture::Load3D(const std::string & file)
{
	std::vector<vec3> LUT;

	std::ifstream lines(file.c_str());

	std::string LUTline;
	int size = 0;
	vec3 line;

	while (!lines.eof())
	{
		std::getline(lines, LUTline);

		if (LUTline.empty()) continue;

		if (sscanf_s(LUTline.c_str(), "%f %f %f", &line.x, &line.y, &line.z) == 3) LUT.push_back(line);
		else if (sscanf_s(LUTline.c_str(), "LUT_3D_SIZE %i", &size) == 1) LUTsize = size;
	}
	if (LUT.size() != (pow(LUTsize, 3.0)))
	{
		std::cout << "LUT size is incorrect.";
		return false;
	}

	glGenTextures(1, &TexObj);
	glBindTexture(GL_TEXTURE_3D, TexObj);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, LUTsize, LUTsize, LUTsize, 0, GL_RGB, GL_FLOAT, &LUT[0]);

	glBindTexture(GL_TEXTURE_3D, GL_NONE);
	return true;
}

void Texture::unload()
{
	if (TexObj != 0)
	{
		//remove data from GPU
		glDeleteTextures(1, &TexObj);
		TexObj = 0;
	}
}

void Texture::bind(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexObj);
}

void Texture::unbind(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Texture::bind3D(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_3D, TexObj);
}

void Texture::unbind3D(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_3D, GL_NONE);
}

void Texture::SetNearestFilter()
{
	glBindTexture(GL_TEXTURE_2D, TexObj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
}
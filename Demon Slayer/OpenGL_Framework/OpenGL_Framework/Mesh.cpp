#define _CRT_SECURE_NO_WARNINGS

#include "Mesh.h"
#include <fstream>
#include <iostream>
#include "Vector.h"

#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i)((char *)0+(i))

struct MeshFace
{
	MeshFace()
	{
		vertices[0] = 0;
		vertices[1] = 0;
		vertices[2] = 0;

		textureUVs[0] = 0;
		textureUVs[1] = 0;
		textureUVs[2] = 0;

		normals[0] = 0;
		normals[1] = 0;
		normals[2] = 0;
	}

	MeshFace(unsigned v1, unsigned v2, unsigned v3,
		unsigned t1, unsigned t2, unsigned t3,
		unsigned n1, unsigned n2, unsigned n3)
	{
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;

		textureUVs[0] = t1;
		textureUVs[1] = t2;
		textureUVs[2] = t3;

		normals[0] = n1;
		normals[1] = n2;
		normals[2] = n3;
	}

	unsigned vertices[3];
	unsigned textureUVs[3];
	unsigned normals[3];
};

Mesh::Mesh()
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO_Vertices);
	glGenBuffers(1, &VBO_UVs);
	glGenBuffers(1, &VBO_Normals);
	glGenBuffers(1, &VBO_Vertices2);
	glGenBuffers(1, &VBO_UVs2);
	glGenBuffers(1, &VBO_Normals2);
}

Mesh::~Mesh()
{

}

// Load a mesh, and send it to OpenGL
bool Mesh::LoadFromFile(const std::string &file)
{
	filename = file;
	std::ifstream input;
	input.open(file);

	if (!input)
	{
		std::cout << "Could not open " << file << std::endl;
		return false;
	}

	char inputString[CHAR_BUFFER_SIZE];

	// Unique data
	std::vector<vec3>vertexData;
	std::vector<vec2>textureData;
	std::vector<vec3>normalData;

	// Index/Face data
	std::vector<MeshFace>faceData;

	// Temporary data vectors
	std::vector<float>TempUnPackedVertexData;
	std::vector<float>TempUnPackedTextureData;
	std::vector<float>TempUnPackedNormalData;

	while (!input.eof())
	{
		input.getline(inputString, CHAR_BUFFER_SIZE);

		if (std::strstr(inputString, "#") != nullptr)
		{
			// This line is a comment
			continue;
		}
		else if (std::strstr(inputString, "vn") != nullptr)
		{
			// This line has Normal data
			vec3 temp;

			std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			normalData.push_back(temp);
		}
		else if (std::strstr(inputString, "vt") != nullptr)
		{
			// This line has UV data
			vec2 temp;

			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "v") != nullptr)
		{
			// This line has Vertex data
			vec3 temp;

			std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			vertexData.push_back(temp);
		}
		else  if (inputString[0] == 'f')
		{
			// This line has Face data
			MeshFace temp;

			std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&temp.vertices[0], &temp.textureUVs[0], &temp.normals[0],
				&temp.vertices[1], &temp.textureUVs[1], &temp.normals[1],
				&temp.vertices[2], &temp.textureUVs[2], &temp.normals[2]);

			faceData.push_back(temp);
		}
	}
	input.close();
	// Unpack the data
	for (unsigned i = 0; i < faceData.size(); i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{
			TempUnPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
			TempUnPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
			TempUnPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

			TempUnPackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].x);
			TempUnPackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].y);

			TempUnPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].x);
			TempUnPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].y);
			TempUnPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].z);
		}
	}

	unPackedVertexData.push_back(TempUnPackedVertexData);
	unPackedTextureData.push_back(TempUnPackedTextureData);
	unPackedNormalData.push_back(TempUnPackedNormalData);

	_NumFrames++;
	_NumFaces = faceData.size();
	_NumVertices = _NumFaces * 3;


	vertexData.clear();
	textureData.clear();
	normalData.clear();
	faceData.clear();
	TempUnPackedVertexData.clear();
	TempUnPackedTextureData.clear();
	TempUnPackedNormalData.clear();

	return true;
}

bool Mesh::SetAnimations(int frame1, int frame2)
{
	if (frame1 > _NumFrames - 1 || frame2 > _NumFrames)
	{
		std::cout << "Animation Frame out of range.\n";
		return false;
	}

	if (frame2 == _NumFrames)
		frame2 = 0;

	lastAnim = frame2;
	interp = 0.0f;

	glBindVertexArray(VAO);
	// Send data to OpenGL
	glEnableVertexAttribArray(0); // Vertex
	glEnableVertexAttribArray(1); // UVs
	glEnableVertexAttribArray(2); // Normals

	glEnableVertexAttribArray(3); // Vertex
	glEnableVertexAttribArray(4); // UVs
	glEnableVertexAttribArray(5); // Normals

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedVertexData[frame1].size(), &unPackedVertexData[frame1][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedTextureData[frame1].size(), &unPackedTextureData[frame1][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedNormalData[frame1].size(), &unPackedNormalData[frame1][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Vertices2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedVertexData[frame2].size(), &unPackedVertexData[frame2][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVs2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedTextureData[frame2].size(), &unPackedTextureData[frame2][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedNormalData[frame2].size(), &unPackedNormalData[frame2][0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)5, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	// Cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

bool Mesh::SetNextAnimation(int frame)
{
	if (SetAnimations(lastAnim, frame))
		return true;
	else
		return false;
}

bool Mesh::PlayNextAnimation()
{
	if (SetAnimations(lastAnim, lastAnim + 1))
		return true;
	else
		return false;
}

// Release data from OpenGL (VRAM)
void Mesh::Unload()
{
	glDeleteBuffers(1, &VBO_Normals);
	glDeleteBuffers(1, &VBO_UVs);
	glDeleteBuffers(1, &VBO_Vertices);
	glDeleteBuffers(1, &VBO_Normals2);
	glDeleteBuffers(1, &VBO_UVs2);
	glDeleteBuffers(1, &VBO_Vertices2);
	glDeleteVertexArrays(1, &VAO);

	VBO_Normals = 0;
	VBO_UVs = 0;
	VBO_Vertices = 0;
	VBO_Normals2 = 0;
	VBO_UVs2 = 0;
	VBO_Vertices2 = 0;
	VAO = 0;

	unPackedVertexData.clear();
	unPackedTextureData.clear();
	unPackedNormalData.clear();

	interp = 0;

	_NumFrames = 0;
	_NumFaces = 0;
	_NumVertices = 0;
}

unsigned int Mesh::GetNumFrames() const
{
	return _NumFrames;
}

unsigned int Mesh::GetNumFaces() const
{
	return _NumFaces;
}

unsigned int Mesh::GetNumVertices() const
{
	return _NumVertices;
}

void Mesh::drawNoTex() const
{
	if (!culling)
		glDisable(GL_CULL_FACE);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, _NumVertices);
	glBindVertexArray(0);

	if (!culling)
		glEnable(GL_CULL_FACE);
}

void Mesh::draw() const
{
	if (!culling)
		glDisable(GL_CULL_FACE);

	if (Tex == nullptr)
	{
		std::cout << filename << " texture not bound!\n";
		system("pause");
	}
	Tex->bind(0);
	TexEmissive->bind(1);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, _NumVertices);
	glBindVertexArray(0);
	Tex->unbind(1);
	Tex->unbind(0);

	if (!culling)
		glEnable(GL_CULL_FACE);
}

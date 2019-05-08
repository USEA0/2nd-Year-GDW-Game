#pragma once
#include <GL\glew.h>

class FrameBuffer
{
public:
	FrameBuffer() = delete;
	FrameBuffer(unsigned numColorAttachments);
	~FrameBuffer();

	void InitDepthTexture(unsigned width, unsigned height);
	void InitColorTexture(unsigned index, unsigned width, unsigned height, GLint internalFormat, GLint filter, GLint wrap);
	bool CheckFBO();

	//Clear openGL memory
	void unload();

	//Clear attached textures
	void clear();

	void bind();
	void unbind();
	void bindColor(unsigned index, int textureSlot);
	void bindDepth(int textureSlot);
	void unbind(int textureSlot);

	void MoveToBackBuffer(int windowWidth, int windowHeight);

	GLuint GetDepthHandle() const;
	GLuint GetColorHandle(unsigned index) const;

private:
	GLuint _FBO = GL_NONE;
	GLuint _DepthAttachment = GL_NONE;
	GLuint *_ColorAttachments = nullptr;
	GLenum *_Bufs = nullptr;

	unsigned int _NumColorAttachments = 0;
};
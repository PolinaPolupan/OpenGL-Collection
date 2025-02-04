#pragma once

#include <glad/glad.h>
#include "Texture.h"

class Renderbuffer;

class Framebuffer {
public:
	class Builder {
	public:
		friend class Framebuffer;

		Builder();

	private:
		GLenum m_Target;
	};

	Framebuffer(Builder& builder);
	Framebuffer();
	~Framebuffer();

	void Bind() const;
	void Unbind() const;

	void AttachTexture(
		GLenum attachment,
		GLenum textarget, 
		GLuint texture = GL_TEXTURE_2D,
		GLint level = 0) const;

	void AttachTexture(
		const Texture& texture,
		GLenum attachment,
		GLenum textarget = GL_TEXTURE_2D,
		GLint level = 0) const;

	void AttachRenderBuffer(const Renderbuffer& renderbuffer, GLenum attachment) const;

	void DrawBuffers(GLsizei n, const GLenum* bufs) const;
	void DrawBuffers(GLsizei n, const std::vector<GLenum>& bufs) const;

private:
	unsigned int m_RendererId;
	GLenum m_Target;
};
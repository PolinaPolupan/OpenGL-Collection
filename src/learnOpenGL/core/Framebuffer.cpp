#include "Framebuffer.h"

#include "Renderer.h"
#include "Renderbuffer.h"


Framebuffer::Framebuffer(): 
	Framebuffer(Builder()) {}

Framebuffer::Framebuffer(Builder& builder):
	m_RendererId(0)
{
	m_Target = builder.m_Target;

	GLCall(glGenFramebuffers(1, &m_RendererId));

	if (glCheckFramebufferStatus(m_Target) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

Framebuffer::~Framebuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererId));
}

void Framebuffer::Bind() const
{
	GLCall(glBindFramebuffer(m_Target, m_RendererId));
}

void Framebuffer::Unbind() const
{
	GLCall(glBindFramebuffer(m_Target, 0));
}

void Framebuffer::AttachTexture(GLenum attachment, GLenum textarget, GLuint texture, GLint level) const
{
	Bind();
	GLCall(glFramebufferTexture2D(m_Target, attachment, textarget, texture, level));
}

void Framebuffer::AttachTexture(const Texture& texture, GLenum attachment, GLenum textarget, GLint level) const
{
	Bind();
	GLCall(glFramebufferTexture2D(m_Target, attachment, textarget, texture.GetId(), level));
}

void Framebuffer::AttachRenderBuffer(const Renderbuffer& renderbuffer, GLenum attachment) const
{
	Bind();
	GLCall(glFramebufferRenderbuffer(m_Target, attachment, GL_RENDERBUFFER, renderbuffer.GetId()));
}

void Framebuffer::DrawBuffers(GLsizei n, const GLenum* bufs) const
{
	Bind();
	GLCall(glDrawBuffers(n, bufs));
}

void Framebuffer::DrawBuffers(GLsizei n, const std::vector<GLenum>& bufs) const
{
	Bind();
	GLCall(glDrawBuffers(n, &bufs[0]));
}

Framebuffer::Builder::Builder():
	m_Target(GL_FRAMEBUFFER) {}

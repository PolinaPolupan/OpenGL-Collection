#include "Renderbuffer.h"

#include "Renderer.h"

Renderbuffer::Renderbuffer(): 
	Renderbuffer(Builder()) {}

Renderbuffer::Renderbuffer(Builder& builder):
	m_RendererId(0)
{
	m_Target = builder.m_Target;

	GLCall(glGenRenderbuffers(1, &m_RendererId));
}

Renderbuffer::~Renderbuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererId));
}

void Renderbuffer::Bind() const
{
	GLCall(glBindRenderbuffer(m_Target, m_RendererId));
}

void Renderbuffer::Unbind() const
{
	GLCall(glBindRenderbuffer(m_Target, 0));
}

void Renderbuffer::SetStorage(GLenum internalformat, GLsizei width, GLsizei height, GLsizei samples) const
{
	if (samples > 0) {
		glRenderbufferStorageMultisample(m_Target, samples, internalformat, width, height);
	}
	else {
		glRenderbufferStorage(m_Target, internalformat, width, height);
	}
}

Renderbuffer::Builder::Builder():
	m_Target(GL_RENDERBUFFER) {}

#pragma once


class Renderbuffer {
public:

	class Builder {
	public:
		friend class Renderbuffer;
		Builder();

	private:
		GLenum m_Target;
	};

	Renderbuffer();
	Renderbuffer(Builder& builder);
	~Renderbuffer();

	void Bind() const;
	void Unbind() const;

	inline const unsigned int GetId() const { return m_RendererId; }
	void SetStorage(GLenum internalformat, GLsizei width, GLsizei height, GLsizei samples = 0) const;

private:
	unsigned int m_RendererId;
	GLenum m_Target;
};
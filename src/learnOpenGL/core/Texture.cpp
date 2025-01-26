#include "Texture.h"

#include "../stb_image/stb_image.h"

Texture::Texture(const std::string& path, TextureType textureType, bool gammaCorrection)
	: m_RendererId(0), m_FilePath(path.c_str()), m_LocalBuffer(nullptr),
	  m_TextureType(textureType),
	  m_Width(0), m_Height(0), m_BPP(0)
{
	if (path.find(".hdr") != std::string::npos) {
		InitHdr(path.c_str(), textureType, gammaCorrection);
	}
	else {
		Init(path.c_str(), textureType, gammaCorrection);
	}
}

Texture::Texture(const char * path, TextureType textureType, bool gammaCorrection)
	: m_RendererId(0), m_FilePath(path), m_LocalBuffer(nullptr),
	  m_TextureType(textureType),
	  m_Width(0), m_Height(0), m_BPP(0)
{
	std::string pathStr = std::string(path);
	if (pathStr.find(".hdr") != std::string::npos) {
		InitHdr(path, textureType, gammaCorrection);
	}
	else {
		Init(path, textureType, gammaCorrection);
	}
}

Texture::Texture(const std::filesystem::path& path, TextureType textureType, bool gammaCorrection)
	: m_RendererId(0), m_FilePath(path.string()), m_LocalBuffer(nullptr),
	m_TextureType(textureType),
	m_Width(0), m_Height(0), m_BPP(0)
{
	if (path.extension() == ".hdr") {
		InitHdr(path.string().c_str(), textureType, gammaCorrection);
	}
	else {
		Init(path.string().c_str(), textureType, gammaCorrection);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererId));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Init(const char* path, TextureType textureType, bool gammaCorrection)
{
	stbi_set_flip_vertically_on_load(1);

	m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

	GLenum internalFormat;
	GLenum dataFormat;

	if (m_BPP == 1)
	{
		internalFormat = dataFormat = GL_RED;
	}
	else if (m_BPP == 3)
	{
		internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
		dataFormat = GL_RGB;
	}
	else if (m_BPP == 4)
	{
		internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
		dataFormat = GL_RGBA;
	}

	GLCall(glGenTextures(1, &m_RendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

void Texture::InitHdr(const char* path, TextureType textureType, bool gammaCorrection)
{
	stbi_set_flip_vertically_on_load(1);

	float* data = stbi_loadf(path, &m_Width, &m_Height, &m_BPP, 0);

	GLenum dataFormat = GL_RGB;

	if (m_BPP == 1)
	{
		dataFormat = GL_RED;
	}
	else if (m_BPP == 3)
	{
		dataFormat = GL_RGB;
	}
	else if (m_BPP == 4)
	{
		dataFormat = GL_RGBA;
	}

	GLCall(glGenTextures(1, &m_RendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Width, m_Height, 0, dataFormat, GL_FLOAT, data));
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();

	if (data)
		stbi_image_free(data);
}

#include "Texture.h"


Texture::Texture(const std::filesystem::path& path, Type textureType, bool gammaCorrection): 
	Texture(path.string(), textureType, gammaCorrection) {}

Texture::Texture(const std::string& path, Type textureType, bool gammaCorrection): 
	Texture(path.c_str(), textureType, gammaCorrection) {}

Texture::Texture(const char* path, Type textureType, bool gammaCorrection): 
	Texture(Builder()
		.SetImage(path, gammaCorrection)
		.SetParameters(Parameters().Default2D())) {}

Texture::Texture(Builder& builder):
	m_RendererId(0),
	m_LocalBuffer(nullptr)
{
	m_LocalBuffer = builder.m_LocalBuffer;
	m_Width = builder.m_Width;
	m_Height = builder.m_Height;
	m_BPP = builder.m_BPP;
	m_Parameters = builder.m_Parameters;
	m_Type = builder.m_Type;
	m_Target = builder.m_Target;
	m_DataFormat = builder.m_DataFormat;
	m_InternalFormat = builder.m_InternalFormat;
	m_Type = builder.m_Type;
	m_TextureType = builder.m_TextureType;
	m_FilePath = builder.m_FilePath;

	if (m_Target == GL_TEXTURE_CUBE_MAP) BuildCubemap();
	else Build();
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererId));
	if (m_LocalBuffer) {
		free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(m_Target, m_RendererId));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(m_Target, 0));
}

const char* Texture::GetTextureTypeName() const
{
	switch (m_TextureType)
	{
	case Type::Diffuse:
		return "diffuse";
	case Type::Specular:
		return "specular";
	case Type::Emission:
		return "emission";
	case Type::Height:
		return "height";
	case Type::Normal:
		return "normal";
	case Type::Standard:
		return "standard";
	}
}

void Texture::Build()
{
	GLCall(glGenTextures(1, &m_RendererId));
	GLCall(glBindTexture(m_Target, m_RendererId));

	GLCall(glTexImage2D(m_Target, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, m_Type, m_LocalBuffer));
	glGenerateMipmap(m_Target);

	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_Parameters.wrapS));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_Parameters.wrapT));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, m_Parameters.wrapR));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_Parameters.minFilter));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_Parameters.magFilter));

	Unbind();

	if (m_LocalBuffer) {
		free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}
}

void Texture::BuildCubemap()
{
	GLCall(glGenTextures(1, &m_RendererId));
	m_Target = GL_TEXTURE_CUBE_MAP;
	GLCall(glBindTexture(m_Target, m_RendererId));

	for (unsigned int i = 0; i < 6; ++i) {
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, m_Type, m_LocalBuffer));
	}
	glGenerateMipmap(m_Target);

	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_Parameters.wrapS));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_Parameters.wrapT));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, m_Parameters.wrapR));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_Parameters.minFilter));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_Parameters.magFilter));

	Unbind();

	if (m_LocalBuffer) {
		free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}
}

Texture::Builder::Builder():
	m_Target(GL_TEXTURE_2D),
	m_Type(GL_UNSIGNED_BYTE),
	m_TextureType(Type::Diffuse),
	m_BPP(0),
	m_Width(0),
	m_Height(0),
	m_InternalFormat(GL_RGBA8),
	m_DataFormat(GL_RGB),
	m_LocalBuffer(nullptr),
	m_Parameters(Parameters::Default2D()) {}

Texture::Builder& Texture::Builder::SetTarget(GLenum target) {
	m_Target = target;
	return *this;
}

Texture::Builder& Texture::Builder::SetType(GLenum type) {
	m_Type = type;
	return *this;
}

Texture::Builder& Texture::Builder::SetInternalFormat(GLenum internalFormat) {
	m_InternalFormat = internalFormat;
	return *this;
}

Texture::Builder& Texture::Builder::SetDataFormat(GLenum dataFormat) {
	m_DataFormat = dataFormat;
	return *this;
}

Texture::Builder& Texture::Builder::SetSize(int w, int h) {
	m_Width = w;
	m_Height = h;
	return *this;
}

Texture::Builder& Texture::Builder::SetParameters(const Parameters& params) {
	m_Parameters = params;
	return *this;
}

Texture::Builder& Texture::Builder::SetImage(const std::filesystem::path& path, bool gammaCorrection, bool flip) {
	return SetImage(path.string(), gammaCorrection, flip);
}

Texture::Builder& Texture::Builder::SetImage(const std::string& path, bool gammaCorrection, bool flip) {
	return SetImage(path.c_str(), gammaCorrection, flip);
}

Texture::Builder& Texture::Builder::SetImage(const char* path, bool gammaCorrection, bool flip) {
	stbi_set_flip_vertically_on_load(flip);

	std::string pathStr = std::string(path);
	m_FilePath = pathStr;

	if (pathStr.find(".hdr") != std::string::npos) {
		m_InternalFormat = GL_RGB16F;
		m_Type = GL_FLOAT;

		m_LocalBuffer = stbi_loadf(path, &m_Width, &m_Height, &m_BPP, 0);

		if (m_BPP == 1)
		{
			m_DataFormat = GL_RED;
		}
		else if (m_BPP == 3)
		{
			m_DataFormat = GL_RGB;
		}
		else if (m_BPP == 4)
		{
			m_DataFormat = GL_RGBA;
		}
	}
	else {
		m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

		if (m_BPP == 1)
		{
			m_InternalFormat = m_DataFormat = GL_RED;
		}
		else if (m_BPP == 3)
		{
			m_InternalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			m_DataFormat = GL_RGB;
		}
		else if (m_BPP == 4)
		{
			m_InternalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			m_DataFormat = GL_RGBA;
		}
	}

	return *this;
}

Texture::Builder& Texture::Builder::SetBuffer(void* buffer, unsigned int size) {
	if (buffer) {
		if (m_LocalBuffer) free(m_LocalBuffer);		
		m_LocalBuffer = malloc(size);
		memcpy(m_LocalBuffer, buffer, size);
	}
	
	return *this;
}

Texture& Texture::Builder::Build() {
	return Texture(*this);
}


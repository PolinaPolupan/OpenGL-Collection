#include "Texture.h"


Texture::Texture():
	m_RendererId(0),  
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0), 
	m_BPP(0)
{}

Texture::Texture(TextureBuilder & builder)
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

	if (m_Target == GL_TEXTURE_CUBE_MAP) BuildCubemap();
	else Build();
}

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
	case TextureType::Diffuse:
		return "diffuse";
	case TextureType::Specular:
		return "specular";
	case TextureType::Emission:
		return "emission";
	case TextureType::Height:
		return "height";
	case TextureType::Normal:
		return "normal";
	case TextureType::Standard:
		return "standard";
	}
}

void Texture::Init(const char* path, TextureType textureType, bool gammaCorrection)
{
	stbi_set_flip_vertically_on_load(1);

	m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

	GLenum internalFormat;
	GLenum dataFormat = GL_RGBA;

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
	GLCall(glBindTexture(m_Target, m_RendererId));

	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(m_Target, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));
	glGenerateMipmap(m_Target);
	Unbind();

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}		
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
	GLCall(glBindTexture(m_Target, m_RendererId));

	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexImage2D(m_Target, 0, GL_RGB16F, m_Width, m_Height, 0, dataFormat, GL_FLOAT, data));
	glGenerateMipmap(m_Target);
	Unbind();

	if (data)
		stbi_image_free(data);
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

Texture::TextureBuilder::TextureBuilder() :
	m_Target(GL_TEXTURE_2D),
	m_Type(GL_UNSIGNED_BYTE),
	m_TextureType(TextureType::Diffuse),
	m_BPP(0),
	m_Width(0),
	m_Height(0),
	m_InternalFormat(GL_RGBA8),
	m_DataFormat(GL_RGB),
	m_LocalBuffer(nullptr),
	m_Parameters(TextureParameters::Default2D()) {}

Texture::TextureBuilder& Texture::TextureBuilder::SetTarget(GLenum target) {
	m_Target = target;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetType(GLenum type) {
	m_Type = type;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetInternalFormat(GLenum internalFormat) {
	m_InternalFormat = internalFormat;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetDataFormat(GLenum dataFormat) {
	m_DataFormat = dataFormat;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetSize(int w, int h) {
	m_Width = w;
	m_Height = h;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetParameters(const TextureParameters& params) {
	m_Parameters = params;
	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetImage(const std::filesystem::path& path, bool gammaCorrection, bool flip) {
	return SetImage(path.string(), gammaCorrection, flip);
}

Texture::TextureBuilder& Texture::TextureBuilder::SetImage(const std::string& path, bool gammaCorrection, bool flip) {
	return SetImage(path.c_str(), gammaCorrection, flip);
}

Texture::TextureBuilder& Texture::TextureBuilder::SetImage(const char* path, bool gammaCorrection, bool flip) {
	stbi_set_flip_vertically_on_load(flip);

	m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 0);

	m_DataFormat = GL_RGB;

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

	std::string pathStr = std::string(path);
	if (pathStr.find(".hdr") != std::string::npos) {
		m_InternalFormat = GL_RGB16F;
		m_Type = GL_FLOAT;
	}

	return *this;
}

Texture::TextureBuilder& Texture::TextureBuilder::SetBuffer(unsigned char* buffer, unsigned int size) {
	if (buffer) {
		if (m_LocalBuffer) delete[] m_LocalBuffer;		
		m_LocalBuffer = (unsigned char*)malloc(size);
		memcpy(m_LocalBuffer, buffer, size);
	}
	
	return *this;
}

Texture& Texture::TextureBuilder::Build() {
	return Texture(*this);
}


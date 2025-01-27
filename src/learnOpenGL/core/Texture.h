#pragma once


#include "../stb_image/stb_image.h"
#include "Renderer.h"
#include <filesystem>

struct TextureParameters {

    GLint wrapS;
    GLint wrapT;
    GLint wrapR;
    GLint minFilter;
    GLint magFilter;

    constexpr TextureParameters(
        GLint wrapS = GL_REPEAT,
        GLint wrapT = GL_REPEAT,
        GLint wrapR = GL_REPEAT,
        GLint minFilter = GL_LINEAR,
        GLint magFilter = GL_LINEAR
    ) : wrapS(wrapS), wrapT(wrapT), wrapR(wrapR), minFilter(minFilter), magFilter(magFilter) {}

    static constexpr TextureParameters Default2D() {
        return { GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR };
    }

    static constexpr TextureParameters DefaultCubeMap() {
        return { GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR };
    }

    static constexpr TextureParameters NearestFilter() {
        return { GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST };
    }
};

enum TextureType
{
    Diffuse,
    Specular,
    Emission,
    Standard,
    Height,
    Normal
};

class Texture
{
public:	

    class TextureBuilder {
    private:
        GLint m_Target = GL_TEXTURE_2D;
        GLenum m_Type;
        int m_Width, m_Height;
        int m_BPP;
        GLenum m_InternalFormat, m_DataFormat;
        unsigned char* m_LocalBuffer;
        TextureParameters m_Parameters;
        TextureType m_TextureType;

    public:
        friend class Texture;

        TextureBuilder() :
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

        TextureBuilder& SetTarget(GLenum target) {
            m_Target = target;
            return *this;
        }

        TextureBuilder& SetType(GLenum type) {
            m_Type = type;
            return *this;
        }

        TextureBuilder& SetInternalFormat(GLenum internalFormat) {
            m_InternalFormat = internalFormat;
            return *this;
        }

        TextureBuilder& SetDataFormat(GLenum dataFormat) {
            m_DataFormat = dataFormat;
            return *this;
        }

        TextureBuilder& SetSize(int w, int h) {
            m_Width = w;
            m_Height = h;
            return *this;
        }

        TextureBuilder& SetParameters(const TextureParameters& params) {
            m_Parameters = params;
            return *this;
        }

        TextureBuilder& SetImage(const std::filesystem::path& path, bool gammaCorrection = false, bool flip = true) {
            SetImage(path.string(), gammaCorrection, flip);
        }

        TextureBuilder& SetImage(const std::string& path, bool gammaCorrection = false, bool flip = true) {
            SetImage(path.c_str(), gammaCorrection, flip);
        }

        TextureBuilder& SetImage(const char* path, bool gammaCorrection = false, bool flip = true) {
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
        }

        Texture& Build() {
            return Texture(*this);
        }
    };

	Texture();
	Texture(const Texture::TextureBuilder& builder);
	Texture(const std::string& path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);
	Texture(const char* path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);  
	Texture(const std::filesystem::path& path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);
	~Texture();

	virtual void Bind(unsigned int slot = 0) const;
	virtual void Unbind() const;

	inline void SetType(GLint type) { m_Type = type; }
	inline void SetParameters(const TextureParameters& parameters) { m_Parameters = parameters; }
	inline void SetResolution(const glm::vec2& res) { m_Width = res.x, m_Height = res.y; }
	inline void SetId(unsigned int id) { m_RendererId = id; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetId() const { return m_RendererId; }
	inline std::string GetPath() const { return m_FilePath; }
	inline TextureType GetType() const { return m_TextureType; }
	inline const char* GetTextureTypeName()
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


	void Init(const char* path, TextureType textureType, bool gammaCorrection);
	void InitHdr(const char* path, TextureType textureType, bool gammaCorrection);

	void Build();
	void BuildCubemap();

protected:
	unsigned int m_RendererId;
	std::string m_FilePath;
	TextureType m_TextureType;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	TextureParameters m_Parameters;
	GLenum m_InternalFormat, m_DataFormat;
	GLenum m_Target = GL_TEXTURE_2D;
	GLenum m_Type;
};

#pragma once


#include "../stb_image/stb_image.h"
#include "Renderer.h"
#include <filesystem>


class Texture
{
public:	

    enum TextureType
    {
        Diffuse,
        Specular,
        Emission,
        Standard,
        Height,
        Normal
    };


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


    class TextureBuilder {
    public:
        friend class Texture;

        TextureBuilder();
        ~TextureBuilder();

        TextureBuilder& SetTarget(GLenum target);
        TextureBuilder& SetType(GLenum type);
        TextureBuilder& SetInternalFormat(GLenum internalFormat);
        TextureBuilder& SetDataFormat(GLenum dataFormat);
        TextureBuilder& SetSize(int w, int h);
        TextureBuilder& SetParameters(const TextureParameters& params);
        TextureBuilder& SetImage(const std::filesystem::path& path, bool gammaCorrection = false, bool flip = true);
        TextureBuilder& SetImage(const std::string& path, bool gammaCorrection = false, bool flip = true);
        TextureBuilder& SetImage(const char* path, bool gammaCorrection = false, bool flip = true);

        Texture& Build();

    private:
        GLint m_Target = GL_TEXTURE_2D;
        GLenum m_Type, m_InternalFormat, m_DataFormat;
        int m_Width, m_Height, m_BPP;
        unsigned char* m_LocalBuffer;
        TextureParameters m_Parameters;
        TextureType m_TextureType;
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
    const char* GetTextureTypeName() const;

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

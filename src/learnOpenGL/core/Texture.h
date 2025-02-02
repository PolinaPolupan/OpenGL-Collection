#pragma once


#include "../stb_image/stb_image.h"
#include "Renderer.h"
#include <filesystem>


class Texture
{
public:	

    enum Type
    {
        Diffuse,
        Specular,
        Emission,
        Standard,
        Height,
        Normal
    };

    struct Parameters {

        GLint wrapS;
        GLint wrapT;
        GLint wrapR;
        GLint minFilter;
        GLint magFilter;

        constexpr Parameters(
            GLint wrapS = GL_REPEAT,
            GLint wrapT = GL_REPEAT,
            GLint wrapR = GL_REPEAT,
            GLint minFilter = GL_LINEAR,
            GLint magFilter = GL_LINEAR
        ) : wrapS(wrapS), wrapT(wrapT), wrapR(wrapR), minFilter(minFilter), magFilter(magFilter) {}

        static constexpr Parameters Default2D() {
            return { GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR };
        }

        static constexpr Parameters DefaultCubeMap() {
            return { GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR };
        }

        static constexpr Parameters NearestFilter() {
            return { GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST };
        }
    };


    class Builder {
    public:
        friend class Texture;

        Builder();

        Builder& SetTarget(GLenum target);
        Builder& SetType(GLenum type);
        Builder& SetInternalFormat(GLenum internalFormat);
        Builder& SetDataFormat(GLenum dataFormat);
        Builder& SetSize(int w, int h);
        Builder& SetParameters(const Parameters& params);
        Builder& SetImage(const std::filesystem::path& path, bool gammaCorrection = false, bool flip = true);
        Builder& SetImage(const std::string& path, bool gammaCorrection = false, bool flip = true);
        Builder& SetImage(const char* path, bool gammaCorrection = false, bool flip = true);
        Builder& SetBuffer(void* buffer, unsigned int size);

        Texture& Build();

    private:
        void* m_LocalBuffer;
        int m_Width,
            m_Height,
            m_BPP;
        GLenum
            m_InternalFormat,
            m_DataFormat,
            m_Target,
            m_Type;
        std::string m_FilePath;
        Parameters m_Parameters;
        Type m_TextureType;
    };

	Texture(Texture::Builder& builder);
    Texture(const Texture& texture) = delete;
	Texture(const std::string& path, Type textureType = Type::Diffuse, bool gammaCorrection = false);
	Texture(const char* path, Type textureType = Type::Diffuse, bool gammaCorrection = false);  
	Texture(const std::filesystem::path& path, Type textureType = Type::Diffuse, bool gammaCorrection = false);
	~Texture();

	virtual void Bind(unsigned int slot = 0) const;
	virtual void Unbind() const;

	inline void SetType(GLint type) { m_Type = type; }
	inline void SetParameters(const Parameters& parameters) { m_Parameters = parameters; }
	inline void SetResolution(const glm::vec2& res) { m_Width = res.x, m_Height = res.y; }
	inline void SetId(unsigned int id) { m_RendererId = id; }
	
    inline const GLenum GetTarget() const { return m_Target; }
    inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetId() const { return m_RendererId; }
	inline std::string GetPath() const { return m_FilePath; }
	inline Type GetType() const { return m_TextureType; }
    const char* GetTextureTypeName() const;

	void Build();
	void BuildCubemap();

private:
	unsigned int m_RendererId;	
	void* m_LocalBuffer;
	int m_Width, 
        m_Height, 
        m_BPP;	
	GLenum 
        m_InternalFormat,
        m_DataFormat,
        m_Target,
        m_Type;
    std::string m_FilePath;
    Parameters m_Parameters;
    Type m_TextureType;
};

#pragma once

#include "Renderer.h"
#include <filesystem>

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
	Texture(const std::string& path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);
	Texture(const char* path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);  
	Texture(const std::filesystem::path& path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

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

private:
	void Init(const char* path, TextureType textureType, bool gammaCorrection);
	void InitHdr(const char* path, TextureType textureType, bool gammaCorrection);

private:
	unsigned int m_RendererId;
	std::string m_FilePath;
	TextureType m_TextureType;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

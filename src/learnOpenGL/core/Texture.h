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
private:

	unsigned int m_RendererId;
	std::string m_FilePath;
	TextureType m_textureType;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	
	Texture(const std::string& path, TextureType textureType=TextureType::Diffuse, bool gammaCorrection = false);
	Texture(const char* path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);  
	Texture(const std::filesystem::path& path, TextureType textureType = TextureType::Diffuse, bool gammaCorrection = false);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline void setId(unsigned int id) { m_RendererId = id; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetId() const { return m_RendererId; }
	inline std::string getPath() const { return m_FilePath; }
	inline TextureType getType() const { return m_textureType; }
	inline const char* getTextureTypeName()
	{
		switch (m_textureType)
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
};

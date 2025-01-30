#pragma once

#include "pch.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace scene {
	class TextRendering: public Scene
	{
	public:
		TextRendering();
		~TextRendering();

		struct Character {
			unsigned int TextureID; // ID handle of the glyph texture
			glm::ivec2   Size;      // Size of glyph
			glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
			unsigned int Advance;   // Horizontal offset to advance to next glyph
		} character;

		std::map<GLchar, Character> characters;
		unsigned int VAO, VBO;
		unsigned int texture;
		FT_Library ft;
		FT_Face face;

		std::shared_ptr<Shader> shader;

		CameraController cameraController;
		Renderer renderer;

		void OnUpdate(float deltaTime) override;
		void OnEvent(int event) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void RenderText(const std::shared_ptr<Shader>& shader, std::string text, float x, float y, float scale, glm::vec3 color);
	};
}
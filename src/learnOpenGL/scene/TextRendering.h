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
			std::shared_ptr<Texture> Texture;
			glm::ivec2   Size;      // Size of glyph
			glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
			unsigned int Advance;   // Horizontal offset to advance to next glyph
		} character;

		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;

		char textBuf[128] = "";
		int size = 48;
		FT_Library ft;
		FT_Face face;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Shader> shader;
		std::vector<std::string> fonts;

		CameraController cameraController;
		Renderer renderer;

		void OnUpdate(float deltaTime) override;
		void OnEvent(int event) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void RenderText(const std::shared_ptr<Shader>& shader, std::string text, float x, float y, glm::vec3 color);
	};
}
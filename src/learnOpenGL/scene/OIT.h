#pragma once

#include "pch.h"

namespace scene
{
	class OIT: public Scene
	{
	public:
		OIT();
		~OIT();

		std::shared_ptr<VertexArray> quadVAO, cubeVAO;
		std::shared_ptr<IndexBuffer> quadIBO, cubeIBO;
		std::shared_ptr<VertexBuffer> quadVBO, cubeVBO;

		std::shared_ptr<Shader> 
			solidShader, 
			transparentShader, 
			compositeShader,
			screenShader;
		std::shared_ptr<Texture> 
			opaqueTexture, 
			depthTexture,
			accumTexture, 
			revealTexture;

		std::shared_ptr<Shader>
			pbrShader,
			pbrTransparentShader,
			equirectangularToCubemapShader,
			backgroundShader,
			irradianceShader,
			prefilterShader,
			brdfShader;
		std::shared_ptr<Texture>
			albedoTexture,
			normalTexture,
			metallicTexture,
			roughnessTexture,
			aoTexture,
			hdr,
			brdfLUTTexture,
			envCubemapTexture,
			irradianceMapTexture,
			prefilterMapTexture;

		std::vector<std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<Texture>> mapTextures;

		CameraController cameraController;
		Renderer renderer;

		std::shared_ptr<Framebuffer> opaqueFBO, transparentFBO, captureFBO;
		std::shared_ptr<Renderbuffer> captureRBO;

		ObjectManager objectManager;
		ObjectManager objectTransparentManager;
		std::vector<std::string> modelsPaths;

		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

		bool PBR = false;
		float transparency = 0.0f;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
		void BakeMaps();
		void RenderPBR(const glm::mat4& view, const glm::mat4& projection);
		void RenderPBRTransparent(const glm::mat4& view, const glm::mat4& projection);
		void MapBrowser(std::shared_ptr<Texture>& texture);
		void ObjectUi(Model& object);
	};
}
#include "SkeletalAnimation.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Animation.h"
#include "Model.h"

scene::SkeletalAnimation::SkeletalAnimation() {

	std::string path = GetResourcePath("res/objects/animation/Talking On Phone.fbx").string();
	Assimp::Importer m_Importer;
	const aiScene* scene = m_Importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << m_Importer.GetErrorString() << std::endl;
		return;
	}

	Animation animation(scene, 0);

	Model model(path);
	model.LoadModel(path);
}

scene::SkeletalAnimation::~SkeletalAnimation()
{
}

void scene::SkeletalAnimation::OnUpdate(float deltaTime)
{
}

void scene::SkeletalAnimation::OnMouseMovedEvent(double posX, double posY)
{
}

void scene::SkeletalAnimation::OnMouseScrolledEvent(double offsetX, double offsetY)
{
}

void scene::SkeletalAnimation::OnRender()
{
}

void scene::SkeletalAnimation::OnImGuiRender()
{
}

void scene::SkeletalAnimation::OnEvent(int event)
{
}

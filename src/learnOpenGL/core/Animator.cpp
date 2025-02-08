#include "Animator.h"

#include "Model.h"
#include "Animation.h"
#include "Constants.h"

Animator::Animator(Model* model, Animation* animation):
	m_CurrentTime(0),
	m_Model(model),
	m_Animation(animation),
	m_BoneMatrices()
{
	for (int i = 0; i < MAX_BONES; i++) {
		m_BoneMatrices.push_back(glm::mat4(1.0f));
	}
}

void Animator::CalculateBoneTransform() {
	for (const auto& bone : m_Model->GetBoneMap()) {
		std::string boneName = bone.first;

		auto& nodesAnimMap = m_Animation->GetNodesAnimMap();

		if (nodesAnimMap.find(boneName) != nodesAnimMap.end()) {
			int index = nodesAnimMap.at(boneName).GetId();

		}
	}
}

#include "Animation.h"

#include <assimp/Importer.hpp>
#include "NodeAnim.h"


Animation::Animation(const aiScene* scene, unsigned int index):
	m_Duration(0),
	m_TicksPerSecond(0)
{
	assert(scene && scene->mRootNode);
	assert(index < scene->mNumAnimations);
	auto animation = scene->mAnimations[index];

	m_Duration = animation->mDuration;
	m_TicksPerSecond = animation->mTicksPerSecond;
	
	ReadAnimNodes(animation);
	std::cout << "Animation " << index << " is proccessed \n";
	std::cout << "Nodes: " << animation->mNumChannels << " \t";
	std::cout << "Duration: " << m_Duration << " \t";
	std::cout << "Ticks per second: " << m_TicksPerSecond << "\n";
}

void Animation::ReadAnimNodes(const aiAnimation* animation) {
	for (int i = 0; i < animation->mNumChannels; i++) {
		m_NodesAnimMap[animation->mChannels[i]->mNodeName.C_Str()] = NodeAnim(i, animation->mChannels[i]);
	}
}

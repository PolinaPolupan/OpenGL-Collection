#pragma once

#include "glm.hpp"
#include <vector>


class Animation;
class Model;

class Animator {
public:
	Animator(Model* model, Animation* animation);

private:
	void CalculateBoneTransform();

private:
	std::vector<glm::mat4> m_BoneMatrices;
	Animation* m_Animation;
	Model* m_Model;
	float m_CurrentTime;
};

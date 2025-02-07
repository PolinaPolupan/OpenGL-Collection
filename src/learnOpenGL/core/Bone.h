#pragma once

#include "glm.hpp"
#include <vector>

struct Bone {
	/* Id is index in finalBoneMatrices */
	int id;

	/* Offset matrix transforms vertex from model space to bone space */
	glm::mat4 offset;

	Bone():
		id(0),
		offset() {}

	Bone(int id, glm::mat4 offest):
		id(id),
		offset(offest) {}
};

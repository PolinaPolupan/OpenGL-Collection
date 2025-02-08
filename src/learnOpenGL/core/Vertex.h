#pragma once

#include "glm.hpp"
#include "Constants.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    int boneIDs[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];

    Vertex(): 
        position(0.0f), 
        normal(0.0f), 
        texCoords(0.0f),
        tangent(0.0f), 
        bitangent(0.0f) {
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
            boneIDs[i] = -1;
            weights[i] = 0.0f;
        }
    }
};

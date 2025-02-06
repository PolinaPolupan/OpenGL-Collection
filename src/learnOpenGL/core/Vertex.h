#pragma once

#include "glm.hpp"

constexpr int MAX_BONE_INFLUENCE = 4;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int BoneIDs[MAX_BONE_INFLUENCE];
    float Weights[MAX_BONE_INFLUENCE];

    Vertex(): 
        Position(0.0f), 
        Normal(0.0f), 
        TexCoords(0.0f),
        Tangent(0.0f), 
        Bitangent(0.0f) {
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
            BoneIDs[i] = -1;
            Weights[i] = 0.0f;
        }
    }
};

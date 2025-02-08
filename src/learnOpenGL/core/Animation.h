#pragma once

#include <map>
#include <filesystem>
#include <assimp/scene.h>

class NodeAnim;

class Animation {
public:
    Animation(const aiScene* scene, unsigned int index = 0);

    inline const std::map<std::string, NodeAnim>& GetNodesAnimMap() const { return m_NodesAnimMap; }

private:
    void ReadAnimNodes(const aiAnimation* animation);

private:
    float m_Duration;
    int m_TicksPerSecond;
    std::map<std::string, NodeAnim> m_NodesAnimMap;
};

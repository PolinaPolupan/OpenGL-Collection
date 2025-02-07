#include "NodeAnim.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "AssimpGLMHelpers.h"


NodeAnim::NodeAnim(const std::string& name, int ID, const aiNodeAnim* channel): 
    m_Name(name),             
    m_Id(ID),                 
    m_LocalTransform(glm::mat4(1.0f))
{
    for (int positionIndex = 0; positionIndex < channel->mNumPositionKeys; ++positionIndex) {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
        data.timeStamp = timeStamp;
        m_Positions.push_back(data);
    }

    for (int rotationIndex = 0; rotationIndex < channel->mNumRotationKeys; ++rotationIndex) {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
        data.timeStamp = timeStamp;
        m_Rotations.push_back(data);
    }

    for (int keyIndex = 0; keyIndex < channel->mNumScalingKeys; ++keyIndex) {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::GetGLMVec(scale);
        data.timeStamp = timeStamp;
        m_Scales.push_back(data);
    }
}

void NodeAnim::Update(float animationTime) {
    glm::mat4 translation = InterpolatePosition(animationTime);
    glm::mat4 rotation = InterpolateRotation(animationTime);
    glm::mat4 scale = InterpolateScaling(animationTime);
    m_LocalTransform = translation * rotation * scale;
}

float NodeAnim::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) {
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}

glm::mat4& NodeAnim::InterpolatePosition(float animationTime) {
    auto& indices = GetAnimationIndices<KeyPosition>(m_Positions, animationTime);
    int p0Index = indices.first;
    int p1Index = indices.second;

    float scaleFactor = GetScaleFactor(m_Positions[p0Index].timeStamp,
        m_Positions[p1Index].timeStamp, animationTime);
    glm::vec3 finalPosition = glm::mix(m_Positions[p0Index].position,
        m_Positions[p1Index].position, scaleFactor);

    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4& NodeAnim::InterpolateRotation(float animationTime) {
    auto& indices = GetAnimationIndices<KeyRotation>(m_Rotations, animationTime);
    int p0Index = indices.first;
    int p1Index = indices.second;

    float scaleFactor = GetScaleFactor(m_Rotations[p0Index].timeStamp,
        m_Rotations[p1Index].timeStamp, animationTime);
    glm::quat finalRotation = glm::slerp(m_Rotations[p0Index].orientation,
        m_Rotations[p1Index].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);

    return glm::toMat4(finalRotation);
}

glm::mat4& NodeAnim::InterpolateScaling(float animationTime) {
    auto& indices = GetAnimationIndices<KeyScale>(m_Scales, animationTime);
    int p0Index = indices.first;
    int p1Index = indices.second;

    float scaleFactor = GetScaleFactor(m_Scales[p0Index].timeStamp,
        m_Scales[p1Index].timeStamp, animationTime);
    glm::vec3 finalScale = glm::mix(m_Scales[p0Index].scale, 
        m_Scales[p1Index].scale, scaleFactor);

    return glm::scale(glm::mat4(1.0f), finalScale);
}

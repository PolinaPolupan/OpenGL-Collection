#include "Bone.h"

#include "AssimpGLMHelpers.h"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel): 
    m_Name(name),             
    m_ID(ID),                 
    m_LocalTransform(glm::mat4(1.0f)), 
    m_NumPositions(0),         
    m_NumRotations(0),        
    m_NumScalings(0) 
{
    m_NumPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < m_NumPositions; ++positionIndex) {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
        data.timeStamp = timeStamp;
        m_Positions.push_back(data);
    }

    m_NumRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < m_NumRotations; ++rotationIndex) {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
        data.timeStamp = timeStamp;
        m_Rotations.push_back(data);
    }

    m_NumScalings = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < m_NumScalings; ++keyIndex) {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::GetGLMVec(scale);
        data.timeStamp = timeStamp;
        m_Scales.push_back(data);
    }
}

void Bone::Update(float animationTime)
{
}

int Bone::GetPositionIndex(float animationTime)
{
    return 0;
}

int Bone::GetRotationIndex(float animationTime)
{
    return 0;
}

int Bone::GetScaleIndex(float animationTime)
{
    return 0;
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    return 0.0f;
}

glm::mat4& Bone::InterpolatePosition(float animationTime)
{
    // TODO: insert return statement here
}

glm::mat4& Bone::InterpolateRotation(float animationTime)
{
    // TODO: insert return statement here
}

glm::mat4& Bone::InterpolateScaling(float animationTime)
{
    // TODO: insert return statement here
}

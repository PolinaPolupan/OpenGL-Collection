#pragma once

#include "glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <assimp/anim.h>


class Bone {
public:

    struct KeyPosition {
        glm::vec3 position;
        float timeStamp;

        KeyPosition():
            position(glm::vec3(0.0f)), 
            timeStamp(0.0f) {}
    };

    struct KeyRotation {
        glm::quat orientation;
        float timeStamp;
        
        KeyRotation():
            orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
            timeStamp(0.0f) {}
    };

    struct KeyScale {
        glm::vec3 scale;
        float timeStamp;

        KeyScale() :
            scale(glm::vec3(0.0f)),
            timeStamp(0.0f) {}
    };

    // Reads keyframes from aiNodeAnim
	Bone(const std::string& name, int ID, const aiNodeAnim* channel);

    inline const glm::mat4& GetLocalTransform() const { return m_LocalTransform; }
    inline const std::string& GetBoneName() const { return m_Name; }
    inline const int GetBoneID() const { return m_ID; }

    /* Interpolates  b/w positions,rotations & scaling keys based on the curren time of
    the animation and prepares the local transformation matrix by combining all keys
    tranformations */
    void Update(float animationTime);

    /* Gets the current index on mKeyPositions to interpolate to based on
    the current animation time */
    int GetPositionIndex(float animationTime);

    /* Gets the current index on mKeyRotations to interpolate to based on the
    current animation time */
    int GetRotationIndex(float animationTime);

    /* Gets the current index on mKeyScalings to interpolate to based on the
    current animation time */
    int GetScaleIndex(float animationTime);

private:
    /* Gets normalized value for Lerp & Slerp */
    float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
    
    /* Figures out which position keys to interpolate b/w and performs the interpolation
    and returns the translation matrix */
    glm::mat4& InterpolatePosition(float animationTime);

    /* Figures out which rotations keys to interpolate b/w and performs the interpolation
    and returns the rotation matrix */
    glm::mat4& InterpolateRotation(float animationTime);

    /* Figures out which scaling keys to interpolate b/w and performs the interpolation
    and returns the scale matrix */
    glm::mat4& InterpolateScaling(float animationTime);

private:
    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;
    int m_NumPositions;
    int m_NumRotations;
    int m_NumScalings;

    glm::mat4 m_LocalTransform;
    std::string m_Name;
    int m_ID;
};
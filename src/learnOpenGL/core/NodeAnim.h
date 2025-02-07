#pragma once

#include "glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <assimp/anim.h>

#include "Texture.h"
#include "Constants.h"
#include "Material.h"
#include "Bone.h"
#include "Mesh.h"


class NodeAnim {
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
	NodeAnim(const std::string& name, int id, const aiNodeAnim* channel);

    inline const glm::mat4& GetLocalTransform() const { return m_LocalTransform; }
    inline const std::string& GetName() const { return m_Name; }
    inline const int GetId() const { return m_Id; }

    /* Interpolates  b/w positions,rotations & scaling keys based on the curren time of
    the animation and prepares the local transformation matrix by combining all keys
    tranformations */
    void Update(float animationTime);


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

    /**
    * \brief Finds the keyframe indices for a given animation time.
    *
    * This function determines two keyframe indices in the animation sequence
    * that enclose the given animation time. These indices are used for
    * interpolation between keyframes.
    *
    * \param T The type of keyframe data, which must have a `timeStamp` field.
    * \param indices A vector of keyframe data.
    * \param animationTime The current animation time for which keyframe indices are needed.
    * \return A pair of integers representing the indices of the keyframes before and after `animationTime`.
    *
    * \note If `indices` contains only one element, the function returns {0, 0}.
    * \warning The function contains an assertion failure if no valid indices are found.
    */
    template<typename T>
    inline const std::pair<int, int>& GetAnimationIndices(const std::vector<T>& indices, float animationTime) const;

private:
    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;

    glm::mat4 m_LocalTransform;
    std::string m_Name;
    int m_Id;
};

template<typename T>
inline const std::pair<int, int>& NodeAnim::GetAnimationIndices(const std::vector<T>& indices, float animationTime) const {
    if (indices.size() == 1) return { 0, 0 };
    for (int index = 0; index < indices.size() - 1; ++index) {
        if (animationTime < indices[index + 1].timeStamp)
            return { index, index + 1 };
    }
    assert(false);
    return { -1, -1 };
}

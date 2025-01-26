#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"


class CameraController {
public:
    CameraController(Camera camera):
        m_DeltaTime(0.0f),
        m_LastMousePosX(400.0f),
        m_LastMousePosY(300.0f),
        m_RotateCamera(false),
        m_FirstMouse(true),
        m_Camera(camera) {}

    CameraController(): CameraController(Camera()) {}

    Camera& GetCamera() { return m_Camera; }

    void SetCameraSensitvity(float sensitivity) { m_Camera.Sensitivity = sensitivity; }

    void ProcessInput(int event);

    void RotateCamera(float mousePosX, float mousePosY);

    void RotateByAngle(float yaw, float pitch);
 
    void ZoomCamera(double xoffset, double yoffset);

    void OnUpdate(float deltaTime) { m_DeltaTime = deltaTime; }

    glm::vec3 GetCameraPos() const { return m_Camera.CameraPos; }

    glm::vec3 GetCameraFront() const { return m_Camera.CameraFront; }

    glm::vec3 GetCameraUp() const { return m_Camera.CameraUp; }

    glm::mat4 GetViewMatrix() { return m_Camera.GetViewMatrix(); }

    glm::mat4 GetProjectionMatrix() { return m_Camera.GetProjectionMatrix(); }

    void SetCameraSpeed(float speed) { m_Camera.CameraSpeed = speed; }

    void SetCameraFOV(float fov) { m_Camera.FOV = fov; }

    float GetFOV() const { return m_Camera.FOV; }

private: 
    Camera m_Camera;
    float m_DeltaTime;
    float m_LastMousePosX;
    float m_LastMousePosY;
    bool m_FirstMouse;
    bool m_RotateCamera;
};

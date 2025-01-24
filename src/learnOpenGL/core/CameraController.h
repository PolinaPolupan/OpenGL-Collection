#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"


class CameraController {
    
    bool RotateCamera = false;
    Camera m_Camera;
    float m_DeltaTime = 0.f;
    float lastMousePosX = 400.f;
    float lastMousePosY = 300.f;
    bool firstMouse = true;

public:

    CameraController(Camera camera) : m_Camera(camera) {}
    CameraController() {}

    Camera& getCamera() { return m_Camera; }

    void setCameraSensitvity(float sensitivity) {
        m_Camera.Sensitivity = sensitivity;
    }

    void processInput(int event)
    {
        if (event == GLFW_KEY_W)
            m_Camera.CameraPos += m_Camera.CameraSpeed * m_Camera.CameraFront * m_DeltaTime;
        if (event == GLFW_KEY_S)
            m_Camera.CameraPos -= m_Camera.CameraSpeed * m_Camera.CameraFront * m_DeltaTime;
        if (event == GLFW_KEY_A)
            m_Camera.CameraPos -= glm::normalize(glm::cross(m_Camera.CameraFront, m_Camera.CameraUp)) * m_Camera.CameraSpeed * m_DeltaTime;
        if (event == GLFW_KEY_D)
            m_Camera.CameraPos += glm::normalize(glm::cross(m_Camera.CameraFront, m_Camera.CameraUp)) * m_Camera.CameraSpeed * m_DeltaTime;
        if (event == GLFW_KEY_UP) {
            rotateByAngle(m_Camera.Yaw, m_Camera.Pitch + 0.05f);
        }
        if (event == GLFW_KEY_DOWN) {
            rotateByAngle(m_Camera.Yaw, m_Camera.Pitch - 0.05f);
        }
        if (event == GLFW_KEY_LEFT) {
            rotateByAngle(m_Camera.Yaw + 0.05f, m_Camera.Pitch);
        }
        if (event == GLFW_KEY_RIGHT) {
            rotateByAngle(m_Camera.Yaw - 0.05f, m_Camera.Pitch);
        }
    }

    void rotateCamera(float mousePosX, float mousePosY)
    {
        if (firstMouse)
        {
            lastMousePosX = mousePosX;
            lastMousePosY = mousePosY;
            firstMouse = false;
        }
        float xoffset = mousePosX - lastMousePosX;
         float yoffset = lastMousePosY - mousePosY; // reversed since y-coordinates go from bottom to top
         lastMousePosX = mousePosX;
         lastMousePosY = mousePosY;

         xoffset *= m_Camera.Sensitivity;
         yoffset *= m_Camera.Sensitivity;

         m_Camera.Yaw += xoffset;
         m_Camera.Pitch += yoffset;

         // make sure that when Pitch is out of bounds, screen doesn't get flipped
         if (m_Camera.Pitch > 89.0f)
             m_Camera.Pitch = 89.0f;
         if (m_Camera.Pitch < -89.0f)
             m_Camera.Pitch = -89.0f;

         glm::vec3 front;
         front.x = cos(glm::radians(m_Camera.Yaw)) * cos(glm::radians(m_Camera.Pitch));
         front.y = sin(glm::radians(m_Camera.Pitch));
         front.z = sin(glm::radians(m_Camera.Yaw)) * cos(glm::radians(m_Camera.Pitch));
         m_Camera.CameraFront = glm::normalize(front);
    }

    void rotateByAngle(float yaw, float pitch) {
        m_Camera.Yaw = yaw;
        m_Camera.Pitch = pitch;

        // make sure that when Pitch is out of bounds, screen doesn't get flipped
        if (m_Camera.Pitch > 89.0f)
            m_Camera.Pitch = 89.0f;
        if (m_Camera.Pitch < -89.0f)
            m_Camera.Pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_Camera.Yaw)) * cos(glm::radians(m_Camera.Pitch));
        front.y = sin(glm::radians(m_Camera.Pitch));
        front.z = sin(glm::radians(m_Camera.Yaw)) * cos(glm::radians(m_Camera.Pitch));
        m_Camera.CameraFront = glm::normalize(front);
    }
 
    void zoomCamera(double xoffset, double yoffset)
    {
        m_Camera.FOV -= (float)yoffset  * m_Camera.Sensitivity;
        if (m_Camera.FOV < 1.0f)
            m_Camera.FOV = 1.0f;
        if (m_Camera.FOV > 45.0f)
            m_Camera.FOV = 45.0f;
    }

    void OnUpdate(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    glm::vec3 getCameraPos()
    {
        return m_Camera.CameraPos;
    }

    glm::vec3 getCameraFront()
    {
        return m_Camera.CameraFront;
    }

    glm::vec3 getCameraUp()
    {
        return m_Camera.CameraUp;
    }

    glm::mat4 getViewMatrix()
    {
        return m_Camera.GetViewMatrix();
    }

    glm::mat4 getProjectionMatrix()
    {
        return m_Camera.GetProjectionMatrix();
    }

    void setCameraSpeed(float speed)
    {
        m_Camera.CameraSpeed = speed;
    }

    void setCameraFOV(float fov)
    {
        m_Camera.FOV = fov;
    }

    float getFOV()
    {
        return m_Camera.FOV;
    }
};

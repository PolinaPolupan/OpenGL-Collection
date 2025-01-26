#include "CameraController.h"

void CameraController::ProcessInput(int event) {
    switch (event) {
    case GLFW_KEY_W:
        m_Camera.CameraPos += m_Camera.CameraSpeed * m_Camera.CameraFront * m_DeltaTime;
        break;
    case GLFW_KEY_S:
        m_Camera.CameraPos -= m_Camera.CameraSpeed * m_Camera.CameraFront * m_DeltaTime;
        break;
    case GLFW_KEY_A:
        m_Camera.CameraPos -= glm::normalize(glm::cross(m_Camera.CameraFront, m_Camera.CameraUp)) * m_Camera.CameraSpeed * m_DeltaTime;
        break;
    case GLFW_KEY_D:
        m_Camera.CameraPos += glm::normalize(glm::cross(m_Camera.CameraFront, m_Camera.CameraUp)) * m_Camera.CameraSpeed * m_DeltaTime;
        break;
    case GLFW_KEY_UP:
        RotateByAngle(m_Camera.Yaw, m_Camera.Pitch + 0.05f);
        break;
    case GLFW_KEY_DOWN:
        RotateByAngle(m_Camera.Yaw, m_Camera.Pitch - 0.05f);
        break;
    case GLFW_KEY_LEFT:
        RotateByAngle(m_Camera.Yaw + 0.05f, m_Camera.Pitch);
        break;
    case GLFW_KEY_RIGHT:
        RotateByAngle(m_Camera.Yaw - 0.05f, m_Camera.Pitch);
        break;
    default:
        break;
    }
}

void CameraController::RotateCamera(float mousePosX, float mousePosY) {
    if (m_FirstMouse) {
        m_LastMousePosX = mousePosX;
        m_LastMousePosY = mousePosY;
        m_FirstMouse = false;
    }
    float xoffset = mousePosX - m_LastMousePosX;
    float yoffset = m_LastMousePosY - mousePosY; // reversed since y-coordinates go from bottom to top
    m_LastMousePosX = mousePosX;
    m_LastMousePosY = mousePosY;

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

void CameraController::RotateByAngle(float yaw, float pitch) {
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

void CameraController::ZoomCamera(double xoffset, double yoffset) {
    m_Camera.FOV -= (float)yoffset * m_Camera.Sensitivity;
    if (m_Camera.FOV < 1.0f)
        m_Camera.FOV = 1.0f;
    if (m_Camera.FOV > 45.0f)
        m_Camera.FOV = 45.0f;
}

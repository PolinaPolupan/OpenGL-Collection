#pragma once

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Constants.h"

class Camera {

public:
	Camera() {}
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float speed) : CameraPos(cameraPos), CameraFront(cameraFront), CameraUp(cameraUp), CameraSpeed(speed) {}

	glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float Yaw = - 90.0f;
	float Pitch = 0.0f;
	float Zoom = 45.f;

	float CameraSpeed = 10.f;
	float Sensitivity = 0.05f;
	float FOV = 45.f;

	float FarClipRange = 100.f;
	float NearClipRange = 0.1f;

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
	}

	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(FOV),(float) WIDTH / HEIGHT, NearClipRange, FarClipRange);
	}

};

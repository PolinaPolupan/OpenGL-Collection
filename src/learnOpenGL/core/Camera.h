#pragma once

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Constants.h"

class Camera {

public:
	Camera(): Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f) {}
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float speed): 
		CameraPos(cameraPos),
		CameraFront(cameraFront),
		CameraUp(cameraUp),
		Yaw(-90.0f),
		Pitch(0.0f),
		Zoom(45.0f),
		CameraSpeed(speed),
		Sensitivity(0.05f),
		FOV(45.0f),
		FarClipRange(100.0f),
		NearClipRange(0.1f) {}

	glm::vec3 CameraPos;
	glm::vec3 CameraFront;
	glm::vec3 CameraUp;

	float Yaw;
	float Pitch;
	float Zoom;
	float CameraSpeed;
	float Sensitivity;
	float FOV;
	float FarClipRange;
	float NearClipRange;

	glm::mat4 GetViewMatrix() const {
		return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
	}

	glm::mat4 GetProjectionMatrix() const {
		return glm::perspective(glm::radians(FOV),(float) WIDTH / HEIGHT, NearClipRange, FarClipRange);
	}
};

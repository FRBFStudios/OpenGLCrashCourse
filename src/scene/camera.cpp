#include<cmath>
#include <glm/glm/glm.hpp>

#include "camera.h"



Camera::Camera(const glm::vec3 startPosition, glm::vec3 startLookDir, float fovArg, float sensitivityArg, float speedArg) {
	world_xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	world_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	world_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	firstMouse = true;

	position = startPosition;

	fov = fovArg;
	sensitivity = sensitivityArg;
	speed = speedArg;

	zAxis = glm::normalize(startLookDir);
	moveDir = glm::normalize(glm::vec3(zAxis.x, 0.0f, zAxis.z));

	xAxis = glm::normalize(glm::cross(world_yAxis, zAxis));
	yAxis = glm::normalize(glm::cross(zAxis, xAxis));

	yaw = -90.0f;
	pitch = 0.0f;

	lastX = 0.0f;
	lastY = 0.0f;
}

void Camera::lookAround(const double xPosIn, const double yPosIn) {
	const auto xPos = static_cast<float>(xPosIn);
	const auto yPos = static_cast<float>(yPosIn);

	if(firstMouse) {
		lastX = xPos;
		lastY = yPos;

		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if(pitch >= 89.0f) {
		pitch = 89.0f;
	} else if(pitch <= -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	moveDir = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	zAxis = glm::normalize(front);
	xAxis = glm::normalize(glm::cross(world_yAxis, zAxis));
	yAxis = glm::normalize(glm::cross(zAxis, xAxis));
}
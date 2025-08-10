#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>

class Camera {
public:
	glm::vec3 world_xAxis{};
	glm::vec3 world_yAxis{};
	glm::vec3 world_zAxis{};


	glm::vec3 position{};
	glm::vec3 xAxis{}, yAxis{}, zAxis{};
	glm::vec3 moveDir{};

	float speed, fov, sensitivity;

	float yaw, pitch;

	float lastX, lastY;

	bool firstMouse;


	Camera(glm::vec3 startPosition, glm::vec3 startLookDir, float fovArg, float sensitivityArg, float speedArg);

	void lookAround(double xPosIn, double yPosIn);
};

#endif //CAMERA_H

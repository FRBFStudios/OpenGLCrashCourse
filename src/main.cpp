#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "texture.h"

#include "shader_program.h"

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

auto world_xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
auto world_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
auto world_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);


auto cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

auto camera_zAxis = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_xAxis = glm::normalize(glm::cross(world_yAxis, camera_zAxis));
glm::vec3 camera_yAxis = glm::normalize(glm::cross(camera_zAxis, camera_xAxis));

float cameraSpeed = 0.01f;

float fov = 80.0;

float yaw = -90.0;
float pitch = 0.0;

float lastX = 0;
float lastY = 0;

bool firstMouse = true;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;

		firstMouse = false;
	}

	float cameraSensitivity = 0.3f;

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	xOffset *= cameraSensitivity;
	yOffset *= cameraSensitivity;

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

	camera_zAxis = glm::normalize(front);
};

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		fov = 30.0f;
	} else {
		fov = 80.0f;
	}


	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPosition += cameraSpeed * camera_zAxis;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPosition -= cameraSpeed * camera_zAxis;
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPosition += cameraSpeed * glm::cross(camera_yAxis, camera_zAxis);
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPosition -= cameraSpeed * glm::cross(camera_yAxis, camera_zAxis);
	}
}

constexpr int WIDTH = 16;
constexpr int HEIGHT = 9;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_FLOATING, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crash Course", glfwGetPrimaryMonitor(), NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	ShaderProgram defaultProgram("shaders/default.vert", "shaders/default.frag");

	float vertices [] = {
		-0.5f, -0.4f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.4f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.4f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.4f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.0f,  0.4f,  0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		2, 3, 4,
		0, 2, 4,
		1, 3, 4
	};

	VAO VAO1;
	VBO VBO1(vertices, sizeof(vertices));

	VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
	VAO1.LinkAttributes(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));

	EBO EBO1(indices, sizeof(indices), VAO1);

	Texture testTexture("resources/n_happy.png", GL_TEXTURE_2D, GL_TEXTURE0);
	Texture::setTexUnit(defaultProgram, "tex", 0);

	// Texture overlayTexture("resources/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1);
	// Texture::setTexUnit(defaultProgram, "texOverlay", 1);

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultProgram.Activate();

		auto modelMatrix = glm::mat4(1.0f);

		glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + camera_zAxis, camera_yAxis);

		auto projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

		defaultProgram.setMat4Uniform("modelMatrix", modelMatrix);
		defaultProgram.setMat4Uniform("viewMatrix", viewMatrix);
		defaultProgram.setMat4Uniform("projectionMatrix", projectionMatrix);

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VBO::Unbind();
	VBO1.Delete();

	VAO::Unbind();
	VAO1.Delete();

	EBO::Unbind();
	EBO1.Delete();

	defaultProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
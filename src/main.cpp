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

#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 80.0f, 0.1f, 0.05f);

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window);

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

		constexpr auto modelMatrix = glm::mat4(1.0f);

		const glm::mat4 viewMatrix = glm::lookAt(camera.position, camera.position + camera.zAxis, camera.yAxis);

		const auto projectionMatrix = glm::perspective(glm::radians(camera.fov), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

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

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	camera.lookAround(xpos, ypos);
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
		camera.fov = 30.0f;
	} else {
		camera.fov = 80.0f;
	}


	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.position += camera.speed * camera.moveDir;
	} else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.position -= camera.speed * camera.moveDir;
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.position += camera.speed * camera.xAxis;
	} else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.position -= camera.speed * camera.xAxis;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.position += camera.speed * camera.world_yAxis;
	} else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.position -= camera.speed * camera.world_yAxis;
	}
}
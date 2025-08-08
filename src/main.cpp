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

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

const int WIDTH = 16;
const int HEIGHT = 9;

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


	ShaderProgram defaultProgram("shaders/default.vert", "shaders/default.frag");


	float vertices [] = {
		-0.5f, -0.5f, -0.4f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.4f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.0f,  0.0f,  0.4f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		2, 3, 4,
		0, 2, 4,
		1, 3, 4
	};

	float offset_x_location = glGetUniformLocation(defaultProgram.ID, "offset_x");

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



	auto projectionMatrix = glm::perspective(glm::radians(80.0f), static_cast<float>(WIDTH / HEIGHT), 0.1f, 100.0f);

	int modelMatrixLocation = glGetUniformLocation(defaultProgram.ID, "modelMatrix");
	int viewMatrixLocation = glGetUniformLocation(defaultProgram.ID, "viewMatrix");
	int projectionMatrixLocation = glGetUniformLocation(defaultProgram.ID, "projectionMatrix");

	float totalAngle = 0.0f;
	float totalDistanceFactor = 0.0f;

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultProgram.Activate();

		totalAngle += 0.5f;

		totalDistanceFactor += 0.03f;

		if(totalAngle >= 360.0f) {
			totalAngle = 0.0f;
		}

		auto modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(totalAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(totalAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(totalAngle), glm::vec3(0.0f, 0.0f, 1.0f));

		auto viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, static_cast<float>(sin(totalDistanceFactor) - 3.0f)));


		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		VAO1.Bind();

		processInput(window);

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
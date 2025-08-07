#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "shader_program.h"

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

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


	ShaderProgram defaultProgram("../shaders/default.vert", "../shaders/default.frag");


	float vertices [] = {
		1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 //0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		//1, 2, 3
	};

	float offset_x_location = glGetUniformLocation(defaultProgram.ID, "offset_x");

	VAO VAO1;
	VBO VBO1(vertices, sizeof(vertices));

	VAO1.LinkVBO(VBO1, 0);

	EBO EBO1(indices, sizeof(indices), VAO1);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		defaultProgram.Activate();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VBO1.Unbind();
	VBO1.Delete();

	VAO1.Unbind();
	VAO1.Delete();

	EBO1.Unbind();
	EBO1.Delete();

	defaultProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
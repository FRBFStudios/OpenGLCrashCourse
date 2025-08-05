#include<iostream>
#include<cmath>

#include<glad/glad.h>

#include<GLFW/glfw3.h>

#include<stb/stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

constexpr unsigned int WIDTH = 2560;
constexpr unsigned int HEIGHT = 1440;

// Vertices coordinates
GLfloat vertices[] = {
	//    COORDINATES   /        COLORS    /     UV      //
	-0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Back left corner
	0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Back right corner
	-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Front left corner
	0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Front right corner
	0.0f, 1.4f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f // Peak
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	1, 2, 3,
	0, 2, 4, // Left side
	1, 3, 4, // Right side
	2, 3, 4, // Front side
	0, 1, 4 // Back side
};

int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW that we are using the CORE profile
	// CORE = only modern functions, COMPATIBILITY = modern and older functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Crash Course", glfwGetPrimaryMonitor(), nullptr);

	// Small error check in case the window creation fails
	if(window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	// The window is given a viewport from its top left to bottom right
	glViewport(0, 0, WIDTH, HEIGHT);

	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof (vertices));
	EBO EBO1(indices, sizeof (indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) nullptr);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// ---- TEXTURE ---- //

	// Creates a reference object for the texture and generates 1 texture
	Texture happyN("resources/n_happy.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	happyN.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	// This loops until the windows is closed so the window isn't closed instantly
	while(!glfwWindowShouldClose(window)) {
		// The background color is set to a navy blue RGBA value
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// The Front Buffer is cleared to that value
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Our shader program is set as the shader program that should be used by glDrawArrays()
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		happyN.Bind();
		VAO1.Bind();

		// The pipeline is started with primitive configuration Triangles, starting at vertex 0, looking for 3 vertices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);

		// Front and Back Buffers are swapped (aka the screen is changed to the next frame)
		glfwSwapBuffers(window);

		// Takes care of all GLFW events
		glfwPollEvents();
	}

	// After the window is closed, everything is deleted before the program ends
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	happyN.Delete();

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	// Ends the main function
	return 0;
}

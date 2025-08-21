#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/stb_image.h"

#include "util/model.h"

#include "util/shader_program.h"

#include "util/VBO.h"
#include "util/VAO.h"
#include "util/EBO.h"

#include "scene/camera.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 80.0f, 0.1f, 0.05f);
glm::vec3 lightSourcePosition(1.2f, 1.0f, 2.0f);

glm::vec3 pointLightPositions[] = {
	glm::vec3( -4.0f,  0.0f,  -4.0f),
	glm::vec3( 4.0f, 0.0f, -4.0f),
	glm::vec3(-4.0f,  0.0f, 4.0f),
	glm::vec3( 4.0f,  0.0f, 4.0f)
};

glm::vec3 pointLightColors[] = {
	glm::vec3(0.1f, 0.5f, 1.0f),
	glm::vec3(0.1f, 0.5f, 1.0f),
	glm::vec3(0.1f, 0.5, 1.0),
	glm::vec3(0.1f, 0.5f, 1.0f)
};

bool enableFlashlight = false;
bool firstFrameHeldFKey = true;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_FLOATING, GL_TRUE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	const int WIDTH = videoMode->width;
	const int HEIGHT = videoMode->height;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crash Course", primaryMonitor, NULL);
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

	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	ShaderProgram modelProgram("shaders/model.vert", "shaders/model.frag");
	Model test("resources/xmas-model/Xmas_House_Exterior.obj");
	//Model test("resources/testmodel/backpack.obj");

	auto backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

	modelProgram.setFloatUniform("material.shininess", 32.0f);

	/*modelProgram.setVec3Uniform("sun.direction", glm::vec3(-0.5f, -1.0f, -0.5f));
	modelProgram.setVec3Uniform("sun.ambientColor", backgroundColor * 0.125f);
	modelProgram.setVec3Uniform("sun.baseColor", backgroundColor);
	modelProgram.setVec3Uniform("sun.specularColor", backgroundColor * 1.25f);*/

	modelProgram.setFloatUniform("flashlight.constant", 1.0f);
	modelProgram.setFloatUniform("flashlight.linear", 0.09f);
	modelProgram.setFloatUniform("flashlight.quadratic", 0.032f);

	modelProgram.setVec3Uniform("pointLights[0].position", pointLightPositions[0]);
	modelProgram.setVec3Uniform("pointLights[0].ambientColor", glm::vec3(0.05f, 0.05f, 0.05f));
	modelProgram.setVec3Uniform("pointLights[0].baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
	modelProgram.setVec3Uniform("pointLights[0].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
	modelProgram.setFloatUniform("pointLights[0].constant", 1.0f);
	modelProgram.setFloatUniform("pointLights[0].linear", 0.09f);
	modelProgram.setFloatUniform("pointLights[0].quadratic", 0.032f);

	modelProgram.setVec3Uniform("pointLights[1].position", pointLightPositions[1]);
	modelProgram.setVec3Uniform("pointLights[1].ambientColor", glm::vec3(0.05f, 0.05f, 0.05f));
	modelProgram.setVec3Uniform("pointLights[1].baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
	modelProgram.setVec3Uniform("pointLights[1].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
	modelProgram.setFloatUniform("pointLights[1].constant", 1.0f);
	modelProgram.setFloatUniform("pointLights[1].linear", 0.09f);
	modelProgram.setFloatUniform("pointLights[1].quadratic", 0.032f);

	modelProgram.setVec3Uniform("pointLights[2].position", pointLightPositions[2]);
	modelProgram.setVec3Uniform("pointLights[2].ambientColor", glm::vec3(0.05f, 0.05f, 0.05f));
	modelProgram.setVec3Uniform("pointLights[2].baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
	modelProgram.setVec3Uniform("pointLights[2].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
	modelProgram.setFloatUniform("pointLights[2].constant", 1.0f);
	modelProgram.setFloatUniform("pointLights[2].linear", 0.09f);
	modelProgram.setFloatUniform("pointLights[2].quadratic", 0.032f);

	modelProgram.setVec3Uniform("pointLights[3].position", pointLightPositions[3]);
	modelProgram.setVec3Uniform("pointLights[3].ambientColor", glm::vec3(0.05f, 0.05f, 0.05f));
	modelProgram.setVec3Uniform("pointLights[3].baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
	modelProgram.setVec3Uniform("pointLights[3].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
	modelProgram.setFloatUniform("pointLights[3].constant", 1.0f);
	modelProgram.setFloatUniform("pointLights[3].linear", 0.09f);
	modelProgram.setFloatUniform("pointLights[3].quadratic", 0.032f);

	while(!glfwWindowShouldClose(window)) {
		modelProgram.Activate();
		processInput(window);

		modelProgram.setVec3Uniform("flashlight.direction", camera.zAxis);
		modelProgram.setVec3Uniform("flashlight.position", camera.position);
		modelProgram.setFloatUniform("flashlight.cutOff", glm::cos(glm::radians(35.0f)));
		modelProgram.setFloatUniform("flashlight.outerCutOff", glm::cos(glm::radians(37.5f)));

		if(enableFlashlight) {
			modelProgram.setVec3Uniform("flashlight.ambientColor", glm::vec3(0.05f, 0.05f, 0.05f));
			modelProgram.setVec3Uniform("flashlight.baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
			modelProgram.setVec3Uniform("flashlight.specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
		} else {
			modelProgram.setVec3Uniform("flashlight.ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			modelProgram.setVec3Uniform("flashlight.baseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			modelProgram.setVec3Uniform("flashlight.specularColor", glm::vec3(0.0f, 0.0f, 0.0f));
		}

		auto modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -50.0f, 0.0f)); // translate it down so it's at the center of the scene
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
		const glm::mat4 viewMatrix = glm::lookAt(camera.position, camera.position + camera.zAxis, camera.yAxis);
		const auto projectionMatrix = glm::perspective(glm::radians(camera.fov), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

		modelProgram.setMat4Uniform("modelMatrix", modelMatrix);
		modelProgram.setMat4Uniform("viewMatrix", viewMatrix);
		modelProgram.setMat4Uniform("projectionMatrix", projectionMatrix);

		modelProgram.setVec3Uniform("cameraPosition", camera.position);


		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		test.draw(modelProgram);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	modelProgram.Delete();

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

	if(firstFrameHeldFKey) {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && enableFlashlight) {
			firstFrameHeldFKey = false;
			enableFlashlight = false;
		} else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !enableFlashlight) {
			firstFrameHeldFKey = false;
			enableFlashlight = true;
		}
	} else if (!firstFrameHeldFKey) {
		if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
			firstFrameHeldFKey = true;
		}
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

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<stb/stb_image.h>

#include "../include/shaderClass.h"
#include "../VAO.h"
#include "../VBO.h"
#include "../include/EBO.h"
#include "../Texture.h"


// Vertices coordinates
GLfloat vertices [] =
{   //    COORDINATES     /       COLORS       /      UV      //            
	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Lower left corner
	 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Lower right corner
	-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f  // Upper right corner
};

// Indices for vertices order
GLuint indices [] =
{
	0, 1, 2,
	1, 2, 3
};

int main ()
{
	// Initialize GLFW
	glfwInit ();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW that we are using the CORE profile
	// CORE = only modern functions, COMPATIBILITY = modern and older functions
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating a new GLFW window pointer for an 800px by 800px window titled "OpenGL Crash Course"
	GLFWwindow* window = glfwCreateWindow (800, 800, "OpenGL Crash Course", NULL, NULL);
	// Small error check in case the window creation fails
	if (window == NULL)
	{
		std::cout<<"Failed to create GLFW window"<<std::endl;
		glfwTerminate ();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent (window);


	// Loading Glad so it configures OpenGL
	gladLoadGL ();


	// The window is given a viewport from its top left to bottom right
	glViewport (0, 0, 800, 800);

	Shader shaderProgram ("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind ();

	VBO VBO1 (vertices, sizeof (vertices));
	EBO EBO1 (indices, sizeof (indices));

	VAO1.LinkAttrib (VBO1, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*) 0);
	VAO1.LinkAttrib (VBO1, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*) (3 * sizeof (float)));
	VAO1.LinkAttrib (VBO1, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*) (6 * sizeof (float)));

	VAO1.Unbind ();
	VBO1.Unbind ();
	EBO1.Unbind ();

	GLuint uniID = glGetUniformLocation (shaderProgram.ID, "scale");

	// Texture

	// Creates a reference object for the texture and generates 1 texture
	Texture happyN ("n_happy.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	happyN.texUnit (shaderProgram, "tex0", 0);


	float lastTime = 0.0f;
	float scale = 0.0f;


	// This loops until the windows is closed so the window isn't closed instantly
	while (!glfwWindowShouldClose (window))
	{
		// The background color is set to a navy blue RGBA value
		glClearColor (0.07f, 0.13f, 0.17f, 1.0f);
		// The Front Buffer is cleared to that value
		glClear (GL_COLOR_BUFFER_BIT);

		// Our shader program is set as the shader program that should be used by glDrawArrays()
		shaderProgram.Activate ();
		
		if (glfwGetTime () - lastTime > 1.0f / 60.0f)
		{
			scale += 0.05f;
			lastTime = glfwGetTime ();
		}

		//glUniform1f (uniID, 0.1f * sin(scale));
		happyN.Bind ();

		// The instructions stored at the ID stored in the VAO variable are set as the default VAO
		VAO1.Bind ();
		// The pipeline is started with primitive configuration Triangles, starting at vertex 0, looking for 3 vertices
		glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

		// Front and Back Buffers are swapped (aka the screen is changed to the next frame)
		glfwSwapBuffers (window);

		// Takes care of all GLFW events
		glfwPollEvents ();
	}

	// After the window is closed, everything is deleted before the program ends
	VAO1.Delete ();
	VBO1.Delete ();
	EBO1.Delete ();

	happyN.Delete ();

	shaderProgram.Delete ();

	glfwDestroyWindow (window);
	glfwTerminate ();

	// Ends the main function
	return 0;
}
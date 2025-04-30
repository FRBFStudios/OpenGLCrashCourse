#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO (GLfloat* vertices, GLsizeiptr size)
{
	// VBO memory block is reserved and its ID stored in the variable
	glGenBuffers (1, &ID);
	glBindBuffer (GL_ARRAY_BUFFER, ID);

	/*
	* "GL_STATIC_DRAW" is a hint the GL uses to choose between possible physical storage locations of the buffer (VRAM, RAM)
	* However, it can obviously only choose one of these if they are available
	* We can choose between "STATIC", "STREAM" and "DYNAMIC" aswell as "DRAW", "READ" and "COPY" to improve performance.
	* Information on these can be found in the OpenGL docs: https://registry.khronos.org/OpenGL-Refpages/gl4/
	*/
	glBufferData (GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// The VBO buffer object is bound as the default VBO
void VBO::Bind ()
{
	glBindBuffer (GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind ()
{
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete ()
{
	glDeleteBuffers (1, &ID);
}
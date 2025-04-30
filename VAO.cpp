#include"VAO.h"

VAO::VAO ()
{
	// VAO memory block is reserved and its ID stored in the variable
	glGenVertexArrays (1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkAttrib (VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind ();
	// Configurates the VAO instructions: Store the coordinate sets at location 0, read 3 values for each vertex (xyz), each value is a float (32 bits/4 bytes)... (1/2)
	// ... don't normalize, jump to next vertex after 3 floats, start reading coordinates at byte 0 of the bound VBO. (2/2)
	glVertexAttribPointer (layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray (layout);
	VBO.Unbind ();
}

// The instructions stored at the ID stored in the VAO variable are bound as the default VAO
void VAO::Bind ()
{
	glBindVertexArray (ID);

}

void VAO::Unbind ()
{
	glBindVertexArray (0);
}

void VAO::Delete ()
{
	glDeleteVertexArrays (1, &ID);
}
#include "VAO.h"

VAO::VAO(): ID(0) {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttributes(VBO &VBO, const unsigned int layout, const GLint size, const GLenum type, const GLsizei stride, const void* offset) const {
	Bind();
	VBO.Bind();

	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VBO::Unbind();
	Unbind();
}

void VAO::Bind() const {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}

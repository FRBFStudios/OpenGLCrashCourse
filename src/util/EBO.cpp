#include "EBO.h"

EBO::EBO(unsigned int* indices, GLsizeiptr size, VAO &VAO) {
	glGenBuffers(1, &ID);

	VAO.Bind();
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	VAO.Unbind();
	Unbind();
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}

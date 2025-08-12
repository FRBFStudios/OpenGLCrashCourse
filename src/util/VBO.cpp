#include "VBO.h"

#include "model_loader.h"

VBO::VBO(std::vector<Vertex> &vertices) {
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	Unbind();
}

void VBO::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const {
	glDeleteBuffers(1, &ID);
}

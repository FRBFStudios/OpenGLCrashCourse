#include "EBO.h"
EBO::EBO(std::vector<unsigned int> &indices, VAO &VAO) {
	glGenBuffers(1, &ID);

	VAO.Bind();
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	VAO::Unbind();
	Unbind();
}

void EBO::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const {
	glDeleteBuffers(1, &ID);
}

#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include "VAO.h"

class EBO {
public:
	unsigned int ID;
	EBO(unsigned int* indices, GLsizeiptr size, VAO &VAO);

	void Bind();
	static void Unbind();
	void Delete();
};

#endif //EBO_H
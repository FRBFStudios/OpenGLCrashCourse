#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include "VBO.h"

class VAO {
public:
	unsigned int ID{};
	VAO();

	void LinkAttributes(::VBO &VBO, unsigned int layout, GLint size, GLenum type, GLsizei stride, const void *offset) const;
	void Bind() const;
	static void Unbind();
	void Delete();
};

#endif //VAO_H
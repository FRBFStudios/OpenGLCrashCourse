#ifndef VBO_H
#define VBO_H

#include <vector>
#include <glad/glad.h>

#include "vertex.h"

class VBO {
public:
	unsigned int ID{};
	explicit VBO(std::vector<Vertex> &vertices);

	void Bind() const;
	static void Unbind();
	void Delete() const;
};

#endif //VBO_H
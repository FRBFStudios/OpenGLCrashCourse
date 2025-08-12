#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

#include "model_loader.h"

class VBO {
public:
	unsigned int ID{};
	explicit VBO(std::vector<Vertex> &vertices);

	void Bind() const;
	static void Unbind();
	void Delete() const;
};

#endif //VBO_H
#ifndef EBO_H
#define EBO_H


#include <vector>
#include <glad/glad.h>
#include "VAO.h"

class EBO {
public:
	unsigned int ID{};
	EBO(std::vector<unsigned int> &indices, VAO &VAO);

	void Bind() const;
	static void Unbind();
	void Delete() const;
};

#endif //EBO_H
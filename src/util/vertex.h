#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

#endif //VERTEX_H

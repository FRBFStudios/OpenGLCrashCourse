#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "texture.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"

#include <string>
#include <vector>

using namespace std;

#include <glm/glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 textureCoordinates;
};


class Mesh {
public:

	vector<Vertex> vertices;
	vector<unsigned int> &indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, vector<Texture> &textures);
	void draw(ShaderProgram &shader);
private:
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;

	void setupMesh() const;
};

#endif //MODEL_LOADER_H

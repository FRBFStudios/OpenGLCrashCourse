#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"

#include <string>
#include <vector>

#include "shader_program.h"

using namespace std;

#include <glm/glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

struct Texture {
	unsigned int ID;
	string type;
	string path;
};


class Mesh {
public:

	vector<Vertex> vertices;
	vector<unsigned int> &indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, vector<Texture> &textures);
	void draw(ShaderProgram &shader);
private:
	VAO VAO1{};
	VBO VBO1(vertices);
	EBO EBO1(indices, VAO1);

	void setupMesh();
};

#endif //MODEL_LOADER_H

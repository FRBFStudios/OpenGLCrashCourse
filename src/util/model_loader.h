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

struct Texture {
	unsigned int ID;
	string type;
	string path;
};


class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	VAO VAO1;

	Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, const vector<Texture> &textures);
	void draw(const ShaderProgram &shader) const;
private:
	VBO VBO1;
	EBO EBO1;

	void setupMesh();
};

#endif //MODEL_LOADER_H

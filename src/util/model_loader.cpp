#include "model_loader.h"

Mesh::Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, vector<Texture> &textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh() const {
	VAO VAO1{};
	VBO VBO1(vertices);
	EBO EBO1(indices, VAO1);

	VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void *>((offsetof(Vertex, normal))));
	VAO1.LinkAttributes(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, textureCoordinates)));
}

void Mesh::draw(ShaderProgram &shader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for(int i = 0; i < textures.size(); i++) {
		string name = textures[i].usage;

		if(name == "DIFFUSE_MAP") {
			name.append(std::to_string(diffuseNr++));
		} else if(name == "SPECULAR_MAP") {
			name.append(std::to_string(specularNr++));
		}

		shader.setIntUniform("material." + name, i);
		textures[i].Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	VAO1.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VAO::Unbind();
}

#include "model_loader.h"



Mesh::Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, const vector<Texture> &textures): VBO1(vertices), EBO1(indices, VAO1) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh() {
	VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void *>((offsetof(Vertex, normal))));
	VAO1.LinkAttributes(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, textureCoordinates)));
}

void Mesh::draw(const ShaderProgram &shader) const {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for(int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		string name = textures[i].type;

		if(name == "DIFFUSE_MAP") {
			name.append(to_string(diffuseNr++));
		} else if(name == "SPECULAR_MAP") {
			name.append(to_string(specularNr++));
		}
		shader.Activate();

		shader.setIntUniform("material." + name, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}
	glActiveTexture(GL_TEXTURE0);

	VAO1.Bind();
	shader.Activate();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VAO::Unbind();
	glActiveTexture(GL_TEXTURE0);
}
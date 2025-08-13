#ifndef MODEL_H
#define MODEL_H
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model_loader.h"
#include "shader_program.h"

using namespace std;

class Model {
public:
	explicit Model(string const &path);
	void draw(ShaderProgram &shader);

private:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void loadModel(const string& path);

	void processNode(const aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif //MODEL_H

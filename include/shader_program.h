#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/fwd.hpp>

std::string getFileContents(const char* filename);

class ShaderProgram {
public:
	unsigned int ID;

	ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

	void setMat4Uniform(const std::string &uniform, glm::mat4 matrix);

	void Activate();
	void Delete();
};

#endif //SHADER_H

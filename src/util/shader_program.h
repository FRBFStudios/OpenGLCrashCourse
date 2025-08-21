#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/glm/fwd.hpp>

std::string getFileContents(const char* filename);

class ShaderProgram {
public:
	unsigned int ID;

	ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

	void setIntUniform(const std::string &uniform, int value) const;
	void setFloatUniform(const std::string &uniform, float value) const;
	void setVec3Uniform(const std::string &uniform, glm::vec3 vector) const;
	void setVec4Uniform(const std::string &uniform, glm::vec4 vector) const;
	void setMat4Uniform(const std::string &uniform, glm::mat4 matrix) const;

	void Activate() const;
	void Delete() const;
};

#endif //SHADER_H

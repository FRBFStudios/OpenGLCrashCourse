#include<fstream>
#include<sstream>
#include<cerrno>
#include <iostream>

#include <glad/glad.h>

#include "shader_program.h"

#include <glm/glm/gtc/type_ptr.hpp>

std::string getFileContents(const char* filename) {
	if (std::ifstream in(filename, std::ios::binary); in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout << "Error reading shader file: " << filename << std::endl;
	throw(errno);
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
	const std::string vertexShaderCode = getFileContents(vertexShaderFile);
	const std::string fragmentShaderCode = getFileContents(fragmentShaderFile);

	const char *vertexShaderSource = vertexShaderCode.c_str();
	const char *fragmentShaderSource = fragmentShaderCode.c_str();

	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);


	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);


	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::setIntUniform(const std::string &uniform, const int value) const {
	Activate();
	glUniform1i(glGetUniformLocation(ID, uniform.c_str()), value);
}

void ShaderProgram::setFloatUniform(const std::string &uniform, const float value) const {
	Activate();
	glUniform1f(glGetUniformLocation(ID,  uniform.c_str()), value);
}


void ShaderProgram::setVec3Uniform(const std::string &uniform, glm::vec3 vector) const {
	Activate();
	glUniform3fv(glGetUniformLocation(ID, uniform.c_str()), 1, glm::value_ptr(vector));
}


void ShaderProgram::setMat4Uniform(const std::string &uniform, glm::mat4 matrix) const {
	Activate();
	glUniformMatrix4fv(glGetUniformLocation(ID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::Activate() const {
	glUseProgram(ID);
}

void ShaderProgram::Delete() const {
	glDeleteProgram(ID);
}
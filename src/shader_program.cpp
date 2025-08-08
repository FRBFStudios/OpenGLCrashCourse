#include<fstream>
#include<sstream>
#include<cerrno>

#include <glad/glad.h>

#include "shader_program.h"

#include <glm/gtc/type_ptr.hpp>

std::string getFileContents(const char* filename) {
	if (std::ifstream in(filename, std::ios::binary); in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
	std::string vertexShaderCode = getFileContents(vertexShaderFile);
	std::string fragmentShaderCode = getFileContents(fragmentShaderFile);

	const char *vertexShaderSource = vertexShaderCode.c_str();
	const char *fragmentShaderSource = fragmentShaderCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);


	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);


	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::setMat4Uniform(const std::string &uniform, glm::mat4 matrix) {
	Activate();
	glUniformMatrix4fv(glGetUniformLocation(ID, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::Activate() {
	glUseProgram(ID);
}

void ShaderProgram::Delete() {
	glDeleteProgram(ID);
}

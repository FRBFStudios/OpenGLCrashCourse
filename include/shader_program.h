#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string getFileContents(const char* filename);

class ShaderProgram {
public:
	unsigned int ID;

	ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

	void Activate();
	void Delete();
};

#endif //SHADER_H

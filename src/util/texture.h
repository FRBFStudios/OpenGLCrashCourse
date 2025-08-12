#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "shader_program.h"

class Texture {
public:
	unsigned int ID;
	unsigned char* textureData;

	std::string usage;

	GLenum format;
	GLenum type;

	explicit Texture(char const* filePath, GLenum type, GLenum texUnit, std::string usage);

	static void setTexUnit(ShaderProgram &shaderProgram, const char *uniform, GLint unit);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif //TEXTURE_H

#ifndef TEXTURE_H
#define TEXTURE_H

#include "shader_program.h"

class Texture {
public:
	unsigned int ID;
	unsigned char* textureData;

	GLenum format;
	GLenum type;

	explicit Texture(char const* filePath, GLenum typeArg, GLenum texUnit);

	static void setTexUnit(ShaderProgram &shaderProgram, const char *uniform, GLint unit);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif //TEXTURE_H

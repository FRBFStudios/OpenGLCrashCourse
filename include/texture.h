#ifndef TEXTURE_H
#define TEXTURE_H

#include "shader_program.h"

class Texture {
public:
	unsigned int ID;
	unsigned char* textureData;

	GLenum format;
	GLenum type;

	explicit Texture(char const* filePath, GLenum typeArg);

	void setTexUnit(ShaderProgram& shaderProgram, const char* uniform, unsigned int unit);
	void Bind() const;
	static void Unbind();
	void Delete();
};

#endif //TEXTURE_H

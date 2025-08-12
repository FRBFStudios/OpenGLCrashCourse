#include "texture.h"

#include <utility>
#include "stb_image.h"

Texture::Texture(char const *filePath, const GLenum type, const GLenum texUnit, std::string usage): ID(0) {
	this->type = type;
	this->usage = std::move(usage);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;

	textureData = stbi_load(filePath, &width, &height, &nrChannels, 0);
	format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &ID);

	glActiveTexture(texUnit);
	Bind();

	glTexImage2D(type, 0, static_cast<GLint>(format), width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(type);

	stbi_image_free(textureData);
}

void Texture::setTexUnit(ShaderProgram &shaderProgram, const char *uniform, const GLint unit) {
	shaderProgram.Activate();
	glUniform1i(glGetUniformLocation(shaderProgram.ID, uniform), unit);
}

void Texture::Bind() const {
	glBindTexture(type, ID);
}

void Texture::Unbind() const {
	glBindTexture(type, 0);
}


void Texture::Delete() const {
	glDeleteTextures(1, &ID);
}

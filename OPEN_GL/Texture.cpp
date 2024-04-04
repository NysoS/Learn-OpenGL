#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType; //GL_TEXTURE_1D - GL_TEXTURE_2D - GL_TEXTURE_3D
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	//Generates an OpenGL texture object
	glGenTextures(1, &ID);
	//Assigns the texture to a texture unit
	glActiveTexture(slot); // GL_TEXTURE0
	glBindTexture(texType, ID);

	//Configure the of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//float flatColor[] = {1.f, 1.f, 1.f, 1.f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//Assign the image to the OpenGL Texture object and configures it's
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	//Delete the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);
	//Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint textUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(textUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::UnBind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

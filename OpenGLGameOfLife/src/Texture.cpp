#include "Texture.h"
#include "VertexMesh.h"

Texture::Texture(int width, int height, const std::vector<Pixel>& pixel_data)
{
	_width = width;
	_height = height;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,               // Mipmap level
		GL_RGB,            // xoffset, yoffset
		width, height,
		0,               // Width, height of the region
		GL_RGB,         // Pixel format
		GL_UNSIGNED_BYTE,// Data type
		pixel_data.data() // Pointer to your vector's data
	);
}

void Texture::setTextureData(const std::vector<Pixel>& pixel_data)
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,               // Mipmap level
		0, 0,            // xoffset, yoffset
		_width, _height,            // Width, height of the region
		GL_RGB,         // Pixel format
		GL_UNSIGNED_BYTE,// Data type
		pixel_data.data() // Pointer to your vector's data
	);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

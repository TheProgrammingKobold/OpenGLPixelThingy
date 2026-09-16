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

	glGenBuffers(1, &m_pboID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboID);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * sizeof(Pixel), nullptr, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	setTextureData(pixel_data);

}

Texture::~Texture()
{
	if (m_textureID)
	{
		glDeleteTextures(1, &m_textureID);
	}
	if (m_pboID)
	{
		glDeleteBuffers(1, &m_pboID);
	}
}

void Texture::setTextureData(const std::vector<Pixel>& pixel_data)
{
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboID);

	Pixel* ptr = (Pixel*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	if (ptr)
	{
		std::memcpy(ptr, pixel_data.data(), pixel_data.size() * sizeof(Pixel));
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	}

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,               // Mipmap level
		0, 0,            // xoffset, yoffset
		_width, _height,            // Width, height of the region
		GL_RGB,         // Pixel format
		GL_UNSIGNED_BYTE,// Data type
		nullptr // Pointer to your vector's data
	);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
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

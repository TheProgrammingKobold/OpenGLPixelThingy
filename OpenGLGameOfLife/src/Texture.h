#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct Pixel
{
	GLubyte r = 0, g = 0, b = 0;
};

class Texture
{
public:
	Texture(int width, int height, const std::vector<Pixel>& pixel_data);

	void setTextureData(const std::vector<Pixel>& pixel_data);

	void bind();

	void unbind();

private:

	int _width, _height;

	GLuint m_textureID;

};


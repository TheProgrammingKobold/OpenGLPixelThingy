#include "PixelSandbox.h"

std::vector<Pixel> _pixels;


bool PixelSandbox::Init(std::function<void()> func)
{
	return false;
}

bool PixelSandbox::Init()
{
	return false;
}

bool PixelSandbox::WindowShouldClose()
{
	return false;
}

void PixelSandbox::CleanUp()
{
}

uint32_t PixelSandbox::GetTextureWidth()
{
	return 0;
}

uint32_t PixelSandbox::GetTextureHeight()
{
	return 0;
}

std::vector<Pixel>& PixelSandbox::GetPixelArray()
{
	return _pixels;
}

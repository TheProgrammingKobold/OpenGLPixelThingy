#pragma once

#include "Window.h"
#include "Renderer.h"
#include "OpenGL.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexMesh.h"

#include <random>
#include <functional>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>


namespace PixelSandbox
{
	bool Init(std::function<void()> func);
	bool Init();

	bool WindowShouldClose();

	void CleanUp();

	uint32_t GetTextureWidth();
	uint32_t GetTextureHeight();
	std::vector<Pixel>& GetPixelArray();
}
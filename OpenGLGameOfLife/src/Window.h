#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window
{
	bool Init(int width, int height, const char* title);
	void Shutdown();
	void SwapBuffers();
	void PollEvents();

	bool WindowShouldClose();

	GLFWwindow* Get();
}


#include "Window.h"

#include <print>

namespace Window
{
	inline GLFWwindow* window = nullptr;

	bool Init(int width, int height, const char* title)
	{
		if (!glfwInit())
		{
			std::println("ERROR: Failed to init glfw!");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window) 
		{
			std::println("ERROR: Failed to create valid window!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){glViewport(0, 0, width, height); });
		return true;
	}

	void Shutdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void PollEvents()
	{
		glfwPollEvents();
	}

	bool WindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	GLFWwindow* Get()
	{
		return window;
	}
}


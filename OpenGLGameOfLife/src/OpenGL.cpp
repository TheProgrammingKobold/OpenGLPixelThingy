#include "OpenGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>

namespace OpenGL
{
	bool Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		{
			std::println("ERROR: Failed to init glad!");
			return false;
		}
		return true;
	}

	void Shutdown()
	{

	}
}
#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer
{
	void Init()
	{

	}

	void Render(const std::function<void()>& renderFunc)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if (renderFunc)
		{
			renderFunc();
		}
	}

	void Shutdown()
	{

	}
}
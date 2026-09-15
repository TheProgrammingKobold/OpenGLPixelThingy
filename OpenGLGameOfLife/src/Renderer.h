#pragma once

#include <functional>

namespace Renderer
{
	void Init();
	void Render(const std::function<void()>& renderFunc = nullptr);
	void Shutdown();
}

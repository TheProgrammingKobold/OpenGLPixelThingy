#include "Window.h"
#include "Renderer.h"
#include "OpenGL.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexMesh.h"

#include <random>
#include <functional>
#include <algorithm>


int sortByMostColor(const Pixel& pixel)
{
    if (pixel.r >= pixel.g && pixel.r >= pixel.b)
    {
        return 1;
    }
    else if (pixel.g >= pixel.r && pixel.g >= pixel.b)
    {
        return 2;
    }
    else if (pixel.b >= pixel.r && pixel.b >= pixel.g)
    {
        return 3;
    }
    return 4;
}

int sortByColorComb(const Pixel& pixel)
{
    return int(pixel.r + pixel.b + pixel.g);
}

void bubblesort(std::vector<Pixel>& pixels, std::function<void()> renderFunc, std::function<int(const Pixel&)> pixelFunc)
{
    bool swapped = false;


    for (int i = 0; i < pixels.size() - 1; i++) {
        swapped = false;


        for (int j = 0; j < pixels.size() - i - 1; j++) {
            if (pixelFunc(pixels[j]) > pixelFunc(pixels[j + 1])) {
                std::swap(pixels[j], pixels[j + 1]);
                swapped = true;
            }
        }

        if (renderFunc)
        {
            renderFunc();
        }

        if (Window::WindowShouldClose())
            break;

        if (!swapped) {
            break;
        }
    }
}

constexpr uint32_t TEXTURE_WIDTH = 800 / 8;
constexpr uint32_t TEXTURE_HEIGHT = 600 / 8;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 255);

std::vector<Pixel> pixels;

void applyPixelFunction()
{
    for (auto& pixel : pixels)
    {
        pixel.r = (dist(gen));
        pixel.g = (dist(gen));
        pixel.b = (dist(gen));
    }
}


int main()
{
    pixels.resize(TEXTURE_WIDTH * TEXTURE_HEIGHT);
    

	if (!Window::Init(800, 600, "Sorting Shinanigans"))
	{
		return -1;
	}

	if (!OpenGL::Init())
	{
		return -1;
	}

    VertexMesh mesh;

    Shader shader;
    Texture texture(TEXTURE_WIDTH, TEXTURE_HEIGHT, pixels);

	Renderer::Init();
    applyPixelFunction();

    size_t sortIndex = 0;
    size_t pass = 0;
    bool passSwapped = false;

	
	while (!Window::WindowShouldClose())
	{
        bubblesort(pixels, [&]() 
            {
                Renderer::Render();

                texture.bind();
                shader.use();

                texture.setTextureData(pixels);

                mesh.bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                Window::SwapBuffers();
                Window::PollEvents();
            }, sortByMostColor);
	}

	Renderer::Shutdown();
	OpenGL::Shutdown();
	Window::Shutdown();

	return 0;
}
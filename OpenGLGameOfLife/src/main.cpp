#include "Window.h"
#include "Renderer.h"
#include "OpenGL.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexMesh.h"

#include <random>

constexpr uint32_t WIDTH = 800 / 4;
constexpr uint32_t HEIGHT = 600 / 4;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 255);

std::vector<Pixel> pixels;

int pixelValue(const Pixel& pixel)
{
    return int(pixel.r + pixel.g + pixel.b);
}

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
    pixels.resize(WIDTH * HEIGHT);
    

	if (!Window::Init(800, 600, "GameOfLife"))
	{
		return -1;
	}

	if (!OpenGL::Init())
	{
		return -1;
	}

    VertexMesh mesh;

    Shader shader;
    Texture texture(WIDTH, HEIGHT, pixels);

	Renderer::Init();
    applyPixelFunction();

    size_t sortIndex = 0;
    size_t pass = 0;
    bool passSwapped = false;

	// Loop to maintain window
	while (!Window::WindowShouldClose())
	{

        bool swapped = false;

        // Outer loop runs up to n-1 times
        for (int i = 0; i < pixels.size() - 1; i++) {
            swapped = false;

            // Inner loop compares adjacent elements
            // The last i elements are already sorted, so we skip them
            for (int j = 0; j < pixels.size() - i - 1; j++) {
                if (pixelValue(pixels[j]) > pixelValue(pixels[j + 1])) {
                    std::swap(pixels[j], pixels[j + 1]);
                    swapped = true; // Mark that a swap occurred
                }
            }

            Renderer::Render();

            texture.bind();
            shader.use();

            texture.setTextureData(pixels);

            mesh.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            Window::SwapBuffers();
            Window::PollEvents();

            if (Window::WindowShouldClose())
                break;

            // If no two elements were swapped by inner loop, break
            if (!swapped) {
                break;
            }
        }


	}

	Renderer::Shutdown();
	OpenGL::Shutdown();
	Window::Shutdown();

	return 0;
}
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

struct HSV
{
    double h, // Hue (color)
        s,   // Saturation (Color -> gray)
        v;   // Value (brightness)
};

struct RGB
{
    double r, g, b;

    void convertPixelToRGB(const Pixel& pixel)
    {
        r = pixel.r / 255.0f;
        g = pixel.g / 255.0f;
        b = pixel.b / 255.0f;
    }
};

HSV rgb2hsv(Pixel _in)
{
    RGB in;
    in.convertPixelToRGB(_in);

    HSV out;
    double min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min < in.b ? min : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max > in.b ? max : in.b;

    out.v = max;

    delta = max - min;

    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0;
        return out;
    }

    if (max > 0.0)
    {
        out.s = delta / max;
    }
    else
    {
        out.s = 0.0;
        out.h = 0.0;
        return out;
    }

    if (in.r >= max)
        out.h = (in.g - in.b) / delta;
    else if (in.g >= max)
        out.h = 2.0 + (in.b - in.r) / delta;
    else
        out.h = 4.0 + (in.r - in.g) / delta;

    out.h *= 60.0;

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}


int sortByMostColor(const Pixel& pixel)
{
    if (pixel.r >= pixel.g && pixel.r >= pixel.b)
    {
        return pixel.r;
    }
    else if (pixel.g >= pixel.r && pixel.g >= pixel.b)
    {
        return pixel.g + 255;
    }
    else if (pixel.b >= pixel.r && pixel.b >= pixel.g)
    {
        return pixel.b + (255 * 2);
    }
    return 4;
}

int sortByColorComb(const Pixel& pixel)
{
    return int(pixel.r + pixel.b + pixel.g);
}

double sortByColor(const Pixel& pixel)
{
    HSV hsv = rgb2hsv(pixel);
    return hsv.h;
}

void selectionSort(std::vector<Pixel>& pixels,std::function<void()> renderFunc, std::function<double(const Pixel&)> pixelFunc) {
    int n = pixels.size();

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (pixelFunc(pixels[j]) < pixelFunc(pixels[min_idx])) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j;
            }
        }

        // Move minimum element to its
        // correct position
        std::swap(pixels[i], pixels[min_idx]);
        if (renderFunc)
        {
            renderFunc();
        }

        if (Window::WindowShouldClose())
            break;
    }
}

void mergeSort(std::vector<Pixel>& pixels, std::function<void()> renderFunc, std::function<double(const Pixel&)> pixelFunc)
{
    std::vector<Pixel> temp(pixels.size());

    std::function<void(int, int)> sort = [&](int left, int right)
        {
            if (left >= right || Window::WindowShouldClose())
                return;

            int mid = left + (right - left) / 2;

            sort(left, mid);
            sort(mid + 1, right);

            int i = left;
            int j = mid + 1;
            int k = left;

            while (i <= mid && j <= right)
            {
                if (pixelFunc(pixels[i]) <= pixelFunc(pixels[j]))
                    temp[k++] = pixels[i++];
                else
                    temp[k++] = pixels[j++];
            }

            while (i <= mid)
                temp[k++] = pixels[i++];

            while (j <= right)
                temp[k++] = pixels[j++];

            for (int n = left; n <= right; n++)
                pixels[n] = temp[n];

            if (renderFunc)
                renderFunc();

            if (Window::WindowShouldClose())
                return;
        };

    if (!pixels.empty())
        sort(0, pixels.size() - 1);
}

void quickSort(std::vector<Pixel>& pixels, std::function<void()> renderFunc, std::function<double(const Pixel&)> pixelFunc)
{
    std::function<void(int, int)> sort = [&](int low, int high)
        {
            if (low >= high || Window::WindowShouldClose())
                return;

            double pivot = pixelFunc(pixels[high]);

            int i = low;

            for (int j = low; j < high; j++)
            {
                if (pixelFunc(pixels[j]) < pivot)
                {
                    std::swap(pixels[i], pixels[j]);
                    i++;

                    if (renderFunc)
                        renderFunc();
                    if (Window::WindowShouldClose())
                        break;
                }
            }

            std::swap(pixels[i], pixels[high]);

            if (renderFunc)
                renderFunc();
            if (Window::WindowShouldClose())
                return;

            sort(low, i - 1);
            sort(i + 1, high);
        };

    if (!pixels.empty())
        sort(0, pixels.size() - 1);
}

void insertionSort(std::vector<Pixel>& pixels, std::function<void()> renderFunc, std::function<double(const Pixel&)> pixelFunc)
{
    for (int i = 1; i < pixels.size(); i++)
    {
        Pixel key = pixels[i];
        double keyValue = pixelFunc(key);

        int j = i - 1;

        while (j >= 0 && pixelFunc(pixels[j]) > keyValue)
        {
            pixels[j + 1] = pixels[j];
            j--;
        }

        pixels[j + 1] = key;

        if (renderFunc)
            renderFunc();

        if (Window::WindowShouldClose())
            break;
    }
}

void bubblesort(std::vector<Pixel>& pixels, std::function<void()> renderFunc, std::function<double(const Pixel&)> pixelFunc)
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
std::uniform_int_distribution<int> dist2(1, 3);

std::vector<Pixel> pixels;

void applyPixelFunction()
{
    std::uniform_real_distribution<float> hueDist(0.0f, 360.0f);

    for (auto& pixel : pixels)
    {
        float h = hueDist(gen);
        float s = 1.0f;
        float v = 1.0f;

        float c = v * s;
        float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = v - c;

        float r, g, b;

        if (h < 60)
            r = c, g = x, b = 0;
        else if (h < 120)
            r = x, g = c, b = 0;
        else if (h < 180)
            r = 0, g = c, b = x;
        else if (h < 240)
            r = 0, g = x, b = c;
        else if (h < 300)
            r = x, g = 0, b = c;
        else
            r = c, g = 0, b = x;

        pixel.r = static_cast<uint8_t>((r + m) * 255);
        pixel.g = static_cast<uint8_t>((g + m) * 255);
        pixel.b = static_cast<uint8_t>((b + m) * 255);
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
            }, sortByColor);
	}

	Renderer::Shutdown();
	OpenGL::Shutdown();
	Window::Shutdown();

	return 0;
}
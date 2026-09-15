#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexMesh
{
public:
	VertexMesh();

	void bind();

private:

	GLuint _VAO;
};


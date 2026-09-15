#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
public:

	Shader();

	void use();

	void setBool(const std::string& name, bool set);
	void setInt(const std::string& name, int set);
	void setFloat(const std::string& name, float set);

private:

	void _checkShaderCompilationErrors(GLuint id, std::string type);

	GLuint _ID;

};


#pragma once

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>


class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexShader, const char* fragmentShader);
	void CreateFromFile(const char* vshaderLocation, const char* fshaderLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexShader, const char* fragmentShader);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


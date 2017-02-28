#pragma once

#include "../../../Include.h"

class ShaderManager
{
public:
	ShaderManager(GLenum shaderType);
	~ShaderManager();

	GLuint Get(std::string shaderPath);

private:
	char*  ReadShaderFromFile(std::string path);
	GLuint CompileShader(const char* shaderText);

	std::map <std::string, GLuint> _shaderMap;
	GLenum                         _shaderType;
};
#include "ShaderManager.h"



ShaderManager::ShaderManager(GLenum shaderType)
{
	_shaderType = shaderType;
}


ShaderManager::~ShaderManager()
{
	for (std::map<std::string, GLuint>::iterator it = _shaderMap.begin(); it != _shaderMap.end(); ++it)
		glDeleteShader (it->second);
}

GLuint ShaderManager::Get (std::string shaderPath)
{
	GLuint shader = _shaderMap[shaderPath];

	if (!shader)
	{
		char* shaderText = ReadShaderFromFile(shaderPath);

		shader = CompileShader(shaderText);

		delete shaderText;

		_shaderMap[shaderPath] = shader;
	}

	return shader;
}

char* ShaderManager::ReadShaderFromFile(std::string path)
{
	int fileLength = 0;

	FILE* in = fopen(path.c_str(), "r");

	fseek(in, 0, SEEK_END);
	fileLength = ftell(in);
	fseek(in, 0, SEEK_SET);

	char* text = new char[fileLength];
	memset(text, 0, sizeof(char) * fileLength);

	fread(text, fileLength, sizeof(char), in);

	fclose(in);

	printf("shader %s is readed.\n", path.c_str());

	return text;
}

GLuint ShaderManager::CompileShader (const char* shaderText)
{
	GLuint shaderObj = glCreateShader(_shaderType);

	if (shaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", _shaderType);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = shaderText;
	GLint lengths[1];
	lengths[0] = strlen(shaderText);
	glShaderSource(shaderObj, 1, p, lengths);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", _shaderType, infoLog);
		exit(1);
	}

	return shaderObj;
}
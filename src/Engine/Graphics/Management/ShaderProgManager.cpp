#include "ShaderProgManager.h"


bool operator< (const ShaderNames& left, const ShaderNames& right) {
	if (left._vertexShaderName  < right._vertexShaderName) return true;
	if (left._vertexShaderName  > right._vertexShaderName) return false;

	if (left._fragmentShaderName < right._fragmentShaderName) return true;
	return false;
}

ShaderProgManager::ShaderProgManager()
{
	_vertexShaderManager   = new ShaderManager (GL_VERTEX_SHADER);
	_fragmentShaderManager = new ShaderManager (GL_FRAGMENT_SHADER);
}


ShaderProgManager::~ShaderProgManager()
{
	delete _vertexShaderManager;
	delete _fragmentShaderManager;

	for (std::map<ShaderNames, ShaderProg*>::iterator it = _shaderProgMap.begin(); it != _shaderProgMap.end(); ++it)
		delete it->second;
}


ShaderProg* ShaderProgManager::Get(ShaderNames names)
{
	ShaderProg* shaderProg = _shaderProgMap[names];

	if (!shaderProg)
	{
		shaderProg = LoadShaderProg (names);

		_shaderProgMap[names] = shaderProg;
	}

	return shaderProg;
}

ShaderProg* ShaderProgManager::LoadShaderProg(ShaderNames names)
{
	GLuint shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	GLuint vertexShader   = _vertexShaderManager  ->Get(names._vertexShaderName  );
	GLuint fragmentShader = _fragmentShaderManager->Get(names._fragmentShaderName);

	glAttachShader(shaderProgram, vertexShader  );
	glAttachShader(shaderProgram, fragmentShader);

	GLint  success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
		exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
		exit(1);
	}

	printf("Vertex   shader %s and\n"      , names._vertexShaderName.  c_str());
	printf("Fragment shader %s is linked\n", names._fragmentShaderName.c_str());

	return new ShaderProg(shaderProgram);
}
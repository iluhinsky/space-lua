#pragma once

#include "../../../Include.h"
#include "../Shaders/ShaderProg.h"
#include "../Shaders/ShaderManager.h"

struct ShaderNames
{
	std::string _vertexShaderName;
	std::string _fragmentShaderName;
	std::string _geometryShaderName;
};

bool operator< (const ShaderNames& left, const ShaderNames& right);


class ShaderProgManager
{
public:
	ShaderProgManager();
	~ShaderProgManager();

	ShaderProg* Get (ShaderNames names);

private:
	ShaderManager* _vertexShaderManager;
	ShaderManager* _fragmentShaderManager;
	ShaderManager* _geometryShaderManager;

	ShaderProg* LoadShaderProg (ShaderNames names);

	std::map <ShaderNames, ShaderProg*> _shaderProgMap;
};


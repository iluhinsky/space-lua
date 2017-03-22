#pragma once

#include "../../../Include.h"
#include "Model.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 


struct Attribute
{
	char*	_name		= nullptr;
	int		_components = 0;
	int		_type		= 0;
	int		_offset		= 0;
};

struct Influence
{
	int _joint = 0;

};

struct MeshInfo
{
	bool			_isTexture		= false;
	float			_color[3]		= {};

	int				_attributeCount	= 0;
	Attribute*	    _attribute		= nullptr;

	int				_influenceCount	= 0;
	Influence*	    _influence		= nullptr;

	int				_dataCount		= 0;
	char*			_data			= nullptr;

	int				_nVerticles		= 0;
};

class ModelParser
{
public:
	ModelParser();
	~ModelParser();

	Model* GetModel(std::string modelName);

private:
	bool ModelParser::SetMeshVBO(char* data, int dataCount, Model* model);

	int _meshCount = 0;
};


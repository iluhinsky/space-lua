#pragma once

#include "../../../Include.h"
#include "Model.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 


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


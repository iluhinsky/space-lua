#pragma once

#include "../../../Include.h"
#include "../Model/Model.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	Model* Get(std::string ModelFileName);

private:
	Model* LoadModel(std::string ModelFileName);

	std::map <std::string, Model*> _modelMap;
};


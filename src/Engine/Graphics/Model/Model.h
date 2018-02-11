#pragma once

#include "Mesh.h"

class Model
{
	friend class ModelParser;

public:
	Model();
	~Model();

	int	  _amountMesh; // TODO: -> private
	Mesh* _meshes = 0; //
};


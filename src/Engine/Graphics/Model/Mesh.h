#pragma once

#include "../../../Include.h"

class Mesh
{
	friend class ModelParser;
	friend class Model;

public:
	Mesh();
	~Mesh();

	GLuint  _VBO;            // TODO: -> private

	int		_nVerticles = 0;

	struct  Offset
	{
		int _stride = 0;
		int _vertex = 0;
		int _normal = 0;
		int _uvtex  = 0;
	} _offset;
};


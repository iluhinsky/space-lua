#pragma once

#include "../../../Include.h"
#include "Model.h"


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

	Model* GetModel(const char modelPath[]);

private:
	bool ParseMesh      (FILE* modelFile, MeshInfo*  mesh     );
	bool ParseAttribute (FILE* modelFile, Attribute* attribute);
	bool ParseInfluence (FILE* modelFile, Influence* influence);

	bool SetBufferAttributes (MeshInfo* meshes, Model* model);
	bool SetMeshVBO          (MeshInfo* meshes, Model* model);

	MeshInfo*			_meshes    = 0;
	int				    _meshCount = 0;
};


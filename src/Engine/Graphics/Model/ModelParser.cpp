#include "ModelParser.h"


//It is absolutly safety class, nice-working;

const int VERTEX_ATTR_TYPE = 1;
const int NORMAL_ATTR_TYPE = 2;
const int UVTEX_ATTR_TYPE  = 3;


ModelParser::ModelParser()
{
}


ModelParser::~ModelParser()
{
	for (int i = 0; i < _meshCount; i++)
	{
		for (int j = 0; j < _meshes[i]._attributeCount; j++)
		{
			delete [] _meshes[i]._attribute[j]._name;
		}

		delete [] _meshes[i]._attribute;
		delete [] _meshes[i]._influence;
		delete [] _meshes[i]._data;
	}

	delete[] _meshes;
}

Model* ModelParser::GetModel(const char ModelPath[])
{
	assert(ModelPath);

	Model* newModel = new Model;

	FILE* modelFile = fopen(ModelPath, "rb");
	assert(modelFile);


	int sizeOfTextureName = 0;
	fread(&sizeOfTextureName, sizeof(int), 1, modelFile);

	char* TextureName = new char[sizeOfTextureName + 1];             // Problem
	fread(TextureName, sizeof(char), sizeOfTextureName, modelFile);  // of format

	fread(&(newModel->_amountMesh), sizeof(int), 1, modelFile);
	_meshCount = newModel->_amountMesh;

	_meshes           = new MeshInfo[newModel->_amountMesh];
	newModel->_meshes = new Mesh    [newModel->_amountMesh];

	for (int i = 0; i < newModel->_amountMesh; i++)
	{
		ParseMesh(modelFile, &_meshes[i]);
	};

	fclose(modelFile);

	SetBufferAttributes (_meshes, newModel);
	SetMeshVBO          (_meshes, newModel);

	printf("Model '%s' is successful parsed.\n", ModelPath);

	return newModel;
}

bool ModelParser::ParseAttribute(FILE* modelFile, Attribute* attribute)
{
	assert(modelFile);
	assert(attribute);
	
	int sizeOfAttributeName = 0;
	fread(&sizeOfAttributeName, sizeof(int), 1, modelFile);

	attribute->_name = new char[sizeOfAttributeName + 1];
	fread(attribute->_name, sizeof(char), sizeOfAttributeName, modelFile);
	(attribute->_name)[sizeOfAttributeName] = 0;

	fread(&(attribute -> _components),	sizeof(int), 1, modelFile);
	fread(&(attribute -> _type),		sizeof(int), 1, modelFile);
	fread(&(attribute -> _offset),		sizeof(int), 1, modelFile);

	if (strcmp(attribute -> _name, "Vertex_Position")		== 0) attribute -> _type = VERTEX_ATTR_TYPE;
	if (strcmp(attribute -> _name, "Vertex_Normal")			== 0) attribute -> _type = NORMAL_ATTR_TYPE;
	if (strcmp(attribute -> _name, "Vertex_TextureCoord")	== 0) attribute -> _type = UVTEX_ATTR_TYPE;
	
	return true;
}

bool ModelParser::ParseInfluence(FILE* modelFile, Influence* influence)
{
	fread(&(influence -> _joint), sizeof(int), 1, modelFile);
	
	float matrixComponents[4 * 4] = {};
	fread(matrixComponents, sizeof(float), 4 * 4, modelFile);

	return true;
};

bool ModelParser::ParseMesh(FILE* modelFile, MeshInfo* mesh)
{
	assert(modelFile);
	assert(mesh);
	
	fread(&(mesh ->_isTexture), sizeof ( bool), 1, modelFile);
	fread  (mesh ->  _color   , sizeof (float), 3, modelFile);

	fread(&(mesh ->_attributeCount), sizeof(int), 1, modelFile);
	mesh -> _attribute = new Attribute[mesh -> _attributeCount];

	for (int i = 0; i < mesh -> _attributeCount; i++)
	{
		ParseAttribute(modelFile, &(mesh -> _attribute)[i]);
	}

	fread(&(mesh -> _influenceCount), sizeof(int), 1, modelFile);
	mesh -> _influence = new Influence  [mesh -> _influenceCount];

	for (int i = 0; i < mesh -> _influenceCount; i++)
	{
		ParseInfluence(modelFile, &(mesh -> _influence)[i]);
	}
	
	fread(&(mesh -> _dataCount), sizeof(int), 1, modelFile);
	mesh -> _data = new char[mesh -> _dataCount];

	fread  (mesh -> _data, sizeof(char), mesh -> _dataCount, modelFile);
	fread(&(mesh -> _nVerticles), sizeof(int), 1, modelFile);
	
	return true;
};


bool ModelParser::SetBufferAttributes(MeshInfo* meshes, Model* model)
{
	for (int i = 0; i < model->_amountMesh; i++)
	{
		model->_meshes[i]._offset._stride = meshes[i]._dataCount / meshes[i]._nVerticles;
		model->_meshes[i]._nVerticles	  = meshes[i]._nVerticles;

		for (int j = 0; j < meshes[i]._attributeCount; j++)
		{
			switch (meshes[i]._attribute[j]._type)
			{
				case NORMAL_ATTR_TYPE: { model->_meshes[i]._offset._normal = meshes[i]._attribute[j]._offset; } break;
				case VERTEX_ATTR_TYPE: { model->_meshes[i]._offset._vertex = meshes[i]._attribute[j]._offset; } break;
				case UVTEX_ATTR_TYPE:  { model->_meshes[i]._offset._uvtex  = meshes[i]._attribute[j]._offset; } break;
			}
		}
	}
	
	return true;
}

bool ModelParser::SetMeshVBO(MeshInfo* meshes, Model* model)
{
	for (int i = 0; i < model -> _amountMesh; i++)
	{
		glGenBuffers(1, &((model->_meshes)[i]._VBO));
		glBindBuffer(GL_ARRAY_BUFFER, model->_meshes[i]._VBO);
		glBufferData(GL_ARRAY_BUFFER, meshes[i]._dataCount, meshes[i]._data, GL_STREAM_DRAW);
	}
	
	return true;
}
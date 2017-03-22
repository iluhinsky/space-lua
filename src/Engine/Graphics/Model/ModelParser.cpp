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

}

Model* ModelParser::GetModel(std::string modelName)
{
	Model* newModel = new Model;

	std::string modelPath = "../bin/resources/models/" + modelName;

	const aiScene *scene = Importer.ReadFile("C:/Users/Ganzz/Source/Repos/GameEngine/bin/resources/models/room1.3ds", aiProcessPreset_TargetRealtime_Fast);
	printf("%s", Importer.GetErrorString());
	
	aiMesh *mesh = scene->mMeshes[0]; 
	newModel->_amountMesh = 1;

	int numVerts = 3 * mesh -> mNumFaces;

	float* data = (float*) calloc(sizeof(float), numVerts * (3 + 2 + 3));


	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			data[(3*i + j) * 8 + 0] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].x;
			data[(3*i + j) * 8 + 1] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].y;
			data[(3*i + j) * 8 + 2] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].z;
			data[(3*i + j) * 8 + 3] = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x;
			data[(3*i + j) * 8 + 4] = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y;
			data[(3*i + j) * 8 + 5] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].x;
			data[(3*i + j) * 8 + 6] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].y;
			data[(3*i + j) * 8 + 7] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].z;
		}
	}

	newModel->_meshes = new Mesh[1];
	
	newModel->_meshes[0]._offset._stride = (3 + 2 + 3) * sizeof(float);
	newModel->_meshes[0]._nVerticles = numVerts;

	newModel->_meshes[0]._offset._vertex	= 0;
	newModel->_meshes[0]._offset._uvtex		= 3 * sizeof(float);
	newModel->_meshes[0]._offset._normal	= (3 + 2) * sizeof(float);

	SetMeshVBO((char*) data, numVerts * (3 + 2 + 3) * sizeof(float), newModel);

	printf("Model %s is parsed\n\n", modelPath.c_str());

	free(data);

	return newModel;

}

/*
Model* ModelParser::GetModel(std::string modelName)
{
	Model* newModel = new Model;

	std::string modelPath = "../bin/resources/models/" + modelName;

	FILE* modelFile = fopen(modelPath.c_str(), "rb");
	assert(modelFile);


	int sizeOfTextureName = 0;
	fread(&sizeOfTextureName, sizeof(int), 1, modelFile);

	char* TextureName = new char[sizeOfTextureName + 1];             
	fread(TextureName, sizeof(char), sizeOfTextureName, modelFile);  

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

	printf("Model '%s' is successful parsed.\n", modelPath);

	return newModel;
}

*/

bool ModelParser::SetMeshVBO(char* data, int dataCount, Model* model)
{
	for (int i = 0; i < model -> _amountMesh; i++)
	{
		glGenBuffers(1, &((model->_meshes)[i]._VBO));
		glBindBuffer(GL_ARRAY_BUFFER, model->_meshes[i]._VBO);
		glBufferData(GL_ARRAY_BUFFER, dataCount, data, GL_STREAM_DRAW);
	}
	
	return true;
}
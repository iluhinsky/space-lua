#include "ObjectManager.h"


bool operator< (const ObjectInfo& left, const ObjectInfo& right) {
	if (left._modelPath   < right._modelPath  ) return true;
	if (left._modelPath   > right._modelPath  ) return false;

	if (left._texturePath < right._texturePath) return true;
	if (left._texturePath > right._texturePath) return false;

	if (left._shaderPaths < right._shaderPaths) return true;
	return false;
}


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}


ObjectInfo* ObjectManager::Get(std::string Path)
{
	ObjectInfo* objectInfo = _objectMap[Path];

	if (!objectInfo)
	{
		objectInfo = LoadObjectInfo (Path);

		_objectMap[Path] = objectInfo;
	}

	return objectInfo;
}

ObjectInfo* ObjectManager::LoadObjectInfo(std::string Path)
{
	FILE* file = fopen(Path.c_str(), "r");

	char string[50] = {};

	ObjectInfo* objectInfo = new ObjectInfo;

	fscanf(file, "%s", string);
	objectInfo->_modelPath   = string;

	fscanf(file, "%s", string);
	objectInfo->_texturePath = string;

	fscanf(file, "%s", string);
	objectInfo->_shaderPaths._vertexShaderName   = string;

	fscanf(file, "%s", string);
	objectInfo->_shaderPaths._fragmentShaderName = string;

	fclose(file);

	printf("Object information %s is loaded.\n", Path.c_str());

	return objectInfo;
}
#pragma once

#include "../../Include.h"
#include "../Graphics/Management/ShaderProgManager.h"

struct ObjectInfo
{
	std::string _modelPath;
	std::string _texturePath;

	ShaderNames _shaderPaths;
};

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	ObjectInfo* Get (std::string Path);

private:
	ObjectInfo* LoadObjectInfo(std::string Path);

	std::map <std::string, ObjectInfo*> _objectMap;
};


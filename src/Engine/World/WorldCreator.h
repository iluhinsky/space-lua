#pragma once

#include "../Objects/ObjectFactory.h"

class WorldCreator
{
public:
	WorldCreator (std::vector<AbstractObject*>*  worldObjects);
	~WorldCreator();

	void Load (std::string worldFilePath);

	AbstractObject* CreateObject (ObjectParameters parameters);

private:
	ObjectType  GetObjectType (char* string);
	glm::vec3   GetPosition   (FILE* file);
	float       GetScale      (FILE* file);
	std::string GetPath       (FILE* file);

	std::vector<AbstractObject*>*  _worldObjects;
	ObjectFactory* _objectFactory;
};


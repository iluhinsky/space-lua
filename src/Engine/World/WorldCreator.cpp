#include "WorldCreator.h"

WorldCreator::WorldCreator(std::vector<AbstractObject*>*  worldObjects) :
	_worldObjects(worldObjects)
{
	_objectFactory = new ObjectFactory;
}


WorldCreator::~WorldCreator()
{
	delete _objectFactory;
}


void WorldCreator::Load(std::string worldFilePath)
{
	system("echo %cd%");

	FILE* file = fopen(worldFilePath.c_str(), "r");

	char string[10] = {};

	fscanf(file, "%s", string);

	while (strcmp(string, "END") != 0)
	{
		ObjectParameters parameters;

		parameters._objectType         = GetObjectType(string);
		parameters._worldPos           = GetPosition(file);
		parameters._scale              = GetScale(file);
		parameters._mainParametersPath = GetPath(file);

		AbstractObject* newObject = _objectFactory->CreateObject(parameters);

		_worldObjects->push_back (newObject);

		fscanf(file, "%s", string);
	}

	printf("World %s is loaded.\n", worldFilePath.c_str());

	fclose(file);
}


ObjectType  WorldCreator::GetObjectType (char* string)
{
	if (strcmp(string, "SHIP"  ) == 0) return SHIP;
	if (strcmp(string, "PLANET") == 0) return PLANET;

	return ERROR_TYPE;
}

glm::vec3   WorldCreator::GetPosition   (FILE* file)
{
	glm::vec3 worldPos;

	fscanf(file, "%f", &worldPos.x);
	fscanf(file, "%f", &worldPos.y);
	fscanf(file, "%f", &worldPos.z);

	return worldPos;
}

float       WorldCreator::GetScale(FILE* file)
{
	float scale = 0;

	fscanf(file, "%f", &scale);

	return scale;
}

std::string WorldCreator::GetPath       (FILE* file)
{
	char Path[50] = {};

	fscanf(file, "%s", Path);

	return Path;
}

AbstractObject* WorldCreator::CreateObject(ObjectParameters parameters)
{
	AbstractObject* newObject = _objectFactory->CreateObject(parameters);

	return newObject;
}
#include "World.h"

World::World()
{
	_worldCreator = new WorldCreator (&_GameObjects);
}

World::~World()
{
	delete _worldCreator;
}

void World::Load(std::string WorldPath)
{
	_worldCreator->Load(WorldPath);
}

void World::Draw(Camera* camera)
{
	for (size_t i = 0; i < _GameObjects.size(); i++)
		_GameObjects[i]->Draw(camera);
}

void World::BindController(Controller* controller)
{
	ObjectParameters parameters;

	parameters._mainParametersPath = ("../bin/resources/objects/SpaceTaxi.txt");
	parameters._objectType         = (SHIP);
	parameters._scale              = 1;
	parameters._worldPos           = (glm::vec3(0.0f, 0.0f, 0.0f));

	AbstractObject* newObject = _worldCreator->CreateObject(parameters);

	controller->BindObject(newObject);

	_GameObjects.push_back(newObject);
}
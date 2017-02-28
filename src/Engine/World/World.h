#pragma once

#include "../Math/Camera.h"
#include "../Objects/AbstractObject.h"
#include "../Logic/Controllers/Controller.h"

#include "WorldCreator.h"

class World
{
public:
	World();
	~World();

	void Load(std::string WorldPath);
	void Draw(Camera* camera);

	void BindController(Controller* controller);

private:
	std::vector <AbstractObject*> _GameObjects;

	WorldCreator* _worldCreator;
};
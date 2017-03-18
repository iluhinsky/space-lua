#pragma once

#include "../../Engine/Math/Camera.h"
#include "../Ship/Ship.h"
#include "WorldLoader.h"


class World
{
	friend class WorldLoader;

public:
	World();
	~World();

	void Init();
	void Load(std::string worldName);

	void Draw(Camera* camera);

private:
	std::vector <Ship*> ships_;

	WorldLoader* worldLoader_;
};
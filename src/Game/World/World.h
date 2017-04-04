#pragma once

#include "../../Engine/Math/Camera.h"
#include "../Ship/Ship.h"
#include "WorldLoader.h"


class World
{
	friend class WorldLoader;

	friend class Application; //! remove

public:
	World();
	~World();

	void Init();
	void Load(std::string worldName);

	void Draw(Camera* camera);

	void RunLUA();
	void ExecuteLogic();

private:
	std::vector <Ship*> ships_;

	WorldLoader* worldLoader_;
};
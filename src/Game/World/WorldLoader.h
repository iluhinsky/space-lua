#pragma once

#include "World.h"
#include "../Ship/Ship.h"
#include "../Ship/ShipFactory.h"

class WorldLoader
{
public:
	WorldLoader(std::vector<Ship*>* ships);
	~WorldLoader();

	void Init();

	World* Load(std::string worldName);

private:
	std::vector<Ship*>* ships_;

	ShipFactory shipFactory_;
};

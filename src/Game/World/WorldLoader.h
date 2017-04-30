#pragma once

#include "World.h"
#include "../Ship/Ship.h"
#include "../Ship/ShipFactory.h"

class WorldLoader
{
public:
	WorldLoader(std::map <int, Ship*>* shipsDataBase);
	~WorldLoader();

	void Init();

	void Load(std::string worldName);

private:
	std::map <int, Ship*>* shipsDataBase_;

	ShipFactory shipFactory_;
};

#pragma once

#include "Ship.h"
#include "Blocks/BlockFactory.h"


struct ShipInfo
{
	std::string name_;
	glm::vec3 coord_;
};


class ShipFactory
{
public:
	ShipFactory();
	~ShipFactory();

	void Init();

	Ship* GenerateShip(ShipInfo shipInfo);

private:
	BlockFactory blockFactory_;

	void LoadConstruction(Ship* ship);
	void LoadController(Ship* ship);
};


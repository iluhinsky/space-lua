#include "ShipFactory.h"



ShipFactory::ShipFactory()
{
}


ShipFactory::~ShipFactory()
{
}


void ShipFactory::Init()
{
	blockFactory_.Init();
}

Ship* ShipFactory::GenerateShip(ShipInfo shipInfo)
{
	Ship* ship = new Ship;

	ship->shipName_ = shipInfo.name_;
	ship->coord_    = shipInfo.coord_;

	LoadConstruction(ship);
	LoadController(ship);

	return ship;
}

void ShipFactory::LoadConstruction(Ship* ship)
{
	std::string constrName = "../bin/resources/construction/" + ship->shipName_ + ".txt";

	FILE* file = fopen(constrName.c_str(), "r");
	assert(file);

	Block* newBlock = nullptr;

	while (true) // TODO: REMOVE THIS FCKN SHIT !!!!!!!
	{
		newBlock = blockFactory_.GetBlock(file);

		if (newBlock == nullptr) break;

		ship->blocks_.push_back(newBlock);
	}

	fclose(file);
}

void ShipFactory::LoadController(Ship* ship)
{
	
}
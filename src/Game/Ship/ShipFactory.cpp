#include "ShipFactory.h"
#include "ShipController.h"


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
	assert(ship);

	std::string constrName = "../bin/resources/construction/" + ship->shipName_ + ".txt";

	FILE* file = fopen(constrName.c_str(), "r");
	assert(file);

	Block* newBlock = nullptr;

	while (true) // TODO: REMOVE THIS FCKN SHIT !!!!!!!
	{
		newBlock = blockFactory_.GetBlock(file);

		if (newBlock == nullptr)
		{
			break;
		}

		ship->blocks_.push_back(newBlock);
	}

	fclose(file);
}

void ShipFactory::LoadController(Ship* ship)
{
	assert(ship);

	std::string scriptName = "../bin/resources/scripts/" + ship->shipName_ + ".lua";
//	std::cout << "C++: scriptName = '" << scriptName << "'\n";

	luabridge::getGlobalNamespace(ship->controller_.luaState_).addFunction("SwitchShield", &ShipController::SwitchShield);
//	register other functions here

//	we need to update controller of a ship ?
	luaL_dofile(ship->controller_.luaState_, scriptName.c_str());
}

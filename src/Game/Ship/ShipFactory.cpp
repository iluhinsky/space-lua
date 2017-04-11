#include "ShipFactory.h"
#include "ShipController.h"

#include <btBulletDynamicsCommon.h>

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

	ship->shipName_      = shipInfo.name_;
	ship->CollisionType_ = CollidingShip;

	btQuaternion rotation(
		(rand() - RAND_MAX) / 2.0f,
		(rand() - RAND_MAX) / 2.0f,
		(rand() - RAND_MAX) / 2.0f,
		(M_PI * rand()) / RAND_MAX);

	btVector3 coord_(shipInfo.coord_.x, shipInfo.coord_.y, shipInfo.coord_.z);

	ship->transform_ = btTransform(rotation, coord_);

	LoadConstruction(ship);
	LoadController(ship);

	ship->InitRigidBody();

	return ship;
}

void ShipFactory::LoadConstruction(Ship* ship)
{
	assert(ship);

	std::string constrName = "../bin/resources/construction/" + ship->shipName_ + ".txt";

	FILE* file = fopen(constrName.c_str(), "r");
	assert(file);

	Block* newBlock = blockFactory_.GetBlock(file);

	while (newBlock != nullptr) 
	{
		ship->blocks_.push_back(newBlock);

		newBlock = blockFactory_.GetBlock(file);
	}

	fclose(file);
}

void ShipFactory::LoadController(Ship* ship)
{
	assert(ship);

	std::string scriptName = "../bin/resources/scripts/" + ship->shipName_ + ".lua";
//	std::cout << "C++: scriptName = '" << scriptName << "'\n";
	luaL_loadfile(ship->controller_.luaThread_, scriptName.c_str());
//	if we use lua_sethook, we should call lua_resume(l, NULL, 0) while updating shipController
	lua_sethook(ship->controller_.luaThread_, ShipController::CatchLuaHook, LUA_MASKCOUNT, INSTRUCTION_LIMIT);

	luabridge::getGlobalNamespace(ship->controller_.luaThread_).addFunction("SwitchShield", &ShipController::SwitchShield);
//	register other functions here

//	we need to update controller of a ship ?
//	luaL_dofile(ship->controller_.luaState_, scriptName.c_str());
	lua_resume(ship->controller_.luaThread_, NULL, 0); // for testing
	lua_resume(ship->controller_.luaThread_, NULL, 0); // for testing
}

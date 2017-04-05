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
	
	ship->shipName_ = shipInfo.name_;

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

	char errorMessage[200] = {};
	int error = luaL_loadfile(ship->controller_.luaThread_, scriptName.c_str(), NULL, errorMessage);
	switch (error)
	{
	case LUA_OK:
//		std::cout << "LUA script loaded." << std::endl;
		break;
	case LUA_ERRSYNTAX:
		std::cout << "LUA compilation error. " << errorMessage << std::endl;
		break;
	default:
		std::cout << "ERROR. Problems with loading LUA script. Code of error is equal to " << error << std::endl;
	}

//	if we use lua_sethook, we should call lua_resume(l, NULL, 0) while updating shipController
	lua_sethook(ship->controller_.luaThread_, ShipController::CatchLuaHook, LUA_MASKCOUNT, INSTRUCTION_LIMIT);

	luabridge::getGlobalNamespace(ship->controller_.luaThread_).addFunction("GetTime",       &ShipController::GetTime);
	luabridge::getGlobalNamespace(ship->controller_.luaThread_).addFunction("SwitchShield",  &ShipController::SwitchShield);
	luabridge::getGlobalNamespace(ship->controller_.luaThread_).addFunction("EnableShield",  &ShipController::EnableShield);
	luabridge::getGlobalNamespace(ship->controller_.luaThread_).addFunction("DisableShield", &ShipController::DisableShield);
//	register other functions here

}

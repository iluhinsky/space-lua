#include "ShipController.h"
#include "Ship.h"
#include "Blocks/BlockShield.h"

std::map<lua_State*, Ship*> ShipController::shipsDataBase_;


ShipController::ShipController(Ship* ship)
{
	assert(ship);
	ship_ = ship;

	luaState_ = luaL_newstate();
	luaL_openlibs(luaState_);

	luaThread_ = lua_newthread(luaState_);
	shipsDataBase_[luaThread_] = ship;
}



ShipController::~ShipController()
{
}


void ShipController::SwitchShield(const std::string& blockName, const bool mode, const float time, lua_State* luaThread)
{
	assert(time >= 0.0);
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	Block* currentBlock = NULL;
	const int blocksNum = ship->blocks_.size();

	for (int i = 0; i < blocksNum; ++i)
	{
		currentBlock = ship->blocks_[i]; 

		if (currentBlock->GetType() == BlockTypeShield && !blockName.compare(((BlockShield*)currentBlock)->GetName()))
		{
			((BlockShield*)currentBlock)->Switch(mode, time);
//			if (mode) std::cout << "Shield was switched on\n"; else std::cout << "Shield was switched off\n"; // for testing
			break;
		}
	}

	std::cout << "There are no appropriate shields for switching" << " ('" << blockName << "') " << std::endl; // for testing
}


void ShipController::CatchLuaHook(lua_State* luaThread, lua_Debug* luaDebug)
{
	assert(luaThread);
	assert(luaDebug);

	std::cout << "LUA HOOK " << std::endl;
	lua_yield(luaThread, 0);
}

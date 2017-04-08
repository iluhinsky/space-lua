#include "ShipController.h"
#include "Ship.h"
#include "Blocks/BlockShield.h"
#include "../../Application/Application.h"

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


float ShipController::GetTime(lua_State* luaThread)
{
	assert(luaThread);

	sf::Time elapsedTime = APPLICATION->getTime();

	return elapsedTime.asSeconds();
}


void ShipController::SwitchShield(const std::string& blockName, const bool mode, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	Block* currentBlock = NULL;
	const int blocksNum = ship->blocks_.size();

	int i = 0;
	for (i = 0; i < blocksNum; ++i)
	{
		currentBlock = ship->blocks_[i]; 

		if (currentBlock->GetType() == BlockTypeShield && !blockName.compare(((BlockShield*)currentBlock)->GetName()))
		{
			if (mode)
			{
				((BlockShield*)currentBlock)->SetComand(EnableShieldCommand);
			}
			else
			{
				((BlockShield*)currentBlock)->SetComand(DisableShieldCommand);
			}

			break;
		}
	}

	if (i == blocksNum)
	{
		std::cout << "There are no appropriate shields for switching" << " ('" << blockName << "') " << std::endl; // for testing
	}
}


void ShipController::EnableShield(const std::string& blockName, lua_State* luaThread)
{
	assert(luaThread);

	SwitchShield(blockName, true, luaThread);
}


void ShipController::DisableShield(const std::string& blockName, lua_State* luaThread)
{
	assert(luaThread);

	SwitchShield(blockName, false, luaThread);
}


void ShipController::CatchLuaHook(lua_State* luaThread, lua_Debug* luaDebug)
{
	assert(luaThread);
	assert(luaDebug);

//	std::cout << "LUA HOOK " << std::endl;
	lua_yield(luaThread, 0);
}


void ShipController::Run()
{
	if (luaThread_ == NULL)
	{
//		std::cout << "LUA script: nothing to do (there are no comands in the stack)." << std::endl;
		return;
	}

	int luaStatus = LUA_OK;
	luaStatus = lua_resume(luaThread_, NULL, 0);
//	std::cout << "luaStatus = " << luaStatus << std::endl;

	switch (luaStatus)
	{
	case LUA_OK:
		//! there is no chunks in the lua stack! We must not call lua_resume after this point
		luaThread_ = NULL;
		break;

	case LUA_YIELD:
		//! lua script has too many instructions! (maybe everything is OK?)
		//std::cout << "LUA script has too many instructions!" << std::endl;
		break;

	default:
		//! handling errors connected with lua script
		std::cout << "LUA ERROR! lua_resume returned " << luaStatus << std::endl;
		luaThread_ = NULL;
		break;
	}

//	for (int i = 0; i < 3e8; i++); // lol
}

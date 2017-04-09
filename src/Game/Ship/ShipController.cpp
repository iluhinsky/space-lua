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

	isLuaScriptNormal_ = true;
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
	if (!isLuaScriptNormal_)
	{
		return;
	}

	lua_pushvalue(luaThread_, -1);
	int luaStatus = lua_resume(luaThread_, NULL, 0);

	switch (luaStatus)
	{
	case LUA_OK:
		lua_sethook(luaThread_, ShipController::CatchLuaHook, 0, INSTRUCTION_LIMIT);
		break;

	case LUA_YIELD:
		std::cout << "ERROR! There are too many instructions for " << shipsDataBase_[luaThread_]->shipName_ << ". The lua script will not work.\n";
		isLuaScriptNormal_ = false;
		break;

	default:
		std::cout << "LUA RUNTIME ERROR! " << lua_tostring(luaThread_, -1) << std::endl;
		lua_pop(luaThread_, 1);
		isLuaScriptNormal_ = false;
		break;
	}

	if (lua_gettop(luaThread_) != 1 || luaStatus != LUA_OK)
	{
		std::cout << "Smth went wrong with lua stack (" << shipsDataBase_[luaThread_]->shipName_ << "). The lua script will not work.\n";
		isLuaScriptNormal_ = false;
	}

}

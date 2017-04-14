#include "ShipController.h"
#include "Ship.h"
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


void ShipController::SwitchShield(const std::string& blockName, BlockShieldCommand command, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	auto it = std::find_if(ship->blocks_.begin(), ship->blocks_.end(), [blockName](Block* block)
	{
		return block->GetType() == BlockTypeShield && 
			!blockName.compare(((BlockShield*)block)->GetName());
	});

	if (it != ship->blocks_.end())
		((BlockShield*)(*it))->SetComand(command);
	else
		std::cout << "There are no appropriate shields for switching" << 
		" ('" << blockName << "') " << std::endl; // for testing
}


void ShipController::EnableShield(const std::string& blockName, lua_State* luaThread)
{
	assert(luaThread);

	SwitchShield(blockName, EnableShieldCommand, luaThread);
}


void ShipController::DisableShield(const std::string& blockName, lua_State* luaThread)
{
	assert(luaThread);

	SwitchShield(blockName, DisableShieldCommand, luaThread);
}


void ShipController::CatchLuaHook(lua_State* luaThread, lua_Debug* luaDebug)
{
	assert(luaThread);
	assert(luaDebug);

//	std::cout << "LUA HOOK " << std::endl;
	lua_yield(luaThread, 0);
}


void ShipController::Shoot(const std::string& blockName, double xBulletDir, double yBulletDir, double zBulletDir, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	auto it = std::find_if(ship->blocks_.begin(), ship->blocks_.end(), [blockName](Block* block)
	{
		return block->GetType() == BlockTypeWeapon &&
			!blockName.compare(((BlockWeapon*)block)->GetName());
	});

	if (it != ship->blocks_.end())
	{
		((BlockWeapon*)(*it))->SetDirection(glm::vec3(xBulletDir, yBulletDir, zBulletDir));
		((BlockWeapon*)(*it))->SetCommand(ShootCommand);
	}
	else
		std::cout << "There are no appropriate shields for shooting" <<
		" ('" << blockName << "') " << std::endl; // for testing
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

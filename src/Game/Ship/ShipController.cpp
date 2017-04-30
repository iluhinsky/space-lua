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

	Block* block = FindBlock(blockName, BlockTypeShield, ship);

	if (block != nullptr)
		((BlockShield*)(block))->SetComand(command);
	else
		std::cout << "There are no appropriate shields for switching" << " ('" << blockName << "') " << std::endl;
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


bool ShipController::IsDirectionAllowed(const std::string& blockName, double xDir, double yDir, double zDir, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	bool isDirectionAllowed = false;
	Block* block = FindBlock(blockName, BlockTypeWeapon, ship);
/*	if (block == ship->blocks_.end())
	{
		block = GetBlock(blockName, BlockTypeEngine, ship); // for engine
	}*/

	if (block != nullptr)
	{
		isDirectionAllowed = ((OrientedBlock*)(block))->IsDirectionAllowed(glm::vec3(xDir, yDir, zDir));
	}

	return isDirectionAllowed;
}


void ShipController::Shoot(const std::string& blockName, double xBulletDir, double yBulletDir, double zBulletDir, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	Block* block = FindBlock(blockName, BlockTypeWeapon, ship);

	if (block != nullptr)
	{
		((BlockWeapon*)(block))->SetDirection(glm::vec3(xBulletDir, yBulletDir, zBulletDir));
		((BlockWeapon*)(block))->SetCommand(ShootCommand);
	}
	else
		std::cout << "There are no appropriate shields for shooting" << " ('" << blockName << "') " << std::endl;
}


ShipInfoForLUA ShipController::GetShipInfo(int shipID, lua_State* luaThread)
{
	assert(shipID >= 0);
	assert(luaThread);

	ShipInfoForLUA info = {};
	Ship* ship = WORLD->GetShipByID(shipID);
	if (!ship)
	{
		std::cout << "There is no ship in your scope with ID = " << shipID << ".\n";
		return info;
	}

	btTransform transform = ship->GetTransform();
	btVector3   coords    = transform.getOrigin();

	info.x = coords.x();
	info.y = coords.y();
	info.z = coords.z();

	return info;
}


std::vector<int> ShipController::GetBlocksByShipID(int shipID, lua_State* luaThread)
{
	assert(shipID >= 0);
	assert(luaThread);

	Ship* ship = WORLD->GetShipByID(shipID);
	if (!ship)
	{
		std::cout << "There is no ship in your scope with ID = " << shipID << ".\n";
		std::vector<int> empty;
		return empty;
	}

	return ship->blocksID_;
}


BlockInfoForLUA ShipController::GetBlockInfo(int shipID, int blockID, lua_State* luaThread)
{
	assert(blockID >= 0);
	assert(luaThread);

	BlockInfoForLUA info = {};
	Ship* ship = WORLD->GetShipByID(shipID);
	if (!ship)
	{
		std::cout << "There is no ship in your scope with ID = " << shipID << ".\n";
		return info;
	}

	auto it = ship->blocksDataBase_.find(blockID);
	if (it == ship->blocksDataBase_.end())
	{
		std::cout << "There is no block with ID = " << blockID << " at the ship with ID = " << shipID << ".\n";
		return info;
	}

	Block* block = it->second;
	assert(block);

	// here we fill the structure 'info' by information about block

	return info;
}


Block* ShipController::FindBlock(const std::string& blockName, BlockType blockType, Ship* ship)
{
	assert(ship);

	auto it = std::find_if(ship->blocksDataBase_.begin(), ship->blocksDataBase_.end(), [blockName, blockType](auto block)
	{
		return block.second->GetType() == blockType && !blockName.compare(block.second->GetName());
	});

	if (it == ship->blocksDataBase_.end())
		return nullptr;

	return (*it).second;
}


void ShipController::Run()
{
	if (!isLuaScriptNormal_)
	{
		return;
	}

	luabridge::push(luaThread_, WORLD->GetShipsID());
	lua_setglobal(luaThread_, "shipsID");

	lua_pushvalue(luaThread_, -1);
	int luaStatus = LUA_OK;
	try
	{
		luaStatus = lua_resume(luaThread_, NULL, 0);
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << "Out of range error in shipsID: " << oor.what() << '\n';
	}

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

#include "ShipController.h"
#include "Ship.h"
#include "../../Application/Application.h"

std::map<lua_State*, Ship*> ShipController::shipsDataBase_;
extern const int engineMaxPower;
extern const int instructionsLimit = 1000;


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


int ShipController::GetSelfID(lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	const int shipID = WORLD->GetIDByShip(ship);
	assert(shipID >= 0);

	return shipID;
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
//	else
//		std::cout << ship->shipName_ << ": There are no appropriate shields for switching" << " (" << blockName << ").\n";
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
	if (block == nullptr)
	{
		block = FindBlock(blockName, BlockTypeEngine, ship);
	}

	if (block != nullptr)
	{
		isDirectionAllowed = ((OrientedBlock*)(block))->IsDirectionAllowed(glm::vec3(xDir, yDir, zDir));
	}
//	else
//		std::cout << ship->shipName_ << ": There is no engine or weapon block with name '" << blockName << "'.\n";

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
//	else
//		std::cout << ship->shipName_ << ": There are no appropriate weapons for shooting" << " (" << blockName << ").\n";
}


void ShipController::Gas(const std::string& blockName, double xDir, double yDir, double zDir, int power, lua_State* luaThread)
{
	assert(luaThread);

	Ship* ship = shipsDataBase_[luaThread];
	assert(ship);

	Block* block = FindBlock(blockName, BlockTypeEngine, ship);

	if (block != nullptr)
	{
		((BlockEngine*)(block))->SetDirectionFromAngles(5, 90);

		//((BlockEngine*)(block))->SetDirection(glm::vec3(xDir, yDir, zDir));
		((BlockEngine*)(block))->SetCommand(GasCommand);
		if (0 <= power && power <= engineMaxPower)
			((BlockEngine*)(block))->SetPower(power);
//		else
//			std::cout << ship->shipName_ << ": Incorrect engine power. It is " << power << " but it should be integer between 0 and 10. It will be equal to 1.\n";
	}
//	else
//		std::cout << ship->shipName_ << ": There are no appropriate engines for gasing" << " (" << blockName << ").\n";
}


ShipInfoForLUA ShipController::GetShipInfo(int shipID, lua_State* luaThread)
{
	assert(shipID >= 0);
	assert(luaThread);

	ShipInfoForLUA info = {};
	Ship* ship = WORLD->GetShipByID(shipID);
	if (!ship)
	{
//		std::cout << shipsDataBase_[luaThread]->shipName_ << ": There is no ship in your scope with ID = " << shipID << ".\n";
		return info;
	}

	btTransform transform = ship->GetTransform();
	btVector3   coords    = transform.getOrigin();
	btVector3   velocity  = ship->getVelocity();

	info.x = coords.x();
	info.y = coords.y();
	info.z = coords.z();
	info.velx = velocity.x();
	info.vely = velocity.y();
	info.velz = velocity.z();
//	std::cout << "C++: velocity = " << info.vx << " " << info.vy << " " << info.vz << "\n";

	info.team = ship->team_;

	return info;
}


std::vector<int> ShipController::GetBlocksByShipID(int shipID, lua_State* luaThread)
{
	assert(shipID >= 0);
	assert(luaThread);

	Ship* ship = WORLD->GetShipByID(shipID);
	if (!ship)
	{
//		std::cout << shipsDataBase_[luaThread]->shipName_ << ": There is no ship in your scope with ID = " << shipID << ".\n";
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
//		std::cout << shipsDataBase_[luaThread]->shipName_ << ": There is no ship in your scope with ID = " << shipID << ".\n";
		return info;
	}

	auto it = ship->blocksDataBase_.find(blockID);
	if (it == ship->blocksDataBase_.end())
	{
//		std::cout << shipsDataBase_[luaThread]->shipName_ << ": There is no block with ID = " << blockID << " at the ship with ID = " << shipID << ".\n";
		return info;
	}

	Block* block = it->second;
	assert(block);

	glm::vec3 globalCoords = block->GetGlobalCoords();

	info.x = globalCoords.x;
	info.y = globalCoords.y;
	info.z = globalCoords.z;

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

	//luabridge::push(luaThread_, )

	lua_pushvalue(luaThread_, -1);
	int luaStatus = LUA_OK;
	try
	{
		luaStatus = lua_resume(luaThread_, NULL, 0);
	}
	catch (const std::out_of_range& oor)
	{	
		std::cout << ship_->shipName_ << ": Out of range error in shipsID: " << oor.what() << ". The lua script will not work.\n";
		isLuaScriptNormal_ = false;
	}

	switch (luaStatus)
	{
	case LUA_OK:
		lua_sethook(luaThread_, ShipController::CatchLuaHook, 0, instructionsLimit);
		break;

	case LUA_YIELD:
		std::cout << ship_->shipName_ << ": ERROR! There are too many instructions for " << shipsDataBase_[luaThread_]->shipName_ << ". The lua script will not work.\n";
		isLuaScriptNormal_ = false;
		break;

	default:
		std::cout << ship_->shipName_ << ": LUA RUNTIME ERROR! " << lua_tostring(luaThread_, -1) << std::endl;
		lua_pop(luaThread_, 1);
		isLuaScriptNormal_ = false;
		break;
	}

	if (lua_gettop(luaThread_) != 1 || luaStatus != LUA_OK)
	{
		std::cout << ship_->shipName_ << ": Smth went wrong with lua stack (" << shipsDataBase_[luaThread_]->shipName_ << "). The lua script will not work.\n";
		isLuaScriptNormal_ = false;
	}

}

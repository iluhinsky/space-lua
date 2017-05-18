#include "ShipFactory.h"
#include "ShipController.h"

#include <btBulletDynamicsCommon.h>
#include "../../Application/Application.h"

extern const int instructionsLimit;

std::vector<glm::vec3> colors =
{
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f)
};

std::map<Direction, glm::vec3> directionShifts =
{
	{ x_up  , glm::vec3( 1.0f, 0.0f, 0.0f) },
	{ y_up  , glm::vec3( 0.0f, 1.0f, 0.0f) },
	{ z_up  , glm::vec3( 0.0f, 0.0f, 1.0f) },
	{ x_down, glm::vec3(-1.0f, 0.0f, 0.0f) },
	{ y_down, glm::vec3( 0.0f,-1.0f, 0.0f) },
	{ z_down, glm::vec3( 0.0f, 0.0f,-1.0f) },
};


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
	ship->collisionType_ = CollidingShip;

	auto shipTeam = teamsDictionary_.find(ship->shipName_);

	if (shipTeam != teamsDictionary_.end())
	{
		ship->team_  = shipTeam->second;
		ship->color_ = colors[shipTeam->second];
	}
	else
	{
		int newTeam = teamsDictionary_.size();

		teamsDictionary_[ship->shipName_] = newTeam;

		ship->team_  = newTeam;
		ship->color_ = colors[newTeam];
	}

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
	ship->UpdateBlocksIDVector();

	for (auto block : ship->blocksDataBase_)
		if (block.second->GetType() == BlockTypeEngine) {
			((BlockEngine*)block.second)->SetFire(APPLICATION->GetGraphicsWorld()->GetFireParticleSystem(glm::vec3(shipInfo.coord_.x, shipInfo.coord_.y, shipInfo.coord_.z) + block.second->GetRelatedCoords(), glm::vec3(1, 0, 0)));
		}

	return ship;
}


void ShipFactory::LoadConstruction(Ship* ship)
{
	assert(ship);

	std::string constrName = "../bin/resources/construction/" + ship->shipName_ + ".txt";

	FILE* file = fopen(constrName.c_str(), "r");
	assert(file);

	int freeID = 0;

	Block* newBlock = blockFactory_.GetBlock(file);

	while (newBlock != nullptr) 
	{
		newBlock->SetShip(ship);

		ship->blocksDataBase_[freeID] = newBlock;
		freeID++;

		newBlock = blockFactory_.GetBlock(file);
	}

	fclose(file);

	auto it = std::find_if(ship->blocksDataBase_.begin(), ship->blocksDataBase_.end(),
		[](std::pair<int, Block*> block)
	{ return block.second->GetType() == BlockTypeMain ? true : false; });

	assert(it != ship->blocksDataBase_.end());

	ship->blockMain = it->second;

	MakeLinks(ship);
}


void ShipFactory::LoadController(Ship* ship)
{
	assert(ship);
	std::string scriptName = "../bin/resources/scripts/" + ship->shipName_ + ".lua";

	lua_State* luaThread = ship->controller_.luaThread_;
	assert(luaThread);

	int errorCode = luaL_loadfile(luaThread, scriptName.c_str());
	switch (errorCode)
	{
	case LUA_OK:
//		std::cout << "LUA script was successfully loaded." << std::endl;
		break;

	case LUA_ERRSYNTAX:
		std::cout << "LUA COMPILATION ERROR. " << lua_tostring(luaThread, -1) << std::endl;
		lua_pop(luaThread, 1);
		break;

	default:
		std::cout << "LUA ERROR. Problems with loading LUA script. Error's code is " << errorCode << std::endl;
		break;
	}

	if (errorCode != LUA_OK || lua_gettop(luaThread) != 1)
	{
		std::cout << "LUA ERROR. Stack is incorrect. It will be empty." << std::endl;
		lua_settop(luaThread, 0);
		ship->controller_.isLuaScriptNormal_ = false;
		return;
	}


	lua_sethook(luaThread, ShipController::CatchLuaHook, LUA_MASKCOUNT, instructionsLimit);

	luabridge::getGlobalNamespace(ship->controller_.luaThread_)
		.addFunction("GetSelfID",          &ShipController::GetSelfID)
		.addFunction("GetTime",            &ShipController::GetTime)
		.addFunction("EnableShield",       &ShipController::EnableShield)
		.addFunction("DisableShield",      &ShipController::DisableShield)
		.addFunction("Shoot",              &ShipController::Shoot)
		.addFunction("IsDirectionAllowed", &ShipController::IsDirectionAllowed)
		.addFunction("GetShipInfo",        &ShipController::GetShipInfo)
		.addFunction("GetBlocks",          &ShipController::GetBlocksByShipID)
		.addFunction("GetBlockInfo",       &ShipController::GetBlockInfo)
		.addFunction("Gas",                &ShipController::Gas)

		.beginClass <ShipInfoForLUA> ("ShipInfoForLUA")
			.addData("x",    &ShipInfoForLUA::x)
			.addData("y",    &ShipInfoForLUA::y)
			.addData("z",    &ShipInfoForLUA::z)
			.addData("vx",   &ShipInfoForLUA::velx)
			.addData("vy",   &ShipInfoForLUA::vely)
			.addData("vz",   &ShipInfoForLUA::velz)
			.addData("team", &ShipInfoForLUA::team)
		.endClass()

		.beginClass <BlockInfoForLUA> ("BlockInfoForLUA")
			.addData("x", &BlockInfoForLUA::x)
			.addData("y", &BlockInfoForLUA::y)
			.addData("z", &BlockInfoForLUA::z)
		.endClass()

		.beginClass <std::vector<int>> ("IntVector")
			.addFunction("GetSize", &std::vector<int>::size)
			.addFunction <std::vector<int>::const_reference(std::vector<int>::*)(std::vector<int>::size_type) const> ("at", &std::vector<int>::at)
		.endClass();

}

void ShipFactory::MakeLinks(Ship* ship)
{
	for (auto currBlock : ship->blocksDataBase_)
	{
		for (auto direction : directionShifts)
		{
			auto neihborBlockIt = std::find_if(ship->blocksDataBase_.begin(), ship->blocksDataBase_.end(),
				[currBlock, direction](std::pair<int, Block*> neihborBlock)
			{
				return isEqual (
					neihborBlock.second->GetRelatedCoords(),
					currBlock.second   ->GetRelatedCoords() + direction.second);
			});

			if (neihborBlockIt != ship->blocksDataBase_.end())
				currBlock.second->Link(direction.first, (*neihborBlockIt).second);
		}
	}
}
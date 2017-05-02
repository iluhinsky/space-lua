#pragma once
#include <map>
#include <SFML/Graphics.hpp>

extern "C"
{
	#include <lua/lua.h>
	#include <lua/lauxlib.h>
	#include <lua/lualib.h>
}
#include <lua/LuaBridge.h>

#include "Blocks/BlockShield.h"
#include "Blocks/BlockWeapon.h"
#include "Blocks/BlockEngine.h"


class Ship;


struct ShipInfoForLUA
{
	float x;
	float y;
	float z;

	int team;
};

struct BlockInfoForLUA
{
	float x;
	float y;
	float z;
};


class ShipController
{
	friend class ShipFactory;

public:
	ShipController(Ship* ship);
	~ShipController();

	static float GetTime           (lua_State* luaThread);
	static void CatchLuaHook       (lua_State* luaThread, lua_Debug* luaDebug);
	static void SwitchShield       (const std::string& blockName, BlockShieldCommand command, lua_State* luaThread);
	static void EnableShield       (const std::string& blockName, lua_State* luaThread);
	static void DisableShield      (const std::string& blockName, lua_State* luaThread);
	static bool IsDirectionAllowed (const std::string& blockName, double xDir, double yDir, double zDir, lua_State* luaThread);
	static void Shoot              (const std::string& blockName, double xBulletDir, double yBulletDir, double zBulletDir, lua_State* luaThread);
	static void Gas                (const std::string& blockName, double xDir, double yDir, double zDir, int power, lua_State* luaThread);
	
	static ShipInfoForLUA GetShipInfo(int shipID, lua_State* luaThread);
	static std::vector<int> GetBlocksByShipID(int shipID, lua_State* luaThread);
	static BlockInfoForLUA GetBlockInfo(int shipID, int blockID, lua_State* luaThread);

	void Run();

private:
	static Block* FindBlock(const std::string& blockName, BlockType blockType, Ship* ship);

	static std::map<lua_State*, Ship*> shipsDataBase_;

	Ship* ship_;
	lua_State* luaState_;
	lua_State* luaThread_;
	bool isLuaScriptNormal_;
};


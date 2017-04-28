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

#define INSTRUCTION_LIMIT 1000


class Ship;

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

	void Run();

private:
	static std::vector<Block*>::iterator FindBlock(const std::string& blockName, BlockType blockType, Ship* ship);

	static std::map<lua_State*, Ship*> shipsDataBase_;

	Ship* ship_;
	lua_State* luaState_;
	lua_State* luaThread_;
	bool isLuaScriptNormal_;
};


#pragma once
#include <map>

extern "C"
{
	#include <lua/lua.h>
	#include <lua/lauxlib.h>
	#include <lua/lualib.h>
}
#include <lua/LuaBridge.h>

#define INSTRUCTION_LIMIT 30


class Ship;

class ShipController
{
	friend class ShipFactory;

public:
	ShipController(Ship* ship);
	~ShipController();

	static void CatchLuaHook(lua_State* luaThread, lua_Debug* luaDebug);
	static void SwitchShield(const std::string& blockName, const bool mode, const float time, lua_State* luaThread);

	void Run();

private:
	static std::map<lua_State*, Ship*> shipsDataBase_;

	Ship* ship_;
	lua_State* luaState_;
	lua_State* luaThread_;
};


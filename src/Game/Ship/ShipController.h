#pragma once
#include <map>

extern "C"
{
	#include <lua/lua.h>
	#include <lua/lauxlib.h>
	#include <lua/lualib.h>
}
#include <lua/LuaBridge.h>


//class ShipFactory;
class Ship;

class ShipController
{
//	friend void ShipFactory::LoadController(Ship* ship);   // in this function access is needed
	friend class ShipFactory;   // TODO: think is it possible to remove it

public:
	ShipController(Ship* ship);
	~ShipController();

	static void SwitchShield(const std::string& blockName, const bool mode, const float time, lua_State* luaState);

private:
	static std::map<lua_State*, Ship*> shipsDataBase_; // maybe we should use unordered_map for speed ?

	Ship* ship_;
	lua_State* luaState_;
};


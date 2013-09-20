#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <stdexcept>


// a lightweight wrapper around lua_State; mostly meant to handle releasing the resources once not needed anymore
class LuaState
{
public:
	LuaState() : state(nullptr) { }

	~LuaState() 
	{
		lua_close(state);
	}

	void Open()
	{
		state = lua_open();
		luabind::open(state);
	}

	void LoadScriptFile(std::string fileName)
	{
		if (state == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}
		luaL_dofile(state, fileName.c_str());
	}

	void OpenLuaLibrary(lua_CFunction f, std::string libraryName)
	{
		if (state == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		lua_pushcfunction(state, f);
		lua_pushstring(state, LUA_IOLIBNAME);
		lua_call(state, 1, 0);
	}


	lua_State *State() { 
		if (state == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}
		return state; 
	}
	
private:
	lua_State *state;
};


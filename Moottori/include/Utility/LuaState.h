#pragma once

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <stdexcept>

// variadic template would be better but visual studio compiler support for them is limited
#define LUA_CALL_FUNCTION(return_type, state, name, ...) luabind::call_function<return_type>((state), (name), __VA_ARGS__)


// a lightweight wrapper around lua_State; mostly meant to handle releasing the resources once not needed anymore
class LuaState
{
public:
	LuaState() : mState(nullptr), mScriptLoaded(false) { }

	~LuaState() 
	{
		if (mState != nullptr)
		{
			lua_close(mState);
		}
	}

	void Open()
	{
		mState = lua_open();
		luabind::open(mState);
	}

	void LoadScriptFile(std::string fileName)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}
		luaL_dofile(mState, fileName.c_str());
		mScriptLoaded = true;
	}

	void OpenLuaLibrary(lua_CFunction f, std::string libraryName)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		lua_pushcfunction(mState, f);
		lua_pushstring(mState, LUA_IOLIBNAME);
		lua_call(mState, 1, 0);
	}

	template<typename ...Args>
	void CallFunction(std::string name, Args&& ...args)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		if (!FunctionExists(name))
		{
			return;
		}

		luabind::call_function<void>(mState, 
			name.c_str(), 
			std::forward<Args>(args)...
			);
	}


	lua_State *State() { 
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}
		return mState; 
	}

	bool ScriptLoaded() 
	{
		return mScriptLoaded;
	}

	bool FunctionExists(std::string name)
	{
		if (!ScriptLoaded())
		{		
			return false;
		}

		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		luabind::object g = luabind::globals(mState);
		luabind::object fun = g[name.c_str()];
		if (fun.is_valid()) {
			return luabind::type(fun)== LUA_TFUNCTION;
		}
		return false;
	}

private:
	lua_State *mState;
	bool mScriptLoaded;
};


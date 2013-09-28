#include "Utility/LuaState.h"



bool LuaState::FunctionExists( std::string name )
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

bool LuaState::ScriptLoaded()
{
	return mScriptLoaded;
}

void LuaState::CallFunction( std::string name )
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}

	if (!FunctionExists(name))
	{
		throw std::runtime_error("Attempting to call script function \"" + name + "\" that does not exist!");
	}

	luabind::call_function<void>(mState, 
		name.c_str());
}

void LuaState::OpenAllLuaLibraries()
{
	luaL_openlibs(mState);
}

void LuaState::OpenLuaLibrary( lua_CFunction f, std::string libraryName )
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}

	lua_pushcfunction(mState, f);
	lua_pushstring(mState, libraryName.c_str());
	lua_call(mState, 1, 0);
}

void LuaState::LoadScriptFile( std::string fileName )
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}
	luaL_dofile(mState, fileName.c_str());
	mScriptLoaded = true;
}

LuaState::~LuaState()
{
	if (mState != nullptr)
	{
		lua_close(mState);
	}
}

void LuaState::Open()
{
	mState = lua_open();
	luabind::open(mState);
}

LuaState::LuaState() : mState(nullptr), mScriptLoaded(false)
{

}

lua_State * LuaState::State()
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}
	return mState;
}

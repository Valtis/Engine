#pragma once

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <stdexcept>

#include "Utility/LoggerManager.h"

// a lightweight wrapper around lua_State; mostly meant to handle releasing the resources once not needed anymore
class LuaState
{
public:
	LuaState();

	~LuaState();

	void Open();

	void LoadScriptFile(std::string fileName);

	void OpenLuaLibrary(lua_CFunction f, std::string libraryName);

	void OpenAllLuaLibraries();


	// calling the template version without parameters causes internal compiler error on vs 2012
	template <typename T>
	T CallFunction(std::string name)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		if (!FunctionExists(name))
		{
			throw std::runtime_error("Attempting to call script function \"" + name + "\" that does not exist!");
		}

		try
		{
			return luabind::call_function<T>(mState, name.c_str());
		}
		catch ( std::exception &e )
		{
			LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Error, GetFunctionCallErrorMessage);
			throw;
		}

	}

	void CallFunction(std::string name);

	template<typename ...Args>
	void CallFunction(std::string name, Args&& ...args)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		if (!FunctionExists(name))
		{
			throw std::runtime_error("Attempting to call script function \"" + name + "\" that does not exist!");
		}

		try {
			luabind::call_function<void>(mState, name.c_str(),  std::forward<Args>(args)...);
		}
		catch ( std::exception &e )
		{
			LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Error, GetFunctionCallErrorMessage);
			throw;
		}

	}

	template<typename T, typename ...Args>
	T CallFunction(std::string name, Args&& ...args)
	{
		if (mState == nullptr)
		{
			throw std::logic_error("lua_State was not opened before attempting to use one!");
		}

		if (!FunctionExists(name))
		{
			throw std::runtime_error("Attempting to call script function \"" + name + "\" that does not exist!");
		}
		
		try
		{
			return luabind::call_function<T>(mState, name.c_str(), std::forward<Args>(args)...);
		}
		catch ( std::exception &e )
		{
			LoggerManager::Instance().GetLog(SCRIPT_LOG).AddLine(LogLevel::Error, GetFunctionCallErrorMessage);
			throw;
		}

	}



	lua_State *State();

	bool ScriptLoaded();

	bool FunctionExists(std::string name);

private:
	lua_State *mState;
	bool mScriptLoaded;
	std::vector<std::string> mAttachedScriptFiles;
	std::string GetFunctionCallErrorMessage();
};


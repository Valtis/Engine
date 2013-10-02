#include "Utility/LuaState.h"
#include "Script/ScriptInterface.h"

LuaState::LuaState() : mState(nullptr), mScriptLoaded(false)
{

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

void LuaState::LoadScriptFile( std::string fileName )
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}
	luaL_dofile(mState, fileName.c_str());

	mAttachedScriptFiles.push_back(fileName);
	mScriptLoaded = true;
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


	try {
		luabind::call_function<void>(mState, name.c_str());
	} 
	catch ( std::exception &e )
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Error, GetFunctionCallErrorMessage(name, e.what()));
		throw;
	}


}


lua_State * LuaState::State()
{
	if (mState == nullptr)
	{
		throw std::logic_error("lua_State was not opened before attempting to use one!");
	}
	return mState;
}

std::string LuaState::GetFunctionCallErrorMessage(std::string name, std::string exceptionMessage)
{

	std::string topStack = lua_tostring(mState, -1);
	std::string errorMsg = "Caught an exception when calling script function " + name + " (error: " + topStack + ")";

	if (mAttachedScriptFiles.size() > 0)
	{
		errorMsg += "\n\tAttached script files:";
	}

	for (auto file : mAttachedScriptFiles)
	{
		errorMsg += "\n\t" + file;
	}

	return errorMsg;
}

void LuaState::RegisterScriptEngineInterface( std::unique_ptr<ScriptInterface> interface )
{
	mInterface = std::move(interface);
	mInterface->RegisterLuaState(this);
	mInterface->RegisterMethods();

}
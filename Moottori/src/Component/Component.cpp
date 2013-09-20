#include "Component/Component.h"

Component::Component() : mEventHandler(nullptr)
{

}

Component::~Component()
{

}

void Component::AttachScript(std::string scriptFile)
{
	mLuaState.Open();
	mLuaState.LoadScriptFile(scriptFile);
	mLuaState.OpenLuaLibrary(luaopen_io, LUA_IOLIBNAME); // DEBUG CODE 
	
	OnAttachingScript();
}


void Component::Update(double ticksPassed)
{
	if (mLuaState.FunctionExists("OnUpdate"))
	{
		luabind::call_function<void>(mLuaState.State(), "OnUpdate"/*,ticksPassed*/);
	}
}
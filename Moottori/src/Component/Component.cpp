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
	mLuaState.OpenLuaLibrary(luaopen_io, LUA_IOLIBNAME);
	mLuaState.OpenLuaLibrary(luaopen_math, LUA_MATHLIBNAME);  
	

	
	luabind::module(mLuaState.State()) [
		luabind::class_<Component>("Component")
			.def("RegisterForEvents", &Component::RegisterForEvents)
	];

	luabind::globals(mLuaState.State())["component"] = this;	
	
	OnAttachingScript();
}


void Component::Update(double ticksPassed)
{
	if (mLuaState.FunctionExists("OnUpdate"))
	{
		luabind::call_function<void>(mLuaState.State(), "OnUpdate", ticksPassed);
	}
}
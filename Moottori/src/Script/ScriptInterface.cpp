#include "Script/ScriptInterface.h"



void ScriptInterface::RegisterLuaState(LuaState *state)
{
	mLuaState = state;
}

void ScriptInterface::RegisterEntityEventHandler(EventHandler *handler)
{
	mEntityEvents.Initialize(handler);
}

void ScriptInterface::RegisterMethods()
{
	mEntityEvents.RegisterFunctions(mLuaState);
	mEngineScriptInterface.RegisterFunctions(mLuaState);
}

void ScriptInterface::RegisterUI(UI *ui)
{
	mEngineScriptInterface.RegisterUI(ui);
}

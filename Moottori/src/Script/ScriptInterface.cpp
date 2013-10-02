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
	mEngineEvents.RegisterFunctions(mLuaState);
}

void ScriptInterface::RegisterUI(UI *ui)
{
	mEngineEvents.RegisterUI(ui);
}

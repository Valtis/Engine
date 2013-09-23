#include "Component/Component.h"
#include "Event/EventScriptCaller.h"
#include "Event/Event.h"
#include "Event/EventHandler.h"


Component::Component() : mEventSender()
{

}

Component::~Component()
{

}

void Component::AttachScript(std::string scriptFile)
{
	mLuaState.Open();
	mLuaState.LoadScriptFile(scriptFile);
	mLuaState.OpenAllLuaLibraries();

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

void Component::HandleEvent(Event *event)
{
	EventScriptCaller caller(mLuaState);
	event->AcceptVisitor(&caller);
}

void Component::RegisterForEvents(EventType type)
{
	mEventHandler->RegisterCallback(type, [&](Event *event) { this->HandleEvent(event); });
}

void Component::RegisterEventHandler(EventHandler *handler)
{
	mEventHandler = handler;
	if (mLuaState.ScriptLoaded())
	{
		mEventSender.Init(mEventHandler, &mLuaState);
	}

	if (mLuaState.FunctionExists("OnRegisterForEvents"))
	{
		
		mLuaState.CallFunction("OnRegisterForEvents");
	}	
}
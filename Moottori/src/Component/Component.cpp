#include "Component/Component.h"
#include "Event/EventActionExecutor.h"
#include "Event/Event.h"
#include "Event/EventHandler.h"
#include "Event/EventSender.h"
#include "Script/ScriptInterface.h"



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


void Component::RegisterForEvents(EventType type)
{
	mEventHandler->RegisterCallback(type, [&](Event *event) { this->HandleEvent(event); });
}

void Component::HandleEvent(Event *event)
{
	EventActionExecutor caller(mLuaState);
	event->AcceptVisitor(&caller);
}


void Component::RegisterEventHandler(EventHandler *handler)
{
	mEventHandler = handler;
	std::unique_ptr<ScriptInterface> interface(new ScriptInterface);
	interface->RegisterEntityEventHandler(handler);
	mLuaState.RegisterScriptEngineInterface(std::move(interface));
	if (mLuaState.ScriptLoaded())
	{
		luabind::module(mLuaState.State()) [
			luabind::class_<EventHandler>("EventHandler")
				.def("GetID", &EventHandler::GetID)
		];
		luabind::globals(mLuaState.State())["entity"] = mEventHandler;	
	}

	OnRegisteringEventHandler(handler);

	if (mLuaState.FunctionExists("OnRegisterForEvents"))
	{
		mLuaState.CallFunction("OnRegisterForEvents");
	}	

}


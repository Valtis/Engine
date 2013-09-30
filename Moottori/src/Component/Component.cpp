#include "Component/Component.h"
#include "Event/EventScriptCaller.h"
#include "Event/EventSender.h"
#include "Event/Event.h"
#include "Event/EventHandler.h"


// THIS IS HERE SIMPLY BECAUSE IT'S GETTING LATE WHEN I'M WRITING THIS AND I DON'T HAVE THE TIME TO CREATE PROPER CLASS FOR THIS
// todo: create some sort of service class so that components can create emitters, etc etc etc
#include <SDL.h>
#include "Graphics/Particle/Emitter.h"
#include "Graphics/Renderer/Renderer.h"
void Component::AddEmitter(int x, int y, int numberOfParticles, double lifeTime, double maxVelocity)
{
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = 500;
	location.h = 500;
	std::unique_ptr<Emitter> emitter(new Emitter(numberOfParticles, location, lifeTime, maxVelocity));
	Renderer::Instance().AddEmitter(std::move(emitter));
}

Component::Component() : mEventHandler(nullptr), mEventSender(new EventSender)
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
			.def("TERRIBLE_DEBUG_HACK_CreateParticleEmitter", &Component::AddEmitter)
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
	EventScriptCaller caller(mLuaState);
	event->AcceptVisitor(&caller);
}


void Component::RegisterEventHandler(EventHandler *handler)
{
	mEventHandler = handler;
	if (mLuaState.ScriptLoaded())
	{
		luabind::module(mLuaState.State()) [
			luabind::class_<EventHandler>("EventHandler")
				.def("GetID", &EventHandler::GetID)
		];
		luabind::globals(mLuaState.State())["entity"] = mEventHandler;	
		mEventSender->Init(mEventHandler, &mLuaState);
	}

	OnRegisteringEventHandler(handler);

	if (mLuaState.FunctionExists("OnRegisterForEvents"))
	{
		
		mLuaState.CallFunction("OnRegisterForEvents");
	}	

}


#include "Component/FactionComponent.h"
#include "Event/QueryFactionEvent.h"
#include "Event/EventHandler.h"
#include <SDL_assert.h>

FactionComponent::FactionComponent( int faction ) : mFaction(faction)
{

}

void FactionComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<FactionComponent>("FactionComponent")
			.def_readwrite("faction", &FactionComponent::mFaction)
	];

	luabind::globals(mLuaState.State())["faction_component"] = this;
}

void FactionComponent::OnRegisteringEventHandler(EventHandler *handler)
{
	handler->RegisterCallback(EventType::QueryFaction, [&](Event *event) { this->HandleFactionQuery(event); });
}

void FactionComponent::HandleFactionQuery(Event *event)
{
	auto factionQuery = dynamic_cast<QueryFactionEvent *>(event);
	SDL_assert(event != nullptr);

	factionQuery->SetFaction(mFaction);
	factionQuery->WasHandled(true);
}
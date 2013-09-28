#include "Component/LocationComponent.h"
#include <SDL_assert.h>
#include <cmath>

#include "Event/EventHandler.h"
#include "Event/QueryLocationEvent.h"
#include "Event/QueryDirectionEvent.h"


void LocationComponent::OnAttachingScript()
{
	luabind::module(mLuaState.State()) [
		luabind::class_<LocationComponent>("LocationComponent")
			.def_readwrite("x", &LocationComponent::mX)
			.def_readwrite("y", &LocationComponent::mY)
			.def_readwrite("rotation", &LocationComponent::mRotation)
	];

	luabind::globals(mLuaState.State())["location_component"] = this;
}

void LocationComponent::OnRegisteringEventHandler()
{
	GetEventHandler().RegisterCallback(EventType::QueryLocation, [&](Event *e) { this->HandleLocationQuery(e); } );
	GetEventHandler().RegisterCallback(EventType::QueryDirection, [&](Event *e) { this->HandleDirectionQuery(e); } );
}

void LocationComponent::HandleLocationQuery(Event *e)
{
	auto locationQuery = dynamic_cast<QueryLocationEvent *>(e);
	SDL_assert(locationQuery != nullptr);

	locationQuery->SetX(mX);
	locationQuery->SetY(mY);
	locationQuery->WasHandled(true);
}

void LocationComponent::HandleDirectionQuery(Event *e)
{
	auto directionQuery = dynamic_cast<QueryDirectionEvent *>(e);
	SDL_assert(directionQuery != nullptr);

	directionQuery->SetDirection(mRotation);
	directionQuery->WasHandled(true);
}
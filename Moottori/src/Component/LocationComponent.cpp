#include "Component/LocationComponent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include <SDL_assert.h>
#include <cmath>
void LocationComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeLocation, [&](Event *event) { this->HandleLocationChangeEvents(event); } );
	GetEventHandler().RegisterCallback(EventType::QueryDirection, [&](Event *event) { this->HandleDirectionQueryEvent(event); } );
}

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

void LocationComponent::HandleLocationChangeEvents(Event *event) 
{
	auto locationEvent = dynamic_cast<ChangeLocationEvent *>(event);
	SDL_assert(locationEvent != nullptr);
	
	if (mLuaState.FunctionExists("OnLocationChangeEvent"))
	{

		luabind::call_function<void>(mLuaState.State(),
			"OnLocationChangeEvent",
			locationEvent->GetXChange(),
			locationEvent->GetYChange(),
			locationEvent->GetRotationChange());
	}
}

// this probably doesn't need to be scriptable as it's essentially just a getter
void LocationComponent::HandleDirectionQueryEvent(Event *event)
{
	auto queryEvent = dynamic_cast<QueryDirectionEvent *>(event);
	SDL_assert(queryEvent != nullptr);
	queryEvent->SetDirection(mRotation);
	queryEvent->WasHandled(true);
}
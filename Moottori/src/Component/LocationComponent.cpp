#include "Component/LocationComponent.h"
#include "Event/ChangeLocationEvent.h"
#include "Event/QueryDirectionEvent.h"
#include "Event/BoundaryCollisionEvent.h"

#include <SDL_assert.h>
#include <cmath>
void LocationComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeLocation, [&](Event *event) { this->HandleLocationChangeEvent(event); } );
	GetEventHandler().RegisterCallback(EventType::QueryDirection, [&](Event *event) { this->HandleDirectionQueryEvent(event); } );
	GetEventHandler().RegisterCallback(EventType::BoundaryCollision, [&](Event *event) { this->HandleBoundaryCollisionEvent(event); } );
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

void LocationComponent::HandleLocationChangeEvent(Event *event) 
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


void LocationComponent::HandleBoundaryCollisionEvent(Event *event) 
{
	auto collisionEvent = dynamic_cast<BoundaryCollisionEvent *>(event);
	SDL_assert(collisionEvent != nullptr);
	
	if (mLuaState.FunctionExists("OnBoundaryCollisionEvent"))
	{

		luabind::call_function<void>(mLuaState.State(),
			"OnBoundaryCollisionEvent",
			static_cast<int>(collisionEvent->GetCollisionDirection()),
			collisionEvent->GetMinX(),
			collisionEvent->GetMinY(),
			collisionEvent->GetMaxX(),
			collisionEvent->GetMaxY());
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
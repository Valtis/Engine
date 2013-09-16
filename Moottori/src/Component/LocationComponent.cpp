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

void LocationComponent::HandleLocationChangeEvents(Event *event) 
{
	auto locationEvent = dynamic_cast<ChangeLocationEvent *>(event);
	SDL_assert(locationEvent != nullptr);

	mX += locationEvent->GetXChange();
	mY += locationEvent->GetYChange();
	mRotation += locationEvent->GetRotationChange();
}


void LocationComponent::HandleDirectionQueryEvent(Event *event)
{
	auto queryEvent = dynamic_cast<QueryDirectionEvent *>(event);
	SDL_assert(queryEvent != nullptr);
	queryEvent->SetDirection(mRotation);
	queryEvent->WasHandled(true);
}
#include "Component/LocationComponent.h"
#include "Event/ChangeLocationEvent.h"
#include <SDL_assert.h>
#include <cmath>
void LocationComponent::OnEventHandlerRegistration()
{
	GetEventHandler().RegisterCallback(EventType::ChangeLocation, [&](Event *event) { this->HandleLocationChangeEvents(event); } );
}

void LocationComponent::HandleLocationChangeEvents(Event *event) 
{
	ChangeLocationEvent *locationEvent = dynamic_cast<ChangeLocationEvent *>(event);
	SDL_assert(locationEvent != nullptr);

	mX += locationEvent->GetXChange();
	mY += locationEvent->GetYChange();
	mRotation += locationEvent->GetRotationChange();

	// experimenting here
	/*int velocity = locationEvent->GetYChange();
	double angle = mRotation*3.1415926535/180.0;
	mX += sin(angle)*velocity;
	mY += -cos(angle)*velocity;*/

}
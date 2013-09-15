#include "Component/InputComponent.h"
#include "UI/UI.h"
#include "Utility/Defines.h"
#include "Event/UIEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include <memory>

InputComponent::InputComponent(UI &ui)
{
	ui.RegisterInputHandler([&](Event *event) { return this->InputHandler(event); }, INPUT_PRIORITY_NORMAL);
}


InputComponent::~InputComponent()
{

}

bool InputComponent::InputHandler(Event *event)
{
	UIEvent *uiEvent = dynamic_cast<UIEvent *>(event);

	if (uiEvent == nullptr)
	{
		return false;
	}
	Direction accelerationDirection = Direction::None;
	Direction rotationDirection = Direction::None;
	switch (uiEvent->GetUIEventType())
	{
		case UIEventType::MoveUp:
			accelerationDirection = Direction::Up;

			break;
		case UIEventType::MoveDown:
			accelerationDirection = Direction::Bottom;
			break;
		case UIEventType::MoveLeft:
			accelerationDirection = Direction::Left;
			break;
		case UIEventType::MoveRight:
			accelerationDirection = Direction::Right;
			break;

		case UIEventType::RotateLeft:
			rotationDirection = Direction::Left;
			break;
		case UIEventType::RotateRight:
			rotationDirection = Direction::Right;
			break;

		default:
			return false;
	}

	GetEventHandler().AddEvent(std::unique_ptr<ChangeAccelerationEvent>(new ChangeAccelerationEvent(accelerationDirection, rotationDirection, uiEvent->GetUIEventState())));

	return true;
}
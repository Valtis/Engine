#include "Component/InputComponent.h"
#include "UI/UI.h"
#include "Utility/Defines.h"
#include "Event/UIEvent.h"
#include "Event/ChangeVelocityEvent.h"

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

	switch (uiEvent->GetUIEventType())
	{
		case UIEventType::MoveUp:
			GetEventHandler().AddEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(Direction::Up)));
			break;
		case UIEventType::MoveDown:
			GetEventHandler().AddEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(Direction::Bottom)));
			break;
		case UIEventType::MoveLeft:
			GetEventHandler().AddEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(Direction::Left)));
			break;
		case UIEventType::MoveRight:
			GetEventHandler().AddEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(Direction::Right)));
			break;

		default:
			return false;
	}

	return true;
}
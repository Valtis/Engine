#include "Component/InputComponent.h"
#include "UI/UI.h"
#include "Utility/Defines.h"
#include "Event/UIEvent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeAnimationStateEvent.h"
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

	if (mLuaState.FunctionExists("OnInputEvent"))
	{
		return luabind::call_function<bool>(mLuaState.State(), 
			"OnInputEvent", 
			static_cast<int>(uiEvent->GetUIEventType()), 
			static_cast<int>(uiEvent->GetUIEventState())
			);
	}

	return false;
}
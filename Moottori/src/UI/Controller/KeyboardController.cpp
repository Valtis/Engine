#include "UI/Controller/KeyboardController.h"
#include <cmath>
// todo: Move key bindings to a file instead of hardcoding them here
void KeyboardController::LoadKeyBindings()
{
	mKeyBindings[SDL_SCANCODE_Q] = UIEventType::RotateLeft;
	mKeyBindings[SDL_SCANCODE_E] = UIEventType::RotateRight;

	mKeyBindings[SDL_SCANCODE_W] = UIEventType::MoveUp;
	mKeyBindings[SDL_SCANCODE_KP_8] = UIEventType::MoveUp;

	mKeyBindings[SDL_SCANCODE_A] = UIEventType::MoveLeft;
	mKeyBindings[SDL_SCANCODE_KP_4] = UIEventType::MoveLeft;

	mKeyBindings[SDL_SCANCODE_D] = UIEventType::MoveRight;
	mKeyBindings[SDL_SCANCODE_KP_6] = UIEventType::MoveRight;

	mKeyBindings[SDL_SCANCODE_S] = UIEventType::MoveDown;
	mKeyBindings[SDL_SCANCODE_KP_2] = UIEventType::MoveDown;

	mKeyBindings[SDL_SCANCODE_KP_MINUS] = UIEventType::MoveBackwards;
	mKeyBindings[SDL_SCANCODE_KP_PLUS] = UIEventType::MoveForward;
}



std::vector<std::pair<UIEventType, UIEventState>> KeyboardController::HandleInput()
{

	std::vector<std::pair<UIEventType, UIEventState>> events;
	SDL_PumpEvents();

	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	SDL_assert(state != nullptr);
	
	for (auto keyBind : mKeyBindings)
	{
		if (state[keyBind.first] == 1)
		{
			mKeyIsPressed[keyBind.first] = 1;
			events.push_back(std::make_pair(keyBind.second, UIEventState::Start));
		}
		else 
		{
			if (mKeyIsPressed[keyBind.first] == 1)
			{
				mKeyIsPressed[keyBind.first] = 0;
				events.push_back(std::make_pair(keyBind.second, UIEventState::Stop));
			}
		}

	}
	
	

	return events;

}
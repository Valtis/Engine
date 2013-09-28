#include "UI/Controller/KeyboardController.h"
#include <cmath>

// todo: Move key bindings to a file instead of hardcoding them here
void KeyboardController::LoadKeyBindings()
{
	mKeyBindings[SDL_SCANCODE_A] = UIEventType::KEY_A;
	mKeyBindings[SDL_SCANCODE_B] = UIEventType::KEY_B;
	mKeyBindings[SDL_SCANCODE_C] = UIEventType::KEY_C;
	mKeyBindings[SDL_SCANCODE_D] = UIEventType::KEY_D;
	mKeyBindings[SDL_SCANCODE_E] = UIEventType::KEY_E;
	mKeyBindings[SDL_SCANCODE_F] = UIEventType::KEY_F;
	mKeyBindings[SDL_SCANCODE_G] = UIEventType::KEY_G;
	mKeyBindings[SDL_SCANCODE_H] = UIEventType::KEY_H;
	mKeyBindings[SDL_SCANCODE_I] = UIEventType::KEY_I;
	mKeyBindings[SDL_SCANCODE_J] = UIEventType::KEY_J;
	mKeyBindings[SDL_SCANCODE_K] = UIEventType::KEY_K;
	mKeyBindings[SDL_SCANCODE_L] = UIEventType::KEY_L;
	mKeyBindings[SDL_SCANCODE_M] = UIEventType::KEY_M;
	mKeyBindings[SDL_SCANCODE_N] = UIEventType::KEY_N;
	mKeyBindings[SDL_SCANCODE_O] = UIEventType::KEY_O;
	mKeyBindings[SDL_SCANCODE_P] = UIEventType::KEY_P;
	mKeyBindings[SDL_SCANCODE_Q] = UIEventType::KEY_Q;
	mKeyBindings[SDL_SCANCODE_R] = UIEventType::KEY_R;
	mKeyBindings[SDL_SCANCODE_S] = UIEventType::KEY_S;
	mKeyBindings[SDL_SCANCODE_T] = UIEventType::KEY_T;
	mKeyBindings[SDL_SCANCODE_U] = UIEventType::KEY_U;
	mKeyBindings[SDL_SCANCODE_V] = UIEventType::KEY_V;
	mKeyBindings[SDL_SCANCODE_W] = UIEventType::KEY_W;
	mKeyBindings[SDL_SCANCODE_X] = UIEventType::KEY_X;
	mKeyBindings[SDL_SCANCODE_Y] = UIEventType::KEY_Y;
	mKeyBindings[SDL_SCANCODE_Z] = UIEventType::KEY_Z;
	mKeyBindings[SDL_SCANCODE_0] = UIEventType::KEY_0;
	mKeyBindings[SDL_SCANCODE_1] = UIEventType::KEY_1;
	mKeyBindings[SDL_SCANCODE_2] = UIEventType::KEY_2;
	mKeyBindings[SDL_SCANCODE_3] = UIEventType::KEY_3;
	mKeyBindings[SDL_SCANCODE_4] = UIEventType::KEY_4;
	mKeyBindings[SDL_SCANCODE_5] = UIEventType::KEY_5;
	mKeyBindings[SDL_SCANCODE_6] = UIEventType::KEY_6;
	mKeyBindings[SDL_SCANCODE_7] = UIEventType::KEY_7;
	mKeyBindings[SDL_SCANCODE_8] = UIEventType::KEY_8;
	mKeyBindings[SDL_SCANCODE_9] = UIEventType::KEY_9;
	mKeyBindings[SDL_SCANCODE_KP_0] = UIEventType::KEY_NUMPAD_0;
	mKeyBindings[SDL_SCANCODE_KP_1] = UIEventType::KEY_NUMPAD_1;
	mKeyBindings[SDL_SCANCODE_KP_2] = UIEventType::KEY_NUMPAD_2;
	mKeyBindings[SDL_SCANCODE_KP_3] = UIEventType::KEY_NUMPAD_3;
	mKeyBindings[SDL_SCANCODE_KP_4] = UIEventType::KEY_NUMPAD_4;
	mKeyBindings[SDL_SCANCODE_KP_5] = UIEventType::KEY_NUMPAD_5;
	mKeyBindings[SDL_SCANCODE_KP_6] = UIEventType::KEY_NUMPAD_6;
	mKeyBindings[SDL_SCANCODE_KP_7] = UIEventType::KEY_NUMPAD_7;
	mKeyBindings[SDL_SCANCODE_KP_8] = UIEventType::KEY_NUMPAD_8;
	mKeyBindings[SDL_SCANCODE_KP_9] = UIEventType::KEY_NUMPAD_9;
	mKeyBindings[SDL_SCANCODE_KP_DIVIDE] = UIEventType::KEY_NUMPAD_DIV;
	mKeyBindings[SDL_SCANCODE_KP_MULTIPLY] = UIEventType::KEY_NUMPAD_MUL;
	mKeyBindings[SDL_SCANCODE_KP_MINUS] = UIEventType::KEY_NUMPAD_MINUS;
	mKeyBindings[SDL_SCANCODE_KP_PLUS] = UIEventType::KEY_NUMPAD_PLUS;
	mKeyBindings[SDL_SCANCODE_KP_ENTER] = UIEventType::KEY_NUMPAD_ENTER;
	mKeyBindings[SDL_SCANCODE_RETURN] = UIEventType::KEY_ENTER;
	mKeyBindings[SDL_SCANCODE_LCTRL] = UIEventType::KEY_LEFT_CONTROL;
	mKeyBindings[SDL_SCANCODE_LSHIFT] = UIEventType::KEY_LEFT_SHIFT;
	mKeyBindings[SDL_SCANCODE_LALT] = UIEventType::KEY_LEFT_ALT;
	mKeyBindings[SDL_SCANCODE_RCTRL] = UIEventType::KEY_RIGHT_CONTROL;
	mKeyBindings[SDL_SCANCODE_LSHIFT] = UIEventType::KEY_RIGHT_SHIFT;
	mKeyBindings[SDL_SCANCODE_RALT] = UIEventType::KEY_RIGHT_ALT;
	mKeyBindings[SDL_SCANCODE_UP] = UIEventType::KEY_UP;
	mKeyBindings[SDL_SCANCODE_DOWN] = UIEventType::KEY_DOWN;
	mKeyBindings[SDL_SCANCODE_LEFT] = UIEventType::KEY_LEFT;
	mKeyBindings[SDL_SCANCODE_RIGHT] = UIEventType::KEY_RIGHT;
	mKeyBindings[SDL_SCANCODE_SPACE] = UIEventType::KEY_SPACE;
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
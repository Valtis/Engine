#include <fstream>

#include "UI/Controller/KeyboardController.h"
#include "Utility/StringUtility.h"

void KeyboardController::LoadKeyBindings()
{
	std::ifstream datafile("data/input/keybindings.dat");
	if (!datafile.is_open())
	{
		return;
	}

	std::string line;

	while (std::getline(datafile, line))
	{
		ParseLine(line);
	}
}

void KeyboardController::ParseLine( std::string line )
{
	std::vector<std::string> tokens = Utility::Tokenize(line, " ");
	if (tokens.size() < 2)
	{
		return;
	}

	SDL_Scancode code = SDL_GetScancodeFromName(tokens[0].c_str());

	if (code == SDL_SCANCODE_UNKNOWN)
	{
		return; 
	}

	mKeyBindings[code] = std::stoi(tokens[1]);
}


std::vector<std::pair<int, UIEventState>> KeyboardController::HandleInput()
{

	std::vector<std::pair<int, UIEventState>> events;
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


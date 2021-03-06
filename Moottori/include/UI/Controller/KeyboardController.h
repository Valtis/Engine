#pragma once
#include "UI/Controller/Controller.h"

#include <unordered_map>
#include "SDL.h"
class KeyboardController : public Controller
{
public:
	KeyboardController() { LoadKeyBindings(); }
	~KeyboardController() {} 
	std::vector<std::pair<int, UIEventState>> HandleInput() override;

#if !defined _MSC_VER || _MSC_VER >= 1800 
	KeyboardController(const KeyboardController &) = delete;
	KeyboardController &operator=(const KeyboardController &) = delete;
#else
private:
	KeyboardController(const KeyboardController &);
	KeyboardController &operator=(const KeyboardController &);
public:
#endif
	
private:

	void LoadKeyBindings();

	void ParseLine( std::string line );

	//std::unordered_map<SDL_Scancode, bool> mKeyIsPressed;
	//std::unordered_map<SDL_Scancode, int> mKeyBindings;

	std::unordered_map<int, bool> mKeyIsPressed;
	std::unordered_map<int, int> mKeyBindings;

};
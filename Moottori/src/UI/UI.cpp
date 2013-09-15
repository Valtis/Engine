#include "UI/UI.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Utility/Defines.h"
#include "Event/UIEvent.h"

#include <algorithm>

UI::UI() : MAX_NUMBER_OF_EVENTS_TO_PROCESS_PER_TICK(10)
{

}

UI::~UI()
{

}

void UI::Initialize(std::string title, std::string spritesheetpath,  int windowWidth, int windowHeight)
{
	Renderer::Instance().CreateWindow(title, windowWidth, windowHeight); 
	SpriteManager::Instance().Initialize(spritesheetpath);

	RegisterInputHandler([&](Event *event) { return this->EventHandler(event); }, INPUT_PRIORITY_MAX);
}

void UI::Draw()
{
	Renderer::Instance().Draw();
}

void UI::Update()
{
	SDL_Event event;
	for (int i = 0; i < MAX_NUMBER_OF_EVENTS_TO_PROCESS_PER_TICK; ++i)
	{
		if (SDL_PollEvent(&event) == 0)
		{
			return; // no events to handle
		}

		HandleEvent(event);
	}
}

void UI::HandleEvent(const SDL_Event &event)
{
	// I wonded if std::(unordered_)map would be better than switch/case

	switch (event.type)
	{
	case SDL_QUIT:
		NotifyInputHandlers(UIEventType::Quit, UIEventState::None);
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		HandleKeys(event.key.keysym.scancode, event.type);
		break;
	default:
		break;
	} 
}
// todo: move to controller-class instead of hardcoding here 
// todo: load keys from file instead of hardcoding
void UI::HandleKeys(SDL_Scancode code, Uint32 type)
{
	UIEventState state = UIEventState::None;
	UIEventType uiEvent = UIEventType::None;
	if (type == SDL_KEYDOWN)
	{
		state = UIEventState::Start;
	}
	else if (type == SDL_KEYUP)
	{
		state = UIEventState::Stop;
	}

	switch (code)
	{

	case SDL_SCANCODE_Q:
		uiEvent = UIEventType::RotateLeft;
		break;

	case SDL_SCANCODE_E:
		uiEvent = UIEventType::RotateRight;
		break;

	case SDL_SCANCODE_W:
	case SDL_SCANCODE_KP_8:
		uiEvent = UIEventType::MoveUp;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_KP_4:
		uiEvent = UIEventType::MoveLeft;
		break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_KP_6:
		uiEvent = UIEventType::MoveRight;
		break;
	case SDL_SCANCODE_S:
	case SDL_SCANCODE_KP_2:
		uiEvent = UIEventType::MoveDown;
		break;

	default:
		break;
	}

	if (uiEvent != UIEventType::None)
	{
		NotifyInputHandlers(uiEvent, state);
	}
}

void UI::RegisterInputHandler(InputHandler handler, int priority)
{
	mInputHandlers.push_back(std::make_pair(priority, handler));
	SortHandlers();
}

void UI::SortHandlers()
{
	SDL_assert(mInputHandlers.size() > 0);

	std::stable_sort(std::begin(mInputHandlers), std::end(mInputHandlers), [](InputHandlerNode firstNode, InputHandlerNode secondNode) 
	{
		return firstNode.first > secondNode.first;	
	}
	);


	SDL_assert(mInputHandlers.front().first >= mInputHandlers.back().first);
}


void UI::NotifyInputHandlers(UIEventType event, UIEventState state)
{
	std::unique_ptr<UIEvent> uiEvent(new UIEvent(event, state));
	for (auto &handler : mInputHandlers)
	{
		if (handler.second(uiEvent.get())) // returns true if event was handled
		{
			break;
		}
	}
}


// in the future will pass events to windows etc if necessary. Otherwise just 
bool UI::EventHandler(Event *event) 
{
	return false;
}
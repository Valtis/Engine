#include "UI/UI.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/SpriteManager.h"
#include "Utility/Defines.h"
#include "Event/EventFactory.h"

#include "UI/Controller/ControllerFactory.h"

#include <algorithm>

UI::UI() : mInputHandlers(), MAX_NUMBER_OF_EVENTS_TO_PROCESS_PER_TICK(10), mCamera(), mController(ControllerFactory::NewObject(ControllerType::Keyboard))
{

}

UI::~UI()
{

}

void UI::Initialize(std::string title, std::string spritesheetpath,  int windowWidth, int windowHeight)
{
	mScreenWidth = windowWidth;
	mScreenHeight = windowHeight;
	Renderer::Instance().CreateWindow(title, windowWidth, windowHeight); 
	SpriteManager::Instance().Initialize(spritesheetpath);

	RegisterInputHandler([&](Event *event) { return this->EventHandler(event); }, INPUT_PRIORITY_MAX);
}

void UI::Draw()
{
	Renderer::Instance().Draw(mCamera.get());
}


void UI::AttachCamera(std::unique_ptr<Camera> camera)
{
	mCamera = std::move(camera); 
	mCamera->SetScreenWidth(mScreenWidth);
	mCamera->SetScreenHeight(mScreenHeight);
}

void UI::Update()
{
	SDL_Event event;
	for (int i = 0; i < MAX_NUMBER_OF_EVENTS_TO_PROCESS_PER_TICK; ++i)
	{
		if (SDL_PollEvent(&event) == 0)
		{
			break; // no events to handle
		}

		HandleEvent(event);
	}

	std::vector<std::pair<UIEventType, UIEventState>> inputEvents = mController->HandleInput();

	for (auto &inputEvent : inputEvents)
	{
		NotifyInputHandlers(inputEvent.first, inputEvent.second);
	}
}

void UI::HandleEvent(const SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		NotifyInputHandlers(UIEventType::Quit, UIEventState::None);
		break;
	default:
		break;
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


void UI::NotifyInputHandlers( int type, UIEventState state )
{
	std::unique_ptr<Event> uiEvent(EventFactory::CreateUIEvent(event, state));
	for (auto &handler : mInputHandlers)
	{
		if (handler.second(uiEvent.get())) // returns true if event was handled
		{
			break;
		}
	}
}

bool UI::EventHandler(Event *event) 
{
	// windows handling code would come here - catch mouse events and handle them
	return false; // pass event forward
}
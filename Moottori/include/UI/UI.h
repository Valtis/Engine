#pragma once
#include <string>
#include <functional>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Utility/Enumerations.h"
#include "UI/Controller/Controller.h"
class Event;

class UI
{
public:
	UI();
	~UI();
#if !defined _MSC_VER || _MSC_VER >= 1800 
	UI(const UI &) = delete;
	UI &operator=(const UI &) = delete;
#else
private:
	UI(const UI &);
	UI &operator=(const UI &);
public:
#endif
	
	typedef std::function<bool(Event *event)> InputHandler;
	typedef std::pair<int, InputHandler> InputHandlerNode;

	void Initialize(std::string title, std::string spritesheetpath, int windowWidth, int windowHeight);
	void Draw();

	void Update();
	
	// basic idea: UI has list of handlers with priority. It offers input for each handler, starting with handler with highest priority. If handler doesn't handle the input, it offers it to next one
	void RegisterInputHandler(InputHandler, int priority);
private:
	void HandleEvent(const SDL_Event &event);

	void NotifyInputHandlers(int type, UIEventState state);
	void SortHandlers();
	bool EventHandler(Event *);

	std::vector<InputHandlerNode> mInputHandlers;


	const int MAX_NUMBER_OF_EVENTS_TO_PROCESS_PER_TICK;
	int mScreenWidth;
	int mScreenHeight;

	std::unique_ptr<Controller> mController;

};
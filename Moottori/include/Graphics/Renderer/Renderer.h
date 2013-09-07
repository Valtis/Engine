#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include <string>

#include "Utility/UniqueID.h"
class Renderer
{
public:

#if (_MSC_VER >= 1800)
	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;
#else
private:
	Renderer(const Renderer &);
	Renderer &operator=(const Renderer &);
public:
#endif

	virtual ~Renderer();

	static Renderer &Instance();
	static void Release();

	void CreateWindow(std::string title, int width, int height);

	void Draw();

protected:
private:
	static Renderer *mInstance;
	Renderer();

	std::vector<UniqueID> mDrawables;

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;

};

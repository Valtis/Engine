#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include <string>

#include "Graphics/Camera/Camera.h"
#include "Utility/UniqueID.h"
class Entity;
class Renderer
{
public:

#if !defined _MSC_VER || _MSC_VER >= 1800 
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

	SDL_Renderer *GetRenderingContext() { return mRenderer; }

	void CreateWindow(std::string title, int width, int height);
	
	void AddEntity(UniqueID id) { mDrawables.push_back(id); }
	void Draw(Camera *camera);

protected:
private:
	static Renderer *mInstance;
	Renderer();
	void ClearScreen();
	void DrawEntities();
	std::vector<Entity *> GetEntitiesForDrawing();
	bool CullEntity(Entity *e);
	void SortByDrawPriority(std::vector<Entity *> &drawList);
	void DrawEntity(Entity *e);

	std::vector<UniqueID> mDrawables;

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;

};

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
	
	void AddEntity(int id);
	void Draw(Camera *camera);

protected:
private:

	static Renderer *mInstance;
	Renderer();
	void ClearScreen();
	void DrawEntities(Camera *camera);
	std::vector<Entity *> GetEntitiesForDrawing(Camera *camera);
	bool CullEntity(Entity *e, Camera *camera);
	void SortByDrawPriority(std::vector<Entity *> &drawList);
	void DrawEntity(Entity *e, Camera *c);

	std::vector<int> mDrawables;
	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
};

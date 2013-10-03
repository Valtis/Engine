#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include <string>

#include "Graphics/Camera/Camera.h"


class Entity;
class Emitter; 
class Sprite;
class Particle;

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

	void UpdateEmitters(double ticks_passed);
	void AddEmitter(std::unique_ptr<Emitter> e);

protected:
private:

	static Renderer *mInstance;
	Renderer();
	void ClearScreen();
	void DrawEntities(Camera *camera);
	std::vector<Entity *> GetEntitiesForDrawing(Camera *camera);
	bool CullEntity(Entity *e, Camera *camera);
	bool IsOutsideCamera(int x, int y, int width, int height, Camera *camera);
	void SortByDrawPriority(std::vector<Entity *> &drawList);
	void DrawEntity(Entity *e, Camera *c);

	SDL_Texture *GetTextureForDrawing( Sprite * sprite, Camera * camera );

	Sprite *GetSprite( Entity * e );


	int GetCameraYOffset( Camera * camera );

	int GetCameraXOffset( Camera * camera );

	void DrawEmitters(Camera *camera);

	void DrawEmitter(Emitter *emitter, Camera * camera );

	void CalculateEmitterLocation(Emitter *emitter, SDL_Rect &emitterLocation, Camera * camera );

	void DrawEmitterParticle(Particle *particle, SDL_Rect emitterLocation );

	std::vector<int> mDrawables;
	std::vector<std::unique_ptr<Emitter>> mParticleEmitters;

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
};

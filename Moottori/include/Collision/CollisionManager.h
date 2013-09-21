#pragma once
#include <vector>
class Entity; 
class LocationComponent;
class GraphicsComponent;

class CollisionManager
{
public:
	CollisionManager() : mLevelWidth(0), mLevelHeight(0) {}

	void SetLevelWidth(int width) { mLevelWidth = width; }
	void SetLevelHeight(int height) { mLevelHeight = height; }

	void Update(double ticksPassed);
	void SetCollidabeEntities(std::vector<int> entities);

private:
	int GetCenterX(Entity *e, LocationComponent *location, GraphicsComponent *graphics);
	int GetCenterY(Entity *e, LocationComponent *location, GraphicsComponent *graphics);

	bool HasRightComponents(Entity *e);
	void CheckLevelBoundaryCollisions(Entity *e);

	std::vector<int> mCollidables;

	int mLevelWidth;
	int mLevelHeight;

};


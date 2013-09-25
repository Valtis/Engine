#pragma once
#include <vector>
#include "Utility/Enumerations.h"
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
	int GetCenterX(Entity *e);
	int GetCenterY(Entity *e);

	bool HasRightComponents(Entity *e);

	void CheckLevelBoundaryCollisions(Entity *e);

	void SendBoundaryCollisionEventToEntity( Entity * e, Direction direction );

	Direction FindCollisionEdge(Entity *e);

	void CheckEntityCollisions(Entity *e);

	void HandleEntityCollision( Entity * first, Entity * second );

	int CalculateDistance( Entity * first, Entity * second );

	std::vector<int> mCollidables;

	int mLevelWidth;
	int mLevelHeight;

};


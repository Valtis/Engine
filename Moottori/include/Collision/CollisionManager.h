#pragma once
#include <vector>
#include "Utility/Enumerations.h"
class Entity; 
class LocationComponent;
class GraphicsComponent;

class CollisionManager
{
public:
	
	void SetLevelWidth(int width) { mLevelWidth = width; }
	void SetLevelHeight(int height) { mLevelHeight = height; }

	void Update(double ticksPassed);
	void SetCollidabeEntities(std::vector<int> entities);

	void AddEntity( int i );

	static void Release();

	static CollisionManager &Instance();


private:
	CollisionManager() : mLevelWidth(0), mLevelHeight(0) {}

	int GetCenterX(Entity *e);
	int GetCenterY(Entity *e);

	bool HasRightComponents(int entityID);

	void CheckLevelBoundaryCollisions(Entity *e);

	void SendBoundaryCollisionEventToEntity( Entity * e, Direction direction );

	Direction FindCollisionEdge(Entity *e);

	void CheckEntityCollisions(Entity *e);

	void HandleEntityCollision( Entity * first, Entity * second );

	int CalculateDistance( Entity * first, Entity * second );

	std::vector<int> mCollidables;

	int mLevelWidth;
	int mLevelHeight;

	static CollisionManager *mInstance;

};


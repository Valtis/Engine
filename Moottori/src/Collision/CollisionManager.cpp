#include "Collision/CollisionManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"
#include "Graphics/SpriteManager.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/CollisionAreaComponent.h"

#include "Event/BoundaryCollisionEvent.h"

#include <SDL_assert.h>

bool CollisionManager::HasRightComponents(Entity *e)
{
	return (e != nullptr && e->GetComponent(ComponentType::Collision) != nullptr && e->GetComponent(ComponentType::Location) != nullptr);
}

void CollisionManager::SetCollidabeEntities(std::vector<int> entitites)
{
	mCollidables.clear();

	for (int i : entitites)
	{
		Entity *e = EntityManager::Instance().GetEntity(i);
		
		if (!HasRightComponents(e))
		{
			continue;
		}

		mCollidables.push_back(i);
	}
}

void CollisionManager::Update(double ticksPassed)
{
	for (int i : mCollidables)
	{
		Entity * e = EntityManager::Instance().GetEntity(i);
		CheckLevelBoundaryCollisions(e);
		// CheckEntityCollisions(e);
	}
}


int CollisionManager::GetCenterX(Entity *e, LocationComponent *location, GraphicsComponent *graphics)
{
	int x = location->GetX();
	if (graphics != nullptr)
	{
		x += SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().w/2;
	}

	return x;
}

int CollisionManager::GetCenterY(Entity *e, LocationComponent *location, GraphicsComponent *graphics)
{
	int y = location->GetY();
	if (graphics != nullptr)
	{
		y += SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().h/2;
	}

	return y;
}


void CollisionManager::CheckLevelBoundaryCollisions(Entity *e)
{
	auto location = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));
	auto collision = dynamic_cast<CollisionAreaComponent *>(e->GetComponent(ComponentType::Collision));
	auto graphics = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));

	SDL_assert(location != nullptr);
	SDL_assert(collision != nullptr);
	// graphicsComponent is optional, no assert required

	int centerX = GetCenterX(e, location, graphics);
	int centerY = GetCenterY(e, location, graphics);
	Direction direction = Direction::None;

	if (centerX - collision->GetCollisionRadius() < 0)
	{
		direction = Direction::Left;
	}
	else if (centerX + collision->GetCollisionRadius() > mLevelWidth)
	{
		direction = Direction::Right;
	}
	else if (centerY - collision->GetCollisionRadius() < 0)
	{
		direction = Direction::Top;
	}
	else if (centerY + collision->GetCollisionRadius() > mLevelHeight)
	{
		direction = Direction::Bottom;
	}
	
	if (direction != Direction::None)
	{

		int minX = collision->GetCollisionRadius(); 
		int minY = collision->GetCollisionRadius();
		if (graphics != nullptr)
		{
			minX -= SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().w/2;
			minY -= SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().h/2; 
		}

		int maxX = mLevelWidth - collision->GetCollisionRadius();
		int maxY = mLevelHeight - collision->GetCollisionRadius();
		e->ProcessEvent(std::unique_ptr<BoundaryCollisionEvent>(new BoundaryCollisionEvent(direction, minX, minY, maxX, maxY)));
	}
		


}
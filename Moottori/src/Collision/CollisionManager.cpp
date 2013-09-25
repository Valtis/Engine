#include "Collision/CollisionManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"
#include "Event/EventFactory.h"

#include "Graphics/SpriteManager.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/CollisionAreaComponent.h"


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
	for (auto iter = std::begin(mCollidables); iter != std::end(mCollidables); ++iter)
	{
		Entity * e = EntityManager::Instance().GetEntity(*iter);
		
		if (e == nullptr)
		{
			iter = mCollidables.erase(iter);
		}
		
		CheckLevelBoundaryCollisions(e);
		CheckEntityCollisions(e);
	}
}


int CollisionManager::GetCenterX(Entity *e)
{
	auto location = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));
	auto graphics = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
	SDL_assert(location != nullptr);
	int x = location->GetX();

	if (graphics != nullptr)
	{
		x += SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().w/2;
	}

	return x;
}

int CollisionManager::GetCenterY(Entity *e)
{
	auto location = dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));
	auto graphics = dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
	SDL_assert(location != nullptr);

	int y = location->GetY();
	if (graphics != nullptr)
	{
		y += SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().h/2;
	}

	return y;
}

Direction CollisionManager::FindCollisionEdge(Entity *e)
{
	Direction direction = Direction::None;
	int centerX = GetCenterX(e);
	int centerY = GetCenterY(e);

	auto collision = dynamic_cast<CollisionAreaComponent *>(e->GetComponent(ComponentType::Collision));
	
	SDL_assert(collision != nullptr);

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

	return direction;
}

void CollisionManager::SendBoundaryCollisionEventToEntity(Entity * e, Direction direction )
{
	auto collision = dynamic_cast<CollisionAreaComponent *>(e->GetComponent(ComponentType::Collision));
	SDL_assert(collision != nullptr);

	auto graphics = dynamic_cast<GraphicsComponent *>(e->GetComponent((ComponentType::Graphics)));
	int minX = collision->GetCollisionRadius(); 
	int minY = collision->GetCollisionRadius();
	if (graphics != nullptr)
	{
		minX -= SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().w/2;
		minY -= SpriteManager::Instance().GetSprite(graphics->GetCurrentSpriteID())->GetLocation().h/2; 
	}

	int maxX = mLevelWidth - collision->GetCollisionRadius();
	int maxY = mLevelHeight - collision->GetCollisionRadius();
	e->ProcessEvent(EventFactory::CreateBoundaryCollisionEvent(direction, minX, minY, maxX, maxY));
}


void CollisionManager::CheckLevelBoundaryCollisions(Entity *e)
{
	Direction direction = FindCollisionEdge(e);

	if (direction != Direction::None)
	{
		SendBoundaryCollisionEventToEntity(e, direction);
	}
}

// todo - implement quad tree or similar structure to improve performance - right now checks collisions to each entity 
// --> slow ( O(n^2) )
void CollisionManager::CheckEntityCollisions(Entity *first)
{
	for (auto id : mCollidables)
	{
		if (first->GetID() == id)
		{
			continue;
		}

		Entity *second = EntityManager::Instance().GetEntity(id);
		if (second == nullptr)
		{
			continue; // the same list is being iterated elsewhere, removing entity here would invalidate the iterator and cause a crash
		}
		
		HandleEntityCollision(first, second);

	}
}

void CollisionManager::HandleEntityCollision( Entity * first, Entity * second )
{
	auto firstCollisionComponent = dynamic_cast<CollisionAreaComponent *>(first->GetComponent(ComponentType::Collision));
	auto secondCollisionComponent = dynamic_cast<CollisionAreaComponent *>(second->GetComponent(ComponentType::Collision));

	SDL_assert(firstCollisionComponent != nullptr);
	SDL_assert(secondCollisionComponent != nullptr);
	
	int distance = CalculateDistance(first, second);

	int collidesIfCloser = firstCollisionComponent->GetCollisionRadius() + secondCollisionComponent->GetCollisionRadius();
	collidesIfCloser *= collidesIfCloser;

	if (distance < collidesIfCloser)
	{
		first->ProcessEvent(EventFactory::CreateEntityCollisionEvent(first->GetID(), second->GetID()));
	}
}

int CollisionManager::CalculateDistance( Entity * first, Entity * second )
{
	int firstCenterX = GetCenterX(first);
	int firstCenterY = GetCenterY(first);

	int secondCenterX = GetCenterX(second);
	int secondCenterY = GetCenterY(second);

	int xDistance = firstCenterX - secondCenterX;
	int yDistance = firstCenterY - secondCenterY;

	return xDistance*xDistance + yDistance*yDistance;
}

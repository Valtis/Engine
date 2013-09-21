#include "Graphics/Camera/EntityTrackingCamera.h"
#include "Graphics/SpriteManager.h"
#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"

EntityTrackingCamera::EntityTrackingCamera(int entityID, int levelWidth, int levelHeight) : mEntityID(entityID)
{
	SetLevelWidth(levelWidth);
	SetLevelHeight(levelHeight);
}

EntityTrackingCamera::~EntityTrackingCamera()
{

}

int EntityTrackingCamera::GetX() const
{

	auto l = GetLocationComponent();
	
	if (l == nullptr)
	{
		return 0;
	}
	
	int x = l->GetX() + GetXOffset();
	return CheckEdge(x, GetLevelWidth(), GetScreenWidth());	
}

int EntityTrackingCamera::CheckEdge(int coordinate, int levelSize, int screenSize) const
{
	// left  or top edge
	if (coordinate < screenSize/2)
	{
		coordinate = screenSize/2;
	}

	// right or bottom edge
	if (coordinate > levelSize - screenSize / 2)
	{
		coordinate = levelSize - screenSize / 2;
	}

	return coordinate;
}

int EntityTrackingCamera::GetY() const
{
	auto l = GetLocationComponent();
	
	
	if (l == nullptr)
	{
		return 0;
	}

	// some code here that handles the case when we are close to area edges
	int y = l->GetY() + GetYOffset();
	return CheckEdge(y, GetLevelHeight(), GetScreenHeight());	
}



LocationComponent *EntityTrackingCamera::GetLocationComponent() const
{
	Entity *e = EntityManager::Instance().GetEntity(mEntityID);
	if (e == nullptr)
	{
		return nullptr;

	}
	return dynamic_cast<LocationComponent *>(e->GetComponent(ComponentType::Location));
}

GraphicsComponent *EntityTrackingCamera::GetGraphicsComponent() const
{
	Entity *e = EntityManager::Instance().GetEntity(mEntityID);
	if (e == nullptr)
	{
		return nullptr;

	}
	return dynamic_cast<GraphicsComponent *>(e->GetComponent(ComponentType::Graphics));
}
// get offsets so that camera is centered on the middle of the sprite
int EntityTrackingCamera::GetXOffset() const
{
	auto g = GetGraphicsComponent();
	if (g == nullptr)
	{
		return 0;
	}

	return SpriteManager::Instance().GetSprite(g->GetCurrentSpriteID())->GetLocation().w/2;
}

int EntityTrackingCamera::GetYOffset() const
{
	auto g = GetGraphicsComponent();
	if (g == nullptr)
	{
		return 0;
	}

	return SpriteManager::Instance().GetSprite(g->GetCurrentSpriteID())->GetLocation().h/2;
}
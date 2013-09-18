#include "Graphics/Camera/EntityTrackingCamera.h"
#include "Graphics/SpriteManager.h"
#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"

EntityTrackingCamera::EntityTrackingCamera(int entityID) : mEntityID(entityID)
{

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
	
	// some code here that handles the case when we are close to area edges
	return l->GetX() + GetXOffset();
}


int EntityTrackingCamera::GetY() const
{
	auto l = GetLocationComponent();
	
	
	if (l == nullptr)
	{
		return 0;
	}

	// some code here that handles the case when we are close to area edges
	return l->GetY() + GetYOffset();
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
#include "Graphics/Camera/EntityTrackingCamera.h"
#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Component/LocationComponent.h"

EntityTrackingCamera::EntityTrackingCamera(UniqueID entityID) : mEntityID(entityID)
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

	return l->GetX();
}


int EntityTrackingCamera::GetY() const
{
	auto l = GetLocationComponent();
	
	if (l == nullptr)
	{
		return 0;
	}

	return l->GetY();
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
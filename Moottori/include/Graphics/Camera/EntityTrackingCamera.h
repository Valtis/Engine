#pragma once

#include "Camera.h"
#include "Utility/UniqueID.h"
class LocationComponent;
class EntityTrackingCamera : public Camera
{
public:
	EntityTrackingCamera(UniqueID entityID);
	~EntityTrackingCamera();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EntityTrackingCamera(const EntityTrackingCamera &) = delete;
	EntityTrackingCamera &operator=(const EntityTrackingCamera &) = delete;
#else
private:
	EntityTrackingCamera(const EntityTrackingCamera &);
	EntityTrackingCamera &operator=(const EntityTrackingCamera &);
public:
#endif

	int GetX() const override;
	int GetY() const override;


private:
	LocationComponent *GetLocationComponent() const;
	UniqueID mEntityID; // entity that will be tracked by the camera
};
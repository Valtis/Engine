#pragma once

#include "Camera.h"
#include "Utility/UniqueID.h"
class LocationComponent;
class GraphicsComponent;
class EntityTrackingCamera : public Camera
{
public:
	EntityTrackingCamera(int entityID);
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
	GraphicsComponent *GetGraphicsComponent() const;
	int GetXOffset() const;
	int GetYOffset() const;

	int mEntityID; // entity that will be tracked by the camera
};
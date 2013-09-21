#include "Entity/EntityFactory.h"
#include "Entity/Entity.h"
#include "UI/UI.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/InputComponent.h"
#include "Component/VelocityComponent.h"
#include "Component/AccelerationComponent.h"

namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(int x, int y,
		double maxAcceleration, double maxRotationAcceleration, std::vector<int> spriteIDs, UI &ui)
	{
		std::unique_ptr<Entity> entity(new Entity());
		entity->AddComponent(ComponentType::Location, std::unique_ptr<Component>(new LocationComponent(x, y)));
		entity->GetComponent(ComponentType::Location)->AttachScript("data/scripts/location.lua"); // HARD CODED TEST VALUE 

		entity->AddComponent(ComponentType::Graphics, std::unique_ptr<Component>(new GraphicsComponent(spriteIDs)));
		entity->AddComponent(ComponentType::Input, std::unique_ptr<Component>(new InputComponent(ui)));
		entity->AddComponent(ComponentType::Velocity, std::unique_ptr<Component>(new VelocityComponent()));
		
		entity->GetComponent(ComponentType::Velocity)->AttachScript("data/scripts/ship_velocity.lua"); // HARD CODED TEST VALUE 

		entity->AddComponent(ComponentType::Acceleration, std::unique_ptr<Component>(new AccelerationComponent(maxAcceleration, maxRotationAcceleration)));
		return entity;
	}
}
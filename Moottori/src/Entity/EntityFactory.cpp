#include "Entity/EntityFactory.h"
#include "Entity/Entity.h"
#include "UI/UI.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/InputComponent.h"
#include "Component/VelocityComponent.h"

namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(int x, int y, int velocity,  std::vector<UniqueID> spriteIDs, UI &ui)
	{
		std::unique_ptr<Entity> entity(new Entity());
		entity->AddComponent(ComponentType::Location, std::unique_ptr<Component>(new LocationComponent(x, y)));
		entity->AddComponent(ComponentType::Graphics, std::unique_ptr<Component>(new GraphicsComponent(spriteIDs)));
		entity->AddComponent(ComponentType::Input, std::unique_ptr<Component>(new InputComponent(ui)));
		entity->AddComponent(ComponentType::Velocity, std::unique_ptr<Component>(new VelocityComponent(velocity)));

		return entity;
	}
}
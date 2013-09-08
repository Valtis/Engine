#include "Entity/EntityFactory.h"
#include "Entity/Entity.h"
#include "UI/UI.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/InputComponent.h"

std::unique_ptr<Entity> CreatePlayer(int x, int y, std::vector<int> spriteIDs, UI &ui)
{
	std::unique_ptr<Entity> entity(new Entity());
	entity->AddComponent(ComponentType::Location, std::unique_ptr<Component>(new LocationComponent(x, y)));
	entity->AddComponent(ComponentType::Graphics, std::unique_ptr<Component>(new GraphicsComponent(spriteIDs)));

	std::unique_ptr<InputComponent> input(new InputComponent());


	return entity;
}
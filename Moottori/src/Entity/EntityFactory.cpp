#include "Entity/EntityFactory.h"
#include "Entity/Entity.h"
#include "UI/UI.h"

#include "Component/LocationComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/InputComponent.h"
#include "Component/VelocityComponent.h"
#include "Component/AccelerationComponent.h"
#include "Component/CollisionAreaComponent.h"
#include "Component//FactionComponent.h"

LuaState EntityFactory::mLuaState;
bool EntityFactory::mLuaStateIsInitialized = false;
std::unique_ptr<Entity> EntityFactory::mEntityBeingCreated(nullptr);
UI *EntityFactory::mUI = nullptr; 

void EntityFactory::InitializeLuaState()
{
	mLuaState.Open();
	mLuaState.OpenLuaLibrary(luaopen_io, LUA_IOLIBNAME);
	mLuaState.OpenLuaLibrary(luaopen_math, LUA_MATHLIBNAME);  

	RegisterMethods();

	mLuaStateIsInitialized = true;
}

void EntityFactory::RegisterMethods()
{
	luabind::module(mLuaState.State()) [
			luabind::def("AddInputComponent", &AddInputComponent),
			luabind::def("AddLocationComponent", &AddLocationComponent),
			luabind::def("AddGraphicsComponent", &AddGraphicsComponent),
			luabind::def("AddSprite", &AddSprite),
			luabind::def("AddVelocityComponent", &AddVelocityComponent),
			luabind::def("AddAccelerationComponent", &AddAccelerationComponent),
			luabind::def("AddCollisionComponent", &AddCollisionComponent),
			luabind::def("AddFactionComponent", &AddFactionComponent)
	];
}


std::unique_ptr<Entity> EntityFactory::CreateEntity(std::string functionName, UI *ui)
{
	if (mLuaState.FunctionExists(functionName))
	{
		mUI = ui;
		mEntityBeingCreated.reset(new Entity);
		luabind::call_function<void>(mLuaState.State(), functionName.c_str());
		mUI = nullptr;
		return std::move(mEntityBeingCreated);
	}

	throw std::runtime_error("Invalid creation script function: " + functionName);
}

void EntityFactory::AddAccelerationComponent(std::string scriptFile)
{
	std::unique_ptr<Component> c(new AccelerationComponent());
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Acceleration, std::move(c));
}

void EntityFactory::AddVelocityComponent(std::string scriptFile)
{
	std::unique_ptr<Component> c(new VelocityComponent());
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Velocity, std::move(c));
}

void EntityFactory::AddLocationComponent(int x, int y, std::string scriptFile)
{
	std::unique_ptr<Component> c(new LocationComponent(x, y));
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Location, std::move(c));
}

void EntityFactory::AddGraphicsComponent(std::string scriptFile)
{
	std::unique_ptr<Component> c(new GraphicsComponent());
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Graphics, std::move(c));
}

void EntityFactory::AddCollisionComponent(int collisionRadius, std::string scriptFile)
{
	std::unique_ptr<Component> c(new CollisionAreaComponent(collisionRadius));
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Collision, std::move(c));
}

void EntityFactory::AddInputComponent(std::string scriptFile)
{
	if (mUI == nullptr)
	{
		return;
	}

	std::unique_ptr<Component> c(new InputComponent(*mUI));
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Input, std::move(c));
}

void EntityFactory::AddSprite(int animationID, int spriteID, int ticksToNextFrame)
{
	auto graphicsComponent = dynamic_cast<GraphicsComponent *>(mEntityBeingCreated->GetComponent(ComponentType::Graphics));
	if (graphicsComponent == nullptr)
	{
		return;
	}

	graphicsComponent->AddSprite(animationID, spriteID, ticksToNextFrame);
}

void EntityFactory::AddFactionComponent( int faction, std::string scriptFile )
{
	std::unique_ptr<Component> c(new FactionComponent(faction));
	c->AttachScript(scriptFile);
	mEntityBeingCreated->AddComponent(ComponentType::Faction, std::move(c));
}

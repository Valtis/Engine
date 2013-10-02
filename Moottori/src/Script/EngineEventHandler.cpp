#include "Script/EngineEventHandler.h"
#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"
#include "Event/EventFactory.h"
#include "Collision/CollisionManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Level/LevelManager.h"
#include "Sound/SoundManager.h"
#include "Graphics/Particle/Emitter.h"


void EngineEventHandler::RegisterUI(UI *ui)
{
	mUI = ui;
}

void EngineEventHandler::RegisterFunctions(LuaState *state)
{
	luabind::module(state->State()) [
		luabind::class_<EngineEventHandler>("EventSender")
			.def("SpawnEntity", &EngineEventHandler::SpawnEntity)
			.def("PlaySoundEffect", &EngineEventHandler::PlaySoundEffect)
			.def("AddParticleEmitter", &EngineEventHandler::AddEmitter)
			.def("AddLevel", &EngineEventHandler::AddLevel)

	];

	luabind::globals(state->State())["engine"] = this;	
}

int EngineEventHandler::SpawnEntity(const char *scriptName, int parentID)
{
	auto entity = EntityFactory::CreateEntity(scriptName, mUI);
	int id = entity->GetID();

	EntityManager::Instance().AddEntity(std::move(entity));
	if (parentID != -1)
	{
		EntityManager::Instance().GetEntity(id)->ProcessEvent(EventFactory::CreateParentIDNotificationEvent(parentID));
	}

	Renderer::Instance().AddEntity(id);
	CollisionManager::Instance().AddEntity(id);
	LevelManager::Instance().GetActiveLevel()->AddEntity(id);
	
	return id;
}


void EngineEventHandler::PlaySoundEffect(int id)
{
	SoundManager::Instance().PlaySoundEffect(id);
}


void EngineEventHandler::AddEmitter(int x, int y, int numberOfParticles, double lifeTime, double maxVelocity)
{
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = 500;
	location.h = 500;
	std::unique_ptr<Emitter> emitter(new Emitter(numberOfParticles, location, lifeTime, maxVelocity));
	Renderer::Instance().AddEmitter(std::move(emitter));
}

void EngineEventHandler::AddLevel(int width, int height)
{
	LevelManager::Instance().AddLevel(width, height);
}
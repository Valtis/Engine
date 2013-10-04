#include "Script/EngineScriptInterface.h"
#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"
#include "Event/EventFactory.h"
#include "Collision/CollisionManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Level/LevelManager.h"
#include "Sound/SoundManager.h"
#include "Graphics/Particle/Emitter.h"
#include "Graphics/Particle/ParticleCache.h"
#include "Graphics/Camera/EntityTrackingCamera.h"
#include "Graphics/Camera/CameraManager.h"


void EngineScriptInterface::RegisterUI(UI *ui)
{
	mUI = ui;
}

void EngineScriptInterface::RegisterFunctions(LuaState *state)
{
	luabind::module(state->State()) [
		luabind::class_<EngineScriptInterface>("EventSender")
			.def("SpawnEntity", &EngineScriptInterface::SpawnEntity)
			.def("PlaySoundEffect", &EngineScriptInterface::PlaySoundEffect)
			.def("AddParticleEmitter", &EngineScriptInterface::AddEmitter)
			.def("AddParticle", &EngineScriptInterface::AddParticle)
			.def("AddLevel", &EngineScriptInterface::AddLevel)
			.def("CreateEntityTrackingCamera", &EngineScriptInterface::CreateEntityTrackingCamera)
			.def("GetNumberOfActiveEntities", &EngineScriptInterface::GetLevelEntitiesCount)

	];

	luabind::globals(state->State())["engine"] = this;	
}

int EngineScriptInterface::SpawnEntity(const char *scriptName, int parentID)
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


void EngineScriptInterface::PlaySoundEffect(int id)
{
	SoundManager::Instance().PlaySoundEffect(id);
}

inline void EngineScriptInterface::AddParticle(int id, int r, int g, int b)
{
	ParticleCache::Instance().AddParticle(id, r, g, b);
}

void EngineScriptInterface::AddEmitter(int id, int x, int y, int numberOfParticles, double lifeTime, double maxVelocity)
{
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = 500;
	location.h = 500;
	std::unique_ptr<Emitter> emitter(new Emitter(id, numberOfParticles, location, lifeTime, maxVelocity));
	Renderer::Instance().AddEmitter(std::move(emitter));
}

void EngineScriptInterface::AddLevel(int width, int height)
{
	LevelManager::Instance().AddLevel(width, height);
}


void EngineScriptInterface::CreateEntityTrackingCamera( int entityID )
{
	Entity *e = EntityManager::Instance().GetEntity(entityID);
	if (e == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Could not find entity with id " + std::to_string(entityID) + " for a camera to attach to - aborting");
		return;
	}

	if (e->GetComponent(ComponentType::Location) == nullptr)
	{
		LoggerManager::GetLog(SCRIPT_LOG).AddLine(LogLevel::Warning, 
			"Entity with id " + std::to_string(entityID) + " does not contain location - cannot attach camera - aborting");
		return;
	}

	std::unique_ptr<Camera> c(new EntityTrackingCamera(entityID, 
		LevelManager::Instance().GetActiveLevel()->GetWidth(), LevelManager::Instance().GetActiveLevel()->GetHeight()));
	CameraManager::Instance().AddCamera(std::move(c));
}


int EngineScriptInterface::GetLevelEntitiesCount()
{
	return LevelManager::Instance().GetActiveLevel()->GetEntities().size();
}
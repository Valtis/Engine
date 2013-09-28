#include "Entity/EntityManager.h"
#include "Entity/EntityFactory.h"
#include "Entity/Entity.h"
#include "Event/EventFactory.h"
#include "Event/RequestTerminationEvent.h"
#include "Event/SpawnEntityEvent.h"
#include "Utility/Enumerations.h"
#include <SDL_assert.h>

EntityManager *EntityManager::mInstance = nullptr;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

EntityManager &EntityManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new EntityManager();
	}

	return *mInstance;
}

void EntityManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}


void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
	SDL_assert(entity != nullptr);
	RegisterEvents(entity.get());

	mEntities[entity->GetID()] = std::move(entity);
}

void EntityManager::RegisterEvents( Entity *entity )
{
	entity->RegisterCallback(EventType::RequestTermination, [&](Event *event) { this->HandleTerminationEvent(event); });
	entity->RegisterCallback(EventType::SpawnEntity, [&](Event *event) { this->HandleSpawnEvent(event); } );
}


Entity *EntityManager::GetEntity(int id)
{
	if (mEntities.count(id) == 0)
	{
		return nullptr;
	}

	return mEntities[id].get();
}


void EntityManager::Update(double doubleTicks)
{
	DeleteQueuedEntities();
}

void EntityManager::DeleteQueuedEntities()
{
	for (int i : mDeleteQueue)
	{
		mEntities.erase(i);
		SDL_assert(mEntities.count(i) == 0);
	}
	mDeleteQueue.clear();
}

void EntityManager::UpdateEntityStates( double doubleTicks )
{
	for (const auto &entityNode : mEntities)
	{
		entityNode.second->Update(doubleTicks);
	}
}



void EntityManager::HandleTerminationEvent(Event *event)
{
	auto termination = dynamic_cast<RequestTerminationEvent *>(event);
	SDL_assert(termination != nullptr);
	mDeleteQueue.push_back(termination->GetID());
}


void EntityManager::HandleSpawnEvent(Event *event)
{
	auto spawn = dynamic_cast<SpawnEntityEvent *>(event);
	SDL_assert(spawn != nullptr);


	auto entity = EntityFactory::CreateEntity(spawn->GetScriptName());

	int id = entity->GetID();
	AddEntity(std::move(entity));

	for (auto listener : mListeners)
	{
		listener->NotifyEventSpawn(id);
	}

	GetEntity(id)->ProcessEvent(EventFactory::CreateParentIDNotificationEvent(spawn->GetParentID()));

}

void EntityManager::AddListener( EntityManagerListener *listener )
{
	mListeners.push_back(listener);
}


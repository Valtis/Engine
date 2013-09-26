#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
#include "Event/RequestTerminationEvent.h"
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
	entity->RegisterCallback(EventType::RequestTermination, [&](Event *event) { this->HandleTerminationEvent(event); });
	mEntities[entity->GetID()] = std::move(entity);
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

void EntityManager::HandleTerminationEvent(Event *event)
{
	auto termination = dynamic_cast<RequestTerminationEvent *>(event);
	SDL_assert(termination != nullptr);
	mDeleteQueue.push_back(termination->GetID());
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

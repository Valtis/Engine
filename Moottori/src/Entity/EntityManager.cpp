#include "Entity/EntityManager.h"
#include "Entity/Entity.h"
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
	for (const auto &entityNode : mEntities)
	{
		entityNode.second->Update(doubleTicks);
	}
}
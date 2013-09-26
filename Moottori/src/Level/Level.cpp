#include "Level/Level.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

void Level::Update(double ticksPassed)
{
	UpdateEntities(ticksPassed);
}

void Level::UpdateEntities(double ticksPassed)
{
	for (auto iter = std::begin(mLevelEntities); iter != std::end(mLevelEntities); ++iter)
	{
		Entity *e = EntityManager::Instance().GetEntity(*iter);
		if (e == nullptr)
		{
			iter = mLevelEntities.erase(iter);
			if (iter == std::end(mLevelEntities))
			{
				break;
			}
			continue;
		}

		e->Update(ticksPassed);
	}
}
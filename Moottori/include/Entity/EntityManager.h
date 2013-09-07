#pragma once
#include <unordered_map>
#include <memory>
#include "Utility/UniqueID.h"

class Entity;
class EntityManager
{
public:
	~EntityManager();
	
	static EntityManager &Instance();
	void Release();

	void AddEntity(std::unique_ptr<Entity> entity);
	Entity *GetEntity(UniqueID id);



private:
	EntityManager();
	static EntityManager *mInstance;
	
	std::unordered_map<UniqueID, std::unique_ptr<Entity>, UniqueIDHashFunction> mEntities;
};
#pragma once
#include <unordered_map>
#include <memory>

class Entity;
class Event;
class EntityManager
{
public:
	~EntityManager();
	
	static EntityManager &Instance();
	static void Release();

	void AddEntity(std::unique_ptr<Entity> entity);
	Entity *GetEntity(int id);

	void Update(double ticksPassed);

	void UpdateEntityStates( double doubleTicks );

	void DeleteQueuedEntities();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	EntityManager(const EntityManager &) = delete;
	EntityManager &operator=(const EntityManager &) = delete;
#else
private:
	EntityManager(const EntityManager &);
	EntityManager &operator=(const EntityManager &);
public:
#endif

private:
	EntityManager();
	static EntityManager *mInstance;
	
	std::unordered_map<int, std::unique_ptr<Entity>> mEntities;
	void HandleTerminationEvent(Event *event);
	std::vector<int> mDeleteQueue;
};
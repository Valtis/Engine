#pragma once
#include <unordered_map>
#include <memory>
#include <vector>


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
	void UpdateEntityStates( double doubleTicks );
	void DeleteQueuedEntities();
	void RegisterEvents( Entity *entity );

	EntityManager();
	static EntityManager *mInstance;
	
	std::unordered_map<int, std::unique_ptr<Entity>> mEntities;

	void HandleTerminationEvent(Event *event);
	void HandleSpawnEvent(Event *event);

	std::vector<int> mDeleteQueue;
};
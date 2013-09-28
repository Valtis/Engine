#pragma once

class EntityManagerListener
{
public:
	virtual void NotifyEventSpawn(int entityID) = 0;
};
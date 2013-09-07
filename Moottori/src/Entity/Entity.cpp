#include "Entity/Entity.h"
#include "Component/Component.h"
#include "Event/Event.h"

#include <SDL_assert.h>

Entity::Entity() : mComponents(), mEventCallbacks(), mEvents()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::AddComponent(ComponentType type, std::unique_ptr<Component> c)
{
    SDL_assert(type != ComponentType::None);
    c->RegisterEventHandler(this);
    mComponents[type] = std::move(c);
}

void Entity::AddEvent(std::unique_ptr<Event> event)
{
    mEvents.push_back(std::move(event));
}

Component *Entity::GetComponent(ComponentType type)
{
    if (mComponents.count(type) == 0)
    {
        return nullptr;
    }

    return mComponents[type].get();
}


void Entity::ProcessEvent(std::unique_ptr<Event> event)
{
    for (auto &eventCallback : mEventCallbacks[event->GetType()])
    {
        eventCallback(event.get());
    }
}

void Entity::RegisterCallback(EventType type, std::function<void(Event *)> callback)
{
	SDL_assert(type != EventType::None);
	mEventCallbacks[type].push_back(callback);
}


void Entity::Update(double ticksPassed)
{
    for (const auto &component : mComponents)
    {
        component.second->Update(ticksPassed);
    }

    while (!mEvents.empty())
    {
        ProcessEvent(std::move(mEvents.front()));
        mEvents.pop_front();
    }
}

#pragma once

#include "Component.h"

class FactionComponent : public Component
{
public: 
	FactionComponent(int faction);

#if !defined _MSC_VER || _MSC_VER >= 1800 
	FactionComponent(const FactionComponent &) = delete;
	FactionComponent &operator=(const FactionComponent &) = delete;
#else
private:
	FactionComponent(const FactionComponent &);
	FactionComponent &operator=(const FactionComponent &);
public:
#endif

protected:
	void OnAttachingScript() override;
	void OnRegisteringEventHandler(EventHandler *handler);

private:

	void HandleFactionQuery(Event *event);
	int mFaction;
};
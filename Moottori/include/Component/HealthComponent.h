#pragma once
#include "Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent() : mCurrentHealth(0), mMaxHealth(0) { }
	HealthComponent(int currentHealth, int maxHealth) : mCurrentHealth(currentHealth), mMaxHealth(maxHealth) { } 
	~HealthComponent() { }

#if !defined _MSC_VER || _MSC_VER >= 1800 
	HealthComponent(const HealthComponent &) = delete;
	HealthComponent &operator=(const HealthComponent &) = delete;
#else
private:
	HealthComponent(const HealthComponent &);
	HealthComponent &operator=(const HealthComponent &);
public:
#endif
	
protected:
	void OnAttachingScript() override;

private:
	int mCurrentHealth;
	int mMaxHealth;

};
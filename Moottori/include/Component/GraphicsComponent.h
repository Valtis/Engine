#pragma once
#include <vector>
#include "Component.h"

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(std::vector<int> spriteIDs);
	GraphicsComponent();
	~GraphicsComponent();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	GraphicsComponent(const GraphicsComponent &) = delete;
	GraphicsComponent &operator=(const GraphicsComponent &) = delete;
#else
private:
	GraphicsComponent(const GraphicsComponent &);
	GraphicsComponent &operator=(const GraphicsComponent &);
public:
#endif


	void AddSpriteID(int id);
	void ClearSpriteIDs();

	int GetCurrentSpriteID();


	void NextSprite();
	void PreviousSprite();
	void ResetSprite();

private:
	std::vector<int> mSpriteIDs;
	int mCurrentSprite;
};
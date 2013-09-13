#pragma once
#include <vector>
#include "Component.h"

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(std::vector<int> spriteIDs);
	GraphicsComponent();
	~GraphicsComponent();


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
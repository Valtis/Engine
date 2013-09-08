#pragma once
#include <vector>
#include "Component.h"
#include "Utility/UniqueID.h"

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(std::vector<int> spriteIDs);
	GraphicsComponent();
	~GraphicsComponent();


	void AddSpriteID(UniqueID id);
	void ClearSpriteIDs();

	UniqueID GetCurrentSpriteID();
	

	void NextSprite();
	void PreviousSprite();
	void ResetSprite();

private:
	std::vector<UniqueID> mSpriteIDs;
	int mCurrentSprite;
};
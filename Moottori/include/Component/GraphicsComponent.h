#pragma once
#include <vector>
#include <unordered_map>
#include "Component.h"
// animation is place holder code, needs to be refactored to something more general\sane
// also solve how\which subsystem drives the animations? (AI, movement, something else?)
struct FrameData
{
	FrameData() : mTicksToNextFrame(0), mCurrentTickCount(0), spriteID(0) {}
	double mTicksToNextFrame;
	double mCurrentTickCount;
	int spriteID;
};

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

	void HandleAnimationStateChangeEvent(Event *event);
	void Update(double ticksPassed) override;

	void SetAnimationState(bool state) {  mIsAnimating = state; }
			
	void AddSpriteID(int id);
	void ClearSpriteIDs();

	int GetCurrentSpriteID();


	void NextSprite();
	void PreviousSprite();
	void ResetSprite();
protected:
	void OnEventHandlerRegistration() override;
private:
	// todo: split to another class? should this component really hold this much responsibility?

	bool mIsAnimating;
	std::unordered_map<int, std::vector<FrameData>> mGraphicsData;
	int mCurrentSprite;
	int mCurrentAnimationID;
};
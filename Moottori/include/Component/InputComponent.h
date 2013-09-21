#include "Component.h"
class UI;
class InputComponent : public Component
{
public:
	InputComponent(UI &ui);
	~InputComponent();

#if !defined _MSC_VER || _MSC_VER >= 1800 
	InputComponent(const InputComponent &) = delete;
	InputComponent &operator=(const InputComponent &) = delete;
#else
private:
	InputComponent(const InputComponent &);
	InputComponent &operator=(const InputComponent &);
public:
#endif

protected:
	void OnAttachingScript() override;

private:
	bool InputHandler(Event *event);
	void SendAccelerationChangeMessage(Direction accelerationDirection, Direction rotationDirection, UIEventState eventState);
};
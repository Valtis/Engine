#include "Component.h"
class UI;
class InputComponent : public Component
{
	public:
		InputComponent(UI &ui);
		~InputComponent();

		
		

	private:
		bool InputHandler(Event *event);



};
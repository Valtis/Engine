#include "UI/Controller/ControllerFactory.h"
#include "UI/Controller/KeyboardController.h"
#include <stdexcept>
namespace ControllerFactory
{
	std::unique_ptr<Controller> NewObject(ControllerType type)
	{
		std::unique_ptr<Controller> controller;
		
		switch (type)
		{
			case ControllerType::Keyboard:
				controller.reset(new KeyboardController);
				break;


			default:
				throw std::invalid_argument("Invalid argument given int ControllerFactory::NewObject: value " + static_cast<int>(type));
		}
		
		return controller;
	}
	
}
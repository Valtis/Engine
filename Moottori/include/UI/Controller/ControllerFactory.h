#pragma once
#include <memory>
#include "Utility/Enumerations.h"
class Controller;
namespace ControllerFactory
{
	std::unique_ptr<Controller> NewObject(ControllerType type);
}
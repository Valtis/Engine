#include "Component/AccelerationComponent.h"
#include "Event/ChangeAccelerationEvent.h"
#include "Event/ChangeVelocityEvent.h"
#include "Event/QueryDirectionEvent.h"
#include <cmath>
#include "SDL_assert.h"

void AccelerationComponent::OnAttachingScript()
{

	luabind::module(mLuaState.State()) [
		luabind::class_<AccelerationComponent>("AccelerationComponent")
			.def("SendAccelerationChangeMessage", &AccelerationComponent::SendAccelerationChangeMessage)
			.def("GetCurrentDirection", &AccelerationComponent::SendDirectionQueryMessage)
			.def_readwrite("x_acceleration", &AccelerationComponent::mCurrentXAcceleration)
			.def_readwrite("y_acceleration", &AccelerationComponent::mCurrentYAcceleration)
			.def_readwrite("rotation_acceleration", &AccelerationComponent::mCurrentRotationAcceleration)
	];

	luabind::globals(mLuaState.State())["acceleration_component"] = this;
}

void AccelerationComponent::SendAccelerationChangeMessage(double ticksPassed)
{
	GetEventHandler().ProcessEvent(std::unique_ptr<ChangeVelocityEvent>(new ChangeVelocityEvent(mCurrentXAcceleration*ticksPassed, 
			mCurrentYAcceleration*ticksPassed, mCurrentRotationAcceleration*ticksPassed)));
}

void AccelerationComponent::SendDirectionQueryMessage()
{
	double rotation;
	bool wasHandled;
	GetEventHandler().ProcessEvent(std::unique_ptr<QueryDirectionEvent>(new QueryDirectionEvent(rotation, wasHandled)));
	// little ugly, but afaik (do correct me if I am wrong), you cannot use references\pointers from lua code and c++ doesn't support multiple return values natively
	/*lua_pushnumber(mLuaState.State(), rotation);
	lua_pushinteger(mLuaState.State(), wasHandled);
	lua_pushinteger(mLuaState.State(), 2); // number of parameters into stack*/
}

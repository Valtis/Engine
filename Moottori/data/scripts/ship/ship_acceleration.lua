
function UpdateXYAcceleration(move_direction, velocity_change, rotation)
	-- shift rotation: currently 0 degrees is upwards, we want it to be on x axis
	rotation = rotation - 90
		
	multiplier = 0 
	if move_direction == Direction_Forward then
		multiplier = 1
	elseif move_direction == Direction_Backward then
		multiplier = -1
	end
		
	rotationRadian = rotation*math.pi/180
	acceleration_component.x_acceleration = multiplier*velocity_change*math.cos(rotationRadian)
	acceleration_component.y_acceleration = multiplier*velocity_change*math.sin(rotationRadian)
end

function ChangeXYAcceleration(move_direction, event_state)
	if move_direction == Direction_None then
		return
	end
	
	max_acceleration = 2
	velocity_change = max_acceleration
	
	if event_state == Event_State_Stop then
		velocity_change = 0
	end
	
	rotation = 0
	wasAnswered = 0
	rotation, wasAnswered = messaging:SendDirectionQueryMessage()
	
	-- it is possible that the entity does not have location component or the component does not handle the query
	if wasAnswered == 0 then
		return
	end
	
	UpdateXYAcceleration(move_direction, velocity_change, rotation) 
	
end


function ChangeRotationAcceleration(turn_direction, event_state)
	if turn_direction == Direction_None then
		return
	end
	
	max_rotation_acceleration = 8
	
	velocity_change = max_rotation_acceleration;
	if event_state == Event_State_Stop then
		velocity_change = 0
	end

	if turn_direction == Direction_Right then
		acceleration_component.rotation_acceleration = velocity_change
	elseif turn_direction == Direction_Left then
		acceleration_component.rotation_acceleration = -velocity_change
	end
end

function OnAccelerationChangeEvent(move_direction, turn_direction, event_state)
	
	ChangeXYAcceleration(move_direction, event_state)
	ChangeRotationAcceleration(turn_direction, event_state)
end

function OnUpdate(ticksPassed)
	if acceleration_component.x_acceleration ~= 0 or 
	   acceleration_component.y_acceleration ~=0 or 
	   acceleration_component.rotation_acceleration ~= 0 then
	   
	   messaging:SendVelocityChangeMessage(
			acceleration_component.x_acceleration*ticksPassed, 
			acceleration_component.y_acceleration*ticksPassed,
			acceleration_component.rotation_acceleration*ticksPassed
			)
			
	end
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeAcceleration)
end
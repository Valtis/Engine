--EventTypes
EventType_None = 0
EventType_UIEvent = 1
EventType_QueryDirection = 2
EventType_ChangeAcceleration = 3
EventType_ChangeVelocity = 4
EventType_ChangeLocation = 5
EventType_ChangeAnimationState = 6
EventType_RequestTermination = 7
EventType_BoundaryCollision = 8
EventType_EntityCollision = 9

function SigNum(value)
	if value < 0 then
		return -1
	elseif value > 0 then
		return 1
	else
		return 0
	end
	
end

function UpdateXYVelocities(x_velocity, y_velocity, velocity_loss_per_tick)
	angle = math.atan2(y_velocity, x_velocity)
	totalVelocity = math.sqrt(x_velocity*x_velocity + y_velocity*y_velocity) - velocity_loss_per_tick
	
	if totalVelocity < 0 then
		totalVelocity = 0
	end
	
	velocity_component.x_velocity = math.abs(totalVelocity)*math.cos(angle)
	velocity_component.y_velocity = math.abs(totalVelocity)*math.sin(angle)
end

function UpdateRotationVelocity(rotation_velocity, rotation_velocity_loss_per_tick)
	rotSign = SigNum(rotation_velocity)
	
	rotation_velocity = math.abs(rotation_velocity) - rotation_velocity_loss_per_tick
	if rotation_velocity < 0 then
		rotation_velocity = 0
	end

	velocity_component.rotation_velocity = rotSign*rotation_velocity
end

function DecaySpeed()
	
	velocity_loss_per_tick = 0.3
	rotation_velocity_loss_per_tick = 1
	
	x_velocity = velocity_component.x_velocity
	y_velocity = velocity_component.y_velocity
	rotation_velocity =  velocity_component.rotation_velocity
	
	UpdateXYVelocities(x_velocity, y_velocity, velocity_loss_per_tick)
	UpdateRotationVelocity(rotation_velocity, rotation_velocity_loss_per_tick)
	
end

function OnUpdate(ticks_passed)
	
	animation_state = false
	animation_id = 0 -- default idle animation --- animation_id defined in player_creation.lua
	if velocity_component.x_velocity ~= 0  or velocity_component.y_velocity ~= 0 or velocity_component.rotation_velocity ~= 0  then
		velocity_component:SendVelocityChangeMessage(ticks_passed)
		DecaySpeed()		
		animation_state = true
		animation_id = 1 -- ship go wroom
	end
	velocity_component:SendAnimationStateMessage(animation_id, animation_state)
end

function OnVelocityChangeEvent(x_velocity_change, y_velocity_change, rotation_velocity_change)

	max_velocity = 8
	max_rotation_speed = 8
	
	velocity_component.x_velocity = velocity_component.x_velocity + x_velocity_change
	velocity_component.y_velocity = velocity_component.y_velocity + y_velocity_change
	velocity_component.rotation_velocity = velocity_component.rotation_velocity + rotation_velocity_change

	x_sign = SigNum(velocity_component.x_velocity)
	y_sign = SigNum(velocity_component.y_velocity)
	rotate_sign = SigNum(velocity_component.rotation_velocity)
	
	if math.abs(velocity_component.x_velocity) > max_velocity then
		velocity_component.x_velocity = max_velocity*x_sign
	end

	if math.abs(velocity_component.y_velocity) > max_velocity then
		velocity_component.y_velocity = max_velocity*y_sign
	end

	if math.abs(velocity_component.rotation_velocity) > max_rotation_speed then
		velocity_component.rotation_velocity = max_rotation_speed*rotate_sign
	end
end

function OnRegisterForEvents()
	component:RegisterForEvents(EventType_ChangeVelocity)
end

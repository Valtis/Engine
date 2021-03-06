
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
	
	velocity_loss_per_tick = 0.2
	rotation_velocity_loss_per_tick = 15
	
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
		
		messaging:SendLocationChangeMessage(
			velocity_component.x_velocity*ticks_passed,
			velocity_component.y_velocity*ticks_passed,
			velocity_component.rotation_velocity*ticks_passed
			)
		
		DecaySpeed()		
		animation_state = true
		animation_id = 1 -- ship go wroom
		
		x, y, wasHandled = messaging:SendLocationQueryMessage()
		if wasHandled then
			engine:AddParticleEmitter(smoke_emitter, x + 25, y + 25, 10, 10, 1.0)
		end
	end
	messaging:SendAnimationStateMessage(animation_id, animation_state)
end

function OnVelocityChangeEvent(x_velocity_change, y_velocity_change, rotation_velocity_change)

	max_velocity = 10
	max_rotation_speed = 15
	
	velocity_component.x_velocity = velocity_component.x_velocity + x_velocity_change
	velocity_component.y_velocity = velocity_component.y_velocity + y_velocity_change
	velocity_component.rotation_velocity = velocity_component.rotation_velocity + rotation_velocity_change

	x_sign = SigNum(velocity_component.x_velocity)
	y_sign = SigNum(velocity_component.y_velocity)
	rotate_sign = SigNum(velocity_component.rotation_velocity)
	
	max_x_velocity, max_y_velocity = CalculateMaxDirectionalVelocities(max_velocity)
	
	if math.abs(velocity_component.x_velocity) > max_x_velocity then
		velocity_component.x_velocity = max_x_velocity*x_sign
	end

	if math.abs(velocity_component.y_velocity) > max_y_velocity then
		velocity_component.y_velocity = max_y_velocity*y_sign
	end

	if math.abs(velocity_component.rotation_velocity) > max_rotation_speed then
		velocity_component.rotation_velocity = max_rotation_speed*rotate_sign
	end
end

function CalculateMaxDirectionalVelocities(max_velocity) 
	--[[angle, wasHandled = messaging:SendDirectionQueryMessage()
	
	if wasHandled == false then
		return
	end
	
	angle = (angle - 90)*math.pi/180]]--
	angle = math.atan2(velocity_component.y_velocity, velocity_component.x_velocity)
	max_x_velocity = math.abs(max_velocity*math.cos(angle))
	max_y_velocity = math.abs(max_velocity*math.sin(angle))
	
	return max_x_velocity, max_y_velocity	
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeVelocity)
end

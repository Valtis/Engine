

function DecaySpeed()
	
	velocity_loss_per_tick = 0.3
	rotation_velocity_loss_per_tick = 1

	x_velocity = velocity_component.x_velocity
	y_velocity = velocity_component.y_velocity
	rotation_velocity =  velocity_component.rotation_velocit

	angle = math.atan2(y_velocity, x_velocity)

	
	totalVelocity = math.sqrt(velocity_component.x_velocity*velocity_component.x_velocity + velocity_component.y_velocity*velocity_component.y_velocity) - velocity_loss_per_tick
	
	if totalVelocity < 0 then
		totalVelocity = 0
	end
	
	velocity_component.x_velocity = math.abs(totalVelocity)*math.cos(angle)
	velocity_component.y_velocity = math.abs(totalVelocity)*math.sin(angle)

	rotSign = 0
	if velocity_component.rotation_velocity < 0 then
		rotSign = -1
	else
		rotSign = 1
	end
	
	velocity_component.rotation_velocity = math.abs(velocity_component.rotation_velocity) - rotation_velocity_loss_per_tick
	if velocity_component.rotation_velocity < 0 then
		velocity_component.rotation_velocity = 0
	end

	velocity_component.rotation_velocity = rotSign*velocity_component.rotation_velocity
	
end


function OnUpdate()
	if velocity_component.x_velocity ~= 0  or velocity_component.y_velocity ~= 0 or velocity_component.rotation_velocity ~= 0  then
		DecaySpeed()
	end
end


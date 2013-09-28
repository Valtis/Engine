is_animating = 0

function OnUpdate(ticks_passed)
	if is_animating ~= 1 then
		is_animating = 1
		messaging:SendAnimationStateMessage(0, true)
	end

	messaging:SendLocationChangeMessage(
			velocity_component.x_velocity*ticks_passed,
			velocity_component.y_velocity*ticks_passed,
			velocity_component.rotation_velocity*ticks_passed
			)


end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')

	CalculateRotation()
	CalculateSpeed()
end

function CalculateRotation()

	velocity_component.rotation_velocity = math.random(8)

	if math.random(2) == 1 then
		velocity_component.rotation_velocity = -1*velocity_component.rotation_velocity
	end
end


function CalculateSpeed()
	angle = CalculateAngle()

	speed = math.random(10)
	velocity_component.x_velocity = speed * math.cos(angle)
	velocity_component.y_velocity = speed * math.sin(angle)
end


function CalculateAngle()

	x, y, wasHandled = messaging:SendLocationQueryMessage()
	targetX = math.random(level_width)
	targetY = math.random(level_height)


	xDiff = targetX - x
	yDiff = targetY - y

	return math.atan2(yDiff, xDiff)
end

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


	velocity_component.rotation_velocity = math.random(8) + 1

	if math.random(2) == 1 then
		velocity_component.rotation_velocity = -1*velocity_component.rotation_velocity
	end





end

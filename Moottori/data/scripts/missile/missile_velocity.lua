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

function OnParentIdNotificationEvent(parent_id)
	CalculateSpeed(parent_id)
end


function CalculateSpeed(parent_id)
	angle, wasHandled = messaging:SendDirectionQueryMessageToEntity(parent_id)

	if wasHandled == 0 then
		return
	end


	speed = 15

	velocity_component.x_velocity = speed*math.sin(angle*math.pi/180)
	velocity_component.y_velocity = -1.0*speed*math.cos(angle*math.pi/180)
end



function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ParentIDNotification)

	velocity_component.rotation_velocity = 0
end







function OnLocationChangeEvent(x_change, y_change, rotation_change)
	location_component.x  = location_component.x + x_change
	location_component.y = location_component.y + y_change
	location_component.rotation = location_component.rotation + rotation_change
end


function OnParentIdNotificationEvent(parent_id)
	x, y, wasHandled = messaging:SendLocationQueryMessageToEntity(parent_id)
	rotation, rotationWasHandled = messaging:SendDirectionQueryMessageToEntity(parent_id)

	if wasHandled == false or rotationWasHandled == false then
		return
	end

	location_component.x = x
	location_component.y = y
	location_component.rotation = rotation

end

function OnUpdate(tick_count)
	engine:AddParticleEmitter(smoke_emitter,
	location_component.x + 25, location_component.y	+ 25,
	20, 20, 0.5)
end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeLocation)
	component:RegisterForEvents(EventType_ParentIDNotification)
end




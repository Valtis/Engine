
function OnLocationChangeEvent(x_change, y_change, rotation_change)
	location_component.x  = location_component.x + x_change
	location_component.y = location_component.y + y_change
	location_component.rotation = location_component.rotation + rotation_change
end

function OnLocationQuery()
	return location_component.x, location_component.y
end


function OnDirectionQuery()
	return location_component.rotation
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeLocation)
	component:RegisterForEvents(EventType_QueryDirection)
end

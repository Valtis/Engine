
function OnLocationChangeEvent(x_change, y_change, rotation_change)
	location_component.x  = location_component.x + x_change
	location_component.y = location_component.y + y_change
	location_component.rotation = location_component.rotation + rotation_change
end

function OnBoundaryCollisionEvent(direction, minX, minY, maxX, maxY)
	location_component.x = math.min(math.max(location_component.x, minX), maxX)
	location_component.y = math.min(math.max(location_component.y, minY), maxY)
end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeLocation)
	component:RegisterForEvents(EventType_BoundaryCollision)
	component:RegisterForEvents(EventType_QueryDirection)
end

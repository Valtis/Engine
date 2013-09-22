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

function OnLocationChangeEvent(x_change, y_change, rotation_change)
	location_component.x  = location_component.x + x_change
	location_component.y = location_component.y + y_change
	location_component.rotation = location_component.rotation + rotation_change
end

function OnBoundaryCollisionEvent(direction, minX, minY, maxX, maxY)
	io.write(minX)
	io.write("\n")
	location_component.x = math.min(math.max(location_component.x, minX), maxX)
	location_component.y = math.min(math.max(location_component.y, minY), maxY)
end

function OnDirectionQuery()
{
	return location_component.x, location_component.y
}

function OnScriptInit()
	component:RegisterForEvents(EventType_ChangeLocation)
	component:RegisterForEvents(EventType_BoundaryCollision)
end
´

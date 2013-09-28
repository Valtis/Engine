
function OnLocationChangeEvent(x_change, y_change, rotation_change)
	location_component.x  = location_component.x + x_change
	location_component.y = location_component.y + y_change
	location_component.rotation = location_component.rotation + rotation_change
end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeLocation)

	CalculateStartPosition()

end


function CalculateStartPosition()

	side = math.random(4)
	location_component.x = math.random(level_width)
	location_component.y = math.random(level_height)

	--left
	if side == 1 then
		location_component.x = -100

	elseif side == 2 then -- right
		location_component.x = level_width + 100
	elseif side == 3 then -- top
		location_component.y = -100
	else -- bot
			location_component.y  = level_height + 100
	end

end

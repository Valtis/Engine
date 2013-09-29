

function OnUpdate(ticks_passed)
	asteroid_health_counter = asteroid_health_counter - ticks_passed

	if asteroid_health_counter < 0 then
		messaging:SendEntityTerminationRequestMessage(entity:GetID())
	end



end



function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	asteroid_health_counter = 15000/game_logic_tick
end

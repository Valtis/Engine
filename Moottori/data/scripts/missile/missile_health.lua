

function OnUpdate(ticks_passed)
	missile_health_counter = missile_health_counter - 1

	if missile_health_counter < 0 then
		messaging:SendEntityTerminationRequestMessage(entity:GetID())
	end



end



function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	missile_health_counter = 4000/game_logic_tick -- lives 4000 milliseconds
end

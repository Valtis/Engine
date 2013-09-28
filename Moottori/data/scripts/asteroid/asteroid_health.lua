

function OnUpdate(ticks_passed)
	asteroid_health_counter = asteroid_health_counter - 1

	if asteroid_health_counter < 0 then
		messaging:SendEntityTerminationRequestMessage(entity:GetID())
	end



end



function OnRegisterForEvents()
	asteroid_health_counter = 1000

end

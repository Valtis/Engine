number_of_ticks_passed = 100000

function OnUpdate(ticks_passed)

	number_of_ticks_passed = ticks_passed + number_of_ticks_passed

	if number_of_ticks_passed*engine.game_logic_tick_length > 1000 then
		if engine:GetNumberOfActiveEntities() < 20 then
			number_of_ticks_passed = 0
			engine:AddEntity("CreateAsteroid")

		end
	end

end


function OnGameInit()
	dofile('data/scripts/defines.lua')
	engine.draw_tick_length = game_draw_tick
	engine.game_logic_tick_length = game_logic_tick
	engine:CreateLevel(level_width, level_height)


	entityID = engine:AddEntity("CreatePlayer")
	engine:AttachCamera(entityID)
end

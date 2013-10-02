number_of_ticks_passed = 100000

function OnUpdate(ticks_passed)

	number_of_ticks_passed = ticks_passed + number_of_ticks_passed

	if number_of_ticks_passed*game_logic_tick > 1000 then
		if placeholder:GetNumberOfActiveEntities() < 20 then
			number_of_ticks_passed = 0
			engine:SpawnEntity("CreateAsteroid", -1)
		end
	end

end


function OnGameInit()
	dofile('data/scripts/defines.lua')
	placeholder.draw_tick_length = game_draw_tick
	placeholder.game_logic_tick_length = game_logic_tick
	engine:AddLevel(level_width, level_height)


	entityID = engine:SpawnEntity("CreatePlayer", -1)
	placeholder:AttachCamera(entityID)

	engine:SpawnEntity("CreateSun", -1)
	engine:SpawnEntity("CreateStar", -1)
	engine:SpawnEntity("CreateStar", -1)
end

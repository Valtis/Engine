number_of_ticks_passed = 100000

function OnUpdate(ticks_passed)

	number_of_ticks_passed = ticks_passed + number_of_ticks_passed

	if number_of_ticks_passed*engine.game_logic_tick_length > 3000 then
		if engine:GetNumberOfActiveEntities() < 20 then

			io.write("Updating game state!\n")
			io.write("Number of entities: " .. engine:GetNumberOfActiveEntities() .. "\n")
			number_of_ticks_passed = 0

			engine:AddEntity("CreateAsteroid")

		end
	end

end


function OnGameInit()
	dofile('data/scripts/defines.lua')
	engine.draw_tick_length = game_draw_tick
	engine.game_logic_tick_length = game_logic_tick
	engine.level_width = level_width
	engine.level_height = level_level_height
	entityID = engine:AddEntity("CreatePlayer")
	engine:AttachCamera(entityID)
end

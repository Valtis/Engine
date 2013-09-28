number_of_ticks_passed = 0

function OnUpdate(ticks_passed)
	--[[
	number_of_ticks_passed = ticks_passed + number_of_ticks_passed
	
	if number_of_ticks_passed*engine.game_logic_tick_length > 1000 then
		if engine:GetNumberOfActiveEntities() < 10 then
		
			io.write("Updating game state!\n")
			io.write("Number of entities: " .. engine:GetNumberOfActiveEntities() .. "\n")
			number_of_ticks_passed = 0
			
		end
	end]]--
	
end


function OnGameInit()
	engine.draw_tick_length = 30
	engine.game_logic_tick_length = 30
	entityID = engine:AddEntity("CreatePlayer")
	engine:AttachCamera(entityID)
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	engine:AddEntity("CreateDebugAsteroid")
	
	io.write("Number of entities: " .. engine:GetNumberOfActiveEntities() .. "\n")
end
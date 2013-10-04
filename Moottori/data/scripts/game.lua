number_of_ticks_passed = 100000

function OnUpdate(ticks_passed)

	number_of_ticks_passed = ticks_passed + number_of_ticks_passed

	if number_of_ticks_passed*game_logic_tick > 1000 then
		if engine:GetNumberOfActiveEntities() < 20 then
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
	engine:CreateEntityTrackingCamera(entityID)

	engine:SpawnEntity("CreateSun", -1)
	engine:SpawnEntity("CreateStar", -1)
	engine:SpawnEntity("CreateStar", -1)
	
	CreateParticlesForEmitters()
	
end

function CreateParticlesForEmitters()

	math.randomseed( os.time())
	
	for i = 0, 100 do
		local r = math.random(15) + 240
		local g = math.random(150)
		engine:AddParticle(explosion_emitter, r, g, 0)
	end
	
	for i = 0, 100 do
		local colorVal = math.random(155) + 100
		engine:AddParticle(smoke_emitter, colorVal, colorVal, colorVal)
	end

end

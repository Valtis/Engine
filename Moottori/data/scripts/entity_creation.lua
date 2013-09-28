--
function AddPlayerSprites()
	AddSprite(0, 200002, 5)
	AddSprite(1, 200003, 5)
	AddSprite(1, 200004, 5)
	AddSprite(1, 200005, 5)
end

function CreatePlayer()
	local playerX = 250
	local playerY = 250
	local collisionRadius = 25

	AddInputComponent("data/scripts/ship/ship_input.lua")
	AddLocationComponent(playerX, playerY, "data/scripts/ship/ship_location.lua")
	AddVelocityComponent("data/scripts/ship/ship_velocity.lua")
	AddAccelerationComponent("data/scripts/ship/ship_acceleration.lua")
	AddGraphicsComponent("data/scripts/generic_entity/graphics.lua")
	AddCollisionComponent(collisionRadius, "")
	AddFactionComponent(0, "data/scripts/generic_entity/faction.lua")
	AddPlayerSprites()
end


function CreateAsteroid()
	local collisionRadius = 25

	AddLocationComponent(20, 20, "data/scripts/asteroid/asteroid_location.lua")
	AddVelocityComponent("data/scripts/asteroid/asteroid_velocity.lua")
	AddGraphicsComponent("data/scripts/generic_entity/graphics.lua")
	AddCollisionComponent(collisionRadius, "data/scripts/asteroid/asteroid_collision.lua")
	AddFactionComponent(1, "data/scripts/generic_entity/faction.lua")
	AddHealthComponent("data/scripts/asteroid/asteroid_health.lua")
	AddSprite(0, 200006, 5)
end


function Initialize()
	io.write("Initializing random seed...\n")
	math.randomseed( os.time() )
end

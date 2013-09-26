
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

	AddInputComponent("data/scripts/ship_input.lua")
	AddLocationComponent(playerX, playerY, "data/scripts/location.lua")
	AddVelocityComponent("data/scripts/ship_velocity.lua")
	AddAccelerationComponent("data/scripts/ship_acceleration.lua") 
	AddGraphicsComponent("data/scripts/graphics.lua")  
	AddCollisionComponent(collisionRadius, "")	
	AddFactionComponent(0, "data/scripts/faction.lua")
	AddPlayerSprites()
end

function CreateDebugAsteroid()
	local asteroidX = 500
	local asteroidY = 500
	local collisionRadius = 25
	
	AddLocationComponent(asteroidX, asteroidY, "")
	AddGraphicsComponent("data/scripts/graphics.lua")
	AddCollisionComponent(collisionRadius, "data/scripts/asteroid_collision.lua")
	AddFactionComponent(1, "data/scripts/faction.lua")
	AddSprite(0, 200006, 5)
end


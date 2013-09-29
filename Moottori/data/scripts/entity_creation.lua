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
	AddFactionComponent(player_faction, "")
	AddSoundComponent("data/scripts/generic_entity/sound.lua")

	AddPlayerSprites()
end


function CreateAsteroid()
	local collisionRadius = 25

	AddLocationComponent(0, 0, "data/scripts/asteroid/asteroid_location.lua")
	AddVelocityComponent("data/scripts/asteroid/asteroid_velocity.lua")
	AddGraphicsComponent("data/scripts/generic_entity/graphics.lua")
	AddCollisionComponent(collisionRadius, "data/scripts/asteroid/asteroid_collision.lua")
	AddFactionComponent(asteroid_faction, "")
	AddHealthComponent("data/scripts/asteroid/asteroid_health.lua")


	AddSprite(0, 200006, 5)
end

function CreateMissile()

	local collisionRadius = 8

	AddLocationComponent(40, 40, "data/scripts/missile/missile_location.lua")
	AddVelocityComponent("data/scripts/missile/missile_velocity.lua")
	AddGraphicsComponent("data/scripts/generic_entity/graphics.lua")
	AddCollisionComponent(collisionRadius, "data/scripts/missile/missile_collision.lua")
	AddFactionComponent(player_faction, "")
	AddHealthComponent("data/scripts/missile/missile_health.lua")


	AddSprite(0, 200007, 5)
	AddSprite(0, 200008, 5)
	AddSprite(0, 200009, 5)
end

function CreateSun()
	AddLocationComponent(400, 400, "")
	AddGraphicsComponent("data/scripts/generic_entity/static_animation.lua")

	AddSprite(0, 200010, 5)
	AddSprite(0, 200011, 5)

end

function CreateStar()
	AddLocationComponent(math.random(level_width),  math.random(level_height), "")
	AddGraphicsComponent("")
	AddSprite(0, 200012, 0)
end


function Initialize()
	dofile("data/scripts/defines.lua")
	math.randomseed( os.time() )
end

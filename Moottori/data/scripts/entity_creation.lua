
function AddSprites()
	AddSprite(0, 200002, 5)
	AddSprite(1, 200003, 5)
	AddSprite(1, 200004, 5)
	AddSprite(1, 200005, 5)
end

function CreatePlayer()
	local playerX = 250
	local playerY = 250
	local collisionAreaSize = 25

	AddInputComponent("data/scripts/ship_input.lua")
	AddLocationComponent(playerX, playerY, "data/scripts/location.lua")
	AddVelocityComponent("data/scripts/ship_velocity.lua")
	AddAccelerationComponent("data/scripts/ship_acceleration.lua")
	AddGraphicsComponent("data/scripts/graphics.lua")
	AddCollisionComponent("", collisionAreaSize)	
	AddSprites()
end

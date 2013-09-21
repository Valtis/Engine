
function AddSprites()
	AddSprite(0, 200002, 5)
	AddSprite(1, 200003, 5)
	AddSprite(1, 200004, 5)
	AddSprite(1, 200005, 5)
end

function CreatePlayer()
	AddInputComponent("")
	AddLocationComponent(250, 250, "data/scripts/location.lua")
	AddVelocityComponent("data/scripts/ship_velocity.lua")
	AddAccelerationComponent("data/scripts/ship_acceleration.lua")
	AddGraphicsComponent("")
	AddSprites()
end


function OnEntityCollisionEvent(firstID, secondID)
	myFaction, wasHandledForMe = messaging:SendFactionQueryMessage()
	theirFaction, wasHandledForThem = messaging:SendFactionQueryMessageToEntity(secondID)

	if wasHandledForMe == false then
		return
	end

	if wasHandledForThem == false then
		theirFaction = -1
	end

	if myFaction ~= theirFaction then
		x, y, wasHandled = messaging:SendLocationQueryMessage()
		if wasHandled then
			engine:AddParticleEmitter(explosion_emitter, x + 25, y + 25, 250, 80, 2.0)
		end

		messaging:SendEntityTerminationRequestMessage(firstID)
	end
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_EntityCollision)
end

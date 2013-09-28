
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
		messaging:SendEntityTerminationRequestMessage(firstID)
	end	
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_EntityCollision)
end

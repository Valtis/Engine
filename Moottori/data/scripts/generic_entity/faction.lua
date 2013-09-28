
function OnFactionQuery()
	return faction_component.faction
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_QueryFaction)
end

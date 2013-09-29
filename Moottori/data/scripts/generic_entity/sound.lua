function OnPlaySoundEffect(id)
	sound_component:PlaySoundEffect(id)
end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_PlaySoundEffect)
end

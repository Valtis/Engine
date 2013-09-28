oldID = -1

function OnAnimationStateChangeEvent(animation_id, animation_state)
	graphics_component.current_animation_ID = animation_id
	graphics_component.is_animating = animation_state
	
	if oldID ~= animation_id then
		oldID = animation_id
		graphics_component:ResetSprite()
	end
end

function OnUpdate(ticks_passed)
	if graphics_component.is_animating == true then
		graphics_component:UpdateAnimationState(ticks_passed)
	end
end


function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
	component:RegisterForEvents(EventType_ChangeAnimationState)
end

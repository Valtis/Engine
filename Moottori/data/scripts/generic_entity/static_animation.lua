

function OnUpdate(ticks_passed)
	graphics_component:UpdateAnimationState(ticks_passed)
end

--[[
function OnRegisterForEvents()
	io.write("Initializing adasd")
	graphics_component.current_animation_ID = 0
	graphics_component.is_animating = true
end
]]--

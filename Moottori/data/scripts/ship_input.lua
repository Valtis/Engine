
function OnInputEvent(ui_event_type, ui_event_state)
	direction = Direction_None
	turn_direction = Direction_None

	--[[animation_id = 0 
	animation_state = false
	
	if ui_event_state == Event_State_Start then
		animation_id = 1
		animation_state = true
	end
	]]--	
	
	if ui_event_type == Key_w then
		direction = Direction_Forward
	elseif ui_event_type == Key_a then
		turn_direction = Direction_Left 
	elseif ui_event_type == Key_d then
		turn_direction = Direction_Right 
	elseif ui_event_type == Key_s then
		direction = Direction_Backward
	end		
	
	--input_component:SendAnimationStateMessage(animation_id, animation_state)
	if direction ~=Direction_None or turn_direction ~= Direction_None then
		input_component:SendAccelerationChangeMessage(direction, turn_direction, ui_event_state)
		return true
	end
		
	return false
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
end
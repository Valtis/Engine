-- TODO: export enumerations from engine to lua

-- keys
Key_w = 52
Key_a = 30
Key_s = 48
Key_d = 33


-- Directions
Direction_None = 0
Direction_Up = 1
Direction_TopRight = 2
Direction_Right = 3
Direction_BottomRight = 4
Direction_Bottom = 5
Direction_BottomLeft = 6
Direction_Left = 7
Direction_TopLeft = 8
Direction_Forward = 9
Direction_Backward = 10

-- Event state
Event_State_None = 0
Event_State_Start = 1
Event_State_Stop = 2

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
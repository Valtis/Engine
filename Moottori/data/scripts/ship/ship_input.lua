fire_counter = 0

function OnUpdate(ticks_passed)

	if fire_counter > 0 then
		fire_counter = fire_counter - 1
		if fire_counter < 0 then
			fire_counter = 0
		end
	end
end

function OnInputEvent(ui_event_type, ui_event_state)
	direction = Direction_None
	turn_direction = Direction_None

	if ui_event_type == Key_space then
		Fire()
		return true
	end

	if ui_event_type == Key_w then
		direction = Direction_Forward
	elseif ui_event_type == Key_a then
		turn_direction = Direction_Left
	elseif ui_event_type == Key_d then
		turn_direction = Direction_Right
	elseif ui_event_type == Key_s then
		direction = Direction_Backward
	end

	if direction ~=Direction_None or turn_direction ~= Direction_None then
		messaging:SendAccelerationChangeMessage(direction, turn_direction, ui_event_state)
		return true
	end

	return false
end

function OnRegisterForEvents()
	dofile('data/scripts/defines.lua')
end




function Fire()
	if fire_counter == 0 then
		engine:SpawnEntity("CreateMissile", entity:GetID())
		fire_counter = 600/game_logic_tick
		engine:PlaySoundEffect(0)
		return
	end
end

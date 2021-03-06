--constants

game_logic_tick = 30
game_draw_tick = 30


player_faction = 0
asteroid_faction = 1

explosion_emitter = 0
smoke_emitter = 1

-- level size
level_width = 800
level_height = 800


-- key values
Key_w = 1000
Key_a = 1002
Key_s = 1001
Key_d = 1003
Key_space = 1004

-- event states
Event_State_None = 0
Event_State_Start = 1
Event_State_Stop = 2


--directions

Direction_None = 0
Direction_Top = 1
Direction_TopRight = 2
Direction_Right = 3
Direction_BottomRight = 4
Direction_Bottom = 5
Direction_BottomLeft = 6
Direction_Left = 7
Direction_TopLeft = 8
Direction_Forward = 9
Direction_Backward = 10

--event types

EventType_None = 0
EventType_UIEvent = 1
EventType_QueryLocation = 2
EventType_QueryDirection = 3
EventType_QueryFaction = 4
EventType_ChangeAcceleration = 5
EventType_ChangeVelocity = 6
EventType_ChangeLocation = 7
EventType_ChangeAnimationState = 8
EventType_RequestTermination = 9
EventType_BoundaryCollision = 10
EventType_EntityCollision = 11
EventType_SpawnEntity = 12
EventType_ParentIDNotification = 13
EventType_PlaySoundEffect = 14

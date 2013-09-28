-- level size
level_width = 1920
level_height = 1080


-- key values
Key_w = 52
Key_a = 30
Key_s = 48
Key_d = 33

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

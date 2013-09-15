#pragma once

enum class ComponentType : int { None, Input, Acceleration, Velocity, Location, Graphics };

enum class EventType : int { None, UIEvent, ChangeAcceleration, ChangeVelocity, ChangeLocation };
enum class UIEventType: int { None, Quit, MoveUp, MoveDown, MoveLeft, MoveRight, RotateLeft, RotateRight };

enum class Direction : int { None, Up, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, TopLeft };
#pragma once

enum class ComponentType : int { None, Input, Acceleration, Velocity, Location, Graphics };

enum class ControllerType : int {None, Keyboard };

enum class EventType : int { None, UIEvent, QueryDirection, ChangeAcceleration, ChangeVelocity, ChangeLocation };
enum class UIEventType: int { None, Quit, MoveForward, MoveBackwards, MoveUp, MoveDown, MoveLeft, MoveRight, RotateLeft, RotateRight };
enum class UIEventState : int {None, Start, Stop };

enum class Direction : int { None, Up, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, TopLeft, Forward, Backward };
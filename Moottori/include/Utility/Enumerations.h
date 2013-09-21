#pragma once

enum class ComponentType : int { None, Input, Acceleration, Velocity, Location, Graphics, Collision, Hitpoints };

enum class ControllerType : int { None, Keyboard };
enum class UIEventState : int {None, Start, Stop };
enum class Direction : int { None, Top, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, TopLeft, Forward, Backward };

enum class EventType : int { None, UIEvent, QueryDirection, ChangeAcceleration, ChangeVelocity, ChangeLocation, ChangeAnimationState, BoundaryCollision };

enum class UIEventType: int { None, Quit, Reserved28, Reserved27, Reserved26, Reserved25, Reserved24, Reserved23, Reserved22, Reserved21, Reserved20, Reserved19, Reserved18, Reserved17, Reserved16, Reserved15,
		Reserved14, Reserved13, Reserved12, Reserved11, Reserved10, Reserved9, Reserved8, Reserved7, Reserved6, Reserved5, Reserved4, Reserved3, Reserved2, Reserved1,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_NUMPAD_0,
		KEY_NUMPAD_1,
		KEY_NUMPAD_2,
		KEY_NUMPAD_3,
		KEY_NUMPAD_4,
		KEY_NUMPAD_5,
		KEY_NUMPAD_6,
		KEY_NUMPAD_7,
		KEY_NUMPAD_8,
		KEY_NUMPAD_9,
		KEY_NUMPAD_DIV,
		KEY_NUMPAD_MUL,
		KEY_NUMPAD_MINUS,
		KEY_NUMPAD_PLUS,
		KEY_NUMPAD_ENTER,
		KEY_ENTER,
		KEY_LEFT_CONTROL,
		KEY_LEFT_SHIFT,
		KEY_LEFT_ALT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_ALT,
		KEY_SPACE,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT

		};
		
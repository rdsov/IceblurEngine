// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

#include "Math/VMath.h"
#include "Event/IEvent.h"

#include <GLFW/glfw3.h>

#define ICE_KEY_PRESS GLFW_PRESS
#define ICE_KEY_RELEASE GLFW_RELEASE
#define ICE_KEY_HOLD GLFW_REPEAT

namespace Iceblur
{
	struct KeyAction
	{
		KeyAction(int keycode = 0, int actionType = ICE_KEY_PRESS, const std::function<void()>& trigger = { })
				: key(keycode), action(actionType), function(trigger)
		{
		}

		//Function that gets triggered.
		std::function<void()> function;

		//Key that has to be pressed.
		int key;

		//Currently, there are only 3 actions: ICE_KEY_PRESS, ICE_KEY_HOLD, ICE_KEY_RELEASE
		int action;

		bool operator==(const KeyAction& keyAction) const
		{
			return keyAction.key == key && keyAction.action == action;
		}

	private:
		bool holding = false;
		bool used = false;

		friend class InputManager;
	};

	struct ScrollWheelAction
	{
		void (* function)(double xOffset, double yOffset);

		int xAxis = 0;
		int yAxis = 0;
	};

	enum class EInputMode
	{
		Default,
		Game
	};

	struct Window;

	class ICE_API InputManager
	{
	public:
		static void Initialize();

		//Adds an IBindableInput object to a queue, which gets iterated through on Initialize() to call the BindInput() function
		//static void AddToBindQueue(IBindableInput* object);

		static void BindKey(int key, int action);

		static void BindKey(const KeyAction& keyAction);

		static void BindShortcut(int modifierKey, int otherKey);

		static void BindScrollWheel(const ScrollWheelAction& action);

		//Hides or shows the cursor
		static void SetInputMode(const EInputMode& mode);

		static V2D GetMousePosition();

		static bool GetMouseVisibility()
		{ return m_MouseVisible; }

		//Check the state of any bound key
		static bool GetKeyAction(int key, int action);

		//Check the state of any bound shortcut
		static bool GetShortcut(int modifierKey, int otherKey);

		//Has to be called every frame
		static void Update();

	private:
		static void OnKeyPressed(IceEventFn e);

		static void OnMouseButtonPressed(IceEventFn e);

		static void OnMouseMoved(IceEventFn e);

		static void OnMouseScrolled(IceEventFn e);

		static std::vector<KeyAction> m_KeyBinds;
		static std::vector<KeyAction> m_HoldBinds;
		static std::vector<KeyAction> m_ActiveKeyBinds;
		static std::vector<ScrollWheelAction> m_ScrollWheelBinds;
		//static std::vector<IBindableInput*> m_BindInputQueue;

		static V2D m_MousePosition;
		static bool m_MouseVisible;

		friend class Win64Window;
	};
}

#define ICE_KEY_SPACE         GLFW_KEY_SPACE
#define ICE_KEY_APOSTROPHE    GLFW_KEY_APOSTROPHE
#define ICE_KEY_COMMA         GLFW_KEY_COMMA
#define ICE_KEY_MINUS         GLFW_KEY_MINUS
#define ICE_KEY_PERIOD        GLFW_KEY_PERIOD
#define ICE_KEY_SLASH         GLFW_KEY_SLASH
#define ICE_KEY_0             GLFW_KEY_0
#define ICE_KEY_1             GLFW_KEY_1
#define ICE_KEY_2             GLFW_KEY_2
#define ICE_KEY_3             GLFW_KEY_3
#define ICE_KEY_4             GLFW_KEY_4
#define ICE_KEY_5             GLFW_KEY_5
#define ICE_KEY_6             GLFW_KEY_6
#define ICE_KEY_7             GLFW_KEY_7
#define ICE_KEY_8             GLFW_KEY_8
#define ICE_KEY_9             GLFW_KEY_9
#define ICE_KEY_SEMICOLON     GLFW_KEY_SEMICOLON
#define ICE_KEY_EQUAL         GLFW_KEY_EQUAL
#define ICE_KEY_A             GLFW_KEY_A
#define ICE_KEY_B             GLFW_KEY_B
#define ICE_KEY_C             GLFW_KEY_C
#define ICE_KEY_D             GLFW_KEY_D
#define ICE_KEY_E             GLFW_KEY_E
#define ICE_KEY_F             GLFW_KEY_F
#define ICE_KEY_G             GLFW_KEY_G
#define ICE_KEY_H             GLFW_KEY_H
#define ICE_KEY_I             GLFW_KEY_I
#define ICE_KEY_J             GLFW_KEY_J
#define ICE_KEY_K             GLFW_KEY_K
#define ICE_KEY_L             GLFW_KEY_L
#define ICE_KEY_M             GLFW_KEY_M
#define ICE_KEY_N             GLFW_KEY_N
#define ICE_KEY_O             GLFW_KEY_O
#define ICE_KEY_P             GLFW_KEY_P
#define ICE_KEY_Q             GLFW_KEY_Q
#define ICE_KEY_R             GLFW_KEY_R
#define ICE_KEY_S             GLFW_KEY_S
#define ICE_KEY_T             GLFW_KEY_T
#define ICE_KEY_U             GLFW_KEY_U
#define ICE_KEY_V             GLFW_KEY_V
#define ICE_KEY_W             GLFW_KEY_W
#define ICE_KEY_X             GLFW_KEY_X
#define ICE_KEY_Y             GLFW_KEY_Y
#define ICE_KEY_Z             GLFW_KEY_Z
#define ICE_KEY_LEFT_BRACKET  GLFW_KEY_LEFT_BRACKET
#define ICE_KEY_BACKSLASH     GLFW_KEY_BACKSLASH
#define ICE_KEY_RIGHT_BRACKET GLFW_KEY_RIGHT_BRACKET
#define ICE_KEY_GRAVE_ACCENT  GLFW_KEY_GRAVE_ACCENT
#define ICE_KEY_WORLD_1       GLFW_KEY_WORLD_1
#define ICE_KEY_WORLD_2       GLFW_KEY_WORLD_2

#define ICE_KEY_ESCAPE        GLFW_KEY_ESCAPE
#define ICE_KEY_ENTER         GLFW_KEY_ENTER
#define ICE_KEY_TAB           GLFW_KEY_TAB
#define ICE_KEY_BACKSPACE     GLFW_KEY_BACKSPACE
#define ICE_KEY_INSERT        GLFW_KEY_INSERT
#define ICE_KEY_DELETE        GLFW_KEY_DELETE
#define ICE_KEY_RIGHT         GLFW_KEY_RIGHT
#define ICE_KEY_LEFT          GLFW_KEY_LEFT
#define ICE_KEY_DOWN          GLFW_KEY_DOWN
#define ICE_KEY_UP            GLFW_KEY_UP
#define ICE_KEY_PAGE_UP       GLFW_KEY_PAGE_UP
#define ICE_KEY_PAGE_DOWN     GLFW_KEY_PAGE_DOWN
#define ICE_KEY_HOME          GLFW_KEY_HOME
#define ICE_KEY_END           GLFW_KEY_END
#define ICE_KEY_CAPS_LOCK     GLFW_KEY_CAPS_LOCK
#define ICE_KEY_SCROLL_LOCK   GLFW_KEY_SCROLL_LOCK
#define ICE_KEY_NUM_LOCK      GLFW_KEY_NUM_LOCK
#define ICE_KEY_PRINT_SCREEN  GLFW_KEY_PRINT_SCREEN
#define ICE_KEY_PAUSE         GLFW_KEY_PAUSE
#define ICE_KEY_F1            GLFW_KEY_F1
#define ICE_KEY_F2            GLFW_KEY_F2
#define ICE_KEY_F3            GLFW_KEY_F3
#define ICE_KEY_F4            GLFW_KEY_F4
#define ICE_KEY_F5            GLFW_KEY_F5
#define ICE_KEY_F6            GLFW_KEY_F6
#define ICE_KEY_F7            GLFW_KEY_F7
#define ICE_KEY_F8            GLFW_KEY_F8
#define ICE_KEY_F9            GLFW_KEY_F9
#define ICE_KEY_F10           GLFW_KEY_F10
#define ICE_KEY_F11           GLFW_KEY_F11
#define ICE_KEY_F12           GLFW_KEY_F12
#define ICE_KEY_F13           GLFW_KEY_F13
#define ICE_KEY_F14           GLFW_KEY_F14
#define ICE_KEY_F15           GLFW_KEY_F15
#define ICE_KEY_F16           GLFW_KEY_F16
#define ICE_KEY_F17           GLFW_KEY_F17
#define ICE_KEY_F18           GLFW_KEY_F18
#define ICE_KEY_F19           GLFW_KEY_F19
#define ICE_KEY_F20           GLFW_KEY_F20
#define ICE_KEY_F21           GLFW_KEY_F21
#define ICE_KEY_F22           GLFW_KEY_F22
#define ICE_KEY_F23           GLFW_KEY_F23
#define ICE_KEY_F24           GLFW_KEY_F24
#define ICE_KEY_F25           GLFW_KEY_F25
#define ICE_KEY_KP_0          GLFW_KEY_KP_0
#define ICE_KEY_KP_1          GLFW_KEY_KP_1
#define ICE_KEY_KP_2          GLFW_KEY_KP_2
#define ICE_KEY_KP_3          GLFW_KEY_KP_3
#define ICE_KEY_KP_4          GLFW_KEY_KP_4
#define ICE_KEY_KP_5          GLFW_KEY_KP_5
#define ICE_KEY_KP_6          GLFW_KEY_KP_6
#define ICE_KEY_KP_7          GLFW_KEY_KP_7
#define ICE_KEY_KP_8          GLFW_KEY_KP_8
#define ICE_KEY_KP_9          GLFW_KEY_KP_9
#define ICE_KEY_KP_DECIMAL    GLFW_KEY_KP_DECIMAL
#define ICE_KEY_KP_DIVIDE     GLFW_KEY_KP_DIVIDE
#define ICE_KEY_KP_MULTIPLY   GLFW_KEY_KP_MULTIPLY
#define ICE_KEY_KP_SUBTRACT   GLFW_KEY_KP_SUBTRACT
#define ICE_KEY_KP_ADD        GLFW_KEY_KP_ADD
#define ICE_KEY_KP_ENTER      GLFW_KEY_KP_ENTER
#define ICE_KEY_KP_EQUAL      GLFW_KEY_KP_EQUAL
#define ICE_KEY_LEFT_SHIFT    GLFW_KEY_LEFT_SHIFT
#define ICE_KEY_LEFT_CONTROL  GLFW_KEY_LEFT_CONTROL
#define ICE_KEY_LEFT_ALT      GLFW_KEY_LEFT_ALT
#define ICE_KEY_LEFT_SUPER    GLFW_KEY_LEFT_SUPER
#define ICE_KEY_RIGHT_SHIFT   GLFW_KEY_RIGHT_SHIFT
#define ICE_KEY_RIGHT_CONTROL GLFW_KEY_RIGHT_CONTROL
#define ICE_KEY_RIGHT_ALT     GLFW_KEY_RIGHT_ALT
#define ICE_KEY_RIGHT_SUPER   GLFW_KEY_RIGHT_SUPER
#define ICE_KEY_MENU          GLFW_KEY_MENU

#define ICE_MOUSE_BUTTON_1      GLFW_MOUSE_BUTTON_1
#define ICE_MOUSE_BUTTON_2      GLFW_MOUSE_BUTTON_2
#define ICE_MOUSE_BUTTON_3      GLFW_MOUSE_BUTTON_3
#define ICE_MOUSE_BUTTON_4      GLFW_MOUSE_BUTTON_4
#define ICE_MOUSE_BUTTON_5      GLFW_MOUSE_BUTTON_5
#define ICE_MOUSE_BUTTON_6      GLFW_MOUSE_BUTTON_6
#define ICE_MOUSE_BUTTON_7      GLFW_MOUSE_BUTTON_7
#define ICE_MOUSE_BUTTON_8      GLFW_MOUSE_BUTTON_8
#define ICE_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_LAST
#define ICE_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_LEFT
#define ICE_MOUSE_BUTTON_RIGHT  GLFW_MOUSE_BUTTON_RIGHT
#define ICE_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE

#define ICE_JOYSTICK_1    GLFW_JOYSTICK_1
#define ICE_JOYSTICK_2    GLFW_JOYSTICK_2
#define ICE_JOYSTICK_3    GLFW_JOYSTICK_3
#define ICE_JOYSTICK_4    GLFW_JOYSTICK_4
#define ICE_JOYSTICK_5    GLFW_JOYSTICK_5
#define ICE_JOYSTICK_6    GLFW_JOYSTICK_6
#define ICE_JOYSTICK_7    GLFW_JOYSTICK_7
#define ICE_JOYSTICK_8    GLFW_JOYSTICK_8
#define ICE_JOYSTICK_9    GLFW_JOYSTICK_9
#define ICE_JOYSTICK_10   GLFW_JOYSTICK_10
#define ICE_JOYSTICK_11   GLFW_JOYSTICK_11
#define ICE_JOYSTICK_12   GLFW_JOYSTICK_12
#define ICE_JOYSTICK_13   GLFW_JOYSTICK_13
#define ICE_JOYSTICK_14   GLFW_JOYSTICK_14
#define ICE_JOYSTICK_15   GLFW_JOYSTICK_15
#define ICE_JOYSTICK_16   GLFW_JOYSTICK_16
#define ICE_JOYSTICK_LAST GLFW_JOYSTICK_LAST

#define ICE_GAMEPAD_BUTTON_A            GLFW_GAMEPAD_BUTTON_A
#define ICE_GAMEPAD_BUTTON_B            GLFW_GAMEPAD_BUTTON_B
#define ICE_GAMEPAD_BUTTON_X            GLFW_GAMEPAD_BUTTON_X
#define ICE_GAMEPAD_BUTTON_Y            GLFW_GAMEPAD_BUTTON_Y
#define ICE_GAMEPAD_BUTTON_LEFT_BUMPER  GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
#define ICE_GAMEPAD_BUTTON_RIGHT_BUMPER GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
#define ICE_GAMEPAD_BUTTON_BACK         GLFW_GAMEPAD_BUTTON_BACK
#define ICE_GAMEPAD_BUTTON_START        GLFW_GAMEPAD_BUTTON_START
#define ICE_GAMEPAD_BUTTON_GUIDE        GLFW_GAMEPAD_BUTTON_GUIDE
#define ICE_GAMEPAD_BUTTON_LEFT_THUMB   GLFW_GAMEPAD_BUTTON_LEFT_THUMB
#define ICE_GAMEPAD_BUTTON_RIGHT_THUMB  GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
#define ICE_GAMEPAD_BUTTON_DPAD_UP      GLFW_GAMEPAD_BUTTON_DPAD_UP
#define ICE_GAMEPAD_BUTTON_DPAD_RIGHT   GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
#define ICE_GAMEPAD_BUTTON_DPAD_DOWN    GLFW_GAMEPAD_BUTTON_DPAD_DOWN
#define ICE_GAMEPAD_BUTTON_DPAD_LEFT    GLFW_GAMEPAD_BUTTON_DPAD_LEFT
#define ICE_GAMEPAD_BUTTON_LAST         GLFW_GAMEPAD_BUTTON_LAST

#define ICE_GAMEPAD_BUTTON_CROSS        GLFW_GAMEPAD_BUTTON_CROSS
#define ICE_GAMEPAD_BUTTON_CIRCLE       GLFW_GAMEPAD_BUTTON_CIRCLE
#define ICE_GAMEPAD_BUTTON_SQUARE       GLFW_GAMEPAD_BUTTON_SQUARE
#define ICE_GAMEPAD_BUTTON_TRIANGLE     GLFW_GAMEPAD_BUTTON_TRIANGLE

#define ICE_GAMEPAD_AXIS_LEFT_X        GLFW_GAMEPAD_AXIS_LEFT_X
#define ICE_GAMEPAD_AXIS_LEFT_Y        GLFW_GAMEPAD_AXIS_LEFT_Y
#define ICE_GAMEPAD_AXIS_RIGHT_X       GLFW_GAMEPAD_AXIS_RIGHT_X
#define ICE_GAMEPAD_AXIS_RIGHT_Y       GLFW_GAMEPAD_AXIS_RIGHT_Y
#define ICE_GAMEPAD_AXIS_LEFT_TRIGGER  GLFW_GAMEPAD_AXIS_LEFT_TRIGGER
#define ICE_GAMEPAD_AXIS_RIGHT_TRIGGER GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
#define ICE_GAMEPAD_AXIS_LAST          GLFW_GAMEPAD_AXIS_LAST

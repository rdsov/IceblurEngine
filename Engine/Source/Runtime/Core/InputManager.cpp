// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "InputManager.h"

#include "Window.h"
#include "WindowManager.h"
#include "Event/EventSystem.h"
#include "CoreUtils.h"

namespace Iceblur
{
	std::vector<KeyAction> InputManager::m_HoldBinds;
	std::vector<KeyAction> InputManager::m_KeyBinds;
	std::vector<KeyAction> InputManager::m_ActiveKeyBinds;
	std::vector<ScrollWheelAction> InputManager::m_ScrollWheelBinds;
	//std::vector<IBindableInput*> InputManager::m_BindInputQueue;
	Vec2 InputManager::m_MousePosition;

	bool InputManager::m_MouseVisible;

	void InputManager::Initialize()
	{
		/*for (const auto& object : m_BindInputQueue)
		{
			object->BindInput();
		}*/

		//Clean up as this won't be used anymore
		//m_BindInputQueue.clear();

		EventSystem::Subscribe(KeyEvent::type, &OnKeyPressed);
		EventSystem::Subscribe(MouseButtonEvent::type, &OnMouseButtonPressed);
		EventSystem::Subscribe(MouseMoveEvent::type, &OnMouseMoved);
		EventSystem::Subscribe(MouseScrollEvent::type, &OnMouseScrolled);
	}

	/*void InputManager::AddToBindQueue(IBindableInput* object)
	{
		m_BindInputQueue.emplace_back(object);
	}*/

	void InputManager::BindKey(int key, int action)
	{
		BindKey(KeyAction(key, action));
	}

	void InputManager::BindKey(const KeyAction& keyAction)
	{
		if (keyAction.action == ICE_HOLD)
		{
			m_HoldBinds.emplace_back(keyAction);
		}
		else
		{
			m_KeyBinds.emplace_back(keyAction);
		}
	}

	void InputManager::BindShortcut(int modifierKey, int otherKey)
	{
		if (std::find(m_HoldBinds.begin(), m_HoldBinds.end(), KeyAction(modifierKey, ICE_HOLD)) == m_HoldBinds.end())
		{
			BindKey(modifierKey, ICE_HOLD);
		}

		BindKey(otherKey, ICE_PRESS);
	}

	void InputManager::BindScrollWheel(const ScrollWheelAction& action)
	{
		m_ScrollWheelBinds.emplace_back(action);
	}

	void InputManager::SetInputMode(const EInputMode& mode)
	{
		if (mode == EInputMode::Default)
		{
			m_MouseVisible = true;
			glfwSetInputMode((GLFWwindow*) WindowManager::GetHost()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (glfwRawMouseMotionSupported())
			{
				glfwSetInputMode((GLFWwindow*) WindowManager::GetHost()->GetNativeWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			}
		}
		else if (mode == EInputMode::Game)
		{
			m_MouseVisible = false;
			glfwSetInputMode((GLFWwindow*) WindowManager::GetHost()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported())
			{
				glfwSetInputMode((GLFWwindow*) WindowManager::GetHost()->GetNativeWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
		}
	}

	void InputManager::OnKeyPressed(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, KeyEvent);

		//Check if current key is found in bound keys registry
		for (auto& bind : m_KeyBinds)
		{
			if (event.GetKey() == bind.key)
			{
				if (event.GetAction() == bind.action)
				{
					if (FIND_NOT_IN_VECTOR(m_ActiveKeyBinds, bind))
					{
						m_ActiveKeyBinds.emplace_back(bind);
					}

					try
					{
						bind.function();
					} catch (std::bad_function_call bfc)
					{
						ICE_ERROR("Bad function call!");
					}
				}
				else
				{
					auto it = std::remove(m_ActiveKeyBinds.begin(), m_ActiveKeyBinds.end(), bind);

					if (it != m_ActiveKeyBinds.end())
					{
						m_ActiveKeyBinds.erase(it);
					}

					if (bind.used)
					{
						bind.used = false;
					}
				}
			}
		}

		for (auto& bind : m_HoldBinds)
		{
			if (event.GetKey() == bind.key)
			{
				if (event.GetAction() == ICE_PRESS)
				{
					bind.holding = true;
				}
				else if (event.GetAction() == ICE_RELEASE)
				{
					bind.holding = false;
				}
			}
		}
	}

	void InputManager::OnMouseButtonPressed(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, MouseButtonEvent);
		for (auto& bind : m_KeyBinds)
		{
			if (event.GetButton() == bind.key)
			{
				if (event.GetAction() == bind.action)
				{
					if (FIND_NOT_IN_VECTOR(m_ActiveKeyBinds, bind))
					{
						m_ActiveKeyBinds.emplace_back(bind);
					}

					try
					{
						bind.function();
					} catch (std::bad_function_call bfc)
					{
						ICE_ERROR("Bad function call!");
					}
				}
				else
				{
					auto it = std::remove(m_ActiveKeyBinds.begin(), m_ActiveKeyBinds.end(), bind);

					if (it != m_ActiveKeyBinds.end())
					{
						m_ActiveKeyBinds.erase(it);
					}

					if (bind.used)
					{
						bind.used = false;
					}
				}
			}
		}

		for (auto& bind : m_HoldBinds)
		{
			if (event.GetButton() == bind.key)
			{
				if (event.GetAction() == ICE_PRESS)
				{
					bind.holding = true;
				}
				else if (event.GetAction() == ICE_RELEASE)
				{
					bind.holding = false;
				}
			}
		}
	}

	void InputManager::OnMouseMoved(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, MouseMoveEvent);
		m_MousePosition = Vec2(event.GetX(), event.GetY());
	}

	void InputManager::OnMouseScrolled(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, MouseScrollEvent);
		for (auto const& action : m_ScrollWheelBinds)
		{
			action.function(event.GetXDelta(), event.GetYDelta());
		}
	}

	Vec2 InputManager::GetMousePosition()
	{
		return m_MousePosition;
	}

	bool InputManager::GetKeyAction(int key, int action)
	{
		if (action == ICE_HOLD)
		{
			for (auto const& bind : m_HoldBinds)
			{
				if (key == bind.key && bind.holding)
				{
					return true;
				}
			}
		}
		else
		{
			for (auto& bind : m_ActiveKeyBinds)
			{
				if (bind.key == key && bind.action == action)
				{
					if (!bind.used)
					{
						bind.used = true;
						return true;
					}
				}
			}
		}

		return false;
	}

	bool InputManager::GetShortcut(int modifierKey, int otherKey)
	{
		bool modifierPressed = false;
		bool otherKeyPressed = false;

		for (auto const& bind : m_HoldBinds)
		{
			if (modifierKey == bind.key && bind.holding) modifierPressed = true;
		}

		for (auto& bind : m_ActiveKeyBinds)
		{
			if (bind.key == otherKey && bind.action == ICE_PRESS)
			{
				if (!bind.used)
				{
					bind.used = true;
					otherKeyPressed = true;
				}
			}
		}

		return modifierPressed && otherKeyPressed;
	}

	void InputManager::Update()
	{
		for (auto const& key : m_HoldBinds)
		{
			if (key.holding && key.function != nullptr)
			{
				try
				{
					key.function();
				} catch (std::bad_function_call bfc)
				{
					ICE_ERROR("Bad function call!");
				}
			}
		}
	}
}

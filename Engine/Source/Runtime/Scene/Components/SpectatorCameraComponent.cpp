// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "SpectatorCameraComponent.h"

#include "Core/InputManager.h"

#include "Scene/Entity.h"
#include "TransformComponent.h"

namespace Iceblur
{
	SpectatorCameraComponent::SpectatorCameraComponent()
	{
		m_Transform = new TransformComponent();
	}

	void SpectatorCameraComponent::Init()
	{
		InputManager::BindKey(ICE_KEY_W, ICE_KEY_HOLD);
		InputManager::BindKey(ICE_KEY_S, ICE_KEY_HOLD);
		InputManager::BindKey(ICE_KEY_A, ICE_KEY_HOLD);
		InputManager::BindKey(ICE_KEY_D, ICE_KEY_HOLD);
		InputManager::BindKey(ICE_KEY_Q, ICE_KEY_HOLD);
		InputManager::BindKey(ICE_KEY_E, ICE_KEY_HOLD);
	}

	void SpectatorCameraComponent::Update(float deltaTime)
	{
		CameraComponent::Update(deltaTime);

		glm::vec3 target = glm::vec3(0.0f);

		if (InputManager::GetKeyAction(ICE_KEY_W, ICE_KEY_HOLD))
		{
			target += m_Front;
		}

		if (InputManager::GetKeyAction(ICE_KEY_S, ICE_KEY_HOLD))
		{
			target -= m_Front;
		}

		if (InputManager::GetKeyAction(ICE_KEY_A, ICE_KEY_HOLD))
		{
			target -= glm::cross(m_Front, m_Up);
		}

		if (InputManager::GetKeyAction(ICE_KEY_D, ICE_KEY_HOLD))
		{
			target += glm::cross(m_Front, m_Up);
		}

		if (InputManager::GetKeyAction(ICE_KEY_Q, ICE_KEY_HOLD))
		{
			target -= m_Up;
		}

		if (InputManager::GetKeyAction(ICE_KEY_E, ICE_KEY_HOLD))
		{
			target += m_Up;
		}

		if (target != glm::vec3(0.0f))
		{
			m_TargetPosition += glm::normalize(target) * m_Speed * 0.01f;
		}

		m_Position = glm::mix(m_Position, m_TargetPosition, deltaTime * 10.0f);

		float x = (InputManager::GetMousePosition().GetX() - m_LastMouse.GetX()) * m_MouseSensitivity * deltaTime;
		float y = (m_LastMouse.GetY() - InputManager::GetMousePosition().GetY()) * m_MouseSensitivity * deltaTime;

		Rotate(x, y);

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

		m_LastMouse.SetX(InputManager::GetMousePosition().GetX());
		m_LastMouse.SetY(InputManager::GetMousePosition().GetY());
	}

	void SpectatorCameraComponent::Rotate(float x, float y)
	{
		m_Yaw += x;
		m_Pitch += y;

		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}

		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
	}
}

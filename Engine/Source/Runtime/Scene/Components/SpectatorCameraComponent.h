// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "CameraComponent.h"
#include "Math/VMath.h"

namespace Iceblur
{
	//Acts like a normal camera but with the ability to move around.
	//The movement behaviour can be changed by overriding the Update() function.
	class ICE_API SpectatorCameraComponent : public CameraComponent
	{
	public:
		ICE_COMPONENT_DECL(SpectatorCameraComponent, false)

		SpectatorCameraComponent()
		{
		}

		//Sets the necessary input bindings.
		virtual void SetupInput();

		virtual void Update(float deltaTime) override;

		const float GetMouseSensitivity() const
		{
			return m_MouseSensitivity;
		}

		void SetMouseSensitivity(float value)
		{
			if (m_MouseSensitivity >= 0.0f)
			{
				m_MouseSensitivity = value;
			}
		}

		const float GetCameraSpeed() const
		{
			return m_Speed;
		}

		void SetCameraSpeed(float value)
		{
			if (value >= 0.0f)
			{
				m_Speed = value;
			}
		}

		//Returns whether the camera can move around.
		const bool IsMovementLocked() const
		{
			return m_LockMovement;
		}

		//If set to true, the spectator will not be able to move around.
		void SetMovementLocked(bool value)
		{
			m_LockMovement = value;
		}

		//Returns whether the camera can look around.
		const bool IsCameraLocked() const
		{
			return m_LockCamera;
		}

		//If set to true, the spectator will not be able to look around.
		void SetCameraLocked(bool value)
		{
			m_LockCamera = value;
		}

		const glm::vec3 GetPosition() const
		{
			return m_Position;
		}

		const glm::vec3 GetRotation() const
		{
			return glm::vec3(m_Yaw, m_Pitch, 0.0f);
		}

	protected:
		void UpdateCameraComponent(float deltaTime);

		//Manipulate this if you want to change the movement behaviour.
		virtual void Move(float deltaTime);

		//Manipulate this if you want to change the camera look behaviour.
		virtual void Rotate(float x, float y);

	protected:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_TargetPosition = glm::vec3(0.0f);
		glm::vec3 m_Front = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		V2D m_LastMouse;

		float m_MouseSensitivity = 40.0f;
		float m_Speed = 3.0f;

		bool m_LockMovement = false;
		bool m_LockCamera = false;
	};
}

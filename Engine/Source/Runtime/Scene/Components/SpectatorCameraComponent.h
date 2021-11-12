// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "CameraComponent.h"
#include "Math/VMath.h"

namespace Iceblur
{
	class TransformComponent;

	//Acts like a normal camera but with the ability to move around.
	//The movement behaviour can be changed by overriding the Update() function.
	class SpectatorCameraComponent : public CameraComponent
	{
	public:
		ICE_COMPONENT_DECL(SpectatorCameraComponent, false)

		SpectatorCameraComponent();

		TransformComponent* Transform() const
		{
			return m_Transform;
		}

		void Init();

		virtual void Update(float deltaTime) override;

		const float GetMouseSensitivity()
		{
			return m_MouseSensitivity;
		}

		void SetMouseSensitivity(float value)
		{
			if (m_MouseSensitivity > 0.0f)
			{
				m_MouseSensitivity = value;
			}
		}

	protected:
		void Rotate(float x, float y);

	protected:
		TransformComponent* m_Transform;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_TargetPosition = glm::vec3(0.0f);
		glm::vec3 m_Front = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		V2D m_LastMouse;

		float m_MouseSensitivity = 40.0f;
		float m_Speed = 3.0f;
	};
}

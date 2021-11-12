// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "CameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/WindowManager.h"
#include "Platform/Windows/Win64Window.h"

namespace Iceblur
{
	CameraComponent::CameraComponent(float fov, const EProjectionType& type, float near, float far)
			: m_FOV(fov), m_Near(near), m_Far(far), m_ProjectionType(type)
	{
		m_View = glm::mat4(1.0f);
		m_Projection = glm::perspective(fov, 16.f / 9.f, near, far);
	}

	void CameraComponent::Update(float deltaTime)
	{
		auto window = (Win64Window*) WindowManager::GetHost();
		//float aspect = window->GetSize().GetAspectRatio();

		m_Projection = glm::perspective(glm::radians(m_FOV), 16.0f / 9.0f, m_Near, m_Far);
	}

	void CameraComponent::SetFOV(float fov)
	{
		if (fov > 0.0f)
		{
			m_FOV = fov;
		}
	}
}

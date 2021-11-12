// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Scene/Component.h"

#include <glm/glm.hpp>

namespace Iceblur
{
	enum class EProjectionType
	{
		Perspective,
		Orthographic
	};

	class ICE_API CameraComponent : public Component
	{
	public:
		ICE_COMPONENT_DECL(CameraComponent, false);

		//FIXME: Currently there is only perspective support
		CameraComponent(float fov = 90.0f, const EProjectionType& type = EProjectionType::Perspective, float near = 0.01f, float far = 100.0f);

		~CameraComponent()
		{
		}

		virtual void Update(float deltaTime);

		const float& GetFOV()
		{
			return m_FOV;
		}

		void SetFOV(float fov);

		const EProjectionType& GetProjectionType()
		{
			return m_ProjectionType;
		}

		void SetProjectionType(const EProjectionType& type)
		{
			m_ProjectionType = type;
		}

		const glm::mat4& GetProjectionMatrix()
		{
			return m_Projection;
		}

		const glm::mat4& GetViewMatrix()
		{
			return m_View;
		}

		float m_Depth = 0;

	protected:
		float m_FOV;
		float m_Near;
		float m_Far;

		EProjectionType m_ProjectionType;

		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}

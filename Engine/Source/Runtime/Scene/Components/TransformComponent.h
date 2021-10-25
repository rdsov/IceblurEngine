// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Scene/Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Iceblur
{
	//Stores information like position, rotation and scale of an entity.
	class ICE_API TransformComponent : public Component
	{
	public:
		ICE_COMPONENT_DECL(TransformComponent, true);

		TransformComponent(float x = 0, float y = 0, float z = 0)
				: m_Position(glm::vec3(x, y, z))
		{
			GenerateUniqueId();
		}

		TransformComponent(const glm::vec3& position)
				: m_Position(position)
		{
			GenerateUniqueId();
		}

		TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale = glm::vec3(1.0f))
				: m_Position(position), m_Rotation(rotation), m_Scale(scale)
		{
			GenerateUniqueId();
		}

		inline void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
		}

		inline const glm::vec3 GetPosition() const
		{
			return m_Position;
		}

		inline void SetRotation(const glm::vec3& rotation)
		{
			m_Rotation = rotation;
		}

		inline const glm::vec3 GetRotation() const
		{
			return m_Rotation;
		}

		inline void SetScale(const glm::vec3& scale)
		{
			m_Scale = scale;
		}

		inline const glm::vec3 GetScale() const
		{
			return m_Scale;
		}

		inline const glm::mat4 GetTransformMatrix() const
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, m_Position);
			transform = glm::scale(transform, m_Scale);
			return transform;
		}

	private:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
	};
}

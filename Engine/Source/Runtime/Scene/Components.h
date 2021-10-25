// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/Identifiable.h"

#include <glm/glm.hpp>

#define ICE_COMPONENT_DECL(ComponentType) \
const std::string GetName() override { return #ComponentType; }

namespace Iceblur
{
	class Entity;

	//-----------------BASE COMPONENT CLASS--------------------//

	class ICE_API Component : public Identifiable
	{
	public:
		virtual const std::string GetName() = 0;

		void SetParent(Entity* parent)
		{
			m_AttachedEntity = parent;
		}

		Entity* GetParent()
		{
			return m_AttachedEntity;
		}

	protected:
		Entity* m_AttachedEntity;
	};

	//---------------------COMPONENTS------------------------//

	//Stores information like position, rotation and scale of an entity.
	class TransformComponent : public Component
	{
		ICE_COMPONENT_DECL(TransformComponent);

	public:
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

	private:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
	};
}

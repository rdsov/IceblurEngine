// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/CoreUtils.h"
#include "Core/Identifiable.h"
#include "Core/IO/Log.h"

#include "Component.h"

namespace Iceblur
{
	class ICE_API Entity : Identifiable
	{
	public:
		Entity(IceString name = "New Entity");

		//Creates a new entity and calls Initialize() function.
		//Returns the newly created entity.
		static Entity* CreateNew(IceString name)
		{
			auto entity = new Entity(name);
			return entity;
		}

		//Same as CreateNew(), but this function also adds the newly
		//created entity to the current scene.
		//If SceneManager::GetCurrentScene() is null, an error is thrown.
		static Entity* CreateAndAdd(IceString name);

		void Update(float deltaTime);

		std::string GetName() const
		{
			return m_Name;
		}

	public:
		template <typename T>
		T* AddComponent(Component* component)
		{
			if (HasComponent<T>())
			{
				return GetComponent<T>();
			}

			component->SetParentEntity(this);
			m_ComponentRegistry.emplace_back(component);
			return (T*) component;
		}

		template <typename T>
		bool RemoveComponent()
		{
			//Check if the component was found
			T* foundComponent = GetComponent<T>();
			if (foundComponent)
			{
				if (foundComponent->IsEssential())
				{
					ICE_ERROR(ICE_CLASS_TYPE(T) + " cannot be removed since it's an essential component!");
					return false;
				}

				REMOVE_FROM_VECTOR(m_ComponentRegistry, foundComponent);
				delete foundComponent;
				return true;
			}

			return false;
		}

		template <typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_ComponentRegistry)
			{
				auto foundComponent = dynamic_cast<T*>(component);
				if (foundComponent)
				{
					return foundComponent;
				}
			}

			//ICE_ERROR(Error::ETypes::A_NULLPTR, { ICE_CLASS_TYPE(T) + " of entity '" + GetName() + "'" });
			return nullptr;
		}

		template <typename T>
		bool HasComponent() const
		{
			for (const auto& component : m_ComponentRegistry)
			{
				if (dynamic_cast<T*>(component))
				{
					return true;
				}
			}

			return false;
		}

		class TransformComponent* Transform() const;

	private:
		std::string m_Name;

		std::vector<Component*> m_ComponentRegistry;
	};
}

// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/Identifiable.h"

//ComponentType must match the class name.
//Essential means that this component cannot be removed from an entity.
#define ICE_COMPONENT_DECL(ComponentType, Essential) \
const std::string GetName() const override { return #ComponentType; } \
const bool IsEssential() const override { return Essential; }

namespace Iceblur
{
	class Entity;

	//-----------------BASE COMPONENT CLASS--------------------//

	class ICE_API Component : public Identifiable
	{
	public:
		virtual ~Component()
		{
		}

		virtual const std::string GetName() const = 0;

		virtual const bool IsEssential() const = 0;

		void SetParentEntity(Entity* parent)
		{
			m_AttachedEntity = parent;
		}

		Entity* GetParentEntity()
		{
			return m_AttachedEntity;
		}

	protected:
		Entity* m_AttachedEntity;
	};
}

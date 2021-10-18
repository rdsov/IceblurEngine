// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "CoreUtils.h"

namespace Iceblur
{
	//This class creates and stores unique identifiers.
	class Identifiable
	{
	public:
		virtual void Initialize() = 0;

		virtual VID GenerateUniqueId()
		{
			m_Id = m_LastId + 1;
			m_LastId = m_Id;

			m_HasGeneratedId = true;

			return m_Id;
		}

		virtual VID GetId() const
		{
			return m_Id;
		}

	protected:
		VID m_Id;
		bool m_HasGeneratedId = false;

	private:
		static inline VID m_LastId = 0;
	};
}

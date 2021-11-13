// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Runtime/Scene/Components/SpectatorCameraComponent.h"

namespace Iceblur
{
	class EditorCamera : public SpectatorCameraComponent
	{
	public:
		EditorCamera()
		{
		}

		void SetupInput() override;

	protected:
		void Move(float deltaTime) override;

	private:
		float m_NormalSpeed = 2.5f;
		float m_AccelerateSpeed = 6.0f;
	};
}

// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "EditorCamera.h"

#include "Runtime/Core/InputManager.h"

namespace Iceblur
{
	void EditorCamera::SetupInput()
	{
		SpectatorCameraComponent::SetupInput();

		InputManager::BindKey(ICE_KEY_LEFT_SHIFT, ICE_HOLD);
	}

	void EditorCamera::Move(float deltaTime)
	{
		if (InputManager::GetKeyAction(ICE_KEY_LEFT_SHIFT, ICE_HOLD))
		{
			SetCameraSpeed(m_AccelerateSpeed);
		}
		else
		{
			SetCameraSpeed(m_NormalSpeed);
		}

		SpectatorCameraComponent::Move(deltaTime);
	}
}

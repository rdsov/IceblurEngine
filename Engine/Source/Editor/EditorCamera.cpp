// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "EditorCamera.h"

#include "Runtime/Core/InputManager.h"

namespace Iceblur
{
	void EditorCamera::SetupInput()
	{
		SpectatorCameraComponent::SetupInput();

		InputManager::BindKey(ICE_KEY_LEFT_SHIFT, ICE_HOLD);
		InputManager::BindKey(ICE_MOUSE_BUTTON_RIGHT, ICE_HOLD);
	}

	void EditorCamera::Update(float deltaTime)
	{
		if (InputManager::GetKeyAction(ICE_MOUSE_BUTTON_RIGHT, ICE_HOLD))
		{
			if (InputManager::IsMouseVisible())
			{
				InputManager::SetInputMode(EInputMode::Game);
			}

			m_LockCamera = false;
			m_LockMovement = false;
		}
		else
		{
			if (!InputManager::IsMouseVisible())
			{
				InputManager::SetInputMode(EInputMode::Default);
			}

			m_LockCamera = true;
			m_LockMovement = true;
		}

		SpectatorCameraComponent::Update(deltaTime);
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

// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Runtime/Scene/Components/SpectatorCameraComponent.h"

namespace Iceblur
{
	class EditorCamera : public SpectatorCameraComponent
	{
	protected:
		void Move(float deltaTime) override;
	};
}

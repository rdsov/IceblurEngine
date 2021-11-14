// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Runtime/Core/CoreMinimal.h"

#include "Runtime/Scene/Components/CameraComponent.h"
#include "EditorCamera.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
	EditorApp() = default;

	~EditorApp() override = default;

	void OnPostInit() override
	{
		Log::SetLogVerbosity(ELogVerbosity::Error);
		WindowManager::CreateWindow(EWindowType::Editor, { }, true);

		KeyAction action(ICE_KEY_ESCAPE, ICE_PRESS, std::bind(&Application::Quit, this));
		InputManager::BindKey(action);
		InputManager::SetInputMode(EInputMode::Game);

		Application::OnPostInit();
	}

	void OnStart() override
	{
		Application::OnStart();

		auto* camera = new EditorCamera();
		camera->SetupInput();
		Renderer::GetCurrentPipeline()->SetSpectatorCamera(camera);
	}
};

ICE_ENTRY_POINT(EditorApp)
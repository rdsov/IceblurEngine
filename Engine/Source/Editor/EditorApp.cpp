// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Runtime/Core/CoreMinimal.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
	EditorApp() = default;

	~EditorApp() override = default;

	static void OnMouseMoved(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, MouseMoveEvent);
		ICE_PRINT(event);
	}

	static void OnWindowResize(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, WindowResizeEvent);
		ICE_PRINT(event);
	}

	static void OnWindowMaximize(IceEventFn e)
	{
		ICE_EVENT_CAST(event, e, WindowMaximizeEvent);
		ICE_PRINT(event);
	}

	void OnPostInit() override
	{
		WindowManager::CreateWindow(EWindowType::EditorPopup, { }, true);

		/*Examples for event system:

		EventSystem::Subscribe(MouseMoveEvent::type, &OnMouseMoved);
		EventSystem::Subscribe(WindowResizeEvent::type, &OnWindowResize);
		EventSystem::Subscribe(WindowMaximizeEvent::type, &OnWindowMaximize);*/

		Application::OnPostInit();
	}
};

ICE_ENTRY_POINT(EditorApp)
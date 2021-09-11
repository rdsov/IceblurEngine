// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Runtime/Core/CoreMinimal.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
    EditorApp() = default;

    ~EditorApp() override = default;

    static void OnMouseMoved(ICE_EVENT_FN e)
    {
        ICE_EVENT_CAST(event, e, MouseMovedEvent);
        ICE_PRINT(event);
    }

    void OnPostInit() override
    {
        EventSystem::Subscribe(MouseMovedEvent::type, &OnMouseMoved);
        Application::OnPostInit();
    }
};

ICE_ENTRY_POINT(EditorApp)
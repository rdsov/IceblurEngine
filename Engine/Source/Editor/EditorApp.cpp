// Copyright (c) 2021 Futureblur. All rights reserved.

#include "Runtime/Core/CoreMinimal.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
    EditorApp() = default;

    ~EditorApp() override = default;

    void OnInit() override
    {
        Application::OnInit();

        auto window = new Window(EWindowType::Editor);

        while (true);
    }
};

ICE_ENTRY_POINT(EditorApp)
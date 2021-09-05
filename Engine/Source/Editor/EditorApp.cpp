// Copyright (c) 2021 Futureblur. All rights reserved.

#include "Runtime/Core/CoreMinimal.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
    EditorApp() = default;

    ~EditorApp() override = default;

    void ICE_SUPER(OnInit, Application)
};

ICE_ENTRY_POINT(EditorApp)
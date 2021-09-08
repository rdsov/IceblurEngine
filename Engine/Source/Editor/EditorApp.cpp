// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Runtime/Core/CoreMinimal.h"

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Iceblur;

class EditorApp : public Application
{
public:
    EditorApp() = default;

    ~EditorApp() override = default;
};

ICE_ENTRY_POINT(EditorApp)
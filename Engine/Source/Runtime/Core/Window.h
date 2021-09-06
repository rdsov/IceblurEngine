// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core.h"

class GLFWwindow;

namespace Iceblur
{
    //TODO: Create resolution struct
    //Sets the properties for a window.
    struct WindowProps
    {
        std::string Title = "Untitled Window";
        int Width = 1280;
        int Height = 720;
        int RefreshRate = 60;
        bool Maximized = true;
        bool Fullscreen = false;
        bool UseMonitorResolution = false;
    };

    //Speeds up the process of creating a window.
    //This config enum overrides members of struct WindowProps
    //The window resolution can be overridden by setting
    //WindowProps.UseMonitorResolution = true
    enum class EWindowType
    {
        Editor,
        EditorPopup,
        FullscreenGame,
        Unknown
    };

    class ICE_API Window
    {
    public:
        explicit Window(const WindowProps& props);

        explicit Window(const EWindowType& type, const WindowProps& props = {});

        ~Window() = default;

    private:
        void Create(const WindowProps& props);

    private:
        GLFWwindow* m_Window;
        EWindowType m_Type;
    };
}

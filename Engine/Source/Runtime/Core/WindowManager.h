// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Iceblur
{
    class ICE_API WindowManager
    {
    public:
        WindowManager() = default;

        ~WindowManager() = default;

        static void Initialize();

        static Window* CreateWindow(const EWindowType& type = EWindowType::Unknown, const WindowProps& props = { }, bool host = false);

        static bool IsWindowRunning(Window* window);

        static void UpdateWindow(Window* window);

        static Window* GetHost()
        {
            return m_Host;
        }

        //Returns a static window variable for a given target window.
        //Target window must be either the host or one of the popup windows.
        //Returns nullptr if target was not found.
        static Window* GetStaticWindow(GLFWwindow* target)
        {
            if (m_Host->GetNativeWindow() == target) return m_Host;

            for (const auto& window : m_PopupWindows)
            {
                if (window->GetNativeWindow() == target)
                {
                    return window;
                }
            }

            return nullptr;
        }

    private:
        struct WindowFnSignature
        {
            EWindowType type = EWindowType::Unknown;
            WindowProps props = { };
            bool isHost = false;
        };

        static Window* CreateWin64Window(const WindowFnSignature& signature);

        static bool IsWin64WindowRunning(Window* window);

        static void UpdateWin64Window(Window* window);

    private:
        static inline Window* m_Host;
        static inline std::vector<Window*> m_PopupWindows;
    };
}

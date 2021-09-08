// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Window.h"

struct GLFWwindow;

namespace Iceblur
{
    class Win64Window : public Window
    {
    public:
        explicit Win64Window(const WindowProps& props)
        {
            Win64Window::Create(props);
        }

        explicit Win64Window(const EWindowType& type, const WindowProps& props = {});

        ~Win64Window() override = default;

        NODISCARD void* GetNativeWindow() const override
        {
            return m_Window;
        }

    private:
        void Create(const WindowProps& props) override;

        static void MousePositionCallback(GLFWwindow* window, double x, double y);

    private:
        GLFWwindow* m_Window = nullptr;
    };
}

// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "IEvent.h"

namespace Iceblur
{
    //---------------EVENT TYPE DECLARATIONS---------------//

    struct Window;

    struct WindowResizeEvent : IEvent
    {
        ICE_EVENT_DECL(WindowResizeEvent)

        WindowResizeEvent(Window* window, int width, int height)
                : m_Window(window), m_Width(width), m_Height(height)
        {
        }

        ~WindowResizeEvent() override = default;

        NODISCARD inline Window* GetWindow() const
        {
            return m_Window;
        }

        NODISCARD inline int GetWidth() const
        {
            return m_Width;
        }

        NODISCARD inline int GetHeight() const
        {
            return m_Height;
        }

    private:
        Window* m_Window = nullptr;
        int m_Width = 0;
        int m_Height = 0;
    };

    struct WindowMaximizeEvent : IEvent
    {
        ICE_EVENT_DECL(WindowMaximizeEvent)

        WindowMaximizeEvent(Window* window, bool maximized)
                : m_Window(window), m_Maximized(maximized)
        {
        }

        ~WindowMaximizeEvent() override = default;

        NODISCARD inline Window* GetWindow() const
        {
            return m_Window;
        }

        NODISCARD inline bool IsMaximized() const
        {
            return m_Maximized;
        }

    private:
        Window* m_Window = nullptr;
        bool m_Maximized = false;
    };

    struct MouseMoveEvent : IEvent
    {
        ICE_EVENT_DECL(MouseMoveEvent)

        MouseMoveEvent(float x, float y)
                : m_X(x), m_Y(y)
        {
        }

        ~MouseMoveEvent() override = default;

        NODISCARD inline float GetX() const
        {
            return m_X;
        }

        NODISCARD inline float GetY() const
        {
            return m_Y;
        }

    private:
        float m_X = 0;
        float m_Y = 0;
    };

    //---------------DEBUG OVERLOADS---------------//

    inline std::ostream& operator<<(std::ostream& os, const WindowResizeEvent& event)
    {
        os << event.DebugString() << "Width: " << event.GetWidth() << " Height: " << event.GetHeight();
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const WindowMaximizeEvent& event)
    {
        os << event.DebugString() << "Is Maximized: " << event.IsMaximized();
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const MouseMoveEvent& event)
    {
        os << event.DebugString() << "X: " << event.GetX() << " Y: " << event.GetY();
        return os;
    }
}

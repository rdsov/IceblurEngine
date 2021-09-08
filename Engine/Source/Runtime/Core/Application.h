// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core.h"
#include "IO/Log.h"

namespace Iceblur
{
    class ICE_API Application
    {
    public:
        Application()
        {
            if (m_Instance)
            {
                ICE_FATAL("Error: Multiple instances of Application!");
            }

            m_Instance = this;
        }

        virtual ~Application() = default;

        //Spawns the host window. This currently returns 0, but this will change in the future.
        virtual int Spawn();

    public:
        static Application* GetInstance()
        {
            return m_Instance;
        }

    protected:
        virtual void OnInit();

        virtual void OnPostInit();

        virtual void OnUpdate();

        virtual void OnShutdown();

    private:
        static inline Application* m_Instance = nullptr;

        static class Window* m_Window;
    };
}

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
            ICE_SINGLETON(m_Instance, Application)
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
        ICE_SINGLETON_DEF(m_Instance, Application)
    };
}

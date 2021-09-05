// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core.h"

namespace Iceblur
{
    class ICE_API Application
    {
    public:
        Application()
        {
            if (m_Instance)
            {
                std::cout << "Error: Multiple instances of Application!\n";
                return;
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

    private:
        static inline Application* m_Instance = nullptr;
    };
}

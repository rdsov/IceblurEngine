// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

namespace Iceblur
{
    int Application::Spawn()
    {
        OnInit();
        return 0;
    }

    void Application::OnInit()
    {
        std::cout << "Welcome to Iceblur Engine! For more information, please visit https://github.com/Futureblur/IceblurEngine.\n";

        while (true);
    }
}

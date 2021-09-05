// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

extern Iceblur::Application* GetHostApplication();

#define ICE_ENTRY_POINT(HostApplicationClass) Application* GetHostApplication() \
{ \
    static_assert(std::is_base_of<Iceblur::Application, HostApplicationClass>::value, "HostApplicationClass must inherit from Iceblur::Application"); \
    return new HostApplicationClass(); \
}

int main()
{
    auto host = GetHostApplication();
    host->Spawn();
    delete host;
}
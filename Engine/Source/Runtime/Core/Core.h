// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#ifdef ICE_BUILD_DLL
#define ICE_API __declspec(dllexport)
#else
#define ICE_API __declspec(dllimport)
#endif

#define ICE_SUPER(Func, SuperClass) Func() override \
{ \
    SuperClass::Func(); \
}

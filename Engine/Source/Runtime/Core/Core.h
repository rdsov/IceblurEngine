// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "PlatformDetection.h"

#ifdef ICE_BUILD_DLL
#define ICE_API __declspec(dllexport)
#else
#define ICE_API __declspec(dllimport)
#endif

#define NODISCARD [[nodiscard]]

#define ICE_DEBUG

#define ICE_SUPER(Func, SuperClass) Func() override \
{ \
    SuperClass::Func(); \
}

//TODO: Create error list class for consistency, errors should be enums rather than hardcoded strings.
//Singleton pattern macro to prevent multiple instances of a class.
//InstanceVar must share the same name as defined in ICE_SINGLETON_DEF
#define ICE_SINGLETON(InstanceVar, Class) if (InstanceVar) \
{ ICE_FATAL("Error: Multiple instances of" + std::string(#Class) + "! This is not allowed."); } \
else { m_Instance = this; };

//Defines a singleton instance class which is used together with the ICE_SINGLETON macro.
#define ICE_SINGLETON_DEF(VarName, Class) static inline Class* VarName = nullptr;

//Converts to string
#define ICE_TOS(x) std::to_string(x)

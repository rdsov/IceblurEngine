// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#ifdef ICE_BUILD_DLL
#define ICE_API __declspec(dllexport)
#else
#define ICE_API __declspec(dllimport)
#endif

#define NODISCARD [[nodiscard]]

#define ICE_DEBUG

#include "Error/ErrorList.h"

//Singleton pattern macro to prevent multiple instances of a class.
//InstanceVar must share the same name as defined in ICE_SINGLETON_DEF
#define ICE_SINGLETON(InstanceVar, Class) if (InstanceVar) \
{ ICE_FATAL(Error::ETypes::A_SINGLETON, { #Class }); } \
else { m_Instance = this; };

//Defines a singleton instance class which is used together with the ICE_SINGLETON macro.
#define ICE_SINGLETON_DEF(VarName, Class) static inline Class* VarName = nullptr;

//Converts to string
#define ICE_TOS(str) std::to_string(str)

//Checks if string is empty (only works for non-static functions).
//Inside static functions, use VIO::Empty() instead.
#define ICE_EMPTY(str) std::string::empty(str)

//Checks if enum length equals the length of array
//Enum should have 'LAST' as the last element
#define ICE_ASSERT_ARRAY_ENUM(Array, Enum) \
static_assert(sizeof(Array) / sizeof(Array[0]) == static_cast<int>(Enum::LAST), INVALID_ENUM_ARRAY_LENGTH);

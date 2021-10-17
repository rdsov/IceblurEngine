// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

//Defines a singleton instance class which is used together with the ICE_SINGLETON macro.
#define ICE_SINGLETON_DEF(VarName, Class) static inline Class* VarName = nullptr;

//Checks if string is empty (only works for non-static functions).
//Inside static functions, use VIO::Empty() instead.
#define ICE_EMPTY(str) std::string::empty(str)

typedef const std::string& IceString;

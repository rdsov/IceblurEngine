// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#if defined (_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__NT__)
#if defined (_WIN64)
#define ICE_WIN64
#else
#error "Windows 32-bit is not supported!"
#endif
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if defined(TARGET_OS_MAC)
#define IE_MAC_OS
#elif TARGET_OS_IPHONE
#define ICE_IPHONE
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
#define ICE_LINUX
#else
#error "Unknown compiler"
#endif

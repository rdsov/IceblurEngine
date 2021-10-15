// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

//Put this in the very first line inside an IEvent child class.
//This is needed in order to declare a custom event.
#define ICE_EVENT_DECL(EventType) EventType() = default; \
static constexpr EventName type = #EventType;            \
NODISCARD EventName GetName() const override { return type; }

namespace Iceblur
{
    struct IEvent
    {
    public:
        IEvent() = default;

        virtual ~IEvent() = default;

        using EventName = const char*;

        NODISCARD virtual EventName

        GetName() const = 0;

        NODISCARD virtual std::string ToString() const
        {
            return GetName();
        }

        NODISCARD virtual std::string DebugString() const
        {
            return "[" + ToString() + "] ";
        }
    };

    //Parameter for event callback functions
    typedef const IEvent& IceEventFn;
}

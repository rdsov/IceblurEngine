// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "EventTypes.h"
#include "Core/Error/ErrorList.h"

//Converts the IEvent base class to any derived type.
//NewVarName is the name of the new variable that will be created by this macro.
//It should not already exist in the current scope otherwise it will cause conflicts.
#define ICE_EVENT_CAST(NewVarName, BaseVarName, EventType) EventType NewVarName; \
try { NewVarName = dynamic_cast<const EventType&>(BaseVarName); } catch (const std::bad_cast& e) \
{ \
ICE_FATAL(Error::EFailed::ACAST_EVENT, { #NewVarName, #EventType }); \
}

namespace Iceblur
{
    class ICE_API EventSystem
    {
    public:
        using Callback = std::function<void(const IEvent& e)>;
        using EventList = std::map<IEvent::EventName, std::vector<Callback>>;

        EventSystem() = default;

        ~EventSystem() = default;

        static void Initialize();

        static void Subscribe(IEvent::EventName type, const Callback& trigger);

        static void Dispatch(const IEvent& event);

    private:
        static EventSystem* GetInstance()
        {
            return m_Instance;
        }

    private:
        static inline EventSystem* m_Instance = nullptr;
        EventList m_EventList;
    };
}

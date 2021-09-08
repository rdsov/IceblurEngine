// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "EventSystem.h"
#include "Core/IO/Log.h"

namespace Iceblur
{
    void EventSystem::Subscribe(IEvent::EventName type, const EventSystem::Callback& trigger)
    {
        m_EventList.insert(std::pair<const char*, Callback>(type, trigger));
    }

    void EventSystem::Dispatch(const IEvent& event)
    {
        for (const auto& e : m_EventList)
        {
            if (strcmp(e.first, event.GetName()) == 0)
            {
                e.second(event);
            }
        }
    }
}

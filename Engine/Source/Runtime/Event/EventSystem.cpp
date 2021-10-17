// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "EventSystem.h"
#include "Core/IO/Log.h"

namespace Iceblur
{
	void EventSystem::Initialize()
	{
		if (m_Instance)
		{
			ICE_FATAL(Error::ETypes::A_SINGLETON, { "EventSystem" });
		}

		m_Instance = new EventSystem();
	}

	void EventSystem::Subscribe(IEvent::EventName type, const EventSystem::Callback& trigger)
	{
		auto& list = GetInstance()->m_EventList;

		//If the event type already exists, insert the callback there
		if (list.find(type) != list.end())
		{
			list[type].push_back(trigger);
			return;
		}

		//Event type was not found, create new entry
		std::vector<Callback> callbackList = { trigger };
		list.insert(std::pair<IEvent::EventName, std::vector<EventSystem::Callback>>(type, callbackList));
	}

	void EventSystem::Dispatch(const IEvent& event)
	{
		for (const auto& e : GetInstance()->m_EventList)
		{
			if (strcmp(e.first, event.GetName()) == 0)
			{
				for (const auto& callback : e.second)
				{
					callback(event);
				}
			}
		}
	}
}

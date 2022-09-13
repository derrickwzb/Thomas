#pragma once

#include "thpch.h"
#include "Thomas/Core.h"

namespace Thomas {
	enum class EventType
	{
		NONE = 0,
		WINDOWCLOSE,
		WINDOWRESIZE,
		WINDOWFOCUS,
		WINDOWLOSTFOCUS,
		WINDOWMOVED,

		APPTICK,
		APPUPDATE,
		APPRENDER,

		KEYPRESSED,
		KEYRELEASED,

		MOUSEBUTTONPRESSED,
		MOUSEBUTTONRELEASED,
		MOUSEMOVED,
		MOUSESCROLLED
	};

	enum EventCategory
	{
		NONE						= 0,
		EVENTCATEGORYAPP			= BIT(0),
		EVENTCATEGORYINPUT			= BIT(1),
		EVENTCATEGORYKEYBOARD		= BIT(2),
		EVENTCATEGORYMOUSE			= BIT(3),
		EVENTCATEGORYMOUSEBUTTON	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class THOMAS_API Event 
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags()  const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool Handled = false;


	};
	class EventDispatcher 
	{

		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_event(event)
		{
			//empty by design
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}


#pragma once

#include "Event.h"

namespace Thomas
{
	class THOMAS_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE (WINDOWRESIZE)
		EVENT_CLASS_CATEGORY (EVENTCATEGORYAPP)


	private:
		unsigned int m_Width, m_Height;
	};

	class THOMAS_API WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent() {}
		EVENT_CLASS_TYPE(WINDOWMAXIMIZED)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYAPP)
	};

	class THOMAS_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_TYPE(APPUPDATE)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYAPP)
	};

	class THOMAS_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		EVENT_CLASS_TYPE(APPTICK)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYAPP)
	};
	
	class THOMAS_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(APPUPDATE)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYAPP)
	};
	class THOMAS_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent(){}
		EVENT_CLASS_TYPE(APPRENDER)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYAPP)
	};


}

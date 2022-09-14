#pragma once

#include "Event.h"

namespace Thomas {

	class THOMAS_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:mouseX(x), mouseY(y) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent : " << mouseX << " , " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSEMOVED)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYMOUSE | EVENTCATEGORYINPUT)

	private:
		float mouseX, mouseY;
	};

	class THOMAS_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
		: xOffset(x) , yOffset(y) {}

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent : " << xOffset << " , " << yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSESCROLLED)
		EVENT_CLASS_CATEGORY(EVENTCATEGORYMOUSE | EVENTCATEGORYINPUT)
	private:
		float xOffset, yOffset;
	};

	class THOMAS_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EVENTCATEGORYMOUSE | EVENTCATEGORYINPUT)
	protected:
		MouseButtonEvent(int button)
			: mButton(button) {}

		int mButton;
	};

	class THOMAS_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MOUSEBUTTONPRESSED)
	};

	class THOMAS_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
		:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSEBUTTONRELEASED)
	};
}
#pragma once

#include "Event.h"

namespace Thomas {
	class THOMAS_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyc; }
		EVENT_CLASS_CATEGORY(EVENTCATEGORYKEYBOARD | EVENTCATEGORYINPUT)
	protected:
		KeyEvent(int keycode)
			:keyc(keycode){}

		int keyc;
	};

	class THOMAS_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeat)
			:KeyEvent(keycode),repeatcnt(repeat){}

		inline int GetRepeatCount() const { return repeatcnt; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << keyc << "(" << repeatcnt << " repeats";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEYPRESSED)
	private:
		int repeatcnt;	
	};

	class THOMAS_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyc;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEYRELEASED)
	};

	class THOMAS_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << keyc;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEYTYPED)

	};
}

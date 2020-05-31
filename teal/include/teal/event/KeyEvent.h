#pragma once

#include "Event.h"

namespace Teal
{
	class TL_API KeyEvent: public Event
	{
	public:
		inline int GetKeyCode() const { return p_KeyCode; }

		EVENT_CLASS_CATEGORY(ECKeyboard | ECInput)
	protected:
		KeyEvent(int keycode) : p_KeyCode(keycode) {}
		int p_KeyCode;
	};

	class TL_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " " << p_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

	class TL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) 
			: KeyEvent(keycode), _RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return _RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " " << p_KeyCode << " Repeated(" << _RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int _RepeatCount;
	};

	class TL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
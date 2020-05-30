#pragma once

#include "../core/Common.h"

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }

#define EVENT_CLASS_CATEGORY(c) virtual int GetCategoryFlags() const override { return EventCategory(c); }

namespace Teal
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowsResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		ECApp			= BIT(0),
		ECInput			= BIT(1),
		ECKeyboard		= BIT(2),
		ECMouse			= BIT(3),
		ECMouseButton	= BIT(4)
	};

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;

		inline void handled() { p_Handled = true; }
		inline void reset() { p_Handled = false; }

		inline bool IsInCategory(EventCategory c)
		{
			return GetCategoryFlags() & c;
		}
	protected:
		bool p_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : _Event(e) {}

		template<typename T, typename F>
		bool Dispatch(const F& f)
		{
			if (_Event.GetEventType == T::GetStaticType())
			{
				if (f(static_cast<T&>(_Event)))
					_Event.handled();
				return true;
			}
			return false;
		}
	private:
		Event& _Event;
	};
}

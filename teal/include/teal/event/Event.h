#pragma once

#include "teal/core/Common.h"
#include <sstream>

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual std::string GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(c) virtual int GetCategoryFlags() const override { return EventCategory(c); }

namespace Teal
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
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

	class TL_API Event
	{
	public:
		virtual EventType GetEventType() const { return EventType::None; };
		virtual int GetCategoryFlags() const { return None; };

		inline void Handled() { p_Handled = true; }
		inline void Reset() { p_Handled = false; }
		inline bool IsHandled() { return p_Handled; }

		inline bool IsInCategory(EventCategory c)
		{
			return GetCategoryFlags() & c;
		}

		virtual std::string GetName() const { return "None"; };
		virtual std::string ToString() const { return GetName(); };

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

#pragma once

#include "Event.h"

namespace Teal
{

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : _Width(width), _Height(height) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << " " << _Width << "," << _Height;
			return ss.str();
		};

		inline int GetWidth() { return _Width; }
		inline int GetHeight() { return _Height; }

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(ECApp)
	private:
		unsigned int _Width, _Height;
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(ECApp)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(ECApp)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(ECApp)
	};
}
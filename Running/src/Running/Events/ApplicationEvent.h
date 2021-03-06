#pragma once
#include "Event.h"

namespace Running
{
	// -----------------------------------------------
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned width, unsigned height) :
			_width(width),
			_height(height)
		{
		}

		inline unsigned GetWidth() const { return _width; }
		inline unsigned GetHeight() const { return _height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowsResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

	private:
		unsigned _width;
		unsigned _height;
	};

	// -----------------------------------------------
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};

	// -----------------------------------------------
	class AppTickEvent : public Event
	{
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};

	// -----------------------------------------------
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};

	// -----------------------------------------------
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};
}

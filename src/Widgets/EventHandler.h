#pragma once

#include <cinder\app\Event.h>
#include <cinder\app\KeyEvent.h>
#include <cinder\app\MouseEvent.h>

namespace Widgets
{
	enum class Event
	{
		MouseUp,
		MouseDown,
		MouseMove,
		MouseDrag,

		KeyUp,
		KeyDown,
	};

	class EventHandler
	{
		void onEventImpl(cinder::app::MouseEvent* mouseEvent, Event event);
		void onEventImpl(cinder::app::KeyEvent* keyEvent, Event event);

	protected:
		virtual void OnMouseUp(cinder::app::MouseEvent& event) = 0;
		virtual void OnMouseDown(cinder::app::MouseEvent& event) = 0;
		virtual void OnMouseMove(cinder::app::MouseEvent& event) = 0;
		virtual void OnMouseDrag(cinder::app::MouseEvent& event) = 0;

		virtual void OnKeyUp(cinder::app::KeyEvent& event) = 0;
		virtual void OnKeyDown(cinder::app::KeyEvent& event) = 0;

	public:
		template <typename EVENT_TYPE, Event EVENT>
		void OnEvent(cinder::app::Event& event)
		{
			onEventImpl(static_cast<EVENT_TYPE*>(&event), EVENT);
		}


		EventHandler() = default;
		EventHandler(const EventHandler&) = default;
		EventHandler(EventHandler&& rhs) = default;
		EventHandler& operator=(const EventHandler&) = default;
		EventHandler& operator=(EventHandler&&) = default;
		virtual ~EventHandler() = default;
	};
}
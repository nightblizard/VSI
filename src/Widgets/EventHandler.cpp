#include "../stdafx.h"

#include "EventHandler.h"


namespace Widgets
{
	void EventHandler::onEventImpl(cinder::app::MouseEvent* mouseEvent, Event event)
	{
		switch(event)
		{
		case Event::MouseUp:
			OnMouseUp(*mouseEvent);
			break;
		case Event::MouseDown:
			OnMouseDown(*mouseEvent);
			break;
		case Event::MouseMove:
			OnMouseMove(*mouseEvent);
			break;
		case Event::MouseDrag:
			OnMouseDrag(*mouseEvent);
			break;
		}
	}

	
	void EventHandler::onEventImpl(cinder::app::KeyEvent* keyEvent, Event event)
	{
		switch (event)
		{
		case Event::KeyUp:
			OnKeyUp(*keyEvent);
			break;
		case Event::KeyDown:
			OnKeyDown(*keyEvent);
			break;
		}
	}
}
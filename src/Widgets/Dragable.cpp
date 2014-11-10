#include "Dragable.h"
#include <cinder\app\Window.h>
#include <cinder\app\App.h>

namespace Widgets
{
	void Dragable::OnMouseUp(cinder::app::MouseEvent& event)
	{
		Selectable::OnMouseUp(event);
	}


	void Dragable::OnMouseDown(cinder::app::MouseEvent& event)
	{
		Selectable::OnMouseDown(event);

		if(IsSelected())
		{
			event.setHandled();
			SetSelected();
			mLastMousePosition.x = event.getX();
			mLastMousePosition.y = event.getY();
		}
	}


	void Dragable::OnMouseDrag(cinder::app::MouseEvent& event)
	{
		if (!IsSelected())
			return;

		event.setHandled();
		event.getPos();

		int mouseX = event.getX();
		int mouseY = event.getY();

		int mouseDownX = mLastMousePosition.x;
		int mouseDownY = mLastMousePosition.y;

		mLastMousePosition.x = mouseX;
		mLastMousePosition.y = mouseY;

		float mx = 0, my = 0;
		auto frameRate = event.getWindow()->getApp()->getFrameRate();

		if (mouseX != mouseDownX)
			mx = (mouseX - mouseDownX) * 0.01f * frameRate;
		if (mouseY != mouseDownY)
			my = (mouseY - mouseDownY) * 0.01f * frameRate;

		mPosition.x += mx;
		mPosition.y += my;
		updateBounds();
		/*
		mBounds.x1 += mx;
		mBounds.x2 += mx;
		mBounds.y1 += my;
		mBounds.y2 += my;
		*/
		OnDrag();
	}
}
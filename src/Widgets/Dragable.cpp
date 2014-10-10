#include "Dragable.h"
#include <cinder\app\Window.h>
#include <cinder\app\App.h>

namespace Widgets
{
	void Dragable::OnMouseUp(cinder::app::MouseEvent& event)
	{
		SetSelected(false);
		OnSelect(event);
	}


	void Dragable::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto pos = event.getPos();

		if (mBounds.contains(pos))
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

		mBounds.x1 += mx;
		mBounds.x2 += mx;
		mBounds.y1 += my;
		mBounds.y2 += my;

		OnDrag();
	}


	bool Dragable::IsSelected() const
	{
		return mIsSelected;
	}

	
	void Dragable::SetSelected(bool selected)
	{
		mIsSelected = selected;
		OnSelect(cinder::app::MouseEvent());
	}
}
#pragma once
#include "Selectable.h"


namespace Widgets
{
	void Selectable::OnMouseUp(cinder::app::MouseEvent& event)
	{
		SetSelected(false);
		OnSelect(event);
	}


	void Selectable::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto pos = event.getPos();

		if (mBounds.contains(pos))
			SetSelected();
	}


	bool Selectable::IsSelected() const
	{
		return mIsSelected;
	}


	void Selectable::SetSelected(bool selected)
	{
		mIsSelected = selected;
		OnSelect(cinder::app::MouseEvent());
	}
}
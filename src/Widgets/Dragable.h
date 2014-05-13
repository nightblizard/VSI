#pragma once
#include "Widget.h"


namespace Widgets
{
	class Dragable : public Widget
	{
		bool mIsSelected = false;

		cinder::Vec2i mLastMousePosition;

	protected:
		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDown(cinder::app::MouseEvent& event) override;
		void OnMouseDrag(cinder::app::MouseEvent& event) override;

	public:
		bool IsSelected() const;
		void SetSelected(bool selected = true);
	};
}
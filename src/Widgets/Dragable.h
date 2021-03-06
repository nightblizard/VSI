#pragma once
#include "Selectable.h"
#include "Widget.h"


namespace Widgets
{
	class Dragable : public Selectable
	{
		cinder::Vec2i mLastMousePosition;

	protected:
		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDown(cinder::app::MouseEvent& event) override;
		void OnMouseDrag(cinder::app::MouseEvent& event) override;
		virtual void OnDrag() {}

	public:
	};
}
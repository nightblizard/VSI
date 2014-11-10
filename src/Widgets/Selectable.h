#pragma once
#include "Widget.h"


namespace Widgets
{
	class Selectable : public Widget
	{
		bool mIsSelected = false;

	protected:
		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDown(cinder::app::MouseEvent& event) override;

		virtual void OnSelect(cinder::app::MouseEvent& event) {}

	public:
		bool IsSelected() const;
		void SetSelected(bool selected = true);
	};
}
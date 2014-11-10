#pragma once

#include "../Widget.h"
#include <cinder\Color.h>


namespace Widgets
{
	class Panel : public Widget
	{
		cinder::Color mColor = cinder::Color::hex(0xFFFFFF);

		bool mEatInput = false;

	protected:
		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDown(cinder::app::MouseEvent& event) override;
		void OnMouseDrag(cinder::app::MouseEvent& event) override;

	public:
		void Draw() const override;
	};
}
#include "../../stdafx.h"
#include "Panel.h"

namespace Widgets
{
	void Panel::OnMouseUp(cinder::app::MouseEvent& event)
	{
		if (mEatInput)
		{
			event.setHandled();
			mEatInput = false;
		}
	}


	void Panel::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto pos = event.getPos();

		if (mBounds.contains(pos))
		{
			event.setHandled();
			mEatInput = true;
		}
	}


	void Panel::OnMouseDrag(cinder::app::MouseEvent& event)
	{
		if (mEatInput)
			event.setHandled();
	}


	void Panel::Draw() const
	{
		static cinder::Font font = cinder::Font("Consolas", 32);

		/*		Background		*/
		static auto innerRect = cinder::Rectf{ -2.f, -2.f, 2.f, 2.f };
		cinder::gl::color(cinder::Color::black());
		cinder::gl::drawSolidRect(mBounds);
		cinder::gl::color(mColor);
		cinder::gl::drawSolidRect(mBounds - innerRect);
	}
}
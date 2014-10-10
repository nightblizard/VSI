#include "../stdafx.h"
#include <cinder\Rect.h>
#include "Widget.h"


namespace Widgets
{
	void Widget::updateBounds()
	{
		if(mParent == nullptr)
		{
			mBounds = cinder::Rectf(static_cast<float>(mPosition.x), 
									static_cast<float>(mPosition.y),
									static_cast<float>(mSize.x + mPosition.x),
									static_cast<float>(mSize.y + mPosition.y));
			return;
		}

		float px = static_cast<float>(mParent->mBounds.x1);
		float py = static_cast<float>(mParent->mBounds.y1);
		float pu = static_cast<float>(mParent->mBounds.x2);
		float pv = static_cast<float>(mParent->mBounds.y2);

		float x1 = px + mPosition.x,
			  y1 = py + mPosition.y,
			  x2 = x1 + mSize.x,
			  y2 = y1 + mSize.y;

		switch (mRelativeTo)
		{
		case RelativePoint::TopRight:
			x1 = pu + mPosition.x;
			x2 = x1 + mSize.x;
			break;

		case RelativePoint::Top:
			x1 = (px + pu) / 2.f + mPosition.x;
			x2 = x1 + mSize.x;
			break;

		case RelativePoint::TopLeft:
			x1 = px + mPosition.x;
			x2 = x1 + mSize.x;
			break;

		case RelativePoint::Left:
			x1 = px + mPosition.x;
			y1 = (py + pv) / 2 + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Center:
			x1 = (px + pu) / 2.f + mPosition.x;
			y1 = (py + pv) / 2 + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Right:
			x1 = pu + mPosition.x;
			y1 = (py + pv) / 2 + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::BottomLeft:
			x1 = px + mPosition.x;
			y1 = pv + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Bottom:
			x1 = (px + pu) / 2.f + mPosition.x;
			y1 = pv + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::BottomRight:
			x1 = pu + mPosition.x;
			y1 = pv + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::None:
			x1 = static_cast<float>(mPosition.x);
			y1 = static_cast<float>(mPosition.y);
			x2 = static_cast<float>(mSize.x);
			y2 = static_cast<float>(mSize.y);
			break;

		default:
			break;
		}

		mBounds = cinder::Rectf(x1, y1, x2, y2);
	}


	cinder::Vec2i Widget::GetPosition() const
	{
		return cinder::Vec2i(static_cast<int>(mBounds.x1), static_cast<int>(mBounds.y1));
	}


	void Widget::SetPosition(const cinder::Vec2i& pos)
	{
		mPosition = pos;
		updateBounds();
	}


	cinder::Vec2i Widget::GetSize() const
	{
		return cinder::Vec2i(static_cast<int>(mBounds.x2), static_cast<int>(mBounds.y2));
	}


	void Widget::SetSize(const cinder::Vec2i& size)
	{
		mSize = size;
		updateBounds();
	}


	cinder::Rectf Widget::GetBounds() const
	{
		return mBounds;
	}


	void Widget::SetBounds(const cinder::Vec2i& position, const cinder::Vec2i& size)
	{
		mPosition = position;
		mSize = size;
		updateBounds();
	}


	void Widget::SetBounds(const std::pair<cinder::Vec2i, cinder::Vec2i>& rect)
	{
		mPosition = { rect.first.x, rect.first.y };
		mSize = { rect.second.x, rect.second.y };
		updateBounds();
	}


	void Widget::SetProperty(const std::string& name, const std::string& value)
	{
		if (name == "name")
			SetName(value);
		else if (name == "relativeTo")
			SetRelativePoint(RelativePointStrings[value]);
		else if (name == "x")
			mPosition.x = std::stoi(value);
		else if (name == "y")
			mPosition.y = std::stoi(value);
		else if (name == "width")
			mSize.x = std::stoi(value);
		else if (name == "height")
			mSize.y = std::stoi(value);

		updateBounds();
	}


	void Widget::SetProperty(const std::string& name, int value)
	{
	}


	void Widget::SetName(const std::string& newName)
	{
		mName = newName;
	}


	std::string Widget::GetName() const
	{
		return mName;
	}


	void Widget::SetRelativePoint(RelativePoint relativeTo)
	{
		mRelativeTo = relativeTo;
	}


	RelativePoint Widget::GetRelativePoint() const
	{
		return mRelativeTo;
	}


	void Widget::SetParent(std::shared_ptr<Widget> parent)
	{
		mParent = parent;
	}


	void Widget::Draw() const
	{
		cinder::gl::drawSolidRect(mBounds);
	}

	void Widget::Update()
	{
		updateBounds();
	}


	Widget::Widget(std::shared_ptr<Widget> parent, RelativePoint relativeTo) :
		mParent(parent),
		mRelativeTo(relativeTo)
	{
	}
}
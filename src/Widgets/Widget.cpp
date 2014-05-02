#include "stdafx.h"
#include <cinder\Rect.h>
#include "Widget.h"


namespace Widgets
{
	Widget::Widget(std::shared_ptr<Widget> parent, RelativePoint relativeTo) :
		mParent(parent),
		mRelativeTo(relativeTo)
	{
	}


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

		float px = static_cast<float>(mParent->mPosition.x);
		float py = static_cast<float>(mParent->mPosition.y);
		float pu = static_cast<float>(mParent->mSize.x);
		float pv = static_cast<float>(mParent->mSize.y);

		float x1 = px + mPosition.x,
			  y1 = py + mPosition.y,
			  x2 = x1 + mSize.x,
			  y2 = y1 + mSize.y;

		switch (mRelativeTo)
		{
		case RelativePoint::TopRight:
			x1 = px + pu + mPosition.x;
			x2 = x1 + mSize.x;
			break;

		case RelativePoint::Top:
			x1 = pu / 2.f + px + mPosition.x;
			x2 = x1 + mSize.x;
			break;

		case RelativePoint::TopLeft:
			break;

		case RelativePoint::Left:
			y1 = pv / 2 + py + mPosition.y;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Center:
			x1 = pu / 2.f + px + mPosition.x;
			y1 = pv / 2 + py + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Right:
			x1 = pu + px + mPosition.x;
			y1 = pv / 2 + py + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::BottomLeft:
			y1 = py + pu + mPosition.y;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::Bottom:
			x1 = pu / 2.f + px + mPosition.x;
			y1 = py + pu + mPosition.y;
			x2 = x1 + mSize.x;
			y2 = y1 + mSize.y;
			break;

		case RelativePoint::BottomRight:
			x1 = pu + px + mPosition.x;
			y1 = py + pu + mPosition.y;
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
		return mPosition;
	}


	void Widget::SetPosition(const cinder::Vec2i& pos)
	{
		updateBounds();
		mPosition = pos;
	}


	cinder::Vec2i Widget::GetSize() const
	{
		return mSize;
	}


	void Widget::SetSize(const cinder::Vec2i& size)
	{
		mSize = size;
		updateBounds();
	}


	std::pair<cinder::Vec2i, cinder::Vec2i> Widget::GetBounds() const
	{
		return std::make_pair(mPosition, mSize);
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


	void Widget::Draw() const
	{
		cinder::gl::drawSolidRect(mBounds);
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
}
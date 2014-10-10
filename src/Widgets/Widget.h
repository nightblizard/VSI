#pragma once
#include <memory>
#include <map>
#include <boost/assign/list_of.hpp>
#include <cinder\Vector.h>
#include <cinder\Rect.h>

#include "EventHandler.h"

namespace Widgets
{
	enum class RelativePoint
	{
		TopRight,
		Top,
		TopLeft,
		Left,
		Center,
		Right,
		BottomLeft,
		Bottom,
		BottomRight,

		None
	};

	static std::map<std::string, RelativePoint> RelativePointStrings = boost::assign::map_list_of
		("TopRight", RelativePoint::TopRight)
		("Top", RelativePoint::Top)
		("TopLeft", RelativePoint::TopLeft)
		("Left", RelativePoint::Left)
		("Center", RelativePoint::Center)
		("Right", RelativePoint::Right)
		("BottomLeft", RelativePoint::BottomLeft)
		("Bottom", RelativePoint::Bottom)
		("BottomRight", RelativePoint::BottomRight)
		("None", RelativePoint::None);

	class Widget : public EventHandler, public std::enable_shared_from_this<Widget>
	{
	protected:
		std::shared_ptr<Widget> mParent = nullptr;
		cinder::Vec2i mPosition;
		cinder::Vec2i mSize;

		RelativePoint mRelativeTo = RelativePoint::None;

		cinder::Rectf mBounds;

		std::string mName;

		void updateBounds();

		virtual void OnMouseUp(cinder::app::MouseEvent& event) override {}
		virtual void OnMouseDown(cinder::app::MouseEvent& event) override {}
		virtual void OnMouseMove(cinder::app::MouseEvent& event) override {}
		virtual void OnMouseDrag(cinder::app::MouseEvent& event) override {}

		virtual void OnKeyUp(cinder::app::KeyEvent& event) override {}
		virtual void OnKeyDown(cinder::app::KeyEvent& event) override {}

	public:
		cinder::Vec2i GetPosition() const;
		void SetPosition(const cinder::Vec2i& pos);

		cinder::Vec2i GetSize() const;
		void SetSize(const cinder::Vec2i& size);

		cinder::Rectf GetBounds() const;
		void SetBounds(const cinder::Vec2i& position, const cinder::Vec2i& size);
		void SetBounds(const std::pair<cinder::Vec2i, cinder::Vec2i>& rect);

		void SetProperty(const std::string& name, const std::string& value);
		void SetProperty(const std::string& name, int value);

		void SetName(const std::string& newName);
		std::string GetName() const;

		void SetRelativePoint(RelativePoint relativeTo);
		RelativePoint GetRelativePoint() const;

		void SetParent(std::shared_ptr<Widget> parent);

		virtual void Draw() const;

		virtual void Update();

		Widget() = default;
		Widget(std::shared_ptr<Widget> parent, RelativePoint relativeTo = RelativePoint::None);
		Widget(const Widget&) = default;
		Widget(Widget&& rhs) = default;
		Widget& operator=(const Widget&) = default;
		Widget& operator=(Widget&&) = default;
		virtual ~Widget() = default;
	};
}
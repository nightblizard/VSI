#pragma once
#include <string>
#include "../Widgets/Widget.h"
#include <cinder/Camera.h>

namespace Scenes
{
	class Scene : public std::enable_shared_from_this<Scene>
	{
	protected:
		cinder::CameraOrtho mCamera;
		cinder::Vec3f mEye{ 0.0f, 0.0f, 100.f };
		cinder::Vec3f mCenter = cinder::Vec3f::zero();
		cinder::Vec3f mUp = cinder::Vec3f(0, 1, 0);

		std::string mName;
		
		std::vector<std::shared_ptr<Widgets::Widget>> mWidgets;

	public:
		Scene(std::string name);

		virtual void OnMouseDown(cinder::app::MouseEvent& event);
		virtual void OnMouseUp(cinder::app::MouseEvent& event);
		virtual void OnMouseDrag(cinder::app::MouseEvent& event);

		virtual void AddWidget(std::shared_ptr<Widgets::Widget> widget);
		virtual void RemoveWidget(std::shared_ptr<Widgets::Widget> widget);

		std::string GetName() const;

		virtual void Draw();
		virtual void Update();

		virtual ~Scene() = default;
	};
}
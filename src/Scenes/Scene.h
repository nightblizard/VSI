#pragma once
#include <string>
#include "../Widgets/Widget.h"

namespace Scenes
{
	class Scene : public std::enable_shared_from_this<Scene>
	{
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
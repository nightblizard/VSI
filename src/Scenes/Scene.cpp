#include "Scene.h"


namespace Scenes
{
	Scene::Scene(std::string name) :
		mName(name)
	{
	}


	void Scene::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mWidgets);
		auto end = std::rend(mWidgets);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnEvent<cinder::app::MouseEvent, Widgets::Event::MouseDown>(event);
	}


	void Scene::OnMouseUp(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mWidgets);
		auto end = std::rend(mWidgets);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnEvent<cinder::app::MouseEvent, Widgets::Event::MouseUp>(event);
	}


	void Scene::OnMouseDrag(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mWidgets);
		auto end = std::rend(mWidgets);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnEvent<cinder::app::MouseEvent, Widgets::Event::MouseDrag>(event);
	}


	void Scene::AddWidget(std::shared_ptr<Widgets::Widget> widget)
	{
		mWidgets.push_back(widget);
	}


	void Scene::RemoveWidget(std::shared_ptr<Widgets::Widget> widget)
	{
		mWidgets.erase(std::remove(std::begin(mWidgets), std::end(mWidgets), widget), std::end(mWidgets));
	}


	std::string Scene::GetName() const
	{
		return mName;
	}


	void Scene::Draw()
	{
		for (auto& widget : mWidgets)
			widget->Draw();
	}


	void Scene::Update()
	{
		for (auto& widget : mWidgets)
			widget->Update();
	}
}
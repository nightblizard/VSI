#include "../stdafx.h"
#include "Scene.h"


namespace Scenes
{
	Scene::Scene(std::string name) :
		mName(name)
	{
		mCamera.setOrtho(0.f,
						 static_cast<float>(cinder::app::getWindowWidth()),
						 static_cast<float>(cinder::app::getWindowHeight()),
						 0.f, 5.f, 10000.f);

		mEye = cinder::Vec3f(0.f, 0.f, 100);
		mCamera.lookAt(mEye, mCenter, mUp);
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
		cinder::gl::setMatrices(mCamera);
		for (auto& widget : mWidgets)
			widget->Draw();
	}


	void Scene::Update()
	{
		for (auto& widget : mWidgets)
			widget->Update();
	}
}
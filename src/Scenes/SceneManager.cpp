#include "SceneManager.h"



namespace Scenes
{
	void SceneManager::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mScenes);
		auto end = std::rend(mScenes);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnMouseDown(event);
	}


	void SceneManager::OnMouseUp(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mScenes);
		auto end = std::rend(mScenes);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnMouseUp(event);
	}


	void SceneManager::OnMouseDrag(cinder::app::MouseEvent& event)
	{
		auto it = std::rbegin(mScenes);
		auto end = std::rend(mScenes);

		for (; !event.isHandled() && it != end; ++it)
			(*it)->OnMouseDrag(event);
	}

	void SceneManager::AddScene(std::shared_ptr<Scene> scene)
	{
		mScenes.push_back(scene);
	}


	void SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
	{
		mScenes.erase(std::remove(std::begin(mScenes), std::end(mScenes), scene), std::end(mScenes));
	}


	void SceneManager::Draw()
	{
		for (auto& scene : mScenes)
			scene->Draw();
	}

	
	void SceneManager::Update()
	{
		for (auto& scene : mScenes)
			scene->Update();
	}
}
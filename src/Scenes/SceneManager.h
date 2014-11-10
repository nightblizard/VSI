#pragma once
#include "Scene.h"

namespace Scenes
{
	class SceneManager
	{
		std::vector<std::shared_ptr<Scene>> mScenes;

	public:
		void OnMouseDown(cinder::app::MouseEvent& event);
		void OnMouseUp(cinder::app::MouseEvent& event);
		void OnMouseDrag(cinder::app::MouseEvent& event);

		void AddScene(std::shared_ptr<Scene> scene);
		void RemoveScene(std::shared_ptr<Scene> scene);

		void Draw();
		void Update();
	};
}
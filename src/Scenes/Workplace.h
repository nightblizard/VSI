#pragma once
#include "Scene.h"

namespace Scenes
{
	class Workplace : public Scene
	{
		cinder::Color mColor{ 1.f, 0.f, 0.f };

		float mPosX = 224.f;
		float mPosY = 126.f;

		int mMouseDownX;
		int mMouseDownY;

		bool mDrawCursorClickPosition = true;

		cinder::Vec3f mLastMousePosition{0, 0, 0};

		cinder::params::InterfaceGlRef	mParams;

	public:
		Workplace(std::string name);

		void OnMouseDown(cinder::app::MouseEvent& event) override;
		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDrag(cinder::app::MouseEvent& event) override;

		void Draw() override;
		void Update() override;
	};
}
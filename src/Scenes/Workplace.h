#pragma once
#include "Scene.h"

namespace Scenes
{
	class Workplace : public Scene
	{
		cinder::CameraOrtho mCamera;
		cinder::Vec3f mEye{ 0.0f, 0.0f, 100.f };
		cinder::Vec3f mCenter = cinder::Vec3f::zero();
		cinder::Vec3f mUp = cinder::Vec3f(0, 1, 0);

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
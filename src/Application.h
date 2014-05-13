#pragma once

class Application : public cinder::app::AppNative
{
	cinder::CameraOrtho mCam;
	cinder::Vec3f mEye{ 0.0f, 0.0f, 0.f };
	cinder::Vec3f mCenter = cinder::Vec3f::zero();
	cinder::Vec3f mUp = cinder::Vec3f(0, 1, 0);
	float mCameraDistance = 100;

	cinder::Quatf mSceneRotation;

	cinder::Color mColor{ 1.f, 0.f, 0.f };

	float mRatio;
	float posX = 224.f;
	float posY = 126.f;

	int mouseDownX;
	int mouseDownY;

	std::shared_ptr<Widgets::Widget> mFunction;

public:
	void setup();
	void draw();
	void prepareSettings(Settings *settings);
	void update();
	void mouseDrag(cinder::app::MouseEvent event);
	void mouseUp(cinder::app::MouseEvent event);
	void mouseDown(cinder::app::MouseEvent event);

	cinder::params::InterfaceGlRef	mParams;
};
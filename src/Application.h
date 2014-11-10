#pragma once

class Application : public cinder::app::AppNative
{
	cinder::CameraOrtho mCam;
	cinder::Vec3f mEye{ 0.0f, 0.0f, 0.f };
	cinder::Vec3f mCenter = cinder::Vec3f::zero();
	cinder::Vec3f mUp = cinder::Vec3f(0, 1, 0);
	float mCameraDistance = 100;

	cinder::Color mColor{ 1.f, 0.f, 0.f };

	float posX = 224.f;
	float posY = 126.f;

	int mouseDownX;
	int mouseDownY;

	std::shared_ptr<Widgets::Widget> mFunction;
	std::shared_ptr<Widgets::Widget> mFunction2;

public:
	void setup() override;
	void draw() override;
	void prepareSettings(Settings *settings) override;
	void update() override;
	void mouseDrag(cinder::app::MouseEvent event) override;
	void mouseUp(cinder::app::MouseEvent event) override;
	void mouseDown(cinder::app::MouseEvent event) override;

	cinder::params::InterfaceGlRef	mParams;
};
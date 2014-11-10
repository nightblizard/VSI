#pragma once

class Application : public cinder::app::AppNative
{
	std::shared_ptr<Widgets::Widget> mFunction;
	std::shared_ptr<Widgets::Widget> mFunction2;

	Scenes::SceneManager mSceneManager;

public:
	void setup() override;
	void draw() override;
	void prepareSettings(Settings *settings) override;
	void update() override;
	void mouseDrag(cinder::app::MouseEvent event) override;
	void mouseUp(cinder::app::MouseEvent event) override;
	void mouseDown(cinder::app::MouseEvent event) override;
};
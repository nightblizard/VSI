#ifdef _WIN32
#include <Windows.h>
#endif
#include <cinder/app/AppNative.h>
#include <cinder/Rand.h>
#include <list>
#include <cinder/gl/Texture.h>
#include "cinder/ImageIO.h"
#include <cinder/Camera.h>
#include <cinder/params/Params.h>
#include <gl\GL.h>
#include <gl/GLU.h>

#include "DrawableString.h"
#include "CodeStub.h"
#include "Widgets/Widget.h"
#include "Widgets/Function.h"
#include "Widgets/Connector.h"
#include "XML/WidgetBuilder.h"

using namespace cinder;

struct Line
{
	Vec2f pos;
	Color clr;
};

class TestApp : public cinder::app::AppNative
{
	std::vector<Line> mPoints;
	std::vector<std::vector<Line>> mPointList;

	CameraOrtho mCam;
	Vec3f mEye{ 0.0f, 0.0f, 0.f };
	Vec3f mCenter = Vec3f::zero();
	Vec3f mUp = Vec3f(0, 1, 0);
	float mCameraDistance = 100;
	
	Quatf mSceneRotation;

	Color mColor {1.f, 0.f, 0.f};

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
	void mouseDrag(app::MouseEvent event);
	void mouseUp(app::MouseEvent event);
	void mouseDown(app::MouseEvent event);

	void drawPointList(const std::vector<Line>& points);
	params::InterfaceGlRef	mParams;
};

void TestApp::mouseUp(app::MouseEvent event)
{
	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseUp>(event);
}

void TestApp::mouseDown(app::MouseEvent event)
{
	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseDown>(event);

	if(event.isHandled() == false && event.isLeft())
	{
		mouseDownX = event.getX();
		mouseDownY = event.getY();
		std::cout << std::endl;
	}
}

void TestApp::mouseDrag(app::MouseEvent event)
{
	app::MouseEvent e(getWindow(), 0, 0, 0, 0, 0.f, 0);

	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseDrag>(event);

	if (event.isHandled() || event.isRight())
		return;

	auto modifier = event.getNativeModifiers();

	if(modifier == 1) //Left Mouse Button
	{
		int mouseX = event.getX();
		int mouseY = event.getY();
		
		if (mouseX != mouseDownX)
			posX += (mouseX - mouseDownX) * 0.01f * this->getFrameRate();
		if (mouseY != mouseDownY)
			posY += (mouseY - mouseDownY) * 0.01f * this->getFrameRate();


		mouseDownX = event.getX();
		mouseDownY = event.getY();
	}
	else if(modifier == 2) //Right Mouse Button
	{
	}
	else if(modifier == 16) //Middle Mouse Button
	{
	}
}

void TestApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60);
	settings->setResizable(false);
}

void TestApp::setup()
{
	getForegroundWindow()->setTitle("VSI");
	mParams = params::InterfaceGl::create("Foobar", Vec2i(200, 160));

	mParams->addParam("Scene Rotation:", &mSceneRotation);
	mParams->addParam("Zoom in %:", &mCameraDistance);
	mParams->addParam("px", &posX);
	mParams->addParam("py", &posY);

	mCam.setOrtho(posX, 
				  static_cast<float>(app::getWindowWidth()), static_cast<float>(app::getWindowHeight()),
				  posY, 5.f, 10000.f);

	mRatio = app::getWindowAspectRatio();

#ifdef _WIN32
	HWND wnd = (HWND)getForegroundWindow()->getNative();
	auto style = GetWindowLong(wnd, GWL_STYLE);
	SetWindowLong(wnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
#endif 

	XML::WidgetBuilder wb;
	mFunction = wb.Parse("xml/Foobar.xml");

	//mFunction = std::make_shared<Widgets::Function>();
	//mFunction->SetBounds({ 200, 200 }, { 100, 100 });
	/*
	auto connector = std::make_shared<Widgets::Connector>();
	auto connector2 = std::make_shared<Widgets::Connector>();
	mFunction->AddInput(connector);
	mFunction->AddInput(connector2);*/
}

void TestApp::update()
{
	mEye = Vec3f(0.f, 0.f, 100);
	mCam.lookAt(mEye, mCenter, mUp);

	mCam.setOrtho(posX, 
				  app::getWindowWidth() * mCameraDistance / 100 + posX,
				  app::getWindowHeight() * mCameraDistance / 100 + posY,
				  posY, 5.f, 10000.f);

	mRatio = app::getWindowAspectRatio();
}

void TestApp::draw()
{
	gl::clear(ColorA(0.39f, 0.58f, 0.92f));

	gl::setMatrices(mCam);

	gl::color(cinder::Color::black());
	/*
	using namespace Widgets;
	static auto w = std::make_shared<Widget>();
	w->SetBounds({ 400, 400 }, { 100, 100 });
	w->Draw();

	cinder::gl::color(cinder::Color::white());
	static auto w2 = std::make_shared<Widget>(w, RelativePoint::BottomRight);
	w2->SetBounds({ 0, 0 }, { 50, 50 });
	w2->Draw();
	*/
	gl::color(cinder::Color::black());
	mFunction->Draw();

	/*
	CodeStub cs("Do something", { 400, 400 });
	cs.addInput("Do it!");
	cs.addOutput("Out");
	cs.addVariable("var1");
	cs.addVariable("var2");
	cs.draw();


	CodeStub cs2("Do something different", { 800, 400 });
	cs2.addInput("Do it!");
	cs2.addOutput("Out");
	cs2.addVariable("var1");
	cs2.addVariable("var2");
	cs2.draw();

	gl::disableAlphaBlending();

	/*
	Path2d path;
	path.moveTo(50, 300);
	path.curveTo(75, 300, 75, 400, 100, 400);

	gl::draw(path);
	*/

	mParams->draw();
}
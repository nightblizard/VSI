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

#pragma comment(lib, "cinder.lib")
#pragma comment(lib, "Glu32.lib")

using namespace cinder;

struct Line
{
	Vec2f pos;
	Color clr;
};

Vec3f screenToWorld(const CameraOrtho& cam, Vec2f coords, float dist)
{
	GLdouble wolrdX, worldY, worldZ;
	double clientX, clientY, clientZ;
	GLint viewport[4];

	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT, viewport);

	auto modelView = cam.getModelViewMatrix();
	auto projection = cam.getProjectionMatrix();

	GLdouble mv[16];
	GLdouble proj[16]; 

	for(int i = 0; i < 16; ++i)
	{
		mv[i] = modelView.m[i];
		proj[i] = projection.m[i];
	}

	wolrdX = coords.x;
	worldY = viewport[3] - coords.y; //invert y 
	worldZ = (dist - 5) / (10000 - 5);
	gluUnProject(wolrdX, worldY, worldZ, mv, proj, viewport, &clientX, &clientY, &clientZ);

	return Vec3f{ float(clientX), float(clientY), float(clientZ) };
}


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

	float px = -6, py = -4;

	float mRatio;
	float posX = 224.f;
	float posY = 126.f;

	int mouseDownX;
	int mouseDownY;

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
}

void TestApp::mouseDown(app::MouseEvent event)
{
	if(event.isLeft())
	{
		mouseDownX = event.getX();
		mouseDownY = event.getY();
		std::cout << std::endl;
	}
}

void TestApp::mouseDrag(app::MouseEvent event)
{
	if (event.isRight())
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
	getForegroundWindow()->setTitle("Hello Cinder!");
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
}

void TestApp::drawPointList(const std::vector<Line>& points)
{
	for (unsigned int i = 1; i < points.size(); ++i)
	{
		auto& pos = points[i].pos;
		auto& last = points[i - 1].pos;

		gl::color(points[i].clr);

		gl::drawLine(last, pos);
	}
}

void TestApp::update()
{
	mEye = Vec3f(0.f, 0.f, 100);
	mCam.lookAt(mEye, mCenter, mUp);

	mCam.setOrtho(posX, 
				  app::getWindowWidth() * mCameraDistance / 100 + posX,
				  app::getWindowHeight() * mCameraDistance / 100 + posY,
				  posY, 5.f, 10000.f);

	gl::setMatrices(mCam);

	mRatio = app::getWindowAspectRatio();
}

void TestApp::draw()
{
	gl::clear(ColorA(0.39f, 0.58f, 0.92f));
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::disableAlphaBlending();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	
	glColor4f(1.f, 1.f, 1.f, 1.f);

	gl::pushMatrices();
		mCam.lookAt(Vec3f(0.f, 0.f, 6), mCenter, mUp);
		gl::setMatrices(mCam);

		gl::translate(4, 3);
		gl::scale(.5f, .5f, .5f);
		gl::rotate(mSceneRotation);
		gl::drawCoordinateFrame();

	gl::popMatrices();

	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::enableAlphaBlending();

	gl::rotate(mSceneRotation);


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


CINDER_APP_NATIVE(TestApp, cinder::app::RendererGl)
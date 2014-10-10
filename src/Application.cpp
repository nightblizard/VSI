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

#include "Application.h"

using namespace cinder;

Vec3f mousePos(0, 0, 0);

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

	for (int i = 0; i < 16; ++i)
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

int GetInitiator(app::MouseEvent event)
{
	int initiator = 0;
	if (event.isLeft())
		initiator |= cinder::app::MouseEvent::LEFT_DOWN;
	if (event.isRight())
		initiator |= cinder::app::MouseEvent::RIGHT_DOWN;
	if (event.isMiddle())
		initiator |= cinder::app::MouseEvent::MIDDLE_DOWN;

	return initiator;
}


void Application::mouseUp(app::MouseEvent event)
{
	auto mousePosition = screenToWorld(mCam, cinder::Vec2f{ (float)event.getX(), (float)event.getY() }, mCameraDistance);
	app::MouseEvent ev(getWindow(), GetInitiator(event), mousePosition[0], mousePosition[1], 0, event.getWheelIncrement(), event.getNativeModifiers());

	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseUp>(ev);
	mFunction2->OnEvent<app::MouseEvent, Widgets::Event::MouseUp>(ev);
}


void Application::mouseDown(app::MouseEvent event)
{
	auto mousePosition = screenToWorld(mCam, cinder::Vec2f{ (float)event.getX(), (float)event.getY() }, mCameraDistance);
	app::MouseEvent ev(getWindow(), GetInitiator(event), mousePosition[0], mousePosition[1], 0, event.getWheelIncrement(), event.getNativeModifiers());

	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseDown>(ev);
	mFunction2->OnEvent<app::MouseEvent, Widgets::Event::MouseDown>(ev);

	if (ev.isHandled() == false && ev.isLeft())
	{
		mouseDownX = event.getX();
		mouseDownY = event.getY();
	}

	mousePos = mousePosition;
}


void Application::mouseDrag(app::MouseEvent event)
{
	auto mousePosition = screenToWorld(mCam, cinder::Vec2f{ (float)event.getX(), (float)event.getY() }, mCameraDistance);
	app::MouseEvent ev(getWindow(), GetInitiator(event), mousePosition[0], mousePosition[1], 0, event.getWheelIncrement(), event.getNativeModifiers());

	mFunction->OnEvent<app::MouseEvent, Widgets::Event::MouseDrag>(ev);
	mFunction2->OnEvent<app::MouseEvent, Widgets::Event::MouseDrag>(ev);

	if (ev.isHandled() || ev.isRight())
		return;

	auto modifier = ev.getNativeModifiers();

	if (modifier == 1) //Left Mouse Button
	{
		int mouseX = event.getX();
		int mouseY = event.getY();

		if (mouseX != mouseDownX)
			posX += (mouseX - mouseDownX) * 0.01f * this->getFrameRate();
		if (mouseY != mouseDownY)
			posY += (mouseY - mouseDownY) * 0.01f * this->getFrameRate();


		mouseDownX = event.getX();
		mouseDownY = event.getY();
	} else if (modifier == 2) //Right Mouse Button
	{
	} else if (modifier == 16) //Middle Mouse Button
	{
	}
}


void Application::prepareSettings(Settings *settings)
{
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60);
	settings->setResizable(false);
}


void Application::setup()
{
	getForegroundWindow()->setTitle("VSI");
	mParams = params::InterfaceGl::create("Foobar", Vec2i(200, 160));

	mParams->addParam("Zoom in %:", &mCameraDistance);
	mParams->addParam("px", &posX);
	mParams->addParam("py", &posY);

	mCam.setOrtho(posX,
				  static_cast<float>(app::getWindowWidth()), static_cast<float>(app::getWindowHeight()),
				  posY, 5.f, 10000.f);

#ifdef _WIN32
	HWND wnd = (HWND)getForegroundWindow()->getNative();
	auto style = GetWindowLong(wnd, GWL_STYLE);
	SetWindowLong(wnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
#endif 

	XML::WidgetBuilder wb;
	mFunction = wb.Parse("xml/Foobar.xml");
	mFunction2 = wb.Parse("xml/Foobar2.xml");
}


void Application::update()
{
	mEye = Vec3f(0.f, 0.f, 100);
	mCam.lookAt(mEye, mCenter, mUp);

	mCam.setOrtho(posX,
				  app::getWindowWidth() * mCameraDistance / 100 + posX,
				  app::getWindowHeight() * mCameraDistance / 100 + posY,
				  posY, 5.f, 10000.f);
}


void Application::draw()
{
	gl::clear(ColorA(0.39f, 0.58f, 0.92f));

	gl::setMatrices(mCam);

	gl::color(cinder::Color::black());
	mFunction->Draw();
	mFunction2->Draw();

	cinder::gl::color(cinder::Color::black());
	gl::drawSolidCircle(cinder::Vec2f(mousePos[0], mousePos[1]), 4);

	mParams->draw();
}


CINDER_APP_NATIVE(Application, cinder::app::RendererGl)
#include <cinder/Camera.h>
#include <cinder/Color.h>

#include "../stdafx.h"

#include "Workplace.h"

cinder::Vec3f screenToWorld(const cinder::CameraOrtho& cam, cinder::Vec2f coords, float dist)
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
	worldY = viewport[3] - coords.y;
	worldZ = (dist - 5) / (10000 - 5);
	gluUnProject(wolrdX, worldY, worldZ, mv, proj, viewport, &clientX, &clientY, &clientZ);

	return cinder::Vec3f{ float(clientX), float(clientY), float(clientZ) };
}


int GetInitiator(cinder::app::MouseEvent event)
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


cinder::app::MouseEvent UpdateEventMouseCoordinates(cinder::app::MouseEvent event, cinder::CameraOrtho& camera,
													cinder::Vec3f* optOutPosition = nullptr)
{
	auto mousePosition = screenToWorld(camera, cinder::Vec2f{ (float)event.getX(), (float)event.getY() }, 100);

	cinder::app::MouseEvent ev(event.getWindow(), GetInitiator(event), mousePosition[0], mousePosition[1], 0, 
							   event.getWheelIncrement(), event.getNativeModifiers());

	if (optOutPosition)
		*optOutPosition = mousePosition;

	return ev;
}

namespace Scenes
{
	Workplace::Workplace(std::string name) :
		Scene(name)
	{
		mCamera.setOrtho(mPosX,
						 static_cast<float>(cinder::app::getWindowWidth()), 
						 static_cast<float>(cinder::app::getWindowHeight()),
					  mPosY, 5.f, 10000.f);

		mEye = cinder::Vec3f(0.f, 0.f, 100);
		mCamera.lookAt(mEye, mCenter, mUp);

		mParams = cinder::params::InterfaceGl::create("Foobar", cinder::Vec2i(200, 160));

		mParams->addParam("px", &mPosX);
		mParams->addParam("py", &mPosY);
		mParams->addParam("cursor", &mDrawCursorClickPosition);
	}


	void Workplace::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto ev = UpdateEventMouseCoordinates(event, mCamera, &mLastMousePosition);
		Scene::OnMouseDown(ev);

		if (ev.isHandled() == false && ev.isLeft())
		{
			mMouseDownX = event.getX();
			mMouseDownY = event.getY();
		}
		event.setHandled(ev.isHandled());
	}


	void Workplace::OnMouseUp(cinder::app::MouseEvent& event)
	{
		auto ev = UpdateEventMouseCoordinates(event, mCamera);
		Scene::OnMouseUp(ev);
		
		event.setHandled(ev.isHandled());
	}


	void Workplace::OnMouseDrag(cinder::app::MouseEvent& event)
	{
		auto ev = UpdateEventMouseCoordinates(event, mCamera);
		Scene::OnMouseDrag(ev);

		event.setHandled(ev.isHandled());
		
		if (ev.isHandled() || ev.isRight())
			return;

		auto modifier = ev.getNativeModifiers();

		if (modifier == 1) //Left Mouse Button
		{
			int mouseX = event.getX();
			int mouseY = event.getY();
			
			if (mouseX != mMouseDownX)
				mPosX += (mouseX - mMouseDownX) * 0.01f * cinder::app::getFrameRate();
			if (mouseY != mMouseDownY)
				mPosY += (mouseY - mMouseDownY) * 0.01f * cinder::app::getFrameRate();


			mMouseDownX = event.getX();
			mMouseDownY = event.getY();
		} else if (modifier == 2) //Right Mouse Button
		{
		} else if (modifier == 16) //Middle Mouse Button
		{
		}
		
	}


	void Workplace::Draw()
	{
		cinder::gl::setMatrices(mCamera);
		Scene::Draw();

		cinder::gl::color(cinder::Color::black());
		if (mDrawCursorClickPosition)
			cinder::gl::drawSolidCircle(cinder::Vec2f(mLastMousePosition[0], mLastMousePosition[1]), 4);

		mParams->draw();
	}


	void Workplace::Update()
	{
		using namespace cinder;
		cinder::gl::clear(cinder::ColorA(0.39f, 0.58f, 0.92f));
		Scene::Update();

		
		mCamera.setOrtho(mPosX,
						 1500 + mPosX,
						 900 + mPosY,
						 mPosY, 5.f, 10000.f);
	}
}
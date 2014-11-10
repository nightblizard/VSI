#ifdef _WIN32
#include <Windows.h>
#endif
#include <cinder/app/AppNative.h>
#include <cinder/Rand.h>
#include <list>
#include "DrawableString.h"
#include "CodeStub.h"
#include "Widgets/Widget.h"
#include "Widgets/Function.h"
#include "Widgets/Connector.h"
#include "XML/WidgetBuilder.h"

#include "Config/ConfigFile.h"
#include "Config/SimpleParser.h"

#include "stdafx.h"
#include "Scenes/SceneManager.h"
#include "Scenes/Workplace.h"

#include "Application.h"


using namespace cinder;


void Application::mouseUp(app::MouseEvent event)
{
	mSceneManager.OnMouseUp(event);
}


void Application::mouseDown(app::MouseEvent event)
{
	mSceneManager.OnMouseDown(event);
}


void Application::mouseDrag(app::MouseEvent event)
{
	mSceneManager.OnMouseDrag(event);
}


void Application::prepareSettings(Settings *settings)
{
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60);
	settings->setResizable(false);

	try
	{
		std::unique_ptr<Config::IParser> parser = std::make_unique<Config::SimpleParser>();
		Config::ConfigFile cfgFile("config/config.cfg", *parser);

		auto width = cfgFile.GetValueOrDefault("width", 800);
		auto height = cfgFile.GetValueOrDefault("height", 600);
		auto framerate = cfgFile.GetValueOrDefault("framerate", 60.f);
		auto resizeable = cfgFile.GetValueOrDefault("resizeable", false);
		auto borderless = cfgFile.GetValueOrDefault("borderless", false);
		auto alwaysOnTop = cfgFile.GetValueOrDefault("alwaysOnTop", false);
		auto console = cfgFile.GetValueOrDefault("console", false);

		settings->setWindowSize(width, height);
		settings->setFrameRate(framerate);
		settings->setResizable(resizeable);
		settings->setBorderless(borderless);
		settings->setAlwaysOnTop(alwaysOnTop);
#ifdef CINDER_MSW
		settings->enableConsoleWindow(console);

		int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
		int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

		settings->setWindowPos(x, y);
#endif
	}
	catch(std::exception& e)
	{
#ifdef CINDER_MSW
		MessageBoxA(nullptr, e.what(), "Error!", 0);
#endif
	}
}


void Application::setup()
{
	getForegroundWindow()->setTitle("VSI");

#ifdef _WIN32
	HWND wnd = (HWND)getForegroundWindow()->getNative();
	auto style = GetWindowLong(wnd, GWL_STYLE);
	SetWindowLong(wnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
#endif 

	XML::WidgetBuilder wb;

	auto mFunction = wb.Parse("xml/Foobar.xml");
	auto mFunction2 = wb.Parse("xml/Foobar2.xml");
	auto scene = std::make_shared<Scenes::Workplace>("Workplace");
	scene->AddWidget(mFunction);
	scene->AddWidget(mFunction2);
	mSceneManager.AddScene(scene);

	auto panel = wb.Parse("xml/Testing.xml");
	auto uiScene = std::make_shared<Scenes::Scene>("Menu");
	uiScene->AddWidget(panel);
	mSceneManager.AddScene(uiScene);
}


void Application::update()
{
	mSceneManager.Update();
}


void Application::draw()
{
	mSceneManager.Draw();
}


CINDER_APP_NATIVE(Application, cinder::app::RendererGl)
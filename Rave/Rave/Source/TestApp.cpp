#include "Include/TestApp.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(L"Rave Application", 800, 600),
	shape(Triangle(gfx, 0, 0, .5, FColors::RaveYellow, true, true))
{
	wnd.background = FColors::RaveBlue;
}

void TestApp::Update(const float dt)
{
	shape.Bind(gfx);
}
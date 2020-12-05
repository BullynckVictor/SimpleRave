#include "Include/TestApp.h"
#include <fstream>

using namespace rave;

TestApp::TestApp()
	:
	Application(L"window yesssir", 800, 600),
	shape(Triangle(gfx, FColors::Cyan, 0, .5f, false, false))
{
	wnd.SetVSync(false);
	wnd.background = FColors::Red;
}

void TestApp::Update(const float dt)
{
	const float s = (sinf(timer.Peek()) + 1.0f) / 2.0f;
	wnd.background.r = s;

	shape.Bind(gfx);
}
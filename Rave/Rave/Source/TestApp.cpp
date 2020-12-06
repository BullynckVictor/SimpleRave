#include "Include/TestApp.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(
		L"Rave Application", 800, 600,
		{
			{ "kappa", L"Assets/Kappa.png" }
		}
	),
	shape(Triangle(gfx, 0, 0, .5f, FColors::RaveYellow)),
	cursor(Rect(gfx, 0, .01f, .01f, 45, FColors::White, false)),
	kappa(gfx, memory, "kappa", {})
{
	wnd.background = FColors::RaveBlue;
	wnd.SetAlphaBlending(true);
}

void TestApp::Update(const float dt)
{
	static constexpr float speed = 1.0f;

	ControllCamera(dt);

	r += dt;
	cursor.transform.Write(gfx, Transform(MousePos(), 1, Radian(45)).viewMatrix);
	shape.transform.Write(gfx, Transform(0, 1, r).Concatonate());

	shape.Bind(gfx);
	kappa.Bind(gfx);
	cursor.Bind(gfx);
}
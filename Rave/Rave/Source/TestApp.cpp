#include "Include/TestApp.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(
		L"Rave Application", 800, 600,
		{
			{ "kappa", L"Assets/Kappa.png" },
			{ "mario", L"Assets/Mario.png" },
			{ "knight", L"Assets/knight walk.gif" }
		}
	),
	shape(Triangle(gfx, 0, 0, .5f, FColors::RaveYellow)),
	cursor(Rect(gfx, 0, .01f, .01f, 45, FColors::White, false)),
	kappa(gfx, memory, "kappa", {}),
	mario(gfx, memory, "mario", {}, true),
	knight(gfx, memory, { AnimationState(gfx, memory, "knight", 8) }, {}, 12, true)
{
	wnd.background = FColors::RaveBlue;
}

void TestApp::Update(const float dt)
{
	static constexpr float speed = 1.0f;

	ControllCamera(dt);

	r += dt;
	cursor.transform.Write(gfx, Transform(MousePos(), 1, Radian(45)).viewMatrix);
	shape.transform.Write(gfx, Transform(0, 1, r).Concatonate());
	mario.transform.Write(gfx, Transform(0, .75f, r).Concatonate());
	kappa.transform.Write(gfx, Transform().Concatonate());
	knight.transform.Write(gfx, Transform().Concatonate());

//	shape.Bind(gfx);
//	kappa.Bind(gfx);
//	mario.Bind(gfx);
	knight.Bind(gfx);
	cursor.Bind(gfx);
}
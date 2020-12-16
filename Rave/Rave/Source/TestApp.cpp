#include "Include/TestApp.h"

#include "Engine/Graphics/Include/TextureUAV.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(L"Rave Application", 800, 600)
{
	wnd.background = FColors::RaveBlue;

	LoadTexture("kappa", L"Assets/Kappa.png");
	LoadTexture("mario", L"Assets/Mario.png");
	LoadTexture("knight", L"Assets/knight walk.gif");

	shape = Triangle(gfx, 0, 0, .5f, FColors::RaveYellow);
	cursor = Rect(gfx, 0, .01f, .01f, 45, FColors::White, false);
	kappa.Load(gfx, memory, "kappa", {});
	mario.Load(gfx, memory, "mario", {}, true);
	knight.Load(gfx, memory, { AnimationState(gfx, memory, "knight", 8) }, {}, 12, true);
}

void TestApp::Update(const float dt)
{
	static constexpr float speed = 1.0f;

	ControllCamera(dt);

	r += dt;
	cursor.transform.Write(gfx, Transform(MousePos(), 1, Radian(45)).viewMatrix);
	shape.transform.Write(gfx, Transform(0, 1, r).viewMatrix);
	mario.transform.Write(gfx, Transform().viewMatrix);
	kappa.transform.Write(gfx, Transform(MousePos(), 1, 0).viewMatrix);
	knight.transform.Write(gfx, Transform(0, .75f, 0).viewMatrix);

	shape.Bind(gfx);
	kappa.Bind(gfx);
	mario.Bind(gfx);
	knight.Bind(gfx);
	cursor.Bind(gfx);
}
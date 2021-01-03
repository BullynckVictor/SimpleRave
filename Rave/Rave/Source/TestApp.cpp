#include "Include/TestApp.h"

#include "Engine/Graphics/Include/TextureUAV.h"
#include "Engine/Utilities/Include/Vector.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(L"Rave Application", 800, 600)
{
	wnd.Bind();

	wnd.background = FColors::RaveBlue;
	wnd.SetVSync(false);

	LoadTexture("kappa", L"Assets/Kappa.png");
	LoadTexture("mario", L"Assets/Mario.png");
	LoadTexture("knight", L"Assets/knight walk.gif");

	debugText.string = L"Hello World!";
	debugText.pos = { -wnd.GetSize().relative.view.x, wnd.GetSize().relative.view.y };
	LoadText(debugText, L"Consolas", 1.0f / 10.0f, FColors::White);

	shape = Triangle(gfx, 0, 0, .5f, FColors::White);
	cursor = Rect(gfx, 0, .01f, .01f, 45, FColors::White, false);

	kappa.Load(gfx, memory, "kappa", {});
	mario.Load(gfx, memory, "mario", {}, true);
	knight.Load(gfx, memory, "knight", 8, {}, 12, true);
}

void TestApp::Update(const float dt)
{
	ControllCamera(dt);

	r += dt;
	Vector2 mpos = MousePos();
	cursor.WriteTransform(gfx, Transform2(0, 1, Radian(45)));
	shape.WriteTransform(gfx, Transform2(0, 1, r));
	mario.WriteTransform(gfx, {});
	kappa.WriteTransform(gfx, Transform2(0, 1, 0));
	knight.WriteTransform(gfx, Transform2(0, .75f, 0));

	Render(knight,	textureR);
	Render(cursor,	flatR);
	RenderGUI(debugText);
}
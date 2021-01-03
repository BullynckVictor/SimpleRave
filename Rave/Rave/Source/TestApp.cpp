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

	debugText.string = L"3D POG";
	debugText.pos = { -.3f, .6f };
	LoadText(debugText, L"Arial", 1.0f / 10.0f, FColors::White);

	shape = Triangle(gfx, 0, 0, .5f, FColors::White);
	cursor = Rect(gfx, 0, .01f, .01f, 45, FColors::White, false);

	kappa.Load(gfx, memory, "kappa", {});
	mario.Load(gfx, memory, "mario", {}, true);
	knight.Load(gfx, memory, "knight", 8, {}, 12, true);

	cube.Load(gfx, { 1, 2, 3 }, Transform3({ 0, 0, 4 }, 1, 0));
}

void TestApp::Update(const float dt)
{
	ControllCamera(dt);

	r += dt;
	Vector2 mpos = MousePos();
	cursor.WriteTransform(gfx, Transform2(MousePos(), 1, Radian(45)));
	shape.WriteTransform(gfx, Transform2(0, 1, r));
	mario.WriteTransform(gfx, {});
	kappa.WriteTransform(gfx, Transform2(0, 1, 0));
	knight.WriteTransform(gfx, Transform2(0, .75f, 0));
	cube.transform.Write(gfx, Transform3({ 0,0,4 }, 1, { r / 2.0f, 0, r }).viewMatrix);

	Render(cursor, flatR);
	Render(cube, boxR);
	RenderGUI(debugText);
}
#include "Include/TestApp.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(L"Rave Application", 800, 600),
	shape(Triangle(gfx, 0, 0, .5f, FColors::RaveYellow)),
	cursor(Rect(gfx, 0, .01f, .01f, 45, FColors::White, false))
{
	wnd.background = FColors::RaveBlue;
}

void TestApp::Update(const float dt)
{
	static constexpr float speed = 1.0f;
	Vector2 delta = 0;

	for(size_t c = 0; c < 255; c++)
	{
		if(wnd.kbd.KeyIsPressed((char)c))
			switch (c)
			{
			case 'Q':
			case VK_LEFT:
				delta.x -= 1;
				break;
			case 'D':
			case VK_RIGHT:
				delta.x += 1;
				break;
			case 'Z':
			case VK_UP:
				delta.y += 1;
				break;
			case 'S':
			case VK_DOWN:
				delta.y -= 1;
				break;
			case 'A':
				camera.rotation += speed * dt;
				break;
			case 'E':
				camera.rotation -= speed * dt;
			}
	}
	camera.position += Transform(0, 1, -camera.rotation).GetTransformedPoint(delta.Normalized()) * speed * dt;
	camera.zoom += camera.zoom * -(float)wnd.mouse.GetScrollDelta() / 15.0f;

//	r += dt;
	cursor.transform.Write(gfx, Transform(MousePos(), 1, Radian(45)).viewMatrix);
	shape.transform.Write(gfx, Transform(0, 1, r).Concatonate());

	shape.Bind(gfx);
	cursor.Bind(gfx);
}
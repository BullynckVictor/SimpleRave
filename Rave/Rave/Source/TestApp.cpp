#include "Include/TestApp.h"

#include "Engine/Graphics/Include/TextureUAV.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Utilities/Include/Random.h"

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
	debugText.pos = { -wnd.GetSize().relative.view.width, 1 };
	LoadText(debugText, L"Arial", 1.0f / 30.0f, FColors::White);

	shape = Triangle(gfx, 0, 0, .5f, FColors::White);
	cursor = Rect(gfx, 0, .01f, .01f, 45, FColors::White, false);

	kappa.Load(gfx, memory, "kappa", {});
	mario.Load(gfx, memory, "mario", {}, true);
	knight.Load(gfx, memory, "knight", 8, {}, 12, true);

	Vector3 dim;
	Randomise(dim.data, 1.5, 3);
	cube.material.diffuse = Colors::Red;
	cube.material.specular = Colors::White;
	cube.material.specularIntensity = 0.5f;
	cube.material.specularPower = 8;
	cube.Load(gfx, dim, Transform3({ 0, 0, 4 }, 1, 0));

	Light point;
	point.type		  = Light::Type::Point;
	point.position	  = { -1.0f, 2.0f, -3.5f };
	point.color		  = FColors::White;
	point.attenuation = { 1.0f, 0.045f, 0.0075f };
	lights.lights.push_back(point);
	lights.Load(gfx);

	light.material.diffuse = Colors::White;
	light.Load(gfx, .25f, Transform3(lights.lights[0].position, 1, 0));

	camera3.farPlane = 50.0f;
	camera3.Load(gfx);

	wnd.DisableCursor();
}

void TestApp::Update(const float dt)
{
	ControllCamera(dt * 3.0f);
	if (dt < 1.0f / 60.0f)
	f++;
	Vector2 mpos = MousePos();
	if (!wnd.kbd.KeyIsPressed(VK_RETURN))
		r += dt;

	cursor.WriteTransform(gfx, Transform2(MousePos(), 1, Radian(45)));
	shape.WriteTransform(gfx, Transform2(0, 1, r));
	mario.WriteTransform(gfx, {});
	kappa.WriteTransform(gfx, Transform2(0, 1, 0));
	knight.WriteTransform(gfx, Transform2(0, .75f, 0));
	cube.WriteTransform(gfx, Transform3({ 0,0,4 }, 1, 0));
	cube.WriteTransform(gfx, Transform3({ 0,0,4 + r / 5 }, 1, { r / 2.0f, 0, r }));
	light.WriteTransform(gfx, Transform3(lights.lights[0].position, 1, 0));


	debugText.string  = L"x: " + Widen(ToString(camera3.position.view.x)) + L'\n';
	debugText.string += L"y: " + Widen(ToString(camera3.position.view.y)) + L'\n';
	debugText.string += L"z: " + Widen(ToString(camera3.position.view.z)) + L'\n';
	UpdateText(debugText);

	camera3.Write(gfx);
	camera3.Bind(gfx);

	lights.Bind(gfx);
	Render(cube, renderer3D);
	Render(light, flat3D);
	RenderGUI(debugText);
}
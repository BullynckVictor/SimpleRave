#include "Include/TestApp.h"

#include "Engine/Graphics/Include/TextureUAV.h"

using namespace rave;

TestApp::TestApp()
	:
	Application(L"Rave Application", 800, 600, PreLoad),
	shape(Triangle(gfx, 0, 0, .5f, FColors::RaveYellow)),
	cursor(Rect(gfx, 0, .01f, .01f, 45, FColors::White, false)),
	kappa(gfx, memory, "kappa", {}),
	mario(gfx, memory, "perlin", {}, true),
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
	mario.transform.Write(gfx, Transform().Concatonate());
	kappa.transform.Write(gfx, Transform().Concatonate());
	knight.transform.Write(gfx, Transform(0, .75f, 0).Concatonate());

//	shape.Bind(gfx);
//	kappa.Bind(gfx);
	mario.Bind(gfx);
//	knight.Bind(gfx);
//	cursor.Bind(gfx);
}

void TestApp::PreLoad(Graphics& gfx, GraphicsMemory& memory)
{
	ImageDecoder decoder;
	LoadTexture(gfx, memory, decoder, "kappa", L"Assets/Kappa.png");
	LoadTexture(gfx, memory, decoder, "mario", L"Assets/Mario.png");
	LoadTexture(gfx, memory, decoder, "knight", L"Assets/knight walk.gif");

	ComputeShader cs(gfx, L"Engine/Graphics/ShaderBins/Perlin.cso");

	Texture perlin(gfx, 800, 600, 4, DXGI_FORMAT_R8G8B8A8_UNORM, nullptr, bindTextureView | bindTextureUAV);
	memory.textureCodex.Add("perlin", TextureView(gfx, perlin));
	TextureUAV uav(gfx, perlin);

	cs.Run(gfx, {}, { uav }, 800, 600, 0);
}
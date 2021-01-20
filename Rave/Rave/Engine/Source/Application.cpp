#include "Engine/Include/Application.h"
#include "Engine/Utilities/Include/Exception.h"
#include "Engine/Include/RaveEngine.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
	wnd(gfx, windowName, width, height, useMouseEvents, useMouseRawDeltas, className)
{
	memory.inputLayoutCodex.Add(  "position2",	InputLayout().Load( gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso",	{InputLayoutElement("Position", DXGI_FORMAT_R32G32_FLOAT,	sizeof(Vertex2))}));
	memory.inputLayoutCodex.Add(  "texture",	InputLayout().Load( gfx, L"Engine/Graphics/ShaderBins/TextureVS.cso",	{InputLayoutElement("Position", DXGI_FORMAT_R32G32_FLOAT,	sizeof(Vertex2)), InputLayoutElement("TexCoord", DXGI_FORMAT_R32G32_FLOAT,	  sizeof(Vertex2)) }));
	memory.inputLayoutCodex.Add(  "light3",		InputLayout().Load( gfx, L"Engine/Graphics/ShaderBins/Transform3VS.cso",{InputLayoutElement("Position", DXGI_FORMAT_R32G32B32_FLOAT,sizeof(Vertex3)), InputLayoutElement("Normal",	 DXGI_FORMAT_R32G32B32_FLOAT, sizeof(Vertex3)) }));
	memory.vertexShaderCodex.Add( "position",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso"));
	memory.vertexShaderCodex.Add( "transform2",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/Transform2VS.cso"));
	memory.vertexShaderCodex.Add( "transform3",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/Transform3VS.cso"));
	memory.vertexShaderCodex.Add( "texture",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/TextureVS.cso"));
	memory.pixelShaderCodex.Add(  "color",		PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/ColorPS.cso"));
	memory.pixelShaderCodex.Add(  "light3",		PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/Light3PS.cso"));
	memory.pixelShaderCodex.Add(  "flat3",		PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/Flat3PS.cso"));
	memory.pixelShaderCodex.Add(  "texture",	PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/TexturePS.cso"));
	memory.samplerCodex.Add(	  "linear",		Sampler().Load(gfx, D3D11_FILTER_MIN_MAG_MIP_LINEAR));
	memory.samplerCodex.Add(	  "pixel",		Sampler().Load(gfx, D3D11_FILTER_MIN_MAG_MIP_POINT));

	flatR		.Load(gfx, memory, "position2", "color",	"transform2");
	renderer3D	.Load(gfx, memory, "light3",	"light3",	"transform3");
	textureR	.Load(gfx, memory, "texture",	"texture",	"texture");
	flat3D		.Load(gfx, memory, "light3",	"flat3",	"transform3");


	Transform2::pCamera = &camera2;
	Transform3::pCamera = &camera3;
}

void rave::Application::Go()
{
	profiler.Mark();
	profiler.StartSection("Windows");
	while (wnd.HandleMessages())
	{
		profiler.EndSection("Windows");
		profiler.Mark();
		profiler.StartSection("Clear");
		wnd.Clear();
		profiler.EndSection("Clear");
		profiler.StartSection("Update");
		Update(ft.Mark());
		profiler.EndSection("Update");
		profiler.StartSection("Draw");
		wnd.Present();
		profiler.EndSection("Draw");
		profiler.StartSection("Windows");
	}
}

rave::Vector2 rave::Application::MousePos() const noexcept
{
	Vector2 pos = { (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() };
	pos /= { (float)wnd.GetWidth(), (float)wnd.GetHeight() };
	pos.view.x = pos.view.x * 2 - 1;
	pos.view.y = -pos.view.y * 2 + 1;
	pos *= wnd.GetSize().relative;

	rave::Matrix mat =
		DirectX::XMMatrixScaling(camera2.zoom, camera2.zoom, 1)
		* DirectX::XMMatrixRotationZ(camera2.rotation)
		* DirectX::XMMatrixTranslation(camera2.position.view.x, camera2.position.view.y, 0)
		;

	rave::Transform2(mat).TransformPointView(pos);

	return pos;
}

void rave::Application::ControllCamera(const float dt, const float moveSpeed, const float rotationSpeed, const float scrollSpeed) noexcept
{
	Vector2 delta;
	Vector3 delta3;
	float rDelta = 0.0f;

	for (size_t c = 0; c < 255; c++)
	{
		if (wnd.kbd.KeyIsPressed((char)c))
			switch (c)
			{
			case 'Q':
			case VK_LEFT:
				delta.view.x -= 1;
				delta3.view.x -= 1;
				break;
			case 'D':
			case VK_RIGHT:
				delta.view.x += 1;
				delta3.view.x += 1;
				break;
			case 'Z':
			case VK_UP:
				delta.view.y += 1;
				delta3.view.z += 1;
				break;
			case 'S':
			case VK_DOWN:
				delta.view.y -= 1;
				delta3.view.z -= 1;
				break;
			case VK_SPACE:
				delta3.view.y += 1;
				break;
			case VK_SHIFT:
				delta3.view.y -= 1;
				break;

			case 'A':
				rDelta += rotationSpeed * dt;
				break;
			case 'E':
				rDelta -= rotationSpeed * dt;
				break;

			case VK_ESCAPE:
				wnd.Close();
				break;
			}
	}

	float sDelta = -(float)wnd.mouse.GetScrollDelta();

	camera2.rotation += rDelta;
	camera2.position += Transform2(0, 1, -camera2.rotation).GetTransformedPoint(delta.Normalized()) * moveSpeed * dt;
	camera2.zoom += camera2.zoom * sDelta / scrollSpeed;

	Vector3 mDelta;
	while (const auto d = wnd.mouse.GetRawDelta())
		mDelta += { (float)d->y, (float)d->x, 0 };

	camera3.rotation.view.z += rDelta;
	camera3.rotation += mDelta * dt; //Transform3(0, 1, Vector3() - camera3.rotation).GetTransformedPoint(mDelta.Normalized()) * dt;
	camera3.position += Transform3(0, 1, Vector3() - camera3.rotation).GetTransformedPoint(delta3.Normalized()) * moveSpeed * dt;
	camera3.position.view.z += -sDelta / scrollSpeed;

	camera3.Concatonate();
}

void rave::Application::LoadTexture(const char* key, const wchar_t* path)
{
	UINT width;
	UINT height;
	memory.textureCodex.Add(key, TextureView().Load(gfx, Texture().Load(gfx, decoder, 4, DXGI_FORMAT_R8G8B8A8_UNORM, path, &width, &height)));
	memory.sizeCodex.Add(key, Vector2({ (float)width, (float)height }));
}

void rave::Application::LoadText(Text& text, const wchar_t* font, const float size, const FColor& color, Vector2 boundingSize)
{
	text.Load(gfx, wnd.GetRenderTarget(), font, size, color, boundingSize);
}

void rave::Application::UpdateText(Text& text, const Vector2& boundingSize)
{
	text.Update(gfx, wnd.GetRenderTarget(), boundingSize);
}

void rave::Application::RenderGUI(const Text& object)
{
	object.Bind(wnd.GetRenderTarget());
}

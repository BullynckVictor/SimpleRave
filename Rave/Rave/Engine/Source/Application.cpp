#include "Engine/Include/Application.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
	wnd(gfx, windowName, width, height, useMouseEvents, useMouseEvents, className),
	camera(Transform::camera)
{
	memory.inputLayoutCodex.Add(  "position",	InputLayout().Load( gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso", {InputLayoutElement("Position", DXGI_FORMAT_R32G32_FLOAT, sizeof(Vertex))}));
	memory.inputLayoutCodex.Add(  "texture",	InputLayout().Load( gfx, L"Engine/Graphics/ShaderBins/TextureVS.cso", {InputLayoutElement("Position", DXGI_FORMAT_R32G32_FLOAT, sizeof(Vertex)), InputLayoutElement("TexCoord", DXGI_FORMAT_R32G32_FLOAT, sizeof(Vertex)) }));
	memory.vertexShaderCodex.Add( "position",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso"));
	memory.vertexShaderCodex.Add( "transform",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/TransformVS.cso"));
	memory.vertexShaderCodex.Add( "texture",	VertexShader().Load(gfx, L"Engine/Graphics/ShaderBins/TextureVS.cso"));
	memory.pixelShaderCodex.Add(  "color",		PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/ColorPS.cso"));
	memory.pixelShaderCodex.Add(  "texture",	PixelShader().Load( gfx, L"Engine/Graphics/ShaderBins/TexturePS.cso"));
	memory.samplerCodex.Add(	  "linear",		Sampler().Load(gfx, D3D11_FILTER_MIN_MAG_MIP_LINEAR));
	memory.samplerCodex.Add(	  "pixel",		Sampler().Load(gfx, D3D11_FILTER_MIN_MAG_MIP_POINT));

	Shape::StaticInitialize(gfx, memory);
	Sprite::StaticInitialize(gfx, memory);
	Animation::StaticInitialize(gfx, memory);
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
	pos.x = pos.x * 2 - 1;
	pos.y = -pos.y * 2 + 1;
	pos *= camera.size;

	rave::Matrix mat =
		DirectX::XMMatrixScaling(camera.zoom, camera.zoom, 1)
		* DirectX::XMMatrixRotationZ(camera.rotation)
		* DirectX::XMMatrixTranslation(camera.position.x, camera.position.y, 0)
		;

	rave::Transform(mat).TransformPointView(pos);

	return pos;
}

void rave::Application::ControllCamera(const float dt, const float moveSpeed, const float rotationSpeed, const float scrollSpeed) noexcept
{
	Vector2 delta;

	for (size_t c = 0; c < 255; c++)
	{
		if (wnd.kbd.KeyIsPressed((char)c))
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
				camera.rotation += rotationSpeed * dt;
				break;
			case 'E':
				camera.rotation -= rotationSpeed * dt;
			}
	}
	camera.position += Transform(0, 1, -camera.rotation).GetTransformedPoint(delta.Normalized()) * moveSpeed * dt;
	camera.zoom += camera.zoom * -(float)wnd.mouse.GetScrollDelta() / scrollSpeed;
}

void rave::Application::LoadTexture(const char* key, const wchar_t* path)
{
	UINT width;
	UINT height;
	memory.textureCodex.Add(key, TextureView().Load(gfx, Texture().Load(gfx, decoder, 4, DXGI_FORMAT_R8G8B8A8_UNORM, path, &width, &height)));
	memory.sizeCodex.Add(key, Vector2((float)width, (float)height));
}
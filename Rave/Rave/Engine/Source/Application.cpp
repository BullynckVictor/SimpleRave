#include "Engine/Include/Application.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
	wnd(gfx, windowName, width, height, useMouseEvents, useMouseEvents, className),
	camera(Transform::camera)
{
	Initialize();
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

void rave::Application::Initialize()
{
	memory.inputLayoutCodex.Add( "position", InputLayout( gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso", {InputLayoutElement("Position", DXGI_FORMAT_R32G32_FLOAT, sizeof(Vertex))}));
	memory.vertexShaderCodex.Add("position", VertexShader(gfx, L"Engine/Graphics/ShaderBins/PositionVS.cso"));
	memory.vertexShaderCodex.Add("transform", VertexShader(gfx, L"Engine/Graphics/ShaderBins/TransformVS.cso"));
	memory.pixelShaderCodex.Add("color", PixelShader(gfx, L"Engine/Graphics/ShaderBins/ColorPS.cso"));

	Shape::StaticInitialize(gfx, memory);
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

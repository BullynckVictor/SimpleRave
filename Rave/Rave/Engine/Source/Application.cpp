#include "Engine/Include/Application.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
	wnd(gfx, windowName, width, height, useMouseEvents, useMouseEvents, className)
{
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
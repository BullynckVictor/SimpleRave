#include "Engine/Include/Application.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
	wnd(gfx, windowName, width, height, useMouseEvents, useMouseEvents, className)
{
}

void rave::Application::Go()
{
	while(wnd.HandleMessages())
		Update(ft.Mark());
}
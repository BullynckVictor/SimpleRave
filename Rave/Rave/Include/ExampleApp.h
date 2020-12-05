#pragma once
#include "Engine/Include/RaveEngine.h"

class ExampleApp : public rave::Application
{
public:
	ExampleApp()
		:
		Application(L"Rave Application", 800, 600)
	{
		wnd.background = rave::FColors::Blue;
	}

private:
	void Update(const float dt) override
	{
		shape.Bind(gfx);
	}

private:
	rave::Shape shape = rave::Triangle(gfx, 0, 0, .5, rave::FColors::Yellow);
};
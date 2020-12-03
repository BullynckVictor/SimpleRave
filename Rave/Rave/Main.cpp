#pragma once
#include "Engine/Header/Application.h"

class TestApp : public rave::Application
{
public:
	TestApp()
		:
		Application(L"yes", 900, 600)
	{}

private:
	void Update(const float dt) override
	{
		rave_throw_message("hello world");
	}
};

int rave_main()
{
	TestApp app;
	app.Go();
}
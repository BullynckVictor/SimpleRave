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
		rave_assert_info(1 == 0, L"Now you know that ain't right!");
	}
};

int rave_main()
{
	TestApp app;
	app.Go();
}
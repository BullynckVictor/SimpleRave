#pragma once
#include "Engine/Include/RaveEngine.h"

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
	}
};

int rave_main()
{
	rave::Execute<TestApp>();
}
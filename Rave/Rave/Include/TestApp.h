#pragma once
#include "Engine/Include/RaveEngine.h"

class TestApp : public rave::Application
{
public:
	TestApp();
	~TestApp();

private:
	void Update(const float dt) override;
	rave::Timer timer;
};
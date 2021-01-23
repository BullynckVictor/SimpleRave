#pragma once
#include "Engine/Include/RaveEngine.h"

class TestApp : public rave::Application
{
public:
	TestApp();

private:
	void Update(const float dt) override;

private:
	float r = 0.0f;
	uint32_t f = 0;

	rave::Cube cube;
	rave::Cube light;
	rave::Mesh sponza;

	rave::Text debugText;
};
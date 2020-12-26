#pragma once
#include "Engine/Include/RaveEngine.h"

class TestApp : public rave::Application
{
public:
	TestApp();

private:
	void Update(const float dt) override;

private:
	rave::Shape shape;
	rave::Shape cursor;
	rave::Shape debugtri;
	rave::Sprite kappa;
	rave::Sprite mario;
	rave::Animation knight;
	float r = 0.0f;

	rave::Text debugText;
};
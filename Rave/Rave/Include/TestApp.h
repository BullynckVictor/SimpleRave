#pragma once
#include "Engine/Include/RaveEngine.h"

class TestApp : public rave::Application
{
public:
	TestApp();

private:
	void Update(const float dt) override;

private:
	rave::SoundMixer mixer;
	rave::Sound music;
	rave::Shape shape;
	rave::Shape cursor;
	rave::Sprite kappa;
	rave::Sprite mario;
	rave::Animation knight;
	float r = 0.0f;
};
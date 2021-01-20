#include "Engine/Drawables/Include/Light.h"

void rave::LightBuffer::Load(Graphics& gfx, const bool write)
{
	buffer.Load(gfx, lights, DXGI_FORMAT_UNKNOWN, write, true);
}

void rave::LightBuffer::Bind(Graphics& gfx)
{
	buffer.Bind(gfx);
}

void rave::LightBuffer::Write(Graphics& gfx)
{
	Buffer buf = buffer.GetResource();
	buf.Write(gfx, lights);
}

rave::Light::Attenuation::Attenuation(const float constant, const float linear, const float quadratic)
	:
	constant(constant),
	linear(linear),
	quadratic(quadratic)
{
}

rave::Light::Attenuation::Attenuation(const float range)
	:
	constant(1.0f),
	linear(4.5f / range),
	quadratic(75.0f / range)
{
}

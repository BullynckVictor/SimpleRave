#include "Engine/Graphics/Include/ViewPort.h"

rave::ViewPort::ViewPort(const int width, const int height)
{
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
}

void rave::ViewPort::Bind(Graphics& gfx) const noexcept
{
   GetContext(gfx)->RSSetViewports(1u, &vp);
}

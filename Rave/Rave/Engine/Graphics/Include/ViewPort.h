#pragma once
#include "Graphics.h"

namespace rave
{
	class ViewPort : public GraphicsFriend
	{
	public:
		ViewPort(const int width, const int height);
		void Bind(Graphics& gfx) const noexcept;

	private:
		D3D11_VIEWPORT vp;
	};
}
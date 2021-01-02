#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Gui/Include/Gui.h"

namespace rave
{
	class FlatRenderer
	{
	public:
		FlatRenderer& Load(Graphics& gfx, GraphicsMemory& memory, const char* layout, const char* pixelShader, const char* vertexShader);
		template<BindableConcept T>
		void Render(Graphics& gfx, const T& object) const
		{
			pLayout->Bind(gfx);
			pPixelShader->Bind(gfx);
			pVertexShader->Bind(gfx);
			object.Bind(gfx);
		}
		template<GuiConcept T>
		void Render(Graphics& gfx, RenderTarget& target, const T& object) const
		{
			pLayout->Bind(gfx);
			pPixelShader->Bind(gfx);
			pVertexShader->Bind(gfx);
			object.Bind(gfx, target);
		}

	private:
		InputLayout*  pLayout;
		PixelShader*  pPixelShader;
		VertexShader* pVertexShader;
	};
}
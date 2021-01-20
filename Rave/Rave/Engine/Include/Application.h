#pragma once
#include <functional>
#include <optional>
#include "Engine/Utilities/Include/Timer.h"
#include "Engine/Utilities/Include/PerformanceProfiler.h"
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Include/Window.h"
#include "Engine/Include/MemoryManager.h"
#include "Engine/Audio/Include/AudioManager.h"
#include "Engine/Include/ComManager.h"

#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/GUI/Include/Gui.h"
#include "Engine/Drawables/Include/FlatRenderer.h"
#include "Engine/Drawables/Include/Text.h"
#include "Engine/Drawables/Include/Light.h"

namespace rave
{
	class Application
	{
	public:
		Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents = false, const bool useMouseRawDeltas = true, const wchar_t* className = L"RaveEngine Direct3D Class");
		virtual ~Application() {}

		void Go();

	protected:
		virtual void Update(const float dt) = 0;

		Vector2 MousePos() const noexcept;
		void ControllCamera(const float dt, const float moveSpeed = 1.0f, const float rotationSpeed = 1.0f, const float scrollSpeed = 15.0f) noexcept;
		void LoadTexture(const char* key, const wchar_t* path);
		void LoadText(Text& text, const wchar_t* font, const float size, const FColor& color, Vector2 boundingSize = Vector2({ targetSize.relative.view.x, -targetSize.relative.view.y }));
		void UpdateText(Text& text, const Vector2& boundingSize = Vector2({ targetSize.relative.view.x, -targetSize.relative.view.y }));

		template<BindableConcept T>
		void Render(const T& object, const FlatRenderer& renderer)
		{
			renderer.Render(gfx, object);
		}
		template<GuiConcept T>
		void RenderGUI(const T& object, const FlatRenderer& renderer)
		{
			renderer.Render(gfx, wnd.GetRenderTarget(), object);
		}

		void RenderGUI(const Text& object);

	private:
		Timer ft;
		PerformanceProfiler profiler;

	protected:
		Graphics gfx;
		Window wnd;
		GraphicsMemory memory; 
		AudioManager audio;
		Camera2 camera2;
		Camera3 camera3;
		ImageDecoder decoder;

		FlatRenderer flatR;
		FlatRenderer textureR;
		FlatRenderer renderer3D;
		FlatRenderer flat3D;

		LightBuffer lights;
	};
}
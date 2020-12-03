#pragma once
#include "Engine/Graphics/Include/RenderTarget.h"
#include "Engine/Include/Mouse.h"
#include "Engine/Include/Keyboard.h"
#include <string>

namespace rave
{
	class Window
	{
	public:
		Window(Graphics& gfx, const wchar_t* windowName, const int width, const int height, const bool useMouseEvents = false, const bool useMouseRawDeltas = false, const wchar_t* className = L"RaveEngine Direct3D Class");
		~Window() noexcept;

		int GetWidth() const noexcept;
		int GetHeight() const noexcept;

		bool HandleMessages() noexcept;

		const wchar_t* GetTitle() const noexcept;
		void SetTitle(const wchar_t* name) noexcept;

		void EnableCursor() noexcept;
		void DisableCursor() noexcept;
		bool CursorEnabled() const noexcept;
		void ShowCursor() noexcept;
		void HideCursor() noexcept;

		void Close()  const noexcept;
		bool IsOpen() const noexcept;

	public:
		FColor background;

		Mouse mouse;
		Keyboard kbd;

	private:
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK StaticWindowProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		static HWND CreateHWND(const HINSTANCE hInst, const wchar_t* windowName, const int width, const int height, const wchar_t* className, const Window* _this);

		void ConfineCursor() noexcept;
		void FreeCursor() noexcept;

	private:
		HINSTANCE hInstance;
		HWND hwnd;
		std::wstring name;
		const std::wstring className;

		const int width;
		const int height;

		Graphics& gfx;
		SwapChain swap;
		RenderTarget target;

		bool captured = false;
		bool cursorEnabled = true;

		bool open = true;
	};
}
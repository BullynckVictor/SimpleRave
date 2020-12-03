#include "Engine/Header/Application.h"

rave::Application::Application(const wchar_t* windowName, const int width, const int height)
{
}

void rave::Application::Go() noexcept
{
	try
	{
		Update(0);
	}
	catch (rave::Exception& e)
	{
		MessageBox(NULL, e.whide_what(), L"rave::Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBox(NULL, Widen(e.what()).c_str(), L"std::exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(NULL, L"Unknown type caught", L"Unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
}
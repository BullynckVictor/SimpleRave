#include "Engine/Utilities/Header/Exception.h"

rave::Exception::Exception(const std::string& what_) noexcept
	:
	whatBuffer(what_),
	wideWhatBuffer(Widen(what_))
{
}

rave::Exception::Exception(const std::wstring& what_) noexcept
	:
	whatBuffer(Narrow(what_)),
	wideWhatBuffer(what_)
{
}

const char* rave::Exception::what() const noexcept
{
	return whatBuffer.c_str();
}

const wchar_t* rave::Exception::whide_what() const noexcept
{
	return wideWhatBuffer.c_str();
}

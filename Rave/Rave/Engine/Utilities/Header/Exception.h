#pragma once
#include <exception>
#include "Engine/Utilities/Header/String.h"
#include "Engine/Header/Windows.h"

namespace rave
{
	class Exception : public std::exception
	{
	public:
		Exception(const std::string& what) noexcept;
		Exception(const std::wstring& what) noexcept;

		const char* what() const noexcept override;
		const wchar_t* whide_what() const noexcept;

	private:
		const std::wstring wideWhatBuffer;
		const std::string whatBuffer;
	};

	class HrException : public Exception
	{

	};
}

#define rave_throw_message(message) throw rave::Exception(message)
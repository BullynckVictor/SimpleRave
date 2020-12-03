#pragma once
#include <locale>
#include <string>

namespace rave
{
	static std::string Narrow(const std::wstring& string) noexcept
	{
		std::locale loc;
		const size_t length = string.size();

		std::string ret;
		ret.resize(length);
		std::use_facet<std::ctype<wchar_t>>(loc).narrow(string.c_str(), string.c_str() + length + 1, '?', ret.data());

		return ret;
	}

	static std::wstring Widen(const std::string& string) noexcept
	{
		std::locale loc;
		std::wstring ret;
		const size_t len = string.size() + 1;
		ret.resize(len);

		std::use_facet<std::ctype<wchar_t>>(loc).widen(string.c_str(),
			string.c_str() + len + 1,
			ret.data()
		);

		return ret;
	}
}
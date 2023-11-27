#ifndef MUTILS_UTFCONV_H
#define MUTILS_UTFCONV_H

#include <string>
#include <codecvt>

namespace mutils
{
	inline std::u16string utf8to16(std::string in)
	{
		return std::wstring_convert<
			std::codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(in);
	}
	inline std::string utf16to8(std::u16string in)
	{
		return std::wstring_convert<
			std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(in);
	}
}

#endif // !MUTILS_UTFCONV_H

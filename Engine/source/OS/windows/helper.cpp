#include "OS/helper.h"

std::wstring Helper::stringToWString(const std::string& str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}
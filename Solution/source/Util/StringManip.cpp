/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "StringManip.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Integer/String manipulation
std::string int_to_hexstring(unsigned long i, bool zerox)
{
	std::stringstream stream;
	if (zerox)
		stream << "0x" << std::setfill('0') << std::setw(sizeof(i) * 2);
	stream << std::hex << i;
	return stream.str();
}

namespace boost
{
	// +ve numbers + ASCII (no UTF-8)
	void to_upper(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	}
	std::string to_upper_copy(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}

	void to_lower(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}
	std::string to_lower_copy(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}
}




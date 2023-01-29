/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "natives2.h"

//#include "GTAmath.h"

#include <string>

Hash GET_HASH_KEY(const char* value)
{
	size_t len = strlen(value);
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash; // joaat
}
Hash GET_HASH_KEY(const std::wstring& value)
{
	size_t len = value.length();
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
Hash GET_HASH_KEY(const std::string& value)
{
	size_t len = value.length();
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

void add_text_component_long_string(const std::string& text)
{
	const UINT8 maxStrComponentLength = 99;
	for (int i = 0; i < text.length(); i += maxStrComponentLength)
	{
		const std::string& strComp = text.substr(i, min(text.length() - i, maxStrComponentLength));
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(strComp.c_str());
	}
}
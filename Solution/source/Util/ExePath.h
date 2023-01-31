/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#pragma once

#include <string>
#include <vector>

std::string ExePathA(bool lastSlash = false);
std::wstring ExePathW(bool lastSlash = false);


#ifdef _UNICODE
#define ExePath ExePathW
#else
#define ExePath ExePathA
#endif


enum class Pathff
{
	RootDir,
	Main,
	Vehicle,
	Outfit,
	Spooner,
	Audio,
	Graphics,
	Speedo,
	WeaponsLoadout,
	Language
};

std::wstring GetPathffW(Pathff type, bool lastSlash = false);
std::string GetPathffA(Pathff type, bool lastSlash = false);
#ifdef _UNICODE
#define GetPathff GetPathffW
#else
#define GetPathff GetPathffA
#endif

bool does_file_exist(const std::string& path);

void get_all_filenames_with_extension(const std::string& directory, const std::string& extension, std::vector<std::string> &results, bool withExtension);

std::string GetClipboardTextA();


/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "ExePath.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <sys\stat.h>
#include <dirent\include\dirent.h>

/*std::string ExePathA(bool lastSlash)
{
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);

	std::string currentPath = currentDir;
	if (lastSlash) currentPath += "\\";

	return currentPath;
}
std::wstring ExePathW(bool lastSlash)
{
	wchar_t currentDir[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, currentDir);

	std::wstring currentPath = currentDir;
	if (lastSlash) currentPath += L"\\";

	return currentPath;
}*/

std::string ExePathA(bool lastSlash)
{
	static std::string ExePathA_filePathStr;
	if (ExePathA_filePathStr.empty())
	{
		char filePath[FILENAME_MAX];
		GetModuleFileNameA(nullptr, filePath, FILENAME_MAX);
		ExePathA_filePathStr = filePath;
		ExePathA_filePathStr = ExePathA_filePathStr.substr(0, ExePathA_filePathStr.rfind('\\'));
	}
	return ExePathA_filePathStr + (lastSlash ? "\\" : "");
}
std::wstring ExePathW(bool lastSlash)
{
	static std::wstring ExePathW_filePathStr;
	if (ExePathW_filePathStr.empty())
	{
		wchar_t filePath[FILENAME_MAX];
		GetModuleFileNameW(nullptr, filePath, FILENAME_MAX);
		ExePathW_filePathStr = filePath;
		ExePathW_filePathStr = ExePathW_filePathStr.substr(0, ExePathW_filePathStr.rfind('\\'));
	}
	return ExePathW_filePathStr + (lastSlash ? L"\\" : L"");
}


std::string ffPathArray[] =
{
		"",
		"\\menyooStuff",
		"\\menyooStuff\\Vehicle",
		"\\menyooStuff\\Outfit",
		"\\menyooStuff\\Spooner",
		"\\menyooStuff\\Audio",
		"\\menyooStuff\\Graphics",
		"\\menyooStuff\\Graphics\\Speedo",
		"\\menyooStuff\\WeaponsLoadout"
};

std::wstring GetPathffW(Pathff type, bool lastSlash)
{
	auto loc = static_cast<int>(type);
	std::wstring path(ffPathArray[loc].begin(), ffPathArray[loc].end());

	path = ExePathW(false) + path;
	if (lastSlash) path += L"\\";
	
	return path;
}
std::string GetPathffA(Pathff type, bool lastSlash)
{
	auto loc = static_cast<int>(type);
	std::string path = ffPathArray[loc];

	path = ExePathA(false) + path;
	if (lastSlash) path += "\\";

	return path;
}

bool does_file_exist(const std::string& path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

void get_all_filenames_with_extension(const std::string& directory, const std::string& extension, std::vector<std::string> &results, bool withExtension)
{
	struct stat stinfo;
	if (stat(directory.c_str(), &stinfo) == 0)
	{
		if (stinfo.st_mode & S_IFDIR) // is folder
		{
			DIR* dir_point = opendir(directory.c_str());
			dirent* entry = readdir(dir_point);
			while (entry)
			{
				std::string fname = entry->d_name;
				if (fname.rfind(extension, (fname.length() - extension.length())) != std::string::npos
					&& fname != "." && fname != "..")
					results.push_back(withExtension ? fname : fname.substr(0, fname.length() - extension.length()));
				entry = readdir(dir_point);
			}
			closedir(dir_point);
		}
	}
}

std::string GetClipboardTextA()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
	{
		return std::string();
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
	{
		return std::string();
	}

	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
		return false;
	}

	// Save text in a string class instance
	std::string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}
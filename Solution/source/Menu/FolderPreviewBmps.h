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

namespace DxHookIMG {
	class DxTexture;
}

namespace sub
{
	namespace FolderPreviewBmps_catind
	{
		extern bool& bFolderBmpsEnabled;
		extern std::string previewPng;
		extern std::vector<std::pair<std::string, DxHookIMG::DxTexture>> vFolderBmps;

		decltype(vFolderBmps)::iterator SearchBmps(const std::string& filePath);

		void GetThisFolderBmpPaths(const std::string& path, decltype(vFolderBmps)& newBmps);
		void PopulateFolderBmps();

		void DrawBmp(const std::string& folderPath);
	}

}



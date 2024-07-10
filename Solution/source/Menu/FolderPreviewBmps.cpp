/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FolderPreviewBmps.h"

#include "Menu.h"
#include "Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\ExePath.h"
#include "..\Scripting\DxHookIMG.h"
#include "..\Util\GTAmath.h"
#include "..\Util\FileLogger.h"
#include "..\Menu\Menu.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <string>
#include <vector>
#include <algorithm>

namespace sub
{
	namespace FolderPreviewBmps_catind
	{
		bool& bFolderBmpsEnabled = _globalSpawnVehicle_drawBmps;
		std::string previewPng = "preview.png";
		std::vector<std::pair<std::string, DxHookIMG::DxTexture>> vFolderBmps;

		decltype(vFolderBmps)::iterator SearchBmps(const std::string& filePath)
		{
			auto& map = vFolderBmps;
			auto last = map.end();
			auto it = std::lower_bound(map.begin(), last, filePath,
				[](const std::pair<std::string, DxHookIMG::DxTexture>& a, const std::string& b)
				-> bool { return a.first < b; });

			return (it != last && filePath == it->first) ? it : last;
		}

		void GetThisFolderBmpPaths(const std::string& path, decltype(vFolderBmps)& newBmps)
		{
			//addlog(ige::LogType::LOG_INFO,  "GetThisFolderBmpPaths in " + path, __FILENAME__);
			std::vector<std::string> fileNames;
			get_all_filenames_with_extension(path, std::string(), fileNames, false);

			//for(auto& s : fileNames) addlog(ige::LogType::LOG_INFO,  "In " + path + ", found " +  s, __FILENAME__);

			if (std::find(fileNames.begin(), fileNames.end(), previewPng) != fileNames.end())
			{
				std::string pathBmp = path + "\\" + previewPng;
				//addlog(ige::LogType::LOG_INFO,  "Registering " + previewPng + " in " + pathBmp, __FILENAME__);
				newBmps.push_back(std::make_pair(pathBmp, DxHookIMG::DxTexture()));
			}

			for (auto& fileName : fileNames)
			{
				std::string nextPath = path + "\\" + fileName;
				if (PathIsDirectoryA(nextPath.c_str()))
				{
					GetThisFolderBmpPaths(nextPath, newBmps);
				}
			}
		}
		void PopulateFolderBmps()
		{
			std::string path = GetPathffA(Pathff::Main, false);

			decltype(vFolderBmps) newBmps, newnewBmps;
			GetThisFolderBmpPaths(path, newBmps);

			for (auto& newBmp : newBmps)
			{
				auto it = SearchBmps(newBmp.first);
				if (it == vFolderBmps.end())
				{
					newBmp.second.Load(newBmp.first);
					if (newBmp.second.Exists())
					{
						newnewBmps.push_back(newBmp);
					}
				}
				else
				{
					if (!it->second.Exists())
					{
						it->second.Load(it->first);
					}
				}
			}

			for (auto& newnewBmp : newnewBmps)
			{
				vFolderBmps.push_back(newnewBmp);
			}

			std::sort(vFolderBmps.begin(), vFolderBmps.end(),
				[](const std::pair<std::string, DxHookIMG::DxTexture>& a, const std::pair<std::string, DxHookIMG::DxTexture>& b)
				-> bool { return a.first < b.first; });
		}

		void DrawBmp(const std::string& folderPath)
		{
			const std::string path = folderPath + "\\" + previewPng;

			auto it = SearchBmps(path);
			if (it != vFolderBmps.end())
			{
				Vector2 res = { 0.1f, 0.0889f };

				FLOAT x_coord = 0.324f + menuPos.x;
				FLOAT y_coord = OptionY + 0.044f + menuPos.y;

				if (menuPos.x > 0.45f) x_coord = menuPos.x - 0.003f;

				DRAW_RECT(x_coord, y_coord, res.x + 0.003f, res.y + 0.003f, 0, 0, 0, 212, false);

				if (it->second.Exists())
				{
					it->second.Draw(0, Vector2(x_coord, y_coord), Vector2(res.x, res.y / 2 + 0.005f), 0.0f, RGBA::AllWhite());
				}
			}
		}
	}

}



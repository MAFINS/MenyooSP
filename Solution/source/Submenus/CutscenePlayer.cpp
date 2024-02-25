/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "CutscenePlayer.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
//#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\Game.h"
#include "..\Util\ExePath.h"
#include "..\Util\FileLogger.h"

#include <Windows.h> //GetTickCount
#include <string>
#include <vector>

namespace sub
{
	namespace CutscenePlayer_catind
	{
		std::vector<std::string> vCutsceneLabels;

		void PopulateCutsceneLabels()
		{
			const std::string& filePath = GetPathffA(Pathff::Main, true) + "CutsceneLabels.txt";
			std::ifstream fin(filePath);

			if (fin.is_open())
			{
				vCutsceneLabels.clear();

				for (std::string line; std::getline(fin, line);)
				{
					if (line.length() > 2)
					{
						vCutsceneLabels.push_back(line);
					}
				}
				addlog(loglevel, ige::LogType::LOG_INFO,  "Loaded cutscene names from " + filePath);
				fin.close();
			}
		}

		void EndCutscene()
		{
			GTAplayer player = Game::Player();

			STOP_CUTSCENE_IMMEDIATELY();
			player.SetControl(true, 32);
			player.SetControl(true, 16);
			player.SetControl(true, 0);
			REMOVE_CUTSCENE();

		}
		void PlayCutscene(const std::string& label)
		{
			if (IS_CUTSCENE_PLAYING())
			{
				EndCutscene();
				WAIT(1500);
			}

			GTAplayer player = Game::Player();

			if (player.IsAlive())
			{
				player.SetControl(false, 32);
				player.SetControl(false, 16);
				player.SetControl(false, 0);
			}

			REQUEST_CUTSCENE(label.c_str(), 8);

			DWORD timeOut = GetTickCount() + 1500;
			while (GetTickCount() < timeOut)
			{
				WAIT(0);
				if (!HAS_CUTSCENE_LOADED())
					continue;
				SET_CUTSCENE_FADE_VALUES(0, 0, 1, 0);
				//SET_CUTSCENE_CAN_BE_SKIPPED(FALSE);
				START_CUTSCENE(0);
				SET_WIDESCREEN_BORDERS(0, 0);
				SET_RADIO_TO_STATION_NAME("OFF");
				break;
			}

		}


		void Sub_CutsceneList()
		{
			AddTitle("Cutscene Player");

			AddOption("STOP CUTSCENE(S)", null, EndCutscene);

			for (auto& label : vCutsceneLabels)
			{
				bool pressed = false;
				AddOption(label, pressed); if (pressed)
				{
					PlayCutscene(label);
				}

			}

		}

	}

}




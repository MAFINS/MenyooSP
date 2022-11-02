/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MainMenu.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GTAplayer.h"
//#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"

namespace sub
{
	// Are these basic (FiveM) player options allowed on 5mods?

	void PlayersSub_()
	{
		AddTitle("Players");

		for (int i = 0; i < GAME_PLAYERCOUNT; i++)
		{
			if (NETWORK_IS_PLAYER_ACTIVE(i))
			{
				bool bPlayerPressed = false;
				AddOption(GET_PLAYER_NAME(i), bPlayerPressed);

				//if (Menu::printingop == *Menu::currentopATM) Static_240 = i;

				if (bPlayerPressed)
				{
					Static_240 = i;
					Static_241 = GET_PLAYER_PED_SCRIPT_INDEX(Static_240); // Store ped
					Static_239 = GET_PLAYER_NAME(Static_240); // Store name
					Menu::SetSub_new(SUB::PLAYERSSUBAMENU); // Change submenu to 'PlayersSubAMenu_'
				}
			}
		}
	}

	void PlayersSubAMenu_()
	{
		bool bSpectateOn = false, bSpectateOff = false;
		bool bSetWp = false;

		std::string spectatePlayerStr = "CM_SPECTATE";
		if (Game::DoesGXTEntryExist(spectatePlayerStr))
		{
			spectatePlayerStr = Game::GetGXTEntry(spectatePlayerStr);
			spectatePlayerStr = spectatePlayerStr.substr(0, spectatePlayerStr.find('('));
		}
		else spectatePlayerStr = "Spectate Player";

		AddTitle(Static_239); // Title = player name
		AddOption("Set Waypoint To Player", bSetWp);
		AddLocal(spectatePlayerStr, loop_spectate_player == Static_240, bSpectateOn, bSpectateOff); // Spectate Player

		if (bSpectateOn)
		{
			Ped ped;
			loop_spectate_player = Static_240;
			for (int i = 0; i < GAME_PLAYERCOUNT; i++)
			{
				if (!NETWORK_IS_PLAYER_ACTIVE(i)) continue;
				ped = GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (!DOES_ENTITY_EXIST(ped)) continue;
				_0x419594E137637120(0, ped, 1);
				NETWORK_SET_IN_SPECTATOR_MODE(false, ped);
			}
			ped = GET_PLAYER_PED_SCRIPT_INDEX(loop_spectate_player);
			if (DOES_ENTITY_EXIST(ped))
			{
				STAT_SET_BOOL(GET_HASH_KEY("MPPLY_CAN_SPECTATE"), true, true);
				NETWORK_SET_IN_SPECTATOR_MODE(true, ped);
			}
		}
		if (bSpectateOff)
		{
			Ped ped;
			for (int i = 0; i < GAME_PLAYERCOUNT; i++)
			{
				if (!NETWORK_IS_PLAYER_ACTIVE(i)) continue;
				ped = GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (!DOES_ENTITY_EXIST(ped)) continue;
				_0x419594E137637120(0, ped, 1);
				NETWORK_SET_IN_SPECTATOR_MODE(false, ped);
			}
			NETWORK_SET_ACTIVITY_SPECTATOR(false);
			loop_spectate_player = -1;
		}

		if (bSetWp)
		{
			GTAplayer player = Static_240;
			if (player.IsActive())
			{
				GTAped& playerPed = player.GetPed();
				if (playerPed.IsAlive())
				{
					Vector3& pos = playerPed.Position_get();
					SET_NEW_WAYPOINT(pos.x, pos.y);
				}
				else
				{
					SET_WAYPOINT_OFF();
				}
			}
			else
			{
				SET_WAYPOINT_OFF();
			}
		}

	}

}





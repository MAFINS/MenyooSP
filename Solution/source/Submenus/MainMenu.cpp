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

namespace sub
{
	void MainMenu()
	{
		AddTitle("MENYOO");

		AddOption("Players", null, nullFunc, SUB::PLAYERSSUB);
		AddOption("Player Options", null, nullFunc, SUB::PLAYEROPS);
		AddOption("Vehicle Options", null, nullFunc, SUB::VEHICLEOPS);
		AddOption("Teleport Options", null, nullFunc, SUB::TELEPORTOPS);
		AddOption("Weapon Options", null, nullFunc, SUB::WEAPONOPS);
		AddOption("Weather Options", null, nullFunc, SUB::WEATHEROPS);
		AddOption("Time Options", null, nullFunc, SUB::TIMEOPS);
		AddOption("Object Spooner", null, nullFunc, SUB::SPOONER_MAIN);
		//AddOption("Lighting Options", null, nullFunc, SUB::OBJECTSPAWNER_LIGHTINGOPS);
		AddOption("Misc Options", null, nullFunc, SUB::MISCOPS);
		AddOption("Settings", null, nullFunc, SUB::SETTINGS);

		local_player_id = PLAYER_ID();
		local_ped_id = PLAYER_PED_ID();
		local_player_name = GET_PLAYER_NAME(local_player_id);
		local_player_group = GET_PLAYER_GROUP(local_player_id);

	}

}





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

#include "..\Misc\GenericLoopedMode.h"

//#include "..\Scripting\GTAped.h"
//#include "..\Scripting\GTAvehicle.h"
//#include "..\Scripting\PTFX.h"
//#include "..\Util\GTAmath.h"

#include <string>

typedef char *PCHAR;

namespace sub
{
	namespace GhostRiderMode_catind
	{
		void ToggleOnOff();
		void Tick();

		extern std::string outfitFileName;
		void ApplyGhostRiderOutfit();
		void SpawnGhostRiderRide();


		void Sub_GhostRiderMode();

	}

}





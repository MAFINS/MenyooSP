/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Databases.h"

#include "..\..\macros.h"

//#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

//#include "..\..\Natives\natives2.h"
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\GTAentity.h"

#include "SpoonerEntity.h"
#include "SpoonerMarker.h"

#include <vector>
#include <utility>
#include <string>

namespace sub::Spooner
{
	namespace Databases
	{
		std::vector<SpoonerEntity> EntityDb;
		std::vector<std::pair<GTAentity, Hash>> RelationshipDb; // Why did I make this?
		std::vector<std::pair<GTAblip, std::string>> RefBlipDb;
		std::vector<SpoonerMarker> MarkerDb;
	}

}




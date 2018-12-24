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

#include <vector>
#include <utility>
#include <string>

typedef unsigned long DWORD, Hash;
class GTAentity;
class GTAblip;

namespace sub::Spooner
{
	class SpoonerEntity;
	class SpoonerMarker;

	namespace Databases
	{
		extern std::vector<SpoonerEntity> EntityDb;
		extern std::vector<std::pair<GTAentity, Hash>> RelationshipDb; // Why did I make this?
		extern std::vector<std::pair<GTAblip, std::string>> RefBlipDb;
		extern std::vector<SpoonerMarker> MarkerDb;
	}

}




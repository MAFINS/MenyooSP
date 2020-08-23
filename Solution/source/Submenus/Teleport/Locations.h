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

//typedef char *PCHAR;

namespace sub::TeleportLocations_catind
{
	class TeleLocation;
	class NamedTeleLocationList;

	namespace IplNames
	{
		extern const std::vector<PCHAR> vYacht_Smboat1;
		extern const std::vector<PCHAR> vYacht_Heist1;
		extern const std::vector<PCHAR> vYacht_Heist2;
		extern const std::vector<PCHAR> vAircraftCarrier1;
		extern const std::vector<PCHAR> vNorthYankton;
		extern const std::vector<PCHAR> vAllCustomisableApartments1;
		extern const std::vector<PCHAR> vAllOffices1;
		extern const std::vector<PCHAR> vAllOfficeGarages1;

	}

	namespace Locations
	{
		extern const std::vector<TeleLocation> vApartmentInteriors;

		extern const std::vector<NamedTeleLocationList> vAllCategories;
	}

}




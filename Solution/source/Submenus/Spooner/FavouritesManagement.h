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

typedef unsigned long DWORD, Hash;
namespace GTAmodel {
	class Model;
}

namespace sub::Spooner
{
	namespace FavouritesManagement
	{
		extern std::string xmlFavouriteProps;
		bool IsPropAFavourite(const std::string& modelName, Hash modelHash);
		bool AddPropToFavourites(const std::string& modelName, Hash modelHash);
		bool RemovePropFromFavourites(const std::string& modelName, Hash modelHash);

		extern bool(*IsVehicleAFavourite)(GTAmodel::Model vehModel);
		extern bool(*AddVehicleToFavourites)(GTAmodel::Model vehModel, const std::string& customName);
		extern bool(*RemoveVehicleFromFavourites)(GTAmodel::Model vehModel);
	}

}




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

typedef int INT;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef unsigned long DWORD, Hash;

namespace GTAmodel {
	class Model;
}

namespace sub::Spooner
{
	namespace MenuOptions
	{
		void AddOption_AddProp(const std::string& text, const GTAmodel::Model& model);
		void AddOption_AddPed(const std::string& text, const GTAmodel::Model& model);
		void AddOption_AddVehicle(const std::string& text, const GTAmodel::Model& model);

		void AddOption_RelationshipTextScroller();

	}

}




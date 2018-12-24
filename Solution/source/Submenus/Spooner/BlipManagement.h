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

#include <utility>
#include <string>

class GTAblip;
class Vector3;

namespace sub::Spooner
{
	namespace BlipManagement
	{
		void ClearDb();
		void ClearAllRefCoordBlips();

		void AddBlipToRefCoordDb(const std::pair<GTAblip, std::string>& pB);
		std::pair<GTAblip, std::string> CreateRefCoordBlip(const Vector3& position, const std::string& name, bool addToDb);
	}

}




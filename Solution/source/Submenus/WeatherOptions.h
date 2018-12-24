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
#include <array>

namespace sub
{
	void WeatherOps_();

	namespace WeatherClouds_catind
	{
		extern const std::array<std::string, 20> vCloudNames;

		void sub_CloudOps();

	}

}




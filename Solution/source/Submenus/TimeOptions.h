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

#include "..\Scripting\DxHookIMG.h"

#include <string>
#include <vector>

typedef unsigned __int8 UINT8;

class Vector2;

namespace sub
{
	void TimeOps_();

	namespace Clock_catind
	{
		extern UINT8 loop_clock;
		extern UINT8 _analogueClockIndex;
		extern Vector2 _analogueClockPos;

		inline void DisplayClockDigital();

		struct sClockImage { std::string name; DxHookIMG::DxTexture faceId, hourId, minuteId; };
		extern std::vector<sClockImage> vClockImages;

		void LoadClockImages();
		inline void DisplayClockAnalogue();

		void DisplayClock();

		void Sub_Clock();
	}

}





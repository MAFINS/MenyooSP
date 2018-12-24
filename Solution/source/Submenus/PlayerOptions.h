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

typedef unsigned short UINT16;

namespace sub
{
	void PlayerOps_();
	
	namespace PedConfigFlagManager_catind
	{
		struct NamedPedFlagS { UINT16 id; std::string title; };
		extern std::vector<NamedPedFlagS> vPedFlags;

		void Sub_FlagList();

		extern int flagID;
		void Sub_CustomFlagSetter();
	}

	void CloneCompanionSub();

}





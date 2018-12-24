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

//#include "GenericLoopedMode.h"

#include <vector>

typedef unsigned long DWORD, Hash;
typedef char *PCHAR;

class GTAplayer;

namespace _FlameThrower_
{
	extern Hash _whash;

	//void TurnOn();

	bool IsPlayerAdded(GTAplayer player);
	void RemovePlayer(GTAplayer player);
	void AddPlayer(GTAplayer player);

	void RemoveSelf();
	void AddSelf();

	void Tick();

}







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

#include "GenericLoopedMode.h"

typedef unsigned long Hash;

namespace _MagnetGun_
{
	class MagnetGun final : public GenericLoopedMode
	{
	private:
		bool bGunActive;
		Hash _whash;
		float distanceFromCam;
	public:
		MagnetGun();

		void TurnOn() override;

		void Tick() override;
		inline void DoMagnetGunTick();

		void DisplayMagnetGunHelp();

	};


	extern MagnetGun g_magnetGun;

	void ToggleOnOff();
}





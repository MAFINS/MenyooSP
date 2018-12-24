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

class GTAvehicle;

namespace _VehicleTow_
{
	class VehicleTow final : public GenericLoopedMode
	{
	private:
		//std::vector<EntitiesAndRope> ropeArr;
		//EntitiesAndRope currentPair;
	public:
		void TurnOn() override;
		void TurnOff() override;

		// run on tick
		void Tick() override;
		inline void Tick2();
		inline void DoTowTick();
		inline void DoTowMaintainTick();

		// get vehicle behind first
		GTAvehicle GetVehicleBehindFirst();

		void ExtendTow(GTAvehicle& newVeh);
		void ShortenTow();
		void EndTows();

		// controls
		bool ExtendPressed();
		bool ShortenPressed();

		// help text
		void DisplayHelpText_Extend(GTAvehicle& vehBehind);

	};


	extern VehicleTow g_vehicleTow;

	void ToggleOnOff();
}



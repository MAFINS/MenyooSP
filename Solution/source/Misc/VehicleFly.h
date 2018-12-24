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

//#include "..\Scripting\GTAvehicle.h"
//#include "..\Scripting\Model.h"

namespace _VehicleFly_
{
	class VehicleFly final : public GenericLoopedMode
	{
	private:
		//GTAvehicle vehicle;
		//ModelDimensions vehicle_md;
		////DWORD hovertimer;
	public:
		void TurnOn() override;

		//void GoStationary();
		void GoUp(float const& control);
		void GoDown(float const& control);
		void GoForward(float const& control);
		void GoBackward(float const& control);
		void GoRight(float const& control);
		void GoLeft(float const& control);

		float Pressed_GoUp();
		float Pressed_GoDown();
		float Pressed_GoForward();
		float Pressed_GoBackward();
		float Pressed_GoRight();
		float Pressed_GoLeft();

		void DisableDrivingControls();

		void Tick() override;
		inline void DoVehicleFlyTick();
		//void HoverTick()

		void PrintFlyInstructions();
	};


	extern VehicleFly g_vehicleFly;

	void ToggleOnOff();
}



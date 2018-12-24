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

namespace _VehicleCruise_
{
	class VehicleCruise final : public GenericLoopedMode
	{
	private:
		float cruiseSpeed;
	public:
		VehicleCruise();

		void TurnOn() override;
		void TurnOff() override;

		void BeginCruise();
		void EndCruise();

		void Tick() override;
		void DoCruiseTick();

		void PrintCruiseText(bool working);

	};


	extern VehicleCruise g_vehicleCruise;

	void ToggleOnOff();
}




/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleCruise.h"

#include "..\macros.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\Game.h"

namespace _VehicleCruise_
{
	VehicleCruise::VehicleCruise()
		: cruiseSpeed(0.0f)
	{
	}

	void VehicleCruise::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		BeginCruise();
	}
	void VehicleCruise::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		EndCruise();
	}

	void VehicleCruise::BeginCruise()
	{
		cruiseSpeed = GTAped(PLAYER_PED_ID()).CurrentVehicle().SpeedVector_get(true).y;
	}
	void VehicleCruise::EndCruise()
	{
		bEnabled = false;
		cruiseSpeed = 0.0f;
	}

	void VehicleCruise::Tick()
	{
		if (bEnabled)
		{
			if (cruiseSpeed == 0.0f) BeginCruise();

			DoCruiseTick();
		}
	}
	void VehicleCruise::DoCruiseTick()
	{
		GTAplayer player = PLAYER_ID();
		GTAped ped = PLAYER_PED_ID();

		if (!ped.IsInVehicle())
		{
			EndCruise();
			return;
		}

		GTAvehicle vehicle = ped.CurrentVehicle();
		Model& vehicleModel = vehicle.Model();

		if (vehicleModel.IsHeli())
		{
			EndCruise();
			return;
		}

		bool isPlane = vehicleModel.IsPlane();

		float speed = vehicle.SpeedVector_get(true).y;

		if (cruiseSpeed < 0.01f)
		{
			EndCruise();
			return;
		}

		//auto cartime = GET_TIME_SINCE_PLAYER_HIT_VEHICLE(player.Handle());
		//auto pedtime = GET_TIME_SINCE_PLAYER_HIT_PED(player.Handle());
		//auto rpm = vehicle.CurrentRPM_get();

		bool inSeat = isPlane ? true : vehicle.GetPedOnSeat(VehicleSeat::SEAT_DRIVER) == ped.Handle();
		bool isInAirOrUpsideDownIfCar = isPlane ? false : (!vehicle.IsOnAllWheels() || vehicle.IsInWater());

		if (!inSeat || isInAirOrUpsideDownIfCar)
		{
			PrintCruiseText(false);
			return;
		}

		if (vehicle.Exists())
		{
			vehicle.SetForwardSpeed(cruiseSpeed);

			if (IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_BRAKE))
			{
				//cruiseSpeed = speed;
				cruiseSpeed -= 2.0f / 3.6f;
			}

			if (IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_ACCELERATE))
			{
				//cruiseSpeed = speed;
				cruiseSpeed += 2.0f / 3.6f;
			}
		}

		PrintCruiseText(true);

	}

	void VehicleCruise::PrintCruiseText(bool working)
	{
		Game::Print::setupdraw(GTAfont::Impact, Vector2(0.30f, 0.30f), false, true, true);
		if (working)
			Game::Print::drawstring(oss_ << "Cruise Speed: ~b~" << int(cruiseSpeed * 3.6f) << " KM/H", 0.95f, 0.24f);
		else
			Game::Print::drawstring("Cruise Status: ~r~Inactive.", 0.95f, 0.24f);
	}


	VehicleCruise g_vehicleCruise;

	void ToggleOnOff()
	{
		g_vehicleCruise.Toggle();
	}

}





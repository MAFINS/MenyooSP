/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GenericLoopedMode.h"

// Not used - put .Tick() calls directly where needed (in Menu\Routine.cpp)
void GenericLoopedMode::TickAll()
{
	/*static std::vector<GenericLoopedMode*> vGLMs
	{
		//_FlameThrower_:://not GenericLoopedMode
		//_JumpAroundMode_:://not GenericLoopedMode
		&_MagnetGun_::g_magnetGun,
		&_RopeGun_::g_ropeGun,
		&_VehicleTow_::g_vehicleTow,
		&_VehicleCruise_::g_vehicleCruise,
		&_VehicleFly_::g_vehicleFly,
		&_ManualRespawn_::g_manualRespawn,
		&_MeteorShower_::g_meteorShower,
		&_SmashAbility_::g_smashAbility,
		&_Gta2Cam_::g_gta2Cam,
		//_FpsCounter_:://not GenericLoopedMode
	};
	
	for (auto& g : vGLMs)
	{
		g->Tick();
	}*/
}


GenericLoopedMode::GenericLoopedMode()
	: bEnabled(false)
{
}

bool& GenericLoopedMode::Enabled()
{
	return bEnabled;
}

void GenericLoopedMode::Toggle()
{
	if (bEnabled)
	{
		TurnOff();
	}
	else
	{
		TurnOn();
	}
}
void GenericLoopedMode::TurnOn()
{
	bEnabled = true;
}
void GenericLoopedMode::TurnOff()
{
	bEnabled = false;
}





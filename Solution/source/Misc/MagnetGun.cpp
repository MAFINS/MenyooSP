/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MagnetGun.h"

#include "..\macros.h"

#include "..\Scripting\enums.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\World.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\WeaponIndivs.h"
#include "..\Menu\Menu.h"

#include "..\Menu\Routine.h"

namespace _MagnetGun_
{
	MagnetGun::MagnetGun()
		: bGunActive(false),
		_whash(WEAPON_ASSAULTRIFLE),
		distanceFromCam(21.0f)
	{
	}

	void MagnetGun::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		DisplayMagnetGunHelp();
	}

	void MagnetGun::Tick()
	{
		if (bEnabled)
		{
			DoMagnetGunTick();
		}
	}
	inline void MagnetGun::DoMagnetGunTick()
	{
		GTAplayer player = PLAYER_ID();
		GTAped ped = PLAYER_PED_ID();

		if (g_myWeap == _whash && (player.IsFreeAiming() || player.IsTargetingAnything()))
		{
			if (bGunActive)
			{
				//Vector3& pedPos = ped.Position_get();

				set_forge_gun_dist(distanceFromCam); // Use buttons to change the hold distance value

				Vector3& targetPos = GameplayCamera::Position_get() + (GameplayCamera::Direction_get() * distanceFromCam);

				World::DrawMarker(MarkerType::DebugSphere, targetPos, Vector3(), Vector3(), Vector3(0.5f, 0.5f, 0.5f), g_fadedRGB.ToRGBA(150));

				std::vector<Entity> magEntities;
				GTAmemory::GetEntityHandles(magEntities, targetPos, 18.7f);

				for (GTAentity entity : magEntities)
				{
					if (entity.Handle() == g_myVeh || entity.Handle() == ped.Handle())
						continue;
					entity.RequestControlOnce();
					entity.FreezePosition(false);
					entity.Oscillate(targetPos, 0.5f, 0.3f);
				}

				if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK))
				{
					for (GTAentity entity : magEntities)
					{
						if (entity.Handle() == g_myVeh || entity.Handle() == ped.Handle())
							continue;
						//entity.ApplyForce(Vector3::Normalize(targetPos - entity.Position_get()) * -135.0f);
						entity.ApplyForce(GameplayCamera::Direction_get() * 200.0f);
					}
					bGunActive = false;
				}
			}
		}
		else
		{
			bGunActive = true;
		}

	}

	void MagnetGun::DisplayMagnetGunHelp()
	{
		Game::Print::PrintBottomLeft(oss_ << "Use the ~b~" << get_weapon_label(_whash, true), "~s~ to use the magnet ability.");
		Game::Print::PrintBottomLeft(oss_ << "Use the ~b~ " << (Menu::bit_controller ? "L and R Sticks" : "Mouse Scroll") << "~s~ to alter the magnet gun distance.");
	}


	MagnetGun g_magnetGun;

	void ToggleOnOff()
	{
		g_magnetGun.Toggle();
	}

}




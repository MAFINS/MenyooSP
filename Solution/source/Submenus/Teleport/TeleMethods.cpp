/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "TeleMethods.h"

#include "..\..\macros.h"

//#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Scripting\PTFX.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Scripting\Camera.h"
#include "..\..\Memory\GTAmemory.h"
#include "..\..\Scripting\GTAblip.h"

#include "..\Spooner\SpoonerMode.h"
#include "TeleLocation.h"

#include <Windows.h> //GetTickCount
#include <string>


void teleport_net_ped(GTAentity ped, float X, float Y, float Z, bool bWait, bool bPtfx)
{
	GTAped myPed = Game::PlayerPed();
	GTAvehicle myVeh = myPed.CurrentVehicle();

	GTAvehicle vehicle = GTAped(ped).CurrentVehicle();

	if (!vehicle.Exists())
	{
		if (bWait)
		{
			Game::RequestControlOfId(ped.NetID());
			ped.RequestControl();
		}
		else
			ped.RequestControlOnce();
		//if (NETWORK_HAS_CONTROL_OF_ENTITY(ped))
		{
			ped.Position_set(Vector3(X, Y, Z));
			if (bPtfx && ped.IsVisible())
			{
				const PTFX::sFxData ptfx = { "scr_rcbarry2", "scr_clown_death" };
				if (!HAS_NAMED_PTFX_ASSET_LOADED(ptfx.asset.c_str()))
					REQUEST_NAMED_PTFX_ASSET(ptfx.asset.c_str());
				else
				{
					USE_PARTICLE_FX_ASSET(ptfx.asset.c_str());
					SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1));
					SET_PARTICLE_FX_NON_LOOPED_ALPHA(0.7f);
					START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(ptfx.effect.c_str(), X, Y, Z, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, false);
				}
			}
		}
	}
	else
	{
		if (bWait)
			vehicle.RequestControl(1000);
		else
			vehicle.RequestControlOnce();
		vehicle.Position_set(Vector3(X, Y, Z));
	}

	if (ped.Equals(myPed) || ped.Equals(myVeh))
	{
		if (sub::Spooner::SpoonerMode::spoonerModeCamera.Exists())
			sub::Spooner::SpoonerMode::spoonerModeCamera.Position_set(X, Y, Z + 3.0f);
	}

	//LOAD_ALL_OBJECTS_NOW();
	//LOAD_SCENE(X, Y, Z);
	//SET_STREAMING(TRUE);

}
void teleport_net_ped(GTAentity ped, const Vector3& pos, bool bWait, bool bPtfx)
{
	teleport_net_ped(ped, pos.x, pos.y, pos.z, bWait, bPtfx);
}
void teleport_to_missionBlip(GTAped ped)
{
	//GTAblip blip;

	//for (int i = 0; i <= 521; i++)
	BlipList* blipList = GTAmemory::GetBlipList();
	for (UINT16 i = 0; i <= 1000; i++)
	{
		Blipx* blip = blipList->m_Blips[i];
		if (blip)
		{
			/*blip.Handle() = GET_FIRST_BLIP_INFO_ID(i);
			if (!blip.Exists()) // Idek
			{
			blip.Handle() = GET_NEXT_BLIP_INFO_ID(i);
			if (!blip.Exists()) continue;
			}
			auto colour = blip.Colour();
			auto icon = blip.Icon();*/
			auto colour = blip->dwColor;
			auto icon = blip->iIcon;

			if ((icon == BlipIcon::CrateDrop) ||
				(colour == BlipColour::Yellow && icon == BlipIcon::Standard) ||
				(colour == BlipColour::Yellow3 && icon == BlipIcon::Standard) ||
				(colour == BlipColour::Yellow2 && icon == BlipIcon::Standard) ||
				(colour == BlipColour::White && icon == BlipIcon::RaceFinish) ||
				(colour == BlipColour::Green && icon == BlipIcon::Standard) ||
				(colour == BlipColour::Blue && icon == BlipIcon::Standard))

			{
				//Vector3 coord = blip.Position_get();
				Vector3 coord = Vector3(blip->x, blip->y, blip->z);

				if (ped.IsInVehicle())
				{
					auto vehicle = ped.CurrentVehicle();
					if (vehicle.RequestControl(1000))
						vehicle.Position_set(coord);
				}
				else
				{
					if (ped.RequestControl(1000))
						ped.Position_set(coord);
				}
				break;
			}
		}
	}
}

namespace sub::TeleportLocations_catind
{
	namespace TeleMethods
	{
		float ____gtaGroundCheckHeight[] = {
			100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
			450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0
		};

		void ToWaypoint(GTAped ped)
		{
			if (IS_WAYPOINT_ACTIVE())
			{
				Vector3 blipCoords = GTAblip(GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint)).Position_get();

				GTAentity e = ped;
				if (ped.IsInVehicle())
					e = ped.CurrentVehicle();

				GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, 810.0, &blipCoords.z, 0, 0);

				Game::RequestControlOfId(e.NetID());
				e.RequestControl(1000);

				for (int height : ____gtaGroundCheckHeight)
				{
					SET_ENTITY_COORDS(e.Handle(), blipCoords.x, blipCoords.y, height, 0, 0, 0, 1);
					WAIT(100);
					if (GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, height, &blipCoords.z, 0, 0))
						break;
				}
				SET_ENTITY_COORDS(e.Handle(), blipCoords.x, blipCoords.y, blipCoords.z, 0, 0, 0, 1);
			}
			else {
				Game::Print::PrintBottomCentre("~r~Error:~s~ No Waypoint set.");
			}
		}
		void ToWaypoint241()
		{
			TeleMethods::ToWaypoint(Static_241);
		}
		void ToMissionBlip241()
		{
			teleport_to_missionBlip(Static_241);
		}
		void ToForward241()
		{
			auto& entityToTeleport = Static_241;
			Vector3 yoffsetforward = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entityToTeleport, 0.0f, 3.5f, 0.0f);
			teleport_net_ped(entityToTeleport, yoffsetforward.x, yoffsetforward.y, yoffsetforward.z, true, false);
		}
		void ToCoordinates241(const Vector3& coord)
		{
			teleport_net_ped(Static_241, coord.x, coord.y, coord.z);
		}
		void ToTeleLocation241(const TeleLocation& loc)
		{
			auto& entityToTeleport = Static_241;

			bool isOnline = NETWORK_IS_IN_SESSION() != 0;
			if (loc.bOnTheLine && loc.bOffTheLine)
			{
				if (isOnline)
				{
					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_SP();
					ON_ENTER_MP();
				}
				else
				{
					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
					ON_ENTER_SP();
				}
			}
			else
			{
				if (loc.bOnTheLine)
				{
					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
				}
				else if (loc.bOffTheLine)
				{
					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_SP();
				}
			}

			for (auto& ipl : loc.iplsToRemove)
			{
				if (IS_IPL_ACTIVE((char*)ipl.data())) REMOVE_IPL((char*)ipl.data());
			}
			for (auto& ipl : loc.iplsToLoad)
			{
				if (!IS_IPL_ACTIVE((char*)ipl.data())) REQUEST_IPL((char*)ipl.data());
			}

			if (loc.bInterior)
			{
				int interior = GET_INTERIOR_AT_COORDS(loc.x, loc.y, loc.z);
				if (IS_VALID_INTERIOR(interior))
				{
					if (IS_INTERIOR_DISABLED(interior))
					{
						PIN_INTERIOR_IN_MEMORY(interior);
						SET_INTERIOR_ACTIVE(interior, true);
						DISABLE_INTERIOR(interior, false);
					}
					for (auto& propName : loc.interiorProps)
					{
						ACTIVATE_INTERIOR_ENTITY_SET(interior, (char*)propName.data());

						for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
						{
							if (IS_INTERIOR_ENTITY_SET_ACTIVE(interior, (char*)propName.data()))
									break;
							WAIT(0);
						}
						SET_INTERIOR_ENTITY_SET_TINT_INDEX(interior, (char*)propName.data(), 1);
					}
					REFRESH_INTERIOR(interior);
				}
			}

			teleport_net_ped(entityToTeleport, loc.x, loc.y, loc.z);

			if (loc.bOnTheLine || loc.bOffTheLine)
			{
				SET_INSTANCE_PRIORITY_MODE(false);
			}

			static bool _bNorthYanktonMiniMapEnabled = false;
			if (loc.name.find("Yankton") != std::string::npos)
			{
				_bNorthYanktonMiniMapEnabled = true;
				SET_MINIMAP_IN_PROLOGUE(true);
			}
			else if (_bNorthYanktonMiniMapEnabled)
			{
				_bNorthYanktonMiniMapEnabled = false;
				SET_MINIMAP_IN_PROLOGUE(false);
			}
		}
	}

}

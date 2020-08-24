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


void teleport_net_ped(GTAentity pedd, float X, float Y, float Z, bool bWait)
{
	GTAped& myPed = Game::PlayerPed();
	GTAvehicle& myVeh = myPed.CurrentVehicle();

	GTAped ped = pedd;
	GTAvehicle& vehicle = ped.CurrentVehicle();

	PTFX::sFxData ptfx = { "scr_rcbarry2", "scr_clown_death" };
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
			if (ped.IsVisible())
			{
				if (!HAS_NAMED_PTFX_ASSET_LOADED(const_cast<PCHAR>(ptfx.asset.c_str())))
					REQUEST_NAMED_PTFX_ASSET(const_cast<PCHAR>(ptfx.asset.c_str()));
				else
				{
					_SET_PTFX_ASSET_NEXT_CALL(const_cast<PCHAR>(ptfx.asset.c_str()));
					SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1));
					SET_PARTICLE_FX_NON_LOOPED_ALPHA(0.7f);
					_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(const_cast<PCHAR>(ptfx.effect.c_str()), X, Y, Z, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0);
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
void teleport_net_ped(GTAentity ped, const Vector3& pos, bool bWait)
{
	teleport_net_ped(ped.Handle(), pos.x, pos.y, pos.z, bWait);
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
				//Vector3& coord = blip.Position_get();
				Vector3& coord = Vector3(blip->x, blip->y, blip->z);

				if (ped.IsInVehicle())
				{
					auto& vehicle = ped.CurrentVehicle();
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
		void ToWaypoint(GTAped ped)
		{
			if (IS_WAYPOINT_ACTIVE())
			{
				Vector3& blipCoords = GTAblip(GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint)).Position_get();

				GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, 800.0f, &blipCoords.z);
				blipCoords.z += 20.0f;
				if (!ped.IsInVehicle())
				{
					Game::RequestControlOfId(ped.NetID());
					ped.RequestControl(1000);
					static float ____gtaGroundCheckHeight[] = {
						100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
						450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
					};
					for (int i = 0; i < sizeof(____gtaGroundCheckHeight) / sizeof(float); i++)
					{
						SET_ENTITY_COORDS(ped.Handle(), blipCoords.x, blipCoords.y, blipCoords.z, 0, 0, 0, 1);
						WAIT(100);
						if (GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, ____gtaGroundCheckHeight[i], &blipCoords.z))
							break;
					}
					SET_ENTITY_COORDS(ped.Handle(), blipCoords.x, blipCoords.y, blipCoords.z, 0, 0, 0, 1);
				}
				else
				{
					GTAvehicle vehicle = ped.CurrentVehicle();
					Game::RequestControlOfId(vehicle.NetID());
					vehicle.RequestControl(1000);
					static float ____gtaGroundCheckHeight[] = {
						100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
						450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
					};
					for (int i = 0; i < sizeof(____gtaGroundCheckHeight) / sizeof(float); i++)
					{
						SET_ENTITY_COORDS(vehicle.Handle(), blipCoords.x, blipCoords.y, blipCoords.z, 0, 0, 0, 1);
						WAIT(100);
						if (GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, ____gtaGroundCheckHeight[i], &blipCoords.z))
							break;
					}
					SET_ENTITY_COORDS(vehicle.Handle(), blipCoords.x, blipCoords.y, blipCoords.z, 0, 0, 0, 1);
				}
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
			Vector3& yoffsetforward = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entityToTeleport, 0.0f, 3.5f, 0.0f);
			teleport_net_ped(entityToTeleport, yoffsetforward.x, yoffsetforward.y, yoffsetforward.z);
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
					_ENABLE_MP_DLC_MAPS(true);
					_LOAD_SP_DLC_MAPS();
					_LOAD_MP_DLC_MAPS();
				}
				else
				{
					_ENABLE_MP_DLC_MAPS(true);
					_LOAD_MP_DLC_MAPS();
					_LOAD_SP_DLC_MAPS();
				}
			}
			else
			{
				if (loc.bOnTheLine)
				{
					_ENABLE_MP_DLC_MAPS(true);
					_LOAD_MP_DLC_MAPS();
				}
				else if (loc.bOffTheLine)
				{
					_ENABLE_MP_DLC_MAPS(true);
					_LOAD_SP_DLC_MAPS();
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
						_LOAD_INTERIOR(interior);
						SET_INTERIOR_ACTIVE(interior, true);
						DISABLE_INTERIOR(interior, false);
					}
					for (auto& propName : loc.interiorProps)
					{
						_ENABLE_INTERIOR_PROP(interior, (char*)propName.data());

						for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
						{
							if (_IS_INTERIOR_PROP_ENABLED(interior, (char*)propName.data()))
									break;
							WAIT(0);
						}
						_0xC1F1920BAF281317(interior, (char*)propName.data(), 1);
					}
					REFRESH_INTERIOR(interior);
				}
			}

			teleport_net_ped(entityToTeleport, loc.x, loc.y, loc.z);

			if (loc.bOnTheLine || loc.bOffTheLine)
			{
				_ENABLE_MP_DLC_MAPS(false);
			}

			static bool _bNorthYanktonMiniMapEnabled = false;
			if (loc.name.find("Yankton") != std::string::npos)
			{
				_bNorthYanktonMiniMapEnabled = true;
				_SET_NORTH_YANKTON_MAP(true);
			}
			else if (_bNorthYanktonMiniMapEnabled)
			{
				_bNorthYanktonMiniMapEnabled = false;
				_SET_NORTH_YANKTON_MAP(false);
			}
		}
	}

}

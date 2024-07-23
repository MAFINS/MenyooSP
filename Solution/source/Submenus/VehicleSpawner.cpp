/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleSpawner.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\DxHookIMG.h"
#include "..\Util\ExePath.h"
#include "..\Scripting\ModelNames.h"
#include "..\Menu\FolderPreviewBmps.h"
#include "..\Util\StringManip.h"
#include "..\Util\keyboard.h"
#include "..\Util\FileLogger.h"

#include "VehicleModShop.h"
#include "WeaponOptions.h"
#include "Spooner\MenuOptions.h"
#include "Spooner\Databases.h"
#include "Spooner\EntityManagement.h"
#include "Spooner\FileManagement.h"
#include "Spooner\SpoonerEntity.h"

#include <Shlwapi.h> //PathIsDirectory
#pragma comment(lib, "Shlwapi.lib")
#include <string>
#include <vector>
#include <pugixml\src\pugixml.hpp>
#include <dirent\include\dirent.h>

namespace sub
{
	// Vehicle - spawn function
	int FuncSpawnVehicle_(GTAmodel::Model model, GTAped ped, bool deleteOld, bool warpIntoVehicle)
	{
		Vehicle newcar = 0;

		Vector3 oldVelocity;
		Vector3 Pos1, Pos2;
		Vehicle oldcar = 0;
		bool oldcarBool = false;
		int oldRadioStation = GET_PLAYER_RADIO_STATION_INDEX();
		bool oldCarOn = true;
		if (ped.IsInVehicle())
		{
			oldcar = ped.CurrentVehicle().GetHandle();
			oldVelocity = GET_ENTITY_VELOCITY(oldcar);
			oldCarOn = GET_IS_VEHICLE_ENGINE_RUNNING(oldcar) != 0;
			oldcarBool = true;
		}

		//if (_IS_DECORATOR_OF_TYPE("MPBitset", 3))
		//{
		//	if (_DOES_DECORATOR_EXIST(PLAYER_ID(), "MPBitset"))
		//	{
		//		uVar0 = DECOR_GET_INT(PLAYER_ID(), "MPBitset");
		//	}
		//}

		if (model.Load(3000))
		{
			if (oldcarBool)
			{
				float spacing1 = Model(GET_ENTITY_MODEL(oldcar)).Dim1().y + model.Dim2().y + 1.0f;
				if(deleteOld)
					Pos1 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(oldcar, 0, 0, 0.5f);
				else
					Pos1 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(oldcar, 0, spacing1, 0.5f);
			}
			else
				Pos1 = ped.GetOffsetInWorldCoords(Vector3());

			PTFX::trigger_ptfx_1("proj_xmas_firework", "scr_firework_xmas_burst_rgw", 0, Pos1, Vector3(), 1.0f);
			//PTFX::trigger_ptfx_1("scr_fbi5a", "scr_fbi5_ped_water_splash", 0, Pos1, Vector3(), 1.5f);

			newcar = CREATE_VEHICLE(model.hash, Pos1.x, Pos1.y, Pos1.z, ped.Heading_get(), 1, 1, 0);
			//SET_VEHICLE_ENGINE_ON(newcar, oldCarOn, oldCarOn);
				
			//if (!IS_ENTITY_IN_AIR(ped) && !IS_ENTITY_IN_WATER(ped)) SET_VEHICLE_ON_GROUND_PROPERLY(newcar, 0.0f);
			

			SET_ENTITY_ALPHA(newcar, 0, false);
			SET_ENTITY_COLLISION(newcar, false, true);
			//SET_VEHICLE_HAS_STRONG_AXLES(newcar, 1);
			SET_VEHICLE_DIRT_LEVEL(newcar, 0.0f);
			//SET_VEHICLE_ENVEFF_SCALE(newcar, 0.0f);
			//SET_ENTITY_AS_MISSION_ENTITY(newcar, 0, 1); //Fixes the despawning of MP onl;y cars after a couple of secs
			//	SET_ENTITY_PROOFS(newcar, 1, 1, 1, 1, 1, 1, 1, 1);

			///int newnetid = VEH_TO_NET(newcar);
			//Game::RequestControlOfId(newnetid);
			//SET_NETWORK_ID_CAN_MIGRATE(newnetid, 1);
			//SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(newnetid, 1);

			if (oldcarBool && DOES_ENTITY_EXIST(oldcar))
			{
				GTAvehicle(newcar).RequestControl();
				SET_VEHICLE_ENGINE_ON(newcar, oldCarOn, true, 0);
				SET_ENTITY_COLLISION(newcar, true, true);
				SET_VEHICLE_FORWARD_SPEED(newcar, abs(oldVelocity.y));
				SET_ENTITY_VELOCITY(newcar, oldVelocity.x, oldVelocity.y, oldVelocity.z);
				if (deleteOld)
				{ 
					//FREEZE_ENTITY_POSITION(oldcar, true);
					SET_ENTITY_COLLISION(oldcar, false, true);
					SET_ENTITY_ALPHA(oldcar, 0, false);
				}
				RESET_ENTITY_ALPHA(newcar);
				if (warpIntoVehicle)
				{
					//if (Model(GET_ENTITY_MODEL(oldcar)).IsPlane()) CLEAR_PED_TASKS_IMMEDIATELY(ped); // mainPed
					int maxi = GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(newcar);// - 2;
					for (INT i = -1; i <= maxi; i++)
					{
						Ped tempPed = GET_PED_IN_VEHICLE_SEAT(oldcar, i, 0);
						if (DOES_ENTITY_EXIST(tempPed))
						{
							if (GTAentity(tempPed).RequestControl())
							{
								//CLEAR_PED_TASKS_IMMEDIATELY(tempPed);
								SET_PED_INTO_VEHICLE(tempPed, newcar, i);
							}
						}
					}
				}

				if (deleteOld)
				{
					WAIT(0);
					int maxi = GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(oldcar);// - 2;
					for (INT i = -1; i <= maxi; i++)
					{
						Ped tempPed = GET_PED_IN_VEHICLE_SEAT(oldcar, i, 0);
						if (DOES_ENTITY_EXIST(tempPed))
						{
							if (GTAentity(tempPed).RequestControl())
							{
								TASK_LEAVE_ANY_VEHICLE(tempPed, 0, 0);
								CLEAR_PED_TASKS_IMMEDIATELY(tempPed);
							}
						}
					}
					WAIT(0);
					GTAvehicle(oldcar).RequestControl();
					//SET_ENTITY_AS_MISSION_ENTITY(oldcar, 0, 1);
					SET_ENTITY_COORDS(oldcar, 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0, 1);
					DELETE_VEHICLE(&oldcar);
				}
			}
			else
			{
				if (warpIntoVehicle)
					SET_PED_INTO_VEHICLE(ped.Handle(), newcar, (int)GTAvehicle(newcar).FirstFreeSeat(SEAT_DRIVER));
					SET_ENTITY_COLLISION(newcar, true, true);
					RESET_ENTITY_ALPHA(newcar);
			}
			//SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(newcar, 5);
			//SET_VEHICLE_NUMBER_PLATE_TEXT(newcar, "MENYOO");

			GTAvehicle(newcar).RadioStation_set(oldRadioStation);
			GTAvehicle(newcar).CloseAllDoors(true);
			//if (IS_VEHICLE_A_CONVERTIBLE(newcar, 0)) LOWER_CONVERTIBLE_ROOF(newcar, 1);

			model.Unload();

			//// Online lock fix
			//if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("Player_Vehicle", 3))
			//	DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
			//if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("Veh_Modded_By_Player", 3))
			//	DECORATOR::DECOR_REGISTER("Veh_Modded_By_Player", 3);
			//if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("Not_Allow_As_Saved_Veh", 3))
			//	DECORATOR::DECOR_REGISTER("Not_Allow_As_Saved_Veh", 3);
			//DECORATOR::DECOR_SET_INT(newcar, "Player_Vehicle", NETWORK::_0xBC1D768F2F5D6C05(PLAYER_ID()));
			//DECORATOR::DECOR_SET_INT(newcar, "Veh_Modded_By_Player", GET_HASH_KEY(GET_PLAYER_NAME(PLAYER_ID())));
			//DECORATOR::DECOR_SET_INT(newcar, "Not_Allow_As_Saved_Veh", 0);
			//if (NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(newnetid))
			//{
			//	ENTITY::_0x3910051CCECDB00C(newcar, true);
			//	if (NETWORK::_0xC7827959479DCC78(newcar))
			//	{
			//		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(newnetid, true);
			//	}
			//}
			SET_VEHICLE_IS_STOLEN(newcar, false);
		}
		
		return newcar;
	}

	// Vehicle spawner

	namespace SpawnVehicle_catind
	{
		UINT8 SpawnVehicle_index;
		//std::string type_name;
		//enum Indices

#pragma region vehicle bmps
		struct VehBmpSprite
		{
			Hash modelHash;
			DxHookIMG::DxTexture tid;
			std::string dict, imgName;

			friend bool operator == (const VehBmpSprite& left, const Hash right)
			{
				return left.modelHash == right;
			}

			VehBmpSprite()
				: modelHash(0)
			{
			}
			VehBmpSprite(Hash modelHashP)
				: modelHash(modelHashP)
			{
			}
			VehBmpSprite(Hash modelHashP, std::string dictP, std::string imgNameP)
				: modelHash(modelHashP), dict(dictP), imgName(imgNameP)
			{
			}

			bool LoadFile(const std::string& path)
			{
				tid.Load(path);
				return tid.ID() != 0;
			}
		};
		std::vector<VehBmpSprite> vVehicleBmps{
			{ VEHICLE_AIRBUS, "candc_default", "airbus" },
			{ VEHICLE_BARRACKS, "candc_default", "barracks" },
			{ VEHICLE_BOXVILLE4, "candc_default", "boxville4" },
			{ VEHICLE_BUS, "candc_default", "bus" },
			{ VEHICLE_BUZZARD, "candc_default", "buzzard" },
			{ VEHICLE_CARGOBOB, "candc_default", "cargobob" },
			{ VEHICLE_COACH, "candc_default", "coach" },
			{ VEHICLE_CRUSADER, "candc_default", "crusader" },
			{ VEHICLE_DUBSTA3, "candc_default", "dubsta3" },
			{ VEHICLE_DUKES2, "candc_default", "dukes" },
			{ VEHICLE_DUMP, "candc_default", "dump" },
			{ VEHICLE_HYDRA, "candc_default", "hydra" },
			{ VEHICLE_INSURGENT, "candc_default", "insurgent" },
			{ VEHICLE_INSURGENT2, "candc_default", "insurgent2" },
			{ VEHICLE_JOURNEY, "candc_default", "journey" },
			{ VEHICLE_MARSHALL, "candc_default", "marshall" },
			{ VEHICLE_MESA, "candc_default", "mesa" },
			{ VEHICLE_MESA3, "candc_default", "mesa3" },
			{ VEHICLE_MONSTER, "candc_default", "monster" },
			{ VEHICLE_MULE, "candc_default", "mule" },
			{ VEHICLE_MULE3, "candc_default", "mule3" },
			{ VEHICLE_PBUS, "candc_default", "pbus" },
			{ VEHICLE_RENTALBUS, "candc_default", "rentbus" },
			{ VEHICLE_RHINO, "candc_default", "rhino" },
			{ VEHICLE_SAVAGE, "candc_default", "savage" },
			{ VEHICLE_TECHNICAL, "candc_default", "technical" },
			{ VEHICLE_VALKYRIE, "candc_default", "valkyrie" },

			{ VEHICLE_DINGHY3, "dock_default", "dinghy3" },
			{ VEHICLE_JETMAX, "dock_default", "jetmax" },
			{ VEHICLE_MARQUIS, "dock_default", "marquis" },
			{ VEHICLE_SEASHARK, "dock_default", "seashark" },
			{ VEHICLE_SPEEDER, "dock_default", "speeder" },
			{ VEHICLE_SQUALO, "dock_default", "squalo" },
			{ VEHICLE_SUBMERSIBLE2, "dock_default", "sub2" },
			{ VEHICLE_SUNTRAP, "dock_default", "suntrap" },
			{ VEHICLE_TROPIC, "dock_default", "tropic" },

			{ VEHICLE_ANNIHILATOR, "elt_default", "annihl" },
			{ VEHICLE_CUBAN800, "elt_default", "cuban800" },
			{ VEHICLE_DODO, "elt_default", "dodo" },
			{ VEHICLE_DUSTER, "elt_default", "duster" },
			{ VEHICLE_FROGGER, "elt_default", "frogger" },
			{ VEHICLE_LUXOR, "elt_default", "luxor" },
			{ VEHICLE_MAMMATUS, "elt_default", "mammatus" },
			{ VEHICLE_MAVERICK, "elt_default", "maverick" },
			{ VEHICLE_SHAMAL, "elt_default", "shamal" },
			{ VEHICLE_STUNT, "elt_default", "stunt" },
			{ VEHICLE_TITAN, "elt_default", "titan" },
			{ VEHICLE_VELUM, "elt_default", "velum" },
			{ VEHICLE_VELUM2, "elt_default", "velum2" },

			{ VEHICLE_VESTRA, "elt_dlc_business", "vestra" },

			{ VEHICLE_LUXOR2, "elt_dlc_luxe", "luxor2" },
			{ VEHICLE_SWIFT2, "elt_dlc_luxe", "swift2" },

			{ VEHICLE_BESRA, "elt_dlc_pilot", "besra" },
			{ VEHICLE_MILJET, "elt_dlc_pilot", "miljet" },
			{ VEHICLE_SWIFT, "elt_dlc_pilot", "swift" },

			{ VEHICLE_ADDER, "lgm_default", "adder" },
			{ VEHICLE_BANSHEE, "lgm_default", "banshee" },
			{ VEHICLE_BULLET, "lgm_default", "bullet" },
			{ VEHICLE_CARBONIZZARE, "lgm_default", "carboniz" },
			{ VEHICLE_CARBONRS, "lgm_default", "carbon" },
			{ VEHICLE_CHEETAH, "lgm_default", "cheetah" },
			{ VEHICLE_COGCABRIO, "lgm_default", "cogcabri" },
			{ VEHICLE_COMET2, "lgm_default", "comet2" },
			{ VEHICLE_COQUETTE, "lgm_default", "coquette" },
			{ VEHICLE_ELEGY2, "lgm_default", "elegy2" },
			{ VEHICLE_ENTITYXF, "lgm_default", "entityxf" },
			{ VEHICLE_EXEMPLAR, "lgm_default", "exemplar" },
			{ VEHICLE_FELTZER2, "lgm_default", "feltzer" },
			{ VEHICLE_HOTKNIFE, "lgm_default", "hotknife" },
			{ VEHICLE_JB700, "lgm_default", "jb700" },
			{ VEHICLE_KHAMELION, "lgm_default", "khamel" },
			{ VEHICLE_MONROE, "lgm_default", "monroe" },
			{ VEHICLE_NEMESIS, "sssa_dlc_heist", "nemesis" },
			{ VEHICLE_NINEF, "lgm_default", "ninef" },
			{ VEHICLE_NINEF2, "lgm_default", "ninef2" },
			{ VEHICLE_RAPIDGT, "lgm_default", "rapidgt" },
			{ VEHICLE_RAPIDGT2, "lgm_default", "rapidgt2" },
			{ VEHICLE_STINGER, "lgm_default", "stinger" },
			{ VEHICLE_STINGERGT, "lgm_default", "stingerg" },
			{ VEHICLE_VOLTIC, "lgm_default", "voltic_tless" },
			{ VEHICLE_ZTYPE, "lgm_default", "ztype" },

			{ VEHICLE_ALPHA, "lgm_dlc_business", "alpha" },
			{ VEHICLE_JESTER, "lgm_dlc_business", "jester" },
			{ VEHICLE_TURISMOR, "lgm_dlc_business", "turismor" },

			{ VEHICLE_COQUETTE2, "lgm_dlc_pilot", "coquette2" },

			{ VEHICLE_HUNTLEY, "lgm_dlc_business2", "huntley" },
			{ VEHICLE_MASSACRO, "lgm_dlc_business2", "massacro" },
			{ VEHICLE_THRUST, "lgm_dlc_business2", "thrust" },
			{ VEHICLE_ZENTORNO, "lgm_dlc_business2", "zentorno" },

			{ VEHICLE_FUROREGT, "lgm_dlc_lts_creator", "furore" },

			{ VEHICLE_FELTZER3, "lgm_dlc_luxe", "feltzer3" },
			{ VEHICLE_OSIRIS, "lgm_dlc_luxe", "osiris" },
			{ VEHICLE_VIRGO, "lgm_dlc_luxe", "virgo" },
			{ VEHICLE_WINDSOR, "lgm_dlc_luxe", "windsor" },
			{ VEHICLE_BRAWLER, "lgm_dlc_luxe", "brawler" },
			{ VEHICLE_VINDICATOR, "lgm_dlc_luxe", "vindicator" },
			{ VEHICLE_CHINO, "lgm_dlc_luxe", "chino" },
			{ VEHICLE_COQUETTE3, "lgm_dlc_luxe", "coquette3" },
			{ VEHICLE_T20, "lgm_dlc_luxe", "t20" },

			{ VEHICLE_TORO, "dock_default", "toro" },

			{ VEHICLE_BMX, "pandm_default", "bmx" },
			{ VEHICLE_CRUISER, "pandm_default", "cruiser" },
			{ VEHICLE_SCORCHER, "pandm_default", "scorcher" },
			{ VEHICLE_TRIBIKE, "pandm_default", "tribike" },
			{ VEHICLE_TRIBIKE2, "pandm_default", "tribike2" },
			{ VEHICLE_TRIBIKE3, "pandm_default", "tribike3" },

			{ VEHICLE_AKUMA, "sssa_default", "akuma" },
			{ VEHICLE_BALLER, "sssa_default", "baller2" },
			{ VEHICLE_BATI, "sssa_default", "bati" },
			{ VEHICLE_BATI2, "sssa_default", "bati2" },
			{ VEHICLE_BFINJECTION, "sssa_default", "bfinject" },
			{ VEHICLE_BIFTA, "sssa_default", "bifta" },
			{ VEHICLE_BISON, "sssa_default", "bison" },
			{ VEHICLE_BLAZER, "sssa_default", "blazer" },
			{ VEHICLE_BODHI2, "sssa_default", "bodhi2" },
			{ VEHICLE_CAVALCADE, "sssa_default", "cavcade" },
			{ VEHICLE_DILETTANTE, "sssa_default", "dilettan" },
			{ VEHICLE_DOUBLE, "sssa_default", "double" },
			{ VEHICLE_DUNE, "sssa_default", "dune" },
			{ VEHICLE_FAGGIO2, "sssa_default", "faggio" },
			{ VEHICLE_FELON, "sssa_default", "felon" },
			{ VEHICLE_FELON2, "sssa_default", "felon2" },
			{ VEHICLE_FUGITIVE, "sssa_default", "fugitive" },
			{ VEHICLE_GAUNTLET, "sssa_default", "gauntlet" },
			{ VEHICLE_HEXER, "sssa_default", "hexer" },
			{ VEHICLE_INFERNUS, "sssa_default", "infernus" },
			{ VEHICLE_ISSI2, "sssa_default", "issi2" },
			{ VEHICLE_KALAHARI, "sssa_default", "kalahari" },
			{ VEHICLE_ORACLE, "sssa_default", "oracle" },
			{ VEHICLE_PARADISE, "sssa_default", "paradise" },
			{ VEHICLE_PCJ, "sssa_default", "pcj" },
			{ VEHICLE_REBEL, "sssa_default", "rebel" },
			{ VEHICLE_ROCOTO, "sssa_default", "rocoto" },
			{ VEHICLE_RUFFIAN, "sssa_default", "ruffian" },
			{ VEHICLE_SADLER, "sssa_default", "sadler" },
			{ VEHICLE_SANCHEZ, "sssa_default", "sanchez" },
			{ VEHICLE_SANCHEZ2, "sssa_default", "sanchez2" },
			{ VEHICLE_SANDKING, "sssa_default", "sandking" },
			{ VEHICLE_SANDKING2, "sssa_default", "sandkin2" },
			{ VEHICLE_SCHWARZER, "sssa_default", "schwarze" },
			{ VEHICLE_STRETCH, "sssa_default", "stretch" },
			{ VEHICLE_SUPERD, "lgm_default", "superd" },
			{ VEHICLE_SURANO, "lgm_default", "surano_convertable" },
			{ VEHICLE_VACCA, "lgm_default", "vacca" },
			{ VEHICLE_VADER, "sssa_default", "vader" },
			{ VEHICLE_VIGERO, "sssa_default", "vigero" },
			{ VEHICLE_ZION, "sssa_default", "zion" },
			{ VEHICLE_ZION2, "sssa_default", "zion2" },

			{ VEHICLE_ASEA, "sssa_dlc_business", "asea" },
			{ VEHICLE_ASTEROPE, "sssa_dlc_business", "astrope" },
			{ VEHICLE_BOBCATXL, "sssa_dlc_business", "bobcatxl" },
			{ VEHICLE_CAVALCADE2, "sssa_dlc_business", "cavcade2" },
			{ VEHICLE_INGOT, "sssa_dlc_business", "ingot" },
			{ VEHICLE_INTRUDER, "sssa_dlc_business", "intruder" },
			{ VEHICLE_MINIVAN, "sssa_dlc_business", "minivan" },
			{ VEHICLE_PREMIER, "sssa_dlc_business", "premier" },
			{ VEHICLE_RADI, "sssa_dlc_business", "radi" },
			{ VEHICLE_RANCHERXL, "sssa_dlc_business", "rancherx" },
			{ VEHICLE_STANIER, "sssa_dlc_business", "stanier" },
			{ VEHICLE_STRATUM, "sssa_dlc_business", "stratum" },
			{ VEHICLE_WASHINGTON, "sssa_dlc_business", "washingt" },
			{ VEHICLE_DOMINATOR, "sssa_dlc_business2", "dominato" },
			{ VEHICLE_F620, "sssa_dlc_business2", "f620" },
			{ VEHICLE_FUSILADE, "sssa_dlc_business2", "fusilade" },
			{ VEHICLE_PENUMBRA, "sssa_dlc_business2", "penumbra" },
			{ VEHICLE_SENTINEL, "sssa_dlc_business2", "sentinel" },

			{ VEHICLE_JESTER2, "sssa_dlc_christmas_2", "jester2" },
			{ VEHICLE_MASSACRO2, "sssa_dlc_christmas_2", "massacro2" },
			{ VEHICLE_RATLOADER2, "sssa_dlc_christmas_2", "rloader2" },
			{ VEHICLE_SLAMVAN, "sssa_dlc_christmas_2", "slamvan" },

			{ VEHICLE_ENDURO, "sssa_dlc_heist", "enduro" },
			{ VEHICLE_GBURRITO2, "sssa_dlc_heist", "gburrito2" },
			{ VEHICLE_GRESLEY, "sssa_dlc_heist", "gresley" },
			{ VEHICLE_JACKAL, "sssa_dlc_heist", "jackal" },
			{ VEHICLE_KURUMA, "sssa_dlc_heist", "kuruma" },
			{ VEHICLE_KURUMA2, "sssa_dlc_heist", "kuruma2" },
			{ VEHICLE_LANDSTALKER, "sssa_dlc_heist", "landstalker" },
			{ VEHICLE_RUMPO, "sssa_dlc_heist", "rumpo" },
			{ VEHICLE_SCHAFTER2, "sssa_dlc_heist", "schafter2" },
			{ VEHICLE_SEMINOLE, "sssa_dlc_heist", "seminole" },
			{ VEHICLE_SURGE, "sssa_dlc_heist", "surge" },

			{ VEHICLE_BLADE, "sssa_dlc_hipster", "blade" },
			{ VEHICLE_BLAZER3, "sssa_dlc_hipster", "blazer3" },
			{ VEHICLE_BUFFALO, "sssa_dlc_hipster", "buffalo" },
			{ VEHICLE_BUFFALO2, "sssa_dlc_hipster", "buffalo2" },
			{ VEHICLE_GLENDALE, "sssa_dlc_hipster", "glendale" },
			{ VEHICLE_PANTO, "sssa_dlc_hipster", "panto" },
			{ VEHICLE_PICADOR, "sssa_dlc_hipster", "picador" },
			{ VEHICLE_PIGALLE, "sssa_dlc_hipster", "pigalle" },
			{ VEHICLE_PRIMO, "sssa_dlc_hipster", "primo" },
			{ VEHICLE_REBEL2, "sssa_dlc_hipster", "rebel2" },
			{ VEHICLE_REGINA, "sssa_dlc_hipster", "regina" },
			{ VEHICLE_RHAPSODY, "sssa_dlc_hipster", "rhapsody" },
			{ VEHICLE_SURFER, "sssa_dlc_hipster", "surfer" },
			{ VEHICLE_TAILGATER, "sssa_dlc_hipster", "tailgater" },
			{ VEHICLE_WARRENER, "sssa_dlc_hipster", "warrener" },
			{ VEHICLE_YOUGA, "sssa_dlc_hipster", "youga" },

			{ VEHICLE_SOVEREIGN, "sssa_dlc_independence", "sovereign" },

			{ VEHICLE_HAKUCHOU, "sssa_dlc_lts_creator", "hakuchou" },
			{ VEHICLE_INNOVATION, "sssa_dlc_lts_creator", "innovation" },

			{ VEHICLE_BLISTA2, "sssa_dlc_mp_to_sp", "blista2" },
			{ VEHICLE_BUFFALO3, "sssa_dlc_mp_to_sp", "buffalo3" },
			{ VEHICLE_DOMINATOR2, "sssa_dlc_mp_to_sp", "dominator2" },
			{ VEHICLE_GAUNTLET2, "sssa_dlc_mp_to_sp", "gauntlet2" },
			{ VEHICLE_STALION, "sssa_dlc_mp_to_sp", "stallion" },
			{ VEHICLE_STALION2, "sssa_dlc_mp_to_sp", "stalion2" },

			{ VEHICLE_RATLOADER, "sssa_dlc_valentines", "rloader" },
			{ VEHICLE_BTYPE, "lgm_dlc_valentines", "roosevelt" },

			{ VEHICLE_CASCO, "lgm_dlc_heist", "casco" },
			{ VEHICLE_LECTRO, "lgm_dlc_heist", "lectro" },

			{ VEHICLE_BUCCANEER2, "lsc_default", "buccaneer2_b" },
			{ VEHICLE_BUCCANEER, "lsc_default", "buccaneer2" },
			{ VEHICLE_CHINO2, "lsc_default", "chino2_b" },
			{ VEHICLE_CHINO, "lsc_default", "chino2" },
			{ VEHICLE_FACTION, "lsc_default", "faction2_a" },
			{ VEHICLE_FACTION2, "lsc_default", "faction2_b" },
			{ VEHICLE_MOONBEAM, "lsc_default", "moonbeam2_a" },
			{ VEHICLE_MOONBEAM2, "lsc_default", "moonbeam2_b" },
			{ VEHICLE_PRIMO, "lsc_default", "primo2_a" },
			{ VEHICLE_PRIMO2, "lsc_default", "primo2_b" },
			{ VEHICLE_VOODOO2, "lsc_default", "voodoo_a" },
			{ VEHICLE_VOODOO, "lsc_default", "voodoo_b" },

			{ VEHICLE_BTYPE2, "sssa_dlc_halloween", "btype2" },
			{ VEHICLE_LURCHER, "sssa_dlc_halloween", "lurcher" },

			{ VEHICLE_SUPERVOLITO, "elt_dlc_apartments", "svolito" },
			{ VEHICLE_SUPERVOLITO2, "elt_dlc_apartments", "svolito2" },
			{ VEHICLE_LIMO2, "candc_apartments", "limo2" },
			{ VEHICLE_BALLER3, "lgm_dlc_apartments", "baller3" },
			{ VEHICLE_BALLER4, "lgm_dlc_apartments", "baller4" },
			{ VEHICLE_COG55, "lgm_dlc_apartments", "cog55" },
			{ VEHICLE_COGNOSCENTI, "lgm_dlc_apartments", "cognosc" },
			{ VEHICLE_COGNOSCENTI2, "lgm_dlc_apartments", "cognosc" },
			{ VEHICLE_MAMBA, "lgm_dlc_apartments", "mamba" },
			{ VEHICLE_NIGHTSHADE, "lgm_dlc_apartments", "niteshad" },
			{ VEHICLE_SCHAFTER3, "lgm_dlc_apartments", "schafter3" },
			{ VEHICLE_SCHAFTER4, "lgm_dlc_apartments", "schafter4" },
			{ VEHICLE_VERLIERER2, "lgm_dlc_apartments", "verlier" },
			{ VEHICLE_TAMPA, "sssa_dlc_christmas_3", "tampa" },

			{ VEHICLE_BANSHEE2, "lsc_jan2016", "banshee2" },
			{ VEHICLE_SULTANRS, "lsc_jan2016", "sultan2" },
			{ VEHICLE_BTYPE3, "lgm_dlc_valentines2", "roosevelt2" },

			//{ VEHICLE_FACTION, "lsc_lowrider2", "faction3_a" },
			{ VEHICLE_FACTION3, "lsc_lowrider2", "faction3_b" },
			//{ VEHICLE_MINIVAN, "lsc_lowrider2", "minivan2_a" },
			{ VEHICLE_MINIVAN2, "lsc_lowrider2", "minivan2_b" },
			{ VEHICLE_SABREGT, "lsc_lowrider2", "sabregt2_a" },
			{ VEHICLE_SABREGT2, "lsc_lowrider2", "sabregt2_b" },
			//{ VEHICLE_SLAMVAN, "lsc_lowrider2", "slamvan3_a" },
			{ VEHICLE_SLAMVAN3, "lsc_lowrider2", "slamvan3_b" },
			{ VEHICLE_TORNADO, "lsc_lowrider2", "tornado5_a" },
			{ VEHICLE_TORNADO5, "lsc_lowrider2", "tornado5_b" },
			//{ VEHICLE_VIRGO, "lsc_lowrider2", "virgo2_a" },
			{ VEHICLE_VIRGO2, "lsc_lowrider2", "virgo2_b" },

			{ VEHICLE_BESTIAGTS, "lgm_dlc_executive1", "bestiagts" },
			{ VEHICLE_FMJ, "lgm_dlc_executive1", "fmj" },
			{ VEHICLE_PFISTER811, "lgm_dlc_executive1", "pfister811" },
			{ VEHICLE_PROTOTIPO, "lgm_dlc_executive1", "prototipo" },
			{ VEHICLE_REAPER, "lgm_dlc_executive1", "reaper" },
			{ VEHICLE_SEVEN70, "lgm_dlc_executive1", "seven70" },
			{ VEHICLE_WINDSOR2, "lgm_dlc_executive1", "windsor2" },
			{ VEHICLE_XLS, "lgm_dlc_executive1", "xls" },
			{ VEHICLE_XLS2, "lgm_dlc_executive1", "xls" },
			{ VEHICLE_RUMPO3, "sssa_dlc_executive_1", "rumpo3" },
			{ VEHICLE_BRICKADE, "candc_executive1", "brickade" },
			{ VEHICLE_CARGOBOB2, "candc_executive1", "cargobob2" },
			{ VEHICLE_NIMBUS, "elt_dlc_executive1", "nimbus" },
			{ VEHICLE_VOLATUS, "elt_dlc_executive1", "volatus" },
			{ VEHICLE_TUG, "dock_dlc_executive1", "tug" },

			{ VEHICLE_LE7B, "lgm_dlc_stunt", "le7b" },
			{ VEHICLE_LYNX, "lgm_dlc_stunt", "lynx" },
			{ VEHICLE_SHEAVA, "lgm_dlc_stunt", "sheava" },
			{ VEHICLE_TYRUS, "lgm_dlc_stunt", "tyrus" },
			{ VEHICLE_BF400, "sssa_dlc_stunt", "bf400" },
			{ VEHICLE_BRIOSO, "sssa_dlc_stunt", "brioso" },
			{ VEHICLE_CLIFFHANGER, "sssa_dlc_stunt", "cliffhanger" },
			{ VEHICLE_CONTENDER, "sssa_dlc_stunt", "contender" },
			{ VEHICLE_GARGOYLE, "sssa_dlc_stunt", "gargoyle" },
			{ VEHICLE_OMNIS, "sssa_dlc_stunt", "omnis" },
			{ VEHICLE_RALLYTRUCK, "sssa_dlc_stunt", "rallytruck" },
			{ VEHICLE_TAMPA2, "sssa_dlc_stunt", "tampa2" },
			{ VEHICLE_TROHPYTRUCK, "sssa_dlc_stunt", "trophy" },
			{ VEHICLE_TROHPYTRUCK2, "sssa_dlc_stunt", "trophy2" },
			{ VEHICLE_TROPOS, "sssa_dlc_stunt", "tropos" },

			{ VEHICLE_HAKUCHOU2, "lgm_dlc_biker", "hakuchou2" },
			{ VEHICLE_RAPTOR, "lgm_dlc_biker", "raptor" },
			{ VEHICLE_SHOTARO, "lgm_dlc_biker", "shotaro" },
			{ VEHICLE_AVARUS, "sssa_dlc_biker", "avarus" },
			{ VEHICLE_BAGGER, "sssa_dlc_biker", "bagger" },
			{ VEHICLE_BLAZER4, "sssa_dlc_biker", "blazer4" },
			{ VEHICLE_CHIMERA, "sssa_dlc_biker", "chimera" },
			{ VEHICLE_DAEMON2, "sssa_dlc_biker", "daemon2" },
			{ VEHICLE_DEFILER, "sssa_dlc_biker", "defiler" },
			{ VEHICLE_ESSKEY, "sssa_dlc_biker", "esskey" },
			{ VEHICLE_FAGGIO3, "sssa_dlc_biker", "faggio3" },
			{ VEHICLE_FAGGION, "sssa_dlc_biker", "faggion" },
			{ VEHICLE_MANCHEZ, "sssa_dlc_biker", "manchez" },
			{ VEHICLE_NIGHTBLADE, "sssa_dlc_biker", "nightblade" },
			{ VEHICLE_RATBIKE, "sssa_dlc_biker", "ratbike" },
			{ VEHICLE_SANCTUS, "sssa_dlc_biker", "sanctus" },
			{ VEHICLE_TORNADO6, "sssa_dlc_biker", "tornado6" },
			{ VEHICLE_VORTEX, "sssa_dlc_biker", "vortex" },
			{ VEHICLE_WOLFSBANE, "sssa_dlc_biker", "wolfsbane" },
			{ VEHICLE_YOUGA2, "sssa_dlc_biker", "youga2" },
			{ VEHICLE_ZOMBIEA, "sssa_dlc_biker", "zombiea" },
			{ VEHICLE_ZOMBIEB, "sssa_dlc_biker", "zombieb" },

			{ VEHICLE_BLAZER5, "candc_importexport", "blazer5" },
			{ VEHICLE_BOXVILLE5, "candc_importexport", "boxville5" },
			{ VEHICLE_DUNE5, "candc_importexport", "dune5" },
			{ VEHICLE_PHANTOM2, "candc_importexport", "phantom2" },
			{ VEHICLE_RUINER2, "candc_importexport", "ruiner2" },
			{ VEHICLE_TECHNICAL2, "candc_importexport", "technical2" },
			{ VEHICLE_VOLTIC2, "candc_importexport", "voltic2" },
			{ VEHICLE_WASTLNDR, "candc_importexport", "wastlndr" },
			{ VEHICLE_PENETRATOR, "lgm_dlc_importexport", "penetrator" },
			{ VEHICLE_TEMPESTA, "lgm_dlc_importexport", "tempesta" },
			//{ VEHICLE_COMET2, "lsc_dlc_import_export", "comet3_a" },
			{ VEHICLE_COMET3, "lsc_dlc_import_export", "comet3_b" },
			{ VEHICLE_DIABLOUS, "lsc_dlc_import_export", "diablous2_a" },
			{ VEHICLE_DIABLOUS2, "lsc_dlc_import_export", "diablous2_b" },
			//{ VEHICLE_ELEGY2, "lsc_dlc_import_export", "elegy_a" },
			{ VEHICLE_ELEGY, "lsc_dlc_import_export", "elegy_b" },
			{ VEHICLE_FCR, "lsc_dlc_import_export", "fcr2_a" },
			{ VEHICLE_FCR2, "lsc_dlc_import_export", "fcr2_b" },
			{ VEHICLE_ITALIGTB, "lsc_dlc_import_export", "italigtb2_a" },
			{ VEHICLE_ITALIGTB2, "lsc_dlc_import_export", "italigtb2_b" },
			{ VEHICLE_NERO, "lsc_dlc_import_export", "nero2_a" },
			{ VEHICLE_NERO2, "lsc_dlc_import_export", "nero2_b" },
			{ VEHICLE_SPECTER, "lsc_dlc_import_export", "specter2_a" },
			{ VEHICLE_SPECTER2, "lsc_dlc_import_export", "specter2_b" },

			{ VEHICLE_GP1, "lgm_dlc_specialraces", "gp1" },
			{ VEHICLE_INFERNUS2, "lgm_dlc_specialraces", "infernus2" },
			{ VEHICLE_RUSTON, "lgm_dlc_specialraces", "ruston" },
			{ VEHICLE_TURISMO2, "lgm_dlc_specialraces", "turismo2" },

			{ VEHICLE_APC, "candc_gunrunning", "apc" },
			{ VEHICLE_ARDENT, "candc_gunrunning", "ardent" },
			{ VEHICLE_CADDY3, "foreclosures_bunker", "transportation_1" },
			{ VEHICLE_CHEETAH2, "lgm_dlc_gunrunning", "cheetah2" },
			{ VEHICLE_DUNE3, "candc_gunrunning", "dune3" },
			{ VEHICLE_HALFTRACK, "candc_gunrunning", "halftrack" },
			{ VEHICLE_HAULER2 , "candc_truck", "cab_1" },
			//{ VEHICLE_INSURGENT3, "", "insurgent3" },
			{ VEHICLE_NIGHTSHARK, "candc_gunrunning", "nightshark" },
			{ VEHICLE_OPPRESSOR, "candc_gunrunning", "oppressor" },
			//{ VEHICLE_PHANTOM3, "", "phantom3" },
			{ VEHICLE_TAMPA3, "candc_gunrunning", "tampa3" },
			//{ VEHICLE_TECHNICAL3, "", "technical3" },
			{ VEHICLE_TORERO, "lgm_dlc_gunrunning", "torero" },
			//{ VEHICLE_TRAILERS4, "", "" },
			//{ VEHICLE_TRAILERLARGE, "", "" },
			{ VEHICLE_TRAILERSMALL2, "candc_gunrunning", "trsmall2" },
			{ VEHICLE_VAGNER, "lgm_dlc_gunrunning", "vagner" },
			{ VEHICLE_XA21, "lgm_dlc_gunrunning", "xa21" },

			{ VEHICLE_HAULER2, "candc_truck", "cab_0" },
			{ VEHICLE_LAZER, "candc_smuggler", "lazer" },
			{ VEHICLE_BOMBUSHKA, "candc_smuggler","bombushka" },
			{ VEHICLE_HUNTER, "candc_smuggler","hunter" },
			{ VEHICLE_LAZER , "candc_smuggler","lazer" },
			{ VEHICLE_MOGUL , "candc_smuggler","mogul" },
			{ VEHICLE_MOLOTOK  , "candc_smuggler","molotok" },
			{ VEHICLE_NOKOTA, "candc_smuggler","nokota" },
			{ VEHICLE_PYRO  , "candc_smuggler","pyro" },
			{ VEHICLE_ROGUE , "candc_smuggler","rogue" },
			{ VEHICLE_STARLING , "candc_smuggler","starling" },
			{ VEHICLE_TULA  , "candc_smuggler","tula" },
			{ VEHICLE_VIGILANTE, "candc_smuggler","vigilante" },
			{ VEHICLE_CYCLONE  , "lgm_dlc_smuggler" , "cyclone" },
			{ VEHICLE_RAPIDGT3 , "lgm_dlc_smuggler" , "rapidgt3" },
			{ VEHICLE_VISIONE  , "lgm_dlc_smuggler" , "visione" },
			{ VEHICLE_RETINUE , "sssa_dlc_smuggler", "retinue" },
			{ VEHICLE_ALPHAZ1  , "elt_dlc_smuggler" , "alphaz1" },
			{ VEHICLE_HAVOK , "elt_dlc_smuggler" , "havok" },
			{ VEHICLE_HOWARD, "elt_dlc_smuggler" , "howard" },
			{ VEHICLE_MICROLIGHT   , "elt_dlc_smuggler" , "microlight" },
			{ VEHICLE_SEABREEZE, "elt_dlc_smuggler" , "seabreeze" },

			// b1290
			{ VEHICLE_AKULA, "candc_xmas2017", "akula" },
			{ VEHICLE_BARRAGE, "candc_xmas2017", "barrage" },
			{ VEHICLE_CHERNOBOG, "candc_xmas2017", "chernobog" },
			{ VEHICLE_DELUXO, "candc_xmas2017", "deluxo" },
			{ VEHICLE_KHANJALI, "candc_xmas2017", "khanjali" },
			{ VEHICLE_RIOT2, "candc_xmas2017", "riot2" },
			{ VEHICLE_STROMBERG, "candc_xmas2017", "stromberg" },
			{ VEHICLE_THRUSTER, "candc_xmas2017", "thruster" },
			{ VEHICLE_VOLATOL, "candc_xmas2017", "volatol" },
			{ VEHICLE_HERMES, "sssa_dlc_xmas2017", "hermes" },
			{ VEHICLE_KAMACHO, "sssa_dlc_xmas2017", "kamacho" },
			{ VEHICLE_RIATA, "sssa_dlc_xmas2017", "riata" },
			{ VEHICLE_SENTINEL3, "sssa_dlc_xmas2017", "sentinel3" },
			{ VEHICLE_STREITER, "sssa_dlc_xmas2017", "streiter" },
			{ VEHICLE_YOSEMITE, "sssa_dlc_xmas2017", "yosemite" },
			{ VEHICLE_AUTARCH, "sssa_dlc_xmas2017", "autarch" },
			{ VEHICLE_COMET4, "lgm_dlc_xmas2017", "comet4" },
			{ VEHICLE_COMET5, "lgm_dlc_xmas2017", "comet5" },
			{ VEHICLE_GT500, "lgm_dlc_xmas2017", "gt500" },
			{ VEHICLE_HUSTLER, "lgm_dlc_xmas2017", "hustler" },
			{ VEHICLE_NEON, "lgm_dlc_xmas2017", "neon" },
			{ VEHICLE_PARIAH, "lgm_dlc_xmas2017", "pariah" },
			{ VEHICLE_RAIDEN, "lgm_dlc_xmas2017", "raiden" },
			{ VEHICLE_REVOLTER, "lgm_dlc_xmas2017", "revolter" },
			{ VEHICLE_SAVESTRA, "lgm_dlc_xmas2017", "savestra" },
			{ VEHICLE_SC1, "lgm_dlc_xmas2017", "sc1" },
			{ VEHICLE_VISERIS, "lgm_dlc_xmas2017", "viseris" },
			{ VEHICLE_Z190, "lgm_dlc_xmas2017", "z190" },

			// b1365 Southern san andreas autos series
			{ VEHICLE_CARACARA, "candc_assault", "caracara" },
			{ VEHICLE_ENTITY2, "lgm_dlc_assault", "entity2" },
			{ VEHICLE_FLASHGT, "lgm_dlc_assault", "flashgt" },
			{ VEHICLE_GB200, "lgm_dlc_assault", "gb200" },
			{ VEHICLE_JESTER3, "lgm_dlc_assault", "jester3" },
			{ VEHICLE_TAIPAN, "lgm_dlc_assault", "taipan" },
			{ VEHICLE_TEZERACT, "lgm_dlc_assault", "tezeract" },
			{ VEHICLE_TYRANT, "lgm_dlc_assault", "tyrant" },
			{ VEHICLE_SEASPARROW, "elt_dlc_assault", "sparrow" },
			{ VEHICLE_CHEBUREK, "sssa_dlc_assault", "cheburek" },
			{ VEHICLE_DOMINATOR3, "sssa_dlc_assault", "dominator3" },
			{ VEHICLE_ELLIE, "sssa_dlc_assault", "ellie" },
			{ VEHICLE_FAGALOA, "sssa_dlc_assault", "fagaloa" },
			{ VEHICLE_HOTRING, "sssa_dlc_assault", "hotring" },
			{ VEHICLE_ISSI3, "sssa_dlc_assault", "issi3" },
			//{ VEHICLE_ISSI3, "mba_vehicles", "issi3" },
			{ VEHICLE_MICHELLI, "sssa_dlc_assault", "michelli" },

			// b1493 After hours
			{ VEHICLE_PBUS2, "sssa_dlc_battle", "pbus2" },
			{ VEHICLE_PATRIOT, "sssa_dlc_battle", "patriot" },
			{ VEHICLE_PATRIOT2, "sssa_dlc_battle", "patriot2" },
			{ VEHICLE_TERBYTE, "candc_hacker", "banner0" },
			{ VEHICLE_POUNDER2, "candc_battle", "pounder2" },
			{ VEHICLE_MULE4, "candc_battle", "mule4" },
			{ VEHICLE_MENACER, "candc_battle", "menacer" },
			{ VEHICLE_OPPRESSOR2, "candc_battle", "oppressor2" },
			{ VEHICLE_SCRAMJET, "candc_battle", "scramjet" },
			{ VEHICLE_STRIKEFORCE, "candc_battle", "strikeforce" },
			{ VEHICLE_SWINGER, "lgm_dlc_battle", "swinger" },
			{ VEHICLE_STAFFORD, "lgm_dlc_battle", "stafford" },
			{ VEHICLE_FREECRAWLER, "lgm_dlc_battle", "freecrawler" },
			{ VEHICLE_BLIMP3, "elt_dlc_battle", "blimp3" },
			//{ VEHICLE_SPEEDO4, "", "" },

			// b1604 Arena battle
			{ VEHICLE_BLISTA3, "sssa_dlc_arena", "blista3" },
			{ VEHICLE_BRUISER, "mba_vehicles", "bruiser_c_1" },
			{ VEHICLE_BRUISER2, "mba_vehicles", "bruiser_c_2" },
			{ VEHICLE_BRUISER3, "mba_vehicles", "bruiser_c_3" },
			{ VEHICLE_BRUTUS, "mba_vehicles", "brutus1" },
			{ VEHICLE_BRUTUS2, "mba_vehicles", "brutus2" },
			{ VEHICLE_BRUTUS3, "mba_vehicles", "brutus3" },
			{ VEHICLE_CERBERUS, "mba_vehicles", "cerberus1" },
			{ VEHICLE_CERBERUS2, "mba_vehicles", "cerberus2" },
			{ VEHICLE_CERBERUS3, "mba_vehicles", "cerberus3" },
			{ VEHICLE_CLIQUE, "lgm_dlc_arena", "clique" },
			{ VEHICLE_DEATHBIKE, "mba_vehicles", "deathbike_c_1" },
			{ VEHICLE_DEATHBIKE2, "mba_vehicles", "deathbike_c_2" },
			{ VEHICLE_DEATHBIKE3, "mba_vehicles", "deathbike_c_3" },
			{ VEHICLE_DEVESTE, "lgm_dlc_arena", "deveste" },
			{ VEHICLE_DEVIANT, "lgm_dlc_arena", "deviant" },
			{ VEHICLE_DOMINATOR4, "mba_vehicles", "dominato_c_1" },
			{ VEHICLE_DOMINATOR5, "mba_vehicles", "dominato_c_2" },
			{ VEHICLE_DOMINATOR6, "mba_vehicles", "dominato_c_3" },
			{ VEHICLE_IMPALER, "mba_vehicles", "impaler" },
			{ VEHICLE_IMPALER2, "mba_vehicles", "impaler_c_1" },
			{ VEHICLE_IMPALER3, "mba_vehicles", "impaler_c_2" },
			{ VEHICLE_IMPALER4, "mba_vehicles", "impaler_c_3" },
			{ VEHICLE_IMPERATOR, "mba_vehicles", "imperator1" },
			{ VEHICLE_IMPERATOR2, "mba_vehicles", "imperator2" },
			{ VEHICLE_IMPERATOR3, "mba_vehicles", "imperator3" },
			//{ VEHICLE_ISSI3, "mba_vehicles", "issi3" },
			{ VEHICLE_ISSI4, "mba_vehicles", "issi3_c_1" },
			{ VEHICLE_ISSI5, "mba_vehicles", "issi3_c_2" },
			{ VEHICLE_ISSI6, "mba_vehicles", "issi3_c_3" },
			{ VEHICLE_ITALIGTO, "lgm_dlc_arena", "italigto" },
			{ VEHICLE_MONSTER3, "mba_vehicles", "monster_c_1" },
			{ VEHICLE_MONSTER4, "mba_vehicles", "monster_c_2" },
			{ VEHICLE_MONSTER5, "mba_vehicles", "monster_c_3" },
			{ VEHICLE_RCBANDITO, "sssa_dlc_arena", "rcbandito" },
			{ VEHICLE_SCARAB, "mba_vehicles", "scarab1" },
			{ VEHICLE_SCARAB2, "mba_vehicles", "scarab2" },
			{ VEHICLE_SCARAB3, "mba_vehicles", "scarab3" },
			{ VEHICLE_SCHLAGEN, "lgm_dlc_arena", "schlagen" },
			{ VEHICLE_SLAMVAN4, "mba_vehicles", "slamvan_c_1" },
			{ VEHICLE_SLAMVAN5, "mba_vehicles", "slamvan_c_2" },
			{ VEHICLE_SLAMVAN6, "mba_vehicles", "slamvan_c_3" },
			{ VEHICLE_TOROS, "lgm_dlc_arena", "toros" },
			{ VEHICLE_TULIP, "sssa_dlc_arena", "tulip" },
			{ VEHICLE_VAMOS, "sssa_dlc_arena", "vamos" },
			{ VEHICLE_ZR380, "mba_vehicles", "zr3801" },
			{ VEHICLE_ZR3802, "mba_vehicles", "zr3802" },
			{ VEHICLE_ZR3803, "mba_vehicles", "zr3803" },

		};
#pragma endregion
		void PopulateVehicleBmps()
		{
			std::vector<std::string> fileNames;
			std::string path = GetPathffA(Pathff::Graphics, true) + "Vehicle Previews\\";
			get_all_filenames_with_extension(path, ".png", fileNames, false);
			for (auto& f : fileNames)
			{
				Hash fhash = GET_HASH_KEY(f);
				auto it = std::find(vVehicleBmps.begin(), vVehicleBmps.end(), fhash);
				if (it == vVehicleBmps.end())
				{
					VehBmpSprite bmp(fhash);
					if (bmp.LoadFile(path + f + ".png"))
					{
						vVehicleBmps.push_back(bmp);
					}
				}
				else
				{
					if (!it->tid.Exists())
					{
						it->LoadFile(path + f + ".png");
					}
				}
			}
		}
		void DrawVehicleBmp(const GTAmodel::Model& vehModel)
		{
			Vector2 res = { 0.1f, 0.0889f };

			FLOAT x_coord = 0.324f + menuPos.x;
			FLOAT y_coord = OptionY + 0.044f + menuPos.y;

			if (menuPos.x > 0.45f)
				x_coord = menuPos.x - 0.003f;

			DRAW_RECT(x_coord, y_coord, res.x + 0.003f, res.y + 0.003f, 0, 0, 0, 212, false);

			auto vit = std::find(vVehicleBmps.begin(), vVehicleBmps.end(), vehModel.hash);
			if (vit != vVehicleBmps.end()) //if found
			{
				if (vit->tid.Exists())//if dxtexture png
				{
					vit->tid.Draw(0, Vector2(x_coord, y_coord), Vector2(res.x, res.y / 2 + 0.005f), 0.0f, RGBA::AllWhite());
				}
				else//if in-game sprite
				{
					if (!HAS_STREAMED_TEXTURE_DICT_LOADED(vit->dict.c_str()))
						REQUEST_STREAMED_TEXTURE_DICT(vit->dict.c_str(), false);
					DRAW_SPRITE(vit->dict.c_str(), vit->imgName.c_str(), x_coord, y_coord, res.x, res.y, 0.0f, 255, 255, 255, 255, false, 0);
				}
			}
			else
			{
				Game::Print::setupdraw(0, Vector2(0, 0.185f), true, false, false);
				Game::Print::drawstring("No preview available", x_coord, y_coord - 0.0043f);
			}
		}
		void DrawVehicleModelName(const GTAmodel::Model& vehModel)
		{
			FLOAT x_coord = menuPos.x + 0.25f;
			FLOAT y_coord = OptionY + menuPos.y;

			Game::Print::setupdraw(font_selection, Vector2(0.0f, (font_options == 0? 0.33f:0.4f)), false, true, false, selectedtext,{0, x_coord});
			Game::Print::drawstring("ModelName: " + vehModel.VehicleModelName(), 0, y_coord);
		}

		void AddvcatOption_(const std::string& text, UINT8 index, bool *extra_option_code)
		{
			std::vector<Model>* tempvecp;
			switch (index)
			{
			case OPENWHEEL:		tempvecp = &g_vehHashes_OPENWHEEL; break;
			case SUPER:			tempvecp = &g_vehHashes_SUPER; break;
			case SPORT:			tempvecp = &g_vehHashes_SPORT; break;
			case SPORTSCLASSIC: tempvecp = &g_vehHashes_SPORTSCLASSIC; break;
			case COUPE:			tempvecp = &g_vehHashes_COUPE; break;
			case MUSCLE:		tempvecp = &g_vehHashes_MUSCLE; break;
			case OFFROAD:		tempvecp = &g_vehHashes_OFFROAD; break;
			case SUV:			tempvecp = &g_vehHashes_SUV; break;
			case SEDAN:			tempvecp = &g_vehHashes_SEDAN; break;
			case COMPACT:		tempvecp = &g_vehHashes_COMPACT; break;
			case VAN:			tempvecp = &g_vehHashes_VAN; break;
			case SERVICE:		tempvecp = &g_vehHashes_SERVICE; break;
			case TRAIN:			tempvecp = &g_vehHashes_TRAIN; break;
			case EMERGENCY:		tempvecp = &g_vehHashes_EMERGENCY; break;
			case MOTORCYCLE:	tempvecp = &g_vehHashes_MOTORCYCLE; break;
			case BICYCLE:		tempvecp = &g_vehHashes_BICYCLE; break;
			case PLANE:			tempvecp = &g_vehHashes_PLANE; break;
			case HELICOPTER:	tempvecp = &g_vehHashes_HELICOPTER; break;
			case BOAT:			tempvecp = &g_vehHashes_BOAT; break;
			case INDUSTRIAL:	tempvecp = &g_vehHashes_INDUSTRIAL; break;
			case COMMERCIAL:	tempvecp = &g_vehHashes_COMMERCIAL; break;
			case UTILITY:		tempvecp = &g_vehHashes_UTILITY; break;
			case MILITARY:		tempvecp = &g_vehHashes_MILITARY; break;
			case OTHER:			tempvecp = &g_vehHashes_OTHER; break;
			case DRIFT:			tempvecp = &g_vehHashes_DRIFT; break;
			}
			if (tempvecp->empty())
				return;

			bool pressed = false;
			AddOption(text, pressed, nullFunc, -1, true); if (pressed)
			{
				SpawnVehicle_index = index;
				//type_name = std::string(text);
				dict = std::string(text);
				Menu::SetSub_delayed = SUB::SPAWNVEHICLE_ALLCATS;

				if (extra_option_code != nullptr)
					*extra_option_code = true;
			}
		}

		void AddVSpawnOption_(const std::string& text, const GTAmodel::Model& vehModel, Ped ped)
		{
			bool pressed = false;
			AddOption(text, pressed, nullFunc, -1, false, false); if (pressed)
			{
				Vehicle vehicle = FuncSpawnVehicle_(vehModel, ped, _globalSpawnVehicle_deleteOld, _globalSpawnVehicle_autoSit);

				set_vehicle_max_upgrades(vehicle, _globalSpawnVehicle_autoUpgrade, _globalSpawnVehicle_invincible,
					_globalSpawnVehicle_plateType, _globalSpawnVehicle_plateTexter_value == 0 ? _globalSpawnVehicle_plateText : "", _globalSpawnVehicle_neonToggle,
					_globalSpawnVehicle_neonCol.R, _globalSpawnVehicle_neonCol.G, _globalSpawnVehicle_neonCol.B,
					_globalSpawnVehicle_PrimCol, _globalSpawnVehicle_SecCol);

				if (!NETWORK_IS_IN_SESSION() && !_globalSpawnVehicle_persistent)
					SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
			}
		}

	}

	void SpawnVehicle_()
	{
		using namespace SpawnVehicle_catind;
		dict2.clear();
		dict3.clear();
		//type_name.clear();
		bool spnrandom = 0;
		bool spawnvehicle_input = 0;

		AddTitle("Vehicles");

		AddOption("Spawn Settings", null, nullFunc, SUB::SPAWNVEHICLE_OPTIONS);
		AddOption("Saved Vehicles", null, nullFunc, SUB::VEHICLE_SAVER);
		AddOption("Favourites", null, nullFunc, SUB::SPAWNVEHICLE_FAVOURITES);
		AddOption("Funny Vehicles (Old)", null, nullFunc, SUB::FUNNYVEHICLES);

		AddBreak("---Cars---");
		AddvcatOption_("Open Wheel", OPENWHEEL);
		AddvcatOption_("Super", SUPER);
		AddvcatOption_("Sports", SPORT);
		AddvcatOption_("Sports Classics", SPORTSCLASSIC);
		AddvcatOption_("Coupes", COUPE);
		AddvcatOption_("Muscle", MUSCLE);
		AddvcatOption_("Offroad", OFFROAD);
		AddvcatOption_("SUVs", SUV);
		AddvcatOption_("Sedans", SEDAN);
		AddvcatOption_("Compacts", COMPACT);
		AddvcatOption_("Drift", DRIFT);

		AddBreak("---Industrial---");
		AddvcatOption_("Vans", VAN);
		AddvcatOption_("Services", SERVICE);
		AddvcatOption_("Industrial", INDUSTRIAL);
		AddvcatOption_("Commercial", COMMERCIAL);
		AddvcatOption_("Utility", UTILITY);
		AddvcatOption_("Trains", TRAIN);

		AddBreak("---Others---");
		AddvcatOption_("Emergency", EMERGENCY);
		AddvcatOption_("Military", MILITARY);
		AddvcatOption_("Motorcycles", MOTORCYCLE);
		AddvcatOption_("Bicycles", BICYCLE);
		AddvcatOption_("Planes", PLANE);
		AddvcatOption_("Helicopters", HELICOPTER);
		AddvcatOption_("Boats", BOAT);
		AddvcatOption_("Others", OTHER);

		AddOption("Random Vehicle", spnrandom);
		AddOption("~b~Input~s~ Model", spawnvehicle_input);

		if (spnrandom || spawnvehicle_input)
		{
			Model model;
			Ped ped = Static_241;

			if (spnrandom)
			{
				if (g_vehHashes.empty())
					return;
				model = g_vehHashes[GET_RANDOM_INT_IN_RANGE(0, (int)g_vehHashes.size())];
				
			}
			else if (spawnvehicle_input)
			{
				std::string inputStr = Game::InputBox("", 64U, "Enter vehicle model name (e.g. adder):");
				if (inputStr.length() == 0)
					return;
				model = GET_HASH_KEY(inputStr);
			}

			if (model.IsInCdImage() && model.IsVehicle())
			{
				Vehicle spawnedVehicle = FuncSpawnVehicle_(model, ped, _globalSpawnVehicle_deleteOld, _globalSpawnVehicle_autoSit);

				set_vehicle_max_upgrades(spawnedVehicle, _globalSpawnVehicle_autoUpgrade, _globalSpawnVehicle_invincible,
					_globalSpawnVehicle_plateType, _globalSpawnVehicle_plateTexter_value == 0 ? _globalSpawnVehicle_plateText : "", _globalSpawnVehicle_neonToggle,
					_globalSpawnVehicle_neonCol.R, _globalSpawnVehicle_neonCol.G, _globalSpawnVehicle_neonCol.B,
					_globalSpawnVehicle_PrimCol, _globalSpawnVehicle_SecCol);

				if (!NETWORK_IS_IN_SESSION() && !_globalSpawnVehicle_persistent)
					SET_VEHICLE_AS_NO_LONGER_NEEDED(&spawnedVehicle);
			}
			else Game::Print::PrintError_InvalidModel();
		}
		/*if (spawnvehicle_input)
		{
		OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::VehicleSpawnerInput, std::string(), 64U, "Enter vehicle model name (e.g. adder):");
		OnscreenKeyboard::State::arg1._int = Static_241;
		}*/

		/*PCHAR chartick;
		for (const auto& vimg : vVehicleBmps)
		{
		chartick = PCHAR(vimg.dict.c_str());
		if (HAS_STREAMED_TEXTURE_DICT_LOADED(chartick))
		SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(chartick);
		}*/

	}

	void SpawnVehicle_Options()
	{
		bool veh_plate_plus = 0, veh_plate_minus = 0, veh_plate_text_set = 0, veh_plate_text_plus = 0, veh_plate_text_minus = 0,
			set_mspaint_index_10 = 0, set_mspaint_index_11 = 0, set_rgbcarcol_index_9 = 0;

		auto& plateTexter_value = _globalSpawnVehicle_plateTexter_value;
		std::vector<std::string> plateTexter{ _globalSpawnVehicle_plateText, "Random" };
		std::vector<std::string> ms_vPlateTypeNames{ "CMOD_PLA_0", "CMOD_PLA_4", "CMOD_PLA_3", "CMOD_PLA_1", "CMOD_PLA_2", "Yankton", "CMOD_PLA_6", "CMOD_PLA_7", "CMOD_PLA_8", "CMOD_PLA_9", "CMOD_PLA_10", "CMOD_PLA_11", "CMOD_PLA_12" }; // BOW1, YOBLA, YOBLU, BOW2, BOW3, YANKTON, ECOLA, LASVENTURAS, LIBERTYCITY, LSCARMEET, LSPOUNDERS, SPRUNK 

		AddTitle("Spawn Settings");
		AddToggle("Delete Old Vehicle", _globalSpawnVehicle_deleteOld);
		AddToggle("Auto-Sit In Vehicle", _globalSpawnVehicle_autoSit);
		AddToggle("Spawn Pre-Upgraded", _globalSpawnVehicle_autoUpgrade);
		AddToggle("Spawn Invincible", _globalSpawnVehicle_invincible);
		AddToggle("Spawn Persistent", _globalSpawnVehicle_persistent);
		AddOption("Primary Paint", set_mspaint_index_10, nullFunc, SUB::MSPAINTS2); // Primary Paint
		AddOption("Secondary Paint", set_mspaint_index_11, nullFunc, SUB::MSPAINTS2); // Secondary Paint
		AddBreak("---Neons---");
		AddToggle("Toggle", _globalSpawnVehicle_neonToggle);
		AddOption("RGB Colour", set_rgbcarcol_index_9, nullFunc, SUB::MSPAINTS_RGB); if (*Menu::currentopATM == Menu::printingop) Add_preset_colour_options_previews(_globalSpawnVehicle_neonCol);

		AddBreak("---Plate---");
		AddTexter("Type", _globalSpawnVehicle_plateType, ms_vPlateTypeNames, null, veh_plate_plus, veh_plate_minus);
		AddTexter("Text", plateTexter_value, plateTexter, veh_plate_text_set, veh_plate_text_plus, veh_plate_text_minus);

		AddBreak("---Previews---");
		AddToggle("Enable Previews", _globalSpawnVehicle_drawBmps);
		bool bReloadPreviewsPressed = false;
		AddOption("Reload Previews", bReloadPreviewsPressed); if (bReloadPreviewsPressed)
		{
			SpawnVehicle_catind::PopulateVehicleBmps();
			FolderPreviewBmps_catind::PopulateFolderBmps();
		}

		if (set_mspaint_index_10) ms_curr_paint_index = 10;
		if (set_mspaint_index_11) ms_curr_paint_index = 11;
		if (set_rgbcarcol_index_9) bit_MSPaints_RGB_mode = 9;

		if (veh_plate_plus) { if (_globalSpawnVehicle_plateType < (INT)(ms_vPlateTypeNames.size() - 1)) _globalSpawnVehicle_plateType++; return; }
		if (veh_plate_minus) { if (_globalSpawnVehicle_plateType > 0) _globalSpawnVehicle_plateType--; return; }

		if (veh_plate_text_plus) { if (plateTexter_value < 1) plateTexter_value++; return; }
		if (veh_plate_text_minus) { if (plateTexter_value > 0) plateTexter_value--; return; }

		if (veh_plate_text_set)
		{
			switch (plateTexter_value)
			{
			case 0:
				std::string inputStr = Game::InputBox("", 9U, "CMOD_MOD_18_D", _globalSpawnVehicle_plateText);
				if (inputStr.length() > 0 && inputStr.length() <= 8)
					_globalSpawnVehicle_plateText = inputStr;
				else
					Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::GSpawnVehiclePlateText, std::string(), 8U, "CMOD_MOD_18_D", _globalSpawnVehicle_plateText);
				break;
			}
			return;
		}

	}

	bool SpawnVehicle_IsVehicleModelAFavourite(GTAmodel::Model vehModel)
	{
		std::string xmlAddedVehicleModels = "AddedVehicleModels.xml";
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()).status != pugi::status_ok)
			return false;
		pugi::xml_node nodeRoot = doc.child("AddedVehicleModels");
		const std::string& vehModelName = vehModel.VehicleDisplayName(false);
		return nodeRoot.find_child_by_attribute("modelName", vehModelName.c_str())
			|| nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(vehModel.hash, true).c_str());
	}
	bool SpawnVehicle_AddVehicleModelToFavourites(GTAmodel::Model vehModel, const std::string& customName)
	{
		if (customName.empty())
			return false;
		std::string xmlAddedVehicleModels = "AddedVehicleModels.xml";
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()).status != pugi::status_ok)
		{
			doc.reset();
			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
			auto nodeRoot = doc.append_child("AddedVehicleModels");
			doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str());
		}
		pugi::xml_node nodeRoot = doc.child("AddedVehicleModels");

		//if (vehModel.IsInCdImage()){
		const std::string& vehModelName = vehModel.VehicleDisplayName(false);
		auto nodeOldLoc = nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(vehModel.hash, true).c_str());
		if (!nodeOldLoc) // If null
		{
			nodeOldLoc = nodeRoot.find_child_by_attribute("modelName", vehModelName.c_str());
		}
		if (nodeOldLoc) // If not null
		{
			nodeOldLoc.parent().remove_child(nodeOldLoc);
		}
		auto nodeNewLoc = nodeRoot.append_child("VehModel");
		nodeNewLoc.append_attribute("modelName") = vehModelName.c_str();
		nodeNewLoc.append_attribute("modelHash") = int_to_hexstring(vehModel.hash, true).c_str();
		nodeNewLoc.append_attribute("customName") = customName.c_str();
		return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()));
	}
	bool SpawnVehicle_RemoveVehicleModelFromFavourites(GTAmodel::Model vehModel)
	{
		std::string xmlAddedVehicleModels = "AddedVehicleModels.xml";
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()).status != pugi::status_ok)
			return false;
		pugi::xml_node nodeRoot = doc.child("AddedVehicleModels");

		const std::string& vehModelName = vehModel.VehicleDisplayName(false);
		auto nodeOldLoc = nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(vehModel.hash, true).c_str());
		if (!nodeOldLoc) // If null
		{
			nodeOldLoc = nodeRoot.find_child_by_attribute("modelName", vehModelName.c_str());
		}
		if (nodeOldLoc) // If not null
		{
			nodeOldLoc.parent().remove_child(nodeOldLoc);
		}
		return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()));
	}

	void SpawnVehicle_AllCatsSub()
	{
		using namespace SpawnVehicle_catind;
		const std::vector<Model> *tempvecp;

		/*for (auto& vimg : vVehicleBmps)
		{
		if (!vimg.tid.Exists())
		{
		PCHAR spriteDictName = vimg.dict.c_str();
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED(spriteDictName))
		REQUEST_STREAMED_TEXTURE_DICT(spriteDictName, false);
		}
		}*/

		AddTitle(dict);

		switch (SpawnVehicle_index)
		{
		case OPENWHEEL:		tempvecp = &g_vehHashes_OPENWHEEL; break;
		case SUPER:			tempvecp = &g_vehHashes_SUPER; break;
		case SPORT:			tempvecp = &g_vehHashes_SPORT; break;
		case SPORTSCLASSIC: tempvecp = &g_vehHashes_SPORTSCLASSIC; break;
		case COUPE:			tempvecp = &g_vehHashes_COUPE; break;
		case MUSCLE:		tempvecp = &g_vehHashes_MUSCLE; break;
		case OFFROAD:		tempvecp = &g_vehHashes_OFFROAD; break;
		case SUV:			tempvecp = &g_vehHashes_SUV; break;
		case SEDAN:			tempvecp = &g_vehHashes_SEDAN; break;
		case COMPACT:		tempvecp = &g_vehHashes_COMPACT; break;
		case VAN:			tempvecp = &g_vehHashes_VAN; break;
		case SERVICE:		tempvecp = &g_vehHashes_SERVICE; break;
		case TRAIN:			tempvecp = &g_vehHashes_TRAIN; break;
		case EMERGENCY:		tempvecp = &g_vehHashes_EMERGENCY; break;
		case MOTORCYCLE:	tempvecp = &g_vehHashes_MOTORCYCLE; break;
		case BICYCLE:		tempvecp = &g_vehHashes_BICYCLE; break;
		case PLANE:			tempvecp = &g_vehHashes_PLANE; break;
		case HELICOPTER:	tempvecp = &g_vehHashes_HELICOPTER; break;
		case BOAT:			tempvecp = &g_vehHashes_BOAT; break;
		case INDUSTRIAL:	tempvecp = &g_vehHashes_INDUSTRIAL; break;
		case COMMERCIAL:	tempvecp = &g_vehHashes_COMMERCIAL; break;
		case UTILITY:		tempvecp = &g_vehHashes_UTILITY; break;
		case MILITARY:		tempvecp = &g_vehHashes_MILITARY; break;
		case OTHER:			tempvecp = &g_vehHashes_OTHER; break;
		case DRIFT:			tempvecp = &g_vehHashes_DRIFT; break;
		}

		//std::vector<std::string>&tempvecp2 = *tempvecp;

		if (tempvecp->empty())
		{
			Menu::SetSub_previous();
			return;
		}

		for (auto& vehModel : *tempvecp)
		{
			if (!vehModel.IsInCdImage())
				continue;

			bool bSetEngSoundPressed = false, bSpawnVehForAllPlayersPressed = false;

			switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
			{
			case SUB::SPOONER_SPAWN_VEHICLE:
				sub::Spooner::MenuOptions::AddOption_AddVehicle(vehModel.VehicleDisplayName(true), vehModel);
				break;
			case SUB::SPAWNVEHICLE:
				AddVSpawnOption_(vehModel.VehicleDisplayName(true), vehModel, Static_241);
				break;

			}
			/// one submenu back >>>
			switch (Menu::currentsub_ar[Menu::currentsub_ar_index - 1]) /// -1
			{
			case SUB::OBJECTGUN:
				AddogunOption_(vehModel.VehicleDisplayName(true), vehModel, nullptr, false);
				break;
			case SUB::KABOOMGUN:
				AddkgunOption_(vehModel.VehicleDisplayName(true), vehModel.hash, nullptr, false);
				break;
			case SUB::MSENGINESOUND:
				AddTickol(vehModel.VehicleDisplayName(true), get_vehicle_engine_sound_name(Static_12) == vehModel.VehicleDisplayName(false), bSetEngSoundPressed, bSetEngSoundPressed); if (bSetEngSoundPressed)
				{
					GTAvehicle veh12 = Static_12;
					veh12.RequestControl(200);
					set_vehicle_engine_sound_name(veh12, vehModel.VehicleDisplayName(false));
				}
				break;
			}


			if (Menu::printingop == *Menu::currentopATM)
			{
				if (_globalSpawnVehicle_drawBmps)
					DrawVehicleBmp(vehModel);
				
				DrawVehicleModelName(vehModel);

				bool bIsAFav = SpawnVehicle_IsVehicleModelAFavourite(vehModel);
				if (Menu::bit_controller)
				{
					Menu::add_IB(INPUT_SCRIPT_RLEFT, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

					if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
					{
						!bIsAFav ? SpawnVehicle_AddVehicleModelToFavourites(vehModel, Game::InputBox("", 28U, "Enter custom name:", vehModel.VehicleDisplayName(true))) : SpawnVehicle_RemoveVehicleModelFromFavourites(vehModel);
						/*if (!bIsAFav)
						{
						OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteVehicleModelSelected, "", 28U, "Enter custom name:", vehModel.VehicleDisplayName(true));
						OnscreenKeyboard::State::arg1._uint = vehModel.hash;
						}
						else SpawnVehicle_RemoveVehicleModelFromFavourites(vehModel);*/
					}
				}
				else
				{
					Menu::add_IB(VirtualKey::B, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

					if (IsKeyJustUp(VirtualKey::B))
					{
						!bIsAFav ? SpawnVehicle_AddVehicleModelToFavourites(vehModel, Game::InputBox("", 28U, "Enter custom name:", vehModel.VehicleDisplayName(true))) : SpawnVehicle_RemoveVehicleModelFromFavourites(vehModel);
						/*if (!bIsAFav)
						{
						OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteVehicleModelSelected, "", 28U, "Enter custom name:", vehModel.VehicleDisplayName(true));
						OnscreenKeyboard::State::arg1._uint = vehModel.hash;
						}
						else SpawnVehicle_RemoveVehicleModelFromFavourites(vehModel);*/
					}
				}
			}
		}

	}
	void SpawnVehicle_Favourites()
	{
		auto& _searchStr = dict2;
		using namespace SpawnVehicle_catind;

		GTAped myPed = Static_241;
		GTAvehicle myVehicle = myPed.CurrentVehicle();
		bool bIsInVehicle = myVehicle.Exists();

		AddTitle("Favourites");

		std::string xmlAddedVehicleModels = "AddedVehicleModels.xml";
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str()).status != pugi::status_ok)
		{
			doc.reset();
			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
			auto nodeRoot = doc.append_child("AddedVehicleModels");
			doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str());
			return;
		}
		pugi::xml_node nodeRoot = doc.child("AddedVehicleModels");

		bool bInputAdd = false;
		AddOption("Add New Vehicle Model", bInputAdd); if (bInputAdd)
		{
			std::string inputStrModel = Game::InputBox("", 28U, "Enter model name (e.g. adder):");
			if (inputStrModel.length() > 0)
			{
				WAIT(500);
				Model ism = GET_HASH_KEY(inputStrModel);
				if (ism.IsInCdImage())
				{
					std::string inputStrName = Game::InputBox("", 28U, "Enter custom name:", ism.VehicleDisplayName(true));
					if (SpawnVehicle_AddVehicleModelToFavourites(ism, inputStrName))
					{
						Game::Print::PrintBottomLeft("Model ~b~added~s~.");
					}
					else
						Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to add model.");
				}
			}
			else
				Game::Print::PrintError_InvalidModel();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteVehicleModelEntryName, std::string(), 28U, "Enter model name (e.g. adder):");
		}

		if (bIsInVehicle)
		{
			const Model& myVehicleModel = myVehicle.Model();
			bool bIsCurrentModelAFav = SpawnVehicle_IsVehicleModelAFavourite(myVehicleModel);
			bool bAddCurrentModelToFav = false, bRemoveCurrentModelFromFav = false;
			AddTickol("Current Vehicle's Model", bIsCurrentModelAFav, bAddCurrentModelToFav, bRemoveCurrentModelFromFav, TICKOL::BOXTICK, TICKOL::BOXBLANK);
			if (bAddCurrentModelToFav)
			{
				std::string inputStrName = Game::InputBox("", 28U, "Enter custom name:", myVehicleModel.VehicleDisplayName(true));
				if (inputStrName.length() > 0)
				{
					if (SpawnVehicle_AddVehicleModelToFavourites(myVehicleModel, inputStrName))
					{
						Game::Print::PrintBottomLeft("Model ~b~added~s~.");
					}
					else Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to add model.");
				}
				else Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteVehicleModelCurrent, std::string(), 28U, "Enter custom name:", myVehicleModel.VehicleDisplayName(true));
				//OnscreenKeyboard::State::arg1._uint = myVehicleModel.hash;
			}
			else if (bRemoveCurrentModelFromFav)
			{
				if (SpawnVehicle_RemoveVehicleModelFromFavourites(myVehicleModel))
				{
					Game::Print::PrintBottomLeft("Model ~b~removed~s~.");
				}
				else Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to remove model.");
			}
		}

		if (nodeRoot.first_child())
		{
			/*for (auto& vimg : vVehicleBmps)
			{
			if (!vimg.tid.Exists())
			{
			PCHAR spriteDictName = vimg.dict.c_str();
			if (!HAS_STREAMED_TEXTURE_DICT_LOADED(spriteDictName))
			REQUEST_STREAMED_TEXTURE_DICT(spriteDictName, false);
			}
			}*/

			AddBreak("---Added Models---");

			bool bSearchPressed = false;
			AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
				boost::to_upper(_searchStr);
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
			}

			for (auto nodeLocToLoad = nodeRoot.first_child(); nodeLocToLoad; nodeLocToLoad = nodeLocToLoad.next_sibling())
			{
				std::string vehModelName = nodeLocToLoad.attribute("modelName").as_string();
				Model vehModel = nodeLocToLoad.attribute("modelHash").as_uint(0);
				std::string vehCustomName = nodeLocToLoad.attribute("customName").as_string();

				if (!_searchStr.empty()) { if (boost::to_upper_copy(vehModelName).find(_searchStr) == std::string::npos) continue; }

				if (vehModel.hash == 0)
					vehModel = GET_HASH_KEY(vehModelName);

				std::string vehDisplayName = vehCustomName.length() ? vehCustomName : vehModel.VehicleDisplayName(true);

				if (!vehModel.IsInCdImage())
				{
					AddOption(vehDisplayName + " (Invalid)", null);
				}
				else
				{
					// The following has to be copied from SpawnVehicle_AllCats when stuff changes there. I can just make a procedure but naaaaah

					bool bSetEngSoundPressed = false, bSpawnVehForAllPlayersPressed = false;

					switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
					{
					case SUB::SPOONER_SPAWN_VEHICLE:
						sub::Spooner::MenuOptions::AddOption_AddVehicle(vehDisplayName, vehModel);
						break;
					case SUB::SPAWNVEHICLE:
						AddVSpawnOption_(vehDisplayName, vehModel, Static_241);
						break;
					}
					/// one submenu back >>>
					switch (Menu::currentsub_ar[Menu::currentsub_ar_index - 1]) /// -1
					{
					case SUB::OBJECTGUN:
						AddogunOption_(vehDisplayName, vehModel, &null, false);
						break;
					case SUB::KABOOMGUN:
						AddkgunOption_(vehDisplayName, vehModel.hash, &null, false);
						break;
					case SUB::MSENGINESOUND:
						AddTickol(vehDisplayName, get_vehicle_engine_sound_name(Static_12) == vehModel.VehicleDisplayName(false), bSetEngSoundPressed, bSetEngSoundPressed); if (bSetEngSoundPressed)
						{
							GTAvehicle veh12 = Static_12;
							veh12.RequestControl(200);
							set_vehicle_engine_sound_name(veh12, vehModel.VehicleDisplayName(false));
						}
						break;
					}
				}

				if (Menu::printingop == *Menu::currentopATM)
				{
					if (_globalSpawnVehicle_drawBmps)
						DrawVehicleBmp(vehModel);

					DrawVehicleModelName(vehModel);

					if (Menu::bit_controller)
					{
						Menu::add_IB(INPUT_SCRIPT_RLEFT, "Remove");

						if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
						{
							nodeLocToLoad.parent().remove_child(nodeLocToLoad);
							doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str());
							if (*Menu::currentopATM >= Menu::totalop)
								Menu::Up();
							return; // Yeah
						}
					}
					else
					{
						Menu::add_IB(VirtualKey::B, "Remove");

						if (IsKeyJustUp(VirtualKey::B))
						{
							nodeLocToLoad.parent().remove_child(nodeLocToLoad);
							doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlAddedVehicleModels).c_str());
							if (*Menu::currentopATM >= Menu::totalop)
								Menu::Up();
							return; // Yeah
						}
					}
				}

			}
		}
		//if (Menu::currentop > Menu::printingop) Menu::Up();

	}

	// Vehicle saver

	namespace VehicleSaver_catind
	{
		UINT8 _persistentAttachmentsTexterIndex = 0;
		UINT8 _driverVisibilityTexterIndex = 0;

		void VehSaver_SaveToFile(std::string filePath, GTAvehicle ev)
		{
			if (!ev.IsVehicle())
			{
				Game::Print::PrintBottomCentre("~r~Error:~s~ Invalid vehicle.");
				return;
			}

			GTAentity myPed = PLAYER_PED_ID();
			GTAentity driverPed = ev.GetPedOnSeat(VehicleSeat::SEAT_DRIVER);
			bool driverPedExists = driverPed.Exists();

			bool bAddAttachmentsToSpoonerDb = false;
			bool bStartTaskSeqsOnLoad = true;

			pugi::xml_document oldXml;
			if (oldXml.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
			{
				auto nodeOldRoot = oldXml.child("Vehicle");
				bAddAttachmentsToSpoonerDb = nodeOldRoot.child("SpoonerAttachments").attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase").as_bool(bAddAttachmentsToSpoonerDb);
				bStartTaskSeqsOnLoad = nodeOldRoot.child("SpoonerAttachments").attribute("StartTaskSequencesOnLoad").as_bool(bStartTaskSeqsOnLoad);
			}

			pugi::xml_document doc;

			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";

			auto nodeVehicle = doc.append_child("Vehicle"); // Root
			nodeVehicle.append_attribute("menyoo_ver") = MENYOO_CURRENT_VER_;

			const Model& eModel = ev.Model();
			nodeVehicle.append_child("ModelHash").text() = int_to_hexstring(eModel.hash, true).c_str();
			nodeVehicle.append_child("InitialHandle").text() = ev.Handle();

			auto nodeVehicleStuff = nodeVehicle.append_child("VehicleProperties");

			// Colours
			auto nodeVehicleColours = nodeVehicleStuff.append_child("Colours");
			int mod1a, mod1b, mod1c;
			GET_VEHICLE_MOD_COLOR_1(ev.Handle(), &mod1a, &mod1b, &mod1c);
			int mod2a, mod2b;
			GET_VEHICLE_MOD_COLOR_2(ev.Handle(), &mod2a, &mod2b);
			bool isPrimaryColourCustom = ev.IsPrimaryColorCustom();
			bool isSecondaryColourCustom = ev.IsSecondaryColorCustom();
			RgbS cust1 = ev.CustomPrimaryColour_get();
			RgbS cust2 = ev.CustomSecondaryColour_get();
			RgbS tyreSmokeRgb = ev.TyreSmokeColour_get();
			nodeVehicleColours.append_child("Primary").text() = ev.PrimaryColour_get();
			nodeVehicleColours.append_child("Secondary").text() = ev.SecondaryColour_get();
			nodeVehicleColours.append_child("Pearl").text() = ev.PearlescentColour_get();
			nodeVehicleColours.append_child("Rim").text() = ev.RimColour_get();
			nodeVehicleColours.append_child("Mod1_a").text() = mod1a;
			nodeVehicleColours.append_child("Mod1_b").text() = mod1b;
			nodeVehicleColours.append_child("Mod1_c").text() = mod1c;
			nodeVehicleColours.append_child("Mod2_a").text() = mod2a;
			nodeVehicleColours.append_child("Mod2_b").text() = mod2b;
			nodeVehicleColours.append_child("IsPrimaryColourCustom").text() = isPrimaryColourCustom;
			if (isPrimaryColourCustom)
			{
				nodeVehicleColours.append_child("Cust1_R").text() = cust1.R;
				nodeVehicleColours.append_child("Cust1_G").text() = cust1.G;
				nodeVehicleColours.append_child("Cust1_B").text() = cust1.B;
			}
			nodeVehicleColours.append_child("IsSecondaryColourCustom").text() = isSecondaryColourCustom;
			if (isSecondaryColourCustom)
			{
				nodeVehicleColours.append_child("Cust2_R").text() = cust2.R;
				nodeVehicleColours.append_child("Cust2_G").text() = cust2.G;
				nodeVehicleColours.append_child("Cust2_B").text() = cust2.B;
			}
			nodeVehicleColours.append_child("tyreSmoke_R").text() = tyreSmokeRgb.R;
			nodeVehicleColours.append_child("tyreSmoke_G").text() = tyreSmokeRgb.G;
			nodeVehicleColours.append_child("tyreSmoke_B").text() = tyreSmokeRgb.B;
			//if (eModel.IsBennySupportedVehicle()) {
			nodeVehicleColours.append_child("LrInterior").text() = ev.InteriorColour_get();
			nodeVehicleColours.append_child("LrDashboard").text() = ev.DashboardColour_get();
			nodeVehicleColours.append_child("LrXenonHeadlights").text() = ev.HeadlightColour_get();

			// Other stuff
			nodeVehicleStuff.append_child("Livery").text() = ev.Livery_get(); // Livery should be applied before paint is applied
			nodeVehicleStuff.append_child("NumberPlateText").text() = ev.NumberPlateText_get().c_str();
			nodeVehicleStuff.append_child("NumberPlateIndex").text() = ev.NumberPlateTextIndex_get();
			nodeVehicleStuff.append_child("WheelType").text() = ev.WheelType_get();
			nodeVehicleStuff.append_child("WheelsInvisible").text() = are_vehicle_wheels_invisible(ev);
			nodeVehicleStuff.append_child("EngineSoundName").text() = get_vehicle_engine_sound_name(ev).c_str();
			nodeVehicleStuff.append_child("WindowTint").text() = ev.WindowTint_get();
			nodeVehicleStuff.append_child("BulletProofTyres").text() = !ev.CanTyresBurst_get();
			nodeVehicleStuff.append_child("DirtLevel").text() = ev.DirtLevel_get();
			nodeVehicleStuff.append_child("PaintFade").text() = ev.PaintFade_get();
			nodeVehicleStuff.append_child("RoofState").text() = (int)ev.RoofState_get();
			nodeVehicleStuff.append_child("SirenActive").text() = ev.SirenActive_get();
			nodeVehicleStuff.append_child("EngineOn").text() = ev.EngineRunning_get();
			nodeVehicleStuff.append_child("EngineHealth").text() = ev.EngineHealth_get();
			nodeVehicleStuff.append_child("LightsOn").text() = ev.LightsOn_get();
			nodeVehicleStuff.append_child("IsRadioLoud").text() = CAN_VEHICLE_RECEIVE_CB_RADIO(ev.Handle());// != 0;
			nodeVehicleStuff.append_child("LockStatus").text() = (int)ev.LockStatus_get();

			// Neons
			auto nodeVehicleNeons = nodeVehicleStuff.append_child("Neons");
			RgbS neonLightsRgb = ev.NeonLightsColour_get();
			nodeVehicleNeons.append_child("Left").text() = ev.IsNeonLightOn(VehicleNeonLight::Left);
			nodeVehicleNeons.append_child("Right").text() = ev.IsNeonLightOn(VehicleNeonLight::Right);
			nodeVehicleNeons.append_child("Front").text() = ev.IsNeonLightOn(VehicleNeonLight::Front);
			nodeVehicleNeons.append_child("Back").text() = ev.IsNeonLightOn(VehicleNeonLight::Back);
			nodeVehicleNeons.append_child("R").text() = neonLightsRgb.R;
			nodeVehicleNeons.append_child("G").text() = neonLightsRgb.G;
			nodeVehicleNeons.append_child("B").text() = neonLightsRgb.B;

			// Extras (modExtras)
			auto nodeVehicleModExtras = nodeVehicleStuff.append_child("ModExtras");
			for (UINT8 i = 0; i < 60; i++)
			{
				if (ev.DoesExtraExist(i)) nodeVehicleModExtras.append_child(("_" + std::to_string(i)).c_str()).text() = ev.ExtraOn_get(i);
			}

			// Mods (customisations)
			auto nodeVehicleMods = nodeVehicleStuff.append_child("Mods");
			for (UINT i = 0; i < vValues_ModSlotNames.size(); i++)
			{
				bool isToggleable = (i >= 17 && i <= 22);
				if (isToggleable) nodeVehicleMods.append_child(("_" + std::to_string(i)).c_str()).text() = ev.IsToggleModOn(i);
				else nodeVehicleMods.append_child(("_" + std::to_string(i)).c_str()).text() = (std::to_string(ev.GetMod(i)) + "," + std::to_string(ev.GetModVariation(i))).c_str();
			}

			// Doors
			auto nodeVehicleDoorsOpen = nodeVehicleStuff.append_child("DoorsOpen");
			nodeVehicleDoorsOpen.append_child("BackLeftDoor").text() = ev.IsDoorOpen(VehicleDoor::BackLeftDoor);
			nodeVehicleDoorsOpen.append_child("BackRightDoor").text() = ev.IsDoorOpen(VehicleDoor::BackRightDoor);
			nodeVehicleDoorsOpen.append_child("FrontLeftDoor").text() = ev.IsDoorOpen(VehicleDoor::FrontLeftDoor);
			nodeVehicleDoorsOpen.append_child("FrontRightDoor").text() = ev.IsDoorOpen(VehicleDoor::FrontRightDoor);
			nodeVehicleDoorsOpen.append_child("Hood").text() = ev.IsDoorOpen(VehicleDoor::Hood);
			nodeVehicleDoorsOpen.append_child("Trunk").text() = ev.IsDoorOpen(VehicleDoor::Trunk);
			nodeVehicleDoorsOpen.append_child("Trunk2").text() = ev.IsDoorOpen(VehicleDoor::Trunk2);
			auto nodeVehicleDoorsBroken = nodeVehicleStuff.append_child("DoorsBroken");
			nodeVehicleDoorsBroken.append_child("BackLeftDoor").text() = ev.IsDoorBroken(VehicleDoor::BackLeftDoor);
			nodeVehicleDoorsBroken.append_child("BackRightDoor").text() = ev.IsDoorBroken(VehicleDoor::BackRightDoor);
			nodeVehicleDoorsBroken.append_child("FrontLeftDoor").text() = ev.IsDoorBroken(VehicleDoor::FrontLeftDoor);
			nodeVehicleDoorsBroken.append_child("FrontRightDoor").text() = ev.IsDoorBroken(VehicleDoor::FrontRightDoor);
			nodeVehicleDoorsBroken.append_child("Hood").text() = ev.IsDoorBroken(VehicleDoor::Hood);
			nodeVehicleDoorsBroken.append_child("Trunk").text() = ev.IsDoorBroken(VehicleDoor::Trunk);
			nodeVehicleDoorsBroken.append_child("Trunk2").text() = ev.IsDoorBroken(VehicleDoor::Trunk2);

			// Tyres Bursted
			auto nodeVehicleTyresBursted = nodeVehicleStuff.append_child("TyresBursted");
			nodeVehicleTyresBursted.append_child("FrontLeft").text() = ev.IsTyreBursted(0);
			nodeVehicleTyresBursted.append_child("FrontRight").text() = ev.IsTyreBursted(1);
			nodeVehicleTyresBursted.append_child("_2").text() = ev.IsTyreBursted(2);
			nodeVehicleTyresBursted.append_child("_3").text() = ev.IsTyreBursted(3);
			nodeVehicleTyresBursted.append_child("BackLeft").text() = ev.IsTyreBursted(4);
			nodeVehicleTyresBursted.append_child("BackRight").text() = ev.IsTyreBursted(5);
			nodeVehicleTyresBursted.append_child("_6").text() = ev.IsTyreBursted(6);
			nodeVehicleTyresBursted.append_child("_7").text() = ev.IsTyreBursted(7);
			nodeVehicleTyresBursted.append_child("_8").text() = ev.IsTyreBursted(8);

			// Multipliers
			if (g_multList_rpm.count(ev.Handle())) nodeVehicleStuff.append_child("RpmMultiplier").text() = g_multList_rpm[ev.Handle()];
			if (g_multList_torque.count(ev.Handle())) nodeVehicleStuff.append_child("TorqueMultiplier").text() = g_multList_torque[ev.Handle()];
			if (g_multList_maxSpeed.count(ev.Handle())) nodeVehicleStuff.append_child("MaxSpeed").text() = g_multList_maxSpeed[ev.Handle()];
			if (g_multList_headlights.count(ev.Handle())) nodeVehicleStuff.append_child("HeadlightIntensity").text() = g_multList_headlights[ev.Handle()];

			nodeVehicle.append_child("OpacityLevel").text() = ev.Alpha_get();
			nodeVehicle.append_child("LodDistance").text() = ev.LodDistance_get();
			nodeVehicle.append_child("IsVisible").text() = ev.IsVisible();
			if (driverPedExists)
			{
				nodeVehicle.append_child("IsDriverVisible").text() = driverPed.IsVisible();
			}
			nodeVehicle.append_child("MaxHealth").text() = ev.MaxHealth_get();
			nodeVehicle.append_child("Health").text() = ev.Health_get();

			nodeVehicle.append_child("HasGravity").text() = ev.HasGravity_get();
			nodeVehicle.append_child("IsOnFire").text() = ev.IsOnFire();
			nodeVehicle.append_child("IsInvincible").text() = ev.IsInvincible();
			nodeVehicle.append_child("IsBulletProof").text() = ev.IsBulletProof();
			//nodeVehicle.append_child("IsCollisionProof").text() = false;
			nodeVehicle.append_child("IsExplosionProof").text() = ev.IsExplosionProof();
			nodeVehicle.append_child("IsFireProof").text() = ev.IsFireProof();
			nodeVehicle.append_child("IsMeleeProof").text() = ev.IsMeleeProof();
			nodeVehicle.append_child("IsOnlyDamagedByPlayer").text() = ev.IsOnlyDamagedByPlayer();

			// Attachments
			auto nodeAttachments = nodeVehicle.append_child("SpoonerAttachments");
			nodeAttachments.append_attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase") = bAddAttachmentsToSpoonerDb;
			nodeAttachments.append_attribute("StartTaskSequencesOnLoad") = bStartTaskSeqsOnLoad;
			std::vector<GTAentity>vSpoonerAttachmentsSaved;
			vSpoonerAttachmentsSaved.push_back(ev);
			for (int bei = 0; bei < vSpoonerAttachmentsSaved.size(); bei++)
			{
				for (auto& e : sub::Spooner::Databases::EntityDb)
				{
					if (e.AttachmentArgs.isAttached)
					{
						GTAentity att;
						if (sub::Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(e.Handle, att))
						{
							if (att.Handle() == vSpoonerAttachmentsSaved[bei].Handle()) // baseEntToCheck is vSpoonerAttachmentsSaved[bei]
							{
								auto nodeAttachment = nodeAttachments.append_child("Attachment");
								sub::Spooner::FileManagement::AddEntityToXmlNode(e, nodeAttachment);
								std::string attachedToHandleStr = nodeAttachment.child("Attachment").child("AttachedTo").text().as_string();
								if (attachedToHandleStr == "PLAYER") nodeAttachment.child("Attachment").child("AttachedTo").text() = myPed.Handle();
								else if (attachedToHandleStr == "VEHICLE") nodeAttachment.child("Attachment").child("AttachedTo").text() = g_myVeh;
								vSpoonerAttachmentsSaved.push_back(e.Handle);
							}
						}
					}
				}
			}

			if (doc.save_file((const char*)filePath.c_str()))
			{
				Game::Print::PrintBottomLeft("File ~b~saved~s~.");
				addlog(ige::LogType::LOG_INFO,  "Vehicle saved - " + eModel.VehicleDisplayName(false) + " in " + filePath, __FILENAME__);
			}
			else
			{
				Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to save file.");
				addlog(ige::LogType::LOG_ERROR,  "Unable to save vehicle.", __FILENAME__);
			}
		}
		void VehSaver_ReadFromFile(std::string filePath, GTAentity ped)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
			{
				addlog(ige::LogType::LOG_ERROR,  "Unable to load vehicle file " + filePath, __FILENAME__);
				Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to load file.");
			}

			GTAentity myPed = PLAYER_PED_ID();
			GTAentity myVehicle = g_myVeh;

			auto nodeVehicle = doc.child("Vehicle"); // Root

			Model eModel = nodeVehicle.child("ModelHash").text().as_uint();
			if (!eModel.IsInCdImage())
			{
				Game::Print::PrintError_InvalidModel();
				return;
			}
			eModel.Load();

			GTAvehicle ev = FuncSpawnVehicle_(eModel, ped.Handle(), _globalSpawnVehicle_deleteOld, _globalSpawnVehicle_autoSit); // spawn vehicle to commence customisation
			if (ped.Handle() == myPed.Handle())
			{
				g_myVeh = ev.Handle();
				g_myVeh_model = eModel;
				myVehicle = g_myVeh;
			}
			SET_VEHICLE_MOD_KIT(ev.Handle(), 0);
			set_vehicle_max_upgrades(ev.Handle(), false, _globalSpawnVehicle_invincible, _globalSpawnVehicle_plateType);

			WAIT(100);

			auto nodeVehicleInitialHandle = nodeVehicle.child("InitialHandle");
			ScrHandle evInitHandle = nodeVehicleInitialHandle.text().as_int();

			ev.HasGravity_set(nodeVehicle.child("HasGravity").text().as_bool(true));

			auto nodeVehicleStuff = nodeVehicle.child("VehicleProperties");

			ev.Livery_set(nodeVehicleStuff.child("Livery").text().as_int()); // Livery should be applied before paint is applied
																			 // Colours
			auto nodeVehicleColours = nodeVehicleStuff.child("Colours");
			int mod1a = nodeVehicleColours.child("Mod1_a").text().as_int();
			int mod1b = nodeVehicleColours.child("Mod1_b").text().as_int();
			int mod1c = nodeVehicleColours.child("Mod1_c").text().as_int();
			SET_VEHICLE_MOD_COLOR_1(ev.Handle(), mod1a, mod1b, mod1c);
			int mod2a = nodeVehicleColours.child("Mod2_a").text().as_int();
			int mod2b = nodeVehicleColours.child("Mod2_b").text().as_int();
			SET_VEHICLE_MOD_COLOR_2(ev.Handle(), mod2a, mod2b);
			ev.PrimaryColour_set(nodeVehicleColours.child("Primary").text().as_int());
			ev.SecondaryColour_set(nodeVehicleColours.child("Secondary").text().as_int());
			ev.PearlescentColour_set(nodeVehicleColours.child("Pearl").text().as_int());
			ev.RimColour_set(nodeVehicleColours.child("Rim").text().as_int());
			bool isPrimaryColourCustom = nodeVehicleColours.child("IsPrimaryColourCustom").text().as_bool();
			bool isSecondaryColourCustom = nodeVehicleColours.child("IsSecondaryColourCustom").text().as_bool();
			if (isPrimaryColourCustom)
			{
				RgbS cust1;
				cust1.R = nodeVehicleColours.child("Cust1_R").text().as_int();
				cust1.G = nodeVehicleColours.child("Cust1_G").text().as_int();
				cust1.B = nodeVehicleColours.child("Cust1_B").text().as_int();
				ev.CustomPrimaryColour_set(cust1);
			}
			if (isSecondaryColourCustom)
			{
				RgbS cust2;
				cust2.R = nodeVehicleColours.child("Cust2_R").text().as_int();
				cust2.G = nodeVehicleColours.child("Cust2_G").text().as_int();
				cust2.B = nodeVehicleColours.child("Cust2_B").text().as_int();
				ev.CustomSecondaryColour_set(cust2);
			}
			RgbS tyreSmokeRgb;
			tyreSmokeRgb.R = nodeVehicleColours.child("tyreSmoke_R").text().as_int();
			tyreSmokeRgb.G = nodeVehicleColours.child("tyreSmoke_G").text().as_int();
			tyreSmokeRgb.B = nodeVehicleColours.child("tyreSmoke_B").text().as_int();
			ev.TyreSmokeColour_set(tyreSmokeRgb);
			//if (eModel.IsBennySupportedVehicle()) {
			ev.InteriorColour_set(nodeVehicleColours.child("LrInterior").text().as_int());
			ev.DashboardColour_set(nodeVehicleColours.child("LrDashboard").text().as_int());
			ev.HeadlightColour_set(nodeVehicleColours.child("LrXenonHeadlights").text().as_int());

			// Other stuff
			ev.NumberPlateText_set(nodeVehicleStuff.child("NumberPlateText").text().as_string());
			ev.NumberPlateTextIndex_set(nodeVehicleStuff.child("NumberPlateIndex").text().as_int());
			ev.WheelType_set(nodeVehicleStuff.child("WheelType").text().as_int());
			ev.WindowTint_set(nodeVehicleStuff.child("WindowTint").text().as_int());
			ev.CanTyresBurst_set(!nodeVehicleStuff.child("BulletProofTyres").text().as_bool());
			ev.DirtLevel_set(nodeVehicleStuff.child("DirtLevel").text().as_float());
			ev.PaintFade_set(nodeVehicleStuff.child("PaintFade").text().as_float());
			ev.RoofState_set((VehicleRoofState)nodeVehicleStuff.child("RoofState").text().as_int());
			ev.SirenActive_set(nodeVehicleStuff.child("SirenActive").text().as_bool());
			if (nodeVehicleStuff.child("EngineOn")) ev.EngineRunning_set(nodeVehicleStuff.child("EngineOn").text().as_bool());
			if (nodeVehicleStuff.child("EngineHealth")) ev.EngineHealth_set(nodeVehicleStuff.child("EngineHealth").text().as_int());
			if (nodeVehicleStuff.child("LightsOn")) ev.LightsOn_set(nodeVehicleStuff.child("LightsOn").text().as_bool());
			if (nodeVehicleStuff.child("IsRadioLoud").text().as_int(0))
			{
				SET_VEHICLE_RADIO_LOUD(ev.Handle(), nodeVehicleStuff.child("IsRadioLoud").text().as_int());
				SET_VEHICLE_RADIO_ENABLED(ev.Handle(), true);
			}
			ev.LockStatus_set((VehicleLockStatus)nodeVehicleStuff.child("LockStatus").text().as_int());

			// Neons
			auto nodeVehicleNeons = nodeVehicleStuff.child("Neons");
			RgbS neonLightsRgb;
			ev.SetNeonLightOn(VehicleNeonLight::Left, nodeVehicleNeons.child("Left").text().as_bool());
			ev.SetNeonLightOn(VehicleNeonLight::Right, nodeVehicleNeons.child("Right").text().as_bool());
			ev.SetNeonLightOn(VehicleNeonLight::Front, nodeVehicleNeons.child("Front").text().as_bool());
			ev.SetNeonLightOn(VehicleNeonLight::Back, nodeVehicleNeons.child("Back").text().as_bool());
			neonLightsRgb.R = nodeVehicleNeons.child("R").text().as_int();
			neonLightsRgb.G = nodeVehicleNeons.child("G").text().as_int();
			neonLightsRgb.B = nodeVehicleNeons.child("B").text().as_int();
			ev.NeonLightsColour_set(neonLightsRgb);

			// Extras (modExtras)
			auto nodeVehicleModExtras = nodeVehicleStuff.child("ModExtras");
			for (auto nodeVehicleModExtrasObject = nodeVehicleModExtras.first_child(); nodeVehicleModExtrasObject; nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling())
			{
				ev.ExtraOn_set(stoi(std::string(nodeVehicleModExtrasObject.name()).substr(1)), nodeVehicleModExtrasObject.text().as_bool());
			}

			// Mods (customisations)
			auto nodeVehicleMods = nodeVehicleStuff.child("Mods");
			for (auto nodeVehicleModsObject = nodeVehicleMods.first_child(); nodeVehicleModsObject; nodeVehicleModsObject = nodeVehicleModsObject.next_sibling())
			{
				int modType = stoi(std::string(nodeVehicleModsObject.name()).substr(1));
				std::string modValueStr = nodeVehicleModsObject.text().as_string();
				if (modValueStr.find(",") == std::string::npos) // isToggleable
				{
					ev.ToggleMod(modType, nodeVehicleModsObject.text().as_bool());
				}
				else
				{
					ev.SetMod(modType, stoi(modValueStr.substr(0, modValueStr.find(","))), stoi(modValueStr.substr(modValueStr.find(",") + 1)));
				}
			}

			// Doors
			auto nodeVehicleDoorsOpen = nodeVehicleStuff.child("DoorsOpen");
			if (nodeVehicleDoorsOpen)
			{
				nodeVehicleDoorsOpen.child("BackLeftDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::BackLeftDoor, false, true) : ev.CloseDoor(VehicleDoor::BackLeftDoor, true);
				nodeVehicleDoorsOpen.child("BackRightDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::BackRightDoor, false, true) : ev.CloseDoor(VehicleDoor::BackRightDoor, true);
				nodeVehicleDoorsOpen.child("FrontLeftDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::FrontLeftDoor, false, true) : ev.CloseDoor(VehicleDoor::FrontLeftDoor, true);
				nodeVehicleDoorsOpen.child("FrontRightDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::FrontRightDoor, false, true) : ev.CloseDoor(VehicleDoor::FrontRightDoor, true);
				nodeVehicleDoorsOpen.child("Hood").text().as_bool() ? ev.OpenDoor(VehicleDoor::Hood, false, true) : ev.CloseDoor(VehicleDoor::Hood, true);
				nodeVehicleDoorsOpen.child("Trunk").text().as_bool() ? ev.OpenDoor(VehicleDoor::Trunk, false, true) : ev.CloseDoor(VehicleDoor::Trunk, true);
				nodeVehicleDoorsOpen.child("Trunk2").text().as_bool() ? ev.OpenDoor(VehicleDoor::Trunk2, false, true) : ev.CloseDoor(VehicleDoor::Trunk2, true);
			}
			auto nodeVehicleDoorsBroken = nodeVehicleStuff.child("DoorsBroken");
			if (nodeVehicleDoorsBroken)
			{
				if (nodeVehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::BackLeftDoor, true);
				if (nodeVehicleDoorsBroken.child("BackRightDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::BackRightDoor, true);
				if (nodeVehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::FrontLeftDoor, true);
				if (nodeVehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::FrontRightDoor, true);
				if (nodeVehicleDoorsBroken.child("Hood").text().as_bool()) ev.BreakDoor(VehicleDoor::Hood, true);
				if (nodeVehicleDoorsBroken.child("Trunk").text().as_bool()) ev.BreakDoor(VehicleDoor::Trunk, true);
				if (nodeVehicleDoorsBroken.child("Trunk2").text().as_bool()) ev.BreakDoor(VehicleDoor::Trunk2, true);
			}

			// Tyres
			auto nodeVehicleTyresBursted = nodeVehicleStuff.child("TyresBursted");
			if (nodeVehicleTyresBursted)
			{
				if (nodeVehicleTyresBursted.child("FrontLeft").text().as_bool()) ev.BurstTyre(0);
				if (nodeVehicleTyresBursted.child("FrontRight").text().as_bool()) ev.BurstTyre(1);
				if (nodeVehicleTyresBursted.child("_2").text().as_bool()) ev.BurstTyre(2);
				if (nodeVehicleTyresBursted.child("_3").text().as_bool()) ev.BurstTyre(3);
				if (nodeVehicleTyresBursted.child("BackLeft").text().as_bool()) ev.BurstTyre(4);
				if (nodeVehicleTyresBursted.child("BackRight").text().as_bool()) ev.BurstTyre(5);
				if (nodeVehicleTyresBursted.child("_6").text().as_bool()) ev.BurstTyre(6);
				if (nodeVehicleTyresBursted.child("_7").text().as_bool()) ev.BurstTyre(7);
				if (nodeVehicleTyresBursted.child("_8").text().as_bool()) ev.BurstTyre(8);
			}

			if (nodeVehicleStuff.child("WheelsInvisible").text().as_bool()) set_vehicle_wheels_invisible(ev, true);
			std::string engSoundName = nodeVehicleStuff.child("EngineSoundName").text().as_string();
			if (engSoundName.length()) set_vehicle_engine_sound_name(ev, engSoundName);

			// Multipliers
			auto nodeVehicleRpmMultiplier = nodeVehicleStuff.child("RpmMultiplier");
			auto nodeVehicleTorqueMultiplier = nodeVehicleStuff.child("TorqueMultiplier");
			auto nodeVehicleMaxSpeed = nodeVehicleStuff.child("MaxSpeed");
			auto nodeVehicleHeadlightIntensity = nodeVehicleStuff.child("HeadlightIntensity");
			if (nodeVehicleRpmMultiplier)
			{
				MODIFY_VEHICLE_TOP_SPEED(ev.Handle(), nodeVehicleRpmMultiplier.text().as_float());
				g_multList_rpm[ev.Handle()] = nodeVehicleRpmMultiplier.text().as_float();
			}
			if (nodeVehicleTorqueMultiplier)
			{
				SET_VEHICLE_CHEAT_POWER_INCREASE(ev.Handle(), nodeVehicleTorqueMultiplier.text().as_float());
				g_multList_torque[ev.Handle()] = nodeVehicleTorqueMultiplier.text().as_float();
			}
			if (nodeVehicleMaxSpeed)
			{
				SET_ENTITY_MAX_SPEED(ev.Handle(), nodeVehicleMaxSpeed.text().as_float());
				g_multList_maxSpeed[ev.Handle()] = nodeVehicleMaxSpeed.text().as_float();
			}
			if (nodeVehicleHeadlightIntensity)
			{
				SET_VEHICLE_LIGHT_MULTIPLIER(ev.Handle(), nodeVehicleHeadlightIntensity.text().as_float());
				g_multList_headlights[ev.Handle()] = nodeVehicleHeadlightIntensity.text().as_float();
			}

			int opacityLevel = nodeVehicle.child("OpacityLevel").text().as_int();
			if (opacityLevel < 255) ev.Alpha_set(opacityLevel);
			ev.LodDistance_set(nodeVehicle.child("LodDistance").text().as_int());

			bool bDriverIsVisible = ped.IsVisible();
			bool bVehicleIsVisible = nodeVehicle.child("IsVisible").text().as_bool();
			if (!bVehicleIsVisible) ev.SetVisible(false);
			if (nodeVehicle.child("IsDriverVisible"))
			{
				bool bSetDriverVisible = nodeVehicle.child("IsDriverVisible").text().as_bool();
				ped.RequestControl();
				switch (_driverVisibilityTexterIndex)
				{
				case 0:
					if (!bVehicleIsVisible || (!bDriverIsVisible && bSetDriverVisible || bDriverIsVisible && !bSetDriverVisible))
						ped.SetVisible(bSetDriverVisible);
					break; // FileDecides
				case 1:
					if (!bVehicleIsVisible)
						ped.SetVisible(bDriverIsVisible);
					break; // Retain
				case 2:
					ped.SetVisible(false);
					break; // ForceOff
				case 3:
					ped.SetVisible(true);
					break; // ForceOn
				}
			}
			if (nodeVehicle.child("MaxHealth")) ev.MaxHealth_set(nodeVehicle.child("MaxHealth").text().as_int());
			if (nodeVehicle.child("Health")) ev.Health_set(nodeVehicle.child("Health").text().as_int());

			ev.SetOnFire(nodeVehicle.child("IsOnFire").text().as_bool());
			ev.SetInvincible(nodeVehicle.child("IsInvincible").text().as_bool());
			ev.SetBulletProof(nodeVehicle.child("IsBulletProof").text().as_bool());
			ev.IsCollisionEnabled_set(true);
			//ev.SetCollisionProof(nodeVehicle.child("IsCollisionProof").text().as_bool());
			ev.SetExplosionProof(nodeVehicle.child("IsExplosionProof").text().as_bool());
			ev.SetFireProof(nodeVehicle.child("IsFireProof").text().as_bool());
			ev.SetMeleeProof(nodeVehicle.child("IsMeleeProof").text().as_bool());
			ev.SetOnlyDamagedByPlayer(nodeVehicle.child("IsOnlyDamagedByPlayer").text().as_bool());

			// Attachments
			std::unordered_set<Hash> vModelHashes;
			std::vector<sub::Spooner::SpoonerEntityWithInitHandle> vSpawnedAttachments;
			auto nodeAttachments = nodeVehicle.child("SpoonerAttachments");
			bool bAddAttachmentsToSpoonerDb = nodeAttachments.attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase").as_bool(false);
			bool bStartTaskSeqsOnLoad = nodeAttachments.attribute("StartTaskSequencesOnLoad").as_bool(true);
			switch (_persistentAttachmentsTexterIndex)
			{
			case 0: break; // FileDecides
			case 1: bAddAttachmentsToSpoonerDb = false; break; // ForceOff
			case 2: bAddAttachmentsToSpoonerDb = true; break; // ForceOn
			}

			for (auto nodeAttachment = nodeAttachments.first_child(); nodeAttachment; nodeAttachment = nodeAttachment.next_sibling())
			{
				auto e = sub::Spooner::FileManagement::SpawnEntityFromXmlNode(nodeAttachment, vModelHashes);
				vSpawnedAttachments.push_back(e);
			}

			WAIT(100);

			if (!nodeVehicleInitialHandle)
			{
				for (auto& e : vSpawnedAttachments)
				{
					sub::Spooner::EntityManagement::AttachEntity(e.e, ev, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
				}
			}
			else
			{
				sub::Spooner::SpoonerEntityWithInitHandle evwih;
				evwih.e.Handle = ev;
				evwih.e.Dynamic = true;
				evwih.e.Type = EntityType::VEHICLE;
				evwih.e.HashName = get_vehicle_model_label(evwih.e.Handle.Model(), true);
				evwih.initHandle = evInitHandle;
				vSpawnedAttachments.push_back(evwih); // ADD EV

				for (auto& e : vSpawnedAttachments)
				{
					if (e.e.AttachmentArgs.isAttached)
					{
						for (auto& b : vSpawnedAttachments)
						{
							if (e.attachedToHandle == b.initHandle)
							{
								sub::Spooner::EntityManagement::AttachEntity(e.e, b.e.Handle, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
								break;
							}

						}
					}
				}

				//vSpawnedAttachments.pop_back(); // REMOVE EV
			}
			if (bAddAttachmentsToSpoonerDb)
			{
				for (auto& e : vSpawnedAttachments)
				{
					if (!e.e.TaskSequence.empty())
					{
						auto& vTskPtrs = e.e.TaskSequence.AllTasks();
						for (auto& u : vSpawnedAttachments)
						{
							for (auto& tskPtr : vTskPtrs)
							{
								tskPtr->LoadTargetingDressing(u.initHandle, u.e.Handle.Handle());
							}
						}
						if (bStartTaskSeqsOnLoad) e.e.TaskSequence.Start();
					}
					sub::Spooner::Databases::EntityDb.push_back(e.e);
				}
			}
			else
			{
				if (NETWORK_IS_IN_SESSION() && !vSpawnedAttachments.empty())
				{
					if (vSpawnedAttachments.back().e.Handle.Handle() == ev.Handle()) vSpawnedAttachments.back().e.Handle = 0;
				}
				for (auto& e : vSpawnedAttachments)
				{
					if (!_globalSpawnVehicle_persistent) e.e.Handle.NoLongerNeeded();
				}
			}

			for (auto& amh : vModelHashes) Model(amh).Unload();
			eModel.Unload();

			addlog(ige::LogType::LOG_INFO,  "Loaded vehicle file " + filePath, __FILENAME__);
			std::ostringstream ss;
			ss << "Spawned vehicle from file with " << (vSpawnedAttachments.size() - 1) << " attachments. ";
			if (bAddAttachmentsToSpoonerDb)
				ss << "The attachments have been added to the Spooner Database.";
			Game::Print::PrintBottomLeft(ss);
		}

		void saveColourVals()
		{
			std::ofstream outfile;
			auto& _dir = dict3;
			int r, g, b;
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12, &r, &g, &b);
			std::array<int, 3> hsv = gethsvfromrgb(r, g, b);
			float normalisedcolour = normalisehsv(hsv[0], hsv[1], hsv[2]);

			std::vector<std::pair<std::string, std::pair<std::string, float>>> ColourNames
			{
				{"3850041493", {"black", 0}},
				{"807368168", {"grey", 35}},
				{"607306136", {"silver", 53}},
				{"4066575219", {"white", 71}},
				{"1325014621", {"beige", 72}},
				{"2201497177", {"brown", 110}},
				{"1585269136", {"red", 122}},
				{"2639756769", {"orange", 129}},
				{"3440150791", {"yellow", 136}},
				{"306110198", {"green", 171}},
				{"1345033317", {"graphite", 214}},
				{"3826758445", {"blue", 240}},
				{"2019367074", {"pink", 352}},
			};

			float minDiff = INFINITY;
			std::string nearestColour;
			std::string nearestAudio;
			for (const auto& colour : ColourNames)
			{
				float diff = std::abs(colour.second.second - normalisedcolour);
				if (diff < minDiff)
				{
					minDiff = diff;
					nearestColour = colour.second.first;
					nearestAudio = colour.first;
				}
			}
			int prim, sec;
			std::string finish;
			GET_VEHICLE_COLOURS(Static_12, &prim, &sec);
			switch (prim)
			{
			case 0:
				finish = "1";
				break;
			case 111:
				finish = "2";
				break;
			case 12:
				finish = "3";
				break;
			case 15:
				finish = "4";
				break;
			case 21:
				finish = "5";
				break;
			case 117:
				finish = "6";
				break;
			case 120:
				finish = "7";
				break;
			case 158:
				finish = "8";
				break;
			case 159:
				finish = "9";
				break;
			case 2: default:
				finish = "normal";
				break;
			}

			std::string customname = Game::InputBox("noname", 64, "Enter Colour Name");

			outfile.open(dict3 + "\\Custom colours.txt", std::ios_base::app); // append instead of overwrite
			outfile << "Check https://gtamods.com/wiki/Carcols.ymt for all colour names, audio hashes and IDs.\n";
			outfile << "<Item>\n";
			outfile << "      <color value = \"0xFF" + ((int_to_hexstring(r, false)) + int_to_hexstring(g, false) + int_to_hexstring(b, false) + "\"/>\n");
			outfile << "      <metallicID>EVehicleModelColorMetallic_" + finish + "</metallicID>\n";
			outfile << "      <audioColor>POLICE_SCANNER_COLOUR_" + nearestColour + "</audioColor>\n";
			outfile << "      <audioPrefix>none</audioPrefix>\n";
			outfile << "      <audioColorHash value=\"" + nearestAudio + "\"/>\n";
			outfile << "      <audioPrefixHash value=\"0\"/>\n";
			outfile << "      <colorName> " + std::to_string(static_cast<int>(normalisedcolour)) + " " + customname + " </colorName>\n";
			outfile << "</Item>\n";
			outfile << "\n";
			Game::Print::PrintBottomLeft("Saved Current Colour: " + customname + "\n" + "HSV: " + std::to_string(hsv[0]) + ", " + std::to_string(hsv[1]) + ", " + std::to_string(hsv[2]));
		}

		int saveCarVars(GTAvehicle vehicle)
		{
			std::ofstream outfile;
			const Model& eModel = vehicle.Model();
			std::string spawnname = GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(eModel.hash);
			int color1 = vehicle.PrimaryColour_get(), 
				color2 = vehicle.SecondaryColour_get(),
				color3 = vehicle.PearlescentColour_get(),
				color4 = vehicle.RimColour_get(),
				color5 = vehicle.InteriorColour_get(),
				color6 = vehicle.DashboardColour_get();


			outfile.open(dict3 + "\\Carvar colours.txt", std::ios_base::app); // append instead of overwrite
			outfile << spawnname << "\n";
			outfile << std::to_string(color1) << "\n";
			outfile << std::to_string(color2) << "\n";
			outfile << std::to_string(color3) << "\n";
			outfile << std::to_string(color4) << "\n";
			outfile << std::to_string(color5) << "\n";
			outfile << std::to_string(color6) << "\n";
			outfile << "\n";
			Game::Print::PrintBottomLeft("Saved Vehicle Carvariations");
			return 0;
		}

		void Sub_VehSaver()
		{
			auto& _searchStr = dict2;
			auto& _name = dict;
			auto& _dir = dict3;

			auto ped = Static_241;
			auto vehicle = GET_VEHICLE_PED_IS_USING(ped);
			bool isPedInVeh = IS_PED_IN_ANY_VEHICLE(ped, 0) || IS_PED_SITTING_IN_ANY_VEHICLE(ped);

			bool save2 = false, bCreateFolderPressed = false, savecarvar = false, ms_paints_savergb = false;
			std::vector<std::string> vfilnames;

			AddTitle("Saved Vehicles");

			bool persistentAttachments_plus = 0, persistentAttachments_minus = 0;
			AddTexter("AddAttachmentsToSpoonerDB", _persistentAttachmentsTexterIndex, std::vector<std::string>{"FileDecides", "ForceOff", "ForceOn"}, null, persistentAttachments_plus, persistentAttachments_minus);
			if (persistentAttachments_plus) { if (_persistentAttachmentsTexterIndex < 2) _persistentAttachmentsTexterIndex++; }
			if (persistentAttachments_minus) { if (_persistentAttachmentsTexterIndex > 0) _persistentAttachmentsTexterIndex--; }

			bool driverVisi_plus = 0, driverVisi_minus = 0;
			AddTexter("Driver Visibility", _driverVisibilityTexterIndex, std::vector<std::string>{"FileDecides", "Retain" "ForceOff", "ForceOn"}, null, driverVisi_plus, driverVisi_minus);
			if (driverVisi_plus) { if (_driverVisibilityTexterIndex < 3) _driverVisibilityTexterIndex++; }
			if (driverVisi_plus) { if (_driverVisibilityTexterIndex > 0) _driverVisibilityTexterIndex--; }


			AddOption("Save Current Vehicle", save2);

			AddOption("Store CarVariations", savecarvar);
			AddOption("Save Colour Profile", ms_paints_savergb);

			AddOption("Create New Folder", bCreateFolderPressed);

			//get_all_filenames_with_extension(GetPathffA(Pathff::Vehicle, false), ".xml", vfilnames, false);
			if (_dir.empty()) _dir = GetPathffA(Pathff::Vehicle, false);
			DIR* dir_point = opendir(_dir.c_str());
			dirent* entry = readdir(dir_point);
			while (entry)
			{
				vfilnames.push_back(entry->d_name);
				entry = readdir(dir_point);
			}
			closedir(dir_point);

			AddBreak("---Found Files---");

			bool bFolderBackPressed = false;
			AddOption("..", bFolderBackPressed); if (bFolderBackPressed)
			{
				_dir = _dir.substr(0, _dir.rfind("\\"));
				Menu::currentop = 6;
			}

			if (!vfilnames.empty())
			{
				bool bSearchPressed = false;
				AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
					boost::to_upper(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto& filname : vfilnames)
				{
					if (filname.front() == '.' || filname.front() == ',')
						continue;
					if (!_searchStr.empty()) { if (boost::to_upper_copy(filname).find(_searchStr) == std::string::npos) continue; }

					bool isFolder = PathIsDirectoryA((_dir + "\\" + filname).c_str()) != 0;
					bool isXml = filname.length() > 4 && filname.rfind(".xml") == filname.length() - 4;
					TICKOL icon = TICKOL::NONE;
					if (isFolder) icon = TICKOL::ARROWRIGHT;
					else if (isXml) icon = TICKOL::TICK2;
					bool bFilePressed = false;

					if (isFolder)
					{
						AddTickol(filname + " >>>", true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
						{
							_dir = _dir + "\\" + filname;
							Menu::currentop = 6;
						}

						if (Menu::printingop == *Menu::currentopATM && !bFilePressed)
						{
							if (FolderPreviewBmps_catind::bFolderBmpsEnabled)
								FolderPreviewBmps_catind::DrawBmp(_dir + "\\" + filname);
						}
					}
					else if (isXml)
					{
						AddTickol(filname, true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
						{
							_name = filname.substr(0, filname.rfind('.'));
							Menu::SetSub_delayed = SUB::VEHICLE_SAVER_INITEM;
							return;
						}
					}
				}
			}


			if (save2)
			{
				if (isPedInVeh)
				{
					std::string inputStr = Game::InputBox("", 28U, "Enter file name:");
					if (inputStr.length() > 0)
					{
						VehSaver_SaveToFile(_dir + "\\" + inputStr + ".xml", vehicle);
					}
					else
						Game::Print::PrintError_InvalidInput();
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SaveVehicleToFile, std::string(), 28U, "Enter file name:");
					//OnscreenKeyboard::State::arg1._int = vehicle;
					//OnscreenKeyboard::State::arg2._ptr = reinterpret_cast<void*>(&_dir);
				}
			}

			if (ms_paints_savergb)
				saveColourVals();

			if (savecarvar)
			{
				if (isPedInVeh)
					saveCarVars(vehicle);
			}

			if (bCreateFolderPressed)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter folder name:");
				if (inputStr.length() > 0)
				{
					if (CreateDirectoryA((_dir + "\\" + inputStr).c_str(), NULL) ||
						GetLastError() == ERROR_ALREADY_EXISTS)
					{
						_dir = _dir + "\\" + inputStr;
						Menu::currentop = 6;
						Game::Print::PrintBottomLeft("Folder ~b~created~s~.");
					}
					else
					{
						Game::Print::PrintBottomCentre("~r~Failed~s~ to create folder.");
					}
				}
				else
					Game::Print::PrintError_InvalidInput();
				return;
				// No OnscreenKeyboard!
			}

			//if (Menu::currentop > Menu::printingop) Menu::Up();
			//else if (Menu::currentop <= 0) Menu::Down();
		}
		void Sub_VehSaver_InItem()
		{
			auto& _name = dict;
			auto& _dir = dict3;
			std::string filePath = _dir + "\\" + _name + ".xml";

			auto& ped = Static_241;
			auto vehicle = GET_VEHICLE_PED_IS_USING(ped);
			bool isPedInVeh = IS_PED_IN_ANY_VEHICLE(ped, 0) || IS_PED_SITTING_IN_ANY_VEHICLE(ped);

			bool bLoad = 0, bRename = 0, bOverwrite = 0, bDelete = 0;

			AddTitle(dict);
			AddOption("Spawn", bLoad);
			AddOption("Rename File", bRename);
			if (isPedInVeh) AddOption("Overwrite File", bOverwrite);
			AddOption("Delete File", bDelete);

			if (bLoad)
			{
				VehSaver_ReadFromFile(filePath, ped);
			}

			if (bRename)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter new name:", _name);
				if (inputStr.length() > 0)
				{
					std::string oldPath = _dir + "\\" + _name + ".xml";
					std::string newPath = _dir + "\\" + inputStr + ".xml";
					if (rename(oldPath.c_str(), (newPath).c_str()) == 0)
					{
						Game::Print::PrintBottomLeft("File ~b~renamed~s~.");
						_name = inputStr;
					}
					else
						Game::Print::PrintBottomCentre("~r~Error~s~ renaming file.");
				}
				else
					Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::RenameVehicleFile, std::string(), 28U, "Enter new name:", _name);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_name);
				//OnscreenKeyboard::State::arg2._ptr = reinterpret_cast<void*>(&_dir);
			}

			if (bOverwrite)
			{
				if (isPedInVeh)
				{
					VehSaver_SaveToFile(filePath, vehicle);
				}
			}

			if (bDelete)
			{
				if (remove(filePath.c_str()) == 0)
					Game::Print::PrintBottomLeft("File ~b~deleted~s~.");
				else
					Game::Print::PrintBottomCentre("~r~Error~s~ deleting file.");
				Menu::SetSub_previous();
				Menu::Up();
				return;
			}

			//=============================================================================
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
			{
				AddBreak("---Attributes---");
				auto nodeVehicle = doc.child("Vehicle"); // Root

				auto nodeDriverVisible = nodeVehicle.child("IsDriverVisible");
				if (nodeDriverVisible)
				{
					bool bToggleDriverVisiblePressed = false;
					AddTickol("Driver Visibility", nodeDriverVisible.text().as_bool(), bToggleDriverVisiblePressed, bToggleDriverVisiblePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleDriverVisiblePressed)
					{
						nodeDriverVisible.text() = !nodeDriverVisible.text().as_bool();
						doc.save_file((const char*)filePath.c_str());
					}
				}

				auto nodeAddAttachmentsToSpoonerDb = nodeVehicle.child("SpoonerAttachments").attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase");
				bool bAddAttachemntsToSpoonerDb = nodeAddAttachmentsToSpoonerDb.as_bool();
				bool bToggleAddAttachmentsToSpoonerDbPressed = false;
				AddTickol("Persistent Attachments (AddToSpoonerDb)", bAddAttachemntsToSpoonerDb, bToggleAddAttachmentsToSpoonerDbPressed, bToggleAddAttachmentsToSpoonerDbPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleAddAttachmentsToSpoonerDbPressed)
				{
					nodeAddAttachmentsToSpoonerDb = !nodeAddAttachmentsToSpoonerDb.as_bool();
					bAddAttachemntsToSpoonerDb = !bAddAttachemntsToSpoonerDb;
					doc.save_file((const char*)filePath.c_str());
				}

				if (bAddAttachemntsToSpoonerDb)
				{
					auto nodeStartTaskSeqOnLoad = nodeVehicle.child("SpoonerAttachments").attribute("StartTaskSequencesOnLoad");
					if (nodeStartTaskSeqOnLoad)
					{
						bool bToggleStartTaskSeqOnLoadPressed = false;
						AddTickol("Start Task Sequences Immediately", nodeStartTaskSeqOnLoad.as_bool(), bToggleStartTaskSeqOnLoadPressed, bToggleStartTaskSeqOnLoadPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleStartTaskSeqOnLoadPressed)
						{
							nodeStartTaskSeqOnLoad = !nodeStartTaskSeqOnLoad.as_bool();
							doc.save_file((const char*)filePath.c_str());
						}
					}
				}

			}

		}

	}

}




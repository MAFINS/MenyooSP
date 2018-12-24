/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "OfficeGarages.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAped.h"

#include "Locations.h"
#include "TeleMethods.h"

#include <string>
#include <vector>
#include <utility>

namespace sub::TeleportLocations_catind
{
	namespace OfficeGarages
	{
		const std::vector<std::string> vGarageIds
		{
			{ "1" },
			{ "2" },
			{ "3" },
			{ "Autoshop" }
		};
		struct OfficeGarageLocation { Vector3 pos; const PCHAR ipl; };
		const std::vector<OfficeGarageLocation> vOffices_ArcadiusBusinessCentre_Garages
		{
			{ { -197.5016f, -579.3605f, 136.0005f },"imp_dt1_02_cargarage_a" }, // 1
			{ { -123.7161f, -569.9810f, 136.0005f },"imp_dt1_02_cargarage_b" }, // 2
			{ { -136.6278f, -623.5266f, 136.0005f },"imp_dt1_02_cargarage_c" }, // 3
			{ { -144.2712f, -593.0843f, 167.0001f },"imp_dt1_02_modgarage" }, // Autoshop
		};
		const std::vector<OfficeGarageLocation> vOffices_MazeBankBuilding_Garages
		{
			{ { -90.7866f, -821.2824f, 222.0005f },"imp_dt1_11_cargarage_a" },
			{ { -71.7458f, -831.5193f, 222.0005f },"imp_dt1_11_cargarage_b" },
			{ { -79.7060f, -806.6108f, 222.0005f },"imp_dt1_11_cargarage_c" },
			{ { -73.9068f, -815.3940f, 285.0001f },"imp_dt1_11_modgarage" },
		};
		const std::vector<OfficeGarageLocation> vOffices_LombankWest_Garages
		{
			{ { -1585.6804f, -561.9070f, 86.5005f },"imp_sm_13_cargarage_a" },
			{ { -1563.4013f, -557.4779f, 86.5005f },"imp_sm_13_cargarage_b" },
			{ { -1560.1299f, -579.9451f, 86.5005f },"imp_sm_13_cargarage_c" },
			{ { -1574.5394f, -571.2640f, 105.2001f },"imp_sm_13_modgarage" },
		};
		const std::vector<OfficeGarageLocation> vOffices_MazeBankWest_Garages
		{
			{ { -1395.2725f, -480.5121f, 57.1005f },"imp_sm_15_cargarage_a" },
			{ { -1394.6155f, -481.2531f, 49.1005f },"imp_sm_15_cargarage_b" },
			{ { -1368.8768f, -471.6262f, 57.1005f },"imp_sm_15_cargarage_c" },
			{ { -1389.9446f, -480.1762f, 78.2001f },"imp_sm_15_modgarage" },
		};
		const std::vector<std::pair<const PCHAR, const std::vector<OfficeGarageLocation>*>> vLocations
		{
			{ "Arcadius Business Centre", &vOffices_ArcadiusBusinessCentre_Garages },
			{ "Maze Bank Building", &vOffices_MazeBankBuilding_Garages },
			{ "Lombank West", &vOffices_LombankWest_Garages },
			{ "Maze Bank West", &vOffices_MazeBankWest_Garages },
		};
		struct GarageInteriorOption { const PCHAR name; const PCHAR value; };
		const std::vector<GarageInteriorOption> vFloorOptions // For Autoshop
		{
			{ "None", "Floor_vinyl_00" },
			{ "1", "Floor_vinyl_01" },
			{ "2", "Floor_vinyl_02" },
			{ "3", "Floor_vinyl_03" },
			{ "4", "Floor_vinyl_04" },
			{ "5", "Floor_vinyl_05" },
			{ "6", "Floor_vinyl_06" },
			{ "7", "Floor_vinyl_07" },
			{ "8", "Floor_vinyl_08" },
			{ "9", "Floor_vinyl_09" },
			{ "10", "Floor_vinyl_10" },
			{ "11", "Floor_vinyl_11" },
			{ "12", "Floor_vinyl_12" },
			{ "13", "Floor_vinyl_13" },
			{ "14", "Floor_vinyl_14" },
			{ "15", "Floor_vinyl_15" },
			{ "16", "Floor_vinyl_16" },
			{ "17", "Floor_vinyl_17" },
			{ "18", "Floor_vinyl_18" },
			{ "19", "Floor_vinyl_19" },
			{ "20", "Floor_vinyl_20" },
		};
		const std::vector<GarageInteriorOption> vDecorOptions
		{
			{ "None", "Garage_Decor_00" },
			{ "1", "Garage_Decor_01" },
			{ "2", "Garage_Decor_02" },
			{ "3", "Garage_Decor_03" },
			{ "4", "Garage_Decor_04" },
			{ "5", "Garage_Decor_05" },
			{ "6", "Garage_Decor_06" },
			{ "7", "Garage_Decor_07" },
			{ "8", "Garage_Decor_08" },
			{ "9", "Garage_Decor_09" },
			{ "10", "Garage_Decor_10" },
			{ "11", "Garage_Decor_11" },
			{ "12", "Garage_Decor_12" },
			{ "13", "Garage_Decor_13" },
			{ "14", "Garage_Decor_14" },
			{ "15", "Garage_Decor_15" },
			{ "16", "Garage_Decor_16" },
			{ "17", "Garage_Decor_17" },
			{ "18", "Garage_Decor_18" },
			{ "19", "Garage_Decor_19" },
			{ "20", "Garage_Decor_20" },
		};
		const std::vector<GarageInteriorOption> vLightingOptions
		{
			{ "None", "Lighting_Option00" },
			{ "1", "Lighting_Option01" },
			{ "2", "Lighting_Option02" },
			{ "3", "Lighting_Option03" },
			{ "4", "Lighting_Option04" },
			{ "5", "Lighting_Option05" },
			{ "6", "Lighting_Option06" },
			{ "7", "Lighting_Option07" },
			{ "8", "Lighting_Option08" },
			{ "9", "Lighting_Option09" },
			{ "10", "Lighting_Option10" },
			{ "11", "Lighting_Option11" },
			{ "12", "Lighting_Option12" },
			{ "13", "Lighting_Option13" },
			{ "14", "Lighting_Option14" },
			{ "15", "Lighting_Option15" },
			{ "16", "Lighting_Option16" },
			{ "17", "Lighting_Option17" },
			{ "18", "Lighting_Option18" },
			{ "19", "Lighting_Option19" },
			{ "20", "Lighting_Option20" },
		};
		const std::vector<GarageInteriorOption> vNumStyleOptions // _N1/_N2/_N3
		{
			{ "None", "Numbering_Style00" },
			{ "1", "Numbering_Style01" },
			{ "2", "Numbering_Style02" },
			{ "3", "Numbering_Style03" },
			{ "4", "Numbering_Style04" },
			{ "5", "Numbering_Style05" },
			{ "6", "Numbering_Style06" },
			{ "7", "Numbering_Style07" },
			{ "8", "Numbering_Style08" },
			{ "9", "Numbering_Style09" },
			{ "10", "Numbering_Style10" },
			{ "11", "Numbering_Style11" },
			{ "12", "Numbering_Style12" },
			{ "13", "Numbering_Style13" },
			{ "14", "Numbering_Style14" },
			{ "15", "Numbering_Style15" },
			{ "16", "Numbering_Style16" },
			{ "17", "Numbering_Style17" },
			{ "18", "Numbering_Style18" },
			{ "19", "Numbering_Style19" },
			{ "20", "Numbering_Style20" },
		};

		struct OfficeGarageInfoStructure
		{
			std::pair<const PCHAR, const std::vector<OfficeGarageLocation>*> const * location;
			UINT8 garageId;
			UINT8 floorOption;
			UINT8 decorOption;
			UINT8 lightingOption;
			UINT8 numStyleOption;

			void operator = (const OfficeGarageInfoStructure& right)
			{
				this->location = right.location;
				this->garageId = right.garageId;
				this->floorOption = right.floorOption;
				this->decorOption = right.decorOption;
				this->lightingOption = right.lightingOption;
				this->numStyleOption = right.numStyleOption;
			}
		};
		OfficeGarageInfoStructure currentGarageInfo = { nullptr, 0, 0, 0, 0, 0 };

		void CreateOfficeGarage(OfficeGarageInfoStructure& garageInfo)
		{
			// online maps, load and enable interior, enable props, refresh interior, teleport
			if (garageInfo.location != nullptr)
			{
				auto& loc = garageInfo.location->second->at(garageInfo.garageId);
				auto& pos = loc.pos;

				_ENABLE_MP_DLC_MAPS(true);
				_LOAD_MP_DLC_MAPS();
				for (auto& ipl : IplNames::vAllOfficeGarages1)
					REMOVE_IPL(ipl);
				REQUEST_IPL(loc.ipl);
				int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z); // Ambiguity?
				DISABLE_INTERIOR(interior, true);
				_LOAD_INTERIOR(interior);
				DISABLE_INTERIOR(interior, false);
				_ENABLE_MP_DLC_MAPS(false);
				WAIT(200);

				for (auto& ip : vFloorOptions)
					_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(ip.value));
				for (auto& ip : vDecorOptions)
					_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(ip.value));
				for (auto& ip : vLightingOptions)
					_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(ip.value));
				for (auto& ip : vNumStyleOptions)
				{
					for (UINT8 i = 1; i <= 3; i++)
						_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(((std::string)ip.value + "_N" + std::to_string(i)).c_str()));
				}
				_ENABLE_INTERIOR_PROP(interior, vFloorOptions[garageInfo.floorOption].value);
				_ENABLE_INTERIOR_PROP(interior, vDecorOptions[garageInfo.decorOption].value);
				_ENABLE_INTERIOR_PROP(interior, vLightingOptions[garageInfo.lightingOption].value);
				_ENABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(((std::string)vNumStyleOptions[garageInfo.numStyleOption].value + "_N" + std::to_string(garageInfo.garageId + 1)).c_str()));

				REFRESH_INTERIOR(interior);
			}
		}
		void TeleportPedToOfficeGarage(GTAentity ped, OfficeGarageInfoStructure& garageInfo)
		{
			if (garageInfo.location != nullptr)
			{
				teleport_net_ped(ped, garageInfo.location->second->at(garageInfo.garageId).pos);
			}
		}

		void Sub_OfficeGarages()
		{
			AddTitle("Office Garages");

			for (auto& loc : vLocations)
			{
				bool bGrpLocPressed = false;
				AddOption(loc.first, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_OFFICEGARAGES_INLOC); if (bGrpLocPressed)
				{
					currentGarageInfo.location = &loc;
					//currentGarageInfo.garageId = 0;
				}
			}
		}
		void Sub_OfficeGarages_InLoc()
		{
			if (currentGarageInfo.location == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			GTAped ped = Static_241;

			AddTitle(currentGarageInfo.location->first);

			bool bGarageId_plus = false, bGarageId_minus = false;
			AddTexter("Garage", 0, std::vector<std::string>{ vGarageIds[currentGarageInfo.garageId] }, null, bGarageId_plus, bGarageId_minus);
			if (bGarageId_plus) { if (currentGarageInfo.garageId < vGarageIds.size() - 1) { currentGarageInfo.garageId++; } }
			if (bGarageId_minus) { if (currentGarageInfo.garageId > 0) { currentGarageInfo.garageId--; } }

			if (currentGarageInfo.garageId == 3) //Autoshop
			{
				bool bFloorOption_plus = false, bFloorOption_minus = false;
				AddTexter("Floor", 0, std::vector<std::string>{ vFloorOptions[currentGarageInfo.floorOption].name }, null, bFloorOption_plus, bFloorOption_minus);
				if (bFloorOption_plus) { if (currentGarageInfo.floorOption < vFloorOptions.size() - 1) { currentGarageInfo.floorOption++; } }
				if (bFloorOption_minus) { if (currentGarageInfo.floorOption > 0) { currentGarageInfo.floorOption--; } }
			}
			else
			{
				bool bDecorOption_plus = false, bDecorOption_minus = false;
				AddTexter("Theme", 0, std::vector<std::string>{ vDecorOptions[currentGarageInfo.decorOption].name }, null, bDecorOption_plus, bDecorOption_minus);
				if (bDecorOption_plus) { if (currentGarageInfo.decorOption < vDecorOptions.size() - 1) { currentGarageInfo.decorOption++; } }
				if (bDecorOption_minus) { if (currentGarageInfo.decorOption > 0) { currentGarageInfo.decorOption--; } }

				bool bLightingOption_plus = false, bLightingOption_minus = false;
				AddTexter("Lighting", 0, std::vector<std::string>{ vLightingOptions[currentGarageInfo.lightingOption].name }, null, bLightingOption_plus, bLightingOption_minus);
				if (bLightingOption_plus) { if (currentGarageInfo.lightingOption < vLightingOptions.size() - 1) { currentGarageInfo.lightingOption++; } }
				if (bLightingOption_minus) { if (currentGarageInfo.lightingOption > 0) { currentGarageInfo.lightingOption--; } }

				bool bNumStyle_plus = false, bNumStyle_minus = false;
				AddTexter("Numbering Style", 0, std::vector<std::string>{ vNumStyleOptions[currentGarageInfo.numStyleOption].name }, null, bNumStyle_plus, bNumStyle_minus);
				if (bNumStyle_plus) { if (currentGarageInfo.numStyleOption < vNumStyleOptions.size() - 1) { currentGarageInfo.numStyleOption++; } }
				if (bNumStyle_minus) { if (currentGarageInfo.numStyleOption > 0) { currentGarageInfo.numStyleOption--; } }
			}

			bool bCreateOfficePressed = false;
			AddOption("Build Office Garage", bCreateOfficePressed); if (bCreateOfficePressed)
			{
				DO_SCREEN_FADE_OUT(50);
				CreateOfficeGarage(currentGarageInfo);
				TeleportPedToOfficeGarage(ped, currentGarageInfo);
				//Menu::SetSub_previous();
				DO_SCREEN_FADE_IN(200);
				return;
			}

		}
	}

}




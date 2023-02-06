/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "BikerInteriors.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAped.h"

#include "TeleMethods.h"

#include <string>
#include <vector>

namespace sub::TeleportLocations_catind
{
	namespace BikerInteriors
	{
		namespace Clubhouses
		{
			struct ClubhouseLocation { const std::string name; Vector3 pos; const std::string ipl; };
			const std::vector<ClubhouseLocation> vLocations
			{
				{ "1 floor",{ 1109.1124f, -3164.1536f, -37.5186f }, "bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo_" },
				{ "2 floors",{ 998.3676f, -3164.6531f, -38.9073f }, "bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo_" }
			};

			struct ClubhouseInteriorOption { const std::string name; const std::string value; };
			const std::vector<ClubhouseInteriorOption> vMuralOptions
			{
				{ "None", "Mural_00" },
				{ "1", "Mural_01" },
				{ "2", "Mural_02" },
				{ "3", "Mural_03" },
				{ "4", "Mural_04" },
				{ "5", "Mural_05" },
				{ "6", "Mural_06" },
				{ "7", "Mural_07" },
				{ "8", "Mural_08" },
				{ "9", "Mural_09" },
			};
			const std::vector<ClubhouseInteriorOption> vWallsOptions
			{
				{ "None", "Walls_00" },
				{ "1", "Walls_01" },
				{ "2", "Walls_02" },
			};
			const std::vector<ClubhouseInteriorOption> vDecorativeOptions
			{
				{ "None", "Decorative_00" },
				{ "1", "Decorative_01" },
				{ "2", "Decorative_02" },
			};
			const std::vector<ClubhouseInteriorOption> vFurnishingsOption
			{
				{ "None", "Furnishings_00" },
				{ "1", "Furnishings_01" },
				{ "2", "Furnishings_02" },
			};
			const std::vector<ClubhouseInteriorOption> vModBoothOptions
			{
				{ "None", "NO_MOD_BOOTH" },
				{ "Present", "Mod_Booth" },
			};
			const std::vector<ClubhouseInteriorOption> vGunLockerOptions
			{
				{ "None", "NO_Gun_Locker" },
				{ "Present", "Gun_Locker" },
			};

			struct ClubhouseInfoStructure
			{
				ClubhouseLocation const * location;
				UINT8 muralOption;
				UINT8 wallsOption;
				UINT8 decorativeOption;
				UINT8 furnishingsOption;
				UINT8 modBoothOption;
				UINT8 gunLockerOption;

				void operator = (const ClubhouseInfoStructure& right)
				{
					this->location = right.location;
					this->muralOption = right.muralOption;
					this->wallsOption = right.wallsOption;
					this->decorativeOption = right.decorativeOption;
					this->furnishingsOption = right.furnishingsOption;
					this->modBoothOption = right.modBoothOption;
					this->gunLockerOption = right.gunLockerOption;
				}
			};
			ClubhouseInfoStructure currentClubhouseInfo = { nullptr, 0, 0, 0, 0, 0, 0 };

			struct ClubhuseInteriorOptionArray {
				const std::string name; UINT8* ptr; const std::vector<ClubhouseInteriorOption>* arr;
			} vOptionArrays[]{
				{ "Murals", &currentClubhouseInfo.muralOption, &vMuralOptions },
				{ "Walls", &currentClubhouseInfo.wallsOption, &vWallsOptions },
				{ "Decoration", &currentClubhouseInfo.decorativeOption, &vDecorativeOptions },
				{ "Furnishing", &currentClubhouseInfo.furnishingsOption, &vFurnishingsOption },
				{ "Mod Booth", &currentClubhouseInfo.modBoothOption, &vModBoothOptions },
				{ "Gun Locker", &currentClubhouseInfo.gunLockerOption, &vGunLockerOptions },
			};

			void CreateClubhouse(ClubhouseInfoStructure& info)
			{
				// online maps, load and enable interior, enable props, refresh interior, teleport
				if (info.location != nullptr)
				{
					auto& loc = *info.location;
					auto& pos = loc.pos;

					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
					REQUEST_IPL(loc.ipl.c_str());
					int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
					DISABLE_INTERIOR(interior, true);
					PIN_INTERIOR_IN_MEMORY(interior);
					DISABLE_INTERIOR(interior, false);
					SET_INSTANCE_PRIORITY_MODE(false);
					WAIT(200);

					for (auto& oa : vOptionArrays)
					{
						for (auto& o : *oa.arr)
							DEACTIVATE_INTERIOR_ENTITY_SET(interior, o.value.c_str());
					}
					for (auto& oa : vOptionArrays)
					{
						ACTIVATE_INTERIOR_ENTITY_SET(interior, oa.arr->at(*oa.ptr).value.c_str());
					}
					REFRESH_INTERIOR(interior);
				}
			}
			void TeleportPedToClubhouse(GTAentity ped, ClubhouseInfoStructure& info)
			{
				if (info.location != nullptr)
				{
					teleport_net_ped(ped, info.location->pos);
				}
			}

			void Sub_Clubhouses()
			{
				AddTitle("Clubhouses");

				for (auto& loc : vLocations)
				{
					bool bGrpLocPressed = false;
					AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_BIKERCLUBHOUSES_INLOC); if (bGrpLocPressed)
					{
						currentClubhouseInfo.location = &loc;
					}
				}
			}
			void Sub_Clubhouses_InLoc()
			{
				if (currentClubhouseInfo.location == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				GTAped ped = Static_241;
				AddTitle(currentClubhouseInfo.location->name);

				for (auto& o : vOptionArrays)
				{
					bool bOption_plus = false, bOption_minus = false;
					AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(*o.ptr).name }, null, bOption_plus, bOption_minus);
					if (bOption_plus) { if (*o.ptr < o.arr->size() - 1) { (*o.ptr)++; } }
					if (bOption_minus) { if (*o.ptr  > 0) { (*o.ptr)--; } }
				}

				bool bCreateClubhousePressed = false;
				AddOption("Build Clubhouse", bCreateClubhousePressed); if (bCreateClubhousePressed)
				{
					DO_SCREEN_FADE_OUT(50);
					CreateClubhouse(currentClubhouseInfo);
					TeleportPedToClubhouse(ped, currentClubhouseInfo);
					//Menu::SetSub_previous();
					DO_SCREEN_FADE_IN(200);
					return;
				}
			}
		}

		namespace Businesses
		{
			struct BusinessLocation { const std::string name; Vector3 pos; const std::string ipl; std::vector<std::string> options; };
			const std::vector<BusinessLocation> vLocations
			{
				{ "Meth Lab",{ 1009.5000f, -3196.6000f, -38.5000f },"bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo_",{
					"meth_lab_basic",
					"meth_lab_upgrade",
					"meth_lab_security_high" } },

				{ "Weed Farm",{ 1049.6000f, -3196.6000f, -38.5000f },"bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo_",{
					"weed_standard_equip",
					"weed_upgrade_equip",
					"light_growtha_stage23_upgrade",
					"light_growthb_stage23_upgrade",
					"light_growthc_stage23_upgrade",
					"light_growthd_stage23_upgrade",
					"light_growthe_stage23_upgrade",
					"light_growthf_stage23_upgrade",
					"light_growthg_stage23_upgrade",
					"light_growthh_stage23_upgrade",
					"light_growthi_stage23_upgrade",
					"weed_low_security",
					"weed_security_upgrade" } },

				{ "Cocaine Warehouse",{ 1093.6000f, -3196.6000f, -38.5000f },"bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo_" ,{
					"equipment_basic",
					"production_basic",
					"equipment_upgrade",
					"table_equipment_upgrade",
					"coke_press_basic",
					"coke_press_upgrade",
					"coke_cut_04",
					"coke_cut_05",
					"security_low",
					"security_high",
				} },

				{ "Counterfeit Cash Factory",{ 1124.6000f, -3196.6000f, -38.5000f },"bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo_",{
					"counterfeit_standard_equip",
					"dryerc_on",
					"dryerd_on",
					"counterfeit_upgrade_equip",
					"counterfeit_low_security",
					"counterfeit_security" } },

				{ "Document Forgery Office",{ 1165.0000f, -3196.6000f, -38.2000f },"bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo_" ,{
					"interior_basic",
					"equipment_basic",
					"interior_upgrade"
					"equipment_upgrade",
					"clutter",
					"Chair05",
					"Chair04",
					"Chair07",
					"security_low",
					"security_high",
								} },
			};

			struct BusinessInfoStructure
			{
				BusinessLocation const * location;
				UINT8 option;

				void operator = (const BusinessInfoStructure& right)
				{
					this->location = right.location;
					this->option = right.option;
				}
			};
			BusinessInfoStructure currentBusinessInfo = { nullptr, 0 };

			void CreateBusiness(BusinessInfoStructure& info)
			{
				// online maps, load and enable interior, enable props, refresh interior, teleport
				if (info.location != nullptr)
				{
					auto& loc = *info.location;
					auto& pos = loc.pos;

					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
					REQUEST_IPL(loc.ipl.c_str());
					int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
					DISABLE_INTERIOR(interior, true);
					PIN_INTERIOR_IN_MEMORY(interior);
					DISABLE_INTERIOR(interior, false);
					SET_INSTANCE_PRIORITY_MODE(false);
					WAIT(200);

					for (auto& ip : loc.options)
					{
						DEACTIVATE_INTERIOR_ENTITY_SET(interior, ip.c_str());
					}
					if (info.option)
					{
						for (UINT8 o = 0; o < info.option; o++)
							ACTIVATE_INTERIOR_ENTITY_SET(interior, loc.options[o].c_str());
					}
					REFRESH_INTERIOR(interior);
				}
			}
			void TeleportPedToBusiness(GTAentity ped, BusinessInfoStructure& info)
			{
				if (info.location != nullptr)
				{
					teleport_net_ped(ped, info.location->pos);
				}
			}

			void Sub_Businesses()
			{
				AddTitle("Businesses");

				for (auto& loc : vLocations)
				{
					bool bGrpLocPressed = false;
					AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_BUSINESSES_INLOC); if (bGrpLocPressed)
					{
						currentBusinessInfo.location = &loc;
						currentBusinessInfo.option = 0;
					}
				}
			}
			void Sub_Businesses_InLoc()
			{
				if (currentBusinessInfo.location == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				GTAped ped = Static_241;
				AddTitle(currentBusinessInfo.location->name);

				bool bOption_plus = false, bOption_minus = false;
				AddTexter("Option", 0, std::vector<std::string>{ currentBusinessInfo.option == 0 ? "Empty" : currentBusinessInfo.location->options[currentBusinessInfo.option - 1] }, null, bOption_plus, bOption_minus);
				if (bOption_plus) { if (currentBusinessInfo.option < currentBusinessInfo.location->options.size()) { currentBusinessInfo.option++; } }
				if (bOption_minus) { if (currentBusinessInfo.option  > 0) { currentBusinessInfo.option--; } }

				bool bCreateBusinessPressed = false;
				AddOption("Build Business", bCreateBusinessPressed); if (bCreateBusinessPressed)
				{
					DO_SCREEN_FADE_OUT(50);
					CreateBusiness(currentBusinessInfo);
					TeleportPedToBusiness(ped, currentBusinessInfo);
					//Menu::SetSub_previous();
					DO_SCREEN_FADE_IN(200);
					return;
				}
			}
		}

	}

}




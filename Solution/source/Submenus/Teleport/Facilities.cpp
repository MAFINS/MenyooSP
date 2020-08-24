/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Facilities.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAped.h"

#include "TeleLocation.h"
#include "TeleMethods.h"

#include <Windows.h>
#include <string>
#include <vector>

namespace sub::TeleportLocations_catind
{
	namespace Facilities
	{
		const std::vector<TeleLocation> vOtherFacilityRelatedTeleports
		{
			TeleLocation("Facility 1 (IAA)", 2047.0000f, 2942.0000f, -62.9025f,{ "xm_x17dlc_int_placement_interior_4_x17dlc_int_facility_milo"_sv },{}, true),
			TeleLocation("Facility 2 (Datacentre)", 2168.0000f, 2920.8900f, -85.8000f,{ "xm_x17dlc_int_placement_interior_5_x17dlc_int_facility2_milo"_sv },{}, true),
			TeleLocation("Submarine", 513.0700f, 4839.6900f, -62.5900f,{ "xm_x17dlc_int_placement_interior_8_x17dlc_int_sub_milo_"_sv },{}, true),
			TeleLocation("Base", 567.1900f, 5954.8800f, -158.5500f,{ "xm_x17dlc_int_placement_interior_34_x17dlc_int_lab_milo_"_sv },{}, true, false, true),
			TeleLocation("Lab", 244.5700f, 6163.3900f, -159.4200f,{ "xm_x17dlc_int_placement_interior_34_x17dlc_int_lab_milo_"_sv },{}, true, false, true),
			TeleLocation("Silo", 368.4300f, 6307.8600f, -160.2500f,{ "xm_x17dlc_int_placement_interior_34_x17dlc_int_lab_milo_"_sv },{}, true, false, true),
			TeleLocation("Avenger", 520.0000f, 4750.0000f, -70.0000f,{ "xm_x17dlc_int_placement_interior_9_x17dlc_int_01_milo_"_sv },{},{ "shell_tint"_sv, "CONTROL_1"_sv, "CONTROL_2"_sv, "CONTROL_3"_sv, "WEAPONS_MOD"_sv, "VEHICLE_MOD"_sv, "GOLD_BLING"_sv }, true, false, true)
		};
		struct FacilityLocation { const PCHAR name; Vector3 pos; std::vector<std::string> ipls; };//std::string interior; };
		const std::vector<FacilityLocation> vLocations
		{
			{ "Regular",{ 462.0900f, 4820.4200f, -59.0000f },{ "xm_x17dlc_int_placement_interior_33_x17dlc_int_02_milo_" } },
		};

		const std::array<std::string, 10> vTintNames
		{ {
			{ "" },
			{ "Utility" },
			{ "Expertise" },
			{ "Altitude" },
			{ "Power" },
			{ "Authority" },
			{ "Influence" },
			{ "Order" },
			{ "Empire" },
			{ "Supremacy" }
			} };

		struct FacilityInteriorOption { const PCHAR name; const PCHAR value; UINT8 maxTints; };
		const std::vector<FacilityInteriorOption> vMainShellOptions
		{
			{ "Normal", "set_int_02_shell", 10 },
		};
		const std::vector<FacilityInteriorOption> vGraphicsOptions
		{
			{ "1","set_int_02_decal_01", 1 },
			{ "2","set_int_02_decal_02", 1 },
			{ "3","set_int_02_decal_03", 1 },
			{ "4","set_int_02_decal_04", 1 },
			{ "5","set_int_02_decal_05", 1 },
			{ "6","set_int_02_decal_06", 1 },
			{ "7","set_int_02_decal_07", 1 },
			{ "8","set_int_02_decal_08", 1 },
			{ "9","set_int_02_decal_09", 1 },
		};
		const std::vector<FacilityInteriorOption> vTrophyOptions
		{
			{ "None", "", 0 },
			{ "1", "set_int_02_trophy1", 10 },
			{ "IAA", "set_int_02_trophy_iaa", 10 },
			{ "SUB", "set_int_02_trophy_sub", 10 },
		};
		const std::vector<FacilityInteriorOption> vOrbitalCannonOptions
		{
			{ "Disabled","set_int_02_no_cannon", 0 },
			{ "Enabled","set_int_02_cannon", 1 },
		};
		const std::vector<FacilityInteriorOption> vSecurityRoomOptions
		{
			{ "Disabled","set_int_02_no_security", 0 },
			{ "Enabled","set_int_02_security", 1 },
		};
		const std::vector<FacilityInteriorOption> vLoungeOptions
		{
			{ "None","", 0 },
			{ "Utilty","set_int_02_lounge1", 1 },
			{ "Prestige","set_int_02_lounge2", 1 },
			{ "Premier","set_int_02_lounge3", 1 },
		};
		const std::vector<FacilityInteriorOption> vSleepingQuartersOptions
		{
			{ "None","set_int_02_no_sleep", 0 },
			{ "Utility","set_int_02_sleep", 1 },
			{ "Prestige","set_int_02_sleep2", 1 },
			{ "Premier","set_int_02_sleep3", 1 },
		};
		const std::vector<FacilityInteriorOption> vClutterOptions
		{
			{ "None","", 0 },
			{ "1","set_int_02_clutter1", 1 },
			{ "2","set_int_02_clutter2", 1 },
			{ "3","set_int_02_clutter3", 1 },
			{ "4","set_int_02_clutter4", 1 },
			{ "5","set_int_02_clutter5", 1 },
		};
		const std::vector<FacilityInteriorOption> vCrewEmblemOptions
		{
			{ "None","", 0 },
			{ "Player","set_int_02_crewemblem", 0 },
		};

		struct FacilityInfoStructure
		{
			FacilityLocation const * location;
			struct FacilityInteriorOptionIndex
			{
				UINT8 index;
				UINT8 currTint;

				FacilityInteriorOptionIndex(int indeX)
					: index(indeX), currTint(1U)
				{
				}
				FacilityInteriorOptionIndex()
					: index(0U), currTint(1U)
				{
				}

				void operator = (const FacilityInteriorOptionIndex& right)
				{
					this->index = right.index;
					this->currTint = right.currTint;
				}
			};
			FacilityInteriorOptionIndex mainShellOption;
			FacilityInteriorOptionIndex graphicsOption;
			FacilityInteriorOptionIndex trophyOption;
			FacilityInteriorOptionIndex orbitalCannonOption;
			FacilityInteriorOptionIndex securityRoomOption;
			FacilityInteriorOptionIndex loungeOption;
			FacilityInteriorOptionIndex sleepingQuartersOption;
			FacilityInteriorOptionIndex clutterOption;
			FacilityInteriorOptionIndex crewEmblemOption;

			void operator = (const FacilityInfoStructure& right)
			{
				this->location = right.location;
				this->mainShellOption = right.mainShellOption;
				this->graphicsOption = right.graphicsOption;
				this->trophyOption = right.trophyOption;
				this->orbitalCannonOption = right.orbitalCannonOption;
				this->securityRoomOption = right.securityRoomOption;
				this->loungeOption = right.loungeOption;
				this->sleepingQuartersOption = right.sleepingQuartersOption;
				this->clutterOption = right.clutterOption;
				this->crewEmblemOption = right.crewEmblemOption;
			}
		};
		FacilityInfoStructure currentFacilityInfo = { nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		struct FacilityInteriorOptionArray {
			const PCHAR name; FacilityInfoStructure::FacilityInteriorOptionIndex* ptr; const std::vector<FacilityInteriorOption>* arr;
		} const vOptionArrays[]{
			//{ NULL, NULL, &vDefaultOptions },
			{ "Main Shell", &currentFacilityInfo.mainShellOption, &vMainShellOptions },
			{ "Graphics", &currentFacilityInfo.graphicsOption, &vGraphicsOptions },
			{ "Trophy", &currentFacilityInfo.trophyOption, &vTrophyOptions },
			{ "Orbital Cannon", &currentFacilityInfo.orbitalCannonOption, &vOrbitalCannonOptions },
			{ "Security Room", &currentFacilityInfo.securityRoomOption, &vSecurityRoomOptions },
			{ "Lounge", &currentFacilityInfo.loungeOption, &vLoungeOptions },
			{ "Sleeping Quarters", &currentFacilityInfo.sleepingQuartersOption, &vSleepingQuartersOptions },
			{ "Clutter", &currentFacilityInfo.clutterOption, &vClutterOptions },
			{ "Crew Emblem", &currentFacilityInfo.crewEmblemOption, &vCrewEmblemOptions },
		};
		const FacilityInteriorOptionArray* selectedOptionArray = nullptr;

		void CreateFacility(FacilityInfoStructure& info)
		{
			// online maps, load and enable interior, enable props, refresh interior, teleport
			if (info.location != nullptr)
			{
				auto& loc = *info.location;
				auto& pos = loc.pos;

				_ENABLE_MP_DLC_MAPS(true);
				_LOAD_MP_DLC_MAPS();
				for (auto& ipl : loc.ipls)
					REQUEST_IPL(const_cast<PCHAR>(ipl.c_str()));
				//int interior = GET_INTERIOR_AT_COORDS_WITH_TYPE(pos.x, pos.y, pos.z, const_cast<PCHAR>(loc.interior.c_str()));
				int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
				DISABLE_INTERIOR(interior, true);
				_LOAD_INTERIOR(interior);
				DISABLE_INTERIOR(interior, false);
				_ENABLE_MP_DLC_MAPS(false);
				WAIT(200);

				for (auto& oa : vOptionArrays)
				{
					for (auto& o : *oa.arr)
						_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(o.value));
				}
				for (auto& oa : vOptionArrays)
				{
					if (oa.ptr == nullptr)
					{
						for (auto& o : *oa.arr)
						{
							_ENABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(o.value));
						}
					}
					else
					{
						auto& o = oa.arr->at(oa.ptr->index);
						_ENABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(o.value));
						if (o.maxTints > 0)
						{
							for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
							{
								if (_IS_INTERIOR_PROP_ENABLED(interior, const_cast<PCHAR>(o.value))) break;
								WAIT(0);
							}
							_0xC1F1920BAF281317(interior, const_cast<PCHAR>(o.value), oa.ptr->currTint);
						}
					}
				}
				REFRESH_INTERIOR(interior);
			}
		}
		void UpdateFacilityProp(FacilityInfoStructure& info, const FacilityInteriorOptionArray& arr)
		{
			if (info.location != nullptr)
			{
				auto& loc = *info.location;
				auto& pos = loc.pos;

				//int interior = GET_INTERIOR_AT_COORDS_WITH_TYPE(pos.x, pos.y, pos.z, const_cast<PCHAR>(loc.interior.c_str()));
				int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
				if (!IS_INTERIOR_DISABLED(interior))
				{
					for (auto& p : *arr.arr)
						_DISABLE_INTERIOR_PROP(interior, const_cast<PCHAR>(p.value));
					auto& p = arr.arr->at(arr.ptr->index);
					PCHAR propName = const_cast<PCHAR>(p.value);
					_ENABLE_INTERIOR_PROP(interior, propName);
					if (p.maxTints > 0)
					{
						for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
						{
							if (_IS_INTERIOR_PROP_ENABLED(interior, propName)) break;
							WAIT(0);
						}
						_0xC1F1920BAF281317(interior, propName, arr.ptr->currTint);
					}
					REFRESH_INTERIOR(interior);
				}
			}
		}
		void TeleportPedToFacility(GTAentity ped, FacilityInfoStructure& info)
		{
			if (info.location != nullptr)
			{
				teleport_net_ped(ped, info.location->pos);
			}
		}

		void Sub_Facilities()
		{
			AddTitle("Facilities");

			for (auto& otherTele : vOtherFacilityRelatedTeleports)
			{
				bool bOtherTelePressed = false;
				AddOption(otherTele.name, bOtherTelePressed); if (bOtherTelePressed)
				{
					TeleMethods::ToTeleLocation241(otherTele);
				}
			}

			AddBreak("---Build A Facility---");

			for (auto& loc : vLocations)
			{
				bool bGrpLocPressed = false;
				AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_FACILITIES_INLOC); if (bGrpLocPressed)
				{
					currentFacilityInfo.location = &loc;
				}
			}
		}
		void Sub_Facilities_InLoc()
		{
			if (currentFacilityInfo.location == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			GTAped ped = Static_241;
			AddTitle(currentFacilityInfo.location->name);

			for (auto& o : vOptionArrays)
			{
				if (o.name != nullptr && o.ptr != nullptr)
				{
					bool bOption_plus = false, bOption_minus = false, bOption_pressed = false;
					AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(o.ptr->index).name }, bOption_pressed, bOption_plus, bOption_minus);
					if (bOption_plus) { if (o.ptr->index < o.arr->size() - 1) { (o.ptr->index)++; UpdateFacilityProp(currentFacilityInfo, o); } }
					if (bOption_minus) { if (o.ptr->index > 0) { (o.ptr->index)--; UpdateFacilityProp(currentFacilityInfo, o); } }
					if (bOption_pressed)
					{
						selectedOptionArray = &o;
						Menu::SetSub_delayed = SUB::TELEPORTOPS_FACILITIES_INOPTION;
					}
				}
			}

			bool bCreateFacilityPressed = false;
			AddOption("Build Facility", bCreateFacilityPressed); if (bCreateFacilityPressed)
			{
				DO_SCREEN_FADE_OUT(50);
				CreateFacility(currentFacilityInfo);
				TeleportPedToFacility(ped, currentFacilityInfo);
				//Menu::SetSub_previous();
				DO_SCREEN_FADE_IN(200);
				return;
			}
		}
		void Sub_Facilities_InOption()
		{
			if (currentFacilityInfo.location == nullptr || selectedOptionArray == nullptr || selectedOptionArray->ptr == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			AddTitle(selectedOptionArray->name == nullptr ? "Option" : selectedOptionArray->name);

			for (UINT i = 0; i < selectedOptionArray->arr->size(); i++)
			{
				auto& o = selectedOptionArray->arr->at(i);
				auto& ptr = selectedOptionArray->ptr;
				bool isSelected = ptr->index == i;
				if (isSelected && o.maxTints > 1)
				{
					bool bTint_plus = false, bTint_minus = false;
					AddTexter(o.name, ptr->currTint, std::vector<std::string>(vTintNames.begin(), vTintNames.end()), null, bTint_plus, bTint_minus);
					if (bTint_plus) { if (ptr->currTint < o.maxTints) { ptr->currTint++; UpdateFacilityProp(currentFacilityInfo, *selectedOptionArray); } }
					if (bTint_minus) { if (ptr->currTint > 1) { ptr->currTint--; UpdateFacilityProp(currentFacilityInfo, *selectedOptionArray); } }
				}
				else
				{
					bool bOpPressed = false;
					AddTickol(o.name, isSelected, bOpPressed, bOpPressed); if (bOpPressed) {
						ptr->index = i;
						ptr->currTint = min(ptr->currTint, o.maxTints);
						UpdateFacilityProp(currentFacilityInfo, *selectedOptionArray);
					}
				}
			}
		}

	}

}




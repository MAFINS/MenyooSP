/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Hangars.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAped.h"

#include "TeleMethods.h"

#include <Windows.h> //GetTickCount
#include <string>
#include <vector>

namespace sub::TeleportLocations_catind
{
	namespace Hangars
	{
		struct HangarLocation { const PCHAR name; Vector3 pos; std::vector<std::string> ipls; std::string interior; };
		const std::vector<HangarLocation> vLocations
		{
			{ "Regular",{ -1253.6600f, -2998.8000f, -48.4900f },{ "sm_smugdlc_interior_placement", "sm_smugdlc_interior_placement_interior_0_smugdlc_int_01_milo_" }, "sm_smugdlc_int_01" },
		};

		struct HangarInteriorOption { const PCHAR name; const PCHAR value; UINT8 maxTints; };
		const std::vector<HangarInteriorOption> vDefaultOptions
		{
			{ NULL, "set_lighting_tint_props", 10 },
		};
		const std::vector<HangarInteriorOption> vMainShellOptions
		{
			{ "Normal", "set_tint_shell", 10 },
		};
		const std::vector<HangarInteriorOption> vBedroomOptions
		{
			{ "Disabled", "", 0 },
			{ "Enabled", "set_bedroom_tint", 10 },
		};
		const std::vector<HangarInteriorOption> vBedroomStyleOptions
		{
			{ "Empty", "", 0 },
			{ "Traditional", "set_bedroom_traditional", 0 },
			{ "Modern", "set_bedroom_modern", 0 },
		};
		const std::vector<HangarInteriorOption> vBedroomClutterOptions
		{
			{ "Disabled", "", 0 },
			{ "Enabled", "set_bedroom_clutter", 0 },
		};
		const std::vector<HangarInteriorOption> vBedroomBlindsOptions
		{
			{ "None", "", 0 },
			{ "Closed", "set_bedroom_blinds_closed", 0 },
			{ "Open", "set_bedroom_blinds_open", 0 },
		};
		const std::vector<HangarInteriorOption> vModAreaOptions
		{
			{ "Disabled", "", 0 },
			{ "Enabled", "set_modarea", 10 },
		};
		const std::vector<HangarInteriorOption> vCraneOptions
		{
			{ "Disabled", "", 0 },
			{ "Enabled", "set_crane_tint", 10 },
		};
		const std::vector<HangarInteriorOption> vOfficeOptions
		{
			{ "Basic", "set_office_basic", 0 },
			{ "Traditional", "set_office_traditional", 0 },
			{ "Modern", "set_office_modern", 0 },
		};
		const std::vector<HangarInteriorOption> vFloorOptions
		{
			{ "1", "set_floor_1", 0 },
			{ "2", "set_floor_2", 10 },
		};
		const std::vector<HangarInteriorOption> vFloorDecalOptions
		{
			{ "1", "set_floor_decal_1", 10 },
			{ "2", "set_floor_decal_2", 10 },
			{ "3", "set_floor_decal_3", 10 },
			{ "4", "set_floor_decal_4", 10 },
			{ "5", "set_floor_decal_5", 10 },
			{ "6", "set_floor_decal_6", 10 },
			{ "7", "set_floor_decal_7", 10 },
			{ "8", "set_floor_decal_8", 10 },
			{ "9", "set_floor_decal_9", 10 },
		};
		const std::vector<HangarInteriorOption> vHangarLightingOptions
		{
			{ "1", "set_lighting_hangar_a", 0 },
			{ "2", "set_lighting_hangar_b", 0 },
			{ "3", "set_lighting_hangar_c", 0 },
		};
		const std::vector<HangarInteriorOption> vWallLightingOptions
		{
			{ "Neutral", "set_lighting_wall_neutral", 0 },
			{ "Tint 1", "set_lighting_wall_tint01", 0 },
			{ "Tint 2", "set_lighting_wall_tint02", 0 },
			{ "Tint 3", "set_lighting_wall_tint03", 0 },
			{ "Tint 4", "set_lighting_wall_tint04", 0 },
			{ "Tint 5", "set_lighting_wall_tint05", 0 },
			{ "Tint 6", "set_lighting_wall_tint06", 0 },
			{ "Tint 7", "set_lighting_wall_tint07", 0 },
			{ "Tint 8", "set_lighting_wall_tint08", 0 },
			{ "Tint 9", "set_lighting_wall_tint09", 0 },
		};

		struct HangarInfoStructure
		{
			HangarLocation const * location;
			struct HangarInteriorOptionIndex
			{
				UINT8 index;
				UINT8 currTint;

				HangarInteriorOptionIndex(int indeX)
					: index(indeX), currTint(1U)
				{
				}
				HangarInteriorOptionIndex()
					: index(0U), currTint(1U)
				{
				}

				void operator = (const HangarInteriorOptionIndex& right)
				{
					this->index = right.index;
					this->currTint = right.currTint;
				}
			};
			HangarInteriorOptionIndex mainShellOption;
			HangarInteriorOptionIndex bedroomOption;
			HangarInteriorOptionIndex bedroomStyleOption;
			HangarInteriorOptionIndex bedroomClutterOption;
			HangarInteriorOptionIndex bedroomBlindsOption;
			HangarInteriorOptionIndex modAreaOption;
			HangarInteriorOptionIndex craneOption;
			HangarInteriorOptionIndex officeOption;
			HangarInteriorOptionIndex floorOption;
			HangarInteriorOptionIndex floorDecalOption;
			HangarInteriorOptionIndex hangarLightingOption;
			HangarInteriorOptionIndex wallLightingOption;

			void operator = (const HangarInfoStructure& right)
			{
				this->location = right.location;
				this->mainShellOption = right.mainShellOption;
				this->bedroomOption = right.bedroomOption;
				this->bedroomStyleOption = right.bedroomStyleOption;
				this->bedroomClutterOption = right.bedroomClutterOption;
				this->bedroomBlindsOption = right.bedroomBlindsOption;
				this->modAreaOption = right.modAreaOption;
				this->craneOption = right.craneOption;
				this->officeOption = right.officeOption;
				this->floorOption = right.floorOption;
				this->floorDecalOption = right.floorDecalOption;
				this->hangarLightingOption = right.hangarLightingOption;
				this->wallLightingOption = right.wallLightingOption;
			}
		};
		HangarInfoStructure currentHangarInfo = { nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		struct HangarInteriorOptionArray {
			const PCHAR name; HangarInfoStructure::HangarInteriorOptionIndex* ptr; const std::vector<HangarInteriorOption>* arr;
		} const vOptionArrays[]{
			{ NULL, NULL, &vDefaultOptions },
			{ "Main Shell", &currentHangarInfo.mainShellOption, &vMainShellOptions },
			{ "Bedroom", &currentHangarInfo.bedroomOption, &vBedroomOptions },
			{ "Bedroom Style", &currentHangarInfo.bedroomStyleOption, &vBedroomStyleOptions },
			{ "Bedroom Clutter", &currentHangarInfo.bedroomClutterOption, &vBedroomClutterOptions },
			{ "Bedroom Blinds", &currentHangarInfo.bedroomBlindsOption, &vBedroomBlindsOptions },
			{ "Auto Shop", &currentHangarInfo.modAreaOption, &vModAreaOptions },
			{ "Crane", &currentHangarInfo.craneOption, &vCraneOptions },
			{ "Office", &currentHangarInfo.officeOption, &vOfficeOptions },
			{ "Floor", &currentHangarInfo.floorOption, &vFloorOptions },
			{ "Floor Decoration", &currentHangarInfo.floorDecalOption, &vFloorDecalOptions },
			{ "Hangar Lighting", &currentHangarInfo.hangarLightingOption, &vHangarLightingOptions },
			{ "Wall Lighting", &currentHangarInfo.wallLightingOption, &vWallLightingOptions }
		};
		const HangarInteriorOptionArray* selectedOptionArray = nullptr;

		void CreateHangar(HangarInfoStructure& info)
		{
			// online maps, load and enable interior, enable props, refresh interior, teleport
			if (info.location != nullptr)
			{
				auto& loc = *info.location;
				auto& pos = loc.pos;

				SET_INSTANCE_PRIORITY_MODE(true);
				ON_ENTER_MP();
				for (auto& ipl : loc.ipls)
					REQUEST_IPL(const_cast<PCHAR>(ipl.c_str()));
				int interior = GET_INTERIOR_AT_COORDS_WITH_TYPE(pos.x, pos.y, pos.z, const_cast<PCHAR>(loc.interior.c_str()));
				DISABLE_INTERIOR(interior, true);
				PIN_INTERIOR_IN_MEMORY(interior);
				DISABLE_INTERIOR(interior, false);
				SET_INSTANCE_PRIORITY_MODE(false);
				WAIT(200);

				for (auto& oa : vOptionArrays)
				{
					for (auto& o : *oa.arr)
						DEACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(o.value));
				}
				for (auto& oa : vOptionArrays)
				{
					if (oa.ptr == nullptr)
					{
						for (auto& o : *oa.arr)
						{
							ACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(o.value));
						}
					}
					else
					{
						auto& o = oa.arr->at(oa.ptr->index);
						ACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(o.value));
						if (o.maxTints > 0)
						{
							for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
							{
								if (IS_INTERIOR_ENTITY_SET_ACTIVE(interior, const_cast<PCHAR>(o.value))) break;
								WAIT(0);
							}
							SET_INTERIOR_ENTITY_SET_TINT_INDEX(interior, const_cast<PCHAR>(o.value), oa.ptr->currTint);
						}
					}
				}
				REFRESH_INTERIOR(interior);
			}
		}
		void UpdateHangarProp(HangarInfoStructure& info, const HangarInteriorOptionArray& arr)
		{
			if (info.location != nullptr)
			{
				auto& loc = *info.location;
				auto& pos = loc.pos;

				int interior = GET_INTERIOR_AT_COORDS_WITH_TYPE(pos.x, pos.y, pos.z, const_cast<PCHAR>(loc.interior.c_str()));
				if (!IS_INTERIOR_DISABLED(interior))
				{
					for (auto& p : *arr.arr)
						DEACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(p.value));
					auto& p = arr.arr->at(arr.ptr->index);
					PCHAR propName = const_cast<PCHAR>(p.value);
					ACTIVATE_INTERIOR_ENTITY_SET(interior, propName);
					if (p.maxTints > 0)
					{
						for (DWORD timeOut = GetTickCount() + 250; GetTickCount() < timeOut;)
						{
							if (IS_INTERIOR_ENTITY_SET_ACTIVE(interior, propName)) break;
							WAIT(0);
						}
						SET_INTERIOR_ENTITY_SET_TINT_INDEX(interior, propName, arr.ptr->currTint);
					}
					REFRESH_INTERIOR(interior);
				}
			}
		}
		void TeleportPedToHangar(GTAentity ped, HangarInfoStructure& info)
		{
			if (info.location != nullptr)
			{
				teleport_net_ped(ped, info.location->pos);
			}
		}

		void Sub_Hangars()
		{
			AddTitle("Hangars");

			for (auto& loc : vLocations)
			{
				bool bGrpLocPressed = false;
				AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_HANGARS_INLOC); if (bGrpLocPressed)
				{
					currentHangarInfo.location = &loc;
				}
			}
		}
		void Sub_Hangars_InLoc()
		{
			if (currentHangarInfo.location == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			GTAped ped = local_ped_id;
			AddTitle(currentHangarInfo.location->name);

			for (auto& o : vOptionArrays)
			{
				if (o.name != nullptr && o.ptr != nullptr)
				{
					bool bOption_plus = false, bOption_minus = false, bOption_pressed = false;
					AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(o.ptr->index).name }, bOption_pressed, bOption_plus, bOption_minus);
					if (bOption_plus) { if (o.ptr->index < o.arr->size() - 1) { (o.ptr->index)++; UpdateHangarProp(currentHangarInfo, o); } }
					if (bOption_minus) { if (o.ptr->index > 0) { (o.ptr->index)--; UpdateHangarProp(currentHangarInfo, o); } }
					if (bOption_pressed)
					{
						selectedOptionArray = &o;
						Menu::SetSub_delayed = SUB::TELEPORTOPS_HANGARS_INOPTION;
					}
				}
			}

			bool bCreateHangarPressed = false;
			AddOption("Build Hangar", bCreateHangarPressed); if (bCreateHangarPressed)
			{
				DO_SCREEN_FADE_OUT(50);
				CreateHangar(currentHangarInfo);
				TeleportPedToHangar(ped, currentHangarInfo);
				//Menu::SetSub_previous();
				DO_SCREEN_FADE_IN(200);
				return;
			}
		}
		void Sub_Hangars_InOption()
		{
			if (currentHangarInfo.location == nullptr || selectedOptionArray == nullptr || selectedOptionArray->ptr == nullptr)
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
				if (isSelected && o.maxTints > 0)
				{
					bool bTint_plus = false, bTint_minus = false;
					AddNumber(o.name, ptr->currTint, 0, null, bTint_plus, bTint_minus);
					if (bTint_plus) { if (ptr->currTint < o.maxTints) { ptr->currTint++; UpdateHangarProp(currentHangarInfo, *selectedOptionArray); } }
					if (bTint_minus) { if (ptr->currTint > 1) { ptr->currTint--; UpdateHangarProp(currentHangarInfo, *selectedOptionArray); } }
				}
				else
				{
					bool bOpPressed = false;
					AddTickol(o.name, isSelected, bOpPressed, bOpPressed); if (bOpPressed) {
						ptr->index = i;
						ptr->currTint = min(ptr->currTint, o.maxTints);
						UpdateHangarProp(currentHangarInfo, *selectedOptionArray);
					}
				}
			}
		}
	}

}




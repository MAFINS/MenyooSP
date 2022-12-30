/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GunRunningInteriors.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAped.h"

#include "TeleMethods.h"

#include <vector>

namespace sub::TeleportLocations_catind
{
	namespace GunRunningInteriors
	{
		namespace Bunkers
		{
			struct BunkerLocation { const PCHAR name; Vector3 pos; const PCHAR ipl; };
			const std::vector<BunkerLocation> vLocations
			{
				{ "Regular",{ 938.3077f, -3196.1120f, -98.0000f }, "gr_grdlc_interior_placement_interior_1_grdlc_int_02_milo_" },
			};

			struct BunkerInteriorOption { const PCHAR name; const PCHAR value; };
			const std::vector<BunkerInteriorOption> vStyleOptions
			{
				{ "A", "bunker_style_a" },
				{ "B", "bunker_style_b" },
				{ "C", "bunker_style_c" },
			};
			const std::vector<BunkerInteriorOption> vSetOptions
			{
				{ "Standard", "standard_bunker_set" },
				{ "Upgraded", "upgrade_bunker_set" },
			};
			const std::vector<BunkerInteriorOption> vSecurityOptions
			{
				{ "Standard", "standard_security_set" },
				{ "Upgraded", "security_upgrade" },
			};
			const std::vector<BunkerInteriorOption> vOfficeOptions
			{
				{ "Blocked", "Office_blocker_set" },
				{ "Upgraded", "Office_Upgrade_set" },
			};
			const std::vector<BunkerInteriorOption> vGunRangeOptions
			{
				{ "Blcoked Section", "gun_range_blocker_set" },
				{ "Blocked Gun Range", "gun_wall_blocker" },
				{ "Present", "gun_range_lights" },
			};
			const std::vector<BunkerInteriorOption> vGunLockerOptions
			{
				{ "None", "" },
				{ "Present", "gun_locker_upgrade" },
			};
			const std::vector<BunkerInteriorOption> vGunSchematicOptions
			{
				{ "None", "" },
				{ "Present", "Gun_schematic_set" },
			};

			struct BunkerInfoStructure
			{
				BunkerLocation const * location;
				UINT8 styleOption;
				UINT8 setOption;
				UINT8 securityOption;
				UINT8 officeOption;
				UINT8 gunRangeOption;
				UINT8 gunLockerOption;
				UINT8 gunSchematicOption;

				void operator = (const BunkerInfoStructure& right)
				{
					this->location = right.location;
					this->styleOption = right.styleOption;
					this->setOption = right.setOption;
					this->securityOption = right.securityOption;
					this->officeOption = right.officeOption;
					this->gunRangeOption = right.gunRangeOption;
					this->gunLockerOption = right.gunLockerOption;
					this->gunSchematicOption = right.gunSchematicOption;
				}
			};
			BunkerInfoStructure currentBunkerInfo = { nullptr, 0, 0, 0, 0, 0, 0, 0 };

			struct BunkerInteriorOptionArray {
				const PCHAR name; UINT8* ptr; const std::vector<BunkerInteriorOption>* arr;
			} vOptionArrays[]{
				{ "Style", &currentBunkerInfo.styleOption, &vStyleOptions },
				{ "Set", &currentBunkerInfo.setOption, &vSetOptions },
				{ "Security", &currentBunkerInfo.securityOption, &vSecurityOptions },
				{ "Office", &currentBunkerInfo.officeOption, &vOfficeOptions },
				{ "Gun Range", &currentBunkerInfo.gunRangeOption, &vGunRangeOptions },
				{ "Gun Locker", &currentBunkerInfo.gunLockerOption, &vGunLockerOptions },
				{ "Gun Schematics", &currentBunkerInfo.gunSchematicOption, &vGunSchematicOptions },
			};

			void CreateBunker(BunkerInfoStructure& info)
			{
				// online maps, load and enable interior, enable props, refresh interior, teleport
				if (info.location != nullptr)
				{
					auto& loc = *info.location;
					auto& pos = loc.pos;

					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
					REQUEST_IPL(loc.ipl);
					int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
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
						ACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(oa.arr->at(*oa.ptr).value));
					}
					REFRESH_INTERIOR(interior);
				}
			}
			void TeleportPedToBunker(GTAentity ped, BunkerInfoStructure& info)
			{
				if (info.location != nullptr)
				{
					teleport_net_ped(ped, info.location->pos);
				}
			}

			void Sub_Bunkers()
			{
				AddTitle("Bunkers");

				for (auto& loc : vLocations)
				{
					bool bGrpLocPressed = false;
					AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_BUNKERS_INLOC); if (bGrpLocPressed)
					{
						currentBunkerInfo.location = &loc;
					}
				}
			}
			void Sub_Bunkers_InLoc()
			{
				if (currentBunkerInfo.location == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				GTAped ped = Static_241;
				AddTitle(currentBunkerInfo.location->name);

				for (auto& o : vOptionArrays)
				{
					bool bOption_plus = false, bOption_minus = false;
					AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(*o.ptr).name }, null, bOption_plus, bOption_minus);
					if (bOption_plus) { if (*o.ptr < o.arr->size() - 1) { (*o.ptr)++; } }
					if (bOption_minus) { if (*o.ptr > 0) { (*o.ptr)--; } }
				}

				bool bCreateBunkerPressed = false;
				AddOption("Build Bunker", bCreateBunkerPressed); if (bCreateBunkerPressed)
				{
					DO_SCREEN_FADE_OUT(50);
					CreateBunker(currentBunkerInfo);
					TeleportPedToBunker(ped, currentBunkerInfo);
					//Menu::SetSub_previous();
					DO_SCREEN_FADE_IN(200);
					return;
				}
			}
		}

		namespace Moc
		{
			struct MocLocation { const PCHAR name; Vector3 pos; const PCHAR ipl; };
			const std::vector<MocLocation> vLocations
			{
				{ "Regular",{ 1103.5620f, -3000.00000f, -38.0000f }, "gr_grdlc_interior_placement_interior_0_grdlc_int_01_milo_" },
			};

			struct MocInteriorOption { const PCHAR name; const PCHAR value; };
			const std::vector<MocInteriorOption> vStyleOptions
			{
				{ "", "" },
			};

			struct MocInfoStructure
			{
				MocLocation const * location;
				UINT8 styleOption;

				void operator = (const MocInfoStructure& right)
				{
					this->location = right.location;
					this->styleOption = right.styleOption;
				}
			};
			MocInfoStructure currentMocInfo = { nullptr, 0 };

			struct MocInteriorOptionArray {
				const PCHAR name; UINT8* ptr; const std::vector<MocInteriorOption>* arr;
			} vOptionArrays[]{
				{ "~italics~no options available yet", &currentMocInfo.styleOption, &vStyleOptions },
			};

			void CreateMoc(MocInfoStructure& info)
			{
				// online maps, load and enable interior, enable props, refresh interior, teleport
				if (info.location != nullptr)
				{
					auto& loc = *info.location;
					auto& pos = loc.pos;

					SET_INSTANCE_PRIORITY_MODE(true);
					ON_ENTER_MP();
					REQUEST_IPL(loc.ipl);
					int interior = GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z);
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
						ACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(oa.arr->at(*oa.ptr).value));
					}
					REFRESH_INTERIOR(interior);
				}
			}
			void TeleportPedToMoc(GTAentity ped, MocInfoStructure& info)
			{
				if (info.location != nullptr)
				{
					teleport_net_ped(ped, info.location->pos);
				}
			}

			void Sub_Moc()
			{
				AddTitle("MOCs");

				for (auto& loc : vLocations)
				{
					bool bGrpLocPressed = false;
					AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_MOC_INLOC); if (bGrpLocPressed)
					{
						currentMocInfo.location = &loc;
					}
				}
			}
			void Sub_Moc_InLoc()
			{
				if (currentMocInfo.location == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				GTAped ped = Static_241;
				AddTitle(currentMocInfo.location->name);

				for (auto& o : vOptionArrays)
				{
					bool bOption_plus = false, bOption_minus = false;
					AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(*o.ptr).name }, null, bOption_plus, bOption_minus);
					if (bOption_plus) { if (*o.ptr < o.arr->size() - 1) { (*o.ptr)++; } }
					if (bOption_minus) { if (*o.ptr > 0) { (*o.ptr)--; } }
				}

				bool bCreateBunkerPressed = false;
				AddOption("Build MOC", bCreateBunkerPressed); if (bCreateBunkerPressed)
				{
					DO_SCREEN_FADE_OUT(50);
					CreateMoc(currentMocInfo);
					TeleportPedToMoc(ped, currentMocInfo);
					//Menu::SetSub_previous();
					DO_SCREEN_FADE_IN(200);
					return;
				}
			}
		}

	}

}




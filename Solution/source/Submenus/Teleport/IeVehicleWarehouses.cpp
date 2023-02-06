/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "IeVehicleWarehouses.h"

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
	namespace IeVehicleWarehouses
	{
		struct IeWarehouseLocation { const std::string name; Vector3 pos; const std::string ipl; };
		const std::vector<IeWarehouseLocation> vLocations
		{
			{ "Warehouse",{ 973.5615f, -2999.5610f, -39.6470f }, "imp_impexp_interior_placement_interior_1_impexp_intwaremed_milo_" },
			{ "Vehicle Bunker",{ 1001.2706f, -2997.8494f, -47.6470f }, "imp_impexp_interior_placement_interior_3_impexp_int_02_milo_" }
		};

		struct IeWarehouseInteriorOption { const std::string name; const std::string value; };
		const std::vector<IeWarehouseInteriorOption> vStyleSetOptions
		{
			{ "None", "" },
			{ "Basic", "Basic_style_set" },
			{ "Urban", "Urban_style_set" },
			{ "Branded", "Branded_style_set" },
		};
		const std::vector<IeWarehouseInteriorOption> vPumpOptions
		{
			{ "None", "Pump_00" },
			{ "1", "Pump_01" },
			{ "2", "Pump_02" },
			{ "3", "Pump_03" },
			{ "4", "Pump_04" },
			{ "5", "Pump_05" },
			{ "6", "Pump_06" },
			{ "7", "Pump_07" },
			{ "8", "Pump_08" },
		};

		struct IeWarehouseInfoStructure
		{
			IeWarehouseLocation const * location;
			UINT8 styleSetOption;
			UINT8 pumpOption;

			void operator = (const IeWarehouseInfoStructure& right)
			{
				this->location = right.location;
				this->styleSetOption = right.styleSetOption;
				this->pumpOption = right.pumpOption;
			}
		};
		IeWarehouseInfoStructure currentWarehouseInfo = { nullptr, 0, 0 };

		struct IeWarehouseInteriorOptionArray {
			const std::string name; UINT8* ptr; const std::vector<IeWarehouseInteriorOption>* arr;
		} vOptionArrays[]{
			{ "Style", &currentWarehouseInfo.styleSetOption, &vStyleSetOptions },
			{ "Basement Pump", &currentWarehouseInfo.pumpOption, &vPumpOptions }
		};

		void CreateWarehouse(IeWarehouseInfoStructure& info)
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
		void TeleportPedToWarehouse(GTAentity ped, IeWarehouseInfoStructure& info)
		{
			if (info.location != nullptr)
			{
				teleport_net_ped(ped, info.location->pos);
			}
		}

		void Sub_IeVehicleWarehouses()
		{
			AddTitle("Vehicle Warehouses");

			for (auto& loc : vLocations)
			{
				bool bGrpLocPressed = false;
				AddOption(loc.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_IEVEHICLEWAREHOUSES_INLOC); if (bGrpLocPressed)
				{
					currentWarehouseInfo.location = &loc;
				}
			}
		}
		void Sub_IeVehicleWarehouses_InLoc()
		{
			if (currentWarehouseInfo.location == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			GTAped ped = Static_241;
			AddTitle(currentWarehouseInfo.location->name);

			for (auto& o : vOptionArrays)
			{
				bool bOption_plus = false, bOption_minus = false;
				AddTexter(o.name, 0, std::vector<std::string>{ o.arr->at(*o.ptr).name }, null, bOption_plus, bOption_minus);
				if (bOption_plus) { if (*o.ptr < o.arr->size() - 1) { (*o.ptr)++; } }
				if (bOption_minus) { if (*o.ptr > 0) { (*o.ptr)--; } }
			}

			bool bCreateWarehousePressed = false;
			AddOption("Build Warehouse", bCreateWarehousePressed); if (bCreateWarehousePressed)
			{
				DO_SCREEN_FADE_OUT(50);
				CreateWarehouse(currentWarehouseInfo);
				TeleportPedToWarehouse(ped, currentWarehouseInfo);
				//Menu::SetSub_previous();
				DO_SCREEN_FADE_IN(200);
				return;
			}
		}
	}

}




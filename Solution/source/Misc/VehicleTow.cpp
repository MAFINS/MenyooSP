/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleTow.h"

#include "..\macros.h"

#include "RopeGun.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\World.h"
#include "..\Menu\Menu.h"
#include "..\Scripting\enums.h"
#include "..\Util\keyboard.h"
#include "..\Scripting\CustomHelpText.h"
#include "..\Scripting\Game.h"

#include <vector>

namespace _VehicleTow_
{
	// Not using these as class members because I feel like it
	using _RopeGun_::EntitiesAndRope;
	std::vector<EntitiesAndRope> ropeArr;
	EntitiesAndRope currentPair;

	void VehicleTow::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		Game::Print::PrintBottomLeft("Park in front of a vehicle and instructions will appear.");
	}
	void VehicleTow::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		EndTows();
	}

	// run on tick
	void VehicleTow::Tick()
	{
		if (bEnabled)
		{
			Tick2();
			DoTowMaintainTick();
		}
	}
	inline void VehicleTow::Tick2()
	{
		GTAped myPed = PLAYER_PED_ID();

		if (myPed.IsInVehicle())
		{
			currentPair.e1 = myPed.CurrentVehicle();
			currentPair.e2 = NULL;
			for (auto& rav : ropeArr)
			{
				if (rav.e1.Handle() == currentPair.e1.Handle())
				{
					currentPair = rav;
				}
			}
			DoTowTick();
		}
	}
	inline void VehicleTow::DoTowTick()
	{
		GTAvehicle& vehBehindFirst = GetVehicleBehindFirst();

		if (vehBehindFirst.Handle() != NULL && vehBehindFirst.Handle() != currentPair.e2.Handle())
		{
			DisplayHelpText_Extend(vehBehindFirst);

			if (ExtendPressed())
			{
				ExtendTow(vehBehindFirst);
			}
		}

		else if (ShortenPressed())
		{
			ShortenTow();
		}
	}
	inline void VehicleTow::DoTowMaintainTick()
	{
		for (auto it = ropeArr.begin(); it != ropeArr.end();)
		{
			if (it->e1.Exists() && it->e2.Exists())
			{
				auto& last = it->e1;
				auto& newVeh = it->e2;
				last.RequestControlOnce();
				newVeh.RequestControlOnce();

				auto& initialDistance = it->initialDistance;
				ModelDimensions& last_md = last.ModelDimensions();
				ModelDimensions& newVeh_md = newVeh.ModelDimensions();

				Vector3 offset1(0, -last_md.Dim2.y, 0);
				Vector3 offset2(0, newVeh_md.Dim1.y, 0);
				Vector3& pos1 = last.GetOffsetInWorldCoords(offset1 / 2);
				Vector3& pos2 = newVeh.GetOffsetInWorldCoords(offset2 / 2);
				float currentDist = pos1.DistanceTo(pos2);

				if (currentDist > initialDistance) // -0.1f?
				{
					Vector3& forceDir = Vector3::Normalize(pos2 - pos1);
					newVeh.ApplyForce(-forceDir, ForceType::MaxForceRot2);
				}

				++it;
			}
			else
			{
				if (it->rope.Exists()) it->rope.Delete();
				it = ropeArr.erase(it);
			}
		}
	}

	// get vehicle behind first
	GTAvehicle VehicleTow::GetVehicleBehindFirst()
	{
		GTAentity& last = currentPair.e1;

		if (!last.Exists())
			return NULL;

		Vector3 newCoord;

		Vector3& oldCoord = last.GetOffsetInWorldCoords(0, -last.Dim2().y, 0);

		for (GTAentity newVeh : _nearbyVehicles)
		{
			if (newVeh.Handle() == last.Handle())
				continue;

			newCoord = newVeh.GetOffsetInWorldCoords(0, newVeh.Dim1().y, 0);
			if (oldCoord.DistanceTo(newCoord) < 0.86f)
			{
				return newVeh;
			}

		}

		return NULL;
	}

	void VehicleTow::ExtendTow(GTAvehicle& newVeh)
	{
		GTAentity& last = currentPair.e1;
		currentPair.e2 = newVeh;

		last.RequestControl(300);
		newVeh.RequestControl(600);

		ModelDimensions& last_md = last.ModelDimensions();
		ModelDimensions& newVeh_md = newVeh.ModelDimensions();

		Vector3 offset1(0, -last_md.Dim2.y / 2, 0);
		Vector3 offset2(0, newVeh_md.Dim1.y / 2, 0);
		Vector3& pos1 = last.GetOffsetInWorldCoords(offset1);
		Vector3& pos2 = newVeh.GetOffsetInWorldCoords(offset2);

		float dist = pos1.DistanceTo(pos2);
		currentPair.initialDistance = dist;

		Rope& newRope = Rope::AddRope(RopeType::Normal, pos1, Vector3(0, 0, 5.0f), dist, 0.0f, true);
		newRope.ActivatePhysics();
		currentPair.rope = newRope;
		//newRope.PinVertex(0, pos1);
		//newRope.PinVertex(newRope.VertexCount() - 1, pos2);

		newRope.AttachEntities(last, offset1, newVeh, offset2, dist + 0.2f);

		ropeArr.push_back(currentPair);
	}
	void VehicleTow::ShortenTow()
	{
		if (currentPair.rope.Exists()) currentPair.rope.Delete();
		for (auto it = ropeArr.begin(); it != ropeArr.end();)
		{
			if (it->rope.Handle() == currentPair.rope.Handle())
			{
				it = ropeArr.erase(it);
			}
			else ++it;
		}
	}
	void VehicleTow::EndTows()
	{
		for (auto& rav : ropeArr)
		{
			if (rav.rope.Exists()) rav.rope.Delete();
		}
		ropeArr.clear();
	}

	// controls
	bool VehicleTow::ExtendPressed()
	{
		return Menu::bit_controller ?
			IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LS) != 0
			: IsKeyJustUp(VirtualKey::K);
	}
	bool VehicleTow::ShortenPressed()
	{
		return Menu::bit_controller ?
			IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LS) != 0
			: get_key_pressed(VirtualKey::K);
	}

	// help text
	void VehicleTow::DisplayHelpText_Extend(GTAvehicle& vehBehind)
	{
		std::string vehBehindName = vehBehind.Model().VehicleDisplayName(true);

		Game::CustomHelpText::ShowTimedText(
			oss_ << "Press " << (Menu::bit_controller ? "~INPUT_FRONTEND_LS~" : "~b~K~s~") << " to tow the ~h~" << vehBehindName << "~h~ behind your current vehicle."
			, 100);
	}


	VehicleTow g_vehicleTow;

	void ToggleOnOff()
	{
		g_vehicleTow.Toggle();
	}

}



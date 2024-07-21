/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleOptions.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAprop.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\World.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GTAblip.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\Raycast.h"
#include "..\Scripting\DxHookIMG.h"
#include "..\Util\ExePath.h"

#include "..\Misc\VehicleCruise.h"
#include "..\Misc\VehicleTow.h"
#include "..\Misc\VehicleFly.h"

#include <math.h>
#include <string>
#include <vector>

namespace sub
{
	// Vehicle - ped task
	void task_rappel(GTAped ped, GTAvehicle vehicle)
	{
		if (vehicle.Model().IsHeli())
		{
			//if (vehicle.Speed_get() < 10.0f && vehicle.HeightAboveGround() < 40.0f)
			ped.RequestControl();
			ped.Task().ClearAll();
			ped.SetIntoVehicle(vehicle, VehicleSeat::SEAT_LEFTREAR);

			GTAped newPed;
			if (vehicle.IsSeatFree(VehicleSeat::SEAT_DRIVER))
			{
				newPed = World::CreatePedInsideVehicle(PedHash::PrologueDriver, vehicle, VehicleSeat::SEAT_DRIVER);
			}

			WAIT(100);

			if (newPed.Exists())
			{
				const Vector3& vehPos = vehicle.Position_get();
				newPed.BlockPermanentEvents_set(true);
				TASK_HELI_MISSION(newPed.Handle(), vehicle.Handle(), 0, 0, vehPos.x, vehPos.y, vehPos.z, 4, 0.0f, 50.0f, -1.0f, 10000, 100, -1082130432, 0);
				newPed.AlwaysKeepTask_set(true);
			}

			vehicle.Velocity_set(Vector3::Zero());

			ped.RequestControl();
			TASK_RAPPEL_FROM_HELI(ped.Handle(), 1); // 1092616192 0x41200000

			WAIT(100);
			if (newPed.Exists())
			{
				newPed.NoLongerNeeded(); // Too soon, maybe?
			}
		}
	}

	void VehicleOps()
	{
		bool set_ent_12 = 0,
			bToggleCargobobMagnet = 0,
			bToggleBoatAnchor = 0,
			goToSlamItSub = 0,
			obj_funny_veh_so_frz__off = 0,
			disableSiren_off = 0,
			VehicleOps_sub_modshop = 0,
			VehicleOps_sub_alphaLevel = 0,
			VehicleOpsRappelHeli = 0,
			VehicleOpsTeleportClosestCar_ = 0,
			VehicleOpsFixCar_ = 0,
			damageAndDefense_plus = 0, damageAndDefense_minus = 0, damageAndDefense_custom = 0,
			//VehicleOpsInvincibilityOn_ = 0,
			VehicleOpsInvincibilityOff_ = 0,
			VehicleOpsInvisible_ = 0,
			VehicleOpsSlippyTires_ = 0,
			VehicleOpsEngine_ = 0,
			VehicleOpsInteriorLight_ = 0,
			VehicleOpsMultiplyLights_ = 0,
			VehicleOpsBoostOn_ = 0,
			VehicleOpsSetOnFire_ = 0,
			VehicleOpsSuprKarModeOn_ = 0,
			VehicleOpsSuprKarModeOff_ = 0,
			carjump_plus = 0, carjump_minus = 0,
			VehicleOpsHydraulicsOn_ = 0,
			VehicleOpsDriveOnWaterOn_ = 0,
			VehicleOpsDriveOnWaterOff_ = 0,
			VehicleOpsChildLocksOn_ = 0, VehicleOpsChildLocksOff_ = 0,
			VehicleOpsDoorLocksOn_ = 0, VehicleOpsDoorLocksOff_ = 0,
			VehicleOpsNoGravityOn_ = 0,
			VehicleOpsNoGravityOff_ = 0,
			VehicleOpsSpeedoOn_ = 0,
			vcollisionon = 0,
			vcollisionoff = 0,
			VehicleOpsFreezeCarOn_ = 0,
			VehicleOpsFreezeCarOff_ = 0,
			VehicleOpsDeleteCar_ = 0,
			VehicleOps_Slam_On = 0,
			VehicleOpsHeavyMassOff_ = 0;

		Static_241 = PLAYER_PED_ID();
		Static_240 = PLAYER_ID();

		bool bAmIOnline = NETWORK_IS_IN_SESSION() != 0;
		GTAped myPed = Static_241;
		GTAplayer myPlayer = Static_240;
		GTAvehicle myVehicle = g_myVeh;
		bool bMyPedIsInVehicle = myPed.IsInVehicle();
		const Model& myVehicleModel = myVehicle.Model();

		static int __VechicleOpsFixCar_texterVal = 0;
		static std::vector<std::string> __VechicleOpsFixCar_texter{ "Full", "Keep Dirt", "Keep windows open", "Keep windows open with Dirt"};
		auto& fixCarTexterVal = __VechicleOpsFixCar_texterVal;
		auto& fixCarTexter = __VechicleOpsFixCar_texter;
		bool bFixCar_plus = false, bFixCar_minus = false;

		AddTitle("Vehicle Options");

		if (myVehicleModel.VehicleDisplayName(false).find("CARGOBOB") != std::string::npos)
			AddLocal("Cargobob Magnet", myVehicle.IsCargobobHookActive(CargobobHook::Magnet), bToggleCargobobMagnet, bToggleCargobobMagnet);
		if (myVehicleModel.hash == VEHICLE_MAVERICK || myVehicleModel.hash == VEHICLE_POLMAV)
			AddOption("Rappel From Helicopter", VehicleOpsRappelHeli);
		if (myVehicle.HasSiren_get())
			AddToggle("Disable Vehicle Siren", loop_vehicle_disableSiren, null, disableSiren_off);
		if (bMyPedIsInVehicle)
			AddTexter("CMOD_MOD_MNT", fixCarTexterVal, fixCarTexter, VehicleOpsFixCar_, bFixCar_plus, bFixCar_minus, true); // Fix & Wash
		if (myVehicleModel.IsBoat())
			AddLocal("Anchor Boat", myVehicle.IsBoatAnchored(), bToggleBoatAnchor, bToggleBoatAnchor);
		AddOption("Teleport Into Closest Vehicle", VehicleOpsTeleportClosestCar_);
		AddOption("Vehicle Spawner", obj_funny_veh_so_frz__off, nullFunc, SUB::SPAWNVEHICLE);
		AddOption("Menyoo Customs", VehicleOps_sub_modshop, nullFunc, -1, true);
		AddOption("Vehicle Weapons", null, nullFunc, SUB::VEHICLEWEAPONS);
		AddOption("Vehicle Multipliers", null, nullFunc, SUB::VEHICLEMULTIPLIERS);
		AddOption("Speedometers", null, nullFunc, SUB::VEHICLESPEEDOS);
		AddOption("Multi-Platform Neons", null, nullFunc, SUB::MULTIPLATNEONS);
		AddOption("PV Options", null, nullFunc, SUB::PVOPS);
		AddOption("Auto Drive", null, nullFunc, SUB::AUTODRIVESUB);
		AddOption((std::string)"Slam It (" + Game::GetGXTEntry("CMOD_MOD_22_D") + ")", goToSlamItSub, nullFunc, SUB::VEHICLESLAM);
		AddOption("Opacity (Local)", VehicleOps_sub_alphaLevel, nullFunc, -1, true);
		AddNumber("Damage & Defense", loop_vehicle_damageAndDefense, 2, damageAndDefense_custom, damageAndDefense_plus, damageAndDefense_minus);
		//AddLocal("Invincibility", VehicleOpsInvincibility_bit, VehicleOpsInvincibilityOn_, VehicleOpsInvincibilityOff_);
		AddToggle("Invincibility (Looped)", loop_vehicle_invincibility, null, VehicleOpsInvincibilityOff_);
		AddLocal("Invisibility", !myVehicle.IsVisible(), loop_vehicle_invisibility, VehicleOpsInvisible_);
		AddToggle("Auto-Repair", loop_vehicle_fixloop);
		AddToggle("Auto-Flip", loop_vehicle_fliploop);
		AddToggle("Keep Engine & Lights On", loop_self_engineOn);
		AddTickol("Kill Engine", (GET_VEHICLE_ENGINE_HEALTH(g_myVeh) < 0.0f), VehicleOpsEngine_, VehicleOpsEngine_, TICKOL::PERCENTAGESTICKER, TICKOL::NONE);
		AddToggle("Rainbow Mode", loop_car_colour_change);
		AddLocal("Slidy Tyres", VehicleOpsSlippyTires_bit, VehicleOpsSlippyTires_, VehicleOpsSlippyTires_);
		AddLocal("Cruise Control", _VehicleCruise_::g_vehicleCruise.Enabled(), _VehicleCruise_::ToggleOnOff, _VehicleCruise_::ToggleOnOff);
		AddLocal("Tow Mode (ALPHA)", _VehicleTow_::g_vehicleTow.Enabled(), _VehicleTow_::ToggleOnOff, _VehicleTow_::ToggleOnOff);
		AddToggle("Race Boost On Horn", loop_race_boost, VehicleOpsBoostOn_);
		AddToggle("Infinite Native Boost (for e.g. Oppressor)", loop_unlimVehBoost);
		AddToggle("SuprKar Mode", loop_SuprKarMode, VehicleOpsSuprKarModeOn_, VehicleOpsSuprKarModeOff_);
		AddLocal("Fly Mode", _VehicleFly_::g_vehicleFly.Enabled(), _VehicleFly_::ToggleOnOff, _VehicleFly_::ToggleOnOff);
		AddToggle("Glue to Ground", loop_super_grip);
		AddTexter("Vehicle Jump", loop_car_jump, Menu::bit_controller ? std::vector<std::string>{"Off", "Tap/Press A/X", "Hold A/X"} : std::vector<std::string>{ "Off", "Tap/Press Space", "Hold Space" }, null, carjump_plus, carjump_minus);
		AddToggle("Hydraulics", loop_car_hydraulics, VehicleOpsHydraulicsOn_);
		AddToggle("Drive On Water", loop_drive_on_water, VehicleOpsDriveOnWaterOn_, VehicleOpsDriveOnWaterOff_);
		AddToggle("Increased Mass", loop_vehicle_heavymass, null, VehicleOpsHeavyMassOff_);
		AddTickol("Child Locks", (GET_VEHICLE_DOOR_LOCK_STATUS(g_myVeh) == 4), VehicleOpsChildLocksOn_, VehicleOpsChildLocksOff_, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		AddTickol("Door Locks", (GET_VEHICLE_DOOR_LOCK_STATUS(g_myVeh) == 2), VehicleOpsDoorLocksOn_, VehicleOpsDoorLocksOff_, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		AddLocal("No Gravity", bit_vehicle_gravity, VehicleOpsNoGravityOn_, VehicleOpsNoGravityOff_);
		AddLocal("Freeze Vehicle", bit_freeze_vehicle, VehicleOpsFreezeCarOn_, VehicleOpsFreezeCarOff_);
		AddLocal("Set on Fire", myVehicle.IsOnFire(), VehicleOpsSetOnFire_, VehicleOpsSetOnFire_);
		AddLocal("Collision", myVehicle.IsCollisionEnabled_get(), vcollisionon, vcollisionoff);
		//AddOption("Collision ON", vcollisionon);
		//AddOption("Collision OFF", vcollisionoff);
		AddOption("Delete Vehicle", VehicleOpsDeleteCar_);

		/*bool inputWeight = false;
		AddOption("Input Mass Multiplier (TEST)", inputWeight); if (inputWeight)
		{
		std::string wei = Game::InputBox("", 9);
		if (wei.length() > 0) myVehicle.SetMass(stof(wei));
		ACTIVATE_PHYSICS(myVehicle.Handle());
		}*/

		//if (obj_funny_veh_so_frz__off) bit_obj_funny_veh_so_frz = false;

		if (bToggleCargobobMagnet) {
			if (myVehicle.IsCargobobHookActive(CargobobHook::Magnet))
			{
				myVehicle.RequestControl();
				myVehicle.RetractCargobobHook();
				WAIT(50);
				myVehicle.DropCargobobHook(CargobobHook::Hook);
			}
			else
			{
				myVehicle.RequestControl();
				myVehicle.DropCargobobHook(CargobobHook::Magnet);
				myVehicle.CargoBobMagnetGrabVehicle();
			}
		}

		if (bToggleBoatAnchor)
		{
				myVehicle.AnchorBoat(!myVehicle.IsBoatAnchored());
		}
		
		if (disableSiren_off) SET_VEHICLE_HAS_MUTED_SIRENS(g_myVeh, FALSE);

		if (VehicleOps_Slam_On) { Game::Print::PrintBottomCentre("~b~Note:~s~ If you try hard enough, you can drive on walls too!"); return; }

		if (vcollisionon || vcollisionoff) myVehicle.IsCollisionEnabled_set(!myVehicle.IsCollisionEnabled_get());
		//if (vcollisionon) SET_ENTITY_COLLISION(g_myVeh, TRUE, 0);
		//if (vcollisionoff) SET_ENTITY_COLLISION(g_myVeh, FALSE, 0);

		if (set_ent_12) Static_12 = g_myVeh;
		if (goToSlamItSub) sub::VehicleSlam_catind::InitSub(g_myVeh, &loop_vehicle_slam);

		if (VehicleOps_sub_modshop) {
			if (DOES_ENTITY_EXIST(g_myVeh)) { Static_12 = g_myVeh; Menu::SetSub_new(SUB::MODSHOP); }
			else Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			return;
		}
		if (VehicleOps_sub_alphaLevel) {
			if (DOES_ENTITY_EXIST(g_myVeh)) { Static_12 = g_myVeh; Menu::SetSub_new(SUB::ENTITYALPHALEVEL); }
			else Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			return;
		}

		if (VehicleOpsRappelHeli) {
			if (myPed.IsInVehicle())
			{
				if (!myPed.IsInHeli()) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a helicopter.");
				else
					task_rappel(myPed.Handle(), myPed.CurrentVehicle());
				return;
			}
		}

		if (VehicleOpsTeleportClosestCar_) {
			/*Vector3 myPos = GET_ENTITY_COORDS(Static_241, 1);
			int CarType = 64;
			CarType |= 2710;
			CarType |= 2048;
			CarType |= 1;
			CarType |= 2;
			CarType |= 4;
			CarType |= 32;
			CarType |= 16;
			CarType |= 8;
			int tempVehicle = GET_CLOSEST_VEHICLE(myPos.x, myPos.y, myPos.z, 400.0f, 0, CarType);
			if (DOES_ENTITY_EXIST(tempVehicle)) SET_PED_INTO_VEHICLE(Static_241, tempVehicle, tempVehicle.FirstFreeSeat(SEAT_DRIVER));*/
			const GTAvehicle& tempVehicle = World::GetClosestVehicle(myPed.Position_get(), FLT_MAX);
			if (tempVehicle.Exists())
				myPed.SetIntoVehicle(tempVehicle, tempVehicle.FirstFreeSeat(SEAT_DRIVER));
			return;
		}

		if (bFixCar_plus && fixCarTexterVal < fixCarTexter.size() - 1)
			fixCarTexterVal++;
		else if (bFixCar_minus && fixCarTexterVal > 0)
			fixCarTexterVal--;
		if (VehicleOpsFixCar_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				std::vector<VehicleWindow> windowsToOpen;
				if (fixCarTexterVal == 1 || fixCarTexterVal == 3)
				{
					for (int i = (int)VehicleWindow::FrontLeftWindow; i < (int)VehicleWindow::Last; i++)
					{
						if (!myVehicle.IsWindowIntact((VehicleWindow)i))
							windowsToOpen.push_back((VehicleWindow)i);
					}
				}


				myVehicle.RequestControlOnce();
				SET_VEHICLE_FIXED(g_myVeh);
				if(fixCarTexterVal == 0 || fixCarTexterVal == 2)
					SET_VEHICLE_DIRT_LEVEL(g_myVeh, 0.0f);
				SET_VEHICLE_ENGINE_CAN_DEGRADE(g_myVeh, 0);
				SET_VEHICLE_ENGINE_HEALTH(g_myVeh, 1250.0f);
				SET_VEHICLE_PETROL_TANK_HEALTH(g_myVeh, 1250.0f);
				SET_VEHICLE_BODY_HEALTH(g_myVeh, 1250.0f);
				SET_VEHICLE_UNDRIVEABLE(g_myVeh, 0);
				if (!GET_IS_VEHICLE_ENGINE_RUNNING(g_myVeh))
					SET_VEHICLE_ENGINE_ON(g_myVeh, 1, 1, 0);

				if (fixCarTexterVal == 1 || fixCarTexterVal == 3)
				{
					for (auto& i : windowsToOpen)
					{
						myVehicle.RollDownWindow(i);
					}
				}
			}
			return;
		}

		if (damageAndDefense_plus) {
			loop_vehicle_damageAndDefense += 0.2f;
			SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
			SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
			return;
		}
		if (damageAndDefense_minus) {
			loop_vehicle_damageAndDefense -= 0.2f;
			SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
			SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
			return;
		}
		if (damageAndDefense_custom) {
			std::string inputStr = Game::InputBox("", 10U);
			if (inputStr.length() > 0)
			{
				float oldVal = loop_vehicle_damageAndDefense;
				bool noexc = true;
				try { loop_vehicle_damageAndDefense = stof(inputStr); }
				catch (...) { noexc = false; loop_vehicle_damageAndDefense = oldVal; }
				if (noexc)
				{
					SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
					SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
				}
			}
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::MyVehicleDamageAndDefense, std::string(), 9U);
		}

		/*if (VehicleOpsInvincibilityOn_){
		if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
		else
		{
		RequestControlOfEnt(g_myVeh);
		set_vehicle_invincible_on(g_myVeh);
		VehicleOpsInvincibility_bit = true;
		}
		return;
		}*/
		if (VehicleOpsInvincibilityOff_) {
			if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
			{
				myVehicle.RequestControlOnce();
				set_vehicle_invincible_off(g_myVeh);
				//VehicleOpsInvincibility_bit = false;
			}
			return;
		}

		if (VehicleOpsInvisible_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				//if (IS_ENTITY_VISIBLE(g_myVeh))
				//{
				//	RequestControlOfEnt(g_myVeh);
				//	SET_ENTITY_VISIBLE(g_myVeh, 0);
				//	SET_ENTITY_VISIBLE(PLAYER_PED_ID(), 1);
				//}
				//else
				//{
				myVehicle.RequestControlOnce();
				myVehicle.SetVisible(true);
				//}
			}
			return;
		}

		if (VehicleOpsSlippyTires_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				VehicleOpsSlippyTires_bit = !VehicleOpsSlippyTires_bit;
				myVehicle.RequestControlOnce();
				SET_VEHICLE_REDUCE_GRIP(g_myVeh, VehicleOpsSlippyTires_bit);
			}
			return;
		}

		if (VehicleOpsEngine_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				if (GET_VEHICLE_ENGINE_HEALTH(g_myVeh) > 0.0f)
				{
					myVehicle.RequestControlOnce();
					SET_VEHICLE_ENGINE_HEALTH(g_myVeh, -1.0f);
					SET_VEHICLE_UNDRIVEABLE(g_myVeh, 1);
					Game::Print::PrintBottomCentre("Engine Killed");
				}
				else
				{
					myVehicle.RequestControlOnce();
					SET_VEHICLE_ENGINE_HEALTH(g_myVeh, 1250.0f);
					SET_VEHICLE_UNDRIVEABLE(g_myVeh, 0);
					Game::Print::PrintBottomCentre("Engine Revived");
				}
			}
			return;
		}

		if (VehicleOpsBoostOn_) {
			Game::Print::PrintBottomLeft("Use the horn for a boost.");
			return;
		}

		if (VehicleOpsSuprKarModeOn_) {
			Game::Print::PrintBottomLeft("Use driving controls and handbrake.");
			return;
		}
		if (VehicleOpsSuprKarModeOff_) {
			SET_VEHICLE_BOOST_ACTIVE(g_myVeh, 0);
			return;
		}

		if (carjump_plus) { if (loop_car_jump < 2) loop_car_jump++; return; }
		if (carjump_minus) { if (loop_car_jump > 0) loop_car_jump--; return; }

		if (VehicleOpsHydraulicsOn_) {
			Game::Print::PrintBottomLeft(oss_ "Use ~b~" << (Menu::bit_controller ? "LS/L1 + stick movement" : "LeftShift + WASD") << "~s~ for hydraulics.");
			return;
		}

		if (VehicleOpsDriveOnWaterOn_) {
			Game::Print::PrintBottomLeft("You can drive and walk on water now!");
			return;
		}
		if (VehicleOpsDriveOnWaterOff_) {
			//SET_OBJECT_AS_NO_LONGER_NEEDED(&drive_water_obj); WAIT(100);
			GTAprop(g_drive_water_obj).Delete(true);
			return;
		}

		if (VehicleOpsChildLocksOn_) {
			myVehicle.RequestControlOnce();
			SET_VEHICLE_DOORS_LOCKED(g_myVeh, 4);
			return;
		}
		if (VehicleOpsChildLocksOff_) {
			myVehicle.RequestControlOnce();
			SET_VEHICLE_DOORS_LOCKED(g_myVeh, 0);
			return;
		}
		if (VehicleOpsDoorLocksOn_) {
			myVehicle.RequestControlOnce();
			SET_VEHICLE_DOORS_LOCKED(g_myVeh, 2);
			return;
		}
		if (VehicleOpsDoorLocksOff_) {
			myVehicle.RequestControlOnce();
			SET_VEHICLE_DOORS_LOCKED(g_myVeh, 0);
			return;
		}

		if (VehicleOpsNoGravityOn_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				myVehicle.RequestControlOnce();
				SET_VEHICLE_GRAVITY(g_myVeh, 0);
				bit_vehicle_gravity = true;
				Game::Print::PrintBottomCentre("Vehicle Gravity ~g~Disabled");
			}
			return;
		}
		if (VehicleOpsNoGravityOff_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				myVehicle.RequestControlOnce();
				SET_VEHICLE_GRAVITY(g_myVeh, 1);
				bit_vehicle_gravity = false;
				Game::Print::PrintBottomCentre("Vehicle Gravity ~r~Enabled");
			}
			return;
		}

		if (VehicleOpsFreezeCarOn_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				bit_freeze_vehicle = true;
				myVehicle.RequestControlOnce();
				SET_VEHICLE_FORWARD_SPEED(g_myVeh, 0.0f);
				FREEZE_ENTITY_POSITION(g_myVeh, 1);
				Game::Print::PrintBottomCentre("Vehicle Freeze ~g~On");
			}
			return;
		}
		if (VehicleOpsFreezeCarOff_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				bit_freeze_vehicle = false;
				myVehicle.RequestControlOnce();
				SET_VEHICLE_FORWARD_SPEED(g_myVeh, 8.0f);
				FREEZE_ENTITY_POSITION(g_myVeh, 0);
				Game::Print::PrintBottomCentre("Vehicle Freeze ~r~Off");
			}
			return;
		}

		if (VehicleOpsSetOnFire_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				if (!myVehicle.IsOnFire())
				{
					myVehicle.RequestControl(200);
					myVehicle.SetProofs(true, false, true, false, false, false, false, true);
					myVehicle.SetFireProof(false);
					WAIT(40);
					myVehicle.SetOnFire(true);
				}
				else
				{
					myVehicle.RequestControl(200);
					myVehicle.SetProofs(true, true, true, false, false, false, false, true);
					myVehicle.SetFireProof(true);
					WAIT(40);
					myVehicle.SetOnFire(false);
				}
			}
			return;
		}

		if (VehicleOpsDeleteCar_) {
			if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				myVehicle.Delete(false);
				Game::Print::PrintBottomCentre("Poof!");
				*Menu::currentopATM = 1;
			}
			return;
		}


		if (VehicleOpsHeavyMassOff_) {
			if (myVehicle.Exists())
			{
				set_vehicle_invincible_off(myVehicle.GetHandle());
				myVehicle.SetFrictionOverride(1.0f);
			}
			return;
		}


	}

	void PVOpsSub_()
	{
		bool PVOpsSub_Save = 0,
			PVOps_TeleportIntoIt = 0,
			PVOpsSub_TeleportToIt = 0,
			PVOpsSub_TeleportItToYou = 0,
			PVOpsSub_Unsave = 0;

		GTAped myPed = PLAYER_PED_ID();
		GTAvehicle myVehicle = g_myVeh;
		GTAvehicle& pv = PV_sub_vehicleid;

		AddTitle("PV Options");
		AddTickol("Remember Vehicle", pv == myVehicle, PVOpsSub_Save, PVOpsSub_Unsave);
		AddOption("Teleport Into Seat", PVOps_TeleportIntoIt);
		AddOption("Teleport to Vehicle", PVOpsSub_TeleportToIt);
		AddOption("Teleport Vehicle to Self", PVOpsSub_TeleportItToYou);

		if (PVOpsSub_Unsave) {
			pv.MissionEntity_set(false);
			GTAblip blip = pv.CurrentBlip();
			if (blip.Exists())
			{
				if (blip.Colour() == 61)
					blip.Remove();
			}
			pv = 0;
			return;
		}

		if (PVOpsSub_Save) {
			if (!myPed.IsInVehicle()) Game::Print::PrintBottomCentre("~r~Error:~s~ You are not in a vehicle.");
			else
			{
				pv = myVehicle;

				pv.MissionEntity_set(true);

				GTAblip blip = pv.CurrentBlip();
				if (!blip.Exists())
				{
					blip = pv.AddBlip();
					if (blip.Exists())
					{
						Model model = pv.Model();
						BlipIcon::BlipIcon sprite = BlipIcon::PersonalVehicleCar;

						if (model.IsHeli())
							sprite = BlipIcon::EnemyHelicopter;
						else if (model.IsPlane())
							sprite = BlipIcon::Plane;
						else if (model.IsBoat())
							sprite = BlipIcon::Boat;
						else if (model.IsBike())
							sprite = BlipIcon::PersonalVehicleBike;
						else if (model.hash == VEHICLE_RHINO)
							sprite = BlipIcon::Tank; // Rhino

						blip.SetIcon(sprite);
						blip.SetScale(0.7f);
						blip.SetColour(BlipColour::Pink);
						blip.SetFriendly(true);
					}
				}
			}
			return;
		}

		if (PVOps_TeleportIntoIt) {
			if (!pv.Exists()) Game::Print::PrintBottomCentre("~r~Error:~s~ No longer in memory.");
			else
			{
				myPed.SetIntoVehicle(pv, pv.FirstFreeSeat(SEAT_DRIVER));
			}
			return;
		}

		if (PVOpsSub_TeleportToIt)
		{
			if (!pv.Exists()) Game::Print::PrintBottomCentre("~r~Error:~s~ No longer in memory.");
			else
			{
				if (myPed.IsInVehicle())
				{
					myVehicle.Position_set(pv.GetOffsetInWorldCoords(0, pv.Dim1().y + myVehicle.Dim2().y + 0.3f, 0));
				}
				else
				{
					myPed.Position_set(pv.GetOffsetInWorldCoords(0, 0, pv.Dim2().z + myPed.Dim1().z));
				}
			}
			return;
		}

		if (PVOpsSub_TeleportItToYou) {
			if (!pv.Exists()) Game::Print::PrintBottomCentre("~r~Error:~s~ No longer in memory.");
			else
			{
				const Vector3& myPos = myPed.Position_get();
				pv.RequestControl(600);
				pv.Position_set(myPos);
			}
			return;
		}

	}

	namespace VehicleAutoDrive_catind
	{
		class MethodsClass final : public GenericLoopedMode
		{
		private:
			GTAped myPed;
			GTAvehicle vehicle;
			Model vehicleModel;
			Vector3 destination;
		public:
			float speed = 20;
			int drivingStyle = 5;
			UINT8 drivingStyleIndex = 0;
			bool bPushEmAway = true;
			bool initialSet = false;

			void TurnOn() override
			{
				GenericLoopedMode::TurnOn();

				initialSet = false;
			}
			void TurnOff() override
			{
				GenericLoopedMode::TurnOff();

				initialSet = false;

				//Vector3& vehPos = vehicle.Position_get();

				/*ScrHandle tsk;
				OPEN_SEQUENCE_TASK(&tsk);

				TASK_LEAVE_ANY_VEHICLE(0, 0, 0);

				CLOSE_SEQUENCE_TASK(tsk);
				TASK_PERFORM_SEQUENCE(myPed.Handle(), tsk);

				if (GET_SEQUENCE_PROGRESS(myPed.Handle()) >= 1)
				CLEAR_PED_TASKS(myPed.Handle());

				CLEAR_SEQUENCE_TASK(&tsk);*/

				CLEAR_PED_TASKS(myPed.Handle());

				//TASK_VEHICLE_PARK(myPed.Handle(), vehicle.Handle(), vehPos.x, vehPos.y, vehPos.z, vehicle.Heading_get(), 1, 1.0f, true);
				//SET_PED_KEEP_TASK(myPed.Handle(), false);
				
			}

			void Tick() override
			{
				if (bEnabled)
				{
					MainTick();
				}
			}
			inline void MainTick()
			{
				myPed = PLAYER_PED_ID();

				if (myPed.IsInVehicle() && IS_WAYPOINT_ACTIVE())
				{
					if (!initialSet)
						destination = GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint));

					vehicle = myPed.CurrentVehicle();
					vehicleModel = vehicle.Model();

					if (vehicleModel.IsHeli())
					{
						HeliTick();
					}
					else if (vehicleModel.IsPlane())
					{
						PlaneTick();
					}
					else if (vehicleModel.IsBoat())
					{
						BoatTick();
					}
					else
					{
						NormalTick();
					}

					if (bPushEmAway)
						PushEmAway();

					//SET_PED_KEEP_TASK(myPed.Handle(), true);

				}
				else
				{
					TurnOff();
				}

			}

			inline void NormalTick()
			{
				if (!initialSet)
				{
					ScrHandle tsk;
					OPEN_SEQUENCE_TASK(&tsk);

					//TASK_VEHICLE_DRIVE_TO_COORD(myPed.Handle(), vehicle.Handle(), destination.x, destination.y, destination.z, speed, 0, vehicleModel.hash, drivingStyle, 1.0f, 100.0f);
					TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(0, vehicle.Handle(), destination.x, destination.y, destination.z, speed, drivingStyle, 7.0f);

					CLOSE_SEQUENCE_TASK(tsk);
					TASK_PERFORM_SEQUENCE(myPed.Handle(), tsk);
					CLEAR_SEQUENCE_TASK(&tsk);

					initialSet = true;
				}


			}

			inline void HeliTick()
			{
				if (!initialSet)
				{
					ScrHandle tsk;
					OPEN_SEQUENCE_TASK(&tsk);

					TASK_HELI_MISSION(0, vehicle.Handle(), 0, 0, destination.x, destination.y, destination.z, 4, speed, 50.0f, -1.0f, 100, 200, 0xbf800000, 0);

					CLOSE_SEQUENCE_TASK(tsk);
					TASK_PERFORM_SEQUENCE(myPed.Handle(), tsk);
					CLEAR_SEQUENCE_TASK(&tsk);

					initialSet = true;
				}


			}

			inline void PlaneTick()
			{
				if (!initialSet)
				{
					ScrHandle tsk;
					OPEN_SEQUENCE_TASK(&tsk);

					TASK_PLANE_MISSION(0, vehicle.Handle(), 0, 0, destination.x, destination.y, destination.z, 4, speed, 50.0f, -1.0f, 100.0f, 200.0f, false);

					CLOSE_SEQUENCE_TASK(tsk);
					TASK_PERFORM_SEQUENCE(myPed.Handle(), tsk);
					CLEAR_SEQUENCE_TASK(&tsk);

					initialSet = true;
				}

			}

			inline void BoatTick()
			{
				if (!initialSet)
				{
					ScrHandle tsk;
					OPEN_SEQUENCE_TASK(&tsk);

					TASK_BOAT_MISSION(0, vehicle.Handle(), 0, 0, destination.x, destination.y, destination.z, 4, speed, 786469, 10.0f, 1071);

					CLOSE_SEQUENCE_TASK(tsk);
					TASK_PERFORM_SEQUENCE(myPed.Handle(), tsk);
					CLEAR_SEQUENCE_TASK(&tsk);

					initialSet = true;
				}

			}

			inline void PushEmAway()
			{
				const auto& md = vehicleModel.Dimensions();
				const auto& pos = vehicle.Position_get();
				const auto& rot = vehicle.Rotation_get();
				const auto& dir = Vector3::RotationToDirection(rot);

				auto ray = RaycastResult::RaycastCapsule(pos, dir, 3.2f + md.Dim1.y, 2.3f, IntersectOptions::Everything, vehicle);
				//auto& ray = RaycastResult::Raycast(pos, dir, 5.0f, IntersectOptions::Everything, vehicle);
				//auto& ray = RaycastResult::Raycast(pos + (dir * md.Dim1.y), pos + (dir * (md.Dim1.y + 4.3f)), IntersectOptions::Everything);

				if (ray.DidHitEntity())
				{
					GTAentity thingInFront = ray.HitEntity();
					thingInFront.ApplyForce(dir * 10.0f);
				}

				const Vector3& myFrontBumper = pos + (dir * md.Dim1.y);

				for (GTAvehicle v : _nearbyVehicles)
				{
					if (v.Handle() == vehicle.Handle()) continue;

					if (v.IsInRangeOf(myFrontBumper, 4.0f))
					{
						v.ApplyForce(dir * 10.0f);
					}
				}
			}


		};
		MethodsClass Methods;

		void ToggleOnOff()
		{
			Methods.Toggle();
		}
		void Tick()
		{
			Methods.Tick();
		}


		void Sub_AutoDrive()
		{
			GTAped myPed = Game::PlayerPed();

			auto& speed = Methods.speed;
			auto& drivingStyle = Methods.drivingStyle;
			auto& drivingStyleIndex = Methods.drivingStyleIndex;
			auto& bPushEmAway = Methods.bPushEmAway;

			std::vector<std::string> drivingStyleNames;
			for (auto& dsns : DrivingStyle::nameArray)
			{
				drivingStyleNames.push_back(dsns.name);
			}

			bool speed_plus = 0, speed_minus = 0;
			bool drivingStyle_plus = 0, drivingStyle_minus = 0;

			AddTitle("Auto Drive");

			AddLocal("Go To Waypoint", Methods.Enabled(), ToggleOnOff, ToggleOnOff);
			AddNumber("Speed (KMPH)", speed * 3.6f, 1, null, speed_plus, speed_minus);
			AddTexter("Driving Style", drivingStyleIndex, drivingStyleNames, null, drivingStyle_plus, drivingStyle_minus);
			AddToggle("Push Other Vehicles Away", bPushEmAway);

			if (speed_plus) {
				if (speed < FLT_MAX) speed += (0.5f / 3.6f);
				myPed.DrivingSpeed_set(speed);
				//Methods.initialSet = false;
				return;
			}
			if (speed_minus) {
				if (speed > 0) speed -= (0.5f / 3.6f);
				myPed.DrivingSpeed_set(speed);
				//Methods.initialSet = false;
				return;
			}

			if (drivingStyle_plus) {
				if (drivingStyleIndex < drivingStyleNames.size() - 1) drivingStyleIndex++;
				myPed.DrivingStyle_set(DrivingStyle::nameArray[drivingStyleIndex].style);
				//drivingStyle = DrivingStyle::nameArray[drivingStyleIndex].style;
				//Methods.initialSet = false;
				return;
			}
			if (drivingStyle_minus) {
				if (drivingStyleIndex > 0) drivingStyleIndex--;
				myPed.DrivingStyle_set(DrivingStyle::nameArray[drivingStyleIndex].style);
				//drivingStyle = DrivingStyle::nameArray[drivingStyleIndex].style;
				//Methods.initialSet = false;
				return;
			}

		}

	}

	namespace VehicleSlam_catind
	{
		Vehicle& _slamVehicle = Static_12;
		float* _slamValue;
		void InitSub(GTAvehicle veh, float* val)
		{
			_slamVehicle = veh.Handle();
			_slamValue = val;
		}

#pragma region slamvalues
		struct NamedSlamValueS { std::string name; float value; };
		std::vector<NamedSlamValueS> vValues_VehicleSlam
		{
			{ "Off", 0.0f },

			{ "I'm A Skyscraper", 0.35f },
			{ "Such High", 0.30f },
			{ "I'm Tall, Aren't I", 0.25f },
			{ "I'm Growing", 0.20f },
			{ "Tip Toeing", 0.10f },

			{ "I Got The Crabs", -0.10f },
			{ "Get Get Get, Get Low", -0.20f },
			{ "Short Is Cute", -0.25f },
			{ "I'm A Ninja Turtle", -0.30f },
			{ "Apple Bottom Jeans", -0.38f }
		};
#pragma endregion

		void Sub_VehicleSlam()
		{
			AddTitle("Slam It");

			bool pressed = 0;
			for (auto& sl : vValues_VehicleSlam)
			{
				pressed = 0;
				AddTickol(sl.name, *_slamValue == sl.value, pressed, pressed, TICKOL::CARTHING); if (pressed)
				{
					*_slamValue = sl.value;
					if (sl.value <= -0.35f)
						Game::Print::PrintBottomCentre("~b~Note:~s~ You can even drive on walls with this value.");
				}
			}
		}
	}

	void AddvweaponOption(const std::string& text, bool &loop_pointer, Hash Hash)
	{
		bool pressed = false;
		AddToggle(text, loop_pointer, pressed); if (pressed)
		{
			if (Hash)
			{
				if (!HAS_WEAPON_ASSET_LOADED(Hash)) REQUEST_WEAPON_ASSET(Hash, 31, 0);
				//	GIVE_WEAPON_TO_PED(Static_241, Hash, 120, 1, 1);
				Game::Print::PrintBottomLeft("Press ~b~LS/L1/NUM_PLUS~s~ for hax!");
			}
		}
	}
	void VehicleWeapons_()
	{
		bool VehicleWeapons_alloff = false;

		AddTitle("Vehicle Weapons");
		AddToggle("Display Projectile Path", loop_vehweap_lines);
		AddOption("Turn All Off", VehicleWeapons_alloff);
		AddvweaponOption("RPG", loop_vehicle_RPG, 3204302209);
		AddvweaponOption("Fireworks", loop_vehicle_fireworks, 2138347493);
		AddvweaponOption("Guns", loop_vehicle_guns, 3220176749);
		AddvweaponOption("Snowballs", loop_vehicle_snowballs, 126349499);
		AddvweaponOption("Balls", loop_vehicle_balls, 600439132);
		AddvweaponOption("Water Hydrants", loop_vehicle_waterhyd, 0);
		AddvweaponOption("Flame Leaks", loop_vehicle_flameleak, 0);
		AddvweaponOption("Green Laser", loop_vehicle_laser_green, 4026335563);
		AddvweaponOption("Red Laser", loop_vehicle_laser_red, 1566990507);
		AddvweaponOption("Valkyrie Turrets", loop_vehicle_turrets_valkyrie, 1097917585);
		AddvweaponOption("Flares", loop_vehicle_flaregun, WEAPON_FLARE);
		AddvweaponOption("Heavy Snipers", loop_vehicle_heavysnip, 205991906);
		AddvweaponOption("Tazers", loop_vehicle_tazerweap, 911657153);
		AddvweaponOption("Molotovs", loop_vehicle_molotovweap, 615608432);
		AddvweaponOption("Combat PDWs", loop_vehicle_combatpdw, 171789620);


		if (VehicleWeapons_alloff) {
			loop_vehicle_RPG =
				loop_vehicle_fireworks =
				loop_vehicle_guns =
				loop_vehicle_snowballs =
				loop_vehicle_balls =
				loop_vehicle_waterhyd =
				loop_vehicle_flameleak =
				loop_vehicle_laser_green =
				loop_vehicle_laser_red =
				loop_vehicle_turrets_valkyrie =
				loop_vehicle_flaregun =
				loop_vehicle_heavysnip =
				loop_vehicle_tazerweap =
				loop_vehicle_molotovweap =
				loop_vehicle_combatpdw = false;
			return;
		}

	}

	void VehicleMultipliers_()
	{
		bool VehicleOps_i69_int_Acceleration = 0,
			VehicleOps_d69_int_Acceleration = 0,
			VehicleOps_i69_int_Brake = 0,
			VehicleOps_d69_int_Brake = 0,
			VehicleOps_i69_int_Handling = 0,
			VehicleOps_d69_int_Handling = 0;

		AddTitle("Multipliers");
		AddNumber("CMOD_STAT_1", mult69_5, 0, null, VehicleOps_i69_int_Acceleration, VehicleOps_d69_int_Acceleration, true); // Acceleration
		AddNumber(Game::GetGXTEntry("CMOD_STAT_2") + " & Reverse", mult69_6, 0, null, VehicleOps_i69_int_Brake, VehicleOps_d69_int_Brake); // Braking & Reverse
		AddNumber("CMOD_STAT_3", mult69_7, 0, null, VehicleOps_i69_int_Handling, VehicleOps_d69_int_Handling, true); // Handling/Traction


		if (VehicleOps_i69_int_Acceleration) { if (mult69_5 < 200) mult69_5++; return; }
		if (VehicleOps_d69_int_Acceleration) { if (mult69_5 > 0) mult69_5--; return; }

		if (VehicleOps_i69_int_Brake) { if (mult69_6 < 100) mult69_6++; return; }
		if (VehicleOps_d69_int_Brake) { if (mult69_6 > 0) mult69_6--; return; }

		if (VehicleOps_i69_int_Handling) { if (mult69_7 < 100) mult69_7++; return; }
		if (VehicleOps_d69_int_Handling) { if (mult69_7 > 0) mult69_7--; return; }


	}

	void VehicleMultiPlatNeons_Sub()
	{
		bool addCar = 0, setRgbIndexTo3 = 0, clearlist = 0,
			intensity_plus = 0, intensity_minus = 0, intensity_custom = 0;

		AddTitle("Neons");
		AddToggle("Toggle", loop_multiplat_neons, null, clearlist);
		AddNumber("Intensity", _global_MultiPlatNeons_Intensity, 2, intensity_custom, intensity_plus, intensity_minus);
		AddToggle("Rainbow Mode", loop_multiplat_neons_rainbow);

		AddOption("Set Colour", setRgbIndexTo3, nullFunc, SUB::MSPAINTS_RGB);
		if (*Menu::currentopATM == Menu::printingop)
			Add_preset_colour_options_previews(_global_MultiPlatNeons_Col);

		if (intensity_plus) _global_MultiPlatNeons_Intensity += 0.05f;
		if (intensity_minus) _global_MultiPlatNeons_Intensity -= 0.05f;

		if (intensity_custom)
		{
			std::string inputStr = Game::InputBox(std::to_string(_global_MultiPlatNeons_Intensity), 10U, "Enter Value:", std::to_string(_global_MultiPlatNeons_Intensity));
			if (inputStr.length() > 0)
			{
				try
				{
					_global_MultiPlatNeons_Intensity = stof(inputStr);
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::to_string(_global_MultiPlatNeons_Intensity), 9U, "Enter Value:", std::to_string(_global_MultiPlatNeons_Intensity));
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_global_MultiPlatNeons_Intensity);
		}

		if (setRgbIndexTo3) bit_MSPaints_RGB_mode = 3;

		if (clearlist) _global_MultiPlatNeons_List.clear();

	}

	namespace Speedo_catind
	{
#pragma region speedo image names
		
		struct NamedSpeedoImage
		{
			std::string displayName;
			std::string fileName;
			DxHookIMG::DxTexture id;
		};

		std::vector<NamedSpeedoImage> vSpeedoImageNames_All[]
		{
			{
				{ "Orange", "needle_orange", 0 },
				{ "Orange Night", "night_needle_orange", 0 },
				{ "Red", "needle_red", 0 },
				{ "Red Night", "night_needle_red", 0 }
			},
			{
				{ "Cyan", "bg_cyan2", 0 },
				{ "Green", "bg_green2", 0 },
				{ "Yellow", "bg_yellow2", 0 },
				{ "Orange", "bg_orange2", 0 },
				{ "Purple", "bg_purple2", 0 },
				{ "Pink", "bg_pink2", 0 }
			},
			{
				{ "Cyan", "bg_cyan", 0 },
				{ "Green", "bg_green", 0 },
				{ "Yellow", "bg_yellow", 0 },
				{ "Orange", "bg_orange", 0 },
				{ "Purple", "bg_purple", 0 },
				{ "Pink", "bg_pink", 0 }
			}
		};
#pragma endregion

		SpeedoImage _currentSpeedoBg = { vSpeedoImageNames_All[2].at(0).fileName, 0 };
		SpeedoImage _currentSpeedoNeedle = { vSpeedoImageNames_All[0].at(0).fileName, 0 };
		UINT8 _speedoAlpha = 0;
		Vector2 _speedoPosition = { 0.85f, 0.86f };

		//enum eSpeedoMode : UINT8 { SPEEDOMODE_OFF, SPEEDOMODE_DIGITAL, SPEEDOMODE_ANALOGUE };
		UINT8 loop_speedo = SPEEDOMODE_OFF;
		bool bit_speedo_mph = false;

		void SetCurrentBgIdFromBgNameForConfig()
		{
			for (auto& sic : vSpeedoImageNames_All)
			{
				for (auto& si : sic)
				{
					if (_currentSpeedoBg.fileName == si.fileName)
					{
						_currentSpeedoBg.id = si.id;
						return;
					}
				}
			}
		}
		void LoadSpeedoImages()
		{
			for (auto& sic : vSpeedoImageNames_All)
			{
				for (auto& si : sic)
				{
					si.id.Load(GetPathffA(Pathff::Speedo, true) + si.fileName + ".png");
				}
			}

			SetCurrentBgIdFromBgNameForConfig();
		}

		inline void DrawSpeedoImage(SpeedoImage& bg, SpeedoImage& needle, float speedf, float alpha)
		{
			//size.x = 256.0f * 0.66f / Game::defaultScreenRes.first; size.y = 256.0f * 0.66f / Game::defaultScreenRes.second; // y is 0.2347f
			Vector2 size = { 0.1540f, 0.164f };
			Vector2& pos = Speedo_catind::_speedoPosition;

			//float aspectRatio = _GET_SCREEN_ASPECT_RATIO(false);
			//drawTexture(bg.id, 0, -9999, 100, size.x, size.y, 0.5f, 0.5f, pos.x, pos.y, 0.0f, aspectRatio, 1.0f, 1.0f, 1.0f, alpha);
			//drawTexture(needle.id, 0, -9998, 100, size.x, size.y, 0.5f, 0.5f, pos.x, pos.y, (speedf > 270.0f ? 270.6f : speedf) / 360.0f, aspectRatio, 1.0f, 1.0f, 1.0f, alpha);

			//bg.id.Draw(0, pos, size, 0.0f, RGBA(255, 255, 255, alpha));
			bg.id.Draw(0, pos, size, 0.0f, RGBA(255, 255, 255, alpha < 170 ? alpha : 170));
			needle.id.Draw(0, pos, size, (speedf > 270.0f ? 270.6f : speedf), RGBA(255, 255, 255, alpha));

			Game::Print::setupdraw(font_speedo, Vector2(0.33, 0.33), true, false, false, RGBA(0, 153, 153, alpha));
			Game::Print::drawfloat(speedf, 0, pos.x, pos.y - 0.073f);
		}
		void SpeedoTick()
		{
			if (!IS_PLAYER_CONTROL_ON(PLAYER_ID()))
			{
				_speedoAlpha = 0;
			}
			else
			{
				float speedf = abs(3.6f * GET_ENTITY_SPEED_VECTOR(g_myVeh, true).y);
				if (bit_speedo_mph)
					speedf *= 0.6214f;

				if (loop_speedo == SPEEDOMODE_DIGITAL)
				{
					/*if (HAS_STREAMED_TEXTURE_DICT_LOADED("busy_spinner"))
					DRAW_SPRITE("busy_spinner", "orange_grad", 0.88f, 0.82f, 0.256, 0.08f, 0.0f, titlebox.R, titlebox.G, titlebox.B, 225);
					else
					REQUEST_STREAMED_TEXTURE_DICT("busy_spinner", 0);*/
					std::string speedStr;
					if (bit_speedo_mph)
					{
						speedStr = std::to_string((int)speedf) + " ~b~MPH";
					}
					else
					{
						//if (font_speedo == 0 || font_speedo == 1) sprintf_s(text, "%i ~b~KM/H", (INT)speedf);
						//else sprintf_s(text, "%i ~b~KMPH", (INT)speedf);
						speedStr = std::to_string((int)speedf) + " ~b~KMPH";
					}
					Game::Print::setupdraw(font_speedo, Vector2(0.8f, 0.8f), true, false, false);
					Game::Print::drawstring(speedStr, 0.915f, 0.8f);

				}
				else //if (loop_speedo == SPEEDOMODE_ANALOGUE)
				{
					/*if (!IS_HUD_COMPONENT_ACTIVE(HUDCOMPONENT_VEHICLE_NAME) || IS_PED_RUNNING_MOBILE_PHONE_TASK(PLAYER_PED_ID()))
					{
					_speedoAlpha = 0.0f;
					}*/

					if (_speedoAlpha < 255) _speedoAlpha += 5;

					UINT8 clockHour = GET_CLOCK_HOURS();
					if (clockHour < 19 && clockHour > 7)
						_currentSpeedoNeedle = { vSpeedoImageNames_All[0].at(0).fileName, vSpeedoImageNames_All[0].at(0).id }; // Day
					else
						_currentSpeedoNeedle = { vSpeedoImageNames_All[0].at(1).fileName, vSpeedoImageNames_All[0].at(1).id }; // Night

					/*if (HAS_STREAMED_TEXTURE_DICT_LOADED("MenyooExtras"))
					{
						PCHAR bg_name = _currentSpeedoBg.fileName.c_str();
						PCHAR needle_name = _currentSpeedoNeedle.fileName.c_str();

						Vector3 res = GET_TEXTURE_RESOLUTION("MenyooExtras", bg_name);
						res.x = res.x * 0.66 / Game::defaultScreenRes.first;
						res.y = res.y * 0.66 / Game::defaultScreenRes.second;

						DRAW_SPRITE("MenyooExtras", bg_name, _speedoPosition.x, _speedoPosition.y, res.x, res.y, 0.0f, 255, 255, 255, _speedoAlpha); // Background
						Game::Print::setupdraw(font_speedo, Vector2(0.33, 0.33), true, false, false, RGBA(0, 153, 153, alpha < 220 ? alpha : 220));
						Game::Print::drawfloat(speedf, 0, _speedoPosition.x, _speedoPosition.y - 0.074f);
						DRAW_SPRITE("MenyooExtras", needle_name, _speedoPosition.x, _speedoPosition.y, res.x, res.y, speedf > 270.0f ? 270.6f : speedf, 255, 255, 255, _speedoAlpha); // Needle
					}
					else
						REQUEST_STREAMED_TEXTURE_DICT("MenyooExtras", 0);*/

					DrawSpeedoImage(_currentSpeedoBg, _currentSpeedoNeedle, speedf, _speedoAlpha);
				}
			}
		}


		void __AddOption(const std::string& text, NamedSpeedoImage& img)
		{
			bool pressed = false;
			AddTickol(text, _currentSpeedoBg.id.ID() == img.id.ID(), pressed, pressed); if (pressed)
			{
				_currentSpeedoBg = { img.fileName, img.id };
			}

		}

		void Sub_Main()
		{
			std::vector<std::string> vSpeedoUnits{ "Metric", "Imperial" };
			std::vector<std::string> vSpeedoTnames{ "Off", "Digital", "Analogue" };

			bool speedo_mode_plus = 0, speedo_mode_minus = 0,
				VehicleSpeedos_analoguize = 0, VehicleSpeedos_digitize = 0,
				speedo_unit_plus = 0,
				asposX_plus = 0, asposX_minus = 0, asposY_plus = 0, asposY_minus = 0;

			AddTitle("Speedometers");
			AddTexter("Speedo", loop_speedo, vSpeedoTnames, null, speedo_mode_plus, speedo_mode_minus);
			AddTexter("Unit", bit_speedo_mph, vSpeedoUnits, null, speedo_unit_plus, speedo_unit_plus);
			if (loop_speedo == SPEEDOMODE_ANALOGUE)
			{
				AddOption("Light Themes", null, nullFunc, SUB::VEHICLESPEEDOS_LIGHT);
				AddOption("Dark Themes", null, nullFunc, SUB::VEHICLESPEEDOS_DARK);
				AddNumber("X Position", _speedoPosition.x, 3, null, asposX_plus, asposX_minus);
				AddNumber("Y Position", _speedoPosition.y, 3, null, asposY_plus, asposY_minus);
			}

			if (asposX_plus) _speedoPosition.x += 0.005f;
			else if (asposX_minus) _speedoPosition.x -= 0.005f;
			if (asposY_plus) _speedoPosition.y += 0.005f;
			else if (asposY_minus) _speedoPosition.y -= 0.005f;

			if (speedo_mode_plus) { if (loop_speedo < vSpeedoTnames.size() - 1) loop_speedo++; }
			if (speedo_mode_minus) { if (loop_speedo  > 0) loop_speedo--; }

			if (speedo_unit_plus) { bit_speedo_mph = bit_speedo_mph == 0 ? 1 : 0; }


		}
		void Sub_Themes_Light()
		{
			AddTitle("Light Themes");

			for (auto& si : vSpeedoImageNames_All[1])
			{
				__AddOption(si.displayName, si);
			}

		}
		void Sub_Themes_Dark()
		{
			AddTitle("Dark Themes");

			for (auto& si : vSpeedoImageNames_All[2])
			{
				__AddOption(si.displayName, si);
			}

		}
	}

}




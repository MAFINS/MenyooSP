/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FunnyVehicles.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAprop.h"

#include "VehicleSpawner.h"
#include "VehicleModShop.h"

#include <string>

namespace sub
{
	// FunnyVehicles & attachObjects subs - weird attachment of entities idek
	void att_ped_to_veh(GTAmodel::Model model, GTAvehicle vehicle, const Vector3& offset, const Vector3& rotation, bool invis, bool piggyback)
	{
		if (vehicle.Exists())
		{
			if (model.Load(2000))
			{
				if (invis && vehicle.IsVisible())
				{
					vehicle.SetVisible(false);
					for (int i = -1; i <= (vehicle.MaxPassengers() - 2); i++)
					{
						if (vehicle.IsSeatFree(VehicleSeat(i)))
							continue;
						GTAentity& sped = vehicle.GetPedOnSeat(VehicleSeat(i));
						sped.RequestControl();
						sped.SetVisible(true);
					}
				}

				Ped ped = CREATE_PED(PedType::Human, model.hash, 0.0f, 0.0f, 0.0f, vehicle.Heading_get(), 1, 1);
				PED_TO_NET(ped);
				SET_ENTITY_LOD_DIST(ped, 696969);
				ATTACH_ENTITY_TO_ENTITY(ped, vehicle.GetHandle(), -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0, 0, 0, 0, 2, 1, 0);
				DETACH_ENTITY(ped, 1, 1);
				ATTACH_ENTITY_TO_ENTITY(ped, vehicle.GetHandle(), -1, offset.x, offset.y, offset.z, rotation.x, rotation.y, rotation.z, 0, 0, 0, 0, 2, 1, 0);
				SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
				if (piggyback)
				{
					//Hash == PedHash::TigerShark ?
					//ATTACH_ENTITY_TO_ENTITY(ped, vehicle, -1, 0.0f, -0.3f, 0.0f, 0.0f, 180.0f, 0.0f, 1, 1, 0, 0, 2, 1) :
					ATTACH_ENTITY_TO_ENTITY(ped, vehicle.GetHandle(), -1, 0.0f, -0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 2, 1, 0);
					REQUEST_ANIM_DICT("mini@prostitutes@sexnorm_veh");
					WAIT(50);
					TASK_PLAY_ANIM(ped, "mini@prostitutes@sexnorm_veh", "bj_loop_male", 8.f, 0.f, -1, 9, 0, 0, 0, 0);
				}
				else
					TASK_STAND_STILL(ped, -1);
				set_ped_invincible_on(ped);
				SET_PED_AS_NO_LONGER_NEEDED(&ped);
			}
		}
	}
	void att_obj_to_veh(GTAmodel::Model model, GTAvehicle vehicle, float X, float Y, float Z, float Pitch, float Roll, float Yaw, bool invis, int boneIndex, bool dynamic, bool collisionEnabled, bool destroyVar)
	{
		if (vehicle.Exists())
		{
			model.Load(3000);

			GTAprop object = CREATE_OBJECT(model.hash, 0.0f, 0.0f, 0.0f, 1, 1, dynamic);
			object.LodDistance_set(1000000);

			GTAped sped;
			if (invis)
			{
				if (model.IsBicycle() || model.IsBike())
				{
					vehicle.Alpha_set(0);
				}
				else if (vehicle.IsVisible())
				{
					vehicle.SetVisible(false);
					for (int i = -1; i <= ((int)(GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle.Handle())) - 2); i++)
					{
						if (IS_VEHICLE_SEAT_FREE(vehicle.Handle(), i, 0)) continue;
						sped.Handle() = GET_PED_IN_VEHICLE_SEAT(vehicle.Handle(), i, 0);
						sped.RequestControl();
						sped.SetVisible(true);
					}
				}
			}

			object.AttachTo(vehicle, boneIndex, false, Vector3(X, Y, Z), Vector3(Pitch, Roll, Yaw));
			//ATTACH_ENTITY_TO_ENTITY(object, vehicle, -1, X, Y, Z, Pitch, Roll, Yaw, 0, 0, 0, 0, 2, 1);
			SET_ENTITY_LIGHTS(object.Handle(), 0);
			if (collisionEnabled) object.IsCollisionEnabled_set(collisionEnabled);
			if (destroyVar) SET_OBJECT_AS_NO_LONGER_NEEDED(&object.Handle());
		}

	}
	void att_veh_to_veh(GTAmodel::Model model, GTAvehicle vehicle, int primColour, int secColour, float X, float Y, float Z, float Pitch, float Roll, float Yaw, bool invis, int boneIndex, bool collisionEnabled)
	{
		if (vehicle.Exists())
		{
			model.Load(3000);

			GTAvehicle veh = CREATE_VEHICLE(model.hash, 0.0f, 0.0f, 0.0f, 0.0f, 1, 1, 0);
			veh.LodDistance_set(1000000);

			GTAped sped;
			if (invis)
			{
				if (model.IsBicycle() || model.IsBike())
				{
					vehicle.Alpha_set(0);
				}
				else if (vehicle.IsVisible())
				{
					vehicle.SetVisible(false);
					for (int i = -1; i <= ((int)(GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle.Handle())) - 2); i++)
					{
						if (IS_VEHICLE_SEAT_FREE(vehicle.Handle(), i, 0)) continue;
						sped.Handle() = GET_PED_IN_VEHICLE_SEAT(vehicle.Handle(), i, 0);
						sped.RequestControl();
						sped.SetVisible(true);
					}
				}
			}

			veh.AttachTo(vehicle, boneIndex, false, Vector3(X, Y, Z), Vector3(Pitch, Roll, Yaw));
			//ATTACH_ENTITY_TO_ENTITY(object, vehicle, -1, X, Y, Z, Pitch, Roll, Yaw, 0, 0, 0, 0, 2, 1);
			SET_ENTITY_LIGHTS(veh.Handle(), 0);
			veh.PrimaryColour_set(primColour);
			veh.SecondaryColour_set(secColour);
			if (collisionEnabled) veh.IsCollisionEnabled_set(collisionEnabled);
			SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh.Handle());
		}

	}

	namespace FunnyVehicles_catind
	{
		void HaxBy(const std::string& name)
		{
			Game::Print::PrintBottomLeft("Hax by ~b~" + name);
		}

		// Spawn funny veh function
		int PlaceFunnyVeh_(Hash hash)
		{
			return FuncSpawnVehicle_(hash, Static_241);
		}

		// Funny vehicles
		void GoKart()
		{
			Vehicle tempVehicle = PlaceFunnyVeh_(VEHICLE_ADDER); // Adder

			GTAvehicle(tempVehicle).BreakAllDoors(true);

			// prop_yoga_mat_02
			Hash tempHash = 2057317573;
			FLOAT X = -0.2f; // 23
			FLOAT Y = 0.3f; // 465
			FLOAT Z = -0.45f; // 466
			FLOAT Pitch = 0.0f; // 467
			FLOAT Roll = 0.0f; // 476
			FLOAT Yaw = 90.0f; // 481
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2057317573;
			X = -0.6000;
			Y = 0.3000;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2057317573;
			X = -0.6000;
			Y = 0.2000;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2057317573;
			X = -0.2000;
			Y = 0.2000;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_bumper_02
			tempHash = 2574278700;
			X = 0.1800;
			Y = 0.2500;
			Z = -0.4100;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2574278700;
			X = -0.9800;
			Y = 0.2500;
			Z = -0.4100;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = -90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_weight_15k
			tempHash = 933757793;
			X = 0.2400;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.2700;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3000;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3000;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3300;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3600;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.2400;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.2700;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3000;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3300;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = 0.3600;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0200;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0500;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0800;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.1100;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.1400;
			Y = 0.9300;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0200;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0500;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.0800;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.1100;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 933757793;
			X = -1.1400;
			Y = -0.4400;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_weight_15k
			tempHash = 933757793;
			X = -0.4000;
			Y = 0.3800;
			Z = 0.2000;
			Pitch = -30.000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_cs_bar
			tempHash = 3062227748;
			X = -0.4000;
			Y = 0.5900;
			Z = -0.1400;
			Pitch = 30.000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_car_seat
			tempHash = 1382419899;
			X = -0.4000;
			Y = -0.1500;
			Z = -0.5000;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 180.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_power_cell
			tempHash = 2235081574;
			X = -0.1500;
			Y = 1.0700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2235081574;
			X = -0.6500;
			Y = 1.0700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2235081574;
			X = -0.4000;
			Y = 1.0700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2235081574;
			X = -0.1500;
			Y = -0.5700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2235081574;
			X = -0.6500;
			Y = -0.5700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 2235081574;
			X = -0.4000;
			Y = -0.5700;
			Z = -0.4500;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);


			//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);


			HaxBy("Stiff_"); // Credits

		}
		void DragsterBike()
		{
			Vehicle tempVehicle = PlaceFunnyVeh_(VEHICLE_AKUMA); // Akuma

																 // prop_cartwheel_01
			Hash tempHash = 4137416026;
			FLOAT X = -0.07f; // 23
			FLOAT Y = 1.1f; // 465
			FLOAT Z = 0.03f; // 466
			FLOAT Pitch = 0.0f; // 467
			FLOAT Roll = 90.0f; // 476
			FLOAT Yaw = 0.0f; // 481
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_cs_bar
			tempHash = 3062227748;
			X = -0.1500;
			Y = 0.7800;
			Z = 0.2100;
			Pitch = 60.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = 0.1500;
			Y = 0.7800;
			Z = 0.2100;
			Pitch = 60.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = 0.1500;
			Y = 0.2800;
			Z = 0.0800;
			Pitch = -30.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = -0.1500;
			Y = 0.2800;
			Z = 0.0800;
			Pitch = -30.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = -0.1500;
			Y = -0.2900;
			Z = -0.2400;
			Pitch = -93.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = 0.1500;
			Y = -0.2900;
			Z = -0.2400;
			Pitch = -93.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = 0.1500;
			Y = -0.3400;
			Z = -0.0200;
			Pitch = -59.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = -0.1500;
			Y = -0.3400;
			Z = -0.0200;
			Pitch = -59.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = -0.1500;
			Y = 0.1400;
			Z = 0.2600;
			Pitch = -59.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			tempHash = 3062227748;
			X = 0.1500;
			Y = 0.1400;
			Z = 0.2600;
			Pitch = -59.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_cs_bar
			tempHash = 3062227748;
			X = 0.0000;
			Y = 0.4600;
			Z = 0.4000;
			Pitch = 0.0000;
			Roll = 90.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_wheel_06
			tempHash = 3730985457;
			X = 0.0000;
			Y = -0.6600;
			Z = -0.2100;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 90.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_power_cell
			tempHash = 2235081574;
			X = 0.0000;
			Y = -0.3900;
			Z = 0.1600;
			Pitch = -40.0000;
			Roll = 0.0000;
			Yaw = 0.0000;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			SET_ENTITY_VISIBLE(tempVehicle, true, false);
			SET_ENTITY_ALPHA(tempVehicle, 0, 0);
			//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);

			HaxBy("Stiff_"); // Credits

		}
		void WeedWheelsBike()
		{
			GTAvehicle tempVehicle = PlaceFunnyVeh_(VEHICLE_BATI); // Bati

			auto wheel_rf = tempVehicle.GetBoneIndex(VBone::wheel_rf); // Still on bike
			auto wheel_lf = tempVehicle.GetBoneIndex(VBone::wheel_lf); // The rotating bone
			auto handlebar = tempVehicle.GetBoneIndex(VBone::handlebars);

			// prop_rub_wheel_02
			Hash tempHash = 3437004565;
			FLOAT X = 0.0f;
			FLOAT Y = 0.0f;
			FLOAT Z = 0.0f;
			FLOAT Pitch = 0.0f;
			FLOAT Roll = 0.0f;
			FLOAT Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_rf);
			tempHash = 3437004565;
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

			// prop_byard_pipe_01
			tempHash = 2971578861;
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
			tempHash = 2971578861;
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

			// prop_rub_wheel_01
			tempHash = 103020963;
			X = 2.1f;
			Y = 0.0f;
			Z = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
			tempHash = 103020963;
			X = -2.0f;
			Y = 0.0f;
			Z = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

			// prop_minigun_01
			tempHash = 3365286072;
			X = 1.0f;
			Y = 0.0f;
			Z = 0.5f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 90.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);
			tempHash = 3365286072;
			X = -1.0f;
			Y = 0.0f;
			Z = 0.5f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 90.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);

			// prop_weed_01
			tempHash = 452618762;
			X = 2.1f;
			Y = 0.0f;
			Z = -1.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
			tempHash = 452618762;
			X = -2.0f;
			Y = 0.0f;
			Z = -1.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

			// prop_car_seat
			tempHash = 1382419899;
			X = 0.0f;
			Y = -0.4f;
			Z = 0.4f;
			Pitch = 22.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);

			// prop_cs_dildo_01
			tempHash = 3872089630;
			X = 0.29f;
			Y = -0.09f;
			Z = -0.36f;
			Pitch = 33.31f;
			Roll = 279.39f;
			Yaw = -34.43f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, handlebar);
			tempHash = 3872089630;
			X = 0.3f;
			Y = -0.08f;
			Z = -0.37f;
			Pitch = 111.699f;
			Roll = 0.0f;
			Yaw = -8.3f;
			att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, handlebar);

			tempVehicle.SetVisible(true);
			tempVehicle.Alpha_set(0);
			//tempVehicle.NoLongerNeeded();

			HaxBy("Wahkah Enyeto");
		}
		void YachtAirship()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BLIMP); // Blimp

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			Hash hash;

			hash = 0x4FCAD2E0; // apa_mp_apa_yacht
			att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0xBCDAC9E7; // apa_mp_apa_yacht_win
			att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0xB4AA481D; // apa_mp_apa_yacht_option2
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x75F724B2; // apa_mp_apa_yacht_o2_rail_a
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x98B5E3D4; // apa_mp_apa_yacht_jacuzzi_ripple1
			att_obj_to_veh(hash, vehicle, 2.00f, -51.00f, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x949F49C7; // apa_mp_apa_y1_l1a
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x2E51B0EA; // apa_mp_apa_y3_l2b
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x956974FD; // apa_mp_apa_yacht_door2
			att_obj_to_veh(hash, vehicle, 1.29f, -36.85f, 0.65f, 0, 0, 90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 3.40f, 0, 6.70, 0, 0, -180.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 0.60f, 0, 6.70f, 0, 0, 0, true, bone_bodyshell, false, true);

			HaxBy("abstractmode");
		}
		void YachtAirshipWithFans()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BLIMP); // Blimp

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			Hash hash;

			hash = 0x4FCAD2E0; // apa_mp_apa_yacht
			att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0xBCDAC9E7; // apa_mp_apa_yacht_win
			att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0xB4AA481D; // apa_mp_apa_yacht_option2
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x75F724B2; // apa_mp_apa_yacht_o2_rail_a
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x98B5E3D4; // apa_mp_apa_yacht_jacuzzi_ripple1
			att_obj_to_veh(hash, vehicle, 2.00f, -51.00f, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x949F49C7; // apa_mp_apa_y1_l1a
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x2E51B0EA; // apa_mp_apa_y3_l2b
			att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

			hash = 0x956974FD; // apa_mp_apa_yacht_door2
			att_obj_to_veh(hash, vehicle, 1.29f, -36.85f, 0.65f, 0, 0, 90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 3.40f, 0, 6.70, 0, 0, -180.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 0.60f, 0, 6.70f, 0, 0, 0, true, bone_bodyshell, false, true);

			hash = 0x745F3383; // prop_windmill_01
			att_obj_to_veh(hash, vehicle, 4.30f, 36.10f, 0.50f, -90.0, 0, 90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 0.70f, 36.10f, 0.50f, -90.0, 0, -90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 4.30f, -8.40f, -4.30f, -90.0, 0, 90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 0.70f, -8.40f, -4.30f, -90.0, 0, -90.0f, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, 5.00f, -47.0f, -4.0f, 0, -110.0f, 0, true, bone_bodyshell, false, true);
			att_obj_to_veh(hash, vehicle, -2.10f, -47.0f, -4.0f, 0, 110.0f, 0, true, bone_bodyshell, false, true);


			HaxBy("abstractmode");
		}
		void FibBuilding()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BLIMP); // Blimp

			auto bone_chassis = vehicle.GetBoneIndex(VBone::chassis_dummy);

			Model building = 0xAC4365DD; // dt1_05_build1_damage
			ModelDimensions& buildingDim = building.Dimensions();
			ModelDimensions& vehicleDim = vehicle.ModelDimensions();

			att_obj_to_veh(building, vehicle, 0, 0, vehicleDim.Dim1.z - buildingDim.Dim2.z, 0, 0, 0, 1, bone_chassis, false, true, false); // Don't set as no longer needed

			HaxBy("scorz (originally)");
		}
		void BlackNoisyUFO()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_VALKYRIE); // Valkyrie

			auto bone_chassis = vehicle.GetBoneIndex(VBone::chassis_dummy);

			Hash hash;

			hash = 0x7D79DAD4; // dt1_tc_dufo_core
			att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 0, 1, bone_chassis, true);

			HaxBy("scorz");
		}
		void ToyCar()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_T20); // T20

			vehicle.BreakAllDoors(true);

			// ind_prop_dlc_roller_car
			Hash hash = 0x5C05F6C1;
			FLOAT X = 0.0f;
			FLOAT Y = 0.2f;
			FLOAT Z = -0.5f;
			FLOAT Pitch = 0.0f;
			FLOAT Roll = 0.0f;
			FLOAT Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_hd_seats_01
			hash = 0x0A5654F6;
			X = 0.0f;
			Y = 0.28f;
			Z = -0.13f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_wheel_03
			hash = 0xD2FB3B23;
			X = 0.95f;
			Y = 1.2f;
			Z = -0.2f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = 1.06f;
			Y = 1.2f;
			Z = -0.2f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = 0.98f;
			Y = -0.91f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = 1.15f;
			Y = -0.91f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = -0.98f;
			Y = 1.2f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = -1.15f;
			Y = 1.2f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = -0.98f;
			Y = -0.91f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xD2FB3B23;
			X = -1.10f;
			Y = -0.91f;
			Z = -0.21f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_bumper_03
			hash = 0xB9579FFA;
			X = 0.0f;
			Y = 1.33f;
			Z = -1.8f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_compressor_03
			hash = 0xE08EF8F2;
			X = 0.03f;
			Y = 1.34f;
			Z = -0.82f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = -90.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// hei_prop_wall_alarm_off
			hash = 0x889E3E33;
			X = -0.55f;
			Y = -1.38f;
			Z = -0.38f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0x889E3E33;
			X = 0.55f;
			Y = -1.38f;
			Z = -0.38f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_car_exhaust_01
			hash = 0xFC612F85;
			X = 0.26f;
			Y = -0.76f;
			Z = -0.49f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xFC612F85;
			X = 0.18f;
			Y = -0.76f;
			Z = -0.49f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xFC612F85;
			X = -0.40f;
			Y = -0.76f;
			Z = -0.49f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0xFC612F85;
			X = -0.32f;
			Y = -0.76f;
			Z = -0.49f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_sh_mr_rasp_01
			hash = 0xD59D6B1A;
			X = -0.01f;
			Y = -0.82f;
			Z = 0.11f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_voltmeter_01
			hash = 0x8F4674EC;
			X = 0.0f;
			Y = 0.98f;
			Z = 0.02f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 0.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

			// prop_spot_01
			hash = 0x5376930C;
			X = -0.57f;
			Y = 1.49f;
			Z = -0.04f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
			hash = 0x5376930C;
			X = 0.55f;
			Y = 1.49f;
			Z = -0.04f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 180.0f;
			att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);


			HaxBy("djbob77");
		}
		void Adderuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_ADDER); // Adder

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_BLACK, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0, 0, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			HaxBy("KeyWest2014");
		}
		void Zentornuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_ZENTORNO); // Zentorno

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_ICE_WHITE, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.2230f, -0.0280f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);

			HaxBy("KeyWest2014");
		}
		void TurismoRuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_TURISMOR); // TurismoR

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_ICE_WHITE, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.0400f, 0.4000f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);

			HaxBy("KeyWest2014");
		}
		void EnturumaXF()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_ENTITYXF); // EntityXF

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_BLACK, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.1410f, 0.1700f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			HaxBy("KeyWest2014");
		}
		void Osirisuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_OSIRIS); // Osiris

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_YELLOW, 0, 0.1300f, 0.0400f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_YELLOW);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_RED);

			set_vehicle_max_upgrades(vehicle.Handle(), true);

			HaxBy("KeyWest2014");
		}
		void T20uma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_T20); // T20

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.1400f, -0.0800f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_YELLOW);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			HaxBy("KeyWest2014");
		}
		void Feltzeruma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_FELTZER2); // Feltzer2

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_LIME_GREEN, VehicleColoursMatte::COLOR_MATTE_SCHAFTER_PURPLE, 0, -0.1530f, 0.0770f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_LIME_GREEN);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_SCHAFTER_PURPLE);

			HaxBy("KeyWest2014");
		}
		void Banshuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BANSHEE); // Banshee

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_RED, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, -0.0500f, 0.0500f, 4.500f, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_RED);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			HaxBy("KeyWest2014");
		}
		void Nightshuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_NIGHTSHADE); // Nightshade

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.0100f, 0.3100f, 5.1600f, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_YELLOW);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			set_vehicle_max_upgrades(vehicle.Handle(), true);

			HaxBy("KeyWest2014");
		}
		void Bulletuma()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BULLET); // Bullet

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_KURUMA2, vehicle, VehicleColoursClassic::COLOR_CLASSIC_GALAXY_BLUE, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, -0.1900f, 0.2600f, 1.5200f, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursClassic::COLOR_CLASSIC_GALAXY_BLUE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			set_vehicle_max_upgrades(vehicle.Handle(), true);

			HaxBy("KeyWest2014");
		}
		void LandJetski()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_BLAZER); // Blzer

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_SEASHARK2, vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_CANDY_RED, 0, -0.1800f, -0.4600f, 0, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE);
			vehicle.SecondaryColour_set(VehicleColoursClassic::COLOR_CLASSIC_CANDY_RED);

			HaxBy("RiNZLR");
		}
		void MonsterTruck_BoatChassis()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MARSHALL); // Marshall

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_MARQUIS, vehicle, VehicleColoursMatte::COLOR_MATTE_ICE_WHITE, VehicleColoursMatte::COLOR_MATTE_ICE_WHITE, 0, 0, 0.7580f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_ICE_WHITE);

			HaxBy("KeyWest2014");
		}
		void MonsterTruck_TankChassis()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MARSHALL); // Marshall

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_RHINO, vehicle, VehicleColoursMatte::COLOR_MATTE_BLACK, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0, 1.4330f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BLACK);

			HaxBy("KeyWest2014");
		}
		void MonsterTruck_HelicopterChassis()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MARSHALL); // Marshall

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_SAVAGE, vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE, 0, -0.2400f, 0.3100f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE);

			HaxBy("KeyWest2014");
		}
		void MonsterTruck_RVChassis()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MARSHALL); // Marshall

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_JOURNEY, vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE, 0, 0.2000f, 0.6400f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE);

			set_vehicle_max_upgrades(vehicle.Handle(), true);

			HaxBy("KeyWest2014");
		}
		void MonsterTruck_FighterJetChassis()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MARSHALL); // Marshall

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_HYDRA, vehicle, VehicleColoursMatte::COLOR_MATTE_BROWN, VehicleColoursMatte::COLOR_MATTE_BROWN, 0, 2.8800f, 1.2800f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_BROWN);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_BROWN);

			HaxBy("KeyWest2014");
		}

		void ChinoODeath()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_CHINO2); // Chino2

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_DUKES2, vehicle, VehicleColoursMatte::COLOR_MATTE_ORANGE, VehicleColoursMatte::COLOR_MATTE_ORANGE, 0, 0.3500f, 0.2200f, 3.5500f, 0, 0, false, bone_bodyshell);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_ORANGE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_ORANGE);

			HaxBy("KeyWest2014");
		}
		void RVBuilding()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_JOURNEY); // Journey

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_JOURNEY, vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, 0, 0, 2.2560f, 0, 0, 0, false, bone_bodyshell, true);
			att_veh_to_veh(VEHICLE_JOURNEY, vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, 0, 0, 2.2560f * 2.0f, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE);
			vehicle.SecondaryColour_set(VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE);

			HaxBy("KeyWest2014");
		}
		void MonsterTrainTruck()
		{
			GTAvehicle vehicle = PlaceFunnyVeh_(VEHICLE_MONSTER); // Liberator

			vehicle.BreakAllDoors(true);

			auto bone_bodyshell = vehicle.GetBoneIndex(VBone::bodyshell);

			att_veh_to_veh(VEHICLE_FREIGHT, vehicle, VehicleColoursMatte::COLOR_MATTE_DARK_BLUE, VehicleColoursMatte::COLOR_MATTE_RED, 0, 1.0600f, 0, 0, 0, 0, false, bone_bodyshell, true);

			vehicle.PrimaryColour_set(VehicleColoursMatte::COLOR_MATTE_DARK_BLUE);
			vehicle.SecondaryColour_set(VehicleColoursMatte::COLOR_MATTE_RED);

			HaxBy("KeyWest2014");
		}

		// Submenus
		void Sub_FunnyVehicles()
		{
			bool FunnyVehicles_CowCar = 0,
				FunnyVehicles_DeerCar = 0,
				FunnyVehicles_SharkCar = 0,
				FunnyVehicles_Coyote = 0,
				FunnyVehicles_Toilet = 0,
				FunnyVehicles_Wheelchair = 0,
				FunnyVehicles_BumperCar = 0,
				FunnyVehicles_RollerCar = 0,
				FunnyVehicles_InflatedFigure = 0,
				FunnyVehicles_Missiles = 0,
				FunnyVehicles_Fort = 0,
				FunnyVehicles_UFO = 0,
				FunnyVehicles_Lights = 0,
				FunnyVehicles_Speakers = 0;

			Vehicle tempVehicle;

			AddTitle("Badly Constructed Vehicles");
			AddOption("Adderuma", null, FunnyVehicles_catind::Adderuma);
			AddOption("Zentornuma", null, FunnyVehicles_catind::Zentornuma);
			AddOption("TurismoRuma", null, FunnyVehicles_catind::TurismoRuma);
			AddOption("EnturumaXF", null, FunnyVehicles_catind::EnturumaXF);
			AddOption("Osirisuma", null, FunnyVehicles_catind::Osirisuma);
			AddOption("T20uma", null, FunnyVehicles_catind::T20uma);
			AddOption("Feltzeruma", null, FunnyVehicles_catind::Feltzeruma);
			AddOption("Banshuma", null, FunnyVehicles_catind::Banshuma);
			//AddOption("Nightshuma", null, FunnyVehicles_catind::Nightshuma);
			AddOption("Bulletuma", null, FunnyVehicles_catind::Bulletuma);
			AddOption("Land Jetski", null, FunnyVehicles_catind::LandJetski);
			AddOption("Chino O Death", null, FunnyVehicles_catind::ChinoODeath);
			AddOption("RV-Building", null, FunnyVehicles_catind::RVBuilding);
			AddOption("Monster Train Truck", null, FunnyVehicles_catind::MonsterTrainTruck);
			AddOption("MonsterTruck (Boat Chassis)", null, FunnyVehicles_catind::MonsterTruck_BoatChassis);
			AddOption("MonsterTruck (RV Chassis)", null, FunnyVehicles_catind::MonsterTruck_RVChassis);
			AddOption("MonsterTruck (Helicopter Chassis)", null, FunnyVehicles_catind::MonsterTruck_HelicopterChassis);
			AddOption("MonsterTruck (Fighter Jet Chassis)", null, FunnyVehicles_catind::MonsterTruck_FighterJetChassis);
			AddOption("MonsterTruck (Tank Chassis)", null, FunnyVehicles_catind::MonsterTruck_TankChassis);
			AddOption("Cow Car", FunnyVehicles_CowCar);
			AddOption("Deer Car", FunnyVehicles_DeerCar);
			AddOption("Shark Car", FunnyVehicles_SharkCar);
			//AddOption("Coyote Car", FunnyVehicles_Coyote);
			AddOption("Poo Mobile", FunnyVehicles_Toilet);
			AddOption("Wheelchair", FunnyVehicles_Wheelchair);
			AddOption("Toy Car", null, FunnyVehicles_catind::ToyCar);
			AddOption("Bumper Car", FunnyVehicles_BumperCar);
			AddOption("Roller Car", FunnyVehicles_RollerCar);
			//AddOption("Inflated Figure", FunnyVehicles_InflatedFigure);
			AddOption("Hydra UFO", FunnyVehicles_UFO);
			//AddOption("Valkyrie UFO (CCM)", null, FunnyVehicles_catind::BlackNoisyUFO);
			AddOption("Missile Surano", FunnyVehicles_Missiles);
			AddOption("'Murican Surano", FunnyVehicles_Lights);
			AddOption("Moveable Platform", FunnyVehicles_Fort);
			AddOption("Speakers Up", FunnyVehicles_Speakers);
			AddOption("Yacht Airship", null, FunnyVehicles_catind::YachtAirshipWithFans);
			AddOption("Yacht Airship (Without Fans)", null, FunnyVehicles_catind::YachtAirship);
			AddOption("FIB Building", null, FunnyVehicles_catind::FibBuilding);
			AddOption("Go-Kart", null, FunnyVehicles_catind::GoKart);
			AddOption("Go-Bike", null, FunnyVehicles_catind::DragsterBike);
			AddOption("Weed-Wheels Bike", null, FunnyVehicles_catind::WeedWheelsBike);


			if (FunnyVehicles_CowCar) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SPEEDO2); // Clown van

				Hash tempHash = PedHash::Cow;
				att_ped_to_veh(tempHash, tempVehicle, Vector3(-0.52f, 0.2f, 0.07f), Vector3(), true);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}
			if (FunnyVehicles_DeerCar) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SPEEDO2); // Clown van

				Hash tempHash = PedHash::Deer;
				att_ped_to_veh(tempHash, tempVehicle, Vector3(-0.52f, 0.2f, -0.07f), Vector3(), true);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}
			if (FunnyVehicles_SharkCar) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				Hash tempHash = PedHash::TigerShark;
				att_ped_to_veh(tempHash, tempVehicle, Vector3(-0.52f, 0.2f, 0.07f), Vector3(), true);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}
			if (FunnyVehicles_Coyote) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_ADDER); // Adder

				Hash tempHash = PedHash::Coyote;
				att_ped_to_veh(tempHash, tempVehicle, Vector3(-0.33f, 0.03f, -0.2f), Vector3(), true);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_Toilet) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 0xC883E74F;
				float X = -0.44f;
				float Y = -0.77f;
				float Z = -0.83f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, GTAvehicle(tempVehicle).GetBoneIndex(VBone::bodyshell));
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_Wheelchair) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 1262298127;
				float X = -0.43f;
				float Y = -0.72f;
				float Z = -0.4f;
				float Pitch = 2.6684f;
				float Roll = 0.0082f;
				float Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_BumperCar) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 4217573666;
				float X = -0.45f;
				float Y = -0.3f;
				float Z = 0.0f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_RollerCar) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 1543894721;
				float X = 0.0f;
				float Y = -0.75f;
				float Z = -0.6f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_InflatedFigure) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 350476011;
				float X = 0.0f;
				float Y = 0.0f;
				float Z = -0.91f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 0.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
				GTAvehicle(tempHash).BreakAllDoors(true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("NOT ME CUZ THIS IS A GIANT WIENER");
				return;
			}

			if (FunnyVehicles_Missiles) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 1246158990;
				float X = 0.0f;
				float Y = 0.0f;
				float Z = 0.0f;
				float Pitch = 0.0f;
				float Roll = 15.0f;
				float Yaw = -90.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_Fort) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				Model tempHash = 1354899844;
				float X = 0.0f;
				float Y = 0.0f;
				float Z = -2.0f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 0.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_UFO) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_HYDRA); // Hydra

				DWORD tempHash = 3026699584;
				float X = 0.0f;
				float Y = 0.0f;
				float Z = 0.0f;
				float Pitch = 0.0f;
				float Roll = 0.0f;
				float Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_Lights) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 1998517203;
				float X = 0.0f; // 23
				float Y = -2.3f; // 465
				float Z = 0.0f; // 466
				float Pitch = 0.4f; // 467
				float Roll = 89.5f; // 476
				float Yaw = -90.9f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = 1998517203;
				X = 0.4f; // 23
				Y = -2.3f; // 465
				Z = 0.0f; // 466
				Pitch = 0.4f; // 467
				Roll = 89.5f; // 476
				Yaw = -90.9f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = 1998517203;
				X = -0.4f; // 23
				Y = -2.3f; // 465
				Z = 0.0f; // 466
				Pitch = 0.4f; // 467
				Roll = 89.5f; // 476
				Yaw = -90.9f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-772034186;
				X = 0.0f; // 23
				Y = 1.4f; // 465
				Z = 0.1f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-1035660791;
				X = 0.0f; // 23
				Y = -1.8f; // 465
				Z = 0.1f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-173347079;
				X = 0.0f; // 23
				Y = -2.0f; // 465
				Z = 0.02f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-173347079;
				X = 0.3f; // 23
				Y = -2.0f; // 465
				Z = 0.02f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-173347079;
				X = -0.3f; // 23
				Y = -2.0f; // 465
				Z = 0.02f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-173347079;
				X = 0.6f; // 23
				Y = -1.6f; // 465
				Z = 0.12f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-173347079;
				X = -0.6f; // 23
				Y = -1.6f; // 465
				Z = 0.12f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-1486744544;
				X = 0.8f; // 23
				Y = 1.6f; // 465
				Z = 0.12f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = (uint)-1486744544;
				X = -0.8f; // 23
				Y = 1.6f; // 465
				Z = 0.12f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				tempHash = 3338484549;
				X = 0.04f; // 23
				Y = -2.01f; // 465
				Z = -0.29f; // 466
				Pitch = 0.2f; // 467
				Roll = -1.4f; // 476
				Yaw = 9.2f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

			if (FunnyVehicles_Speakers) {
				tempVehicle = PlaceFunnyVeh_(VEHICLE_SURANO); // Surano

				DWORD tempHash = 2819992632;
				float X = 0.6f; // 23
				float Y = -1.5f; // 465
				float Z = 0.2f; // 466
				float Pitch = 0.0f; // 467
				float Roll = 0.0f; // 476
				float Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				//DWORD tempHash = -1474974664;
				X = -0.6f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				tempHash = 2112313308;
				X = 0.0f;
				Y = 1.8f;
				Z = -0.4f;
				Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				tempHash = 3326797986;
				X = 0.0f; // 23
				Y = -0.9f; // 465
				Z = -0.1f; // 466
				Pitch = 0.0f; // 467
				Roll = 0.0f; // 476
				Yaw = 0.0f; // 481
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				//DWORD tempHash = -968169310;
				Yaw = 180.0f;
				att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 0, -1, false, true);
				//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);
				HaxBy("MAFINS");
				return;
			}

		}

	}

}




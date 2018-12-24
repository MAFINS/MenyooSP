/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleFly.h"

#include "..\macros.h"

#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\PTFX.h"
#include "..\Natives\natives2.h"
#include "..\Menu\Menu.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\Game.h"
#include "..\Util\keyboard.h"

#include <math.h>

namespace _VehicleFly_
{
	// Not using these as class members because I feel like it
	GTAvehicle vehicle;
	GTAmodel::ModelDimensions vehicle_md;

	void VehicleFly::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		PrintFlyInstructions();
	}

	/*void VehicleFly::oStationary()
	{
		float speed = vehicle.Speed_get() * 3.6f;

		if (speed > 5)
		{
			//vehicle.SetForwardSpeed((speed - 0.5f) / 3.6f);
			vehicle.SetForwardSpeed(GET_RANDOM_FLOAT_IN_RANGE(-1, 1) / 3.6f);
		}
	}*/
	void VehicleFly::GoUp(float const& control)
	{
		if (!control)
			return;

		std::string fxAsset = "scr_rcbarry1", fxName = "scr_alien_teleport";
		float fxScale = 0.068f;

		PTFX::trigger_ptfx_1(fxAsset, fxName, vehicle, Vector3(-vehicle_md.Dim2.x, vehicle_md.Dim1.y, -vehicle_md.Dim2.z), Vector3(90, 0, 0), fxScale);
		PTFX::trigger_ptfx_1(fxAsset, fxName, vehicle, Vector3(vehicle_md.Dim1.x, vehicle_md.Dim1.y, -vehicle_md.Dim2.z), Vector3(90, 0, 0), fxScale);
		PTFX::trigger_ptfx_1(fxAsset, fxName, vehicle, Vector3(-vehicle_md.Dim2.x, -vehicle_md.Dim2.y, -vehicle_md.Dim2.z), Vector3(90, 0, 0), fxScale);
		PTFX::trigger_ptfx_1(fxAsset, fxName, vehicle, Vector3(vehicle_md.Dim1.x, -vehicle_md.Dim2.y, -vehicle_md.Dim2.z), Vector3(90, 0, 0), fxScale);

		vehicle.ApplyForceRelative(Vector3(0, 0, 1.0f * control));

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(0, 0, 1.0f * control));
	}
	void VehicleFly::GoDown(float const& control)
	{
		if (!control)
			return;

		vehicle.ApplyForceRelative(Vector3(0, 0, -1.0f * control));

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(0, 0, -1.0f * control));
	}
	void VehicleFly::GoForward(float const& control)
	{
		if (!control)
			return;

		//PTFX::trigger_ptfx_1("scr_trevor1", "scr_trev1_trailer_boosh", vehicle, Vector3(0, -vehicle_md.Dim2.y, -0.2f), vehicle.Rotation_get() * Vector3(1, 1, -1), 0.5f);
		PTFX::trigger_ptfx_1("scr_carsteal4", "scr_carsteal4_wheel_burnout", vehicle, Vector3(-vehicle_md.Dim1.x, -vehicle_md.Dim1.y, -0.2f), vehicle.Rotation_get() * Vector3(1, 1, -1), 0.08f);
		PTFX::trigger_ptfx_1("scr_carsteal4", "scr_carsteal4_wheel_burnout", vehicle, Vector3(vehicle_md.Dim2.x, -vehicle_md.Dim1.y, -0.2f), vehicle.Rotation_get() * Vector3(1, 1, -1), 0.08f);

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(0, 1.0f * control, 0));
		vehicle.ApplyForceRelative(Vector3(0, 1.0f * control, 0));

		//Vector3& vehRot = Vector3(0, 0, vehicle.Heading_get()).RotToDir(); // Just heading
		//vehicle.ApplyForce(vehRot);
	}
	void VehicleFly::GoBackward(float const& control)
	{
		if (!control)
			return;

		//PTFX::trigger_ptfx_1("scr_trevor1", "scr_trev1_trailer_boosh", vehicle, Vector3(0, vehicle_md.Dim1.y, -0.2f), vehicle.Rotation_get(), 0.5f);

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(0, -1.0f * control, 0));
		vehicle.ApplyForceRelative(Vector3(0, -1.0f * control, 0));

		//Vector3& vehRot = Vector3(0, 0, vehicle.Heading_get()).RotToDir(); // Just heading
		//vehicle.ApplyForce(-vehRot);
	}
	void VehicleFly::GoRight(float const& control)
	{
		if (!control)
			return;

		//vehicle.ApplyForceRelative(Vector3(0, 0, -0.4f), Vector3(0, vehicle_md.Dim1.y - 0.2f, 0));
		//vehicle.ApplyForce(Vector3(control, 0, 0), Vector3(-vehicle_md.Dim1.x + 0.2f, vehicle_md.Dim2.y - 0.2f, 0));

		//vehicle.ApplyForceRelative(Vector3(control / 2, 0, 0), Vector3(control / 2, 0, 0));
		vehicle.ApplyForceRelative(Vector3(1.2f * control, 0, 0));

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(1.0f * control, 0, 0));
	}
	void VehicleFly::GoLeft(float const& control)
	{
		if (!control)
			return;

		//vehicle.ApplyForceRelative(Vector3(0, 0, -0.4f), Vector3(0, vehicle_md.Dim1.y - 0.2f, 0));
		//vehicle.ApplyForce(Vector3(control, 0, 0), Vector3(vehicle_md.Dim1.x - 0.2f, vehicle_md.Dim2.y - 0.2f, 0));

		//vehicle.ApplyForceRelative(Vector3(control / 2, 0, 0), Vector3(control / 2, 0, 0));
		vehicle.ApplyForceRelative(Vector3(-1.2 * control, 0, 0));

		//vehicle.Position_set(vehicle.GetOffsetInWorldCoords(-1.0f * control, 0, 0));
	}

	float VehicleFly::Pressed_GoUp()
	{
		if (Menu::bit_controller)
		{
			return GET_DISABLED_CONTROL_NORMAL(2, INPUT_VEH_ACCELERATE);
		}
		else
		{
			return GET_DISABLED_CONTROL_NORMAL(2, INPUT_VEH_HANDBRAKE);
		}
	}
	float VehicleFly::Pressed_GoDown()
	{
		if (Menu::bit_controller)
		{
			return GET_DISABLED_CONTROL_NORMAL(2, INPUT_VEH_BRAKE);
		}
		else
		{
			return GET_DISABLED_CONTROL_NORMAL(0, INPUT_SPRINT);
		}
	}
	float VehicleFly::Pressed_GoForward()
	{
		if (Menu::bit_controller)
		{
			float norm = -GET_DISABLED_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_Y);
			return (norm > 0.0f) ? (norm) : 0.0f;
		}
		else
		{
			return (GET_DISABLED_CONTROL_NORMAL(2, INPUT_VEH_ACCELERATE));
		}
	}
	float VehicleFly::Pressed_GoBackward()
	{
		if (Menu::bit_controller)
		{
			float norm = -GET_DISABLED_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_Y);
			return (norm < 0.0f) ? abs(norm) : 0.0f;
		}
		else
		{
			return (GET_DISABLED_CONTROL_NORMAL(2, INPUT_VEH_BRAKE));
		}
	}
	float VehicleFly::Pressed_GoRight()
	{
		if (Menu::bit_controller)
		{
			float norm = GET_DISABLED_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_X);
			return (norm > 0.0f) ? norm : 0.0f;
		}
		else
		{
			return IsKeyDown(VirtualKey::D);
		}
	}
	float VehicleFly::Pressed_GoLeft()
	{
		if (Menu::bit_controller)
		{
			float norm = GET_DISABLED_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_X);
			return (norm < 0.0f) ? abs(norm) : 0.0f;
		}
		else
		{
			return IsKeyDown(VirtualKey::A);
		}
	}

	void VehicleFly::DisableDrivingControls()
	{
		std::vector<UINT16> list
		{
			INPUT_VEH_ACCELERATE,
			INPUT_VEH_BRAKE,
			INPUT_VEH_HANDBRAKE,
			INPUT_SPRINT,
			//INPUT_SCRIPT_LEFT_AXIS_X,
			//INPUT_SCRIPT_LEFT_AXIS_Y,
		};

		for (auto& control : list)
		{
			DISABLE_CONTROL_ACTION(2, control, true);
		}
	}

	void VehicleFly::Tick()
	{
		if (bEnabled)
		{
			DoVehicleFlyTick();
		}
	}
	inline void VehicleFly::DoVehicleFlyTick()
	{
		GTAped ped = PLAYER_PED_ID();
		if (!ped.IsInVehicle()) return;

		vehicle = ped.CurrentVehicle();
		vehicle_md = vehicle.ModelDimensions();

		DisableDrivingControls();

		//HoverTick();

		vehicle.Rotation_set(GameplayCamera::Rotation_get());

		float bGoUp = Pressed_GoUp();
		float bGoDown = Pressed_GoDown();
		float bGoForward = Pressed_GoForward();
		float bGoBackward = Pressed_GoBackward();
		float bGoRight = Pressed_GoRight();
		float bGoLeft = Pressed_GoLeft();

		/*if (!bGoUp && !bGoDown && !bGoForward && !bGoBackward && !bGoRight && !bGoLeft)
		{
		GoStationary();
		}*/
		if (bGoUp || bGoDown || bGoForward || bGoBackward || bGoRight || bGoLeft)
		{
			PLAY_SOUND_FROM_ENTITY(-1, "DISTANT_RACERS", vehicle.Handle(), "ROAD_RACE_SOUNDSET", 0, 0);
			PLAY_SOUND_FROM_ENTITY(0, "GENERATOR", vehicle.Handle(), "THE_FERRIS_WHALE_SOUNDSET", 0, 0);
		}

		// NEED LOOPED PTFX, NOT NON LOOPED PTFX
		//PTFX::trigger_ptfx_1("core", "ent_sht_flame", vehicle, Vector3(0, -vehicle_md.Dim2.y, -0.14f), vehicle.Rotation_get() * -1, 0.3f);

		GoUp(bGoUp);
		GoDown(bGoDown);
		GoForward(bGoForward);
		GoBackward(bGoBackward);
		GoRight(bGoRight);
		GoLeft(bGoLeft);


	}
	//void VehicleFly::HoverTick()

	void VehicleFly::PrintFlyInstructions()
	{
		const bool& c = Menu::bit_controller;
		Game::Print::PrintBottomLeft(
			oss_ << (c ? "~b~Accelerate" : "~b~Handbrake") << "~s~ for Up." << "\n"
			<< (c ? "~b~Brake" : "~b~Sprint") << "~s~ for Down."
		);
		Game::Print::PrintBottomLeft(
			oss_ << (c ? "~b~LeftStick" : "~b~Accelerate") << "~s~ for Forward." << "\n"
			<< (c ? "~b~LeftStick" : "~b~Brake") << "~s~ for Backward."
		);
		Game::Print::PrintBottomLeft(
			oss_ << (c ? "~b~LeftStick" : "~b~D") << "~s~ for Right." << "\n"
			<< (c ? "~b~LeftStick" : "~b~A") << "~s~ for Left."
		);
	}


	VehicleFly g_vehicleFly;

	void ToggleOnOff()
	{
		g_vehicleFly.Toggle();
	}

}



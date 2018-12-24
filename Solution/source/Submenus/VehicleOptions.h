/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#pragma once

#include "..\Scripting\DxHookIMG.h"

#include <string>

typedef unsigned __int8 UINT8;
typedef int INT, Entity, Ped, Vehicle, Object, ScrHandle;
typedef unsigned long DWORD, Hash;
typedef char *PCHAR;

class GTAvehicle;
class Vector2;

namespace sub
{
	
	void VehicleOps();

	void PVOpsSub_();

	namespace VehicleAutoDrive_catind
	{
		void ToggleOnOff();
		void Tick();

		void Sub_AutoDrive();
	}

	namespace VehicleSlam_catind
	{
		void InitSub(GTAvehicle veh, float* val);

		void Sub_VehicleSlam();
	}

	void VehicleWeapons_();

	void VehicleMultipliers_();

	void VehicleMultiPlatNeons_Sub();

	namespace Speedo_catind
	{
		struct SpeedoImage
		{
			std::string fileName;
			DxHookIMG::DxTexture id;
		};

		extern SpeedoImage _currentSpeedoBg;
		extern SpeedoImage _currentSpeedoNeedle;
		extern UINT8 _speedoAlpha;
		extern Vector2 _speedoPosition;

		enum eSpeedoMode : UINT8 { SPEEDOMODE_OFF, SPEEDOMODE_DIGITAL, SPEEDOMODE_ANALOGUE };
		extern UINT8 loop_speedo;
		extern bool bit_speedo_mph;

		void SetCurrentBgIdFromBgNameForConfig();
		void LoadSpeedoImages();

		void SpeedoTick();

		void Sub_Main();
		void Sub_Themes_Light();
		void Sub_Themes_Dark();
	}

}




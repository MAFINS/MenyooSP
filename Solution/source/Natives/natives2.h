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

#include "natives.h"

#include "..\main.h" // scriptWait

#include <string>

using namespace PLAYER;
using namespace ENTITY;
using namespace PED;
using namespace VEHICLE;
using namespace OBJECT;
using namespace AI;
using namespace GAMEPLAY;
using namespace AUDIO;
using namespace CUTSCENE;
using namespace INTERIOR;
using namespace CAM;
using namespace WEAPON;
using namespace ITEMSET;
using namespace STREAMING;
using namespace SCRIPT;
using namespace UI;
using namespace GRAPHICS;
using namespace STATS;
using namespace BRAIN;
using namespace MOBILE;
using namespace APP;
using namespace TIME;
using namespace PATHFIND;
using namespace CONTROLS;
using namespace DATAFILE;
using namespace FIRE;
using namespace DECISIONEVENT;
using namespace ZONE;
using namespace ROPE;
using namespace WATER;
using namespace WORLDPROBE;
using namespace NETWORK;
using namespace NETWORKCASH;
using namespace DLC1;
using namespace DLC2;
using namespace SYSTEM;
using namespace DECORATOR;
using namespace SOCIALCLUB;
using namespace UNK;
using namespace UNK1;
using namespace UNK2;
using namespace UNK3;

//#define WAIT scriptWait
static inline void WAIT(DWORD time)
{
	scriptWait(time);
}
static inline void TERMINATE()
{
	WAIT(MAXDWORD);
}

Hash GET_HASH_KEY(char* value);
Hash GET_HASH_KEY(const std::wstring& value);
Hash GET_HASH_KEY(const std::string& value);

void add_text_component_long_string(const std::string& text);

namespace PED
{
	static void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, bool p1) { invoke<Void>(0xC8A9481A01E63C28, ped, p1); } // 0xC8A9481A01E63C28 0x4111BA46

}
namespace VEHICLE
{
	// Interior colour
	static void _0x7D1464D472D32136(Vehicle vehicle, int* interiorColour) { invoke<Void>(0x7D1464D472D32136, vehicle, interiorColour); } // 0x7D1464D472D32136
	static void _0xF40DD601A65F7F19(Vehicle vehicle, int interiorColour) { invoke<Void>(0xF40DD601A65F7F19, vehicle, interiorColour); } // 0xF40DD601A65F7F19

	// Dashboard colour
	static void _0xB7635E80A5C31BFF(Vehicle vehicle, int* dashboardColour) { invoke<Void>(0xB7635E80A5C31BFF, vehicle, dashboardColour); } // 0xB7635E80A5C31BFF
	static void _0x6089CDF6A57F326C(Vehicle vehicle, int dashboardColour) { invoke<Void>(0x6089CDF6A57F326C, vehicle, dashboardColour); } // 0x6089CDF6A57F326C

	// Imp/Exp DLC
	static BOOL _HAS_VEHICLE_ROCKET_BOOST(Vehicle vehicle) { return invoke<BOOL>(0x36D782F68B309BDA, vehicle); }
	static BOOL _IS_VEHICLE_ROCKET_BOOST_ACTIVE(Vehicle vehicle) { return invoke<BOOL>(0x3D34E80EED4AE3BE, vehicle); }
	static void _SET_VEHICLE_ROCKET_BOOST_ACTIVE(Vehicle vehicle, BOOL active) { invoke<Void>(0x81E1552E35DC3839, vehicle, active); }
	static BOOL _HAS_VEHICLE_JUMPING_ABILITY(Vehicle vehicle) { return invoke<Void>(0x9078C0C5EF8C19E9, vehicle); }
	static BOOL _HAS_VEHICLE_PARACHUTE(Vehicle vehicle) { return invoke<BOOL>(0xBC9CFF381338CB4F, vehicle); }
	static BOOL _CAN_VEHICLE_PARACHUTE_BE_ACTIVATED(Vehicle vehicle) { return invoke<BOOL>(0xA916396DF4154EE3, vehicle); }
	static void _SET_VEHICLE_PARACHUTE_ACTIVE(Vehicle vehicle, BOOL active) { invoke<Void>(0x0BFFB028B3DD0A97, vehicle, active); }
	static BOOL _IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model) { return invoke<BOOL>(0x633F6F44A537EBB6, model); } // 0x633F6F44A537EBB6

	// b1604
	static INT _0x3DFF319A831E0CDB(Vehicle vehicle) { return invoke<INT>(0x3DFF319A831E0CDB, vehicle); } // 0x3DFF319A831E0CDB
	static void _0xE41033B25D003A07(Vehicle vehicle, INT value) { invoke<Void>(0xE41033B25D003A07, vehicle, value); } // 0xE41033B25D003A07
}
namespace WEAPON
{
	// Weapon (camo) liveries
	static void _0x9FE5633880ECD8ED(Ped ped, Hash weapon, Hash component, int index) { invoke<Void>(0x9FE5633880ECD8ED, ped, weapon, component, index); } // 0x9FE5633880ECD8ED
	static int _0xF0A60040BE558F2D(Ped ped, Hash weapon, Hash component) { return invoke<Any>(0xF0A60040BE558F2D, ped, weapon, component); } // 0xF0A60040BE558F2D
}



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

typedef int INT, Ped, Vehicle, Object, Entity;
typedef unsigned long DWORD, Hash;
typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef char *PCHAR;

class Vector3;
class GTAentity;
class GTAped;

void teleport_net_ped(GTAentity ped, float X, float Y, float Z, bool bWait = true, bool bPtfx = true);
void teleport_net_ped(GTAentity ped, const Vector3& pos, bool bWait = true, bool bPtfx = true);
void teleport_to_missionBlip(GTAped ped);

namespace sub::TeleportLocations_catind
{
	class TeleLocation;

	namespace TeleMethods
	{
		void ToWaypoint(GTAped ped);
		void ToWaypoint241();
		void ToMissionBlip241();
		void ToForward241();
		void ToCoordinates241(const Vector3& coord);
		void ToTeleLocation241(const TeleLocation& loc);
	}

}




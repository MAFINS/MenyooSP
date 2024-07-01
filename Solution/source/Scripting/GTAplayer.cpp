/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GTAplayer.h"

#include "..\macros.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAentity.h"

#include <string>

GTAplayer::GTAplayer()
	: index(0Ui8)
{
}

GTAplayer::GTAplayer(const GTAplayer& obj)
	: index(obj.index)
{
}

GTAplayer::GTAplayer(INT8 newIndex)
	: index(newIndex)
{
}


INT8& GTAplayer::Handle()
{
	return index;
}
INT8 GTAplayer::GetHandle() const
{
	return index;
}

void GTAplayer::SetIndex(INT8 newIndex)
{
	index = newIndex;
}

GTAped GTAplayer::GetPed() const
{
	return GET_PLAYER_PED(index);
}

std::string GTAplayer::GetName() const
{
	return GET_PLAYER_NAME(index);
}

bool GTAplayer::IsActive() const
{
	return NETWORK_IS_PLAYER_ACTIVE(index) != 0;
}

bool GTAplayer::IsAlive() const
{
	return !IS_PLAYER_DEAD(index);
}

GTAplayer::NetHandle13 GTAplayer::GetNetHandle() const
{
	NetHandle13 netHandle;
	NETWORK_HANDLE_FROM_PLAYER(index, (Any*)&netHandle._0, 13);
	return netHandle;
}
ScrHandle GTAplayer::GetClanDescription() const
{
	ScrHandle clan = -1;
	ScrHandle netHandle[13];
	NETWORK_HANDLE_FROM_PLAYER(index, (Any*)netHandle, 13);
	NETWORK_CLAN_PLAYER_GET_DESC((Any*)&clan, 35, (Any*)netHandle);
	return clan;
}

bool GTAplayer::IsTalking() const
{
	return NETWORK_IS_PLAYER_TALKING(index) != 0;
}

bool GTAplayer::IsPressingHorn() const
{
	return IS_PLAYER_PRESSING_HORN(index) != 0;
}

bool GTAplayer::IsFreeAiming() const
{
	return IS_PLAYER_FREE_AIMING(index) != 0;
}
bool GTAplayer::IsFreeAimingAt(Entity entity) const
{
	return IS_PLAYER_FREE_AIMING_AT_ENTITY(index, entity) != 0;
}
bool GTAplayer::IsTargetingAnything() const
{
	return IS_PLAYER_TARGETTING_ANYTHING(index) != 0;
}
bool GTAplayer::IsTargetingAt(Entity entity) const
{
	return IS_PLAYER_TARGETTING_ENTITY(index, entity) != 0;
}
GTAentity GTAplayer::AimedEntity() const
{
	Entity target;
	if (GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(index, &target))
	{
		if (IS_ENTITY_A_PED(target))
		{
			if (IS_PED_SITTING_IN_ANY_VEHICLE(target))
				return GET_VEHICLE_PED_IS_IN(target, 0);
		}
		return target;
	}
	return 0;
}

INT GTAplayer::MaxArmour_get() const
{
	return GET_PLAYER_MAX_ARMOUR(index);
}

INT GTAplayer::WantedLevel_get() const
{
	return GET_PLAYER_WANTED_LEVEL(index);
}

void GTAplayer::GiveRagdollControl(bool value)
{
	GIVE_PLAYER_RAGDOLL_CONTROL(index, value);
}

bool GTAplayer::IsControlOn() const
{
	return IS_PLAYER_CONTROL_ON(index) != 0;
}
void GTAplayer::SetControl(bool toggle, int flag)
{
	SET_PLAYER_CONTROL(index, toggle, flag);
}



bool GTAplayer::operator == (const GTAplayer& other) const
{
	return this->index == other.index;
}



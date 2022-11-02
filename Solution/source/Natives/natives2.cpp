/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "natives2.h"

//#include "GTAmath.h"

#include <string>


Hash GET_HASH_KEY(char* value)
{
	size_t len = strlen(value);
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash; // joaat
}
Hash GET_HASH_KEY(const std::wstring& value)
{
	size_t len = value.length();
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
Hash GET_HASH_KEY(const std::string& value)
{
	size_t len = value.length();
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(value[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

void add_text_component_long_string(const std::string& text)
{
	const UINT8 maxStrComponentLength = 99;
	for (int i = 0; i < text.length(); i += maxStrComponentLength)
	{
		std::string& strComp = text.substr(i, min(text.length() - i, maxStrComponentLength));
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<PCHAR>(strComp.c_str()));
	}
}

bool IS_PED_SHOOTING(Ped ped) 
{
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
}

Entity IS_PLAYER_FREE_AIMING_AT_ENTITY(Player _, Entity ent)
{
	BOOL hit;
	Vector3 endCoords;
	Vector3 surfaceNormal;

	Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 dir = Vector3::RotationToDirection(rot);
	Vector3 farCoords;

	farCoords.x = camCoords.x + dir.x * 1000;
	farCoords.y = camCoords.y + dir.y * 1000;
	farCoords.z = camCoords.z + dir.z * 1000;

	int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, 0, 7);
	SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

	return hit ? ent : 0;
}


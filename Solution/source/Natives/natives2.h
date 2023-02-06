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

using namespace SYSTEM;
using namespace APP;
using namespace AUDIO;
using namespace BRAIN;
using namespace CAM;
using namespace CLOCK;
using namespace CUTSCENE;
using namespace DATAFILE;
using namespace DECORATOR;
using namespace DLC;
using namespace ENTITY;
using namespace EVENT;
using namespace FILES;
using namespace FIRE;
using namespace GRAPHICS;
using namespace HUD;
using namespace INTERIOR;
using namespace ITEMSET;
using namespace LOADINGSCREEN;
using namespace LOCALIZATION;
using namespace MISC;
using namespace MOBILE;
using namespace MONEY;
using namespace NETSHOPPING;
using namespace NETWORK;
using namespace OBJECT;
using namespace PAD;
using namespace PATHFIND;
using namespace PED;
using namespace PHYSICS;
using namespace PLAYER;
using namespace RECORDING;
using namespace REPLAY;
using namespace SAVEMIGRATION;
using namespace SCRIPT;
using namespace SECURITY;
using namespace SHAPETEST;
using namespace SOCIALCLUB;
using namespace STATS;
using namespace STREAMING;
using namespace TASK;
using namespace VEHICLE;
using namespace WATER;
using namespace WEAPON;
using namespace ZONE;

//#define WAIT scriptWait
static inline void WAIT(DWORD time)
{
	scriptWait(time);
}
static inline void TERMINATE()
{
	WAIT(MAXDWORD);
}

Hash GET_HASH_KEY(const char* value);
Hash GET_HASH_KEY(const std::wstring& value);
Hash GET_HASH_KEY(const std::string& value);

void add_text_component_long_string(const std::string& text);
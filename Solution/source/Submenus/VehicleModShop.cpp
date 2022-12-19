/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "VehicleModShop.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Util\StringManip.h"
#include "..\Scripting\enums.h"
#include "..\main.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\Game.h"
#include "..\Memory\GTAmemory.h"

#include "Settings.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>

namespace sub
{

	bool firsttime = true;
	bool lowersuspension = 0;
	int lastMod = -2;
	bool selectwheel = false;
	bool setwheel = false;
	bool selectmod = false;
	bool setMod = false;
	int lastpaint, lastpearl, lastr, lastg, lastb;
	bool menuselect = true, getpaint = true, iscustompaint;

	// Paints

	struct NamedVehiclePaint { std::string name; INT16 paint, pearl; };

#pragma region paintvectors
	std::vector<NamedVehiclePaint> PAINTS_NORMAL{

	};

	std::vector<NamedVehiclePaint> PAINTS_METALLIC{

	};

	std::vector<NamedVehiclePaint> PAINTS_MATTE{

	};

	std::vector<NamedVehiclePaint> PAINTS_METAL{

	};

	std::vector<NamedVehiclePaint> PAINTS_PEARL{

	};

	const std::vector<NamedVehiclePaint> PAINTS_WHEELS
	{
		{ "Default", 156, -1 },
		{ "Black", 0, -1 },
		{ "Carbon Black", 1, -1 },
		{ "Anthracite Black", 11, -1 },
		{ "Black Steel", 2, -1 },
		{ "Stone Silver", 8, -1 },
		{ "Frost White", 122, -1 },
		{ "Red", 27, -1 },
		{ "Blaze Red", 30, -1 },
		{ "Garnet Red", 45, -1 },
		{ "Candy Red", 35, -1 },
		{ "Sunset Red", 33, -1 },
		{ "Salmon Pink", 136, -1 },
		{ "Hot Pink", 135, -1 },
		{ "Sunrise Orange", 36, -1 },
		{ "Orange", 41, -1 },
		{ "Bright Orange", 138, -1 },
		{ "Gold", 37, -1 },
		{ "Straw Brown", 99, -1 },
		{ "Dark Copper", 90, -1 },
		{ "Dark Ivory", 95, -1 },
		{ "Dark Brown", 115, -1 },
		{ "Bronze", 109, -1 },
		{ "Dark Earth", 153, -1 },
		{ "Desert Tan", 154, -1 },
		{ "Yellow", 88, -1 },
		{ "Race Yellow", 89, -1 },
		{ "Yellow Bird", 91, -1 },
		{ "Lime Green", 55, -1 },
		{ "Pea Green", 125, -1 },
		{ "Green", 53, -1 },
		{ "Dark Green", 56, -1 },
		{ "Olive Green", 151, -1 },
		{ "Midnight Blue", 82, -1 },
		{ "Royal Blue", 64, -1 },
		{ "Baby Blue", 87, -1 },
		{ "Bright Blue", 70, -1 },
		{ "Flourescent Blue", 140, -1 },
		{ "Slate Blue", 81, -1 },
		{ "Schafter Purple", 145, -1 },
		{ "Midnight Purple", 142, -1 }
	};

	const std::vector<NamedVehiclePaint> PAINTS_UTIL
	{
		{ "Black", COLOR_UTIL_BLACK, -1 },
		{ "Black Poly", COLOR_UTIL_BLACK_POLY, -1 },
		{ "Dark Silver", COLOR_UTIL_DARK_SILVER, -1 },
		{ "Alloy", COLOR_METALS_DEFAULT_ALLOY, COLOR_METALS_DEFAULT_ALLOY },
		{ "Gun Metal", COLOR_UTIL_GUN_METAL, -1 },
		{ "Shadow Silver", COLOR_UTIL_SHADOW_SILVER, -1 },
		{ "Pearl Steel", COLOR_METALS_PEARLESCENT_STEEL, COLOR_METALS_PEARLESCENT_STEEL },
		{ "Pearl Gold", COLOR_METALS_PEARLESCENT_GOLD, -1 },
		{ "Red", COLOR_UTIL_RED, -1 },
		{ "Bright Red", COLOR_UTIL_BRIGHT_RED, -1 },
		{ "Garnet Red", COLOR_UTIL_GARNET_RED, -1 },
		{ "Midnight Blue", COLOR_UTIL_MIDNIGHT_BLUE, -1 },
		{ "Blue", COLOR_UTIL_BLUE, -1 },
		{ "Sea Foam Blue", COLOR_UTIL_SEA_FOAM_BLUE, -1 },
		{ "Lightning Blue", COLOR_UTIL_LIGHTNING_BLUE, -1 },
		{ "Police Blue", COLOR_CLASSIC_POLICE_BLUE, -1 },
		{ "Maui Blue", COLOR_UTIL_MAUI_BLUE_POLY, -1 },
		{ "Bright Blue", COLOR_UTIL_BRIGHT_BLUE, -1 },
		{ "Brown", COLOR_UTIL_BROWN, -1 },
		{ "Medium Brown", COLOR_UTIL_MEDIUM_BROWN, -1 },
		{ "Light Brown", COLOR_UTIL_LIGHT_BROWN, -1 },
		{ "Off White", COLOR_UTIL_OFF_WHITE, -1 },
		{ "Pure White", COLOR_CLASSIC_PURE_WHITE, COLOR_CLASSIC_PURE_WHITE }
	};

	const std::vector<NamedVehiclePaint> PAINTS_WORN
	{
		{ "Black", COLOR_WORN_BLACK, -1 },
		{ "Graphite", COLOR_WORN_GRAPHITE, -1 },
		{ "Silver Grey", COLOR_WORN_SILVER_GREY, -1 },
		{ "Silver", COLOR_WORN_SILVER, -1 },
		{ "Bluish Silver", COLOR_WORN_BLUE_SILVER, -1 },
		{ "Shadow Silver", COLOR_WORN_SHADOW_SILVER, -1 },
		{ "Red", COLOR_WORN_RED, -1 },
		{ "Golden Red", COLOR_WORN_GOLDEN_RED, -1 },
		{ "Dark Red", COLOR_WORN_DARK_RED, -1 },
		{ "Dark Green", COLOR_WORN_DARK_GREEN, -1 },
		{ "Green", COLOR_WORN_GREEN, -1 },
		{ "Sea Wash", COLOR_WORN_SEA_WASH, -1 },
		{ "Dark Blue", COLOR_WORN_DARK_BLUE, -1 },
		{ "Blue", COLOR_WORN_BLUE, -1 },
		{ "Baby Blue", COLOR_WORN_BABY_BLUE, -1 },
		{ "Honey Beige", COLOR_WORN_HONEY_BEIGE, -1 },
		{ "Brown", COLOR_WORN_BROWN, -1 },
		{ "Dark Brown", COLOR_WORN_DARK_BROWN, -1 },
		{ "Straw Beige", COLOR_WORN_STRAW_BEIGE, -1 },
		{ "White", COLOR_WORN_WHITE, -1 },
		{ "Off White", COLOR_WORN_OFF_WHITE, -1 },
		{ "Orange", COLOR_WORN_ORANGE, -1 },
		{ "Light Orange", COLOR_WORN_LIGHT_ORANGE, -1 },
		{ "Taxi Yellow", COLOR_WORN_TAXI_YELLOW, -1 },
		{ "Pale Orange", COLOR_WORN_PALE_ORANGE, -1 },
		{ "Olive Green", COLOR_WORN_ARMY_OLIVE_GREEN, -1 },

	};

	std::vector<NamedVehiclePaint> PAINTS_CHROME
	{

	};
	std::vector<NamedVehiclePaint> PAINTS_CHAMELEON
	{

	};
	std::vector<NamedVehiclePaint> PAINTS_ADDED
	{

	};

	INT paintIndex_maxValue = 0;

	INT8 selectedpainttype;
	INT8 lastwheeltype;
	INT8 lastfwheel;
	INT8 lastbwheel;

	void GetAllPaintIDs()
	{
		firsttime = false;
		Vehicle veh;
		DWORD model = GET_HASH_KEY("adder");
		STREAMING::REQUEST_MODEL(model);
		int timeC = 2500;
		ULONGLONG LoadMaxC = GetTickCount64() + timeC;
		while (!STREAMING::HAS_MODEL_LOADED(model))
		{
			if (GetTickCount64() > LoadMaxC)
			{
				Game::Print::PrintBottomCentre("Couldn't Load Model, returning");
				firsttime = true;
				break;
			}
			WAIT(0);
		}

		//spawn dummy vehicle
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -100.0);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		veh = CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 1, 0);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 5.0f);
		int painttype, colour, pearl, second;

		//Loop paint types (normal, metallic, matte etc...)
		for (painttype = 0; painttype < 7; painttype++)
		{
			int numcols = GET_NUM_MOD_COLORS(painttype, 0);
			const char* colourname;

			//loop colour options and assign to PAINTS_ vectors
			for (int i = 0; i < numcols; i++)
			{
				second = 0;
				auto& PaintList = PAINTS_ADDED;
				//set and get colour ID's and names
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, painttype, i, 0);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &second);
				VEHICLE::GET_VEHICLE_COLOURS(veh, &colour, &second);
				colourname = VEHICLE::_0xB45085B721EFD38C(veh, 0);
				std::string colourid = std::to_string(i);
				if (colour > paintIndex_maxValue)
					paintIndex_maxValue = colour;
				if (pearl > paintIndex_maxValue)
					paintIndex_maxValue = pearl;

				// write to relevant vector, depending on painttype
				switch (painttype)
				{
				case 0:
					PAINTS_METALLIC.resize(numcols);
					PAINTS_METALLIC[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_METALLIC[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_METALLIC[i].paint = colour;
					PAINTS_METALLIC[i].pearl = pearl;
					break;
				case 1:
					PAINTS_NORMAL.resize(numcols);
					PAINTS_NORMAL[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_NORMAL[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_NORMAL[i].paint = colour;
					PAINTS_NORMAL[i].pearl = pearl;
					break;
				case 2:
					PAINTS_PEARL.resize(numcols);
					PAINTS_PEARL[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_PEARL[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_PEARL[i].paint = -1;
					PAINTS_PEARL[i].pearl = colour;
					break;
				case 3:
					PAINTS_MATTE.resize(numcols);
					PAINTS_MATTE[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_MATTE[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_MATTE[i].paint = colour;
					PAINTS_MATTE[i].pearl = pearl;
					break;
				case 4:
					PAINTS_METAL.resize(numcols);
					PAINTS_METAL[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_METAL[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_METAL[i].paint = colour;
					PAINTS_METAL[i].pearl = pearl;
					break;
				case 5:
					PAINTS_CHROME.resize(numcols);
					PAINTS_CHROME[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_CHROME[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_CHROME[i].paint = colour;
					PAINTS_CHROME[i].pearl = pearl;
					break;
				case 6:
					PAINTS_CHAMELEON.resize(numcols);
					PAINTS_CHAMELEON[i].name = "Extra Colour " + colourid;
					if (colourname != nullptr)
					{
						PAINTS_CHAMELEON[i].name = Game::GetGXTEntry(colourname, "Extra Colour " + colourid);
					}

					PAINTS_CHAMELEON[i].paint = colour;
					PAINTS_CHAMELEON[i].pearl = pearl;
					break;
				}

			}
		}
		painttype = null;
		//unloading test vehicle from memory
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
		VEHICLE::DELETE_VEHICLE(&veh);


	}

	void AddMSPaintsPointOption_(const std::string& text, INT8 index, bool& extra_option_code = null)
	{
		bool pressed = false;
		AddOption(text, pressed, nullFunc, SUB::MSPAINTS2, true, false);
		if (pressed)
		{
			ms_curr_paint_index = index;
			extra_option_code = true;
			getpaint = true;
		}
	}
	INT getpaintCarUsing_index(Vehicle veh, INT partIndex_CustomK)
	{
		GTAvehicle vehicle(veh);

		switch (partIndex_CustomK)
		{
		case 1:
			return vehicle.PrimaryColour_get();
			break;
		case 2:
			return vehicle.SecondaryColour_get();
			break;
		case 3:
			return vehicle.PearlescentColour_get();
			break;
		case 4:
			return vehicle.RimColour_get();
			break;
		case 5:
			return vehicle.InteriorColour_get();
			break;
		case 6:
			return vehicle.DashboardColour_get();
			break;
		case 10:
			return _globalSpawnVehicle_PrimCol;
			break;
		case 11:
			return _globalSpawnVehicle_SecCol;
			break;
		}

		return 0;
	}
	void paintCarUsing_index(Vehicle veh, INT partIndex_CustomK, INT16 colour_index, INT16 pearl_index)
	{
		GTAvehicle vehicle(veh);
		if (vehicle.Exists())
			vehicle.RequestControlOnce();

		switch (partIndex_CustomK)
		{
		case 1:
			vehicle.ClearCustomPrimaryColour();
			vehicle.PrimaryColour_set(colour_index);
			if (pearl_index != -1)
				vehicle.PearlescentColour_set(pearl_index);
			break;
		case 2:
			vehicle.ClearCustomSecondaryColour();
			vehicle.SecondaryColour_set(colour_index);
			break;
		case 3:
			vehicle.PearlescentColour_set(colour_index);
			break;
		case 4:
			vehicle.RimColour_set(colour_index);
			break;
		case 5:
			vehicle.InteriorColour_set(colour_index);
			break;
		case 6:
			vehicle.DashboardColour_set(colour_index);
			break;
		case 10:
			_globalSpawnVehicle_PrimCol = colour_index;
			break;
		case 11:
			_globalSpawnVehicle_SecCol = colour_index;
			break;
		}

	}

	void AddcarcolOption_(const std::string& text, Vehicle vehicle, INT16 colour_index, INT16 pearl_index_ifPrimary)
	{
		INT currPaintInd;
		currPaintInd = getpaintCarUsing_index(vehicle, ms_curr_paint_index);

		bool pressed = false;

		if (_globalLSC_Customs)
		{
			if (getpaint)
			{
				lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(Static_12, 3);
				if (ms_curr_paint_index == 1)
				{
					if (GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Static_12))
					{
						iscustompaint = true;
						GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12, &lastr, &lastg, &lastb);
					}
				}
				if (ms_curr_paint_index == 2)
				{
					if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Static_12))
					{
						iscustompaint = true;
						GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12, &lastr, &lastg, &lastb);
					}
				}
				getpaint = false;
			}

			std::vector<NamedVehiclePaint> THISMENUPAINT
			{

			};
			switch (selectedpainttype)
			{
			case 0:
				THISMENUPAINT = PAINTS_ADDED;
				break;
			case 1:
				THISMENUPAINT = PAINTS_CHROME;
				break;
			case 2:
				THISMENUPAINT = PAINTS_NORMAL;
				break;
			case 3:
				THISMENUPAINT = PAINTS_MATTE;
				break;
			case 4:
				THISMENUPAINT = PAINTS_METALLIC;
				break;
			case 5:
				THISMENUPAINT = PAINTS_METAL;
				break;
			case 6:
				THISMENUPAINT = PAINTS_CHAMELEON;
				break;
			case 7:
				THISMENUPAINT = PAINTS_UTIL;
				break;
			case 8:
				THISMENUPAINT = PAINTS_WORN;
				break;
			case 9: default:
				THISMENUPAINT = PAINTS_WHEELS;
				break;
			}

			AddTickol(text, lastpaint == colour_index, pressed, pressed,
				IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING);
			{
				if (IS_ENTITY_A_VEHICLE(vehicle) && menuselect || ms_curr_paint_index == 10 || ms_curr_paint_index == 11)
					paintCarUsing_index(vehicle, ms_curr_paint_index, THISMENUPAINT[*Menu::currentopATM - 1].paint, THISMENUPAINT[*Menu::currentopATM - 1].pearl);
			}

			if (pressed)
			{
				//lastpaint = getpaintCarUsing_index(vehicle, ms_curr_paint_index);
				//lastpearl = getpaintCarUsing_index(vehicle, 3);
				//getpaint = true;
				menuselect = false;
				//if (IS_ENTITY_A_VEHICLE(vehicle) || ms_curr_paint_index == 10 || ms_curr_paint_index == 11)
					//paintCarUsing_index(vehicle, ms_curr_paint_index, lastpaint, lastpearl);
				Menu::SetSub_previous();
				WAIT(10);
				return;
			}
			if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back))
			{
				//getpaint = true;
				menuselect = false;
				if (IS_ENTITY_A_VEHICLE(vehicle) || ms_curr_paint_index == 10 || ms_curr_paint_index == 11)
					paintCarUsing_index(vehicle, ms_curr_paint_index, lastpaint, lastpearl);
				if (iscustompaint)
				{
					if (ms_curr_paint_index == 1)
						SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,lastr, lastg, lastb);
					else if (ms_curr_paint_index == 2)
						SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,lastr, lastg, lastb);
				}
			}
		}
		else
		{
			AddTickol(text, currPaintInd == colour_index, pressed, pressed,
				IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING); if (pressed)
			{
				if (IS_ENTITY_A_VEHICLE(vehicle) || ms_curr_paint_index == 10 || ms_curr_paint_index == 11)
					paintCarUsing_index(vehicle, ms_curr_paint_index, colour_index, pearl_index_ifPrimary);
			}
		}
	}
	/*void AddcarcolModOption_(const std::string& text, Vehicle vehicle, INT16 part, INT16 type, INT paint)
	{
		INT currPaintType, currPaintIndex;
		getpaintCarUsing_index(vehicle, true, currPaintType, currPaintIndex);

		bool pressed = false;
		AddTickol(text, currPaintType == type && currPaintIndex == paint, pressed, pressed,
			IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING); if (pressed)
		{
			if (IS_ENTITY_A_VEHICLE(vehicle) || ms_curr_paint_index == 10 || ms_curr_paint_index == 11)
				paintCarUsing_index(vehicle, 0, true, part, type, paint);
		}
	}*/



	void MSPaints_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		float paintFade = _GET_VEHICLE_PAINT_FADE(Static_12);
		float dirtLevel = GET_VEHICLE_DIRT_LEVEL(Static_12);
		float carvarcol = GET_VEHICLE_COLOUR_COMBINATION(Static_12)+1;
		bool set_mspaints_index_4 = 0, set_mspaints_index_3 = 0,
			set_mspaints_index_5 = 0, set_mspaints_index_6 = 0,
			paintFade_plus = 0, paintFade_minus = 0,
			dirtLevel_plus = 0, dirtLevel_minus = 0,
			carvarcol_plus = 0, carvarcol_minus = 0;
		getpaint = true;
		menuselect = true;

				AddTitle("Paints");
		AddMSPaintsPointOption_(Game::GetGXTEntry("CMOD_COL0_0", "Primary"), 1); // Primary CMOD_COL0_0
		 //if (_DOES_VEHICLE_HAVE_SECONDARY_COLOUR(Static_12))
		AddMSPaintsPointOption_(Game::GetGXTEntry("CMOD_COL0_1", "Secondary"), 2); // Secondary CMOD_COL0_1
		AddOption(Game::GetGXTEntry("CMOD_COL1_6", "Pearlescent"), set_mspaints_index_3, nullFunc, SUB::MSPAINTS2_WHEELS, true, false); // Pearlescent CMOD_COL1_6
		AddOption(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels"), set_mspaints_index_4, nullFunc, -1, true);
		AddOption("Interior Colour", set_mspaints_index_5, nullFunc, SUB::MSPAINTS2, true);
		AddOption("Dashboard Colour", set_mspaints_index_6, nullFunc, SUB::MSPAINTS2,true);


		AddBreak("---Collateral---");
		AddNumber("Paint Fade", paintFade, 2, null, paintFade_plus, paintFade_minus);
		AddNumber("Dirt Level", dirtLevel, 2, null, dirtLevel_plus, dirtLevel_minus);
		AddNumber("CarVariation Colours", carvarcol, 0, null, carvarcol_plus, carvarcol_minus);

		if (firsttime)
		{
			GetAllPaintIDs();
		}

		if (set_mspaints_index_3) {
			ms_curr_paint_index = 3;
			//int paintType, paintCol, paint3;
			//GET_VEHICLE_MOD_COLOR_1(Static_12, &paintType, &paintCol, &paint3);
			//if (/*paintType != 3 &&*/ paintType != 4 && paintType != 5) Menu::SetSub_new(SUB::MSPAINTS2_WHEELS);
			//else Game::Print::PrintBottomCentre("~r~Error:~s~ Pearlescent cannot be applied over the current paint type.");
			return;
		}

		if (set_mspaints_index_4) {
			ms_curr_paint_index = 4;
			if (GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels) < 0)
				Game::Print::PrintBottomCentre("~b~Note:~s~ Colours cannot always be applied to stock wheels.");
			Menu::SetSub_new(SUB::MSPAINTS2_WHEELS);
			return;
		}

		if (set_mspaints_index_5) {
			ms_curr_paint_index = 5;
			return;
		}

		if (set_mspaints_index_6) {
			ms_curr_paint_index = 6;
			return;
		}

		if (paintFade_plus)
		{
			if (paintFade < 1.0f) 
				paintFade += 0.02f;
			_SET_VEHICLE_PAINT_FADE(Static_12, paintFade);
		}
		if (paintFade_minus)
		{
			if (paintFade > 0.02f) 
				paintFade -= 0.02f;
			_SET_VEHICLE_PAINT_FADE(Static_12, paintFade);
		}

		if (dirtLevel_plus)
		{
			if (dirtLevel < 15.0f)
			{
				dirtLevel += 0.1f;
				SET_VEHICLE_DIRT_LEVEL(Static_12, dirtLevel);
			}
		}
		if (dirtLevel_minus)
		{
			if (dirtLevel > 0.0f)
			{
				dirtLevel -= 0.1f;
				SET_VEHICLE_DIRT_LEVEL(Static_12, dirtLevel);
			}
		}

		if (carvarcol_plus)
		{
			if (carvarcol < GET_NUMBER_OF_VEHICLE_COLOURS(Static_12))
			{
				carvarcol += 1;
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol-1);
			}
			else
			{
				carvarcol = 1;
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol-1);
			}
		}
		if (carvarcol_minus)
		{
			if (carvarcol > 1)
			{
				carvarcol -= 1;
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol-1);
			}
			else
			{
				carvarcol = GET_NUMBER_OF_VEHICLE_COLOURS(Static_12);
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol-1);
			}
		}
	}
	void MSPaints2_()
	{
		bool paintIndex_plus = 0, paintIndex_minus = 0, paintIndex_input = 0,
			MSPaints_RIndex = 0,
			MSPaints_RColour = 0,
			MSPaints_primRGB = 0,
			copypaint = 0;
		
		menuselect = true;
		
		GTAvehicle vehicle = Static_12;

		INT paintIndex;
		paintIndex = getpaintCarUsing_index(Static_12, ms_curr_paint_index);

		int totalpaints = 49;
		for (int i = 0; i < 6; i++)
		{
			if (i != 2)
			{
				totalpaints = totalpaints + GET_NUM_MOD_COLORS(i, 1);
			}
		}
		int extrapaints = totalpaints - 225;

		switch (ms_curr_paint_index)
		{
		case 1: case 10: AddTitle(Game::GetGXTEntry("CMOD_COL0_0", "Primary")); break;
		case 2: case 11: AddTitle(Game::GetGXTEntry("CMOD_COL0_1", "Secondary")); break;
		case 3: AddTitle(Game::GetGXTEntry("CMOD_COL1_6", "Pearlescent")); break;
		case 5: AddTitle("Interior"); break;
		case 6: AddTitle("Dashboard"); break;
		case 4: default: AddTitle(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels")); break;
		}

		switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
		{
		case SUB::SPAWNVEHICLE_OPTIONS:
			INT16* carColSettingPtr = (ms_curr_paint_index == 10 ? &_globalSpawnVehicle_PrimCol : &_globalSpawnVehicle_SecCol);
			bool bCarColSettingToNullPressed = false;
			AddTickol("None (Default)", *carColSettingPtr == -3, bCarColSettingToNullPressed, bCarColSettingToNullPressed); if (bCarColSettingToNullPressed) *carColSettingPtr = -3;
			break;
		}

		AddOption("Chrome", null, nullFunc, SUB::MSPAINTS2_CHROME, true, true); // CMOD_COL1_0
		AddOption("Classic", null, nullFunc, SUB::MSPAINTS2_NORMAL, true, true); // CMOD_COL1_1
		AddOption("Matte", null, nullFunc, SUB::MSPAINTS2_MATTE, true, true); // CMOD_COL1_5
		AddOption("Metallic", null, nullFunc, SUB::MSPAINTS2_METALLIC, true, true); // CMOD_COL1_3
		AddOption("Metal", null, nullFunc, SUB::MSPAINTS2_METAL, true, true); // CMOD_COL1_4
		AddOption("Chameleon", null, nullFunc, SUB::MSPAINTS2_CHAMELEON, true, true); // CMOD_COL1_4
		AddOption("Utility", null, nullFunc, SUB::MSPAINTS2_UTIL);
		AddOption("Worn", null, nullFunc, SUB::MSPAINTS2_WORN);

		/* (extrapaints > 0)
		{
			AddOption("Extra Colours: " + std::to_string(extrapaints), null, nullFunc, SUB::MSPAINTS2_ADDED);
		}*/
		if (ms_curr_paint_index < 10)
		{
			AddNumber("Paint Index", paintIndex, 0, paintIndex_input, paintIndex_plus, paintIndex_minus);
		}

		AddOption("Random Index", MSPaints_RIndex);

		std::string painttypeswitch;
		if (ms_curr_paint_index == 1 || ms_curr_paint_index == 2)
		{
			AddOption("Random RGB", MSPaints_RColour);
			AddOption("Set RGB", MSPaints_primRGB, nullFunc, SUB::MSPAINTS_RGB);
			if (*Menu::currentopATM == Menu::printingop)
				Add_preset_colour_options_previews(ms_curr_paint_index == 1 ? vehicle.CustomPrimaryColour_get() : ms_curr_paint_index == 2 ? vehicle.CustomSecondaryColour_get() : RgbS(0, 0, 0));
			ms_curr_paint_index == 1 ? painttypeswitch = "Secondary" : painttypeswitch = "Primary";
			AddOption("Copy to " + painttypeswitch, copypaint);
		}

		if (MSPaints_RIndex) {
			if (vehicle.IsVehicle())
			{
				int randindex = rand() % paintIndex_maxValue;
				paintCarUsing_index(Static_12, ms_curr_paint_index, randindex, -1);
				getpaint = true;
			}
			return;
		}
		if (MSPaints_RColour) {
			if (vehicle.IsVehicle())
			{
				int randr = rand() % 255;
				int randg = rand() % 255;
				int randb = rand() % 255;
				paintCarUsing_index(Static_12, ms_curr_paint_index, 0, -1);
				if (ms_curr_paint_index == 1)
					vehicle.CustomPrimaryColour_set(randr, randg, randb);
				else if (ms_curr_paint_index == 2)
					vehicle.CustomSecondaryColour_set(randr, randg, randb);
				getpaint = true;
			}
			return;
		}

		if (ms_curr_paint_index == 1) { if (MSPaints_primRGB) { bit_MSPaints_RGB_mode = 0; return; } }
		else if (ms_curr_paint_index == 2) { if (MSPaints_primRGB) { bit_MSPaints_RGB_mode = 1; return; } }



		if (paintIndex_plus) {
			if (paintIndex < paintIndex_maxValue) paintIndex++;
			else paintIndex = 0;
			paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
			if (_globalLSC_Customs)
			{
				lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(Static_12, 3);
			}
			return;
		}
		if (paintIndex_minus) {
			if (paintIndex > 0) paintIndex--;
			else paintIndex = paintIndex_maxValue;
			paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
			if (_globalLSC_Customs)
			{
				lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(Static_12, 3);
			}
			return;
		}
		if (paintIndex_input) {
			std::string inputStr = Game::InputBox("", 4U, "Enter a paint index:", std::to_string(paintIndex));
			if (inputStr.length() > 0)
			{
				try
				{
					paintIndex = stoi(inputStr);
					paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
					if (_globalLSC_Customs)
					{
						lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
						lastpearl = getpaintCarUsing_index(Static_12, 3);
					}
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsPaintIndex, std::string(), 3U, "Enter a paint index:", std::to_string(paintIndex));
			//OnscreenKeyboard::State::arg1._int = Static_12;
			//OnscreenKeyboard::State::arg2._int = paintIndex;
		}
		if (copypaint)
		{
			paintCarUsing_index(Static_12, 3 - ms_curr_paint_index, getpaintCarUsing_index(Static_12, ms_curr_paint_index), -1);
			switch (ms_curr_paint_index)
			{
			case 1:
				if (GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Static_12))
				{
					auto& copy = vehicle.CustomPrimaryColour_get();
					vehicle.CustomSecondaryColour_set(copy.R ,copy.G, copy.B);
				}
				break;
			case 2:
				if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Static_12))
				{
					auto& copy = vehicle.CustomSecondaryColour_get();
					vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			}
		}


	}

	namespace MSPaints_catind
	{

#pragma endregion

		void Sub_Wheels()
		{
			INT paintIndex;

			paintIndex = getpaintCarUsing_index(Static_12, ms_curr_paint_index);

			switch (ms_curr_paint_index)
			{
			case 1: case 10: AddTitle(Game::GetGXTEntry("CMOD_COL0_0", "Primary")); break;
			case 2: case 11: AddTitle(Game::GetGXTEntry("CMOD_COL0_1", "Secondary")); break;
			case 3: AddTitle(Game::GetGXTEntry("CMOD_COL1_6", "Pearlescent")); break;
			case 5: AddTitle("Interior"); break;
			case 6: AddTitle("Dashboard"); break;
			case 4: default: AddTitle(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels")); break;
			}

			auto& vPaints = PAINTS_WHEELS;
			selectedpainttype = 9;
			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

			int totalpaints = 0;
			for (int i = 0; i < 5; i++)
			{
				totalpaints = totalpaints + GET_NUM_MOD_COLORS(i, 1);
			}
			int extrapaints = totalpaints - 232;

			bool paintIndex_plus = 0, paintIndex_minus = 0, paintIndex_input = 0;
			AddNumber("Paint Index", paintIndex, 0, paintIndex_input, paintIndex_plus, paintIndex_minus);
			const INT paintIndex_maxValue = 160 + extrapaints;
			if (paintIndex_plus) {
				if (paintIndex < paintIndex_maxValue) paintIndex++;
				else paintIndex = 0;
				paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
				return;
			}
			if (paintIndex_minus) {
				if (paintIndex > 0) paintIndex--;
				else paintIndex = paintIndex_maxValue;
				paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
				return;
			}
			if (paintIndex_input) {
				std::string inputStr = Game::InputBox("", 4U, "Enter a paint index:", std::to_string(paintIndex));
				if (inputStr.length() > 0)
				{
					try
					{
						paintIndex = stoi(inputStr);
						paintCarUsing_index(Static_12, ms_curr_paint_index, paintIndex, -1);
					}
					catch (...)
					{
						Game::Print::PrintError_InvalidInput();
					}
				}
				return;
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsPaintIndex, std::string(), 3U, "Enter a paint index:", std::to_string(paintIndex));
				//OnscreenKeyboard::State::arg1._int = Static_12;
				//OnscreenKeyboard::State::arg2._int = paintIndex;
			}



		}
		void Sub_Added()
		{
			AddTitle("Extra Colours");

			auto& vPaints = PAINTS_ADDED;
			selectedpainttype = 0;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		void Sub_Chrome()
		{
			AddTitle("Chrome");
			selectedpainttype = 1;

			auto& vPaints = PAINTS_CHROME;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		void Sub_Normal()
		{
			AddTitle("Classic");
			selectedpainttype = 2;

			auto& vPaints = PAINTS_NORMAL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		void Sub_Matte()
		{
			AddTitle("Matte");
			selectedpainttype = 3;

			auto& vPaints = PAINTS_MATTE;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		void Sub_Metallic()
		{
			AddTitle("Metallic");
			selectedpainttype = 4;

			auto& vPaints = PAINTS_METALLIC;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		void Sub_Metal()
		{
			AddTitle("Metal");
			selectedpainttype = 5;

			auto& vPaints = PAINTS_METAL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		void Sub_Chameleon()
		{
			AddTitle("Chameleon");
			selectedpainttype = 6;

			auto& vPaints = PAINTS_CHAMELEON;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		void Sub_Util()
		{
			AddTitle("Utility");
			selectedpainttype = 7;

			auto& vPaints = PAINTS_UTIL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		void Sub_Worn()
		{
			AddTitle("Worn");
			selectedpainttype = 8;

			auto& vPaints = PAINTS_WORN;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
	}

	void rgb_mode_set_carcol(Vehicle veh, INT16 R, INT16 G, INT16 B, INT16 A)
	{
		GTAvehicle vehicle(veh);
		if (vehicle.IsVehicle())
		{
			vehicle.RequestControlOnce();
			if (GET_VEHICLE_MOD_KIT(vehicle.GetHandle()) != 0)
				SET_VEHICLE_MOD_KIT(vehicle.GetHandle(), 0);
		}

		switch (bit_MSPaints_RGB_mode)
		{
		case 0: vehicle.CustomPrimaryColour_set(R, G, B);
			break;
		case 1: vehicle.CustomSecondaryColour_set(R, G, B);
			break;
		case 2: vehicle.NeonLightsColour_set(R, G, B);
			break;
		case 3:
			_global_MultiPlatNeons_Col.R = R;
			_global_MultiPlatNeons_Col.G = G;
			_global_MultiPlatNeons_Col.B = B;
			break;
		case 4:
			vehicle.ToggleMod(VehicleMod::TireSmoke, true);
			vehicle.TyreSmokeColour_set(R, G, B);
			break;

			/*case 7: GET_PLAYER_PARACHUTE_TINT_INDEX(Static_240, &inull); _SET_PLAYER_PARACHUTE_SMOKE_COLOUR(Static_240, R, G, B);
			_SET_PLAYER_PARACHUTE_SMOKE_ENABLED(Static_240, 1); REMOVE_WEAPON_FROM_PED(GET_PLAYER_PED(Static_240), GADGET_PARACHUTE);
			GIVE_WEAPON_TO_PED(GET_PLAYER_PED(Static_240), GADGET_PARACHUTE, 1, 0, 0); SET_PLAYER_PARACHUTE_TINT_INDEX(Static_240, inull); break;*/
		case 7:
			SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Static_240, R, G, B);
			SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Static_240, TRUE);
			break;

		case 9:
			_globalSpawnVehicle_neonCol = RgbS(R, G, B);
			break;
		case 10:
			_SET_HUD_COLOUR(Static_12, R, G, B, A);
			break;
		}

	}
	void MSPaints_RGB()
	{
		int ms_paints_rgb_r = 0,
			ms_paints_rgb_g = 0,
			ms_paints_rgb_b = 0,
			ms_paints_rgb_a = -1,
			ms_paints_finish{};
		bool ms_paints_rgb_r_custom = 0,
			ms_paints_rgb_r_plus = 0,
			ms_paints_rgb_r_minus = 0,
			ms_paints_rgb_g_custom = 0,
			ms_paints_rgb_g_plus = 0,
			ms_paints_rgb_g_minus = 0,
			ms_paints_rgb_b_custom = 0,
			ms_paints_rgb_b_plus = 0,
			ms_paints_rgb_b_minus = 0,
			ms_paints_rgb_a_custom = 0,
			ms_paints_rgb_a_plus = 0,
			ms_paints_rgb_a_minus = 0,
			ms_paints_hexinput = 0,
			settings_hud_c_custom = 0,
			settings_hud_c_plus = 0,
			settings_hud_c_minus = 0,
			ms_paints_finish_plus = 0,
			ms_paints_finish_minus = 0;

		GTAvehicle vehicle = Static_12;

		const std::vector<NamedVehiclePaint> PAINTS_FINISH
		{
			{ "Standard Metallic", 2, -1 },
			{ "Dark Metallic", 0, -1 },
			{ "Bright Metallic", 111, -1 },
			{ "Matte", 12, -1 },
			{ "Util", 15, -1 },
			{ "Worn", 21, -1 },
			{ "Brushed Metal", 117, -1 },
			{ "Pure Chrome", 120, -1 },
			{ "Coloured Chrome", 158, -1 },
			{ "Satin", 159, -1 },
		};

		const std::vector<std::string> PAINTS_FINISH_NAMES
		{
			{ "Standard Metallic"},
			{ "Dark Metallic"},
			{ "Bright Metallic"},
			{ "Matte"},
			{ "Util"},
			{ "Worn"},
			{ "Brushed Metal"},
			{ "Pure Chrome"},
			{ "Coloured Chrome"},
			{ "Satin"},
		};

		if (bit_MSPaints_RGB_mode == 0 || bit_MSPaints_RGB_mode == 1)
		{
			switch (getpaintCarUsing_index(Static_12, ms_curr_paint_index))
			{
			case 0:
				ms_paints_finish = 1;
				break;
			case 111:
				ms_paints_finish = 2;
				break;
			case 12:
				ms_paints_finish = 3;
				break;
			case 15:
				ms_paints_finish = 4;
				break;
			case 21:
				ms_paints_finish = 5;
				break;
			case 117:
				ms_paints_finish = 6;
				break;
			case 120:
				ms_paints_finish = 7;
				break;
			case 158:
				ms_paints_finish = 8;
				break;
			case 159:
				ms_paints_finish = 9;
				break;
			case 2: default:
				ms_paints_finish = 0;
				break;
			}
		}

		switch (bit_MSPaints_RGB_mode)
		{
		case 0: GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;
		case 1: GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;
		case 2: _GET_VEHICLE_NEON_LIGHTS_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;
		case 3: ms_paints_rgb_r = _global_MultiPlatNeons_Col.R; ms_paints_rgb_g = _global_MultiPlatNeons_Col.G; ms_paints_rgb_b = _global_MultiPlatNeons_Col.B; break;
		case 4: GET_VEHICLE_TYRE_SMOKE_COLOR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;

		case 7: GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Static_240/*idk so ja*/, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;

		case 9: ms_paints_rgb_r = _globalSpawnVehicle_neonCol.R; ms_paints_rgb_g = _globalSpawnVehicle_neonCol.G; ms_paints_rgb_b = _globalSpawnVehicle_neonCol.B; break;
		case 10: GET_HUD_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b, &ms_paints_rgb_a); break;
		}
		AddTitle("Set Colour");
		if(bit_MSPaints_RGB_mode == 0 || bit_MSPaints_RGB_mode == 1)
			AddTexter("Paint Finish", ms_paints_finish, PAINTS_FINISH_NAMES, null , ms_paints_finish_plus, ms_paints_finish_minus);
		AddNumber("Red", ms_paints_rgb_r, 0, ms_paints_rgb_r_custom, ms_paints_rgb_r_plus, ms_paints_rgb_r_minus);

		switch (*Menu::currentopATM)
		{
		case 1:case 2:case 3:
			Add_preset_colour_options_previews(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b);
			break;
		}

		AddNumber("Green", ms_paints_rgb_g, 0, ms_paints_rgb_g_custom, ms_paints_rgb_g_plus, ms_paints_rgb_g_minus);
		AddNumber("Blue", ms_paints_rgb_b, 0, ms_paints_rgb_b_custom, ms_paints_rgb_b_plus, ms_paints_rgb_b_minus);
		if (ms_paints_rgb_a != -1) AddNumber("Opacity", ms_paints_rgb_a, 0, ms_paints_rgb_a_custom, ms_paints_rgb_a_plus, ms_paints_rgb_a_minus);
		AddTexter("HUD Colour", settings_hud_c, HudColour::vHudColours, settings_hud_c_custom, settings_hud_c_plus, settings_hud_c_minus);
		AddOption("~b~Input~s~ Hex Code", ms_paints_hexinput);

		AddBreak("---Presets---");
		if (Add_preset_colour_options(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b))
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);

		if (ms_paints_rgb_r_plus) {
			if (ms_paints_rgb_r < 255) ms_paints_rgb_r++;
			else ms_paints_rgb_r = 0;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_r_minus) {
			if (ms_paints_rgb_r > 0) ms_paints_rgb_r--;
			else ms_paints_rgb_r = 255;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_r_custom) {
			std::string inputStr = Game::InputBox("", 4U, "", std::to_string(ms_paints_rgb_r));
			if (inputStr.length() > 0)
			{
				try
				{
					int newVal = abs(stoi(inputStr));
					if (newVal < 0 || newVal > 255)
						throw;
					ms_paints_rgb_r = newVal;
					rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsRgbR, std::string(), 3U, std::string(), std::to_string(ms_paints_rgb_r));
			//OnscreenKeyboard::State::arg1._int = Static_12;
			//OnscreenKeyboard::State::arg2._uint = RGBA(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a).ToArgb();
			return;
		}

		if (ms_paints_rgb_g_plus) {
			if (ms_paints_rgb_g < 255) ms_paints_rgb_g++;
			else ms_paints_rgb_g = 0;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_g_minus) {
			if (ms_paints_rgb_g > 0) ms_paints_rgb_g--;
			else ms_paints_rgb_g = 255;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_g_custom) {
			std::string inputStr = Game::InputBox("", 4U, "", std::to_string(ms_paints_rgb_g));
			if (inputStr.length() > 0)
			{
				try
				{
					int newVal = abs(stoi(inputStr));
					if (newVal < 0 || newVal > 255)
						throw;
					ms_paints_rgb_g = newVal;
					rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsRgbG, std::string(), 3U, std::string(), std::to_string(ms_paints_rgb_g));
			//OnscreenKeyboard::State::arg1._int = Static_12;
			//OnscreenKeyboard::State::arg2._uint = RGBA(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a).ToArgb();
			return;
		}

		if (ms_paints_rgb_b_plus) {
			if (ms_paints_rgb_b < 255) ms_paints_rgb_b++;
			else ms_paints_rgb_b = 0;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_b_minus) {
			if (ms_paints_rgb_b > 0) ms_paints_rgb_b--;
			else ms_paints_rgb_b = 255;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_b_custom) {
			std::string inputStr = Game::InputBox("", 4U, "", std::to_string(ms_paints_rgb_b));
			if (inputStr.length() > 0)
			{
				try
				{
					int newVal = abs(stoi(inputStr));
					if (newVal < 0 || newVal > 255)
						throw;
					ms_paints_rgb_b = newVal;
					rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsRgbB, std::string(), 3U, std::string(), std::to_string(ms_paints_rgb_b));
			//OnscreenKeyboard::State::arg1._int = Static_12;
			//OnscreenKeyboard::State::arg2._uint = RGBA(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a).ToArgb();
			return;
		}

		if (ms_paints_rgb_a_plus) {
			if (ms_paints_rgb_a < 255) ms_paints_rgb_b++;
			else ms_paints_rgb_a = 0;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_a_minus) {
			if (ms_paints_rgb_a > 0) ms_paints_rgb_a--;
			else ms_paints_rgb_a = 255;
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_rgb_a_custom) {
			std::string inputStr = Game::InputBox("", 4U, "", std::to_string(ms_paints_rgb_a));
			if (inputStr.length() > 0)
			{
				try
				{
					int newVal = abs(stoi(inputStr));
					if (newVal < 0 || newVal > 255)
						throw;
					ms_paints_rgb_a = newVal;
					rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsRgbA, std::string(), 3U, std::string(), std::to_string(ms_paints_rgb_a));
			//OnscreenKeyboard::State::arg1._int = Static_12;
			//OnscreenKeyboard::State::arg2._uint = RGBA(ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a).ToArgb();
			return;
		}

		if (ms_paints_hexinput)
		{
			std::size_t hexcheck;
			std::string titlestring;
			std::string hexr = int_to_hexstring(ms_paints_rgb_r, false);
			std::string hexg = int_to_hexstring(ms_paints_rgb_g, false);
			std::string hexb = int_to_hexstring(ms_paints_rgb_b, false);
			if (hexr.length() == 1)
				hexr = "0" + hexr;
			if (hexg.length() == 1)
				hexg = "0" + hexg;
			if (hexb.length() == 1)
				hexb = "0" + hexb;
			titlestring = hexr + hexg + hexb;
			std::string inputStr = Game::InputBox("", 6U, "", titlestring);
			if (inputStr.length() == 6)
			{
				try
				{	
					hexcheck = inputStr.find_first_not_of("0123456789abcdef");
					if (hexcheck == std::string::npos)
					{
						ms_paints_rgb_r = std::stoul(inputStr.substr(0, 2), nullptr, 16);
						ms_paints_rgb_g = std::stoul(inputStr.substr(2, 2), nullptr, 16);
						ms_paints_rgb_b = std::stoul(inputStr.substr(4, 2), nullptr, 16);
						rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, 255);
					}
					else
						Game::Print::PrintError_InvalidInput();
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			else
				Game::Print::PrintError_InvalidInput();			
		}

		if (settings_hud_c_plus) {
			if (settings_hud_c < HudColour::vHudColours.size() - 1) settings_hud_c++;
			else settings_hud_c = 0;
			return;
		}
		if (settings_hud_c_minus) {
			if (settings_hud_c > 0) settings_hud_c--;
			else settings_hud_c = 180;
			return;
		}
		if (settings_hud_c_custom) {
			/*int tempHash = settings_hud_c;
			try{ tempHash = abs(stoi(Game::InputBox(std::to_string(settings_hud_c)))); }
			catch (...){ tempHash = settings_hud_c; }
			if (!(tempHash >= 0 && tempHash <= 180)) Game::Print::PrintError_InvalidInput();
			else
			{
			settings_hud_c = tempHash;
			GET_HUD_COLOUR(settings_hud_c, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b, &inull);
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b);
			}*/
			GET_HUD_COLOUR(settings_hud_c, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b, &inull);
			rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
			return;
		}
		if (ms_paints_finish_plus)
		{
			if (ms_paints_finish < 9)
				ms_paints_finish++;
			else
				ms_paints_finish = 0;
			switch (ms_curr_paint_index)
			{
			case 1:	
			{
				auto& copy = vehicle.CustomPrimaryColour_get();
				paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
				vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				break;
			}
			case 2:	
			{
				auto& copy = vehicle.CustomSecondaryColour_get();
				paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
				vehicle.CustomSecondaryColour_set(copy.R, copy.G, copy.B);
				break;
			}
			}
		}
		if (ms_paints_finish_minus)
		{
			if (ms_paints_finish > 0)
				ms_paints_finish--;
			else
				ms_paints_finish = 9;
			switch (ms_curr_paint_index)
			{
			case 1:
				if (GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Static_12))
				{
					auto& copy = vehicle.CustomPrimaryColour_get();
					paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
					vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			case 2:
				if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Static_12))
				{
					auto& copy = vehicle.CustomSecondaryColour_get();
					paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
					vehicle.CustomSecondaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			}
		}
	}

	// vehicle - upgrades
	void set_vehicle_max_upgrades(Vehicle vehicle, bool upgradeIt, bool invincible, INT8 plateType, std::string plateText,

		bool neonIt, UINT8 NeonR, UINT8 NeonG, UINT8 NeonB, INT16 prim_col_index, INT16 sec_col_index)
	{
		if (!DOES_ENTITY_EXIST(vehicle) || !IS_ENTITY_A_VEHICLE(vehicle))
			return;
		srand(time(0));
		int i;
		Vector3& Pos = GET_ENTITY_COORDS(vehicle, 1);

		GTAvehicle(vehicle).RequestControl();

		if (GET_VEHICLE_MOD_KIT(vehicle) != 0)
			SET_VEHICLE_MOD_KIT(vehicle, 0);

		if (invincible)
			set_vehicle_invincible_on(vehicle);
		else
			set_vehicle_invincible_off(vehicle);

		if (plateText.length() > 0)
			SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, (PCHAR)plateText.c_str());

		SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, plateType);


		if (upgradeIt) // upgrade
		{
			TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
			TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
			TOGGLE_VEHICLE_MOD(vehicle, 22, 1);

			for (i = 0; i < vValues_ModSlotNames.size(); i++)
			{
				if (i >= 17 && i <= 22)
					continue;
				if (i == 24)
				{
					UINT8 modIndex = GET_VEHICLE_MOD(vehicle, 23);
					SET_VEHICLE_MOD(vehicle, i, modIndex, 0);
					continue;
				}
				UINT8 modIndex = GET_NUM_VEHICLE_MODS(vehicle, i) - 1;
				if (modIndex > -1)
					modIndex = std::rand() % (modIndex + 2) - 1;
				if (i == VehicleMod::Horns)
					modIndex = 44; // Liberty City Loop
				SET_VEHICLE_MOD(vehicle, i, modIndex, 0);
			}
			SET_VEHICLE_WINDOW_TINT(vehicle, 1);

			SET_VEHICLE_TYRES_CAN_BURST(vehicle, false);
		}

		if (neonIt) // neons
		{
			for (i = 0; i <= 3; i++)
				_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, i, TRUE);
			_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, NeonR, NeonG, NeonB);
		}

		WAIT(50);

		if (prim_col_index != -3) // basic paint primary
		{
			CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);
			GET_VEHICLE_COLOURS(vehicle, &i, &inull);
			SET_VEHICLE_COLOURS(vehicle, prim_col_index, inull);
		}
		if (sec_col_index != -3) // basic paint secondary
		{
			CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
			GET_VEHICLE_COLOURS(vehicle, &inull, &i);
			SET_VEHICLE_COLOURS(vehicle, inull, sec_col_index);
		}

		WAIT(40);

		/*if (PrimModPaintType != -3)
		{
		CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);
		SET_VEHICLE_MOD_COLOR_1(vehicle, PrimModPaintType, PrimModPaint, -1);
		}
		if (SecModPaintType != -3)
		{
		CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
		SET_VEHICLE_MOD_COLOR_2(vehicle, SecModPaintType, SecModPaint);
		}*/

	}


	// ModShop



	void ModShop_()
	{
		if (!DOES_ENTITY_EXIST(Static_12) || !IS_ENTITY_A_VEHICLE(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		bool veh_plate_plus = 0, veh_plate_minus = 0, veh_plate_text_set = 0;
		INT i, veh_plate_current = GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Static_12);

		bool veh_static12_autoUpgrade = 0,
			aileron_on = 0,
			aileron_off = 0,
			SubMS_Paints = 0,
			SubMS_Extra = 0,
			ms_armour_plus = 0,
			ms_armour_minus = 0,
			ms_fbumper_plus = 0,
			ms_fbumper_minus = 0,
			ms_rbumper_plus = 0,
			ms_rbumper_minus = 0,
			ms_sideskirts_plus = 0,
			ms_sideskirts_minus = 0,
			ms_chasis_plus = 0,
			ms_chasis_minus = 0,
			ms_hood_plus = 0,
			ms_hood_minus = 0,
			ms_fenders_plus = 0,
			ms_fenders_minus = 0,
			ms_spoiler_plus = 0,
			ms_spoiler_minus = 0,
			ms_grille_plus = 0,
			ms_grille_minus = 0,
			ms_lights_toggle = 0,
			ms_engine_plus = 0,
			ms_engine_minus = 0,
			ms_trans_plus = 0,
			ms_trans_minus = 0,
			ms_brakes_plus = 0,
			ms_brakes_minus = 0,
			ms_susp_plus = 0,
			ms_susp_minus = 0,
			ms_exh_plus = 0,
			ms_exh_minus = 0,
			ms_livery_plus = 0,
			ms_livery_minus = 0,
			ms_turbo_toggle = 0,
			ms_light_int_1 = 0,
			ms_light_int_plus = 0,
			ms_light_int_minus = 0,
			rpm_input = 0, rpm_plus = 0, rpm_minus = 0,
			torque_input = 0, torque_plus = 0, torque_minus = 0,
			maxSpeed_input = 0, maxSpeed_plus = 0, maxSpeed_minus = 0,
			MSLowerSuspension_ = 0;


		Model Static_12_veh_model = GET_ENTITY_MODEL(Static_12);
		GTAvehicle vehicle = Static_12;
		Model& vehicleModel = Static_12_veh_model;
		bool Static_12_is_bike = (vehicleModel.IsBike() || vehicleModel.IsBicycle() || vehicleModel.IsQuadbike());
		bool Static_12_is_bicycle = Static_12_veh_model.IsBicycle();


		INT ms_armour = GET_VEHICLE_MOD(Static_12, 16) + 1,
			ms_fbumper = GET_VEHICLE_MOD(Static_12, 1) + 1,
			ms_rbumper = GET_VEHICLE_MOD(Static_12, 2) + 1,
			ms_sideskirts = GET_VEHICLE_MOD(Static_12, 3) + 1,
			ms_chasis = GET_VEHICLE_MOD(Static_12, 5) + 1,
			ms_hood = GET_VEHICLE_MOD(Static_12, 7) + 1,
			ms_fenders = GET_VEHICLE_MOD(Static_12, 8) + 1,
			ms_spoiler = GET_VEHICLE_MOD(Static_12, 0) + 1,
			ms_grille = GET_VEHICLE_MOD(Static_12, 6) + 1,
			// MOD 8 IS LEFT WING
			// MOD 9 IS RIGHT WING
			// MOD 10 IS ROOF
			ms_engine = GET_VEHICLE_MOD(Static_12, 11) + 1,
			ms_trans = GET_VEHICLE_MOD(Static_12, 13) + 1,
			ms_brakes = GET_VEHICLE_MOD(Static_12, 12) + 1,
			ms_susp = GET_VEHICLE_MOD(Static_12, 15) + 1,
			ms_exh = GET_VEHICLE_MOD(Static_12, 4) + 1,
			ms_livery = GET_VEHICLE_LIVERY(Static_12) + 1;

		auto rpmMultVal = 1.0f;
		auto& rpmMultIt = g_multList_rpm.find(vehicle.Handle());
		if (rpmMultIt != g_multList_rpm.end())
			rpmMultVal = rpmMultIt->second;

		auto torqueMultVal = 1.0f;
		auto& torqueMultIt = g_multList_torque.find(vehicle.Handle());
		if (torqueMultIt != g_multList_torque.end())
			torqueMultVal = torqueMultIt->second;

		auto maxSpeedMultVal = _GET_VEHICLE_MODEL_MAX_SPEED(vehicleModel.hash);
		auto& maxSpeedMultIt = g_multList_maxSpeed.find(vehicle.Handle());
		if (maxSpeedMultIt != g_multList_maxSpeed.end())
			maxSpeedMultVal = maxSpeedMultIt->second;

		auto headLightsMultVal = 1.0f;
		auto& headLightsMultIt = g_multList_headlights.find(vehicle.Handle());
		if (headLightsMultIt != g_multList_headlights.end())
			headLightsMultVal = headLightsMultIt->second;

		std::string ms_plateText = GET_VEHICLE_NUMBER_PLATE_TEXT(Static_12);

		std::vector<std::string> ms_vPlateTypeNames{ "CMOD_PLA_0", "CMOD_PLA_4", "CMOD_PLA_3", "CMOD_PLA_1", "CMOD_PLA_2", "Yankton" }; // BOW1, YOBLA, YOBLU, BOW2, BOW3, YANKTON 
		if (veh_plate_current < 0) veh_plate_current = 0;
		if (veh_plate_current >= ms_vPlateTypeNames.size()) veh_plate_current = (INT)ms_vPlateTypeNames.size() - 1;

		FLOAT ms_dirtLevel = GET_VEHICLE_DIRT_LEVEL(Static_12);


		AddTitle("Menyoo Customs");

		if (Static_12_veh_model.IsPlane()) {
			AddOption("Plane Aileron On", aileron_on);
			AddOption("Plane Aileron Off", aileron_off);
		}

		if (true) // Display Benny's sub ptr if veh is supported Static_12_veh_model.IsBennySupportedVehicle()
		{
			AddOption(Game::GetGXTEntry("S_MO_09", "Benny's Lowrider Mods"), null, nullFunc, SUB::MS_BENNYS); // Use 25 to 48 here.
		}

		if (Static_12_veh_model.IsWheelChangingSupportedVehicle())
		{
			AddOption(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels"), null, nullFunc, SUB::MSWHEELS, true);
		}

		/*AddNumber("Armour", ms_armour, 0, null, ms_armour_plus, ms_armour_minus);
		if (!Static_12_is_bike){
		AddNumber("Front Bumper", ms_fbumper, 0, null, ms_fbumper_plus, ms_fbumper_minus);
		AddNumber("Rear Bumper", ms_rbumper, 0, null, ms_rbumper_plus, ms_rbumper_minus);
		AddNumber("Side Skirts", ms_sideskirts, 0, null, ms_sideskirts_plus, ms_sideskirts_minus);
		AddNumber("Chasis", ms_chasis, 0, null, ms_chasis_plus, ms_chasis_minus);
		AddNumber("Hood", ms_hood, 0, null, ms_hood_plus, ms_hood_minus);
		AddNumber("Fenders", ms_fenders, 0, null, ms_fenders_plus, ms_fenders_minus);
		AddNumber("Spoiler", ms_spoiler, 0, null, ms_spoiler_plus, ms_spoiler_minus);
		AddNumber("Grille", ms_grille, 0, null, ms_grille_plus, ms_grille_minus);}
		AddNumber("Engine", ms_engine, 0, null, ms_engine_plus, ms_engine_minus);
		AddNumber("Brakes", ms_brakes, 0, null, ms_brakes_plus, ms_brakes_minus);
		AddNumber("Transmission", ms_trans, 0, null, ms_trans_plus, ms_trans_minus);
		AddNumber("Suspension", ms_susp, 0, null, ms_susp_plus, ms_susp_minus);
		AddNumber("Exhaust", ms_exh, 0, null, ms_exh_plus, ms_exh_minus);	*/

		selectmod = true;
		setMod = true;

		bool pressed = 0;
		for (i = 0; i <= 24/*vValues_ModSlotNames.size()*/; i++) // Only want 0 to 24 here. 25 to 48 are at Benny's.
		{
			pressed = 0;
			if (i >= 17 && i <= 24)
				continue; // Toggleables and front/back wheels not needed here
			//if (i == VehicleMod::Suspension && Static_12_veh_model.hash == VEHICLE_GLENDALE) continue;
			if (GET_NUM_VEHICLE_MODS(Static_12, i) > 0)
			{
				lastMod = -2;
				AddOption(get_mod_slot_name(Static_12, i, true), pressed, nullFunc, SUB::MSCATALL, true, false); if (pressed)
				{
					ms_curr_paint_index = i;
				}
			}
		}

		//if (!(Static_12_veh_model == VehicleHashes::Police || Static_12_veh_model == VehicleHashes::Police2 || Static_12_veh_model == VehicleHashes::Police3 || Static_12_veh_model == VehicleHashes::Police4 || Static_12_veh_model == VehicleHashes::Policeb || Static_12_veh_model == VehicleHashes::PoliceOld1 || Static_12_veh_model == VehicleHashes::PoliceOld2 || Static_12_veh_model == VehicleHashes::PoliceT))
		//if (Static_12_veh_model != VehicleHashes::Policeb && Static_12_veh_model != VehicleHashes::Riot && Static_12_veh_model != VehicleHashes::PoliceOld1 && Static_12_veh_model != VehicleHashes::PoliceOld2)
		//AddOption("Horns", null, nullFunc, SUB::MSHORNS);
		AddOption("Paints", null, nullFunc, SUB::MSPAINTS, true, false);
		if (!Static_12_is_bike)
		{
			AddOption(Game::GetGXTEntry("PIM_PVEO_004", "Neons Lights"), null, nullFunc, SUB::MSNEONS);
			AddOption(Game::GetGXTEntry("CMM_MOD_S6", "Doors"), null, nullFunc, SUB::MSDOORS);
			AddOption(Game::GetGXTEntry("CMOD_MOD_WIN", "Windows"), null, nullFunc, SUB::MSWINDOWS, true, false); // Windows CMOD_MOD_WIN
		}
		AddOption(Game::GetGXTEntry("CMOD_COL0_3", "Emblem"), null, nullFunc, SUB::MS_EMBLEM, true, false); // Crew Emblems CMOD_COL0_3
		AddOption(Game::GetGXTEntry("CMOD_MOD_GLD2", "Extras"), SubMS_Extra, nullFunc, -1, true, false); // Extras CMOD_MOD_GLD2
		if (GET_VEHICLE_LIVERY_COUNT(Static_12) > 0)
			AddNumber(Game::GetGXTEntry("CMOD_COL0_4", "Livery"), ms_livery, 0, null, ms_livery_plus, ms_livery_minus);
		AddLocal(Game::GetGXTEntry("CMOD_MOD_TUR", "Turbo"), IS_TOGGLE_MOD_ON(Static_12, VehicleMod::Turbo), ms_turbo_toggle, ms_turbo_toggle); // Turbo
		AddLocal(Game::GetGXTEntry("CMOD_LGT_1", "Xenon Lights"), IS_TOGGLE_MOD_ON(Static_12, VehicleMod::XenonHeadlights), ms_lights_toggle, ms_lights_toggle); // Xenon lights
		AddLocal("Lower Suspension", lowersuspension, MSLowerSuspension_, MSLowerSuspension_, true); // Tuners Lower Suspension

		if (MSLowerSuspension_) {
			vehicle.RequestControlOnce();
			lowersuspension = !lowersuspension;
			_SET_REDUCE_DRIFT_VEHICLE_SUSPENSION(Static_12, lowersuspension);
			return;
		}

		if (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM && vehicle.IsToggleModOn(VehicleMod::XenonHeadlights))
		{ // Xenon Headlight Colours
			std::vector<std::string> vHlColours
			{
				{ "White" }, //0
				{ "Blue" },
				{ "Light Blue" },
				{ "Green" },
				{ "Light Green" },
				{ "Light Yellow" },
				{ "Yellow" },
				{ "Orange" },
				{ "Red" },
				{ "Light Pink" },
				{ "Pink" },
				{ "Purple" },
				{ "Light Purple" }
			};

			int hlColour = vehicle.HeadlightColour_get();

			bool bHlColourPlus = false, bHlColourMinus = false;
			AddTexter(Game::GetGXTEntry("CMOD_LGT_1", "Xenon Lights") + " Colour", hlColour == 255 ? 0 : hlColour,
				hlColour == 255 ? std::vector<std::string>{"Stock"} : vHlColours,
				null, bHlColourPlus, bHlColourMinus);
			if (bHlColourPlus)
			{
				if (hlColour >= vHlColours.size())
					hlColour = 0;
				else if (hlColour < vHlColours.size() - 1)
					hlColour++;
				vehicle.HeadlightColour_set(hlColour);
			}
			else if (bHlColourMinus)
			{
				if (hlColour == 0)
					hlColour = 255;
				else if (hlColour != 255 && hlColour > 0)
					hlColour--;
				vehicle.HeadlightColour_set(hlColour);
			}
		}

		AddNumber(Game::GetGXTEntry("CMOD_MOD_LGT_H", "Headlights") + " Intensity", headLightsMultVal, 2, ms_light_int_1, ms_light_int_plus, ms_light_int_minus);
		AddTexter(Game::GetGXTEntry("CMOD_MOD_PLA", "Plate") + " " + Game::GetGXTEntry("FMMC_MTYPE", "Type"), veh_plate_current, ms_vPlateTypeNames, null, veh_plate_plus, veh_plate_minus);
		AddTexter(Game::GetGXTEntry("CMOD_MOD_18_D", "Plate Text"), 0, std::vector<std::string>{ms_plateText}, veh_plate_text_set);
		AddOption(Game::GetGXTEntry("CMM_MOD_G3", "Engine") + " " + Game::GetGXTEntry("VEUI_AUD_TIT", "Sound"), null, nullFunc, SUB::MSENGINESOUND);
		AddNumber("Horse Power Multiplier", rpmMultVal, 2, rpm_input, rpm_plus, rpm_minus);
		AddNumber("Torque Multiplier", torqueMultVal, 2, torque_input, torque_plus, torque_minus);
		AddNumber(Game::GetGXTEntry("FMMC_VEHST_0", "Top Speed") + " (Kmph)", maxSpeedMultVal * 3.6f, 0, maxSpeed_input, maxSpeed_plus, maxSpeed_minus);
		AddOption(Game::GetGXTEntry("CMOD_MOD_LGT", "Lights"), null, nullFunc, SUB::MSLIGHTS);
		//bool bLightsOnTogglePressed = false; AddTickol(Game::GetGXTEntry("CMOD_MOD_LGT", "Lights"), vehicle.LightsOn_get(), bLightsOnTogglePressed, bLightsOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bLightsOnTogglePressed) vehicle.LightsOn_set(!vehicle.LightsOn_get());
		bool bEngineOnTogglePressed = false; AddTickol(Game::GetGXTEntry("CMM_MOD_G3", "Engine"), vehicle.EngineRunning_get(), bEngineOnTogglePressed, bEngineOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bEngineOnTogglePressed) vehicle.EngineRunning_set(!vehicle.EngineRunning_get());
		//bool bLoudRadioTogglePressed = false; AddTickol("Loud Radio", vehicle.LoudRadioActive_get(), bLoudRadioTogglePressed, bLoudRadioTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bLoudRadioTogglePressed) vehicle.LoudRadioActive_set(!vehicle.LoudRadioActive_get());

		if (Static_12_veh_model.HasSiren())
		{
			bool bSirenOnTogglePressed = false;
			AddTickol("Sirens", vehicle.SirenActive_get(), bSirenOnTogglePressed, bSirenOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bSirenOnTogglePressed)
				vehicle.SirenActive_set(!vehicle.SirenActive_get());
		}

		AddOption("AUTO UPGRADE", veh_static12_autoUpgrade);
		AddToggle("LSC Style Part Selection", _globalLSC_Customs);

		if (GET_VEHICLE_MOD_KIT != 0)
		{
			vehicle.RequestControlOnce();
			SET_VEHICLE_MOD_KIT(vehicle.GetHandle(), 0);
		}

		if (aileron_on) DISABLE_PLANE_AILERON(Static_12, 0, 0);
		if (aileron_off) DISABLE_PLANE_AILERON(Static_12, 0, 1);

		/*if (ms_armour_plus){
		if (ms_armour < GET_NUM_VEHICLE_MODS(Static_12, 16)) ms_armour++;
		SET_VEHICLE_MOD(Static_12, 16, (ms_armour - 1), 0);
		return;
		}
		if (ms_armour_minus){
		if (ms_armour > 0) ms_armour--;
		if (ms_armour == 0) REMOVE_VEHICLE_MOD(Static_12, 16);
		SET_VEHICLE_MOD(Static_12, 16, (ms_armour - 1), 0);
		return;
		}

		if (ms_fbumper_plus){
		if (ms_fbumper < GET_NUM_VEHICLE_MODS(Static_12, 1)) ms_fbumper++;
		SET_VEHICLE_MOD(Static_12, 1, (ms_fbumper - 1), 0);
		return;
		}
		if (ms_fbumper_minus){
		if (ms_fbumper > 0) ms_fbumper--;
		if (ms_fbumper == 0) REMOVE_VEHICLE_MOD(Static_12, 1);
		SET_VEHICLE_MOD(Static_12, 1, (ms_fbumper - 1), 0);
		return;
		}

		if (ms_rbumper_plus){
		if (ms_rbumper < GET_NUM_VEHICLE_MODS(Static_12, 2)) ms_rbumper++;
		SET_VEHICLE_MOD(Static_12, 2, (ms_rbumper - 1), 0);
		return;
		}
		if (ms_rbumper_minus){
		if (ms_rbumper > 0) ms_rbumper--;
		if (ms_rbumper == 0) REMOVE_VEHICLE_MOD(Static_12, 2);
		SET_VEHICLE_MOD(Static_12, 2, (ms_rbumper - 1), 0);
		return;
		}

		if (ms_sideskirts_plus){
		if (ms_sideskirts < GET_NUM_VEHICLE_MODS(Static_12, 3)) ms_sideskirts++;
		SET_VEHICLE_MOD(Static_12, 3, (ms_sideskirts - 1), 0);
		return;
		}
		if (ms_sideskirts_minus){
		if (ms_sideskirts > 0) ms_sideskirts--;
		if (ms_sideskirts == 0) REMOVE_VEHICLE_MOD(Static_12, 3);
		SET_VEHICLE_MOD(Static_12, 3, (ms_sideskirts - 1), 0);
		return;
		}

		if (ms_chasis_plus){
		if (ms_chasis < GET_NUM_VEHICLE_MODS(Static_12, 5)) ms_chasis++;
		SET_VEHICLE_MOD(Static_12, 5, (ms_chasis - 1), 0);
		return;
		}
		if (ms_chasis_minus){
		if (ms_chasis > 0) ms_chasis--;
		if (ms_chasis == 0) REMOVE_VEHICLE_MOD(Static_12, 5);
		SET_VEHICLE_MOD(Static_12, 5, (ms_chasis - 1), 0);
		return;
		}

		if (ms_hood_plus){
		if (ms_hood < GET_NUM_VEHICLE_MODS(Static_12, 7)) ms_hood++;
		SET_VEHICLE_MOD(Static_12, 7, (ms_hood - 1), 0);
		return;
		}
		if (ms_hood_minus){
		if (ms_hood > 0) ms_hood--;
		if (ms_hood == 0) REMOVE_VEHICLE_MOD(Static_12, 7);
		SET_VEHICLE_MOD(Static_12, 7, (ms_hood - 1), 0);
		return;
		}

		if (ms_fenders_plus){
		if (ms_fenders < GET_NUM_VEHICLE_MODS(Static_12, 8)) ms_fenders++;
		SET_VEHICLE_MOD(Static_12, 8, (ms_fenders - 1), 0);
		return;
		}
		if (ms_fenders_minus){
		if (ms_fenders > 0) ms_fenders--;
		if (ms_fenders == 0) REMOVE_VEHICLE_MOD(Static_12, 8);
		SET_VEHICLE_MOD(Static_12, 8, (ms_fenders - 1), 0);
		return;
		}

		if (ms_spoiler_plus){
		if (ms_spoiler < GET_NUM_VEHICLE_MODS(Static_12, 0)) ms_spoiler++;
		SET_VEHICLE_MOD(Static_12, 0, (ms_spoiler - 1), 0);
		return;
		}
		if (ms_spoiler_minus){
		if (ms_spoiler > 0) ms_spoiler--;
		if (ms_spoiler == 0) REMOVE_VEHICLE_MOD(Static_12, 0);
		SET_VEHICLE_MOD(Static_12, 0, (ms_spoiler - 1), 0);
		return;
		}

		if (ms_grille_plus){
		if (ms_grille < GET_NUM_VEHICLE_MODS(Static_12, 6)) ms_grille++;
		SET_VEHICLE_MOD(Static_12, 6, (ms_grille - 1), 0);
		return;
		}
		if (ms_grille_minus){
		if (ms_grille > 0) ms_grille--;
		if (ms_grille == 0) REMOVE_VEHICLE_MOD(Static_12, 6);
		SET_VEHICLE_MOD(Static_12, 6, (ms_grille - 1), 0);
		return;
		}

		if (ms_engine_plus){
		if (ms_engine < GET_NUM_VEHICLE_MODS(Static_12, 11)) ms_engine++;
		SET_VEHICLE_MOD(Static_12, 11, (ms_engine - 1), 0);
		return;
		}
		if (ms_engine_minus){
		if (ms_engine > 0) ms_engine--;
		if (ms_engine == 0) REMOVE_VEHICLE_MOD(Static_12, 11);
		SET_VEHICLE_MOD(Static_12, 11, (ms_engine - 1), 0);
		return;
		}

		if (ms_trans_plus){
		if (ms_trans < GET_NUM_VEHICLE_MODS(Static_12, 13)) ms_trans++;
		SET_VEHICLE_MOD(Static_12, 13, (ms_trans - 1), 0);
		return;
		}
		if (ms_trans_minus){
		if (ms_trans > 0) ms_trans--;
		if (ms_trans == 0) REMOVE_VEHICLE_MOD(Static_12, 13);
		SET_VEHICLE_MOD(Static_12, 13, (ms_trans - 1), 0);
		return;
		}

		if (ms_brakes_plus){
		if (ms_brakes < GET_NUM_VEHICLE_MODS(Static_12, 12)) ms_brakes++;
		SET_VEHICLE_MOD(Static_12, 12, (ms_brakes - 1), 0);
		return;
		}
		if (ms_brakes_minus){
		if (ms_brakes > 0) ms_brakes--;
		if (ms_brakes == 0) REMOVE_VEHICLE_MOD(Static_12, 12);
		SET_VEHICLE_MOD(Static_12, 12, (ms_brakes - 1), 0);
		return;
		}

		if (ms_susp_plus){
		if (ms_susp < GET_NUM_VEHICLE_MODS(Static_12, 15)) ms_susp++;
		SET_VEHICLE_MOD(Static_12, 15, (ms_susp - 1), 0);
		return;
		}
		if (ms_susp_minus){
		if (ms_susp > 0) ms_susp--;
		if (ms_susp == 0) REMOVE_VEHICLE_MOD(Static_12, 15);
		SET_VEHICLE_MOD(Static_12, 15, (ms_susp - 1), 0);
		return;
		}

		if (ms_exh_plus){
		if (ms_exh < GET_NUM_VEHICLE_MODS(Static_12, 4)) ms_exh++;
		SET_VEHICLE_MOD(Static_12, 4, (ms_exh - 1), 0);
		return;
		}
		if (ms_exh_minus){
		if (ms_exh > 0) ms_exh--;
		if (ms_exh == 0) REMOVE_VEHICLE_MOD(Static_12, 4);
		SET_VEHICLE_MOD(Static_12, 4, (ms_exh - 1), 0);
		return;
		}*/

		if (ms_livery_plus) {
			if (ms_livery < GET_VEHICLE_LIVERY_COUNT(Static_12)) ms_livery++;
			SET_VEHICLE_LIVERY(Static_12, ms_livery - 1);
			return;
		}
		if (ms_livery_minus) {
			if (ms_livery > 1) ms_livery--;
			SET_VEHICLE_LIVERY(Static_12, ms_livery - 1);
			return;
		}

		if (ms_lights_toggle) {
			if (IS_TOGGLE_MOD_ON(Static_12, 22)) TOGGLE_VEHICLE_MOD(Static_12, 22, 0);
			else TOGGLE_VEHICLE_MOD(Static_12, 22, 1);
			return;
		}
		if (ms_turbo_toggle) {
			if (IS_TOGGLE_MOD_ON(Static_12, 18)) TOGGLE_VEHICLE_MOD(Static_12, 18, 0);
			else TOGGLE_VEHICLE_MOD(Static_12, 18, 1);
			return;
		}

		if (SubMS_Extra) {
			for (i = 0; i <= 12; i++)
				if (DOES_EXTRA_EXIST(Static_12, i)) { Menu::SetSub_new(SUB::MSEXTRA); break; }
			if (Menu::currentsub != SUB::MSEXTRA)
				Game::Print::PrintBottomCentre("~r~Error:~s~ Vehicle has no extras.");
			return;
		}


		if (veh_plate_plus) {
			if (veh_plate_current < GET_NUMBER_OF_VEHICLE_NUMBER_PLATES() - 1)
			{
				veh_plate_current++;
				vehicle.RequestControl();
				SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Static_12, veh_plate_current);
			}
			return;
		}
		if (veh_plate_minus) {
			if (veh_plate_current > 0)
			{
				veh_plate_current--;
				vehicle.RequestControl();
				SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Static_12, veh_plate_current);
			}
			return;
		}

		if (veh_plate_text_set)
		{
			std::string inputStr = Game::InputBox("", 8U + 1 - 1, "CMOD_MOD_18_D", ms_plateText);
			if (inputStr.length() > 0 && inputStr.length() <= 8)
			{
				vehicle.RequestControl(400);
				vehicle.NumberPlateText_set(inputStr);
				Game::Print::PrintBottomLeft("CMOD_PLATEFIT", true);
			}
			else Game::Print::PrintError_InvalidInput();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsPlateText, std::string(), 8U, "CMOD_MOD_18_D", ms_plateText);
			//OnscreenKeyboard::State::arg1._int = vehicle.Handle();
			return;
		}

		if (ms_light_int_1)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << headLightsMultVal;
			std::string oldStr = ss.str();

			std::string inputStr = Game::InputBox("", 10U, "", oldStr);
			if (inputStr.length() > 0)
			{
				try
				{
					headLightsMultVal = stof(inputStr);
					vehicle.RequestControl();
					vehicle.LightsMultiplier_set(headLightsMultVal);
					if (headLightsMultIt != g_multList_headlights.end())
						headLightsMultIt->second = headLightsMultVal;
					else
						g_multList_headlights[vehicle.Handle()] = headLightsMultVal;
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsHeadlightIntensity, std::string(), 10U, std::string(), oldStr);
			//OnscreenKeyboard::State::arg1._int = vehicle.Handle();
		}
		if (ms_light_int_plus)
		{
			if (headLightsMultVal < FLT_MAX - 0.1f)
			{
				headLightsMultVal += 0.1f;
				vehicle.RequestControl();
				vehicle.LightsMultiplier_set(headLightsMultVal);
				if (headLightsMultIt != g_multList_headlights.end())
					headLightsMultIt->second = headLightsMultVal;
				else
					g_multList_headlights[vehicle.Handle()] = headLightsMultVal;
			}
			return;
		}
		if (ms_light_int_minus)
		{
			if (headLightsMultVal > -FLT_MAX + 0.1f)
			{
				headLightsMultVal -= 0.1f;
				vehicle.RequestControl();
				vehicle.LightsMultiplier_set(headLightsMultVal);
				if (headLightsMultIt != g_multList_headlights.end())
					headLightsMultIt->second = headLightsMultVal;
				else
					g_multList_headlights[vehicle.Handle()] = headLightsMultVal;
			}
			return;
		}

		if (rpm_input)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << rpmMultVal;
			std::string oldStr = ss.str();

			std::string inputStr = Game::InputBox("", 10U, "", oldStr);
			if (inputStr.length() > 0)
			{
				try
				{
					rpmMultVal = stof(inputStr);
					vehicle.RequestControl(400);
					vehicle.EnginePowerMultiplier_set(rpmMultVal);
					if (rpmMultIt != g_multList_rpm.end())
						rpmMultIt->second = rpmMultVal;
					else
						g_multList_rpm[vehicle.Handle()] = rpmMultVal;
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsRpm, std::string(), 10U, std::string(), oldStr);
			//OnscreenKeyboard::State::arg1._int = vehicle.Handle();
		}
		if (rpm_plus)
		{
			if (rpmMultVal < FLT_MAX - 0.1f)
			{
				rpmMultVal += 0.1f;
				vehicle.RequestControl(400);
				vehicle.EnginePowerMultiplier_set(rpmMultVal);
				if (rpmMultIt != g_multList_rpm.end())
					rpmMultIt->second = rpmMultVal;
				else
					g_multList_rpm[vehicle.Handle()] = rpmMultVal;
			}
			return;
		}
		if (rpm_minus)
		{
			if (rpmMultVal > -FLT_MAX + 0.1f)
			{
				rpmMultVal -= 0.1f;
				vehicle.RequestControl(400);
				vehicle.EnginePowerMultiplier_set(rpmMultVal);
				if (rpmMultIt != g_multList_rpm.end())
					rpmMultIt->second = rpmMultVal;
				else
					g_multList_rpm[vehicle.Handle()] = rpmMultVal;
			}
			return;
		}

		if (torque_input)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << torqueMultVal;
			std::string oldStr = ss.str();

			std::string inputStr = Game::InputBox("", 10U, "", oldStr);
			if (inputStr.length() > 0)
			{
				try
				{
					torqueMultVal = stof(inputStr);
					vehicle.RequestControl(400);
					vehicle.EngineTorqueMultiplier_set(torqueMultVal);
					if (torqueMultIt != g_multList_torque.end())
						torqueMultIt->second = torqueMultVal;
					else
						g_multList_torque[vehicle.Handle()] = torqueMultVal;
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsTorque, std::string(), 10U, std::string(), oldStr);
			//OnscreenKeyboard::State::arg1._int = vehicle.Handle();
		}
		if (torque_plus)
		{
			if (torqueMultVal < FLT_MAX - 0.1f)
			{
				torqueMultVal += 0.1f;
				vehicle.RequestControl(400);
				vehicle.EngineTorqueMultiplier_set(torqueMultVal);
				if (torqueMultIt != g_multList_torque.end())
					torqueMultIt->second = torqueMultVal;
				else
					g_multList_torque[vehicle.Handle()] = torqueMultVal;
			}
			return;
		}
		if (torque_minus)
		{
			if (torqueMultVal > -FLT_MAX + 0.1f)
			{
				torqueMultVal -= 0.1f;
				vehicle.RequestControl(400);
				vehicle.EngineTorqueMultiplier_set(torqueMultVal);
				if (torqueMultIt != g_multList_torque.end())
					torqueMultIt->second = torqueMultVal;
				else
					g_multList_torque[vehicle.Handle()] = torqueMultVal;
			}
			return;
		}

		if (maxSpeed_input)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(0) << (maxSpeedMultVal * 3.6f);
			std::string oldStr = ss.str();

			std::string inputStr = Game::InputBox("", 9U, "", oldStr);
			if (inputStr.length() > 0)
			{
				try
				{
					maxSpeedMultVal = stof(inputStr) / 3.6f;
					vehicle.RequestControl(400);
					vehicle.MaxSpeed_set(maxSpeedMultVal);
					if (maxSpeedMultIt != g_multList_maxSpeed.end())
						maxSpeedMultIt->second = maxSpeedMultVal;
					else
						g_multList_maxSpeed[vehicle.Handle()] = maxSpeedMultVal;
				}
				catch (...)
				{
					Game::Print::PrintError_InvalidInput();
				}
			}
			return;
			// No OnScreenKeyboard!
		}
		if (maxSpeed_plus)
		{
			if (maxSpeedMultVal < FLT_MAX / 3.6f - 3.6f)
			{
				maxSpeedMultVal += 1.0f / 3.6f;
				vehicle.RequestControl(400);
				vehicle.MaxSpeed_set(maxSpeedMultVal);
				if (maxSpeedMultIt != g_multList_maxSpeed.end())
					maxSpeedMultIt->second = maxSpeedMultVal;
				else
					g_multList_maxSpeed[vehicle.Handle()] = maxSpeedMultVal;
			}
			return;
		}
		if (maxSpeed_minus)
		{
			if (maxSpeedMultVal > -FLT_MAX / 3.6f + 3.6f)
			{
				maxSpeedMultVal -= 1.0f / 3.6f;
				vehicle.RequestControl(400);
				vehicle.MaxSpeed_set(maxSpeedMultVal);
				if (maxSpeedMultIt != g_multList_maxSpeed.end())
					maxSpeedMultIt->second = maxSpeedMultVal;
				else
					g_multList_maxSpeed[vehicle.Handle()] = maxSpeedMultVal;
			}
			return;
		}

		if (veh_static12_autoUpgrade)
		{
			vehicle.RequestControl(400);
			set_vehicle_max_upgrades(Static_12, true, false, GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Static_12));
			SET_VEHICLE_TYRES_CAN_BURST(Static_12, false);
		}
	}

	// Bennys

	namespace Bennys_catind
	{

		void Sub_BennysMain()
		{
			GTAvehicle vehicle = Static_12;
			auto& vehModel = vehicle.Model();

			if (!vehicle.Exists())
			{
				Menu::SetSub_previous();
				return;
			}

			int i;

			AddTitle(Game::GetGXTEntry("S_MO_09", "Benny's Lowrider Mods"));

			if (firsttime == true)
			{
				GetAllPaintIDs();
			}

			bool goToInteriorColour = 0;
			AddOption("Interior Colour", goToInteriorColour, nullFunc, SUB::MSPAINTS2); if (goToInteriorColour)
			{
				ms_curr_paint_index = 5;
			}

			bool goToDashboardColour = 0;
			AddOption("Dashboard Colour", goToDashboardColour, nullFunc, SUB::MSPAINTS2); if (goToDashboardColour)
			{
				ms_curr_paint_index = 6;
			}

			setMod = true;
			selectmod = true;

			bool pressed = 0;
			for (i = 25; i <= 48/*vValues_ModSlotNames.size()*/; i++) // Only want 25 to 48 here.
			{
				pressed = 0;
				if (GET_NUM_VEHICLE_MODS(vehicle.Handle(), i) > 0)
				{
					lastMod = -2;
					AddOption(get_mod_slot_name(vehicle.Handle(), i, true), pressed, nullFunc, SUB::MSCATALL, true, false); if (pressed)
					{
						ms_curr_paint_index = i;
					}
				}
			}

		}
	}

	// Selected vehicle mod submenu (for selection of mod value)
	/*void previewvehicleoption(Vehicle vehicle, int modType, int modindex, BOOL customtyres)  //this whole void is completely unused?
	{
		SET_VEHICLE_MOD(vehicle, modType, modindex, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
	}*/


	void MSCatall_()
	{
		Vehicle& vehicle = Static_12;

		if (!DOES_ENTITY_EXIST(vehicle))
		{
			Menu::SetSub_previous();
			return;
		}


		INT& modType = ms_curr_paint_index,
			maxMod = GET_NUM_VEHICLE_MODS(vehicle, modType) - 1,
			currMod = GET_VEHICLE_MOD(vehicle, modType);

		if (selectmod)
		{
			lastMod = GET_VEHICLE_MOD(vehicle, modType);
			selectmod = false;
		}

		AddTitle(get_mod_slot_name(vehicle, modType, true));

		if (_globalLSC_Customs) //to allow toggleable LSC style menu nav
		{
			for (INT i = -1; i <= maxMod; i++)
			{
				bool pressed = false;
				AddTickol(get_mod_text_label(vehicle, modType, i, true), lastMod == i, pressed, pressed,
					IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, false);
				if (setMod)
					SET_VEHICLE_MOD(vehicle, modType, *Menu::currentopATM - 2, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
				if (pressed)
				{
					setMod = false;
					Menu::SetSub_previous();
					return;
				}
				if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back))
				{
					SET_VEHICLE_MOD(vehicle, modType, lastMod, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
					setMod = false;
				}
			}
		}
		else
		{
			for (INT i = -1; i <= maxMod; i++)
			{
				setMod = false;
				AddTickol(get_mod_text_label(vehicle, modType, i, true), currMod == i, setMod, setMod,
					IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, false); if (setMod)
					SET_VEHICLE_MOD(vehicle, modType, i, GET_VEHICLE_MOD_VARIATION(vehicle, modType));

			}
		}
	}

	// Emblem

	void MSEmblem_()
	{
		GTAvehicle vehicle = Static_12;

		if (!vehicle.Exists())
		{
			Menu::SetSub_previous();
			return;
		}

		int i;
		bool pressed = 0, pressedClear = 0;

		AddTitle(Game::GetGXTEntry("CMOD_COL0_3", "Emblem"));

		AddTickol(Game::GetGXTEntry("FMMC_REM", "CLEAR"), true, pressedClear, pressedClear, TICKOL::CROSS); if (pressedClear)
		{
			vehicle.RequestControlOnce();
			REMOVE_DECALS_FROM_VEHICLE(vehicle.Handle());
		}

		for (i = 0; i < GAME_PLAYERCOUNT; i++)
		{
			pressed = 0;
			if (NETWORK_IS_PLAYER_ACTIVE(i))
			{
				AddOption(GET_PLAYER_NAME(i), pressed); if (pressed)
				{
					add_emblem_to_vehicle(vehicle, GET_PLAYER_PED(i));
				}
			}

		}

	}

	// Wheels

	namespace MSWheels_catind
	{
		//bool ms_wheel_windice_pressed = false; 
		bool ms_bit_bike_back;
		//INT ms_old_wtype, ms_old_windex, ms_old_windexBB;
		int ms_max_windices;
		std::vector<std::string> vWheelTNames{ "Sport", "Muscle", "Lowrider", "SUV", "Offroad", "Tuner", "Bike", "High-End", "Benny's Originals", "Benny's Bespoke", "Open Wheel", "Street", "Track" };
		//std::vector<std::string> vWheelTNames{ "CMOD_WHE1_5", "CMOD_WHE1_3", "CMOD_WHE1_2", "CMOD_WHE1_6", "CMOD_WHE1_4", "CMOD_WHE1_7", "CMOD_WHE1_0", "CMOD_WHE1_1", "Benny's Original", "Benny's Bespoke" };
		//std::vector<std::string> vAllWheelNames[]
		//{
		//	{ "Inforno", "Deep Five", "Lozspeed Mk.V", "Diamond Cut", "Chrono", "Feroci RR", "FiftyNine", "Mercie", "Synthetic Z", "Organic Type 0", "Endo v.1", "GT One", "Duper 7", "Uzer", "Groundride", "S Racer", "Venum", "Cosmo", "Dash VIP", "Ice Kid"}, // sport
		//	{ "Classic Five", "Dukes", "Muscle Freak", "Kracka", "Azreal", "Mecha", "Black Top", "Drag SPL", "Revolver", "Classic Rod", "Fairlie", "Spooner", "Five Star", "Old School", "El Jefe", "Dodman", "Six Gun", "Mercenary" }, // muscle
		//	{ "Flare", "Wired", "Triple Golds", "Big Worm", "Seven Fives", "Split Six", "Fresh Mesh", "Lead Sled", "Turbine", "Super Fin", "Classic Rod", "Dollar", "Dukes", "Low Five", "Gooch" }, // lowrider
		//	{ "VIP", "Benefactor", "Cosmo", "Bippu", "Royal Six", "Fagorme", "Deluxe", "Iced Out", "Congoscenti", "Lozspeed Ten", "Supernova", "Obey RS", "Lozspeed Baller", "Extravaganzo", "Split Six", "Empowered", "Sunrise", "Dash VIP", "Cutter" }, // suv
		//	{ "Raider", "Mudslinger", "Nevis", "Cairngorm", "Amazon", "Challenger", "Dune Basher", "Five Star", "Rock Crawler", "Mil Spec Steelie" }, // offroad
		//	{ "Cosmo", "Super Mesh", "Outsider", "Rollas", "Driftmeister", "Slicer", "El Quatro", "Dubbed", "Five Star", "Sideways", "Apex", "Stanced EG", "Countersteer", "Endo v.1", "Endo v.2 Dish", "Gruppe Z", "Choku-Dori", "Chicane", "Saisoku", "Dished Eight" }, // tuner
		//	{ "Speedway", "Street Special", "Racer", "Track Star", "Overlord", "Trident", "Triple Threat", "Stiletto", "Wires", "Bobber", "Solidus", "Ice Shield", "Loops"}, // bike
		//	{ "Shadow", "Hypher", "Blade", "Diamond", "Supa Gee", "Chromatic Z", "Merchie Ch.Lip", "Obey RS", "GT Chrome", "Cheetah RR", "Solar", "Split Ten", "Dash VIP", "LozSpeed Ten", "Carbon Inferno", "Carbon Shadow", "Carbonic Z", "Carbon Solar", "Cheetah Cobra R", "Carbon S Racer" } // highend
		//};

		void __AddpointOption(const std::string& text, INT8 wheelType)
		{
			int& wtype = ms_curr_paint_index, & chrtype = bit_MSPaints_RGB_mode;
			bool pressed = false;
			AddOption(text, pressed, nullFunc, -1, true, true); if (pressed)
			{
				ms_curr_paint_index = wheelType;
				if (wheelType == WheelType::BikeWheels)
				{
					ms_bit_bike_back = true;
					Menu::SetSub_delayed = SUB::MSWHEELS2;
				}
				else
				{
					ms_bit_bike_back = false;
					chrtype = 0;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
					Menu::SetSub_delayed = SUB::MSWHEELS3;
				}
			}
		}
		void __AddOption(const std::string& text, Vehicle vehicle, INT8 wheelType, INT16 wheelIndex, bool isBikeBack)
		{
			INT currWheelType = -1;
			INT currWheelIndex = -1;
			if (_globalLSC_Customs)
			{
				if (selectwheel)
				{
					currWheelType = lastwheeltype;
					currWheelIndex = lastfwheel;
					selectwheel = false;
				}
				bool pressed = false;
				if (isBikeBack)
					AddTickol(text, currWheelIndex == wheelIndex && currWheelType == wheelType, pressed, pressed,
						TICKOL::BIKETHING, TICKOL::NONE, true);
				else
					AddTickol(text, currWheelIndex == wheelIndex && currWheelType == wheelType, pressed, pressed,
						IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, true);


				if (setwheel && IS_ENTITY_A_VEHICLE(vehicle))
				{
					GTAvehicle(vehicle).RequestControl();
					SET_VEHICLE_WHEEL_TYPE(vehicle, wheelType);
					if (wheelType == WheelType::BikeWheels)
					{
						isBikeBack ? SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels))
							: SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
					}
					else
					{
						SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
						SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels));
					}

					if (pressed)
					{
						setwheel = false;
						if (wheelType == WheelType::BikeWheels)
						{
							isBikeBack ? SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels))
								: SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
						}
						else
						{
							SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
							SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, *Menu::currentopATM - 1, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels));
						}
						lastfwheel = GET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels);
						lastbwheel = GET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels);
						Menu::SetSub_previous();
						return;
					}
				}

				//Game::Print::PrintBottomCentre("~b~Debug -~s~  setwheel:" + std::to_string(setwheel) + ", selectwheel:" + std::to_string(selectwheel) + ", lastfwheel:" + std::to_string(lastfwheel) + ", *Menu::currentopATM - 1" + std::to_string(*Menu::currentopATM - 1) + ", lastwheeltype:" + std::to_string(lastwheeltype));
			}
			else ///lsccustoms off
			{
				currWheelType = GET_VEHICLE_WHEEL_TYPE(vehicle);
				currWheelIndex = GET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels);

				bool pressed = false;
				if (isBikeBack)
					AddTickol(text, currWheelIndex == wheelIndex && currWheelType == wheelType, pressed, pressed,
						TICKOL::BIKETHING, TICKOL::NONE, true);
				else
					AddTickol(text, currWheelIndex == wheelIndex && currWheelType == wheelType, pressed, pressed,
						IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, true);

				if (pressed)
				{
					if (IS_ENTITY_A_VEHICLE(vehicle))
					{
						GTAvehicle(vehicle).RequestControl();
						SET_VEHICLE_WHEEL_TYPE(vehicle, wheelType);
						if (wheelType == WheelType::BikeWheels)
						{
							isBikeBack ? SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels))
								: SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
						}
						else
						{
							SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
							SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels));
						}
					}
					//ms_old_wtype = GET_VEHICLE_WHEEL_TYPE(Static_12);
					//ms_old_windex = GET_VEHICLE_MOD(Static_12, 23);
					//ms_old_windexBB = GET_VEHICLE_MOD(Static_12, 24);
					//ms_wheel_windice_pressed = true;
				}
			}
		}
	}

	void MSWheels_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		using namespace MSWheels_catind;

		GTAvehicle vehicle = Static_12;
		bool set_mspaints_index_4 = 0,
			set_msrgb_index_4 = 0,
			MSWheelsCustomTyres_ = 0,
			MSWheelsBPTyresOn_ = 0,
			MSWheelsDriftTyresOn_ = 0,
			MSWheelsStockWheels_ = 0;

		UINT i;


		Model Static_12_veh_model = GET_ENTITY_MODEL(Static_12);
		bool isBike = Static_12_veh_model.IsBike();
		INT wheel_no = GET_VEHICLE_MOD(Static_12, 23);
		INT ms_custom_tyres = GET_VEHICLE_MOD_VARIATION(Static_12, 23);
		BOOL ms_drift_tyres = _GET_DRIFT_TYRES_ENABLED(Static_12);
		//if (!selectwheel)
		{
			lastwheeltype = GET_VEHICLE_WHEEL_TYPE(Static_12);
			lastfwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels);
			lastbwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels);
		}
		//if (ms_custom_tyres == 0) activeWheelType = 1;
		//GET_VEHICLE_TYRE_SMOKE_COLOR(Static_12, &wheels_smoke_r, &wheels_smoke_g, &wheels_smoke_b);
		selectwheel = true;
		setwheel = true;
		AddTitle(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels"));

		AddOption(Game::GetGXTEntry("CMOD_MOD_WCL", "Rim Colour"), set_mspaints_index_4, nullFunc, -1, true); // Wheel Colour CMOD_MOD_WCL

		AddTickol(Game::GetGXTEntry("CMOD_TYR_0", "Stock Wheels"), GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels) < 0, MSWheelsStockWheels_, MSWheelsStockWheels_);

		for (i = 0; i < vWheelTNames.size(); i++)
		{
			const bool ibw = (i == WheelType::BikeWheels);
			if (isBike && ibw || !isBike && !ibw)
				__AddpointOption(vWheelTNames[i], i);
		}

		AddLocal("CMOD_TYR_1", ms_custom_tyres, MSWheelsCustomTyres_, MSWheelsCustomTyres_, true); // Custom Tyres
		AddLocal("CMOD_TYR_2", GET_VEHICLE_TYRES_CAN_BURST(Static_12) == FALSE, MSWheelsBPTyresOn_, MSWheelsBPTyresOn_, true); // Bulletproof Tyres
		AddLocal("Drift Tyres", _GET_DRIFT_TYRES_ENABLED(Static_12), MSWheelsDriftTyresOn_, MSWheelsDriftTyresOn_, true); // Drift Tyres
		AddOption("Remove Tires", null, nullFunc, SUB::MS_TYRESBURST);

		AddOption(Game::GetGXTEntry("CMOD_MOD_TYR3", "Tire Smoke Colour"), set_msrgb_index_4, nullFunc, SUB::MSPAINTS_RGB);
		if (*Menu::currentopATM == Menu::printingop)
			Add_preset_colour_options_previews(vehicle.TyreSmokeColour_get());



		if (set_mspaints_index_4) {
			ms_curr_paint_index = 4;
			//if (GET_VEHICLE_MOD(Static_12, 23) > -1) Menu::SetSub_new(SUB::MSPAINTS2_WHEELS);
			//else Game::Print::PrintBottomCentre("~r~Error:~s~ Colours cannot be applied to stock wheels.");
			if (GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels) < 0)
				Game::Print::PrintBottomCentre("~b~Note:~s~ Colours cannot always be applied to stock wheels.");
			Menu::SetSub_new(SUB::MSPAINTS2_WHEELS);
			return;
		}


		if (set_msrgb_index_4) { bit_MSPaints_RGB_mode = 4; return; }


		if (MSWheelsStockWheels_) {
			vehicle.RequestControlOnce();
			vehicle.RemoveMod(VehicleMod::FrontWheels);
			vehicle.RemoveMod(VehicleMod::BackWheels);
			return;
		}

		if (MSWheelsCustomTyres_) {
			vehicle.RequestControlOnce();
			vehicle.SetMod(VehicleMod::FrontWheels, wheel_no, !ms_custom_tyres);
			vehicle.SetMod(VehicleMod::BackWheels, wheel_no, !ms_custom_tyres);
			return;
		}

		if (MSWheelsBPTyresOn_) {
			vehicle.RequestControlOnce();
			vehicle.CanTyresBurst_set(!vehicle.CanTyresBurst_get());
			return;
		}

		if (MSWheelsDriftTyresOn_) {
			vehicle.RequestControlOnce();
			vehicle.CanTyresDrift_set(!vehicle.CanTyresDrift_get());
			return;
		}
	}
	void MSWheels2_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		using namespace MSWheels_catind;
		int& wtype = ms_curr_paint_index, & chrtype = bit_MSPaints_RGB_mode;
		setwheel = true;

		lastwheeltype = 6;
		lastfwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels);
		lastbwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels);

		AddTitle(vWheelTNames[wtype]);

		//if (DOES_ENTITY_EXIST(Static_12))
		//{
		//	SET_VEHICLE_WHEEL_TYPE(Static_12, ms_old_wtype);
		//	SET_VEHICLE_MOD(Static_12, 23, ms_old_windex, 0); // GET_VEHICLE_MOD_VARIATION(Static_12, 23)
		//	SET_VEHICLE_MOD(Static_12, 24, ms_old_windex, 0);
		//}

		//if (wtype == WheelType::Bennys || wtype == WheelType::BennysBespoke)
		//if (true) //no need to split chrome and normal with addon wheels.    
		//{
			//if (ms_bit_bike_back) // Can probably remove this whole if statement with this exclusively working for bike wheels now - ijc
			//{
		bool bFrontPressed = false, bBackPressed = false;
		AddOption("Front", bFrontPressed, nullFunc, SUB::MSWHEELS3); if (bFrontPressed)
		{
			chrtype = 0;
			SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
			ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
		}
		AddOption("Rear", bBackPressed, nullFunc, SUB::MSWHEELS3); if (bBackPressed)
		{
			chrtype = 2;
			SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
			ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::BackWheels);
		}
		//}
		/*else // Not a bike.
		{
			bool bFrontPressed = false;
			AddOption("Front & Rear", bFrontPressed, nullFunc, SUB::MSWHEELS3); if (true) //bypass this menu for all but bikes
			{
				chrtype = 0;
				SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
				ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
				Menu::SetSub_delayed = SUB::MSWHEELS3;
				return;
			}
		}*/
		//}
		/*else // Unused - remove?
		{
			if (ms_bit_bike_back)
			{
				bool front_normal = 0, front_chrome = 0, back_normal = 0, back_chrome = 0;

				AddBreak("CMOD_WHE0_0"); // Front Wheel
				AddOption("Stock", front_normal, nullFunc, SUB::MSWHEELS3);
				AddOption("Chrome", front_chrome, nullFunc, SUB::MSWHEELS3);

				AddBreak("CMOD_WHE0_1"); // Rear Wheel
				AddOption("Stock", back_normal, nullFunc, SUB::MSWHEELS3);
				AddOption("Chrome", back_chrome, nullFunc, SUB::MSWHEELS3);

				if (front_normal) {
					chrtype = 0;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
				}
				else if (front_chrome) {
					chrtype = 1;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
				}
				else if (back_normal) {
					chrtype = 2;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::BackWheels);
				}
				else if (back_chrome) {
					chrtype = 3;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::BackWheels);
				}
			}
			else
			{
				bool type_normal = 0, type_chrome = 0;

				AddOption("Stock Rims", type_normal, nullFunc, SUB::MSWHEELS3);
				AddOption("Chrome Rims", type_chrome, nullFunc, SUB::MSWHEELS3);

				if (type_normal) {
					chrtype = 0;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
				}
				else if (type_chrome) {
					chrtype = 1;
					SET_VEHICLE_WHEEL_TYPE(Static_12, wtype);
					ms_max_windices = GET_NUM_VEHICLE_MODS(Static_12, VehicleMod::FrontWheels);
				}
			}
		}*/
	}
	void MSWheels3_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		using namespace MSWheels_catind;
		int& wtype = ms_curr_paint_index, & chrtype = bit_MSPaints_RGB_mode, i;
		//switch (wtype)
		//{
		//case SPORT: max = 20; break;
		//case MUSCLE: max = 18; break;
		//case LOWRIDER: max = 15; break;
		//case SUV: max = 19; break;
		//case OFFROAD: max = 10; break;
		//case TUNER: max = 24; break;
		//case BIKE: max = 13; break;
		//case HIGHEND: max = 20; break;
		//}
		//if (chrtype == 1 || chrtype == 3) // if chrome selected
		//{
		//	start = max;
		//	max *= 2;
		//}
		//max -= 1;


		int windices2;
		if (wtype == WheelType::BikeWheels) // Bike Normal/Chrome
		{
			bool bIsChromeSelected = chrtype == 1 || chrtype == 3;

			AddTitle(bIsChromeSelected ? "Chrome Wheels" : "Bike Wheels");

			std::array<int, 5> ids{ 0, 13, 26, 48, ms_max_windices };
			for (UINT8 j = bIsChromeSelected ? 1 : 0; j < ids.size(); j += 2)
			{
				for (i = ids[j]; i < ids[j + 1]; i++)
				{
					__AddOption(get_mod_text_label(Static_12, VehicleMod::FrontWheels, i, false), Static_12, wtype, i, chrtype == 2);
				}
			}
			if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back)) // this has been split out for bikes, see further comments on the original section below (line 2575)
			{
				setwheel = false;
				(chrtype == 2) ? SET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels, lastbwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::BackWheels))
					: SET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels, lastfwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::FrontWheels));
			}
			return;
		}
		else //if (wtype == WheelType::Bennys || wtype == WheelType::BennysBespoke) // Benny's
		{
			windices2 = ms_max_windices;	//bypass normal/chrome split
			i = 0;
		}
		/*else if (chrtype == 0 || chrtype == 2) // Normal
		{
			windices2 = ms_max_windices / 2;
			i = 0;
		}
		else if (chrtype == 1 || chrtype == 3) // Chrome
		{
			windices2 = ms_max_windices;
			i = ms_max_windices / 2;
		}*/
		bool bIsChromeSelected = chrtype == 1 || chrtype == 3;
		AddTitle(bIsChromeSelected ? "Chrome Wheels" : "Normal Wheels");
		for (; i < windices2; i++)
		{
			__AddOption(get_mod_text_label(Static_12, VehicleMod::FrontWheels, i, false), Static_12, wtype, i, chrtype == 2);
		}

		if (_globalLSC_Customs)
		{
			if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back)) // running this here prevents the sript from working for bikes due to (I believe) the return on line 2459. Moving it to before that section causes a crash when using a car. 
			{
				if (wtype != WheelType::BikeWheels)
				{
					setwheel = false;
					SET_VEHICLE_WHEEL_TYPE(Static_12, lastwheeltype);
					SET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels, lastfwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::FrontWheels));
					SET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels, lastbwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::BackWheels));
				}
			}
		}
	}
	void MSTyresBurst_()
	{
		GTAvehicle vehicle = Static_12;

		AddTitle("Remove Tyres");

		std::vector<std::string> vCaptions_tyres{ "FrontLeft", "FrontRight", "2", "3", "BackLeft", "BackRight", "6", "7", "8" };
		for (int i = 0; i < vCaptions_tyres.size(); i++)
		{
			bool bBurstPressed = false, bUnburstPressed = false;
			AddTickol(vCaptions_tyres[i], vehicle.IsTyreBursted(i), bBurstPressed, bUnburstPressed, TICKOL::CROSS);
			if (bBurstPressed)
			{
				vehicle.RequestControl(800);
				vehicle.CanTyresBurst_set(true);
				vehicle.BurstTyre(i);
			}
			else if (bUnburstPressed)
			{
				std::vector<int> vTyresBurstedAlready;
				for (int j = 0; j < vCaptions_tyres.size(); j++)
				{
					if (j != i)
					{
						if (vehicle.IsTyreBursted(j))
							vTyresBurstedAlready.push_back(j);
					}
				}
				vehicle.RequestControl(600);
				for (int j = 0; j < vCaptions_tyres.size(); j++)
					vehicle.FixTyre(j);
				vehicle.Repair(false);
				for (auto& ttb : vTyresBurstedAlready)
					vehicle.BurstTyre(ttb);
			}
		}

		bool bMakeAllWheelsInvis = false;
		AddLocal("Make All Wheels Invisible", are_vehicle_wheels_invisible(vehicle), bMakeAllWheelsInvis, bMakeAllWheelsInvis); if (bMakeAllWheelsInvis)
		{
			vehicle.RequestControl(600);
			if (!are_vehicle_wheels_invisible(vehicle))
			{
				set_vehicle_wheels_invisible(vehicle, true);
			}
			else
			{
				set_vehicle_wheels_invisible(vehicle, false);
				Game::Print::PrintBottomCentre("~b~Note:~s~ It may take a while for the wheels to come back.");
			}
		}

	}

	// Windows

	namespace MSWindows_catind
	{
		enum MSWINDOWS_MODE : UINT8 { MSWINDOWS_MODE_OPEN, MSWINDOWS_MODE_CLOSE, MSWINDOWS_MODE_BREAK, MSWINDOWS_MODE_FIX, MSWINDOWS_MODE_REMOVE };
		UINT8 msWindows_mode = 0;

		const std::vector<std::string> msWindows_mode_names{ "Open", "Close", "Break", "Fix", "Remove" };
		const std::vector<std::string> msWindows_window_names{ "Front Left", "Front Right", "Back Left", "Back Right" };
		//const std::vector<std::string> msWindows_wintint_names{ "None", "Black", "Dark Smoke", "Light Smoke", "Stock", "Limo", "Green" };
		const std::vector<std::string> msWindows_wintint_names{ "None", "Black", "CMOD_WIN_2", "CMOD_WIN_1", "Stock", "CMOD_WIN_3", "Green" };

		void DoWindow(GTAvehicle vehicle, VehicleWindow window, UINT8 mode)
		{
			vehicle.RequestControl();

			switch (mode)
			{
			case MSWINDOWS_MODE_OPEN:
				vehicle.RollDownWindow(window);
				break;
			case MSWINDOWS_MODE_CLOSE:
				vehicle.RollUpWindow(window);
				break;
			case MSWINDOWS_MODE_BREAK:
				vehicle.SmashWindow(window);
				break;
			case MSWINDOWS_MODE_FIX:
				vehicle.FixWindow(window);
				break;
			case MSWINDOWS_MODE_REMOVE:
				vehicle.RemoveWindow(window);
				break;
			}
		}

		void MSWindows_()
		{
			GTAvehicle vehicle = Static_12;
			if (!vehicle.Exists())
			{
				Menu::SetSub_previous();
				return;
			}

			int ms_wintint = vehicle.WindowTint_get();
			if (ms_wintint < 0 || ms_wintint >= msWindows_wintint_names.size()) ms_wintint = 0;
			//vehicle.RequestControlOnce();

			AddTitle("Windows");

			bool ms_wintint_plus = false, ms_wintint_minus = false;
			AddTexter("CMOD_GLD2_2", ms_wintint, msWindows_wintint_names, null, ms_wintint_plus, ms_wintint_minus, true); // Window Tint
			if (ms_wintint_plus) { if (ms_wintint < msWindows_wintint_names.size() - 1) ms_wintint++; vehicle.WindowTint_set(ms_wintint); }
			if (ms_wintint_minus) { if (ms_wintint > 0) ms_wintint--; vehicle.WindowTint_set(ms_wintint); }

			AddBreak("---Status---");

			bool msWindows_mode_plus = false, msWindows_mode_minus = false;
			AddTexter("Action", msWindows_mode, msWindows_mode_names, null, msWindows_mode_plus, msWindows_mode_minus);
			if (msWindows_mode_plus) { if (msWindows_mode < msWindows_mode_names.size() - 1) msWindows_mode++; }
			if (msWindows_mode_minus) { if (msWindows_mode > 0) msWindows_mode--; }

			for (UINT8 i = 0; i < msWindows_window_names.size(); i++)
			{
				bool bWindowNamePressed = false;
				AddOption(msWindows_window_names[i], bWindowNamePressed); if (bWindowNamePressed)
				{
					MSWindows_catind::DoWindow(vehicle, VehicleWindow(i), msWindows_mode);
				}
			}

			bool bAllWindowsPressed = false;
			AddOption("All Windows", bAllWindowsPressed); if (bAllWindowsPressed)
			{
				for (UINT8 i = 0; i < msWindows_window_names.size(); i++)
				{
					MSWindows_catind::DoWindow(vehicle, VehicleWindow(i), msWindows_mode);
				}
			}

		}
	}

	// Doors

	void AddmsdoorsOption_(const std::string& text, GTAvehicle vehicle, VehicleDoor door, UINT8 supposedAction, bool instantly = false, bool loose = false)
	{
		auto action = supposedAction;
		bool conditionForTick = false;

		switch (supposedAction)
		{
		case 0: // Open
			conditionForTick = vehicle.IsDoorOpen(door);
			action = conditionForTick ? 2 : 0;
			break;
		case 1: // Open All
			conditionForTick = true;
			for (auto& d : vehicle.Doors_get())
				conditionForTick = conditionForTick && vehicle.IsDoorOpen(d);
			action = conditionForTick ? 3 : 1;
			break;
		}

		bool pressed = false;
		AddTickol(text, conditionForTick, pressed, pressed); if (pressed)
		{
			vehicle.RequestControl();
			switch (action)
			{
			case 0: // Open
				vehicle.OpenDoor(door, loose, instantly, true);
				break;
			case 1: // Open All
				vehicle.OpenDoor(VehicleDoor::FrontLeftDoor, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::FrontRightDoor, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::BackLeftDoor, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::BackRightDoor, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::Hood, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::Trunk, loose, instantly, true);
				vehicle.OpenDoor(VehicleDoor::Trunk2, loose, instantly, true); // Not used
				break;
			case 2: // Close
				vehicle.CloseDoor(door, instantly, true);
				break;
			case 3: // Close All
				vehicle.CloseDoor(VehicleDoor::FrontLeftDoor, instantly, true);
				vehicle.CloseDoor(VehicleDoor::FrontRightDoor, instantly, true);
				vehicle.CloseDoor(VehicleDoor::BackLeftDoor, instantly, true);
				vehicle.CloseDoor(VehicleDoor::BackRightDoor, instantly, true);
				vehicle.CloseDoor(VehicleDoor::Hood, instantly, true);
				vehicle.CloseDoor(VehicleDoor::Trunk, instantly, true);
				vehicle.CloseDoor(VehicleDoor::Trunk2, instantly, true); // Not used
				break;
			case 4: // Remove
				vehicle.BreakDoor(door, instantly);
				break;
			case 5: // Remove All
				vehicle.BreakAllDoors(instantly);
				break;
			case 6: // Fix
				vehicle.FixDoor(door);
				break;
			case 7: // Fix All
				vehicle.FixAllDoors();
				//SET_VEHICLE_FIXED(vehicle.Handle());
				break;
			}
		}
	}
	void MSDoors_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		GTAvehicle vehicle = Static_12;

		AddTitle("Doors");

		std::vector<std::string> vDoorLockNames
		{
			"None",
			"Unlocked",
			"Locked",
			"LockedForPlayer",
			"ChildLock",
			"Unknown 5",
			"Unknown 6",
			"CanBeBrokenInto",
			"CanBeBrokenIntoPersist",
			"Unknown 9",
			"CannotBeTriedToBeEntered"
		};
		int lockStatus = static_cast<int>(vehicle.LockStatus_get());
		bool bLockStatus_plus = false, bLockStatus_minus = false;
		AddTexter("Lock Status", lockStatus, vDoorLockNames, null, bLockStatus_plus, bLockStatus_minus);
		if (bLockStatus_plus) { if (lockStatus < vDoorLockNames.size() - 1) { lockStatus++; vehicle.LockStatus_set(static_cast<VehicleLockStatus>(lockStatus)); } }
		if (bLockStatus_minus) { if (lockStatus > 0) { lockStatus--; vehicle.LockStatus_set(static_cast<VehicleLockStatus>(lockStatus)); } }

		static UINT8 ____ms_doors_action_index = 0;
		auto& action = ____ms_doors_action_index;

		std::vector<std::string> vActionNames{ "Open/Close", "", "Close", "", "Remove", "", "Fix", "" };
		bool bAction_plus = false, bAction_minus = false;
		AddTexter("Action", action, vActionNames, null, bAction_plus, bAction_minus);
		if (bAction_plus) { if (action < vActionNames.size() - 1) action++; while (!vActionNames[action].length()) { action++; if (action >= vActionNames.size()) { action = 0; } } }
		if (bAction_minus) { if (action > 0) action--; while (!vActionNames[action].length()) { action--; if (action < 0) { action = (UINT8)(vActionNames.size() - 1); } } }

		switch (action)
		{
		case 0: // Open
		case 2: // Close
		case 4: // Remove
		case 6: // Fix
			AddmsdoorsOption_("Driver Door", vehicle, VehicleDoor::FrontLeftDoor, action, action == 4, false);
			AddmsdoorsOption_("Passenger Door", vehicle, VehicleDoor::FrontRightDoor, action, action == 4, false);
			AddmsdoorsOption_("Rear Left", vehicle, VehicleDoor::BackLeftDoor, action, action == 4, false);
			AddmsdoorsOption_("Rear Right", vehicle, VehicleDoor::BackRightDoor, action, action == 4, false);
			AddmsdoorsOption_("Hood", vehicle, VehicleDoor::Hood, action, action == 4, false);
			AddmsdoorsOption_("Trunk", vehicle, VehicleDoor::Trunk, action, action == 4, false);
			//case 6: // Fix
			AddmsdoorsOption_("All", vehicle, VehicleDoor::Hood, action + 1, action == 4, false);
			break;
		}

	}

	//Lights

	bool leftind = 0;
	bool rightind = 0;
	bool hazard = 0;
	void MSLights_()
	{
		GTAvehicle vehicle = Static_12;
		bool bHLightsOnTogglePressed = false;
		AddTickol("Headlights", vehicle.LightsOn_get(), bHLightsOnTogglePressed, bHLightsOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		if (bHLightsOnTogglePressed) vehicle.LightsOn_set(!vehicle.LightsOn_get());
		bool bLindOnTogglePressed = false;
		AddTickol("Left Indicator", leftind, bLindOnTogglePressed, bLindOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		if (bLindOnTogglePressed)
		{
			rightind = false;
			hazard = false;
			vehicle.LeftIndicatorLightOn_set(!leftind);
			vehicle.RightIndicatorLightOn_set(false);
			leftind = !leftind;
		}
		bool bRindOnTogglePressed = false;
		AddTickol("Right Indicator", rightind, bRindOnTogglePressed, bRindOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		if (bRindOnTogglePressed)
		{
			leftind = false;
			hazard = false;
			vehicle.RightIndicatorLightOn_set(!rightind);
			vehicle.LeftIndicatorLightOn_set(false);
			rightind = !rightind;
		}
		bool bHzdOnTogglePressed = false;
		AddTickol("Hazard Lights", hazard, bHzdOnTogglePressed, bHzdOnTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		if (bHzdOnTogglePressed)
		{
			if (rightind == leftind)
			{
				rightind = false;
				leftind = false;
				vehicle.RightIndicatorLightOn_set(!hazard);
				vehicle.LeftIndicatorLightOn_set(!hazard);
				hazard = !hazard;
			}
			else
			{
				rightind = false;
				leftind = false;
				vehicle.RightIndicatorLightOn_set(true);
				vehicle.LeftIndicatorLightOn_set(true);
				hazard = true;
			}

		}
	}

	// Extras

	void MSExtra_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		GTAvehicle thisVehicle = Static_12;

		AddTitle("Extras"); // CMOD_MOD_GLD2
		for (UINT8 i = 0; i <= 60; i++)
		{
			if (!thisVehicle.DoesExtraExist(i))
				continue;
			bool bExtraPressed = false;
			AddTickol("Extra " + std::to_string(i), thisVehicle.ExtraOn_get(i), bExtraPressed, bExtraPressed, TICKOL::CARTHING); if (bExtraPressed)
			{
				thisVehicle.ExtraOn_set(i, !thisVehicle.ExtraOn_get(i));
			}
		}

	}

	// Neons

	void MSNeons_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		GTAvehicle vehicle = Static_12;

		AddTitle(Game::GetGXTEntry("PIM_PVEO_004", "Neons Lights"));

		for (auto& i : std::map<VehicleNeonLight, std::pair<Hash, std::string>>{
			{ VehicleNeonLight::Left,{ 0xCE8DADF3, "Left" } },
			{ VehicleNeonLight::Right,{ 0x92E936A7, "Right" } },
			{ VehicleNeonLight::Front,{ 0x79ABE687, "Front" } },
			{ VehicleNeonLight::Back,{ 0x6BECCB09, "Back" } }
			})
		{
			bool bPressed_on = false, bPressed_off = false;
			AddTickol(i.second.second, vehicle.IsNeonLightOn(i.first), bPressed_on, bPressed_off, TICKOL::CARTHING);
			if (bPressed_on || bPressed_off)
			{
				vehicle.RequestControl(300);
				vehicle.SetNeonLightOn(i.first, bPressed_on);
			}
		}

		bool rgbmode2 = false;
		AddOption("Set Colour", rgbmode2, nullFunc, SUB::MSPAINTS_RGB); if (rgbmode2)
		{
			bit_MSPaints_RGB_mode = 2;
		}
		if (*Menu::currentopATM == Menu::printingop)
			Add_preset_colour_options_previews(vehicle.NeonLightsColour_get());

	}

	// Engine sound

	void MSEngineSound_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		AddOption("Select Vehicle", null, nullFunc, SUB::LIST_VEHICLECATS);

		bool bInputModelPressed = false;
		AddOption("Input Model", bInputModelPressed); if (bInputModelPressed)
		{
			std::string inputStr = (Game::InputBox("", 28U, "Enter vehicle model name:"));
			if (inputStr.length())
			{
				if (!Model(inputStr).IsVehicle())
					Game::Print::PrintError_InvalidModel();
				else
				{
					GTAvehicle vehicle = Static_12;
					vehicle.RequestControl(300);
					set_vehicle_engine_sound_name(vehicle, inputStr);
				}
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::CustomsEngineSoundModelName, std::string(), 28U, "Enter vehicle model name:");
			//OnscreenKeyboard::State::arg1._int = Static_12;
		}

	}

}
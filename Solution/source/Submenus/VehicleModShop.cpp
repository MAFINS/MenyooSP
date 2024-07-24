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
#include "..\Util\FileLogger.h"
#include "..\Scripting\enums.h"
#include "..\main.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\Game.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\World.h"

#include "Settings.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>

namespace sub
{
	bool lowersuspension = 0;
	int lastMod = -2;
	bool selectmod = false;
	int lastpaint, lastpearl, lastr, lastg, lastb;
	bool getpaint = true, iscustompaint;

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
		{ "Alloy", 156, -1 },
		{ "Black", 0, -1 },
		{ "Carbon Black (Graphite)", 1, -1 },
		{ "Anthracite Black", 11, -1 },
		{ "Black Steel", 2, -1 },
		{ "Stone Silver", 8, -1 },
		{ "Frost White (Util Off White)", 122, -1 },
		{ "Red", 27, -1 },
		{ "Blaze Red", 30, -1 },
		{ "Garnet Red (Util Garnet Red)", 45, -1 },
		{ "Candy Red", 35, -1 },
		{ "Sunset Red", 33, -1 },
		{ "Salmon Pink", 136, -1 },
		{ "Hot Pink", 135, -1 },
		{ "Sunrise Orange", 36, -1 },
		{ "Orange (Matte Orange)", 41, -1 },
		{ "Bright Orange", 138, -1 },
		{ "Gold", 37, -1 },
		{ "Straw Brown", 99, -1 },
		{ "Dark Copper (Bronze)", 90, -1 },
		{ "Dark Ivory (Creek Brown)", 95, -1 },
		{ "Dark Brown (Worn Dark Brown)", 115, -1 },
		{ "Bronze (Util Medium Brown)", 109, -1 },
		{ "Dark Earth (Matte Dark Earth)", 153, -1 },
		{ "Desert Tan (Matte Desert Tan)", 154, -1 },
		{ "Yellow", 88, -1 },
		{ "Race Yellow", 89, -1 },
		{ "Yellow Bird (Dew Yellow)", 91, -1 },
		{ "Lime Green (Matte Light Green)", 55, -1 },
		{ "Pea Green", 125, -1 },
		{ "Green (Bright Green)", 53, -1 },
		{ "Dark Green (Util Dark Green)", 56, -1 },
		{ "Olive Green (Matte Forest Green)", 151, -1 },
		{ "Midnight Blue (Matte Dark Blue)", 82, -1 },
		{ "Royal Blue (Blue)", 64, -1 },
		{ "Baby Blue (Worn Baby Blue)", 87, -1 },
		{ "Bright Blue (Ultra Blue)", 70, -1 },
		{ "Fluorescent Blue", 140, -1 },
		{ "Slate Blue (Util Bright Blue)", 81, -1 },
		{ "Schafter Purple (Bright Purple)", 145, -1 },
		{ "Midnight Purple", 142, -1 },
	};

	const std::vector<NamedVehiclePaint> PAINTS_INTERIOR
	{
		{ "Black", 0, -1 },
		{ "Graphite", 1, -1 },
		{ "Anthracite Black", 11, -1 },
		{ "Black Steel", 2, -1 },
		{ "Dark Steel", 3, -1 },
		{ "Bluish Silver", 5, -1 },
		{ "Rolled Steel", 6, -1 },
		{ "Shadow Silver", 7, -1 },
		{ "Stone Silver", 8, -1 },
		{ "Midnight Silver", 9, -1 },
		{ "Cast Iron Silver", 10, -1 },
		{ "Red", 27, -1 },
		{ "Torino Red", 28, -1 },
		{ "Lava Red", 150, -1 },
		{ "Blaze Red", 30, -1 },
		{ "Grace Red", 31, -1 },
		{ "Garnet Red", 32, -1 },
		{ "Sunset Red", 33, -1 },
		{ "Cabernet Red", 34, -1 },
		{ "Wine Red", 143, -1 },
		{ "Candy Red", 35, -1 },
		{ "Pfister Pink", 137, -1 },
		{ "Salmon Pink", 136, -1 },
		{ "Sunrise Orange", 36, -1 },
		{ "Orange", 38, -1 },
		{ "Bright Orange", 138, -1 },
		{ "Bronze", 90, -1 },
		{ "Yellow", 88, -1 },
		{ "Race Yellow", 89, -1 },
		{ "Dew Yellow", 91, -1 },
		{ "Dark Green", 49, -1 },
		{ "Racing Green", 50, -1 },
		{ "Sea Green", 51, -1 },
		{ "Olive Green", 52, -1 },
		{ "Bright Green", 53, -1 },
		{ "Gasoline Green", 54, -1 },
		{ "Lime Green", 92, -1 },
		{ "Midnight Blue", 141, -1 },
		{ "Galaxy Blue", 61, -1 },
		{ "Dark Blue", 62, -1 },
		{ "Saxon Blue", 63, -1 },
		{ "Mariner Blue", 65, -1 },
		{ "Harbor Blue", 66, -1 },
		{ "Diamond Blue", 67, -1 },
		{ "Surf Blue", 68, -1 },
		{ "Nautical Blue", 69, -1 },
		{ "Racing Blue", 73, -1 },
		{ "Ultra Blue", 70, -1 },
		{ "Light Blue", 74, -1 },
		{ "Chocolate Brown", 96, -1 },
		{ "Bison Brown", 101, -1 },
		{ "Creek Brown", 95, -1 },
		{ "Feltzer Brown", 94, -1 },
		{ "Maple Brown", 97, -1 },
		{ "Beechwood Brown", 103, -1 },
		{ "Sienna Brown", 104, -1 },
		{ "Saddle Brown", 98, -1 },
		{ "Moss Brown", 100, -1 },
		{ "Woodbeech Brown", 102, -1 },
		{ "Straw Brown", 99, -1 },
		{ "Sandy Brown", 105, -1 },
		{ "Bleached Brown", 106, -1 },
		{ "Spinnaker Purple", 72, -1 },
		{ "Midnight Purple", 146, -1 },
		{ "Bright Purple", 145, -1 },
		{ "Cream", 107, -1 },
		{ "Ice White", 111, -1 },
		{ "Frost White", 112, -1 },
	};

	const std::vector<NamedVehiclePaint> PAINTS_DASHBOARD
	{
		{ "Silver", 4, -1 },
		{ "Bluish Silver", 5, -1 },
		{ "Rolled Steel", 6, -1 },
		{ "Shadow Silver", 7, -1 },
		{ "Ice White", 111, -1 },
		{ "Frost White", 112, -1 },
		{ "Cream", 107, -1 },
		{ "Sienna Brown", 104, -1 },
		{ "Saddle Brown", 98, -1 },
		{ "Moss Brown", 100, -1 },
		{ "Woodbeech Brown", 102, -1 },
		{ "Straw Brown", 99, -1 },
		{ "Sandy Brown", 105, -1 },
		{ "Bleached Brown", 106, -1 },
		{ "Gold", 37, -1 },
		{ "Bronze", 90, -1 },
		{ "Yellow", 88, -1 },
		{ "Race Yellow", 89, -1 },
		{ "Dew Yellow", 91, -1 },
		{ "Orange", 38, -1 },
		{ "Bright Orange", 138, -1 },
		{ "Sunrise Orange", 36, -1 },
		{ "Red", 27, -1 },
		{ "Torino Red", 28, -1 },
		{ "Formula Red", 29, -1 },
		{ "Lava Red", 150, -1 },
		{ "Blaze Red", 30, -1 },
		{ "Grace Red", 31, -1 },
		{ "Garnet Red", 32, -1 },
		{ "Candy Red", 35, -1 },
		{ "Hot Pink", 135, -1 },
		{ "Pfister Pink", 137, -1 },
		{ "Salmon Pink", 136, -1 },
		{ "Schafter Purple", 71, -1 },
		{ "Bright Purple", 145, -1 },
		{ "Saxon Blue", 63, -1 },
		{ "Blue", 64, -1 },
		{ "Mariner Blue", 65, -1 },
		{ "Harbor Blue", 66, -1 },
		{ "Diamond Blue", 67, -1 },
		{ "Surf Blue", 68, -1 },
		{ "Nautical Blue", 69, -1 },
		{ "Racing Blue", 73, -1 },
		{ "Ultra Blue", 70, -1 },
		{ "Light Blue", 74, -1 },
		{ "Sea Green", 51, -1 },
		{ "Bright Green", 53, -1 },
		{ "Gasoline Green", 54, -1 },
		{ "Lime Green", 92, -1 },
	};

	const std::vector<NamedVehiclePaint> PAINTS_UTIL
	{
		{ "Black", COLOR_UTIL_BLACK, -1 },
		{ "Black Poly", COLOR_UTIL_BLACK_POLY, COLOR_UTIL_BLACK_POLY },
		{ "Dark Silver", COLOR_UTIL_DARK_SILVER, -1 },
		{ "Silver", 18, COLOR_CLASSIC_ICE_WHITE },
		{ "Alloy", COLOR_METALS_DEFAULT_ALLOY, COLOR_METALS_DEFAULT_ALLOY },
		{ "Gun Metal", COLOR_UTIL_GUN_METAL, COLOR_UTIL_GUN_METAL },
		{ "Shadow Silver", COLOR_UTIL_SHADOW_SILVER, COLOR_UTIL_SHADOW_SILVER },
		{ "Red", COLOR_UTIL_RED, COLOR_UTIL_RED },
		{ "Bright Red", COLOR_UTIL_BRIGHT_RED, COLOR_UTIL_BRIGHT_RED },
		{ "Garnet Red", COLOR_UTIL_GARNET_RED, COLOR_CLASSIC_BLACK },
		{ "Dark Green", 56, 56 },
		{ "Green", 57, 57 },
		{ "Dark Blue", 75, COLOR_WORN_BABY_BLUE },
		{ "Midnight Blue", 76, 77 },
		{ "Blue", 77, 0 },
		{ "Sea Foam Blue", 78, 80 },
		{ "Lightning Blue", 79, -1 },
		{ "Maui Blue Poly", 80, 68 },
		{ "Bright Blue", 81, -1 },
		{ "Brown", COLOR_UTIL_BROWN, -1 },
		{ "Medium Brown", COLOR_UTIL_MEDIUM_BROWN, COLOR_UTIL_MEDIUM_BROWN },
		{ "Light Brown", COLOR_UTIL_LIGHT_BROWN, COLOR_UTIL_LIGHT_BROWN },
		{ "Off White", COLOR_UTIL_OFF_WHITE, COLOR_UTIL_OFF_WHITE },
		{ "Pure White", COLOR_CLASSIC_PURE_WHITE, COLOR_CLASSIC_BLACK },
		{ "Police Blue", COLOR_CLASSIC_POLICE_BLUE, -1 },
		{ "Pearl Gold", COLOR_METALS_PEARLESCENT_GOLD, -1 },
	};

	const std::vector<NamedVehiclePaint> PAINTS_WORN
	{
		{ "Black", COLOR_WORN_BLACK, COLOR_CLASSIC_BLACK },
		{ "Graphite", COLOR_WORN_GRAPHITE, COLOR_CLASSIC_SILVER },
		{ "Silver Grey", COLOR_WORN_SILVER_GREY, COLOR_CLASSIC_ICE_WHITE },
		{ "Silver", COLOR_WORN_SILVER, COLOR_WORN_SILVER },
		{ "Bluish Silver", COLOR_WORN_BLUE_SILVER, COLOR_CLASSIC_ICE_WHITE },
		{ "Shadow Silver", COLOR_WORN_SHADOW_SILVER, COLOR_CLASSIC_DIAMOND_BLUE },
		{ "Red", COLOR_WORN_RED, COLOR_CLASSIC_BLACK },
		{ "Golden Red", COLOR_WORN_GOLDEN_RED, COLOR_WORN_GOLDEN_RED },
		{ "Dark Red", COLOR_WORN_DARK_RED, COLOR_CLASSIC_BLACK },
		{ "Green", 58, 58 },
		{ "Dark Green", 59, 59 },
		{ "Sea Wash", COLOR_WORN_SEA_WASH, COLOR_WORN_SEA_WASH },
		{ "Dark Blue", COLOR_WORN_DARK_BLUE, COLOR_WORN_DARK_BLUE },
		{ "Blue", COLOR_WORN_BLUE, COLOR_WORN_BLUE },
		{ "Baby Blue", COLOR_WORN_BABY_BLUE, COLOR_CLASSIC_BLACK },
		{ "Honey Beige", COLOR_WORN_HONEY_BEIGE, COLOR_WORN_HONEY_BEIGE },
		{ "Brown", COLOR_WORN_BROWN, COLOR_CLASSIC_BLACK },
		{ "Dark Brown", COLOR_WORN_DARK_BROWN, -1 },
		{ "Straw Beige", COLOR_WORN_STRAW_BEIGE, COLOR_WORN_STRAW_BEIGE },
		{ "White", COLOR_WORN_WHITE, COLOR_WORN_WHITE },
		{ "Off White", COLOR_WORN_OFF_WHITE, COLOR_CLASSIC_BLACK },
		{ "Orange", COLOR_WORN_ORANGE, COLOR_CLASSIC_BLACK_STEEL },
		{ "Light Orange", COLOR_WORN_LIGHT_ORANGE, COLOR_WORN_LIGHT_ORANGE },
		{ "Taxi Yellow", COLOR_WORN_TAXI_YELLOW, COLOR_WORN_TAXI_YELLOW },
		{ "Pale Orange", COLOR_WORN_PALE_ORANGE, COLOR_WORN_PALE_ORANGE },
		{ "Olive Green", COLOR_WORN_ARMY_OLIVE_GREEN, COLOR_WORN_ARMY_OLIVE_GREEN },

	};

	std::vector<NamedVehiclePaint> PAINTS_CHROME
	{

	};
	std::vector<NamedVehiclePaint> PAINTS_CHAMELEON
	{
	};
#pragma endregion

	INT paintIndex_maxValue = 0;

	INT8 lastwheeltype;
	INT8 lastfwheel;
	INT8 lastbwheel;

	void PopulateAllPaintIDs()
	{
		Model model = VEHICLE_ADDER;
		model.Load(5000);

		//spawn dummy vehicle
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -100.0);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		Vehicle veh =  CREATE_VEHICLE(model.hash, coords.x, coords.y, coords.z, heading, 1, 0, 0);
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
				//set and get colour ID's and names
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, painttype, i, 0);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &second);
				VEHICLE::GET_VEHICLE_COLOURS(veh, &colour, &second);
				colourname = VEHICLE::GET_VEHICLE_MOD_COLOR_1_NAME(veh, 0);
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
		//unloading test vehicle from memory
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
		VEHICLE::DELETE_VEHICLE(&veh);
		model.Unload();


		// Pearl, Wheels, Interior, Dashboard
		/*const std::array<std::vector<int>, 7> indicesToOmitAll{ {
				{}, //not used
				{}, //Primary
				{}, //Secondary
				{11, 12, 15, 29, 30, 31, 32, 33, 40, 41, 57, 58, 59, 65, 79, 80, 82, 83, 84, 85, 86, 90, 91, 94, 101, 102, 103, 104}, //Pearl
				{3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 22, 23, 25, 29, 31, 32, 33, 34, 35, 36, 37, 39, 41, 42, 43, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 59, 65, 66, 68, 69, 70, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 89, 90, 92, 93, 94, 100, 101, 103, 104, 105}, //Wheels
				{4, 11, 12, 13, 15, 16, 17, 20, 28, 29, 30, 31, 32, 33, 40, 41, 42, 43, 47, 54, 57, 58, 59, 60, 65, 79, 80, 82, 83, 84, 85, 86, 87, 90, 91, 94, 101, 102, 103, 104, 105}, //Interior
				{0, 1, 2, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 29, 30, 31, 32, 33, 34, 35, 37, 40, 41, 42, 43, 44, 45, 55, 57, 58, 59, 60, 65, 66, 67, 68, 69, 73, 75, 79, 80, 82, 83, 84, 85, 86, 90, 91, 92, 93, 94, 96, 97, 99, 101, 102, 103, 104, 105}, //Dashboard
			} };
		const std::array<std::vector<NamedVehiclePaint>*, 4> pPaintsArr{ {
				&PAINTS_PEARL, &PAINTS_WHEELS, &PAINTS_INTERIOR, &PAINTS_DASHBOARD
		} };

		for (int i = 0; i < pPaintsArr.size(); i++)
		{
			int paintVectorId = i + 3;
			std::vector<NamedVehiclePaint>* pPaints = pPaintsArr[i];
			for (int paintIt = 0; paintIt < PAINTS_STATIC.size(); paintIt++)
			{
				const auto& paintToInclude = PAINTS_STATIC[paintIt];
				const auto& indicesToOmit = indicesToOmitAll[paintVectorId];
				// Check if the current index is in the list of indices to omit
				if (std::find(indicesToOmit.begin(), indicesToOmit.end(), paintToInclude.paint) == indicesToOmit.end())
				{
					pPaints->push_back(paintToInclude);
				}
			}
		}*/

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
		switch (partIndex_CustomK)
		{
		case 10:
			_globalSpawnVehicle_PrimCol = colour_index;
			return;
		case 11:
			_globalSpawnVehicle_SecCol = colour_index;
			return;
		}

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
		}

	}

	void AddcarcolOption_(const std::string& text, Vehicle vehicle, INT16 colour_index, INT16 pearl_index_ifPrimary)
	{
		bool pressed = false;

		if (_globalLSC_Customs)
		{
			if (getpaint)
			{
				lastpaint = getpaintCarUsing_index(vehicle, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(vehicle, 3);
				if (ms_curr_paint_index == 1 && GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle))
				{
					iscustompaint = true;
					GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &lastr, &lastg, &lastb);
				}
				if (ms_curr_paint_index == 2 && GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle))
				{
					iscustompaint = true;
					GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &lastr, &lastg, &lastb);
				}
				getpaint = false;
			}
			AddTickol(text, lastpaint == colour_index, pressed, pressed,
				IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING);
			if (*Menu::currentopATM == Menu::printingop && getpaintCarUsing_index(vehicle, ms_curr_paint_index) != colour_index)
				paintCarUsing_index(vehicle, ms_curr_paint_index, colour_index, pearl_index_ifPrimary);
			if (pressed)
			{
				lastpaint = getpaintCarUsing_index(vehicle, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(vehicle, 3);
				iscustompaint = false;
				//Menu::SetSub_previous();
				return;
			}

			if (Menu::OnSubBack == nullptr)
			{
				Menu::OnSubBack = [vehicle]()
				{
					paintCarUsing_index(vehicle, ms_curr_paint_index, lastpaint, lastpearl);
					if (iscustompaint)
					{
						if (ms_curr_paint_index == 1)
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, lastr, lastg, lastb);
						else if (ms_curr_paint_index == 2)
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, lastr, lastg, lastb);
					}
				};
			}
		}
		else
		{
			AddTickol(text, colour_index == getpaintCarUsing_index(vehicle, ms_curr_paint_index), pressed, pressed,
				IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING); if (pressed)
			{
				paintCarUsing_index(vehicle, ms_curr_paint_index, colour_index, pearl_index_ifPrimary);
			}
		}
	}

	void MSPaints_()
	{
		if (!DOES_ENTITY_EXIST(Static_12))
		{
			Menu::SetSub_previous();
			return;
		}

		float paintFade = GET_VEHICLE_ENVEFF_SCALE(Static_12);
		float dirtLevel = GET_VEHICLE_DIRT_LEVEL(Static_12);
		float carvarcol = GET_VEHICLE_COLOUR_COMBINATION(Static_12) + 1;
		bool set_mspaints_index_4 = 0, set_mspaints_index_3 = 0,
			set_mspaints_index_5 = 0, set_mspaints_index_6 = 0,
			paintFade_plus = 0, paintFade_minus = 0,
			dirtLevel_plus = 0, dirtLevel_minus = 0,
			carvarcol_plus = 0, carvarcol_minus = 0, carvarcol_input = 0;
		getpaint = true;

		AddTitle("Paints");
		AddMSPaintsPointOption_(Game::GetGXTEntry("CMOD_COL0_0", "Primary"), 1); // Primary CMOD_COL0_0
		 //if (_DOES_VEHICLE_HAVE_SECONDARY_COLOUR(Static_12))
		AddMSPaintsPointOption_(Game::GetGXTEntry("CMOD_COL0_1", "Secondary"), 2); // Secondary CMOD_COL0_1
		AddOption(Game::GetGXTEntry("CMOD_COL1_6", "Pearlescent"), set_mspaints_index_3, nullFunc, SUB::MSPAINTS2_PEARL, true, false); // Pearlescent CMOD_COL1_6
		AddOption(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels"), set_mspaints_index_4, nullFunc, -1, true);
		AddOption("Interior Colour", set_mspaints_index_5, nullFunc, SUB::MSPAINTS2_SHARED, true);
		AddOption("Dashboard Colour", set_mspaints_index_6, nullFunc, SUB::MSPAINTS2_SHARED, true);


		AddBreak("---Collateral---");
		AddNumber("Paint Fade", paintFade, 2, null, paintFade_plus, paintFade_minus);
		AddNumber("Dirt Level", dirtLevel, 2, null, dirtLevel_plus, dirtLevel_minus);
		AddNumber("CarVariation Colours", carvarcol, 0, carvarcol_input, carvarcol_plus, carvarcol_minus);


		if (set_mspaints_index_3) {
			ms_curr_paint_index = 3;
			return;
		}

		if (set_mspaints_index_4) {
			ms_curr_paint_index = 4;
			if (GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels) < 0)
				Game::Print::PrintBottomCentre("~b~Note:~s~ Colours cannot always be applied to stock wheels.");
			Menu::SetSub_new(SUB::MSPAINTS2_SHARED);
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
			paintFade += 0.02f;
			if (paintFade > 1.0f) paintFade = 1.0f;
			SET_VEHICLE_ENVEFF_SCALE(Static_12, paintFade);
		}
		if (paintFade_minus)
		{
			paintFade -= 0.02f;
			if (paintFade < 0.0f) paintFade = 0.0f;
			SET_VEHICLE_ENVEFF_SCALE(Static_12, paintFade);
		}

		if (dirtLevel_plus)
		{
			dirtLevel += 0.1f;
			if (dirtLevel > 15.0f) dirtLevel = 15.0f;
			SET_VEHICLE_DIRT_LEVEL(Static_12, dirtLevel);
		}
		if (dirtLevel_minus)
		{
			dirtLevel -= 0.1f;
			if (dirtLevel < 0.0f) dirtLevel = 0.0f;
			SET_VEHICLE_DIRT_LEVEL(Static_12, dirtLevel);
		}

		if (carvarcol_input) {
			std::string inputStr = Game::InputBox("", 4, "Enter a CarVariation index:", std::to_string(carvarcol));
			if (inputStr.length() > 0)
			{
				try
				{
					carvarcol = stoi(inputStr);
					CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12);
					CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12);
					SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol - 1);
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

		if (carvarcol_plus)
		{
			if (carvarcol < GET_NUMBER_OF_VEHICLE_COLOURS(Static_12))
			{
				carvarcol += 1;
				CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12);
				CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12);
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol - 1);
			}
			else
			{
				carvarcol = 1;
				CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12);
				CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12);
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol - 1);
			}
			if (_globalLSC_Customs)
			{
				lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(Static_12, 3);
			}
		}
		if (carvarcol_minus)
		{
			if (carvarcol > 1)
			{
				carvarcol -= 1;
				CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12);
				CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12);
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol - 1);
			}
			else
			{
				carvarcol = GET_NUMBER_OF_VEHICLE_COLOURS(Static_12);
				CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Static_12);
				CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Static_12);
				SET_VEHICLE_COLOUR_COMBINATION(Static_12, carvarcol - 1);
			}
			if (_globalLSC_Customs)
			{
				lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
				lastpearl = getpaintCarUsing_index(Static_12, 3);
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
		
		
		GTAvehicle vehicle = Static_12;

		INT paintIndex;
		paintIndex = getpaintCarUsing_index(Static_12, ms_curr_paint_index);

		/*int totalpaints = 49;
		for (int i = 0; i < 6; i++)
		{
			if (i != 2)
			{
				totalpaints = totalpaints + GET_NUM_MOD_COLORS(i, 1);
			}
		}
		int extrapaints = totalpaints - 225;*/

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
		if(IS_DLC_PRESENT(GET_HASH_KEY("spchameleon")))
			AddOption("Chameleon", null, nullFunc, SUB::MSPAINTS2_CHAMELEON, true, true); // CMOD_COL1_4
		AddOption("Utility", null, nullFunc, SUB::MSPAINTS2_UTIL);
		AddOption("Worn", null, nullFunc, SUB::MSPAINTS2_WORN);

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
				iscustompaint = false;
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
				iscustompaint = false;
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
						iscustompaint = false;
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
					RgbS copy = vehicle.CustomPrimaryColour_get();
					vehicle.CustomSecondaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			case 2:
				if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Static_12))
				{
					RgbS copy = vehicle.CustomSecondaryColour_get();
					vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			}
		}


	}

	namespace MSPaints_catind
	{
		void _AddPaintIndexSlider()
		{
			INT paintIndex = getpaintCarUsing_index(Static_12, ms_curr_paint_index);

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
				if (_globalLSC_Customs)
				{
					lastpaint = getpaintCarUsing_index(Static_12, ms_curr_paint_index);
					lastpearl = getpaintCarUsing_index(Static_12, 3);
					iscustompaint = false;
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
					iscustompaint = false;
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
							iscustompaint = false;
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
		}

		void Sub_Shared()
		{
			const std::vector<NamedVehiclePaint>* pPaints = &PAINTS_NORMAL;

			switch (ms_curr_paint_index)
			{
			case 1: case 10: AddTitle(Game::GetGXTEntry("CMOD_COL0_0", "Primary")); break;
			case 2: case 11: AddTitle(Game::GetGXTEntry("CMOD_COL0_1", "Secondary")); break;
			case 3:
				AddTitle(Game::GetGXTEntry("CMOD_COL1_6", "Pearlescent"));
				pPaints = &PAINTS_PEARL;
				break;
			case 5:
				AddTitle("Interior");
				pPaints = &PAINTS_INTERIOR;
				break;
			case 6:
				AddTitle("Dashboard");
				pPaints = &PAINTS_DASHBOARD;
				break;
			case 4: default:
				AddTitle(Game::GetGXTEntry("CMOD_MOD_WHEM", "Wheels"));
				pPaints = &PAINTS_WHEELS;
				break;
			}

			for (auto& p : *pPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

			_AddPaintIndexSlider();

		}
		
		void Sub_Chrome()
		{
			AddTitle("Chrome");

			auto& vPaints = PAINTS_CHROME;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		
		void Sub_Normal()
		{
			AddTitle("Classic");

			auto& vPaints = PAINTS_NORMAL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		
		void Sub_Matte()
		{
			AddTitle("Matte");

			auto& vPaints = PAINTS_MATTE;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		
		void Sub_Metallic()
		{
			AddTitle("Metallic");

			auto& vPaints = PAINTS_METALLIC;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		
		void Sub_Metal()
		{
			AddTitle("Metal");

			auto& vPaints = PAINTS_METAL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		
		void Sub_Chameleon()
		{
			AddTitle("Chameleon");

			auto& vPaints = PAINTS_CHAMELEON;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);

		}
		
		void Sub_Pearl()
		{
			AddTitle("Pearlescent");

			auto& vPaints = PAINTS_PEARL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.pearl, p.pearl);

			_AddPaintIndexSlider();

		}
		
		void Sub_Util()
		{
			AddTitle("Utility");

			auto& vPaints = PAINTS_UTIL;

			for (auto& p : vPaints)
				AddcarcolOption_(p.name, Static_12, p.paint, p.pearl);
		}
		
		void Sub_Worn()
		{
			AddTitle("Worn");

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
			REPLACE_HUD_COLOUR_WITH_RGBA(Static_12, R, G, B, A);
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
			ms_paints_finish_minus = 0,
			ms_paints_savergb = 0;

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
		case 2: GET_VEHICLE_NEON_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;
		case 3: ms_paints_rgb_r = _global_MultiPlatNeons_Col.R; ms_paints_rgb_g = _global_MultiPlatNeons_Col.G; ms_paints_rgb_b = _global_MultiPlatNeons_Col.B; break;
		case 4: GET_VEHICLE_TYRE_SMOKE_COLOR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;

		case 7: GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Static_240/*idk so ja*/, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b); break;

		case 9: ms_paints_rgb_r = _globalSpawnVehicle_neonCol.R; ms_paints_rgb_g = _globalSpawnVehicle_neonCol.G; ms_paints_rgb_b = _globalSpawnVehicle_neonCol.B; break;
		case 10: GET_HUD_COLOUR(Static_12, &ms_paints_rgb_r, &ms_paints_rgb_g, &ms_paints_rgb_b, &ms_paints_rgb_a); break;
		}
		AddTitle("Set Colour");
		if (bit_MSPaints_RGB_mode == 0 || bit_MSPaints_RGB_mode == 1)
			AddTexter("Paint Finish", ms_paints_finish, PAINTS_FINISH_NAMES, null, ms_paints_finish_plus, ms_paints_finish_minus);
		AddNumber("Red", ms_paints_rgb_r, 0, ms_paints_rgb_r_custom, ms_paints_rgb_r_plus, ms_paints_rgb_r_minus);

		switch (*Menu::currentopATM)
		{
		case 2:case 3:case 4:
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
						Game::Print::PrintError_InvalidInput();
					else
					{
						ms_paints_rgb_r = newVal;
						rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
					}
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
						Game::Print::PrintError_InvalidInput();
					else
					{
						ms_paints_rgb_g = newVal;
						rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
					}
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
						Game::Print::PrintError_InvalidInput();
					else
					{
						ms_paints_rgb_b = newVal;
						rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
					}
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
						Game::Print::PrintError_InvalidInput();
					else
					{
						ms_paints_rgb_a = newVal;
						rgb_mode_set_carcol(Static_12, ms_paints_rgb_r, ms_paints_rgb_g, ms_paints_rgb_b, ms_paints_rgb_a);
					}
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
				RgbS copy = vehicle.CustomPrimaryColour_get();
				paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
				vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				break;
			}
			case 2:
			{
				RgbS copy = vehicle.CustomSecondaryColour_get();
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
					RgbS copy = vehicle.CustomPrimaryColour_get();
					paintCarUsing_index(Static_12, ms_curr_paint_index, PAINTS_FINISH[ms_paints_finish].paint, -1);
					vehicle.CustomPrimaryColour_set(copy.R, copy.G, copy.B);
				}
				break;
			case 2:
				if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Static_12))
				{
					RgbS copy = vehicle.CustomSecondaryColour_get();
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
		//const Vector3& Pos = GET_ENTITY_COORDS(vehicle, 1);

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
				if (11 <= i && 16 >= i)
					modIndex = GET_NUM_VEHICLE_MODS(vehicle, i) - 1;
				SET_VEHICLE_MOD(vehicle, i, modIndex, 0);
			}
			SET_VEHICLE_WINDOW_TINT(vehicle, 1);

			SET_VEHICLE_TYRES_CAN_BURST(vehicle, false);
		}

		if (neonIt) // neons
		{
			for (i = 0; i <= 3; i++)
				SET_VEHICLE_NEON_ENABLED(vehicle, i, TRUE);
			SET_VEHICLE_NEON_COLOUR(vehicle, NeonR, NeonG, NeonB);
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
		if (!(DOES_ENTITY_EXIST(Static_12) && IS_ENTITY_A_VEHICLE(Static_12)))
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
			ms_livery2_plus = 0,
			ms_livery2_minus = 0,
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
			ms_livery = GET_VEHICLE_LIVERY(Static_12) + 1,
			ms_livery2 = GET_VEHICLE_LIVERY2(Static_12) + 1;

		auto rpmMultVal = 1.0f;
		const auto& rpmMultIt = g_multList_rpm.find(vehicle.Handle());
		if (rpmMultIt != g_multList_rpm.end())
			rpmMultVal = rpmMultIt->second;

		auto torqueMultVal = 1.0f;
		const auto& torqueMultIt = g_multList_torque.find(vehicle.Handle());
		if (torqueMultIt != g_multList_torque.end())
			torqueMultVal = torqueMultIt->second;

		auto maxSpeedMultVal = GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(vehicleModel.hash);
		const auto& maxSpeedMultIt = g_multList_maxSpeed.find(vehicle.Handle());
		if (maxSpeedMultIt != g_multList_maxSpeed.end())
			maxSpeedMultVal = maxSpeedMultIt->second;

		auto headLightsMultVal = 1.0f;
		const auto& headLightsMultIt = g_multList_headlights.find(vehicle.Handle());
		if (headLightsMultIt != g_multList_headlights.end())
			headLightsMultVal = headLightsMultIt->second;

		std::string ms_plateText = GET_VEHICLE_NUMBER_PLATE_TEXT(Static_12);

		std::vector<std::string> ms_vPlateTypeNames{ "CMOD_PLA_0", "CMOD_PLA_4", "CMOD_PLA_3", "CMOD_PLA_1", "CMOD_PLA_2", "Yankton", "CMOD_PLA_6", "CMOD_PLA_7", "CMOD_PLA_8", "CMOD_PLA_9", "CMOD_PLA_10", "CMOD_PLA_11", "CMOD_PLA_12" }; // BOW1, YOBLA, YOBLU, BOW2, BOW3, YANKTON, ECOLA, LASVENTURAS, LIBERTYCITY, LSCARMEET, LSPOUNDERS, SPRUNK
		if (veh_plate_current < 0) veh_plate_current = 0;

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

		if (Static_12_veh_model.IsWheelChangingSupportedVehicle() && 65535 != GET_VEHICLE_MOD_KIT(Static_12))
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
		if (GET_VEHICLE_LIVERY2_COUNT(Static_12) > 0)
			AddNumber(Game::GetGXTEntry("Roof Livery", "Roof Livery"), ms_livery2, 0, null, ms_livery2_plus, ms_livery2_minus);
		AddLocal(Game::GetGXTEntry("CMOD_MOD_TUR", "Turbo"), IS_TOGGLE_MOD_ON(Static_12, VehicleMod::Turbo), ms_turbo_toggle, ms_turbo_toggle); // Turbo
		AddLocal(Game::GetGXTEntry("CMOD_LGT_1", "Xenon Lights"), IS_TOGGLE_MOD_ON(Static_12, VehicleMod::XenonHeadlights), ms_lights_toggle, ms_lights_toggle); // Xenon lights
		AddLocal("Lower Suspension", lowersuspension, MSLowerSuspension_, MSLowerSuspension_, true); // Tuners Lower Suspension

		if (MSLowerSuspension_) {
			vehicle.RequestControlOnce();
			lowersuspension = !lowersuspension;
			SET_REDUCED_SUSPENSION_FORCE(Static_12, lowersuspension);
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

		if (vehicle.HasSiren_get())
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

		if (ms_livery2_plus) {
			if (ms_livery2 < GET_VEHICLE_LIVERY2_COUNT(Static_12)) ms_livery2++;
			SET_VEHICLE_LIVERY2(Static_12, ms_livery2 - 1);
			return;
		}
		if (ms_livery2_minus) {
			if (ms_livery2 > 1) ms_livery2--;
			SET_VEHICLE_LIVERY2(Static_12, ms_livery2 - 1);
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
			const auto& vehModel = vehicle.Model();

			if (!vehicle.Exists())
			{
				Menu::SetSub_previous();
				return;
			}

			int i;

			AddTitle(Game::GetGXTEntry("S_MO_09", "Benny's Lowrider Mods"));

			bool goToInteriorColour = 0;
			AddOption("Interior Colour", goToInteriorColour, nullFunc, SUB::MSPAINTS2_SHARED); if (goToInteriorColour)
			{
				ms_curr_paint_index = 5;
			}

			bool goToDashboardColour = 0;
			AddOption("Dashboard Colour", goToDashboardColour, nullFunc, SUB::MSPAINTS2_SHARED); if (goToDashboardColour)
			{
				ms_curr_paint_index = 6;
			}

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
			lastMod = currMod;
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
				if (*Menu::currentopATM == Menu::printingop && currMod != i)
					SET_VEHICLE_MOD(vehicle, modType, i, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
				if (pressed)
				{
					lastMod = i;
					//Menu::SetSub_previous();
				}
				if (Menu::OnSubBack == nullptr)
				{
					Menu::OnSubBack = [vehicle, modType]()
					{
						SET_VEHICLE_MOD(vehicle, modType, lastMod, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
					};
				}
			}
		}
		else
		{
			for (INT i = -1; i <= maxMod; i++)
			{
				bool pressed = false;
				AddTickol(get_mod_text_label(vehicle, modType, i, true), currMod == i, pressed, pressed,
					IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, false); if (pressed)
				{
					SET_VEHICLE_MOD(vehicle, modType, i, GET_VEHICLE_MOD_VARIATION(vehicle, modType));
				}
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
			if (_globalLSC_Customs)
			{
				auto& lastwheelRelevant = isBikeBack ? lastbwheel : lastfwheel;
				bool pressed = false;
				AddTickol(text, lastwheelRelevant == wheelIndex && lastwheeltype == wheelType, pressed, pressed,
					IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, true);

				bool allowSettingWheelPreview = GET_VEHICLE_WHEEL_TYPE(vehicle) != wheelType ||
					(wheelType == WheelType::BikeWheels && isBikeBack ? GET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels) != wheelIndex
						: GET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels) != wheelIndex);

				if (*Menu::currentopATM == Menu::printingop && allowSettingWheelPreview)
				{
					GTAvehicle(vehicle).RequestControlOnce();
					SET_VEHICLE_WHEEL_TYPE(vehicle, wheelType);
					if (wheelType == WheelType::BikeWheels)
					{
						isBikeBack ? SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels))	//for some reason, inverting this allows the previews to work, albeit reversed.
							: SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));		//but as it stands now, refuses to preview the wheels at all. 
					}
					else
					{
						SET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::FrontWheels));
						//SET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels, wheelIndex, GET_VEHICLE_MOD_VARIATION(vehicle, VehicleMod::BackWheels)); //redundant on non-bike tuning
					}
				}

				if (pressed)
				{
					lastwheeltype = wheelType;
					lastfwheel = GET_VEHICLE_MOD(vehicle, VehicleMod::FrontWheels);
					lastbwheel = GET_VEHICLE_MOD(vehicle, VehicleMod::BackWheels);
					//Menu::SetSub_previous();
					return;
				}

			}
			else ///lsccustoms off
			{
				INT currWheelType = GET_VEHICLE_WHEEL_TYPE(vehicle);
				INT currWheelIndex = GET_VEHICLE_MOD(vehicle, isBikeBack ? (int)VehicleMod::BackWheels : (int)VehicleMod::FrontWheels);

				bool pressed = false;
				AddTickol(text, currWheelIndex == wheelIndex && currWheelType == wheelType, pressed, pressed,
					IS_THIS_MODEL_A_BIKE(GET_ENTITY_MODEL(vehicle)) ? TICKOL::BIKETHING : TICKOL::CARTHING, TICKOL::NONE, true);

				if (pressed)
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
		BOOL ms_drift_tyres = GET_DRIFT_TYRES_SET(Static_12);

		lastwheeltype = GET_VEHICLE_WHEEL_TYPE(Static_12);
		lastfwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels);
		lastbwheel = GET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels);

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
		AddLocal("Drift Tyres", GET_DRIFT_TYRES_SET(Static_12), MSWheelsDriftTyresOn_, MSWheelsDriftTyresOn_, true); // Drift Tyres
		AddOption("Remove Tires", null, nullFunc, SUB::MS_TYRESBURST);

		AddOption(Game::GetGXTEntry("CMOD_MOD_TYR3", "Tire Smoke Colour"), set_msrgb_index_4, nullFunc, SUB::MSPAINTS_RGB);
		if (*Menu::currentopATM == Menu::printingop)
			Add_preset_colour_options_previews(vehicle.TyreSmokeColour_get());



		if (set_mspaints_index_4) {
			ms_curr_paint_index = 4;
			//if (GET_VEHICLE_MOD(Static_12, 23) > -1) Menu::SetSub_new(SUB::MSPAINTS2_SHARED);
			//else Game::Print::PrintBottomCentre("~r~Error:~s~ Colours cannot be applied to stock wheels.");
			if (GET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels) < 0)
				Game::Print::PrintBottomCentre("~b~Note:~s~ Colours cannot always be applied to stock wheels.");
			Menu::SetSub_new(SUB::MSPAINTS2_SHARED);
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
			for (int j = bIsChromeSelected ? 0 : 0; j < ids.size(); j += 1)
			{
				for (i = ids[j]; i < ids[j + 1]; i++)
				{
					__AddOption(get_mod_text_label(Static_12, VehicleMod::FrontWheels, i, false), Static_12, wtype, i, chrtype == 2);
				}
			}

			if (_globalLSC_Customs && Menu::OnSubBack == nullptr) // this has been split out for bikes, see further comments on the original section below (line 2575)
			{
				Menu::OnSubBack = [&]()
				{
					(chrtype == 2) ? SET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels, lastbwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::BackWheels))
						: SET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels, lastfwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::FrontWheels));
				};
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
			if (wtype != WheelType::BikeWheels && Menu::OnSubBack == nullptr)
			{
				Menu::OnSubBack = []()
				{
					SET_VEHICLE_WHEEL_TYPE(Static_12, lastwheeltype);
					SET_VEHICLE_MOD(Static_12, VehicleMod::FrontWheels, lastfwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::FrontWheels));
					//SET_VEHICLE_MOD(Static_12, VehicleMod::BackWheels, lastbwheel, GET_VEHICLE_MOD_VARIATION(Static_12, VehicleMod::BackWheels));
				};
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

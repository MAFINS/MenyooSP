/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "WeaponIndivs.h"

#include "..\macros.h"

#include "enums.h"
#include "..\Natives\natives2.h"

#include "GTAped.h"

#include <string>
#include <vector>
#include <array>
#include <map>



#pragma region Weapon labels and names
std::map<Hash, std::string> WeaponIndivs::vWeaponLabels
{
	//slot gadget (2)
	{ GADGET_PARACHUTE, "Parachute" },
	{ GADGET_NIGHTVISION, "Nightvision" },
	{ WEAPON_HACKINGDEVICE, "Hacking Device"},
	//slot melee (19)
	{ WEAPON_UNARMED, "Unarmed" },
	{ WEAPON_KNIFE, "Knife" },
	{ WEAPON_NIGHTSTICK, "Night Stick" },
	{ WEAPON_HAMMER, "Hammer" },
	{ WEAPON_BAT, "Baseball Bat" },
	{ WEAPON_CROWBAR, "Crowbar" },
	{ WEAPON_BOTTLE, "Bottle" },
	{ WEAPON_GOLFCLUB, "Golf Club" },
	{ WEAPON_DAGGER, "Antique Cavalry Dagger" },
	{ WEAPON_HATCHET, "Hatchet" },
	{ WEAPON_KNUCKLE, "Knuckle Duster" },
	{ WEAPON_SWITCHBLADE, "Switchblade" },
	{ WEAPON_MACHETE, "Machete" },
	{ WEAPON_FLASHLIGHT, "Flashlight" },
	{ WEAPON_BATTLEAXE, "Battle Axe" },
	{ WEAPON_POOLCUE, "Pool Cue" },
	{ WEAPON_WRENCH, "Wrench" },
	{ WEAPON_STONE_HATCHET, "Stone Hatchet" },
	{ WEAPON_FERTILIZERCAN, "Fertilizer Can" }, //2545
	{ WEAPON_METALDETECTOR, "Metal Detector" }, //2699
	{ WEAPON_CANDYCANE, "Candy Cane" }, //2802
	{ WEAPON_STUNROD, "Stun Rod"},
	//slot pistol (22)
	{ WEAPON_PISTOL, "Pistol" },
	{ WEAPON_PISTOL_MK2, "Pistol Mk2" },
	{ WEAPON_COMBATPISTOL, "Combat Pistol" },
	{ WEAPON_PISTOL50, "Pistol .50" },
	{ WEAPON_HEAVYPISTOL, "Heavy Pistol" },
	{ WEAPON_VINTAGEPISTOL, "Vintage Pistol" },
	{ WEAPON_APPISTOL, "AP Pistol" },
	{ WEAPON_MACHINEPISTOL, "Machine Pistol" },
	{ WEAPON_REVOLVER, "Revolver" },
	{ WEAPON_REVOLVER_MK2, "Revolver Mk2" },
	{ WEAPON_DOUBLEACTION, "Double-Action Revolver" },
	{ WEAPON_STUNGUN, "Stun Gun" },
	{ WEAPON_SNSPISTOL, "SNS Pistol" },
	{ WEAPON_SNSPISTOL_MK2, "SNS Pistol Mk2" },
	{ WEAPON_MARKSMANPISTOL, "Marksman Pistol" },
	{ WEAPON_FLAREGUN, "Flare Gun" },
	{ WEAPON_RAYPISTOL, "Ray Pistol" },
	// 1.0.1868.0
	{ WEAPON_NAVYREVOLVER, "Navy Revolver" },
	{ WEAPON_CERAMICPISTOL, "Ceramic Pistol" },
    // 1.0.2189.0
	{ WEAPON_GADGETPISTOL, "Perico Pistol"},
	{ WEAPON_STUNGUN_MP, "Stun Gun MP" }, //2545
	{ WEAPON_PISTOLXM3, "Pistol XM3" }, //2802
	//slot Shotgun (9)
	{ WEAPON_PUMPSHOTGUN, "Pump Shotgun" },
	{ WEAPON_PUMPSHOTGUN_MK2, "Pump Shotgun Mk2" },
	{ WEAPON_SAWNOFFSHOTGUN, "Sawed-Off Shotgun" },
	{ WEAPON_BULLPUPSHOTGUN, "Bullpup Shotgun" },
	{ WEAPON_ASSAULTSHOTGUN, "Assault Shotgun" },
	{ WEAPON_MUSKET, "Musket" },
	{ WEAPON_HEAVYSHOTGUN, "Heavy Shotgun" },
	{ WEAPON_DBSHOTGUN, "Double-Barrel Shotgun" },
	{ WEAPON_AUTOSHOTGUN, "Auto Shotgun" },
    // 1.0.2189.0
	{ WEAPON_COMBATSHOTGUN, "Combat Shotgun" },                                                   
	//slot MG (10)
	{ WEAPON_MICROSMG, "Micro SMG" },
	{ WEAPON_SMG, "SMG" },
	{ WEAPON_SMG_MK2, "SMG Mk2" },
	{ WEAPON_COMBATPDW, "Combat PDW" },
	{ WEAPON_ASSAULTSMG, "Assault SMG" },
	{ WEAPON_MG, "MG" },
	{ WEAPON_COMBATMG, "Combat MG" },
	{ WEAPON_COMBATMG_MK2, "Combat MG Mk2" },
	{ WEAPON_GUSENBERG, "Gusenberg Sweeper" },
	{ WEAPON_MINISMG, "Mini SMG" },
	{ WEAPON_TECPISTOL, "Technical SMG" },
	//slot Rifle (14)
	{ WEAPON_ASSAULTRIFLE, "Assault Rifle" },
	{ WEAPON_ASSAULTRIFLE_MK2, "Assault Rifle Mk2" },
	{ WEAPON_CARBINERIFLE, "Carbine Rifle" },
	{ WEAPON_CARBINERIFLE_MK2, "Carbine Rifle Mk2" },
	{ WEAPON_ADVANCEDRIFLE, "Advance Rifle" },
	{ WEAPON_SPECIALCARBINE, "Special Carbine" },
	{ WEAPON_SPECIALCARBINE_MK2, "Special Carbine Mk2" },
	{ WEAPON_BULLPUPRIFLE, "Bullpup Rifle" },
	{ WEAPON_BULLPUPRIFLE_MK2, "Bullpup Rifle Mk2" },
	{ WEAPON_COMPACTRIFLE, "Compact Rifle" },
	{ WEAPON_RAYCARBINE, "Ray Carbine Rifle" },
	{ WEAPON_BATTLERIFLE, "Battle Rifle" },
    // 1.0.2189.0
	{ WEAPON_MILITARYRIFLE, "Military Rifle" },
	{ WEAPON_HEAVYRIFLE, "Heavy Rifle" }, //2545
	{ WEAPON_TACTICALRIFLE, "Tactical Rifle" }, //2699                                                             
	//slot Sniper (6)
	{ WEAPON_SNIPERRIFLE, "Sniper Rifle" },
	{ WEAPON_HEAVYSNIPER, "Heavy Sniper" },
	{ WEAPON_HEAVYSNIPER_MK2, "Heavy Sniper Mk2" },
	{ WEAPON_MARKSMANRIFLE, "Marksman Rifle" },
	{ WEAPON_MARKSMANRIFLE_MK2, "Marksman Rifle Mk2" },
	{ WEAPON_PRECISIONRIFLE, "Precision Rifle" }, //2699 
	//slot throwables (14)
	{ WEAPON_GRENADE, "Grenade" },
	{ WEAPON_STICKYBOMB, "Sticky Bomb" },
	{ WEAPON_PROXMINE, "Proximity Mine" },
	{ WEAPON_SMOKEGRENADE, "Tear Gas" },
	{ WEAPON_BZGAS, "Bz Gas" },
	{ WEAPON_MOLOTOV, "Molotov" },
	{ WEAPON_FIREEXTINGUISHER, "Fire Extinguisher" },
	{ WEAPON_PETROLCAN, "Jerry Can" },
	{ WEAPON_BALL, "Ball" },
	{ WEAPON_SNOWBALL, "Snowball" },
	{ WEAPON_FLARE, "Flare" },
	{ WEAPON_PIPEBOMB, "Pipe Bomb" },
	{ WEAPON_ACIDPACKAGE, "Acid Package" }, //2802
	// 1.0.1868.0
	{ WEAPON_HAZARDCAN, "Hazardous Jerry Can" },
	{ WEAPON_BATTLERIFLE, "Battle Rifle" },
	//slot launcher (10)
	{ WEAPON_GRENADELAUNCHER, "Grenade Launcher" },
	{ WEAPON_RPG, "RPG" },
	{ WEAPON_MINIGUN, "Minigun" },
	{ WEAPON_FIREWORK, "Firework Launcher" },
	{ WEAPON_RAILGUN, "Railgun" },
	{ WEAPON_HOMINGLAUNCHER, "Homing Launcher" },
	{ WEAPON_COMPACTLAUNCHER, "Compact Grenade Launcher" },
	{ WEAPON_RAYMINIGUN, "Ray Minigun" },
	{ WEAPON_EMPLAUNCHER, "EMP Launcher" }, //2545
	{ WEAPON_RAILGUNXM3, "Railgun XM3" }, //2802
	{ WEAPON_SNOWLAUNCHER , "Snow Launcher"},

};
#pragma endregion

const std::vector<std::string> WeaponIndivs::vCategoryNames{ "Melee", "Pistols", "Submachine Guns", "Machine Guns", "Assault Rifles", "Shotguns", "Sniper Rifles", "Heavy Weapons", "Throwable Weapons", "Add-on Weapons" };

#pragma region tint names
const std::vector<std::string> WeaponIndivs::vCaptions_Tints{ "Normal", "Green", "Gold", "Pink", "Army", "LSPD", "Orange", "Platinum" };

const std::vector<std::string> WeaponIndivs::vCaptions_TintsMk2
{
	{ "Classic Black" },
	{ "Classic Gray" },
	{ "Classic Two-Tone" },
	{ "Classic White" },
	{ "Classic Beige" },
	{ "Classic Green" },
	{ "Classic Blue" },
	{ "Classic Earth" },
	{ "Classic Brown & Black" },
	{ "Red Contrast" },
	{ "Blue Contrast" },
	{ "Yellow Contrast" },
	{ "Orange Contrast" },
	{ "Bold Pink" },
	{ "Bold Purple & Yellow" },
	{ "Bold Orange" },
	{ "Bold Green & Purple" },
	{ "Bold Red Features" },
	{ "Bold Green Features " },
	{ "Bold Cyan Features" },
	{ "Bold Yellow Features" },
	{ "Bold Red & White" },
	{ "Bold Blue & White" },
	{ "Metallic Gold" },
	{ "Metallic Platinum" },
	{ "Metallic Gray & Lilca" },
	{ "Metallic Purple & Lime" },
	{ "Metallic Red" },
	{ "Metallic Green" },
	{ "Metallic Blue" },
	{ "Metallic White & Aqua" },
	{ "Metallic Red & Yellow" }
};

const std::vector<std::string> WeaponIndivs::vCaptions_ChuteTints
{
	{ "Rainbow Chute" },
	{ "Red Chute" },
	{ "Seaside Stripes Chute" },
	{ "Widowmaker Chute" },
	{ "Patriot Chute" },
	{ "Blue Chute" },
	{ "Black Chute" },
	{ "Hornet Chute" },
	{ "Airforce Chute" },
	{ "Desert Chute" },
	{ "Shadow Chute" },
	{ "High Altitude Chute" },
	{ "Airborn Chute" },
	{ "Sunrise Chute" },
};
#pragma endregion

#pragma region weapons and components
//struct WeaponComponent{ std::string name; Hash hash; };
//struct WeaponAndComponents{ Hash weaponHash; std::vector<NamedWeaponComponent> components; std::vector<std::string>* tintCaptions; };

#pragma region melee
std::vector<WeaponAndComponents> WeaponIndivs::wc_MELEE
{
	{ WEAPON_KNUCKLE,{
		{ "Default", COMPONENT_KNUCKLE_VARMOD_BASE },
		{ "Pimp", COMPONENT_KNUCKLE_VARMOD_PIMP },
		{ "Ballas", COMPONENT_KNUCKLE_VARMOD_BALLAS },
		{ "Dollar", COMPONENT_KNUCKLE_VARMOD_DOLLAR },
		{ "Diamond", COMPONENT_KNUCKLE_VARMOD_DIAMOND },
		{ "Hate", COMPONENT_KNUCKLE_VARMOD_HATE },
		{ "Love", COMPONENT_KNUCKLE_VARMOD_LOVE },
		{ "Player", COMPONENT_KNUCKLE_VARMOD_PLAYER },
		{ "King", COMPONENT_KNUCKLE_VARMOD_KING },
		{ "Vagos", COMPONENT_KNUCKLE_VARMOD_VAGOS },
	}, nullptr },

	{ WEAPON_SWITCHBLADE,{
		{ "Default", COMPONENT_SWITCHBLADE_VARMOD_BASE },
		{ "Variation 1", COMPONENT_SWITCHBLADE_VARMOD_VAR1 },
		{ "Variation 2", COMPONENT_SWITCHBLADE_VARMOD_VAR2 },
	}, nullptr },

	{ WEAPON_KNIFE,{
		{ "Eyes", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3") },
		{ "Spatter", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_01") },
		{ "Flames", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_02") },
		{ "Lightning", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_03") },
		{ "Pills", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_04") },
		{ "Snakeskin", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_05") },
		{ "Lucha Libre", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_06") },
		{ "Trippy", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_07") },
		{ "Tequilya", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_08") },
		{ "Orang-O-Tang", GET_HASH_KEY("COMPONENT_KNIFE_VARMOD_XM3_09") },
	}, nullptr },
	{ WEAPON_NIGHTSTICK,{
	}, nullptr },
	{ WEAPON_HAMMER,{
	}, nullptr },
	{ WEAPON_BAT,{
		{ "Blagueurs", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3") },
		{ "Spatter", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_01") },
		{ "Bullet Holes", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_02") },
		{ "Burger Shot", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_03") },
		{ "Cluckin' Bell", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_04") },
		{ "Fatal Incursion", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_05") },
		{ "Lucha Libre", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_06") },
		{ "Trippy", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_07") },
		{ "Tie-Dye", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_08") },
		{ "Wall", GET_HASH_KEY("COMPONENT_BAT_VARMOD_XM3_09") },
	}, nullptr },
	{ WEAPON_GOLFCLUB,{
	}, nullptr },
	{ WEAPON_CROWBAR,{
	}, nullptr },
	{ WEAPON_BOTTLE,{
	}, nullptr },
	{ WEAPON_DAGGER,{
	}, nullptr },
	{ WEAPON_HATCHET,{
	}, nullptr },
	{ WEAPON_MACHETE,{
	}, nullptr },
	{ WEAPON_FLASHLIGHT,{
	}, nullptr },
	{ WEAPON_BATTLEAXE,{
	}, nullptr },
	{ WEAPON_POOLCUE,{
	}, nullptr },
	{ WEAPON_WRENCH,{
	}, nullptr },
	{ WEAPON_STONE_HATCHET,{
	}, nullptr },

	{ WEAPON_FERTILIZERCAN,{
	}, nullptr },
	{ WEAPON_METALDETECTOR,{
	}, nullptr },
	{ WEAPON_CANDYCANE,{
	}, nullptr },
	{ WEAPON_STUNROD,{
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region pistols/stun
std::vector<WeaponAndComponents> WeaponIndivs::wc_PISTOLS
{
	{ WEAPON_PISTOL,{
		{ "Extended_Clip", COMPONENT_PISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP_02 },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_PISTOL_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_PISTOL_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_INCENDIARY") },
		{ "Hollowpoint Rounds", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_HOLLOWPOINT") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_FMJ") },
		{ "Rail", GET_HASH_KEY("COMPONENT_AT_PI_RAIL") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_PI_SUPP_02") },
		{ "Compressor", GET_HASH_KEY("COMPONENT_AT_PI_COMP") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_PI_FLSH_02") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_IND_01_SLIDE") },
		{ "Season's Greetings Frame", GET_HASH_KEY("COMPONENT_PISTOL_MK2_VARMOD_XM3") },
		{ "Season's Greetings Slide", GET_HASH_KEY("COMPONENT_PISTOL_MK2_VARMOD_XM3_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_COMBATPISTOL,{
		{ "Extended_Clip", COMPONENT_COMBATPISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_APPISTOL,{
		{ "Extended_Clip", COMPONENT_APPISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Gilded Gun Metal Finish", COMPONENT_APPISTOL_VARMOD_LUXE },
		{ "Record A Finish", GET_HASH_KEY("COMPONENT_APPISTOL_VARMOD_SECURITY") },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_PISTOL50,{
		{ "Extended_Clip", COMPONENT_PISTOL50_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Platinum Pearl Deluxe Finish", COMPONENT_PISTOL50_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SNSPISTOL,{
		{ "Extended_Clip", COMPONENT_SNSPISTOL_CLIP_02 },
		{ "Etched Wood Grip Finish", COMPONENT_SNSPISTOL_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SNSPISTOL_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIARY") },
		{ "Hollowpoint Rounds", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_HOLLOWPOINT") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_FMJ") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_PI_FLSH_03") },
		{ "Rail", GET_HASH_KEY("COMPONENT_AT_PI_RAIL_02") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_PI_SUPP_02") },
		{ "Compensator", GET_HASH_KEY("COMPONENT_AT_PI_COMP_02") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_HEAVYPISTOL,{
		{ "Extended_Clip", COMPONENT_HEAVYPISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Etched Wood Grip Finish", COMPONENT_HEAVYPISTOL_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_VINTAGEPISTOL,{
		{ "Extended_Clip", COMPONENT_VINTAGEPISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_MARKSMANPISTOL,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_MACHINEPISTOL,{
		{ "Extended_Clip", COMPONENT_MACHINEPISTOL_CLIP_02 },
		{ "Drum Magazine", COMPONENT_MACHINEPISTOL_CLIP_03 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_REVOLVER,{
		{ "Standard_Clip", COMPONENT_REVOLVER_CLIP_01 },
		{ "Boss Finish", COMPONENT_REVOLVER_VARMOD_BOSS },
		{ "Goon Finish", COMPONENT_REVOLVER_VARMOD_GOON },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_REVOLVER_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_01") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_INCENDIARY") },
		{ "Hollowpoint Rounds", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_HOLLOWPOINT") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_PI_FLSH") },
		{ "Compensator", GET_HASH_KEY("COMPONENT_AT_PI_COMP_03") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_DOUBLEACTION,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_STUNGUN,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_FLAREGUN,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_RAYPISTOL,{
		{ "Green Eyes White Dragon", GET_HASH_KEY("COMPONENT_RAYPISTOL_VARMOD_XMAS18") },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_NAVYREVOLVER,{
	}, &WeaponIndivs::vCaptions_Tints },
	
	{ WEAPON_CERAMICPISTOL,{
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_CERAMICPISTOL_CLIP_02") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_CERAMICPISTOL_SUPP") },
	}, &WeaponIndivs::vCaptions_Tints },
    { WEAPON_GADGETPISTOL,{
	}, &WeaponIndivs::vCaptions_Tints },   

	{ WEAPON_STUNGUN_MP,{
		//{ "Bottom Dollar Bail Enforcement", GET_HASH_KEY("COMPONENT_STUNGUN_VARMOD_BAIL") },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_PISTOLXM3,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_PISTOLXM3_CLIP_01") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_PISTOLXM3_SUPP") },
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region submachine guns
std::vector<WeaponAndComponents> WeaponIndivs::wc_SMGS
{
	{ WEAPON_MICROSMG,{
		{ "Extended_Clip", COMPONENT_MICROSMG_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_MACRO },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Flashlight", COMPONENT_AT_PI_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_MICROSMG_VARMOD_LUXE },
		{ "Organics Finish", GET_HASH_KEY("COMPONENT_MICROSMG_VARMOD_SECURITY") },
		{ "Dildodude Camo", GET_HASH_KEY("COMPONENT_MICROSMG_VARMOD_XM3") },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SMG,{
		{ "Extended_Clip", COMPONENT_SMG_CLIP_02 },
		{ "Drum Magazine", COMPONENT_SMG_CLIP_03 },
		{ "Scope", COMPONENT_AT_SCOPE_MACRO_02 },
		{ "Suppressor", COMPONENT_AT_PI_SUPP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_SMG_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SMG_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_INCENDIARY") },
		{ "Hollowpoint Rounds", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_HOLLOWPOINT") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS_SMG") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_02_SMG_MK2") },
		{ "Small Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_SMG_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_PI_SUPP") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_SB_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_SB_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_ASSAULTSMG,{
		{ "Extended_Clip", COMPONENT_ASSAULTSMG_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_MACRO },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_COMBATPDW,{
		{ "Extended_Clip", COMPONENT_COMBATPDW_CLIP_02 },
		{ "Drum Magazine", COMPONENT_COMBATPDW_CLIP_03 },
		{ "Scope", COMPONENT_AT_SCOPE_SMALL },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_MINISMG,{
		{ "Standard_Clip", COMPONENT_MINISMG_CLIP_01 },
		{ "Extended_Clip", COMPONENT_MINISMG_CLIP_02 },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_TECPISTOL,{
		{ "Standard_Clip", COMPONENT_TECPISTOL_CLIP_01 },
		{ "Drum Magazine", COMPONENT_TECPISTOL_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_MACRO },
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region machine guns
std::vector<WeaponAndComponents> WeaponIndivs::wc_MGS
{
	{ WEAPON_MG,{
		{ "Extended_Clip", COMPONENT_MG_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_SMALL_02 },
		{ "Yusuf Amir Luxury Finish", COMPONENT_MG_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_COMBATMG,{
		{ "Extended_Clip", COMPONENT_COMBATMG_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_MEDIUM },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Etched Gun Metal Finish", COMPONENT_COMBATMG_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_COMBATMG_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Small Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_MG_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_MG_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_GUSENBERG,{
		{ "Extended_Clip", COMPONENT_GUSENBERG_CLIP_02 },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_RAYCARBINE,{
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region assault rifles
std::vector<WeaponAndComponents> WeaponIndivs::wc_ASSAULTRIFLES
{
	{ WEAPON_ASSAULTRIFLE,{
		{ "Extended_Clip", COMPONENT_ASSAULTRIFLE_CLIP_02 },
		{ "Drum Magazine", COMPONENT_ASSAULTRIFLE_CLIP_03 },
		{ "Scope", COMPONENT_AT_SCOPE_MACRO },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_ASSAULTRIFLE_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_ASSAULTRIFLE_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_AR_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_AR_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_CARBINERIFLE,{
		{ "Extended_Clip", COMPONENT_CARBINERIFLE_CLIP_02 },
		{ "Drum Magazine", COMPONENT_CARBINERIFLE_CLIP_03 },
		{ "Scope", COMPONENT_AT_SCOPE_MEDIUM },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_CARBINERIFLE_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_CARBINERIFLE_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_CR_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_CR_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_ADVANCEDRIFLE,{
		{ "Extended_Clip", COMPONENT_ADVANCEDRIFLE_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_SMALL },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Gilded Gun Metal Finish", COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SPECIALCARBINE,{
		{ "Extended_Clip", COMPONENT_SPECIALCARBINE_CLIP_02 },
		{ "Drum Magazine", COMPONENT_SPECIALCARBINE_CLIP_03 },
		{ "Scope", COMPONENT_AT_SCOPE_MEDIUM },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Etched Gun Metal Finish", COMPONENT_SPECIALCARBINE_VARMOD_LOWRIDER },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_SPECIALCARBINE_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_SC_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_SC_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_BULLPUPRIFLE,{
		{ "Extended_Clip", COMPONENT_BULLPUPRIFLE_CLIP_02 },
		{ "Scope", COMPONENT_AT_SCOPE_SMALL },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Gilded Gun Metal Finish", COMPONENT_BULLPUPRIFLE_VARMOD_LOW },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_BULLPUPRIFLE_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_02_MK2") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_BP_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_BP_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_COMPACTRIFLE,{
		{ "Standard_Clip", COMPONENT_COMPACTRIFLE_CLIP_01 },
		{ "Extended_Clip", COMPONENT_COMPACTRIFLE_CLIP_02 },
		{ "Drum Magazine", COMPONENT_COMPACTRIFLE_CLIP_03 },
	}, &WeaponIndivs::vCaptions_Tints },
    { WEAPON_MILITARYRIFLE,{
		{ "Standard_Clip", COMPONENT_MILITARYRIFLE_CLIP_01 },
		{ "Extended_Clip", COMPONENT_MILITARYRIFLE_CLIP_02 },
		{ "Iron Sights", COMPONENT_MILITARYRIFLE_SIGHT_01 },
		{ "Scope", COMPONENT_AT_SCOPE_SMALL },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
	}, &WeaponIndivs::vCaptions_Tints },    

	{ WEAPON_HEAVYRIFLE,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_HEAVYRIFLE_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_HEAVYRIFLE_CLIP_02") },
		{ "Iron Sights", GET_HASH_KEY("COMPONENT_HEAVYRIFLE_SIGHT_01") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP") },
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_TACTICALRIFLE,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_TACTICALRIFLE_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_TACTICALRIFLE_CLIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH_REH") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP") },
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_BATTLERIFLE,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_BATTLERIFLE_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_BATTLERIFLE_CLIP_02") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP") },
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region shotguns
std::vector<WeaponAndComponents> WeaponIndivs::wc_SHOTGUNS
{
	{ WEAPON_PUMPSHOTGUN,{
		{ "Suppressor", COMPONENT_AT_SR_SUPP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Yusuf Amir Luxury Finish", COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER },
		{ "Bone Finish", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_VARMOD_SECURITY") },
		{ "Dildodude Camo", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_VARMOD_XM3") },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_PUMPSHOTGUN_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_01") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_ARMORPIERCING") },
		{ "Hollowpoint Rounds", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_HOLLOWPOINT") },
		{ "Explosive Rounds", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_EXPLOSIVE") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Macro Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2") },
		{ "Small Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_SR_SUPP_03") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Muzzle 8", GET_HASH_KEY("COMPONENT_AT_MUZZLE_08") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_SAWNOFFSHOTGUN,{
		{ "Gilded Gun Metal Finish", COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_BULLPUPSHOTGUN,{
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_ASSAULTSHOTGUN,{
		{ "Extended_Clip", COMPONENT_ASSAULTSHOTGUN_CLIP_02 },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
		{ "Flashlight", COMPONENT_AT_AR_FLSH},
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_MUSKET,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_HEAVYSHOTGUN,{
		{ "Extended_Clip", COMPONENT_HEAVYSHOTGUN_CLIP_02 },
		{ "Drum Magazine", COMPONENT_HEAVYSHOTGUN_CLIP_03 },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_DBSHOTGUN,{
		{ "Standard_Clip", COMPONENT_DBSHOTGUN_CLIP_01 },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_AUTOSHOTGUN,{
		{ "Standard_Clip", COMPONENT_AUTOSHOTGUN_CLIP_01 },
	}, &WeaponIndivs::vCaptions_Tints },
    { WEAPON_COMBATSHOTGUN,{
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
	}, &WeaponIndivs::vCaptions_Tints },                                                    
};
#pragma endregion
#pragma region snipers
std::vector<WeaponAndComponents> WeaponIndivs::wc_SNIPERS
{
	{ WEAPON_SNIPERRIFLE,{
		{ "Advanced Scope", COMPONENT_AT_SCOPE_MAX },
		{ "Suppressor", COMPONENT_AT_AR_SUPP_02 },
		{ "Etched Wood Grip Finish", COMPONENT_SNIPERRIFLE_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_HEAVYSNIPER,{
		{ "Normal Scope", COMPONENT_AT_SCOPE_LARGE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_HEAVYSNIPER_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_02") },
		{ "Explosive Rounds", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIVE") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_FMJ") },
		{ "Large Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE_MK2") },
		{ "Max Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MAX") },
		{ "Nightvision Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_NV") },
		{ "Thermal Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_THERMAL") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_SR_SUPP_03") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_SR_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_SR_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_08") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_09") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_MARKSMANRIFLE,{
		{ "Extended_Clip", COMPONENT_MARKSMANRIFLE_CLIP_02 },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Suppressor", COMPONENT_AT_AR_SUPP },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
		{ "Yusuf Amir Luxury Finish", COMPONENT_MARKSMANRIFLE_VARMOD_LUXE },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_MARKSMANRIFLE_MK2,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_01") },
		{ "Extended_Clip", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_02") },
		{ "Tracer Rounds", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_TRACER") },
		{ "Incendiary Rounds", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIARY") },
		{ "Armor Piercing Rounds", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_ARMORPIERCING") },
		{ "FMJ Rounds", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_FMJ") },
		{ "Sights", GET_HASH_KEY("COMPONENT_AT_SIGHTS") },
		{ "Medium Scope", GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") },
		{ "Large Scope (Fixed Zoom)", GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK2") },
		{ "Suppressor", GET_HASH_KEY("COMPONENT_AT_AR_SUPP") },
		{ "Grip", GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02") },
		{ "Flashlight", GET_HASH_KEY("COMPONENT_AT_AR_FLSH") },
		{ "Barrel 1", GET_HASH_KEY("COMPONENT_AT_MRFL_BARREL_01") },
		{ "Barrel 2", GET_HASH_KEY("COMPONENT_AT_MRFL_BARREL_02") },
		{ "Muzzle 1", GET_HASH_KEY("COMPONENT_AT_MUZZLE_01") },
		{ "Muzzle 2", GET_HASH_KEY("COMPONENT_AT_MUZZLE_02") },
		{ "Muzzle 3", GET_HASH_KEY("COMPONENT_AT_MUZZLE_03") },
		{ "Muzzle 4", GET_HASH_KEY("COMPONENT_AT_MUZZLE_04") },
		{ "Muzzle 5", GET_HASH_KEY("COMPONENT_AT_MUZZLE_05") },
		{ "Muzzle 6", GET_HASH_KEY("COMPONENT_AT_MUZZLE_06") },
		{ "Muzzle 7", GET_HASH_KEY("COMPONENT_AT_MUZZLE_07") },
		{ "Camo 1", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO") },
		//{ "Camo 1 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_SLIDE") },
		{ "Camo 2", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_02") },
		//{ "Camo 2 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_02_SLIDE") },
		{ "Camo 3", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_03") },
		//{ "Camo 3 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_03_SLIDE") },
		{ "Camo 4", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_04") },
		//{ "Camo 4 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_04_SLIDE") },
		{ "Camo 5", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_05") },
		//{ "Camo 5 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_05_SLIDE") },
		{ "Camo 6", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_06") },
		//{ "Camo 6 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_06_SLIDE") },
		{ "Camo 7", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_07") },
		//{ "Camo 7 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_07_SLIDE") },
		{ "Camo 8", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_08") },
		//{ "Camo 8 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_08_SLIDE") },
		{ "Camo 9", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_09") },
		//{ "Camo 9 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_09_SLIDE") },
		{ "Camo 10", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_10") },
		//{ "Camo 10 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_10_SLIDE") },
		{ "Camo Independence 1", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_IND_01") },
		//{ "Camo Independence 1 Slide", GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_IND_01_SLIDE") },
	}, &WeaponIndivs::vCaptions_TintsMk2 },

	{ WEAPON_PRECISIONRIFLE,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_PRECISIONRIFLE_CLIP_01") },
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region heavy
std::vector<WeaponAndComponents> WeaponIndivs::wc_HEAVY
{
	{ WEAPON_GRENADELAUNCHER,{
		{ "Scope", COMPONENT_AT_SCOPE_SMALL },
		{ "Flashlight", COMPONENT_AT_AR_FLSH },
		{ "Grip", COMPONENT_AT_AR_AFGRIP },
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_RPG,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_MINIGUN,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_FIREWORK,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_RAILGUN,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_HOMINGLAUNCHER,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_COMPACTLAUNCHER,{
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_RAYMINIGUN,{
	}, &WeaponIndivs::vCaptions_Tints },

	{ WEAPON_EMPLAUNCHER,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_EMPLAUNCHER_CLIP_01") },
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_RAILGUNXM3,{
		{ "Standard_Clip", GET_HASH_KEY("COMPONENT_RAILGUNXM3_CLIP_01") },
	}, &WeaponIndivs::vCaptions_Tints },
	{ WEAPON_SNOWLAUNCHER,{
	}, &WeaponIndivs::vCaptions_Tints },
};
#pragma endregion
#pragma region throwables/flame thrower/spillables
std::vector<WeaponAndComponents> WeaponIndivs::wc_THROWABLES
{
	{ WEAPON_GRENADE,{
	}, nullptr },
	{ WEAPON_SMOKEGRENADE,{
	}, nullptr },
	{ WEAPON_STICKYBOMB,{
	}, nullptr },
	{ WEAPON_PROXMINE,{
	}, nullptr },
	{ WEAPON_MOLOTOV,{
	}, nullptr },
	{ WEAPON_FIREEXTINGUISHER,{
	}, nullptr },
	{ WEAPON_PETROLCAN,{
	}, nullptr },
	{ WEAPON_FLARE,{
	}, nullptr },
	{ WEAPON_SNOWBALL,{
	}, nullptr },
	{ WEAPON_PIPEBOMB,{
	}, nullptr },
	{ WEAPON_HAZARDCAN,{
	}, nullptr },
	{ WEAPON_ACIDPACKAGE,{
	}, nullptr },
};
#pragma endregion
#pragma region add-on weapons
std::vector<WeaponAndComponents> WeaponIndivs::wc_ADDON
{

};
#pragma endregion

std::array<std::vector<WeaponAndComponents>*, 10> WeaponIndivs::vAllWeapons =
{
	&WeaponIndivs::wc_MELEE,
	&WeaponIndivs::wc_PISTOLS,
	&WeaponIndivs::wc_SMGS,
	&WeaponIndivs::wc_MGS,
	&WeaponIndivs::wc_ASSAULTRIFLES,
	&WeaponIndivs::wc_SHOTGUNS,
	&WeaponIndivs::wc_SNIPERS,
	&WeaponIndivs::wc_HEAVY,
	&WeaponIndivs::wc_THROWABLES,
	&WeaponIndivs::wc_ADDON
};

const WeaponAndComponents* WeaponIndivs::get_weapon(Hash weaponHash)
{
	for (auto& cc : vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if ((c.weaponHash) == weaponHash)
			{
				return &c;
			}
		}
	}
	return nullptr;
}
bool WeaponIndivs::get_weapon_components(Hash weaponHash, std::vector<NamedWeaponComponent>& result)
{
	for (auto& cc : vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if ((c.weaponHash) == weaponHash)
			{
				result = c.components;
				return !c.components.empty();
			}
		}
	}
	result.clear();
	return false;
}
unsigned __int8 WeaponIndivs::get_weapon_components_count(Hash weaponHash)
{
	for (auto& cc : vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if ((c.weaponHash) == weaponHash)
			{
				return (unsigned __int8)c.components.size();
			}
		}
	}
	return false;
}
bool WeaponIndivs::is_weapon_tintable(Hash weaponHash)
{
	for (auto& cc : vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if ((c.weaponHash) == weaponHash)
			{
				return c.tintCaptions != nullptr;
			}
		}
	}
	return false;
}


// Weapon - labels
std::string get_weapon_label(Hash hash, bool gxt)
{
	auto wit = WeaponIndivs::vWeaponLabels.find(hash);
	if (wit != WeaponIndivs::vWeaponLabels.end())
	{
		return wit->second;
	}
	return gxt ? "Unknown" : std::string();
}

// Weapon - give
void give_ped_parachute(GTAentity ped)
{
	if (ped.Exists())
	{
		int paraState = GET_PED_PARACHUTE_STATE(ped.Handle());
		if ((paraState == -1 || paraState == -3 || paraState == (int)ParachuteState::FallingToDoom))
		{
			GIVE_DELAYED_WEAPON_TO_PED(ped.Handle(), GADGET_PARACHUTE, 1, 0/*1*/);
		}
	}
}
void give_ped_max_ammo(GTAentity ped)
{
	for (auto& cc : WeaponIndivs::vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if (HAS_PED_GOT_WEAPON(ped.Handle(), c.weaponHash, false))
			{
				int maxAmmo = 0;
				GET_MAX_AMMO(ped.Handle(), c.weaponHash, &maxAmmo);
				SET_AMMO_IN_CLIP(ped.Handle(), c.weaponHash, GET_MAX_AMMO_IN_CLIP(ped.Handle(), c.weaponHash, false));
				SET_PED_AMMO(ped.Handle(), c.weaponHash, maxAmmo, 0);
			}
		}
	}
}
void give_all_weapons_to_ped(GTAentity ped, bool bInfAmmo)
{
	if (ped.Exists())
	{
		bool bHasControl = ped.HasControl();
		UINT8 i = 0;
		for (auto& cc : WeaponIndivs::vAllWeapons)
		{
			for (auto& c : *cc)
			{
				if (!HAS_PED_GOT_WEAPON(ped.Handle(), c.weaponHash, false))
				{
					int ammo = bInfAmmo ? -1 : 9999;
					if (i == WeaponIndivs::WEAPE_MELEE) ammo = 1;

					if (bHasControl && ammo != -1)
						GIVE_WEAPON_TO_PED(ped.Handle(), c.weaponHash, ammo, true, false);
					else
						GIVE_DELAYED_WEAPON_TO_PED(ped.Handle(), c.weaponHash, ammo, false);

					for (auto& compHash : c.components)
					{
						GIVE_WEAPON_COMPONENT_TO_PED(ped.Handle(), c.weaponHash, compHash.hash);
					}
				}

				if (!bInfAmmo)
				{
					int maxAmmo = 0;
					GET_MAX_AMMO(ped.Handle(), c.weaponHash, &maxAmmo);
					SET_AMMO_IN_CLIP(ped.Handle(), c.weaponHash, GET_MAX_AMMO_IN_CLIP(ped.Handle(), c.weaponHash, false));
					SET_PED_AMMO(ped.Handle(), c.weaponHash, maxAmmo, 0);
				}

				//SET_PED_WEAPON_TINT_INDEX(ped.Handle(), c.weaponHash, c.tintCaptions->size() - 1);
			}
			i++;
		}
		GIVE_DELAYED_WEAPON_TO_PED(ped.Handle(), GADGET_PARACHUTE, 1, false);
	}
}





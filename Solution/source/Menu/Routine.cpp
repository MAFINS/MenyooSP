/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Routine.h"

#include "..\macros.h"

#include "Menu.h"
#include "MenuConfig.h"

#include "..\Util\FileLogger.h"
#include "..\Util\ExePath.h"
#include "..\Util\keyboard.h"
#include "..\Scripting\enums.h"
#include "..\Natives\types.h" // RGBA/RgbS & types
#include "..\Natives\natives2.h"
#include "..\Scripting\DxHookIMG.h"
#include "..\Scripting\TimecycleModification.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\Camera.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\CustomHelpText.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
//#include "..\Scripting\GTAprop.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\World.h"
#include "..\Scripting\WeaponIndivs.h"
#include "..\Scripting\Raycast.h"
#include "..\Scripting\ModelNames.h"
#include "..\Scripting\GTAblip.h"

#include "..\Misc\FlameThrower.h"
#include "..\Misc\FpsCounter.h"
#include "..\Misc\Gta2Cam.h"
#include "..\Misc\JumpAroundMode.h"
#include "..\Misc\MagnetGun.h"
#include "..\Misc\ManualRespawn.h"
#include "..\Misc\MeteorShower.h"
#include "..\Misc\RopeGun.h"
#include "..\Misc\SmashAbility.h"
#include "..\Misc\VehicleCruise.h"
#include "..\Misc\VehicleFly.h"
#include "..\Misc\VehicleTow.h"

#include "..\Submenus\PedAnimation.h"
#include "..\Submenus\WeaponOptions.h"
#include "..\Submenus\PedComponentChanger.h"
#include "..\Submenus\AnimalRiding.h"
#include "..\Submenus\VehicleSpawner.h"
#include "..\Menu\FolderPreviewBmps.h"
#include "..\Submenus\PedSpeech.h"
#include "..\Submenus\GhostRiderMode.h"
#include "..\Submenus\Spooner\SpoonerMode.h"
#include "..\Submenus\VehicleOptions.h"
#include "..\Submenus\VehicleModShop.h"
#include "..\Submenus\TimeOptions.h"
#include "..\Submenus\BreatheStuff.h"
#include "..\Submenus\MiscOptions.h"
#include "..\Submenus\Teleport\Yachts.h"
#include "..\Submenus\Teleport\TeleMethods.h"
#include "..\Submenus\PtfxSubs.h"
#include "..\Submenus\Spooner\SpoonerEntity.h"
#include "..\Submenus\Spooner\EntityManagement.h"
#include "..\Submenus\CutscenePlayer.h"

#include <Windows.h>
#include <thread>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <time.h> // time/localtime_s


//--------------------------------Threads--------------------------------------------------------

DWORD g_MenyooConfigTick = 0UL;
DWORD g_FaderTick = 0UL;


void Menu::justopened()
{
	Game::Print::PrintBottomLeft(oss_ << "Menyoo PC v" << MENYOO_CURRENT_VER_ << " by ItsJustCurtis and MAFINS");

	SET_AUDIO_FLAG("IsDirectorModeActive", true);

	SET_THIS_SCRIPT_CAN_BE_PAUSED(0);
	SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(0); // lol poopoo dummy me this isn't a ysc

	if (
		IS_DLC_PRESENT(GET_HASH_KEY("mp2023_01_g9ec")) or
		IS_DLC_PRESENT(GET_HASH_KEY("mp2023_02_g9ec")) or
		IS_DLC_PRESENT(GET_HASH_KEY("mpchristmas3_g9ec")) or
		IS_DLC_PRESENT(GET_HASH_KEY("mpg9ec")) or
		IS_DLC_PRESENT(GET_HASH_KEY("mpSum2_G9EC")) or
		IS_DLC_PRESENT(GET_HASH_KEY("patch2023_01_g9ec")) or
		IS_DLC_PRESENT(GET_HASH_KEY("patchday27g9ecng")) or
		IS_DLC_PRESENT(GET_HASH_KEY("patchday28g9ecng")) or
		IS_DLC_PRESENT(GET_HASH_KEY("patchdayg9ecng"))			//this hardcoding needs to get in the bin.
		)
	{
		Game::Print::PrintBottomCentre("~r~Warning~s~: 9th Gen content detected, some instability may occur. See MenyooLog for details.");
		ige::myLog << ige::LogType::LOG_WARNING << "Gen9 Content found in dlcpacks, this can cause crashes if attempted to be loaded by Menyoo." << std::endl << "				    You can find these in your dlclist.xml by searching for \"g9\" and removing these lines or using a comment." << std::endl << "				    For example: <!--<Item>dlcpacks:/mpg9ec/</Item>-->" << std::endl;
	}


	//sub::SettingsThemes_catind::g_menyooTheme_temp = sub::SettingsThemes_catind::MenyooTheme::CurrentlyActiveTheme();

	sub::PopulateAllPaintIDs();

	g_menuNotOpenedYet = false;
}
inline void MenyooMain()
{	
	DxHookIMG::LoadAllMenyooTexturesInit();
	sub::AnimationSub_catind::PopulateAllPedAnimsList();
	sub::WeaponFavourites_catind::PopulateFavouritesInfo();
	sub::PedDecals_catind::PopulateDecalsDict();
	sub::AnimalRiding_catind::PopulateAnimals();
	sub::SpawnVehicle_catind::PopulateVehicleBmps();
	sub::FolderPreviewBmps_catind::PopulateFolderBmps();
	sub::Speech_catind::PopulateVoiceData();
	TimecycleModification::PopulateTimecycleNames();
	PopulateGlobalEntityModelsArrays();
	sub::CutscenePlayer_catind::PopulateCutsceneLabels();

	srand(GetTickCount());
	SET_RANDOM_SEED(GetTickCount());
	//_initialProgramTick = GetTickCount();

	//MenuConfig::ConfigInit();
	g_MenyooConfigTick = GetTickCount();
	g_FaderTick = GetTickCount();

	if (!NETWORK_IS_SESSION_STARTED())
	{
		if (GTAmemory::FindShopController())
			GeneralGlobalHax::EnableBlockedMpVehiclesInSp();
	}

	for (;;)
	{
		DxHookIMG::DxTexture::GlobalDrawOrderRef() = -9999;

		Menu::Tick();
		TickMenyooConfig();
		TickRainbowFader();
		WAIT(0);
	}

}
void ThreadMenyooMain()
{
	MenyooMain();
}

void TickMenyooConfig()
{
	//if (GetTickCount() > g_MenyooConfigOnceTick + 9000U)
		if (GetTickCount() > g_MenyooConfigTick + 30000U)
		{
			if (MenuConfig::bSaveAtIntervals)
			{
				MenuConfig::ConfigSave();
			}
			g_MenyooConfigTick = GetTickCount();
		}
}

void TickRainbowFader()
{
	if (GetTickCount() > g_FaderTick + 20U) {
		auto& colour = g_fadedRGB;
		if (colour.R > 0 && colour.B == 0)
		{
			colour.R--;
			colour.G++;
		}
		if (colour.G > 0 && colour.R == 0)
		{
			colour.G--;
			colour.B++;
		}
		if (colour.B > 0 && colour.G == 0)
		{
			colour.R++;
			colour.B--;
		}

		g_FaderTick = GetTickCount();
	}
}

//--------------------------------On tick--------------------------------------------------------

#pragma region variables used define // p.s. this ain't it chief

INT16 bind_no_clip = VirtualKey::F3;

RgbS g_fadedRGB(255, 0, 0);

UINT8 pause_clock_H, pause_clock_M;
Vehicle g_myVeh = 0;
GTAmodel::Model g_myVeh_model;
Hash g_myWeap = 0U;
PTFX::sFxData triggerfx_gun_data = { "scr_fbi4", "scr_fbi4_trucks_crash" };
Hash kaboom_gun_hash = EXPLOSION::DIR_WATER_HYDRANT, bullet_gun_hash = WEAPON_FLARE;
GTAmodel::Model ped_gun_hash = PedHash::KillerWhale, object_gun_hash = VEHICLE_BUS;
FLOAT current_timescale = 1.0f;
INT Static_241, Static_240, Static_242, Static_12;
const char* Static_239;
INT bit_MSPaints_RGB_mode;
bool kaboom_gun_invis = 0, kaboom_gun_rand_bit = 0, ped_gun_rand_bit = 0, object_gun_rand_bit_o = 0, object_gun_rand_bit_v = 0;
bool bit_night_vision = false;
FLOAT mult69_0 = 0, mult_playerNoiseValue = 1.0f, mult_self_sweat = 0.0f;
FLOAT g_playerVerticalElongationMultiplier = 1.0f;
FLOAT loop_vehicle_damageAndDefense = 1.0f;
FLOAT loop_vehicle_slam = 0.0f;
FLOAT menu_current_timecycle_strength = 1.0f;
INT mult69_5 = 0, mult69_6 = 0, mult69_7 = 0;
INT16 g_frozenRadioStation = -1;
bool bit_vehicle_gravity = 0, bit_freeze_vehicle = 0, VehicleOpsSlippyTires_bit = 0;

INT ms_curr_paint_index = 0;

// String variables used in various submenus for search, storage, etc.
std::string dict, dict2, dict3;

// Spawn vehicle settings
std::string _globalSpawnVehicle_plateText = "MENYOO";
INT8 _globalSpawnVehicle_plateType = 5, _globalSpawnVehicle_plateTexter_value = 0;
RgbS _globalSpawnVehicle_neonCol = { 0, 255, 0 };
bool _globalSpawnVehicle_autoSit = 1, _globalSpawnVehicle_autoUpgrade = 1, _globalSpawnVehicle_invincible = 1, _globalSpawnVehicle_persistent = 0, _globalSpawnVehicle_deleteOld = 0, _globalSpawnVehicle_neonToggle = 0, _globalLSC_Customs = 1;
INT16 _globalSpawnVehicle_PrimCol = -3, _globalSpawnVehicle_SecCol = -3;
bool _globalSpawnVehicle_drawBmps = true;

FLOAT _globalClearArea_radius = 36.0f;

FLOAT _globalRainFXIntensity = 0.0f;

Entity g_drive_water_obj;

INT8 loop_spectate_player = -1;

UINT8 loop_explosion_wp = 0;

bool loop_multiplat_neons = 0, loop_multiplat_neons_rainbow = 0;
RgbS _global_MultiPlatNeons_Col(0, 255, 0);
std::vector<GTAvehicle> _global_MultiPlatNeons_List;

bool loop_Check_self_death_model = false;

UINT8 loop_car_jump = 0;
UINT8 loop_autoKillEnemies = 0;
float loop_weapon_damage_increase = 1.0f;

UINT8 loop_forcefield = 0;
UINT8 loop_self_freezeWantedLevel = 0;
Entity bit_infinite_ammo_enth = 0;

bool loop_RainbowBoxes = 0, loop_forge_gun = 0, loop_player_noRagdoll = 0, loop_player_seatbelt = 0, loop_player_unlimSpecialAbility = 0, loop_player_autoClean = 0, loop_player_Walkunderwater = 0,
loop_explosive_rounds = 0, loop_flaming_rounds = 0, loop_teleport_gun = 0, loop_kaboom_gun = 0, loop_triggerfx_gun = 0, loop_bullet_gun = 0, loop_ped_gun = 0, loop_object_gun = 0, loop_light_gun = 0, loop_bullet_time = 0, loop_self_triggerbot = 0,
loop_explosive_melee = 0, loop_super_jump = 0, loop_self_refillHealthInCover = 0, loop_player_invincibility = 0, loop_no_clip = 0, loop_no_clip_toggle = 0, loop_super_run = 0,
loop_XYZHcoords = 0, loop_ignored_by_everyone = 0, loop_never_wanted = 0, loop_superman = 0, loop_superman_auto = 0,
loop_vehicle_population = 0, loop_ped_population = 0, loop_clearWeaponPickups = 0, loop_drive_on_water = 0, loop_massacre_mode = 0,
loop_player_burn = 0, loop_vehicle_invincibility = 0, loop_vehicle_heavymass = 0, loop_race_boost = 0,
loop_car_hydraulics = 0, loop_super_grip = 0, loop_SuprKarMode = 0, loop_unlimVehBoost = 1,

loop_vehweap_lines = 0, loop_vehicle_RPG = 0, loop_vehicle_fireworks = 0, loop_vehicle_guns = 0, loop_vehicle_snowballs = 0, loop_vehicle_balls = 0, loop_vehicle_waterhyd = 0, loop_vehicle_laser_green = 0, loop_vehicle_flameleak = 0,
loop_vehicle_laser_red = 0, loop_vehicle_turrets_valkyrie = 0, loop_vehicle_flaregun = 0, loop_vehicle_heavysnip = 0, loop_vehicle_tazerweap = 0, loop_vehicle_molotovweap = 0, loop_vehicle_combatpdw = 0,

loop_car_colour_change = 0, loop_vehicle_invisibility = 0, loop_self_engineOn = 0, loop_hide_hud = 0, loop_showFullHud = 0,
loop_pause_clock = 0, loop_sync_clock = 0, loop_triple_bullets = 0, loop_rapid_fire = 0, loop_self_resurrectionGun = 0, loop_soulswitch_gun = 0, loop_self_deleteGun = 0, loop_vehicle_fixloop = 0, loop_vehicle_fliploop = 0,
loop_blackout_mode = 0, loop_simple_blackout_mode = 0, loop_restricted_areas_access = 0, loop_HVSnipers = 0, loop_vehicle_disableSiren = 0, loop_fireworksDisplay = 0,
bit_infinite_ammo = 0, loop_self_inf_parachutes = 0;

Entity targ_slot_entity = 0;
bool targ_entity_locked = 0;

bool bit_grav_gun_disabled = 0;

float forge_dist = 6.0f, _globalForgeGun_prec = 0.2f, _globalForgeGun_shootForce = 300.0f;
bool ObjSpawn_forge_assistance = 0;

#pragma endregion

#pragma region methods used define // p.s. this ain't it chief

// Game - HUD
void display_full_hud_this_frame(bool bEnabled)
{
	DISPLAY_AMMO_THIS_FRAME(bEnabled);
	DISPLAY_CASH(bEnabled);
	//DISPLAY_AREA_NAME(bEnabled);

	std::list<HudComponent> comps
	{
		HudComponent::Cash,
		HudComponent::MpCash,
		HudComponent::MpRankBar,
		HudComponent::WantedStars,
		HudComponent::WeaponIcon,
		//HudComponent::Cash,
		//HudComponent::MpCash,
		HudComponent::VehicleName,
		HudComponent::AreaName,
		//HudComponent::VehicleClass,
		HudComponent::StreetName,
		HudComponent::Reticle,
	};

	if (bEnabled)
	{
		for (auto& x : comps)
		{
			SHOW_HUD_COMPONENT_THIS_FRAME((int)x);
		}
	}
	else
	{
		for (auto& x : comps)
		{
			HIDE_HUD_COMPONENT_THIS_FRAME((int)x);
		}
	}
}

// World - Entities
void update_nearby_stuff_arrays_tick()
{
	_nearbyPeds.clear();
	_nearbyVehicles.clear();

	_worldPeds.clear();
	_worldVehicles.clear();
	_worldObjects.clear();
	_worldEntities.clear();

	//bool alreadyIn;
	GTAmemory::GetVehicleHandles(_worldVehicles);
	GTAmemory::GetPedHandles(_worldPeds);
	GTAmemory::GetPropHandles(_worldObjects);
	GTAmemory::GetEntityHandles(_worldEntities);

	/*INT i, offsettedID, count = 80;

	Ped *peds = new Ped[count * 2 + 2];
	peds[0] = count;
	INT found = GET_PED_NEARBY_PEDS(PLAYER_PED_ID(), peds, -1);
	for (i = 0; i < found; i++)
	{
	offsettedID = i * 2 + 2;

	if (!DOES_ENTITY_EXIST(peds[offsettedID]))	continue;

	_nearbyPeds.push_back(peds[offsettedID]);
	}
	delete[] peds;


	Vehicle *vehicles = new Vehicle[count * 2 + 2];
	vehicles[0] = count;
	found = GET_PED_NEARBY_VEHICLES(PLAYER_PED_ID(), vehicles);
	for (i = 0; i < found; i++)
	{
	offsettedID = i * 2 + 2;

	if (!DOES_ENTITY_EXIST(vehicles[offsettedID]))	continue;

	_nearbyVehicles.push_back(vehicles[offsettedID]);
	}
	delete[] vehicles;*/

	Ped me = PLAYER_PED_ID();
	//Vector3 pedPos = GET_ENTITY_COORDS(me, 1);

	INT i, offsettedID, count = 100;

	Ped *peds = new Ped[count * 2 + 2];
	peds[0] = count;
	INT found = GET_PED_NEARBY_PEDS(me, (Any*)peds, -1);
	for (i = 0; i < found; i++)
	{
		offsettedID = i * 2 + 2;

		if (!DOES_ENTITY_EXIST(peds[offsettedID]))	continue;

		//if (pedPos.DistanceTo(GET_ENTITY_COORDS(peds[offsettedID], 1)) < 100.0f)
		_nearbyPeds.push_back(peds[offsettedID]);

		/*for (auto& wp : _worldPeds)
		{
		if (peds[offsettedID] != wp) alreadyIn = false;
		alreadyIn = true;
		break;
		}
		if (!alreadyIn) _worldPeds.push_back(peds[offsettedID]);*/
	}
	delete[] peds;


	Vehicle *vehicles = new Vehicle[count * 2 + 2];
	vehicles[0] = count;
	found = GET_PED_NEARBY_VEHICLES(me, (Any*)vehicles);
	for (i = 0; i < found; i++)
	{
		offsettedID = i * 2 + 2;

		if (!DOES_ENTITY_EXIST(vehicles[offsettedID]))	continue;

		//if (pedPos.DistanceTo(GET_ENTITY_COORDS(vehicles[offsettedID], 1)) < 100.0f)
		_nearbyVehicles.push_back(vehicles[offsettedID]);

		/*for (auto& wv : _worldVehicles)
		{
		if (vehicles[offsettedID] != wv) alreadyIn = false;
		alreadyIn = true;
		break;
		}
		if (!alreadyIn) _worldVehicles.push_back(vehicles[offsettedID]);*/
	}
	delete[] vehicles;

	/*for (auto& nv : _nearbyVehicles)
	{
	for (auto& wv : _worldVehicles)
	{
	if (nv != wv) alreadyIn = false;
	alreadyIn = true;
	break;
	}
	if (!alreadyIn) _worldVehicles.push_back(nv);
	}
	for (auto& np : _nearbyPeds)
	{
	for (auto& wp : _worldPeds)
	{
	if (np != wp) alreadyIn = false;
	alreadyIn = true;
	break;
	}
	if (!alreadyIn) _worldPeds.push_back(np);
	}*/

	//for (auto& v : _worldVehicles) _worldEntities.push_back(v);
	//for (auto& p : _worldPeds) _worldEntities.push_back(p);
	//for (auto& o : _worldObjects) _worldEntities.push_back(o);

	/*for (auto& veh : _worldVehicles)
	{
	if (pedPos.DistanceTo(GET_ENTITY_COORDS(veh, 1)) < 100.0f)
	_nearbyVehicles.push_back(veh);
	}

	for (auto& ped : _worldPeds)
	{
	if (pedPos.DistanceTo(GET_ENTITY_COORDS(ped, 1)) < 100.0f && ped != me)
	_nearbyPeds.push_back(ped);
	}*/


}

// Game - HUD (teleport to wp command) - Doesn't work in SP?
void SetPauseMenuTeleToWpCommand()
{
	//if ((IS_PAUSE_MENU_ACTIVE())
	{
		if ((PauseMenuState)GET_PAUSE_MENU_STATE() == PauseMenuState::ViewingMap)
		{
			GTAentity myPed = PLAYER_PED_ID();
			if (IS_WAYPOINT_ACTIVE() && myPed.IsAlive())
			{
				//Game::Print::setupdraw(GTAfont::Impact, Vector2(0.3f, 0.3f), false, true, true);
				//Game::Print::drawstring((std::string)"Press ~b~" + (Menu::bit_controller ? "X/Square" : "T") + "~s~ to teleport to waypoint", 0.936f, 0.05f);
				/*auto& ib = Menu::instructional_buttons;
				ib.Load("instructional_buttons");

				ib.PushFunction("SET_MAX_WIDTH");
				ib.PushFloat(100.0f);
				ib.PopFunction();

				ib.PushFunction("TOGGLE_MOUSE_BUTTONS");
				ib.PushBoolean(true);
				ib.PopFunction();

				ib.PushFunction("SET_DATA_SLOT");
				ib.PushInteger(0);
				ib.PushString2(Menu::bit_controller ? GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(2, INPUT_FRONTEND_RLEFT, 1) : "t_T");
				ib.PushTextComponent("Teleport to waypoint");
				ib.PushBoolean(true);
				ib.PushInteger(INPUT_FRONTEND_RLEFT); // Idk if this is even necessary. The bool too.
				ib.PopFunction();

				ib.PushFunction("SET_BACKGROUND_COLOUR");
				ib.PushRGBA(RGBA(0, 0, 0, 80));
				ib.PopFunction();

				ib.PushFunction("DRAW_INSTRUCTIONAL_BUTTONS");
				ib.PushInteger(0);
				ib.PopFunction();

				SET_SCRIPT_GFX_ALIGN(76, 66); // Safezone
				SET_SCRIPT_GFX_ALIGN_PARAMS(0.0f, 0.0f, 0.0f, 0.0f); // Offset
				RESET_SCRIPT_GFX_ALIGN(); // Safezone end
				ib.Render2D();*/

				(Menu::bit_controller ? DxHookIMG::teleToWpBoxIconGamepad : DxHookIMG::teleToWpBoxIconKeyboard).Draw(0, Vector2(0.5f, 0.04f), Vector2(0.0943f, 0.016f), 0.0f, RGBA::AllWhite());

				if (Menu::bit_controller ? IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RLEFT) : IsKeyJustUp(VirtualKey::T))
				{
					sub::TeleportLocations_catind::TeleMethods::ToWaypoint(myPed);
				}
			}
		}
	}
}

// PTFX
void set_Ptfxlop_tick()
{
	using sub::Ptfx_catind::_fxlops;

	if (GET_GAME_TIMER() > Menu::delayedTimer)
	{
		for (auto it = _fxlops.begin(); it != _fxlops.end();)
		{
			if (!it->entity.Exists())
			{
				it = _fxlops.erase(it);
				continue;
			}

			switch ((EntityType)it->entity.Type())
			{
			case EntityType::PED:
				if (IS_PED_A_PLAYER(it->entity.Handle()) && it->entity.Handle() != PLAYER_PED_ID())
					PTFX::trigger_ptfx_1(it->asset, it->fx, NULL, GET_PED_BONE_COORDS(it->entity.Handle(), Bone::SKEL_Head, 0.0f, 0.0f, 0.0f), it->entity.Rotation_get(), GET_RANDOM_FLOAT_IN_RANGE(0.76f, 1.4f));
				else
					PTFX::trigger_ptfx_1(it->asset, it->fx, it->entity, Vector3(), Vector3(), GET_RANDOM_FLOAT_IN_RANGE(0.76f, 1.4f), Bone::SKEL_Head);
				break;
			default:
				//PTFX::trigger_ptfx_1((PCHAR)it->asset.c_str(), (PCHAR)it->fx.c_str(), NULL, Vector3(), it->entity.Rotation_get(), GET_RANDOM_FLOAT_IN_RANGE(0.76f, 1.4f));
				PTFX::trigger_ptfx_1(it->asset, it->fx, it->entity, Vector3(), Vector3(), GET_RANDOM_FLOAT_IN_RANGE(0.76f, 1.4f));
				break;
			}
			++it;
		}
	}
}

// Time
void set_sync_clock_time()
{
	time_t now = time(0);
	tm t;
	localtime_s(&t, &now);
	SET_CLOCK_DATE(t.tm_mday, t.tm_mon, t.tm_year + 1900);
	SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
}

// Misc - massacre mode
void set_massacre_mode_tick()
{
	float tempCoords1[3];
	//Hash tempHash;
	Ped tempPed = PLAYER_PED_ID();
	//int i;
	//bool tick = 0;

	//Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS((tempPed, GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);

	// Apply force to nearby vehicles
	//std::vector<Vehicle>& allVehicles = get_all_nearby_vehicles(tempPed, 50);
	auto& allVehicles = _nearbyVehicles;
	for (GTAentity veh : allVehicles)
	{
		if (veh.Equals(g_myVeh))
			continue;
		veh.RequestControlOnce();
		APPLY_FORCE_TO_ENTITY(veh.Handle(), 1, GET_RANDOM_FLOAT_IN_RANGE(1.0f, 9.0f), GET_RANDOM_FLOAT_IN_RANGE(1.0f, 9.0f), GET_RANDOM_FLOAT_IN_RANGE(1.0f, 6.0f), 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
	}

	// Apply force to nearby peds
	//std::vector<Ped>& allPeds = get_all_nearby_peds(tempPed, 50);
	auto& allPeds = _nearbyPeds;
	for (GTAped ped : allPeds)
	{
		ped.RequestControlOnce();
		ped.GiveNM(NMString::nm0286_handCuffsBehindBack);
		SET_PED_RAGDOLL_FORCE_FALL(ped.Handle());
		APPLY_FORCE_TO_ENTITY(ped.Handle(), 1, GET_RANDOM_FLOAT_IN_RANGE(1.0f, 9.0f), GET_RANDOM_FLOAT_IN_RANGE(1.0f, 9.0f), GET_RANDOM_FLOAT_IN_RANGE(1.0f, 6.0f), 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
	}

	// Water hydrants and explosions
	if (rand() % 2)
	{
		Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::TRAIN, 0.2f, 0, 0, 0.05f, false);
		Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(-25.0f, -50.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::TRAIN, 0.2f, 0, 0, 0.05f, false);

		//Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(9.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		//ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::DIR_WATER_HYDRANT, 8.0f, 1, 0, 0.0f);
	}
	else
	{
		Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(-25.0f, -50.0f), GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::TRAIN, 4.0f, 0, 0, 0.15f, false);
		Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(-25.0f, -50.0f), GET_RANDOM_FLOAT_IN_RANGE(-25.0f, -50.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::TRAIN, 4.0f, 0, 0, 0.15f, false);

		//Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(-9.0f, -25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f))).ToArray(tempCoords1);
		//ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], EXPLOSION::DIR_WATER_HYDRANT, 8.0f, 1, 0, 0.0f);
	}
	// Zombies
	/*tempHash = PedHash::Zombie01;
	if (GET_GAME_TIMER() >= Menu::delayedTimer)
	{
	if (!HAS_MODEL_LOADED(tempHash)) REQUEST_MODEL(tempHash);
	else
	{
	Vector3(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(tempPed, GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(25.0f, 50.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 5.0f))).ToArray(tempCoords1);
	tempPed = CREATE_PED(PedType::Human, 2890614022, tempCoords1[0], tempCoords1[1], tempCoords1[2], GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
	SET_NETWORK_ID_CAN_MIGRATE(PED_TO_NET(tempPed), 1);
	SET_PED_COMBAT_ABILITY(tempPed, 100);
	TASK_COMBAT_PED(tempPed, PLAYER_PED_ID(), 0, 16);
	TASK_COMBAT_HATED_TARGETS_AROUND_PED(tempPed, 400.0f, 0);
	SET_PED_AS_NO_LONGER_NEEDED(&tempPed);
	}
	}*/


}

// Misc
void set_blackoutEmp_mode()
{
	SET_ARTIFICIAL_LIGHTS_STATE(TRUE);

	for (auto& vehicle : _nearbyVehicles)
	{
		if (vehicle == g_myVeh) continue;

		NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
		SET_VEHICLE_ENGINE_ON(vehicle, 0, 1, 0);
		//SET_VEHICLE_LIGHTS(vehicle, 4);

	}

	ScrHandle tempSeq;
	OPEN_SEQUENCE_TASK(&tempSeq);
	TASK_LEAVE_ANY_VEHICLE(0, 0, 0);
	TASK_CLEAR_LOOK_AT(0);
	TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(0, 0);
	TASK_STAND_STILL(0, 300);
	TASK_START_SCENARIO_IN_PLACE(0, "WORLD_HUMAN_STAND_IMPATIENT", 800, 1);
	TASK_USE_MOBILE_PHONE_TIMED(0, 6000);
	//TASK_START_SCENARIO_IN_PLACE(0, "WORLD_HUMAN_STAND_MOBILE", 6000, 1);
	TASK_WANDER_STANDARD(0, 0x471c4000, 0);
	CLOSE_SEQUENCE_TASK(tempSeq);

	for (auto& ped : _nearbyPeds)
	{
		if (GET_SEQUENCE_PROGRESS(ped) < 0)
		{
			if (!IS_PED_IN_ANY_VEHICLE(ped, 0))
				continue;
			if (GET_ENTITY_SPEED(GET_VEHICLE_PED_IS_IN(ped, 0)) > 0.6f)
				continue;

			NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
			TASK_PERFORM_SEQUENCE(ped, tempSeq);
			SET_PED_KEEP_TASK(ped, 1);
			SET_PED_FLEE_ATTRIBUTES(ped, 0, 1);
			SET_PED_FLEE_ATTRIBUTES(ped, 1024, 1);
			SET_PED_FLEE_ATTRIBUTES(ped, 131072, 1);
		}
	}
	CLEAR_SEQUENCE_TASK(&tempSeq);
	//SET_ALL_RANDOM_PEDS_FLEE(PLAYER_ID(), 1);

}
void set_blackout_mode()
{
	SET_ARTIFICIAL_LIGHTS_STATE(TRUE);
	SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(FALSE);
}

// Playerped - ability
void set_self_nearby_peds_calm()
{
	for (auto& ped : _nearbyPeds)
	{
		NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
		SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
		SET_PED_FLEE_ATTRIBUTES(ped, 0, 0);
		SET_PED_COMBAT_ATTRIBUTES(ped, 17, 1);
	}
}
void network_set_everyone_ignore_player(Player player)
{
	SET_POLICE_IGNORE_PLAYER(player, 1);
	SET_EVERYONE_IGNORE_PLAYER(player, 1);
	SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, 0);
	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, 1);
}

// World
void set_explosion_at_coords(GTAentity entity, Vector3 pos, UINT8 type, float radius, float camshake, bool sound, bool invis, GTAentity owner)
{
	const Vector3& Pos = (entity.Handle() == 0) ? pos : entity.GetOffsetInWorldCoords(pos);

	if (owner.Handle() != 0 && owner.IsPed())
		ADD_OWNED_EXPLOSION(owner.Handle(), Pos.x, Pos.y, Pos.z, type, radius, sound, invis, camshake);
	else
		ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, type, radius, sound, invis, camshake, false);
}
// World-Misc
void start_fireworks_at_coord(const Vector3& pos, const Vector3& rot, float scale)
{
	if (!HAS_NAMED_PTFX_ASSET_LOADED("scr_indep_fireworks"))
		REQUEST_NAMED_PTFX_ASSET("scr_indep_fireworks");
	{
		std::vector<std::string> fw{ "scr_indep_firework_starburst", "scr_indep_firework_fountain", "scr_indep_firework_shotburst", "scr_indep_firework_trailburst" };
		//_9C720B61("scr_indep_fireworks");
		USE_PARTICLE_FX_ASSET("scr_indep_fireworks");
		SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f));
		START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(fw[rand() % 4].c_str(), pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, scale, 0, 0, 0, false);
	}
}

// Weapon - funguns
void set_target_into_slot()
{
	GTAplayer player = PLAYER_ID();

	if (player.IsTargetingAnything() || player.IsFreeAiming())
	{
		if (loop_rapid_fire)
			set_rapid_fire();
		if (loop_self_triggerbot)
			set_player_triggerbot(player);
		if (loop_soulswitch_gun)
			set_soulswitch_gun();
		if (loop_self_deleteGun)
			set_self_deleteGun();
		if (loop_self_resurrectionGun)
			set_self_resurrectionGun();
		if (loop_HVSnipers)
			set_HVSnipers(true);

		if (!targ_entity_locked)
		{
			targ_slot_entity = player.AimedEntity().GetHandle();
			if (targ_slot_entity == 0)
			{
				GTAentity aimedEntity = World::EntityFromAimCamRay();
				if (aimedEntity.Handle() != 0)
				{
					targ_slot_entity = aimedEntity.Handle();
				}
				else
				{
					targ_slot_entity = 0;
					return;
				}
			}

			if (IS_ENTITY_A_PED(targ_slot_entity))
			{
				if (IS_PED_SITTING_IN_ANY_VEHICLE(targ_slot_entity))
					targ_slot_entity = GET_VEHICLE_PED_IS_IN(targ_slot_entity, 0);
				//else if (loop_target_into_slot && IS_PED_A_PLAYER(targ_slot_entity)){ Game::Print::PrintBottomCentre("~r~Error:~s~ That's a player."); } //targ_slot_entity = 0; return; }
			}

			targ_entity_locked = true;

			//if (loop_target_into_slot)
			//{
			//	Hash hash = GET_ENTITY_MODEL(targ_slot_entity);
			//	/*inull = GET_BLIP_FROM_ENTITY(*current_obj);
			//	if (DOES_BLIP_EXIST(inull)) REMOVE_BLIP(&inull);
			//	inull = ADD_BLIP_FOR_ENTITY(targ_slot_entity);
			//	set_blip_spr(inull, hash);
			//	SET_BLIP_AS_FRIENDLY(inull, 1);
			//	SET_BLIP_SCALE(inull, 0.7f);
			//	SET_BLIP_COLOUR(inull, 2);*/

			//	*current_obj = targ_slot_entity;
			//	sprintf_s(str, "~o~TARGET CAPTURED!~s~ (Slot %i) (Hash %llu)", obj_num, hash);
			//	Game::Print::PrintBottomCentre(str);
			//}
		}
	}
	else
	{
		if (loop_HVSnipers)
			set_HVSnipers(false);
		targ_entity_locked = false;
		targ_slot_entity = 0;
	}
	//if (IS_CONTROL_JUST_RELEASED(0, INPUT_AIM)) { targ_entity_locked = false; }
}
void set_player_triggerbot(GTAplayer player)
{
	GTAentity playerPed = player.GetPed();

	if (player.IsTargetingAnything() || player.IsFreeAiming())
	{
		GTAentity target;
		if (GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player.Handle(), &target.Handle()))
		{
			if (target.IsPed() && target.IsAlive())
			{
				Hash weap = 0;
				GET_CURRENT_PED_WEAPON(playerPed.Handle(), &weap, true);

				if (IS_WEAPON_VALID(weap))
				{
					static const std::array<int, 1> _triggerbot_bonelist
					{ {
							Bone::SKEL_Head,
							/*Bone::SKEL_L_Hand,
							Bone::SKEL_L_Forearm,
							Bone::SKEL_L_UpperArm,
							Bone::SKEL_R_Hand,
							Bone::SKEL_R_Forearm,
							Bone::SKEL_R_UpperArm,
							Bone::SKEL_Pelvis,
							Bone::SKEL_L_Thigh,
							Bone::SKEL_L_Foot,
							Bone::SKEL_R_Foot*/
						} };
					const Vector3& targetPos = GET_PED_BONE_COORDS(target.Handle(), _triggerbot_bonelist[rand() % _triggerbot_bonelist.size()], 0.0f, 0.0f, 0.0f);
					if (player.Handle() == PLAYER_ID())
					{
						// Raycast or nah?
						SET_PED_SHOOTS_AT_COORD(playerPed.Handle(), targetPos.x, targetPos.y, targetPos.z, 0);
					}
					else
					{
						GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed.Handle(), 0);
						const Vector3& launchPos = gunObj.GetOffsetInWorldCoords(0, gunObj.Dim1().y, 0); //GTAentity(GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ped.Handle())).GetBoneCoords("Gun_Nuzzle");
						CLEAR_AREA_OF_PROJECTILES(launchPos.x, launchPos.y, launchPos.z, 4.0f, 0);
						World::ShootBullet(launchPos, targetPos, playerPed, weap, 5, -1, true, true);
					}
				}
			}
		}
	}
}
void set_rapid_fire()
{
	/*if (myWeap == 2725352035 || myWeap == 4194021054 || myWeap == 148160082 || myWeap == 2578778090 || myWeap == 1737195953 || myWeap == 1317494643 || myWeap == 2508868239 || myWeap == 1141786504 || myWeap == 2227010557 || myWeap == 4192643659 || myWeap == 2460120199 || myWeap == 3494679629 || myWeap == 2803906140 || myWeap == 4222310262 || myWeap == 0xF9DCBF2D)
	return;*/
	if (GET_WEAPONTYPE_GROUP(g_myWeap) == WeaponGroupHash::Melee)
		return;

	DISABLE_CONTROL_ACTION(0, INPUT_ATTACK, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_ATTACK2, TRUE);

	if (/*!IS_PLAYER_DEAD(PLAYER_ID()) && */IS_DISABLED_CONTROL_PRESSED(0, INPUT_ATTACK))
	{
		Player playerPed = PLAYER_PED_ID();
		GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed, 0);
		//Vector3& launchPos = gunObj.GetOffsetInWorldCoords(0, gunObj.Dim1().y, 0); //get_coords_from_cam(GameplayCamera::Position_get().DistanceTo(GET_ENTITY_COORDS(GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed), 1)) + 0.3f);
		/*	if (GET_WEAPONTYPE_GROUP(g_myWeap) == WeaponGroupHash::Throwable)
		{
		myPos = get_coords_from_cam(GameplayCamera::Position_get().DistanceTo(GET_ENTITY_COORDS(playerPed, 1)) + 0.56f);
		}
		else
		{
		myPos = GTAentity(GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed)).GetBoneCoords("Gun_Nuzzle");
		}*/
		//Vector3& targPos = GameplayCamera::RaycastForCoord(Vector2(0.0f, 0.0f), gunObj, 340.0f, 200.0f); //get_coords_from_cam(340.0f);
		// //Vector3& targPos = GameplayCamera::GetOffsetInWorldCoords(Vector3(0.0f, 340.0f, 0.0f));
		const Vector3& camDir = GameplayCamera::DirectionFromScreenCentre_get();
		const Vector3& camPos = GameplayCamera::Position_get();
		const Vector3& launchPos = camPos + (camDir * (camPos.DistanceTo(gunObj.Position_get()) + 0.4f));
		const Vector3& targPos = camPos + (camDir * 200.0f);

		CLEAR_AREA_OF_PROJECTILES(launchPos.x, launchPos.y, launchPos.z, 6.0f, 0);

		SET_CONTROL_SHAKE(0, 250, 125);
		World::ShootBullet(launchPos, targPos, playerPed, g_myWeap, 5, 24000.0f, true, true);
		World::ShootBullet(launchPos, targPos, playerPed, g_myWeap, 5, 24000.0f, true, true);
		STOP_CONTROL_SHAKE(0);
		//SET_CONTROL_SHAKE(0, 0, 0);
	}

}
void set_soulswitch_gun()
{
	if (g_myWeap != WEAPON_COMBATPISTOL)
		return;

	DISABLE_CONTROL_ACTION(0, INPUT_ATTACK, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_ATTACK2, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_VEH_ATTACK, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_VEH_ATTACK2, TRUE);

	GTAplayer player = PLAYER_ID();
	GTAentity playerPed = PLAYER_PED_ID();
	ScrHandle ehandle;
	if (GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player.Handle(), &ehandle))
	{
		GTAentity soulswitchentity = ehandle;

		if (soulswitchentity.IsPed() && soulswitchentity.IsAlive()
			&& (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK) || (IS_PED_IN_ANY_VEHICLE(playerPed.Handle(), false) && IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_VEH_ATTACK))))
		{
			if (IS_SPECIAL_ABILITY_ACTIVE(PLAYER_ID(), 0))
			{
				SPECIAL_ABILITY_DEACTIVATE_FAST(PLAYER_ID(), 0);
				WAIT(16);
			}

			Game::Sound::PlayFrontend("Knuckle_Crack_Hard_Cel", "MP_SNACKS_SOUNDSET");
			ANIMPOSTFX_PLAY("MinigameEndNeutral", 0, 0); // FocusIn
			set_become_ped(soulswitchentity);

			SET_CONTROL_SHAKE(0, 4000, 210);
			STOP_CONTROL_SHAKE(0);

			if (Static_241 == playerPed.Handle())
				Static_241 = PLAYER_PED_ID();

			soulswitchentity.Handle() = 0;
			sub::Spooner::SpoonerEntity spe;
			spe.Handle = playerPed;
			if (!(sub::Spooner::EntityManagement::GetEntityIndexInDb(spe) >= 0))
			{
				playerPed.NoLongerNeeded();
			}

			WAIT(64);

			playerPed = PLAYER_PED_ID();
			//player = PLAYER_ID();

			SET_CURRENT_PED_WEAPON(playerPed.Handle(), WEAPON_COMBATPISTOL, true);
			SET_PED_CURRENT_WEAPON_VISIBLE(playerPed.Handle(), 1, 1, 1, 0);
		}
	}
}
void set_self_deleteGun()
{
	//GTAentity myPed = PLAYER_PED_ID();

	if (g_myWeap == WEAPON_SNSPISTOL)
	{
		if (IS_PED_SHOOTING(PLAYER_PED_ID()))
		{
			GTAentity targEntity = World::EntityFromAimCamRay();

			if (targEntity.Handle())
			{
				sub::Spooner::SpoonerEntity ent;
				ent.Handle = targEntity;
				sub::Spooner::EntityManagement::DeleteEntity(ent);
			}
		}
	}
}
void set_self_resurrectionGun()
{
	if (g_myWeap == WEAPON_STUNGUN)
	{
		GTAentity myPed = PLAYER_PED_ID();
		if (IS_PED_SHOOTING(myPed.Handle()))
		{
			GTAped targPed = World::EntityFromAimCamRay();

			if (targPed.IsPed() && targPed.IsDead())
			{
				targPed.RequestControl();
				targPed.Health_set(200);
				RESURRECT_PED(targPed.Handle());
				REVIVE_INJURED_PED(targPed.Handle());
				targPed.MaxHealth_set(400);
				targPed.Health_set(200);
				SET_PED_GENERATES_DEAD_BODY_EVENTS(targPed.Handle(), false);
				SET_PED_CONFIG_FLAG(targPed.Handle(), 166, 0);
				SET_PED_CONFIG_FLAG(targPed.Handle(), 187, 0);

				targPed.Task().ClearAllImmediately();
				TaskSequence seq;
				seq.AddTask().PlayAnimation("get_up@directional@movement@from_knees@standard", rand() % 3 == 1 ? "getup_r_90" : "getup_l_90", 8.0f, -8.0f, -1, AnimFlag::SecondTask, 0, false);
				seq.AddTask().WanderAround();
				seq.Close();
				seq.MakePedPerform(targPed);
				seq.Clear();
			}
		}
	}
}
void set_HVSnipers(bool set)
{
	/*if (g_myWeap == 100416529 ||
	g_myWeap == 205991906 ||
	g_myWeap == 856002082 ||
	g_myWeap == 3342088282
	*/
	if (set && g_myWeap == WEAPON_UNARMED)
		return;
	SET_SEETHROUGH(set);
}
// Weapon - funguns - onshoot
void set_teleport_gun()
{
	GTAentity myPed = PLAYER_PED_ID();
	Hash weap;
	GET_CURRENT_PED_WEAPON(myPed.Handle(), &weap, true);
	if (weap == WEAPON_HEAVYPISTOL)
	{
		GTAentity ent = IS_PED_IN_ANY_VEHICLE(myPed.Handle(), false) ? g_myVeh : myPed;
		//Vector3& targetPos = myPed.LastWeaponImpactCoord();
		Vector3 targetPos;
		const Vector3& camPos = GameplayCamera::Position_get();
		const Vector3& camDir = GameplayCamera::DirectionFromScreenCentre_get();
		auto ray = RaycastResult::Raycast(camPos, camDir, 15000.0f, IntersectOptions::Everything, myPed);
		if (ray.DidHitAnything())
		{
			if (ray.DidHitEntity())
			{
				const GTAentity& hitEntity = ray.HitEntity();
				if (hitEntity.IsVehicle() || !hitEntity.MissionEntity_get())
					targetPos = hitEntity.Position_get() + Vector3(0, 0, hitEntity.Dim2().z + ent.Dim1().z);
				else
					targetPos = ray.HitCoords();
			}
			else targetPos = ray.HitCoords();

			if (!targetPos.IsZero())
			{
				ent.RequestControl();
				ent.Position_set(targetPos);
				Game::Sound::PlayFrontend("Knuckle_Crack_Hard_Cel", "MP_SNACKS_SOUNDSET");
				ANIMPOSTFX_PLAY("ExplosionJosh3", 0, 0);
			}
		}
	}
}
void set_bullet_gun()
{
	GTAentity playerPed = PLAYER_PED_ID();

	//GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed.Handle());
	//Vector3& launchPos = gunObj.GetOffsetInWorldCoords(0, gunObj.Dim1().y, 0); //GTAentity(GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed.Handle())).GetBoneCoords("Gun_Nuzzle");
	//Vector3& targPos = GameplayCamera::RaycastForCoord(Vector2(0.0f, 0.0f), gunObj, 340.0f, 200.0f); //get_coords_from_cam(340.0f);
	//CLEAR_AREA_OF_PROJECTILES(launchPos.x, launchPos.y, launchPos.z, 6.0f, 0);
	//SHOOT_SINGLE_BULLET_BETWEEN_COORDS(launchPos.x, launchPos.y, launchPos.z, targPos.x, targPos.y, targPos.z, 5, 1, bullet_gun_hash.hash, playerPed.Handle(), 0, 1, 2500.0f);

	GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed.Handle(), 0);
	const Vector3& camDir = GameplayCamera::DirectionFromScreenCentre_get();
	const Vector3& camPos = GameplayCamera::Position_get();
	const Vector3& launchPos = camPos + (camDir * (camPos.DistanceTo(gunObj.Position_get()) + 0.4f));
	const Vector3& targPos = camPos + (camDir * 200.0f);

	CLEAR_AREA_OF_PROJECTILES(launchPos.x, launchPos.y, launchPos.z, 6.0f, 0);
	World::ShootBullet(launchPos, targPos, playerPed, bullet_gun_hash, 5, 2500.0f, true, true);
}
void set_ped_gun()
{
	if (ped_gun_rand_bit) { ped_gun_hash = GET_HASH_KEY(g_pedModels[rand() % (INT)g_pedModels.size()].first); ped_gun_hash.Load(200); }

	if (ped_gun_hash.IsLoaded())
	{
		GTAentity myPed = PLAYER_PED_ID();
		//GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(myPed.Handle());
		//Vector3& launchPos = gunObj.GetOffsetInWorldCoords(0, gunObj.Dim1().y + ped_gun_hash.Dim2().y + 0.2f, 0); //GTAentity(GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ped.Handle())).GetBoneCoords("Gun_Nuzzle");
		const Vector3& launchPos = get_coords_from_cam(GameplayCamera::Position_get().DistanceTo(myPed.Position_get()) + ped_gun_hash.Dim2().y + 0.5f);
		const Vector3& Rot = GameplayCamera::Rotation_get();

		GTAentity spawnedPed = CREATE_PED(PedType::Human, ped_gun_hash.hash, launchPos.x, launchPos.y, launchPos.z, Rot.z, 1, 1);
		spawnedPed.Rotation_set(Rot);
		//auto& spawnedPed = World::CreatePed(ped_gun_hash, launchPos, Rot, false);
		spawnedPed.ApplyForceRelative(Vector3(0, 300.0f, 0), Vector3(0, -0.65f, 0), ForceType::MaxForceRot);

		spawnedPed.NoLongerNeeded();
	}
	if (ped_gun_rand_bit)
		ped_gun_hash.Unload();
}
void set_object_gun()
{
	Entity tempPed = PLAYER_PED_ID();
	Entity tempEntity;

	if (object_gun_rand_bit_o) { object_gun_hash = GET_HASH_KEY(objectModels[rand() % (INT)objectModels.size()]); }
	else if (object_gun_rand_bit_v) { object_gun_hash = g_vehHashes[rand() % (INT)g_vehHashes.size()]; }

	if (object_gun_hash.IsInCdImage())
	{
		if (object_gun_rand_bit_o || object_gun_rand_bit_v) object_gun_hash.Load(160);

		const Vector3& launchPos = get_coords_from_cam(GameplayCamera::Position_get().DistanceTo(GET_ENTITY_COORDS(tempPed, 1)) + object_gun_hash.Dim2().y + 1.355f);
		const Vector3& Rot = GET_GAMEPLAY_CAM_ROT(2);

		if (object_gun_hash.IsVehicle())
			tempEntity = CREATE_VEHICLE(object_gun_hash.hash, launchPos.x, launchPos.y, launchPos.z, GET_ENTITY_HEADING(tempPed), 1, 1, 0);
		else tempEntity = CREATE_OBJECT(object_gun_hash.hash, launchPos.x, launchPos.y, launchPos.z, 1, 1, 1);
		SET_ENTITY_ROTATION(tempEntity, Rot.x, Rot.y, Rot.z, 2, 1);
		APPLY_FORCE_TO_ENTITY(tempEntity, 1, 0.0f, 350.0f, 0.0f, 0.0f, -0.65f, 0.0f, 0, 1, 1, 1, 0, 1);

		if (object_gun_rand_bit_o || object_gun_rand_bit_v) object_gun_hash.Unload();

		if (DOES_ENTITY_EXIST(tempEntity))
			SET_ENTITY_AS_NO_LONGER_NEEDED(&tempEntity);
	}
}
void set_light_gun()
{
	GTAentity myPed = PLAYER_PED_ID();

	if (IS_PED_SHOOTING(myPed.Handle()))
	{
		const auto& colour = RgbS::Random();
		//Vector2 size = { GET_RANDOM_FLOAT_IN_RANGE(0.6, 1.8), GET_RANDOM_FLOAT_IN_RANGE(2.6, 4.0) };
		//Vector2 size = { 1.5f, 3.0f };

		Game::Sound::GameSound soundEffect("EPSILONISM_04_SOUNDSET", "IDLE_BEEP");
		soundEffect.Play(myPed);

		const Vector3& camPos = GameplayCamera::Position_get();
		const Vector3& camDir = GameplayCamera::DirectionFromScreenCentre_get();
		float launchDist;
		GTAentity myWeaponEntity = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(myPed.Handle(), 0);
		if (myWeaponEntity.Exists())
			launchDist = camPos.DistanceTo(myWeaponEntity.Position_get()) + 0.26f;
		else
			launchDist = camPos.DistanceTo(myPed.Position_get()) + 0.44f;

		for (float i = launchDist; i < 260.0f; i += 0.02f)
		{
			World::DrawLightWithRange(camPos + (camDir * i), colour, 1.0f, 3.0f);
		}

		//DWORD maxtick = GetTickCount() + 620;
		//for (float i = meFromCam() + 0.4f; GetTickCount() < maxtick; i += 0.2f)
		//{
		//	World::DrawLightWithRange(get_coords_from_cam(i), colour, 1.0f, 1.0f);
		//}

	}
}
void set_triple_bullets()
{
	if (GET_WEAPONTYPE_GROUP(g_myWeap) == WeaponGroupHash::Melee)
		return;
	Player playerPed = PLAYER_PED_ID();

	GTAentity gunObj = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed, 0);
	const Vector3& launchPos = gunObj.GetOffsetInWorldCoords(0, gunObj.Dim1().y, 0);
	/*Vector3 myPos[]
	{
	get_coords_from_cam(meFromCam() + 0.63f),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1, 1, 0.2),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -0.75, 1, 0.2),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -0.5, 1, 0.2),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.5, 1, 0.2),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.75, 1, 0.2),
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 1, 1, 0.2),
	};*/
	Vector3 targPos[]
	{
		{ -2, 2, 2 },
		{ -1.5, 1, 1 },
		{ -1, 0, 0 },
		//{ 0, 0, 0 },
		{ 1, 0, 0 },
		{ 1.5, 1, 1 },
		{ 2, 2, 2 }
	};

	CLEAR_AREA_OF_PROJECTILES(launchPos.x, launchPos.y, launchPos.z, 6.0f, 0);

	float maxDist = GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(playerPed);

	for (auto& pos : targPos)
		//World::ShootBullet(launchPos, camPos + (camDir * maxDist) + pos, playerPed, g_myWeap, 5, 0xbf800000, true, true);
		World::ShootBullet(launchPos, GameplayCamera::RaycastForCoord(Vector2(0.0f, 0.0f), playerPed, maxDist, maxDist) + pos, playerPed, g_myWeap, 5, 0xbf800000, true, true);

}
// Forge gun
void set_forge_gun_dist(float& distance)
{
	DISABLE_CONTROL_ACTION(2, INPUT_LOOK_BEHIND, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_NEXT, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_PREV, TRUE);
	if (Menu::bit_controller)
	{
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_RS)) distance += 0.166f;
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_LS))
		{
			if (distance > 3.0f) distance -= 0.166f;
			auto ped = PLAYER_PED_ID();
			if (GET_PED_STEALTH_MOVEMENT(ped)) SET_PED_STEALTH_MOVEMENT(ped, 0, 0);
			if (GET_PED_COMBAT_MOVEMENT(ped)) SET_PED_COMBAT_MOVEMENT(ped, 0);
		}
	}
	else
	{
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_CURSOR_SCROLL_UP)) distance += 0.32f;
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_CURSOR_SCROLL_DOWN))
		{
			if (distance > 3.0f) distance -= 0.32f;
		}
	}

	ENABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_NEXT, TRUE);
	ENABLE_CONTROL_ACTION(2, INPUT_WEAPON_WHEEL_PREV, TRUE);
}
inline void set_forge_gun_rot_hotkeys()
{
	Vector3 Rot = GET_ENTITY_ROTATION(targ_slot_entity, 2);
	FLOAT &precision = _globalForgeGun_prec;

	if (!Menu::bit_controller)
	{
		if (IsKeyDown(VK_OEM_4)) Rot.x -= precision;
		if (IsKeyDown(VK_OEM_6)) Rot.x += precision;
		if (IsKeyDown(VK_OEM_1)) Rot.y -= precision;
		if (IsKeyDown(VK_OEM_7)) Rot.y += precision;
		if (IsKeyDown(VK_OEM_COMMA)) Rot.z -= precision;
		if (IsKeyDown(VK_OEM_PERIOD)) Rot.z += precision;

	}
	else
	{
		DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_NEXT, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_PREV, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_LR, TRUE);
		//DISABLE_CONTROL_ACTION(2, INPUT_INTERACTION_MENU, TRUE);
		//DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, TRUE);
		//DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_PAUSE, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_MAP, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_SELECT_NEXT_WEAPON, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_CANCEL, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_SELECT, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_UP, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_DOWN, TRUE);


		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_DOWN)) Rot.x -= precision;
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_UP)) Rot.x += precision;
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LEFT)) Rot.y -= precision;
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RIGHT)) Rot.y += precision;
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LB)) Rot.z -= precision;
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RB)) Rot.z += precision;
	}

	SET_ENTITY_ROTATION(targ_slot_entity, Rot.x, Rot.y, Rot.z, 2, 1);
}
void set_forge_gun()
{
	Ped tempPed = PLAYER_ID();

	if (g_myWeap == WEAPON_PISTOL && (IS_PLAYER_FREE_AIMING(tempPed) || IS_PLAYER_TARGETTING_ANYTHING(tempPed)))
	{
		if (!DOES_ENTITY_EXIST(targ_slot_entity) || bit_grav_gun_disabled)
			return;

		if (forge_dist == 0) forge_dist = GameplayCamera::Position_get().DistanceTo(GET_ENTITY_COORDS(targ_slot_entity, 1));
		set_forge_gun_dist(forge_dist);
		set_forge_gun_rot_hotkeys();

		Vector3 Coord, dim2;
		dim2 = GTAentity(targ_slot_entity).Dim2();
		float h = GET_ENTITY_HEADING(targ_slot_entity), hh = GET_ENTITY_HEADING(PLAYER_PED_ID());
		if (h > (hh - 50) && h < (hh + 50))
			Coord = get_coords_from_cam(forge_dist + abs(dim2.y));
		else
			Coord = get_coords_from_cam(forge_dist + abs(dim2.x));

		/*if (!DOES_PARTICLE_FX_LOOPED_EXIST(grav_partfx))
		{
		REQUEST_PTFX_ASSET();
		if (HAS_PTFX_ASSET_LOADED())
		{
		USE_PARTICLE_FX_ASSET("scr_drug_traffic_flare_L");
		grav_partfx = START_PARTICLE_FX_LOOPED_AT_COORD("scr_drug_traffic_flare_L", Coord.x, Coord.y, Coord.z, 0.0f, 0.0f, 0.0f, 3.0f, 0, 0, 0, 0);
		SET_PARTICLE_FX_LOOPED_COLOUR(grav_partfx, GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), 0);
		}
		}*/

		GTAentity(targ_slot_entity).RequestControl();
		SET_ENTITY_COORDS_NO_OFFSET(targ_slot_entity, Coord.x, Coord.y, Coord.z, 0, 0, 0);
		FREEZE_ENTITY_POSITION(targ_slot_entity, ObjSpawn_forge_assistance);
		///if (!ObjSpawn_forge_assistance) ACTIVATE_PHYSICS(targ_slot_entity);

		//World::DrawLine(get_coords_from_cam(meFromCam() + 0.366f), Coord, titlebox);

		if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK))
		{
			FREEZE_ENTITY_POSITION(targ_slot_entity, 0);

			PLAY_SOUND_FROM_ENTITY(-1, "Foot_Swish", targ_slot_entity, "docks_heist_finale_2a_sounds", 0, 0);
			PLAY_SOUND_FROM_ENTITY(-1, "SUSPENSION_SCRIPT_FORCE", targ_slot_entity, 0, 0, 0);
			PLAY_SOUND_FROM_ENTITY(-1, "Chopper_Destroyed", PLAYER_PED_ID(), "FBI_HEIST_FIGHT_CHOPPER_SOUNDS", 0, 0);
			dim2 = GET_GAMEPLAY_CAM_ROT(2);
			SET_ENTITY_ROTATION(targ_slot_entity, dim2.x, dim2.y, dim2.z, 2, 1);
			APPLY_FORCE_TO_ENTITY(targ_slot_entity, 1, 0.0f, _globalForgeGun_shootForce, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
			PTFX::trigger_ptfx_1("scr_carsteal4", "scr_carsteal4_wheel_burnout", 0, Coord, Vector3(), 0.66f);

			targ_slot_entity = 0;
			forge_dist = 0;
			bit_grav_gun_disabled = true;
			targ_entity_locked = false;
		}

		//if (!IS_PLAYER_FREE_AIMING_AT_ENTITY(tempPed, targ_slot_entity) || !IS_PLAYER_TARGETTING_ENTITY(tempPed, targ_slot_entity)) targ_entity_locked = false;
	}
	else
	{
		forge_dist = 0;
		bit_grav_gun_disabled = false;
		/*if (DOES_PARTICLE_FX_LOOPED_EXIST(grav_partfx))
		{
		STOP_PARTICLE_FX_LOOPED(grav_partfx, 0);
		REMOVE_PARTICLE_FX(grav_partfx, 0);
		REMOVE_PTFX_ASSET();
		}*/
	}

}
// Weapon - bullet hit/raycast
void set_explosion_at_bullet_hit(Ped ped, Hash type, bool invisible)
{
	Vector3_t Pos;
	if (!GET_PED_LAST_WEAPON_IMPACT_COORD(ped, &Pos) && ped == PLAYER_PED_ID())
	{
		const Vector3& camDir = GameplayCamera::Direction_get();
		const Vector3& camCoord = GameplayCamera::Position_get();
		Vector3 hitCoord = (camDir * 1000.0f) + camCoord;

		RaycastResult ray = RaycastResult::Raycast(camCoord, hitCoord, IntersectOptions::Everything);
		if (ray.DidHitAnything())
		{
			Pos = hitCoord.ToTypeStruct();
		}
		else
		{
			hitCoord = (camDir * 100.0f) + camCoord;
			Pos = hitCoord.ToTypeStruct();
		}
	}


	if (loop_kaboom_gun && ped == PLAYER_PED_ID() && kaboom_gun_rand_bit)
		ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, GET_RANDOM_INT_IN_RANGE(0, 40), 5.0, 1, invisible, 0.5, false);
	else if (type < 70)
		ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, type, 5.0, 1, invisible, 0.5, false);
	else
	{
		Entity ent;
		//if ( IS_THIS_MODEL_A_CAR(type) || IS_THIS_MODEL_A_BOAT(type) || IS_THIS_MODEL_A_PLANE(type) || IS_THIS_MODEL_A_HELI(type) || IS_THIS_MODEL_A_TRAIN(type) || IS_THIS_MODEL_A_BIKE(type) || IS_THIS_MODEL_A_BICYCLE(type) || IS_THIS_MODEL_A_QUADBIKE(type) )
		if (IS_MODEL_A_VEHICLE(type))
			ent = CREATE_VEHICLE(type, Pos.x, Pos.y, Pos.z + 0.16f, GET_ENTITY_HEADING(ped), 1, 1, 0);
		else
			ent = CREATE_PED(PedType::Human, type, Pos.x, Pos.y, Pos.z + 0.16f, GET_ENTITY_HEADING(ped), 1, 1);

		SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
	}
}
void set_triggerfx_at_bullet_hit(Ped ped, const std::string& fxAsset, const std::string& fxName, const Vector3& Rot, float scale)
{
	Vector3_t Pos;
	if (!GET_PED_LAST_WEAPON_IMPACT_COORD(ped, &Pos) && ped == PLAYER_PED_ID())
	{
		const Vector3& camDir = GameplayCamera::Direction_get();
		const Vector3& camCoord = GameplayCamera::Position_get();
		Vector3 hitCoord = (camDir * 1000.0f) + camCoord;

		RaycastResult ray = RaycastResult::Raycast(camCoord, hitCoord, IntersectOptions::Everything);
		if (ray.DidHitAnything())
		{
			Pos = hitCoord.ToTypeStruct();
		}
		else
		{
			hitCoord = (camDir * 100.0f) + camCoord;
			Pos = hitCoord.ToTypeStruct();
		}
	}

	PTFX::trigger_ptfx_1(fxAsset, fxName, 0, Pos, Rot, scale);
}

// Spooner/ped
void set_become_ped(GTAped ped)
{
	GTAped oldPed = PLAYER_PED_ID();

	std::vector<s_Weapon_Components_Tint> weaponsBackup;
	oldPed.StoreWeaponsInArray(weaponsBackup);

	GTAvehicle vehicle(0);
	VehicleSeat currVehSeat;
	if (ped.IsInVehicle())
	{
		vehicle = ped.CurrentVehicle();
		currVehSeat = ped.CurrentVehicleSeat_get();
	}

	//float camHeadingRelative = GameplayCamera::RelativeHeading_get();
	float camPitchRelative = GameplayCamera::RelativePitch_get();

	if (ped.IsPlayer())
		return;

	ped.RequestControl();
	set_ped_invincible_off(oldPed.Handle());
	CHANGE_PLAYER_PED(PLAYER_ID(), ped.Handle(), true, true); //false,true?

	GameplayCamera::RelativeHeading_set(0.0f);
	GameplayCamera::RelativePitch_set(camPitchRelative);

	ped = PLAYER_PED_ID();

	if (vehicle.Exists())
	{
		vehicle.RequestControl();
		ped.SetIntoVehicle(vehicle, currVehSeat);
	}

	ped.GiveWeaponsFromArray(weaponsBackup);

	SET_PED_INFINITE_AMMO_CLIP(ped.Handle(), bit_infinite_ammo);

}

// Ped - proofs?
void set_ped_invincible_on(Ped ped)
{
	SET_ENTITY_INVINCIBLE(ped, 1);
	SET_PED_DIES_IN_WATER(ped, 0);
	SET_ENTITY_PROOFS(ped, 1, 0, 1, 1, 1, 1, 1, 1);
}
void set_ped_invincible_off(Ped ped)
{
	SET_ENTITY_INVINCIBLE(ped, 0);
	SET_PED_DIES_IN_WATER(ped, 1);
	SET_ENTITY_PROOFS(ped, 0, 0, 0, 0, 0, 0, 0, 0);
}
void set_ped_no_ragdoll_on(Ped ped)
{
	SET_PED_CAN_RAGDOLL(ped, 0);
	SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, 0);
}
void set_ped_no_ragdoll_off(Ped ped)
{
	SET_PED_CAN_RAGDOLL(ped, 1);
	SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, 1);
}
void set_ped_seatbelt_on(Ped ped)
{
	SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, 1); // state cantFollOff
	//SET_PED_CONFIG_FLAG(ped, 32, true);
	SET_PED_CONFIG_FLAG(ped, 32, false);
}
void set_ped_seatbelt_off(Ped ped)
{
	SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, 0); // state canFallOff
	SET_PED_CONFIG_FLAG(ped, 32, true);
}

// Misc - FreeCam
bool bit_noclip_already_invis, bit_noclip_already_collis, bit_noclip_show_help = true;
Camera g_cam_noClip;
void set_no_clip_off1()
{
	GTAentity myPed = PLAYER_PED_ID();
	GTAentity ent = IS_PED_IN_ANY_VEHICLE(myPed.Handle(), false) ? GET_VEHICLE_PED_IS_IN(myPed.Handle(), false) : myPed;

	ent.RequestControl();
	ent.SetVisible(!bit_noclip_already_invis);
	ent.IsCollisionEnabled_set(bit_noclip_already_collis);
	ent.FreezePosition(false);
	ENABLE_CONTROL_ACTION(2, INPUT_VEH_HORN, TRUE);
	ENABLE_CONTROL_ACTION(2, INPUT_LOOK_BEHIND, TRUE);
	ENABLE_CONTROL_ACTION(2, INPUT_VEH_LOOK_BEHIND, TRUE);
	ENABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON, TRUE);
	bit_noclip_show_help = true;
}
void set_no_clip_off2()
{
	auto& cam = g_cam_noClip;
	if (cam.Exists())
	{
		cam.SetActive(false);
		cam.Destroy();
		World::RenderingCamera_set(0);
	}
}
void set_no_clip()
{
	if (sub::Spooner::SpoonerMode::bEnabled)
		return;

	auto& cam = g_cam_noClip;
	GTAentity myPed = PLAYER_PED_ID();
	GTAplayer myPlayer = PLAYER_ID();
	GTAentity ent = IS_PED_IN_ANY_VEHICLE(myPed.Handle(), false) ? GET_VEHICLE_PED_IS_IN(myPed.Handle(), false) : myPed;

	if (ent.Exists())
	{
		if (Menu::bit_controller ? (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_X) && IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LS)) : IsKeyJustUp(bind_no_clip))
		{
			loop_no_clip_toggle = !loop_no_clip_toggle;
			if (!loop_no_clip_toggle)
			{
				set_no_clip_off1();
			}
			else
			{
				if (bit_noclip_show_help)
				{
					bit_noclip_show_help = false;
					if (Menu::bit_controller) Game::CustomHelpText::ShowTimedText(oss_ << "FreeCam:~n~~INPUT_MOVE_UD~ = " << Game::GetGXTEntry("ITEM_MOV_CAM")
						<< "~n~~INPUT_LOOK_LR~ = " << Game::GetGXTEntry("ITEM_MOVE") << "~n~~INPUT_FRONTEND_RT~/~INPUT_FRONTEND_LT~ = " << "Ascend/Descend" << "~n~~INPUT_FRONTEND_RB~ = " << "Hasten", 6000);
					else Game::CustomHelpText::ShowTimedText(oss_ << "FreeCam:~n~~INPUT_MOVE_UD~/~INPUT_MOVE_LR~ = " << Game::GetGXTEntry("ITEM_MOV_CAM")
						<< "~n~~INPUT_LOOK_LR~ = " << Game::GetGXTEntry("ITEM_MOVE") << "~n~~INPUT_PARACHUTE_BRAKE_RIGHT~/~INPUT_PARACHUTE_BRAKE_LEFT~ = " << "Ascend/Descend" << "~n~~INPUT_SPRINT~ = " << "Hasten", 6000);
					bit_noclip_show_help = false;
				}
				bit_noclip_already_invis = !ent.IsVisible();
				bit_noclip_already_collis = ent.IsCollisionEnabled_get();
				//if (IS_ENTITY_A_PED(tempEntity)) task_HandsUp(tempEntity);
			}
		}

		if (!loop_no_clip_toggle)
		{
			set_no_clip_off2();
			return;
		}

		DISABLE_CONTROL_ACTION(2, INPUT_VEH_HORN, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_LOOK_BEHIND, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_VEH_LOOK_BEHIND, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_SELECT_WEAPON, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_VEH_ACCELERATE, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_VEH_BRAKE, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, TRUE);

		const Vector3& entPos = ent.Position_get();
		const Vector3& camOffset = Vector3();//Vector3(0, -4.0f, 3.6f);

		if (!cam.Exists())
		{
			ent.RequestControl();
			cam = World::CreateCamera();
			cam.Position_set(GameplayCamera::Position_get());
			cam.Rotation_set(GameplayCamera::Rotation_get());
			cam.AttachTo(ent, camOffset);
			cam.FieldOfView_set(GameplayCamera::FieldOfView_get());
			cam.DepthOfFieldStrength_set(0.0f);
			World::RenderingCamera_set(cam);
		}

		ent.RequestControl();
		//ent.Position_set(cam.GetOffsetInWorldCoords(-camOffset));
		ent.FreezePosition(true);
		ent.IsCollisionEnabled_set(false);
		ent.SetVisible(false);
		myPed.SetVisible(false);

		Vector3 nextRot = cam.Rotation_get() - Vector3(GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_UD), 0, GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_LR)) * (Menu::bit_controller ? 2.5f : 11.0f);
		nextRot.y = 0.0f; // No roll
		ent.Rotation_set(Vector3(0, 0, nextRot.z));
		cam.Rotation_set(nextRot);
		if (!myPlayer.IsFreeAiming() && !myPlayer.IsTargetingAnything())
			SET_GAMEPLAY_CAM_RELATIVE_HEADING(0.0f);

		if (Menu::bit_controller)
		{
			DISABLE_CONTROL_ACTION(0, INPUT_VEH_HORN, TRUE);

			if (ent == myPed)
			{
				if (GET_PED_STEALTH_MOVEMENT(myPed.Handle()))
					SET_PED_STEALTH_MOVEMENT(myPed.Handle(), false, 0);
				if (GET_PED_COMBAT_MOVEMENT(myPed.Handle()))
					SET_PED_COMBAT_MOVEMENT(myPed.Handle(), 0);
			}
			float noclip_prec_level = IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_RB) ? 1.8f : 0.8f;
			Vector3 offset;
			offset.x = GET_CONTROL_NORMAL(0, INPUT_MOVE_LR) * noclip_prec_level;
			offset.y = -GET_CONTROL_NORMAL(0, INPUT_MOVE_UD) * noclip_prec_level;
			offset.z = (GET_DISABLED_CONTROL_NORMAL(2, INPUT_FRONTEND_RT) - GET_DISABLED_CONTROL_NORMAL(2, INPUT_FRONTEND_LT)) * noclip_prec_level;
			if (!offset.IsZero())
				ent.Position_set(cam.GetOffsetInWorldCoords(offset - camOffset));

			//if (Menu::currentsub == SUB::CLOSED)
			//{
			//	Menu::add_IB(INPUT_MOVE_UD, "ITEM_MOV_CAM");
			//	Menu::add_IB(INPUT_LOOK_LR, "ITEM_MOVE");
			//	Menu::add_IB(INPUT_FRONTEND_LT, "");
			//	Menu::add_IB(INPUT_FRONTEND_RT, "Ascend/Descend");
			//	Menu::add_IB(INPUT_FRONTEND_RB, "Hasten");
			//	//Menu::add_IB(INPUT_FRONTEND_RLEFT, "Visibility");
			//}
		}
		else
		{
			float noclip_prec_level = IS_DISABLED_CONTROL_PRESSED(0, INPUT_SPRINT) ? 1.77f : 0.35f;
			Vector3 offset;
			offset.x = GET_CONTROL_NORMAL(0, INPUT_MOVE_LR) * noclip_prec_level;
			offset.y = -GET_CONTROL_NORMAL(0, INPUT_MOVE_UD) * noclip_prec_level;
			offset.z = IS_DISABLED_CONTROL_PRESSED(2, INPUT_PARACHUTE_BRAKE_RIGHT) ? noclip_prec_level : IS_DISABLED_CONTROL_PRESSED(2, INPUT_PARACHUTE_BRAKE_LEFT) ? -noclip_prec_level : 0.0f;
			if (!offset.IsZero())
				ent.Position_set(cam.GetOffsetInWorldCoords(offset - camOffset));

			//if (Menu::currentsub == SUB::CLOSED)
			//{
			//	Menu::add_IB(INPUT_LOOK_LR, "ITEM_MOVE");
			//	Menu::add_IB(INPUT_SCRIPT_PAD_RIGHT, "");
			//	Menu::add_IB(INPUT_SCRIPT_PAD_DOWN, "");
			//	Menu::add_IB(INPUT_SCRIPT_PAD_LEFT, "");
			//	Menu::add_IB(INPUT_SCRIPT_PAD_UP, "ITEM_MOV_CAM");
			//	Menu::add_IB(INPUT_PARACHUTE_BRAKE_LEFT, "");
			//	Menu::add_IB(INPUT_PARACHUTE_BRAKE_RIGHT, "Ascend/Descend");
			//	Menu::add_IB(INPUT_SPRINT, "Hasten");
			//	//Menu::add_IB(-3, "Visibility - T");
			//}
		}
	}

}

// Playerped - ability
void set_local_button_super_run()
{
	auto ped = PLAYER_PED_ID();
	bool isInAir = IS_ENTITY_IN_AIR(ped) != 0;

	if (!isInAir)
	{
		if (IS_CONTROL_PRESSED(0, INPUT_SPRINT))
			APPLY_FORCE_TO_ENTITY(ped, 1, 0.0, 3.4, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);

		else if (IS_CONTROL_JUST_RELEASED(0, INPUT_SPRINT))
		{
			FREEZE_ENTITY_POSITION(ped, 1);
			FREEZE_ENTITY_POSITION(ped, 0);
		}
	}

}

// Playerped - ability
void set_self_refill_health_when_in_cover()
{
	if (GET_GAME_TIMER() >= Menu::delayedTimer - 100)
	{
		//SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER_ID(), 8);
		GTAped playerPed = PLAYER_PED_ID();
		auto health = playerPed.Health_get();
		auto maxHealth = playerPed.MaxHealth_get();
		if (playerPed.IsInCover() && !playerPed.IsAimingFromCover() && health < maxHealth)
		{
			playerPed.Health_set(health + 4);
		}
	}
}

// Game - HUD (Display coordinates)
void xyzh_drawfloat(float text, float x_coord, float y_coord)
{
	Game::Print::setupdraw(font_xyzh, Vector2(0.35f, 0.35f), false, false, true);
	Game::Print::drawfloat(text, 4, x_coord, y_coord);
}
void xyzh_()
{
	Vector3 Pos = GET_ENTITY_COORDS(PLAYER_PED_ID(), 1);

	Game::Print::setupdraw(font_xyzh, Vector2(0.35f, 0.36f), false, false, true);
	Game::Print::drawstring("Coords:", 0.90f, 0.066f);
	xyzh_drawfloat(Pos.x, 0.90f, 0.10f);
	xyzh_drawfloat(Pos.y, 0.90f, 0.13f);
	xyzh_drawfloat(Pos.z, 0.90f, 0.16f);
	xyzh_drawfloat(GET_ENTITY_HEADING(PLAYER_PED_ID()), 0.90f, 0.19f);
}

// Playerped - ability
void set_local_superman_MANUAL()
{
	if (IS_PAUSE_MENU_ACTIVE() || IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
		return;

	DISABLE_CONTROL_ACTION(2, INPUT_PARACHUTE_DEPLOY, TRUE);

	Ped playerPed = PLAYER_PED_ID();
	bool isInParaFreeFall = IS_PED_IN_PARACHUTE_FREE_FALL(playerPed) != 0;

	if (isInParaFreeFall)
	{
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RB) || get_key_pressed(VK_ADD))
		{
			APPLY_FORCE_TO_ENTITY(playerPed, 1, 0.0, 45.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
		}

		DISABLE_CONTROL_ACTION(2, INPUT_PARACHUTE_DEPLOY, TRUE);
		if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RDOWN) || get_key_pressed(VK_SUBTRACT))
		{
			FREEZE_ENTITY_POSITION(playerPed, true);
		}
		else if (IS_CONTROL_JUST_RELEASED(2, INPUT_FRONTEND_RDOWN) || IsKeyJustUp(VK_SUBTRACT))
		{
			FREEZE_ENTITY_POSITION(playerPed, false);
		}
	}

	if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RT) || IsKeyDown(VK_NUMPAD7))
	{
		if (!isInParaFreeFall) TASK_PARACHUTE(playerPed, true, false);
		APPLY_FORCE_TO_ENTITY(playerPed, 1, 0.0, 0.0, 13.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
	}

	if (IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LT) || IsKeyDown(VK_NUMPAD1))
	{
		if (!isInParaFreeFall) TASK_PARACHUTE(playerPed, true, false);
		APPLY_FORCE_TO_ENTITY(playerPed, 1, 0.0, 0.0, -13.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
	}

}
void set_ped_superman_AUTO(Ped ped)
{
	if (IS_PED_IN_PARACHUTE_FREE_FALL(ped))
	{
		if (!NETWORK_HAS_CONTROL_OF_ENTITY(ped))
			NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);

		APPLY_FORCE_TO_ENTITY(ped, 1, 0.0, 70.0f, 70.0f, 0.0, 0.0, 0.0, 0, 1, 0, 0, 0, 1);

		////WeaponS ptfx = { "scr_rcbarry2", "scr_clown_appears" };
		//WeaponS ptfx = { "scr_trevor1", "scr_trev1_trailer_boosh" };
		//if (!HAS_NAMED_PTFX_ASSET_LOADED(ptfx.label)) REQUEST_NAMED_PTFX_ASSET(ptfx.label);
		//else
		//{
		//	USE_PARTICLE_FX_ASSET(ptfx.label);
		//	//SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1));
		//	SET_PARTICLE_FX_NON_LOOPED_ALPHA(0.58f);
		//	START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(ptfx.name, ped, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, Bone::RightFoot, 0.015f, 0, 0, 0);
		//	USE_PARTICLE_FX_ASSET(ptfx.label);
		//	SET_PARTICLE_FX_NON_LOOPED_ALPHA(0.58f);
		//	START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(ptfx.name, ped, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, Bone::LeftFoot, 0.015f, 0, 0, 0);
		//}

		if (ped == PLAYER_PED_ID())
		{
			bool isBrakePressed, isBrakeReleased = false;
			if (Menu::bit_controller)
			{
				DISABLE_CONTROL_ACTION(2, INPUT_PARACHUTE_DEPLOY, TRUE);
				isBrakePressed = IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RDOWN) != 0;
				if (!isBrakePressed) isBrakeReleased = IS_CONTROL_JUST_RELEASED(2, INPUT_FRONTEND_RDOWN) != 0;
			}
			else
			{
				isBrakePressed = IsKeyDown(VK_ADD);
				if (!isBrakePressed) isBrakeReleased = IsKeyJustUp(VK_ADD);
			}
			if (isBrakePressed)//get_key_pressed(VK_ADD))
			{
				FREEZE_ENTITY_POSITION(ped, true);
			}
			else if (isBrakeReleased)
			{
				FREEZE_ENTITY_POSITION(ped, false);
			}
		}

	}
}

// Vehicle - ability
void set_vehicle_nos_ptfx_this_frame(GTAvehicle vehicle)
{
	WeaponS ptfx1 = { "scr_rcbarry1", "scr_alien_teleport" };
	if (!HAS_NAMED_PTFX_ASSET_LOADED(ptfx1.label.c_str()))
		REQUEST_NAMED_PTFX_ASSET(ptfx1.label.c_str());
	else
	{
		Vector3 dim1, dim2;
		vehicle.ModelDimensions(dim1, dim2);
		USE_PARTICLE_FX_ASSET(ptfx1.label.c_str());
		SET_PARTICLE_FX_NON_LOOPED_COLOUR(float(titlebox.R) / 255.0f, float(titlebox.G) / 255.0f, float(titlebox.B) / 255.0f);
		START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(ptfx1.name.c_str(), vehicle.Handle(), dim1.x - 0.2f, 0.4 - dim2.y, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0, 0, 0);
		USE_PARTICLE_FX_ASSET(ptfx1.label.c_str());
		SET_PARTICLE_FX_NON_LOOPED_COLOUR(float(titlebox.R) / 255.0f, float(titlebox.G) / 255.0f, float(titlebox.B) / 255.0f);
		START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(ptfx1.name.c_str(), vehicle.Handle(), 0.2f - dim2.x, 0.4 - dim2.y, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0, 0, 0);
	}

	PTFX::NonLoopedPTFX muzzleFlash("scr_carsteal4", "scr_carsteal5_car_muzzle_flash");
	if (!muzzleFlash.IsAssetLoaded())
		muzzleFlash.LoadAsset();
	else
	{
		//auto& otherWayRot = Vector3(vehicle.Pitch_get(), 0, vehicle.Heading_get() - 90.0f);
		const Vector3& otherWayRot = vehicle.Rotation_get() + Vector3(0, 0, -90.0f);
		for (auto& exh : { VBone::exhaust, VBone::exhaust_2 })
		{
			muzzleFlash.Start(vehicle.GetBoneCoords(vehicle.GetBoneIndex(exh)), 1.0f, otherWayRot);
		}
	}
}

// Vehicle - ability
void set_SuprKarMode_self()
{
	if (IS_VEHICLE_ON_ALL_WHEELS(g_myVeh))
	{
		if (IS_CONTROL_PRESSED(2, INPUT_VEH_ACCELERATE))
		{
			SET_VEHICLE_BOOST_ACTIVE(g_myVeh, 1);
			SET_VEHICLE_BOOST_ACTIVE(g_myVeh, 0);
			SET_VEHICLE_FORWARD_SPEED(g_myVeh, GET_ENTITY_SPEED_VECTOR(g_myVeh, true).y + 0.46f);
			//ANIMPOSTFX_PLAY("RaceTurbo", 0, 0);
			set_vehicle_nos_ptfx_this_frame(GTAvehicle(g_myVeh));
		}
		if (IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_BRAKE))
		{
			SET_VEHICLE_FORWARD_SPEED(g_myVeh, 0.0f);
		}
		else if (IS_CONTROL_PRESSED(2, INPUT_VEH_BRAKE))
		{
			APPLY_FORCE_TO_ENTITY(g_myVeh, 1, 0.0, -0.4, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
			//SET_VEHICLE_FORWARD_SPEED(g_myVeh, GET_ENTITY_SPEED(g_myVeh) - 0.46f);
			//ANIMPOSTFX_PLAY("FocusOut", 0, 0);
		}
	}
}
void set_local_car_jump()
{
	if (!IS_MP_TEXT_CHAT_TYPING())
	{
		Model& model = g_myVeh_model;

		if (model.IsPlane() || model.IsHeli())
			return;

		GTAvehicle vehicle = g_myVeh;
		bool bPressed;

		switch (loop_car_jump)
		{
		case 1: // Tap
			if (vehicle.Model().IsBicycle())
				bPressed = IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_JUMP);
			else
				bPressed = Menu::bit_controller ? IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RDOWN) : IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_HANDBRAKE);
			if (bPressed)
			{
				vehicle.ApplyForceCustom(Vector3(0, 0, 3.6f), Vector3(0, 1.2f, 0), ForceType::MaxForceRot, true, false, true, true, true, true);
				vehicle.ApplyForceCustom(Vector3(0, 0, 3.6f), Vector3(0, -1.0f, 0), ForceType::MaxForceRot, true, false, true, true, true, true);
			}
			break;
		case 2: // Hold
			if (vehicle.Model().IsBicycle())
				bPressed = IS_CONTROL_PRESSED(2, INPUT_VEH_JUMP);
			else
				bPressed = Menu::bit_controller ? IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RDOWN) : IS_CONTROL_PRESSED(2, INPUT_VEH_HANDBRAKE);
			if (bPressed)
			{
				vehicle.ApplyForceCustom(Vector3(0, 0, 0.6f), Vector3(0, 0.06f, 0), ForceType::MaxForceRot, true, false, true, true, true, true);
			}
			break;
		}
	}
}
void set_local_car_hydraulics()
{
	GTAvehicle vehicle = g_myVeh;

	if ((Menu::bit_controller ? IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_LS) : get_key_pressed(VirtualKey::LeftShift))
		&& vehicle.IsOnAllWheels())
	{
		Vector2 normal;

		if (Menu::bit_controller)
		{
			DISABLE_CONTROL_ACTION(2, INPUT_VEH_HORN, true);
			normal.x = GET_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_X);
			normal.y = GET_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_Y);
		}
		else
		{
			if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_RIGHT) || IsKeyDown('D'))
				normal.x = 1.0f;
			else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_LEFT) || IsKeyDown('A'))
				normal.x = -1.0f;
			else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_UP) || IsKeyDown('W'))
				normal.y = 1.0f;
			else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_DOWN) || IsKeyDown('S'))
				normal.y = -1.0f;
		}

		if (normal.x > 0.4f || normal.x < -0.4f)
		{
			vehicle.ApplyForceCustom(Vector3(0, 0, abs(normal.x) * 0.294f), Vector3((normal.x > 0 ? 1 : -1) * 0.98f, 0, 0), ForceType::MaxForceRot, true, true, true, true, false, true);
			//vehicle.ApplyForceRelative({0, 0, normal.x * 6.4f}, {normal.x * -6.4f, 0, 0}, 0);
		}
		if (normal.y > 0.4f || normal.y < -0.4f)
		{
			vehicle.ApplyForceCustom(Vector3(0, 0, abs(normal.y) * 0.164f), Vector3(0, (normal.y > 0 ? 1 : -1) * 3.05f, 0), ForceType::MaxForceRot, true, true, true, true, false, true);
			//vehicle.ApplyForceRelative({ 0, 0, normal.y * 36.0f }, { 0, 0, normal.y * -36.0f }, 0);
		}
	}
}
void set_local_forcefield()
{
	GTAentity myPed = PLAYER_PED_ID();
	const Vector3& myPos = myPed.Position_get();
	switch (loop_forcefield)
	{
	case 1: //push out
		for (GTAentity ent : _worldEntities)
		{
			if (ent.Handle() != myPed.Handle() && ent.Handle() != g_myVeh)
			{
				const Vector3& entPos = ent.Position_get();
				if (myPos.DistanceTo(entPos) < 10.0f)
				{
					ent.ApplyForce(entPos - myPos, ForceType::MaxForceRot2);
				}
			}
		}
		break;
	case 2://explode
		myPed.SetExplosionProof(true);
		World::AddExplosion(myPos, EXPLOSION::BLIMP, 5.0f, 0.0f, false, false);
		//set_explosion_at_coords(myPed, Vector3::Zero(), EXPLOSION::BLIMP, 5.0, 0.0f, 0, 1);
		break;
	}

	/*INT i, offsettedID;

	FLOAT h, myh = GET_ENTITY_HEADING(myPed);

	Ped *peds = new Ped[40 * 2 + 2];
	peds[0] = 40;
	INT found = GET_PED_NEARBY_PEDS(myPed, peds, -1);
	for (i = 0; i < found; i++)
	{
	offsettedID = i * 2 + 2;

	if (!DOES_ENTITY_EXIST(peds[offsettedID]))	continue;

	if (vdist(Pos, GET_ENTITY_COORDS(peds[offsettedID], 1)) > 7.2f) continue;
	NETWORK_REQUEST_CONTROL_OF_ENTITY(peds[offsettedID]);
	h = GET_ENTITY_HEADING(peds[offsettedID]);
	if (h < myh + 45 && h > myh - 45)
	APPLY_FORCE_TO_ENTITY(peds[offsettedID], 1, 0, 18, 0, 0, 0, -3, 1, 1, 1, 1, 0, 1);
	myh += 45;
	if (myh > 360) myh -= 360;
	if (h < myh + 45 && h > myh - 45)
	{
	SET_ENTITY_HEADING(peds[offsettedID], myh);
	APPLY_FORCE_TO_ENTITY(peds[offsettedID], 1, 0, 18, 0, 0, 0, -3, 1, 1, 1, 1, 0, 1);
	}


	}
	delete[] peds;

	Vehicle *vehicles = new Vehicle[40 * 2 + 2];
	vehicles[0] = 40;
	found = GET_PED_NEARBY_VEHICLES(myPed, vehicles);
	Int3 NeonRGB = { RandomRGB(), RandomRGB(), RandomRGB() };
	for (i = 0; i < found; i++)
	{
	offsettedID = i * 2 + 2;

	if (!DOES_ENTITY_EXIST(vehicles[offsettedID]))	continue;

	if (vdist(Pos, GET_ENTITY_COORDS(vehicles[offsettedID], 1)) > 7.2f) continue;
	NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicles[offsettedID]);
	h = GET_ENTITY_HEADING(vehicles[offsettedID]);
	if (h < myh + 45 && h > myh - 45)
	APPLY_FORCE_TO_ENTITY(vehicles[offsettedID], 1, 0, 70, 0, 0, 0, -3, 1, 1, 1, 1, 0, 1);
	myh += 45;
	if (myh > 360) myh -= 360;
	if (h < myh + 45 && h > myh - 45)
	{
	SET_ENTITY_HEADING(vehicles[offsettedID], myh);
	APPLY_FORCE_TO_ENTITY(vehicles[offsettedID], 1, 0, 70, 0, 0, 0, -3, 1, 1, 1, 1, 0, 1);
	}


	}
	delete[] vehicles;*/

}

// World - explosion
void set_explosion_wp(UINT8 mode)
{
	if (!IS_WAYPOINT_ACTIVE())
		return;

	float camshake = 0.0f;
	bool visible = true;

	switch (mode)
	{
	case 0: // off
		return;
		break;
	case 1: default: // visible + shaky
		camshake = 3.0f;
		break;
	case 2: // visible
		visible = true;
		break;
	case 3: // invisible
		visible = false;
		break;
	}

	Vector3 pos = GET_BLIP_INFO_ID_COORD(GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint));
	ADD_EXPLOSION(pos.x, pos.y, pos.z, 16, 36.0f, 1, !visible, camshake, false);
	GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, 600.0f, &pos.z, 0, 0);
	ADD_EXPLOSION(pos.x, pos.y, pos.z + 5.0f, 29, 36.0f, 1, !visible, camshake, false);
	ADD_EXPLOSION(pos.x, pos.y, pos.z + 20.0f, 29, 36.0f, 1, !visible, camshake, false);

}

// Vehicle - ability
float _global_MultiPlatNeons_Intensity = 3.5f;
void draw_vehicle_ambientlight_neons(const GTAvehicle& vehicle, const RgbS& colour)
{
	Vector3 dim1, dim2;
	vehicle.ModelDimensions(dim1, dim2);

	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 1.4f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 1.2f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 1.0f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 0.8f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 0.6f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 0.4f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 0.2f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, 0.0f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -0.2f, -0.3f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -0.4f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -0.6f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -0.8f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -1.0f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -1.2f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);
	//draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.0f, -1.4f, -0.4f)), 5.0f, _global_MultiPlatNeons_Intensity, colour);

	World::DrawLightWithRange(vehicle.GetOffsetInWorldCoords(0.0f, dim1.y - 0.3f, -0.4f), colour, 5.0f, _global_MultiPlatNeons_Intensity);
	World::DrawLightWithRange(vehicle.GetOffsetInWorldCoords(0.0f, 0.3f - dim2.y, -0.4f), colour, 5.0f, _global_MultiPlatNeons_Intensity);
	World::DrawLightWithRange(vehicle.GetOffsetInWorldCoords(dim1.x - 0.3f, 0.64f, -0.4f), colour, 5.0f, _global_MultiPlatNeons_Intensity);
	World::DrawLightWithRange(vehicle.GetOffsetInWorldCoords(0.3f - dim2.x, 0.64f, -0.4f), colour, 5.0f, _global_MultiPlatNeons_Intensity);




	/*draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, -1.4, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, -0.7, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, 0.0, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, 0.7, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, 1.4, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.24, 2.1, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);


	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), -1.4, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), -0.7, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), 0.0, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), 0.7, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), 1.4, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);
	draw_spot_light_pls(vehicle.GetOffsetInWorldCoords(Vector3(0-(dim2.x - 0.24), 2.1, 0.0)), vehicle.Rotation_get(), dim2.z - 0.4f, 70, 3, 9, 1.6, 0, colour);*/

	/*draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0, dim1.y - 0.2, -0.7)), 1.0, 2.5, colour);

	draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0, 0.2 - dim2.y, -0.7)), 1.0, 2.5, colour);

	draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.37, 1.5, -0.4)), 0.9, 2.5, colour);
	draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(dim1.x - 0.37, -1.5, -0.4)), 0.9, 2.5, colour);

	draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.37 - dim2.x, 1.5, -0.4)), 0.9, 2.5, colour);
	draw_light_ranged_pls(vehicle.GetOffsetInWorldCoords(Vector3(0.37 - dim2.x, -1.5, -0.4)), 0.9, 2.5, colour);*/

	//World::DrawLine(vehicle.GetOffsetInWorldCoords(dim1.x, 1.0, 0.1 - dim1.z), vehicle.GetOffsetInWorldCoords(dim1.x, -1.0, 0.1 - dim1.z), RGBA(colour.R, colour.G, colour.B, 230));
	//World::DrawLine(vehicle.GetOffsetInWorldCoords(-dim2.x, 1.0, 0.1 - dim1.z), vehicle.GetOffsetInWorldCoords(-dim2.x, -1.0, 0.1 - dim1.z), RGBA(colour.R, colour.G, colour.B, 230));

}
void set_multiplat_neons()
{
	bool already = false;
	auto& theList = _global_MultiPlatNeons_List;
	auto& colour = _global_MultiPlatNeons_Col;

	if (loop_multiplat_neons_rainbow) // rainbow loop
	{
		colour = g_fadedRGB;
	}

	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
	{
		for (auto& veh : theList)
		{
			if (veh.Equals(g_myVeh)) { already = true; break; }
		}
		if (!already)
			theList.push_back((g_myVeh));
		//theList.insert(g_myVeh);
	}

	for (auto it = theList.begin(); it != theList.end();)
	{
		if (!it->Exists() || it->IsDead())
		{
			it = theList.erase(it);
			continue;
		}
		draw_vehicle_ambientlight_neons(*it, _global_MultiPlatNeons_Col);
		++it;
	}

}

// Vehicle - ability
void drive_on_water(GTAped ped, Entity& waterobject)
{
	if (ped.IsInVehicle())
		ped = ped.CurrentVehicle();

	if (!DOES_ENTITY_EXIST(waterobject))
	{
		Model objModel = 0xC42C019A; // prop_ld_ferris_wheel
		objModel.LoadAndWait();
		const Vector3& Pos = ped.GetOffsetInWorldCoords(0, 4.0f, 0);
		float whh = 0.0f;
		if (GET_WATER_HEIGHT_NO_WAVES(Pos.x, Pos.y, Pos.z, &whh))
		{
			ped.RequestControl();
			SET_ENTITY_COORDS(ped.Handle(), Pos.x, Pos.y, whh, 0, 0, 0, 1);
		}
		waterobject = CREATE_OBJECT(objModel.hash, Pos.x, Pos.y, whh - 4.0f, 1, 1, 1);
		SET_NETWORK_ID_CAN_MIGRATE(OBJ_TO_NET(waterobject), ped != PLAYER_PED_ID());
		SET_ENTITY_COORDS_NO_OFFSET(waterobject, Pos.x, Pos.y, whh, 0, 0, 0);
		SET_ENTITY_ROTATION(waterobject, 0, 90, 0, 2, 1);
		FREEZE_ENTITY_POSITION(waterobject, true);
		Game::Print::PrintBottomCentre("~b~Note:~s~ Enable again if water level is incorrect/changes.");
		WAIT(65);
		return;
	}

	const Vector3& myPos = ped.Position_get();
	const Vector3& Pos = GET_ENTITY_COORDS(waterobject, 1);

	if (ped.IsInWater())
	{
		float whh = 0.0f;
		if (GET_WATER_HEIGHT_NO_WAVES(Pos.x, Pos.y, Pos.z, &whh))
		{
			SET_ENTITY_COORDS_NO_OFFSET(waterobject, Pos.x, Pos.y, whh, 0, 0, 0);
		}
	}

	//if (!IS_ENTITY_IN_WATER(tempEntity)) return;
	//GET_WATER_HEIGHT(myPos.x, myPos.y, myPos.z, &Pos.z);

	if (!NETWORK_HAS_CONTROL_OF_ENTITY(waterobject))
		NETWORK_REQUEST_CONTROL_OF_ENTITY(waterobject);
	SET_ENTITY_COORDS_NO_OFFSET(waterobject, myPos.x, myPos.y, Pos.z, 1, 1, 1);
	SET_ENTITY_ROTATION(waterobject, 180.0f, 90.0f, 180.0f, 2, 1);
	SET_ENTITY_VISIBLE(waterobject, false, false);
	FREEZE_ENTITY_POSITION(waterobject, true);


}

// Playerped - ability
void set_ped_burn_mode(GTAped ped, bool enable)
{
	auto isOnFire = ped.IsOnFire();

	if (enable && !isOnFire && !ped.IsInWater())
	{
		ped.SetOnFire(enable);
	}
	else if (!enable && isOnFire)
	{
		ped.SetOnFire(enable);
	}

}

// Vehicle - ability - multiplier
inline void set_Handling_Mult69_7()
{
	if (mult69_7 == 0)
		return;
	if (!Menu::bit_controller)
	{
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_RIGHT) || IsKeyDown('D'))
			APPLY_FORCE_TO_ENTITY(g_myVeh, 1, mult69_7 / 220, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_PAD_LEFT) || IsKeyDown('A'))
			APPLY_FORCE_TO_ENTITY(g_myVeh, 1, (0 - mult69_7) / 220, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
	}
	else
	{
		FLOAT handling_mult69_7_control_normal = GET_DISABLED_CONTROL_NORMAL(2, INPUT_SCRIPT_LEFT_AXIS_X);
		if (handling_mult69_7_control_normal > 0.5f || handling_mult69_7_control_normal < -0.5f)
			APPLY_FORCE_TO_ENTITY(g_myVeh, 1, (mult69_7 * handling_mult69_7_control_normal) / 220, 0.0, 0.0, 0.0, 0.0f, 0.0, 0, 1, 1, 1, 0, 1);
	}
}

// Vehicle - ability - invincibility
void set_vehicle_invincible_on(Vehicle vehicle)
{
	SET_VEHICLE_CAN_BREAK(vehicle, 0);
	SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, 0);
	SET_VEHICLE_TYRES_CAN_BURST(vehicle, 0);
	SET_ENTITY_CAN_BE_DAMAGED(vehicle, 0);
	SET_ENTITY_INVINCIBLE(vehicle, 1);
	SET_ENTITY_PROOFS(vehicle, 1, 0, 1, 1, 1, 1, 1, 1);
	//SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(vehicle, 0);
}
void set_vehicle_invincible_off(Vehicle vehicle)
{
	SET_VEHICLE_CAN_BREAK(vehicle, 1);
	SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, 1);
	SET_ENTITY_CAN_BE_DAMAGED(vehicle, 1);
	SET_ENTITY_INVINCIBLE(vehicle, 0);
	SET_ENTITY_PROOFS(vehicle, 0, 0, 0, 0, 0, 0, 0, 0);
	SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(vehicle, 0);
}

// Vehicle - ability
void set_vehicle_fliploop(GTAvehicle vehicle)
{
	// if(!DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(vehicle))
	//		ADD_VEHICLE_UPSIDEDOWN_CHECK(vehicle);
	// else if(IS_VEHICLE_STUCK_ON_ROOF(vehicle))
	//		SET_ENTITY_HEADING(vehicle, GET_ENTITY_HEADING(vehicle) + 0.1f);

	FLOAT roll = GET_ENTITY_ROLL(vehicle.Handle());
	if (vehicle.IsUpsideDown() && (roll > 160 || roll < -160))
	{
		const Model& model = vehicle.Model();
		if (!vehicle.IsInAir() && !vehicle.IsInWater() && !model.IsPlane() && !model.IsHeli())
		{
			vehicle.RequestControlOnce();
			vehicle.Rotation_set(Vector3(0, 0, vehicle.Rotation_get().z));
			//vehicle.Heading_set(vehicle.Heading_get() + 0.1f);
		}
	}
}

// Vehicle - ability
void set_vehicle_rainbow_mode_tick(GTAvehicle vehicle, bool useFader)
{
	vehicle.RequestControlOnce();
	if (useFader)
	{
		vehicle.CustomPrimaryColour_set(g_fadedRGB);
		vehicle.CustomSecondaryColour_set(g_fadedRGB);
	}
	else
	{
		if (vehicle.IsPrimaryColorCustom())
			vehicle.ClearCustomPrimaryColour();
		if (vehicle.IsSecondaryColorCustom())
			vehicle.ClearCustomSecondaryColour();
		vehicle.PrimaryColour_set(rand() % 160);
		vehicle.SecondaryColour_set(rand() % 160);
	}
}
void set_vehicle_heavy_mass_tick(GTAvehicle vehicle)
{
	if (!vehicle.Exists())
		return;

	float speed = vehicle.Speed_get();
	if (speed < 0.5f)
		return;

	vehicle.RequestControlOnce();

	set_vehicle_invincible_on(vehicle.Handle());
	vehicle.Repair(true); // Only if it needs a repair obv
	vehicle.SetFrictionOverride(100.0f);
	if (!vehicle.IsSeatFree(VehicleSeat::SEAT_DRIVER))
		set_ped_seatbelt_on(vehicle.GetPedOnSeat(VehicleSeat::SEAT_DRIVER).Handle());

	float pushForce = speed * 3.5f; // More speed === More bleed

	auto& vehicleArray = vehicle == g_myVeh ? _nearbyVehicles : _worldVehicles;

	for (auto& veh : vehicleArray)
	{
		if (vehicle != veh && vehicle.IsTouching(veh))
		{
			GTAvehicle(veh).ApplyForce(vehicle.CollisionNormal() * pushForce);
			vehicle.SetForwardSpeed(speed);
		}
	}

}

// Vehicle weapons
Vector3 vehicle_weapons_originR, vehicle_weapons_targetR;
Vector3 vehicle_weapons_originL, vehicle_weapons_targetL;
void store_vehicle_weapon_pos(const GTAentity& vehicle)
{
	Vector3_t dim1, dim2;
	vehicle.Model().Dimensions(dim1, dim2);

	if (IS_DISABLED_CONTROL_PRESSED(0, INPUT_LOOK_BEHIND))// || IS_GAMEPLAY_CAM_LOOKING_BEHIND()) // RS
	{
		vehicle_weapons_originR = vehicle.GetOffsetInWorldCoords(dim1.x - 0.22f, 0.5f - dim2.y, 0.5f);
		vehicle_weapons_targetR = vehicle.GetOffsetInWorldCoords(dim1.x - 0.22f, -(dim1.y + 350.0f), 0.5f);

		vehicle_weapons_originL = vehicle.GetOffsetInWorldCoords(0.22f - dim2.x, 0.5f - dim2.y, 0.5f);
		vehicle_weapons_targetL = vehicle.GetOffsetInWorldCoords(0.22f - dim2.x, -(dim2.y + 350.0f), 0.5f);
	}
	else
	{
		vehicle_weapons_originR = vehicle.GetOffsetInWorldCoords(dim1.x - 0.22f, dim1.y - 0.5f, 0.5f);
		vehicle_weapons_targetR = vehicle.GetOffsetInWorldCoords(dim1.x - 0.22f, dim1.y + 350.0f, 0.5f);

		vehicle_weapons_originL = vehicle.GetOffsetInWorldCoords(0.22f - dim2.x, dim1.y - 0.5f, 0.5f);
		vehicle_weapons_targetL = vehicle.GetOffsetInWorldCoords(0.22f - dim2.x, dim1.y + 350.0f, 0.5f);
	}
}
void set_vehicle_weapon_fire(Hash whash, float speed = 2000.0f)
{
	const auto& owner = Game::PlayerPed();

	World::ShootBullet(vehicle_weapons_originR, vehicle_weapons_targetR, owner, whash, 200, speed, true, true);
	World::ShootBullet(vehicle_weapons_originL, vehicle_weapons_targetL, owner, whash, 200, speed, true, true);
	//BOOL p7 = 0 or 1?
}
void set_vehicle_weapon_explosion(const EXPLOSION::EXPLOSION& type)
{
	Vector3 targPosR, targPosL;

	GTAvehicle vehicle(g_myVeh);

	if (IS_DISABLED_CONTROL_PRESSED(0, INPUT_LOOK_BEHIND))// || IS_GAMEPLAY_CAM_LOOKING_BEHIND()) // RS
	{
		targPosR = vehicle.GetOffsetInWorldCoords(1.24f, -40.0f, 0.0f);
		targPosL = vehicle.GetOffsetInWorldCoords(-1.24f, -40.0f, 0.0f);

	}
	else
	{
		targPosR = vehicle.GetOffsetInWorldCoords(1.24f, 40.0f, 0.0f);
		targPosL = vehicle.GetOffsetInWorldCoords(-1.24f, 40.0f, 0.0f);
	}

	World::AddExplosion(targPosR, type, 5.0f, 0.3f, true, true);
	World::AddExplosion(targPosL, type, 5.0f, 0.3f, true, true);
}
void set_vehicle_weapon_lines()
{
	World::DrawLine(vehicle_weapons_originR, vehicle_weapons_targetR, RGBA(titlebox.R, titlebox.G, titlebox.B, 255));
	World::DrawLine(vehicle_weapons_originL, vehicle_weapons_targetL, RGBA(titlebox.R, titlebox.G, titlebox.B, 255));
}
void set_vehicle_weapons()
{
	// Store bullet coordinates
	store_vehicle_weapon_pos(g_myVeh);

	// Vehicle weapons - lines
	if (loop_vehweap_lines)
		set_vehicle_weapon_lines();

	// Left stick / numplus press
	if (Menu::bit_controller ? IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LS) : IsKeyDown(VirtualKey::Add))
	{
		if (loop_vehicle_RPG
			|| loop_vehicle_fireworks
			|| loop_vehicle_guns
			|| loop_vehicle_snowballs
			|| loop_vehicle_balls
			|| loop_vehicle_waterhyd
			|| loop_vehicle_flameleak
			|| loop_vehicle_laser_green
			|| loop_vehicle_laser_red
			|| loop_vehicle_turrets_valkyrie
			|| loop_vehicle_flaregun
			|| loop_vehicle_heavysnip
			|| loop_vehicle_tazerweap
			|| loop_vehicle_molotovweap
			|| loop_vehicle_combatpdw)
			CLEAR_AREA_OF_PROJECTILES(vehicle_weapons_originR.x, vehicle_weapons_originR.y, vehicle_weapons_originR.z, 8.0f, 0);

		// RPG
		if (loop_vehicle_RPG)
			set_vehicle_weapon_fire(WEAPON_VEHICLE_ROCKET);

		// Fireworks
		if (loop_vehicle_fireworks)
			set_vehicle_weapon_fire(WEAPON_FIREWORK);

		// Guns
		if (loop_vehicle_guns)
			set_vehicle_weapon_fire(WEAPON_ASSAULTRIFLE);

		// Snowballs
		if (loop_vehicle_snowballs)
			set_vehicle_weapon_fire(WEAPON_SNOWBALL, 2970.0f);

		// Balls
		if (loop_vehicle_balls)
			set_vehicle_weapon_fire(WEAPON_BALL, 2970.0f);

		// Water hydrant explosions
		if (loop_vehicle_waterhyd)
			set_vehicle_weapon_explosion(EXPLOSION::DIR_WATER_HYDRANT);

		// Flame Explosions
		if (loop_vehicle_flameleak)
			set_vehicle_weapon_explosion(EXPLOSION::DIR_FLAME_EXPLODE);

		// Green laser
		if (loop_vehicle_laser_green)
			set_vehicle_weapon_fire(VEHICLE_WEAPON_PLAYER_LASER);

		// Red laser
		if (loop_vehicle_laser_red)
			set_vehicle_weapon_fire(VEHICLE_WEAPON_ENEMY_LASER);

		// Valkyrie turrets
		if (loop_vehicle_turrets_valkyrie) set_vehicle_weapon_fire(VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE);

		// Flare gun/flare
		if (loop_vehicle_flaregun)
			set_vehicle_weapon_fire(WEAPON_FLARE, 2970.0f);

		// Heavy sniper
		if (loop_vehicle_heavysnip)
			set_vehicle_weapon_fire(WEAPON_HEAVYSNIPER);

		// Tazer
		if (loop_vehicle_tazerweap)
			set_vehicle_weapon_fire(WEAPON_STUNGUN, 2970.0f);

		// Molotov
		if (loop_vehicle_molotovweap)
			set_vehicle_weapon_fire(WEAPON_MOLOTOV, 2970.0f);

		// Combat pdw
		if (loop_vehicle_combatpdw)
			set_vehicle_weapon_fire(WEAPON_COMBATPDW);

	}

}

// Vehicle - ability - boost
void set_self_vehicle_boost()
{
	//if (!IS_PLAYER_PRESSING_HORN(pIndex)) return;

	GTAvehicle vehicle(g_myVeh);

	if (!vehicle.Exists())
		return;

	vehicle.RequestControlOnce();

	SET_VEHICLE_BOOST_ACTIVE(vehicle.Handle(), true);
	APPLY_FORCE_TO_ENTITY(vehicle.Handle(), 1, 0.0f, 1.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
	SET_VEHICLE_BOOST_ACTIVE(vehicle.Handle(), false);

	set_vehicle_nos_ptfx_this_frame(vehicle);
}
// Vehicle - ability - native boost
inline void set_self_vehicle_nativeboost()
{
	//if (loop_unlimVehBoost)
	{
		const GTAentity& myPed = Game::PlayerPed();
		if (IS_PED_SITTING_IN_ANY_VEHICLE(myPed.GetHandle()) && DOES_ENTITY_EXIST(g_myVeh) && GET_HAS_ROCKET_BOOST(g_myVeh))
		{
			//LOG_PRINT("boostCharge %.4f", *boostCharge);
			if (IS_CONTROL_PRESSED(2, INPUT_VEH_HORN)) //_IS_VEHICLE_ROCKET_BOOST_ACTIVE(g_myVeh))
			{
				float* boostCharge = GeneralGlobalHax::GetVehicleBoostChargePtr();
				if (boostCharge != nullptr)
					*boostCharge = 1.24f; // 2.5f full 1.25f full after b944
				GeneralGlobalHax::SetVehicleBoostState(1);
				//_SET_VEHICLE_ROCKET_BOOST_ACTIVE(g_myVeh, true);
			}
			else
			{
				float* boostCharge = GeneralGlobalHax::GetVehicleBoostChargePtr();
				if (boostCharge != nullptr)
					*boostCharge = 1.24f;
				GeneralGlobalHax::SetVehicleBoostState(0);
				//_SET_VEHICLE_ROCKET_BOOST_ACTIVE(g_myVeh, false);
			}
		}
	}
}

// Vehicle - ability (personal vehicle)
GTAvehicle PV_sub_vehicleid;
void set_PVops_vehicle_text_world2Screen()
{
	if (PV_sub_vehicleid.Exists())
	{
		GTAblip carblip = PV_sub_vehicleid.CurrentBlip();

		GTAped playerPed = PLAYER_PED_ID();

		if (IS_PED_SITTING_IN_VEHICLE(playerPed.Handle(), PV_sub_vehicleid.Handle()))
		{
			if (carblip.Exists())
				carblip.SetAlpha(0);
			return;
		}

		if (carblip.Exists())
			carblip.SetAlpha(255);

		const Vector3& carpos = PV_sub_vehicleid.Position_get();

		if (carpos.DistanceTo(playerPed.Position_get()) < 40.0f)
		{
			Vector2 newScreenPos;
			if (GET_SCREEN_COORD_FROM_WORLD_COORD(carpos.x, carpos.y, carpos.z, &newScreenPos.x, &newScreenPos.y))
			{
				Game::Print::setupdraw(GTAfont::Impact, Vector2(0.64f, 0.64f), true, false, false);
				Game::Print::drawstring(PV_sub_vehicleid.Model().VehicleDisplayName(true) + " - PV", newScreenPos.x, newScreenPos.y);
			}
		}
	}
}

// Vehicle - ability (multiplier on tick)
std::map<Vehicle, float> g_multList_rpm;
std::map<Vehicle, float> g_multList_torque;
std::map<Vehicle, float> g_multList_maxSpeed;
std::map<Vehicle, float> g_multList_headlights;
inline void vehicle_torque_mult_tick()
{
	for (auto it = g_multList_torque.begin(); it != g_multList_torque.end();)
	{
		if (DOES_ENTITY_EXIST(it->first))
		{
			SET_VEHICLE_CHEAT_POWER_INCREASE(it->first, it->second);
			++it;
		}
		else
		{
			it = g_multList_torque.erase(it);
		}
	}
}
inline void vehicle_maxSpeed_mult_tick()
{
	for (auto it = g_multList_maxSpeed.begin(); it != g_multList_maxSpeed.end();)
	{
		if (DOES_ENTITY_EXIST(it->first))
		{
			SET_ENTITY_MAX_SPEED(it->first, it->second);
			++it;
		}
		else
		{
			it = g_multList_maxSpeed.erase(it);
		}
	}
}
// Vehicle - getter/setter - engine sound
std::map<Vehicle, std::string> g_vehList_engSound;
std::string get_vehicle_engine_sound_name(const GTAvehicle& vehicle)
{
	auto it = g_vehList_engSound.find(vehicle.GetHandle());
	if (it != g_vehList_engSound.end())
	{
		return it->second;
	}
	else
		return std::string();
}
void set_vehicle_engine_sound_name(GTAvehicle vehicle, const std::string& name)
{
	g_vehList_engSound[vehicle.GetHandle()] = name;
	vehicle.EngineSound_set(name);
}
// Vehicle - getter/setter - removeTyres
std::unordered_set<Vehicle> g_vehWheelsInvisForRussian;
bool are_vehicle_wheels_invisible(const GTAvehicle& vehicle)
{
	return (g_vehWheelsInvisForRussian.find(vehicle.GetHandle()) != g_vehWheelsInvisForRussian.end());
}
void set_vehicle_wheels_invisible(GTAvehicle vehicle, bool enable)
{
	if (enable)
	{
		if (g_vehWheelsInvisForRussian.find(vehicle.Handle()) == g_vehWheelsInvisForRussian.end())
			g_vehWheelsInvisForRussian.insert(vehicle.Handle());

		vehicle.RequestControl(800);
		vehicle.SetForwardSpeed(DBL_MAX*DBL_MAX);
		WAIT(100);
		SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), DBL_MAX*DBL_MAX);
		MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), DBL_MAX*DBL_MAX);
		vehicle.ApplyForceRelative(Vector3(0, 0, -DBL_MAX*DBL_MAX));
		WAIT(100);
		if (g_multList_rpm.count(vehicle.Handle()))
		{
			MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), g_multList_rpm[vehicle.Handle()]);
		}
		else
		{
			MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), 1.0f);
		}
		if (g_multList_torque.count(vehicle.Handle()))
		{
			SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), g_multList_torque[vehicle.Handle()]);
		}
		else
		{
			SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), 1.0f);
		}
	}
	else
	{
		if (g_vehWheelsInvisForRussian.find(vehicle.Handle()) != g_vehWheelsInvisForRussian.end())
			g_vehWheelsInvisForRussian.erase(vehicle.Handle());

		vehicle.RequestControl(800);
		for (UINT i = 0; i <= 8; i++)
			vehicle.FixTyre(i);
		vehicle.Repair(false);

		SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), 0.0f);
		MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), 0.0f);
		WAIT(100);
		if (g_multList_rpm.count(vehicle.Handle()))
		{
			MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), g_multList_rpm[vehicle.Handle()]);
		}
		else
		{
			MODIFY_VEHICLE_TOP_SPEED(vehicle.Handle(), 1.0f);
		}
		if (g_multList_torque.count(vehicle.Handle()))
		{
			SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), g_multList_torque[vehicle.Handle()]);
		}
		else
		{
			SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle.Handle(), 1.0f);
		}
	}
}

// Ped - ability (multiplier lists)
std::map<Ped, std::string> g_pedList_movGrp;
std::map<Ped, std::string> g_pedList_wmovGrp;
// Spooner/ped - facial mood - getter/setter
std::map<Ped, std::string> g_pedList_facialMood;
std::string get_ped_facial_mood(GTAentity ped)
{
	auto it = g_pedList_facialMood.find(ped.Handle());
	if (it == g_pedList_facialMood.end())
		return std::string();
	else return it->second;
}
void set_ped_facial_mood(GTAentity ped, const std::string& animName)
{
	//ped.RequestControl();
	auto& m = g_pedList_facialMood[ped.Handle()];
	m = animName;
	SET_FACIAL_IDLE_ANIM_OVERRIDE(ped.Handle(), animName.c_str(), 0);
}
void clear_ped_facial_mood(GTAentity ped)
{
	//ped.RequestControl();
	auto it = g_pedList_facialMood.find(ped.Handle());
	if (it != g_pedList_facialMood.end())
		g_pedList_facialMood.erase(it);
	CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(ped.Handle());
}

void Set_Walkunderwater(Entity PlayerPed)
{
	if (IS_ENTITY_IN_WATER(PlayerPed))
	{
		SET_PED_CONFIG_FLAG(PlayerPed, 65, false);
		SET_PED_CONFIG_FLAG(PlayerPed, 66, false);
		SET_PED_CONFIG_FLAG(PlayerPed, 168, false);
		
		Vector3 PlayerPos = GET_ENTITY_COORDS(PlayerPed, 0);
		DRAW_LIGHT_WITH_RANGEEX(PlayerPos.x, PlayerPos.y, (PlayerPos.z + 1.5f), 255, 255, 251, 100.0f, 1.5f, 0.0f);
		DRAW_LIGHT_WITH_RANGEEX(PlayerPos.x, PlayerPos.y, (PlayerPos.z + 50.0f), 255, 255, 251, 200.0f, 1.0f, 0.0f);

		if (IS_PED_JUMPING(PlayerPed)) // small pushup so jump feel more natural ( like when not underwater )
		{
			APPLY_FORCE_TO_ENTITY(PlayerPed, true, 0, 0, 0.7f, 0, 0, 0, true, true, true, true, false, true);
		}

		if (GET_ENTITY_HEIGHT_ABOVE_GROUND(PlayerPed) > 1) //Do falling down
		{
			SET_PED_CONFIG_FLAG(PlayerPed, 60, false);
			SET_PED_CONFIG_FLAG(PlayerPed, 61, false);
			SET_PED_CONFIG_FLAG(PlayerPed, 104, false);
			SET_PED_CONFIG_FLAG(PlayerPed, 276, false);
			SET_PED_CONFIG_FLAG(PlayerPed, 76, true);
			APPLY_FORCE_TO_ENTITY(PlayerPed, true, 0, 0, -0.7f, 0, 0, 0, true, true, true, true, false, true);
		}

		if (GET_IS_TASK_ACTIVE(PlayerPed, 281)|| IS_PED_SWIMMING(PlayerPed) || IS_PED_SWIMMING_UNDER_WATER(PlayerPed)) // Stop Swimming
		{
			CLEAR_PED_TASKS_IMMEDIATELY(PlayerPed);
		}
	}
}

std::array<int, 3> gethsvfromrgb(int r, int g, int b)
{
	std::array<int, 3> hsv;
	//setup
	float R = (r / 255.0f),
		G = (g / 255.0f),
		B = (b / 255.0f),
		M = max(R, max(G, B)),
		m = min(R, min(G, B)),
		C = M - m;
	int H = 0,
		S = 0;
	//Hue
	if (C != 0)
	{
		if (M == R)
		{
			H = 60 * ((G - B) / C);
		}
		else if (M == G)
		{
			H = 60 * (((B - R) / C) + 2);
		}
		else if (M == B)
		{
			H = 60 * (((R - G) / C) + 4);
		}
		H %= 360;
		if (H < 0)
			H += 360;
	}
	//Saturation
	if (M != 0)
		S = static_cast<int>((C / M) * 100);

	hsv[0] = H;
	hsv[1] = S;
	hsv[2] = static_cast<int>(M * 100);

	return hsv;
}

void gethsvfromrgb(RgbS colour)
{
	int r, g, b;
	r = colour.R;
	g = colour.G;
	b = colour.B;;
	gethsvfromrgb(r, g, b);
}

float normalisehsv(int h, int s, int v)
{
	float normalout = sqrt(pow(h, 2) + pow(s, 2) + pow(v / 2, 2));
	return normalout;
}

#pragma endregion

void Menu::loops()
{
	//_programTick = GetTickCount() - _initialProgramTick;
	//_programTick++; if (_programTick == MAXDWORD) _programTick == 0;
	//_programTick++; //if(_programTick > MAXDWORD) _programTick = 0;
	bool gameIsPaused = IS_PAUSE_MENU_ACTIVE() != 0;
	int iped, player;
	GTAplayer player2;

	Game::CustomHelpText::Tick();

	update_nearby_stuff_arrays_tick();

	if (gameIsPaused)
		SetPauseMenuTeleToWpCommand();

	sub::Spooner::SpoonerMode::Tick();

	sub::GhostRiderMode_catind::Tick();//sub::GhostRiderMode_catind::g_ghostRiderMode.Tick();
	sub::VehicleAutoDrive_catind::Tick();//sub::VehicleAutoDrive_catind::Methods.Tick();
	sub::GravityGun_catind::Tick();//sub::GravityGun_catind::g_gravityGun.Tick();
	_MagnetGun_::g_magnetGun.Tick();
	_SpSnow.Tick();
	_VehicleTow_::g_vehicleTow.Tick();
	_VehicleCruise_::g_vehicleCruise.Tick();
	_VehicleFly_::g_vehicleFly.Tick();
	sub::WaterHack_catind::Tick();//sub::WaterHack_catind::g_waterHack.Tick();
	sub::LaserSight_catind::Tick();
	_MeteorShower_::g_meteorShower.Tick();
	_SmashAbility_::g_smashAbility.Tick();
	_RopeGun_::g_ropeGun.Tick();
	sub::AnimalRiding_catind::Tick();//sub::AnimalRiding_catind::g_animalRidingMode.Tick();
	_Gta2Cam_::g_gta2Cam.Tick();

	set_Ptfxlop_tick();

	MenuInput::UpdateDeltaCursorNormal();

	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0)) // Store current vehicle
	{
		g_myVeh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), false); //GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
		g_myVeh_model = GET_ENTITY_MODEL(g_myVeh);
	}
	else
	{
		g_myVeh = 0;
	}

	if (!IS_PLAYER_DEAD(PLAYER_ID()))
	{
		GET_CURRENT_PED_WEAPON(PLAYER_PED_ID(), &g_myWeap, 1); // Breaks with /o2 optimisation
	}

	if (loop_RainbowBoxes /* && GET_GAME_TIMER() >= delayedTimer*/)
	{
		//Menu::gradients = false;
		titlebox = { g_fadedRGB.R, g_fadedRGB.G, g_fadedRGB.B, titlebox.A };
		//GET_HUD_COLOUR(GET_RANDOM_INT_IN_RANGE(0, 180), &titlebox.R, &titlebox.G, &titlebox.B, &inull);
		//selectionhi = titlebox;
		//iped = selectedtext.A; selectedtext = InverseRGB(selectionhi.R, selectionhi.G, selectionhi.B); selectedtext.A = iped;

		//GET_HUD_COLOUR(GET_RANDOM_INT_IN_RANGE(0, 180), &BG.R, &BG.G, &BG.B, &inull);
		//selectedtext.R = RandomRGB(); selectedtext.G = RandomRGB(); selectedtext.B = RandomRGB();
	}

	if (loop_Check_self_death_model)
		_ManualRespawn_::Check_self_death_model();

	if (loop_restricted_areas_access)
	{
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_doors");
	}

	if (!IS_PLAYER_SWITCH_IN_PROGRESS())
	{
		if (loop_pause_clock)
			NETWORK_OVERRIDE_CLOCK_TIME(pause_clock_H, pause_clock_M, 0);
		if (loop_sync_clock)
			set_sync_clock_time();
		if (sub::Clock_catind::loop_clock)
			sub::Clock_catind::DisplayClock();

		if (loop_hide_hud)
			HIDE_HUD_AND_RADAR_THIS_FRAME();
		if (loop_showFullHud)
			display_full_hud_this_frame(true);

		if (loop_massacre_mode)
			set_massacre_mode_tick();
		if (loop_blackout_mode)
			set_blackoutEmp_mode();
		if (loop_simple_blackout_mode)
			set_blackout_mode();
		if (_JumpAroundMode_::bEnabled)
			_JumpAroundMode_::Tick();
	}
	
	if (loop_player_Walkunderwater)
		Set_Walkunderwater(PLAYER_PED_ID());

	if (GET_GAME_TIMER() >= delayedTimer)
	{
		player = PLAYER_ID();
		player2.Handle() = (player);
		iped = PLAYER_PED_ID();

		// Ignored by everyone
		if (loop_ignored_by_everyone)
		{
			network_set_everyone_ignore_player(player);
			set_self_nearby_peds_calm();
		}
		// Freeze wanted level
		if (loop_self_freezeWantedLevel)
		{
			SET_PLAYER_WANTED_LEVEL(player, loop_self_freezeWantedLevel, 0);
			SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
		}

		if (loop_player_unlimSpecialAbility)
		{
			//if (!IS_SPECIAL_ABILITY_UNLOCKED(PedHash::FreemodeMale01)) SPECIAL_ABILITY_UNLOCK(PedHash::FreemodeMale01);
			if (!IS_SPECIAL_ABILITY_ENABLED(player, 0))
				ENABLE_SPECIAL_ABILITY(player, TRUE, 0);
			SET_SPECIAL_ABILITY_MULTIPLIER(FLT_MAX);
			//SPECIAL_ABILITY_CHARGE_ABSOLUTE(player, 15, TRUE);
			SPECIAL_ABILITY_FILL_METER(player, TRUE, 0);
		}

		if (loop_player_autoClean)
		{
			sub::PedDamageTextures_catind::ClearAllBloodDamage(iped);
			sub::PedDamageTextures_catind::ClearAllVisibleDamage(iped);
		}

		// Fireworks display
		if (loop_fireworksDisplay)
		{
			start_fireworks_at_coord(GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player2.GetPed().Handle(), GET_RANDOM_FLOAT_IN_RANGE(-10.0f, 10.0f), GET_RANDOM_FLOAT_IN_RANGE(-6.0f, 27.0f), GET_RANDOM_FLOAT_IN_RANGE(-9.0f, 3.5f)), Vector3(0, 0, GET_RANDOM_FLOAT_IN_RANGE(-90.0f, 90.0f)), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 2.45f));
			if (rand() % (INT)2)
			{
				set_explosion_at_coords(iped, Vector3(GET_RANDOM_FLOAT_IN_RANGE(9.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f)), EXPLOSION::DIR_WATER_HYDRANT, 8.0f, 0.0f, true, false, 0);
			}
			else
			{
				set_explosion_at_coords(iped, Vector3(GET_RANDOM_FLOAT_IN_RANGE(-9.0f, -25.0f), GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f)), EXPLOSION::DIR_WATER_HYDRANT, 8.0f, 0.0f, true, false, 0);
			}
		}
		//if (loop_laserSightRendering) ENABLE_LASER_SIGHT_RENDERING(1);

		if (_globalRainFXIntensity > 0.0f)
			SET_RAIN(_globalRainFXIntensity);

		if (g_frozenRadioStation != -1)
		{
			if (GET_PLAYER_RADIO_STATION_INDEX() != g_frozenRadioStation)
				SET_RADIO_TO_STATION_NAME(GET_RADIO_STATION_NAME(g_frozenRadioStation));
		}

		if (loop_clearWeaponPickups) {
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_BULLPUPSHOTGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_ASSAULTSMG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_VEHICLE_WEAPON_ASSAULTSMG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PISTOL50);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_ASSAULTRIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_CARBINERIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_ADVANCEDRIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_COMBATMG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SNIPERRIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HEAVYSNIPER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MICROSMG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SMG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_RPG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MINIGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PUMPSHOTGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SAWNOFFSHOTGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_ASSAULTSHOTGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_GRENADE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MOLOTOV);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SMOKEGRENADE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_STICKYBOMB);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_COMBATPISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_APPISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_GRENADELAUNCHER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_STUNGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_FIREEXTINGUISHER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PETROLCAN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_KNIFE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_NIGHTSTICK);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HAMMER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_BAT);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_GOLFCLUB);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_CROWBAR);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_BULLPUPRIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_BOTTLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SNSPISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_GUSENBERG);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HEAVYPISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SPECIALCARBINE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_DAGGER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_VINTAGEPISTOL);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_FIREWORK);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MUSKET);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HEAVYSHOTGUN);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_MARKSMANRIFLE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PROXMINE);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HOMINGLAUNCHER);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_FLAREGUN);

			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_PISTOL_MK2);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_SMG_MK2);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_ASSAULTRIFLE_MK2);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_CARBINERIFLE_MK2);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_COMBATMG_MK2);
			REMOVE_ALL_PICKUPS_OF_TYPE(PICKUP_WEAPON_HEAVYSNIPER_MK2);
		}

	}

	// Never wanted
	if (loop_never_wanted)
	{
		//SET_POLICE_IGNORE_PLAYER(PLAYER_ID(), TRUE);
		SET_MAX_WANTED_LEVEL(0);
		SET_WANTED_LEVEL_MULTIPLIER(0.0f);
	}

	set_target_into_slot(); // Set targeted entity into spawner slot (self)

	if (loop_forge_gun)
		set_forge_gun();

	if (loop_player_seatbelt)
		set_ped_seatbelt_on(PLAYER_PED_ID()); // PLAYER_ID() seatbelt

	// Ammo hax
	if (sub::BreatheStuff_catind::loop_player_breatheStuff != sub::BreatheStuff_catind::BreathePtfxType::None)
		sub::BreatheStuff_catind::set_self_breathe_ptfx(sub::BreatheStuff_catind::loop_player_breatheStuff);
	if (loop_explosive_rounds)
		SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER_ID());
	if (loop_explosive_melee)
		SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER_ID());
	if (loop_flaming_rounds)
		SET_FIRE_AMMO_THIS_FRAME(PLAYER_ID());
	if (bit_infinite_ammo && (bit_infinite_ammo_enth != PLAYER_PED_ID() || GET_TIME_SINCE_LAST_DEATH() < 10000))
	{
		bit_infinite_ammo_enth = PLAYER_PED_ID();
		SET_PED_INFINITE_AMMO_CLIP(bit_infinite_ammo_enth, true);
	}
	if (loop_self_inf_parachutes)
		give_ped_parachute(PLAYER_PED_ID());

	if (loop_weapon_damage_increase != 1.0f)
	{
		SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER_ID(), loop_weapon_damage_increase);
		//SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER_ID(), loop_weapon_damage_increase);
		SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER_ID(), loop_weapon_damage_increase, true);
		//SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(PLAYER_ID(), loop_weapon_damage_increase);
	}

	if (IS_PED_SHOOTING(PLAYER_PED_ID()))
	{
		if (loop_kaboom_gun)
			set_explosion_at_bullet_hit(PLAYER_PED_ID(), kaboom_gun_hash, kaboom_gun_invis);
		if (loop_triggerfx_gun)
			set_triggerfx_at_bullet_hit(PLAYER_PED_ID(), triggerfx_gun_data.asset, triggerfx_gun_data.effect, Vector3::RandomXYZ() * 180.0f, GET_RANDOM_FLOAT_IN_RANGE(0.63f, 1.40f));
		if (loop_bullet_gun)
			set_bullet_gun(); // Bullet gun (self)
		if (loop_teleport_gun)
			set_teleport_gun(); // Teleport gun (self)
		if (loop_ped_gun)
			set_ped_gun(); // Ped gun (self)
		if (loop_object_gun)
			set_object_gun(); // Object gun (self)
		//if (loop_light_gun)
			//set_light_gun(); // Light gun (self) - moved to thread loops2
		if (loop_bullet_time)
			SET_TIME_SCALE(0.2f); // Bullet time (self)
		if (loop_triple_bullets)
			set_triple_bullets(); // Triple bullets (self)
	}
	/*else*/ if (GET_GAME_TIMER() >= delayedTimer && loop_bullet_time)
		SET_TIME_SCALE(current_timescale);


	if (loop_super_jump)
		SET_SUPER_JUMP_THIS_FRAME(PLAYER_ID()); // Superjump (self)

	if (loop_no_clip)
		set_no_clip(); // No clip mode

	if (loop_super_run)
		set_local_button_super_run(); // Super run (self)

	if (loop_self_refillHealthInCover)
		set_self_refill_health_when_in_cover();
	
	// PLAYER_ID() invincibility
	if (loop_player_invincibility/* && !GET_PLAYER_INVINCIBLE(PLAYER_ID())*/)
	{
		//SET_ABILITY_BAR_VALUE(1.0f, 1.0f);
		//ENABLE_SPECIAL_ABILITY(PLAYER_ID(), 1);
		//	FLASH_ABILITY_BAR(10000);
		//SET_SPECIAL_ABILITY_MULTIPLIER(FLT_MAX);
		if (!GET_PLAYER_INVINCIBLE(PLAYER_ID()))
			SET_PLAYER_INVINCIBLE(PLAYER_ID(), 1);
		set_ped_invincible_on(PLAYER_PED_ID());
	}
	if (mult_self_sweat > 0.0f)
	{
		iped = PLAYER_PED_ID();
		SET_PED_SWEAT(iped, mult_self_sweat);
		if (mult_self_sweat > 4.0f)
		{
			SET_PED_WETNESS_ENABLED_THIS_FRAME(iped);
			SET_PED_WETNESS_HEIGHT(iped, mult_self_sweat / 6);
		}
	}

	if (loop_player_noRagdoll)
		set_ped_no_ragdoll_on(PLAYER_PED_ID()); // PLAYER_ID() no ragdoll

	if (loop_XYZHcoords)
		xyzh_(); // Display xyzh coords

	if (_FpsCounter_::bDisplayFps)
		_FpsCounter_::DisplayFps(); // Display Frame rate


	// Superman mode (manual)
	if (loop_superman)
		set_local_superman_MANUAL();

	if (loop_superman_auto)
		set_ped_superman_AUTO(PLAYER_PED_ID()); // Superman AUTO (self)

	// Forcefield (self)
	if (loop_forcefield)
		set_local_forcefield();

	if (loop_explosion_wp != 0)
		set_explosion_wp(loop_explosion_wp); // Explosion at waypoint

	// Multiplatform neons
	if (loop_multiplat_neons)
		set_multiplat_neons();

	// Decrease vehicle population
	if (loop_vehicle_population)
	{
		SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		SET_VEHICLE_POPULATION_BUDGET(0);
	}
	// Decrease ped population
	if (loop_ped_population)
	{
		SET_PED_POPULATION_BUDGET(0);
		SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	}

	// Drive on water
	if (loop_drive_on_water)
		drive_on_water(PLAYER_PED_ID(), g_drive_water_obj);

	if (loop_player_burn)
		set_ped_burn_mode(PLAYER_PED_ID(), true);

	//if (loop_player_noGravity)
		//SET_PED_GRAVITY(PLAYER_PED_ID(), false);

	// Multipliers
	if (mult69_0) // Player movement speed
	{
		SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER_ID(), mult69_0);
		SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER_ID(), mult69_0);
	}

	if (g_playerVerticalElongationMultiplier != 1.0f) // Player height
		GeneralGlobalHax::SetPlayerHeight(g_playerVerticalElongationMultiplier);

	// Acceleration and brake 'multipliers'
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
	{
		if (!g_myVeh_model.IsHeli())
		{
			if (g_myVeh_model.IsPlane() || IS_VEHICLE_ON_ALL_WHEELS(g_myVeh))
			{
				if (GET_PED_IN_VEHICLE_SEAT(g_myVeh, VehicleSeat::SEAT_DRIVER, 0) == PLAYER_PED_ID())
				{
					if (IS_CONTROL_PRESSED(2, INPUT_VEH_ACCELERATE))
					{
						if (mult69_5 != 0)
							APPLY_FORCE_TO_ENTITY(g_myVeh, 1, 0.0, (float)(mult69_5) / 69.0f, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
					}
					if (mult69_6 != 0 && (IS_CONTROL_PRESSED(2, INPUT_VEH_BRAKE)))
					{
						APPLY_FORCE_TO_ENTITY(g_myVeh, 0, 0.0, (float)(0 - mult69_6), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1); // -abs
					}
					if (GET_ENTITY_SPEED_VECTOR(g_myVeh, true).y > 2)
						set_Handling_Mult69_7();
				}
			}
		}

		// Vehicle damage and defense modifiers
		if (loop_vehicle_damageAndDefense != 1.0f)
		{
			SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
			SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(PLAYER_ID(), loop_vehicle_damageAndDefense);
		}
	}

	// Player noise multiplier
	if (mult_playerNoiseValue != 1)
		SET_PLAYER_NOISE_MULTIPLIER(PLAYER_ID(), mult_playerNoiseValue);

	// Keep engine running
	if (loop_self_engineOn)
	{
		GTAvehicle veh = g_myVeh;
		if (veh.Exists())
		{
			if (!veh.EngineRunning_get())
				veh.EngineRunning_set(true);
			if (!veh.LightsOn_get())
				veh.LightsOn_set(true);
		}
	}



	// ONLY IF SELF IS IN A VEHICLE
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
	{
		// Vehicle invincibility
		if (loop_vehicle_invincibility)
			set_vehicle_invincible_on(g_myVeh);

		// Vehicle fix
		if (loop_vehicle_fixloop)
		{
			GTAvehicle veh = g_myVeh;
			if (veh.IsDamaged())
			{
				static int __VechicleOpsFixCar_texterVal = 0;
				auto& fixCarTexterVal = __VechicleOpsFixCar_texterVal;
				std::array<bool, (int)VehicleWindow::Last> __loop_vehicle_fixloop_windowsIntact;
				auto& windowsIntact = __loop_vehicle_fixloop_windowsIntact;
				if (fixCarTexterVal == 1)
				{
					for (int i = 0; i < windowsIntact.size(); i++)
					{
						windowsIntact[i] = veh.IsWindowIntact((VehicleWindow)i);
					}
				}

				SET_VEHICLE_FIXED(veh.Handle());
				SET_VEHICLE_DIRT_LEVEL(veh.Handle(), 0.0f);
				//SET_VEHICLE_ENGINE_CAN_DEGRADE(veh.Handle(), false);
				SET_VEHICLE_ENGINE_HEALTH(veh.Handle(), 2000.0f);
				SET_VEHICLE_PETROL_TANK_HEALTH(veh.Handle(), 2000.0f);
				SET_VEHICLE_BODY_HEALTH(veh.Handle(), 2000.0f);
				SET_VEHICLE_UNDRIVEABLE(veh.Handle(), false);
				//if(!GET_IS_VEHICLE_ENGINE_RUNNING(veh.Handle())) SET_VEHICLE_ENGINE_ON(veh.Handle(), true, true);

				if (fixCarTexterVal == 1)
				{
					for (int i = 0; i < windowsIntact.size(); i++)
					{
						if (!windowsIntact[i])
							veh.RollDownWindow((VehicleWindow)i);
					}
				}
			}
		}

		// Vehicle flip
		if (loop_vehicle_fliploop)
			set_vehicle_fliploop(g_myVeh);

		// Vehicle invisibility
		if (loop_vehicle_invisibility)
		{
			inull = IS_ENTITY_VISIBLE(PLAYER_PED_ID());
			SET_ENTITY_VISIBLE(g_myVeh, false, false);
			SET_ENTITY_VISIBLE(PLAYER_PED_ID(), inull, false);
			loop_vehicle_invisibility = false;
		}

		// Vehicle rainbow mode-
		if (loop_car_colour_change/* && GET_GAME_TIMER() >= delayedTimer - 400*/)
			set_vehicle_rainbow_mode_tick(g_myVeh, true);

		// Disable self popo sirens
		if (loop_vehicle_disableSiren)
		{
			if (GTAvehicle(g_myVeh).HasSiren_get())
				SET_VEHICLE_HAS_MUTED_SIRENS(g_myVeh, TRUE);
		}

		// Slam it
		if (loop_vehicle_slam)
		{
			if (loop_vehicle_slam <= -0.35f || IS_VEHICLE_ON_ALL_WHEELS(g_myVeh))
				APPLY_FORCE_TO_ENTITY(g_myVeh, 1, 0.0, 0.0, loop_vehicle_slam, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
		}

		// Heavy mass
		if (loop_vehicle_heavymass)
			set_vehicle_heavy_mass_tick(g_myVeh);


		// ONLY IF PAUSE MENU IS INACTIVE
		if (!gameIsPaused)
		{
			// Race boost (self)
			if (loop_race_boost && IS_CONTROL_PRESSED(2, INPUT_VEH_HORN))
			{
				/*ANIMPOSTFX_PLAY("RaceTurbo", 0, 0);*/
				set_self_vehicle_boost();
			}

			// Car jump (self)
			if (loop_car_jump != 0)
				set_local_car_jump();

			// Hydraulics (self)
			if (loop_car_hydraulics)
				set_local_car_hydraulics();

			// Vehicle super grip
			if (loop_super_grip)
				SET_VEHICLE_ON_GROUND_PROPERLY(g_myVeh, 0.0f);

			// SuprKar mode
			if (loop_SuprKarMode)
				set_SuprKarMode_self();

			// Vehicle weapons
			set_vehicle_weapons();

			// Speedometer
			if (sub::Speedo_catind::loop_speedo != sub::Speedo_catind::SPEEDOMODE_OFF)
				sub::Speedo_catind::SpeedoTick();


		}


	}
	// IF NOT IN A VEHICLE:
	else
	{
		/*VehicleOpsInvincibility_bit =*/ bit_vehicle_gravity = bit_freeze_vehicle = VehicleOpsSlippyTires_bit = false;
		//ms_light_intensity = 1.0f;
		//sub::Speedo_catind::_speedoAlpha = 0;

	}


	//Print (WORLD2SCREEN) for PV'ops remembered vehicle
	set_PVops_vehicle_text_world2Screen();


}

inline void menu_AllPlayerOps()
{
	bool bAmIOnline = NETWORK_IS_IN_SESSION() != 0;
	int myPlayer = PLAYER_ID();

	// Spectate player
	if (loop_spectate_player >= 0 && loop_spectate_player < GAME_PLAYERCOUNT)//<= GTA_PLATFORM_SCTVSLOT2)
	{
		if (!NETWORK_IS_PLAYER_ACTIVE(loop_spectate_player))
		{
			NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(false, loop_spectate_player, 1);
			int p = GET_PLAYER_PED(loop_spectate_player);
			if (DOES_ENTITY_EXIST(p))
				NETWORK_SET_IN_SPECTATOR_MODE(false, p);
			NETWORK_SET_ACTIVITY_SPECTATOR(false);
			loop_spectate_player = -1;
		}
		else
		{
			NETWORK_SET_IN_SPECTATOR_MODE(true, GET_PLAYER_PED(loop_spectate_player));
		}
	}

}
void Thread_menu_loops2()
{
	for (;;)
	{
		WAIT(0);

		vehicle_torque_mult_tick();
		vehicle_maxSpeed_mult_tick();

		_FlameThrower_::Tick();

		if (sub::TVChannelStuff_catind::loop_basictv)
			sub::TVChannelStuff_catind::DrawTvWhereItsSupposedToBe();

		menu_AllPlayerOps();

		if (loop_light_gun)
			set_light_gun(); // Light gun (self)

		//if (loop_unloadMapTextures)
			//_SET_DRAW_MAP_VISIBLE(false);

		GTAentity playerPed = PLAYER_PED_ID();

		switch (loop_autoKillEnemies)
		{
		case 1: //Weak
			World::KillNearbyPeds(playerPed, FLT_MAX, PedRelationship::Hate);
			World::KillNearbyPeds(playerPed, FLT_MAX, PedRelationship::Dislike);
			break;
		case 2: //Radical
			World::KillMyEnemies();
			break;
		}


		sub::TeleportLocations_catind::Yachts::Tick();

		_ManualRespawn_::g_manualRespawn.Tick();

		if (loop_unlimVehBoost)
			set_self_vehicle_nativeboost();

	}
}







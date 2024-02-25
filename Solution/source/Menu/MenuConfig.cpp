/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MenuConfig.h"

#include "..\macros.h"

#include "Menu.h"
#include "Routine.h"
#include "Language.h"

#include "..\Util\ExePath.h"
#include "..\Natives\types.h" // RGBA/RgbS
#include "..\Util\GTAmath.h"
#include "..\Util\FileLogger.h"

#include "..\Submenus\Spooner\SpoonerMode.h"
#include "..\Submenus\Spooner\SpoonerSettings.h"
#include "..\Misc\ManualRespawn.h"
#include "..\Misc\FpsCounter.h"
#include "..\Submenus\MiscOptions.h"
#include "..\Misc\JumpAroundMode.h"
#include "..\Memory\GTAmemory.h"
#include "..\Submenus\AnimalRiding.h"
#include "..\Submenus\WeaponOptions.h"
#include "..\Misc\MagnetGun.h"
#include "..\Misc\RopeGun.h"
#include "..\Misc\SmashAbility.h"
#include "..\Misc\VehicleTow.h"
#include "..\Misc\VehicleFly.h"
#include "..\Submenus\TimeOptions.h"
#include "..\Submenus\VehicleOptions.h"

#include <Windows.h>
#include <simpleini\SimpleIni.h>

CSimpleIniA MenuConfig::iniFile;
bool MenuConfig::bSaveAtIntervals = true;

void MenuConfig::ConfigInit()
{
	MenuConfig::iniFile.SetUnicode(true);
	MenuConfig::iniFile.SetMultiKey(false);
	MenuConfig::iniFile.SetMultiLine(false);
	SetFileAttributesW(GetPathffW(Pathff::Main, false).c_str(), GetFileAttributes(GetPathffW(Pathff::Main, false).c_str()) & ~FILE_ATTRIBUTE_READONLY);

	if (MenuConfig::iniFile.LoadFile((GetPathffA(Pathff::Main, true) + "menyooConfig.ini").c_str()) < 0)
		addlog(loglevel, ige::LogType::LOG_ERROR,  "Failed to load menyooConfig from " + GetPathffA(Pathff::Main, true) + "menyooConfig.ini.");
	else
		ConfigRead();
	addlog(loglevel, ige::LogType::LOG_INFO, "Logging Type Detected:" + std::to_string(loglevel));
}

void MenuConfig::ConfigRead()
{
	auto& ini = MenuConfig::iniFile;


	std::string section_settings = "settings";/////////

	MenuConfig::bSaveAtIntervals = ini.GetBoolValue(section_settings.c_str(), "sync_with_config_at_intervals", MenuConfig::bSaveAtIntervals);
	loop_Check_self_death_model = ini.GetBoolValue(section_settings.c_str(), "DeathModelReset", loop_Check_self_death_model);
	menubinds = ini.GetLongValue(section_settings.c_str(), "open_key", menubinds);
	menubindsGamepad.first = ini.GetLongValue(section_settings.c_str(), "open_button_for_gamepad_1", menubindsGamepad.first);
	menubindsGamepad.second = ini.GetLongValue(section_settings.c_str(), "open_button_for_gamepad_2", menubindsGamepad.second);
	respawnbinds = ini.GetLongValue(section_settings.c_str(), "manual_respawn_button", respawnbinds);
	menuPos.x = ini.GetDoubleValue(section_settings.c_str(), "menuPosX", (menuPos.x + 0.0598f) * 100); menuPos.x = menuPos.x / 100 - 0.0598f;
	menuPos.y = ini.GetDoubleValue(section_settings.c_str(), "menuPosY", (menuPos.y + 0.074f) * 100); menuPos.y = menuPos.y / 100 - 0.074f;
	Menu::bit_glare_test = ini.GetBoolValue(section_settings.c_str(), "Titlebox_Globe", Menu::bit_glare_test);
	Menu::bit_centre_title = ini.GetBoolValue(section_settings.c_str(), "centre_title", Menu::bit_centre_title);
	Menu::bit_centre_options = ini.GetBoolValue(section_settings.c_str(), "centre_options", Menu::bit_centre_options);
	Menu::bit_centre_breaks = ini.GetBoolValue(section_settings.c_str(), "centre_breaks", Menu::bit_centre_breaks);
	Language::configLangName = ini.GetValue(section_settings.c_str(), "language", Language::configLangName.c_str());
	Language::Init();
	loglevel = ini.GetLongValue(section_settings.c_str(), "log level", loglevel);


	std::string section_general = "general";/////////


	bind_no_clip = ini.GetLongValue(section_general.c_str(), "FreeCamButton", bind_no_clip);


	std::string section_colours = "colours";/////////


	Menu::gradients = ini.GetBoolValue(section_colours.c_str(), "gradients", Menu::gradients);
	loop_RainbowBoxes = ini.GetBoolValue(section_colours.c_str(), "rainbow_mode", loop_RainbowBoxes);
	Menu::thin_line_over_screct = ini.GetBoolValue(section_colours.c_str(), "thin_line_over_footer", Menu::thin_line_over_screct);

	titlebox.R = ini.GetLongValue(section_colours.c_str(), "titlebox_R", titlebox.R);
	titlebox.G = ini.GetLongValue(section_colours.c_str(), "titlebox_G", titlebox.G);
	titlebox.B = ini.GetLongValue(section_colours.c_str(), "titlebox_B", titlebox.B);
	titlebox.A = ini.GetLongValue(section_colours.c_str(), "titlebox_A", titlebox.A);

	BG.R = ini.GetLongValue(section_colours.c_str(), "BG_R", BG.R);
	BG.G = ini.GetLongValue(section_colours.c_str(), "BG_G", BG.G);
	BG.B = ini.GetLongValue(section_colours.c_str(), "BG_B", BG.B);
	BG.A = ini.GetLongValue(section_colours.c_str(), "BG_A", BG.A);

	titletext.R = ini.GetLongValue(section_colours.c_str(), "titletext_R", titletext.R);
	titletext.G = ini.GetLongValue(section_colours.c_str(), "titletext_G", titletext.G);
	titletext.B = ini.GetLongValue(section_colours.c_str(), "titletext_B", titletext.B);
	titletext.A = ini.GetLongValue(section_colours.c_str(), "titletext_A", titletext.A);

	optiontext.R = ini.GetLongValue(section_colours.c_str(), "optiontext_R", optiontext.R);
	optiontext.G = ini.GetLongValue(section_colours.c_str(), "optiontext_G", optiontext.G);
	optiontext.B = ini.GetLongValue(section_colours.c_str(), "optiontext_B", optiontext.B);
	optiontext.A = ini.GetLongValue(section_colours.c_str(), "optiontext_A", optiontext.A);

	selectedtext.R = ini.GetLongValue(section_colours.c_str(), "selectedtext_R", selectedtext.R);
	selectedtext.G = ini.GetLongValue(section_colours.c_str(), "selectedtext_G", selectedtext.G);
	selectedtext.B = ini.GetLongValue(section_colours.c_str(), "selectedtext_B", selectedtext.B);
	selectedtext.A = ini.GetLongValue(section_colours.c_str(), "selectedtext_A", selectedtext.A);

	optionbreaks.R = ini.GetLongValue(section_colours.c_str(), "optionbreaks_R", optionbreaks.R);
	optionbreaks.G = ini.GetLongValue(section_colours.c_str(), "optionbreaks_G", optionbreaks.G);
	optionbreaks.B = ini.GetLongValue(section_colours.c_str(), "optionbreaks_B", optionbreaks.B);
	optionbreaks.A = ini.GetLongValue(section_colours.c_str(), "optionbreaks_A", optionbreaks.A);

	optioncount.R = ini.GetLongValue(section_colours.c_str(), "optioncount_R", optioncount.R);
	optioncount.G = ini.GetLongValue(section_colours.c_str(), "optioncount_G", optioncount.G);
	optioncount.B = ini.GetLongValue(section_colours.c_str(), "optioncount_B", optioncount.B);
	optioncount.A = ini.GetLongValue(section_colours.c_str(), "optioncount_A", optioncount.A);

	selectionhi.R = ini.GetLongValue(section_colours.c_str(), "selectionhi_R", selectionhi.R);
	selectionhi.G = ini.GetLongValue(section_colours.c_str(), "selectionhi_G", selectionhi.G);
	selectionhi.B = ini.GetLongValue(section_colours.c_str(), "selectionhi_B", selectionhi.B);
	selectionhi.A = ini.GetLongValue(section_colours.c_str(), "selectionhi_A", selectionhi.A);

	_globalPedTrackers_Col.R = ini.GetLongValue(section_colours.c_str(), "pedTrackers_R", _globalPedTrackers_Col.R);
	_globalPedTrackers_Col.G = ini.GetLongValue(section_colours.c_str(), "pedTrackers_G", _globalPedTrackers_Col.G);
	_globalPedTrackers_Col.B = ini.GetLongValue(section_colours.c_str(), "pedTrackers_B", _globalPedTrackers_Col.B);
	_globalPedTrackers_Col.A = ini.GetLongValue(section_colours.c_str(), "pedTrackers_A", _globalPedTrackers_Col.A);


	std::string section_fonts = "fonts";/////////


	font_title = ini.GetLongValue(section_fonts.c_str(), "title", font_title);
	font_options = ini.GetLongValue(section_fonts.c_str(), "options", font_options);
	font_selection = ini.GetLongValue(section_fonts.c_str(), "selection", font_selection);
	font_breaks = ini.GetLongValue(section_fonts.c_str(), "breaks", font_breaks);
	font_xyzh = ini.GetLongValue(section_fonts.c_str(), "font_xyzh", font_xyzh);
	font_speedo = ini.GetLongValue(section_fonts.c_str(), "font_speedo", font_speedo);


	std::string section_spooner = "object-spooner";/////////

	sub::Spooner::SpoonerMode::bindsKeyboard = ini.GetLongValue(section_spooner.c_str(), "SpoonerModeHotkey", sub::Spooner::SpoonerMode::bindsKeyboard);
	sub::Spooner::SpoonerMode::bindsGamepad.first = ini.GetLongValue(section_spooner.c_str(), "SpoonerModeGamepadBind_1", sub::Spooner::SpoonerMode::bindsGamepad.first);
	sub::Spooner::SpoonerMode::bindsGamepad.second = ini.GetLongValue(section_spooner.c_str(), "SpoonerModeGamepadBind_2", sub::Spooner::SpoonerMode::bindsGamepad.second);
	sub::Spooner::Settings::CameraMovementSensitivityKeyboard = (float)ini.GetDoubleValue(section_spooner.c_str(), "CameraMovementSensitivityKeyboard", sub::Spooner::Settings::CameraMovementSensitivityKeyboard);
	sub::Spooner::Settings::CameraRotationSensitivityMouse = (float)ini.GetDoubleValue(section_spooner.c_str(), "CameraRotationSensitivityMouse", sub::Spooner::Settings::CameraRotationSensitivityMouse);
	sub::Spooner::Settings::CameraMovementSensitivityGamepad = (float)ini.GetDoubleValue(section_spooner.c_str(), "CameraMovementSensitivityGamepad", sub::Spooner::Settings::CameraMovementSensitivityGamepad);
	sub::Spooner::Settings::CameraRotationSensitivityGamepad = (float)ini.GetDoubleValue(section_spooner.c_str(), "CameraRotationSensitivityGamepad", sub::Spooner::Settings::CameraRotationSensitivityGamepad);
	sub::Spooner::Settings::bShowModelPreviews = ini.GetBoolValue(section_spooner.c_str(), "ShowModelPreviews", sub::Spooner::Settings::bShowModelPreviews);
	sub::Spooner::Settings::bShowBoxAroundSelectedEntity = ini.GetBoolValue(section_spooner.c_str(), "ShowBoxAroundSelectedEntity", sub::Spooner::Settings::bShowBoxAroundSelectedEntity);
	sub::Spooner::Settings::bSpawnDynamicProps = ini.GetBoolValue(section_spooner.c_str(), "SpawnDynamicProps", sub::Spooner::Settings::bSpawnDynamicProps);
	sub::Spooner::Settings::bSpawnDynamicPeds = ini.GetBoolValue(section_spooner.c_str(), "SpawnDynamicPeds", sub::Spooner::Settings::bSpawnDynamicPeds);
	sub::Spooner::Settings::bSpawnDynamicVehicles = ini.GetBoolValue(section_spooner.c_str(), "SpawnDynamicVehicles", sub::Spooner::Settings::bSpawnDynamicVehicles);
	sub::Spooner::Settings::bFreezeEntityWhenMovingIt = ini.GetBoolValue(section_spooner.c_str(), "FreezeEntityWhenMovingIt", sub::Spooner::Settings::bFreezeEntityWhenMovingIt);
	sub::Spooner::Settings::bSpawnInvincibleEntities = ini.GetBoolValue(section_spooner.c_str(), "SpawnInvincibleEntities", sub::Spooner::Settings::bSpawnInvincibleEntities);
	sub::Spooner::Settings::bSpawnStillPeds = ini.GetBoolValue(section_spooner.c_str(), "SpawnStillPeds", sub::Spooner::Settings::bSpawnStillPeds);
	sub::Spooner::Settings::bAddToDbAsMissionEntities = ini.GetBoolValue(section_spooner.c_str(), "AddToDbAsMissionEntities", sub::Spooner::Settings::bAddToDbAsMissionEntities);
	sub::Spooner::Settings::bTeleportToReferenceWhenLoadingFile = ini.GetBoolValue(section_spooner.c_str(), "TeleportToReferenceWhenLoadingFile", sub::Spooner::Settings::bTeleportToReferenceWhenLoadingFile);
	sub::Spooner::Settings::bKeepPositionWhenAttaching = ini.GetBoolValue(section_spooner.c_str(), "KeepPositionWhenAttaching", sub::Spooner::Settings::bKeepPositionWhenAttaching);
	sub::Spooner::Settings::SpoonerModeMode = (sub::Spooner::eSpoonerModeMode)ini.GetLongValue(section_spooner.c_str(), "SpoonerModeMethod", (UINT8)sub::Spooner::Settings::SpoonerModeMode);


	std::string section_haxValues = "hax-values";/////////


	 //loop_hide_hud = ini.GetBoolValue(section_haxValues.c_str(), "hide_hud", loop_hide_hud);
	loop_showFullHud = ini.GetBoolValue(section_haxValues.c_str(), "show_full_hud", loop_showFullHud);
	_ManualRespawn_::g_manualRespawn.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "manual_respawn", _ManualRespawn_::g_manualRespawn.Enabled());
	loop_no_clip = ini.GetBoolValue(section_haxValues.c_str(), "freecam", loop_no_clip);
	loop_XYZHcoords = ini.GetBoolValue(section_haxValues.c_str(), "display_xyzh_coords", loop_XYZHcoords);
	_FpsCounter_::bDisplayFps = ini.GetBoolValue(section_haxValues.c_str(), "display_fps", _FpsCounter_::bDisplayFps);
	sub::TVChannelStuff_catind::loop_basictv = ini.GetBoolValue(section_haxValues.c_str(), "basic_tv_player", sub::TVChannelStuff_catind::loop_basictv);
	loop_sync_clock = ini.GetBoolValue(section_haxValues.c_str(), "sync_clock", loop_sync_clock);
	loop_pause_clock = ini.GetBoolValue(section_haxValues.c_str(), "pause_clock", loop_pause_clock);
	pause_clock_H = ini.GetLongValue(section_haxValues.c_str(), "pause_clock_hour", pause_clock_H);
	pause_clock_M = ini.GetLongValue(section_haxValues.c_str(), "pause_clock_minute", pause_clock_M);
	loop_ped_population = ini.GetBoolValue(section_haxValues.c_str(), "decreased_ped_population", loop_ped_population);
	loop_vehicle_population = ini.GetBoolValue(section_haxValues.c_str(), "decreased_veh_population", loop_vehicle_population);
	loop_clearWeaponPickups = ini.GetBoolValue(section_haxValues.c_str(), "decreased_weapon_pickups", loop_clearWeaponPickups);
	_globalClearArea_radius = ini.GetDoubleValue(section_haxValues.c_str(), "clear_area_radius", _globalClearArea_radius);
	loop_restricted_areas_access = ini.GetBoolValue(section_haxValues.c_str(), "restricted_area_access", loop_restricted_areas_access);
	loop_fireworksDisplay = ini.GetBoolValue(section_haxValues.c_str(), "fireworks_ahoy", loop_fireworksDisplay);
	loop_blackout_mode = ini.GetBoolValue(section_haxValues.c_str(), "emp_mode", loop_blackout_mode);
	loop_simple_blackout_mode = ini.GetBoolValue(section_haxValues.c_str(), "simple_blackout_mode", loop_simple_blackout_mode);
	loop_massacre_mode = ini.GetBoolValue(section_haxValues.c_str(), "massacre_mode", loop_massacre_mode);
	_JumpAroundMode_::bEnabled = ini.GetBoolValue(section_haxValues.c_str(), "jump_around_mode", _JumpAroundMode_::bEnabled);
	g_frozenRadioStation = (INT16)ini.GetLongValue(section_haxValues.c_str(), "frozen_radio_station", g_frozenRadioStation);
	_SpSnow.ToggleSnow(ini.GetBoolValue(section_haxValues.c_str(), "snow_on_terrain", _SpSnow.IsSnow()));
	sub::AnimalRiding_catind::Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "animal_riding_mode", sub::AnimalRiding_catind::Enabled());

	loop_forge_gun = ini.GetBoolValue(section_haxValues.c_str(), "forge_gun", loop_forge_gun);
	_globalForgeGun_shootForce = ini.GetDoubleValue(section_haxValues.c_str(), "forge_gun_shoot_force", _globalForgeGun_shootForce);
	sub::GravityGun_catind::Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "gravity_gun", sub::GravityGun_catind::Enabled());
	sub::GravityGun_catind::ShootForce() = ini.GetDoubleValue(section_haxValues.c_str(), "gravity_gun_shoot_force", sub::GravityGun_catind::ShootForce());
	_MagnetGun_::g_magnetGun.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "magnet_gun", _MagnetGun_::g_magnetGun.Enabled());
	loop_teleport_gun = ini.GetBoolValue(section_haxValues.c_str(), "teleport_gun", loop_teleport_gun);
	//loop_kaboom_gun = ini.GetBoolValue(section_haxValues.c_str(), "kaboom_gun", loop_kaboom_gun);
	//loop_triggerfx_gun = ini.GetBoolValue(section_haxValues.c_str(), "triggerfx_gun", loop_triggerfx_gun);
	//loop_bullet_gun = ini.GetBoolValue(section_haxValues.c_str(), "bullet_gun", loop_bullet_gun);
	//loop_ped_gun = ini.GetBoolValue(section_haxValues.c_str(), "ped_gun", loop_ped_gun);
	//loop_object_gun = ini.GetBoolValue(section_haxValues.c_str(), "object_vehicle_gun", loop_object_gun);
	loop_light_gun = ini.GetBoolValue(section_haxValues.c_str(), "light_gun", loop_light_gun);
	_RopeGun_::g_ropeGun.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "rope_gun", _RopeGun_::g_ropeGun.Enabled());
	loop_bullet_time = ini.GetBoolValue(section_haxValues.c_str(), "bullet_time", loop_bullet_time);
	loop_weapon_damage_increase = ini.GetDoubleValue(section_haxValues.c_str(), "weapon_damage_multiplier", loop_weapon_damage_increase);
	loop_explosive_rounds = ini.GetBoolValue(section_haxValues.c_str(), "explosive_bullets", loop_explosive_rounds);
	loop_flaming_rounds = ini.GetBoolValue(section_haxValues.c_str(), "flaming_bullets", loop_flaming_rounds);
	loop_explosive_melee = ini.GetBoolValue(section_haxValues.c_str(), "explosive_melee", loop_explosive_melee);
	loop_triple_bullets = ini.GetBoolValue(section_haxValues.c_str(), "triple_bullets", loop_triple_bullets);
	loop_self_triggerbot = ini.GetBoolValue(section_haxValues.c_str(), "self_triggerbot", loop_self_triggerbot);
	loop_rapid_fire = ini.GetBoolValue(section_haxValues.c_str(), "rapid_fire", loop_rapid_fire);
	loop_soulswitch_gun = ini.GetBoolValue(section_haxValues.c_str(), "soul_switch_gun", loop_soulswitch_gun);
	loop_self_resurrectionGun = ini.GetBoolValue(section_haxValues.c_str(), "self_revival_gun", loop_self_resurrectionGun);
	loop_self_deleteGun = ini.GetBoolValue(section_haxValues.c_str(), "self_delete_gun", loop_self_deleteGun);
	bit_infinite_ammo = ini.GetBoolValue(section_haxValues.c_str(), "self_infinite_ammo_clip", bit_infinite_ammo);
	loop_self_inf_parachutes = ini.GetBoolValue(section_haxValues.c_str(), "infinite_parachutes", loop_self_inf_parachutes);
	loop_autoKillEnemies = ini.GetLongValue(section_haxValues.c_str(), "auto_kill_enemies", loop_autoKillEnemies);

	sub::LaserSight_catind::bEnabled = ini.GetBoolValue(section_haxValues.c_str(), "laser_sight_toggle", sub::LaserSight_catind::bEnabled);
	sub::LaserSight_catind::_colour.R = ini.GetLongValue(section_haxValues.c_str(), "laser_sight_R", sub::LaserSight_catind::_colour.R);
	sub::LaserSight_catind::_colour.G = ini.GetLongValue(section_haxValues.c_str(), "laser_sight_G", sub::LaserSight_catind::_colour.G);
	sub::LaserSight_catind::_colour.B = ini.GetLongValue(section_haxValues.c_str(), "laser_sight_B", sub::LaserSight_catind::_colour.B);
	sub::LaserSight_catind::_colour.A = ini.GetLongValue(section_haxValues.c_str(), "laser_sight_A", sub::LaserSight_catind::_colour.A);

	loop_self_refillHealthInCover = ini.GetBoolValue(section_haxValues.c_str(), "player_refill_health_when_in_cover", loop_self_refillHealthInCover);
	loop_player_invincibility = ini.GetBoolValue(section_haxValues.c_str(), "player_invincibility", loop_player_invincibility);
	loop_player_noRagdoll = ini.GetBoolValue(section_haxValues.c_str(), "player_no_ragdoll", loop_player_noRagdoll);
	loop_player_seatbelt = ini.GetBoolValue(section_haxValues.c_str(), "player_seatbelt", loop_player_seatbelt);
	loop_player_unlimSpecialAbility = ini.GetBoolValue(section_haxValues.c_str(), "player_unlimited_special_ab", loop_player_unlimSpecialAbility);
	loop_player_autoClean = ini.GetBoolValue(section_haxValues.c_str(), "player_auto_clean", loop_player_autoClean);

	loop_super_jump = ini.GetBoolValue(section_haxValues.c_str(), "player_super_jump", loop_super_jump);
	loop_super_run = ini.GetBoolValue(section_haxValues.c_str(), "player_super_run", loop_super_run);
	loop_superman = ini.GetBoolValue(section_haxValues.c_str(), "player_superman_manual", loop_superman);
	loop_superman_auto = ini.GetBoolValue(section_haxValues.c_str(), "player_superman_auto", loop_superman_auto);
	loop_forcefield = ini.GetLongValue(section_haxValues.c_str(), "player_forcefield", loop_forcefield);
	_SmashAbility_::g_smashAbility.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "player_smash_ability", _SmashAbility_::g_smashAbility.Enabled());
	loop_ignored_by_everyone = ini.GetBoolValue(section_haxValues.c_str(), "player_ignored_by_everyone", loop_ignored_by_everyone);
	loop_never_wanted = ini.GetBoolValue(section_haxValues.c_str(), "player_never_wanted", loop_never_wanted);
	loop_player_burn = ini.GetBoolValue(section_haxValues.c_str(), "player_burn_mode", loop_player_burn);
	//sub::GhostRiderMode_catind::g_ghostRiderMode.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "player_ghost_rider_mode", sub::GhostRiderMode_catind::g_ghostRiderMode.Enabled());
	//loop_player_noGravity = ini.GetBoolValue(section_haxValues.c_str(), "player_no_gravity", loop_player_noGravity);

	loop_vehicle_invincibility = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_invincibility", loop_vehicle_invincibility);
	loop_vehicle_heavymass = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_increased_mass", loop_vehicle_heavymass);
	loop_race_boost = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_horn_boost", loop_race_boost);
	loop_unlimVehBoost = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_unlim_native_boost", loop_unlimVehBoost);
	loop_car_jump = ini.GetLongValue(section_haxValues.c_str(), "vehicle_jump", loop_car_jump);
	loop_car_hydraulics = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_hydraulics", loop_car_hydraulics);
	loop_super_grip = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_glue_to_ground", loop_super_grip);
	loop_SuprKarMode = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_SuprKar_mode", loop_SuprKarMode);
	loop_car_colour_change = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_rainbow_mode", loop_car_colour_change);
	loop_vehicle_fixloop = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_auto_fix", loop_vehicle_fixloop);
	loop_vehicle_fliploop = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_auto_flip", loop_vehicle_fliploop);
	loop_self_engineOn = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_keep_engine_running", loop_self_engineOn);
	_VehicleTow_::g_vehicleTow.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_tow_mode", _VehicleTow_::g_vehicleTow.Enabled());
	_VehicleFly_::g_vehicleFly.Enabled() = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_fly_mode", _VehicleFly_::g_vehicleFly.Enabled());
	loop_multiplat_neons = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_multiplat_neons", loop_multiplat_neons);
	loop_multiplat_neons_rainbow = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_multiplat_neons_rainbow", loop_multiplat_neons_rainbow);
	_global_MultiPlatNeons_Col.R = ini.GetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_R", _global_MultiPlatNeons_Col.R);
	_global_MultiPlatNeons_Col.G = ini.GetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_G", _global_MultiPlatNeons_Col.G);
	_global_MultiPlatNeons_Col.B = ini.GetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_B", _global_MultiPlatNeons_Col.B);
	mult69_5 = (float)ini.GetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_acceleration", mult69_5);
	mult69_6 = (float)ini.GetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_brakes", mult69_6);
	mult69_7 = (float)ini.GetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_handling", mult69_7);

	_globalSpawnVehicle_drawBmps = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_enable_previews", _globalSpawnVehicle_drawBmps);
	_globalSpawnVehicle_plateText = ini.GetValue(section_haxValues.c_str(), "vehicle_spawner_plate_text", _globalSpawnVehicle_plateText.c_str());
	_globalSpawnVehicle_plateTexter_value = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_plate_text_texter_value", _globalSpawnVehicle_plateTexter_value);
	_globalSpawnVehicle_plateType = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_plate_type", _globalSpawnVehicle_plateType);
	_globalSpawnVehicle_autoSit = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_auto_sit", _globalSpawnVehicle_autoSit);
	_globalSpawnVehicle_autoUpgrade = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_auto_upgrade", _globalSpawnVehicle_autoUpgrade);
	_globalSpawnVehicle_invincible = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_invincible", _globalSpawnVehicle_invincible);
	_globalSpawnVehicle_persistent = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_persistent", _globalSpawnVehicle_persistent);
	_globalSpawnVehicle_deleteOld = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_delete_old", _globalSpawnVehicle_deleteOld);
	_globalSpawnVehicle_neonToggle = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_spawner_neons_on", _globalSpawnVehicle_neonToggle);
	_globalSpawnVehicle_neonCol.R = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_R", _globalSpawnVehicle_neonCol.R);
	_globalSpawnVehicle_neonCol.G = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_G", _globalSpawnVehicle_neonCol.G);
	_globalSpawnVehicle_neonCol.B = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_B", _globalSpawnVehicle_neonCol.B);
	_globalSpawnVehicle_PrimCol = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_primary_colour", _globalSpawnVehicle_PrimCol);
	_globalSpawnVehicle_SecCol = ini.GetLongValue(section_haxValues.c_str(), "vehicle_spawner_secondary_colour", _globalSpawnVehicle_SecCol);
	_globalLSC_Customs = ini.GetBoolValue(section_haxValues.c_str(), "vehicle_menyoo_customs_lsc", _globalLSC_Customs);

	sub::Clock_catind::loop_clock = ini.GetDoubleValue(section_haxValues.c_str(), "clock", sub::Clock_catind::loop_clock);
	sub::Clock_catind::_analogueClockPos.x = (float)ini.GetDoubleValue(section_haxValues.c_str(), "clock_screen_pos_x", sub::Clock_catind::_analogueClockPos.x);
	sub::Clock_catind::_analogueClockPos.y = (float)ini.GetDoubleValue(section_haxValues.c_str(), "clock_screen_pos_y", sub::Clock_catind::_analogueClockPos.y);

	sub::Speedo_catind::loop_speedo = ini.GetLongValue(section_haxValues.c_str(), "speedo", sub::Speedo_catind::loop_speedo);
	sub::Speedo_catind::bit_speedo_mph = ini.GetBoolValue(section_haxValues.c_str(), "speedo_mph_instead_of_kmph", sub::Speedo_catind::bit_speedo_mph);
	sub::Speedo_catind::_speedoPosition.x = (float)ini.GetDoubleValue(section_haxValues.c_str(), "speedo_screen_pos_x", sub::Speedo_catind::_speedoPosition.x);
	sub::Speedo_catind::_speedoPosition.y = (float)ini.GetDoubleValue(section_haxValues.c_str(), "speedo_screen_pos_y", sub::Speedo_catind::_speedoPosition.y);
	sub::Speedo_catind::_currentSpeedoBg.fileName = ini.GetValue(section_haxValues.c_str(), "speedo_bg_name", sub::Speedo_catind::_currentSpeedoBg.fileName.c_str());
	sub::Speedo_catind::SetCurrentBgIdFromBgNameForConfig();

}

void MenuConfig::ConfigSave()
{
	auto& ini = MenuConfig::iniFile;


	std::string section_settings = "settings";/////////


	ini.SetBoolValue(section_settings.c_str(), "sync_with_config_at_intervals", MenuConfig::bSaveAtIntervals);
	ini.SetBoolValue(section_settings.c_str(), "DeathModelReset", loop_Check_self_death_model);
	ini.SetLongValue(section_settings.c_str(), "open_key", menubinds);
	ini.SetLongValue(section_settings.c_str(), "open_button_for_gamepad_1", menubindsGamepad.first);
	ini.SetLongValue(section_settings.c_str(), "open_button_for_gamepad_2", menubindsGamepad.second);
	ini.SetLongValue(section_settings.c_str(), "manual_respawn_button", respawnbinds);
	ini.SetDoubleValue(section_settings.c_str(), "menuPosX", (menuPos.x + 0.0598f) * 100);
	ini.SetDoubleValue(section_settings.c_str(), "menuPosY", (menuPos.y + 0.074f) * 100);
	ini.SetBoolValue(section_settings.c_str(), "Titlebox_Globe", Menu::bit_glare_test);
	ini.SetBoolValue(section_settings.c_str(), "centre_title", Menu::bit_centre_title);
	ini.SetBoolValue(section_settings.c_str(), "centre_options", Menu::bit_centre_options);
	ini.SetBoolValue(section_settings.c_str(), "centre_breaks", Menu::bit_centre_breaks);
	ini.SetValue(section_settings.c_str(), "language", Language::configLangName.c_str());
	ini.SetLongValue(section_settings.c_str(), "log level", loglevel);


	std::string section_general = "general";/////////


	ini.SetLongValue(section_general.c_str(), "FreeCamButton", bind_no_clip);


	std::string section_colours = "colours";/////////


	ini.SetBoolValue(section_colours.c_str(), "gradients", Menu::gradients);
	ini.SetBoolValue(section_colours.c_str(), "rainbow_mode", loop_RainbowBoxes);
	ini.SetBoolValue(section_colours.c_str(), "thin_line_over_footer", Menu::thin_line_over_screct);

	ini.SetLongValue(section_colours.c_str(), "titlebox_R", titlebox.R);
	ini.SetLongValue(section_colours.c_str(), "titlebox_G", titlebox.G);
	ini.SetLongValue(section_colours.c_str(), "titlebox_B", titlebox.B);
	ini.SetLongValue(section_colours.c_str(), "titlebox_A", titlebox.A);

	ini.SetLongValue(section_colours.c_str(), "BG_R", BG.R);
	ini.SetLongValue(section_colours.c_str(), "BG_G", BG.G);
	ini.SetLongValue(section_colours.c_str(), "BG_B", BG.B);
	ini.SetLongValue(section_colours.c_str(), "BG_A", BG.A);

	ini.SetLongValue(section_colours.c_str(), "titletext_R", titletext.R);
	ini.SetLongValue(section_colours.c_str(), "titletext_G", titletext.G);
	ini.SetLongValue(section_colours.c_str(), "titletext_B", titletext.B);
	ini.SetLongValue(section_colours.c_str(), "titletext_A", titletext.A);

	ini.SetLongValue(section_colours.c_str(), "optiontext_R", optiontext.R);
	ini.SetLongValue(section_colours.c_str(), "optiontext_G", optiontext.G);
	ini.SetLongValue(section_colours.c_str(), "optiontext_B", optiontext.B);
	ini.SetLongValue(section_colours.c_str(), "optiontext_A", optiontext.A);

	ini.SetLongValue(section_colours.c_str(), "selectedtext_R", selectedtext.R);
	ini.SetLongValue(section_colours.c_str(), "selectedtext_G", selectedtext.G);
	ini.SetLongValue(section_colours.c_str(), "selectedtext_B", selectedtext.B);
	ini.SetLongValue(section_colours.c_str(), "selectedtext_A", selectedtext.A);

	ini.SetLongValue(section_colours.c_str(), "optionbreaks_R", optionbreaks.R);
	ini.SetLongValue(section_colours.c_str(), "optionbreaks_G", optionbreaks.G);
	ini.SetLongValue(section_colours.c_str(), "optionbreaks_B", optionbreaks.B);
	ini.SetLongValue(section_colours.c_str(), "optionbreaks_A", optionbreaks.A);

	ini.SetLongValue(section_colours.c_str(), "optioncount_R", optioncount.R);
	ini.SetLongValue(section_colours.c_str(), "optioncount_G", optioncount.G);
	ini.SetLongValue(section_colours.c_str(), "optioncount_B", optioncount.B);
	ini.SetLongValue(section_colours.c_str(), "optioncount_A", optioncount.A);

	ini.SetLongValue(section_colours.c_str(), "selectionhi_R", selectionhi.R);
	ini.SetLongValue(section_colours.c_str(), "selectionhi_G", selectionhi.G);
	ini.SetLongValue(section_colours.c_str(), "selectionhi_B", selectionhi.B);
	ini.SetLongValue(section_colours.c_str(), "selectionhi_A", selectionhi.A);

	ini.SetLongValue(section_colours.c_str(), "pedTrackers_R", _globalPedTrackers_Col.R);
	ini.SetLongValue(section_colours.c_str(), "pedTrackers_G", _globalPedTrackers_Col.G);
	ini.SetLongValue(section_colours.c_str(), "pedTrackers_B", _globalPedTrackers_Col.B);
	ini.SetLongValue(section_colours.c_str(), "pedTrackers_A", _globalPedTrackers_Col.A);


	std::string section_fonts = "fonts";/////////


	ini.SetLongValue(section_fonts.c_str(), "title", font_title);
	ini.SetLongValue(section_fonts.c_str(), "options", font_options);
	ini.SetLongValue(section_fonts.c_str(), "selection", font_selection);
	ini.SetLongValue(section_fonts.c_str(), "breaks", font_breaks);
	ini.SetLongValue(section_fonts.c_str(), "font_xyzh", font_xyzh);
	ini.SetLongValue(section_fonts.c_str(), "font_speedo", font_speedo);


	std::string section_spooner = "object-spooner";/////////

	ini.SetLongValue(section_spooner.c_str(), "SpoonerModeHotkey", sub::Spooner::SpoonerMode::bindsKeyboard);
	ini.SetLongValue(section_spooner.c_str(), "SpoonerModeGamepadBind_1", sub::Spooner::SpoonerMode::bindsGamepad.first);
	ini.SetLongValue(section_spooner.c_str(), "SpoonerModeGamepadBind_2", sub::Spooner::SpoonerMode::bindsGamepad.second);
	ini.SetDoubleValue(section_spooner.c_str(), "CameraMovementSensitivityKeyboard", sub::Spooner::Settings::CameraMovementSensitivityKeyboard);
	ini.SetDoubleValue(section_spooner.c_str(), "CameraRotationSensitivityMouse", sub::Spooner::Settings::CameraRotationSensitivityMouse);
	ini.SetDoubleValue(section_spooner.c_str(), "CameraMovementSensitivityGamepad", sub::Spooner::Settings::CameraMovementSensitivityGamepad);
	ini.SetDoubleValue(section_spooner.c_str(), "CameraRotationSensitivityGamepad", sub::Spooner::Settings::CameraRotationSensitivityGamepad);
	ini.SetBoolValue(section_spooner.c_str(), "ShowModelPreviews", sub::Spooner::Settings::bShowModelPreviews);
	ini.SetBoolValue(section_spooner.c_str(), "ShowBoxAroundSelectedEntity", sub::Spooner::Settings::bShowBoxAroundSelectedEntity);
	ini.SetBoolValue(section_spooner.c_str(), "SpawnDynamicProps", sub::Spooner::Settings::bSpawnDynamicProps);
	ini.SetBoolValue(section_spooner.c_str(), "SpawnDynamicPeds", sub::Spooner::Settings::bSpawnDynamicPeds);
	ini.SetBoolValue(section_spooner.c_str(), "SpawnDynamicVehicles", sub::Spooner::Settings::bSpawnDynamicVehicles);
	ini.SetBoolValue(section_spooner.c_str(), "FreezeEntityWhenMovingIt", sub::Spooner::Settings::bFreezeEntityWhenMovingIt);
	ini.SetBoolValue(section_spooner.c_str(), "SpawnInvincibleEntities", sub::Spooner::Settings::bSpawnInvincibleEntities);
	ini.SetBoolValue(section_spooner.c_str(), "SpawnStillPeds", sub::Spooner::Settings::bSpawnStillPeds);
	ini.SetBoolValue(section_spooner.c_str(), "AddToDbAsMissionEntities", sub::Spooner::Settings::bAddToDbAsMissionEntities);
	ini.SetBoolValue(section_spooner.c_str(), "TeleportToReferenceWhenLoadingFile", sub::Spooner::Settings::bTeleportToReferenceWhenLoadingFile);
	ini.SetBoolValue(section_spooner.c_str(), "KeepPositionWhenAttaching", sub::Spooner::Settings::bKeepPositionWhenAttaching);
	ini.SetLongValue(section_spooner.c_str(), "SpoonerModeMethod", (UINT8)sub::Spooner::Settings::SpoonerModeMode);


	std::string section_haxValues = "hax-values";/////////


										   //ini.SetBoolValue(section_haxValues.c_str(), "hide_hud", loop_hide_hud);
	ini.SetBoolValue(section_haxValues.c_str(), "show_full_hud", loop_showFullHud);
	ini.SetBoolValue(section_haxValues.c_str(), "manual_respawn", _ManualRespawn_::g_manualRespawn.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "freecam", loop_no_clip);
	ini.SetBoolValue(section_haxValues.c_str(), "display_xyzh_coords", loop_XYZHcoords);
	ini.SetBoolValue(section_haxValues.c_str(), "display_fps", _FpsCounter_::bDisplayFps);
	ini.SetBoolValue(section_haxValues.c_str(), "basic_tv_player", sub::TVChannelStuff_catind::loop_basictv);
	ini.SetBoolValue(section_haxValues.c_str(), "sync_clock", loop_sync_clock);
	ini.SetBoolValue(section_haxValues.c_str(), "pause_clock", loop_pause_clock);
	ini.SetLongValue(section_haxValues.c_str(), "pause_clock_hour", pause_clock_H);
	ini.SetLongValue(section_haxValues.c_str(), "pause_clock_minute", pause_clock_M);
	ini.SetBoolValue(section_haxValues.c_str(), "decreased_ped_population", loop_ped_population);
	ini.SetBoolValue(section_haxValues.c_str(), "decreased_veh_population", loop_vehicle_population);
	ini.SetBoolValue(section_haxValues.c_str(), "decreased_weapon_pickups", loop_clearWeaponPickups);
	ini.SetDoubleValue(section_haxValues.c_str(), "clear_area_radius", _globalClearArea_radius);
	ini.SetBoolValue(section_haxValues.c_str(), "restricted_area_access", loop_restricted_areas_access);
	ini.SetBoolValue(section_haxValues.c_str(), "fireworks_ahoy", loop_fireworksDisplay);
	ini.SetBoolValue(section_haxValues.c_str(), "emp_mode", loop_blackout_mode);
	ini.SetBoolValue(section_haxValues.c_str(), "simple_blackout_mode", loop_simple_blackout_mode);
	ini.SetBoolValue(section_haxValues.c_str(), "massacre_mode", loop_massacre_mode);
	ini.SetBoolValue(section_haxValues.c_str(), "jump_around_mode", _JumpAroundMode_::bEnabled);
	ini.SetLongValue(section_haxValues.c_str(), "frozen_radio_station", g_frozenRadioStation);
	ini.SetBoolValue(section_haxValues.c_str(), "snow_on_terrain", _SpSnow.IsSnow());
	ini.SetBoolValue(section_haxValues.c_str(), "animal_riding_mode", sub::AnimalRiding_catind::Enabled());

	ini.SetBoolValue(section_haxValues.c_str(), "forge_gun", loop_forge_gun);
	ini.SetDoubleValue(section_haxValues.c_str(), "forge_gun_shoot_force", _globalForgeGun_shootForce);
	ini.SetBoolValue(section_haxValues.c_str(), "gravity_gun", sub::GravityGun_catind::Enabled());
	ini.SetDoubleValue(section_haxValues.c_str(), "gravity_gun_shoot_force", sub::GravityGun_catind::ShootForce());
	ini.SetBoolValue(section_haxValues.c_str(), "magnet_gun", _MagnetGun_::g_magnetGun.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "teleport_gun", loop_teleport_gun);
	//ini.SetBoolValue(section_haxValues.c_str(), "kaboom_gun", loop_kaboom_gun);
	//ini.SetBoolValue(section_haxValues.c_str(), "triggerfx_gun", loop_triggerfx_gun);
	//ini.SetBoolValue(section_haxValues.c_str(), "bullet_gun", loop_bullet_gun);
	//ini.SetBoolValue(section_haxValues.c_str(), "ped_gun", loop_ped_gun);
	//ini.SetBoolValue(section_haxValues.c_str(), "object_vehicle_gun", loop_object_gun);
	ini.SetBoolValue(section_haxValues.c_str(), "light_gun", loop_light_gun);
	ini.SetBoolValue(section_haxValues.c_str(), "rope_gun", _RopeGun_::g_ropeGun.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "bullet_time", loop_bullet_time);
	ini.SetDoubleValue(section_haxValues.c_str(), "weapon_damage_multiplier", loop_weapon_damage_increase);
	ini.SetBoolValue(section_haxValues.c_str(), "explosive_bullets", loop_explosive_rounds);
	ini.SetBoolValue(section_haxValues.c_str(), "flaming_bullets", loop_flaming_rounds);
	ini.SetBoolValue(section_haxValues.c_str(), "explosive_melee", loop_explosive_melee);
	ini.SetBoolValue(section_haxValues.c_str(), "triple_bullets", loop_triple_bullets);
	ini.SetBoolValue(section_haxValues.c_str(), "self_triggerbot", loop_self_triggerbot);
	ini.SetBoolValue(section_haxValues.c_str(), "rapid_fire", loop_rapid_fire);
	ini.SetBoolValue(section_haxValues.c_str(), "soul_switch_gun", loop_soulswitch_gun);
	ini.SetBoolValue(section_haxValues.c_str(), "self_revival_gun", loop_self_resurrectionGun);
	ini.SetBoolValue(section_haxValues.c_str(), "self_delete_gun", loop_self_deleteGun);
	ini.SetBoolValue(section_haxValues.c_str(), "self_infinite_ammo_clip", bit_infinite_ammo);
	ini.SetBoolValue(section_haxValues.c_str(), "infinite_parachutes", loop_self_inf_parachutes);
	ini.SetLongValue(section_haxValues.c_str(), "auto_kill_enemies", loop_autoKillEnemies);

	ini.SetBoolValue(section_haxValues.c_str(), "laser_sight_toggle", sub::LaserSight_catind::bEnabled);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_R", sub::LaserSight_catind::_colour.R);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_G", sub::LaserSight_catind::_colour.G);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_B", sub::LaserSight_catind::_colour.B);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_A", sub::LaserSight_catind::_colour.A);

	ini.SetBoolValue(section_haxValues.c_str(), "player_refill_health_when_in_cover", loop_self_refillHealthInCover);
	ini.SetBoolValue(section_haxValues.c_str(), "player_invincibility", loop_player_invincibility);
	ini.SetBoolValue(section_haxValues.c_str(), "player_no_ragdoll", loop_player_noRagdoll);
	ini.SetBoolValue(section_haxValues.c_str(), "player_seatbelt", loop_player_seatbelt);
	ini.SetBoolValue(section_haxValues.c_str(), "player_unlimited_special_ab", loop_player_unlimSpecialAbility);
	ini.SetBoolValue(section_haxValues.c_str(), "player_auto_clean", loop_player_autoClean);
	ini.SetBoolValue(section_haxValues.c_str(), "player_super_jump", loop_super_jump);
	ini.SetBoolValue(section_haxValues.c_str(), "player_super_run", loop_super_run);
	ini.SetBoolValue(section_haxValues.c_str(), "player_superman_manual", loop_superman);
	ini.SetBoolValue(section_haxValues.c_str(), "player_superman_auto", loop_superman_auto);
	ini.SetLongValue(section_haxValues.c_str(), "player_forcefield", loop_forcefield);
	ini.SetBoolValue(section_haxValues.c_str(), "player_smash_ability", _SmashAbility_::g_smashAbility.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "player_ignored_by_everyone", loop_ignored_by_everyone);
	ini.SetBoolValue(section_haxValues.c_str(), "player_never_wanted", loop_never_wanted);
	ini.SetBoolValue(section_haxValues.c_str(), "player_burn_mode", loop_player_burn);
	//ini.SetBoolValue(section_haxValues.c_str(), "player_ghost_rider_mode", sub::GhostRiderMode_catind::g_ghostRiderMode.Enabled());
	//ini.SetBoolValue(section_haxValues.c_str(), "player_no_gravity", loop_player_noGravity);

	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_invincibility", loop_vehicle_invincibility);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_increased_mass", loop_vehicle_heavymass);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_horn_boost", loop_race_boost);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_unlim_native_boost", loop_unlimVehBoost);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_jump", loop_car_jump);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_hydraulics", loop_car_hydraulics);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_glue_to_ground", loop_super_grip);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_SuprKar_mode", loop_SuprKarMode);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_rainbow_mode", loop_car_colour_change);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_auto_fix", loop_vehicle_fixloop);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_auto_flip", loop_vehicle_fliploop);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_keep_engine_running", loop_self_engineOn);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_tow_mode", _VehicleTow_::g_vehicleTow.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_fly_mode", _VehicleFly_::g_vehicleFly.Enabled());
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_multiplat_neons", loop_multiplat_neons);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_multiplat_neons_rainbow", loop_multiplat_neons_rainbow);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_R", _global_MultiPlatNeons_Col.R);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_G", _global_MultiPlatNeons_Col.G);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_multiplat_neons_B", _global_MultiPlatNeons_Col.B);
	ini.SetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_acceleration", mult69_5);
	ini.SetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_brakes", mult69_6);
	ini.SetDoubleValue(section_haxValues.c_str(), "vehicle_multiplier_handling", mult69_7);

	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_enable_previews", _globalSpawnVehicle_drawBmps);
	ini.SetValue(section_haxValues.c_str(), "vehicle_spawner_plate_text", _globalSpawnVehicle_plateText.c_str());
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_plate_text_texter_value", _globalSpawnVehicle_plateTexter_value);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_plate_type", _globalSpawnVehicle_plateType);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_auto_sit", _globalSpawnVehicle_autoSit);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_auto_upgrade", _globalSpawnVehicle_autoUpgrade);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_invincible", _globalSpawnVehicle_invincible);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_persistent", _globalSpawnVehicle_persistent);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_delete_old", _globalSpawnVehicle_deleteOld);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_spawner_neons_on", _globalSpawnVehicle_neonToggle);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_R", _globalSpawnVehicle_neonCol.R);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_G", _globalSpawnVehicle_neonCol.G);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_neons_B", _globalSpawnVehicle_neonCol.B);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_primary_colour", _globalSpawnVehicle_PrimCol);
	ini.SetLongValue(section_haxValues.c_str(), "vehicle_spawner_secondary_colour", _globalSpawnVehicle_SecCol);
	ini.SetBoolValue(section_haxValues.c_str(), "vehicle_menyoo_customs_lsc", _globalLSC_Customs);

	ini.SetDoubleValue(section_haxValues.c_str(), "clock", sub::Clock_catind::loop_clock);
	ini.SetDoubleValue(section_haxValues.c_str(), "clock_screen_pos_x", sub::Clock_catind::_analogueClockPos.x);
	ini.SetDoubleValue(section_haxValues.c_str(), "clock_screen_pos_y", sub::Clock_catind::_analogueClockPos.y);

	ini.SetLongValue(section_haxValues.c_str(), "speedo", sub::Speedo_catind::loop_speedo);
	ini.SetBoolValue(section_haxValues.c_str(), "speedo_mph_instead_of_kmph", sub::Speedo_catind::bit_speedo_mph);
	ini.SetDoubleValue(section_haxValues.c_str(), "speedo_screen_pos_x", sub::Speedo_catind::_speedoPosition.x);
	ini.SetDoubleValue(section_haxValues.c_str(), "speedo_screen_pos_y", sub::Speedo_catind::_speedoPosition.y);
	ini.SetValue(section_haxValues.c_str(), "speedo_bg_name", sub::Speedo_catind::_currentSpeedoBg.fileName.c_str());

	ini.SaveFile((GetPathffA(Pathff::Main, true) + "menyooConfig.ini").c_str());
}

void MenuConfig::ConfigResetHaxValues()
{
	auto& ini = MenuConfig::iniFile;

	std::string section_haxValues = "hax-values";/////////

	CSimpleIniA::TNamesDepend keys;
	ini.GetAllKeys(section_haxValues.c_str(), keys);

	for (auto& key : keys)
	{
		if (std::string(ini.GetValue(section_haxValues.c_str(), key.pItem)).find(".") == std::string::npos)
			ini.SetLongValue(section_haxValues.c_str(), key.pItem, 0);
	}

	ini.SetLongValue(section_haxValues.c_str(), "frozen_radio_station", -1);

	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_R", sub::LaserSight_catind::_colour.R);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_G", sub::LaserSight_catind::_colour.G);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_B", sub::LaserSight_catind::_colour.B);
	ini.SetLongValue(section_haxValues.c_str(), "laser_sight_A", sub::LaserSight_catind::_colour.A);

	ini.SetValue(section_haxValues.c_str(), "speedo_bg_name", sub::Speedo_catind::_currentSpeedoBg.fileName.c_str());

	MenuConfig::ConfigRead();

}



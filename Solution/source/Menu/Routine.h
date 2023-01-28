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

#include <string>
#include <unordered_set>
#include <map>

#define TRUE 1
#define FALSE 0

typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed char INT8;
typedef unsigned char UINT8, BYTE;
typedef int INT, Entity, Ped, Vehicle, Player;
typedef unsigned long DWORD, Hash;
typedef float FLOAT;
typedef char *PCHAR;
typedef const char *LPCSTR;

class RgbS;
class Vector3;
class Camera;
namespace GTAmodel {
	class Model;
}
class GTAplayer;
class GTAentity;
class GTAvehicle;
class GTAped;
//class GTAprop;
namespace PTFX {
	class sFxData;
}


 //--------------------------------Threads--------------------------------------------------------

void ThreadMenyooMain();

void Thread_menu_loops2();

void TickMenyooConfig();

void TickRainbowFader();

//--------------------------------On tick--------------------------------------------------------

#pragma region variables used declare // p.s. this ain't it chief

extern INT16 bind_no_clip;

extern RgbS g_fadedRGB;

extern UINT8 pause_clock_H, pause_clock_M;
extern Vehicle g_myVeh;
extern GTAmodel::Model g_myVeh_model;
extern Hash g_myWeap;
extern PTFX::sFxData triggerfx_gun_data;
extern Hash kaboom_gun_hash, bullet_gun_hash;
extern GTAmodel::Model ped_gun_hash, object_gun_hash;
extern FLOAT current_timescale;
extern INT Static_241, Static_240, Static_242, Static_12;
extern const char* Static_239;
extern INT bit_MSPaints_RGB_mode;
extern bool kaboom_gun_invis, kaboom_gun_rand_bit, ped_gun_rand_bit, object_gun_rand_bit_o, object_gun_rand_bit_v;
extern bool bit_night_vision;
extern FLOAT mult69_0, mult_playerNoiseValue, mult_self_sweat;
extern FLOAT g_playerVerticalElongationMultiplier;
extern FLOAT loop_vehicle_damageAndDefense;
extern FLOAT loop_vehicle_slam;
extern FLOAT menu_current_timecycle_strength;
extern INT mult69_5, mult69_6, mult69_7;
extern INT16 g_frozenRadioStation;
extern bool bit_vehicle_gravity, bit_freeze_vehicle, VehicleOpsSlippyTires_bit;

extern INT ms_curr_paint_index;

// String variables used in various submenus for search, storage, etc.
extern std::string dict, dict2, dict3;

extern std::string _globalSpawnVehicle_plateText;
extern INT8 _globalSpawnVehicle_plateType, _globalSpawnVehicle_plateTexter_value;
extern RgbS _globalSpawnVehicle_neonCol;
extern bool _globalSpawnVehicle_autoSit, _globalSpawnVehicle_autoUpgrade, _globalSpawnVehicle_invincible, _globalSpawnVehicle_deleteOld, _globalSpawnVehicle_neonToggle, _globalLSC_Customs;
extern INT16 _globalSpawnVehicle_PrimCol, _globalSpawnVehicle_SecCol;
extern bool _globalSpawnVehicle_drawBmps;
extern FLOAT _globalClearArea_radius;
extern FLOAT _globalRainFXIntensity;

extern Entity g_drive_water_obj;

extern INT8 loop_spectate_player;
extern UINT8 loop_explosion_wp;

extern bool loop_multiplat_neons, loop_multiplat_neons_rainbow;
extern RgbS _global_MultiPlatNeons_Col;
extern std::vector<GTAvehicle> _global_MultiPlatNeons_List;

extern bool loop_Check_self_death_model;

extern UINT8 loop_car_jump;
extern UINT8 loop_autoKillEnemies;
extern float loop_weapon_damage_increase;

extern UINT8 loop_forcefield;
extern UINT8 loop_self_freezeWantedLevel;
extern Entity bit_infinite_ammo_enth;

extern bool loop_RainbowBoxes, loop_forge_gun, loop_player_noRagdoll, loop_player_seatbelt, loop_player_unlimSpecialAbility, loop_player_autoClean, loop_player_Walkunderwater,
loop_explosive_rounds, loop_flaming_rounds, loop_teleport_gun, loop_kaboom_gun, loop_triggerfx_gun, loop_bullet_gun, loop_ped_gun, loop_object_gun, loop_light_gun, loop_bullet_time, loop_self_triggerbot,
loop_explosive_melee, loop_super_jump, loop_self_refillHealthInCover, loop_player_invincibility, loop_no_clip, loop_no_clip_toggle, loop_super_run,
loop_XYZHcoords, loop_ignored_by_everyone, loop_never_wanted, loop_superman, loop_superman_auto,
loop_vehicle_population, loop_ped_population, loop_clearWeaponPickups, loop_drive_on_water, loop_massacre_mode,
loop_player_burn, loop_vehicle_invincibility, loop_vehicle_heavymass, loop_race_boost,
loop_car_hydraulics, loop_super_grip, loop_SuprKarMode, loop_unlimVehBoost,

loop_vehweap_lines, loop_vehicle_RPG, loop_vehicle_fireworks, loop_vehicle_guns, loop_vehicle_snowballs, loop_vehicle_balls, loop_vehicle_waterhyd, loop_vehicle_laser_green, loop_vehicle_flameleak,
loop_vehicle_laser_red, loop_vehicle_turrets_valkyrie, loop_vehicle_flaregun, loop_vehicle_heavysnip, loop_vehicle_tazerweap, loop_vehicle_molotovweap, loop_vehicle_combatpdw,

loop_car_colour_change, loop_vehicle_invisibility, loop_self_engineOn, loop_hide_hud, loop_showFullHud,
loop_pause_clock, loop_sync_clock, loop_triple_bullets, loop_rapid_fire, loop_self_resurrectionGun, loop_soulswitch_gun, loop_self_deleteGun, loop_vehicle_fixloop, loop_vehicle_fliploop,
loop_blackout_mode, loop_simple_blackout_mode, loop_restricted_areas_access, loop_HVSnipers, loop_vehicle_disableSiren, loop_fireworksDisplay,
bit_infinite_ammo, loop_self_inf_parachutes;

extern Entity targ_slot_entity;
extern bool targ_entity_locked;

extern bool bit_grav_gun_disabled;

extern float forge_dist, _globalForgeGun_prec, _globalForgeGun_shootForce;
extern bool ObjSpawn_forge_assistance;

#pragma endregion

#pragma region methods used declare // p.s. this ain't it chief

// Game - HUD
void display_full_hud_this_frame(bool bEnabled);

// World - Entities
void update_nearby_stuff_arrays_tick();

// Game - HUD (teleport to wp command) - Doesn't work in SP?
void SetPauseMenuTeleToWpCommand();

// PTFX
void set_Ptfxlop_tick();

// Time
void set_sync_clock_time();

// Misc - massacre mode
void set_massacre_mode_tick();

// Misc
void set_blackoutEmp_mode();
void set_blackout_mode();

// Playerped - ability
void set_self_nearby_peds_calm();
void network_set_everyone_ignore_player(Player player);

// World
void set_explosion_at_coords(GTAentity entity, Vector3 pos, UINT8 type, float radius, float camshake, bool sound, bool invis, GTAentity owner);
// World-Misc
void start_fireworks_at_coord(const Vector3& pos, const Vector3& rot, float scale);

// Weapon
void set_target_into_slot();
void set_player_triggerbot(GTAplayer player);
void set_rapid_fire();
void set_soulswitch_gun();
void set_self_deleteGun();
void set_self_resurrectionGun();
void set_HVSnipers(bool set);
// Weapon - funguns - onshoot
void set_teleport_gun();
void set_bullet_gun();
void set_ped_gun();
void set_object_gun();
void set_light_gun();
void set_triple_bullets();
// Forge gun
void set_forge_gun_dist(float& distance);
inline void set_forge_gun_rot_hotkeys();
void set_forge_gun();
// Weapon - bullet hit/raycast
void set_explosion_at_bullet_hit(Ped ped, Hash type, bool invisible);
void set_triggerfx_at_bullet_hit(Ped ped, const std::string& fxAsset, const std::string& fxName, const Vector3& Rot, float scale);

// Spooner/ped
void set_become_ped(GTAped ped);

// Ped - proofs?
void set_ped_invincible_on(Ped ped);
void set_ped_invincible_off(Ped ped);
void set_ped_no_ragdoll_on(Ped ped);
void set_ped_no_ragdoll_off(Ped ped);
void set_ped_seatbelt_on(Ped ped);
void set_ped_seatbelt_off(Ped ped);

// Misc - FreeCam
extern bool bit_noclip_already_invis, bit_noclip_already_collis, bit_noclip_show_help;
extern Camera g_cam_noClip;
void set_no_clip_off1();
void set_no_clip_off2();
void set_no_clip();

// Playerped - ability
void set_local_button_super_run();

// Playerped - ability
void set_self_refill_health_when_in_cover();

// Game - HUD (Display coordinates)
void xyzh_drawfloat(float text, float x_coord, float y_coord);
void xyzh_();

// Playerped - ability
void set_local_superman_MANUAL();
void set_ped_superman_AUTO(Ped ped);

// Vehicle - ability
void set_vehicle_nos_ptfx_this_frame(GTAvehicle vehicle);

// Vehicle - ability
void set_SuprKarMode_self();
void set_local_car_jump();
void set_local_car_hydraulics();
void set_local_forcefield();

// Vehicle - ability
extern float _global_MultiPlatNeons_Intensity;
void draw_vehicle_ambientlight_neons(const GTAvehicle& vehicle, const RgbS& colour);
void set_multiplat_neons();

// Vehicle - ability
void drive_on_water(GTAped ped, Entity& waterobject);

// Playerped - ability
void set_ped_burn_mode(GTAped ped, bool enable);

// Vehicle - ability - multiplier
//inline void set_Handling_Mult69_7();

// Vehicle - ability - invincibility
void set_vehicle_invincible_on(Vehicle vehicle);
void set_vehicle_invincible_off(Vehicle vehicle);

// Vehicle - ability
void set_vehicle_fliploop(GTAvehicle vehicle);

// Vehicle - ability
void set_vehicle_rainbow_mode_tick(GTAvehicle vehicle, bool useFader);
void set_vehicle_heavy_mass_tick(GTAvehicle vehicle);

// Vehicle weapons
//....

// Vehicle - ability - boost
void set_self_vehicle_boost();
// Vehicle - ability - native boost
//inline void set_self_vehicle_nativeboost()

// Vehicle - ability (personal vehicle)
extern GTAvehicle PV_sub_vehicleid;
void set_PVops_vehicle_text_world2Screen();

// Vehicle - ability (multiplier on tick)
extern std::map<Vehicle, float> g_multList_rpm;
extern std::map<Vehicle, float> g_multList_torque;
extern std::map<Vehicle, float> g_multList_maxSpeed;
extern std::map<Vehicle, float> g_multList_headlights;
inline void vehicle_torque_mult_tick();
inline void vehicle_maxSpeed_mult_tick();
// Vehicle - getter/setter - engine sound
extern std::map<Vehicle, std::string> g_vehList_engSound;
std::string get_vehicle_engine_sound_name(const GTAvehicle& vehicle);
void set_vehicle_engine_sound_name(GTAvehicle vehicle, const std::string& name);
// Vehicle - getter/setter - removeTyres
extern std::unordered_set<Vehicle> g_vehWheelsInvisForRussian;
bool are_vehicle_wheels_invisible(const GTAvehicle& vehicle);
void set_vehicle_wheels_invisible(GTAvehicle vehicle, bool enable);

// Ped - ability (multiplier lists)
extern std::map<Ped, std::string> g_pedList_movGrp;
extern std::map<Ped, std::string> g_pedList_wmovGrp;
// Spooner/ped - facial mood - getter/setter
extern std::map<Ped, std::string> g_pedList_facialMood;
extern std::string get_ped_facial_mood(GTAentity ped);
void set_ped_facial_mood(GTAentity ped, const std::string& animName);
void clear_ped_facial_mood(GTAentity ped);



#pragma endregion



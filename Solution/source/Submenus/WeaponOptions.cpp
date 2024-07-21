/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "WeaponOptions.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\WeaponIndivs.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\World.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\Model.h"
#include "..\Util\ExePath.h"
#include "..\Util\StringManip.h"
#include "..\Util\keyboard.h"
#include "..\Menu\FolderPreviewBmps.h"
#include "..\Natives\types.h" //RGBA
#include "..\Scripting\Raycast.h"
#include "..\Scripting\ModelNames.h"

#include "..\Misc\RopeGun.h"
#include "..\Misc\MagnetGun.h"
#include "..\Misc\FlameThrower.h"
#include "..\Misc\Gta2Cam.h"

#include "PtfxSubs.h"
#include "VehicleSpawner.h"
#include "Settings.h"

#include <Shlwapi.h> //PathIsDirectory
#pragma comment(lib, "Shlwapi.lib")
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <pugixml\src\pugixml.hpp>
#include <dirent\include\dirent.h>

namespace sub
{
	void Weaponops()
	{
		dict2.clear();
		dict3.clear();

		Static_241 = PLAYER_PED_ID();
		Static_240 = PLAYER_ID();

		std::stringstream wdmg_ss;
		wdmg_ss << std::fixed << std::setprecision(2) << (loop_weapon_damage_increase / 0.72f);
		wdmg_ss << "x";

		bool WeaponopsRapidFireOn_ = 0, WeaponopsBulletTimeOff_ = 0,
			bTeleportGunOn = 0,
			wdmg_jump = 0, wdmg_plus = 0, wdmg_minus = 0,
			Weaponops_soulswitch_on = 0, WeaponopsInfiniteAmmoOff_ = 0, WeaponopsInfiniteAmmoOn_ = 0,
			bSelfDeleteGunOn = 0, bSelfResurrectionGunOn = 0,
			ped_weaps_all = 0, ped_weaps_dlc = 0, ped_weaps_garbage = 0, ped_weaps_handcuffs = 0, ped_weaps_digiscanner = 0, ped_weaps_briefcase = 0, bGiveMaxAmmoPressed = 0, WeaponopsRemoveWeaps_ = 0;

		AddTitle("Weapon Options");
		AddOption("Individual Weapons & Customisation", null, nullFunc, SUB::WEAPONOPS_INDIVS_CATEGORIES);
		AddOption("Loadouts", null, nullFunc, SUB::WEAPONOPS_LOADOUTS);
		//AddOption("Set A Permanent Weapon", null, nullFunc, SUB::WEAPONOPS_FORCEAWEAPON_LIST);
		AddOption("Give All Weapons", ped_weaps_all);
		//	AddOption("Give Garbage Bag", ped_weaps_garbage);
		//	AddOption("Give Handcuffs", ped_weaps_handcuffs);
		AddOption("Give Digiscanner", ped_weaps_digiscanner);
		AddOption("Give Briefcase", ped_weaps_briefcase);
		AddOption("Give Max Ammo", bGiveMaxAmmoPressed);
		AddOption("Remove All Weapons", WeaponopsRemoveWeaps_);
		AddToggle("Infinite Parachutes", loop_self_inf_parachutes);
		AddToggle("Infinite Ammo In Clip", bit_infinite_ammo, WeaponopsInfiniteAmmoOn_, WeaponopsInfiniteAmmoOff_);
		AddToggle("Explosive Melee", loop_explosive_melee);
		AddToggle("Explosive Ammo", loop_explosive_rounds);
		AddToggle("Tenfold Bullets", loop_triple_bullets);
		AddToggle("Flaming Bullets", loop_flaming_rounds);
		AddTexter("Weapon Damage", 0, std::vector<std::string>{wdmg_ss.str()}, wdmg_jump, wdmg_plus, wdmg_minus);
		AddToggle("Bullet Time", loop_bullet_time, null, WeaponopsBulletTimeOff_);
		AddToggle("Triggerbot", loop_self_triggerbot);
		AddToggle("Rapid Fire", loop_rapid_fire, WeaponopsRapidFireOn_);
		AddToggle("Soul-Switch Gun (SP)", loop_soulswitch_gun, Weaponops_soulswitch_on);
		AddLocal("Rope Gun (Glitchy)", _RopeGun_::g_ropeGun.Enabled(), _RopeGun_::ToggleOnOff, _RopeGun_::ToggleOnOff);
		AddLocal("Magnet Gun", _MagnetGun_::g_magnetGun.Enabled(), _MagnetGun_::ToggleOnOff, _MagnetGun_::ToggleOnOff);
		AddLocal("Flamethrower " + get_weapon_label(_FlameThrower_::_whash, true), _FlameThrower_::IsPlayerAdded(Static_240), _FlameThrower_::AddSelf, _FlameThrower_::RemoveSelf);
		AddToggle("Teleport Gun", loop_teleport_gun, bTeleportGunOn);
		AddToggle("Ped Revival Gun", loop_self_resurrectionGun, bSelfResurrectionGunOn);
		AddToggle("Entity Removal Gun", loop_self_deleteGun, bSelfDeleteGunOn);
		AddToggle("Light Gun", loop_light_gun);
		AddOption("Laser Sight", null, nullFunc, SUB::WEAPONOPS_LASERSIGHT);
		AddOption("Forge Gun", null, nullFunc, SUB::FORGEGUN);
		AddOption("Gravity Gun", null, nullFunc, SUB::GRAVITYGUN);
		AddOption("TriggerFX Gun", null, nullFunc, SUB::TRIGGERFXGUN);
		AddOption("Kaboom Gun", null, nullFunc, SUB::KABOOMGUN);
		AddOption("Bullet Gun", null, nullFunc, SUB::BULLETGUN);
		AddOption("Ped Gun", null, nullFunc, SUB::PEDGUN);
		AddOption("Object & Vehicle Gun", null, nullFunc, SUB::OBJECTGUN);


		if (WeaponopsRapidFireOn_) { Game::Print::PrintBottomLeft("~b~Note:~s~ You cannot use other Menyoo weapon mods with this on."); return; }
		if (Weaponops_soulswitch_on) { if (NETWORK_IS_IN_SESSION()) loop_soulswitch_gun = false; else Game::Print::PrintBottomLeft("Shoot ~b~scrubs~s~ with the ~b~combat pistol~s~ for hax!"); return; }
		if (bTeleportGunOn) { Game::Print::PrintBottomLeft("Use the ~b~Heavy pistol~s~ to teleport to places."); return; }
		if (bSelfDeleteGunOn) { Game::Print::PrintBottomLeft("Shoot ~b~anything*~s~ with the ~b~SNS pistol~s~ to delete it."); return; }
		if (bSelfResurrectionGunOn) { Game::Print::PrintBottomLeft("Shoot ~b~dead people~s~ with the ~b~stun gun~s~ to bring them back from the other side."); return; }

		if (ped_weaps_all) { give_all_weapons_to_ped(Static_241); WAIT(15); give_ped_max_ammo(Static_241); return; }
		if (bGiveMaxAmmoPressed) { give_ped_max_ammo(Static_241); return; }
		if (WeaponopsRemoveWeaps_) { REMOVE_ALL_PED_WEAPONS(Static_241, 1); return; }


		if (ped_weaps_garbage) { GIVE_WEAPON_TO_PED(Static_241, WEAPON_GARBAGEBAG, 1, true, true); SET_CURRENT_PED_WEAPON(Static_241, WEAPON_GARBAGEBAG, true); SET_PED_CURRENT_WEAPON_VISIBLE(Static_241, 1, 1, 1, 0); return; }
		if (ped_weaps_handcuffs) { GIVE_WEAPON_TO_PED(Static_241, WEAPON_HANDCUFFS, 1, true, true); SET_CURRENT_PED_WEAPON(Static_241, WEAPON_HANDCUFFS, true); SET_PED_CURRENT_WEAPON_VISIBLE(Static_241, 1, 1, 1, 0); return; }
		if (ped_weaps_digiscanner) { GIVE_WEAPON_TO_PED(Static_241, WEAPON_DIGISCANNER, 1, true, true); SET_CURRENT_PED_WEAPON(Static_241, WEAPON_DIGISCANNER, true); SET_PED_CURRENT_WEAPON_VISIBLE(Static_241, 1, 1, 1, 0); return; }
		if (ped_weaps_briefcase) { GIVE_WEAPON_TO_PED(Static_241, WEAPON_BRIEFCASE, 1, true, true); SET_CURRENT_PED_WEAPON(Static_241, WEAPON_BRIEFCASE, true); SET_PED_CURRENT_WEAPON_VISIBLE(Static_241, 1, 1, 1, 0); return; }

		if (wdmg_jump)
		{
			loop_weapon_damage_increase = (loop_weapon_damage_increase == 1.0f ? 100.0f : 1.0f) * 0.72f;
			SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase);
			//SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Static_240, loop_weapon_damage_increase);
			SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase, true);
			//SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Static_240, loop_weapon_damage_increase);
		}
		if (wdmg_plus)
		{
			if (loop_weapon_damage_increase / 0.72f < 100.0f) loop_weapon_damage_increase += (0.1f * 0.72f);
			SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase);
			SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase, true);
		}
		if (wdmg_minus)
		{
			if (loop_weapon_damage_increase / 0.72f > -100.0f) loop_weapon_damage_increase -= (0.1f * 0.72f);
			SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase);
			SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Static_240, loop_weapon_damage_increase, true);
		}

		if (WeaponopsBulletTimeOff_) { SET_TIME_SCALE(current_timescale); return; }

		if (WeaponopsInfiniteAmmoOn_) {
			give_ped_max_ammo(Static_241);
			SET_PED_INFINITE_AMMO_CLIP(Static_241, true);
			return;
		}
		if (WeaponopsInfiniteAmmoOff_) {
			SET_PED_INFINITE_AMMO_CLIP(Static_241, false);
			return;
		}
		/*if (WeaponopsInfiniteAmmo_){
		if (!bit_infinite_ammo)
		{
		SET_PED_INFINITE_AMMO_CLIP(Static_241, 1);
		bit_infinite_ammo = true;
		}
		else
		{
		SET_PED_INFINITE_AMMO_CLIP(Static_241, 0);
		bit_infinite_ammo = false;
		}
		return;
		}*/


		//if (laserSightRendering_off) ENABLE_LASER_SIGHT_RENDERING(0);

	}

	void ForgeGun_()
	{
		bool Weaponops_forgeGun_on = 0, prec_plus = 0, prec_minus = 0,
			setForce_custom = 0, setForce_plus = 0, setForce_minus = 0;

		AddTitle("Forge Gun");
		AddToggle("Gun Toggle", loop_forge_gun, Weaponops_forgeGun_on);
		AddToggle("Freeze Pickups In Place", ObjSpawn_forge_assistance);
		AddNumber("Rotation Precision", _globalForgeGun_prec, 4, null, prec_plus, prec_minus);
		AddNumber("Launch Force", _globalForgeGun_shootForce, 0, setForce_custom, setForce_plus, setForce_minus);


		if (setForce_custom) {
			std::string inputStr = Game::InputBox("", 11U, "", std::to_string(_globalForgeGun_shootForce));
			if (inputStr.length() > 0)
			{
				try { _globalForgeGun_shootForce = stof(inputStr); }
				catch (...) { Game::Print::PrintError_InvalidInput(); }
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 10U, std::to_string(_globalForgeGun_shootForce));
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_globalForgeGun_shootForce);
		}
		if (setForce_plus) { if (_globalForgeGun_shootForce < FLT_MAX) _globalForgeGun_shootForce++; return; }
		if (setForce_minus) { if (_globalForgeGun_shootForce > 0) _globalForgeGun_shootForce--; return; }

		if (prec_plus) {
			if (_globalForgeGun_prec < 10.0f) _globalForgeGun_prec *= 10;
			return;
		}
		if (prec_minus) {
			if (_globalForgeGun_prec > 0.0001) _globalForgeGun_prec /= 10;
			return;
		}

		if (Weaponops_forgeGun_on) {
			Game::Print::PrintBottomLeft("Use the ~b~pistol~s~ for hax.");
			if (!Menu::bit_controller)
			{
				Game::Print::PrintBottomLeft("~b~Mouse Scroll~s~ for distance.");
				Game::Print::PrintBottomLeft(oss_ << "~b~ [ ~s~& ~b~ ] ~s~for pitch." << " \n"
					<< "~b~ ; ~s~& ~b~ ' ~s~for roll." << " \n"
					<< "~b~ , ~s~& ~b~ . ~s~for yaw.");
			}
			else
			{
				Game::Print::PrintBottomLeft("~b~RS~s~ & ~b~LS~s~ for distance.");
				Game::Print::PrintBottomLeft(oss_ << "~b~Up~s~ & ~b~Down~s~ for pitch." << " \n"
					<< "~b~Right~s~ & ~b~Left~s~ for roll." << " \n"
					<< "~b~RB~s~ & ~b~LB~s~ for yaw.");


			}
			Game::Print::PrintBottomLeft("~b~Shoot~s~ for launch.");
			return;
		}


	}

	namespace GravityGun_catind
	{
		class GravityGun
		{
		private:
			const Hash _whash = WEAPON_MARKSMANPISTOL;
			bool bEnabled = false;
			bool bGunActive = true;
			bool bMultipleEntities = true;
			float distanceFromCam = 0;
			float shootForce = 69.0f;
			EntityType typeToPickUp = EntityType::ALL;
			std::set<GTAentity> entityArray;
		public:
			GravityGun()
			{
			}
			bool& Enabled()
			{
				return bEnabled;
			}
			const Hash& WHASH()
			{
				return _whash;
			}
			bool& MultipleEntities()
			{
				return bMultipleEntities;
			}
			float& ShootForce()
			{
				return shootForce;
			}
			EntityType& TypeToPickUp()
			{
				return typeToPickUp;
			}

			void Tick()
			{
				if (bEnabled)
				{
					DoGravityGunTick();
				}
			}
			inline void DoGravityGunTick()
			{
				GTAplayer player = PLAYER_ID();
				GTAped ped = PLAYER_PED_ID();

				if (g_myWeap == _whash && (player.IsFreeAiming() || player.IsTargetingAnything()))
				{
					if (bGunActive && StoreEntities())
					{
						Vector3 camPos = GameplayCamera::Position_get();
						GTAentity firstEntity = *std::next(entityArray.begin(), 0);

						if (distanceFromCam == 0) distanceFromCam = camPos.DistanceTo(firstEntity.Position_get());

						set_forge_gun_dist(distanceFromCam); // Use buttons to change the hold distance value

						Vector3 targetPos = camPos + (GameplayCamera::Direction_get() * distanceFromCam);

						if (entityArray.size() == 1)
						{
							GTAentity entity = *entityArray.begin();
							entity.RequestControlOnce();
							//entity.Oscillate(targetPos, 0.38729833f, 0.075f);
							entity.Oscillate(targetPos, 0.395f, 0.1f);
						}
						else
						{
							for (GTAentity entity : entityArray)
							{
								entity.RequestControlOnce();
								entity.Oscillate(targetPos, 0.5f, 0.3f);
							}
						}

						if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK))
						{
							PLAY_SOUND_FROM_ENTITY(-1, "Chopper_Destroyed", ped.Handle(), "FBI_HEIST_FIGHT_CHOPPER_SOUNDS", 0, 0);
							//PTFX::trigger_ptfx_1("scr_carsteal4", "scr_carsteal4_wheel_burnout", 0, entityArray.front().Position_get(), Vector3(), 0.66f);

							Vector3 force = GameplayCamera::Direction_get() * shootForce;

							for (GTAentity entity : entityArray)
							{
								entity.ApplyForce(force);
							}

							entityArray.clear();
							distanceFromCam = 0;
							bGunActive = false;
						}
					}
				}
				else
				{
					if (!entityArray.empty())
						entityArray.clear();
					distanceFromCam = 0;
					bGunActive = true;
				}

			}

			bool StoreEntities()
			{
				GTAplayer player = PLAYER_ID();
				GTAentity myPed = PLAYER_PED_ID();
				EntityType type;

				if (entityArray.empty())
				{
					GTAentity aimedEntity = World::EntityFromAimCamRay();
					if (!aimedEntity.Handle())
						return false;

					type = (EntityType)aimedEntity.Type();
					if (typeToPickUp == EntityType::ALL || typeToPickUp == type)
					{
						aimedEntity.FreezePosition(false);
						entityArray.insert(aimedEntity.Handle());
					}
					else
						return false;
				}

				if (bMultipleEntities)
				{
					for (GTAentity outside : _worldEntities)
					{
						if (outside.Equals(myPed))
							continue;
						for (GTAentity inside : entityArray)
						{
							if (inside.Equals(outside))
								continue;

							type = (EntityType)outside.Type();

							if (inside.IsTouching(outside) && (typeToPickUp == EntityType::ALL || typeToPickUp == type))
							{
								outside.FreezePosition(false);
								entityArray.insert(outside);
								break;
							}
						}
					}
				}

				return true;
			}
		};
		GravityGun g_gravityGun;

		void Tick()
		{
			g_gravityGun.Tick();
		}
		bool& Enabled()
		{
			return g_gravityGun.Enabled();
		}
		float& ShootForce()
		{
			return g_gravityGun.ShootForce();
		}

		void Sub_GravityGun()
		{
			bool printInstructions = 0, setForce_custom = 0, setForce_plus = 0, setForce_minus = 0;
			bool type_plus = 0, type_minus = 0;

			auto& shootForce = g_gravityGun.ShootForce();
			auto& type = *reinterpret_cast<UINT8*>(&g_gravityGun.TypeToPickUp());

			static const std::vector<std::string> str_entitytypes{ "All", "Peds", "Vehicles", "Objects" };

			AddTitle("Gravity Gun");
			AddToggle("Toggle", g_gravityGun.Enabled(), printInstructions);
			AddToggle("Multiple Pick Ups", g_gravityGun.MultipleEntities());
			AddTexter("Pick Up Type", type, str_entitytypes, null, type_plus, type_minus);
			AddNumber("Launch Force", shootForce, 0, setForce_custom, setForce_plus, setForce_minus);

			if (printInstructions) {
				Game::Print::PrintBottomLeft("Use the ~b~" + get_weapon_label(g_gravityGun.WHASH(), true) + "~s~ for hax.");
				Game::Print::PrintBottomLeft((std::string)"Use ~b~" + (Menu::bit_controller ? "RS/LS" : "mouse scroll") + "~s~ to change the hold distance.");
				Game::Print::PrintBottomLeft("Shoot to launch.");
				return;
			}

			if (setForce_custom) {
				std::string inputStr = Game::InputBox("", 11U, "", std::to_string(shootForce));
				if (inputStr.length() > 0)
				{
					try { shootForce = stof(inputStr); }
					catch (...) { Game::Print::PrintError_InvalidInput(); }
				}
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 10U, std::to_string(shootForce));
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&shootForce);
			}
			if (setForce_plus) { if (shootForce < FLT_MAX) shootForce++; return; }
			if (setForce_minus) { if (shootForce > 0) shootForce--; return; }

			if (type_plus) { if (type < str_entitytypes.size() - 1) type++; return; }
			if (type_minus) { if (type > 0) type--; return; }

		}

	}

	namespace TriggerFxGun_catind
	{
		void __AddOption_GunFx(const sub::Ptfx_catind::PtfxS& fx)
		{
			bool pressed = false;
			AddTickol(fx.name, (triggerfx_gun_data.asset == fx.asset && triggerfx_gun_data.effect == fx.fx), pressed, pressed, TICKOL::TICK); if (pressed)
			{
				triggerfx_gun_data.asset = fx.asset;
				triggerfx_gun_data.effect = fx.fx;
			}
		}

		void Sub_GunMain()
		{
			AddTitle("TriggerFX Gun");

			AddToggle("Gun Toggle", loop_triggerfx_gun);
			AddOption("Select FX", null, nullFunc, SUB::PTFXSUB);
		}
	}

	void AddkgunOption_(const std::string& text, Hash newHash, bool *extra_option_code, bool gxt)
	{
		bool pressed = false;
		AddTickol(text, (kaboom_gun_hash == newHash), pressed, pressed, TICKOL::TICK, TICKOL::NONE, gxt); if (pressed)
		{
			if (newHash > 70)
				Model(newHash).Load();
			kaboom_gun_hash = newHash;

			if (extra_option_code != nullptr)
				*extra_option_code = true;
		}
	}
	void KaboomGun_()
	{
		bool KaboomGun_Input = 0;
		bool bAmIOnline = NETWORK_IS_IN_SESSION() != 0;

		AddTitle("Kaboom Gun");
		AddToggle("Gun Toggle", loop_kaboom_gun);
		AddToggle("Invisibility Toggle", kaboom_gun_invis);
		AddToggle("Random Toggle", kaboom_gun_rand_bit);
		AddkgunOption_("Molotov", 3);
		AddkgunOption_("Steam", 11);
		AddkgunOption_("Flame", 12);
		AddkgunOption_("Water Hydrant", 13);
		AddkgunOption_("Flare", 22);
		AddkgunOption_("Huge", 29);
		AddkgunOption_("SuperFlame", 30);
		AddkgunOption_("Firework", 38);
		AddkgunOption_("Snowball", 39);
		AddkgunOption_("Valkyrie Cannon", 40);
		AddkgunOption_("Monkey", 3268439891);
		AddkgunOption_("Mani", 3367706194);
		AddkgunOption_("Zombie", 2890614022);
		AddkgunOption_("Pogo", 3696858125);
		AddkgunOption_("Police Bus", 2287941233);
		AddkgunOption_("Slamvan", 833469436);
		AddkgunOption_("Fixter", 3458454463);
		AddOption("All Vehicles", null, nullFunc, SUB::LIST_VEHICLECATS);
		AddOption("~b~Input~s~ Model", KaboomGun_Input);

		if (KaboomGun_Input)
		{
			std::string inputStr = Game::InputBox("", 64U, "Enter vehicle model name:");
			if (inputStr.length() > 0)
			{
				Model model(inputStr);
				if (model.IsInCdImage())
				{
					kaboom_gun_hash = model.hash;
					model.Load();
				}
				else Game::Print::PrintError_InvalidModel();
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::KaboomGunHash, std::string(), 64U, "Enter vehicle model name:");
		}

	}

	void AddbgunOption_(const std::string& text, Hash hash, bool *extra_option_code)
	{
		bool pressed = false;
		AddTickol(text, (bullet_gun_hash == hash), pressed, pressed); if (pressed)
		{
			Hash currentWeapon;
			BOOL bCurrentWeapon = GET_CURRENT_PED_WEAPON(Static_241, &currentWeapon, 1);

			if (!HAS_WEAPON_ASSET_LOADED(hash))
				REQUEST_WEAPON_ASSET(hash, 31, 0);
			GIVE_WEAPON_TO_PED(Static_241, hash, 120, 1, 1);

			if (bCurrentWeapon)
				SET_CURRENT_PED_WEAPON(Static_241, currentWeapon, true);

			bullet_gun_hash = hash;

			if (extra_option_code != nullptr)
				*extra_option_code = true;
		}
	}
	void BulletGun_()
	{

		AddTitle("Bullet Gun");
		AddToggle("Gun Toggle", loop_bullet_gun);
		AddbgunOption_("Green Laser", VEHICLE_WEAPON_PLAYER_LASER);
		AddbgunOption_("Red Laser", VEHICLE_WEAPON_ENEMY_LASER);
		AddbgunOption_("Insurgent Turret", VEHICLE_WEAPON_TURRET_INSURGENT);
		AddbgunOption_("Technical Turret", VEHICLE_WEAPON_TURRET_TECHNICAL);
		AddbgunOption_("Valkyrie Turret", VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE);
		//	AddbgunOption_("Savage Rocket", 1638077257);
		AddbgunOption_("Airstrike Rocket", WEAPON_AIRSTRIKE_ROCKET);
		AddbgunOption_("Tazer", WEAPON_STUNGUN);
		AddbgunOption_("Firework", WEAPON_FIREWORK);
		AddbgunOption_("Snowball", WEAPON_SNOWBALL);
		AddbgunOption_("Ball", WEAPON_BALL);
		AddbgunOption_("Flare", WEAPON_FLAREGUN);
		AddbgunOption_("Flare 2", WEAPON_FLARE);
		//AddbgunOption_("Petrol", WEAPON_PETROLCAN);
		//AddbgunOption_("Garbage Bag", VEHICLE_WEAPON_PLAYER_SAVAGE);


	}

	void AddpgunOption_(const std::string& text, GTAmodel::Model newModel, bool *extra_option_code)
	{
		bool pressed = false;
		AddTickol(text, (ped_gun_hash == newModel), pressed, pressed); if (pressed)
		{
			if (newModel.IsInCdImage())
			{
				ped_gun_rand_bit = false;

				Model oldModel = ped_gun_hash;

				if (oldModel.IsLoaded())
					oldModel.Unload();
				if (!newModel.IsLoaded())
					newModel.Load();

				ped_gun_hash = newModel;
			}
			if (extra_option_code != nullptr)
				*extra_option_code = true;
		}
	}
	void PedGun_()
	{
		bool PedGun_Input = 0;

		AddTitle("Ped Gun");
		AddToggle("Gun Toggle", loop_ped_gun);
		AddToggle("Random Toggle", ped_gun_rand_bit);
		AddOption("All Peds", null, nullFunc, SUB::PEDGUN_ALLPEDS);
		AddpgunOption_("Pogo", 3696858125);
		AddpgunOption_("Mime", 1021093698);
		AddpgunOption_("Mani", 3367706194);
		AddpgunOption_("Imponent Rage", 880829941);
		AddpgunOption_("Lester", 1302784073);
		AddpgunOption_("Fattie", 3050275044);
		AddpgunOption_("Cop", 368603149);
		AddpgunOption_("Pilot", 2872052743);
		AddpgunOption_("Tracy", 3728026165);
		AddpgunOption_("Jimmy", 1459905209);
		AddpgunOption_("Chimp", 2825402133);
		AddpgunOption_("Monkey", 3268439891);
		AddpgunOption_("Hen", 1794449327);
		AddpgunOption_("Seagull", 3549666813);
		AddpgunOption_("Shark", 113504370);
		AddpgunOption_("Fish", 802685111);
		AddpgunOption_("Cow", 4244282910);
		AddpgunOption_("Mountain Lion", 307287994);
		AddpgunOption_("Husky", 1318032802);
		AddpgunOption_("Chop", 351016938);
		AddOption("~b~Input~s~ Model", PedGun_Input);

		if (PedGun_Input)
		{
			std::string inputStr = Game::InputBox("", 64U, "Enter ped model name:");
			if (inputStr.length() > 0)
			{
				Model model(inputStr);
				if (model.IsInCdImage())
				{
					ped_gun_hash = model;
					model.Load();
				}
				else Game::Print::PrintError_InvalidModel();
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::PedGunHash, std::string(), 64U, "Enter ped model name:");
		}

	}
	void PedGun_AllPeds()
	{
		AddTitle("All Peds");
		AddOption("Favourites", null, nullFunc, SUB::MODELCHANGER_FAVOURITES);
		AddOption("Player", null, nullFunc, SUB::MODELCHANGER_PLAYER);
		AddOption("Animals", null, nullFunc, SUB::MODELCHANGER_ANIMAL);
		AddOption("Ambient Females", null, nullFunc, SUB::MODELCHANGER_AMBFEMALES);
		AddOption("Ambient Males", null, nullFunc, SUB::MODELCHANGER_AMBMALES);
		AddOption("Cutscene Models", null, nullFunc, SUB::MODELCHANGER_CS);
		AddOption("Gang Females", null, nullFunc, SUB::MODELCHANGER_GANGFEMALES);
		AddOption("Gang Males", null, nullFunc, SUB::MODELCHANGER_GANGMALES);
		AddOption("Story Models", null, nullFunc, SUB::MODELCHANGER_STORY);
		AddOption("Multiplayer Models", null, nullFunc, SUB::MODELCHANGER_MP);
		AddOption("Scenario Females", null, nullFunc, SUB::MODELCHANGER_SCENARIOFEMALES);
		AddOption("Scenario Males", null, nullFunc, SUB::MODELCHANGER_SCENARIOMALES);
		AddOption("Story Scenario Females", null, nullFunc, SUB::MODELCHANGER_ST_SCENARIOFEMALES);
		AddOption("Story Scenario Males", null, nullFunc, SUB::MODELCHANGER_ST_SCENARIOMALES);
		AddOption("Others", null, nullFunc, SUB::MODELCHANGER_OTHERS);
	}

	void AddogunOption_(const std::string& text, GTAmodel::Model newModel, bool *extra_option_code, bool gxt)
	{
		bool pressed = false;
		AddTickol(text, (object_gun_hash == newModel.hash), pressed, pressed, TICKOL::TICK, TICKOL::NONE, gxt); if (pressed)
		{
			if (newModel.IsInCdImage())
			{
				object_gun_rand_bit_o = false;
				object_gun_rand_bit_v = false;

				Model oldModel = object_gun_hash;

				if (oldModel.IsLoaded())
					oldModel.Unload();
				if (!newModel.IsLoaded())
					newModel.Load();

				object_gun_hash = newModel.hash;
			}
			if (extra_option_code != nullptr)
				*extra_option_code = true;
		}
	}
	void ObjectGun_()
	{
		bool bObjectGun_Input = 0;
		bool clearSearchStr = 0;

		AddTitle("Object & Vehicle Gun");
		AddToggle("Gun Toggle", loop_object_gun);
		//AddToggle("Random Objects", object_gun_rand_bit_o);
		//AddToggle("Random Vehicles", object_gun_rand_bit_v);
		AddOption("All Objects", clearSearchStr, nullFunc, SUB::OBJECTSPAWNER_OBJS); if (clearSearchStr)
			dict.clear();
		AddOption("All Vehicles", null, nullFunc, SUB::LIST_VEHICLECATS);
		AddogunOption_("Poo", 2452367939);
		AddogunOption_("Body Parts", 3026386862);
		AddogunOption_("Corpse", 3283329087);
		AddogunOption_("Cone", 3235319999);
		AddogunOption_("Shopping Cart", 1395334609);
		AddogunOption_("Gold Bar", 4031179319);
		AddogunOption_("Jukebox", 1945457558);
		AddogunOption_("Christmas Tree S", 238789712);
		AddogunOption_("Bank Safe", 1089807209);
		AddogunOption_("W33D", 3989082015);
		AddogunOption_("EMP", 932490441);
		AddogunOption_("Laptop", 3618439924);
		AddogunOption_("Molten Gate", 735855031);
		AddogunOption_("Case", 1037912790);
		AddogunOption_("Snowman", 2677555217);
		AddogunOption_("Doors", 672525579);
		AddogunOption_("Fixter", 3458454463);
		AddogunOption_("Barracks", 630371791);
		AddogunOption_("Lectro", 640818791);
		AddogunOption_("Hakuchou", 1265391242);
		AddogunOption_("Thrust", 1836027715);
		AddogunOption_("Panto", 3863274624);
		AddOption("~b~Input~s~ Model", bObjectGun_Input);

		if (bObjectGun_Input)
		{
			std::string inputStr = Game::InputBox("", 64U, "Enter object/vehicle model name:");
			if (inputStr.length() > 0)
			{
				Model model(inputStr);
				if (model.IsInCdImage())
				{
					object_gun_hash = model;
					model.Load();
				}
				else Game::Print::PrintError_InvalidModel();
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::ObjectGunHash, std::string(), 64U, "Enter object/vehicle model name:");
		}

	}

	void List_VehicleCats_Sub()
	{
		using SpawnVehicle_catind::AddvcatOption_;
		typedef SpawnVehicle_catind::Indices Indices;

		AddTitle("Vehicles");
		AddOption("Favourites", null, nullFunc, SUB::SPAWNVEHICLE_FAVOURITES);

		AddBreak("---Cars---");
		AddvcatOption_("Open Wheel", Indices::OPENWHEEL);
		AddvcatOption_("Super", Indices::SUPER);
		AddvcatOption_("Sports", Indices::SPORT);
		AddvcatOption_("Sports Classics", Indices::SPORTSCLASSIC);
		AddvcatOption_("Coupes", Indices::COUPE);
		AddvcatOption_("Muscle", Indices::MUSCLE);
		AddvcatOption_("Offroad", Indices::OFFROAD);
		AddvcatOption_("SUVs", Indices::SUV);
		AddvcatOption_("Sedans", Indices::SEDAN);
		AddvcatOption_("Compacts", Indices::COMPACT);
		AddvcatOption_("Drift", Indices::DRIFT);

		AddBreak("---Industrial---");
		AddvcatOption_("Vans", Indices::VAN);
		AddvcatOption_("Services", Indices::SERVICE);
		AddvcatOption_("Industrial", Indices::INDUSTRIAL);
		AddvcatOption_("Commercial", Indices::COMMERCIAL);
		AddvcatOption_("Utility", Indices::UTILITY);
		AddvcatOption_("Trains", Indices::TRAIN);

		AddBreak("---Others---");
		AddvcatOption_("Emergency", Indices::EMERGENCY);
		AddvcatOption_("Military", Indices::MILITARY);
		AddvcatOption_("Motorcycles", Indices::MOTORCYCLE);
		AddvcatOption_("Bicycles", Indices::BICYCLE);
		AddvcatOption_("Others", Indices::OTHER);

		/*PCHAR chartick;
		for (const auto& vimg : vVehicleBmps)
		{
		chartick = PCHAR(vimg.dict.c_str());
		if (HAS_STREAMED_TEXTURE_DICT_LOADED(chartick))
		SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(chartick);
		}*/

	}

	namespace WeaponFavourites_catind
	{
		std::string xmlFavouriteWeapons = "FavouriteWeapons.xml";
		bool PopulateFavouritesInfo()
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.document_element();
			for (auto nodeWeap = nodeRoot.child("Weapon"); nodeWeap; nodeWeap = nodeWeap.next_sibling("Weapon"))
			{
				Hash whash = nodeWeap.attribute("hash").as_uint();
				std::string customName = nodeWeap.attribute("customName").as_string();
				bool bIsPresentAlready = WeaponIndivs::vWeaponLabels.count(whash) != 0;
				WeaponIndivs::vWeaponLabels[whash] = customName;
				if (!bIsPresentAlready)
				{
					WeaponAndComponents wac(whash, {}, &WeaponIndivs::vCaptions_Tints);
					WeaponIndivs::vAllWeapons.back()->push_back(wac);
				}
			}
			return true;
		}
		bool IsWeaponAFavourite(Hash whash)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.document_element();
			return nodeRoot.find_child_by_attribute("hash", int_to_hexstring(whash, true).c_str()) != NULL;
		}
		bool AddWeaponToFavourites(Hash whash, const std::string& customName)
		{
			if (customName.empty())
				return false;

			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()).status != pugi::status_ok)
			{
				doc.reset();
				auto nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto nodeRoot = doc.append_child("FavouriteWeapons");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str());
			}
			pugi::xml_node nodeRoot = doc.document_element();

			auto nodeOldLoc = nodeRoot.find_child_by_attribute("hash", int_to_hexstring(whash, true).c_str());
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
				for (auto wit = WeaponIndivs::vAllWeapons.back()->begin(); wit != WeaponIndivs::vAllWeapons.back()->end(); ++wit)
				{
					if (wit->weaponHash == whash)
					{
						WeaponIndivs::vAllWeapons.back()->erase(wit);
						break;
					}
				}
			}
			auto nodeNewLoc = nodeRoot.append_child("Weapon");
			nodeNewLoc.append_attribute("hash") = int_to_hexstring(whash, true).c_str();
			nodeNewLoc.append_attribute("customName") = customName.c_str();

			WeaponIndivs::vWeaponLabels[whash] = customName;
			WeaponAndComponents wac(whash, {}, &WeaponIndivs::vCaptions_Tints);
			WeaponIndivs::vAllWeapons.back()->push_back(wac);

			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()));
		}
		bool RemoveWeaponFromFavourites(Hash whash)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.document_element();
			auto nodeOldLoc = nodeRoot.find_child_by_attribute("hash", int_to_hexstring(whash, true).c_str());
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
			}

			//auto& wlit = WeaponIndivs::vWeaponLabels.find(whash); if (wlit != WeaponIndivs::vWeaponLabels.end())WeaponIndivs::vWeaponLabels.erase(wlit);
			for (auto wit = WeaponIndivs::vAllWeapons.back()->begin(); wit != WeaponIndivs::vAllWeapons.back()->end(); ++wit)
			{
				if (wit->weaponHash == whash)
				{
					WeaponIndivs::vAllWeapons.back()->erase(wit);
					break;
				}
			}

			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()));
		}

		void Sub_WeaponFavourites()
		{
			GTAped ped = Static_241;
			Hash currentPedWeapon = ped.Weapon_get();

			AddTitle("Favourites");

			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str()).status != pugi::status_ok)
			{
				doc.reset();
				auto nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto nodeRoot = doc.append_child("FavouriteWeapons");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str());
				return;
			}
			pugi::xml_node nodeRoot = doc.document_element();

			bool bInputAdd = false;
			AddOption("Add New Weapon", bInputAdd); if (bInputAdd)
			{
				std::string hashNameStr = Game::InputBox("", 40U, "Enter name (e.g. WEAPON_FLAMETHROWER):");
				if (hashNameStr.length() > 0)
				{
					WAIT(500);
					Hash hashNameHash = GET_HASH_KEY(hashNameStr);
					if (IS_WEAPON_VALID(hashNameHash))
					{
						std::string customNameStr = Game::InputBox("", 28U, "Enter custom name:", get_weapon_label(hashNameHash, true));
						if (customNameStr.length() > 0)
						{
							if (AddWeaponToFavourites(hashNameHash, customNameStr))
							{
								Game::Print::PrintBottomLeft("Weapon ~b~added~s~.");
							}
							else
								Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to add weapon.");
						}
						else
							Game::Print::PrintError_InvalidInput();
					}
					else
						Game::Print::PrintError_InvalidInput();
				}
				else
					Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteWeaponEntryName, std::string(), 40U, "Enter name (e.g. WEAPON_FLAMETHROWER):");
			}

			if (currentPedWeapon != WEAPON_UNARMED)
			{
				bool bIsCurrentWeaponAFav = IsWeaponAFavourite(currentPedWeapon);
				bool bAddCurrentWeaponToFav = false, bRemoveCurrentWeaponFromFav = false;
				AddTickol("Currently Held Weapon", bIsCurrentWeaponAFav, bAddCurrentWeaponToFav, bRemoveCurrentWeaponFromFav, TICKOL::BOXTICK, TICKOL::BOXBLANK);
				if (bAddCurrentWeaponToFav)
				{
					std::string customNameStr = Game::InputBox("", 28U, "Enter custom name:", get_weapon_label(currentPedWeapon, true));
					if (customNameStr.length())
					{
						if (AddWeaponToFavourites(currentPedWeapon, customNameStr))
						{
							Game::Print::PrintBottomLeft("Weapon ~b~added~s~.");
						}
						else
							Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to add weapon.");
					}
					else
						Game::Print::PrintError_InvalidInput();
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteWeaponCurrent, std::string(), 28U, "Enter custom name:");
					//OnscreenKeyboard::State::arg1._uint = currentPedWeapon;
				}
				else if (bRemoveCurrentWeaponFromFav)
				{
					if (RemoveWeaponFromFavourites(currentPedWeapon))
					{
						Game::Print::PrintBottomLeft("Weapon ~b~removed~s~.");
					}
					else
						Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to remove weapon.");
				}
			}

			if (nodeRoot.first_child())
			{
				AddBreak("---Added Weapons---");

				for (auto nodeLocToLoad = nodeRoot.first_child(); nodeLocToLoad; nodeLocToLoad = nodeLocToLoad.next_sibling())
				{
					const std::string& customName = nodeLocToLoad.attribute("customName").as_string();
					Model whash = nodeLocToLoad.attribute("hash").as_uint();

					bool bWeapPressed = false;
					AddOption(customName, bWeapPressed); if (bWeapPressed)
					{
						INT& selectedCategoryForInItem = Static_12;
						INT& selectedWeaponForInItem = ms_curr_paint_index;
						auto& vAllAddedWeaponsArr = *WeaponIndivs::vAllWeapons.back();
						for (UINT i = 0; i < vAllAddedWeaponsArr.size(); i++)
						{
							if (vAllAddedWeaponsArr[i].weaponHash == whash)
							{
								selectedCategoryForInItem = (INT)(WeaponIndivs::vAllWeapons.size() - 1);
								selectedWeaponForInItem = i;
								Menu::SetSub_delayed = SUB::WEAPONOPS_INDIVS_ITEM;
								break;
							}
						}
					}

					if (Menu::printingop == *Menu::currentopATM)
					{
						if (Menu::bit_controller)
						{
							Menu::add_IB(INPUT_SCRIPT_RLEFT, "Remove");

							if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
							{
								nodeLocToLoad.parent().remove_child(nodeLocToLoad);
								doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str());
								if (*Menu::currentopATM >= Menu::totalop) Menu::Up();
								return; // Yeah
							}
						}
						else
						{
							Menu::add_IB(VirtualKey::B, "Remove");

							if (IsKeyJustUp(VirtualKey::B))
							{
								nodeLocToLoad.parent().remove_child(nodeLocToLoad);
								doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteWeapons).c_str());
								if (*Menu::currentopATM >= Menu::totalop)
									Menu::Up();
								return; // Yeah
							}
						}
					}
				}
			}
		}
	}

	namespace WeaponIndivs_catind
	{
		//using namespace WeaponIndivs;
		using WeaponIndivs::WEAPONTYPE;
		using WeaponIndivs::vCategoryNames;
		using WeaponIndivs::vAllWeapons;
		using WeaponIndivs::get_weapon;
		using WeaponIndivs::vCaptions_ChuteTints;

		INT& selectedCategory = Static_12;
		INT& selectedWeapon = ms_curr_paint_index;


		// THESE SUBMENUS NEED THE AMMU NATION BANNER
		void Sub_CategoriesList()
		{
			int i;
			auto& ped = Static_241;
			Hash pedCurrentWeapon; GET_CURRENT_PED_WEAPON(ped, &pedCurrentWeapon, 1);

			AddTitle("Individual Weapons");

			bool pressedCurrent = false;
			AddOption("Currently Held Weapon", pressedCurrent); if (pressedCurrent)
			{
				switch (pedCurrentWeapon)
				{
				case WEAPON_UNARMED:
					Game::Print::PrintBottomCentre(oss_ << "This weapon isn't exactly valid: ~b~" << get_weapon_label(pedCurrentWeapon, true) << "~s~.");
					break;
				default:
					selectedCategory = WEAPONTYPE::WEAPE_CURRENTLYHELD;
					Menu::SetSub_delayed = (SUB::WEAPONOPS_INDIVS_ITEM);
					break;
				}
			}

			if (GET_PLAYER_PED(Static_240) == ped)
				AddOption("Parachutes", null, nullFunc, SUB::WEAPONOPS_PARACHUTE);

			bool pressed = false;
			for (i = 0; i < vCategoryNames.size() - 1 /*Minus Added weapons*/; i++)
			{
				pressed = 0;
				AddOption(vCategoryNames[i], pressed, nullFunc, -1, true); if (pressed)
				{
					selectedCategory = i;
					Menu::SetSub_delayed = (SUB::WEAPONOPS_INDIVS_CATEGORY);
				}
			}

			bool bFavsPressed = false;
			AddOption("Favourites", bFavsPressed, nullFunc, SUB::WEAPONOPS_WEAPONFAVOURITES); if (bFavsPressed)
			{
				selectedCategory = (INT)(vCategoryNames.size() - 1);
			}

		}
		void Sub_InCategory()
		{
			int i;

			bool bWeapPressed = false;
			AddTitle(vCategoryNames[selectedCategory]);
			for (i = 0; i < vAllWeapons[selectedCategory]->size(); i++)
			{
				auto& thisWeaponInfo = vAllWeapons[selectedCategory]->at(i);
				bool bWeapPressed = false;
				AddOption(get_weapon_label(thisWeaponInfo.weaponHash, true), bWeapPressed); if (bWeapPressed)
				{
					selectedWeapon = i;
					Menu::SetSub_delayed = SUB::WEAPONOPS_INDIVS_ITEM;
				}

				if (Menu::printingop == *Menu::currentopATM)
				{
					bool bIsAFav = WeaponFavourites_catind::IsWeaponAFavourite(thisWeaponInfo.weaponHash);
					if (Menu::bit_controller)
					{
						Menu::add_IB(INPUT_SCRIPT_RLEFT, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

						if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
						{
							!bIsAFav ?
								WeaponFavourites_catind::AddWeaponToFavourites(thisWeaponInfo.weaponHash, Game::InputBox("", 28U, "Enter custom name:", get_weapon_label(thisWeaponInfo.weaponHash, true)))
								: WeaponFavourites_catind::RemoveWeaponFromFavourites(thisWeaponInfo.weaponHash);
							/*if (!bIsAFav)
							{
							OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteWeaponSelected, std::string(), 28U, "Enter custom name:", get_weapon_label(thisWeaponInfo.weaponHash, true));
							OnscreenKeyboard::State::arg1._uint = thisWeaponInfo.weaponHash;
							}
							else WeaponFavourites_catind::RemoveWeaponFromFavourites(thisWeaponInfo.weaponHash);*/
						}
					}
					else
					{
						Menu::add_IB(VirtualKey::B, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

						if (IsKeyJustUp(VirtualKey::B))
						{
							!bIsAFav ?
								WeaponFavourites_catind::AddWeaponToFavourites(thisWeaponInfo.weaponHash, Game::InputBox("", 28U, "Enter custom name:", get_weapon_label(thisWeaponInfo.weaponHash, true)))
								: WeaponFavourites_catind::RemoveWeaponFromFavourites(thisWeaponInfo.weaponHash);
							/*if (!bIsAFav)
							{
							OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouriteWeaponSelected, std::string(), 28U, "Enter custom name:", get_weapon_label(thisWeaponInfo.weaponHash, true));
							OnscreenKeyboard::State::arg1._uint = thisWeaponInfo.weaponHash;
							}
							else WeaponFavourites_catind::RemoveWeaponFromFavourites(thisWeaponInfo.weaponHash);*/
						}
					}
				}

			}

		}
		void Sub_InItem()
		{
			auto& ped = Static_241;
			NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);

			Hash pedCurrentWeapon; GET_CURRENT_PED_WEAPON(ped, &pedCurrentWeapon, 1);

			Hash whash;

			const WeaponAndComponents* selWeapon = nullptr;
			const std::vector<NamedWeaponComponent>* selWeaponComponents = nullptr;
			const std::vector<std::string>* selWeaponTints = nullptr;

			if (selectedCategory == WEAPONTYPE::WEAPE_CURRENTLYHELD)
			{
				whash = pedCurrentWeapon;
				selWeapon = get_weapon(whash);
				if (selWeapon == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				selWeaponComponents = &selWeapon->components;
				selWeaponTints = selWeapon->tintCaptions;
			}
			else
			{
				selWeapon = &vAllWeapons[selectedCategory]->at(selectedWeapon);
				whash = selWeapon->weaponHash;
				selWeaponComponents = &selWeapon->components;
				selWeaponTints = selWeapon->tintCaptions;
			}

			std::string displayName = get_weapon_label(whash, true);

			AddTitle(displayName);

			bool it_Equip = 0;
			AddTickol("Equip Weapon", pedCurrentWeapon == whash, it_Equip, null); if (it_Equip)
			{
				if (DOES_ENTITY_EXIST(ped))
				{
					if (!HAS_PED_GOT_WEAPON(ped, whash, false))
					{
						GIVE_DELAYED_WEAPON_TO_PED(ped, whash, 1000, 0);
						int maxAmmo = 0;
						GET_MAX_AMMO(ped, whash, &maxAmmo);
						SET_AMMO_IN_CLIP(ped, whash, GET_MAX_AMMO_IN_CLIP(ped, whash, false));
						SET_PED_AMMO(ped, whash, maxAmmo, 0);
					}
					SET_CURRENT_PED_WEAPON(ped, whash, true);
				}
			}

			bool it_FillAmmo = 0;
			AddOption("Fill Ammo", it_FillAmmo); if (it_FillAmmo)
			{
				int maxAmmo = 0;
				GET_MAX_AMMO(ped, whash, &maxAmmo);
				SET_AMMO_IN_CLIP(ped, whash, GET_MAX_AMMO_IN_CLIP(ped, whash, false));
				SET_PED_AMMO(ped, whash, maxAmmo, 0);
			}

			bool it_FillinfAmmo = 0;
			AddOption("Empty Ammo", it_FillinfAmmo); if (it_FillinfAmmo)
			{
				SET_AMMO_IN_CLIP(ped, whash, -1);
				SET_PED_AMMO(ped, whash, -1, 0);
			}

			bool it_RemoveWeapon = 0;
			AddOption("Remove Weapon", it_RemoveWeapon); if (it_RemoveWeapon)
			{
				if (HAS_PED_GOT_WEAPON(ped, whash, false)) REMOVE_WEAPON_FROM_PED(ped, whash);
			}

			if (selWeapon != nullptr)
			{
				if (selWeaponComponents->size() > 0 || selWeaponTints != nullptr)
				{
					AddOption("Attachments & Tints", null, nullFunc, SUB::WEAPONOPS_INDIVS_ITEM_MODS);
				}
			}

		}
		void Sub_InItem_Mods()
		{
			auto& ped = Static_241;
			NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);

			Hash pedCurrentWeapon; GET_CURRENT_PED_WEAPON(ped, &pedCurrentWeapon, 1);

			Hash whash;

			const WeaponAndComponents* selWeapon = nullptr;
			const std::vector<NamedWeaponComponent>* selWeaponComponents = nullptr;
			const std::vector<std::string>* selWeaponTints = nullptr;

			if (selectedCategory == WEAPONTYPE::WEAPE_CURRENTLYHELD)
			{
				whash = pedCurrentWeapon;
				selWeapon = get_weapon(whash);
				if (selWeapon == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				selWeaponComponents = &selWeapon->components;
				selWeaponTints = selWeapon->tintCaptions;
			}
			else
			{
				selWeapon = &vAllWeapons[selectedCategory]->at(selectedWeapon);
				whash = selWeapon->weaponHash;
				selWeaponComponents = &selWeapon->components;
				selWeaponTints = selWeapon->tintCaptions;
			}

			auto currentTint = GET_PED_WEAPON_TINT_INDEX(ped, whash);

			AddTitle("Attachments & Tints");

			for (auto& comp : *selWeaponComponents)
			{
				//if (!comp.name.length()) continue; // Some problem due to initializer lists/ operator= happened. Blank first element idk.
				bool bAttachmentPressed = false;
				bool bHasComponent = HAS_PED_GOT_WEAPON_COMPONENT(ped, whash, comp.hash) != 0;
				if (bHasComponent && boost::to_upper_copy(comp.name).find("CAMO") != std::string::npos)
				{
					bool bLiveryPressed = false, bLivery_plus = false, bLivery_minus = false;
					int currentLivery = GET_PED_WEAPON_COMPONENT_TINT_INDEX(ped, whash, comp.hash);
					AddTexter(comp.name, 0, std::vector<std::string>{Game::GetGXTEntry("WCT_C_TINT_" + std::to_string(currentLivery))}, bLiveryPressed, bLivery_plus, bLivery_minus);
					if (bLivery_plus && currentLivery < 31) { currentLivery++; bLiveryPressed = true; }
					else if (bLivery_minus && currentLivery > 0) { currentLivery--; bLiveryPressed = true; }
					if (bLiveryPressed) { SET_PED_WEAPON_COMPONENT_TINT_INDEX(ped, whash, comp.hash, currentLivery); }
				}
				else
				{
					AddTickol(comp.name, bHasComponent, bAttachmentPressed, bAttachmentPressed, TICKOL::WEAPONTHING); if (bAttachmentPressed)
					{
						bHasComponent ?
							REMOVE_WEAPON_COMPONENT_FROM_PED(ped, whash, comp.hash) :
							GIVE_WEAPON_COMPONENT_TO_PED(ped, whash, comp.hash);
					}
				}
			}

			if (selWeaponTints != nullptr)
			{
				if (!selWeaponComponents->empty())
					AddBreak("---Tints---");

				for (int i = 0; i < selWeaponTints->size(); i++)
				{
					bool bTintPressed = false;
					AddTickol(selWeaponTints->at(i), (currentTint == i), bTintPressed, null, TICKOL::WEAPONTHING); if (bTintPressed)
					{
						SET_PED_WEAPON_TINT_INDEX(ped, whash, i);
					}
				}
			}

		}
		void Sub_Parachute()
		{
			auto& ped = Static_241;
			NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
			auto& player = Static_240;
			UINT i;
			int currentChuteTint; GET_PLAYER_PARACHUTE_TINT_INDEX(player, &currentChuteTint);

			RGBA paraSmokeCol; GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(player, &paraSmokeCol.R, &paraSmokeCol.G, &paraSmokeCol.B);

			Hash whash = GADGET_PARACHUTE;
			bool doesPedHavePara = HAS_PED_GOT_WEAPON(ped, whash, false) != 0;

			AddTitle("Parachute");

			bool it_Equip = 0;
			AddTickol("Equip Primary", doesPedHavePara, it_Equip, it_Equip); if (it_Equip)
			{
				if (DOES_ENTITY_EXIST(ped))
				{
					give_ped_parachute(ped);
					//SET_PLAYER_PARACHUTE_TINT_INDEX(Static_240, numChute);
				}
			}

			bool it_Equip2 = 0;
			AddTickol("Equip Secondary", doesPedHavePara, it_Equip2, it_Equip2); if (it_Equip2)
			{
				if (DOES_ENTITY_EXIST(ped))
				{
					give_ped_parachute(ped);
					SET_PLAYER_HAS_RESERVE_PARACHUTE(Static_240);
					//_0xAF04C87F5DC1DF38(Static_240, numChute2);
				}
			}

			bool it_RemoveWeapon = 0;
			AddOption("Remove", it_RemoveWeapon); if (it_RemoveWeapon)
			{
				if (doesPedHavePara)
					REMOVE_WEAPON_FROM_PED(ped, whash);
			}

			bool goRgbSmokeMenu = 0;
			AddOption("Set Smoke Colour", goRgbSmokeMenu, nullFunc, SUB::MSPAINTS_RGB);
			if (*Menu::currentopATM == Menu::printingop) 
				Add_preset_colour_options_previews(paraSmokeCol);
			if (goRgbSmokeMenu)
			{
				bit_MSPaints_RGB_mode = 7;
			}

			AddBreak("---Tints---");

			bool tintPressed = 0;
			for (i = 0; i < vCaptions_ChuteTints.size(); i++)
			{
				tintPressed = 0;
				AddTickol(vCaptions_ChuteTints[i], currentChuteTint == i, tintPressed, tintPressed, TICKOL::WEAPONTHING); if (tintPressed)
				{
					SET_PLAYER_PARACHUTE_TINT_INDEX(player, i);
					if (IS_DLC_PRESENT(0xC40B8B70))
					{
						SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(player, 0x73268708);
					}
					else if (IS_DLC_PRESENT(0x55292CC7))
					{
						SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(player, 0x815E52EB);
					}
				}
			}


		}

	}

	namespace WeaponsLoadouts_catind
	{
		std::string& _searchStr = dict2;
		std::string& _name = dict;
		std::string& _dir = dict3;
		auto& _ped = Static_241;

		bool Create(GTAped ped, const std::string& filePath)
		{
			pugi::xml_document doc;

			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";

			auto nodeLoadout = doc.append_child("Loadout"); // Root
			nodeLoadout.append_attribute("menyoo_ver") = MENYOO_CURRENT_VER_;

			std::vector<s_Weapon_Components_Tint> wct;
			ped.StoreWeaponsInArray(wct);

			for (auto& c : wct)
			{
				auto nodeWeapon = nodeLoadout.append_child("Weapon");
				nodeWeapon.append_attribute("hash") = int_to_hexstring(c.weaponHash, true).c_str();
				nodeWeapon.append_attribute("tint") = c.tint;
				auto nodeComponents = nodeWeapon.append_child("Components");
				for (auto& cc : c.componentHashes)
				{
					auto nodeComponent = nodeComponents.append_child("Component");
					nodeComponent.append_attribute("hash") = int_to_hexstring(cc.first, true).c_str();
					nodeComponent.append_attribute("livery") = int_to_hexstring(cc.second, true).c_str();
				}
			}

			return (doc.save_file((const char*)filePath.c_str()));
		}
		bool Apply(GTAped ped, const std::string& filePath)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
				return false;

			auto nodeLoadout = doc.child("Loadout"); // Root

			std::vector<s_Weapon_Components_Tint> wct;
			for (auto nodeWeapon = nodeLoadout.child("Weapon"); nodeWeapon; nodeWeapon = nodeWeapon.next_sibling("Weapon"))
			{
				s_Weapon_Components_Tint c;
				c.weaponHash = nodeWeapon.attribute("hash").as_uint();
				c.tint = nodeWeapon.attribute("tint").as_int();
				auto nodeComponents = nodeWeapon.child("Components");
				for (auto nodeComponent = nodeComponents.first_child(); nodeComponent; nodeComponent = nodeComponent.next_sibling())
				{
					auto componentHashAttr = nodeComponent.attribute("hash");
					auto componentLiveryAttr = nodeComponent.attribute("livery");
					if (componentHashAttr) c.componentHashes.push_back({ componentHashAttr.as_uint(), componentLiveryAttr ? componentLiveryAttr.as_int() : -1 });
					else c.componentHashes.push_back({ nodeComponent.text().as_uint(), componentLiveryAttr ? componentLiveryAttr.as_int() : -1 });
				}
				wct.push_back(c);
			}

			if (NETWORK_IS_IN_SESSION())
				ped.RequestControl(600);
			ped.RemoveAllWeapons();
			ped.GiveWeaponsFromArray(wct);
			return true;
		}

		void Sub_Loadouts()
		{
			bool save2 = false, bCreateFolderPressed = false;
			std::vector<std::string> vfilnames;

			AddTitle("Loadouts");

			AddOption("Save Current Loadout", save2);

			AddOption("Create New Folder", bCreateFolderPressed);

			//get_all_filenames_with_extension(GetPathffA(Pathff::WeaponsLoadout, false), ".xml", vfilnames, false);
			if (_dir.empty()) _dir = GetPathffA(Pathff::WeaponsLoadout, false);
			DIR* dir_point = opendir(_dir.c_str());
			dirent* entry = readdir(dir_point);
			while (entry)
			{
				vfilnames.push_back(entry->d_name);
				entry = readdir(dir_point);
			}
			closedir(dir_point);

			AddBreak("---Found Files---");

			bool bFolderBackPressed = false;
			AddOption("..", bFolderBackPressed); if (bFolderBackPressed)
			{
				_dir = _dir.substr(0, _dir.rfind("\\"));
				Menu::currentop = 4;
			}

			if (!vfilnames.empty())
			{
				bool bSearchPressed = false;
				AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
					boost::to_upper(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto& filname : vfilnames)
				{
					if (filname.front() == '.' || filname.front() == ',')
						continue;
					if (!_searchStr.empty()) { if (boost::to_upper_copy(filname).find(_searchStr) == std::string::npos) continue; }

					bool isFolder = PathIsDirectoryA((_dir + "\\" + filname).c_str()) != 0;
					bool isXml = filname.length() > 4 && filname.rfind(".xml") == filname.length() - 4;
					TICKOL icon = TICKOL::NONE;
					if (isFolder) icon = TICKOL::ARROWRIGHT;
					else if (isXml) icon = TICKOL::TICK2;
					bool bFilePressed = false;

					if (isFolder)
					{
						AddTickol(filname + " >>>", true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
						{
							_dir = _dir + "\\" + filname;
							Menu::currentop = 4;
						}

						if (Menu::printingop == *Menu::currentopATM && !bFilePressed)
						{
							if (FolderPreviewBmps_catind::bFolderBmpsEnabled)
								FolderPreviewBmps_catind::DrawBmp(_dir + "\\" + filname);
						}
					}
					else if (isXml)
					{
						AddTickol(filname, true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
						{
							_name = filname.substr(0, filname.rfind('.'));
							Menu::SetSub_delayed = SUB::WEAPONOPS_LOADOUTS_INITEM;
							return;
						}
					}
				}
			}

			if (save2)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter loadout name:");
				if (inputStr.length() > 0)
				{
					if (WeaponsLoadouts_catind::Create(_ped, _dir + "\\" + inputStr + ".xml"))
						Game::Print::PrintBottomLeft("Loadout ~b~saved~s~.");
					else
						Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to save loadout.");
				}
				else
					Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SaveLoadoutToFile, std::string(), 28U, "Enter loadout name:");
				//OnscreenKeyboard::State::arg1._int = _ped;
				//OnscreenKeyboard::State::arg2._ptr = reinterpret_cast<std::string*>(&_dir);
			}

			if (bCreateFolderPressed)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter folder name:");
				if (inputStr.length() > 0)
				{
					if (CreateDirectoryA((_dir + "\\" + inputStr).c_str(), NULL) ||
						GetLastError() == ERROR_ALREADY_EXISTS)
					{
						_dir = _dir + "\\" + inputStr;
						Menu::currentop = 4;
						Game::Print::PrintBottomLeft("Folder ~b~created~s~.");
					}
					else
					{
						Game::Print::PrintBottomCentre("~r~Failed~s~ to create folder.");
					}
				}
				else
					Game::Print::PrintError_InvalidInput();
				return;
				// No OnscreenKeyboard!
			}

			//if (Menu::currentop > Menu::printingop) Menu::Up();
			//else if (Menu::currentop <= 0) Menu::Down();
		}
		void Sub_Loadouts_InItem()
		{
			std::string filePath = _dir + "\\" + _name + ".xml";

			bool bLoad = false, bRename = false, bOverwrite = false, bDelete = false;

			AddTitle(_name);
			AddOption("Apply", bLoad);
			AddOption("Rename File", bRename);
			AddOption("Overwrite File", bOverwrite);
			AddOption("Delete File", bDelete);

			if (bLoad)
			{
				if (WeaponsLoadouts_catind::Apply(_ped, filePath))
					Game::Print::PrintBottomLeft("Loadout ~b~applied~s~.");
				else
					Game::Print::PrintBottomLeft("~r~Error~s~ applying loadout.");
			}

			if (bRename)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter new name:", _name);
				if (inputStr.length())
				{
					if (rename(filePath.c_str(), (_dir + "\\" + inputStr + ".xml").c_str()) == 0)
					{
						_name = inputStr;
						Game::Print::PrintBottomLeft("File ~b~renamed~s~.");
					}
					else
						Game::Print::PrintBottomCentre("~r~Error~s~ renaming file.");
				}
				else
					Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::RenameLoadoutFile, std::string(), 28U, "Enter new name:");
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_name);
				//OnscreenKeyboard::State::arg2._ptr = reinterpret_cast<void*>(&_dir);
			}

			if (bOverwrite)
			{
				if (WeaponsLoadouts_catind::Create(_ped, filePath))
					Game::Print::PrintBottomLeft("File ~b~overwritten~s~.");
				else
					Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to overwrite file.");
			}

			if (bDelete)
			{
				if (remove(filePath.c_str()) == 0)
					Game::Print::PrintBottomLeft("File ~b~deleted~s~.");
				else
					Game::Print::PrintBottomCentre("~r~Error~s~ deleting file.");
				Menu::SetSub_previous();
				Menu::Up();
				return;
			}

			// Attributes if any
		}
	}

	namespace LaserSight_catind
	{
		bool bEnabled = false;
		RGBA _colour(255, 0, 0, 255);

		inline void DoSight()
		{
			GTAped myPed = PLAYER_PED_ID();
			if (!myPed.Exists())
				return;
			GTAplayer myPlayer = PLAYER_ID();

			Hash weap = myPed.Weapon_get();
			switch (GET_WEAPONTYPE_GROUP(weap))
			{
			case WeaponGroupHash::FireExtinguisher:
			case WeaponGroupHash::Melee:
			case WeaponGroupHash::Spillable:
			case WeaponGroupHash::Throwable:
				return; break;
			}

			RaycastResult ray;
			Vector3 hitCoord;
			GTAentity gun = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(myPed.Handle(), 0);

			if (gun.Handle() != NULL)
			{
				if (!myPed.IsReloading() && (myPlayer.IsFreeAiming() || myPlayer.IsTargetingAnything()))
				{
					const Vector3& camDir = GameplayCamera::DirectionFromScreenCentre_get();
					const Vector3& camCoord = GameplayCamera::Position_get();

					ray = RaycastResult::Raycast(camCoord, camDir, 300.0f, IntersectOptions::Everything, myPed);

					if (ray.DidHitAnything())
						hitCoord = ray.HitCoords() + Vector3(0, 0, -0.07f);
					else
					{
						hitCoord = camCoord + (camDir * 1000.0f);
					}


					Vector3 laserLaunchPos;
					Vector3 dotSize(0.016f, 0.016f, 0.016f);

					float distanceToEnd = myPed.Position_get().DistanceTo(hitCoord);
					if (distanceToEnd < 7.0f)
						dotSize = Vector3(0.009f, 0.009f, 0.009f);
					if (myPed.IsShooting())
						hitCoord = hitCoord + Vector3(0, 0, distanceToEnd * sin(RadianToDegree(0.7f)));


					if (GET_WEAPONTYPE_GROUP(weap) == WeaponGroupHash::Sniper)
					{
						laserLaunchPos = gun.GetOffsetInWorldCoords(0, 0, -0.006f);
					}
					else
					{
						laserLaunchPos = gun.GetOffsetInWorldCoords(0, 0, -0.01f);
					}

					World::DrawLine(laserLaunchPos, hitCoord, _colour);
					World::DrawMarker(MarkerType::DebugSphere, hitCoord, Vector3(), Vector3(), dotSize, _colour);
				}
			}
		}
		void Tick()
		{
			if (LaserSight_catind::bEnabled && !_Gta2Cam_::g_gta2Cam.Enabled()) // This does not work well with the top down camera
			{
				DoSight();
			}
		}

		void Sub_LaserSight()
		{
			AddTitle("Laser Sight");
			AddToggle("Toggle", LaserSight_catind::bEnabled);
			AddsettingscolOption("Set Colour", LaserSight_catind::_colour);
		}
	}

	void ObjectSpawner_objs()
	{
		std::string& _searchStr = dict;
		bool Obj_Spawn_input_obj = 0, searchobj = 0;

		AddTitle("All Objects");

		AddOption(_searchStr.empty() ? "SEARCH" : boost::to_upper_copy(_searchStr), searchobj, nullFunc, -1, true); if (searchobj)
		{
			_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", _searchStr);
			boost::to_lower(_searchStr);
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToLower, _searchStr, 126U, std::string(), _searchStr);
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
		}

		// Display props models loop
		for (const auto& current : objectModels)
		{
			if (!_searchStr.empty()) { if (current.find(_searchStr) == std::string::npos) continue; }

			switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
			{
			case SUB::OBJECTGUN:
				AddogunOption_(current, GET_HASH_KEY(current));
				break;

			}

		}

	}

}




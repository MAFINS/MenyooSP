/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PlayerOptions.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Util\FileLogger.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Game.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\World.h"
#include "..\Scripting\Camera.h"

#include "..\Misc\SmashAbility.h"

#include "..\Submenus\PedComponentChanger.h"
#include "..\Submenus\Spooner\SpoonerEntity.h"
#include "..\Submenus\Spooner\EntityManagement.h"

#include <string>
#include <vector>

namespace sub
{
	void PlayerOps_()
	{
		dict2.clear();

		bool bGoToAlphaLevelSub = 0,
			PlayerOpsReplenishPlayer_ = 0,
			PlayerOpsInvincibilityOff_ = 0,
			PlayerOpsInvisibilityOff_ = 0,
			PlayerOpsNoRagdollOff_ = 0,
			PlayerOpsSeatbeltOff_ = 0,
			PlayerOpsSupermanOn_ = 0,
			PlayerOpsSupermanAUTOOn_ = 0,
			PlayerOps_ignoredByEveryone_off = 0,
			PlayerOpsNeverWantedOn_ = 0,
			PlayerOpsNeverWantedOff_ = 0,
			PlayerOpsWanted_plus = 0,
			PlayerOpsWanted_minus = 0,
			PlayerOpsWanted_freezeOn = 0,
			PlayerOpsWanted_freezeOff = 0,
			PlayerOpsBurnModeOn_ = 0,
			PlayerOpsBurnModeOff_ = 0,
			//PlayerOpsNoGravityOff_ = 0,
			PlayerOps_i69_flt_MovementSpeed = 0,
			PlayerOps_d69_flt_MovementSpeed = 0,
			PlayerOps_sweat_plus = 0,
			PlayerOps_sweat_minus = 0,
			PlayerOps_noiseValue_plus = 0,
			PlayerOps_noiseValue_minus = 0,
			vcollisionon = 0,
			vcollisionoff = 0,
			forcefield_plus = 0, forcefield_minus = 0,
			bHeight_plus = 0, bHeight_minus = 0,
			bMovementSpeed_plus = 0, bMovementSpeed_minus = 0,
			bSwimSpeed_plus = 0, bSwimSpeed_minus = 0;

		std::vector<std::string> forcefield_names{ "Off", "Push Out", "Destroy" };

		float& fHeight = g_playerVerticalElongationMultiplier;//GeneralGlobalHax::GetPlayerHeight();
		//float fMovementSpeed = 0.0f, fSwimSpeed = 0.0f;
		float fMovementSpeed = GeneralGlobalHax::GetPlayerMovementSpeed();
		float fSwimSpeed = GeneralGlobalHax::GetPlayerSwimSpeed();

		bool butAmIOnline = NETWORK_IS_IN_SESSION() != 0;

		Static_241 = PLAYER_PED_ID();
		Static_240 = PLAYER_ID();

		GTAped myPed = Static_241;
		GTAplayer myPlayer = Static_240;

		int PlayerOpsWantedLevel = myPlayer.WantedLevel_get();

		AddTitle("Player Options");
		AddOption("Basic Stats", null, nullFunc, SUB::SPSTATMANAGER);
		AddOption("Model Changer", null, nullFunc, SUB::MODELCHANGER);

		AddOption("Wardrobe", null, nullFunc, SUB::COMPONENTS);
		if (g_cam_componentChanger.Exists())
		{
			g_cam_componentChanger.SetActive(false);
			g_cam_componentChanger.Destroy();
			World::RenderingCamera_set(0);
		}
		
		AddOption("Animations", null, nullFunc, SUB::ANIMATIONSUB);
		AddOption("Scenario Actions", null, nullFunc, SUB::ANIMATIONSUB_TASKSCENARIOS);
		AddOption("Moods", null, nullFunc, SUB::FACIALMOOD);
		AddOption("Movement Styles", null, nullFunc, SUB::MOVEMENTGROUP);
		AddOption("Speech Player", null, nullFunc, SUB::SPEECHPLAYER);
		AddOption("Voice Changer", null, nullFunc, SUB::VOICECHANGER);
		AddOption("Ped Flags", null, nullFunc, SUB::PEDFLAGMANAGER_NAMEDLIST);
		AddOption("TriggerFX", null, nullFunc, SUB::PTFXSUB);
		AddOption("Breathe Stuff", null, nullFunc, SUB::BREATHESTUFF);
		AddOption("Ghost Rider Mode", null, nullFunc, SUB::GHOSTRIDERMODE);

		AddOption("Opacity (Local)", bGoToAlphaLevelSub, nullFunc, SUB::ENTITYALPHALEVEL);
		if (bGoToAlphaLevelSub)
			Static_12 = myPed.Handle();

		AddOption("Cloning Options", null, nullFunc, SUB::CLONECOMPANIONSUB);

		AddOption("Replenish Player", PlayerOpsReplenishPlayer_);
		AddToggle("Refill Health When In Cover", loop_self_refillHealthInCover);
		AddToggle("Invincibility", loop_player_invincibility, null, PlayerOpsInvincibilityOff_);
		AddLocal("Invisibility", !myPed.IsVisible(), PlayerOpsInvisibilityOff_, PlayerOpsInvisibilityOff_);
		AddToggle("No Ragdoll", loop_player_noRagdoll, null, PlayerOpsNoRagdollOff_);
		AddToggle("Seatbelt", loop_player_seatbelt, null, PlayerOpsSeatbeltOff_);
		AddToggle("Unlimited Special Ability (SP)", loop_player_unlimSpecialAbility);
		AddToggle("Auto-Clean", loop_player_autoClean);
		AddToggle("Super Run", loop_super_run);
		AddToggle("Super Jump", loop_super_jump);
		AddToggle("Walk underwater", loop_player_Walkunderwater);
		AddTexter("Forcefield", loop_forcefield, forcefield_names, null, forcefield_plus, forcefield_minus);
		AddLocal("Smash Ability", _SmashAbility_::g_smashAbility.Enabled(), _SmashAbility_::ToggleOnOff, _SmashAbility_::ToggleOnOff);
		AddToggle("Fly Manual", loop_superman, PlayerOpsSupermanOn_);
		AddToggle("Fly Auto", loop_superman_auto, PlayerOpsSupermanAUTOOn_);
		AddToggle("Ignored By Everyone", loop_ignored_by_everyone, null, PlayerOps_ignoredByEveryone_off);
		AddNumber("Wanted Level", PlayerOpsWantedLevel, 0, null, PlayerOpsWanted_plus, PlayerOpsWanted_minus);
		if (PlayerOpsWantedLevel > 0)
			AddLocal("Freeze Wanted Level", loop_self_freezeWantedLevel, PlayerOpsWanted_freezeOn, PlayerOpsWanted_freezeOff);
		else
			AddToggle("Never Wanted", loop_never_wanted, PlayerOpsNeverWantedOn_, PlayerOpsNeverWantedOff_);
		AddToggle("Burn Mode", loop_player_burn, PlayerOpsBurnModeOn_, PlayerOpsBurnModeOff_);
		//AddToggle("No Gravity (ALPHA)", loop_player_noGravity, null, PlayerOpsNoGravityOff_);
		AddNumber("Height (Elongation)", fHeight, 2, null, bHeight_plus, bHeight_minus);
		//AddNumber("Walk & Run Speed", fMovementSpeed, 2, null, bMovementSpeed_plus, bMovementSpeed_minus);
		//AddNumber("Swim Speed", fSwimSpeed, 2, null, bSwimSpeed_plus, bSwimSpeed_minus);
		AddNumber("Movement Speed (Alt)", mult69_0, 2, null, PlayerOps_i69_flt_MovementSpeed, PlayerOps_d69_flt_MovementSpeed);
		AddNumber("Sweat Level", mult_self_sweat, 2, null, PlayerOps_sweat_plus, PlayerOps_sweat_minus);
		AddNumber("Noise Level", mult_playerNoiseValue, 2, null, PlayerOps_noiseValue_plus, PlayerOps_noiseValue_minus);
		AddLocal("Collision", myPed.IsCollisionEnabled_get(), vcollisionon, vcollisionoff);
		//AddOption("Collision ON", vcollisionon);
		//AddOption("Collision OFF", vcollisionoff);

		if (vcollisionon || vcollisionoff) myPed.IsCollisionEnabled_set(!myPed.IsCollisionEnabled_get());
		//if (vcollisionon) SET_ENTITY_COLLISION(PLAYER_PED_ID(), TRUE, 0);
		//if (vcollisionoff) SET_ENTITY_COLLISION(PLAYER_PED_ID(), FALSE, 0);

		if (PlayerOpsReplenishPlayer_) {
			myPed.Health_set(myPed.MaxHealth_get());
			myPed.Armour_set(myPlayer.MaxArmour_get());
			PedDamageTextures_catind::ClearAllBloodDamage(myPed);
			PedDamageTextures_catind::ClearAllVisibleDamage(myPed);
			return;
		}

		if (PlayerOpsInvincibilityOff_) {
			SET_PLAYER_INVINCIBLE(PLAYER_ID(), 0);
			set_ped_invincible_off(PLAYER_PED_ID());
			return;
		}

		if (PlayerOpsInvisibilityOff_)
			myPed.SetVisible(!myPed.IsVisible());

		if (PlayerOpsNoRagdollOff_) { set_ped_no_ragdoll_off(PLAYER_PED_ID()); return; }
		if (PlayerOpsSeatbeltOff_) { set_ped_seatbelt_off(PLAYER_PED_ID()); return; }

		if (forcefield_plus) { if (loop_forcefield < forcefield_names.size() - 1) loop_forcefield++; return; }
		if (forcefield_minus) { if (loop_forcefield > 0) loop_forcefield--; return; }

		if (PlayerOpsSupermanOn_) {
			if (Menu::bit_controller) Game::Print::PrintBottomLeft("RT for Up. LT for Down. RB for Boost. A for Brake.");
			else Game::Print::PrintBottomLeft("Num7 for Up. Num1 for Down. NumPlus for Boost. NumMinus for Brake.");
			return;
		}

		if (PlayerOpsSupermanAUTOOn_) {
			Vector3 Pos = GET_ENTITY_COORDS(Static_241, 1);
			CREATE_AMBIENT_PICKUP(PICKUP_PARACHUTE, Pos.x, Pos.y, Pos.z, 0, 300, 1, 0, 1);
			TASK_PARACHUTE(Static_241, true, false);
			APPLY_FORCE_TO_ENTITY(PLAYER_PED_ID(), 1, 0.0f, 0.0f, 10.0f, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			if (Menu::bit_controller) Game::Print::PrintBottomLeft("Press ~b~A~s~ for temporary brake.");
			else Game::Print::PrintBottomLeft("Press ~b~NUMPLUS~s~ for temporary brake.");
			return;
		}

		if (PlayerOps_ignoredByEveryone_off) {
			Player temp = PLAYER_ID();
			SET_POLICE_IGNORE_PLAYER(temp, loop_never_wanted);
			SET_EVERYONE_IGNORE_PLAYER(temp, 0);
			SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(temp, 1);
			SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(temp, 0);
			return;
		}

		if (PlayerOpsNeverWantedOn_) {
			SET_PLAYER_WANTED_LEVEL(PLAYER_ID(), 0, 0);
			SET_PLAYER_WANTED_LEVEL_NOW(PLAYER_ID(), 0);
			return;
		}
		if (PlayerOpsNeverWantedOff_) {
			//SET_POLICE_IGNORE_PLAYER(PLAYER_ID(), FALSE);
			SET_MAX_WANTED_LEVEL(6);
			SET_WANTED_LEVEL_MULTIPLIER(1.0f);
			return;
		}
		if (PlayerOpsWanted_plus) {
			if (PlayerOpsWantedLevel < 6)
			{
				PlayerOpsWantedLevel += 1;
				SET_MAX_WANTED_LEVEL(6);
				SET_PLAYER_WANTED_LEVEL/*_NO_DROP*/(PLAYER_ID(), PlayerOpsWantedLevel, 0);
				SET_PLAYER_WANTED_LEVEL_NOW(PLAYER_ID(), 0);
				loop_never_wanted = false;
			}
			if (loop_self_freezeWantedLevel != 0) loop_self_freezeWantedLevel = PlayerOpsWantedLevel;
			return;
		}
		if (PlayerOpsWanted_minus) {
			if (PlayerOpsWantedLevel > 0)
			{
				if (PlayerOpsWantedLevel == 1)
				{
					PlayerOpsWantedLevel -= 1;
					SET_PLAYER_WANTED_LEVEL(PLAYER_ID(), PlayerOpsWantedLevel, 0);
				}
				else
				{
					PlayerOpsWantedLevel -= 1;
					SET_PLAYER_WANTED_LEVEL/*_NO_DROP*/(PLAYER_ID(), PlayerOpsWantedLevel, 0);
				}
				SET_PLAYER_WANTED_LEVEL_NOW(PLAYER_ID(), 0);
				loop_never_wanted = false;
			}
			if (loop_self_freezeWantedLevel != 0) loop_self_freezeWantedLevel = PlayerOpsWantedLevel;
			return;
		}

		if (PlayerOpsWanted_freezeOn) {
			loop_self_freezeWantedLevel = Game::Player().WantedLevel_get();
			return;
		}
		if (PlayerOpsWanted_freezeOff) {
			loop_self_freezeWantedLevel = 0;
			return;
		}

		if (PlayerOpsBurnModeOn_) {
			//set_explosion_at_coords(Static_241, Vector3::Zero(), EXPLOSION::DIR_FLAME, 4, 0, 0, 1);
			if (GET_PLAYER_INVINCIBLE(Static_240)) SET_PLAYER_INVINCIBLE(Static_240, 0);
			set_ped_invincible_off(Static_241);
			WAIT(130);
			if (!IS_ENTITY_ON_FIRE(Static_241)) START_ENTITY_FIRE(Static_241);
			Game::Print::PrintBottomCentre("~b~Note:~s~ If you're not on fire yet, kill yourself.");
			return;
		}
		if (PlayerOpsBurnModeOff_) {
			if (IS_ENTITY_ON_FIRE(Static_241)) STOP_ENTITY_FIRE(Static_241);
			return;
		}

		//if (PlayerOpsNoGravityOff_) myPed.Gravity_set(true);

		if (bHeight_plus) { if (fHeight < 2.5f) { fHeight += 0.1f; GeneralGlobalHax::SetPlayerHeight(fHeight); } }
		if (bHeight_minus) { if (fHeight > -2.5f) { fHeight -= 0.1f; GeneralGlobalHax::SetPlayerHeight(fHeight); } }
		if (bMovementSpeed_plus) { if (fMovementSpeed < 9.0f) { fMovementSpeed += 0.1f; GeneralGlobalHax::SetPlayerMovementSpeed(fMovementSpeed); } }
		if (bMovementSpeed_minus) { if (fMovementSpeed > 0.0f) { fMovementSpeed -= 0.1f; GeneralGlobalHax::SetPlayerMovementSpeed(fMovementSpeed); } }
		if (bSwimSpeed_plus) { if (fSwimSpeed < 9.0f) { fSwimSpeed += 0.1f; GeneralGlobalHax::SetPlayerSwimSpeed(fSwimSpeed); } }
		if (bSwimSpeed_minus) { if (fSwimSpeed > 0.0f) { fSwimSpeed -= 0.1f; GeneralGlobalHax::SetPlayerSwimSpeed(fSwimSpeed); } }

		if (PlayerOps_i69_flt_MovementSpeed) {
			if (mult69_0 < 1.40f) mult69_0 += 0.1f;
			return;
		}
		if (PlayerOps_d69_flt_MovementSpeed) {
			if (mult69_0 > 0.0f) mult69_0 -= 0.1f;
			return;
		}

		if (PlayerOps_sweat_plus) { if (mult_self_sweat < 5.5f) mult_self_sweat += 0.1f; return; }
		if (PlayerOps_sweat_minus) { if (mult_self_sweat > 0.0f) mult_self_sweat -= 0.1f; if (mult_self_sweat == 0.0f) { SET_PED_SWEAT(Static_241, mult_self_sweat); CLEAR_PED_WETNESS(Static_241); } return; }

		if (PlayerOps_noiseValue_plus) { if (mult_playerNoiseValue < 10.0f) mult_playerNoiseValue += 0.1f; return; }
		if (PlayerOps_noiseValue_minus) { if (mult_playerNoiseValue > 0.0f) mult_playerNoiseValue -= 0.1f; return; }


	}

	namespace PedConfigFlagManager_catind
	{
		//struct NamedPedFlagS { UINT16 id; std::string title; };
		std::vector<NamedPedFlagS> vPedFlags
		{
			//{ 227, "Play Dead" },
			{ 32, "Can Fall Out Through Windscreen" },
			{ 62, "Is (Nearby) Car (MAY CRASH)" },
			{ 78, "Is Aiming Check" },
			{ 101, "Is Aiming" },
			{ 125, "Has Overflowing Diaper (MAY CRASH)" },
			{ 166, "Is Injured" },
			{ 187, "Is Injured In Combat" },
			{ 223, "Is Short Heighted (Small)" },
			//{ 000000, "" },

		};

		void Sub_FlagList()
		{
			GTAped ped = Static_241;

			AddTitle("Ped Flags");

			AddOption("Custom", null, nullFunc, SUB::PEDFLAGMANAGER_CUSTOM);

			for (auto& f : vPedFlags)
			{
				bool bFlagPressed = false;
				BOOL flagStatus = GET_PED_CONFIG_FLAG(ped.Handle(), f.id, true);
				AddLocal(f.title, flagStatus, bFlagPressed, bFlagPressed); if (bFlagPressed)
				{
					SET_PED_CONFIG_FLAG(ped.Handle(), f.id, !flagStatus);
				}
			}
		}

		int flagID = 0;
		void Sub_CustomFlagSetter()
		{
			GTAped ped = Static_241;
			bool id_input = 0, id_plus = 0, id_minus = 0, id_toggle = 0;
			BOOL flagStatus = GET_PED_CONFIG_FLAG(ped.Handle(), flagID, true);

			AddTitle("Custom");
			AddNumber("ID", flagID, 0, id_input, id_plus, id_minus);
			AddLocal("Status", flagStatus, id_toggle, id_toggle);

			if (id_plus) { if (flagID < INT_MAX) flagID++; }
			if (id_minus) { if (flagID > 0) flagID--; }
			if (id_input)
			{
				std::string inputStr = Game::InputBox("", 10U);
				if (inputStr.length() > 0)
				{
					try { flagID = stoi(inputStr); }
					catch (...) 
					{ 
						Game::Print::PrintError_InvalidInput();
						addlog(ige::LogType::LOG_ERROR, "Invalid flagID entered: " + inputStr, __FILENAME__);
					}
				}
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::PedFlagIdInput, "", 9U);
			}

			if (id_toggle)
				SET_PED_CONFIG_FLAG(ped.Handle(), flagID, !flagStatus);

		}
	}

	void CloneCompanionSub()
	{
		GTAplayer player = Static_240;
		GTAped playerPed = Static_241;

		if (!playerPed.Exists())
		{
			Game::Print::PrintBottomCentre("~r~Error:~s~ No longer in memory.");
			addlog(ige::LogType::LOG_WARNING, "Cannot start clone menu, playerPed No longer in memory", __FILENAME__);
			Menu::SetSub_previous();
			return;
		}

		AddTitle("Cloning");

		bool bCloneNeutralPressed = false;
		AddOption("Clone As Neutral", bCloneNeutralPressed); if (bCloneNeutralPressed)
		{
			GTAped clone = playerPed.Clone(playerPed.Heading_get(), true, true);
			auto cloneNetId = clone.NetID();
			Game::RequestControlOfId(cloneNetId);
			SET_NETWORK_ID_CAN_MIGRATE(cloneNetId, true);
			SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(cloneNetId, true);
			clone.BlockPermanentEvents_set(true);
			SET_PED_COMBAT_ABILITY(cloneNetId, 100);
			clone.MissionEntity_set(true);
			clone.NoLongerNeeded();

			Game::Print::PrintBottomLeft(oss_ << "Cloned ~b~" << player.GetName());
		}

		bool bCloneCompanionPressed = false;
		AddOption("Clone As Companion (7 Max)", bCloneCompanionPressed); if (bCloneCompanionPressed)
		{
			GTAped clone = playerPed.Clone(playerPed.Heading_get(), true, true);
			clone.RequestControl(300);
			auto cloneNetId = clone.NetID();
			Game::RequestControlOfId(cloneNetId);
			SET_NETWORK_ID_CAN_MIGRATE(cloneNetId, true);
			SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(cloneNetId, true);
			//clone.BlockPermanentEvents_set(true);
			SET_PED_COMBAT_ABILITY(cloneNetId, 200);
			Hash weaponToGive = WEAPON_APPISTOL;
			GIVE_DELAYED_WEAPON_TO_PED(clone.Handle(), weaponToGive, 9999, true);
			clone.Weapon_set(weaponToGive);
			clone.FiringPattern_set(FiringPattern::FullAuto);
			clone.ShootRate_set(100);
			sub::Spooner::SpoonerEntity cloneEnt;
			cloneEnt.Dynamic = true;
			cloneEnt.Handle = clone;
			cloneEnt.HashName = player.GetName() + "\'s Clone Companion";
			cloneEnt.IsStill = false;
			cloneEnt.Type = EntityType::PED;
			// Add any other SpoonerEntity attributes
			sub::Spooner::EntityManagement::AddEntityToDb(cloneEnt);
			//clone.MissionEntity_set(false); // To avoid freezing and all. This may cause Spooner invalids, though.

			PedGroup grp;
			if (playerPed.IsInGroup())
			{
				grp = playerPed.CurrentPedGroup_get();
			}
			else
			{
				grp = PedGroup::CreateNewGroup();
				grp.Add(playerPed, true);
			}
			grp.Add(clone, false);
			grp.SeparationRange_set(100.0f);
			grp.FormationSpacing_set(1.5f);

			Game::Print::PrintBottomLeft(oss_ << "Cloned ~b~" << player.GetName() << "~s~ and made the clone " << (playerPed.Gender_get() == Gender::Female ? "her" : "his") << " companion.");
			Game::Print::PrintBottomLeft("Clone added to Spooner Database as a persistent entity.");
		}

		bool bCloneEnemyPressed = false;
		AddOption("Clone As Enemy", bCloneEnemyPressed); if (bCloneEnemyPressed)
		{
			GTAped clone = playerPed.Clone(playerPed.Heading_get(), true, true);
			clone.RequestControl(300);
			auto cloneNetId = clone.NetID();
			Game::RequestControlOfId(cloneNetId);
			SET_NETWORK_ID_CAN_MIGRATE(cloneNetId, true);
			SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(cloneNetId, true);
			clone.BlockPermanentEvents_set(true);
			SET_PED_COMBAT_ABILITY(cloneNetId, 100);
			Hash weaponToGive = WEAPON_APPISTOL;
			GIVE_DELAYED_WEAPON_TO_PED(clone.Handle(), weaponToGive, 9999, true);
			clone.Weapon_set(weaponToGive);
			clone.FiringPattern_set(FiringPattern::FullAuto);
			clone.ShootRate_set(100);
			sub::Spooner::SpoonerEntity cloneEnt;
			cloneEnt.Dynamic = true;
			cloneEnt.Handle = clone;
			cloneEnt.HashName = player.GetName() + "\'s Clone Enemy";
			cloneEnt.IsStill = false;
			cloneEnt.Type = EntityType::PED;
			// Add any other SpoonerEntity attributes
			sub::Spooner::EntityManagement::AddEntityToDb(cloneEnt);
			//clone.MissionEntity_set(false); // To avoid freezing and all. This may cause Spooner invalids, though.
			TASK_COMBAT_PED(clone.Handle(), playerPed.Handle(), 0, 16);

			TaskSequence squ;
			TASK_COMBAT_PED_TIMED(0, playerPed.Handle(), 0, 10000);
			TASK_SHOOT_AT_ENTITY(0, playerPed.Handle(), 10000, FiringPattern::FullAuto);
			TASK_PUT_PED_DIRECTLY_INTO_MELEE(0, playerPed.Handle(), 0.0f, -1.0f, 0.0f, 0);
			TASK_COMBAT_HATED_TARGETS_AROUND_PED(0, 25.0f, 0);
			squ.Close(true); // Repeat task sequence if it ends.
			squ.MakePedPerform(clone);
			clone.AlwaysKeepTask_set(true); // May ruin the task sequence. Not sure.
			squ.Clear();

			//clone.NoLongerNeeded();

			Game::Print::PrintBottomLeft(oss_ << "Cloned ~b~" << player.GetName() << "~s~ and made the clone " << (playerPed.Gender_get() == Gender::Female ? "her" : "his") << " enemy.");
			Game::Print::PrintBottomLeft("Clone added to Spooner Database as a persistent entity.");
		}


	}

}





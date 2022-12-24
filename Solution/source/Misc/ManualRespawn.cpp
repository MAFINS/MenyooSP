/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "ManualRespawn.h"

#include "..\macros.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\Game.h"
#include "..\Menu\Menu.h"

// death model check
#include "..\Scripting\Model.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAped.h"
#include "..\Util\ExePath.h"
#include "..\Scripting\CustomHelpText.h"
#include "..\Scripting\WeaponIndivs.h"

#include "..\Submenus\PedComponentChanger.h"

#include <vector>

namespace _ManualRespawn_
{
	//UINT16 respawnbinds = INPUT_LOOK_BEHIND;

	ManualRespawn::ManualRespawn()
		: inRespawn(false)
	{
	}

	bool ManualRespawn::InRespawn()
	{
		return inRespawn;
	}

	void ManualRespawn::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(false);
		SCRIPT::SET_NO_LOADING_SCREEN(false);
		GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(true);
		GAMEPLAY::SET_FADE_OUT_AFTER_ARREST(true);
	}

	bool ManualRespawn::IsSkipPressed()
	{
		return IS_DISABLED_CONTROL_JUST_PRESSED(0, respawnbinds) != 0;
	}

	inline void ManualRespawn::ShowRespawnHelpText()
	{
		//there has to be a better way to get the controller string than this
		const std::string controllerbinds[] = 
		{
			"NEXT_CAMERA",
			"LOOK_LR",
			"LOOK_UD",
			"LOOK_UP_ONLY",
			"LOOK_DOWN_ONLY",
			"LOOK_LEFT_ONLY",
			"LOOK_RIGHT_ONLY",
			"CINEMATIC_SLOWMO",
			"SCRIPTED_FLY_UD",
			"SCRIPTED_FLY_LR",
			"SCRIPTED_FLY_ZUP",
			"SCRIPTED_FLY_ZDOWN",
			"WEAPON_WHEEL_UD",
			"WEAPON_WHEEL_LR",
			"WEAPON_WHEEL_NEXT",
			"WEAPON_WHEEL_PREV",
			"SELECT_NEXT_WEAPON",
			"SELECT_PREV_WEAPON",
			"SKIP_CUTSCENE",
			"CHARACTER_WHEEL",
			"MULTIPLAYER_INFO",
			"SPRINT",
			"JUMP",
			"ENTER",
			"ATTACK",
			"AIM",
			"LOOK_BEHIND",
			"PHONE",
			"SPECIAL_ABILITY",
			"SPECIAL_ABILITY_SECONDARY",
			"MOVE_LR",
			"MOVE_UD",
			"MOVE_UP_ONLY",
			"MOVE_DOWN_ONLY",
			"MOVE_LEFT_ONLY",
			"MOVE_RIGHT_ONLY",
			"DUCK",
			"SELECT_WEAPON",
			"PICKUP",
			"SNIPER_ZOOM",
			"SNIPER_ZOOM_IN_ONLY",
			"SNIPER_ZOOM_OUT_ONLY",
			"SNIPER_ZOOM_IN_SECONDARY",
			"SNIPER_ZOOM_OUT_SECONDARY",
			"COVER",
			"RELOAD",
			"TALK",
			"DETONATE",
			"HUD_SPECIAL",
			"ARREST",
			"ACCURATE_AIM",
			"CONTEXT",
			"CONTEXT_SECONDARY",
			"WEAPON_SPECIAL",
			"WEAPON_SPECIAL_TWO",
			"DIVE",
			"DROP_WEAPON",
			"DROP_AMMO",
			"THROW_GRENADE",
			"VEH_MOVE_LR",
			"VEH_MOVE_UD",
			"VEH_MOVE_UP_ONLY",
			"VEH_MOVE_DOWN_ONLY",
			"VEH_MOVE_LEFT_ONLY",
			"VEH_MOVE_RIGHT_ONLY",
			"VEH_SPECIAL",
			"VEH_GUN_LR",
			"VEH_GUN_UD",
			"VEH_AIM",
			"VEH_ATTACK",
			"VEH_ATTACK2",
			"VEH_ACCELERATE",
			"VEH_BRAKE",
			"VEH_DUCK",
			"VEH_HEADLIGHT",
			"VEH_EXIT",
			"VEH_HANDBRAKE",
			"VEH_HOTWIRE_LEFT",
			"VEH_HOTWIRE_RIGHT",
			"VEH_LOOK_BEHIND",
			"VEH_CIN_CAM",
			"VEH_NEXT_RADIO",
			"VEH_PREV_RADIO",
			"VEH_NEXT_RADIO_TRACK",
			"VEH_PREV_RADIO_TRACK",
			"VEH_RADIO_WHEEL",
			"VEH_HORN",
			"VEH_FLY_THROTTLE_UP",
			"VEH_FLY_THROTTLE_DOWN",
			"VEH_FLY_YAW_LEFT",
			"VEH_FLY_YAW_RIGHT",
			"VEH_PASSENGER_AIM",
			"VEH_PASSENGER_ATTACK",
			"VEH_SPECIAL_ABILITY_FRANKLIN",
			"VEH_STUNT_UD",
			"VEH_CINEMATIC_UD",
			"VEH_CINEMATIC_UP_ONLY",
			"VEH_CINEMATIC_DOWN_ONLY",
			"VEH_CINEMATIC_LR",
			"VEH_SELECT_NEXT_WEAPON",
			"VEH_SELECT_PREV_WEAPON",
			"VEH_ROOF",
			"VEH_JUMP",
			"VEH_GRAPPLING_HOOK",
			"VEH_SHUFFLE",
			"VEH_DROP_PROJECTILE",
			"VEH_MOUSE_CONTROL_OVERRIDE",
			"VEH_FLY_ROLL_LR",
			"VEH_FLY_ROLL_LEFT_ONLY",
			"VEH_FLY_ROLL_RIGHT_ONLY",
			"VEH_FLY_PITCH_UD",
			"VEH_FLY_PITCH_UP_ONLY",
			"VEH_FLY_PITCH_DOWN_ONLY",
			"VEH_FLY_UNDERCARRIAGE",
			"VEH_FLY_ATTACK",
			"VEH_FLY_SELECT_NEXT_WEAPON",
			"VEH_FLY_SELECT_PREV_WEAPON",
			"VEH_FLY_SELECT_TARGET_LEFT",
			"VEH_FLY_SELECT_TARGET_RIGHT",
			"VEH_FLY_VERTICAL_FLIGHT_MODE",
			"VEH_FLY_DUCK",
			"VEH_FLY_ATTACK_CAMERA",
			"VEH_FLY_MOUSE_CONTROL_OVERRIDE",
			"VEH_SUB_TURN_LR",
			"VEH_SUB_TURN_LEFT_ONLY",
			"VEH_SUB_TURN_RIGHT_ONLY",
			"VEH_SUB_PITCH_UD",
			"VEH_SUB_PITCH_UP_ONLY",
			"VEH_SUB_PITCH_DOWN_ONLY",
			"VEH_SUB_THROTTLE_UP",
			"VEH_SUB_THROTTLE_DOWN",
			"VEH_SUB_ASCEND",
			"VEH_SUB_DESCEND",
			"VEH_SUB_TURN_HARD_LEFT",
			"VEH_SUB_TURN_HARD_RIGHT",
			"VEH_SUB_MOUSE_CONTROL_OVERRIDE",
			"VEH_PUSHBIKE_PEDAL",
			"VEH_PUSHBIKE_SPRINT",
			"VEH_PUSHBIKE_FRONT_BRAKE",
			"VEH_PUSHBIKE_REAR_BRAKE",
			"MELEE_ATTACK_LIGHT",
			"MELEE_ATTACK_HEAVY",
			"MELEE_ATTACK_ALTERNATE",
			"MELEE_BLOCK",
			"PARACHUTE_DEPLOY",
			"PARACHUTE_DETACH",
			"PARACHUTE_TURN_LR",
			"PARACHUTE_TURN_LEFT_ONLY",
			"PARACHUTE_TURN_RIGHT_ONLY",
			"PARACHUTE_PITCH_UD",
			"PARACHUTE_PITCH_UP_ONLY",
			"PARACHUTE_PITCH_DOWN_ONLY",
			"PARACHUTE_BRAKE_LEFT",
			"PARACHUTE_BRAKE_RIGHT",
			"PARACHUTE_SMOKE",
			"PARACHUTE_PRECISION_LANDING",
			"MAP",
			"SELECT_WEAPON_UNARMED",
			"SELECT_WEAPON_MELEE",
			"SELECT_WEAPON_HANDGUN",
			"SELECT_WEAPON_SHOTGUN",
			"SELECT_WEAPON_SMG",
			"SELECT_WEAPON_AUTO_RIFLE",
			"SELECT_WEAPON_SNIPER",
			"SELECT_WEAPON_HEAVY",
			"SELECT_WEAPON_SPECIAL",
			"SELECT_CHARACTER_MICHAEL",
			"SELECT_CHARACTER_FRANKLIN",
			"SELECT_CHARACTER_TREVOR",
			"SELECT_CHARACTER_MULTIPLAYER",
			"SAVE_REPLAY_CLIP",
			"SPECIAL_ABILITY_PC",
			"CELLPHONE_UP",
			"CELLPHONE_DOWN",
			"CELLPHONE_LEFT",
			"CELLPHONE_RIGHT",
			"CELLPHONE_SELECT",
			"CELLPHONE_CANCEL",
			"CELLPHONE_OPTION",
			"CELLPHONE_EXTRA_OPTION",
			"CELLPHONE_SCROLL_FORWARD",
			"CELLPHONE_SCROLL_BACKWARD",
			"CELLPHONE_CAMERA_FOCUS_LOCK",
			"CELLPHONE_CAMERA_GRID",
			"CELLPHONE_CAMERA_SELFIE",
			"CELLPHONE_CAMERA_DOF",
			"CELLPHONE_CAMERA_EXPRESSION",
			"FRONTEND_DOWN",
			"FRONTEND_UP",
			"FRONTEND_LEFT",
			"FRONTEND_RIGHT",
			"FRONTEND_RDOWN",
			"FRONTEND_RUP",
			"FRONTEND_RLEFT",
			"FRONTEND_RRIGHT",
			"FRONTEND_AXIS_X",
			"FRONTEND_AXIS_Y",
			"FRONTEND_RIGHT_AXIS_X",
			"FRONTEND_RIGHT_AXIS_Y",
			"FRONTEND_PAUSE",
			"FRONTEND_PAUSE_ALTERNATE",
			"FRONTEND_ACCEPT",
			"FRONTEND_CANCEL",
			"FRONTEND_X",
			"FRONTEND_Y",
			"FRONTEND_LB",
			"FRONTEND_RB",
			"FRONTEND_LT",
			"FRONTEND_RT",
			"FRONTEND_LS",
			"FRONTEND_RS",
			"FRONTEND_LEADERBOARD",
			"FRONTEND_SOCIAL_CLUB",
			"FRONTEND_SOCIAL_CLUB_SECONDARY",
			"FRONTEND_DELETE",
			"FRONTEND_ENDSCREEN_ACCEPT",
			"FRONTEND_ENDSCREEN_EXPAND",
			"FRONTEND_SELECT",
			"SCRIPT_LEFT_AXIS_X",
			"SCRIPT_LEFT_AXIS_Y",
			"SCRIPT_RIGHT_AXIS_X",
			"SCRIPT_RIGHT_AXIS_Y",
			"SCRIPT_RUP",
			"SCRIPT_RDOWN",
			"SCRIPT_RLEFT",
			"SCRIPT_RRIGHT",
			"SCRIPT_LB",
			"SCRIPT_RB",
			"SCRIPT_LT",
			"SCRIPT_RT",
			"SCRIPT_LS",
			"SCRIPT_RS",
			"SCRIPT_PAD_UP",
			"SCRIPT_PAD_DOWN",
			"SCRIPT_PAD_LEFT",
			"SCRIPT_PAD_RIGHT",
			"SCRIPT_SELECT",
			"CURSOR_ACCEPT",
			"CURSOR_CANCEL",
			"CURSOR_X",
			"CURSOR_Y",
			"CURSOR_SCROLL_UP",
			"CURSOR_SCROLL_DOWN",
			"ENTER_CHEAT_CODE",
			"INTERACTION_MENU",
			"MP_TEXT_CHAT_ALL",
			"MP_TEXT_CHAT_TEAM",
			"MP_TEXT_CHAT_FRIENDS",
			"MP_TEXT_CHAT_CREW",
			"PUSH_TO_TALK",
			"CREATOR_LS",
			"CREATOR_RS",
			"CREATOR_LT",
			"CREATOR_RT",
			"CREATOR_MENU_TOGGLE",
			"CREATOR_ACCEPT",
			"CREATOR_DELETE",
			"ATTACK2",
			"RAPPEL_JUMP",
			"RAPPEL_LONG_JUMP",
			"RAPPEL_SMASH_WINDOW",
			"PREV_WEAPON",
			"NEXT_WEAPON",
			"MELEE_ATTACK1",
			"MELEE_ATTACK2",
			"WHISTLE",
			"MOVE_LEFT",
			"MOVE_RIGHT",
			"MOVE_UP",
			"MOVE_DOWN",
			"LOOK_LEFT",
			"LOOK_RIGHT",
			"LOOK_UP",
			"LOOK_DOWN",
			"SNIPER_ZOOM_IN",
			"SNIPER_ZOOM_OUT",
			"SNIPER_ZOOM_IN_ALTERNATE",
			"SNIPER_ZOOM_OUT_ALTERNATE",
			"VEH_MOVE_LEFT",
			"VEH_MOVE_RIGHT",
			"VEH_MOVE_UP",
			"VEH_MOVE_DOWN",
			"VEH_GUN_LEFT",
			"VEH_GUN_RIGHT",
			"VEH_GUN_UP",
			"VEH_GUN_DOWN",
			"VEH_LOOK_LEFT",
			"VEH_LOOK_RIGHT",
			"REPLAY_START_STOP_RECORDING",
			"REPLAY_START_STOP_RECORDING_SECONDARY",
			"SCALED_LOOK_LR",
			"SCALED_LOOK_UD",
			"SCALED_LOOK_UP_ONLY",
			"SCALED_LOOK_DOWN_ONLY",
			"SCALED_LOOK_LEFT_ONLY",
			"SCALED_LOOK_RIGHT_ONLY",
			"REPLAY_MARKER_DELETE",
			"REPLAY_CLIP_DELETE",
			"REPLAY_PAUSE",
			"REPLAY_REWIND",
			"REPLAY_FFWD",
			"REPLAY_NEWMARKER",
			"REPLAY_RECORD",
			"REPLAY_SCREENSHOT",
			"REPLAY_HIDEHUD",
			"REPLAY_STARTPOINT",
			"REPLAY_ENDPOINT",
			"REPLAY_ADVANCE",
			"REPLAY_BACK",
			"REPLAY_TOOLS",
			"REPLAY_RESTART",
			"REPLAY_SHOWHOTKEY",
			"REPLAY_CYCLEMARKERLEFT",
			"REPLAY_CYCLEMARKERRIGHT",
			"REPLAY_FOVINCREASE",
			"REPLAY_FOVDECREASE",
			"REPLAY_CAMERAUP",
			"REPLAY_CAMERADOWN",
			"REPLAY_SAVE",
			"REPLAY_TOGGLETIME",
			"REPLAY_TOGGLETIPS",
			"REPLAY_PREVIEW",
			"REPLAY_TOGGLE_TIMELINE",
			"REPLAY_TIMELINE_PICKUP_CLIP",
			"REPLAY_TIMELINE_DUPLICATE_CLIP",
			"REPLAY_TIMELINE_PLACE_CLIP",
			"REPLAY_CTRL",
			"REPLAY_TIMELINE_SAVE",
			"REPLAY_PREVIEW_AUDIO",
			"VEH_DRIVE_LOOK",
			"VEH_DRIVE_LOOK2",
			"VEH_FLY_ATTACK2",
			"RADIO_WHEEL_UD",
			"RADIO_WHEEL_LR",
			"VEH_SLOWMO_UD",
			"VEH_SLOWMO_UP_ONLY",
			"VEH_SLOWMO_DOWN_ONLY",
			"MAP_POI",
		};

		std::string bindsname = controllerbinds[respawnbinds];
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0, 0.4f), false, true, false, RGBA(255, 255, 255, 190));
		Game::Print::drawstring("Press ~b~[" + bindsname + "]~s~ to respawn.", NULL, 0.1f);
		//Game::Print::drawstring("Press ~b~[" + std::to_string(static_cast<ControllerInputs>(respawnbinds)).substr(6) + "]~s~to respawn.", NULL, 0.1f);
		//Game::CustomHelpText::ShowTimedText(oss_ << "Press " << "~INPUT_LOOK_BEHIND~" << " to respawn.", 100);
	}

	void ManualRespawn::Tick()
	{
		if (bEnabled)
		{
			DoManualRespawnTick();
		}
	}
	inline void ManualRespawn::DoManualRespawnTick()
	{
		auto player = PLAYER_ID();

		if (IS_PLAYER_DEAD(player))// || IS_PLAYER_BEING_ARRESTED(player, true))
		{
			if (IsSkipPressed())
			{
				_DISABLE_AUTOMATIC_RESPAWN(false);
				SET_NO_LOADING_SCREEN(false);
				SET_FADE_OUT_AFTER_DEATH(true);
				SET_FADE_OUT_AFTER_ARREST(true);
				DO_SCREEN_FADE_OUT(4000);
				inRespawn = true;
			}
			else if (!inRespawn)
			{
				_DISABLE_AUTOMATIC_RESPAWN(true);
				SET_NO_LOADING_SCREEN(true);
				SET_FADE_OUT_AFTER_DEATH(false);
				SET_FADE_OUT_AFTER_ARREST(false);
				if (IS_SCREEN_FADING_OUT()) DO_SCREEN_FADE_IN(100);
				ShowRespawnHelpText();
			}
		}
		else
		{
			inRespawn = false;
		}

	}


	ManualRespawn g_manualRespawn;

	void ToggleOnOff()
	{
		g_manualRespawn.Toggle();
	}


	void Check_self_death_model()
	{
		GTAped playerPed = PLAYER_PED_ID();
		
		if (!playerPed.Exists())
			return;

		GTAplayer player = PLAYER_ID();

		bool is_death = playerPed.IsDead();
		bool is_arrest = IS_PLAYER_BEING_ARRESTED(player.Handle(), true) != 0;

		if ((!is_death && !is_arrest) || _ManualRespawn_::g_manualRespawn.InRespawn())
			return;
		if (_GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(0xCAC8014F) > 0)//director_mode.ysc
			return;

		Model& model = playerPed.Model();
		Model orig_model;


		if (model.hash != PedHash::Michael && model.hash != PedHash::Franklin && model.hash != PedHash::Trevor)
		{
			std::vector<s_Weapon_Components_Tint> weaponsBackup;
			playerPed.StoreWeaponsInArray(weaponsBackup);

			/*int did[12], tid[12], did2[10], tid2[10];
			for (i = 0; i<12; i++)
			{
			did[i] = GET_PED_DRAWABLE_VARIATION(playerPed, i);
			tid[i] = GET_PED_TEXTURE_VARIATION(playerPed, i);
			}
			for (i = 0; i<10; i++)
			{
			did2[i] = GET_PED_PROP_INDEX(playerPed, i);
			tid2[i] = GET_PED_PROP_TEXTURE_INDEX(playerPed, i);
			}*/

			std::string& ofn = GetPathffA(Pathff::Outfit, true) + "_reserved.xml";
			sub::ComponentChanger_Outfit_catind::Create(PLAYER_PED_ID(), ofn);


			if (is_death)
				WAIT(8500); // wait until screen turns black
			else // is_arrest
				WAIT(10000); // wait until screen turns black

			// load a default model
			orig_model = PedHash::Michael;
			orig_model.LoadAndWait();
			SET_PLAYER_MODEL(PLAYER_ID(), orig_model.hash);
			SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER_PED_ID());
			orig_model.Unload();

			// wait until player has resurrected
			if (is_death)
				while (GET_TIME_SINCE_LAST_DEATH() <= 0 || GET_TIME_SINCE_LAST_DEATH() > 6000)
					WAIT(0);
			else
				while (GET_TIME_SINCE_LAST_ARREST() <= 0 || GET_TIME_SINCE_LAST_ARREST() > 6000)
					WAIT(0);

			while (!player.IsControlOn())
				WAIT(0);

			// change back the model
			sub::ComponentChanger_Outfit_catind::Apply(PLAYER_PED_ID(), ofn, true, true, true, true, true, false);

			WAIT(0);

			player = PLAYER_ID();
			playerPed = PLAYER_PED_ID();

			playerPed.GiveWeaponsFromArray(weaponsBackup);

			Game::CustomHelpText::ShowTimedText("If you are having issues at this point, load a saved game.", 7000);
		}


	}

}




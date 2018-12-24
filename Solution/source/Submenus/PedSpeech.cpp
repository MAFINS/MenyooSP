/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PedSpeech.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\ExePath.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Game.h"
#include "..\Util\StringManip.h"

#include <string>
#include <array>
#include <vector>
#include <set>
#include <simpleini\SimpleIni.h>

namespace sub
{
	namespace Speech_catind
	{
#pragma region ambient speech names old
		//struct SpeechNameS { std::string title, label; };
		std::vector<SpeechNameS> vSpeechNames
		{
			{ "Whimper", "WHIMPER" },
			{ "Cheer", "GENERIC_CHEER" },
			{ "Greet", "SHOP_GREET" },
			{ "Greet Start", "SHOP_GREET_START" },
			{ "Greet End", "SHOP_GREET_END" },
			{ "Brave", "SHOP_BRAVE" },
			{ "Remove Vehicle", "SHOP_REMOVE_VEHICLE" },
			{ "React To Shout", "SHOP_REACT_TO_SHOUT" },
			{ "Hurrying", "SHOP_HURRYING" },
			{ "No Cops", "SHOP_NO_COPS" },
			{ "No Cops Start", "SHOP_NO_COPS_START" },
			{ "No Cops End", "SHOP_NO_COPS_END" },
			{ "Cops Arrived", "SHOP_COPS_ARRIVED" },
			{ "Threatened", "SHOP_THREATENED" },
			{ "Scared", "SHOP_SCARED" },
			{ "Scared Start", "SHOP_SCARED_START" },
			{ "Scared End", "SHOP_SCARED_END" },
			{ "Sell", "SHOP_SELL" },
			{ "No Entry", "SHOP_NO_ENTRY" },
			{ "Steal", "SHOP_STEAL" },
			{ "Panic", "SCREAM_PANIC" },
			{ "Scream", "SCREAM_TERROR" },
			{ "Falling", "SUPER_HIGH_FALL" },
			{ "DFAH", "AR2_DFAH" },
			{ "Generic High", "GENERIC_FRIGHTENED_HIGH" },
			{ "Franklin's Dying", "BUDDY_SEES_FRANKLIN_DEATH" },
			{ "Michael's Dying", "BUDDY_SEES_MICHAEL_DEATH" },
			{ "Trevor's Dying", "BUDDY_SEES_TREVOR_DEATH" },
			{ "Threaten", "CHALLENGE_THREATEN" },
			{ "Stare", "PROVOKE_STARING" },
			{ "Beg", "GUN_BEG" },
			{ "Curse Med", "GENERIC_CURSE_MED" },
			{ "Insult Med", "GENERIC_INSULT_MED" },
			{ "Chat", "CHAT_STATE" },
			{ "EPS ANAA", "EPS8_ANAA" },
			{ "EPS AOAA", "EPS8_AOAA" },
			{ "EPS APAA", "EPS8_APAA" },
			{ "Arrest Player", "ARREST_PLAYER" },
			{ "Bump", "BUMP" },
			{ "Josh BCAA", "JOSH2_BCAA" },
			{ "Nigel CXAA", "NIGE3_CXAA" },
			{ "Pap APAA", "PAP3A_APAA" },
			{ "Pap AOAF", "PAP3A_AOAF" },
			{ "Pap BFAA", "PAP3B_BFAA" },
			{ "Pap BCAA", "PAP3B_BCAA" },
			{ "Pap BDAA", "PAP3B_BDAA" },
			{ "Pap GDAA", "T1M1_GDAA" },
			{ "Wanted Level", "GET_WANTED_LEVEL" },
			{ "Taxi Fail", "TAXI_FAIL" },
			{ "Taxi No Pay", "TAXI_NO_PAY" },
			{ "Call Cops", "CALL_COPS_COMMIT" },
			{ "Crash", "CRASH_GENERIC" },
			{ "Hit Ped", "CAR_HIT_PED_DRIVEN" },
			{ "Car Flipped", "VEHICLE_FLIPPED" },
			{ "Police Persuit", "POLICE_PURSUIT_DRIVEN" },
			{ "Apologize", "APOLOGY_NO_TROUBLE" },
			{ "Cough", "COUGH" },
			{ "PRO FLAA", "PRO_FLAA" },
			{ "PRO FLAB", "PRO_FLAB" },
			{ "PRO FLAC", "PRO_FLAC" },
			{ "PRO FLAD", "PRO_FLAD" },
			{ "Dismiss Michael (Amanda)", "DISMISS_MICHAEL" },

		};

#pragma endregion
#pragma region ambient speech voice names old
		//struct VoiceNameS { std::string title, label; };
		std::vector<VoiceNameS> vVoiceNames
		{
			{ "No Voice", "NO_VOICE" },
			{ "Male Pain", "WAVELOAD_PAIN_MALE" },
			{ "Female Pain", "WAVELOAD_PAIN_FEMALE" },
			{ "Sheriff", "S_M_Y_SHERIFF_01_WHITE_FULL_01" },
			{ "Maude", "MAUDE" },
			{ "Franklin Normal", "FRANKLIN_NORMAL" },
			{ "Michael Normal", "MICHAEL_NORMAL" },
			{ "Trevor Normal", "TREVOR_NORMAL" },
			{ "White Cop 1", "S_M_Y_Cop_01_WHITE_FULL_02" },
			{ "Vinewood Black 2", "A_M_Y_BevHills_02_Black_FULL_01" },
			{ "Hillbilly 1 3", "A_M_M_HILLBILLY_01_WHITE_MINI_03" },
			{ "Hillbilly 1 2", "A_M_M_HILLBILLY_01_WHITE_MINI_02" },
			{ "Hillbilly 2 2", "A_M_M_HillBilly_02_WHITE_MINI_02" },
			{ "Hillbilly 2 3", "A_M_M_HILLBILLY_02_WHITE_MINI_03" },
			{ "Shop Mask White 1", "S_M_Y_SHOP_MASK_WHITE_MINI_01" },
			{ "Shop Assistant", "SHOPASSISTANT" },
			{ "EPS Guard 2", "EPSGUARD2" },
			{ "EPS Guard 7", "EPSGUARD7" },
			{ "EPS Guard 8", "EPSGUARD8" },
			{ "Black Trucker", "S_M_M_TRUCKER_01_BLACK_FULL_02" },
			{ "Avery", "AVERY" },
			{ "Dinapoli", "DINAPOLI" },
			{ "Paparazzi Cop 3", "PAPARAZZO3ACOP3" },
			{ "Paparazzi Bodyguard 1", "PAPARAZZO3BBODYGUARD1" },
			{ "Ortega", "ORTEGA" },
			{ "Tonya", "TONYA" },
			{ "Pro victim 1", "PROVICTIM1" },
			{ "Manuel", "MANUEL" },
			{ "Alien", "ALIENS" },
			{ "Clown", "CLOWNS" },
			{ "Hao", "HAO" },
			{ "Amanda Drunk", "AMANDA_DRUNK" },
			{ "Amanda Normal", "AMANDA_NORMAL" },
			{ "Lamar Drunk", "LAMAR_DRUNK" },
			{ "Lamar Normal", "LAMAR_NORMAL" },
			{ "Generic Security Latino 1", "S_M_M_GENERICSECURITY_01_LATINO_MINI_01" },
			{ "Generic Security Latino 2", "S_M_M_GENERICSECURITY_01_LATINO_MINI_02" },
			{ "Armlieut Armenian 1", "G_M_M_ARMLIEUT_01_WHITE_ARMENIAN_MINI_01" },
			{ "Lost 3 1", "G_M_Y_LOST_03_WHITE_FULL_01" },
			{ "Salvadorian 3", "G_M_Y_SALVAGOON_01_SALVADORIAN_MINI_03" },
			{ "Latino 1 2", "G_M_Y_LATINO01_LATINO_MINI_02" },
			{ "Melvin", "MELVIN" },
			{ "Ammunation 1", "S_M_M_AMMUCOUNTRY_WHITE_MINI_01" },
			{ "Ammunation 2", "AMMUCITY" },
			{ "Ammunation 3", "S_M_Y_AMMUCITY_01_WHITE_MINI_01" },
			{ "Black Hair Dresser", "S_M_M_HAIRDRESSER_01_BLACK_MINI_01" },
			{ "Female Barber", "S_F_M_FEMBARBER_BLACK_MINI_01" },
			{ "Street Punk", "G_M_Y_StreetPunk_01_BLACK_MINI_03" },
			{ "Beach Latino", "A_M_Y_BeachVesp_01_LATINO_MINI_01" },
			{ "Beach White", "A_M_Y_BeachVesp_01_White_Mini_01" },
			{ "Worker", "S_M_Y_GENERICWORKER_01_WHITE_01" },
			{ "Drunk AI", "REDR1Drunk1_AI_Drunk" },
			{ "Black Tramp", "A_M_M_TRAMP_01_BLACK_MINI_01" },
			{ "Vagos", "G_F_Y_Vagos_01_LATINO_MINI_02" },
			{ "Packite", "PACKIE_AI_Norm_Part1_Booth" },
			{ "Chinese Businessman", "A_M_Y_Business_01_CHINESE_MINI_01" },
			{ "Lacy", "LACEY" },
			{ "Lost", "REPRI1Lost" },
			{ "Lost Girl", "LostKidnapGirl" },
			{ "Ranger", "S_M_Y_RANGER_01_WHITE_FULL_01" },
			{ "Armed Goon", "G_M_Y_ArmGoon_02_White_Armenian_MINI_01" },
			{ "Korean 1", "G_M_Y_KorLieut_01_Korean_MINI_01" },
			{ "Korean 2", "G_M_Y_Korean_01_Korean_MINI_02" },
			{ "Groom", "GROOM" },
			{ "White Male DJ", "MALE_STRIP_DJ_WHITE" },
			{ "Latino Bouncer", "S_M_M_BOUNCER_LATINO_FULL_01" },
			{ "Tattoo Guy", "U_M_Y_TATTOO_01_WHITE_MINI_01" },
			{ "Taxi OJ", "TaxiOJCop1" },
			{ "Taxi Liz", "TaxiLiz" },
			{ "Taxi Bruce", "TaxiBruce" },
			{ "Taxi Dom", "TaxiDom" },
			{ "Taxi Gang Male", "TaxiGangM" },
			{ "Taxi Gang Girl 1", "TaxiGangGirl1" },
			{ "Taxi Gang Girl 2", "TaxiGangGirl2" },

		};
#pragma endregion
#pragma region ambient speech data organised old
		//struct AmbientSpeechDataS { std::string title, voiceName, speechName, paramName; };
		const std::vector<AmbientSpeechDataS> vSpeechData
		{
			{ "Frightened", "MAUDE", "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE" },
			{ "Whimper (Male)", "WAVELOAD_PAIN_MALE", "WHIMPER", "SPEECH_PARAMS_FORCE_NORMAL" },
			{ "Whimper (Female)", "WAVELOAD_PAIN_FEMALE", "WHIMPER", "SPEECH_PARAMS_FORCE_NORMAL" },
			{ "Scream Panic (Male)", "WAVELOAD_PAIN_MALE", "SCREAM_PANIC", "SPEECH_PARAMS_FORCE_SHOUTED" },
			//{ "Scream Panic (Female)", "WAVELOAD_PAIN_FEMALE", "SCREAM_PANIC", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Scream Terror (Male)", "WAVELOAD_PAIN_MALE", "SCREAM_TERROR", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Scream Terror (Female)", "WAVELOAD_PAIN_FEMALE", "SCREAM_TERROR", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Scream Falling (Male)", "WAVELOAD_PAIN_MALE", "SUPER_HIGH_FALL", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Scream Falling (Female)", "WAVELOAD_PAIN_FEMALE", "SUPER_HIGH_FALL", "SPEECH_PARAMS_FORCE_SHOUTED" },
			//{ "Threaten (Shout)", "FIBConstruction", "SHOUT_THREATEN", "SPEECH_PARAMS_FORCE_SHOUTED_CLEAR" },
			{ "Threaten (Challenge)", "S_M_Y_Cop_01_WHITE_FULL_02", "CHALLENGE_THREATEN", "SPEECH_PARAMS_FORCE" },
			{ "Provoke Staring", "S_M_Y_Cop_01_WHITE_FULL_02", "PROVOKE_STARING", "SPEECH_PARAMS_FORCE" },
			{ "Arrest Player (White)", "S_M_Y_COP_01_WHITE_MINI_03", "ARREST_PLAYER", "SPEECH_PARAMS_FORCE" },
			{ "Arrest Player (Black)", "S_M_Y_COP_01_BLACK_MINI_04", "ARREST_PLAYER", "SPEECH_PARAMS_FORCE" },
			{ "Bump (White)", "S_M_Y_COP_01_WHITE_MINI_03", "BUMP", "SPEECH_PARAMS_FORCE" },
			{ "Bump (Black)", "S_M_Y_COP_01_BLACK_MINI_04", "BUMP", "SPEECH_PARAMS_FORCE" },
			{ "Beg", "A_M_Y_BevHills_02_Black_FULL_01", "GUN_BEG", "SPEECH_PARAMS_FORCE" },
			//{ "Run (Shout)", "FIBConstruction", "FIGHT_RUN", "SPEECH_PARAMS_FORCE_SHOUTED_CLEAR" },
			{ "Generic Cheer 1", "A_M_M_Hillbilly_01_White_mini_02", "generic_cheer", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Generic Cheer 2", "A_M_M_Hillbilly_01_White_mini_03", "generic_cheer", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Generic Curse Medium 1", "A_M_M_Hillbilly_01_White_mini_03", "GENERIC_CURSE_MED", "SPEECH_PARAMS_FORCE_SHOUTED" },
			//{ "Generic Curse Medium 2", "S_M_M_TRUCKER_01_BLACK_FULL_02", "GENERIC_CURSE_MED", "SPEECH_PARAMS_FORCE" },
			//{ "Generic Curse High", "S_M_M_TRUCKER_01_BLACK_FULL_02", "GENERIC_CURSE_HIGH", "SPEECH_PARAMS_FORCE" },
			//{ "Generic Frightened Medium", "S_M_M_TRUCKER_01_BLACK_FULL_02", "GENERIC_FRIGHTENED_MED", "SPEECH_PARAMS_FORCE" },
			//{ "Generic Frightened High", "S_M_M_TRUCKER_01_BLACK_FULL_02", "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE" },
			{ "Generic Insult", "A_M_M_Hillbilly_01_White_mini_03", "GENERIC_INSULT_MED", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Chat State", "A_M_M_Hillbilly_01_White_mini_03", "CHAT_STATE", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Greet (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_GREET", "SPEECH_PARAMS_FORCE" },
			{ "Greet (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_GREET", "SPEECH_PARAMS_FORCE" },
			{ "Greet (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_GREET", "SPEECH_PARAMS_FORCE" },
			{ "Brave (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_BRAVE", "SPEECH_PARAMS_FORCE" },
			{ "Brave (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_BRAVE", "SPEECH_PARAMS_FORCE" },
			{ "Brave (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_BRAVE", "SPEECH_PARAMS_FORCE" },
			{ "Remove Vehicle (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_REMOVE_VEHICLE", "SPEECH_PARAMS_FORCE" },
			{ "Remove Vehicle (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_REMOVE_VEHICLE", "SPEECH_PARAMS_FORCE" },
			{ "Remove Vehicle (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_REMOVE_VEHICLE", "SPEECH_PARAMS_FORCE" },
			{ "React To Shout (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_REACT_TO_SHOUT", "SPEECH_PARAMS_FORCE" },
			{ "React To Shout (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_REACT_TO_SHOUT", "SPEECH_PARAMS_FORCE" },
			{ "React To Shout (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_REACT_TO_SHOUT", "SPEECH_PARAMS_FORCE" },
			{ "Hurrying (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_HURRYING", "SPEECH_PARAMS_FORCE" },
			{ "Hurrying (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_HURRYING", "SPEECH_PARAMS_FORCE" },
			{ "Hurrying (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_HURRYING", "SPEECH_PARAMS_FORCE" },
			{ "No Cops (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_NO_COPS", "SPEECH_PARAMS_FORCE" },
			{ "No Cops (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_NO_COPS", "SPEECH_PARAMS_FORCE" },
			{ "No Cops (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_NO_COPS", "SPEECH_PARAMS_FORCE" },
			{ "Threatened (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_THREATENED", "SPEECH_PARAMS_FORCE" },
			{ "Threatened (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_THREATENED", "SPEECH_PARAMS_FORCE" },
			{ "Threatened (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_THREATENED", "SPEECH_PARAMS_FORCE" },
			{ "Sell (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_SELL", "SPEECH_PARAMS_FORCE" },
			{ "Sell (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_SELL", "SPEECH_PARAMS_FORCE" },
			{ "Sell (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_SELL", "SPEECH_PARAMS_FORCE" },
			{ "No Entry (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_NO_ENTRY", "SPEECH_PARAMS_FORCE" },
			{ "No Entry (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_NO_ENTRY", "SPEECH_PARAMS_FORCE" },
			{ "No Entry (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_NO_ENTRY", "SPEECH_PARAMS_FORCE" },
			{ "Steal (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SHOP_STEAL", "SPEECH_PARAMS_FORCE" },
			{ "Steal (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SHOP_STEAL", "SPEECH_PARAMS_FORCE" },
			{ "Steal (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SHOP_STEAL", "SPEECH_PARAMS_FORCE" },
			//{ "Scream (Indian)", "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", "SCREAM_PANIC", "SPEECH_PARAMS_FORCE" },
			//{ "Scream (Latino)", "MP_M_SHOPKEEP_01_LATINO_MINI_01", "SCREAM_PANIC", "SPEECH_PARAMS_FORCE" },
			//{ "Scream (Asian)", "MP_M_SHOPKEEP_01_CHINESE_MINI_01", "SCREAM_PANIC", "SPEECH_PARAMS_FORCE" },
			{ "Dfah (Shout)", "ARM2bum", "AR2_DFAH", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Franklin Sees Trevor Dying", "FRANKLIN_NORMAL", "BUDDY_SEES_TREVOR_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "Franklin Sees Michael Dying", "FRANKLIN_NORMAL", "BUDDY_SEES_MICHAEL_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "Trevor Sees Franklin Dying", "TREVOR_NORMAL", "BUDDY_SEES_FRANKLIN_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "Trevor Sees Michael Dying", "TREVOR_NORMAL", "BUDDY_SEES_MICHAEL_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "Michael Sees Franklin Dying", "MICHAEL_NORMAL", "BUDDY_SEES_FRANKLIN_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "Michael Sees Trevor Dying", "MICHAEL_NORMAL", "BUDDY_SEES_TREVOR_DEATH", "SPEECH_PARAMS_FORCE" },
			{ "You're Drunk", "WFStewardess", "PLAYER_DRUNK", "SPEECH_PARAMS_FORCE" },
			{ "Bartender Chat (Female)", "WFStewardess", "BARTENDER_CHAT", "SPEECH_PARAMS_FORCE" },
			{ "Bartender Serve (Female)", "WFStewardess", "BARTENDER_SERVE", "SPEECH_PARAMS_FORCE" },
			{ "Bartender Greet (Female)", "WFStewardess", "BARTENDER_GREET", "SPEECH_PARAMS_FORCE" },
			{ "Hi, Customer (Female)", "WFStewardess", "GENERIC_HI", "SPEECH_PARAMS_FORCE" },
			{ "Hi, Male (Female)", "WFStewardess", "GENERIC_HI_MALE", "SPEECH_PARAMS_FORCE" },
			{ "Hi, Female (Female)", "WFStewardess", "GENERIC_HI_FEMALE", "SPEECH_PARAMS_FORCE" },
			{ "Thanks (Female)", "WFStewardess", "GENERIC_THANKS", "SPEECH_PARAMS_FORCE" },
			{ "Bye (Female)", "WFStewardess", "GENERIC_BYE", "SPEECH_PARAMS_FORCE" },
			{ "Bump (Female)", "WFStewardess", "BUMP", "SPEECH_PARAMS_FORCE" }
		};
#pragma endregion
#pragma region ambient speech SPEECH_PARAM names
		//struct SpeechParamS { std::string title, label; };
		const std::array<SpeechParamS, 37> vSpeechParams
		{ {
			{ "Standard", "SPEECH_PARAMS_STANDARD" },
			{ "Allow Repeat", "SPEECH_PARAMS_ALLOW_REPEAT" },
			{ "Beat", "SPEECH_PARAMS_BEAT" },

			{ "Force", "SPEECH_PARAMS_FORCE" },
			{ "Force Frontend", "SPEECH_PARAMS_FORCE_FRONTEND" },
			{ "Force NoRepeat Frontend", "SPEECH_PARAMS_FORCE_NO_REPEAT_FRONTEND" },

			{ "Shouted", "SPEECH_PARAMS_SHOUTED" },
			{ "Shouted Clear", "SPEECH_PARAMS_SHOUTED_CLEAR" },
			{ "Shouted Critical", "SPEECH_PARAMS_SHOUTED_CRITICAL" },

			{ "Force Normal", "SPEECH_PARAMS_FORCE_NORMAL" },
			{ "Force Normal Clear", "SPEECH_PARAMS_FORCE_NORMAL_CLEAR" },
			{ "Force Normal Critical", "SPEECH_PARAMS_FORCE_NORMAL_CRITICAL" },

			{ "Force Shouted", "SPEECH_PARAMS_FORCE_SHOUTED" },
			{ "Force Shouted Clear", "SPEECH_PARAMS_FORCE_SHOUTED_CLEAR" },
			{ "Force Shouted Critical", "SPEECH_PARAMS_FORCE_SHOUTED_CRITICAL" },

			{ "Force Preload Only", "SPEECH_PARAMS_FORCE_PRELOAD_ONLY" },
			{ "Force Preload Only Shouted", "SPEECH_PARAMS_FORCE_PRELOAD_ONLY_SHOUTED" },
			{ "Force Preload Only Shouted Clear", "SPEECH_PARAMS_FORCE_PRELOAD_ONLY_SHOUTED_CLEAR" },
			{ "Force Preload Only Shouted Critical", "SPEECH_PARAMS_FORCE_PRELOAD_ONLY_SHOUTED_CRITICAL" },

			{ "Megaphone", "SPEECH_PARAMS_MEGAPHONE" },
			{ "Force Megaphone", "SPEECH_PARAMS_FORCE_MEGAPHONE" },

			{ "Helicopter", "SPEECH_PARAMS_HELI" },
			{ "Force Helicopter", "SPEECH_PARAMS_FORCE_HELI" },

			{ "Interrupt", "SPEECH_PARAMS_INTERRUPT" },
			{ "Interrupt Shouted", "SPEECH_PARAMS_INTERRUPT_SHOUTED" },
			{ "Interrupt Shouted Clear", "SPEECH_PARAMS_INTERRUPT_SHOUTED_CLEAR" },
			{ "Interrupt Shouted Critical", "SPEECH_PARAMS_INTERRUPT_SHOUTED_CRITICAL" },
			{ "Interrupt NoForce", "SPEECH_PARAMS_INTERRUPT_NO_FORCE" },
			{ "Interrupt Frontend", "SPEECH_PARAMS_INTERRUPT_FRONTEND" },
			{ "Interrupt NoForce Frontend", "SPEECH_PARAMS_INTERRUPT_NO_FORCE_FRONTEND" },

			{ "AddBlip", "SPEECH_PARAMS_ADD_BLIP" },
			{ "AddBlip Allow Repeat", "SPEECH_PARAMS_ADD_BLIP_ALLOW_REPEAT" },
			{ "AddBlip Force", "SPEECH_PARAMS_ADD_BLIP_FORCE" },
			{ "AddBlip Shouted", "SPEECH_PARAMS_ADD_BLIP_SHOUTED" },
			{ "AddBlip Shouted Force", "SPEECH_PARAMS_ADD_BLIP_SHOUTED_FORCE" },
			{ "AddBlip Interrupt", "SPEECH_PARAMS_ADD_BLIP_INTERRUPT" },
			{ "AddBlip Interrupt Force", "SPEECH_PARAMS_ADD_BLIP_INTERRUPT_FORCE" },
			} };
#pragma endregion

		std::vector<AmbientVoice_t> vVoiceData;

		AmbientVoice_t* _currVoiceInfo = nullptr;
		uint16_t _currSpeechParamIndex = 3; // SPEECH_PARAMS_FORCE

		std::string& _searchStr = dict2;

		bool PopulateVoiceData()
		{
			CSimpleIniA ini;
			ini.SetMultiKey(true);
			if (ini.LoadFile((GetPathffA(Pathff::Main, true) + "PedSpeechList.txt").c_str()) != SI_Error::SI_OK)
				return false;

			CSimpleIniA::TNamesDepend keys;
			const char* section = "all";
			ini.GetAllKeys(section, keys);

			vVoiceData.clear();
			vVoiceData.reserve(keys.size());

			std::set<std::string> keysDone;
			for (auto& k : keys)
			{
				if (keysDone.find(k.pItem) != keysDone.end())
					continue;

				vVoiceData.push_back({ k.pItem,{} });
				auto& finalV = vVoiceData.back();

				CSimpleIniA::TNamesDepend values;
				ini.GetAllValues(section, k.pItem, values);

				finalV.speechNames.clear();
				finalV.speechNames.reserve(values.size());

				std::set<std::string> valuesDone;
				for (auto& v : values)
				{
					std::string randomSpeech = v.pItem;
					randomSpeech = randomSpeech.substr(0, randomSpeech.find(','));
					if (valuesDone.find(randomSpeech) != valuesDone.end())
						continue;
					finalV.speechNames.push_back(randomSpeech);

					//std::string val = v.pItem;
					//val.replace(val.find(','), 2, val.substr(val.length()-3)[0] == ',' ? "_0" : "_");
					//finalV.speechNames.push_back(val);

					valuesDone.insert(randomSpeech);
				}

				keysDone.insert(k.pItem);
			}

			std::sort(vVoiceData.begin(), vVoiceData.end(),
				[](const AmbientVoice_t& a, const AmbientVoice_t& b)
				-> bool { return a.voiceName < b.voiceName; });
			for (auto& i : vVoiceData)
				std::sort(i.speechNames.begin(), i.speechNames.end());

			return true;
		}

		void Sub_VoiceChanger()
		{
			GTAped ped = Static_241;
			if (!ped.Exists())
			{
				Menu::SetSub_previous();
				return;
			}

			bool pressed = 0;

			AddTitle("Voice Changer");

			bool bSearchPressed = false;
			AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "", _searchStr);
				boost::to_upper(_searchStr);
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
			}

			for (auto& v : vVoiceData)
			{
				if (!_searchStr.empty()) { if (boost::to_upper_copy(v.voiceName).find(_searchStr) == std::string::npos) continue; }

				pressed = 0;
				AddOption(v.voiceName, pressed); if (pressed)
				{
					ped.RequestControl();
					ped.VoiceName_set(v.voiceName);
					Game::Print::PrintBottomCentre("Voice ~b~changed~s~.\n ~r~Note:~s~ This does not work for all peds.");
				}
			}

		}

		void Sub_AmbientSpeechPlayer()
		{
			GTAped ped = Static_241;
			_currVoiceInfo = nullptr;
			if (!ped.Exists())
			{
				Menu::SetSub_previous();
				return;
			}

			AddTitle("Speech");

			bool bSearchPressed = false;
			AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "", _searchStr);
				boost::to_upper(_searchStr);
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
			}

			for (auto& v : vVoiceData)
			{
				if (!_searchStr.empty()) { if (boost::to_upper_copy(v.voiceName).find(_searchStr) == std::string::npos) continue; }

				bool bVoicePressed = false;
				AddOption(v.voiceName, bVoicePressed); if (bVoicePressed)
				{
					_currVoiceInfo = &v;
					Menu::SetSub_delayed = SUB::SPEECHPLAYER_INVOICE;
				}
			}

		}
		void Sub_AmbientSpeechPlayer_InVoice()
		{
			GTAped ped = Static_241;
			if (_currVoiceInfo == nullptr || !ped.Exists())
			{
				Menu::SetSub_previous();
				return;
			}
			auto& v = *_currVoiceInfo;

			AddTitle(v.voiceName);

			bool bSpeechParam_plus = false, bSpeechParam_minus = false;
			AddTexter("Modifier", 0, std::vector<std::string>{ vSpeechParams[_currSpeechParamIndex].title }, null, bSpeechParam_plus, bSpeechParam_minus);
			if (bSpeechParam_plus) { if (_currSpeechParamIndex < vSpeechParams.size() - 1) _currSpeechParamIndex++; }
			if (bSpeechParam_minus) { if (_currSpeechParamIndex > 0) _currSpeechParamIndex--; }

			for (auto& s : v.speechNames)
			{
				bool bSpeechPressed = false;
				AddOption(s, bSpeechPressed); if (bSpeechPressed)
				{
					ped.PlaySpeechWithVoice(s, v.voiceName, vSpeechParams[_currSpeechParamIndex].label);
				}
			}
		}

	}

}





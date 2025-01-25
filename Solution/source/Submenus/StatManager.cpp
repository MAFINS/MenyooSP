/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "StatManager.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
//#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\Game.h"
#include "..\Util\FileLogger.h"

#include <string>
#include <vector>
#include <utility>

namespace sub
{
	namespace SpStatManager_catind
	{
		//enum class StatDataType_t
		//struct CharStat_t { std::string name, caption; StatDataType_t type; float min, max; };
		struct NamedCharStatList_t { std::string title; std::vector<CharStat_t> list; };

#pragma region character stats		
		const std::array<NamedCharStatList_t, 5> vCharStatLists
		{ {
			{ "Cash",{
				{ "TOTAL_CASH", "Total Cash", StatDataType_t::INT, 0, static_cast<float>(INT_MAX) }
				//{ "TOTAL_CASH_EARNED", "Earned Cash", StatDataType_t::INT, 0, INT_MAX }
			} },
			{ "Abilities (ALPHA)",{
				{ "STAMINA", "Stamina", StatDataType_t::INT, 0, 100 },
				{ "STRENGTH", "Strength", StatDataType_t::INT, 0, 100 },
				{ "LUNG_CAPACITY", "Lung Capacity", StatDataType_t::INT, 0, 100 },
				{ "WHEELIE_ABILITY", "Wheelieing", StatDataType_t::INT, 0, 100 },
				{ "FLYING_ABILITY", "Flying", StatDataType_t::INT, 0, 100 },
				{ "SHOOTING_ABILITY", "Shooting", StatDataType_t::INT, 0, 100 },
				{ "STEALTH_ABILITY", "Stealth", StatDataType_t::INT, 0, 100 }
			} },
			{ "Special Ability",{
				{ "SPECIAL_ABILITY", "Amount Not Unlocked (ALPHA)", StatDataType_t::INT, 0, 100 },
				{ "SPECIAL_ABILITY_UNLOCKED", "Special Capacity", StatDataType_t::INT, 0, 100 }
			} },
			{ "K/D Ratio",{
				{ "KILLS", "Kill Count", StatDataType_t::INT, 0, static_cast<float>(INT_MAX) },
				{ "DEATHS", "Death Count", StatDataType_t::INT, 0, static_cast<float>(INT_MAX) }
			} },
			{ "Properties",{
				{ "PROP_BOUGHT_TRAF", "Arms Trafficking", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_CSCR", "Car Scrap Yard", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_WEED", "Weed Shop", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_TAXI", "Taxi Lot", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_CMSH", "Car Mod Shop", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_SOCO", "Sonar Collections", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_TOWI", "Towing Impound", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_GOLF", "Golf Club", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_CINV", "Vinewood Cinema", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_CIND", "Downtown Cinema", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_CINM", "Morningwood Cinema", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_BARTE", "Tequilala Bar", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_BARPI", "Pitchers Bar", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_BARHE", "Hen House Bar", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_BARHO", "Hookies Bar", StatDataType_t::BOOL, 0, 0 },
				{ "PROP_BOUGHT_STRIP", "Strip Club", StatDataType_t::BOOL, 0, 0 }
			} }
			} };
#pragma endregion

		std::pair<std::string, std::string> vCharNames[3] = { { "SP0_", "Michael" },{ "SP1_", "Franklin" },{ "SP2_", "Trevor" } };
		std::pair<std::string, std::string>* selectedCharName;
		const NamedCharStatList_t* selectedStatList;

		// Setters/Getters
		int StatGetInt(const std::string& name)
		{
			int tempp;
			STAT_GET_INT(GET_HASH_KEY(name), &tempp, -1);
			return tempp;
		}
		bool StatGetBool(const std::string& name)
		{
			int tempp;
			STAT_GET_BOOL(GET_HASH_KEY(name), &tempp, -1);
			return tempp != 0;
		}
		float StatGetFloat(const std::string& name)
		{
			float tempp;
			STAT_GET_FLOAT(GET_HASH_KEY(name), &tempp, -1);
			return tempp;
		}
		std::string StatGetString(const std::string& name)
		{
			return STAT_GET_STRING(GET_HASH_KEY(name), -1);
		}
		void StatSetInt(const std::string& name, int value)
		{
			STAT_SET_INT(GET_HASH_KEY(name), value, 1);
		}
		void StatSetBool(const std::string& name, bool value)
		{
			STAT_SET_BOOL(GET_HASH_KEY(name), value, 1);
		}
		void StatSetFloat(const std::string& name, float value)
		{
			STAT_SET_FLOAT(GET_HASH_KEY(name), value, 1);
		}
		void StatSetString(const std::string& name, const std::string& value)
		{
			STAT_SET_STRING(GET_HASH_KEY(name), value.c_str(), 1);
		}

		void __AddOption(const CharStat_t& stat)
		{
			bool bStatValue_plus = false, bStatValue_minus = false, bStatValue_input = false;

			const std::string& statName = selectedCharName->first + stat.name;

			switch (stat.type)
			{
			case StatDataType_t::BOOL:
			{
				bool statValue = StatGetBool(statName);
				AddTickol(stat.caption, statValue, bStatValue_input, bStatValue_input, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bStatValue_input)
				{
					statValue = !statValue;
					StatSetBool(statName, statValue);
				}
				break;
			}
			case StatDataType_t::INT:
			{
				int statValue = StatGetInt(statName);
				AddNumber(stat.caption, statValue, 0, bStatValue_input, bStatValue_plus, bStatValue_minus); if (bStatValue_input)
				{
					std::string inputStr = Game::InputBox(std::string(), (int)std::to_string((int)stat.max).length() + 1, "Enter integer value:", std::to_string(statValue));
					if (inputStr.length() > 0)
					{
						try
						{
							statValue = stoi(inputStr);
							StatSetInt(statName, statValue);
						}
						catch (...) { 
							Game::Print::PrintError_InvalidInput(); 
							addlog(ige::LogType::LOG_ERROR, "Invalid Stat Integer for " + stat.caption + " Entered", __FILENAME__);
						}
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SpStatManagerInputInt, std::string(), (int)std::to_string((int)stat.max).length(), "Enter integer value:", std::to_string(statValue));
					//OnscreenKeyboard::State::arg1._uint = GET_HASH_KEY(statName);
					//OnscreenKeyboard::State::arg2._int = statValue;
				}
				if (bStatValue_plus) { if (statValue < stat.max) { statValue += 1.0f; StatSetInt(statName, statValue); } }
				if (bStatValue_minus) { if (statValue > stat.min) { statValue -= 1.0f; StatSetInt(statName, statValue); } }
				break;
			}
			case StatDataType_t::FLOAT:
			{
				float statValue = StatGetFloat(statName);
				AddNumber(stat.caption, statValue, 2, bStatValue_input, bStatValue_plus, bStatValue_minus); if (bStatValue_input)
				{
					std::string inputStr = Game::InputBox(std::string(), 13U, "Enter floating point value:", std::to_string(statValue));
					if (inputStr.length() > 0)
					{
						try
						{
							statValue = stof(inputStr);
							StatSetFloat(statName, statValue);
						}
						catch (...) { 
							Game::Print::PrintError_InvalidInput();
							addlog(ige::LogType::LOG_ERROR, "Invalid Stat Float for " + stat.caption + " Entered", __FILENAME__);
						}
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SpStatManagerInputFloat, std::string(), 13U, "Enter floating point value:", std::to_string(statValue));
					//OnscreenKeyboard::State::arg1._uint = GET_HASH_KEY(statName);
					//OnscreenKeyboard::State::arg2._float = statValue;
				}
				if (bStatValue_plus) { if (statValue < stat.max) { statValue += 0.05f; StatSetInt(statName, statValue); } }
				if (bStatValue_minus) { if (statValue > stat.min) { statValue -= 0.05f; StatSetInt(statName, statValue); } }
				break;
			}
			}
		}

		void Sub_SpStatManager()
		{
			AddTitle("Stat Manager");

			for (auto& charName : vCharNames)
			{
				bool bGoToCharacterPressed = false;
				AddOption(charName.second, bGoToCharacterPressed, nullFunc, SUB::SPSTATMANAGER_INCHAR); if (bGoToCharacterPressed)
				{
					selectedCharName = &charName;
				}
			}

			/*AddBreak("---Others---");
			int statExclus = StatGetInt("SP_UNLOCK_EXCLUS_CONTENT");
			bool bExclus_plus = false, bExclus_minus = false;
			AddNumber("Exclusive Content", statExclus, 0, null, bExclus_plus, bExclus_minus);
			if (bExclus_plus) { if (statExclus < 100) { statExclus++; StatSetInt("SP_UNLOCK_EXCLUS_CONTENT", statExclus); } }
			if (bExclus_minus) { if (statExclus > 0) { statExclus--; StatSetInt("SP_UNLOCK_EXCLUS_CONTENT", statExclus); } }*/

			// Is this legal?
			AddBreak("---Achievements---");
			bool bUnlockAllAch = false;
			AddOption("Unlock All Achievements", bUnlockAllAch); if (bUnlockAllAch)
			{
				int numAchievements = 78;
				//gamever
				for (int i = 0; i < numAchievements; i++)
					if (!HAS_ACHIEVEMENT_BEEN_PASSED(i))
						GIVE_ACHIEVEMENT_TO_PLAYER(i);
			}

			auto unlockAchievement = [](int id, const char* description) {
				bool unlockFlag = false;
				AddOption(std::to_string(id) + ". " + description, unlockFlag);
				if (unlockFlag && !HAS_ACHIEVEMENT_BEEN_PASSED(id))
				{
					GIVE_ACHIEVEMENT_TO_PLAYER(id);
				}
			};
			
			unlockAchievement(1, "Unlock 'Welcome to Los Santos'");
			unlockAchievement(2, "Unlock 'A Friendship Resurrected'");
			unlockAchievement(3, "Unlock 'A Fair Day's Pay'");
			unlockAchievement(4, "Unlock 'The Moment of Truth'");
			unlockAchievement(5, "Unlock 'To Live or Die in Los Santos'");
			unlockAchievement(6, "Unlock 'Diamond Hard'");
			unlockAchievement(7, "Unlock 'Subversive'");
			unlockAchievement(8, "Unlock 'Blitzed'");
			unlockAchievement(9, "Unlock 'Small Town, Big Job'");
			unlockAchievement(10, "Unlock 'The Government Gimps'");
			unlockAchievement(11, "Unlock 'The Big One!'");
			unlockAchievement(12, "Unlock 'Solid Gold, Baby!'");
			unlockAchievement(13, "Unlock 'Career Criminal'");
			unlockAchievement(14, "Unlock 'San Andreas Sightseer'");
			unlockAchievement(15, "Unlock 'All's Fare in Love and War'");
			unlockAchievement(16, "Unlock 'TP Industries Arms Race'");
			unlockAchievement(17, "Unlock 'Multi-Disciplined'");
			unlockAchievement(18, "Unlock 'From Beyond the Stars'");
			unlockAchievement(19, "Unlock 'A Mystery, Solved'");
			unlockAchievement(20, "Unlock 'Waste Management'");
			unlockAchievement(21, "Unlock 'Red Mist'");
			unlockAchievement(22, "Unlock 'Show Off'");
			unlockAchievement(23, "Unlock 'Kifflom!'");
			unlockAchievement(24, "Unlock 'Three Man Army'");
			unlockAchievement(25, "Unlock 'Out of Your Depth'");
			unlockAchievement(26, "Unlock 'Altruist Acolyte'");
			unlockAchievement(27, "Unlock 'A Lot of Cheddar'");
			unlockAchievement(28, "Unlock 'Trading Pure Alpha'");
			unlockAchievement(29, "Unlock 'Pimp My Sidearm'");
			unlockAchievement(30, "Unlock 'Wanted: Alive Or Alive'");
			unlockAchievement(31, "Unlock 'Los Santos Customs'");
			unlockAchievement(32, "Unlock 'Close Shave'");
			unlockAchievement(33, "Unlock 'Off the Plane'");
			unlockAchievement(34, "Unlock 'Three-Bit Gangster'");
			unlockAchievement(35, "Unlock 'Making Moves'");
			unlockAchievement(36, "Unlock 'Above the Law'");
			unlockAchievement(37, "Unlock 'Numero Uno'");
			unlockAchievement(38, "Unlock 'The Midnight Club'");
			unlockAchievement(39, "Unlock 'Unnatural Selection'");
			unlockAchievement(40, "Unlock 'Backseat Driver'");
			unlockAchievement(41, "Unlock 'Run Like The Wind'");
			unlockAchievement(42, "Unlock 'Clean Sweep'");
			unlockAchievement(43, "Unlock 'Decorated'");
			unlockAchievement(44, "Unlock 'Stick Up Kid'");
			unlockAchievement(45, "Unlock 'Enjoy Your Stay'");
			unlockAchievement(46, "Unlock 'Crew Cut'");
			unlockAchievement(47, "Unlock 'Full Refund'");
			unlockAchievement(48, "Unlock 'Dialling Digits'");
			unlockAchievement(49, "Unlock 'American Dream'");
			unlockAchievement(50, "Unlock 'A New Perspective'");
			unlockAchievement(51, "Unlock 'Be Prepared'");
			unlockAchievement(52, "Unlock 'In the Name of Science'");
			unlockAchievement(53, "Unlock 'Dead Presidents'");
			unlockAchievement(54, "Unlock 'Parole Day'");
			unlockAchievement(55, "Unlock 'Shot Caller'");
			unlockAchievement(56, "Unlock 'Four Way'");
			unlockAchievement(57, "Unlock 'Live a Little'");
			unlockAchievement(58, "Unlock 'Can't Touch This'");
			unlockAchievement(59, "Unlock 'Mastermind'");
			unlockAchievement(60, "Unlock 'Vinewood Visionary'");
			unlockAchievement(61, "Unlock 'Majestic'");
			unlockAchievement(62, "Unlock 'Humans of Los Santos'");
			unlockAchievement(63, "Unlock 'First Time Director'");
			unlockAchievement(64, "Unlock 'Animal Lover'");
			unlockAchievement(65, "Unlock 'Ensemble Piece'");
			unlockAchievement(66, "Unlock 'Cult Movie'");
			unlockAchievement(67, "Unlock 'Location Scout'");
			unlockAchievement(68, "Unlock 'Method Actor'");
			unlockAchievement(69, "Unlock 'Cryptozoologist'");
			unlockAchievement(70, "Unlock 'Getting Started'");
			unlockAchievement(71, "Unlock 'The Data Breaches'");
			unlockAchievement(72, "Unlock 'The Bogdan Problem'");
			unlockAchievement(73, "Unlock 'The Doomsday Scenario'");
			unlockAchievement(74, "Unlock 'A World Worth Saving'");
			unlockAchievement(75, "Unlock 'Orbital Obliteration'");
			unlockAchievement(76, "Unlock 'Elitist'");
			unlockAchievement(77, "Unlock 'Masterminds'");

		}
		void Sub_InChar()
		{
			AddTitle(selectedCharName->second);

			for (auto& statList : vCharStatLists)
			{
				if (statList.list.size() == 1)
					__AddOption(statList.list.front());
				else
				{
					bool bStatListPressed = false;
					AddOption(statList.title, bStatListPressed, nullFunc, SUB::SPSTATMANAGER_INCHAR_INLIST); if (bStatListPressed)
					{
						selectedStatList = &statList;
					}
				}
			}
		}
		void Sub_InChar_InList()
		{
			AddTitle(selectedStatList->title);

			for (auto& stat : selectedStatList->list)
			{
				__AddOption(stat);
			}
		}

	}

}




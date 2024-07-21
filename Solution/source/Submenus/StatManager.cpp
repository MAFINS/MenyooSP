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
				int numAchievements = 59;
				//gamever
				for (int i = 0; i < numAchievements; i++)
					if (!HAS_ACHIEVEMENT_BEEN_PASSED(i))
						GIVE_ACHIEVEMENT_TO_PLAYER(i);
			}
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




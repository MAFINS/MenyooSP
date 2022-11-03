/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PedAnimation.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\enums.h"
#include "..\Util\ExePath.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Game.h"
#include "..\Util\keyboard.h"
#include "..\Util\StringManip.h"

#include "..\Submenus\Spooner\Databases.h"
#include "..\Submenus\Spooner\EntityManagement.h"
#include "..\Submenus\Spooner\SpoonerEntity.h"

#include <vector>
#include <string>
#include <map>
//#include <utility>
#include <fstream>
#include <pugixml\src\pugixml.hpp>

namespace sub
{
	// Old animation subs declare

	void AddanimOption_(const std::string& text, const std::string& anim_dict, std::string anim_name = "", bool &extra_option_code = null);

	// All animations subs

	namespace AnimationSub_catind
	{
		//struct NamedAnimation { std::string caption; std::string animDict, animName; };
		const std::vector<AnimationSub_catind::NamedAnimation> vPresetPedAnims
		{
			{ "Idle - Conceal Weapon 1", "anim@miss@low@fin@vagos@", "idle_ped01" },
			{ "Idle - Conceal Weapon 2", "anim@miss@low@fin@vagos@", "idle_ped02" },
			{ "Idle - Conceal Weapon 3", "anim@miss@low@fin@vagos@", "idle_ped03" },
			{ "Idle - Conceal Weapon 4", "anim@miss@low@fin@vagos@", "idle_ped04" },
			{ "Idle - Conceal Weapon 5", "anim@miss@low@fin@vagos@", "idle_ped05" },
			{ "Idle - Conceal Weapon 6", "anim@miss@low@fin@vagos@", "idle_ped06" },
			{ "Idle - Conceal Weapon 7", "anim@miss@low@fin@vagos@", "idle_ped07" },
			{ "Idle - Conceal Weapon 8", "anim@miss@low@fin@vagos@", "idle_ped08" },
			{ "Surrender", "random@arrests@busted", "idle_a" },
			{ "Police - Use Radio", "random@arrests", "generic_radio_chatter" },
			{ "Sniper Crouch", "missfbi2", "franklin_sniper_crouch" },
			{ "Crouch Walking", "move_weapon@rifle@generic", "walk_crouch" },
			{ "Hip Hop Dance", "missfbi3_sniping", "dance_m_default" },
			{ "Private Dance", "mini@strip_club@private_dance@part1", "priv_dance_p1" },
			{ "Move to the Beat 1", "amb@world_human_strip_watch_stand@male_a@base", "base" },
			{ "Move to the Beat 2", "amb@world_human_strip_watch_stand@male_b@base", "base" },
			{ "Move to the Beat 3", "amb@world_human_strip_watch_stand@male_c@base", "base" },
			{ "Move to the Beat 4", "amb@world_human_strip_watch_stand@male_c@idle_a", "idle_a" },
			{ "Move to the Beat 5", "amb@world_human_partying@female@partying_beer@base", "base" },
			{ "Mountain Dance", "special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven" },
			{ "Bump and Grind", "mini@strip_club@private_dance@idle", "priv_dance_idle" },
			{ "Corny Dancing", "anim@mp_player_intincardancebodhi@rds@", "idle_a" },
			{ "Dirty Dancing", "oddjobs@assassinate@multi@yachttarget@lapdance", "yacht_ld_f" },
			{ "Crazy Dancing", "misschinese2_crystalmazemcs1_ig", "dance_loop_tao" },
			{ "Shake Your Butt", "switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_stripper" },
			{ "Jerking Off", "switch@trevor@jerking_off", "trev_jerking_off_loop" },
			{ "Butt Scratch", "mp_player_int_upperarse_pick", "mp_player_int_arse_pick" },
			{ "Peeing", "misscarsteal2peeing", "peeing_loop" },
			{ "Pooping", "missfbi3ig_0", "shit_loop_trev" },
			{ "Pick Nose", "anim@mp_player_intincarnose_pickstd@rps@", "idle_a" },
			{ "Wash Hands", "missheist_agency3aig_23", "urinal_sink_loop" },
			{ "Look at Fingernails", "missfbi3_camcrew", "base_gal" },
			{ "Brush Shoulders Off", "missfbi3_camcrew", "base_gal" },
			{ "Drunk", "move_m@drunk@verydrunk_idles@", "fidget_01" },
			{ "Twitchy", "oddjobs@bailbond_hobotwitchy", "idle_a" },
			{ "Ow, My Head", "misscarsteal4@actor", "dazed_idle" },
			{ "So Depressed", "oddjobs@bailbond_hobodepressed", "idle_a" },
			{ "Kick Rocks", "timetable@ron@ig_1", "ig_1_idle_a" },
			{ "Looking for Something", "missmic_4premierejimwaitbef_prem", "wait_idle_a" },
			{ "Bend Over to Look", "switch@franklin@admire_motorcycle", "base_franklin" },
			{ "Examining", "missfbi5ig_15", "look_into_microscope_c_scientistb" },
			{ "It's a Bird, It's a Plane", "oddjobs@basejump@", "ped_a_loop" },
			{ "Flip the Bird", "anim@mp_player_intincarfingerbodhi@ds@", "idle_a" },
			{ "Yelling at Someone", "misscarsteal4@actor", "actor_berating_loop" },
			{ "Getting Yelled At", "misscarsteal4", "assistant_loop" },
			{ "Arguing Girl", "missfbi3_camcrew", "first_action_gal" },
			{ "Arguing Guy", "missfbi3_camcrew", "first_action_guy" },
			{ "Kicking Guy on Ground 1", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_guard1" },
			{ "Kicking Guy on Ground 2", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_guard2" },
			{ "Getting Kicked", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_dockworker" },
			{ "Tough Guy - Arms Crossed", "missdocksshowoffcar@idle_a", "idle_b_5" },
			{ "Stand at Rail", "anim@amb@yacht@rail@standing@male@variant_01@", "base" },
			{ "Out of Breath", "re@construction", "out_of_breath" },
			{ "Base Jump Prep", "oddjobs@bailbond_mountain", "base_jump_idle" },
			{ "Jazzercise 1", "timetable@tracy@ig_5@idle_a", "idle_c" },
			{ "Jazzercise 2", "timetable@tracy@ig_5@idle_b", "idle_e" },
			{ "Warmup Stretching 1", "mini@triathlon", "idle_a" },
			{ "Warmup Stretching 2", "mini@triathlon", "ig_2_gen_warmup_01" },
			{ "Jog in Place", "amb@world_human_jog_standing@male@fitbase", "base" },
			{ "Cat - Scratch Ear", "creatures@cat@player_action@", "action_a" },
			{ "Dog - Sit", "creatures@dog@move", "sit_loop" },
			{ "Dog - Walk in Circles", "creatures@dog@move", "idle_turn_l" },
			{ "Rabbit - Scratch Ear", "creatures@rabbit@player_action@", "action_a" },
			{ "Monkey - Idle 1", "missfbi5ig_30monkeys", "monkey_a_idle" },
			{ "Monkey - Idle 2", "missfbi5ig_30monkeys", "monkey_b_idle" },
			{ "Monkey - Idle 3", "missfbi5ig_30monkeys", "monkey_c_idle" },
			{ "Monkey - Freakout 1", "missfbi5ig_30monkeys", "monkey_a_freakout_loop" },
			{ "Monkey - Freakout 2", "missfbi5ig_30monkeys", "monkey_b_freakout_loop" },
			{ "Monkey - Freakout 3", "missfbi5ig_30monkeys", "monkey_c_freakout_loop" }
		};

		std::map<std::string, std::vector<std::string>> vAllPedAnims;
		std::pair<const std::string, std::vector<std::string>>* selectedAnimDictPtr = nullptr;

		void PopulateAllPedAnimsList()
		{
			std::ifstream fin(GetPathffA(Pathff::Main, true) + "PedAnimList.txt");

			if (fin.is_open())
			{
				vAllPedAnims.clear();

				size_t space;
				std::string lineLeft, lineRight;
				//std::vector<std::string> newFileLines;

				for (std::string line; std::getline(fin, line);)
				{
					if (line.length() > 2)
					{
						space = line.find(' ');
						if (space != std::string::npos)
						{
							lineLeft = line.substr(0, space);
							lineRight = line.substr(space + 1);
							vAllPedAnims[lineLeft].push_back(lineRight);
						}
					}
				}
				fin.close();
			}
		}

		void Sub_AllPedAnims()
		{
			auto& _searchStr = dict;
			selectedAnimDictPtr = nullptr;
			bool searchobj = false;
			bool bCurrentPressed;
			bool notFoundInDict;

			AddTitle("All Animations");

			AddOption(_searchStr.empty() ? "SEARCH" : boost::to_upper_copy(_searchStr), searchobj, nullFunc, -1, true); if (searchobj)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "", _searchStr);
				boost::to_lower(_searchStr);
			}

			AddOption("Stop Animation", null, AnimationSub_StopAnimationCallback);

			for (auto& current : vAllPedAnims)
			{
				if (!current.second.empty())
				{
					if (!_searchStr.empty())
					{
						if (current.first.find(_searchStr) == std::string::npos)
						{
							notFoundInDict = true;
							for (auto& current2 : current.second)
							{
								if (current2.find(_searchStr) != std::string::npos) { notFoundInDict = false; break; }
							}
							if (notFoundInDict) { continue; }
						}
					}

					bCurrentPressed = false;
					AddOption(current.first, bCurrentPressed); if (bCurrentPressed)
					{
						selectedAnimDictPtr = &current;
						Menu::SetSub_delayed = SUB::ANIMATIONSUB_ALLPEDANIMS_INDICT;
					}
				}
			}
		}
		void Sub_AllPedAnims_InDict()
		{
			if (selectedAnimDictPtr == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			auto& selectedDict = *selectedAnimDictPtr;
			//auto& _searchStr = dict;

			AddTitle(selectedDict.first);

			for (auto& current : selectedDict.second)
			{
				AddanimOption_(current, selectedDict.first, current);
			}

			AddOption("Settings", null, nullFunc, SUB::ANIMATIONSUB_SETTINGS);
		}
	}

	// Animation settings

	std::string _globalCustomAnim_dict = "Enter Dictionary", _globalCustomAnim_name = "Enter Name";
	float _globalCustomAnim_speed = 4, _globalCustomAnim_speedMult = -4, _globalCustomAnim_rate = 0;
	int _globalCustomAnim_duration = -1, _globalCustomAnim_flag = AnimFlag::Loop;
	bool _globalCustomAnim_lockPos = false;

	// Animation Favourites

	void GetFavouriteAnimations(std::vector<std::pair<std::string, std::string>>& result)
	{
		result.clear();
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml").c_str()).status == pugi::status_ok)
		{
			auto& nodeAnims = doc.child("PedAnims");
			for (auto& nodeAnim = nodeAnims.first_child(); nodeAnim; nodeAnim = nodeAnim.next_sibling())
			{
				std::string dict = nodeAnim.attribute("dict").as_string();
				std::string name = nodeAnim.attribute("name").as_string();

				result.push_back(std::make_pair(dict, name));
			}
		}
	}
	bool IsAnimationAFavourite(const std::string animDict, const std::string& animName)
	{
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml").c_str()).status != pugi::status_ok)
			return false;

		auto& nodeAnims = doc.child("PedAnims");

		for (auto& nodeAnim = nodeAnims.first_child(); nodeAnim; nodeAnim = nodeAnim.next_sibling())
		{
			std::string dict = nodeAnim.attribute("dict").as_string();
			std::string name = nodeAnim.attribute("name").as_string();
			if (animDict == dict && animName == name)
				return true;
		}
		return false;
	}
	void AddAnimationToFavourites(const std::string animDict, const std::string& animName)
	{
		pugi::xml_document doc;
		std::string filePath = GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml";
		if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
		{
			doc.reset();
			auto& nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
			doc.append_child("PedAnims");
		}

		auto& nodeAnims = doc.child("PedAnims");

		auto& nodeAnim = nodeAnims.append_child("Anim");
		nodeAnim.append_attribute("dict") = animDict.c_str();
		nodeAnim.append_attribute("name") = animName.c_str();

		doc.save_file((const char*)filePath.c_str());
	}
	void RemoveAnimationFromFavourites(const std::string animDict, const std::string& animName)
	{
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml").c_str()).status != pugi::status_ok)
			return;

		auto& nodeAnims = doc.child("PedAnims");

		for (auto& nodeAnim = nodeAnims.first_child(); nodeAnim; nodeAnim = nodeAnim.next_sibling())
		{
			std::string dict = nodeAnim.attribute("dict").as_string();
			std::string name = nodeAnim.attribute("name").as_string();
			if (animDict == dict && animName == name)
			{
				nodeAnims.remove_child(nodeAnim);
			}
		}

		doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml").c_str());
	}

	// Old animation subs

	void AddanimOption_(const std::string& text, const std::string& anim_dict, std::string anim_name, bool &extra_option_code)
	{
		if (anim_name.length() == 0)
			anim_name = text;
		bool pressed = false;
		AddTickol(text, IS_ENTITY_PLAYING_ANIM(local_ped_id, const_cast<PCHAR>(anim_dict.c_str()), const_cast<PCHAR>(anim_name.c_str()), 3), pressed, pressed, TICKOL::MANWON); if (pressed)
		{
			GTAped ped = local_ped_id;
			GTAentity att;
			auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
			}

			ped.RequestControl();
			ped.Task().PlayAnimation(anim_dict, anim_name, _globalCustomAnim_speed, _globalCustomAnim_speedMult, _globalCustomAnim_duration,
				_globalCustomAnim_flag, _globalCustomAnim_rate, _globalCustomAnim_lockPos);

			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				spe.LastAnimation.dict = anim_dict;
				spe.LastAnimation.name = anim_name;
				if (att.Exists() && spe.AttachmentArgs.isAttached)
					spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
				spe.TaskSequence.Reset();
				if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
				{
					sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
					sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
					sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
				}
			}

			extra_option_code = true;
		}

		if (Menu::printingop == *Menu::currentopATM)
		{
			bool bIsAFav = IsAnimationAFavourite(anim_dict, anim_name);
			if (Menu::bit_controller)
			{
				Menu::add_IB(INPUT_SCRIPT_RLEFT, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

				if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
				{
					!bIsAFav ? AddAnimationToFavourites(anim_dict, anim_name) : RemoveAnimationFromFavourites(anim_dict, anim_name);
				}
			}
			else
			{
				Menu::add_IB(VirtualKey::B, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

				if (IsKeyJustUp(VirtualKey::B))
				{
					!bIsAFav ? AddAnimationToFavourites(anim_dict, anim_name) : RemoveAnimationFromFavourites(anim_dict, anim_name);
				}
			}
		}

	}

	void AnimationSub_StopAnimationCallback()
	{
		GTAped ped = local_ped_id;
		GTAentity att;
		auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
		if (spi >= 0)
		{
			auto& spe = sub::Spooner::Databases::EntityDb[spi];
			Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
		}

		GTAvehicle veh = ped.CurrentVehicle();
		bool isInVehicle = veh.Exists();
		VehicleSeat vehSeat;
		if (isInVehicle)
		{
			vehSeat = ped.CurrentVehicleSeat_get();
		}
		ped.Task().ClearAllImmediately();
		if (isInVehicle)
		{
			ped.SetIntoVehicle(veh, vehSeat);
		}

		if (spi >= 0)
		{
			auto& spe = sub::Spooner::Databases::EntityDb[spi];
			spe.LastAnimation.dict.clear();
			spe.LastAnimation.name.clear();
			if (att.Exists() && spe.AttachmentArgs.isAttached)
				spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
			spe.TaskSequence.Reset();
			if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
			{
				sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
				sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
				sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
			}
		}
	}

	void AnimationSub_()
	{
		//sub::Spooner::SpoonerEntity uselessSpoonerEntity;
		//sub::Spooner::SpoonerEntity* spoonerCurrentPed = local_ped_id == sub::Spooner::SelectedEntity.Handle.Handle() ? &sub::Spooner::SelectedEntity : &uselessSpoonerEntity;
		auto& _searchStr = dict;
		dict.clear();

		bool dictset_deer = 0, dictset_cow = 0, dictset_shark = 0, dictset_guard_reac = 0, dictset_randarrests = 0,
			dictset_swat = 0, dictset_missrappel = 0, dictset_gestures_sitting = 0;

		SET_PED_CAN_PLAY_AMBIENT_ANIMS(local_ped_id, TRUE);
		SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(local_ped_id, TRUE);
		SET_PED_CAN_PLAY_GESTURE_ANIMS(local_ped_id, TRUE);
		SET_PED_CAN_PLAY_VISEME_ANIMS(local_ped_id, TRUE, TRUE);
		SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(local_ped_id, TRUE);

		AddTitle("Animations");
		AddOption("Stop Animation", null, AnimationSub_StopAnimationCallback);
		AddanimOption_("Pole Dance", "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03");
		AddanimOption_("Hood Dance", "missfbi3_sniping", "dance_m_default");
		AddanimOption_("Burning", "ragdoll@human", "on_fire");
		AddanimOption_("Getting Stunned", "ragdoll@human", "electrocute");
		AddanimOption_("Private Dance", "mini@strip_club@private_dance@part1", "priv_dance_p1");
		AddanimOption_("The Rear Abundance", "rcmpaparazzo_2", "shag_loop_poppy");
		AddanimOption_("The Invisible Man", "rcmpaparazzo_2", "shag_loop_a");
		AddanimOption_("Push ups", "amb@world_human_push_ups@male@base", "base");
		AddanimOption_("Sit ups", "amb@world_human_sit_ups@male@base", "base");
		AddanimOption_("Wave Yo' Arms", "random@car_thief@victimpoints_ig_3", "arms_waving");
		AddanimOption_("Give BJ to Driver", "mini@prostitutes@sexnorm_veh", "bj_loop_prostitute");
		AddanimOption_("Pleasure Driver", "mini@prostitutes@sexnorm_veh", "sex_loop_prostitute");
		AddanimOption_("Mime", "special_ped@mime@monologue_8@monologue_8a", "08_ig_1_wall_ba_0");
		AddanimOption_("Mime 2", "special_ped@mime@monologue_7@monologue_7a", "11_ig_1_run_aw_0");
		AddanimOption_("Throw", "switch@franklin@throw_cup", "throw_cup_loop");
		AddanimOption_("Smoke Coughing", "timetable@gardener@smoking_joint", "idle_cough");
		AddanimOption_("Chilling with Friends", "friends@laf@ig_1@base", "base");
		AddanimOption_("They Think We Dumb", "timetable@ron@they_think_were_stupid", "they_think_were_stupid");
		AddanimOption_("Come Here", "gestures@m@standing@fat", "gesture_come_here_hard");
		AddanimOption_("No Way", "gestures@m@standing@fat", "gesture_no_way");
		AddanimOption_("They're Gonna Kill Me", "random@bicycle_thief@ask_help", "my_dads_going_to_kill_me");
		AddanimOption_("You Gotta Help Me", "random@bicycle_thief@ask_help", "please_man_you_gotta_help_me");
		AddanimOption_("Sleep", "savecouch@", "t_sleep_loop_couch");
		AddanimOption_("Sleep 2", "savem_default@", "m_sleep_r_loop");
		AddanimOption_("Sleep 3", "timetable@tracy@sleep@", "idle_c");
		AddanimOption_("Meditate", "rcmcollect_paperleadinout@", "meditiate_idle");
		AddanimOption_("Fap", "switch@trevor@jerking_off", "trev_jerking_off_loop");
		AddanimOption_("Yeah Yeah Yeah", "special_ped@jessie@michael_1@michael_1b", "jessie_ig_2_yeahyeahyeah_1");
		AddanimOption_("Idle On Laptop", "switch@franklin@on_laptop", "001927_01_fras_v2_4_on_laptop_idle");
		AddanimOption_("Hands Up", "random@arrests", "idle_2_hands_up");
		AddanimOption_("Stand Still, Arms Spread", "mp_sleep", "bind_pose_180");

		AddOption("Sitting Animations", dictset_gestures_sitting, nullFunc, SUB::ANIMATIONSUB_GESTSIT);
		AddOption("Rappel Movements", dictset_missrappel, nullFunc, SUB::ANIMATIONSUB_MISSRAPPEL);
		AddOption("Arrest Movements", dictset_randarrests, nullFunc, SUB::ANIMATIONSUB_RANDARREST);
		AddOption("Swat Movements", dictset_swat, nullFunc, SUB::ANIMATIONSUB_SWAT);
		AddOption("Guard Movements", dictset_guard_reac, nullFunc, SUB::ANIMATIONSUB_GUARDREAC);
		AddOption("Deer Movements", dictset_deer, nullFunc, SUB::ANIMATIONSUB_DEER);
		AddOption("Cow Movements", dictset_cow, nullFunc, SUB::ANIMATIONSUB_DEER);
		AddOption("Shark Movements", dictset_shark, nullFunc, SUB::ANIMATIONSUB_SHARK);
		AddOption("All Animations", null, nullFunc, SUB::ANIMATIONSUB_ALLPEDANIMS);
		AddOption("Custom Input", null, nullFunc, SUB::ANIMATIONSUB_CUSTOM);
		AddOption("Favourites", null, nullFunc, SUB::ANIMATIONSUB_FAVOURITES);
		AddOption("Settings", null, nullFunc, SUB::ANIMATIONSUB_SETTINGS);


		if (dictset_deer) { dict = "creatures@deer@move"; return; }
		if (dictset_cow) { dict = "creatures@cow@move"; return; }
		if (dictset_shark) { dict = "creatures@shark@move"; return; }
		if (dictset_guard_reac) { dict = "guard_reactions"; return; }
		if (dictset_randarrests) { dict = "random@arrests"; return; }
		if (dictset_swat) { dict = "swat"; return; }
		if (dictset_missrappel) { dict = "missrappel"; return; }
		if (dictset_gestures_sitting) { dict = "gestures@m@sitting@generic@casual"; return; }

	}
	void AnimationSub_Settings()
	{
		bool speed_plus = 0, speed_minus = 0, speedMult_plus = 0, speedMult_minus = 0, duration_plus = 0, duration_minus = 0, rate_plus = 0, rate_minus = 0,
			flag_plus = 0, flag_minus = 0,
			bToggleLockPos = 0;

		AddTitle("Settings");
		AddNumber("Blend-In Speed", _globalCustomAnim_speed, 2, null, speed_plus, speed_minus);
		AddNumber("Blend-Out Speed", _globalCustomAnim_speedMult, 2, null, speedMult_plus, speedMult_minus);
		AddNumber("Duration (ms)", _globalCustomAnim_duration, 0, null, duration_plus, duration_minus);
		AddTexter("Flag", 0, std::vector<std::string>{ AnimFlag::vFlagNames[_globalCustomAnim_flag] }, null, flag_plus, flag_minus);
		AddNumber("Playback Rate", _globalCustomAnim_rate, 2, null, rate_plus, rate_minus);
		AddTickol("Lock Position", _globalCustomAnim_lockPos, bToggleLockPos, bToggleLockPos, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleLockPos)
			_globalCustomAnim_lockPos = !_globalCustomAnim_lockPos;

		/*AddToggle("Lock X", _globalCustomAnim_lockX);
		AddToggle("Lock Y", _globalCustomAnim_lockY);
		AddToggle("Lock Z", _globalCustomAnim_lockZ);*/


		if (speed_plus) { if (_globalCustomAnim_speed < FLT_MAX) _globalCustomAnim_speed += 0.1f; return; };
		if (speed_minus) { if (_globalCustomAnim_speed > 0) _globalCustomAnim_speed -= 0.1f; return; }
		if (speedMult_plus) { if (_globalCustomAnim_speedMult < FLT_MAX) _globalCustomAnim_speedMult += 0.1f; return; };
		if (speedMult_minus) { if (_globalCustomAnim_speedMult > 0 - FLT_MAX) _globalCustomAnim_speedMult -= 0.1f; return; }
		if (duration_plus) { if (_globalCustomAnim_duration < INT_MAX) _globalCustomAnim_duration += 100; return; };
		if (duration_minus) { if (_globalCustomAnim_duration > -1) _globalCustomAnim_duration -= 100; return; }
		if (flag_plus)
		{
			for (auto it = AnimFlag::vFlagNames.begin(); it != AnimFlag::vFlagNames.end(); ++it)
			{
				if (it->first == _globalCustomAnim_flag)
				{
					++it;
					if (it != AnimFlag::vFlagNames.end())
						_globalCustomAnim_flag = it->first;
					break;
				}
			}
			return;
		};
		if (flag_minus)
		{
			for (auto it = AnimFlag::vFlagNames.rbegin(); it != AnimFlag::vFlagNames.rend(); ++it)
			{
				if (it->first == _globalCustomAnim_flag)
				{
					++it;
					if (it != AnimFlag::vFlagNames.rend())
						_globalCustomAnim_flag = it->first;
					break;
				}
			}
			return;
		};
		if (rate_plus) { if (_globalCustomAnim_rate < FLT_MAX) _globalCustomAnim_rate += 0.1f; return; };
		if (rate_minus) { if (_globalCustomAnim_rate > 0) _globalCustomAnim_rate -= 0.1f; return; }

	}
	void AnimationSub_Favourites()
	{
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + "FavouriteAnims.xml").c_str()).status != pugi::status_ok)
		{
			Game::Print::PrintBottomCentre("~r~Error~s~: No favourites found. Go to ~b~Custom Input~s~ and add an animation to the favourites.");
			Menu::SetSub_previous();
			return;
		}

		auto& nodeAnims = doc.child("PedAnims");

		AddTitle("Favourites");

		for (auto& nodeAnim = nodeAnims.first_child(); nodeAnim; nodeAnim = nodeAnim.next_sibling())
		{
			std::string dict = nodeAnim.attribute("dict").as_string();
			std::string name = nodeAnim.attribute("name").as_string();

			AddanimOption_(dict + ", " + name, dict, name);
		}
	}
	void AnimationSub_Custom()
	{
		//PCHAR sub_animDict = (PCHAR)_globalCustomAnim_dict.c_str(), sub_animName = (PCHAR)_globalCustomAnim_name.c_str();
		auto& sub_animDict = _globalCustomAnim_dict;
		auto& sub_animName = _globalCustomAnim_name;
		bool inputDict = 0, inputName = 0, apply = 0, stop = 0, bAddToFavourites = 0, bRemoveFromFavourites = 0,
			flag_plus = 0, flag_minus = 0,
			speed_plus = 0, speed_minus = 0, speedMult_plus = 0, speedMult_minus = 0, duration_plus = 0, duration_minus = 0, rate_plus = 0, rate_minus = 0,
			bToggleLockPos = 0;

		bool bIsAFavourite = IsAnimationAFavourite(sub_animDict, sub_animName);

		AddTitle("Custom Animation");
		AddOption(sub_animDict, inputDict);
		AddOption(sub_animName, inputName);
		AddOption("Apply", apply);
		AddOption("Stop", stop);
		AddTickol("Favourite", bIsAFavourite, bAddToFavourites, bRemoveFromFavourites, TICKOL::BOXTICK, TICKOL::BOXBLANK);
		AddBreak("---Settings---");
		AddNumber("Blend-In Speed", _globalCustomAnim_speed, 2, null, speed_plus, speed_minus);
		AddNumber("Blend-Out Speed", _globalCustomAnim_speedMult, 2, null, speedMult_plus, speedMult_minus);
		AddNumber("Duration (ms)", _globalCustomAnim_duration, 0, null, duration_plus, duration_minus);
		AddTexter("Flag", 0, std::vector<std::string>{ AnimFlag::vFlagNames[_globalCustomAnim_flag] }, null, flag_plus, flag_minus);
		AddNumber("Playback Rate", _globalCustomAnim_rate, 2, null, rate_plus, rate_minus);
		AddTickol("Lock Position", _globalCustomAnim_lockPos, bToggleLockPos, bToggleLockPos, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleLockPos)
			_globalCustomAnim_lockPos = !_globalCustomAnim_lockPos;

		/*AddToggle("Lock X", _globalCustomAnim_lockX);
		AddToggle("Lock Y", _globalCustomAnim_lockY);
		AddToggle("Lock Z", _globalCustomAnim_lockZ);*/


		if (speed_plus) { if (_globalCustomAnim_speed < FLT_MAX) _globalCustomAnim_speed += 0.1f; return; };
		if (speed_minus) { if (_globalCustomAnim_speed > 0) _globalCustomAnim_speed -= 0.1f; return; }
		if (speedMult_plus) { if (_globalCustomAnim_speedMult < FLT_MAX) _globalCustomAnim_speedMult += 0.1f; return; };
		if (speedMult_minus) { if (_globalCustomAnim_speedMult > 0 - FLT_MAX) _globalCustomAnim_speedMult -= 0.1f; return; }
		if (duration_plus) { if (_globalCustomAnim_duration < INT_MAX) _globalCustomAnim_duration += 100; return; };
		if (duration_minus) { if (_globalCustomAnim_duration > -1) _globalCustomAnim_duration -= 100; return; }
		if (flag_plus)
		{
			for (auto it = AnimFlag::vFlagNames.begin(); it != AnimFlag::vFlagNames.end(); ++it)
			{
				if (it->first == _globalCustomAnim_flag)
				{
					++it;
					if (it != AnimFlag::vFlagNames.end())
						_globalCustomAnim_flag = it->first;
					break;
				}
			}
			return;
		};
		if (flag_minus)
		{
			for (auto it = AnimFlag::vFlagNames.rbegin(); it != AnimFlag::vFlagNames.rend(); ++it)
			{
				if (it->first == _globalCustomAnim_flag)
				{
					++it;
					if (it != AnimFlag::vFlagNames.rend())
						_globalCustomAnim_flag = it->first;
					break;
				}
			}
			return;
		};
		if (rate_plus) { if (_globalCustomAnim_rate < FLT_MAX) _globalCustomAnim_rate += 0.1f; return; };
		if (rate_minus) { if (_globalCustomAnim_rate > 0) _globalCustomAnim_rate -= 0.1f; return; }


		if (bAddToFavourites)
		{
			AddAnimationToFavourites(sub_animDict, sub_animName);
		}
		if (bRemoveFromFavourites)
		{
			RemoveAnimationFromFavourites(sub_animDict, sub_animName);
		}

		if (apply)
		{
			GTAped ped = local_ped_id;
			GTAentity att;
			auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
			}

			ped.RequestControl();
			ped.Task().PlayAnimation(sub_animDict, sub_animName, _globalCustomAnim_speed, _globalCustomAnim_speedMult, _globalCustomAnim_duration,
				_globalCustomAnim_flag, _globalCustomAnim_rate, _globalCustomAnim_lockPos);

			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				spe.LastAnimation.dict = sub_animDict;
				spe.LastAnimation.name = sub_animName;
				if (att.Exists() && spe.AttachmentArgs.isAttached)
					spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
				spe.TaskSequence.Reset();
				if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
				{
					sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
					sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
					sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
				}
			}
			return;
		}

		if (stop)
		{
			GTAped ped = local_ped_id;
			GTAentity att;
			auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
			}

			GTAvehicle veh = ped.CurrentVehicle();
			bool isInVehicle = veh.Exists();
			VehicleSeat vehSeat;
			if (isInVehicle)
			{
				vehSeat = ped.CurrentVehicleSeat_get();
			}
			ped.Task().ClearAllImmediately();
			if (isInVehicle)
			{
				ped.SetIntoVehicle(veh, vehSeat);
			}

			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				spe.LastAnimation.dict.clear();
				spe.LastAnimation.name.clear();
				if (att.Exists() && spe.AttachmentArgs.isAttached)
					spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
				spe.TaskSequence.Reset();
				if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
				{
					sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
					sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
					sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
				}
			}
			return;
		}

		if (inputDict)
		{
			std::string inputStr = Game::InputBox(_globalCustomAnim_dict, 126U, "Enter dict:", _globalCustomAnim_dict);
			if (inputStr.length() > 0)
				_globalCustomAnim_dict = inputStr;
			else Game::Print::PrintError_InvalidInput();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1String, _globalCustomAnim_dict, 126U, "Enter dict:", _globalCustomAnim_dict);
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_globalCustomAnim_dict);
			return;
		}

		if (inputName)
		{
			std::string inputStr = Game::InputBox(_globalCustomAnim_name, 126U, "Enter name:", _globalCustomAnim_name);
			if (inputStr.length() > 0)
				_globalCustomAnim_name = inputStr;
			else Game::Print::PrintError_InvalidInput();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1String, _globalCustomAnim_name, 126U, "Enter name:", _globalCustomAnim_name);
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_globalCustomAnim_name);
			return;
		}


	}
	void AnimationSub_Deer()
	{
		const std::string& tempDict = dict;

		AddTitle("Animalations");
		AddanimOption_("Idle Turn Left", tempDict, "idle_turn_l");
		AddanimOption_("Idle Turn Right", tempDict, "idle_turn_r");
		AddanimOption_("gallop_turn_l", tempDict);
		AddanimOption_("gallop_turn_r", tempDict);
		AddanimOption_("walk_turn_l", tempDict);
		AddanimOption_("walk_turn_r", tempDict);
		AddanimOption_("walk_start_0_l", tempDict);
		AddanimOption_("walk_start_0_r", tempDict);
		AddanimOption_("walk_start_90_l", tempDict);
		AddanimOption_("walk_start_90_r", tempDict);
		AddanimOption_("walk_backwards", tempDict);
		AddanimOption_("gallop", tempDict);
		AddanimOption_("canter", tempDict);
		AddanimOption_("trot", tempDict);
		AddanimOption_("dead_left", tempDict);
		AddanimOption_("dying", tempDict);


	}
	void AnimationSub_Shark()
	{
		const std::string& tempDict = dict;

		AddTitle("Animalations");
		AddanimOption_("attack_player", tempDict, "attack_player");
		AddanimOption_("swim_turn_r", tempDict, "swim_turn_r");
		AddanimOption_("swim_turn_l", tempDict, "swim_turn_l");
		AddanimOption_("dead_left", tempDict, "dead_left");
		AddanimOption_("dead_right", tempDict, "dead_right");
		AddanimOption_("dead_up", tempDict, "dead_up");
		AddanimOption_("dying", tempDict, "dying");
		AddanimOption_("attack_cam", tempDict, "attack_cam");
		AddanimOption_("attack", tempDict, "attack");
		AddanimOption_("attack_onspot", tempDict, "attack_onspot");
		AddanimOption_("attack_jump", tempDict, "attack_jump");
		AddanimOption_("swim", tempDict, "swim");
		AddanimOption_("accelerate", tempDict, "accelerate");


	}
	void AnimationSub_MissRappel()
	{
		const std::string& tempDict = dict;

		AddTitle("Swat Animations");
		AddanimOption_("rappel_to_free_rope_prop", tempDict);
		AddanimOption_("rope_slide", tempDict);
		AddanimOption_("rappel_jump_a_prop", tempDict);
		AddanimOption_("rappel_jump_c", tempDict);
		AddanimOption_("rappel_walk", tempDict);
		AddanimOption_("rappel_jump_c_prop", tempDict);
		AddanimOption_("rappel_loop", tempDict);
		AddanimOption_("rappel_to_free_rope", tempDict);
		AddanimOption_("rope_idle", tempDict);
		AddanimOption_("rappel_walk_prop", tempDict);
		AddanimOption_("rappel_idle", tempDict);
		AddanimOption_("rappel_idle_prop", tempDict);
		AddanimOption_("rappel_intro_player", tempDict);
		AddanimOption_("land_action", tempDict);
		AddanimOption_("land_crouched", tempDict);
		AddanimOption_("rappel_jump_a", tempDict);
		AddanimOption_("land", tempDict);


	}
	void AnimationSub_GestSit()
	{
		const std::string& tempDict = dict;

		AddTitle("Sitting Animations");
		AddanimOption_("Sit n Shit", "timetable@trevor@on_the_toilet", "trevonlav_struggleloop");
		AddanimOption_("Smoke Meth", "timetable@trevor@smoking_meth@base", "base");
		AddanimOption_("Michael Exit Chair", "switch@michael@sitting", "exit_forward_chair");
		AddanimOption_("Michael Exit Chair 2", "switch@michael@sitting", "exit_forward");
		AddanimOption_("Michael Idle", "switch@michael@sitting", "idle_chair");
		AddanimOption_("Michael Idle 2", "switch@michael@sitting", "idle");
		AddanimOption_("Sitting On Car Bonnet", "switch@michael@sitting_on_car_bonnet", "sitting_on_car_bonnet_loop");
		AddanimOption_("Sitting On Car Premiere", "switch@michael@sitting_on_car_premiere", "sitting_on_car_premiere_loop_player");
		AddanimOption_("sitting_stungun_idk", "stungun@sitting", "damage_vehicle");
		AddanimOption_("gesture_come_here_hard", tempDict);
		AddanimOption_("gesture_come_here_soft", tempDict);
		AddanimOption_("gesture_me_hard", tempDict);
		AddanimOption_("gesture_you_hard", tempDict);
		AddanimOption_("gesture_no_way", tempDict);
		AddanimOption_("gesture_why_left", tempDict);
		AddanimOption_("gesture_nod_no_hard", tempDict);
		AddanimOption_("gesture_hello", tempDict);
		AddanimOption_("gesture_i_will", tempDict);
		AddanimOption_("getsure_its_mine", tempDict);
		AddanimOption_("gesture_me", tempDict);
		AddanimOption_("gesture_you_soft", tempDict);
		AddanimOption_("gesture_what_hard", tempDict);
		AddanimOption_("gesture_pleased", tempDict);
		AddanimOption_("gesture_shrug_soft", tempDict);
		AddanimOption_("gesture_point", tempDict);
		AddanimOption_("gesture_shrug_hard", tempDict);
		AddanimOption_("gesture_why", tempDict);
		AddanimOption_("gesture_nod_no_soft", tempDict);
		AddanimOption_("gesture_nod_yes_hard", tempDict);
		AddanimOption_("gesture_what_soft", tempDict);
		AddanimOption_("gesture_nod_yes_soft", tempDict);
		AddanimOption_("gesture_damn", tempDict);
		AddanimOption_("gesture_displeased", tempDict);
		AddanimOption_("gesture_easy_now", tempDict);
		AddanimOption_("gesture_hand_down", tempDict);
		AddanimOption_("gesture_hand_left", tempDict);
		AddanimOption_("gesture_bring_it_on", tempDict);
		AddanimOption_("gesture_bye_hard", tempDict);
		AddanimOption_("gesture_bye_soft", tempDict);
		AddanimOption_("gesture_head_no", tempDict);
		AddanimOption_("gesture_hand_right", tempDict);




	}
	void AnimationSub_Swat()
	{
		const std::string& tempDict = dict;

		AddTitle("Swat Animations");
		AddanimOption_("understood", tempDict);
		AddanimOption_("you_back", tempDict);
		AddanimOption_("rally_point", tempDict);
		AddanimOption_("you_fwd", tempDict);
		AddanimOption_("you_left", tempDict);
		AddanimOption_("you_right", tempDict);
		AddanimOption_("freeze", tempDict);
		AddanimOption_("go_fwd", tempDict);
		AddanimOption_("come", tempDict);


	}
	void AnimationSub_GuardReac()
	{
		const std::string& tempDict = dict;

		AddTitle("Guard Animations");
		AddanimOption_("1hand_fwd_fire_additive", tempDict);
		AddanimOption_("1hand_turn0r", tempDict);
		AddanimOption_("1hand_turn90r", tempDict);
		AddanimOption_("1hand_turn180r", tempDict);
		AddanimOption_("1hand_turn0l", tempDict);
		AddanimOption_("1hand_turn90l", tempDict);
		AddanimOption_("1hand_turn180l", tempDict);
		AddanimOption_("1hand_aim_med_sweep", tempDict);
		AddanimOption_("1hand_aiming_cycle", tempDict);
		AddanimOption_("1hand_aiming_to_idle", tempDict);
		AddanimOption_("med_down", tempDict);
		AddanimOption_("1hand_aim_additive", tempDict);
		AddanimOption_("1hand_aim_high_sweep", tempDict);
		AddanimOption_("1hand_aim_low_sweep", tempDict);
		AddanimOption_("1hand_right_trans", tempDict);
		AddanimOption_("1hand_left_trans", tempDict);


	}
	void AnimationSub_RandArrest()
	{
		const std::string& tempDict = dict;

		AddTitle("Arrest Animations");
		AddanimOption_("kneeling_arrest_get_up", tempDict);
		AddanimOption_("generic_radio_enter", tempDict);
		AddanimOption_("kneeling_arrest_escape", tempDict);
		AddanimOption_("generic_radio_chatter", tempDict);
		AddanimOption_("cop_gunaimed_door_open_idle", tempDict);
		AddanimOption_("generic_radio_exit", tempDict);
		AddanimOption_("thanks_male_05", tempDict);
		AddanimOption_("radio_exit", tempDict);
		AddanimOption_("radio_enter", tempDict);
		AddanimOption_("radio_chatter", tempDict);
		AddanimOption_("kneeling_arrest_idle", tempDict);
		AddanimOption_("idle_c", tempDict);
		AddanimOption_("idle_2_hands_up", tempDict);
		AddanimOption_("arrest_walk", tempDict);
		AddanimOption_("idle_a", "random@arrests@busted", "idle_a");
		AddanimOption_("idle_b", "random@arrests@busted", "idle_b");
		AddanimOption_("enter", "random@arrests@busted", "enter");
		AddanimOption_("idle_c", "random@arrests@busted", "idle_c");
		AddanimOption_("exit", "random@arrests@busted", "exit");





	}
	
	// Scenario animations

	namespace AnimationSub_TaskScenarios
	{
#pragma region scenariovector
		std::vector<std::string> vValues_TaskScenarios{ "bbq_registered", "bum_wash_mist_triggered", "bum_wash_scoop_triggered", "chaining_entry", "chaining_exit", "cigarette", "code_human_cower", "code_human_cower_female", "code_human_cower_male", "code_human_cower_stand",
			"code_human_cower_stand_female", "code_human_cower_stand_male", "code_human_cross_road_wait", "code_human_cross_road_wait_female", "code_human_cross_road_wait_male", "code_human_medic_kneel", "code_human_medic_tend_to_dead", "code_human_medic_time_of_death", "code_human_park_car", "code_human_police_crowd_control", "code_human_police_investigate",
			"code_human_stand_cower", "drill debris", "drive", "ear_to_text", "ear_to_text_fat", "ear_to_text_female", "ear_to_text_female_fat", "ear_to_text_leaning_female", "ear_to_text_leaning_male", "ear_to_text_male", "ear_to_text_male_fat",
			"exhale", "exhale_nose", "feeding_animal_small_triggered", "gardener_plant_dusty_hands_triggered", "gardener_plant_soil_debris_triggered", "grazing_animal_large_triggered", "leaf blower registered", "paparazzi_flash_triggered", "park_vehicle", "prop_bird_in_tree", "prop_bird_telegraph_pole",
			"prop_human_atm", "prop_human_atm_female", "prop_human_atm_female_player", "prop_human_atm_male", "prop_human_atm_male_player", "prop_human_bbq", "prop_human_bum_bin", "prop_human_bum_shopping_cart", "prop_human_movie_bulb", "prop_human_movie_studio_light", "prop_human_muscle_chin_ups",
			"prop_human_muscle_chin_ups_army", "prop_human_muscle_chin_ups_prison", "prop_human_parking_meter", "prop_human_parking_meter_female", "prop_human_parking_meter_male", "prop_human_seat_armchair", "prop_human_seat_armchair_female_arms_folded", "prop_human_seat_armchair_female_generic", "prop_human_seat_armchair_female_legs_crossed", "prop_human_seat_armchair_male_elbows_on_knees", "prop_human_seat_armchair_male_generic",
			"prop_human_seat_armchair_male_left_elbow_on_knee", "prop_human_seat_bar", "prop_human_seat_bar_female_elbows_on_bar", "prop_human_seat_bar_female_left_elbow_on_bar", "prop_human_seat_bar_male_elbows_on_bar", "prop_human_seat_bar_male_hands_on_bar", "prop_human_seat_bench", "prop_human_seat_bench_all", "prop_human_seat_bench_and_beer", "prop_human_seat_bench_and_beer_and_food", "prop_human_seat_bench_and_coffee",
			"prop_human_seat_bench_and_coffee_and_food", "prop_human_seat_bench_and_food", "prop_human_seat_bench_any", "prop_human_seat_bench_drink", "prop_human_seat_bench_drink_beer", "prop_human_seat_bench_drink_beer_female", "prop_human_seat_bench_drink_beer_male", "prop_human_seat_bench_drink_female_generic", "prop_human_seat_bench_drink_male_generic", "prop_human_seat_bench_female", "prop_human_seat_bench_female_arms_folded",
			"prop_human_seat_bench_female_food", "prop_human_seat_bench_female_generic_skinny", "prop_human_seat_bench_female_legs_crossed", "prop_human_seat_bench_food", "prop_human_seat_bench_male", "prop_human_seat_bench_male_elbows_on_knees", "prop_human_seat_bench_male_food", "prop_human_seat_bench_male_generic_skinny", "prop_human_seat_bench_male_left_elbow_on_knee", "prop_human_seat_bus_stop_wait", "prop_human_seat_bus_stop_wait_female_arms_folded",
			"prop_human_seat_bus_stop_wait_female_generic", "prop_human_seat_bus_stop_wait_female_legs_crossed", "prop_human_seat_bus_stop_wait_male_elbows_on_knees", "prop_human_seat_bus_stop_wait_male_generic", "prop_human_seat_bus_stop_wait_male_left_elbow_on_knee", "prop_human_seat_chair", "prop_human_seat_chair_all", "prop_human_seat_chair_and_beer", "prop_human_seat_chair_and_beer_and_food", "prop_human_seat_chair_and_coffee", "prop_human_seat_chair_and_coffee_and_food",
			"prop_human_seat_chair_and_food", "prop_human_seat_chair_any", "prop_human_seat_chair_drink", "prop_human_seat_chair_drink_beer", "prop_human_seat_chair_drink_beer_female", "prop_human_seat_chair_drink_beer_male", "prop_human_seat_chair_drink_female_generic", "prop_human_seat_chair_drink_male_generic", "prop_human_seat_chair_female_arms_folded", "prop_human_seat_chair_female_food", "prop_human_seat_chair_female_generic",
			"prop_human_seat_chair_female_generic_mp_player", "prop_human_seat_chair_female_generic_skinny", "prop_human_seat_chair_female_heels_mp_player", "prop_human_seat_chair_female_legs_crossed", "prop_human_seat_chair_food", "prop_human_seat_chair_male_elbows_on_knees", "prop_human_seat_chair_male_food", "prop_human_seat_chair_male_generic", "prop_human_seat_chair_male_generic_mp_player", "prop_human_seat_chair_male_generic_skinny", "prop_human_seat_chair_male_left_elbow_on_knee",
			"prop_human_seat_chair_mp_player", "prop_human_seat_chair_upright", "prop_human_seat_computer", "prop_human_seat_computer_female", "prop_human_seat_computer_male", "prop_human_seat_deckchair", "prop_human_seat_deckchair_any", "prop_human_seat_deckchair_drink", "prop_human_seat_deckchair_female", "prop_human_seat_deckchair_female_drink", "prop_human_seat_deckchair_male",
			"prop_human_seat_deckchair_male_generic_drink", "prop_human_seat_muscle_bench_press", "prop_human_seat_muscle_bench_press_prison", "prop_human_seat_sewing", "prop_human_seat_sewing_female", "prop_human_seat_strip_watch", "prop_human_seat_strip_watch_bit_thuggy", "prop_human_seat_strip_watch_bouncy_guy", "prop_human_seat_strip_watch_female", "prop_human_seat_sunlounger", "prop_human_seat_sunlounger_female",
			"prop_human_seat_sunlounger_male", "prop_human_seat_train", "prop_human_stand_impatient", "standing", "sweeping_litter_triggered", "walk", "welding_torch_spark_registered", "world_boar_grazing", "world_cat_sleeping_ground", "world_cat_sleeping_ledge", "world_chickenhawk_feeding",
			"world_chickenhawk_standing", "world_cormorant_standing", "world_cow_grazing", "world_coyote_howl", "world_coyote_rest", "world_coyote_walk", "world_coyote_wander", "world_crow_feeding", "world_crow_standing", "world_deer_grazing", "world_dog_barking_retriever",
			"world_dog_barking_rottweiler", "world_dog_barking_shepherd", "world_dog_barking_small", "world_dog_sitting__rottweiler", "world_dog_sitting_retriever", "world_dog_sitting_rottweiler", "world_dog_sitting_shepherd", "world_dog_sitting_small", "world_dolphin_swim", "world_fish_flee", "world_fish_idle",
			"world_gull_feeding", "world_gull_standing", "world_hen_flee", "world_hen_pecking", "world_hen_standing", "world_human_aa_coffee", "world_human_aa_smoke", "world_human_binoculars", "world_human_binoculars_female", "world_human_binoculars_male", "world_human_bum_freeway",
			"world_human_bum_slumped", "world_human_bum_slumped_laying_on_left_side", "world_human_bum_slumped_laying_on_right_side", "world_human_bum_standing", "world_human_bum_standing_male_depressed", "world_human_bum_standing_male_drunk", "world_human_bum_standing_male_twitchy", "world_human_bum_wash", "world_human_bum_wash_high", "world_human_bum_wash_low", "world_human_car_park_attendant",
			"world_human_cheering", "world_human_cheering_female_a", "world_human_cheering_female_b", "world_human_cheering_female_c", "world_human_cheering_female_d", "world_human_cheering_male_a", "world_human_cheering_male_b", "world_human_cheering_male_d", "world_human_cheering_male_e", "world_human_clipboard", "world_human_clipboard_male",
			"world_human_const_drill", "world_human_cop_idles", "world_human_cop_idles_female", "world_human_cop_idles_male", "world_human_drinking", "world_human_drinking_beer_female", "world_human_drinking_beer_male", "world_human_drinking_coffee_female", "world_human_drinking_coffee_male", "world_human_drinking_fat_beer_male", "world_human_drinking_fat_coffee_female",
			"world_human_drug_dealer", "world_human_drug_dealer_hard", "world_human_drug_dealer_soft", "world_human_gardener_leaf_blower", "world_human_gardener_plant", "world_human_gardener_plant_female", "world_human_gardener_plant_male", "world_human_golf_player", "world_human_golf_player_male", "world_human_guard_patrol", "world_human_guard_stand",
			"world_human_guard_stand_army", "world_human_hammering", "world_human_hang_out_street", "world_human_hang_out_street_female_arm_side", "world_human_hang_out_street_female_arms_crossed", "world_human_hang_out_street_female_hold_arm", "world_human_hang_out_street_male_a", "world_human_hang_out_street_male_b", "world_human_hang_out_street_male_c", "world_human_hiker", "world_human_hiker_female",
			"world_human_hiker_male", "world_human_hiker_standing", "world_human_hiker_standing_female", "world_human_hiker_standing_male", "world_human_human_statue", "world_human_janitor", "world_human_jog", "world_human_jog_female", "world_human_jog_male", "world_human_jog_standing", "world_human_jog_standing_female",
			"world_human_jog_standing_male", "world_human_jog_standing_male_fit", "world_human_leaning", "world_human_leaning_female_coffee", "world_human_leaning_female_hand_up", "world_human_leaning_female_holding_elbow", "world_human_leaning_female_mobile", "world_human_leaning_female_smoking", "world_human_leaning_female_texting", "world_human_leaning_male_beer", "world_human_leaning_male_coffee",
			"world_human_leaning_male_foot_up", "world_human_leaning_male_hands_together", "world_human_leaning_male_legs_crossed", "world_human_leaning_male_mobile", "world_human_leaning_male_smoking", "world_human_leaning_male_texting", "world_human_maid_clean", "world_human_mobile_film_shocking", "world_human_mobile_film_shocking_female", "world_human_mobile_film_shocking_male", "world_human_muscle_flex",
			"world_human_muscle_flex_arms_at_side", "world_human_muscle_flex_arms_in_front", "world_human_muscle_free_weights", "world_human_muscle_free_weights_male_barbell", "world_human_musician", "world_human_musician_male_bongos", "world_human_musician_male_guitar", "world_human_paparazzi", "world_human_partying", "world_human_partying_female_partying_beer", "world_human_partying_female_partying_cellphone",
			"world_human_partying_male_partying_beer", "world_human_picnic", "world_human_picnic_female", "world_human_picnic_male", "world_human_power_walker", "world_human_prostitute_cokehead", "world_human_prostitute_crackhooker", "world_human_prostitute_french", "world_human_prostitute_high_class", "world_human_prostitute_hooker", "world_human_prostitute_low_class",
			"world_human_push_ups", "world_human_seat_ledge", "world_human_seat_ledge_eating", "world_human_seat_ledge_eating_female", "world_human_seat_ledge_eating_male", "world_human_seat_ledge_female", "world_human_seat_ledge_male", "world_human_seat_steps", "world_human_seat_steps_female", "world_human_seat_steps_male_elbows_on_knees", "world_human_seat_steps_male_elbows_on_knees_skinny",
			"world_human_seat_steps_male_hands_in_lap", "world_human_seat_wall", "world_human_seat_wall_eating", "world_human_seat_wall_eating_female", "world_human_seat_wall_eating_male", "world_human_seat_wall_female", "world_human_seat_wall_male", "world_human_seat_wall_tablet", "world_human_seat_wall_tablet_female", "world_human_seat_wall_tablet_male", "world_human_security_shine_torch",
			"world_human_sit_ups", "world_human_smoking", "world_human_smoking_fat_female", "world_human_smoking_fat_male_a", "world_human_smoking_fat_male_b", "world_human_smoking_female", "world_human_smoking_male_a", "world_human_smoking_male_b", "world_human_smoking_pot", "world_human_smoking_pot_female", "world_human_smoking_pot_female_fat",
			"world_human_smoking_pot_male", "world_human_stand_fire", "world_human_stand_fire_male", "world_human_stand_fishing", "world_human_stand_impatient", "world_human_stand_impatient_female", "world_human_stand_impatient_male", "world_human_stand_impatient_upright", "world_human_stand_mobile", "world_human_stand_mobile_call_female", "world_human_stand_mobile_call_male",
			"world_human_stand_mobile_fat_call_female", "world_human_stand_mobile_fat_call_male", "world_human_stand_mobile_fat_text_female", "world_human_stand_mobile_fat_text_male", "world_human_stand_mobile_text_female", "world_human_stand_mobile_text_male", "world_human_stand_mobile_upright", "world_human_strip_watch_stand", "world_human_strip_watch_stand_male_a", "world_human_strip_watch_stand_male_b", "world_human_strip_watch_stand_male_c",
			"world_human_stupor", "world_human_stupor_male", "world_human_stupor_male_looking_left", "world_human_stupor_male_looking_right", "world_human_sunbathe", "world_human_sunbathe_back", "world_human_sunbathe_back", "world_human_sunbathe_back_female", "world_human_sunbathe_back_male", "world_human_sunbathe_female", "world_human_sunbathe_male",
			"world_human_superhero", "world_human_superhero_space_pistol", "world_human_superhero_space_rifle", "world_human_swimming", "world_human_tennis_player", "world_human_tourist_map", "world_human_tourist_map_female", "world_human_tourist_map_male", "world_human_tourist_mobile", "world_human_tourist_mobile_female", "world_human_tourist_mobile_male",
			"world_human_vehicle_mechanic", "world_human_welding", "world_human_window_shop_browse", "world_human_window_shop_browse_female", "world_human_window_shop_browse_male", "world_human_yoga", "world_human_yoga_female", "world_human_yoga_male", "world_lookat_point", "world_mountain_lion_rest", "world_mountain_lion_wander",
			"world_orca_swim", "world_pig_grazing", "world_pigeon_feeding", "world_pigeon_standing", "world_rabbit_eating", "world_rabbit_feeding", "world_rabbit_flee", "world_rats_eating", "world_rats_fleeing", "world_shark_hammerhead_swim", "world_shark_swim",
			"world_stingray_swim", "world_vehicle_ambulance", "world_vehicle_attractor", "world_vehicle_bicycle_bmx", "world_vehicle_bicycle_bmx_ballas", "world_vehicle_bicycle_bmx_family", "world_vehicle_bicycle_bmx_harmony", "world_vehicle_bicycle_bmx_vagos", "world_vehicle_bicycle_mountain", "world_vehicle_bicycle_road", "world_vehicle_bike_off_road_race",
			"world_vehicle_biker", "world_vehicle_boat_idle", "world_vehicle_boat_idle_alamo", "world_vehicle_boat_idle_marquis", "world_vehicle_broken_down", "world_vehicle_businessmen", "world_vehicle_cluckin_bell_trailer", "world_vehicle_construction_passengers", "world_vehicle_construction_solo", "world_vehicle_distant_empty_ground", "world_vehicle_drive_passengers",
			"world_vehicle_drive_passengers_limited", "world_vehicle_drive_solo", "world_vehicle_empty", "world_vehicle_farm_worker", "world_vehicle_fire_truck", "world_vehicle_heli_lifeguard", "world_vehicle_mariachi", "world_vehicle_mechanic", "world_vehicle_military_planes_big", "world_vehicle_military_planes_small", "world_vehicle_park_parallel",
			"world_vehicle_park_perpendicular_nose_in", "world_vehicle_passenger_exit", "world_vehicle_police", "world_vehicle_police_bike", "world_vehicle_police_car", "world_vehicle_police_next_to_car", "world_vehicle_quarry", "world_vehicle_salton", "world_vehicle_salton_dirt_bike", "world_vehicle_security_car", "world_vehicle_streetrace",
			"world_vehicle_tandl", "world_vehicle_tourbus", "world_vehicle_tourist", "world_vehicle_tractor", "world_vehicle_tractor_beach", "world_vehicle_truck_logs", "world_vehicle_trucks_trailers", "world_whale_swim" };
#pragma endregion
		//struct NamedScenario { std::string name; std::string label; };
#pragma region named scenariovector
		std::vector<NamedScenario> vNamedScenarios
		{
			{ "Drilling", "WORLD_HUMAN_CONST_DRILL" },
			{ "Hammering", "WORLD_HUMAN_HAMMERING" },
			{ "Mechanic", "WORLD_HUMAN_VEHICLE_MECHANIC" },
			{ "Janitor", "WORLD_HUMAN_JANITOR" },
			{ "Hang Out", "WORLD_HUMAN_HANG_OUT_STREET" },
			{ "Play Guitar", "WORLD_HUMAN_MUSICIAN_MALE_BONGOS" },
			{ "Play Bongos", "WORLD_HUMAN_MUSICIAN_MALE_GUITAR" },
			{ "Clipboard", "WORLD_HUMAN_CLIPBOARD" },
			{ "Smoking", "WORLD_HUMAN_SMOKING" },
			{ "Smoking 2", "WORLD_HUMAN_AA_SMOKE" },
			{ "Smoking Weed", "WORLD_HUMAN_SMOKING_POT" },
			{ "Standing With Phone", "WORLD_HUMAN_STAND_MOBILE" },
			{ "Standing With Phone 2", "WORLD_HUMAN_STAND_MOBILE_UPRIGHT" },
			{ "Standing Guard", "WORLD_HUMAN_GUARD_STAND" },
			{ "Standing Impatiently", "WORLD_HUMAN_STAND_IMPATIENT" },
			{ "Standing Impatiently 2", "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT" },
			{ "Soldier Stand", "WORLD_HUMAN_GUARD_STAND_ARMY" },
			{ "Hobo Stand", "WORLD_HUMAN_BUM_STANDING" },
			{ "Doing Pushups", "WORLD_HUMAN_PUSH_UPS" },
			{ "Lifting Weights", "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS" },
			{ "Flexing", "WORLD_HUMAN_MUSCLE_FLEX" },
			{ "Drug Dealer", "WORLD_HUMAN_DRUG_DEALER_HARD" },
			{ "Hooker", "WORLD_HUMAN_PROSTITUTE_LOW_CLASS" },
			{ "Hooker 2", "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS" },
			{ "Drunk", "WORLD_HUMAN_STUPOR" },
			{ "Drinking", "WORLD_HUMAN_DRINKING" },
			{ "Drinking Coffee", "WORLD_HUMAN_AA_COFFEE" },
			{ "Binoculars", "WORLD_HUMAN_BINOCULARS" },
			{ "Welding", "WORLD_HUMAN_WELDING" },
			{ "Shocked", "WORLD_HUMAN_MOBILE_FILM_SHOCKING" },
			{ "Taking Pictures", "WORLD_HUMAN_PAPARAZZI" },
			{ "Medic", "CODE_HUMAN_MEDIC_KNEEL" },
			{ "Window Shopping", "WORLD_HUMAN_WINDOW_SHOP_BROWSE" },
			{ "Cleaning", "WORLD_HUMAN_MAID_CLEAN" },
			{ "Doing Yoga", "WORLD_HUMAN_YOGA" },
			{ "Tourist Map", "WORLD_HUMAN_TOURIST_MAP" },
			{ "Tennis Player", "WORLD_HUMAN_TENNIS_PLAYER" },
			{ "Sunbathing", "WORLD_HUMAN_SUNBATHE" },
			{ "Sunbathing 2", "WORLD_HUMAN_SUNBATHE_BACK" },
			{ "Fishing", "WORLD_HUMAN_STAND_FISHING" },
			{ "Shining Torch", "WORLD_HUMAN_SECURITY_SHINE_TORCH" },
			{ "Picnic", "WORLD_HUMAN_PICNIC" },
			{ "Partying", "WORLD_HUMAN_PARTYING" },
			{ "Leaning", "WORLD_HUMAN_LEANING" },
			{ "Jog Standing", "WORLD_HUMAN_JOG_STANDING" },
			{ "Human Statue", "WORLD_HUMAN_HUMAN_STATUE" },
			{ "Hanging Out (Street)", "WORLD_HUMAN_HANG_OUT_STREET" },
			{ "Golf Player", "WORLD_HUMAN_GOLF_PLAYER" },
			{ "Gardening", "WORLD_HUMAN_GARDENER_PLANT" },
			{ "Drug Dealing", "WORLD_HUMAN_DRUG_DEALER_HARD" },
			{ "Cheering", "WORLD_HUMAN_CHEERING" },
			{ "Parking Attendant", "WORLD_HUMAN_CAR_PARK_ATTENDANT" },
			{ "Wash", "WORLD_HUMAN_BUM_WASH" },
			{ "Holding Sign", "WORLD_HUMAN_BUM_FREEWAY" },
			{ "Laying Down (Hobo)", "WORLD_HUMAN_BUM_SLUMPED" },
			{ "BBQ", "PROP_HUMAN_BBQ" },
		};
#pragma endregion

		auto& _searchStr = dict;

		void __AddOption(const std::string& text, const std::string& scenarioLabel, int delay = -1, bool playEnterAnim = true)
		{
			bool pressed = false;
			AddTickol(text, IS_PED_USING_SCENARIO(local_ped_id, const_cast<PCHAR>(scenarioLabel.c_str())), pressed, pressed, TICKOL::MANWON);
			if (pressed)
			{
				GTAped ped = local_ped_id;
				GTAentity att;
				auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
				if (spi >= 0)
				{
					auto& spe = sub::Spooner::Databases::EntityDb[spi];
					Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
				}

				//if (animDict.length() > 0) Game::RequestAnimDict((PCHAR)animDict.c_str());
				ped.Task().ClearAllImmediately();
				if (!ped.Task().IsUsingScenario(scenarioLabel))
				{
					//ped.Task().StartScenario(scenarioLabel, delay, playEnterAnim);
					TASK_START_SCENARIO_IN_PLACE(local_ped_id, const_cast<PCHAR>(scenarioLabel.c_str()), delay, playEnterAnim);
				}

				if (scenarioLabel.find("MUSICIAN") != std::string::npos)
				{
					ped.Task().ClearAllImmediately();
					TASK_START_SCENARIO_IN_PLACE(local_ped_id, "WORLD_HUMAN_MUSICIAN", delay, playEnterAnim);
				}

				if (spi >= 0)
				{
					auto& spe = sub::Spooner::Databases::EntityDb[spi];
					spe.LastAnimation.dict.clear();
					spe.LastAnimation.name = scenarioLabel;
					if (att.Exists() && spe.AttachmentArgs.isAttached)
						spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
					spe.TaskSequence.Reset();
					if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
					{
						sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
						sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
						sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
					}
				}

			}
		}
		void stopScenarioPls()
		{
			GTAped ped = local_ped_id;
			GTAentity att;
			auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(ped);
			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
			}

			GTAvehicle veh = ped.CurrentVehicle();
			bool isInVehicle = veh.Exists();
			VehicleSeat vehSeat;
			if (isInVehicle)
			{
				vehSeat = ped.CurrentVehicleSeat_get();
			}
			ped.Task().ClearAllImmediately();
			if (isInVehicle)
			{
				ped.SetIntoVehicle(veh, vehSeat);
			}

			if (spi >= 0)
			{
				auto& spe = sub::Spooner::Databases::EntityDb[spi];
				spe.LastAnimation.dict.clear();
				spe.LastAnimation.name.clear();
				if (att.Exists() && spe.AttachmentArgs.isAttached)
					spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
				spe.TaskSequence.Reset();
				if (sub::Spooner::SelectedEntity.Handle.Equals(spe.Handle))
				{
					sub::Spooner::SelectedEntity.LastAnimation.dict = spe.LastAnimation.dict;
					sub::Spooner::SelectedEntity.LastAnimation.name = spe.LastAnimation.name;
					sub::Spooner::SelectedEntity.TaskSequence = spe.TaskSequence;
				}
			}
		}

		void AnimationSub_TaskScenarios()
		{
			bool clearSearchStr = false;
			bool musician_on = false;

			AddTitle("Scenarios");

			AddOption("ALL SCENARIOS", clearSearchStr, nullFunc, SUB::ANIMATIONSUB_TASKSCENARIOS2); if (clearSearchStr)
				_searchStr.clear();

			AddOption("End Scenarios", null, stopScenarioPls);

			for (auto& scen : vNamedScenarios)
			{
				__AddOption(scen.name, scen.label);
			}
		}
		void AnimationSub_TaskScenarios2()
		{
			bool searchobj = 0;

			AddTitle("All Scenarios");

			AddOption(_searchStr.empty() ? "SEARCH" : boost::to_upper_copy(_searchStr), searchobj, nullFunc, -1, true); if (searchobj)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "", _searchStr);
				boost::to_lower(_searchStr);
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToLower, _searchStr, 126U, std::string(), _searchStr);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
			}

			AddOption("End Scenarios", null, stopScenarioPls);

			for (auto& current : vValues_TaskScenarios)
			{
				if (!_searchStr.empty()) { if (current.find(_searchStr) == std::string::npos) continue; }

				__AddOption(current, current);
			}

		}

	}

	// Movement clipsets

	std::string get_ped_movement_clipset(const GTAentity& ped)
	{
		auto it = g_pedList_movGrp.find(ped.GetHandle());
		if (it != g_pedList_movGrp.end())
		{
			return it->second;
		}
		return std::string();
	}
	void set_ped_movement_clipset(GTAentity ped, const std::string& setName)
	{
		Game::RequestAnimSet(setName);
		SET_PED_MOVEMENT_CLIPSET(ped.Handle(), const_cast<PCHAR>(setName.c_str()), 0x3E800000);
		WAIT(30);
		Vector3& coord = GET_ENTITY_COORDS(ped.Handle(), 1);
		SET_ENTITY_COORDS(local_ped_id, coord.x, coord.y, coord.z + 0.05f, 0, 0, 0, 1);
		FREEZE_ENTITY_POSITION(ped.Handle(), 0);
		g_pedList_movGrp[ped.Handle()] = setName;
	}
	std::string get_ped_weapon_movement_clipset(const GTAentity& ped)
	{
		auto it = g_pedList_wmovGrp.find(ped.GetHandle());
		if (it != g_pedList_wmovGrp.end())
		{
			return it->second;
		}
		return std::string();
	}
	void set_ped_weapon_movement_clipset(GTAentity ped, const std::string& setName)
	{
		Game::RequestAnimSet(setName);
		SET_PED_WEAPON_MOVEMENT_CLIPSET(ped.Handle(), const_cast<PCHAR>(setName.c_str()));
		WAIT(30);
		Vector3& coord = GET_ENTITY_COORDS(ped.Handle(), 1);
		SET_ENTITY_COORDS(local_ped_id, coord.x, coord.y, coord.z + 0.05f, 0, 0, 0, 1);
		FREEZE_ENTITY_POSITION(ped.Handle(), 0);
		g_pedList_wmovGrp[ped.Handle()] = setName;
	}

	void AddmovgrpOption_(const std::string& text, std::string movgrp = "", bool &extra_option_code = null)
	{
		if (movgrp.length() == 0) movgrp = text;
		PCHAR movgrp2 = const_cast<PCHAR>(movgrp.c_str());

		bool bMovGrpIsActive = get_ped_movement_clipset(local_ped_id) == movgrp2;

		bool pressed = false;
		AddTickol(text, bMovGrpIsActive, pressed, pressed); if (pressed)
		{
			set_ped_movement_clipset(local_ped_id, movgrp);
			extra_option_code = true;
		}
	}
	void AddwmovgrpOption_(const std::string& text, std::string movgrp = "", bool &extra_option_code = null)
	{
		if (movgrp.length() == 0) movgrp = text;
		PCHAR movgrp2 = const_cast<PCHAR>(movgrp.c_str());

		bool bMovGrpIsActive = get_ped_weapon_movement_clipset(local_ped_id) == movgrp2;

		bool pressed = false;
		AddTickol(text, bMovGrpIsActive, pressed, pressed); if (pressed)
		{
			set_ped_weapon_movement_clipset(local_ped_id, movgrp);
			extra_option_code = true;
		}
	}
	void MovementGroup_()
	{
		auto mgit = g_pedList_movGrp.find(local_ped_id);
		bool mgitIsValid = mgit != g_pedList_movGrp.end();

		auto wmgit = g_pedList_wmovGrp.find(local_ped_id);
		bool wmgitIsValid = mgit != g_pedList_wmovGrp.end();

		bool MovementGroupReset_ = 0, MovementGroupResetW_ = 0;

		AddTitle("Movement Styles");
		AddTickol("Default", !mgitIsValid, MovementGroupReset_, MovementGroupReset_);
		AddmovgrpOption_("Generic Male", "move_m@generic");
		AddmovgrpOption_("Generic Female", "move_f@generic");
		AddmovgrpOption_("Policeman", "move_cop@action");
		AddmovgrpOption_("Drunk", "move_m@drunk@a");
		AddmovgrpOption_("Moderate Drunk", "move_m@drunk@moderatedrunk");
		AddmovgrpOption_("Moderate Drunk 2", "move_m@drunk@moderatedrunk_head_up");
		AddmovgrpOption_("Slightly Drunk", "move_m@drunk@slightlydrunk");
		AddmovgrpOption_("Very Drunk", "move_m@drunk@verydrunk");
		//	AddmovgrpOption_("Very Drunk Idle", "move_m@drunk@verydrunk_idles@");
		AddmovgrpOption_("Gangster", "move_m@gangster@generic");
		AddmovgrpOption_("Hipster", "move_m@hipster@a");
		AddmovgrpOption_("Hobo", "move_m@hobo@a");
		AddmovgrpOption_("Hobo2", "move_m@hobo@b");
		AddmovgrpOption_("Obese", "move_m@fat@a");
		AddmovgrpOption_("Obese2", "move_f@fat@a");
		AddmovgrpOption_("Lester", "move_lester_CaneUp");
		AddmovgrpOption_("Film Female", "move_f@film_reel");
		AddmovgrpOption_("Cool Jog", "move_m@jog@");
		AddmovgrpOption_("Leaf Blower", "move_m@leaf_blower");
		AddmovgrpOption_("Tool Belt Walk", "move_m@tool_belt@a");
		AddmovgrpOption_("Tool Belt Walk 2", "move_f@tool_belt@a");
		AddmovgrpOption_("Appealing", "move_f@sexy@a");
		AddmovgrpOption_("Amanda - Bag", "move_characters@amanda@bag");
		AddmovgrpOption_("Michael - Fire", "move_characters@michael@fire");
		AddmovgrpOption_("Franklin - Fire", "move_characters@franklin@fire");
		AddmovgrpOption_("Jimmy - Nervous", "move_characters@jimmy@nervous@");
		AddmovgrpOption_("Jimmy - Slow", "move_characters@jimmy@slow@");
		AddmovgrpOption_("Alien", "move_m@alien");
		AddmovgrpOption_("Brave", "move_m@brave");
		AddmovgrpOption_("Brave2", "move_m@brave@a");
		AddmovgrpOption_("Brave3", "move_m@brave@b");
		AddmovgrpOption_("Brave4", "move_m@brave@fallback");
		AddmovgrpOption_("BraveStill", "move_m@brave@idle_a");
		AddmovgrpOption_("BraveStill2", "move_m@brave@idle_b");
		AddmovgrpOption_("Business", "move_m@business@a");
		AddmovgrpOption_("Business2", "move_m@business@b");
		AddmovgrpOption_("Business3", "move_m@business@c");
		AddmovgrpOption_("Casual", "move_m@casual@a");
		AddmovgrpOption_("Casual2", "move_m@casual@b");
		AddmovgrpOption_("Casual3", "move_m@casual@c");
		AddmovgrpOption_("Casual4", "move_m@casual@d");
		AddmovgrpOption_("Casual5", "move_m@casual@e");
		AddmovgrpOption_("Casual6", "move_m@casual@f");
		AddmovgrpOption_("Clipboard", "move_m@clipboard");
		AddmovgrpOption_("Coward", "move_m@coward");
		AddmovgrpOption_("Burning", "move_m@fire");
		AddmovgrpOption_("Flee", "move_m@flee@a");
		AddmovgrpOption_("Flee2", "move_m@flee@b");
		AddmovgrpOption_("Flee3", "move_m@flee@c");
		AddmovgrpOption_("Flee4", "move_f@flee@a");
		AddmovgrpOption_("Flee5", "move_f@flee@b");
		AddmovgrpOption_("Flee6", "move_f@flee@c");
		AddmovgrpOption_("Hiking", "move_m@hiking");
		AddmovgrpOption_("Hiking2", "move_f@hiking");
		AddmovgrpOption_("Hurry", "move_m@hurry@a");
		AddmovgrpOption_("Hurry2", "move_m@hurry@b");
		AddmovgrpOption_("Hurry3", "move_m@hurry@c");
		AddmovgrpOption_("Hurry4", "move_f@hurry@a");
		AddmovgrpOption_("Hurry5", "move_f@hurry@b");
		AddmovgrpOption_("Injured", "move_m@injured");
		AddmovgrpOption_("Injured2", "move_injured_generic");
		AddmovgrpOption_("Injured3", "move_f@injured");
		AddmovgrpOption_("Intimidation", "move_m@intimidation@1h");
		AddmovgrpOption_("Intimidation2", "move_m@intimidation@cop@unarmed");
		AddmovgrpOption_("Intimidation3", "move_m@intimidation@unarmed");
		AddmovgrpOption_("Muscular", "move_m@muscle@a");
		AddmovgrpOption_("Quick", "move_m@quick");
		AddmovgrpOption_("Sad", "move_m@sad@a");
		AddmovgrpOption_("Sad2", "move_m@sad@b");
		AddmovgrpOption_("Sad3", "move_m@sad@c");
		AddmovgrpOption_("Sad4", "move_f@sad@a");
		AddmovgrpOption_("Sad5", "move_f@sad@b");
		AddmovgrpOption_("Shady", "move_m@shadyped@a");
		AddmovgrpOption_("Shocked", "move_m@shocked@a");
		AddmovgrpOption_("Arrogant", "move_f@arrogant@a");
		AddmovgrpOption_("Chubby", "move_f@chubby@a");
		AddmovgrpOption_("Handbag Walk", "move_f@handbag");
		AddmovgrpOption_("Heels", "move_f@heels@c");
		//	AddmovgrpOption_("Runner", "move_f@runner");
		AddmovgrpOption_("move_p_m_one");
		AddmovgrpOption_("move_p_m_one_briefcase");
		AddmovgrpOption_("move_p_m_two");
		AddmovgrpOption_("move_p_m_zero");
		AddmovgrpOption_("move_p_m_zero_slow");
		AddmovgrpOption_("Ballistic", "anim_group_move_ballistic");
		//AddmovgrpOption_("Buggy", "move_crawl");

		AddBreak("Weapon Handling");
		AddTickol("Default", !wmgitIsValid, MovementGroupResetW_, MovementGroupResetW_);
		AddwmovgrpOption_("Lester's Cane", "move_lester_CaneUp");
		AddwmovgrpOption_("Crouched", "move_ped_crouched");
		AddwmovgrpOption_("Bucket", "move_ped_wpn_bucket");
		AddwmovgrpOption_("Mop", "move_ped_wpn_mop");
		AddwmovgrpOption_("Assault Rifle (Crouched)", "Wpn_AssaultRifle_WeaponHoldingCrouched");
		AddwmovgrpOption_("Garbageman", "missfbi4prepp1_garbageman");
		AddwmovgrpOption_("Prison Guard", "MOVE_M@PRISON_GAURD");
		AddwmovgrpOption_("Jerrycan (Generic)", "move_ped_wpn_jerrycan_generic");
		AddwmovgrpOption_("Golfer", "move_m@golfer@");
		AddwmovgrpOption_("Rucksack", "MOVE_P_M_ZERO_RUCKSACK");
		AddwmovgrpOption_("Clipboard", "MOVE_M@CLIPBOARD");
		AddwmovgrpOption_("Tennis (Male)", "weapons@tennis@male");
		AddwmovgrpOption_("Tennis Locomotion (Female)", "TENNIS_LOCOMOTION_FEMALE");
		AddwmovgrpOption_("Paparazzi (Standing)", "random@escape_paparazzi@standing@");
		AddwmovgrpOption_("Paparazzi (In Car)", "random@escape_paparazzi@incar@");
		//AddwmovgrpOption_("Paparazzo", "RCM_Paparazzo");
		AddwmovgrpOption_("Leaf Blower", "MOVE_M@LEAF_BLOWER");

		AddBreak("Weapon Animations (Doesn't Save)");
		const std::vector<std::pair<std::string, Hash>> vWeaponAnimsOrWhatever
		{
			{ "Default", 0xE4DF46D5 }, // default
			{ "Female", 0x6D155A1B }, // female
			{ "MP Freemode Female", 0xACB10C83 }, // mp_f_freemode
			{ "Ballistic", 0x5534A626 }, // ballistic
			{ "Unknown 1", 0xc531a409 }, // 0xc531a409
			{ "Unknown 2", 0x529e5780 }, // 0x529e5780
		};
		for (auto& wa : vWeaponAnimsOrWhatever)
		{
			bool bWeaponAnimPressed = false;
			AddOption(wa.first, bWeaponAnimPressed); if (bWeaponAnimPressed)
			{
				WEAPON::SET_WEAPON_ANIMATION_OVERRIDE(local_ped_id, wa.second);
			}
		}


		if (MovementGroupReset_)
		{
			RESET_PED_MOVEMENT_CLIPSET(local_ped_id, 0x3E800000);
			WAIT(10);
			Vector3 Coord = GET_ENTITY_COORDS(local_ped_id, 1);
			SET_ENTITY_COORDS_NO_OFFSET(local_ped_id, Coord.x, Coord.y, Coord.z + 0.05f, 1, 1, 0);
			FREEZE_ENTITY_POSITION(local_ped_id, 0);
			if (mgitIsValid) g_pedList_movGrp.erase(mgit);
		}
		if (MovementGroupResetW_)
		{
			RESET_PED_WEAPON_MOVEMENT_CLIPSET(local_ped_id);
			WAIT(10);
			Vector3 Coord = GET_ENTITY_COORDS(local_ped_id, 1);
			SET_ENTITY_COORDS_NO_OFFSET(local_ped_id, Coord.x, Coord.y, Coord.z + 0.05f, 1, 1, 0);
			FREEZE_ENTITY_POSITION(local_ped_id, 0);
			if (wmgitIsValid) g_pedList_wmovGrp.erase(wmgit);
		}

	}

	// Facial animations

	namespace FacialAnims_catind
	{
		//struct NamedFacialAnim { std::string caption; std::string animName; };
		const std::vector<NamedFacialAnim> vFacialAnims
		{
			{ "Normal", "mood_normal_1" },
			{ "Aiming", "mood_aiming_1" },
			{ "Angry", "mood_angry_1" },
			{ "Happy", "mood_happy_1" },
			{ "Injured", "mood_injured_1" },
			{ "Stressed", "mood_stressed_1" },
			{ "Smug", "mood_smug_1" },
			{ "Sulk", "mood_sulk_1" },
			{ "Sleeping", "mood_sleeping_1" },
			{ "Drunk", "mood_drunk_1" },
			{ "Burning", "burning_1" },
			{ "Dead", "dead_1" }
		};

		void Sub_FacialMood()
		{
			GTAentity ped = local_ped_id;
			auto& current = get_ped_facial_mood(ped);

			AddTitle("Mood");

			bool bClearPressed = false;
			AddTickol("Default", current.empty(), bClearPressed, bClearPressed); if (bClearPressed)
			{
				ped.RequestControl(400);
				clear_ped_facial_mood(ped);
			}

			for (auto& fa : vFacialAnims)
			{
				bool bFaPressed = false;
				AddTickol(fa.caption, current == fa.animName, bFaPressed, bFaPressed); if (bFaPressed)
				{
					ped.RequestControl(400);
					set_ped_facial_mood(ped, fa.animName);
					current = fa.animName;
				}
			}

		}
	}

}




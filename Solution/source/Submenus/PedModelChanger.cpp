/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PedModelChanger.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\Model.h"
#include "..\Util\ExePath.h"
#include "..\Util\StringManip.h"
#include "..\Util\keyboard.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\ModelNames.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\WeaponIndivs.h"

#include "..\Submenus\PedComponentChanger.h"
#include "..\Submenus\WeaponOptions.h"
#include "..\Submenus\Spooner\SpoonerEntity.h"
#include "..\Submenus\Spooner\Databases.h"
#include "..\Submenus\Spooner\EntityManagement.h"
#include "..\Submenus\Spooner\MenuOptions.h"

#include <string>
#include <vector>
#include <pugixml\src\pugixml.hpp>

namespace sub
{
	namespace PedFavourites_catind
	{
		std::string xmlFavouritePeds = "FavouritePeds.xml";
		std::string _searchStr = std::string();

		void ClearSearchStr() { _searchStr.clear(); }

		bool IsPedAFavourite(GTAmodel::Model model)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.document_element();
			return nodeRoot.find_child_by_attribute("hash", int_to_hexstring(model.hash, true).c_str()) != NULL;
		}
		bool AddPedToFavourites(GTAmodel::Model model, const std::string& customName)
		{
			if (customName.empty())
				return false;
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()).status != pugi::status_ok)
			{
				doc.reset();
				auto nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto nodeRoot = doc.append_child("FavouriteWeapons");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str());
			}
			pugi::xml_node nodeRoot = doc.document_element();

			auto nodeOldLoc = nodeRoot.find_child_by_attribute("hash", int_to_hexstring(model.hash, true).c_str());
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
			}
			auto nodeNewLoc = nodeRoot.append_child("Ped");
			nodeNewLoc.append_attribute("hash") = int_to_hexstring(model.hash, true).c_str();
			nodeNewLoc.append_attribute("customName") = customName.c_str();

			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()));
		}
		bool RemovePedFromFavourites(GTAmodel::Model model)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.document_element();
			auto nodeOldLoc = nodeRoot.find_child_by_attribute("hash", int_to_hexstring(model.hash, true).c_str());
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
			}

			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()));
		}

		void ShowInstructionalButton(GTAmodel::Model model)
		{
			bool bIsAFav = IsPedAFavourite(model);
			if (Menu::bit_controller)
			{
				Menu::add_IB(INPUT_SCRIPT_RLEFT, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

				if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
				{
					!bIsAFav ? AddPedToFavourites(model, Game::InputBox("", 28U, "Enter custom name:", get_ped_model_label(model, true))) : RemovePedFromFavourites(model);
					/*if (!bIsAFav)
					{
					OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouritePedModelSelected, "", 28U, "Enter custom name:", get_ped_model_label(model, true));
					OnscreenKeyboard::State::arg1._uint = model.hash;
					}
					else RemovePedFromFavourites(model);*/
				}
			}
			else
			{
				Menu::add_IB(VirtualKey::B, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

				if (IsKeyJustUp(VirtualKey::B))
				{
					!bIsAFav ? AddPedToFavourites(model, Game::InputBox("", 28U, "Enter custom name:", get_ped_model_label(model, true))) : RemovePedFromFavourites(model);
					/*if (!bIsAFav)
					{
					OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouritePedModelSelected, "", 28U, "Enter custom name:", get_ped_model_label(model, true));
					OnscreenKeyboard::State::arg1._uint = model.hash;
					}
					else RemovePedFromFavourites(model);*/
				}
			}
		}

		void Sub_PedFavourites()
		{
			Menu::OnSubBack = ClearSearchStr;

			AddTitle("Favourites");

			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str()).status != pugi::status_ok)
			{
				doc.reset();
				auto nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto nodeRoot = doc.append_child("FavouritePeds");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouritePeds).c_str());
				return;
			}
			pugi::xml_node nodeRoot = doc.document_element();

			bool bInputAdd = false;
			AddOption("Add New Ped Model", bInputAdd); if (bInputAdd)
			{
				std::string hashNameStr = Game::InputBox("", 40U, "Enter model name (e.g. IG_BENNY):");
				if (hashNameStr.length())
				{
					Model hashNameHash = GET_HASH_KEY(hashNameStr);
					if (hashNameHash.IsInCdImage())
					{
						WAIT(500);
						std::string customNameStr = Game::InputBox("", 28U, "Enter custom name:", get_ped_model_label(hashNameHash, true));
						if (customNameStr.length())
						{
							if (AddPedToFavourites(hashNameHash, customNameStr))
							{
								Game::Print::PrintBottomLeft("Ped model ~b~added~s~.");
							}
							else Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to add ped model.");
						}
						else Game::Print::PrintError_InvalidInput();
					}
					else Game::Print::PrintError_InvalidModel();
				}
				else Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::FavouritePedModelEntryName, std::string(), 40U, "Enter model name (e.g. IG_BENNY):");
			}

			if (nodeRoot.first_child())
			{
				AddBreak("---Added Ped Models---");

				bool bSearchPressed = false;
				AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
					boost::to_upper(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto nodeLocToLoad = nodeRoot.first_child(); nodeLocToLoad; nodeLocToLoad = nodeLocToLoad.next_sibling())
				{
					const std::string& customName = nodeLocToLoad.attribute("customName").as_string();
					Model model = nodeLocToLoad.attribute("hash").as_uint();

					if (!_searchStr.empty()) { if (boost::to_upper_copy(customName).find(_searchStr) == std::string::npos) continue; }

					AddmodelOption_(customName, model);
				}
			}
			//if (Menu::currentop > Menu::printingop) Menu::Up();
			//else if (Menu::currentop <= 0) Menu::Down();
		}
	}

	// Model changer

	void ChangeModel_(GTAmodel::Model model)
	{
		if (model.IsInCdImage())
		{
			if (model.Load(4000))
			{
				GTAped playerPed = PLAYER_PED_ID();
				int oldPlayerPed = playerPed.Handle();

				if (sub::PedDamageTextures_catind::vPedsAndDamagePacks.count(playerPed.Handle()))
					sub::PedDamageTextures_catind::vPedsAndDamagePacks.erase(playerPed.Handle());
				if (sub::PedDecals_catind::vPedsAndDecals.count(playerPed.Handle()))
					sub::PedDecals_catind::vPedsAndDecals.erase(playerPed.Handle());

				std::vector<s_Weapon_Components_Tint> weaponsBackup;
				playerPed.StoreWeaponsInArray(weaponsBackup);
				Hash currWeaponHash = playerPed.Weapon_get();

				GTAentity att;
				auto spi = sub::Spooner::EntityManagement::GetEntityIndexInDb(playerPed);
				if (spi >= 0)
				{
					auto& spe = sub::Spooner::Databases::EntityDb[spi];
					sub::Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(spe.Handle, att);
				}

				bool wasInVehicle = playerPed.IsInVehicle();
				GTAvehicle vehicle;
				VehicleSeat currentVehSeat;
				if (wasInVehicle)
				{
					vehicle = playerPed.CurrentVehicle();
					currentVehSeat = playerPed.CurrentVehicleSeat_get();
				}

				bool bHasCollision = playerPed.IsCollisionEnabled_get();

				SET_PLAYER_MODEL(PLAYER_ID(), model.hash);

				playerPed = PLAYER_PED_ID();

				playerPed.IsCollisionEnabled_set(bHasCollision);

				SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed.Handle());
				//SET_PED_RANDOM_COMPONENT_VARIATION(playerPed.Handle(), 0);

				model.Unload();


				if (wasInVehicle)
				{
					playerPed.SetIntoVehicle(vehicle, currentVehSeat);
				}

				if (playerPed.PedType() == PedType::Animal && !HAS_ANIM_DICT_LOADED("creatures@rottweiler@melee@streamed_core@"))
				{
					REQUEST_ANIM_DICT("creatures@rottweiler@melee@streamed_core@");
					REQUEST_ANIM_DICT("creatures@cougar@melee@streamed_core@");
				}

				playerPed.GiveWeaponsFromArray(weaponsBackup);
				if (IS_WEAPON_VALID(currWeaponHash))
					playerPed.Weapon_set(currWeaponHash);

				SET_PED_INFINITE_AMMO_CLIP(playerPed.Handle(), bit_infinite_ammo);

				if (spi >= 0)
				{
					auto& spe = sub::Spooner::Databases::EntityDb[spi];
					GTAentity oldPlayerPed = spe.Handle;
					spe.Handle = playerPed;
					spe.HashName = get_ped_model_label(model, true);
					if (spe.HashName.length() == 0)
						int_to_hexstring(model.hash, true);
					spe.LastAnimation.dict.clear();
					spe.LastAnimation.name.clear();
					if (att.Exists() && spe.AttachmentArgs.isAttached)
						spe.Handle.AttachTo(att, spe.AttachmentArgs.boneIndex, spe.Handle.IsCollisionEnabled_get(), spe.AttachmentArgs.offset, spe.AttachmentArgs.rotation);
					spe.TaskSequence.Reset();
					if (sub::Spooner::SelectedEntity.Handle.Equals(oldPlayerPed))
					{
						sub::Spooner::SelectedEntity = spe;
					}

					/*for (auto& e : sub::Spooner::Databases::EntityDb)
					{
					for (auto& t : e.TaskSequence.AllTasks())
					{
					if (t->targetEntity == oldPlayerPed)
					t->targetEntity = playerPed;
					}
					}*/
				}
			}
		}
	}
	void AddmodelchangerOption_(const std::string& text, const GTAmodel::Model& model, int tickTrue)
	{
		const GTAped& ped = Game::PlayerPed();
		const Model& pedModel = ped.Model();

		bool pressed = false;
		AddTickol(text, model.Equals(pedModel), pressed, pressed, static_cast<TICKOL>(tickTrue)); if (pressed)
		{
			PTFX::trigger_ptfx_1("scr_solomon3", "scr_trev4_747_blood_impact", 0, ped.GetOffsetInWorldCoords(0.37, -0.32f, -1.32f), Vector3(90.0f, 0, 0), 0.7f);
			ChangeModel_(model);
		}
	}
	void AddmodelOption_(const std::string& text, const GTAmodel::Model& model, bool* extra_option_code, int tickTrue)
	{
		if (model.IsInCdImage())
		{
			switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
			{
			case SUB::MODELCHANGER:
				AddmodelchangerOption_(text, model.hash, tickTrue);
				break;
			case SUB::PEDGUN_ALLPEDS:
				AddpgunOption_(text, model.hash, extra_option_code);
				break;
			case SUB::SPOONER_SPAWN_PED:
				sub::Spooner::MenuOptions::AddOption_AddPed(text, model);
				break;
			}

			if (*Menu::currentopATM == Menu::printingop)
				PedFavourites_catind::ShowInstructionalButton(model);
		}
	}

	void ModelChanger_()
	{
		bool ModelChangerRandomPedVariation_ = 0,
			ModelChangerInput_ = 0;
		//	 ModelChangerVariationWarning_ = 0,
		//	 ModelChangerSlendy_ = 0,
		//	 ModelChanger_Animal = 0;

		Static_241 = PLAYER_PED_ID();
		AddTitle("Model Changer");
		AddOption("Randomize Ped Variation", ModelChangerRandomPedVariation_);
		AddOption("Favourites", null, nullFunc, SUB::MODELCHANGER_FAVOURITES);
		AddOption("Player", null, nullFunc, SUB::MODELCHANGER_PLAYER);
		AddOption("Animals", null, nullFunc, SUB::MODELCHANGER_ANIMAL);
		AddOption("Ambient Females", null, nullFunc, SUB::MODELCHANGER_AMBFEMALES);
		AddOption("Ambient Males", null, nullFunc, SUB::MODELCHANGER_AMBMALES);
		AddOption("Cutscene Models", null, nullFunc, SUB::MODELCHANGER_CS);
		AddOption("Gang Female", null, nullFunc, SUB::MODELCHANGER_GANGFEMALES);
		AddOption("Gang Males", null, nullFunc, SUB::MODELCHANGER_GANGMALES);
		AddOption("Story Models", null, nullFunc, SUB::MODELCHANGER_STORY);
		AddOption("Multiplayer Models", null, nullFunc, SUB::MODELCHANGER_MP);
		AddOption("Scenario Females", null, nullFunc, SUB::MODELCHANGER_SCENARIOFEMALES);
		AddOption("Scenario Males", null, nullFunc, SUB::MODELCHANGER_SCENARIOMALES);
		AddOption("Story Scenario Females", null, nullFunc, SUB::MODELCHANGER_ST_SCENARIOFEMALES);
		AddOption("Story Scenario Males", null, nullFunc, SUB::MODELCHANGER_ST_SCENARIOMALES);
		AddOption("Others", null, nullFunc, SUB::MODELCHANGER_OTHERS);
		AddOption("~b~Input~s~ Model", ModelChangerInput_);


		if (ModelChangerRandomPedVariation_) {
			SET_PED_RANDOM_COMPONENT_VARIATION(Static_241, 0);
			SET_PED_RANDOM_PROPS(Static_241);
			return;
		}

		if (ModelChangerInput_) {
			std::string inputStr = Game::InputBox("", 64U, "Enter ped model name (e.g. IG_BENNY):");
			if (inputStr.length() > 0)
			{
				Model model = (inputStr);
				if (model.IsInCdImage())
					ChangeModel_(model);
				else
					Game::Print::PrintError_InvalidModel();
				return;
			}
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::ModelChangerInput, std::string(), 64U, "Enter ped model name (e.g. IG_BENNY):");
		}

		//if (ModelChangerVariationWarning_){
		//	Game::Print::PrintBottomCentre("~r~Warning:~s~ Do not change ped variation.");
		//	ModelChangerVariationWarning_ = false;
		//}

		//if (ModelChangerSlendy_){
		//	SET_PED_COMPONENT_VARIATION(Static_241, 0, 0, 3, 0);
		//	SET_PED_COMPONENT_VARIATION(Static_241, 0, 3, 3, 0);
		//	ModelChangerSlendy_ = false;
		//}



	}
	// I would really like this whole section to be refactored into one function - IJC
	void ModelChanger_Player()
	{
		AddTitle("Player");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Player[std::rand() % g_pedModels_Player.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Player)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Animal()
	{
		AddTitle("Animals");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Animal[std::rand() % g_pedModels_Animal.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Animal)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_AmbientFemale()
	{
		AddTitle("Ambient Females");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_AmbientFemale[std::rand() % g_pedModels_AmbientFemale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_AmbientFemale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_AmbientMale()
	{
		AddTitle("Ambient Males");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_AmbientMale[std::rand() % g_pedModels_AmbientMale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_AmbientMale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Cutscene()
	{
		AddTitle("Cutscene Models");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Cutscene[std::rand() % g_pedModels_Cutscene.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Cutscene)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_GangFemale()
	{
		AddTitle("Gang Females");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_GangFemale[std::rand() % g_pedModels_GangFemale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_GangFemale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_GangMale()
	{
		AddTitle("Gang Males");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_GangMale[std::rand() % g_pedModels_GangMale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_GangMale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Story()
	{
		AddTitle("Story Models");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Story[std::rand() % g_pedModels_Story.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Story)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Multiplayer()
	{
		AddTitle("Multiplayer Models");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Multiplayer[std::rand() % g_pedModels_Multiplayer.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Multiplayer)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_ScenarioFemale()
	{
		AddTitle("Scenario Females");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_ScenarioFemale[std::rand() % g_pedModels_ScenarioFemale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_ScenarioFemale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_ScenarioMale()
	{
		AddTitle("Scenario Males");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_ScenarioMale[std::rand() % g_pedModels_ScenarioMale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_ScenarioMale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Story_ScenarioFemale()
	{
		AddTitle("Story Scenario Females");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_StoryScenarioFemale[std::rand() % g_pedModels_StoryScenarioFemale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_StoryScenarioFemale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Story_ScenarioMale()
	{
		AddTitle("Story Scenario Males");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_StoryScenarioMale[std::rand() % g_pedModels_StoryScenarioMale.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_StoryScenarioMale)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}
	void ModelChanger_Others()
	{
		AddTitle("Others");
		std::pair<std::string, std::string> rngped;
		do {
			rngped = g_pedModels_Others[std::rand() % g_pedModels_Others.size()];
		} while (rngped.first == Game::PlayerPed().Model());
		AddmodelOption_("Random", (rngped.first), nullptr, 0);
		for (auto& pmn : g_pedModels_Others)
		{
			AddmodelOption_(pmn.second, (pmn.first));
		}
	}

}



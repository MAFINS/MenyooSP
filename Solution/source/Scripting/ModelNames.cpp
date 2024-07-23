/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "ModelNames.h"

#include "..\macros.h"

#include "enums.h"
#include "..\Util\ExePath.h"
#include "..\Memory\GTAmemory.h"
#include "..\Natives\natives2.h"
#include "Model.h"
#include "..\Util\StringManip.h"

#include <unordered_map>
#include <vector>
#include <array>
#include <utility>
#include <string>
#include <fstream>
#include <pugixml\src\pugixml.hpp>
#include <algorithm> // std::sort, VS 2019 update 16.7.1

#pragma region Vehicle model labels
std::vector<GTAmodel::Model> g_vehHashes;
std::vector<GTAmodel::Model> g_vehHashes_OPENWHEEL;
std::vector<GTAmodel::Model> g_vehHashes_SUPER;
std::vector<GTAmodel::Model> g_vehHashes_SPORT;
std::vector<GTAmodel::Model> g_vehHashes_SPORTSCLASSIC;
std::vector<GTAmodel::Model> g_vehHashes_COUPE;
std::vector<GTAmodel::Model> g_vehHashes_MUSCLE;
std::vector<GTAmodel::Model> g_vehHashes_OFFROAD;
std::vector<GTAmodel::Model> g_vehHashes_SUV;
std::vector<GTAmodel::Model> g_vehHashes_SEDAN;
std::vector<GTAmodel::Model> g_vehHashes_COMPACT;
std::vector<GTAmodel::Model> g_vehHashes_VAN;
std::vector<GTAmodel::Model> g_vehHashes_SERVICE;
std::vector<GTAmodel::Model> g_vehHashes_TRAIN;
std::vector<GTAmodel::Model> g_vehHashes_EMERGENCY;
std::vector<GTAmodel::Model> g_vehHashes_MOTORCYCLE;
std::vector<GTAmodel::Model> g_vehHashes_BICYCLE;
std::vector<GTAmodel::Model> g_vehHashes_PLANE;
std::vector<GTAmodel::Model> g_vehHashes_HELICOPTER;
std::vector<GTAmodel::Model> g_vehHashes_BOAT;
std::vector<GTAmodel::Model> g_vehHashes_UTILITY;
std::vector<GTAmodel::Model> g_vehHashes_INDUSTRIAL;
std::vector<GTAmodel::Model> g_vehHashes_COMMERCIAL;
std::vector<GTAmodel::Model> g_vehHashes_MILITARY;
std::vector<GTAmodel::Model> g_vehHashes_OTHER;
std::vector<GTAmodel::Model> g_vehHashes_DRIFT;

#pragma endregion

#pragma region Named neon colours
const std::vector<NamedRgbS> _vNeonColours
{
	{ "White", RgbS(255, 255, 255) },
	{ "Black", RgbS(0, 0, 0) },
	{ "Electric Blue", RgbS(3, 83, 255) },
	{ "Mint Green", RgbS(0, 255, 140) },
	{ "Lime Green", RgbS(94, 255, 1) },
	{ "Yellow", RgbS(255, 255, 0) },
	{ "Golden Shower", RgbS(255, 150, 5) },
	{ "Orange", RgbS(255, 62, 0) },
	{ "Red", RgbS(255, 1, 1) },
	{ "Pony Pink", RgbS(255, 50, 100) },
	{ "Hot Pink", RgbS(255, 5, 190) },
	{ "Purple", RgbS(35, 1, 255) },
	{ "Blacklight", RgbS(15, 3, 255) },
};

#pragma endregion

#pragma region Ped model labels and names
std::vector<std::pair<std::string, std::string>> g_pedModels;
std::vector<std::pair<std::string, std::string>> g_pedModels_Player;
std::vector<std::pair<std::string, std::string>> g_pedModels_Animal;
std::vector<std::pair<std::string, std::string>> g_pedModels_AmbientFemale;
std::vector<std::pair<std::string, std::string>> g_pedModels_AmbientMale;
std::vector<std::pair<std::string, std::string>> g_pedModels_Cutscene;
std::vector<std::pair<std::string, std::string>> g_pedModels_GangFemale;
std::vector<std::pair<std::string, std::string>> g_pedModels_GangMale;
std::vector<std::pair<std::string, std::string>> g_pedModels_Story;
std::vector<std::pair<std::string, std::string>> g_pedModels_Multiplayer;
std::vector<std::pair<std::string, std::string>> g_pedModels_ScenarioFemale;
std::vector<std::pair<std::string, std::string>> g_pedModels_ScenarioMale;
std::vector<std::pair<std::string, std::string>> g_pedModels_StoryScenarioFemale;
std::vector<std::pair<std::string, std::string>> g_pedModels_StoryScenarioMale;
std::vector<std::pair<std::string, std::string>> g_pedModels_Others;

#pragma endregion

std::vector<std::string> objectModels;

void PopulatePedModelsArray()
{
	pugi::xml_document doc;
	if (doc.load_file((const wchar_t*)(GetPathffW(Pathff::Main, true) + (L"PedList.xml")).c_str()).status == pugi::status_ok)
	{
		g_pedModels.clear();
		auto nodeRoot = doc.document_element();//doc.child("PedList");
		for (auto& cta : std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>*>>{
			{ "Player", &g_pedModels_Player },
			{ "Animal", &g_pedModels_Animal },
			{ "AmbientFemale", &g_pedModels_AmbientFemale },
			{ "AmbientMale", &g_pedModels_AmbientMale },
			{ "Cutscene", &g_pedModels_Cutscene },
			{ "GangFemale", &g_pedModels_GangFemale },
			{ "GangMale", &g_pedModels_GangMale },
			{ "Story", &g_pedModels_Story },
			{ "Multiplayer", &g_pedModels_Multiplayer },
			{ "ScenarioFemale", &g_pedModels_ScenarioFemale },
			{ "ScenarioMale", &g_pedModels_ScenarioMale },
			{ "StoryScenarioFemale", &g_pedModels_StoryScenarioFemale },
			{ "StoryScenarioMale", &g_pedModels_StoryScenarioMale },
			{ "Others", &g_pedModels_Others },
		})
		{
			auto nodeCat = nodeRoot.find_child_by_attribute("name", cta.first.c_str());
			if (nodeCat)
			{
				for (auto nodePed = nodeCat.first_child()/*nodeCat.child("Ped")*/; nodePed; nodePed = nodePed.next_sibling()/*nodeVeh.next_sibling("Ped")*/)
				{
					std::string pedModelName = nodePed.attribute("name").as_string();
					std::string pedDisplayName = nodePed.attribute("caption").as_string();
					cta.second->push_back({ pedModelName, pedDisplayName });
					g_pedModels.push_back({ pedModelName, pedDisplayName });
				}
			}
		}
	}

	std::vector<std::vector<std::pair<std::string, std::string>>*> vHashLists
	{
		{ &g_pedModels },
		{ &g_pedModels_Player },
		{ &g_pedModels_Animal },
		{ &g_pedModels_AmbientFemale },
		{ &g_pedModels_AmbientMale },
		{ &g_pedModels_Cutscene },
		{ &g_pedModels_GangFemale },
		{ &g_pedModels_GangMale },
		{ &g_pedModels_Story },
		{ &g_pedModels_Multiplayer },
		{ &g_pedModels_ScenarioFemale },
		{ &g_pedModels_ScenarioMale },
		{ &g_pedModels_StoryScenarioFemale },
		{ &g_pedModels_StoryScenarioMale },
		{ &g_pedModels_Others }
	};
	for (auto& hlist : vHashLists)
	{
		std::sort(hlist->begin(), hlist->end(), [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) -> bool { return boost::to_lower_copy(a.second) < boost::to_lower_copy(b.second); });
	}
}
void PopulateVehicleModelsArray()
{
	g_vehHashes.clear();
	g_vehHashes_OPENWHEEL.clear();
	g_vehHashes_SUPER.clear();
	g_vehHashes_SPORT.clear();
	g_vehHashes_SPORTSCLASSIC.clear();
	g_vehHashes_COUPE.clear();
	g_vehHashes_MUSCLE.clear();
	g_vehHashes_OFFROAD.clear();
	g_vehHashes_SUV.clear();
	g_vehHashes_SEDAN.clear();
	g_vehHashes_COMPACT.clear();
	g_vehHashes_VAN.clear();
	g_vehHashes_SERVICE.clear();
	g_vehHashes_TRAIN.clear();
	g_vehHashes_EMERGENCY.clear();
	g_vehHashes_MOTORCYCLE.clear();
	g_vehHashes_BICYCLE.clear();
	g_vehHashes_PLANE.clear();
	g_vehHashes_HELICOPTER.clear();
	g_vehHashes_BOAT.clear();
	g_vehHashes_INDUSTRIAL.clear();
	g_vehHashes_COMMERCIAL.clear();
	g_vehHashes_UTILITY.clear();
	g_vehHashes_MILITARY.clear();
	g_vehHashes_OTHER.clear();
	g_vehHashes_DRIFT.clear();

	GTAmemory::GenerateVehicleModelList();
	auto& hashes = GTAmemory::VehicleModels();
	std::unordered_map<VehicleClass, std::vector<Model>*> vDestMap
	{
		{ VehicleClass::Openwheel, &g_vehHashes_OPENWHEEL }, { VehicleClass::Super, &g_vehHashes_SUPER },{ VehicleClass::Sport, &g_vehHashes_SPORT },{ VehicleClass::SportsClassic, &g_vehHashes_SPORTSCLASSIC },
		{ VehicleClass::Coupe, &g_vehHashes_COUPE },{ VehicleClass::Muscle, &g_vehHashes_MUSCLE },{ VehicleClass::Offroad, &g_vehHashes_OFFROAD },{ VehicleClass::SUV, &g_vehHashes_SUV },
		{ VehicleClass::Sedan, &g_vehHashes_SEDAN },{ VehicleClass::Compact, &g_vehHashes_COMPACT },
		{ VehicleClass::Van, &g_vehHashes_VAN },{ VehicleClass::Service, &g_vehHashes_SERVICE },{ VehicleClass::Industrial, &g_vehHashes_INDUSTRIAL },
		{ VehicleClass::Military, &g_vehHashes_MILITARY },{ VehicleClass::Commercial, &g_vehHashes_COMMERCIAL },{ VehicleClass::Utility, &g_vehHashes_UTILITY },
		{ VehicleClass::Train, &g_vehHashes_TRAIN },{ VehicleClass::Emergency, &g_vehHashes_EMERGENCY },{ VehicleClass::Motorcycle, &g_vehHashes_MOTORCYCLE },
		{ VehicleClass::Cycle, &g_vehHashes_BICYCLE },{ VehicleClass::Plane, &g_vehHashes_PLANE },{ VehicleClass::Helicopter, &g_vehHashes_HELICOPTER },{ VehicleClass::Boat, &g_vehHashes_BOAT }
	};

	const bool isMinGameVersion3095 = GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_3095_0;
	for (int d = 0x0; d < 0x20; d++)
	{
		for (auto& dd : hashes[d])
		{
			if (std::find(g_vehHashes.begin(), g_vehHashes.end(), Model(dd)) == g_vehHashes.end())
			{
				if (!isMinGameVersion3095 || !IS_VEHICLE_GEN9_EXCLUSIVE_MODEL(dd))
				{
					std::string ModelName = boost::to_lower_copy(Model(dd).VehicleModelName());
					if (ModelName.starts_with("drift"))
					{
						g_vehHashes_DRIFT.push_back(dd);
					}
					else
					{
						auto dit = vDestMap.find(VehicleClass(d));
						if (dit != vDestMap.end())
							dit->second->push_back(dd);
						else g_vehHashes_OTHER.push_back(dd);
					}
					g_vehHashes.push_back(dd);
				}
			}
		}
	}

	std::vector<std::vector<Model>*> vHashLists
	{
		{ &g_vehHashes },
		{ &g_vehHashes_OPENWHEEL },
		{ &g_vehHashes_SUPER },
		{ &g_vehHashes_SPORT },
		{ &g_vehHashes_SPORTSCLASSIC },
		{ &g_vehHashes_COUPE },
		{ &g_vehHashes_MUSCLE },
		{ &g_vehHashes_OFFROAD },
		{ &g_vehHashes_SUV },
		{ &g_vehHashes_SEDAN },
		{ &g_vehHashes_COMPACT },
		{ &g_vehHashes_VAN },
		{ &g_vehHashes_SERVICE },
		{ &g_vehHashes_TRAIN },
		{ &g_vehHashes_EMERGENCY },
		{ &g_vehHashes_MOTORCYCLE },
		{ &g_vehHashes_BICYCLE },
		{ &g_vehHashes_PLANE },
		{ &g_vehHashes_HELICOPTER },
		{ &g_vehHashes_BOAT },
		{ &g_vehHashes_INDUSTRIAL },
		{ &g_vehHashes_COMMERCIAL },
		{ &g_vehHashes_UTILITY },
		{ &g_vehHashes_MILITARY },
		{ &g_vehHashes_OTHER },
		{ &g_vehHashes_DRIFT },
	};
	for (auto& hlist : vHashLists)
	{
		std::sort(hlist->begin(), hlist->end(), [](const Model& a, const Model& b) -> bool { return boost::to_lower_copy(a.VehicleDisplayName(true)) < boost::to_lower_copy(b.VehicleDisplayName(true)); });
	}
}
void PopulateObjectModelsArray()
{
	std::ifstream fin((GetPathffW(Pathff::Main, true) + (L"PropList.txt")).c_str());

	//objectModels.resize(std::count(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), '\n') + 1);
	objectModels.clear();

	UINT i = 0;
	for (std::string line; std::getline(fin, line);)
	{
		if (line.length() > 2)
		{
			//objectModels[i] = line;
			objectModels.push_back(line);
			i++;
		}
	}
	//objectModels.resize(i);

	std::sort(objectModels.begin(), objectModels.end());

	fin.close();
}
void PopulateGlobalEntityModelsArrays()
{
	PopulatePedModelsArray();
	PopulateVehicleModelsArray();
	PopulateObjectModelsArray();
}

// Model - labels
std::string get_ped_model_label(const GTAmodel::Model& model, bool properName)
{
	for (UINT i = 0; i < g_pedModels.size(); i++)
	{
		if (GET_HASH_KEY(g_pedModels[i].first) == model.hash)
		{
			return properName ? g_pedModels[i].second : g_pedModels[i].first;
		}
	}
	return std::string();
}
std::string get_vehicle_model_label(const GTAmodel::Model& model, bool properName)
{
	return model.VehicleDisplayName(properName);
}
std::string get_prop_model_label(const GTAmodel::Model& model)
{
	for (UINT i = 0; i < objectModels.size(); i++)
	{
		if (GET_HASH_KEY(objectModels[i]) == model.hash)
		{
			return objectModels[i];
		}
	}
	return std::string();
}




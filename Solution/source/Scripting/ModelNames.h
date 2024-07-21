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

#include "..\Natives\types.h" // RgbS

#include <vector>
#include <array>
#include <utility>
#include <string>

typedef unsigned __int32 UINT32;
namespace GTAmodel {
	class Model;
}

extern std::vector<GTAmodel::Model> g_vehHashes;
extern std::vector<GTAmodel::Model> g_vehHashes_OPENWHEEL;
extern std::vector<GTAmodel::Model> g_vehHashes_SUPER;
extern std::vector<GTAmodel::Model> g_vehHashes_SPORT;
extern std::vector<GTAmodel::Model> g_vehHashes_SPORTSCLASSIC;
extern std::vector<GTAmodel::Model> g_vehHashes_COUPE;
extern std::vector<GTAmodel::Model> g_vehHashes_MUSCLE;
extern std::vector<GTAmodel::Model> g_vehHashes_OFFROAD;
extern std::vector<GTAmodel::Model> g_vehHashes_SUV;
extern std::vector<GTAmodel::Model> g_vehHashes_SEDAN;
extern std::vector<GTAmodel::Model> g_vehHashes_COMPACT;
extern std::vector<GTAmodel::Model> g_vehHashes_VAN;
extern std::vector<GTAmodel::Model> g_vehHashes_SERVICE;
extern std::vector<GTAmodel::Model> g_vehHashes_TRAIN;
extern std::vector<GTAmodel::Model> g_vehHashes_EMERGENCY;
extern std::vector<GTAmodel::Model> g_vehHashes_MOTORCYCLE;
extern std::vector<GTAmodel::Model> g_vehHashes_BICYCLE;
extern std::vector<GTAmodel::Model> g_vehHashes_PLANE;
extern std::vector<GTAmodel::Model> g_vehHashes_HELICOPTER;
extern std::vector<GTAmodel::Model> g_vehHashes_BOAT;
extern std::vector<GTAmodel::Model> g_vehHashes_INDUSTRIAL;
extern std::vector<GTAmodel::Model> g_vehHashes_COMMERCIAL;
extern std::vector<GTAmodel::Model> g_vehHashes_UTILITY;
extern std::vector<GTAmodel::Model> g_vehHashes_MILITARY;
extern std::vector<GTAmodel::Model> g_vehHashes_OTHER;
extern std::vector<GTAmodel::Model> g_vehHashes_DRIFT;
void PopulateVehicleModelsArray();

struct NamedRgbS{ std::string name; RgbS rgb; };
extern const std::vector<NamedRgbS> _vNeonColours;

extern std::vector<std::pair<std::string, std::string>> g_pedModels;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Player;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Animal;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_AmbientFemale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_AmbientMale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Cutscene;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_GangFemale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_GangMale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Story;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Multiplayer;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_ScenarioFemale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_ScenarioMale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_StoryScenarioFemale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_StoryScenarioMale;
extern std::vector<std::pair<std::string, std::string>> g_pedModels_Others;
void PopulatePedModelsArray();

extern std::vector<std::string> objectModels;

void PopulateObjectModelsArray();
void PopulateGlobalEntityModelsArrays();

// Model - labels
std::string get_ped_model_label(const GTAmodel::Model& model, bool properName);
std::string get_vehicle_model_label(const GTAmodel::Model& model, bool properName);
std::string get_prop_model_label(const GTAmodel::Model& model);







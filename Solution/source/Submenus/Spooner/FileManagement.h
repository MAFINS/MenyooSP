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

#include <string>
#include <unordered_set>
#include <vector>

typedef int ScrHandle, Entity, Ped, Vehicle;
typedef unsigned long DWORD, Hash;

namespace pugi {
	class xml_node;
}

namespace sub::Spooner
{
	class SpoonerEntity;
	class SpoonerEntityWithInitHandle;
	class SpoonerMarker;
	class SpoonerMarkerWithInitHandle;

	namespace FileManagement
	{
		extern std::string _oldAudioAlias;

		//bool Exists(const std::string& fileName, std::string extension = ".xml");
		//bool Rename(const std::string& oldName, const std::string& newName, std::string extension = ".xml");
		//bool Delete(const std::string& fileName, std::string extension = ".xml");

		void AddEntityToXmlNode(SpoonerEntity& e, pugi::xml_node& nodeEntity);
		SpoonerEntityWithInitHandle SpawnEntityFromXmlNode(pugi::xml_node& nodeEntity, std::unordered_set<Hash>& vModelHashes);

		void AddMarkerToXmlNode(SpoonerMarker& m, pugi::xml_node& nodeMarker);
		SpoonerMarkerWithInitHandle SpawnMarkerFromXmlNode(pugi::xml_node& nodeMarker);

		bool SaveDbToFile(const std::string& filePath, bool bForceReferenceCoords);
		bool SaveWorldToFile(const std::string& filePath, std::vector<Entity>& vEntityHandles, std::vector<SpoonerMarker>& vMarkers);
		bool LoadPlacementsFromFile(const std::string& filePath);

		bool LoadPlacementsFromSP00NFile(const std::string& filePath);

		bool TeleportToReference(const std::string& filePath);
	}

}




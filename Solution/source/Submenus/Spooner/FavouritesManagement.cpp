/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FavouritesManagement.h"

#include "../../macros.h"

//#include "../../Menu/Menu.h"
//#include "../../Menu/Routine.h"

#include "../../Natives/natives2.h"
#include "../../Util/ExePath.h"
#include "../../Util/StringManip.h"
#include "../../Scripting/Model.h"

#include "../VehicleSpawner.h"

#include <string>
#include <pugixml.hpp>

namespace sub::Spooner
{
	namespace FavouritesManagement
	{
		std::string xmlFavouriteProps = "FavouriteProps.xml";
		bool IsPropAFavourite(const std::string& modelName, Hash modelHash)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.child("FavouriteProps");
			return nodeRoot.find_child_by_attribute("modelName", modelName.c_str()) || nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(modelHash == 0 ? GET_HASH_KEY(modelName) : modelHash, true).c_str());
		}
		bool AddPropToFavourites(const std::string& modelName, Hash modelHash)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str()).status != pugi::status_ok)
			{
				doc.reset();
				auto& nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto& nodeRoot = doc.append_child("FavouriteProps");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str());
			}
			pugi::xml_node nodeRoot = doc.child("FavouriteProps");

			auto& nodeOldLoc = nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(modelHash == 0 ? GET_HASH_KEY(modelName) : modelHash, true).c_str());
			if (!nodeOldLoc) // If null
			{
				nodeOldLoc = nodeRoot.find_child_by_attribute("modelName", modelName.c_str());
			}
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
			}
			auto& nodeNewLoc = nodeRoot.append_child("PropModel");
			nodeNewLoc.append_attribute("modelName") = modelName.c_str();
			nodeNewLoc.append_attribute("modelHash") = int_to_hexstring(modelHash == 0 ? GET_HASH_KEY(modelName) : modelHash, true).c_str();
			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str()));
		}
		bool RemovePropFromFavourites(const std::string& modelName, Hash modelHash)
		{
			std::string xmlFavouriteProps = "FavouriteProps.xml";
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str()).status != pugi::status_ok)
				return false;
			pugi::xml_node nodeRoot = doc.child("FavouriteProps");

			auto& nodeOldLoc = nodeRoot.find_child_by_attribute("modelHash", int_to_hexstring(modelHash == 0 ? GET_HASH_KEY(modelName) : modelHash, true).c_str());
			if (!nodeOldLoc) // If null
			{
				nodeOldLoc = nodeRoot.find_child_by_attribute("modelName", modelName.c_str());
			}
			if (nodeOldLoc) // If not null
			{
				nodeOldLoc.parent().remove_child(nodeOldLoc);
			}
			return (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlFavouriteProps).c_str()));
		}

		bool(*IsVehicleAFavourite)(GTAmodel::Model vehModel) = SpawnVehicle_IsVehicleModelAFavourite;
		bool(*AddVehicleToFavourites)(GTAmodel::Model vehModel, const std::string& customName) = SpawnVehicle_AddVehicleModelToFavourites;
		bool(*RemoveVehicleFromFavourites)(GTAmodel::Model vehModel) = SpawnVehicle_RemoveVehicleModelFromFavourites;
	}

}




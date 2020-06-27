/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Teleport_Submenus.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Memory\GTAmemory.h"
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\World.h"
#include "..\..\Util\ExePath.h"
#include "..\..\Util\keyboard.h"

#include "TeleLocation.h"
#include "Locations.h"
#include "TeleMethods.h"

#include <pugixml\src\pugixml.hpp>

Vector3 _customTeleLoc;
bool GrabbedCoords = 0;

namespace sub::TeleportLocations_catind
{
	const NamedTeleLocationList* _selectedCategory;

	Vector3 _customTeleLoc(Locations::vApartmentInteriors[0].x, Locations::vApartmentInteriors[0].y, Locations::vApartmentInteriors[0].z);

	namespace Submenus
	{
		void Sub_TeleportMain()
		{
			AddTitle("Locations");

			AddOption("Forward", null, TeleMethods::ToForward241);
			AddOption("Waypoint", null, TeleMethods::ToWaypoint241);
			AddOption("Mission Objective", null, TeleMethods::ToMissionBlip241);
			AddOption("Map Blips", null, nullFunc, SUB::TELEPORTOPS_BLIPLIST);

			AddBreak("---Ready To Go---");
			for (auto& cat : Locations::vAllCategories)
			{
				bool bCategoryPressed = false;
				AddOption(cat.categoryName, bCategoryPressed, nullFunc, -1, true); if (bCategoryPressed)
				{
					_selectedCategory = &cat;
					if (reinterpret_cast<DWORD64>(cat.nextNamedLocListList) < SUB::MAX_SUBS && cat.nextNamedLocListList != nullptr)
					{
						Menu::SetSub_delayed = reinterpret_cast<DWORD64>(cat.nextNamedLocListList);
					}
					else
					{
						Menu::SetSub_delayed = SUB::TELEPORTOPS_SELECTEDCATEGORY;
					}
				}
			}

			AddBreak("---Custom---");
			AddOption("Custom Coordinates", null, nullFunc, SUB::TELEPORTOPS_CUSTOMCOORDS);
			AddOption("Favourites", null, nullFunc, SUB::TELEPORTOPS_SAVEDLOCATIONS);
		}
		void Sub_CustomCoords()
		{
			GTAentity thisEntity = Static_241;

			if (!GrabbedCoords)
			{
				_customTeleLoc = GET_ENTITY_COORDS(PLAYER_PED_ID(), 0);
				GrabbedCoords = true;
			}

			bool x_plus = 0, x_minus = 0,
				y_plus = 0, y_minus = 0,
				z_plus = 0, z_minus = 0,
				x_custom = 0, y_custom = 0, z_custom = 0, apply = 0, update = 0;

			AddTitle("Custom Coordinates");
			AddOption("Update to current", update);
			AddNumber("  X", _customTeleLoc.x, 4, x_custom, x_plus, x_minus);
			AddNumber("  Y", _customTeleLoc.y, 4, y_custom, y_plus, y_minus);
			AddNumber("  Z", _customTeleLoc.z, 4, z_custom, z_plus, z_minus);
			AddOption("Apply", apply);


			if (x_plus) { _customTeleLoc.x += 0.1f; return; }
			if (y_plus) { _customTeleLoc.y += 0.1f; return; }
			if (z_plus) { _customTeleLoc.z += 0.1f; return; }
			if (x_minus) { _customTeleLoc.x -= 0.1f; return; }
			if (y_minus) { _customTeleLoc.y -= 0.1f; return; }
			if (z_minus) { _customTeleLoc.z -= 0.1f; return; }

			if (x_custom)
			{

				try
				{
					_customTeleLoc.x = stof(Game::InputBox(std::to_string(_customTeleLoc.x), 11U, std::string(), std::to_string(_customTeleLoc.x)));
				}
				catch (...) {}
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 10U, std::string(), std::to_string(_customTeleLoc.x));
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_customTeleLoc.x);
			}
			if (y_custom)
			{

				try
				{
					_customTeleLoc.y = stof(Game::InputBox(std::to_string(_customTeleLoc.y), 11U, std::string(), std::to_string(_customTeleLoc.y)));
				}
				catch (...) {}
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 10U, std::string(), std::to_string(_customTeleLoc.y));
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_customTeleLoc.y);
			}
			if (z_custom)
			{

				try
				{
					_customTeleLoc.z = stof(Game::InputBox(std::to_string(_customTeleLoc.z), 11U, std::string(), std::to_string(_customTeleLoc.z)));
				}
				catch (...) {}
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 10U, std::string(), std::to_string(_customTeleLoc.z));
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_customTeleLoc.z);
			}


			if (apply)
			{
				GrabbedCoords = false;
				teleport_net_ped(thisEntity, _customTeleLoc.x, _customTeleLoc.y, _customTeleLoc.z);
			}

			if (update)
			{
				GrabbedCoords = false;
			}
		}
		void Sub_SelectedCategory()
		{
			AddTitle(_selectedCategory->categoryName);

			if (_selectedCategory->locList_ptr != nullptr)
			{
				for (auto& loc : *_selectedCategory->locList_ptr)
				{
					bool bLocPressed = false;
					AddOption(loc.name, bLocPressed); if (bLocPressed)
					{
						TeleMethods::ToTeleLocation241(loc);
					}
				}
			}
			if (_selectedCategory->nextNamedLocListList != nullptr)
			{
				for (auto& locList : *_selectedCategory->nextNamedLocListList)
				{
					AddBreak(locList.categoryName);
					if (locList.locList_ptr != nullptr)
					{
						for (auto& loc : *locList.locList_ptr)
						{
							bool bLocPressed = false;
							AddOption(loc.name, bLocPressed); if (bLocPressed)
							{
								TeleMethods::ToTeleLocation241(loc);
							}
						}
					}
				}
			}

		}
		void Sub_BlipList()
		{
			AddTitle("Map Blips");

			//std::vector<GTAblip> vBlips;
			//World::GetActiveBlips(vBlips);

			BlipList* blipList = GTAmemory::GetBlipList();
			for (UINT16 i = 0; i <= 1000; i++)
			{
				Blipx* blip = blipList->m_Blips[i];
				if (blip)
				{
					if (blip->iIcon <= 521)
					{
						bool bPressedBlip = false;
						Vector3& blipPosition = Vector3(blip->x, blip->y, blip->z);
						auto& bnit = BlipIcon::vNames.find(blip->iIcon);
						const std::string& blipName = bnit == BlipIcon::vNames.end() ? "Unknown" : bnit->second;
						AddOption(blipName + " (" + World::GetZoneName(blipPosition, true) + ")", bPressedBlip); if (bPressedBlip)
						{
							TeleMethods::ToCoordinates241(blipPosition);
						}
					}
				}
			}
			/*for (auto& blip : vBlips)
			{
			bool bPressedBlip = false;
			AddOption(blip.IconName() + " (" + World::GetZoneName(blip.Position_get(), true) + ")", bPressedBlip); if (bPressedBlip)
			{
			TeleMethods::ToCoordinates241(blip.Position_get());
			}
			}*/

			//if (Menu::currentop > Menu::printingop && !vBlips.empty()) Menu::Up();
		}
		void Sub_SavedLocations()
		{
			AddTitle("Favourites");

			std::string xmlSavedMapLocations = "SavedMapLocations.xml";
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str()).status != pugi::status_ok)
			{
				//Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to load " + xmlSavedMapLocations);
				//Menu::SetSub_previous();
				doc.reset();
				auto& nodeDecleration = doc.append_child(pugi::node_declaration);
				nodeDecleration.append_attribute("version") = "1.0";
				nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
				auto& nodeRoot = doc.append_child("SavedMapLocations");
				doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str());
				return;
			}
			pugi::xml_node nodeRoot = doc.child("SavedMapLocations");

			bool bSaveCurrentLocation = false;
			AddOption("Save Current Location", bSaveCurrentLocation); if (bSaveCurrentLocation)
			{
				std::string inputStr = Game::InputBox("", 28U, "Enter name:");
				if (inputStr.length() > 0)
				{
					GTAentity ent = Static_241;
					Vector3& myPos = ent.Position_get();
					Vector3& myRot = ent.Rotation_get();
					auto& nodeOldLoc = nodeRoot.find_child_by_attribute("name", inputStr.c_str());
					if (nodeOldLoc) // If not null
					{
						nodeRoot.remove_child(nodeOldLoc);
					}
					auto& nodeNewLoc = nodeRoot.append_child("Loc");
					nodeNewLoc.append_attribute("name") = inputStr.c_str();
					nodeNewLoc.append_child("X").text() = myPos.x;
					nodeNewLoc.append_child("Y").text() = myPos.y;
					nodeNewLoc.append_child("Z").text() = myPos.z;
					nodeNewLoc.append_child("Yaw").text() = myRot.z;
					if (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str()))
					{
						Game::Print::PrintBottomLeft("Location ~b~saved~s~.");
					}
				}
				else Game::Print::PrintError_InvalidInput();
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SaveEntityLocation, std::string(), 28U, "Enter name:");
				//OnscreenKeyboard::State::arg1._int = Static_241;
			}

			//bool bLoadLocationInput = false;
			//AddOption("Remove Location (By Name)", bLoadLocationInput); if (bLoadLocationInput)
			//{
			//	std::string inputStr = Game::InputBox("", 28U, "Enter name:");
			//	if (inputStr.length() > 0)
			//	{
			//		auto& nodeLocToLoad = nodeRoot.find_child_by_attribute("name", inputStr.c_str());
			//		if (nodeLocToLoad) // If not null
			//		{
			//			nodeRoot.remove_child(nodeLocToLoad);
			//			if (doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str()))
			//			{
			//				Game::Print::PrintBottomLeft("Location ~b~removed~s~.");
			//			}
			//		}
			//	}
			//}

			if (nodeRoot.first_child())
			{
				AddBreak("---Locations---");
				for (auto& nodeLocToLoad = nodeRoot.first_child(); nodeLocToLoad; nodeLocToLoad = nodeLocToLoad.next_sibling())
				{
					bool bPressedLoc = false;
					Vector3 locPos;
					locPos.x = nodeLocToLoad.child("X").text().as_float();
					locPos.y = nodeLocToLoad.child("Y").text().as_float();
					locPos.z = nodeLocToLoad.child("Z").text().as_float();
					AddOption((std::string)nodeLocToLoad.attribute("name").as_string() + " - " + World::GetZoneName(locPos, true), bPressedLoc); if (bPressedLoc)
					{
						TeleMethods::ToCoordinates241(locPos);
					}

					if (Menu::printingop == *Menu::currentopATM)
					{
						if (Menu::bit_controller)
						{
							Menu::add_IB(INPUT_SCRIPT_RLEFT, "Remove");

							if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
							{
								nodeLocToLoad.parent().remove_child(nodeLocToLoad);
								doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str());
								if (*Menu::currentopATM >= Menu::totalop)
									Menu::Up();
								return; // Yeah
							}
						}
						else
						{
							Menu::add_IB(VirtualKey::B, "Remove");

							if (IsKeyJustUp(VirtualKey::B))
							{
								nodeLocToLoad.parent().remove_child(nodeLocToLoad);
								doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlSavedMapLocations).c_str());
								if (*Menu::currentopATM >= Menu::totalop)
									Menu::Up();
								return; // Yeah
							}
						}
					}

				}
			}
			//if (Menu::currentop > Menu::printingop) Menu::Up();
		}

	}

}




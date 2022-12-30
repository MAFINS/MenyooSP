/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Yachts.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Natives\types.h" // RGBA
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAprop.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Scripting\Scaleform.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Scripting\World.h"
#include "..\..\Memory\GTAmemory.h"
#include "..\..\Scripting\Model.h"
#include "..\..\Scripting\PTFX.h"
#include "..\..\Scripting\GameplayCamera.h"

#include "TeleLocation.h"
#include "TeleMethods.h"
#include "Locations.h"
#include "..\Settings.h"

#include <Windows.h> //GetTickCount
#include <string>
#include <vector>
#include <map>
//#include <utility>
#include <array>
#include <stdio.h>

namespace sub::TeleportLocations_catind
{
	namespace Yachts
	{
		const std::vector<TeleLocation> vOtherYachtRelatedTeleports
		{
			TeleLocation("Dignity Party (Vespucci Beach)", -2023.455f, -1038.181f, 8.0629f, IplNames::vYacht_Smboat1, IplNames::vYacht_Heist1, false),
			TeleLocation("Dignity Heist (Vespucci Beach)", -2023.455f, -1038.181f, 8.0629f, IplNames::vYacht_Heist1, IplNames::vYacht_Smboat1, true),
			TeleLocation("Gunrunning Heist (Paleto Bay)", -1368.7260f, 6736.3266f, 7.0000f, IplNames::vYacht_Heist2,{}, true)
		};
		struct CoordinatesWithHeading { Vector3 pos; float h; };
		struct YachtLocation { const PCHAR name; CoordinatesWithHeading poses[3]; };
		const std::map<UINT8, YachtLocation> vGroupLocations
		{
			{ 1,{ "Lago Zancudo",{ { { -3542.8215f, 1488.2498f, 5.4300f }, -123.0449f },{ { -3148.37912f, 2807.5549f, 5.4300f }, 91.95499f },{ { -3280.5012f, 2140.5071f, 5.4300f }, 86.9550f } } } },
			{ 2,{ "North Chumash",{ { { -2814.4895f, 4072.7398f, 5.4300f }, -108.04495f },{ { -3254.5520f, 3685.6765f, 5.4300f }, 81.9550f },{ { -2368.4412f, 4697.8740f, 5.4300f }, -133.0450f } } } },
			{ 3,{ "Pacific Bluffs",{ { { -3205.3440f, -219.0104f, 5.4300f }, 176.9550f },{ { -3448.2542f, 311.5018f, 5.4300f }, -83.04494f },{ { -2697.8616f, -540.6123f, 5.4300f }, 146.9550f } } } },
			{ 4,{ "Vespucci Beach",{ { { -1995.7343f, -1523.6902f, 5.4300f }, -38.0450f },{ { -2117.5806f, -2543.3460f, 5.4300f }, 36.9550f },{ { -1605.0737f, -1872.4680f, 5.4300f }, -68.0450f } } } },
			{ 5,{ "Los Santos International Airport",{ { { -753.0817f, -3919.0676f, 5.4300f }, 11.9550f },{ { -351.0608f, -3553.3235f, 5.4300f }, -123.0450f },{ { -1460.5361f, -3761.4670f, 5.4300f }, 161.9550f } } } },
			{ 6,{ "Terminal",{ { { 1546.8916f, -3045.6270f, 5.4300f }, -118.0445f },{ { 2490.8855f, -2428.8481f, 5.4300f }, -168.0450f },{ { 2049.7898f, -2821.6240f, 5.4300f }, 31.9550f } } } },
			{ 7,{ "Palomino Highlands",{ { { 3029.0183f, -1495.7024f, 5.4300f }, -108.0450f },{ { 3021.2537f, -723.3903f, 5.4300f }, 81.9550f },{ { 2976.6218f, -1994.7598f, 5.4300f }, -133.0450f } } } },
			{ 8,{ "Tataviam Mountains",{ { { 3404.5095f, 1977.0444f, 5.4300f }, -103.0450f },{ { 3411.1003f, 1193.4446f, 5.4300f }, 31.95502f },{ { 3784.8025f, 2548.5413f, 5.4300f }, 86.9551f } } } },
			{ 9,{ "San Chianski Mountain Range",{ { { 4225.0283f, 3988.0015f, 5.4300f }, 61.9551f },{ { 4250.5811f, 4576.5654f, 5.4300f }, 111.9550f },{ { 4204.3555f, 3373.7002f, 5.4300f }, 81.9550f } } } },
			{ 10,{ "Mount Gordo",{ { { 3751.6814f, 5753.5010f, 5.4300f }, 136.9550f },{ { 3490.1052f, 6305.7852f, 5.4300f }, 156.9550f },{ { 3684.8533f, 5212.2383f, 5.4300f }, -58.0450f } } } },
			{ 11,{ "Procopio Beach",{ { { 581.5955f, 7124.5576f, 5.4300f }, 121.9550f },{ { 2004.4617f, 6907.1572f, 5.4300f }, 6.9550f },{ { 1396.6379f, 6860.2031f, 5.4300f }, 176.9550f } } } },
			{ 12,{ "Paleto Bay",{ { { -1170.6904f, 5980.6816f, 5.4300f }, 91.9550f },{ { -777.4865f, 6566.9072f, 5.4300f }, 26.9549f },{ { -381.7739f, 6946.9600f, 5.4300f }, 71.9550f } } } }
		};
		namespace YachtOffsets
		{
			bool bPlayerJustTeleportedBetweenMarkers = false;
			std::vector<std::pair<Vector3, Vector3>> markerOffsets
			{
				{ { -37.5245f, -2.0054f, 0.2776f },{ -13.6966f, -1.9615f, 0.2808f } },
				{ { -13.6966f, -1.9615f, 0.2808f },{ -37.5245f, -2.0054f, 0.2776f } },
				{ { -0.5604f, -2.0216f, 6.3030f },{ 5.0348f, -1.9846f, 6.3074f } },
				{ { 5.0348f, -1.9846f, 6.3074f },{ -0.5604f, -2.0216f, 6.3030f } },
			};
			Vector3 teleportLocationOffset = { -57.6840f, -3.7550f, -3.2132f };
		}
		struct YachtBmp { const PCHAR title; const PCHAR imgName; };
		const std::map<UINT8, YachtBmp> vOptionNames
		{
			{ 1,{ "The Orion", "yacht_model_0_0" } },
			{ 2,{ "The Pisces", "yacht_model_1_0" } },
			{ 3,{ "The Aquarius", "yacht_model_2_0" } }
		};
		const std::vector<std::string> vFlagSuffixes
		{
			{ "Argentina" },
			{ "Australia" },
			{ "Austria" },
			{ "Belgium" },
			{ "Brazil" },
			{ "Canadat_yt" },
			{ "China" },
			{ "Columbia" },
			{ "Croatia" },
			{ "CzechRep" },
			{ "Denmark" },
			{ "England" },
			{ "EU_yt" },
			{ "Finland" },
			{ "France" },
			{ "German_yt" },
			{ "Hungary" },
			{ "Ireland" },
			{ "Israel" },
			{ "Italy" },
			{ "Jamaica" },
			{ "Japan_yt" },
			{ "Lstein" },
			{ "Malta" },
			{ "Mexico_yt" },
			{ "Netherlands" },
			{ "NewZealand" },
			{ "Nigeria" },
			{ "Norway" },
			{ "Palestine" },
			{ "Poland" },
			{ "Portugal" },
			{ "PuertoRico" },
			{ "Russia_yt" },
			{ "Scotland_yt" },
			{ "Script" },
			{ "Slovakia" },
			{ "Slovenia" },
			{ "SouthAfrica" },
			{ "Southkorea" },
			{ "Spain" },
			{ "Sweden" },
			{ "Switzerland" },
			{ "Turkey" },
			{ "UK_yt" },
			{ "US_yt" },
			{ "Wales" },
		};

		struct YachtBuildInfoStructure
		{
			std::pair<const UINT8, YachtLocation> const * location;
			UINT8 internalLocationIndex;
			std::pair<const UINT8, YachtBmp> const * option;
			GTAprop yachtProp;
			UINT8 yachtPropTextureVariation;
			char railingColour;
			UINT8 lightingType;
			char lightingColour;
			char doorColour;
			UINT8 flagIndex;
			GTAblip blip;
			RGBA markerColour;
			std::vector<GTAentity> vSpawnedEntities;
			std::vector<std::pair<Vector3, Vector3>> vMarkerPositions;
			std::array<std::pair<Scaleform, std::string>, 3> vScaleforms;

			void operator = (const YachtBuildInfoStructure& right)
			{
				this->location = right.location;
				this->internalLocationIndex = right.internalLocationIndex;
				this->option = right.option;
				this->yachtProp = right.yachtProp;
				this->yachtPropTextureVariation = right.yachtPropTextureVariation;
				this->railingColour = right.railingColour;
				this->lightingType = right.lightingType;
				this->lightingColour = right.lightingColour;
				this->doorColour = right.doorColour;
				this->blip = right.blip;
				this->markerColour = right.markerColour;
				this->vSpawnedEntities = right.vSpawnedEntities;
				this->vMarkerPositions = right.vMarkerPositions;
				this->vScaleforms = right.vScaleforms;
			}
		};
		YachtBuildInfoStructure currentYachtInfo = { nullptr, 1, nullptr, 0, 0, 'a', 1, 'a', '\0', 0, 0,{ 0, 220, 220, 130 } };
		YachtBuildInfoStructure oldYachtInfoVal;
		YachtBuildInfoStructure* oldYachtInfo = nullptr;

		void DrawYachtBmpPreview(UINT8 yachtId)
		{
			Vector2 res = { 0.1f, 0.0889f };

			FLOAT x_coord = 0.324f + menuPos.x;
			FLOAT y_coord = OptionY + 0.044f + menuPos.y;

			if (menuPos.x > 0.45f) x_coord = menuPos.x - 0.003f;

			DRAW_RECT(x_coord, y_coord, res.x + 0.003f, res.y + 0.003f, 0, 0, 0, 212, false);

			auto onit = vOptionNames.find(yachtId);
			if (onit != vOptionNames.end())
			{
				auto& vimg = onit->second;
				std::string imgDict = "dock_dlc_model";
				if (!HAS_STREAMED_TEXTURE_DICT_LOADED(const_cast<PCHAR>(imgDict.c_str())))
					REQUEST_STREAMED_TEXTURE_DICT(const_cast<PCHAR>(imgDict.c_str()), false);
				else
					DRAW_SPRITE(const_cast<PCHAR>(imgDict.c_str()), const_cast<PCHAR>(vimg.imgName), x_coord, y_coord, res.x, res.y, 0, 255, 255, 255, 255, false, 0);
			}
			else
			{
				Game::Print::setupdraw(0, Vector2(0, 0.185f), true, false, false);
				Game::Print::drawstring("No preview available", x_coord, y_coord - 0.0043f);
			}
		}

		Vector3 GetYachtVectorWorldPosition(YachtBuildInfoStructure& yachtInfo, const Vector3& vec)
		{
			if (yachtInfo.location != nullptr)
			{
				auto& posh = yachtInfo.location->second.poses[yachtInfo.internalLocationIndex - 1];
				float vectorLength = vec.Length();
				float yaw = posh.h;
				Vector3& result = Vector3::DirectionToRotation(vec);
				result.z = yaw - 90.0f;
				result = Vector3::RotationToDirection(result);
				result.Normalize();
				return (posh.pos + (result * vectorLength));
			}
			return Vector3();
		}
		void CreateYacht(YachtBuildInfoStructure& yachtInfo)
		{
			if (_worldObjects.size() > 2000)//GTA_MAX_ENTITIES - 48)
			{
				Game::Print::PrintBottomCentre("~r~Error:~s~ Too many entities in world.");
				return;
			}
			if (yachtInfo.location != nullptr && yachtInfo.option != nullptr)
			{
				auto& posh = yachtInfo.location->second.poses[yachtInfo.internalLocationIndex - 1];

				char buffer[64];// = new char[64];

				//Game::Print::PrintBottomLeft("Building Yacht.");

				SET_INSTANCE_PRIORITY_MODE(true);
				ON_ENTER_MP();

				sprintf_s(buffer, "%02d", yachtInfo.location->first);
				std::string groupIdStr = buffer;

				sprintf_s(buffer, "apa_yacht_grp%s_%i", groupIdStr.c_str(), yachtInfo.internalLocationIndex);
				std::string iplInitials = buffer;

				REQUEST_IPL(const_cast<PCHAR>((iplInitials).c_str()));
				REQUEST_IPL(const_cast<PCHAR>((iplInitials + "_int").c_str()));
				REQUEST_IPL(const_cast<PCHAR>((iplInitials + "_lod").c_str()));
				SET_INSTANCE_PRIORITY_MODE(false);

				WAIT(200);

				for (DWORD timeOut = GetTickCount() + 6500; GetTickCount() < timeOut;)
				{
					if (World::GetClosestPropOfType(posh.pos, 3.0f, 0x4FCAD2E0).Exists()) break; // apa_mp_apa_yacht
				}

				UINT8 optionNumber = yachtInfo.option->first;
				//char optionNumberChar = '0' + optionNumber;

				std::vector<Entity> propYachtArr;
				GTAmemory::GetPropHandles(propYachtArr, posh.pos, 3.0f, { 0x4FCAD2E0 }); // apa_mp_apa_yacht
				yachtInfo.yachtProp = World::GetClosestPropOfType(posh.pos, 3.0f, 0x4FCAD2E0); // apa_mp_apa_yacht
				auto& propYacht = yachtInfo.yachtProp;
				if (!propYacht.Exists() && !propYachtArr.empty()) { if (DOES_ENTITY_EXIST(propYachtArr.front())) propYacht = propYachtArr.front(); }
				if (!propYacht.Exists())
				{
					yachtInfo.vMarkerPositions.clear();
					Game::Print::PrintBottomLeft("~r~Error:~s~ Unable to build yacht. Try again.");
					return;
				}
				Vector3& propYachtPos = propYacht.Position_get();

				SET_OBJECT_TINT_INDEX(propYacht.Handle(), yachtInfo.yachtPropTextureVariation);

				auto& propYachtWin = propYacht;//World::GetClosestPropOfType(yachtInfo.location->second.pos, 4.0f, 0xBCDAC9E7); // apa_mp_apa_yacht_win
											   //if (!propYachtWin.Exists()) propYachtWin = propYacht;


				sprintf_s(buffer, "apa_mp_apa_yacht_o%u_rail_%c", optionNumber, yachtInfo.railingColour);
				auto& propRailings = World::CreateProp(std::string(buffer), Vector3(), false, false);
				propRailings.IsCollisionEnabled_set(true);
				propRailings.AttachTo(propYachtWin, 0, false, Vector3(0.0032f, 0.0028f, 14.5700f), Vector3());
				SET_ENTITY_LIGHTS(propRailings.Handle(), 0);
				propRailings.MissionEntity_set(true);
				yachtInfo.vSpawnedEntities.push_back(propRailings);

				std::vector<std::string> optionColModels;
				switch (optionNumber)
				{
				case 1:
					optionColModels = { "apa_mp_apa_yacht_option1", "apa_mp_apa_yacht_option1_cola" };
					break;
				case 2:
					optionColModels = { "apa_mp_apa_yacht_option2", "apa_mp_apa_yacht_option2_cola", "apa_mp_apa_yacht_option2_colb" };
					break;
				case 3:
					optionColModels = { "apa_mp_apa_yacht_option3", "apa_mp_apa_yacht_option3_cola", "apa_mp_apa_yacht_option3_colb", "apa_mp_apa_yacht_option3_colc", "apa_mp_apa_yacht_option3_cold", "apa_mp_apa_yacht_option3_cole" };
					break;
				}
				for (Model ms : optionColModels)
				{
					auto& p = World::CreateProp(ms, Vector3(), false, false);
					p.AttachTo(propYachtWin, 0, false, Vector3(0.0032f, 0.0028f, 14.5700f), Vector3());
					p.IsCollisionEnabled_set(true);
					SET_OBJECT_TINT_INDEX(p.Handle(), yachtInfo.yachtPropTextureVariation);
					SET_ENTITY_LIGHTS(p.Handle(), 0);
					propRailings.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(p);
				}

				sprintf_s(buffer, "apa_mp_apa_y%u_l%u%c", optionNumber, yachtInfo.lightingType, yachtInfo.lightingColour);
				auto& propLights = World::CreateProp(std::string(buffer), propYachtPos, false, false);
				propLights.AttachTo(propYachtWin, 0, false, Vector3(0.0032f, 0.0028f, 14.5700f), Vector3());
				propLights.IsCollisionEnabled_set(true);
				SET_ENTITY_LIGHTS(propLights.Handle(), 0);
				propLights.MissionEntity_set(true);
				yachtInfo.vSpawnedEntities.push_back(propLights);

				sprintf_s(buffer, "apa_mp_apa_yacht_door%c", yachtInfo.doorColour);
				for (auto& doorOffset : std::vector<std::pair<Vector3, Vector3>>
				{
					{ { 0.01894f, -3.3871f, 6.6600f },{ 0.0000f, 0.0000f, 90.2950f } },
					{ { 0.0046f, -0.6018f, 6.6600f },{ 0.0000f, 0.0000f, -89.7050f } },
					{ { -36.8202f, -1.2778f, 0.6500f },{ 0.0000f, 0.0000f, -89.9550f } }
				})
				{
					auto& propDoor = World::CreateProp(std::string(buffer), Vector3(), true, false);
					propDoor.AttachTo(propYachtWin, 0, false, doorOffset.first, doorOffset.second);
					propDoor.IsCollisionEnabled_set(true);
					SET_OBJECT_TINT_INDEX(propDoor.Handle(), yachtInfo.yachtPropTextureVariation);
					SET_ENTITY_LIGHTS(propDoor.Handle(), 0);
					propDoor.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(propDoor);
				}

				// Flag
				auto& propFlag = World::CreateProp("apa_prop_flag_" + vFlagSuffixes[yachtInfo.flagIndex], Vector3(), true, false);
				propFlag.AttachTo(propYachtWin, 0, false, Vector3(-56.6221f, -2.0013f, 1.5937f), Vector3(49.6800f, 0.0000f, -89.9500f));
				propFlag.IsCollisionEnabled_set(true);
				SET_ENTITY_LIGHTS(propFlag.Handle(), 0);
				propFlag.MissionEntity_set(true);
				yachtInfo.vSpawnedEntities.push_back(propFlag);

				// Keypad
				auto& propKeypad = World::CreateProp(0x25286EB9, Vector3(), true, false); // prop_ld_keypad_01b
				propKeypad.AttachTo(propYachtWin, 0, false, Vector3(-36.8196f, -2.8881f, 0.8880f), Vector3(0.0000f, 0.0000f, -84.7550f));
				propKeypad.IsCollisionEnabled_set(true);
				SET_ENTITY_LIGHTS(propKeypad.Handle(), 0);
				propKeypad.MissionEntity_set(true);
				yachtInfo.vSpawnedEntities.push_back(propKeypad);

				std::map<UINT8, std::vector<std::pair<Vector3, float>>> radomeOffsets
				{
					{ 1,{ { { 0.95549f, -2.1682f, 9.6040f }, 90.0000f },{ { 1.2820f, -1.9895f, 13.4305f }, -180.0000f },{ { 5.4844f, -1.9817f, 18.1568f }, -90.0000f } } },
					{ 2,{ { { -2.2487f, -1.9926f, 17.3200f }, -90.0000f },{ { 1.6188f, -1.9927f, 14.0505f }, -180.0000f },{ { 7.6349f, -1.9927f, 10.3491f }, 90.0000f } } },
					{ 3,{ { { 10.8361f, -1.9899f, 9.8530f }, 90.0000f },{ { -0.2231f, -1.9601f, 12.8964f }, 180.0000f },{ { -15.0487f, -1.9918f, 9.0674f }, 90.0000f } } }
				};
				auto& radomeOffset = radomeOffsets[optionNumber];
				for (auto& r : radomeOffset)
				{
					auto& propRadome = World::CreateProp(0x49566db0, Vector3(), true, false); // apa_mp_apa_yacht_radar_01a
					propRadome.AttachTo(propYachtWin, 0, false, r.first, Vector3(0, 0, r.second));
					propRadome.Detach();
					propRadome.FreezePosition(true);
					propRadome.IsCollisionEnabled_set(true);
					SET_OBJECT_TINT_INDEX(propRadome.Handle(), yachtInfo.yachtPropTextureVariation);
					SET_ENTITY_LIGHTS(propRadome.Handle(), 0);
					propRadome.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(propRadome);
				}

				// Buoys
				for (auto& b : std::vector<Vector3>
				{
					{ -53.4131f, -10.0086f, -6.0113f },
					{ -1631.3173f, -1819.5632f, -0.6474f },
					{ -58.8841f, 0.2735f, -6.1121f },
					{ -1619.7332f, -1820.7730f, -0.8027f }
				})
				{
					auto& propBuoy = World::CreateProp(0x51d2a887, Vector3(), true, false); // apa_prop_yacht_float_1a
					propBuoy.AttachTo(propYachtWin, 0, false, b, Vector3());
					propBuoy.Detach();
					propBuoy.FreezePosition(false);
					propBuoy.Dynamic_set(true);
					propBuoy.IsCollisionEnabled_set(true);
					SET_ENTITY_LIGHTS(propBuoy.Handle(), 0);
					propBuoy.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(propBuoy);
				}

				// Jacuzzi
				if (optionNumber >= 2)
				{
					auto& propJacuzzi = World::CreateProp(0x98B5E3D4, Vector3(), true, false); // apa_mp_apa_yacht_jacuzzi_ripple1
					propJacuzzi.AttachTo(propYachtWin, 0, false, Vector3(-50.8033f, -1.9774f, 0.1368f), Vector3());
					propJacuzzi.IsCollisionEnabled_set(true);
					SET_ENTITY_LIGHTS(propJacuzzi.Handle(), 0);
					propJacuzzi.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(propJacuzzi);
				}

				// Vehicles
				std::map<UINT8, std::vector<std::tuple<Model, Vector3, Vector3>>> vVehicleOffsetsArr
				{
					{ 1,{
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_TROPIC2,{ -54.3528f, -13.3907f, -5.1819f },{ 1.6733f, 1.9946f, -109.0565f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5043f, -8.9306f, -5.5869f },{ 4.1636f, -0.8436f, 116.3082f })
					} },
					{ 2,{
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5275f, 4.6035f, -5.3742f },{ 4.6320f, -1.7134f, 63.7883f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5155f, -8.896f, -5.3594f },{ 4.5635f, -1.1910f, -243.6808f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_DINGHY4,{ -54.3522f, -13.3903f, -4.8438f },{ 4.8526f, -1.0505f, -109.0528f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SPEEDER2,{ -53.7848f, 9.1620f, -4.6511f },{ 3.3195f, 0.8531f, -69.9578f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SWIFT2,{ -30.8168f, -1.8687f, 6.5134f },{ -0.2890f, 0.0000f, -90.0000f })
					} },
					{ 3,{
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5189f, 2.3503f, -5.8703f },{ 5.6612f, 0.2225f, 64.4417f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5050f, -8.9017f, -5.6858f },{ 7.4903f, -0.0753f, 116.2442f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.52280f, 4.5982f, -5.8566f },{ 5.9844f, -0.3815f, 64.5492f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SEASHARK3,{ -61.5087f, -6.6536f, -5.7382f },{ 7.2774f, 0.9445f, 114.6004f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_DINGHY4,{ -54.3447f, -13.3947f, -5.4129f },{ 3.6041f, -2.1484f, -108.2869f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_TORO,{ -54.3726f, 9.1093f, -5.5979f },{ -1.8536f, 0.7891f, -69.8533f }),
						std::make_tuple<Model, Vector3, Vector3>(VEHICLE_SUPERVOLITO2,{ -30.8329f, -1.8728f, 7.2883f },{ 0.0409f, 0.0000f, -90.0000f })
					} }
				};
				auto& vVehicleOffsets = vVehicleOffsetsArr[optionNumber];
				for (auto& v : vVehicleOffsets)
				{
					auto& veh = World::CreateVehicle(std::get<0>(v), Vector3(), 0.0f, false);
					veh.AttachTo(propYachtWin, 0, false, std::get<1>(v), std::get<2>(v));
					veh.Detach();
					veh.FreezePosition(false);
					veh.IsCollisionEnabled_set(true);
					SET_ENTITY_LIGHTS(veh.Handle(), 0);
					if (std::get<0>(v).IsBoat()) SET_BOAT_ANCHOR(veh.Handle(), true);
					//veh.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(veh);
				}

				// Peds
				for (auto& p : std::vector<std::tuple<Model, Vector3, Vector3, PTFX::sFxData>>
				{
					std::make_tuple<Model, Vector3, Vector3, PTFX::sFxData>(PedHash::BoatStaff01Male,{ 14.2079f, -2.1206f, 7.3519f },{ 0.0000f, 0.0000f, -88.2933f },{ std::string(), std::string() }),
					std::make_tuple<Model, Vector3, Vector3, PTFX::sFxData>(PedHash::BoatStaff01Female,{ 23.3344f, -1.6929f, 3.5506f },{ 0.0000f, 0.0000f, 88.9650f },{ "anim@mini@yacht@bar@drink@idle_a", "idle_a_bartender" }),
				})
				{
					auto& ped = World::CreatePed(std::get<0>(p), Vector3(), 0.0f, false);
					ped.AttachTo(propYachtWin, 0, false, std::get<1>(p), std::get<2>(p));
					ped.Detach();
					ped.FreezePosition(false);
					ped.IsCollisionEnabled_set(true);
					SET_ENTITY_LIGHTS(ped.Handle(), 0);
					ped.RelationshipGroup_set("PLAYER");
					ped.BlockPermanentEvents_set(true);
					auto& animArgs = std::get<3>(p);
					if (animArgs.asset.empty()) { if (!animArgs.effect.empty()) { ped.Task().StartScenario(animArgs.effect); } }
					else if (!animArgs.effect.empty()) { ped.Task().PlayAnimation(animArgs.asset, animArgs.effect); }
					//ped.MissionEntity_set(true);
					yachtInfo.vSpawnedEntities.push_back(ped);
				}

				// Blip
				auto& blipYacht = yachtInfo.blip;
				blipYacht = propYachtWin.AddBlip();
				blipYacht.SetIcon(BlipIcon::Yacht);
				blipYacht.SetBlipName("Menyoo Yacht");
				blipYacht.SetColour(BlipColour::Blue);
				blipYacht.SetAlpha(200);
				blipYacht.SetFriendly(true);
				blipYacht.SetScale(0.8f);

				for (auto& v : YachtOffsets::markerOffsets)//YachtVectors::markerVectors)
				{
					//currentYachtInfo.vMarkerPositions.push_back({ GetYachtVectorWorldPosition(currentYachtInfo, v.first), GetYachtVectorWorldPosition(currentYachtInfo, v.second) });
					currentYachtInfo.vMarkerPositions.push_back({ propYachtWin.GetOffsetInWorldCoords(v.first), propYachtWin.GetOffsetInWorldCoords(v.second) });
				}

				//delete[] buffer;
			}
		}
		void DeleteYacht(YachtBuildInfoStructure& yachtInfo)
		{
			for (auto& entity : yachtInfo.vSpawnedEntities)
			{
				if (entity.Handle() != g_myVeh)
				{
					entity.RequestControl();
					entity.Delete(true);
				}
			}
			yachtInfo.vSpawnedEntities.clear();
			yachtInfo.yachtProp = 0;
			yachtInfo.blip.Remove();
		}
		void TeleportPedToYacht(const GTAentity ped, YachtBuildInfoStructure& yachtInfo)
		{
			if (yachtInfo.location != nullptr)
			{
				auto& posh = yachtInfo.location->second.poses[yachtInfo.internalLocationIndex - 1];
				Vector3 yachtPos = posh.pos;
				Vector3 teleOffset = YachtOffsets::teleportLocationOffset;
				if (yachtInfo.yachtProp.Exists())
					teleport_net_ped(ped, yachtInfo.yachtProp.GetOffsetInWorldCoords(teleOffset));
				else
					teleport_net_ped(ped, yachtPos + Vector3::RotationToDirection(Vector3::DirectionToRotation(teleOffset) + Vector3(0, 0, posh.h)) * teleOffset.Length());
			}
		}

		void Sub_Yachts()
		{
			AddTitle("Yachts");

			for (auto& otherTele : vOtherYachtRelatedTeleports)
			{
				bool bOtherTelePressed = false;
				AddOption(otherTele.name, bOtherTelePressed); if (bOtherTelePressed)
				{
					TeleMethods::ToTeleLocation241(otherTele);
				}
			}

			AddBreak("---Build A Yacht---");

			if (oldYachtInfo != nullptr)
			{
				if (oldYachtInfo->location != nullptr && oldYachtInfo->option != nullptr)
				{
					currentYachtInfo.location = oldYachtInfo->location;
					currentYachtInfo.internalLocationIndex = oldYachtInfo->internalLocationIndex;
					currentYachtInfo.option = oldYachtInfo->option;
					currentYachtInfo.vScaleforms = oldYachtInfo->vScaleforms;
				}
				//delete oldYachtInfo;
				oldYachtInfo = nullptr;
			}
			for (auto& grp : vGroupLocations)
			{
				bool bGrpLocPressed = false;
				AddOption(grp.second.name, bGrpLocPressed, nullFunc, SUB::TELEPORTOPS_YACHTS_INGRP); if (bGrpLocPressed)
				{
					if (oldYachtInfo == nullptr)
					{
						oldYachtInfo = &oldYachtInfoVal;
						*oldYachtInfo = currentYachtInfo;
					}
					currentYachtInfo.location = &grp;
					currentYachtInfo.option = &*vOptionNames.begin();
				}
			}


		}
		void Sub_Yachts_InGrp()
		{
			if (currentYachtInfo.location == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			GTAped ped = Static_241;

			AddTitle(currentYachtInfo.location->second.name);

			bool bInternalLoc_plus = false, bInternalLoc_minus = false;
			AddTexter("Position Index", currentYachtInfo.internalLocationIndex, std::vector<std::string>{}, null, bInternalLoc_plus, bInternalLoc_minus);
			if (bInternalLoc_plus) { if (currentYachtInfo.internalLocationIndex < 3) { currentYachtInfo.internalLocationIndex++; } }
			if (bInternalLoc_minus) { if (currentYachtInfo.internalLocationIndex > 1) { currentYachtInfo.internalLocationIndex--; } }

			bool bYachtType_plus = false, bYachtType_minus = false;
			AddTexter("Yacht", 0, std::vector<std::string>{ currentYachtInfo.option->second.title }, null, bYachtType_plus, bYachtType_minus);
			if (*Menu::currentopATM == Menu::printingop) DrawYachtBmpPreview(currentYachtInfo.option->first);
			if (bYachtType_plus) { if (vOptionNames.rbegin()->first != currentYachtInfo.option->first) { currentYachtInfo.option = &*(++vOptionNames.find(currentYachtInfo.option->first)); } }
			if (bYachtType_minus) { if (vOptionNames.begin()->first != currentYachtInfo.option->first) { currentYachtInfo.option = &*(--vOptionNames.find(currentYachtInfo.option->first)); } }

			bool bYachtPaint_plus = false, bYachtPaint_minus = false;
			AddTexter("Yacht Paint", currentYachtInfo.yachtPropTextureVariation, YachtPropPaintVariation::vNames, null, bYachtPaint_plus, bYachtPaint_minus);
			if (bYachtPaint_plus) { if (currentYachtInfo.yachtPropTextureVariation < YachtPropPaintVariation::vNames.size() - 1) { currentYachtInfo.yachtPropTextureVariation++; } }
			if (bYachtPaint_minus) { if (currentYachtInfo.yachtPropTextureVariation > 0) { currentYachtInfo.yachtPropTextureVariation--; } }

			bool bRailings_plus = false, bRailings_minus = false;
			AddTexter("Railings", currentYachtInfo.railingColour - 'a', std::vector<std::string>{"Chrome", "Gold"}, null, bRailings_plus, bRailings_minus);
			if (bRailings_plus) { if (currentYachtInfo.railingColour < 'b') { currentYachtInfo.railingColour++; } }
			if (bRailings_minus) { if (currentYachtInfo.railingColour > 'a') { currentYachtInfo.railingColour--; } }

			bool bLightingType_plus = false, bLightingType_minus = false;
			AddTexter("Lighting", currentYachtInfo.lightingType - 1, std::vector<std::string>{"Presidential", "Vivacious"}, null, bLightingType_plus, bLightingType_minus);
			if (bLightingType_plus) { if (currentYachtInfo.lightingType < 2) { currentYachtInfo.lightingType++; } }
			if (bLightingType_minus) { if (currentYachtInfo.lightingType > 1) { currentYachtInfo.lightingType--; } }

			bool bLightingColour_plus = false, bLightingColour_minus = false;
			AddTexter("Lighting Colour", currentYachtInfo.lightingColour - 'a', std::vector<std::string>{"Gold", "Blue", "Pink", "Green"}, null, bLightingColour_plus, bLightingColour_minus);
			if (bLightingColour_plus) { if (currentYachtInfo.lightingColour < 'd') { currentYachtInfo.lightingColour++; } }
			if (bLightingColour_minus) { if (currentYachtInfo.lightingColour > 'a') { currentYachtInfo.lightingColour--; } }

			bool bDoorColour_plus = false, bDoorColour_minus = false;
			AddTexter("Doors", 0, std::vector<std::string>{ currentYachtInfo.doorColour == '\0' ? "Chrome" : "Gold"}, null, bDoorColour_plus, bDoorColour_minus);
			if (bDoorColour_plus) { if (currentYachtInfo.doorColour == '\0') { currentYachtInfo.doorColour = '2'; } }
			if (bDoorColour_minus) { if (currentYachtInfo.doorColour == '2') { currentYachtInfo.doorColour = '\0'; } }

			bool bFlagIndex_plus = false, bFlagIndex_minus = false;
			AddTexter("Flag", currentYachtInfo.flagIndex, vFlagSuffixes, null, bFlagIndex_plus, bFlagIndex_minus);
			if (bFlagIndex_plus) { if (currentYachtInfo.flagIndex < vFlagSuffixes.size() - 1) { currentYachtInfo.flagIndex++; } }
			if (bFlagIndex_minus) { if (currentYachtInfo.flagIndex > 0) { currentYachtInfo.flagIndex--; } }

			AddsettingscolOption("Marker Colour", currentYachtInfo.markerColour);

			bool bCreateYachtPressed = false;
			AddOption("Build Yacht", bCreateYachtPressed); if (bCreateYachtPressed)
			{
				DO_SCREEN_FADE_OUT(50);
				for (auto& sclf : currentYachtInfo.vScaleforms) sclf.first.Unload();
				currentYachtInfo.yachtProp.Handle() = 0;
				TeleportPedToYacht(ped, currentYachtInfo);
				(ped.IsInVehicle() ? ped.CurrentVehicle() : GTAentity(ped)).FreezePosition(true);

				if (oldYachtInfo != nullptr)
				{
					DeleteYacht(*oldYachtInfo);
					//delete oldYachtInfo;
					oldYachtInfo = nullptr;
				}
				WAIT(150);
				CreateYacht(currentYachtInfo);
				TeleportPedToYacht(ped, currentYachtInfo);
				(ped.IsInVehicle() ? ped.CurrentVehicle() : GTAentity(ped)).FreezePosition(false);
				WATER::SET_DEEP_OCEAN_SCALER(0.0f);
				WATER::REMOVE_EXTRA_CALMING_QUAD(-4);
				Menu::SetSub_previous();
				DO_SCREEN_FADE_IN(200);
				return;
			}

		}

		void Tick()
		{
			auto& yachtInfo = currentYachtInfo;
			if (yachtInfo.location != nullptr && yachtInfo.option != nullptr)
			{
				GTAentity myPed = PLAYER_PED_ID();
				Vector3& myPos = myPed.Position_get();
				auto& posh = yachtInfo.location->second.poses[yachtInfo.internalLocationIndex - 1];

				if (myPos.DistanceTo(posh.pos) < 100.0f)
				{
					bool bMyPedIsInVehicle = IS_PED_IN_ANY_VEHICLE(myPed.Handle(), false) != 0;

					auto& colour = yachtInfo.markerColour;
					float scale = 0.75f;
					auto& vPositions = yachtInfo.vMarkerPositions;

					//auto& scaleformGamerName = yachtInfo.vScaleforms[2];
					////if (scaleformGamerName.first.Load("YACHT_GAMERNAME"))
					//if (!scaleformGamerName.first.HasLoaded())
					//{
					//	scaleformGamerName.first.Load("YACHT_GAMERNAME");
					//	//scaleformGamerName.first.Handle() = invoke<int>(0x2F14983962462691, "YACHT_GAMERNAME");
					//}
					//else
					//{
					//	scaleformGamerName.first.CallFunction("SET_MISSION_INFO");
					//	scaleformGamerName.first.PushString2("AAAAYYYYY HAX");//(scaleformGamerName.second);
					//	scaleformGamerName.first.PopFunction();
					//	scaleformGamerName.first.Render3D(myPos + Vector3::WorldUp() * 1.3f, GameplayCamera::Rotation_get() + Vector3(0, 0, 180), Vector3(1, 1, 1), Vector3(21, 21, 7));
					//}

					for (auto& p : vPositions)
					{
						World::DrawMarker(MarkerType::VerticalCylinder, p.first + Vector3::WorldDown() * 0.8301f, Vector3(), Vector3(), Vector3::One() * scale, colour);

						if (!YachtOffsets::bPlayerJustTeleportedBetweenMarkers)
						{
							if (!bMyPedIsInVehicle)
							{
								if (myPos.DistanceTo(p.first) < scale)
								{
									YachtOffsets::bPlayerJustTeleportedBetweenMarkers = true;
									DO_SCREEN_FADE_OUT(5);
									myPed.RequestControl();
									WAIT(20);
									myPed.Position_set(p.second);
									//myPed.Heading_set(same);
									TaskSequence sq;
									Vector3& outsideMarkerPos = myPed.GetOffsetInWorldCoords(0, scale + 1.0f, 0);
									TASK_GO_STRAIGHT_TO_COORD(0, outsideMarkerPos.x, outsideMarkerPos.y, outsideMarkerPos.z, 1.5f, 2000, Vector3::DirectionToRotation(Vector3::Normalize(outsideMarkerPos - p.second)).z, 0.0f);
									sq.Close();
									sq.MakePedPerform(myPed);
									sq.Clear();
									GameplayCamera::RelativeHeading_set(0.0f);
									GameplayCamera::RelativePitch_set(0.0f);
									WAIT(100);
									DO_SCREEN_FADE_IN(300);
									return;
								}
							}
						}
						else
						{
							YachtOffsets::bPlayerJustTeleportedBetweenMarkers = false;
							for (auto& pp : yachtInfo.vMarkerPositions)
							{
								if (myPos.DistanceTo(pp.first) < scale + 0.36f)
								{
									YachtOffsets::bPlayerJustTeleportedBetweenMarkers = true;
									return;
								}
							}

						}
					}
				}
			}
		}

	}

}




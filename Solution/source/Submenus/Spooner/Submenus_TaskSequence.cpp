/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Submenus_TaskSequence.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Scripting\enums.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAprop.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Scripting\World.h"
#include "..\..\Util\StringManip.h"
#include "..\..\Util\keyboard.h"
#include "..\..\Util\FileLogger.h"
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\Camera.h"
#include "..\..\Scripting\WeaponIndivs.h"

#include "STSTask.h"
#include "STSTasks.h"
#include "SpoonerEntity.h"
#include "SpoonerMode.h"
#include "Databases.h"
#include "EntityManagement.h"
#include "Submenus.h"
#include "..\..\Submenus\PedComponentChanger.h"
#include "..\..\Submenus\Settings.h"
#include "..\..\Submenus\PedAnimation.h"
#include "..\..\Submenus\PedSpeech.h"
#include "..\..\Submenus\PtfxSubs.h"

namespace sub::Spooner
{
	namespace Submenus
	{
		STSTask* _selectedSTST = nullptr;

		namespace Sub_TaskSequence
		{
			void Nothing()
			{
			}
			void SetHealth()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SetHealth>();

				bool bTogglePlayOncePressed = false;
				AddTickol("Apply Only Once", !tskPtr->isLoopedTask, bTogglePlayOncePressed, bTogglePlayOncePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bTogglePlayOncePressed)
				{
					if (tskPtr->isLoopedTask)
					{
						tskPtr->duration = -2;
						tskPtr->isLoopedTask = false;
						Menu::Up();
					}
					else
					{
						tskPtr->duration = 5000;
						tskPtr->isLoopedTask = true;
						Menu::Down();

					}
				}

				bool bInputPressed = false, bPlusPressed = false, bMinusPressed = false;
				AddNumber("Health Value", tskPtr->healthValue, 0, bInputPressed, bPlusPressed, bMinusPressed);
				if (bPlusPressed) { if (tskPtr->healthValue < INT_MAX) { tskPtr->healthValue++; } }
				if (bMinusPressed) { if (tskPtr->healthValue > 0) { tskPtr->healthValue--; } }
				if (bInputPressed)
				{
					std::string inputStr = Game::InputBox(std::string(), 5U, std::string(), std::to_string(tskPtr->healthValue));
					if (inputStr.length())
					{
						try { tskPtr->healthValue = stoi(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Int, std::string(), 5U, std::string(), std::to_string(tskPtr->healthValue));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->healthValue);
				}
			}

			void AddBlip()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AddBlip>();

				bool bEditLabelPressed = false;
				AddTexter("Label", 0, std::vector<std::string>{tskPtr->label}, bEditLabelPressed); if (bEditLabelPressed)
				{
					tskPtr->label = Game::InputBox(tskPtr->label, 26U, "Enter custom label:", tskPtr->label);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1String, tskPtr->label, 26U, "Enter custom marker name:", tskPtr->label);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->label);
				}

				bool colour_plus = false, colour_minus = false;
				AddTexter("Colour", 0, std::vector<std::string>{ BlipColour::vNames.at(tskPtr->colour) }, null, colour_plus, colour_minus);
				if (colour_plus)
				{
					auto colourIt = BlipColour::vNames.find(tskPtr->colour);
					if (std::next(colourIt) != BlipColour::vNames.end())
					{
						++colourIt;
						tskPtr->colour = colourIt->first;
					}
				};
				if (colour_minus)
				{
					auto colourIt = BlipColour::vNames.find(tskPtr->colour);
					if (colourIt != BlipColour::vNames.begin())
					{
						--colourIt;
						tskPtr->colour = colourIt->first;
					}
				};

				bool icon_plus = false, icon_minus = false;
				AddTexter("Icon", 0, std::vector<std::string>{ BlipIcon::vNames.at(tskPtr->icon) }, null, icon_plus, icon_minus);
				if (icon_plus)
				{
					auto iconIt = BlipIcon::vNames.find(tskPtr->icon);
					if (std::next(iconIt) != BlipIcon::vNames.end())
					{
						++iconIt;
						tskPtr->icon = iconIt->first;
					}
				};
				if (icon_minus)
				{
					auto iconIt = BlipIcon::vNames.find(tskPtr->icon);
					if (iconIt != BlipIcon::vNames.begin())
					{
						--iconIt;
						tskPtr->icon = iconIt->first;
					}
				};

				bool bAlpha_plus = false, bAlpha_minus = false;
				AddNumber("Alpha", tskPtr->alpha, 2, null, bAlpha_plus, bAlpha_minus);
				if (bAlpha_plus) { if (tskPtr->alpha < UINT8_MAX) tskPtr->alpha++; }
				if (bAlpha_minus) { if (tskPtr->alpha > 0ui8) tskPtr->alpha--; }

				bool bScale_plus = false, bScale_minus = false;
				AddNumber("Scale", tskPtr->scale, 2, null, bScale_plus, bScale_minus);
				if (bScale_plus) { if (tskPtr->scale < FLT_MAX) tskPtr->scale += 0.01f; }
				if (bScale_minus) { if (tskPtr->scale > 0.0f) tskPtr->scale -= 0.01f; }

				AddToggle("Flashing", tskPtr->isFlashing);
				AddToggle("Friendly", tskPtr->isFriendly);
				AddToggle("Short-Range", tskPtr->isShortRange);
				AddToggle("Show Route", tskPtr->showRoute);

				bool number_plus = false, number_minus = false;
				AddTexter("Display Number", tskPtr->showNumber, std::vector<std::string>{""}, null, number_plus, number_minus);
				if (number_plus) { if (tskPtr->showNumber < INT_MAX) tskPtr->showNumber++; }
				if (number_minus) { if (tskPtr->showNumber > INT_MIN) tskPtr->showNumber--; }
			}
			void RemoveBlip()
			{
			}

			void PAtCoord(Vector3& coord)
			{
				World::DrawMarker(MarkerType::ThickChevronUp, coord, Vector3(), Vector3(180.0f, 0.0f, 0.0f), Vector3(1, 1, 1), RGBA(177, 33, 193, 210));

				AddOption("~italic~" + coord.ToString(), null);

				auto& spoocam = SpoonerMode::spoonerModeCamera;
				if (!spoocam.IsActive())
				{
					bool bSetPosToMe = false;
					AddOption("Set Target To Player Position", bSetPosToMe); if (bSetPosToMe)
					{
						Vector3 myPos = GTAentity(PLAYER_PED_ID()).Position_get();
						coord = myPos;
					}
				}
				else
				{
					bool bSetPosToHitCoords = false;
					AddOption("Set Target To Camera Target", bSetPosToHitCoords); if (bSetPosToHitCoords)
					{
						Vector3 hitCoords = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 160.0f, 3.0f);
						coord = hitCoords;
					}
				}
				if (IS_WAYPOINT_ACTIVE())
				{
					bool bSetPosToWp = false;
					AddOption("Set Target To Waypoint", bSetPosToWp); if (bSetPosToWp)
					{
						GTAblip wpBlip = GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint);
						Vector3 wpCoords = wpBlip.Position_get();
						wpCoords.z = World::GetGroundHeight(wpCoords);
						coord = wpCoords;
					}
				}

				bool bManualPlacementForPosPressed = false;
				AddOption("Adjust Target Manually", bManualPlacementForPosPressed, nullFunc, SUB::SPOONER_VECTOR3_MANUALPLACEMENT); if (bManualPlacementForPosPressed)
				{
					SpoonerVector3ManualPlacementPtrs = { 0, &coord, nullptr };
				}
			}
			void PAtEntity(GTAentity& targetEntity, EntityType eType = EntityType::ALL)
			{
				UINT8 eTypeInt = (UINT8)eType;
				std::array<std::string, 4> eTypeNames{ { "Entities", "Peds", "Vehicles", "Objects" } };
				AddBreak("Available " + eTypeNames[eTypeInt >= 0 && eTypeInt < eTypeNames.size() ? eTypeInt : 0]);

				GTAentity& thisTargetEnt = targetEntity;

				GTAentity myPed = PLAYER_PED_ID();
				if (myPed.Handle() != SelectedEntity.Handle.Handle() && myPed.Exists())
				{
					bool bMyPedPressed = false;
					AddTickol("Self", thisTargetEnt == myPed, bMyPedPressed, bMyPedPressed); if (bMyPedPressed)
					{
						thisTargetEnt = myPed;
					}
				}

				for (auto& e : Databases::EntityDb)
				{
					if (e.Handle.Handle() != SelectedEntity.Handle.Handle() && e.Handle.Exists() && (eType == EntityType::ALL || e.Type == eType))
					{
						bool bEntPressed = false;
						AddTickol(e.HashName, thisTargetEnt == e.Handle, bEntPressed, bEntPressed); if (bEntPressed)
						{
							thisTargetEnt = e.Handle;
						}
						if (*Menu::currentopATM == Menu::printingop)
							EntityManagement::ShowArrowAboveEntity(e.Handle, RGBA(0, 255, 0, 200));
					}
				}
			}

			void Pause()
			{
			}
			void UsePhone()
			{
			}
			void ThrowProjectile()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ThrowProjectile>();

				World::DrawMarker(MarkerType::ThickChevronUp, tskPtr->targetPos, Vector3(), Vector3(180.0f, 0.0f, 0.0f), Vector3(1, 1, 1), RGBA(177, 33, 193, 210));

				AddOption("~italic~" + tskPtr->targetPos.ToString(), null);

				auto& spoocam = SpoonerMode::spoonerModeCamera;
				if (!spoocam.IsActive())
				{
					bool bSetPosToMe = false;
					AddOption("Set Target To Player Position", bSetPosToMe); if (bSetPosToMe)
					{
						Vector3 myPos = GTAentity(PLAYER_PED_ID()).Position_get();
						tskPtr->targetPos = myPos;
					}
				}
				else
				{
					bool bSetPosToHitCoords = false;
					AddOption("Set Target To Camera Target", bSetPosToHitCoords); if (bSetPosToHitCoords)
					{
						Vector3 hitCoords = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 160.0f, 3.0f);
						tskPtr->targetPos = hitCoords;
					}
				}

			}
			void Writhe()
			{
			}
			void FaceDirection()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FaceDirection>();

				World::DrawMarker(MarkerType::DebugSphere, SelectedEntity.Handle.Position_get().PointOnCircle(1.0f, tskPtr->heading), Vector3(0, 0, tskPtr->heading), Vector3(), Vector3(0.3f, 0.3f, 0.3f), RGBA(177, 33, 193, 210));

				bool bHeading_plus = false, bHeading_minus = false;
				AddNumber("Direction To Face", tskPtr->heading, 0, null, bHeading_plus, bHeading_minus);
				if (bHeading_plus) { tskPtr->heading += 1.0f; if (tskPtr->heading > 180.0f) tskPtr->heading = -180.0f; }
				if (bHeading_minus) { tskPtr->heading -= 1.0f; if (tskPtr->heading < -180.0f) tskPtr->heading = 180.0f; }
			}
			void FaceEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FaceEntity>();

				PAtEntity(tskPtr->targetEntity);
			}
			void LookAtCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::LookAtCoord>();

				PAtCoord(tskPtr->coord);
			}
			void LookAtEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::LookAtEntity>();

				PAtEntity(tskPtr->targetEntity);
			}
			void TeleportToCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::TeleportToCoord>();

				if (SelectedEntity.Type == EntityType::PED)
				{
					bool bTeleVehicleToggle = false;
					AddTickol("Take Vehicle Too (If In One)", tskPtr->takeVehicleToo, bTeleVehicleToggle, bTeleVehicleToggle, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bTeleVehicleToggle) tskPtr->takeVehicleToo = !tskPtr->takeVehicleToo;
				}

				PAtCoord(tskPtr->destination);
			}
			void SeekCoverAtCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SeekCoverAtCoord>();

				bool bAllowPeekingToggle = false;
				AddTickol("Allow Peeking", tskPtr->canPeekInCover, bAllowPeekingToggle, bAllowPeekingToggle, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bAllowPeekingToggle) tskPtr->canPeekInCover = !tskPtr->canPeekInCover;

				PAtCoord(tskPtr->coverPos);
			}
			void SlideToCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SlideToCoord>();

				World::DrawMarker(MarkerType::DebugSphere, SelectedEntity.Handle.Position_get().PointOnCircle(1.0f, tskPtr->heading), Vector3(), Vector3(0, 0, tskPtr->heading), Vector3(0.3f, 0.3f, 0.3f), RGBA(177, 33, 193, 210));

				bool bSpeed_plus = false, bSpeed_minus = false;
				AddNumber("Speed", tskPtr->speed, 1, null, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speed < 250.0f) tskPtr->speed += 0.5f; }
				if (bSpeed_minus) { if (tskPtr->speed > 0.0f) tskPtr->speed -= 0.5f; }

				bool bHeading_plus = false, bHeading_minus = false;
				AddNumber("Direction To Face", tskPtr->heading, 0, null, bHeading_plus, bHeading_minus);
				if (bHeading_plus) { tskPtr->heading += 1.0f; if (tskPtr->heading > 180.0f) tskPtr->heading = -180.0f; }
				if (bHeading_minus) { tskPtr->heading -= 1.0f; if (tskPtr->heading < -180.0f) tskPtr->heading = 180.0f; }

				PAtCoord(tskPtr->destination);
			}
			void GoToCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::GoToCoord>();

				bool bSpeed_plus = false, bSpeed_minus = false;
				AddTexter("Speed", (tskPtr->speed > 2.5f ? 1 : 0), std::vector<std::string>{"Walk", "Run"}, null, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speed < 4.0f) tskPtr->speed = 4.0f; }
				if (bSpeed_minus) { if (tskPtr->speed > 1.0f) tskPtr->speed = 1.0f; }

				PAtCoord(tskPtr->destination);
			}
			void FollowRoute()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FollowRoute>();

				const Vector3& entityPos = SelectedEntity.Handle.Position_get();

				for (auto porit = tskPtr->route.begin(); porit != tskPtr->route.end(); ++porit)
				{
					World::DrawMarker(MarkerType::ThickChevronUp, *porit, Vector3(), Vector3(180.0f, 0.0f, 0.0f), Vector3(1, 1, 1), RGBA(177, 33, 193, 210));
					World::DrawLine(porit == tskPtr->route.begin() ? entityPos : *(porit - 1), *porit, RGBA(177, 33, 193, 210));
				}

				bool bSpeed_plus = false, bSpeed_minus = false;
				AddTexter("Speed", (tskPtr->speed > 2.5f ? 1 : 0), std::vector<std::string>{"Walk", "Run"}, null, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speed < 4.0f) tskPtr->speed = 4.0f; }
				if (bSpeed_minus) { if (tskPtr->speed > 1.0f) tskPtr->speed = 1.0f; }

				for (auto cit = tskPtr->route.begin(); cit != tskPtr->route.end();)
				{
					AddOption("~italic~" + cit->ToString(), null);

					if (Menu::printingop == *Menu::currentopATM)
					{
						bool bRemoveCoordPressed = false;
						if (Menu::bit_controller)
						{
							Menu::add_IB(INPUT_SCRIPT_RLEFT, "Remove coord");
							bRemoveCoordPressed = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT) != 0;
						}
						else
						{
							Menu::add_IB(VirtualKey::B, "Remove coord");
							bRemoveCoordPressed = IsKeyJustUp(VirtualKey::B);
						}
						if (bRemoveCoordPressed)
						{
							cit = tskPtr->route.erase(cit);
							//Menu::Up();
						}
						else ++cit;
					}
					else ++cit;
				}

				auto& spoocam = SpoonerMode::spoonerModeCamera;
				if (!spoocam.IsActive())
				{
					bool bSetPosToMe = false;
					AddTickol("Add Player Position", true, bSetPosToMe, bSetPosToMe, TICKOL::SMALLNEWSTAR); if (bSetPosToMe)
					{
						Vector3 myPos = GTAentity(PLAYER_PED_ID()).Position_get();
						tskPtr->route.push_back(myPos);
						Menu::Down();
					}
				}
				else
				{
					bool bSetPosToHitCoords = false;
					AddTickol("Add Camera Target Position", true, bSetPosToHitCoords, bSetPosToHitCoords, TICKOL::SMALLNEWSTAR); if (bSetPosToHitCoords)
					{
						Vector3 hitCoords = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 160.0f, 3.0f);
						tskPtr->route.push_back(hitCoords);
						Menu::Down();
					}
				}

			}
			void FollowEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FollowEntity>();

				bool bSpeed_plus = false, bSpeed_minus = false;
				AddTexter("Speed", (tskPtr->speed > 2.5f ? 1 : 0), std::vector<std::string>{"Walk", "Run"}, null, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speed < 4.0f) tskPtr->speed = 4.0f; }
				if (bSpeed_minus) { if (tskPtr->speed > 1.0f) tskPtr->speed = 1.0f; }

				PAtEntity(tskPtr->targetEntity);
			}
			void PatrolInRange()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PatrolInRange>();

				float& thisRadius = tskPtr->radius;

				bool bRadius_plus = false, bRadius_minus = false;
				AddNumber("Radius", thisRadius, 0, null, bRadius_plus, bRadius_minus);
				if (*Menu::currentopATM == Menu::printingop)
					EntityManagement::DrawRadiusDisplayingMarker(SelectedEntity.Handle.Position_get(), thisRadius);
				if (bRadius_plus) { if (thisRadius < FLT_MAX) thisRadius += 1.0f; }
				if (bRadius_minus) { if (thisRadius > 0.0f) thisRadius -= 1.0f; }

				PAtCoord(tskPtr->coord);
			}
			void WanderFreely()
			{
			}
			void FleeFromCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FleeFromCoord>();

				PAtCoord(tskPtr->originCoords);
			}
			void NearestAppropriateAction()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::NearestAppropriateAction>();

				float& thisSearchRadius = tskPtr->searchRadius;
				bool& thisWarp = tskPtr->warp;

				bool bSearchRadius_plus = false, bSearchRadius_minus = false;
				AddNumber("Search Radius", thisSearchRadius, 0, null, bSearchRadius_plus, bSearchRadius_minus);
				if (*Menu::currentopATM == Menu::printingop)
					EntityManagement::DrawRadiusDisplayingMarker(SelectedEntity.Handle.Position_get(), thisSearchRadius);
				if (bSearchRadius_plus) { if (thisSearchRadius < FLT_MAX) thisSearchRadius += 1.0f; }
				if (bSearchRadius_minus) { if (thisSearchRadius > 0.0f) thisSearchRadius -= 1.0f; }

				bool bWarpTogglePressed = false;
				AddTickol("Warp", thisWarp, bWarpTogglePressed, bWarpTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bWarpTogglePressed) thisWarp = !thisWarp;

			}
			void ScenarioAction()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ScenarioAction>();

				std::string& thisScenarioName = tskPtr->scenarioName;

				AddBreak("---Actions---");

				AddOption("All Actions", null, nullFunc, SUB::SPOONER_TASKSEQUENCE_TASKSUB_SCENARIOACTION_LIST);

				for (auto& sn : AnimationSub_TaskScenarios::vNamedScenarios)
				{
					bool bScenarioNamePressed = false;
					AddTickol(sn.name, thisScenarioName == sn.label, bScenarioNamePressed, bScenarioNamePressed); if (bScenarioNamePressed)
					{
						thisScenarioName = sn.label;
					}
				}
			}
			void ScenarioAction_list()
			{
				if (_selectedSTST == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ScenarioAction>();

				std::string& thisScenarioName = tskPtr->scenarioName;

				AddTitle("All Actions");

				bool searchobj = false;
				AddOption(_searchStr.empty() ? "SEARCH" : boost::to_upper_copy(_searchStr), searchobj, nullFunc, -1, true); if (searchobj)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", _searchStr);
					boost::to_lower(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToLower, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto& sl : AnimationSub_TaskScenarios::vValues_TaskScenarios)
				{
					if (!_searchStr.empty()) { if (sl.find(_searchStr) == std::string::npos) continue; }

					bool bScenarioNamePressed = false;
					AddTickol(sl, thisScenarioName == sl, bScenarioNamePressed, bScenarioNamePressed); if (bScenarioNamePressed)
					{
						thisScenarioName = sl;
					}
				}

			}
			void PlayAnimation()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlayAnimation>();
				auto& _searchStr = dict;
				_searchStr.clear();

				AddOption("Settings", null, nullFunc, SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_SETTINGS);
				AddOption("All Animations", null, nullFunc, SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_ALLPEDANIMS);

				if (!sub::AnimationSub_catind::vPresetPedAnims.empty())
				{
					AddBreak("---Basic---");
					for (auto& npa : sub::AnimationSub_catind::vPresetPedAnims)
					{
						bool bPresetAnimPressed = false;
						AddTickol(npa.caption, (npa.animDict == tskPtr->animDict && npa.animName == tskPtr->animName), bPresetAnimPressed, bPresetAnimPressed); if (bPresetAnimPressed)
						{
							tskPtr->animDict = npa.animDict;
							tskPtr->animName = npa.animName;
						}
					}
				}

				std::vector<std::pair<std::string, std::string>> vFavAnims;
				GetFavouriteAnimations(vFavAnims);
				if (!vFavAnims.empty())
				{
					AddBreak("---Favourites---");
					for (auto& animFav : vFavAnims)
					{
						bool bAnimFavPressed = false;
						AddTickol(animFav.first + ", " + animFav.second, (animFav.first == tskPtr->animDict && animFav.second == tskPtr->animName), bAnimFavPressed, bAnimFavPressed); if (bAnimFavPressed)
						{
							tskPtr->animDict = animFav.first;
							tskPtr->animName = animFav.second;
						}
					}
				}

				AddBreak("---Custom---");
				bool bInputAnimDict = false, bInputAnimName = false;
				AddOption(tskPtr->animDict, bInputAnimDict);
				AddOption(tskPtr->animName, bInputAnimName);
				if (bInputAnimDict || bInputAnimName)
				{
					std::string* inputStr = bInputAnimDict ? &tskPtr->animDict : &tskPtr->animName;
					*inputStr = Game::InputBox(*inputStr, 126U, bInputAnimDict ? "Enter Dictionary:" : "Enter Name:", *inputStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1String, *inputStr, 126U, bInputAnimDict ? "Enter Dictionary:" : "Enter Name:", *inputStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(inputStr);
				}

				/// maybe a scroller with indices like darkel wants
			}
			void PlayAnimation_settings()
			{
				if (_selectedSTST == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlayAnimation>();

				AddTitle("Settings");

				bool bSpeed_plus = false, bSpeed_minus = false, bSpeed_input = false;
				AddNumber("Blend-In Speed", tskPtr->speed, 1, bSpeed_input, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speed < FLT_MAX) tskPtr->speed += 0.1f; }
				if (bSpeed_minus) { if (tskPtr->speed > -FLT_MAX) tskPtr->speed -= 0.1f; }
				if (bSpeed_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speed).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speed = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speed).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speed);
				}

				bool bSpeedMultiplier_plus = false, bSpeedMultiplier_minus = false, bSpeedMultiplier_input = false;
				AddNumber("Blend-Out Speed", tskPtr->speedMultiplier, 1, bSpeedMultiplier_input, bSpeedMultiplier_plus, bSpeedMultiplier_minus);
				if (bSpeedMultiplier_plus) { if (tskPtr->speedMultiplier < FLT_MAX) tskPtr->speedMultiplier += 0.1f; }
				if (bSpeedMultiplier_minus) { if (tskPtr->speedMultiplier > -FLT_MAX) tskPtr->speedMultiplier -= 0.1f; }
				if (bSpeedMultiplier_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speedMultiplier).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speedMultiplier = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speedMultiplier).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speedMultiplier);
				}

				bool flag_plus = false, flag_minus = false;
				AddTexter("Flag", 0, std::vector<std::string>{ AnimFlag::vFlagNames[tskPtr->flag] }, null, flag_plus, flag_minus);
				if (flag_plus)
				{
					for (auto it = AnimFlag::vFlagNames.begin(); it != AnimFlag::vFlagNames.end(); ++it)
					{
						if (it->first == tskPtr->flag)
						{
							++it;
							if (it != AnimFlag::vFlagNames.end())
								tskPtr->flag = it->first;
							break;
						}
					}
				};
				if (flag_minus)
				{
					for (auto it = AnimFlag::vFlagNames.rbegin(); it != AnimFlag::vFlagNames.rend(); ++it)
					{
						if (it->first == tskPtr->flag)
						{
							++it;
							if (it != AnimFlag::vFlagNames.rend())
								tskPtr->flag = it->first;
							break;
						}
					}
				};

				bool bToggleLockPos = false;
				AddTickol("Lock Position", tskPtr->lockPos, bToggleLockPos, bToggleLockPos, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleLockPos)
					tskPtr->lockPos = !tskPtr->lockPos;

				//bool bToggleDurationToAnimDuration = false;
				//AddTickol("Task Duration To Anim Duration", tskPtr->durationToAnimDuration, bToggleDurationToAnimDuration, bToggleDurationToAnimDuration, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleDurationToAnimDuration) tskPtr->durationToAnimDuration = !tskPtr->durationToAnimDuration;

			}
			void PlayAnimation_allPedAnims()
			{
				if (_selectedSTST == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlayAnimation>();

				auto& _searchStr = dict;
				sub::AnimationSub_catind::selectedAnimDictPtr = nullptr;
				bool searchobj = false;
				bool bCurrentPressed;
				bool notFoundInDict;

				AddTitle("All Animations");

				AddOption(_searchStr.empty() ? "SEARCH" : boost::to_upper_copy(_searchStr), searchobj, nullFunc, -1, true); if (searchobj)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", _searchStr);
					boost::to_lower(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToLower, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto& current : sub::AnimationSub_catind::vAllPedAnims)
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
								if (notFoundInDict)
									continue;
							}
						}

						bCurrentPressed = false;
						AddOption(current.first, bCurrentPressed); if (bCurrentPressed)
						{
							sub::AnimationSub_catind::selectedAnimDictPtr = &current;
							Menu::SetSub_delayed = SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_ALLPEDANIMS_INDICT;
						}
					}
				}
			}
			void PlayAnimation_allPedAnims_inDict()
			{
				if (_selectedSTST == nullptr || sub::AnimationSub_catind::selectedAnimDictPtr == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlayAnimation>();
				auto& selectedDict = *sub::AnimationSub_catind::selectedAnimDictPtr;
				//auto& _searchStr = dict;
				bool bCurrentPressed;

				AddTitle(selectedDict.first);

				for (auto& current : selectedDict.second)
				{
					bCurrentPressed = false;
					AddTickol(current, (selectedDict.first == tskPtr->animDict && current == tskPtr->animName), bCurrentPressed, bCurrentPressed); if (bCurrentPressed)
					{
						tskPtr->animDict = selectedDict.first;
						tskPtr->animName = current;
					}

					if (Menu::printingop == *Menu::currentopATM)
					{
						bool bIsAFav = IsAnimationAFavourite(selectedDict.first, current);
						if (Menu::bit_controller)
						{
							Menu::add_IB(INPUT_SCRIPT_RLEFT, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

							if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT))
							{
								!bIsAFav ? AddAnimationToFavourites(selectedDict.first, current) : RemoveAnimationFromFavourites(selectedDict.first, current);
							}
						}
						else
						{
							Menu::add_IB(VirtualKey::B, (!bIsAFav ? "Add to" : "Remove from") + (std::string)" favourites");

							if (IsKeyJustUp(VirtualKey::B))
							{
								!bIsAFav ? AddAnimationToFavourites(selectedDict.first, current) : RemoveAnimationFromFavourites(selectedDict.first, current);
							}
						}
					}
				}

				AddOption("Settings", null, nullFunc, SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_SETTINGS);
			}
			void SetActiveWeapon()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SetActiveWeapon>();

				AddBreak("---Weapon---");
				for (auto& w : WeaponIndivs::vWeaponLabels)
				{
					bool bWeapPressed = false;
					AddTickol(w.second, tskPtr->weaponHash == w.first, bWeapPressed, bWeapPressed, TICKOL::TICK, TICKOL::NONE, true); if (bWeapPressed)
					{
						tskPtr->weaponHash = w.first;
					}
				}
			}
			void AimAtCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AimAtCoord>();

				PAtCoord(tskPtr->coord);
			}
			void AimAtEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AimAtEntity>();

				PAtEntity(tskPtr->targetEntity);
			}
			void ShootAtCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ShootAtCoord>();

				PAtCoord(tskPtr->coord);
			}
			void ShootAtEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ShootAtEntity>();

				PAtEntity(tskPtr->targetEntity);
			}
			void FightHatedTargets()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FightHatedTargets>();

				float& thisRadius = tskPtr->radius;

				bool bRadius_plus = false, bRadius_minus = false;
				AddNumber("Radius", thisRadius, 0, null, bRadius_plus, bRadius_minus);
				if (*Menu::currentopATM == Menu::printingop)
					EntityManagement::DrawRadiusDisplayingMarker(SelectedEntity.Handle.Position_get(), thisRadius);
				if (bRadius_plus) { if (thisRadius < FLT_MAX) thisRadius += 1.0f; }
				if (bRadius_minus) { if (thisRadius > 0.0f) thisRadius -= 1.0f; }
			}
			void FightPed()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FightPed>();

				PAtEntity(tskPtr->targetEntity, EntityType::PED);
			}
			void SpeakToPed()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SpeakToPed>();

				PAtEntity(tskPtr->targetEntity, EntityType::PED);
			}
			void PlaySpeechWithVoice()
			{
				std::string& _searchStr = dict;

				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlaySpeechWithVoice>();

				/*for (auto& oasd : sub::Speech_catind::vSpeechData)
				{
				bool bSpeechDatumPressed = false;
				bool bSpeechIsActive = tskPtr->speechName == oasd.speechName && tskPtr->voiceName == oasd.voiceName;
				AddTickol(oasd.title, bSpeechIsActive, bSpeechDatumPressed, bSpeechDatumPressed); if (bSpeechDatumPressed)
				{
				GTAped(SelectedEntity.Handle).PlaySpeechWithVoice(oasd.speechName, oasd.voiceName, oasd.paramName);
				tskPtr->speechName = oasd.speechName;
				tskPtr->voiceName = oasd.voiceName;
				tskPtr->paramName = oasd.paramName;
				}
				}*/

				sub::Speech_catind::_currVoiceInfo = nullptr;

				bool bSearchPressed = false;
				AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
				{
					_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
					boost::to_upper(_searchStr);
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
				}

				for (auto& v : sub::Speech_catind::vVoiceData)
				{
					if (!_searchStr.empty()) { if (boost::to_upper_copy(v.voiceName).find(_searchStr) == std::string::npos) continue; }

					bool bVoicePressed = false;
					AddOption(v.voiceName, bVoicePressed); if (bVoicePressed)
					{
						sub::Speech_catind::_currVoiceInfo = &v;
						Menu::SetSub_delayed = SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYSPEECHWITHVOICE_INVOICE;
					}
				}
			}
			void PlaySpeechWithVoice_inVoice()
			{
				if (_selectedSTST == nullptr || sub::Speech_catind::_currVoiceInfo == nullptr)
				{
					Menu::SetSub_previous();
					return;
				}
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::PlaySpeechWithVoice>();

				auto& v = *sub::Speech_catind::_currVoiceInfo;

				AddTitle(v.voiceName);

				auto paramIter = std::find_if(sub::Speech_catind::vSpeechParams.begin(), sub::Speech_catind::vSpeechParams.end(),
					[tskPtr](const sub::Speech_catind::SpeechParamS& item) {
					return item.label.compare(tskPtr->paramName) == 0;
				});
				if (paramIter == sub::Speech_catind::vSpeechParams.end())
					paramIter = sub::Speech_catind::vSpeechParams.begin();
				bool bSpeechParam_plus = false, bSpeechParam_minus = false;
				AddTexter("Modifier", 0, std::vector<std::string>{ paramIter->title }, null, bSpeechParam_plus, bSpeechParam_minus);
				if (bSpeechParam_plus) { if (std::next(paramIter) != sub::Speech_catind::vSpeechParams.end()) tskPtr->paramName = (++paramIter)->label; }
				if (bSpeechParam_minus) { if (paramIter != sub::Speech_catind::vSpeechParams.begin()) tskPtr->paramName = (--paramIter)->label; }

				for (auto& s : v.speechNames)
				{
					bool bSpeechPressed = false;
					AddTickol(s, tskPtr->speechName == s, bSpeechPressed, bSpeechPressed, TICKOL::TICK, TICKOL::NONE, false); if (bSpeechPressed)
					{
						tskPtr->voiceName = v.voiceName;
						tskPtr->speechName = s;
						GTAped(SelectedEntity.Handle).PlaySpeechWithVoice(tskPtr->speechName, tskPtr->voiceName, tskPtr->paramName);
					}
				}
			}

			void WarpIntoVehicle()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::WarpIntoVehicle>();

				bool bSeatIndex_plus = false, bSeatIndex_minus = false;
				AddTexter("Seat", tskPtr->seatIndex + 2, std::vector<std::string>{"First Free Seat", "Driver", "Passenger", "Back Seat - Left", "Back Seat - Right"}, null, bSeatIndex_plus, bSeatIndex_minus);
				if (bSeatIndex_plus) { if (tskPtr->seatIndex < 20) { tskPtr->seatIndex++; } }
				if (bSeatIndex_minus) { if (tskPtr->seatIndex > -2) { tskPtr->seatIndex--; } }

				AddBreak("Available Vehicles");

				GTAentity& thisTargetVehicle = tskPtr->vehicleToEnter;

				for (auto& e : Databases::EntityDb)
				{
					if (e.Handle.Handle() != SelectedEntity.Handle.Handle() && e.Handle.IsVehicle())
					{
						bool bPedPressed = false;
						AddTickol(e.HashName, thisTargetVehicle == e.Handle, bPedPressed, bPedPressed); if (bPedPressed)
						{
							thisTargetVehicle = e.Handle;
						}
						if (*Menu::currentopATM == Menu::printingop)
							EntityManagement::ShowArrowAboveEntity(e.Handle, RGBA(0, 255, 0, 200));
					}
				}
			}
			void EnterVehicle()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::EnterVehicle>();

				bool bSeatIndex_plus = false, bSeatIndex_minus = false;
				AddTexter("Seat", tskPtr->seatIndex + 2, std::vector<std::string>{"First Free Seat", "Driver", "Passenger", "Back Seat - Left", "Back Seat - Right"}, null, bSeatIndex_plus, bSeatIndex_minus);
				if (bSeatIndex_plus) { if (tskPtr->seatIndex < 20) { tskPtr->seatIndex++; } }
				if (bSeatIndex_minus) { if (tskPtr->seatIndex > -2) { tskPtr->seatIndex--; } }

				AddBreak("Available Vehicles");

				GTAentity& thisTargetVehicle = tskPtr->vehicleToEnter;

				for (auto& e : Databases::EntityDb)
				{
					if (e.Handle.Handle() != SelectedEntity.Handle.Handle() && e.Handle.IsVehicle())
					{
						bool bPedPressed = false;
						AddTickol(e.HashName, thisTargetVehicle == e.Handle, bPedPressed, bPedPressed); if (bPedPressed)
						{
							thisTargetVehicle = e.Handle;
						}
						if (*Menu::currentopATM == Menu::printingop)
							EntityManagement::ShowArrowAboveEntity(e.Handle, RGBA(0, 255, 0, 200));
					}
				}
			}
			void DriveWander()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::DriveWander>();

				bool bSpeed_plus = false, bSpeed_minus = false, bSpeed_input = false;
				AddNumber("Speed (KMPH)", tskPtr->speedInKmph, 0, bSpeed_input, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speedInKmph < FLT_MAX) tskPtr->speedInKmph += 1.0f; }
				if (bSpeed_minus) { if (tskPtr->speedInKmph > -FLT_MAX) tskPtr->speedInKmph -= 1.0f; }
				if (bSpeed_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speedInKmph).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speedInKmph = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speedInKmph).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speedInKmph);
				}

				int cdsi = 0;
				std::vector<std::string> cds;
				for (UINT i = 0; i < DrivingStyle::nameArray.size(); i++)
				{
					if (DrivingStyle::nameArray[i].style == tskPtr->drivingStyle)
					{
						cdsi = i;
						cds.push_back(DrivingStyle::nameArray[i].name);
						break;
					}
				}
				bool bDrivingStyle_plus = false, bDrivingStyle_minus = false;
				AddTexter("Driving Style", 0, cds, null, bDrivingStyle_plus, bDrivingStyle_minus);
				if (bDrivingStyle_plus) { if (cdsi < DrivingStyle::nameArray.size() - 1) { cdsi++; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }
				if (bDrivingStyle_minus) { if (cdsi > 0) { cdsi--; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }
			}
			void DriveToCoord()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::DriveToCoord>();

				bool bSpeed_plus = false, bSpeed_minus = false, bSpeed_input = false;
				AddNumber("Speed (KMPH)", tskPtr->speedInKmph, 0, bSpeed_input, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speedInKmph < FLT_MAX) tskPtr->speedInKmph += 1.0f; }
				if (bSpeed_minus) { if (tskPtr->speedInKmph > -FLT_MAX) tskPtr->speedInKmph -= 1.0f; }
				if (bSpeed_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speedInKmph).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speedInKmph = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speedInKmph).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speedInKmph);
				}

				int cdsi = 0;
				std::vector<std::string> cds;
				for (UINT i = 0; i < DrivingStyle::nameArray.size(); i++)
				{
					if (DrivingStyle::nameArray[i].style == tskPtr->drivingStyle)
					{
						cdsi = i;
						cds.push_back(DrivingStyle::nameArray[i].name);
						break;
					}
				}
				bool bDrivingStyle_plus = false, bDrivingStyle_minus = false;
				AddTexter("Driving Style", 0, cds, null, bDrivingStyle_plus, bDrivingStyle_minus);
				if (bDrivingStyle_plus) { if (cdsi < DrivingStyle::nameArray.size() - 1) { cdsi++; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }
				if (bDrivingStyle_minus) { if (cdsi > 0) { cdsi--; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }

				PAtCoord(tskPtr->destination);
			}
			void DriveFollowEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::DriveFollowEntity>();

				bool bSpeed_plus = false, bSpeed_minus = false, bSpeed_input = false;
				AddNumber("Max Speed (KMPH)", tskPtr->speedInKmph, 0, bSpeed_input, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speedInKmph < FLT_MAX) tskPtr->speedInKmph += 1.0f; }
				if (bSpeed_minus) { if (tskPtr->speedInKmph > -FLT_MAX) tskPtr->speedInKmph -= 1.0f; }
				if (bSpeed_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speedInKmph).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speedInKmph = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speedInKmph).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speedInKmph);
				}

				int cdsi = 0;
				std::vector<std::string> cds;
				for (UINT i = 0; i < DrivingStyle::nameArray.size(); i++)
				{
					if (DrivingStyle::nameArray[i].style == tskPtr->drivingStyle)
					{
						cdsi = i;
						cds.push_back(DrivingStyle::nameArray[i].name);
						break;
					}
				}
				bool bDrivingStyle_plus = false, bDrivingStyle_minus = false;
				AddTexter("Driving Style", 0, cds, null, bDrivingStyle_plus, bDrivingStyle_minus);
				if (bDrivingStyle_plus) { if (cdsi < DrivingStyle::nameArray.size() - 1) { cdsi++; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }
				if (bDrivingStyle_minus) { if (cdsi > 0) { cdsi--; tskPtr->drivingStyle = DrivingStyle::nameArray[cdsi].style; } }

				bool bMinDistance_plus = false, bMinDistance_minus = false;
				AddNumber("Minimum Distance", tskPtr->minDistance, 1, null, bMinDistance_plus, bMinDistance_minus);
				if (bMinDistance_plus) { if (tskPtr->minDistance < FLT_MAX) tskPtr->minDistance += 0.5f; }
				if (bMinDistance_minus) { if (tskPtr->minDistance > 0.0f) tskPtr->minDistance -= 0.5f; }
				
				PAtEntity(tskPtr->targetEntity);
			}
			void DriveLandPlane()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::DriveLandPlane>();

				World::DrawMarker(MarkerType::ThickChevronUp, tskPtr->runwayStart, Vector3(), Vector3(180.0f, 0.0f, 0.0f), Vector3(1, 1, 1), RGBA(177, 33, 193, 210));
				World::DrawMarker(MarkerType::ThickChevronUp, tskPtr->runwayEnd, Vector3(), Vector3(180.0f, 0.0f, 0.0f), Vector3(1, 1, 1), RGBA(177, 33, 193, 210));
				World::DrawLine(tskPtr->runwayStart, tskPtr->runwayEnd, RGBA(177, 33, 193, 210));

				for (auto& nas : std::vector<std::pair<std::string, Vector3*>>
					{
						{ "Runway Start", &tskPtr->runwayStart },
						{ "Runway End", &tskPtr->runwayEnd }
					})
				{
					AddBreak(nas.first);
					AddOption("~italic~" + nas.second->ToString(), null);

					auto& spoocam = SpoonerMode::spoonerModeCamera;
					if (!spoocam.IsActive())
					{
						bool bSetPosToMe = false;
						AddOption("Set To Player Position", bSetPosToMe); if (bSetPosToMe)
						{
							Vector3 myPos = GTAentity(PLAYER_PED_ID()).Position_get();
							*nas.second = myPos;
						}
					}
					else
					{
						bool bSetPosToHitCoords = false;
						AddOption("Set To Camera Target", bSetPosToHitCoords); if (bSetPosToHitCoords)
						{
							Vector3 hitCoords = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 160.0f, 3.0f);
							*nas.second = hitCoords;
						}
					}
					if (IS_WAYPOINT_ACTIVE())
					{
						bool bSetPosToWp = false;
						AddOption("Set To Waypoint", bSetPosToWp); if (bSetPosToWp)
						{
							GTAblip wpBlip = GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint);
							Vector3 wpCoords = wpBlip.Position_get();
							wpCoords.z = World::GetGroundHeight(wpCoords);
							*nas.second = wpCoords;
						}
					}

					bool bManualPlacementForPosPressed = false;
					AddOption("Adjust Manually", bManualPlacementForPosPressed, nullFunc, SUB::SPOONER_VECTOR3_MANUALPLACEMENT); if (bManualPlacementForPosPressed)
					{
						SpoonerVector3ManualPlacementPtrs = { 0, nas.second, nullptr };
					}
				}

			}

			void AchieveVehicleForwardSpeed()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AchieveVehicleForwardSpeed>();

				bool bSpeed_plus = false, bSpeed_minus = false, bSpeed_input = false;
				AddNumber("Speed (KMPH)", tskPtr->speedInKmph, 0, bSpeed_input, bSpeed_plus, bSpeed_minus);
				if (bSpeed_plus) { if (tskPtr->speedInKmph < FLT_MAX) tskPtr->speedInKmph += 1.0f; }
				if (bSpeed_minus) { if (tskPtr->speedInKmph > -FLT_MAX) tskPtr->speedInKmph -= 1.0f; }
				if (bSpeed_input)
				{
					std::string inputStr = Game::InputBox("", 6U, "", std::to_string(tskPtr->speedInKmph).substr(0, 5));
					if (inputStr.length() > 0)
					{
						try { tskPtr->speedInKmph = stof(inputStr); }
						catch (...) { Game::Print::PrintError_InvalidInput(); }
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Float, std::string(), 5U, std::string(), std::to_string(tskPtr->speedInKmph).substr(0, 5));
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->speedInKmph);
				}

				bool bOnGroundOnlyTogglePressed = false;
				AddTickol("On Ground Only", tskPtr->onGroundOnly, bOnGroundOnlyTogglePressed, bOnGroundOnlyTogglePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bOnGroundOnlyTogglePressed) tskPtr->onGroundOnly = !tskPtr->onGroundOnly;

			}

			void ChangeTextureVariation()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ChangeTextureVariation>();

				bool bNewValue_plus = false, bNewValue_minus = false;
				AddNumber("New Value", tskPtr->newValue, 0, null, bNewValue_plus, bNewValue_minus);
				if (bNewValue_plus) { if (tskPtr->newValue < UINT8_MAX) tskPtr->newValue++; }
				if (bNewValue_minus) { if (tskPtr->newValue > 0) tskPtr->newValue--; }
			}

			void AchieveVelocity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AchieveVelocity>();

				const GTAentity& thisEntity = SelectedEntity.Handle;
				const Vector3& entityPos = thisEntity.Position_get();
				const Vector3& entityRot = thisEntity.Rotation_get();
				const Vector3& rotForVel = (tskPtr->isRelative ? entityRot : Vector3::Zero()) + Vector3(tskPtr->pitch, 0.0f, tskPtr->heading);
				const Vector3& dirForVel = Vector3::RotationToDirection(rotForVel);

				const ModelDimensions& entityMd = thisEntity.ModelDimensions();

				const Vector3& markerPos = entityPos + (dirForVel * (entityMd.Dim1.y + 2.0f));
				const Vector3& markerRot = rotForVel;
				World::DrawMarker(MarkerType::DebugSphere, markerPos, markerRot, Vector3(), Vector3(0.3f, 0.3f, 0.3f), RGBA(177, 33, 193, 210));
				World::DrawLine(entityPos, markerPos, RGBA(177, 33, 193, 210));

				bool bToggleRelativePressed = false;
				AddTickol("Relative", tskPtr->isRelative, bToggleRelativePressed, bToggleRelativePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleRelativePressed)
					tskPtr->isRelative = !tskPtr->isRelative;

				bool bHeading_plus = false, bHeading_minus = false;
				AddNumber("Direction", tskPtr->heading, 0, null, bHeading_plus, bHeading_minus);
				if (bHeading_plus) { tskPtr->heading += 1.0f; if (tskPtr->heading > 180.0f) tskPtr->heading = -180.0f; }
				if (bHeading_minus) { tskPtr->heading -= 1.0f; if (tskPtr->heading < -180.0f) tskPtr->heading = 180.0f; }

				bool bPitch_plus = false, bPitch_minus = false;
				AddNumber("Pitch", tskPtr->pitch, 2, null, bPitch_plus, bPitch_minus);
				if (bPitch_plus) { tskPtr->pitch += 1.0f; if (tskPtr->pitch > 90.0f) tskPtr->pitch = -90.0f; }
				if (bPitch_minus) { tskPtr->pitch -= 1.0f; if (tskPtr->pitch < -90.0f) tskPtr->pitch = 90.0f; }

				bool bMagnitude_plus = false, bMagnitude_minus = false;
				AddNumber("Magnitude (m/s)", tskPtr->magnitude, 1, null, bMagnitude_plus, bMagnitude_minus);
				if (bMagnitude_plus) { if (tskPtr->magnitude < FLT_MAX) tskPtr->magnitude += 0.5f; }
				if (bMagnitude_minus) { if (tskPtr->magnitude > -FLT_MAX) tskPtr->magnitude -= 0.5f; }
			}
			void AchievePushForce()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::AchievePushForce>();

				const GTAentity& thisEntity = SelectedEntity.Handle;
				const Vector3& entityPos = thisEntity.Position_get();
				const Vector3& entityRot = thisEntity.Rotation_get();
				const Vector3& rotForFrc = (tskPtr->isRelative ? entityRot : Vector3::Zero()) + Vector3(tskPtr->pitch, 0.0f, tskPtr->heading);
				const Vector3& dirForFrc = Vector3::RotationToDirection(rotForFrc);

				const ModelDimensions& entityMd = thisEntity.ModelDimensions();

				const Vector3& markerPos = entityPos + (dirForFrc * (entityMd.Dim1.y + 2.0f));
				const Vector3& markerRot = rotForFrc;
				World::DrawMarker(MarkerType::DebugSphere, markerPos, markerRot, Vector3(), Vector3(0.3f, 0.3f, 0.3f), RGBA(177, 33, 193, 210));
				World::DrawLine(entityPos, markerPos, RGBA(177, 33, 193, 210));

				World::DrawMarker(MarkerType::DebugSphere, thisEntity.GetOffsetInWorldCoords(tskPtr->offsetVector), markerRot, Vector3(), Vector3(0.07f, 0.07f, 0.07f), RGBA(177, 33, 193, 210));

				bool bToggleRelativePressed = false;
				AddTickol("Relative", tskPtr->isRelative, bToggleRelativePressed, bToggleRelativePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleRelativePressed)
					tskPtr->isRelative = !tskPtr->isRelative;

				std::vector<std::string> vForceTypeNames = { "0", "Standard", "2", "Standard Weak" };
				bool bForceType_plus = false, bForceType_minus = false;
				AddTexter("Force Type", tskPtr->forceType, vForceTypeNames, null, bForceType_plus, bForceType_minus);
				if (bForceType_plus) { if (tskPtr->forceType < vForceTypeNames.size() - 1) tskPtr->forceType++; }
				if (bForceType_minus) { if (tskPtr->forceType > 0) tskPtr->forceType--; }

				bool bHeading_plus = false, bHeading_minus = false;
				AddNumber("Direction", tskPtr->heading, 0, null, bHeading_plus, bHeading_minus);
				if (bHeading_plus) { tskPtr->heading += 1.0f; if (tskPtr->heading > 180.0f) tskPtr->heading = -180.0f; }
				if (bHeading_minus) { tskPtr->heading -= 1.0f; if (tskPtr->heading < -180.0f) tskPtr->heading = 180.0f; }

				bool bPitch_plus = false, bPitch_minus = false;
				AddNumber("Pitch", tskPtr->pitch, 2, null, bPitch_plus, bPitch_minus);
				if (bPitch_plus) { tskPtr->pitch += 1.0f; if (tskPtr->pitch > 90.0f) tskPtr->pitch = -90.0f; }
				if (bPitch_minus) { tskPtr->pitch -= 1.0f; if (tskPtr->pitch < -90.0f) tskPtr->pitch = 90.0f; }

				bool bMagnitude_plus = false, bMagnitude_minus = false;
				AddNumber("Magnitude", tskPtr->magnitude, 1, null, bMagnitude_plus, bMagnitude_minus);
				if (bMagnitude_plus) { if (tskPtr->magnitude < FLT_MAX) tskPtr->magnitude += 0.5f; }
				if (bMagnitude_minus) { if (tskPtr->magnitude > -FLT_MAX) tskPtr->magnitude -= 0.5f; }

				//=========================OFFSET VECTOR======================
				AddBreak("---Region To Push---");
				bool prec_plus = 0, prec_minus = 0,
					offsetx_plus = 0, offsetx_minus = 0,
					offsety_plus = 0, offsety_minus = 0,
					offsetz_plus = 0, offsetz_minus = 0,
					bResetOffsetVector = 0;

				AddNumber("Scroll Sensitivity", _manualPlacementPrecision, 4, null, prec_minus, prec_plus);
				AddNumber("X", tskPtr->offsetVector.x, 4, null, offsetx_plus, offsetx_minus);
				AddNumber("Y", tskPtr->offsetVector.y, 4, null, offsety_plus, offsety_minus);
				AddNumber("Z", tskPtr->offsetVector.z, 4, null, offsetz_plus, offsetz_minus);
				AddOption("RESET", bResetOffsetVector); if (bResetOffsetVector) tskPtr->offsetVector.clear();

				if (prec_plus) { if (_manualPlacementPrecision < 10.0f) _manualPlacementPrecision *= 10; }
				if (prec_minus) { if (_manualPlacementPrecision > 0.0001f) _manualPlacementPrecision /= 10; }

				if (offsetx_plus) tskPtr->offsetVector.x += _manualPlacementPrecision;
				if (offsetx_minus) tskPtr->offsetVector.x -= _manualPlacementPrecision;
				if (offsety_plus) tskPtr->offsetVector.y += _manualPlacementPrecision;
				if (offsety_minus) tskPtr->offsetVector.y -= _manualPlacementPrecision;
				if (offsetz_plus) tskPtr->offsetVector.z += _manualPlacementPrecision;
				if (offsetz_minus) tskPtr->offsetVector.z -= _manualPlacementPrecision;

			}
			void OscillateToPoint()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::OscillateToPoint>();

				bool bAngleFreq_plus = false, bAngleFreq_minus = false;
				AddNumber("Angular Frequency", tskPtr->angleFreq, 2, null, bAngleFreq_plus, bAngleFreq_minus);
				if (bAngleFreq_plus) { if (tskPtr->angleFreq < FLT_MAX - 2.0f) tskPtr->angleFreq += 0.01f; }
				if (bAngleFreq_minus) { if (tskPtr->angleFreq > 0.0f) tskPtr->angleFreq -= 0.01f; }

				bool bDampRatio_plus = false, bDampRatio_minus = false;
				AddNumber("Damping Ratio", tskPtr->dampRatio, 2, null, bDampRatio_plus, bDampRatio_minus);
				if (bDampRatio_plus) { if (tskPtr->dampRatio < FLT_MAX - 2.0f) tskPtr->dampRatio += 0.05f; }
				if (bDampRatio_minus) { if (tskPtr->dampRatio > 0.0f) tskPtr->dampRatio -= 0.05f; }

				PAtCoord(tskPtr->destination);
			}
			void OscillateToEntity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::OscillateToEntity>();

				if (tskPtr->targetEntity.Exists())
					World::DrawMarker(MarkerType::DebugSphere, tskPtr->targetEntity.GetOffsetInWorldCoords(tskPtr->offsetVector), Vector3(), Vector3(), Vector3(0.07f, 0.07f, 0.07f), RGBA(177, 33, 193, 210));

				bool bAngleFreq_plus = false, bAngleFreq_minus = false;
				AddNumber("Angular Frequency", tskPtr->angleFreq, 2, null, bAngleFreq_plus, bAngleFreq_minus);
				if (bAngleFreq_plus) { if (tskPtr->angleFreq < FLT_MAX - 2.0f) tskPtr->angleFreq += 0.01f; }
				if (bAngleFreq_minus) { if (tskPtr->angleFreq > 0.0f) tskPtr->angleFreq -= 0.01f; }

				bool bDampRatio_plus = false, bDampRatio_minus = false;
				AddNumber("Damping Ratio", tskPtr->dampRatio, 2, null, bDampRatio_plus, bDampRatio_minus);
				if (bDampRatio_plus) { if (tskPtr->dampRatio < FLT_MAX - 2.0f) tskPtr->dampRatio += 0.05f; }
				if (bDampRatio_minus) { if (tskPtr->dampRatio > 0.0f) tskPtr->dampRatio -= 0.05f; }

				//=========================OFFSET VECTOR======================
				AddBreak("---Destination Offset---");
				bool prec_plus = 0, prec_minus = 0,
					offsetx_plus = 0, offsetx_minus = 0,
					offsety_plus = 0, offsety_minus = 0,
					offsetz_plus = 0, offsetz_minus = 0,
					bResetOffsetVector = 0;

				AddNumber("Scroll Sensitivity", _manualPlacementPrecision, 4, null, prec_minus, prec_plus);
				AddNumber("X", tskPtr->offsetVector.x, 4, null, offsetx_plus, offsetx_minus);
				AddNumber("Y", tskPtr->offsetVector.y, 4, null, offsety_plus, offsety_minus);
				AddNumber("Z", tskPtr->offsetVector.z, 4, null, offsetz_plus, offsetz_minus);
				AddOption("RESET", bResetOffsetVector); if (bResetOffsetVector) tskPtr->offsetVector.clear();

				if (prec_plus) { if (_manualPlacementPrecision < 10.0f) _manualPlacementPrecision *= 10; }
				if (prec_minus) { if (_manualPlacementPrecision > 0.0001f) _manualPlacementPrecision /= 10; }

				if (offsetx_plus) tskPtr->offsetVector.x += _manualPlacementPrecision;
				if (offsetx_minus) tskPtr->offsetVector.x -= _manualPlacementPrecision;
				if (offsety_plus) tskPtr->offsetVector.y += _manualPlacementPrecision;
				if (offsety_minus) tskPtr->offsetVector.y -= _manualPlacementPrecision;
				if (offsetz_plus) tskPtr->offsetVector.z += _manualPlacementPrecision;
				if (offsetz_minus) tskPtr->offsetVector.z -= _manualPlacementPrecision;

				PAtEntity(tskPtr->targetEntity);
			}
			void FreezeInPlace()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::FreezeInPlace>();

				std::vector<std::pair<STSTasks::FreezeInPlace::eFreezeType, std::string>> vFrzTypNames
				{
					{ STSTasks::FreezeInPlace::eFreezeType::FREEZETYPE_FREEZE, "Freeze" },
					{ STSTasks::FreezeInPlace::eFreezeType::FREEZETYPE_UNFREEZE, "Unfreeze" },
					{ STSTasks::FreezeInPlace::eFreezeType::FREEZETYPE_RESETVELOCITY, "Reset Velocity" },
				};

				for (auto& ft : vFrzTypNames)
				{
					bool bFrzTypPressed = false;
					AddTickol(ft.second, tskPtr->freezeType == ft.first, bFrzTypPressed, bFrzTypPressed); if (bFrzTypPressed)
					{
						tskPtr->freezeType = ft.first;
					}
				}

			}
			void SetRotation()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::SetRotation>();

				const GTAentity& thisEntity = SelectedEntity.Handle;
				const Vector3& entityPos = thisEntity.Position_get();
				const Vector3& entityRot = thisEntity.Rotation_get();
				const Vector3& rotForRot = (tskPtr->isRelative ? entityRot : Vector3::Zero()) + tskPtr->rotationValue;
				const Vector3& dirForRot = Vector3::RotationToDirection(rotForRot);
				const Vector3& rotForRoll = Vector3(rotForRot.y + 90.0f, 0.0f, rotForRot.y > 0 ? rotForRot.z - 90.0f : rotForRot.z + 90.0f);
				const Vector3& dirForRoll = Vector3::RotationToDirection(rotForRoll);

				const ModelDimensions& entityMd = thisEntity.ModelDimensions();

				const Vector3& markerPos = entityPos + (dirForRot * (entityMd.Dim1.y + 2.0f));
				const Vector3& markerRot = rotForRot;
				World::DrawMarker(MarkerType::DebugSphere, markerPos, Vector3(), Vector3(), Vector3(0.3f, 0.3f, 0.3f), RGBA(177, 33, 193, 210));
				const Vector3& rollMarkerPos = markerPos + (dirForRoll * 0.3f);
				const Vector3& rollMarkerRot = rotForRoll;
				World::DrawMarker(MarkerType::DebugSphere, rollMarkerPos, Vector3(), Vector3(), Vector3(0.1f, 0.1f, 0.1f), RGBA(0, 0, 0, 255));
				World::DrawLine(entityPos, markerPos, RGBA(177, 33, 193, 210));

				bool bToggleRelativePressed = false;
				AddTickol("Relative", tskPtr->isRelative, bToggleRelativePressed, bToggleRelativePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleRelativePressed) tskPtr->isRelative = !tskPtr->isRelative;

				bool prec_plus = 0, prec_minus = 0,
					rotx_plus = 0, rotx_minus = 0,
					roty_plus = 0, roty_minus = 0,
					rotz_plus = 0, rotz_minus = 0,
					bResetRotVector = 0;

				AddNumber("Scroll Sensitivity", _manualPlacementPrecision, 4, null, prec_minus, prec_plus);
				AddNumber("X", tskPtr->rotationValue.x, 4, null, rotx_plus, rotx_minus);
				AddNumber("Y", tskPtr->rotationValue.y, 4, null, roty_plus, roty_minus);
				AddNumber("Z", tskPtr->rotationValue.z, 4, null, rotz_plus, rotz_minus);
				AddOption("RESET", bResetRotVector); if (bResetRotVector)
				{
					if (tskPtr->isRelative) tskPtr->rotationValue.clear();
					else tskPtr->rotationValue = entityRot;
				}

				if (prec_plus) { if (_manualPlacementPrecision < 10.0f) _manualPlacementPrecision *= 10; }
				if (prec_minus) { if (_manualPlacementPrecision > 0.0001f) _manualPlacementPrecision /= 10; }

				if (rotx_plus && tskPtr->rotationValue.x < 180.0f) tskPtr->rotationValue.x += _manualPlacementPrecision;
				if (rotx_minus && tskPtr->rotationValue.x > -180.0f) tskPtr->rotationValue.x -= _manualPlacementPrecision;
				if (roty_plus && tskPtr->rotationValue.y < 180.0f) tskPtr->rotationValue.y += _manualPlacementPrecision;
				if (roty_minus && tskPtr->rotationValue.y > -180.0f) tskPtr->rotationValue.y -= _manualPlacementPrecision;
				if (rotz_plus && tskPtr->rotationValue.z < 180.0f) tskPtr->rotationValue.z += _manualPlacementPrecision;
				if (rotz_minus && tskPtr->rotationValue.z > -180.0f) tskPtr->rotationValue.z -= _manualPlacementPrecision;
			}
			void ChangeOpacity()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::ChangeOpacity>();

				bool bAlphaLevelResetPressed = false;
				AddTickol("Reset To Default", tskPtr->opacityValue == 269, bAlphaLevelResetPressed, null); if (bAlphaLevelResetPressed)
				{
					tskPtr->opacityValue = 269;
				}

				std::array<BYTE, 5> alphaLevels = { 0, 50, 89, 160, 255 };

				for (auto& lvl : alphaLevels)
				{
					bool bAlphaLevelPressed = false;
					AddTickol(std::to_string((int)(((float)(lvl) / 255.0f) * 100)) + "%", tskPtr->opacityValue == lvl, bAlphaLevelPressed, null); if (bAlphaLevelPressed)
					{
						tskPtr->opacityValue = lvl;
					}
				}

				if (tskPtr->opacityValue >= 0 && tskPtr->opacityValue <= 255)
				{
					AddBreak("---Manual---");
					bool bInputPressed = false, bPlusPressed = false, bMinusPressed = false;
					AddNumber("Level", tskPtr->opacityValue, 0, bInputPressed, bPlusPressed, bMinusPressed);
					if (bPlusPressed) { if (tskPtr->opacityValue < 255) { tskPtr->opacityValue++; } }
					if (bMinusPressed) { if (tskPtr->opacityValue > 0) { tskPtr->opacityValue--; } }
					if (bInputPressed)
					{
						std::string inputStr = Game::InputBox(std::string(), 4U, std::string(), std::to_string(tskPtr->opacityValue));
						if (inputStr.length())
						{
							try
							{
								int inputVal = stoi(inputStr);
								if (inputVal < 0 || inputVal > 255)
									throw;
								tskPtr->opacityValue = inputVal;
							}
							catch (...) { Game::Print::PrintError_InvalidInput(); }
						}
						//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SetArg1Int, std::string(), 5U, std::string(), std::to_string(tskPtr->opacityValue));
						//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->opacityValue);
					}
				}
				else if (tskPtr->opacityValue != 269)
					tskPtr->opacityValue = 255;
			}
			void TriggerFx()
			{
				auto tskPtr = _selectedSTST->GetTypeTask<STSTasks::TriggerFx>();

				const GTAentity& thisEntity = SelectedEntity.Handle;
				World::DrawMarker(MarkerType::DebugSphere, thisEntity.GetOffsetInWorldCoords(tskPtr->posOffset), Vector3(), Vector3(), Vector3(0.1f, 0.1f, 0.1f), RGBA(tskPtr->colour, 190));

				bool bTogglePlayOncePressed = false;
				AddTickol("Play Only Once", !tskPtr->isLoopedTask, bTogglePlayOncePressed, bTogglePlayOncePressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bTogglePlayOncePressed)
				{
					if (tskPtr->isLoopedTask)
					{
						tskPtr->duration = -2;
						tskPtr->isLoopedTask = false;
						Menu::Up();
					}
					else
					{
						tskPtr->duration = 1000;
						tskPtr->isLoopedTask = true;
						Menu::Down();
					}
				}

				if (tskPtr->isLoopedTask)
				{
					bool bDelay_input = false, bDelay_plus = false, bDelay_minus = false;
					AddNumber("Interval (In Seconds)", (float(tskPtr->delay) / 1000), 1, bDelay_input, bDelay_plus, bDelay_minus);
					if (bDelay_plus) { if (tskPtr->delay < INT_MAX) tskPtr->delay += 100; }
					if (bDelay_minus) { if (tskPtr->delay > 0U) tskPtr->delay -= 100; }
					if (bDelay_input)
					{
						std::string inputStr = Game::InputBox("", 7 + 1, "Enter delay/interval in seconds:", std::to_string((float(tskPtr->delay) / 1000)));
						if (inputStr.length() > 0)
						{
							UINT inputVal;
							try
							{
								inputVal = int(stof(inputStr) * 1000);
							}
							catch (std::out_of_range&)
							{
								inputVal = INT_MAX;
							}
							catch (...)
							{
								inputVal = tskPtr->delay;
							}
							inputVal -= (inputVal % 100);
							tskPtr->delay = inputVal;
						}
						//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::ST_TriggerFx_Interval, std::string(), 7U, "Enter delay/interval in seconds:", std::to_string((float(tskPtr->delay) / 1000)));
						//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&tskPtr->delay);
					}
				}

				bool bSize_plus = false, bSize_minus = false;
				AddNumber("Size", tskPtr->scale, 2, null, bSize_plus, bSize_minus);
				if (bSize_plus) { if (tskPtr->scale < FLT_MAX - 1.0f) { tskPtr->scale += 0.02f; } }
				if (bSize_minus) { if (tskPtr->scale > 1.0f - FLT_MAX) { tskPtr->scale -= 0.02f; } }

				AddsettingscolOption("Colour", tskPtr->colour);

				bool bManualPlacementForPosPressed = false;
				AddOption("Adjust Relative Position", bManualPlacementForPosPressed, nullFunc, SUB::SPOONER_VECTOR3_MANUALPLACEMENT); if (bManualPlacementForPosPressed)
				{
					SpoonerVector3ManualPlacementPtrs = { thisEntity, &tskPtr->posOffset, &tskPtr->rotOffset };
				}

				AddBreak("---FX---");
				const auto& fxData = tskPtr->fx.GetFxData();
				for (auto& ef : sub::Ptfx_catind::vPTFX)
				{
					bool bFxNamePressed = false;
					AddTickol(ef.name, fxData.asset == ef.asset && fxData.effect == ef.fx, bFxNamePressed, null); if (bFxNamePressed)
					{
						tskPtr->fx = PTFX::NonLoopedPTFX(ef.asset, ef.fx);
						tskPtr->fx.EasyStart(thisEntity, tskPtr->scale, tskPtr->posOffset, tskPtr->rotOffset, tskPtr->colour);
					}
				}
			}
		}

		void Sub_TaskSequence_TaskList()
		{
			dict.clear();

			if (!SelectedEntity.Handle.Exists())
			{
				Menu::SetSub_previous();
				return;
			}
			SelectedEntity.Handle.RequestControlOnce();
			auto thisEntityIndexInDb = EntityManagement::GetEntityIndexInDb(SelectedEntity);
			bool isThisEntityInDb = thisEntityIndexInDb >= 0;
			if (!isThisEntityInDb)
			{
				Game::Print::PrintBottomLeft("~r~Error:~s~ Entity is not in the Spooner Database");
				addlog(ige::LogType::LOG_WARNING, "Cannot display task list, Entity not in Spooner Database",__FILENAME__);
				Menu::SetSub_previous();
				return;
			}

			AddTitle("Tasks");

			auto& taskSequence = Databases::EntityDb[thisEntityIndexInDb].TaskSequence;
			auto& taskList = taskSequence.AllTasks();
			GTAentity thisEntity = SelectedEntity.Handle;
			EntityType thisEntityType = (EntityType)thisEntity.Type();

			SelectedEntity.TaskSequence = taskSequence;

			bool bStartPressed = false, bStopPressed = false;
			AddLocal("Status", taskSequence.IsActive(), bStartPressed, bStopPressed);
			if (bStartPressed)
			{
				if (!taskList.empty())
				{
					taskSequence.Start();
					Game::Print::PrintBottomLeft("Started a Spooner task sequence.");
				}
				else
				{
					Game::Print::PrintBottomCentre("~r~Error:~s~ Task list is empty.");
					addlog(ige::LogType::LOG_WARNING, "Cannot start tasks, Task list is empty", __FILENAME__);
				}
			}
			else if (bStopPressed)
			{
				taskSequence.Reset(false);
				CLEAR_PED_TASKS_IMMEDIATELY(SelectedEntity.Handle.Handle());
				Game::Print::PrintBottomLeft("Ended a Spooner task sequence.");
			}

			char bMenuUpDown = 0i8;

			for (UINT16 i = 0; i < taskSequence.TaskCount(); i++)
			{
				bool bTaskInListPressed = false;
				AddOption(STSTaskGetName(taskList[i]->type)->second.first, bTaskInListPressed); if (bTaskInListPressed)
				{
					if (taskList[i]->duration != -1) // Has settings
					{
						_selectedSTST = taskList[i];
						Menu::SetSub_delayed = SUB::SPOONER_TASKSEQUENCE_INTASK;
					}
				}

				if (Menu::printingop == *Menu::currentopATM)
				{
					bool bRemoveTaskPressed = false;
					char bMoveTaskPressed = 0i8;
					if (Menu::bit_controller)
					{
						Menu::add_IB(INPUT_SCRIPT_RLEFT, "Remove");
						bRemoveTaskPressed = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RLEFT) != 0;

						Menu::add_IB(INPUT_FRONTEND_RIGHT, std::string());
						Menu::add_IB(INPUT_FRONTEND_LEFT, "Move");
						bMoveTaskPressed = MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Left) ? -1
							: MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Right) ? 1 : 0;
					}
					else
					{
						Menu::add_IB(VirtualKey::B, "Remove");
						bRemoveTaskPressed = IsKeyJustUp(VirtualKey::B);

						Menu::add_IB(INPUT_FRONTEND_RIGHT, std::string());
						Menu::add_IB(INPUT_FRONTEND_LEFT, "Move");
						bMoveTaskPressed = MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Left) ? -1
							: MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Right) ? 1 : 0;
					}
					if (bRemoveTaskPressed) // Remove task
					{
						taskSequence.RemoveTask(i);
						i--;
						//Menu::Up();
					}
					else if (bMoveTaskPressed > 0) // Move task ahead
					{
						taskSequence.SwapTasks(i, i == taskSequence.TaskCount() - 1 ? 0 : i + 1);
						bMenuUpDown = bMoveTaskPressed;
					}
					else if (bMoveTaskPressed < 0) // Move task behind
					{
						taskSequence.SwapTasks(i, i == 0 ? taskSequence.TaskCount() - 1 : i - 1);
						bMenuUpDown = bMoveTaskPressed;
					}
				}

			}

			if (bMenuUpDown > 0) // Move currentop ahead
			{
				if (Menu::currentop == Menu::printingop) // Last task selected
				{
					Menu::Top();
					Menu::Down();
				}
				else
					Menu::Down();
				//bMenuUpDown = 0;
			}
			else if (bMenuUpDown < 0) // Move currentop behind
			{
				if (Menu::currentop == 2) // First task selected
				{
					Menu::Bottom();
					Menu::Up();
				}
				else
					Menu::Up();
				//bMenuUpDown = 0;
			}

			AddOption("ADD NEW", null, nullFunc, SUB::SPOONER_TASKSEQUENCE_ADDTASK);

		}
		void Sub_TaskSequence_AddTask()
		{
			if (!SelectedEntity.Handle.Exists())
			{
				Menu::SetSub_previous();
				return;
			}
			auto thisEntityIndexInDb = EntityManagement::GetEntityIndexInDb(SelectedEntity);
			bool isThisEntityInDb = thisEntityIndexInDb >= 0;
			if (!isThisEntityInDb)
			{
				Menu::SetSub_previous();
				return;
			}

			AddTitle("Add Task");

			auto& thisEntity = Databases::EntityDb[thisEntityIndexInDb];
			auto& taskSequence = thisEntity.TaskSequence;

			for (auto& tn : vSTSTaskTypeNames)
			{
				if (tn.second.second == EntityType::ALL || tn.second.second == thisEntity.Type)
				{
					bool bTaskTypePressed = false;
					AddOption(tn.second.first, bTaskTypePressed); if (bTaskTypePressed)
					{
						taskSequence.AddTask(tn.first);
						SelectedEntity.TaskSequence = taskSequence;
						Menu::SetSub_previous();
						return;
					}
				}
			}
		}
		void Sub_TaskSequence_InTask()
		{
			auto tskPtr = _selectedSTST;
			if (tskPtr == nullptr)
			{
				Menu::SetSub_previous();
				return;
			}
			AddTitle(STSTaskGetName(tskPtr->type)->second.first);

			auto& thisDuration = tskPtr->duration;
			if (thisDuration >= 0) // -1 for tasks with no settings. -2 for tasks with settings but no duration setting.
			{
				bool bDuration_plus = false, bDuration_minus = false, bDuration_input = false;
				AddNumber("Duration (In Seconds)", (float(thisDuration) / 1000), 1, bDuration_input, bDuration_plus, bDuration_minus);
				if (bDuration_plus) { if (thisDuration < INT_MAX) thisDuration += 500; }
				if (bDuration_minus) { if (thisDuration > 0) thisDuration -= 500; }
				if (bDuration_input)
				{
					std::string oldDurationPreText = std::to_string(float(thisDuration - (thisDuration % 500)) / 1000);
					oldDurationPreText = oldDurationPreText.substr(0, oldDurationPreText.find('.') + 2);
					std::string inputStr = Game::InputBox("", 7 + 1, "Enter duration in seconds:", oldDurationPreText);
					if (inputStr.length() > 0)
					{
						int inputVal;
						try
						{
							inputVal = abs(int(stof(inputStr) * 1000));
						}
						catch (std::out_of_range&)
						{
							inputVal = INT_MAX - 100;
						}
						catch (...)
						{
							inputVal = thisDuration;
						}
						inputVal -= (inputVal % 500);
						thisDuration = inputVal;
					}
					//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::ST_Duration, std::string(), 7U, "Enter duration in seconds:", oldDurationPreText);
					//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&thisDuration);
				}

				if (tskPtr->durationAfterLife >= 0)
				{
					bool bInfDurationToggle = false;
					AddTickol("Keep Task Running After Allocated Time", tskPtr->durationAfterLife == 1, bInfDurationToggle, bInfDurationToggle, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bInfDurationToggle) tskPtr->durationAfterLife = tskPtr->durationAfterLife == 1 ? 0 : 1;
				}
			}

			_selectedSTST->submenu();
		}

	}

}




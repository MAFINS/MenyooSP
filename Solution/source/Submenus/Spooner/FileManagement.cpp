/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FileManagement.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Scripting\GTAprop.h"
#include "..\..\Scripting\Model.h"
#include "..\..\Util\StringManip.h"
#include "..\..\Scripting\enums.h"
#include "..\..\Scripting\World.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Util\FileLogger.h"
#include "..\..\Scripting\CustomHelpText.h"
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\ModelNames.h"
#include "..\..\Util\ExePath.h"
#include "..\..\Scripting\Camera.h"

#include "SpoonerEntity.h"
#include "SpoonerMarker.h"
#include "RelationshipManagement.h"
#include "EntityManagement.h"
#include "SpoonerMode.h"
#include "Databases.h"
#include "BlipManagement.h"
#include "MarkerManagement.h"
#include "..\PedComponentChanger.h"
#include "..\PtfxSubs.h"
#include "..\PedAnimation.h"
#include "..\Teleport\TeleMethods.h"

#include <string>
#include <unordered_set>
#include <vector>
#include <pugixml/src/pugixml.hpp>
#include <simpleini\SimpleIni.h>

namespace sub::Spooner
{
	namespace FileManagement
	{
		std::string _oldAudioAlias;

		/*bool Exists(const std::string& fileName, std::string extension = ".xml")
		{
			struct stat buffer;
			return (stat((GetPathffA(Pathff::Spooner, true) + fileName + extension).c_str(), &buffer) == 0);
		}
		bool Rename(const std::string& oldName, const std::string& newName, std::string extension = ".xml")
		{
			if (rename((GetPathffA(Pathff::Spooner, true) + oldName + extension).c_str(), (GetPathffA(Pathff::Spooner, true) + newName + extension).c_str()) == 0)
			{
				return true;
			}
			return false;
		}
		bool Delete(const std::string& fileName, std::string extension = ".xml")
		{
			if (remove((GetPathffA(Pathff::Spooner, true) + fileName + extension).c_str()) == 0)
			{
				return true;
			}
			return false;
		}*/

		void AddEntityToXmlNode(SpoonerEntity& e, pugi::xml_node& nodeEntity)
		{
			//addlog(ige::LogType::LOG_INFO,  "Adding entity " + e.HashName + " of type " + (int)e.Type + " to xml node.", __FILENAME__);

			GTAped myPed = PLAYER_PED_ID();

			const Model& eModel = e.Handle.Model();
			nodeEntity.append_child("ModelHash").text() = int_to_hexstring(eModel.hash, true).c_str();
			nodeEntity.append_child("Type").text() = (int)e.Type;
			nodeEntity.append_child("Dynamic").text() = e.Dynamic;
			nodeEntity.append_child("FrozenPos").text() = e.Handle.IsPositionFrozen();
			if (e.HashName.length() == 0)
				e.HashName = int_to_hexstring(eModel.hash, true);
			nodeEntity.append_child("HashName").text() = e.HashName.c_str();
			nodeEntity.append_child("InitialHandle").text() = e.Handle.Handle();

			// Task sequence for all entity types
			bool bEntHasTaskSequence = !e.TaskSequence.empty();
			bool bEntTaskSequenceIsActive = e.TaskSequence.IsActive();
			if (bEntHasTaskSequence)
			{
				auto nodeEntTaskSeq = nodeEntity.append_child("TaskSequence");
				const auto& vTasks = e.TaskSequence.AllTasks();
				for (auto& task : vTasks)
				{
					auto nodeEntSTSTask = nodeEntTaskSeq.append_child("Task");
					task->GetXmlNode(nodeEntSTSTask);
				}
			}

			if (e.Type == EntityType::PROP)
			{
				auto nodePropStuff = nodeEntity.append_child("ObjectProperties");
				GTAprop eo = e.Handle;

				nodePropStuff.append_child("TextureVariation").text() = e.TextureVariation;
			}
			else if (e.Type == EntityType::PED)
			{
				auto nodePedStuff = nodeEntity.append_child("PedProperties");
				GTAped ep = e.Handle;

				/*auto& nodePedConfigFlags = nodePedStuff.append_child("PedConfigFlags");
				for (UINT16 i = 0; i <= 255; i++)
				{
					nodePedConfigFlags.append_child(("_" + std::to_string(i)).c_str()).text() = (bool)GET_PED_CONFIG_FLAG(ep.Handle(), i, true);
				}*/

				nodePedStuff.append_child("IsStill").text() = e.IsStill;

				nodePedStuff.append_child("CanRagdoll").text() = ep.CanRagdoll_get();

				nodePedStuff.append_child("HasShortHeight").text() = GET_PED_CONFIG_FLAG(ep.Handle(), ePedConfigFlags::_Shrink, false) != 0;

				nodePedStuff.append_child("Armour").text() = ep.Armour_get();

				nodePedStuff.append_child("CurrentWeapon").text() = int_to_hexstring(ep.Weapon_get(), true).c_str();

				auto nodePedProps = nodePedStuff.append_child("PedProps");
				auto nodePedComps = nodePedStuff.append_child("PedComps");
				for (UINT8 i = 0; i <= 9; i++)
				{
					nodePedProps.append_child(("_" + std::to_string(i)).c_str()).text() = (std::to_string(GET_PED_PROP_INDEX(ep.Handle(), i, 0)) + "," + std::to_string(GET_PED_PROP_TEXTURE_INDEX(ep.Handle(), i))).c_str();
				}
				for (UINT8 i = 0; i <= 11; i++)
				{
					nodePedComps.append_child(("_" + std::to_string(i)).c_str()).text() = (std::to_string(GET_PED_DRAWABLE_VARIATION(ep.Handle(), i)) + "," + std::to_string(GET_PED_TEXTURE_VARIATION(ep.Handle(), i))).c_str();
				}

				if (sub::PedHeadFeatures_catind::DoesPedModelSupportHeadFeatures(eModel))
				{
					auto nodePedHeadFeatures = nodePedStuff.append_child("HeadFeatures");

					auto nodePedHeadBlend = nodePedHeadFeatures.append_child("ShapeAndSkinTone");
					const auto& headBlend = ep.HeadBlendData_get();
					nodePedHeadBlend.append_child("ShapeFatherId").text() = headBlend.shapeFirstID;
					nodePedHeadBlend.append_child("ShapeMotherId").text() = headBlend.shapeSecondID;
					nodePedHeadBlend.append_child("ShapeOverrideId").text() = headBlend.shapeThirdID;
					nodePedHeadBlend.append_child("ToneFatherId").text() = headBlend.skinFirstID;
					nodePedHeadBlend.append_child("ToneMotherId").text() = headBlend.skinSecondID;
					nodePedHeadBlend.append_child("ToneOverrideId").text() = headBlend.skinThirdID;
					nodePedHeadBlend.append_child("ShapeVal").text() = headBlend.shapeMix;
					nodePedHeadBlend.append_child("ToneVal").text() = headBlend.skinMix;
					nodePedHeadBlend.append_child("OverrideVal").text() = headBlend.thirdMix;
					nodePedHeadBlend.append_child("IsP").text() = headBlend.isParent;

					if (sub::PedHeadFeatures_catind::vPedHeads.count(ep.Handle()))
					{
						nodePedHeadFeatures.append_attribute("WasInArray") = true;
						auto& pedHead = sub::PedHeadFeatures_catind::vPedHeads[ep.Handle()];
						nodePedHeadFeatures.append_child("HairColour").text() = pedHead.hairColour;
						nodePedHeadFeatures.append_child("HairColourStreaks").text() = pedHead.hairColourStreaks;
						nodePedHeadFeatures.append_child("EyeColour").text() = pedHead.eyeColour;

						auto nodePedFacialFeatures = nodePedHeadFeatures.append_child("FacialFeatures"); //currently returning 0 to xml file for all values
						for (int i = 0; i < pedHead.facialFeatureData.size(); i++)
						{
							addlog(ige::LogType::LOG_DEBUG, "Saving Facial feature " + std::to_string(i) + " as value " + std::to_string(pedHead.facialFeatureData[i]));
							nodePedFacialFeatures.append_child(("_" + std::to_string(i)).c_str()).text() = std::to_string(pedHead.facialFeatureData[i]).c_str();
						}

						auto nodePedHeadOverlays = nodePedHeadFeatures.append_child("Overlays");
						for (int i = 0; i < pedHead.overlayData.size(); i++)
						{
							auto nodePedHeadOverlay = nodePedHeadOverlays.append_child(("_" + std::to_string(i)).c_str());
							nodePedHeadOverlay.append_attribute("index") = GET_PED_HEAD_OVERLAY(ep.Handle(), i);
							nodePedHeadOverlay.append_attribute("colour") = pedHead.overlayData[i].colour;
							nodePedHeadOverlay.append_attribute("colourSecondary") = pedHead.overlayData[i].colourSecondary;
							nodePedHeadOverlay.append_attribute("opacity") = pedHead.overlayData[i].opacity;
						}
					}
					else
					{
						nodePedHeadFeatures.append_attribute("WasInArray") = false;
					}
				}

				if (sub::PedDecals_catind::vPedsAndDecals.count(ep.Handle()))
				{
					auto nodePedTattooLogoDecals = nodePedStuff.append_child("TattooLogoDecals");
					auto& decalsApplied = sub::PedDecals_catind::vPedsAndDecals[ep.Handle()];
					for (auto& decal : decalsApplied)
					{
						auto nodeDecal = nodePedTattooLogoDecals.append_child();
						nodeDecal.append_attribute("collection") = int_to_hexstring(decal.collection, true).c_str();
						nodeDecal.append_attribute("value") = int_to_hexstring(decal.value, true).c_str();
					}
				}

				if (sub::PedDamageTextures_catind::vPedsAndDamagePacks.count(ep.Handle()))
				{
					auto nodePedDamagePacks = nodePedStuff.append_child("DamagePacks");
					auto& dmgPacksApplied = sub::PedDamageTextures_catind::vPedsAndDamagePacks[ep.Handle()];
					for (auto& dpna : dmgPacksApplied)
					{
						nodePedDamagePacks.append_child().text() = dpna.c_str();
					}
				}

				Hash relationshipGroupHash;
				bool bRelationshipGroupAltered = RelationshipManagement::GetPedRelationshipGroup(ep, relationshipGroupHash);
				nodePedStuff.append_child("RelationshipGroupAltered").text() = bRelationshipGroupAltered;
				nodePedStuff.append_child("RelationshipGroup").text() = int_to_hexstring(relationshipGroupHash, true).c_str();

				auto movGrpIter = g_pedList_movGrp.find(ep.Handle());
				if (movGrpIter != g_pedList_movGrp.end())
				{
					nodePedStuff.append_child("MovementGroupName").text() = movGrpIter->second.c_str();
				}
				auto wmovGrpIter = g_pedList_wmovGrp.find(ep.Handle());
				if (wmovGrpIter != g_pedList_wmovGrp.end())
				{
					nodePedStuff.append_child("WeaponMovementGroupName").text() = wmovGrpIter->second.c_str();
				}

				bool isUsingScenario = IS_PED_USING_SCENARIO(ep.Handle(), e.LastAnimation.name.c_str()) != 0;
				bool isPlayingAnim = IS_ENTITY_PLAYING_ANIM(ep.Handle(), e.LastAnimation.dict.c_str(), e.LastAnimation.name.c_str(), 3) != 0;

				if (isUsingScenario && !(bEntTaskSequenceIsActive && e.TaskSequence.ContainsType(STSTaskType::ScenarioAction)))
				{
					nodePedStuff.append_child("ScenarioActive").text() = true;
					nodePedStuff.append_child("ScenarioName").text() = e.LastAnimation.name.c_str();
				}
				else
				{
					nodePedStuff.append_child("ScenarioActive").text() = false;
				}
				if (isPlayingAnim && !(bEntTaskSequenceIsActive && e.TaskSequence.ContainsType(STSTaskType::PlayAnimation)))
				{
					nodePedStuff.append_child("AnimActive").text() = true;
					nodePedStuff.append_child("AnimDict").text() = e.LastAnimation.dict.c_str();
					nodePedStuff.append_child("AnimName").text() = e.LastAnimation.name.c_str();
				}
				else
				{
					nodePedStuff.append_child("AnimActive").text() = false;
				}

				const auto& facialMoodStr = get_ped_facial_mood(ep);
				if (!facialMoodStr.empty())
				{
					nodePedStuff.append_child("FacialMood").text() = facialMoodStr.c_str();
				}

			}
			else if (e.Type == EntityType::VEHICLE)
			{
				auto nodeVehicleStuff = nodeEntity.append_child("VehicleProperties");
				GTAvehicle ev = e.Handle;

				// Colours
				auto nodeVehicleColours = nodeVehicleStuff.append_child("Colours");
				int mod1a, mod1b, mod1c;
				GET_VEHICLE_MOD_COLOR_1(ev.Handle(), &mod1a, &mod1b, &mod1c);
				int mod2a, mod2b;
				GET_VEHICLE_MOD_COLOR_2(ev.Handle(), &mod2a, &mod2b);
				bool isPrimaryColourCustom = ev.IsPrimaryColorCustom();
				bool isSecondaryColourCustom = ev.IsSecondaryColorCustom();
				const auto& cust1 = ev.CustomPrimaryColour_get();
				const auto& cust2 = ev.CustomSecondaryColour_get();
				const auto& tyreSmokeRgb = ev.TyreSmokeColour_get();
				nodeVehicleColours.append_child("Primary").text() = ev.PrimaryColour_get();
				nodeVehicleColours.append_child("Secondary").text() = ev.SecondaryColour_get();
				nodeVehicleColours.append_child("Pearl").text() = ev.PearlescentColour_get();
				nodeVehicleColours.append_child("Rim").text() = ev.RimColour_get();
				nodeVehicleColours.append_child("Mod1_a").text() = mod1a;
				nodeVehicleColours.append_child("Mod1_b").text() = mod1b;
				nodeVehicleColours.append_child("Mod1_c").text() = mod1c;
				nodeVehicleColours.append_child("Mod2_a").text() = mod2a;
				nodeVehicleColours.append_child("Mod2_b").text() = mod2b;
				nodeVehicleColours.append_child("IsPrimaryColourCustom").text() = isPrimaryColourCustom;
				if (isPrimaryColourCustom)
				{
					nodeVehicleColours.append_child("Cust1_R").text() = cust1.R;
					nodeVehicleColours.append_child("Cust1_G").text() = cust1.G;
					nodeVehicleColours.append_child("Cust1_B").text() = cust1.B;
				}
				nodeVehicleColours.append_child("IsSecondaryColourCustom").text() = isSecondaryColourCustom;
				if (isSecondaryColourCustom)
				{
					nodeVehicleColours.append_child("Cust2_R").text() = cust2.R;
					nodeVehicleColours.append_child("Cust2_G").text() = cust2.G;
					nodeVehicleColours.append_child("Cust2_B").text() = cust2.B;
				}
				nodeVehicleColours.append_child("tyreSmoke_R").text() = tyreSmokeRgb.R;
				nodeVehicleColours.append_child("tyreSmoke_G").text() = tyreSmokeRgb.G;
				nodeVehicleColours.append_child("tyreSmoke_B").text() = tyreSmokeRgb.B;
				//if (eModel.IsBennySupportedVehicle()) {
				nodeVehicleColours.append_child("LrInterior").text() = ev.InteriorColour_get();
				nodeVehicleColours.append_child("LrDashboard").text() = ev.DashboardColour_get();
				nodeVehicleColours.append_child("LrXenonHeadlights").text() = ev.HeadlightColour_get();

				// Other stuff
				nodeVehicleStuff.append_child("Livery").text() = ev.Livery_get(); // Livery should be applied before paint is applied
				nodeVehicleStuff.append_child("NumberPlateText").text() = ev.NumberPlateText_get().c_str();
				nodeVehicleStuff.append_child("NumberPlateIndex").text() = ev.NumberPlateTextIndex_get();
				nodeVehicleStuff.append_child("WheelType").text() = ev.WheelType_get();
				nodeVehicleStuff.append_child("WheelsInvisible").text() = are_vehicle_wheels_invisible(ev);
				nodeVehicleStuff.append_child("EngineSoundName").text() = get_vehicle_engine_sound_name(ev).c_str();
				nodeVehicleStuff.append_child("WindowTint").text() = ev.WindowTint_get();
				nodeVehicleStuff.append_child("BulletProofTyres").text() = !ev.CanTyresBurst_get();
				nodeVehicleStuff.append_child("DirtLevel").text() = ev.DirtLevel_get();
				nodeVehicleStuff.append_child("PaintFade").text() = ev.PaintFade_get();
				nodeVehicleStuff.append_child("RoofState").text() = (int)ev.RoofState_get();
				nodeVehicleStuff.append_child("SirenActive").text() = ev.SirenActive_get();
				nodeVehicleStuff.append_child("EngineOn").text() = ev.EngineRunning_get();
				nodeVehicleStuff.append_child("EngineHealth").text() = ev.EngineHealth_get();
				nodeVehicleStuff.append_child("LightsOn").text() = ev.LightsOn_get();
				nodeVehicleStuff.append_child("IsRadioLoud").text() = CAN_VEHICLE_RECEIVE_CB_RADIO(ev.Handle());// != 0;
				nodeVehicleStuff.append_child("LockStatus").text() = (int)ev.LockStatus_get();

				// Neons
				auto nodeVehicleNeons = nodeVehicleStuff.append_child("Neons");
				const auto& neonLightsRgb = ev.NeonLightsColour_get();
				nodeVehicleNeons.append_child("Left").text() = ev.IsNeonLightOn(VehicleNeonLight::Left);
				nodeVehicleNeons.append_child("Right").text() = ev.IsNeonLightOn(VehicleNeonLight::Right);
				nodeVehicleNeons.append_child("Front").text() = ev.IsNeonLightOn(VehicleNeonLight::Front);
				nodeVehicleNeons.append_child("Back").text() = ev.IsNeonLightOn(VehicleNeonLight::Back);
				nodeVehicleNeons.append_child("R").text() = neonLightsRgb.R;
				nodeVehicleNeons.append_child("G").text() = neonLightsRgb.G;
				nodeVehicleNeons.append_child("B").text() = neonLightsRgb.B;

				// Doors
				auto nodeVehicleDoorsOpen = nodeVehicleStuff.append_child("DoorsOpen");
				nodeVehicleDoorsOpen.append_child("BackLeftDoor").text() = ev.IsDoorOpen(VehicleDoor::BackLeftDoor);
				nodeVehicleDoorsOpen.append_child("BackRightDoor").text() = ev.IsDoorOpen(VehicleDoor::BackRightDoor);
				nodeVehicleDoorsOpen.append_child("FrontLeftDoor").text() = ev.IsDoorOpen(VehicleDoor::FrontLeftDoor);
				nodeVehicleDoorsOpen.append_child("FrontRightDoor").text() = ev.IsDoorOpen(VehicleDoor::FrontRightDoor);
				nodeVehicleDoorsOpen.append_child("Hood").text() = ev.IsDoorOpen(VehicleDoor::Hood);
				nodeVehicleDoorsOpen.append_child("Trunk").text() = ev.IsDoorOpen(VehicleDoor::Trunk);
				nodeVehicleDoorsOpen.append_child("Trunk2").text() = ev.IsDoorOpen(VehicleDoor::Trunk2);
				auto nodeVehicleDoorsBroken = nodeVehicleStuff.append_child("DoorsBroken");
				nodeVehicleDoorsBroken.append_child("BackLeftDoor").text() = ev.IsDoorBroken(VehicleDoor::BackLeftDoor);
				nodeVehicleDoorsBroken.append_child("BackRightDoor").text() = ev.IsDoorBroken(VehicleDoor::BackRightDoor);
				nodeVehicleDoorsBroken.append_child("FrontLeftDoor").text() = ev.IsDoorBroken(VehicleDoor::FrontLeftDoor);
				nodeVehicleDoorsBroken.append_child("FrontRightDoor").text() = ev.IsDoorBroken(VehicleDoor::FrontRightDoor);
				nodeVehicleDoorsBroken.append_child("Hood").text() = ev.IsDoorBroken(VehicleDoor::Hood);
				nodeVehicleDoorsBroken.append_child("Trunk").text() = ev.IsDoorBroken(VehicleDoor::Trunk);
				nodeVehicleDoorsBroken.append_child("Trunk2").text() = ev.IsDoorBroken(VehicleDoor::Trunk2);

				// Tyres
				auto nodeVehicleTyresBursted = nodeVehicleStuff.append_child("TyresBursted");
				nodeVehicleTyresBursted.append_child("FrontLeft").text() = ev.IsTyreBursted(0);
				nodeVehicleTyresBursted.append_child("FrontRight").text() = ev.IsTyreBursted(1);
				nodeVehicleTyresBursted.append_child("_2").text() = ev.IsTyreBursted(2);
				nodeVehicleTyresBursted.append_child("_3").text() = ev.IsTyreBursted(3);
				nodeVehicleTyresBursted.append_child("BackLeft").text() = ev.IsTyreBursted(4);
				nodeVehicleTyresBursted.append_child("BackRight").text() = ev.IsTyreBursted(5);
				nodeVehicleTyresBursted.append_child("_6").text() = ev.IsTyreBursted(6);
				nodeVehicleTyresBursted.append_child("_7").text() = ev.IsTyreBursted(7);
				nodeVehicleTyresBursted.append_child("_8").text() = ev.IsTyreBursted(8);

				// Multipliers
				if (g_multList_rpm.count(ev.Handle())) nodeVehicleStuff.append_child("RpmMultiplier").text() = g_multList_rpm[ev.Handle()];
				if (g_multList_torque.count(ev.Handle())) nodeVehicleStuff.append_child("TorqueMultiplier").text() = g_multList_torque[ev.Handle()];
				if (g_multList_maxSpeed.count(ev.Handle())) nodeVehicleStuff.append_child("MaxSpeed").text() = g_multList_maxSpeed[ev.Handle()];
				if (g_multList_headlights.count(ev.Handle())) nodeVehicleStuff.append_child("HeadlightIntensity").text() = g_multList_headlights[ev.Handle()];

				// Extras (modExtras)
				auto nodeVehicleModExtras = nodeVehicleStuff.append_child("ModExtras");
				for (UINT8 i = 0; i < 60; i++)
				{
					if (ev.DoesExtraExist(i)) nodeVehicleModExtras.append_child(("_" + std::to_string(i)).c_str()).text() = ev.ExtraOn_get(i);
				}

				// Mods (customisations)
				auto nodeVehicleMods = nodeVehicleStuff.append_child("Mods");
				for (UINT i = 0; i < vValues_ModSlotNames.size(); i++)
				{
					bool isToggleable = (i >= 17 && i <= 22);
					if (isToggleable) nodeVehicleMods.append_child(("_" + std::to_string(i)).c_str()).text() = ev.IsToggleModOn(i);
					else nodeVehicleMods.append_child(("_" + std::to_string(i)).c_str()).text() = (std::to_string(ev.GetMod(i)) + "," + std::to_string(ev.GetModVariation(i))).c_str();
				}

			}

			// fx lops
			for (auto& ptfxlop : sub::Ptfx_catind::_fxlops)
			{
				if (ptfxlop.entity == e.Handle)
				{
					nodeEntity.append_child("PtfxLopAsset").text() = ptfxlop.asset.c_str();
					nodeEntity.append_child("PtfxLopEffect").text() = ptfxlop.fx.c_str();
					break;
				}
			}

			nodeEntity.append_child("OpacityLevel").text() = e.Handle.Alpha_get();
			nodeEntity.append_child("LodDistance").text() = e.Handle.LodDistance_get();
			nodeEntity.append_child("IsVisible").text() = e.Handle.IsVisible();
			//nodeEntity.append_child("IsDead").text() = e.Handle.IsDead();
			nodeEntity.append_child("MaxHealth").text() = e.Handle.MaxHealth_get();
			nodeEntity.append_child("Health").text() = e.Handle.Health_get();

			nodeEntity.append_child("HasGravity").text() = e.Handle.HasGravity_get();
			nodeEntity.append_child("IsOnFire").text() = e.Handle.IsOnFire();
			nodeEntity.append_child("IsInvincible").text() = e.Handle.IsInvincible();
			nodeEntity.append_child("IsBulletProof").text() = e.Handle.IsBulletProof();
			nodeEntity.append_child("IsCollisionProof").text() = !e.Handle.IsCollisionEnabled_get();
			nodeEntity.append_child("IsExplosionProof").text() = e.Handle.IsExplosionProof();
			nodeEntity.append_child("IsFireProof").text() = e.Handle.IsFireProof();
			nodeEntity.append_child("IsMeleeProof").text() = e.Handle.IsMeleeProof();
			nodeEntity.append_child("IsOnlyDamagedByPlayer").text() = e.Handle.IsOnlyDamagedByPlayer();

			auto nodeEntityPosRot = nodeEntity.append_child("PositionRotation");
			const Vector3& epos = e.Handle.Position_get();
			const Vector3& erot = e.Handle.Rotation_get();
			nodeEntityPosRot.append_child("X").text() = epos.x;
			nodeEntityPosRot.append_child("Y").text() = epos.y;
			nodeEntityPosRot.append_child("Z").text() = epos.z;
			nodeEntityPosRot.append_child("Pitch").text() = erot.x;
			nodeEntityPosRot.append_child("Roll").text() = erot.y;
			nodeEntityPosRot.append_child("Yaw").text() = erot.z;

			auto nodeEntityAttachment = nodeEntity.append_child("Attachment");
			GTAentity attBaseEnt;
			e.AttachmentArgs.isAttached = EntityManagement::GetEntityThisEntityIsAttachedTo(e.Handle, attBaseEnt);
			nodeEntityAttachment.append_attribute("isAttached") = e.AttachmentArgs.isAttached;
			if (e.AttachmentArgs.isAttached)
			{
				/*if (attBaseEnt.Handle() == myPed.Handle())
				{
					nodeEntityAttachment.append_child("AttachedTo").text() = "PLAYER";
				}
				else if (attBaseEnt.Handle() == myPed.CurrentVehicle().Handle())
				{
					nodeEntityAttachment.append_child("AttachedTo").text() = "VEHICLE";
				}
				else*/
				{
					nodeEntityAttachment.append_child("AttachedTo").text() = attBaseEnt.Handle();
				}
				nodeEntityAttachment.append_child("BoneIndex").text() = e.AttachmentArgs.boneIndex;
				nodeEntityAttachment.append_child("X").text() = e.AttachmentArgs.offset.x;
				nodeEntityAttachment.append_child("Y").text() = e.AttachmentArgs.offset.y;
				nodeEntityAttachment.append_child("Z").text() = e.AttachmentArgs.offset.z;
				nodeEntityAttachment.append_child("Pitch").text() = e.AttachmentArgs.rotation.x;
				nodeEntityAttachment.append_child("Roll").text() = e.AttachmentArgs.rotation.y;
				nodeEntityAttachment.append_child("Yaw").text() = e.AttachmentArgs.rotation.z;
			}
		}
		SpoonerEntityWithInitHandle SpawnEntityFromXmlNode(pugi::xml_node& nodeEntity, std::unordered_set<Hash>& vModelHashes)
		{
			bool isPtfxLopAdded = false;
			BOOL bNetworkIsGameInProgress = NETWORK_IS_GAME_IN_PROGRESS();
			SpoonerEntityWithInitHandle e;
			Model eModel = nodeEntity.child("ModelHash").text().as_uint();
			vModelHashes.insert(eModel.hash);
			e.e.Type = (EntityType)nodeEntity.child("Type").text().as_int();
			e.e.Dynamic = nodeEntity.child("Dynamic").text().as_bool();
			bool bFrozenPos = nodeEntity.child("FrozenPos").text().as_bool(!e.e.Dynamic);
			e.e.HashName = nodeEntity.child("HashName").text().as_string();
			if (e.e.HashName.length() == 0)
				e.e.HashName = int_to_hexstring(eModel.hash, true);
			e.initHandle = nodeEntity.child("InitialHandle").text().as_int();

			auto nodeEntityPosRot = nodeEntity.child("PositionRotation");
			Vector3 placingEpos;
			Vector3	placingErot;
			placingEpos.x = nodeEntityPosRot.child("X").text().as_float();
			placingEpos.y = nodeEntityPosRot.child("Y").text().as_float();
			placingEpos.z = nodeEntityPosRot.child("Z").text().as_float();
			placingErot.x = nodeEntityPosRot.child("Pitch").text().as_float();
			placingErot.y = nodeEntityPosRot.child("Roll").text().as_float();
			placingErot.z = nodeEntityPosRot.child("Yaw").text().as_float();


			if (e.e.Type == EntityType::PROP)
			{
				e.e.Handle = World::CreateProp(eModel, placingEpos, placingErot, e.e.Dynamic, false);
				e.e.Handle.FreezePosition(true);

				GTAprop eo = e.e.Handle;

				eo.HasGravity_set(nodeEntity.child("HasGravity").text().as_bool(true));

				auto nodePropStuff = nodeEntity.child("ObjectProperties");

				e.e.TextureVariation = nodePropStuff.child("TextureVariation").text().as_int(-1);
				if (e.e.TextureVariation != -1)
					SET_OBJECT_TINT_INDEX(eo.Handle(), e.e.TextureVariation);
			}
			else if (e.e.Type == EntityType::PED)
			{
				e.e.Handle = World::CreatePed(eModel, placingEpos, placingErot, false);
				e.e.Handle.FreezePosition(true);

				GTAped ep = e.e.Handle;

				ep.HasGravity_set(nodeEntity.child("HasGravity").text().as_bool(true));

				auto nodePedStuff = nodeEntity.child("PedProperties");

				e.e.IsStill = nodePedStuff.child("IsStill") ? nodePedStuff.child("IsStill").text().as_bool() : true;
				ep.BlockPermanentEvents_set(e.e.IsStill);

				ep.CanRagdoll_set(nodePedStuff.child("CanRagdoll").text().as_bool(true));
				SET_PED_RAGDOLL_ON_COLLISION(ep.Handle(), nodePedStuff.child("CanRagdoll").text().as_bool(false));

				if (nodePedStuff.child("HasShortHeight").text().as_bool()) SET_PED_CONFIG_FLAG(ep.Handle(), ePedConfigFlags::_Shrink, 1);

				ep.Armour_set(nodePedStuff.child("Armour").text().as_int());
				ep.Weapon_set(nodePedStuff.child("CurrentWeapon").text().as_uint());
				ep.CanSwitchWeapons_set(false);
				SET_PED_PATH_CAN_USE_CLIMBOVERS(ep.Handle(), true);
				SET_PED_PATH_CAN_USE_LADDERS(ep.Handle(), true);
				SET_PED_PATH_CAN_DROP_FROM_HEIGHT(ep.Handle(), true);
				//SET_PED_PATH_PREFER_TO_AVOID_WATER(ep.Handle(), true);
				//SET_PED_PATH_AVOID_FIRE(ep.Handle(), true);
				SET_PED_COMBAT_ABILITY(ep.Handle(), 2);
				SET_PED_COMBAT_MOVEMENT(ep.Handle(), 2);

				SET_PED_CAN_PLAY_AMBIENT_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_GESTURE_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_VISEME_ANIMS(ep.Handle(), true, TRUE);
				SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(ep.Handle(), true);

				auto nodePedProps = nodePedStuff.child("PedProps");
				auto nodePedComps = nodePedStuff.child("PedComps");
				for (auto nodePedCompsObject = nodePedComps.first_child(); nodePedCompsObject; nodePedCompsObject = nodePedCompsObject.next_sibling())
				{
					int pedCompId = stoi(std::string(nodePedCompsObject.name()).substr(1));
					std::string pedCompIdValueStr = nodePedCompsObject.text().as_string();

					SET_PED_COMPONENT_VARIATION(ep.Handle(), pedCompId, stoi(pedCompIdValueStr.substr(0, pedCompIdValueStr.find(","))), stoi(pedCompIdValueStr.substr(pedCompIdValueStr.find(",") + 1)), 0);
				}
				for (auto nodePedPropsObject = nodePedProps.first_child(); nodePedPropsObject; nodePedPropsObject = nodePedPropsObject.next_sibling())
				{
					int pedPropId = stoi(std::string(nodePedPropsObject.name()).substr(1));
					std::string pedPropIdValueStr = nodePedPropsObject.text().as_string();

					SET_PED_PROP_INDEX(ep.Handle(), pedPropId, stoi(pedPropIdValueStr.substr(0, pedPropIdValueStr.find(","))), stoi(pedPropIdValueStr.substr(pedPropIdValueStr.find(",") + 1)), bNetworkIsGameInProgress, 0);
				}

				auto nodePedConfigFlags = nodePedStuff.child("PedConfigFlags"); // Only if the node exists
				for (auto nodePedConfigFlagsObject = nodePedConfigFlags.first_child(); nodePedConfigFlagsObject; nodePedConfigFlagsObject = nodePedConfigFlagsObject.next_sibling())
				{
					SET_PED_CONFIG_FLAG(ep.Handle(), stoi(std::string(nodePedConfigFlagsObject.name()).substr(1)), nodePedConfigFlagsObject.text().as_bool());
				}

				auto nodePedHeadFeatures = nodePedStuff.child("HeadFeatures");
				if (sub::PedHeadFeatures_catind::DoesPedModelSupportHeadFeatures(eModel) && nodePedHeadFeatures)
				{
					auto nodePedHeadBlend = nodePedHeadFeatures.child("ShapeAndSkinTone");
					PED::SET_PED_HEAD_BLEND_DATA(ep.Handle(), 0, 0, 0, 1, 1, 1, 0.0f, 0.0f, 0.0f, false);
					PedHeadBlendData headBlend;
					headBlend.shapeFirstID = nodePedHeadBlend.child("ShapeFatherId").text().as_int();
					headBlend.shapeSecondID = nodePedHeadBlend.child("ShapeMotherId").text().as_int();
					headBlend.shapeThirdID = nodePedHeadBlend.child("ShapeOverrideId").text().as_int();
					headBlend.skinFirstID = nodePedHeadBlend.child("ToneFatherId").text().as_int();
					headBlend.skinSecondID = nodePedHeadBlend.child("ToneMotherId").text().as_int();
					headBlend.skinThirdID = nodePedHeadBlend.child("ToneOverrideId").text().as_int();
					headBlend.shapeMix = nodePedHeadBlend.child("ShapeVal").text().as_float();
					headBlend.skinMix = nodePedHeadBlend.child("ToneVal").text().as_float();
					headBlend.thirdMix = nodePedHeadBlend.child("OverrideVal").text().as_float();
					headBlend.isParent = nodePedHeadBlend.child("IsP").text().as_int();
					ep.HeadBlendData_set(headBlend);

					if (nodePedHeadFeatures.attribute("WasInArray").as_bool())
					{
						sub::PedHeadFeatures_catind::sPedHeadFeatures pedHead;
						pedHead.hairColour = nodePedHeadFeatures.child("HairColour").text().as_int();
						pedHead.hairColourStreaks = nodePedHeadFeatures.child("HairColourStreaks").text().as_int();
						pedHead.eyeColour = nodePedHeadFeatures.child("EyeColour").text().as_int();

						SET_PED_HAIR_TINT(ep.Handle(), pedHead.hairColour, pedHead.hairColourStreaks);
						SET_HEAD_BLEND_EYE_COLOR(ep.Handle(), SYSTEM::ROUND((float)pedHead.eyeColour)); // Sjaak says so

						auto nodePedFacialFeatures = nodePedHeadFeatures.child("FacialFeatures");
						int ii = 0;
						for (auto nodePedFacialFeature = nodePedFacialFeatures.first_child(); nodePedFacialFeature; nodePedFacialFeature = nodePedFacialFeature.next_sibling())
						{
							ii = stoi(std::string(nodePedFacialFeature.name()).substr(1));
							pedHead.facialFeatureData[ii] = nodePedFacialFeature.text().as_float();
							SET_PED_MICRO_MORPH(ep.Handle(), ii, pedHead.facialFeatureData[ii]);
						}

						auto nodePedHeadOverlays = nodePedHeadFeatures.child("Overlays");
						ii = 0;
						for (auto nodePedHeadOverlay = nodePedHeadOverlays.first_child(); nodePedHeadOverlay; nodePedHeadOverlay = nodePedHeadOverlay.next_sibling())
						{
							ii = stoi(std::string(nodePedHeadOverlay.name()).substr(1));
							auto overlayData_index = nodePedHeadOverlay.attribute("index").as_int();
							pedHead.overlayData[ii].colour = nodePedHeadOverlay.attribute("colour").as_int();
							pedHead.overlayData[ii].colourSecondary = nodePedHeadOverlay.attribute("colourSecondary").as_int();
							pedHead.overlayData[ii].opacity = nodePedHeadOverlay.attribute("opacity").as_float();
							SET_PED_HEAD_OVERLAY(ep.Handle(), ii, overlayData_index, pedHead.overlayData[ii].opacity);
							SET_PED_HEAD_OVERLAY_TINT(ep.Handle(), ii, sub::PedHeadFeatures_catind::GetPedHeadOverlayColourType((PedHeadOverlay)ii), pedHead.overlayData[ii].colour, pedHead.overlayData[ii].colourSecondary);
						}
						sub::PedHeadFeatures_catind::vPedHeads[ep.Handle()] = pedHead;
					}
				}

				auto nodePedTattooLogoDecals = nodePedStuff.child("TattooLogoDecals");
				if (nodePedTattooLogoDecals)
				{
					auto& decalsApplied = sub::PedDecals_catind::vPedsAndDecals[ep.Handle()];
					for (auto nodeDecal = nodePedTattooLogoDecals.first_child(); nodeDecal; nodeDecal = nodeDecal.next_sibling())
					{
						sub::PedDecals_catind::PedDecalValue decal(
							nodeDecal.attribute("collection").as_uint(),
							nodeDecal.attribute("value").as_uint()
						);
						decalsApplied.push_back(decal);
						ADD_PED_DECORATION_FROM_HASHES(ep.Handle(), decal.collection, decal.value);
					}
				}

				auto nodePedDamagePacks = nodePedStuff.child("DamagePacks");
				if (nodePedDamagePacks)
				{
					auto& dmgPacksApplied = sub::PedDamageTextures_catind::vPedsAndDamagePacks[ep.Handle()];
					for (auto nodePedDamagePack = nodePedDamagePacks.first_child(); nodePedDamagePack; nodePedDamagePack = nodePedDamagePack.next_sibling())
					{
						const std::string dpnta = nodePedDamagePack.text().as_string();
						ep.ApplyDamagePack(dpnta, 1.0f, 1.0f);
						dmgPacksApplied.push_back(dpnta);
					}
				}

				bool bRelationshipGroupAltered = nodePedStuff.child("RelationshipGroupAltered").text().as_bool();
				Hash relationshipGroupHash = nodePedStuff.child("RelationshipGroup").text().as_uint();
				RelationshipManagement::SetPedRelationshipGroup(ep, relationshipGroupHash);

				auto nodeMovGrpName = nodePedStuff.child("MovementGroupName");
				if (nodeMovGrpName)
				{
					std::string movGrpName = nodeMovGrpName.text().as_string();
					//set_ped_movement_clipset(ep, movGrpName);
					Game::RequestAnimSet(movGrpName);
					SET_PED_MOVEMENT_CLIPSET(ep.Handle(), movGrpName.c_str(), 0x3E800000);
					g_pedList_movGrp[ep.Handle()] = movGrpName;
				}
				auto nodeWmovGrpName = nodePedStuff.child("WeaponMovementGroupName");
				if (nodeWmovGrpName)
				{
					std::string wmovGrpName = nodeWmovGrpName.text().as_string();
					//set_ped_weapon_movement_clipset(ep, wmovGrpName);
					Game::RequestAnimSet(wmovGrpName);
					SET_PED_WEAPON_MOVEMENT_CLIPSET(ep.Handle(), wmovGrpName.c_str());
					g_pedList_wmovGrp[ep.Handle()] = wmovGrpName;
				}
				if (nodeMovGrpName || nodeWmovGrpName)
				{
					WAIT(30);
					const Vector3& coord = ep.Position_get();
					SET_ENTITY_COORDS(ep.Handle(), coord.x, coord.y, coord.z + 0.05f, 0, 0, 0, 1);
					FREEZE_ENTITY_POSITION(ep.Handle(), !bFrozenPos);
				}

				bool isUsingScenario = nodePedStuff.child("ScenarioActive").text().as_bool();
				bool isUsingAnim = nodePedStuff.child("AnimActive").text().as_bool();

				if (isUsingScenario)
				{
					e.e.LastAnimation.name = nodePedStuff.child("ScenarioName").text().as_string();
					ep.Task().StartScenario(e.e.LastAnimation.name);
				}
				if (isUsingAnim)
				{
					e.e.LastAnimation.dict = nodePedStuff.child("AnimDict").text().as_string();
					e.e.LastAnimation.name = nodePedStuff.child("AnimName").text().as_string();
					Game::RequestAnimDict(e.e.LastAnimation.dict, 1800);
					ep.Task().PlayAnimation(e.e.LastAnimation.dict, e.e.LastAnimation.name);
				}

				auto nodeFacialMood = nodePedStuff.child("FacialMood");
				if (nodeFacialMood)
				{
					set_ped_facial_mood(ep, nodeFacialMood.text().as_string());
				}

				if (!isPtfxLopAdded)
				{
					auto nodePtfxLopAsset = nodePedStuff.child("PtfxLopAsset");
					auto nodePtfxLopEffect = nodePedStuff.child("PtfxLopEffect");
					if (nodePtfxLopAsset || nodePtfxLopEffect)
					{
						sub::Ptfx_catind::PtfxS ptfxLopFx;
						ptfxLopFx.asset = nodePtfxLopAsset.text().as_string();
						ptfxLopFx.fx = nodePtfxLopEffect.text().as_string();
						sub::Ptfx_catind::AddEntityToPtfxLops(ptfxLopFx, ep);
						isPtfxLopAdded = true;
					}
				}

			}
			else if (e.e.Type == EntityType::VEHICLE)
			{
				e.e.Handle = World::CreateVehicle(eModel, placingEpos, placingErot, false);
				e.e.Handle.FreezePosition(true);

				GTAvehicle ev = e.e.Handle;

				ev.HasGravity_set(nodeEntity.child("HasGravity").text().as_bool(true));

				auto nodeVehicleStuff = nodeEntity.child("VehicleProperties");

				SET_VEHICLE_MOD_KIT(ev.Handle(), 0);
				ev.Livery_set(nodeVehicleStuff.child("Livery").text().as_int()); // Livery should be applied before paint is applied
				// Colours
				auto nodeVehicleColours = nodeVehicleStuff.child("Colours");
				int mod1a = nodeVehicleColours.child("Mod1_a").text().as_int();
				int mod1b = nodeVehicleColours.child("Mod1_b").text().as_int();
				int mod1c = nodeVehicleColours.child("Mod1_c").text().as_int();
				SET_VEHICLE_MOD_COLOR_1(ev.Handle(), mod1a, mod1b, mod1c);
				int mod2a = nodeVehicleColours.child("Mod2_a").text().as_int();
				int mod2b = nodeVehicleColours.child("Mod2_b").text().as_int();
				SET_VEHICLE_MOD_COLOR_2(ev.Handle(), mod2a, mod2b);
				ev.PrimaryColour_set(nodeVehicleColours.child("Primary").text().as_int());
				ev.SecondaryColour_set(nodeVehicleColours.child("Secondary").text().as_int());
				ev.PearlescentColour_set(nodeVehicleColours.child("Pearl").text().as_int());
				ev.RimColour_set(nodeVehicleColours.child("Rim").text().as_int());
				bool isPrimaryColourCustom = nodeVehicleColours.child("IsPrimaryColourCustom").text().as_bool();
				bool isSecondaryColourCustom = nodeVehicleColours.child("IsSecondaryColourCustom").text().as_bool();
				if (isPrimaryColourCustom)
				{
					RgbS cust1;
					cust1.R = nodeVehicleColours.child("Cust1_R").text().as_int();
					cust1.G = nodeVehicleColours.child("Cust1_G").text().as_int();
					cust1.B = nodeVehicleColours.child("Cust1_B").text().as_int();
					ev.CustomPrimaryColour_set(cust1);
				}
				if (isSecondaryColourCustom)
				{
					RgbS cust2;
					cust2.R = nodeVehicleColours.child("Cust2_R").text().as_int();
					cust2.G = nodeVehicleColours.child("Cust2_G").text().as_int();
					cust2.B = nodeVehicleColours.child("Cust2_B").text().as_int();
					ev.CustomSecondaryColour_set(cust2);
				}
				//if (eModel.IsBennySupportedVehicle()) {
				ev.InteriorColour_set(nodeVehicleColours.child("LrInterior").text().as_int());
				ev.DashboardColour_set(nodeVehicleColours.child("LrDashboard").text().as_int());
				ev.HeadlightColour_set(nodeVehicleColours.child("LrXenonHeadlights").text().as_int());

				// Other stuff
				ev.NumberPlateText_set(nodeVehicleStuff.child("NumberPlateText").text().as_string());
				ev.NumberPlateTextIndex_set(nodeVehicleStuff.child("NumberPlateIndex").text().as_int());
				ev.WheelType_set(nodeVehicleStuff.child("WheelType").text().as_int());
				ev.WindowTint_set(nodeVehicleStuff.child("WindowTint").text().as_int());
				ev.CanTyresBurst_set(!nodeVehicleStuff.child("BulletProofTyres").text().as_bool());
				ev.DirtLevel_set(nodeVehicleStuff.child("DirtLevel").text().as_float());
				ev.PaintFade_set(nodeVehicleStuff.child("PaintFade").text().as_float());
				ev.RoofState_set((VehicleRoofState)nodeVehicleStuff.child("RoofState").text().as_int());
				ev.SirenActive_set(nodeVehicleStuff.child("SirenActive").text().as_bool());
				if (nodeVehicleStuff.child("EngineOn")) ev.EngineRunning_set(nodeVehicleStuff.child("EngineOn").text().as_bool());
				if (nodeVehicleStuff.child("EngineHealth")) ev.EngineHealth_set(nodeVehicleStuff.child("EngineHealth").text().as_int());
				if (nodeVehicleStuff.child("LightsOn")) ev.LightsOn_set(nodeVehicleStuff.child("LightsOn").text().as_bool());
				if (nodeVehicleStuff.child("IsRadioLoud").text().as_int(0))
				{
					SET_VEHICLE_RADIO_LOUD(ev.Handle(), nodeVehicleStuff.child("IsRadioLoud").text().as_int());
					SET_VEHICLE_RADIO_ENABLED(ev.Handle(), true);
				}
				ev.LockStatus_set((VehicleLockStatus)nodeVehicleStuff.child("LockStatus").text().as_int());

				// Neons
				auto nodeVehicleNeons = nodeVehicleStuff.child("Neons");
				RgbS neonLightsRgb;
				ev.SetNeonLightOn(VehicleNeonLight::Left, nodeVehicleNeons.child("Left").text().as_bool());
				ev.SetNeonLightOn(VehicleNeonLight::Right, nodeVehicleNeons.child("Right").text().as_bool());
				ev.SetNeonLightOn(VehicleNeonLight::Front, nodeVehicleNeons.child("Front").text().as_bool());
				ev.SetNeonLightOn(VehicleNeonLight::Back, nodeVehicleNeons.child("Back").text().as_bool());
				neonLightsRgb.R = nodeVehicleNeons.child("R").text().as_int();
				neonLightsRgb.G = nodeVehicleNeons.child("G").text().as_int();
				neonLightsRgb.B = nodeVehicleNeons.child("B").text().as_int();
				ev.NeonLightsColour_set(neonLightsRgb);

				// Extras (modExtras)
				auto nodeVehicleModExtras = nodeVehicleStuff.child("ModExtras");
				for (auto nodeVehicleModExtrasObject = nodeVehicleModExtras.first_child(); nodeVehicleModExtrasObject; nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling())
				{
					ev.ExtraOn_set(stoi(std::string(nodeVehicleModExtrasObject.name()).substr(1)), nodeVehicleModExtrasObject.text().as_bool());
				}

				// Mods (customisations)
				auto nodeVehicleMods = nodeVehicleStuff.child("Mods");
				for (auto nodeVehicleModsObject = nodeVehicleMods.first_child(); nodeVehicleModsObject; nodeVehicleModsObject = nodeVehicleModsObject.next_sibling())
				{
					int modType = stoi(std::string(nodeVehicleModsObject.name()).substr(1));
					std::string modValueStr = nodeVehicleModsObject.text().as_string();
					if (modValueStr.find(",") == std::string::npos) // isToggleable
					{
						ev.ToggleMod(modType, nodeVehicleModsObject.text().as_bool());
					}
					else
					{
						ev.SetMod(modType, stoi(modValueStr.substr(0, modValueStr.find(","))), stoi(modValueStr.substr(modValueStr.find(",") + 1)));
					}
				}

				// Tyre smoke colour
				RgbS tyreSmokeRgb;
				tyreSmokeRgb.R = nodeVehicleColours.child("tyreSmoke_R").text().as_int();
				tyreSmokeRgb.G = nodeVehicleColours.child("tyreSmoke_G").text().as_int();
				tyreSmokeRgb.B = nodeVehicleColours.child("tyreSmoke_B").text().as_int();
				ev.TyreSmokeColour_set(tyreSmokeRgb);

				auto nodeVehicleDoorsOpen = nodeVehicleStuff.child("DoorsOpen");
				if (nodeVehicleDoorsOpen)
				{
					nodeVehicleDoorsOpen.child("BackLeftDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::BackLeftDoor, false, true) : ev.CloseDoor(VehicleDoor::BackLeftDoor, true);
					nodeVehicleDoorsOpen.child("BackRightDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::BackRightDoor, false, true) : ev.CloseDoor(VehicleDoor::BackRightDoor, true);
					nodeVehicleDoorsOpen.child("FrontLeftDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::FrontLeftDoor, false, true) : ev.CloseDoor(VehicleDoor::FrontLeftDoor, true);
					nodeVehicleDoorsOpen.child("FrontRightDoor").text().as_bool() ? ev.OpenDoor(VehicleDoor::FrontRightDoor, false, true) : ev.CloseDoor(VehicleDoor::FrontRightDoor, true);
					nodeVehicleDoorsOpen.child("Hood").text().as_bool() ? ev.OpenDoor(VehicleDoor::Hood, false, true) : ev.CloseDoor(VehicleDoor::Hood, true);
					nodeVehicleDoorsOpen.child("Trunk").text().as_bool() ? ev.OpenDoor(VehicleDoor::Trunk, false, true) : ev.CloseDoor(VehicleDoor::Trunk, true);
					nodeVehicleDoorsOpen.child("Trunk2").text().as_bool() ? ev.OpenDoor(VehicleDoor::Trunk2, false, true) : ev.CloseDoor(VehicleDoor::Trunk2, true);
				}
				auto nodeVehicleDoorsBroken = nodeVehicleStuff.child("DoorsBroken");
				if (nodeVehicleDoorsBroken)
				{
					if (nodeVehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::BackLeftDoor, true);
					if (nodeVehicleDoorsBroken.child("BackRightDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::BackRightDoor, true);
					if (nodeVehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::FrontLeftDoor, true);
					if (nodeVehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) ev.BreakDoor(VehicleDoor::FrontRightDoor, true);
					if (nodeVehicleDoorsBroken.child("Hood").text().as_bool()) ev.BreakDoor(VehicleDoor::Hood, true);
					if (nodeVehicleDoorsBroken.child("Trunk").text().as_bool()) ev.BreakDoor(VehicleDoor::Trunk, true);
					if (nodeVehicleDoorsBroken.child("Trunk2").text().as_bool()) ev.BreakDoor(VehicleDoor::Trunk2, true);
				}

				// Tyres
				auto nodeVehicleTyresBursted = nodeVehicleStuff.child("TyresBursted");
				if (nodeVehicleTyresBursted)
				{
					if (nodeVehicleTyresBursted.child("FrontLeft").text().as_bool()) ev.BurstTyre(0);
					if (nodeVehicleTyresBursted.child("FrontRight").text().as_bool()) ev.BurstTyre(1);
					if (nodeVehicleTyresBursted.child("_2").text().as_bool()) ev.BurstTyre(2);
					if (nodeVehicleTyresBursted.child("_3").text().as_bool()) ev.BurstTyre(3);
					if (nodeVehicleTyresBursted.child("BackLeft").text().as_bool()) ev.BurstTyre(4);
					if (nodeVehicleTyresBursted.child("BackRight").text().as_bool()) ev.BurstTyre(5);
					if (nodeVehicleTyresBursted.child("_6").text().as_bool()) ev.BurstTyre(6);
					if (nodeVehicleTyresBursted.child("_7").text().as_bool()) ev.BurstTyre(7);
					if (nodeVehicleTyresBursted.child("_8").text().as_bool()) ev.BurstTyre(8);
				}

				if (nodeVehicleStuff.child("WheelsInvisible").text().as_bool()) set_vehicle_wheels_invisible(ev, true);
				std::string engSoundName = nodeVehicleStuff.child("EngineSoundName").text().as_string();
				if (engSoundName.length()) set_vehicle_engine_sound_name(ev, engSoundName);

				// Multipliers
				auto nodeVehicleRpmMultiplier = nodeVehicleStuff.child("RpmMultiplier");
				auto nodeVehicleTorqueMultiplier = nodeVehicleStuff.child("TorqueMultiplier");
				auto nodeVehicleMaxSpeed = nodeVehicleStuff.child("MaxSpeed");
				auto nodeVehicleHeadlightIntensity = nodeVehicleStuff.child("HeadlightIntensity");
				if (nodeVehicleRpmMultiplier)
				{
					MODIFY_VEHICLE_TOP_SPEED(ev.Handle(), nodeVehicleRpmMultiplier.text().as_float());
					g_multList_rpm[ev.Handle()] = nodeVehicleRpmMultiplier.text().as_float();
				}
				if (nodeVehicleTorqueMultiplier)
				{
					SET_VEHICLE_CHEAT_POWER_INCREASE(ev.Handle(), nodeVehicleTorqueMultiplier.text().as_float());
					g_multList_torque[ev.Handle()] = nodeVehicleTorqueMultiplier.text().as_float();
				}
				if (nodeVehicleMaxSpeed)
				{
					SET_ENTITY_MAX_SPEED(ev.Handle(), nodeVehicleMaxSpeed.text().as_float());
					g_multList_maxSpeed[ev.Handle()] = nodeVehicleMaxSpeed.text().as_float();
				}
				if (nodeVehicleHeadlightIntensity)
				{
					SET_VEHICLE_LIGHT_MULTIPLIER(ev.Handle(), nodeVehicleHeadlightIntensity.text().as_float());
					g_multList_headlights[ev.Handle()] = nodeVehicleHeadlightIntensity.text().as_float();
				}

			}

			// Task sequence for all entity types
			auto nodeEntTaskSeq = nodeEntity.child("PedProperties").child("TaskSequence");
			if (!nodeEntTaskSeq) nodeEntTaskSeq = nodeEntity.child("TaskSequence");
			for (auto nodeEntSTSTask = nodeEntTaskSeq.first_child(); nodeEntSTSTask; nodeEntSTSTask = nodeEntSTSTask.next_sibling())
			{
				const STSTaskType& stsTaskType = (STSTaskType)nodeEntSTSTask.child("Type").text().as_uint();
				STSTask* stsTaskPtr = e.e.TaskSequence.AddTask(stsTaskType);
				if (stsTaskPtr != nullptr)
				{
					stsTaskPtr->ImportXmlNode(nodeEntSTSTask);
				}
			}

			if (!isPtfxLopAdded)
			{
				auto nodePtfxLopAsset = nodeEntity.child("PtfxLopAsset");
				auto nodePtfxLopEffect = nodeEntity.child("PtfxLopEffect");
				if (nodePtfxLopAsset || nodePtfxLopEffect)
				{
					sub::Ptfx_catind::PtfxS ptfxLopFx;
					ptfxLopFx.asset = nodePtfxLopAsset.text().as_string();
					ptfxLopFx.fx = nodePtfxLopEffect.text().as_string();
					sub::Ptfx_catind::AddEntityToPtfxLops(ptfxLopFx, e.e.Handle);
					isPtfxLopAdded = true;
				}
			}

			int opacityLevel = nodeEntity.child("OpacityLevel").text().as_int(255);
			if (opacityLevel < 255) e.e.Handle.Alpha_set(opacityLevel);
			e.e.Handle.LodDistance_set(nodeEntity.child("LodDistance").text().as_int());
			//e.e.Handle.SetVisible(nodeEntity.child("IsVisible").text().as_bool());
			//nodeEntity.child("IsDead").text()
			if (nodeEntity.child("MaxHealth")) e.e.Handle.MaxHealth_set(nodeEntity.child("MaxHealth").text().as_int());
			if (nodeEntity.child("Health")) e.e.Handle.Health_set(nodeEntity.child("Health").text().as_int());

			e.e.Handle.SetOnFire(nodeEntity.child("IsOnFire").text().as_bool());
			e.e.Handle.SetInvincible(nodeEntity.child("IsInvincible").text().as_bool());
			e.e.Handle.SetBulletProof(nodeEntity.child("IsBulletProof").text().as_bool());
			e.e.Handle.Dynamic_set(false);
			e.e.Handle.FreezePosition(true);
			e.e.Handle.Dynamic_set(e.e.Dynamic);
			e.e.Handle.FreezePosition(bFrozenPos);
			e.e.Handle.SetExplosionProof(nodeEntity.child("IsExplosionProof").text().as_bool());
			e.e.Handle.SetFireProof(nodeEntity.child("IsFireProof").text().as_bool());
			e.e.Handle.SetMeleeProof(nodeEntity.child("IsMeleeProof").text().as_bool());
			e.e.Handle.SetOnlyDamagedByPlayer(nodeEntity.child("IsOnlyDamagedByPlayer").text().as_bool());

			eModel.LoadCollision(100);
			e.e.Handle.IsCollisionEnabled_set(!nodeEntity.child("IsCollisionProof").text().as_bool());
			e.e.Handle.SetVisible(nodeEntity.child("IsVisible").text().as_bool());

			auto nodeEntityAttachment = nodeEntity.child("Attachment");
			e.e.AttachmentArgs.isAttached = nodeEntityAttachment.attribute("isAttached").as_bool();
			if (e.e.AttachmentArgs.isAttached)
			{
				std::string attachedToHandleStr = nodeEntityAttachment.child("AttachedTo").text().as_string();
				if (attachedToHandleStr == "PLAYER")
				{
					e.attachedToHandle = PLAYER_PED_ID();
				}
				else if (attachedToHandleStr == "VEHICLE")
				{
					if (DOES_ENTITY_EXIST(g_myVeh)) e.attachedToHandle = g_myVeh;
					else e.e.AttachmentArgs.isAttached = false;
				}
				else
				{
					e.attachedToHandle = nodeEntityAttachment.child("AttachedTo").text().as_int();//stoi(attachedToHandleStr);
				}
				e.e.AttachmentArgs.boneIndex = nodeEntityAttachment.child("BoneIndex").text().as_int();
				e.e.AttachmentArgs.offset.x = nodeEntityAttachment.child("X").text().as_float();
				e.e.AttachmentArgs.offset.y = nodeEntityAttachment.child("Y").text().as_float();
				e.e.AttachmentArgs.offset.z = nodeEntityAttachment.child("Z").text().as_float();
				e.e.AttachmentArgs.rotation.x = nodeEntityAttachment.child("Pitch").text().as_float();
				e.e.AttachmentArgs.rotation.y = nodeEntityAttachment.child("Roll").text().as_float();
				e.e.AttachmentArgs.rotation.z = nodeEntityAttachment.child("Yaw").text().as_float();
			}

			SET_ENTITY_LIGHTS(e.e.Handle.Handle(), 0); // Someone pls explan. 0 1 0 1 0 1 0 1

			return e;
		}

		void AddMarkerToXmlNode(SpoonerMarker& m, pugi::xml_node& nodeMarker)
		{
			addlog(ige::LogType::LOG_INFO,  "Adding marker " + m.m_name + " of type " + std::to_string(m.m_type) + "to xml node.", __FILENAME__);

			nodeMarker.append_child("Name").text() = m.m_name.c_str();
			nodeMarker.append_child("InitialHandle").text() = m.m_id;
			nodeMarker.append_child("Type").text() = m.m_type;
			nodeMarker.append_child("Scale").text() = m.m_scale;
			nodeMarker.append_child("ShowName").text() = m.m_showName;
			nodeMarker.append_child("RotateContinuously").text() = m.m_rotateContinuously;
			nodeMarker.append_child("AllowVehicles").text() = m.m_allowVehicles;

			auto nodeColour = nodeMarker.append_child("Colour");
			nodeColour.append_attribute("R") = m.m_colour.R;
			nodeColour.append_attribute("G") = m.m_colour.G;
			nodeColour.append_attribute("B") = m.m_colour.B;
			nodeColour.append_attribute("A") = m.m_colour.A;

			auto nodePosition = nodeMarker.append_child("Position");

			auto nodePositionPos = nodePosition.append_child("Position");
			nodePositionPos.append_attribute("X") = m.m_position.x;
			nodePositionPos.append_attribute("Y") = m.m_position.y;
			nodePositionPos.append_attribute("Z") = m.m_position.z;

			auto nodePositionRot = nodePosition.append_child("Rotation");
			nodePositionRot.append_attribute("X") = m.m_rotation.x;
			nodePositionRot.append_attribute("Y") = m.m_rotation.y;
			nodePositionRot.append_attribute("Z") = m.m_rotation.z;

			if (m.m_attachmentArgs.attachedTo.Exists())
			{
				auto nodePositionAttachment = nodePosition.append_child("Attachment");
				nodePositionAttachment.append_child("InitHandle").text() = m.m_attachmentArgs.attachedTo.GetHandle();
				auto nodePositionAttachmentOffset = nodePositionAttachment.append_child("Offset");
				nodePositionAttachmentOffset.append_attribute("X") = m.m_attachmentArgs.offset.x;
				nodePositionAttachmentOffset.append_attribute("Y") = m.m_attachmentArgs.offset.y;
				nodePositionAttachmentOffset.append_attribute("Z") = m.m_attachmentArgs.offset.z;
				auto nodePositionAttachmentRotation = nodePositionAttachment.append_child("Rotation");
				nodePositionAttachmentRotation.append_attribute("X") = m.m_attachmentArgs.rotation.x;
				nodePositionAttachmentRotation.append_attribute("Y") = m.m_attachmentArgs.rotation.y;
				nodePositionAttachmentRotation.append_attribute("Z") = m.m_attachmentArgs.rotation.z;
			}

			auto nodeDestination = nodeMarker.append_child("Destination");

			nodeDestination.append_child("LinkInitHandle").text() = m.m_destinationPtr == nullptr ? 0U : m.m_destinationPtr->m_id;

			auto nodeDestinationPos = nodeDestination.append_child("Position");
			nodeDestinationPos.append_attribute("X") = m.m_destinationVal.m_position.x;
			nodeDestinationPos.append_attribute("Y") = m.m_destinationVal.m_position.y;
			nodeDestinationPos.append_attribute("Z") = m.m_destinationVal.m_position.z;

			auto nodeDestinationRot = nodeDestination.append_child("Rotation");
			nodeDestinationRot.append_attribute("X") = m.m_destinationVal.m_rotation.x;
			nodeDestinationRot.append_attribute("Y") = m.m_destinationVal.m_rotation.y;
			nodeDestinationRot.append_attribute("Z") = m.m_destinationVal.m_rotation.z;

			if (m.m_destinationVal.m_attachmentArgs.attachedTo.Exists())
			{
				auto nodeDestinationAttachment = nodeDestination.append_child("Attachment");
				nodeDestinationAttachment.append_child("InitHandle").text() = m.m_destinationVal.m_attachmentArgs.attachedTo.GetHandle();
				auto nodeDestinationAttachmentOffset = nodeDestinationAttachment.append_child("Offset");
				nodeDestinationAttachmentOffset.append_attribute("X") = m.m_destinationVal.m_attachmentArgs.offset.x;
				nodeDestinationAttachmentOffset.append_attribute("Y") = m.m_destinationVal.m_attachmentArgs.offset.y;
				nodeDestinationAttachmentOffset.append_attribute("Z") = m.m_destinationVal.m_attachmentArgs.offset.z;
				auto nodeDestinationAttachmentRotation = nodeDestinationAttachment.append_child("Rotation");
				nodeDestinationAttachmentRotation.append_attribute("X") = m.m_destinationVal.m_attachmentArgs.rotation.x;
				nodeDestinationAttachmentRotation.append_attribute("Y") = m.m_destinationVal.m_attachmentArgs.rotation.y;
				nodeDestinationAttachmentRotation.append_attribute("Z") = m.m_destinationVal.m_attachmentArgs.rotation.z;
			}

			nodeMarker.append_child("DestinationHeading").text() = m.m_destinationHeading;
		}
		SpoonerMarkerWithInitHandle SpawnMarkerFromXmlNode(pugi::xml_node& nodeMarker)
		{
			SpoonerMarkerWithInitHandle mi;
			SpoonerMarker& m = mi.m;
			m.m_name = nodeMarker.child("Name").text().as_string();
			mi.initHandle = nodeMarker.child("InitialHandle").text().as_uint();
			m.m_type = nodeMarker.child("Type").text().as_int();
			m.m_scale = nodeMarker.child("Scale").text().as_float();
			m.m_showName = nodeMarker.child("ShowName").text().as_bool();
			m.m_rotateContinuously = nodeMarker.child("RotateContinuously").text().as_bool();
			m.m_allowVehicles = nodeMarker.child("AllowVehicles").text().as_bool();

			auto nodeColour = nodeMarker.child("Colour");
			m.m_colour.R = nodeColour.attribute("R").as_int();
			m.m_colour.G = nodeColour.attribute("G").as_int();
			m.m_colour.B = nodeColour.attribute("B").as_int();
			m.m_colour.A = nodeColour.attribute("A").as_int();

			auto nodePosition = nodeMarker.child("Position");

			if (!nodePosition.first_child())
			{
				m.m_position.x = nodePosition.attribute("X").as_float();
				m.m_position.y = nodePosition.attribute("Y").as_float();
				m.m_position.z = nodePosition.attribute("Z").as_float();

				auto nodeRotation = nodeMarker.child("Rotation");
				m.m_rotation.x = nodeRotation.attribute("X").as_float();
				m.m_rotation.y = nodeRotation.attribute("Y").as_float();
				m.m_rotation.z = nodeRotation.attribute("Z").as_float();
			}
			else
			{
				auto nodePositionPos = nodePosition.child("Position");
				m.m_position.x = nodePositionPos.attribute("X").as_float();
				m.m_position.y = nodePositionPos.attribute("Y").as_float();
				m.m_position.z = nodePositionPos.attribute("Z").as_float();

				auto nodePositionRot = nodePosition.child("Rotation");
				m.m_rotation.x = nodePositionRot.attribute("X").as_float();
				m.m_rotation.y = nodePositionRot.attribute("Y").as_float();
				m.m_rotation.z = nodePositionRot.attribute("Z").as_float();

				auto nodePositionAttachment = nodePosition.child("Attachment");
				if (nodePositionAttachment)
				{
					m.m_attachmentArgs.attachedTo = nodePositionAttachment.child("InitHandle").text().as_int();

					auto nodePositionAttachmentOffset = nodePositionAttachment.child("Offset");
					m.m_attachmentArgs.offset.x = nodePositionAttachmentOffset.attribute("X").as_float();
					m.m_attachmentArgs.offset.y = nodePositionAttachmentOffset.attribute("Y").as_float();
					m.m_attachmentArgs.offset.z = nodePositionAttachmentOffset.attribute("Z").as_float();
					auto nodePositionAttachmentRotation = nodePositionAttachment.child("Rotation");
					m.m_attachmentArgs.rotation.x = nodePositionAttachmentRotation.attribute("X").as_float();
					m.m_attachmentArgs.rotation.y = nodePositionAttachmentRotation.attribute("Y").as_float();
					m.m_attachmentArgs.rotation.z = nodePositionAttachmentRotation.attribute("Z").as_float();
				}
			}

			auto nodeDestination = nodeMarker.child("Destination");
			if (!nodeDestination.first_child())
			{
				m.m_destinationVal.m_position.x = nodeDestination.attribute("X").as_float();
				m.m_destinationVal.m_position.y = nodeDestination.attribute("Y").as_float();
				m.m_destinationVal.m_position.z = nodeDestination.attribute("Z").as_float();
			}
			else
			{
				mi.linkToHandle = nodeDestination.child("LinkInitHandle").text().as_uint();

				auto nodeDestinationPos = nodeDestination.child("Position");
				m.m_destinationVal.m_position.x = nodeDestinationPos.attribute("X").as_float();
				m.m_destinationVal.m_position.y = nodeDestinationPos.attribute("Y").as_float();
				m.m_destinationVal.m_position.z = nodeDestinationPos.attribute("Z").as_float();

				auto nodeDestinationRot = nodeDestination.child("Rotation");
				m.m_destinationVal.m_rotation.x = nodeDestinationRot.attribute("X").as_float();
				m.m_destinationVal.m_rotation.y = nodeDestinationRot.attribute("Y").as_float();
				m.m_destinationVal.m_rotation.z = nodeDestinationRot.attribute("Z").as_float();

				auto nodeDestinationAttachment = nodeDestination.child("Attachment");
				if (nodeDestinationAttachment)
				{
					m.m_destinationVal.m_attachmentArgs.attachedTo = nodeDestinationAttachment.child("InitHandle").text().as_int();

					auto nodeDestinationAttachmentOffset = nodeDestinationAttachment.child("Offset");
					m.m_destinationVal.m_attachmentArgs.offset.x = nodeDestinationAttachmentOffset.attribute("X").as_float();
					m.m_destinationVal.m_attachmentArgs.offset.y = nodeDestinationAttachmentOffset.attribute("Y").as_float();
					m.m_destinationVal.m_attachmentArgs.offset.z = nodeDestinationAttachmentOffset.attribute("Z").as_float();
					auto nodeDestinationAttachmentRotation = nodeDestinationAttachment.child("Rotation");
					m.m_destinationVal.m_attachmentArgs.rotation.x = nodeDestinationAttachmentRotation.attribute("X").as_float();
					m.m_destinationVal.m_attachmentArgs.rotation.y = nodeDestinationAttachmentRotation.attribute("Y").as_float();
					m.m_destinationVal.m_attachmentArgs.rotation.z = nodeDestinationAttachmentRotation.attribute("Z").as_float();
				}
			}

			m.m_destinationHeading = nodeMarker.child("DestinationHeading").text().as_float();

			return mi;
		}

		bool SaveDbToFile(const std::string& filePath, bool bForceReferenceCoords)
		{
			addlog(ige::LogType::LOG_INFO,  "Saving Spooner database to xml file " + filePath, __FILENAME__);

			auto& spoocam = SpoonerMode::spoonerModeCamera;
			GTAentity myPed = PLAYER_PED_ID();
			pugi::xml_node nodeNote;
			pugi::xml_node nodeAudioFile;
			bool bClearDbSetting = false;
			float bClearWorldSetting = 0.0f;
			bool bClearMarkersSetting = false;
			pugi::xml_node nodeIplsToLoad, nodeIplsToUnload;
			pugi::xml_node nodeInteriorsToEnable, nodeInteriorsToCap;
			std::string weatherToSet;
			std::string timecycMod;
			float timecycModStren = 1.0f;
			bool bStartTaskSeqsOnLoad = true;
			Vector3 oldRefCoords;
			bool bUseOldRefCoords = false;
			Vector3 oldImgLoadingCoords;
			bool bUseOldImgLoadingCoords = false;

			pugi::xml_document doc2;
			if (doc2.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
			{
				auto nodeOldRoot = doc2.child("SpoonerPlacements");

				nodeNote = nodeOldRoot.child("Note");

				nodeAudioFile = nodeOldRoot.child("AudioFile");

				bClearDbSetting = nodeOldRoot.child("ClearDatabase").text().as_bool();
				bClearWorldSetting = nodeOldRoot.child("ClearWorld").text().as_float();
				bClearMarkersSetting = nodeOldRoot.child("ClearMarkers").text().as_bool();

				/*auto& nodeOldIplsToLoad = nodeOldRoot.child("IPLsToLoad");
				bIplsRequireMpMaps = nodeOldIplsToLoad.attribute("load_mp_maps").as_bool();
				bIplsRequireSpMaps = nodeOldIplsToLoad.attribute("load_sp_maps").as_bool();
				for (auto& nodeOldIplToLoad = nodeOldIplsToLoad.first_child(); nodeOldIplToLoad; nodeOldIplToLoad = nodeOldIplToLoad.next_sibling())
				{
				vIplsToLoad.push_back(nodeOldIplToLoad.text().as_string());
				}
				auto& nodeOldIplsToUnload = nodeOldRoot.child("IPLsToRemove");
				for (auto& nodeOldIplToUnload = nodeOldIplsToUnload.first_child(); nodeOldIplToUnload; nodeOldIplToUnload = nodeOldIplToUnload.next_sibling())
				{
				vIplsToUnload.push_back(nodeOldIplToUnload.text().as_string());
				}*/
				nodeIplsToLoad = nodeOldRoot.child("IPLsToLoad");
				nodeIplsToUnload = nodeOldRoot.child("IPLsToUnload");

				nodeInteriorsToEnable = nodeOldRoot.child("InteriorsToEnable");

				auto nodeOldWeatherToSet = nodeOldRoot.child("WeatherToSet");
				if (nodeOldWeatherToSet)
					weatherToSet = nodeOldWeatherToSet.text().as_string();

				auto nodeOldTimecycMod = nodeOldRoot.child("TimecycleModifier");
				if (nodeOldTimecycMod)
				{
					timecycMod = nodeOldTimecycMod.text().as_string();
					timecycModStren = nodeOldTimecycMod.attribute("strength").as_float(1.0f);
				}

				bStartTaskSeqsOnLoad = nodeOldRoot.child("StartTaskSequencesOnLoad").text().as_bool(bStartTaskSeqsOnLoad);

				auto nodeOldImgLoadingCoords = nodeOldRoot.child("ImgLoadingCoords");
				if (nodeOldImgLoadingCoords)
				{
					oldImgLoadingCoords.x = nodeOldImgLoadingCoords.child("X").text().as_float();
					oldImgLoadingCoords.y = nodeOldImgLoadingCoords.child("Y").text().as_float();
					oldImgLoadingCoords.z = nodeOldImgLoadingCoords.child("Z").text().as_float();
					bUseOldImgLoadingCoords = true;
				}

				if (!bForceReferenceCoords)
				{
					auto nodeOldReferenceCoords = nodeOldRoot.child("ReferenceCoords");
					if (nodeOldReferenceCoords)
					{
						oldRefCoords.x = nodeOldReferenceCoords.child("X").text().as_float();
						oldRefCoords.y = nodeOldReferenceCoords.child("Y").text().as_float();
						oldRefCoords.z = nodeOldReferenceCoords.child("Z").text().as_float();
						bUseOldRefCoords = true;
					}
				}
			}
			pugi::xml_document doc;

			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";

			auto nodeRoot = doc.append_child("SpoonerPlacements");

			if (nodeNote)
			{
				nodeRoot.append_copy(nodeNote);
			}
			else
			{
				nodeNote = nodeRoot.append_child("Note");
			}

			if (nodeAudioFile)
			{
				nodeRoot.append_copy(nodeAudioFile);
			}
			else
			{
				nodeAudioFile = nodeRoot.append_child("AudioFile");
				nodeAudioFile.append_attribute("volume") = 400;
			}

			nodeRoot.append_child("ClearDatabase").text() = bClearDbSetting;
			nodeRoot.append_child("ClearWorld").text() = bClearWorldSetting;
			nodeRoot.append_child("ClearMarkers").text() = bClearMarkersSetting;

			/*auto& nodeIplsToLoad = nodeRoot.append_child("IPLsToLoad");
			nodeIplsToLoad.append_attribute("load_mp_maps") = bIplsRequireMpMaps;
			nodeIplsToLoad.append_attribute("load_sp_maps") = bIplsRequireSpMaps;
			for (auto& ipln : vIplsToLoad) nodeIplsToLoad.append_child("IPL").text() = ipln.c_str();
			auto& nodeIplsToUnload = nodeRoot.append_child("IPLsToRemove");
			for (auto& ipln : vIplsToUnload) nodeIplsToUnload.append_child("IPL").text() = ipln.c_str();*/
			if (nodeIplsToLoad)
			{
				nodeRoot.append_copy(nodeIplsToLoad);
			}
			else
			{
				nodeIplsToLoad = nodeRoot.append_child("IPLsToLoad");
				nodeIplsToLoad.append_attribute("load_mp_maps") = false;
				nodeIplsToLoad.append_attribute("load_sp_maps") = false;
			}
			if (nodeIplsToUnload)
			{
				nodeRoot.append_copy(nodeIplsToUnload);
			}
			else
			{
				nodeIplsToUnload = nodeRoot.append_child("IPLsToRemove");
			}

			if (nodeInteriorsToEnable)
			{
				nodeRoot.append_copy(nodeInteriorsToEnable);
			}
			else
			{
				nodeInteriorsToEnable = nodeRoot.append_child("InteriorsToEnable");
			}
			if (nodeInteriorsToCap)
			{
				nodeRoot.append_copy(nodeInteriorsToCap);
			}
			else
			{
				nodeInteriorsToCap = nodeRoot.append_child("InteriorsToCap");
			}

			//weatherToSet = World::WeatherName_get(); // Just set "" by default
			nodeRoot.append_child("WeatherToSet").text() = weatherToSet.c_str();

			auto nodeTimecycMod = nodeRoot.append_child("TimecycleModifier");
			nodeTimecycMod.text() = timecycMod.c_str();
			nodeTimecycMod.append_attribute("strength") = timecycModStren;

			nodeRoot.append_child("StartTaskSequencesOnLoad").text() = bStartTaskSeqsOnLoad;

			if (bUseOldImgLoadingCoords)
			{
				auto nodeImgLoadingCoords = nodeRoot.append_child("ImgLoadingCoords");
				nodeImgLoadingCoords.append_child("X").text() = oldImgLoadingCoords.x;
				nodeImgLoadingCoords.append_child("Y").text() = oldImgLoadingCoords.y;
				nodeImgLoadingCoords.append_child("Z").text() = oldImgLoadingCoords.z;
			}

			if (bForceReferenceCoords)
			{
				auto nodeReferenceCoords = nodeRoot.append_child("ReferenceCoords");
				SET_WAYPOINT_OFF();
				bool bSpoocamIsActive = false;
				bool bWaypointRemoved = false;
				bool bReferenceCoordsToSelfCoords = false;
				Vector3 wpCoords;
				for (;;)
				{
					SpoonerMode::Tick();
					bSpoocamIsActive = spoocam.IsActive();

					Game::Print::setupdraw(GTAfont::Caps, Vector2(0.9f, 0.9f), true, false, false);
					Game::Print::drawstring("SET A WAYPOINT AS A MAP REFERENCE", 0.5f, 0.5f);

					Game::CustomHelpText::ShowThisFrame(oss_ << "Press ~INPUT_LOOK_BEHIND~ to save " << (bSpoocamIsActive ? "the camera target position" : "your current position") << " as the map reference.");
					if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_LOOK_BEHIND)) bReferenceCoordsToSelfCoords = true;

					if (bSpoocamIsActive)
					{
						wpCoords = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 160.0f, 3.0f);
						World::DrawMarker(MarkerType::DebugSphere, wpCoords, Vector3(), Vector3(), Vector3(0.77f, 0.77f, 0.77f), RGBA(0, 153, 76, 190));
					}

					if (!IS_WAYPOINT_ACTIVE()) bWaypointRemoved = true;
					if ((bWaypointRemoved && IS_WAYPOINT_ACTIVE()) || bReferenceCoordsToSelfCoords)
					{
						if (bReferenceCoordsToSelfCoords)
						{
							if (bSpoocamIsActive)
							{
								//wpCoords = wpCoords;
							}
							else
							{
								wpCoords = myPed.Position_get();
							}
						}
						else
						{
							wpCoords = GTAblip(GET_FIRST_BLIP_INFO_ID(BlipIcon::Waypoint)).Position_get();
							wpCoords.z = World::GetGroundHeight(wpCoords);
						}
						nodeReferenceCoords.append_child("X").text() = wpCoords.x;
						nodeReferenceCoords.append_child("Y").text() = wpCoords.y;
						nodeReferenceCoords.append_child("Z").text() = wpCoords.z;
						break;
					}
					WAIT(0);
				}
			}
			else if (bUseOldRefCoords)
			{
				auto nodeReferenceCoords = nodeRoot.append_child("ReferenceCoords");
				nodeReferenceCoords.append_child("X").text() = oldRefCoords.x;
				nodeReferenceCoords.append_child("Y").text() = oldRefCoords.y;
				nodeReferenceCoords.append_child("Z").text() = oldRefCoords.z;
			}

			//====================================================================================================================

			for (auto& e : Databases::EntityDb)
			{
				if (e.Handle.Exists())
				{
					auto nodeEntity = nodeRoot.append_child("Placement");
					AddEntityToXmlNode(e, nodeEntity);
				}
			}

			for (auto& m : Databases::MarkerDb)
			{
				auto nodeMarker = nodeRoot.append_child("Marker");
				AddMarkerToXmlNode(m, nodeMarker);
			}

			//====================================================================================================================

			bool saveSucceeded = doc.save_file((const char*)filePath.c_str());
			return saveSucceeded;
		}
		bool SaveWorldToFile(const std::string& filePath, std::vector<Entity>& vEntityHandles, std::vector<SpoonerMarker>& vMarkers)
		{
			addlog(ige::LogType::LOG_INFO,  "Saving World to xml file " + filePath, __FILENAME__);

			//GTAentity myPed = PLAYER_PED_ID();
			//auto& myPos = myPed.Position_get();
			//bool bCheckEntDistFromSelf = maxDistFromSelf < FLT_MAX;

			pugi::xml_node nodeNote;
			pugi::xml_node nodeAudioFile;
			bool bClearDbSetting = false;
			float bClearWorldSetting = 0.0f;
			bool bClearMarkersSetting = false;
			pugi::xml_node nodeIplsToLoad, nodeIplsToUnload;
			pugi::xml_node nodeInteriorsToEnable, nodeInteriorsToCap;
			std::string weatherToSet;
			std::string timecycMod;
			float timecycModStren = 1.0f;
			bool bStartTaskSeqsOnLoad = true;
			Vector3 oldRefCoords;
			bool bUseOldRefCoords = false;
			Vector3 oldImgLoadingCoords;
			bool bUseOldImgLoadingCoords = false;

			pugi::xml_document doc2;
			if (doc2.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
			{
				auto nodeOldRoot = doc2.child("SpoonerPlacements");

				nodeNote = nodeOldRoot.child("Note");

				nodeAudioFile = nodeOldRoot.child("AudioFile");

				bClearDbSetting = nodeOldRoot.child("ClearDatabase").text().as_bool();
				bClearWorldSetting = nodeOldRoot.child("ClearWorld").text().as_float();
				bClearMarkersSetting = nodeOldRoot.child("ClearMarkers").text().as_bool();

				/*auto& nodeOldIplsToLoad = nodeOldRoot.child("IPLsToLoad");
				bIplsRequireMpMaps = nodeOldIplsToLoad.attribute("load_mp_maps").as_bool();
				bIplsRequireSpMaps = nodeOldIplsToLoad.attribute("load_sp_maps").as_bool();
				for (auto& nodeOldIplToLoad = nodeOldIplsToLoad.first_child(); nodeOldIplToLoad; nodeOldIplToLoad = nodeOldIplToLoad.next_sibling())
				{
				vIplsToLoad.push_back(nodeOldIplToLoad.text().as_string());
				}
				auto& nodeOldIplsToUnload = nodeOldRoot.child("IPLsToRemove");
				for (auto& nodeOldIplToUnload = nodeOldIplsToUnload.first_child(); nodeOldIplToUnload; nodeOldIplToUnload = nodeOldIplToUnload.next_sibling())
				{
				vIplsToUnload.push_back(nodeOldIplToUnload.text().as_string());
				}*/
				nodeIplsToLoad = nodeOldRoot.child("IPLsToLoad");
				nodeIplsToUnload = nodeOldRoot.child("IPLsToUnload");

				nodeInteriorsToEnable = nodeOldRoot.child("InteriorsToEnable");

				auto nodeOldWeatherToSet = nodeOldRoot.child("WeatherToSet");
				if (nodeOldWeatherToSet)
					weatherToSet = nodeOldWeatherToSet.text().as_string();

				auto nodeOldTimecycMod = nodeOldRoot.child("TimecycleModifier");
				if (nodeOldTimecycMod)
				{
					timecycMod = nodeOldTimecycMod.text().as_string();
					timecycModStren = nodeOldTimecycMod.attribute("strength").as_float(1.0f);
				}

				bStartTaskSeqsOnLoad = nodeOldRoot.child("StartTaskSequencesOnLoad").text().as_bool(bStartTaskSeqsOnLoad);

				auto nodeOldImgLoadingCoords = nodeOldRoot.child("ImgLoadingCoords");
				if (nodeOldImgLoadingCoords)
				{
					oldImgLoadingCoords.x = nodeOldImgLoadingCoords.child("X").text().as_float();
					oldImgLoadingCoords.y = nodeOldImgLoadingCoords.child("Y").text().as_float();
					oldImgLoadingCoords.z = nodeOldImgLoadingCoords.child("Z").text().as_float();
					bUseOldImgLoadingCoords = true;
				}

				auto nodeOldReferenceCoords = nodeOldRoot.child("ReferenceCoords");
				if (nodeOldReferenceCoords)
				{
					oldRefCoords.x = nodeOldReferenceCoords.child("X").text().as_float();
					oldRefCoords.y = nodeOldReferenceCoords.child("Y").text().as_float();
					oldRefCoords.z = nodeOldReferenceCoords.child("Z").text().as_float();
					bUseOldRefCoords = true;
				}
			}
			pugi::xml_document doc;

			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";

			auto nodeRoot = doc.append_child("SpoonerPlacements");

			if (nodeNote)
			{
				nodeRoot.append_copy(nodeNote);
			}
			else
			{
				nodeNote = nodeRoot.append_child("Note");
			}

			if (nodeAudioFile)
			{
				nodeRoot.append_copy(nodeAudioFile);
			}
			else
			{
				nodeAudioFile = nodeRoot.append_child("AudioFile");
				nodeAudioFile.append_attribute("volume") = 400;
			}

			nodeRoot.append_child("ClearDatabase").text() = bClearDbSetting;
			nodeRoot.append_child("ClearWorld").text() = bClearWorldSetting;
			nodeRoot.append_child("ClearMarkers").text() = bClearMarkersSetting;

			/*auto& nodeIplsToLoad = nodeRoot.append_child("IPLsToLoad");
			nodeIplsToLoad.append_attribute("load_mp_maps") = bIplsRequireMpMaps;
			nodeIplsToLoad.append_attribute("load_sp_maps") = bIplsRequireSpMaps;
			for (auto& ipln : vIplsToLoad) nodeIplsToLoad.append_child("IPL").text() = ipln.c_str();
			auto& nodeIplsToUnload = nodeRoot.append_child("IPLsToRemove");
			for (auto& ipln : vIplsToUnload) nodeIplsToUnload.append_child("IPL").text() = ipln.c_str();*/
			if (nodeIplsToLoad)
			{
				nodeRoot.append_copy(nodeIplsToLoad);
			}
			else
			{
				nodeIplsToLoad = nodeRoot.append_child("IPLsToLoad");
				nodeIplsToLoad.append_attribute("load_mp_maps") = false;
				nodeIplsToLoad.append_attribute("load_sp_maps") = false;
			}
			if (nodeIplsToUnload)
			{
				nodeRoot.append_copy(nodeIplsToUnload);
			}
			else
			{
				nodeIplsToUnload = nodeRoot.append_child("IPLsToRemove");
			}

			if (nodeInteriorsToEnable)
			{
				nodeRoot.append_copy(nodeInteriorsToEnable);
			}
			else
			{
				nodeInteriorsToEnable = nodeRoot.append_child("InteriorsToEnable");
			}
			if (nodeInteriorsToCap)
			{
				nodeRoot.append_copy(nodeInteriorsToCap);
			}
			else
			{
				nodeInteriorsToCap = nodeRoot.append_child("InteriorsToCap");
			}

			//weatherToSet = World::WeatherName_get(); // Just set "" by default
			nodeRoot.append_child("WeatherToSet").text() = weatherToSet.c_str();

			auto nodeTimecycMod = nodeRoot.append_child("TimecycleModifier");
			nodeTimecycMod.text() = timecycMod.c_str();
			nodeTimecycMod.append_attribute("strength") = timecycModStren;

			nodeRoot.append_child("StartTaskSequencesOnLoad").text() = bStartTaskSeqsOnLoad;

			if (bUseOldImgLoadingCoords)
			{
				auto nodeImgLoadingCoords = nodeRoot.append_child("ImgLoadingCoords");
				nodeImgLoadingCoords.append_child("X").text() = oldImgLoadingCoords.x;
				nodeImgLoadingCoords.append_child("Y").text() = oldImgLoadingCoords.y;
				nodeImgLoadingCoords.append_child("Z").text() = oldImgLoadingCoords.z;
			}

			if (bUseOldRefCoords)
			{
				auto nodeReferenceCoords = nodeRoot.append_child("ReferenceCoords");
				nodeReferenceCoords.append_child("X").text() = oldRefCoords.x;
				nodeReferenceCoords.append_child("Y").text() = oldRefCoords.y;
				nodeReferenceCoords.append_child("Z").text() = oldRefCoords.z;
			}

			//=================================================================

			for (auto& eHandle : vEntityHandles)
			{
				SpoonerEntity e;
				e.Handle = eHandle;
				if (e.Handle.Exists())
				{
					//if (bCheckEntDistFromSelf)
					//{if (myPos.DistanceTo(e.Handle.Position_get()) > maxDistFromSelf) continue;}

					auto indInDb = EntityManagement::GetEntityIndexInDb(e);
					if (indInDb >= 0)
					{
						e = Databases::EntityDb[indInDb];
					}
					else
					{
						const Model& eModel = e.Handle.Model();
						e.Type = (EntityType)e.Handle.Type();
						e.Dynamic = true;
						switch (e.Type)
						{
						case EntityType::PROP:
						{
							e.HashName = get_prop_model_label(eModel);
							break;
						}
						case EntityType::PED:
						{
							e.HashName = get_ped_model_label(eModel, true);
							for (auto& anmnm : AnimationSub_catind::vPresetPedAnims)
							{
								if (IS_ENTITY_PLAYING_ANIM(e.Handle.Handle(), anmnm.animDict.c_str(), anmnm.animName.c_str(), 3))
								{
									e.LastAnimation.dict = anmnm.animDict;
									e.LastAnimation.name = anmnm.animName;
								}
							}
							if (e.LastAnimation.dict.empty() && IS_PED_USING_ANY_SCENARIO(e.Handle.Handle()))
							{
								for (auto& scnnm : AnimationSub_TaskScenarios::vValues_TaskScenarios)
								{
									if (IS_PED_USING_SCENARIO(e.Handle.Handle(), scnnm.c_str()))
									{
										e.LastAnimation.name = scnnm;
									}
								}
							}
							break;
						}
						case EntityType::VEHICLE:
						{
							e.HashName = get_vehicle_model_label(eModel, true);
							break;
						}
						}
						//if (e.HashName.length() == 0) e.HashName = int_to_hexstring(eModel.hash, true);
					}

					auto nodeEntity = nodeRoot.append_child("Placement");
					AddEntityToXmlNode(e, nodeEntity);
				}
			}

			for (auto& m : vMarkers)
			{
				auto nodeMarker = nodeRoot.append_child("Marker");
				AddMarkerToXmlNode(m, nodeMarker);
			}

			//=================================================================

			return doc.save_file((const char*)filePath.c_str());
		}
		bool LoadPlacementsFromFile(const std::string& filePath)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
				return false;
			std::string fileName = filePath.substr(filePath.rfind("\\") + 1, filePath.rfind('.') - filePath.rfind("\\") - 1);

			GTAentity myPed = PLAYER_PED_ID();
			GTAentity myVehicle = g_myVeh;
			const Vector3& myPos = myPed.Position_get();

			pugi::xml_node nodeRoot = doc.child("SpoonerPlacements");

			auto nodeIplsToUnload = nodeRoot.child("IPLsToRemove");
			for (auto nodeIplToUnload = nodeIplsToUnload.first_child(); nodeIplToUnload; nodeIplToUnload = nodeIplToUnload.next_sibling())
			{
				PCHAR iplName = (PCHAR)nodeIplToUnload.text().as_string();
				if (IS_IPL_ACTIVE(iplName)) REMOVE_IPL(iplName);
			}
			auto nodeIplsToLoad = nodeRoot.child("IPLsToLoad");
			bool bIplsRequireMpMaps = nodeIplsToLoad.attribute("load_mp_maps").as_bool();
			bool bIplsRequireSpMaps = nodeIplsToLoad.attribute("load_sp_maps").as_bool();
			if (bIplsRequireMpMaps)
			{
				SET_INSTANCE_PRIORITY_MODE(true);
				ON_ENTER_MP();
			}
			if (bIplsRequireSpMaps)
			{
				SET_INSTANCE_PRIORITY_MODE(true);
				ON_ENTER_SP();
			}
			for (auto nodeIplToLoad = nodeIplsToLoad.first_child(); nodeIplToLoad; nodeIplToLoad = nodeIplToLoad.next_sibling())
			{
				PCHAR iplName = (PCHAR)nodeIplToLoad.text().as_string();
				if (!IS_IPL_ACTIVE(iplName)) REQUEST_IPL(iplName);
			}

			auto nodeInteriorsToEnable = nodeRoot.child("InteriorsToEnable");
			for (auto nodeInterior = nodeInteriorsToEnable.first_child(); nodeInterior; nodeInterior = nodeInterior.next_sibling())
			{
				bool enableOrNah = nodeInterior.attribute("enable").as_bool(true);
				int interior = nodeInterior.attribute("id").as_int(-1);
				if (interior == -1)
				{
					if (nodeInterior.attribute("X"))
					{
						Vector3 coords;
						coords.x = nodeInterior.attribute("X").as_float();
						coords.y = nodeInterior.attribute("Y").as_float();
						coords.z = nodeInterior.attribute("Z").as_float();
						interior = GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
					}
					else if (nodeInterior.child("X"))
					{
						Vector3 coords;
						coords.x = nodeInterior.child("X").text().as_float();
						coords.y = nodeInterior.child("Y").text().as_float();
						coords.z = nodeInterior.child("Z").text().as_float();
						interior = GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
					}
				}
				if (IS_VALID_INTERIOR(interior))
				{
					if (enableOrNah)
					{
						PIN_INTERIOR_IN_MEMORY(interior);
						if (IS_INTERIOR_DISABLED(interior))
						{
							DISABLE_INTERIOR(interior, false);
						}
						for (auto nodeInteriorProp = nodeInterior.child("InteriorProp"); nodeInteriorProp; nodeInteriorProp = nodeInterior.next_sibling("InteriorProp"))
						{
							std::string interiorPropName = nodeInteriorProp.attribute("name").as_string();
							if (interiorPropName.length())
							{
								if (nodeInteriorProp.attribute("enable").as_bool(true))
								{
									ACTIVATE_INTERIOR_ENTITY_SET(interior, interiorPropName.c_str());
								}
								else
								{
									DEACTIVATE_INTERIOR_ENTITY_SET(interior, interiorPropName.c_str());
								}

							}
						}
						REFRESH_INTERIOR(interior);
					}
					else
					{
						if (!IS_INTERIOR_DISABLED(interior))
						{
							DISABLE_INTERIOR(interior, true);
						}
					}
				}
			}
			auto nodeInteriorsToCap = nodeRoot.child("InteriorsToCap");
			for (auto nodeInterior = nodeInteriorsToCap.first_child(); nodeInterior; nodeInterior = nodeInterior.next_sibling())
			{
				bool capOrNah = nodeInterior.attribute("cap").as_bool(true);
				int interior = nodeInterior.attribute("id").as_int(-1);
				if (interior == -1)
				{
					if (nodeInterior.attribute("X"))
					{
						Vector3 coords;
						coords.x = nodeInterior.attribute("X").as_float();
						coords.y = nodeInterior.attribute("Y").as_float();
						coords.z = nodeInterior.attribute("Z").as_float();
						interior = GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
					}
					else if (nodeInterior.child("X"))
					{
						Vector3 coords;
						coords.x = nodeInterior.child("X").text().as_float();
						coords.y = nodeInterior.child("Y").text().as_float();
						coords.z = nodeInterior.child("Z").text().as_float();
						interior = GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
					}
				}
				if (IS_VALID_INTERIOR(interior))
				{
					CAP_INTERIOR(interior, capOrNah);
				}
			}

			if (bIplsRequireMpMaps || bIplsRequireSpMaps)
			{
				SET_INSTANCE_PRIORITY_MODE(false);
			}

			//=================================================================

			auto nodeWeatherToSet = nodeRoot.child("WeatherToSet");
			if (nodeWeatherToSet)
			{
				std::string weatherToSet = nodeWeatherToSet.text().as_string();
				if (weatherToSet.length() > 0)
				{
					World::ClearWeatherOverride();
					//World::SetWeatherOverride(weatherToSet);
					World::SetWeatherOverTime(weatherToSet, 3000);
				}
			}

			auto nodeTimecycMod = nodeRoot.child("TimecycleModifier");
			if (nodeTimecycMod)
			{
				std::string timecycMod = nodeTimecycMod.text().as_string();
				float timecycModStren = nodeTimecycMod.attribute("strength").as_float(1.0f);
				if (timecycMod.length() > 0)
				{
					SET_TIMECYCLE_MODIFIER(timecycMod.c_str());
					SET_TIMECYCLE_MODIFIER_STRENGTH(timecycModStren);
				}
			}

			bool bStartTaskSeqsOnLoad = nodeRoot.child("StartTaskSequencesOnLoad").text().as_bool(true);

			Vector3 imgLoadingCoords;
			auto nodeImgLoadingCoords = nodeRoot.child("ImgLoadingCoords");
			if (nodeImgLoadingCoords)
			{
				imgLoadingCoords.x = nodeImgLoadingCoords.child("X").text().as_float();
				imgLoadingCoords.y = nodeImgLoadingCoords.child("Y").text().as_float();
				imgLoadingCoords.z = nodeImgLoadingCoords.child("Z").text().as_float();
			}

			Vector3 refCoords;
			auto nodeReferenceCoords = nodeRoot.child("ReferenceCoords");
			if (nodeReferenceCoords)
			{
				refCoords.x = nodeReferenceCoords.child("X").text().as_float();
				refCoords.y = nodeReferenceCoords.child("Y").text().as_float();
				refCoords.z = nodeReferenceCoords.child("Z").text().as_float();
				BlipManagement::CreateRefCoordBlip(refCoords, fileName, true);
			}

			auto nodeClearWorldSetting = nodeRoot.child("ClearWorld");
			if (nodeClearWorldSetting)
			{
				if (nodeReferenceCoords)
				{
					float clearWorldRadius = nodeClearWorldSetting.text().as_float();
					if (clearWorldRadius > 0.0f)
					{
						clear_area_of_entities(EntityType::ALL, refCoords, clearWorldRadius, { myPed, myVehicle });
						WAIT(0);
						MarkerManagement::RemoveAllMarkersInRange(refCoords, clearWorldRadius);
					}
				}
			}
			if (nodeRoot.child("ClearDatabase").text().as_bool())
			{
				EntityManagement::DeleteAllEntitiesInDb();
				WAIT(0);
			}
			if (nodeRoot.child("ClearMarkers").text().as_bool())
			{
				MarkerManagement::RemoveAllMarkers();
			}

			//=========ImgLoadingCoords (Vanilla Triangle ftw)=================

			DO_SCREEN_FADE_OUT(300);
			//WAIT(150);
			//teleport_net_ped(myPed.Handle(), 140.7751f, -1305.944f, 24.36);
			if (nodeImgLoadingCoords)
			{
				teleport_net_ped(myPed.Handle(), imgLoadingCoords.x, imgLoadingCoords.y, imgLoadingCoords.z);
				WAIT(1400);
			}

			//=================================================================

			//====================================================================================================================

			std::unordered_set<Hash> vModelHashes;
			std::vector<SpoonerEntityWithInitHandle> newDb;
			std::vector<SpoonerMarkerWithInitHandle> newMarkerDb;

			for (auto nodeEntity = nodeRoot.child("Placement"); nodeEntity; nodeEntity = nodeEntity.next_sibling("Placement"))
			{
				const auto& e = SpawnEntityFromXmlNode(nodeEntity, vModelHashes);
				newDb.push_back(e);
			}

			size_t markerDbToNewDbOffset = 0;
			for (auto nodeMarker = nodeRoot.child("Marker"); nodeMarker; nodeMarker = nodeMarker.next_sibling("Marker"))
			{
				const auto& m = SpawnMarkerFromXmlNode(nodeMarker);
				bool bm = true;
				for (auto mm = Databases::MarkerDb.begin(); mm != Databases::MarkerDb.end(); ++mm)
				{
					if (m.m == *mm)
					{
						//bm = false;
						MarkerManagement::RemoveMarker(mm);
						break;
					}
				}
				if (bm)
				{
					newMarkerDb.push_back(m);
					Databases::MarkerDb.push_back(m.m);
				}
			}
			markerDbToNewDbOffset = Databases::MarkerDb.size() - newMarkerDb.size();

			WAIT(1000);

			for (auto& e : newDb)
			{
				if (e.e.AttachmentArgs.isAttached)
				{
					if (e.attachedToHandle == myPed.Handle())
					{
						EntityManagement::AttachEntity(e.e, myPed, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
					}
					else if (e.attachedToHandle == myVehicle.Handle())
					{
						EntityManagement::AttachEntity(e.e, myVehicle, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
					}
					else
					{
						for (auto& x : newDb)
						{
							if (e.attachedToHandle == x.initHandle)
							{
								EntityManagement::AttachEntity(e.e, x.e.Handle, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
								break;
							}
						}
					}
				}

				for (UINT i = 0; i < newMarkerDb.size(); i++)
				{
					auto& m = Databases::MarkerDb[markerDbToNewDbOffset + i];
					if (m.m_attachmentArgs.attachedTo == e.initHandle)
					{
						m.m_attachmentArgs.attachedTo = e.e.Handle;
					}
					if (m.m_destinationVal.m_attachmentArgs.attachedTo == e.initHandle)
					{
						m.m_destinationVal.m_attachmentArgs.attachedTo = e.e.Handle;
					}
					for (int j = 0; j < newMarkerDb.size(); j++)
					{
						if (newMarkerDb[i].linkToHandle == newMarkerDb[j].initHandle)
						{
							m.m_destinationPtr = &Databases::MarkerDb[markerDbToNewDbOffset + j];
							break;
						}
					}
				}

				if (!e.e.TaskSequence.empty())
				{
					auto& vTskPtrs = e.e.TaskSequence.AllTasks();
					for (auto& u : newDb)
					{
						for (auto& tskPtr : vTskPtrs)
						{
							tskPtr->LoadTargetingDressing(u.initHandle, u.e.Handle.Handle());
						}
					}
					if (bStartTaskSeqsOnLoad) e.e.TaskSequence.Start();
				}

				Databases::EntityDb.push_back(e.e);
			}

			for (Model mh : vModelHashes)
			{
				//mh.Unload();
			}

			//=================================================================

			if (nodeReferenceCoords && Settings::bTeleportToReferenceWhenLoadingFile) teleport_net_ped(myPed.Handle(), refCoords.x, refCoords.y, refCoords.z);
			else if (nodeImgLoadingCoords) teleport_net_ped(myPed.Handle(), myPos.x, myPos.y, myPos.z);
			WAIT(200);
			DO_SCREEN_FADE_IN(300);

			//=================================================================

			std::string noteStr = nodeRoot.child("Note").text().as_string();
			if (noteStr.length())
			{
				Game::Print::PrintBottomLeft("~b~Note:~s~ " + noteStr);
			}

			mciSendStringA(("close " + _oldAudioAlias).c_str(), NULL, 0, 0);
			auto nodeAudioFile = nodeRoot.child("AudioFile");
			if (nodeAudioFile)
			{
				std::string audioFileName = nodeAudioFile.text().as_string();
				if (audioFileName.length())
				{
					const std::string& audioFilePath = GetPathffA(Pathff::Audio, true) + audioFileName;
					if (does_file_exist(audioFilePath))
					{
						std::string audioCommand, audioAlias = fileName;
						_oldAudioAlias = fileName;
						audioCommand = "open \"" + audioFilePath + "\" type MPEGVideo" + " alias " + audioAlias;
						mciSendStringA(audioCommand.c_str(), NULL, 0, 0);

						audioCommand = "play " + audioAlias + " from 0";
						mciSendStringA(audioCommand.c_str(), NULL, 0, 0);

						audioCommand = "setaudio " + audioAlias + " volume to " + (std::string)nodeAudioFile.attribute("volume").as_string("400");
						mciSendStringA(audioCommand.c_str(), NULL, 0, 0);
					}
				}
			}

			//====================================================================================================================

			Menu::SetSub_closed();

			return true;
		}

		bool LoadPlacementsFromSP00NFile(const std::string& filePath)
		{
			CSimpleIniA ini;
			if (ini.LoadFile(filePath.c_str()) != SI_Error::SI_OK)
				return false;

			std::unordered_set<Hash> vModelHashes;

			CSimpleIniA::TNamesDepend vSections;
			ini.GetAllSections(vSections);

			for (auto& section : vSections)
			{
				if (ini.GetValue(section.pItem, "Type", 0) == 0)
					continue;
				SpoonerEntity e;
				e.Type = (EntityType)ini.GetLongValue(section.pItem, "Type", 0);
				if (e.Type == EntityType(0))
					continue;
				Model eModel = strtoul(ini.GetValue(section.pItem, "Hash"), NULL, 16);
				e.HashName = e.Type == EntityType::PROP ? get_prop_model_label(eModel)
					: (e.Type == EntityType::PED ? get_ped_model_label(eModel, true)
						: get_vehicle_model_label(eModel, true));
				if (e.HashName.length() == 0) e.HashName = int_to_hexstring(eModel.hash, true);
				e.IsStill = true;

				Vector3 position, rotation;
				position.x = ini.GetDoubleValue(section.pItem, "X");
				position.y = ini.GetDoubleValue(section.pItem, "Y");
				position.z = ini.GetDoubleValue(section.pItem, "Z");
				rotation.x = ini.GetDoubleValue(section.pItem, "Pitch");
				rotation.y = ini.GetDoubleValue(section.pItem, "Roll");
				rotation.z = ini.GetDoubleValue(section.pItem, "Yaw");

				if (e.Type == EntityType::PROP)
				{
					e.Dynamic = false;
					e.Handle = World::CreateProp(eModel, position, rotation, e.Dynamic, false);
				}
				else if (e.Type == EntityType::PED)
				{
					e.Dynamic = true;
					auto ep = World::CreatePed(eModel, position, rotation, false);
					e.Handle = ep;
					ep.BlockPermanentEvents_set(e.IsStill);
				}
				else if (e.Type == EntityType::VEHICLE)
				{
					e.Dynamic = true;
					auto ev = World::CreateVehicle(eModel, position, rotation, false);
					e.Handle = ev;
				}

				//e.Handle.Position_set(position);
				//e.Handle.Rotation_set(rotation);
				e.Handle.FreezePosition(!e.Dynamic);
				e.Handle.MissionEntity_set(true);
				int opacityLevel = ini.GetLongValue(section.pItem, "Opacity", 255);
				if (opacityLevel < 255) e.Handle.Alpha_set(opacityLevel);
				e.Handle.LodDistance_set(1000000);
				eModel.LoadCollision(100);
				e.Handle.IsCollisionEnabled_set(true);

				vModelHashes.insert(eModel.hash);
				Databases::EntityDb.push_back(e);
			}

			for (Model mh : vModelHashes)
			{
				mh.Unload();
			}

			Menu::SetSub_closed();

			return true;
		}

		bool TeleportToReference(const std::string& filePath)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
				return false;

			pugi::xml_node nodeRoot = doc.child("SpoonerPlacements");
			auto nodeReferenceCoords = nodeRoot.child("ReferenceCoords");
			if (!nodeReferenceCoords)
				return false;

			Vector3 refCoords;
			refCoords.x = nodeReferenceCoords.child("X").text().as_float();
			refCoords.y = nodeReferenceCoords.child("Y").text().as_float();
			refCoords.z = nodeReferenceCoords.child("Z").text().as_float();

			teleport_net_ped(PLAYER_PED_ID(), refCoords.x, refCoords.y, refCoords.z);

			return true;
		}
	}

}




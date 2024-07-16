/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "EntityManagement.h"

#include "..\..\macros.h"

//#include "..\..\Menu\Menu.h"
#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Natives\types.h" //RGBA/RgbS
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAprop.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Util\StringManip.h"
#include "..\..\Util\FileLogger.h"
#include "..\..\Scripting\World.h"
#include "..\..\Scripting\Model.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Scripting\ModelNames.h"
#include "..\..\Scripting\enums.h"
#include "..\..\Scripting\Camera.h"

#include "..\PedAnimation.h"
#include "..\PedComponentChanger.h"
#include "..\PtfxSubs.h"
#include "Databases.h"
#include "SpoonerEntity.h"
#include "SpoonerSettings.h"
#include "BlipManagement.h"
#include "SpoonerMode.h"
#include "RelationshipManagement.h"

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

namespace sub::Spooner
{
	namespace EntityManagement
	{
		UINT GetNumberOfEntitiesSpawned(const EntityType& type)
		{
			switch (type)
			{
			case EntityType::ALL:
				return (UINT)Databases::EntityDb.size();
				break;
			default:
				return (UINT)std::count_if(Databases::EntityDb.begin(), Databases::EntityDb.end(),
					[type](const SpoonerEntity& item) {
					return item.Type == type;
				});
				break;
			}
		}

		int GetEntityIndexInDb(const GTAentity& entity)
		{
			for (int i = 0; i < Databases::EntityDb.size(); i++)
			{
				if (Databases::EntityDb[i].Handle == entity)
					return i;
			}
			return -1;
		}
		int GetEntityIndexInDb(const SpoonerEntity& ent)
		{
			return GetEntityIndexInDb(ent.Handle);
		}
		void AddEntityToDb(SpoonerEntity ent, bool missionEnt)
		{
			if (ent.Handle.Exists())
			{
				if (ent.HashName.length() == 0)
					ent.HashName = int_to_hexstring(ent.Handle.Model().hash, true);
				if (missionEnt)
					ent.Handle.MissionEntity_set(true);
				Databases::EntityDb.push_back(ent);
			}
		}
		void RemoveEntityFromDb(const SpoonerEntity& ent)
		{
			GTAentity handle = ent.Handle;

			const auto& eit = std::find(Databases::EntityDb.begin(), Databases::EntityDb.end(), ent);
			if (eit != Databases::EntityDb.end())
			{
				eit->TaskSequence.Reset(true);
				Databases::EntityDb.erase(eit);
			}

			for (auto rit = Databases::RelationshipDb.begin(); rit != Databases::RelationshipDb.end();)
			{
				if (rit->first.Equals(handle))
				{
					rit = Databases::RelationshipDb.erase(rit);
					break;
				}
				else ++rit;
			}
		}

		void ClearDb()
		{
			Databases::EntityDb.clear();
			Databases::RelationshipDb.clear();
			BlipManagement::ClearAllRefCoordBlips();
		}
		void DeleteEntity(SpoonerEntity& ent)
		{
			GTAentity handle = ent.Handle;
			for (auto& e : Databases::EntityDb)
			{
				GTAentity attTo;
				if (e.AttachmentArgs.isAttached && GetEntityThisEntityIsAttachedTo(e.Handle, attTo) && attTo.Equals(handle))
				{
					DetachEntity(e); // Detach other attachments (to clear variables)
				}
			}
			RemoveEntityFromDb(ent); // Remove this from db
			handle.Detach(); // Detach this
			//GTAblip(handle.CurrentBlip()).Remove();
			handle.Delete(handle != PLAYER_PED_ID() && handle != g_myVeh);
		}
		void DeleteAllEntitiesInDb()
		{
			GTAentity myPed = PLAYER_PED_ID();
			for (auto& e : Databases::EntityDb)
			{
				if (e.Handle != myPed &&  e.Handle != g_myVeh)
				{
					//GTAblip(e.Handle.CurrentBlip()).Remove();
					e.Handle.Delete(true);
				}
			}
			ClearDb();
		}
		void DeleteAllEntitiesOfTypeInDb(const EntityType& targetType)
		{
			GTAentity myPed = PLAYER_PED_ID();
			for (auto it = Databases::EntityDb.begin(); it != Databases::EntityDb.end();)
			{
				if (it->Type == targetType)
				{
					for (auto& e : Databases::EntityDb)
					{
						GTAentity attTo;
						if (e.AttachmentArgs.isAttached && GetEntityThisEntityIsAttachedTo(e.Handle, attTo) && attTo.Equals(it->Handle))
						{
							DetachEntity(e); // Detach other attachments (to clear variables)
						}
					}
					it->Handle.Detach(); // Detach this
					//GTAblip(it->Handle.CurrentBlip()).Remove();
					it->Handle.Delete(it->Handle != myPed && it->Handle != g_myVeh);
					it = Databases::EntityDb.erase(it);
				}
				else ++it;
			}
			if (targetType == EntityType::PED) Databases::RelationshipDb.clear();
		}
		inline void DeleteAllPropsInDb()
		{
			DeleteAllEntitiesOfTypeInDb(EntityType::PROP);
		}
		inline void DeleteAllPedsInDb()
		{
			DeleteAllEntitiesOfTypeInDb(EntityType::PED);
		}
		inline void DeleteAllVehiclesInDb()
		{
			DeleteAllEntitiesOfTypeInDb(EntityType::VEHICLE);
		}
		void DeleteInvalidEntitiesInDb()
		{
			for (auto it = Databases::EntityDb.begin(); it != Databases::EntityDb.end();)
			{
				if (!it->Handle.Exists())
				{
					//it->Handle.Delete(false);
					it = Databases::EntityDb.erase(it);
				}
				else ++it;
			}
			for (auto rit = Databases::RelationshipDb.begin(); rit != Databases::RelationshipDb.end();)
			{
				if (!rit->first.Exists())
				{
					rit = Databases::RelationshipDb.erase(rit);
				}
				else ++rit;
			}
		}

		void DeleteAllEntitiesInWorld()
		{
			GTAentity myPed = PLAYER_PED_ID();
			for (GTAentity e : _worldEntities)
			{
				if (e != myPed && e != g_myVeh)
					e.Delete();
			}
			ClearDb();

			WAIT(0);
			update_nearby_stuff_arrays_tick();
		}
		void DeleteAllPropsInWorld()
		{
			for (GTAentity e : _worldObjects)
			{
				e.Delete();
			}

			/*std::vector<SpoonerEntity> newdb;
			for (auto& dbe : Databases::EntityDb)
			{
			switch (dbe.Type)
			{
			case EntityType::PROP: break;
			default: newdb.push_back(dbe); break;
			}
			}
			Databases::EntityDb = newdb;*/
			DeleteAllPropsInDb();

			WAIT(0);
			update_nearby_stuff_arrays_tick();
		}
		void DeleteAllPedsInWorld()
		{
			GTAentity myPed = PLAYER_PED_ID();
			for (GTAentity e : _worldPeds)
			{
				if (e != myPed)
					e.Delete();
			}

			/*std::vector<SpoonerEntity> newdb;
			for (auto& dbe : Databases::EntityDb)
			{
			switch (dbe.Type)
			{
			case EntityType::PED: break;
			default: newdb.push_back(dbe); break;
			}
			}
			Databases::EntityDb = newdb;
			Databases::RelationshipDb.clear();*/
			DeleteAllPedsInDb();

			WAIT(0);
			update_nearby_stuff_arrays_tick();
		}
		void DeleteAllVehiclesInWorld()
		{
			for (GTAprop e : _worldVehicles)
			{
				e.Delete(e != g_myVeh);
			}

			/*std::vector<SpoonerEntity> newdb;
			for (auto& dbe : Databases::EntityDb)
			{
			switch (dbe.Type)
			{
			case EntityType::VEHICLE: break;
			default: newdb.push_back(dbe); break;
			}
			}
			Databases::EntityDb = newdb;*/
			DeleteAllVehiclesInDb();

			WAIT(0);
			update_nearby_stuff_arrays_tick();
		}

		SpoonerEntity AddProp(const GTAmodel::Model& model, const std::string& name, bool unloadModel)
		{
			if (Databases::EntityDb.size() >= GTA_MAX_ENTITIES)
			{
				Game::Print::PrintBottomLeft("~r~Error:~s~ Max spawn count reached.");
				addlog(ige::LogType::LOG_WARNING, "Failed to add prop, max spawn count " + std::to_string(GTA_MAX_ENTITIES) + " Reached", __FILENAME__);
				return SpoonerEntity();
			}
			if (!model.IsInCdImage())
			{
				const std::string& mdlnme = get_prop_model_label(model);
				std::string nameOfPlaceWhereYouMayFindThisModelToBeValid = "NO SUGGESTED LOCATIONS";
				if (!mdlnme.empty())
				{
					for (auto& prfx : std::vector<std::pair<std::string, std::string>>
					{
						{ "v_club", "Nightclubs" },
						{ "bah", "Bahama Mama's" },
						{ "cc", "Comedy club (Split Sides West)" },
						{ "vu", "Vanilla Unicorn" },
						{ "rock", "Tequila-la" },
						{ "v_res", "Residential - Vanilla Unicorn" },
						{ "d", "Strawberry Ave - Franklin's house" },
						{ "fa", "Strawberry Ave - Franklin's house" },
						{ "fh", "Vinewood Hills - Franklin's house" },
						{ "j", "FIB janitor's apartment" },
						{ "lest", "Lester's place" },
						{ "m", "Michael's place" },
						{ "mp", "Multiplayer apartments" },
						{ "r", "Madrazo's ranch" },
						{ "son", "Jimmy's room" },
						{ "mson", "Jimmy's room" },
						{ "tre", "Floyd's apartment" },
						{ "tt", "Trevor's trailer" },
						{ "v_med", "medical facilities" },
						{ "lab", "Humane Labs" },
						{ "cor", "Morgue" },
						{ "hosp", "Hospital" },
						{ "p", "Psychiatrist's office (Michael's shrink)" },
						{ "v_ret", "Retail outlets" },
						{ "247", "Convenience stores" },
						{ "csr", "Car showroom (Simeon)" },
						{ "fh", "Farmhouse" },
						{ "gc", "Gun club (Ammunation)" },
						{ "ml", "Meth lab" },
						{ "ps", "Ponsonby's clothing" },
						{ "ta", "tattoo parlour" },
						{ "v_serv", "Services" },
						{ "bs", "Barber shops" },
						{ "ct", "Control towers" },
						{ "v_corp", "Corporate" },
						{ "face", "Lifeinvader Building" }

					})
					{
						if (mdlnme.size() > prfx.first.size())
						{
							if (mdlnme.compare(0, prfx.first.size(), prfx.first) == 0)
								nameOfPlaceWhereYouMayFindThisModelToBeValid = prfx.second;
						}
					}
				}
				Game::Print::PrintBottomCentre("~r~Error:~s~ Invalid model.\n Check suggested locations: [" + nameOfPlaceWhereYouMayFindThisModelToBeValid + "]");
				return SpoonerEntity();
			}

			GTAped myPed = PLAYER_PED_ID();
			SpoonerEntity newEntity;
			const ModelDimensions& dimensions = model.Dimensions();
			bool bDynamic = Settings::bSpawnDynamicProps;
			bool bFreezePos = !bDynamic;
			bool bCollision = true;

			auto& spoocam = SpoonerMode::spoonerModeCamera;

			if (!spoocam.IsActive())
			{
				GTAentity myPedOrVehicle = myPed.IsInVehicle() ? (GTAentity)myPed.CurrentVehicle() : (GTAentity)myPed;

				newEntity.Handle = World::CreateProp(model, myPedOrVehicle.GetOffsetInWorldCoords(0, myPedOrVehicle.Dim1().y + 2.6f + dimensions.Dim2.y, 0), myPedOrVehicle.Rotation_get(), bDynamic, false);
				if (unloadModel)
					model.Unload();
				if (!myPedOrVehicle.IsInAir())
					PLACE_OBJECT_ON_GROUND_PROPERLY(newEntity.Handle.Handle());
			}
			else
			{
				Vector3 spawnPos = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 120.0f, 30.0f + dimensions.Dim2.y);
				spawnPos.z += dimensions.Dim1.z;

				newEntity.Handle = World::CreateProp(model, spawnPos, Vector3(0, 0, spoocam.Rotation_get().z), bDynamic, false);
				if (unloadModel)
					model.Unload();
			}

			SET_NETWORK_ID_CAN_MIGRATE(OBJ_TO_NET(newEntity.Handle.Handle()), true);
			newEntity.Handle.Dynamic_set(false);
			newEntity.Handle.FreezePosition(true);
			newEntity.Handle.FreezePosition(bFreezePos);
			newEntity.Handle.Dynamic_set(bDynamic);
			newEntity.Handle.LodDistance_set(1000000);
			newEntity.Handle.MissionEntity_set(true);
			newEntity.Handle.SetInvincible(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetExplosionProof(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetMeleeProof(Settings::bSpawnInvincibleEntities);
			model.LoadCollision(100);
			newEntity.Handle.IsCollisionEnabled_set(bCollision);
			model.Unload();

			newEntity.Type = (EntityType)newEntity.Handle.Type();

			if (name.length() > 0)
				newEntity.HashName = name;
			else
			{
				newEntity.HashName = get_prop_model_label(model);
				if (newEntity.HashName.length() == 0) newEntity.HashName = int_to_hexstring(model.hash, true);
			}

			newEntity.Dynamic = bDynamic;

			AddEntityToDb(newEntity);

			return newEntity;
		}
		SpoonerEntity AddPed(const GTAmodel::Model& model, const std::string& name, bool unloadModel)
		{
			if (Databases::EntityDb.size() >= GTA_MAX_ENTITIES)
			{
				Game::Print::PrintBottomLeft("~r~Error:~s~ Max spawn count reached.");
				addlog(ige::LogType::LOG_WARNING, "Failed to spawn ped, max spawn count " + std::to_string(GTA_MAX_ENTITIES) + " Reached", __FILENAME__);
				return SpoonerEntity();
			}
			if (!model.IsInCdImage())
			{
				Game::Print::PrintError_InvalidModel();
				return SpoonerEntity();
			}

			GTAped myPed = PLAYER_PED_ID();
			SpoonerEntity newEntity;
			const ModelDimensions& dimensions = model.Dimensions();
			bool bDynamic = Settings::bSpawnDynamicPeds;
			bool bFreezePos = !bDynamic;
			bool bCollision = true;

			auto& spoocam = SpoonerMode::spoonerModeCamera;

			if (!spoocam.IsActive())
			{
				GTAentity myPedOrVehicle = myPed.IsInVehicle() ? (GTAentity)myPed.CurrentVehicle() : (GTAentity)myPed;

				newEntity.Handle = World::CreatePed(model, myPedOrVehicle.GetOffsetInWorldCoords(0, myPedOrVehicle.Dim1().y + 2.6f + dimensions.Dim2.y, 0), myPedOrVehicle.Rotation_get(), myPedOrVehicle.HeightAboveGround() < 3.0f);
				if (unloadModel)
					model.Unload();
			}
			else
			{
				Vector3 spawnPos = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 120.0f, 30.0f + dimensions.Dim2.y);
				spawnPos.z += dimensions.Dim1.z;

				newEntity.Handle = World::CreatePed(model, spawnPos, Vector3(0, 0, spoocam.Rotation_get().z), false);
				if (unloadModel)
					model.Unload();
			}

			GTAped ep = newEntity.Handle;
			SET_NETWORK_ID_CAN_MIGRATE(PED_TO_NET(newEntity.Handle.Handle()), true);
			newEntity.Handle.FreezePosition(bFreezePos);
			newEntity.Handle.Dynamic_set(bDynamic);
			newEntity.Handle.LodDistance_set(1000000);
			newEntity.Handle.MissionEntity_set(true);
			newEntity.Handle.SetInvincible(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetExplosionProof(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetMeleeProof(Settings::bSpawnInvincibleEntities);
			newEntity.IsStill = Settings::bSpawnStillPeds;
			ep.BlockPermanentEvents_set(Settings::bSpawnStillPeds);

			SET_PED_CAN_PLAY_AMBIENT_ANIMS(ep.Handle(), true);
			SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(ep.Handle(), true);
			SET_PED_CAN_PLAY_GESTURE_ANIMS(ep.Handle(), true);
			SET_PED_CAN_PLAY_VISEME_ANIMS(ep.Handle(), true, TRUE);
			SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(ep.Handle(), true);

			SET_PED_PATH_CAN_USE_CLIMBOVERS(ep.Handle(), true);
			SET_PED_PATH_CAN_USE_LADDERS(ep.Handle(), true);
			SET_PED_PATH_CAN_DROP_FROM_HEIGHT(ep.Handle(), true);
			//SET_PED_PATH_PREFER_TO_AVOID_WATER(ep.Handle(), true);
			//SET_PED_PATH_AVOID_FIRE(ep.Handle(), true);
			SET_PED_COMBAT_ABILITY(ep.Handle(), 2);
			SET_PED_COMBAT_MOVEMENT(ep.Handle(), 2);
			ep.CanSwitchWeapons_set(false);
			model.LoadCollision(100);
			newEntity.Handle.IsCollisionEnabled_set(bCollision);
			model.Unload();

			newEntity.Type = (EntityType)newEntity.Handle.Type();

			if (name.length() > 0)
				newEntity.HashName = name;
			else
			{
				newEntity.HashName = get_ped_model_label(model, false);
				if (newEntity.HashName.length() == 0)
					newEntity.HashName = int_to_hexstring(model.hash, true);
			}

			newEntity.Dynamic = bDynamic;

			AddEntityToDb(newEntity);

			return newEntity;
		}
		SpoonerEntity AddVehicle(const GTAmodel::Model& model, const std::string& name, bool unloadModel)
		{
			if (Databases::EntityDb.size() >= GTA_MAX_ENTITIES)
			{
				Game::Print::PrintBottomLeft("~r~Error:~s~ Max spawn count reached.");
				addlog(ige::LogType::LOG_WARNING, "Failed to add vehicle, max spawn count " + std::to_string(GTA_MAX_ENTITIES) + " Reached", __FILENAME__);
				return SpoonerEntity();
			}
			if (!model.IsInCdImage())
			{
				Game::Print::PrintError_InvalidModel();
				return SpoonerEntity();
			}

			GTAped myPed = PLAYER_PED_ID();
			SpoonerEntity newEntity;
			const ModelDimensions& dimensions = model.Dimensions();
			bool bDynamic = Settings::bSpawnDynamicVehicles;
			bool bFreezePos = !bDynamic;
			bool bCollision = true;

			auto& spoocam = SpoonerMode::spoonerModeCamera;

			if (!spoocam.IsActive())
			{
				GTAentity myPedOrVehicle = myPed.IsInVehicle() ? (GTAentity)myPed.CurrentVehicle() : (GTAentity)myPed;

				newEntity.Handle = World::CreateVehicle(model, myPedOrVehicle.GetOffsetInWorldCoords(0, myPedOrVehicle.Dim1().y + 3.6f + dimensions.Dim2.y, 0), myPedOrVehicle.Rotation_get(), false);
				if (unloadModel)
					model.Unload();
				if (!myPedOrVehicle.IsInAir())
					SET_VEHICLE_ON_GROUND_PROPERLY(newEntity.Handle.Handle(), 0.0f);
			}
			else
			{
				Vector3 spawnPos = spoocam.RaycastForCoord(Vector2(0.0f, 0.0f), 0, 120.0f, 30.0f + dimensions.Dim2.y);
				spawnPos.z += dimensions.Dim1.z;

				newEntity.Handle = World::CreateVehicle(model, spawnPos, Vector3(0, 0, spoocam.Rotation_get().z), false);
				if (unloadModel) model.Unload();
			}

			SET_NETWORK_ID_CAN_MIGRATE(VEH_TO_NET(newEntity.Handle.Handle()), true);
			SET_VEHICLE_MOD_KIT(newEntity.Handle.Handle(), 0);
			SET_VEHICLE_DIRT_LEVEL(newEntity.Handle.Handle(), 0.0f);
			SET_VEHICLE_ENVEFF_SCALE(newEntity.Handle.Handle(), 0.3f);
			GTAvehicle(newEntity.Handle).CloseAllDoors(true);
			newEntity.Handle.FreezePosition(bFreezePos);
			newEntity.Handle.Dynamic_set(bDynamic);
			newEntity.Handle.LodDistance_set(1000000);
			newEntity.Handle.MissionEntity_set(true);
			newEntity.Handle.SetInvincible(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetExplosionProof(Settings::bSpawnInvincibleEntities);
			newEntity.Handle.SetMeleeProof(Settings::bSpawnInvincibleEntities);
			model.LoadCollision(100);
			newEntity.Handle.IsCollisionEnabled_set(bCollision);
			model.Unload();

			newEntity.Type = (EntityType)newEntity.Handle.Type();

			if (name.length() > 0)
				newEntity.HashName = name;
			else
			{
				newEntity.HashName = get_vehicle_model_label(model, false);
				if (newEntity.HashName.length() == 0)
					newEntity.HashName = int_to_hexstring(model.hash, true);
			}

			newEntity.Dynamic = bDynamic;

			AddEntityToDb(newEntity);

			return newEntity;
		}
		SpoonerEntity AddEntityOfType(const EntityType& type, const GTAmodel::Model& model, const std::string& name)
		{
			switch (type)
			{
			case EntityType::PROP: return AddProp(model, name); break;
			case EntityType::PED: return AddPed(model, name); break;
			case EntityType::VEHICLE: return AddVehicle(model, name); break;
			}
			return SpoonerEntity();
		}

		SpoonerEntity CopyEntity(SpoonerEntity orig, bool isInDb, bool addToDb, UINT8 copyAttachments, bool unloadModel, UINT8 currAtir)
		{
			if (!orig.Handle.Exists())
				return SpoonerEntity();

			bool bOrigWasMissionEntity = orig.Handle.MissionEntity_get();
			if (!bOrigWasMissionEntity)
			{
				orig.Handle.MissionEntity_set(true);
				WAIT(20);
			}
			SpoonerEntity newEntity(orig);
			bool bDynamic = orig.Dynamic;
			bool bFreezePos = orig.Handle.IsPositionFrozen();
			newEntity.Handle.Dynamic_set(false);
			newEntity.Handle.FreezePosition(true);

			GTAped myPed = PLAYER_PED_ID();
			bool isThisMyPed = orig.Handle.Handle() == myPed.Handle();

			bool bTaskSeqIsActive = false;
			if (isInDb)
			{
				bool bTaskSeqIsEmpty = orig.TaskSequence.empty();
				bTaskSeqIsActive = orig.TaskSequence.IsActive();
				newEntity.TaskSequence.AllTasks().clear();
				newEntity.TaskSequence.Reset();
				auto& oldTaskSeqTasks = orig.TaskSequence.AllTasks();

				if (!bTaskSeqIsEmpty)
				{
					for (STSTask* tskPtr : oldTaskSeqTasks)
					{
						if (tskPtr != nullptr)
						{
							STSTask* newtskPtr = newEntity.TaskSequence.AddTask(tskPtr->type);
							if (newtskPtr != nullptr)
							{
								newtskPtr->Assign(tskPtr);
							}
						}
					}
					if (bTaskSeqIsActive) newEntity.TaskSequence.Start();
				}
			}

			EntityType entType = (EntityType)orig.Handle.Type();
			if (entType == EntityType::PROP)
			{
				newEntity.Handle = World::CreateProp(orig.Handle.Model(), orig.Handle.Position_get(), orig.Handle.Rotation_get(), bDynamic, false);
				SET_NETWORK_ID_CAN_MIGRATE(OBJ_TO_NET(newEntity.Handle.Handle()), true);
				GTAprop eo = newEntity.Handle;

				if (orig.TextureVariation != -1)
					SET_OBJECT_TINT_INDEX(eo.Handle(), orig.TextureVariation);
			}
			else if (entType == EntityType::PED)
			{
				//std::vector<s_Weapon_Components_Tint> weaponsBackup;
				GTAped ep;
				GTAped origPed = orig.Handle;

				//newEntity.Handle = World::CreatePed(orig.Handle.Model(), orig.Handle.Position_get(), orig.Handle.Rotation_get(), false);
				newEntity.Handle = origPed.Clone(origPed.Heading_get(), true, true);
				ep = newEntity.Handle;

				const auto& movGrpStr = get_ped_movement_clipset(orig.Handle);
				if (!movGrpStr.empty())
					set_ped_movement_clipset(ep, movGrpStr);
				const auto& wMovGrpStr = get_ped_weapon_movement_clipset(orig.Handle);
				if (!wMovGrpStr.empty())
					set_ped_weapon_movement_clipset(ep, wMovGrpStr);

				ep.Position_set(origPed.Position_get());
				ep.Rotation_set(origPed.Rotation_get());
				sub::PedHeadFeatures_catind::vPedHeads[ep.Handle()] = sub::PedHeadFeatures_catind::vPedHeads[origPed.Handle()];
				sub::PedDamageTextures_catind::vPedsAndDamagePacks[ep.Handle()] = sub::PedDamageTextures_catind::vPedsAndDamagePacks[origPed.Handle()];
				sub::PedDecals_catind::vPedsAndDecals[ep.Handle()] = sub::PedDecals_catind::vPedsAndDecals[origPed.Handle()];
				//GTAped(orig.Handle).StoreWeaponsInArray(weaponsBackup);
				//GTAped(newEntity.Handle).GiveWeaponsFromArray(weaponsBackup);
				SET_NETWORK_ID_CAN_MIGRATE(ep.NetID(), true);
				ep.BlockPermanentEvents_set(orig.IsStill);
				SET_PED_CONFIG_FLAG(ep.Handle(), 223, GET_PED_CONFIG_FLAG(origPed.Handle(), 223, false));

				SET_PED_CAN_PLAY_AMBIENT_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_GESTURE_ANIMS(ep.Handle(), true);
				SET_PED_CAN_PLAY_VISEME_ANIMS(ep.Handle(), true, TRUE);
				SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(ep.Handle(), true);

				if (!bTaskSeqIsActive && IS_PED_USING_SCENARIO(orig.Handle.Handle(), orig.LastAnimation.name.c_str()))
				{
					WAIT(40);
					ep.Task().StartScenario(orig.LastAnimation.name, -1, false);
				}
				if (!bTaskSeqIsActive && IS_ENTITY_PLAYING_ANIM(orig.Handle.Handle(), orig.LastAnimation.dict.c_str(), orig.LastAnimation.name.c_str(), 3))
				{
					ep.Task().PlayAnimation(orig.LastAnimation.dict, orig.LastAnimation.name);
				}

				const auto& facialMoodStr = get_ped_facial_mood(orig.Handle);
				if (!facialMoodStr.empty())
					set_ped_facial_mood(ep, facialMoodStr);

				ep.Armour_set(origPed.Armour_get());
				ep.Weapon_set(origPed.Weapon_get());
				ep.CanSwitchWeapons_set(false);
				SET_PED_PATH_CAN_USE_CLIMBOVERS(ep.Handle(), true);
				SET_PED_PATH_CAN_USE_LADDERS(ep.Handle(), true);
				SET_PED_PATH_CAN_DROP_FROM_HEIGHT(ep.Handle(), true);
				//SET_PED_PATH_PREFER_TO_AVOID_WATER(ep.Handle(), true);
				//SET_PED_PATH_AVOID_FIRE(ep.Handle(), true);
				SET_PED_COMBAT_ABILITY(ep.Handle(), 2);
				SET_PED_COMBAT_MOVEMENT(ep.Handle(), 2);
				Hash oldRelationshipGrp;
				RelationshipManagement::GetPedRelationshipGroup(orig.Handle, oldRelationshipGrp);
				RelationshipManagement::SetPedRelationshipGroup(ep, oldRelationshipGrp);
			}
			else if (entType == EntityType::VEHICLE)
			{
				//newEntity.Handle = World::CreateVehicle(orig.Handle.Model(), orig.Handle.Position_get(), orig.Handle.Rotation_get(), false);
				newEntity.Handle = clone_vehicle(orig.Handle);
				newEntity.Handle.Position_set(orig.Handle.Position_get());
				newEntity.Handle.Rotation_set(orig.Handle.Rotation_get());
				SET_NETWORK_ID_CAN_MIGRATE(VEH_TO_NET(newEntity.Handle.Handle()), true);
			}

			newEntity.Handle.FreezePosition(bFreezePos);
			newEntity.Handle.Dynamic_set(bDynamic);
			newEntity.Handle.LodDistance_set(1000000);
			newEntity.Handle.MissionEntity_set(true);
			newEntity.Handle.SetVisible(orig.Handle.IsVisible());
			newEntity.Handle.SetInvincible(orig.Handle.IsInvincible());
			newEntity.Handle.SetBulletProof(orig.Handle.IsBulletProof());
			newEntity.Handle.IsCollisionEnabled_set(orig.Handle.IsCollisionEnabled_get());
			newEntity.Handle.SetExplosionProof(orig.Handle.IsExplosionProof());
			newEntity.Handle.SetFireProof(orig.Handle.IsFireProof());
			newEntity.Handle.SetMeleeProof(orig.Handle.IsMeleeProof());
			newEntity.Handle.SetOnlyDamagedByPlayer(orig.Handle.IsOnlyDamagedByPlayer());
			newEntity.Handle.SetOnFire(orig.Handle.IsOnFire());
			newEntity.Handle.Alpha_set(orig.Handle.Alpha_get());
			newEntity.Handle.Health_set(orig.Handle.Health_get());

			orig.Handle.MissionEntity_set(bOrigWasMissionEntity);

			if (orig.AttachmentArgs.isAttached && !currAtir)
			{
				GTAentity attTo;
				if (GetEntityThisEntityIsAttachedTo(orig.Handle, attTo))
				{
					EntityManagement::AttachEntity(newEntity, attTo, orig.AttachmentArgs.boneIndex, orig.AttachmentArgs.offset, orig.AttachmentArgs.rotation);
				}
				// else set both isAttached to false??
			}

			// fx lops
			for (auto& ptfxlop : sub::Ptfx_catind::_fxlops)
			{
				if (ptfxlop.entity == orig.Handle)
				{
					sub::Ptfx_catind::PtfxlopS newPtfxLop;
					newPtfxLop.entity = newEntity.Handle;
					newPtfxLop.asset = ptfxlop.asset.c_str();
					newPtfxLop.fx = ptfxlop.fx.c_str();
					sub::Ptfx_catind::_fxlops.push_back(newPtfxLop);
					break;
				}
			}

			if (isInDb && copyAttachments)
			{
				std::set<Hash> atirModelHashes;
				GTAentity attTo;
				for (auto& e : Databases::EntityDb)
				{
					if (GetEntityThisEntityIsAttachedTo(e.Handle, attTo) && attTo == orig.Handle)
					{
						atirModelHashes.insert(e.Handle.Model().hash);
						auto newAtt = CopyEntity(e, true, false, copyAttachments, false, currAtir + 1);
						EntityManagement::AttachEntity(newAtt, newEntity.Handle, e.AttachmentArgs.boneIndex, e.AttachmentArgs.offset, e.AttachmentArgs.rotation);
						if (addToDb) Databases::EntityDb.push_back(newAtt);
					}
				}
				if (unloadModel)
				{
					for (Model amh : atirModelHashes)
						amh.Unload();
				}
			}

			//bug?
			orig.Handle.FreezePosition(bFreezePos);
			orig.Handle.Dynamic_set(bDynamic);

			if (unloadModel)
				newEntity.Handle.Model().Unload();
			if (addToDb)
				Databases::EntityDb.push_back(newEntity);
			return newEntity;
		}

		void DetachEntity(SpoonerEntity& ent)
		{
			bool isOnTheLine = NETWORK_IS_IN_SESSION() != 0;
			bool bHasCollision = ent.Handle.IsCollisionEnabled_get();
			if (isOnTheLine)
				ent.Handle.RequestControl();
			ent.Handle.Detach();
			ent.AttachmentArgs.isAttached = false;
			ent.AttachmentArgs.boneIndex = 0;
			ent.AttachmentArgs.offset.clear();
			ent.AttachmentArgs.rotation.clear();
			ent.Handle.IsCollisionEnabled_set(bHasCollision);

			GTAentity attTo;
			for (auto& e : Databases::EntityDb)
			{
				if (GetEntityThisEntityIsAttachedTo(e.Handle, attTo) && attTo == ent.Handle)
				{
					AttachEntity(e, attTo, e.AttachmentArgs.boneIndex, e.AttachmentArgs.offset, e.AttachmentArgs.rotation);
				}
			}
		}
		bool GetEntityThisEntityIsAttachedTo(GTAentity& from, GTAentity& to)
		{
			/*for (auto& e : _worldEntities)
			{
			if (IS_ENTITY_ATTACHED_TO_ENTITY(from.Handle.Handle(), to.Handle()))
			{
			to = e;
			return true;
			}
			}
			return false;*/
			if (from.IsAttached())
			{
				to = GET_ENTITY_ATTACHED_TO(from.Handle());
				return true;
			}
			to = 0;
			return false;
		}
		void AttachEntity(SpoonerEntity& ent, GTAentity to, int boneIndex, const Vector3& offset, const Vector3& rotation)
		{
			if (ent.Handle.Handle() != to.Handle())
			{
				bool isOnTheLine = NETWORK_IS_IN_SESSION() != 0;
				bool bHasCollision = ent.Handle.IsCollisionEnabled_get();
				bool wheelsAreInvis = are_vehicle_wheels_invisible(ent.Handle);
				if (isOnTheLine)
				{
					ent.Handle.RequestControl();
					//to.RequestControl();
				}
				ent.Handle.AttachTo(to, boneIndex, bHasCollision, offset, rotation);
				ent.AttachmentArgs.isAttached = true;
				ent.AttachmentArgs.boneIndex = boneIndex;
				ent.AttachmentArgs.offset = offset;
				ent.AttachmentArgs.rotation = rotation;
				ent.Handle.Dynamic_set(ent.Dynamic);
				//ent.Handle.IsCollisionEnabled_set(bHasCollision);
				SET_ENTITY_LIGHTS(ent.Handle.Handle(), 0);
				if (wheelsAreInvis)
					set_vehicle_wheels_invisible(ent.Handle, true);
			}
		}
		void AttachEntityInit(SpoonerEntity& ent, GTAentity to, bool bAttachWithRelativePosRot)
		{
			if (to.IsAttachedTo(ent.Handle))
			{
				SpoonerEntity to1;
				to1.Handle = to;
				auto to1ind = EntityManagement::GetEntityIndexInDb(to1);
				if (to1ind >= 0)
				{
					bool isOnTheLine = NETWORK_IS_IN_SESSION() != 0;
					if (isOnTheLine)
						to1.Handle.RequestControl();
					auto& to1r = Databases::EntityDb[to1ind];
					DetachEntity(to1r);
				}
			}
			DetachEntity(ent);
			if (bAttachWithRelativePosRot)
			{
				AttachEntity(ent, to, 0, to.GetOffsetGivenWorldCoords(ent.Handle.Position_get()), ent.Handle.Rotation_get() - to.Rotation_get());
			}
			else
			{
				AttachEntity(ent, to, 0, Vector3(), Vector3());
			}
		}

		// Keyboard input
		SpoonerEntity InputEntityIntoDb(const EntityType& type)
		{
			std::string inputStr = Game::InputBox("", 64U, "Input model name:");
			if (inputStr.length() > 0)
			{
				return AddEntityOfType(type, GET_HASH_KEY(inputStr), inputStr);
			}
			return SpoonerEntity();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SpoonerInputEntityIntoDb, std::string(), 64U, "Input model name:");
			//OnscreenKeyboard::State::arg1._int = static_cast<int>(type);
		}

		void ShowBoxAroundEntity(const GTAentity& ent, bool showPoly, RgbS colour)
		{
			if (ent.Exists())
			{
				const auto& ent_md = ent.ModelDimensions();

				// I've used the opposite Z dimensions for reasons
				const auto& boxUpperLeftRear = ent.GetOffsetInWorldCoords(-ent_md.Dim2.x, -ent_md.Dim2.y, ent_md.Dim2.z);
				const auto& boxUpperRightRear = ent.GetOffsetInWorldCoords(ent_md.Dim1.x, -ent_md.Dim2.y, ent_md.Dim2.z);
				const auto& boxLowerLeftRear = ent.GetOffsetInWorldCoords(-ent_md.Dim2.x, -ent_md.Dim2.y, -ent_md.Dim1.z);
				const auto& boxLowerRightRear = ent.GetOffsetInWorldCoords(ent_md.Dim1.x, -ent_md.Dim2.y, -ent_md.Dim1.z);

				const auto& boxUpperLeftFront = ent.GetOffsetInWorldCoords(-ent_md.Dim2.x, ent_md.Dim1.y, ent_md.Dim2.z);
				const auto& boxUpperRightFront = ent.GetOffsetInWorldCoords(ent_md.Dim1.x, ent_md.Dim1.y, ent_md.Dim2.z);
				const auto& boxLowerLeftFront = ent.GetOffsetInWorldCoords(-ent_md.Dim2.x, ent_md.Dim1.y, -ent_md.Dim1.z);
				const auto& boxLowerRightFront = ent.GetOffsetInWorldCoords(ent_md.Dim1.x, ent_md.Dim1.y, -ent_md.Dim1.z);

				const RGBA& lineColour = colour.ToRGBA(250);
				const RGBA& polyColour = colour.ToRGBA(100);

				World::DrawLine(boxUpperLeftRear, boxUpperRightRear, lineColour);
				World::DrawLine(boxLowerLeftRear, boxLowerRightRear, lineColour);
				World::DrawLine(boxUpperLeftRear, boxLowerLeftRear, lineColour);
				World::DrawLine(boxUpperRightRear, boxLowerRightRear, lineColour);

				World::DrawLine(boxUpperLeftFront, boxUpperRightFront, lineColour);
				World::DrawLine(boxLowerLeftFront, boxLowerRightFront, lineColour);
				World::DrawLine(boxUpperLeftFront, boxLowerLeftFront, lineColour);
				World::DrawLine(boxUpperRightFront, boxLowerRightFront, lineColour);

				World::DrawLine(boxUpperLeftRear, boxUpperLeftFront, lineColour);
				World::DrawLine(boxUpperRightRear, boxUpperRightFront, lineColour);
				World::DrawLine(boxLowerLeftRear, boxLowerLeftFront, lineColour);
				World::DrawLine(boxLowerRightRear, boxLowerRightFront, lineColour);

				if (showPoly)
				{
					World::DrawPoly(boxUpperRightRear, boxLowerRightRear, boxUpperLeftRear, polyColour);
					World::DrawPoly(boxUpperLeftRear, boxLowerLeftRear, boxLowerRightRear, polyColour);

					World::DrawPoly(boxUpperRightFront, boxLowerRightFront, boxUpperLeftFront, polyColour);
					World::DrawPoly(boxUpperLeftFront, boxLowerLeftFront, boxLowerRightFront, polyColour);

					World::DrawPoly(boxUpperLeftFront, boxLowerLeftFront, boxUpperLeftRear, polyColour);
					World::DrawPoly(boxUpperLeftRear, boxLowerLeftFront, boxLowerLeftRear, polyColour);

					World::DrawPoly(boxUpperRightFront, boxLowerRightFront, boxUpperRightRear, polyColour);
					World::DrawPoly(boxUpperRightRear, boxLowerRightFront, boxLowerRightRear, polyColour);

					World::DrawPoly(boxUpperRightFront, boxUpperRightRear, boxUpperLeftRear, polyColour);
					World::DrawPoly(boxUpperLeftFront, boxUpperRightFront, boxUpperLeftRear, polyColour);

					World::DrawPoly(boxLowerRightFront, boxLowerRightRear, boxLowerLeftRear, polyColour);
					World::DrawPoly(boxLowerLeftFront, boxLowerRightFront, boxLowerLeftRear, polyColour);
				}
			}
		}
		void ShowArrowAboveEntity(const GTAentity& ent, RGBA colour)
		{
			if (ent.Exists())
			{
				const auto& soe_pos = ent.Position_get();
				const auto& soe_md = ent.ModelDimensions();
				const auto& markerPos = soe_pos + Vector3(0, 0, (std::max)(soe_md.Dim1.z, soe_md.Dim2.z) + 1.4f); // May not be at the right position if the entity is tilted
				World::DrawMarker(MarkerType::UpsideDownCone, markerPos, Vector3(), Vector3(), Vector3(1, 1, 2), colour);
			}
		}
		void DrawRadiusDisplayingMarker(const Vector3& pos, float radius, RGBA colour)
		{
			World::DrawMarker(MarkerType::DebugSphere, pos, Vector3(), Vector3(), Vector3(radius, radius, radius), colour);
		}
	}

}




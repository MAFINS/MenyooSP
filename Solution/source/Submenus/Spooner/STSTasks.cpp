/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "STSTasks.h"

#include "..\..\macros.h"

#include "STSTask.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Menu\submenu_enum.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAped.h"
#include "..\..\Scripting\GTAblip.h"
#include "..\..\Scripting\Game.h"
#include "..\..\Util\StringManip.h"
#include "..\..\Scripting\enums.h"
#include "..\..\Scripting\World.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Scripting\Model.h"
#include "..\..\Natives\types.h" //RGBA
#include "..\..\Scripting\PTFX.h"

#include "SpoonerEntity.h"
#include "EntityManagement.h"
#include "Submenus_TaskSequence.h"

#include <pugixml\src\pugixml.hpp>
#include <vector>
#include <string>
#include <Windows.h> //GetTickCount

namespace sub::Spooner
{
	namespace STSTasks
	{
		Nothing::Nothing()
		{
			this->type = STSTaskType::Nothing;
			this->submenu = Submenus::Sub_TaskSequence::Nothing;
			this->duration = 22000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void Nothing::Run(void* ve)
		{
		}

		SnapTasks::SnapTasks()
		{
			this->type = STSTaskType::SnapTasks;
			this->submenu = Submenus::Sub_TaskSequence::Nothing;
			this->duration = -1; // No settings
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void SnapTasks::RunP(GTAped& ep)
		{
			ep.Task().ClearLookAt();
			ep.Task().ClearAllImmediately();
		}

		void SetHealth::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("HealthValue").text() = this->healthValue;
		}
		void SetHealth::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->healthValue = nodeTask.child("HealthValue").text().as_int();
		}
		void SetHealth::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SetHealth>();
			this->healthValue = otherTskT->healthValue;
		}
		SetHealth::SetHealth()
		{
			this->type = STSTaskType::SetHealth;
			this->submenu = Submenus::Sub_TaskSequence::SetHealth;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->healthValue = 500;
		}
		void SetHealth::Run(void* ve)
		{
			reinterpret_cast<SpoonerEntity*>(ve)->Handle.Health_set(this->healthValue);
		}

		void AddBlip::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Label").text() = this->label.c_str();
			nodeTask.append_child("Colour").text() = this->colour;
			nodeTask.append_child("Alpha").text() = this->alpha;
			nodeTask.append_child("Icon").text() = this->icon;
			nodeTask.append_child("Scale").text() = this->scale;
			nodeTask.append_child("IsFlashing").text() = this->isFlashing;
			nodeTask.append_child("IsFriendly").text() = this->isFriendly;
			nodeTask.append_child("IsShortRange").text() = this->isShortRange;
			nodeTask.append_child("ShowRoute").text() = this->showRoute;
			nodeTask.append_child("ShowNumber").text() = this->showNumber;
		}
		void AddBlip::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->label = nodeTask.child("Label").text().as_string();
			this->colour = nodeTask.child("Colour").text().as_int();
			this->alpha = nodeTask.child("Alpha").text().as_uint();
			this->icon = nodeTask.child("Icon").text().as_int();
			this->scale = nodeTask.child("Scale").text().as_float();
			this->isFlashing = nodeTask.child("IsFlashing").text().as_bool();
			this->isFriendly = nodeTask.child("IsFriendly").text().as_bool();
			this->isShortRange = nodeTask.child("IsShortRange").text().as_bool();
			this->showRoute = nodeTask.child("ShowRoute").text().as_bool();
			this->showNumber = nodeTask.child("ShowNumber").text().as_int();
		}
		void AddBlip::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AddBlip>();
			this->blip = otherTskT->blip;
			this->label = otherTskT->label;
			this->colour = otherTskT->colour;
			this->alpha = otherTskT->alpha;
			this->icon = otherTskT->icon;
			this->scale = otherTskT->scale;
			this->isFlashing = otherTskT->isFlashing;
			this->isFriendly = otherTskT->isFriendly;
			this->isShortRange = otherTskT->isShortRange;
			this->showRoute = otherTskT->showRoute;
			this->showNumber = otherTskT->showNumber;
		}
		AddBlip::AddBlip()
		{
			this->type = STSTaskType::AddBlip;
			this->submenu = Submenus::Sub_TaskSequence::AddBlip;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			//this->blip = GTAblip();
			//this->label = std::string();
			this->colour = BlipColour::White;
			this->alpha = 255U;
			this->icon = BlipIcon::Standard;
			this->scale = 0.8f;
			this->isFlashing = false;
			this->isFriendly = false;
			this->isShortRange = false;
			this->showRoute = false;
			this->showNumber = 0;
		}
		void AddBlip::Run(void* ve)
		{
			SpoonerEntity& e = *reinterpret_cast<SpoonerEntity*>(ve);

			//GTAblip(e.Handle.CurrentBlip()).Remove();
			if (!GTAblip(e.Handle.CurrentBlip()).Exists()) // Only add new blip if none present already
			{
				this->blip = e.Handle.AddBlip();
				this->blip.SetFriendly(this->isFriendly);
				this->blip.SetFlashing(this->isFlashing);
				this->blip.SetIcon(this->icon);
				this->blip.SetScale(this->scale);
				this->blip.SetColour(this->colour);
				this->blip.SetAlpha(this->alpha);
				if (!this->label.empty())
					this->blip.SetBlipName(this->label);
				this->blip.SetShortRange(this->isShortRange);
				this->blip.ShowRoute(this->showRoute);
				if (this->showNumber != 0)
					this->blip.ShowNumber(this->showNumber);
			}
		}

		RemoveBlip::RemoveBlip()
		{
			this->type = STSTaskType::RemoveBlip;
			this->submenu = Submenus::Sub_TaskSequence::RemoveBlip;
			this->duration = -1; // No settings
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void RemoveBlip::Run(void* ve)
		{
			SpoonerEntity& e = *reinterpret_cast<SpoonerEntity*>(ve);

			GTAblip(e.Handle.CurrentBlip()).Remove();
		}

		Pause::Pause()
		{
			this->type = STSTaskType::Pause;
			this->submenu = Submenus::Sub_TaskSequence::Pause;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
		}
		void Pause::RunP(GTAped& ep)
		{
			ep.Task().Wait(this->durationAfterLife > 0 ? -1 : this->duration);
		}

		UsePhone::UsePhone()
		{
			this->type = STSTaskType::UsePhone;
			this->submenu = Submenus::Sub_TaskSequence::UsePhone;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
		}
		void UsePhone::RunP(GTAped& ep)
		{
			this->durationAfterLife > 0 ? ep.Task().UseMobilePhone() : ep.Task().UseMobilePhone(this->duration);
		}

		void ThrowProjectile::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodeTargetPos = nodeTask.append_child("TargetPos");
			nodeTargetPos.append_attribute("X") = this->targetPos.x;
			nodeTargetPos.append_attribute("Y") = this->targetPos.y;
			nodeTargetPos.append_attribute("Z") = this->targetPos.z;
		}
		void ThrowProjectile::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodeTargetPos = nodeTask.child("TargetPos");
			this->targetPos.x = nodeTargetPos.attribute("X").as_float();
			this->targetPos.y = nodeTargetPos.attribute("Y").as_float();
			this->targetPos.z = nodeTargetPos.attribute("Z").as_float();
		}
		void ThrowProjectile::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ThrowProjectile>();
			this->targetPos = otherTskT->targetPos;
		}
		ThrowProjectile::ThrowProjectile()
		{
			this->type = STSTaskType::ThrowProjectile;
			this->submenu = Submenus::Sub_TaskSequence::ThrowProjectile;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void ThrowProjectile::RunP(GTAped& ep)
		{
			ep.Task().ThrowProjectile(this->targetPos);
		}

		Writhe::Writhe()
		{
			this->type = STSTaskType::Writhe;
			this->submenu = Submenus::Sub_TaskSequence::Writhe;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
		}
		void Writhe::RunP(GTAped& ep)
		{
			//if (!IS_PED_IN_WRITHE(ep.Handle()))
			TASK_WRITHE(ep.Handle(), PLAYER_PED_ID(), this->durationAfterLife > 0 ? -1 : this->duration, 0, false, 0);
			//ep.GiveNM(NMString::nm0526_bodyWrithe);
		}

		void FaceDirection::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Heading").text() = this->heading;
		}
		void FaceDirection::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->heading = nodeTask.child("Heading").text().as_float();
		}
		void FaceDirection::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FaceDirection>();
			this->heading = otherTskT->heading;
		}
		FaceDirection::FaceDirection()
		{
			this->type = STSTaskType::FaceDirection;
			this->submenu = Submenus::Sub_TaskSequence::FaceDirection;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->heading = 0.0f;
		}
		void FaceDirection::RunP(GTAped& ep)
		{
			ep.Task().TurnTo(ep.Position_get().PointOnCircle(2.0f, this->heading), this->durationAfterLife > 0 ? -1 : this->duration + 200);
		}

		void FaceEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void FaceEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void FaceEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FaceEntity>();
			this->targetEntity = otherTskT->targetEntity;
		}
		FaceEntity::FaceEntity()
		{
			this->type = STSTaskType::FaceEntity;
			this->submenu = Submenus::Sub_TaskSequence::FaceEntity;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			//this->targetEntity = 0;
		}
		void FaceEntity::RunP(GTAped& ep)
		{
			ep.Task().TurnTo(this->targetEntity, this->durationAfterLife > 0 ? -1 : this->duration + 200);
		}
		void FaceEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void LookAtCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodePos = nodeTask.append_child("Position");
			nodePos.append_attribute("X") = this->coord.x;
			nodePos.append_attribute("Y") = this->coord.y;
			nodePos.append_attribute("Z") = this->coord.z;
		}
		void LookAtCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodePos = nodeTask.child("Position");
			this->coord.x = nodePos.attribute("X").as_float();
			this->coord.y = nodePos.attribute("Y").as_float();
			this->coord.z = nodePos.attribute("Z").as_float();
		}
		void LookAtCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::LookAtCoord>();
			this->coord = otherTskT->coord;
		}
		LookAtCoord::LookAtCoord()
		{
			this->type = STSTaskType::LookAtCoord;
			this->submenu = Submenus::Sub_TaskSequence::LookAtCoord;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
		}
		void LookAtCoord::RunP(GTAped& ep)
		{
			ep.Task().LookAt(this->coord, this->durationAfterLife > 0 ? -1 : this->duration);
		}
		void LookAtCoord::EndP(GTAped& ep)
		{
			if (this->durationAfterLife == 0)
			{
				ep.Task().ClearLookAt();
			}
		}

		void LookAtEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void LookAtEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void LookAtEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::LookAtEntity>();
			this->targetEntity = otherTskT->targetEntity;
		}
		LookAtEntity::LookAtEntity()
		{
			this->type = STSTaskType::LookAtEntity;
			this->submenu = Submenus::Sub_TaskSequence::LookAtEntity;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			//this->targetEntity = 0;
		}
		void LookAtEntity::RunP(GTAped& ep)
		{
			ep.Task().LookAt(this->targetEntity, this->durationAfterLife > 0 ? -1 : this->duration);
		}
		void LookAtEntity::EndP(GTAped& ep)
		{
			if (this->durationAfterLife == 0)
			{
				ep.Task().ClearLookAt();
			}
		}
		void LookAtEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void TeleportToCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("TakeVehicleToo").text() = this->takeVehicleToo;

			auto& nodeDest = nodeTask.append_child("Destination");
			nodeDest.append_attribute("X") = this->destination.x;
			nodeDest.append_attribute("Y") = this->destination.y;
			nodeDest.append_attribute("Z") = this->destination.z;
		}
		void TeleportToCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->takeVehicleToo = nodeTask.child("TakeVehicleToo").text().as_bool();

			auto& nodeDest = nodeTask.child("Destination");
			this->destination.x = nodeDest.attribute("X").as_float();
			this->destination.y = nodeDest.attribute("Y").as_float();
			this->destination.z = nodeDest.attribute("Z").as_float();
		}
		void TeleportToCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::TeleportToCoord>();
			this->takeVehicleToo = otherTskT->takeVehicleToo;
			this->destination = otherTskT->destination;
		}
		TeleportToCoord::TeleportToCoord()
		{
			this->type = STSTaskType::TeleportToCoord;
			this->submenu = Submenus::Sub_TaskSequence::TeleportToCoord;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->takeVehicleToo = true;
		}
		void TeleportToCoord::RunP(GTAped& ep)
		{
			if (takeVehicleToo)
			{
				auto& veh = ep.CurrentVehicle();
				(veh.Exists() ? veh : ep).Position_set(this->destination);
				//SET_PED_COORDS_KEEP_VEHICLE(ep.Handle(), this->destination.x, this->destination.y, this->destination.z);
			}
			else
			{
				ep.Position_set(this->destination);
			}
		}

		void SeekCoverAtCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("CanPeakInCover").text() = this->canPeekInCover;

			auto& nodeDest = nodeTask.append_child("CoverPos");
			nodeDest.append_attribute("X") = this->coverPos.x;
			nodeDest.append_attribute("Y") = this->coverPos.y;
			nodeDest.append_attribute("Z") = this->coverPos.z;
		}
		void SeekCoverAtCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->canPeekInCover = nodeTask.child("CanPeakInCover").text().as_bool();

			auto& nodeDest = nodeTask.child("CoverPos");
			this->coverPos.x = nodeDest.attribute("X").as_float();
			this->coverPos.y = nodeDest.attribute("Y").as_float();
			this->coverPos.z = nodeDest.attribute("Z").as_float();
		}
		void SeekCoverAtCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SeekCoverAtCoord>();
			this->canPeekInCover = otherTskT->canPeekInCover;
			this->coverPos = otherTskT->coverPos;
		}
		SeekCoverAtCoord::SeekCoverAtCoord()
		{
			this->type = STSTaskType::SeekCoverAtCoord;
			this->submenu = Submenus::Sub_TaskSequence::SeekCoverAtCoord;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			this->canPeekInCover = true;
		}
		void SeekCoverAtCoord::RunP(GTAped& ep)
		{
			SET_PED_TO_LOAD_COVER(ep.Handle(), true);
			TASK_PUT_PED_DIRECTLY_INTO_COVER(ep.Handle(), this->coverPos.x, this->coverPos.y, this->coverPos.z, this->durationAfterLife > 0 ? -1 : this->duration, true, 0.5f, true, true, 0, false);
			SET_PED_CAN_PEEK_IN_COVER(ep.Handle(), this->canPeekInCover);
			SET_PED_COMBAT_ATTRIBUTES(ep.Handle(), 34, true);
		}

		void SlideToCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Speed").text() = this->speed;
			nodeTask.append_child("Heading").text() = this->heading;

			auto& nodeDest = nodeTask.append_child("Destination");
			nodeDest.append_attribute("X") = this->destination.x;
			nodeDest.append_attribute("Y") = this->destination.y;
			nodeDest.append_attribute("Z") = this->destination.z;
		}
		void SlideToCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speed = nodeTask.child("Speed").text().as_float();
			this->heading = nodeTask.child("Heading").text().as_float();

			auto& nodeDest = nodeTask.child("Destination");
			this->destination.x = nodeDest.attribute("X").as_float();
			this->destination.y = nodeDest.attribute("Y").as_float();
			this->destination.z = nodeDest.attribute("Z").as_float();
		}
		void SlideToCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SlideToCoord>();
			this->speed = otherTskT->speed;
			this->heading = otherTskT->heading;
			this->destination = otherTskT->destination;
		}
		SlideToCoord::SlideToCoord()
		{
			this->type = STSTaskType::SlideToCoord;
			this->submenu = Submenus::Sub_TaskSequence::SlideToCoord;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->speed = 10.0f;
			this->heading = 0.0f;
		}
		void SlideToCoord::RunP(GTAped& ep)
		{
			TASK_PED_SLIDE_TO_COORD(ep.Handle(), this->destination.x, this->destination.y, this->destination.z, this->heading, this->speed);
		}

		void GoToCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Speed").text() = this->speed;

			auto& nodeDest = nodeTask.append_child("Destination");
			nodeDest.append_attribute("X") = this->destination.x;
			nodeDest.append_attribute("Y") = this->destination.y;
			nodeDest.append_attribute("Z") = this->destination.z;
		}
		void GoToCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speed = nodeTask.child("Speed").text().as_float();

			auto& nodeDest = nodeTask.child("Destination");
			if (nodeDest)
			{
				this->destination.x = nodeDest.attribute("X").as_float();
				this->destination.y = nodeDest.attribute("Y").as_float();
				this->destination.z = nodeDest.attribute("Z").as_float();
			}
		}
		void GoToCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::GoToCoord>();
			this->speed = otherTskT->speed;
			this->destination = otherTskT->destination;
		}
		GoToCoord::GoToCoord()
		{
			this->type = STSTaskType::GoToCoord;
			this->submenu = Submenus::Sub_TaskSequence::GoToCoord;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			this->speed = 1.0f;
		}
		void GoToCoord::RunP(GTAped& ep)
		{
			TASK_GO_STRAIGHT_TO_COORD(ep.Handle(), this->destination.x, this->destination.y, this->destination.z, this->speed, this->durationAfterLife > 0 ? -1 : this->duration, Vector3::DirectionToRotation(Vector3::Normalize(this->destination - ep.Position_get())).z, 0.0f);
		}

		void FollowRoute::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Speed").text() = this->speed;

			auto& nodeRoute = nodeTask.append_child("Route");
			for (auto& routePoint : this->route)
			{
				auto& nodeRoutePoint = nodeRoute.append_child("Coord");
				nodeRoutePoint.append_attribute("X") = routePoint.x;
				nodeRoutePoint.append_attribute("Y") = routePoint.y;
				nodeRoutePoint.append_attribute("Z") = routePoint.z;
			}
		}
		void FollowRoute::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speed = nodeTask.child("Speed").text().as_float();

			this->route.clear();
			auto& nodeRoute = nodeTask.child("Route");
			for (auto& nodeRoutePoint = nodeRoute.first_child(); nodeRoutePoint; nodeRoutePoint = nodeRoutePoint.next_sibling())
			{
				Vector3 nrp;
				nrp.x = nodeRoutePoint.attribute("X").as_float();
				nrp.y = nodeRoutePoint.attribute("Y").as_float();
				nrp.z = nodeRoutePoint.attribute("Z").as_float();
				this->route.push_back(nrp);
			}
		}
		void FollowRoute::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FollowRoute>();
			this->speed = otherTskT->speed;
			this->route = otherTskT->route;
		}
		FollowRoute::FollowRoute()
		{
			this->type = STSTaskType::FollowRoute;
			this->submenu = Submenus::Sub_TaskSequence::FollowRoute;
			this->duration = 40000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->speed = 1.0f;
		}
		void FollowRoute::RunP(GTAped& ep)
		{
			ep.Task().FollowPointRoute(this->route, this->speed);
		}

		void FollowEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Speed").text() = this->speed;

			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void FollowEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speed = nodeTask.child("Speed").text().as_float();

			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void FollowEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FollowEntity>();
			this->speed = otherTskT->speed;
			this->targetEntity = otherTskT->targetEntity;
		}
		FollowEntity::FollowEntity()
		{
			this->type = STSTaskType::FollowEntity;
			this->submenu = Submenus::Sub_TaskSequence::FollowEntity;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			this->speed = 1.0f;
			//this->targetEntity = 0;
		}
		void FollowEntity::RunP(GTAped& ep)
		{
			TASK_FOLLOW_TO_OFFSET_OF_ENTITY(ep.Handle(), this->targetEntity.Handle(), GET_RANDOM_FLOAT_IN_RANGE(-1.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(-1.5f, 0.5f), 0.0f, this->speed, this->durationAfterLife > 0 ? -1 : this->duration, 0.1f, true);
		}
		void FollowEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void PatrolInRange::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Radius").text() = this->radius;
			auto& nodeCoord = nodeTask.append_child("Coord");
			nodeCoord.append_attribute("X") = this->coord.x;
			nodeCoord.append_attribute("Y") = this->coord.y;
			nodeCoord.append_attribute("Z") = this->coord.z;
		}
		void PatrolInRange::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->radius = nodeTask.child("Radius").text().as_float();
			auto& nodeCoord = nodeTask.child("Coord");
			this->coord.x = nodeCoord.attribute("X").as_float();
			this->coord.y = nodeCoord.attribute("Y").as_float();
			this->coord.z = nodeCoord.attribute("Z").as_float();
		}
		void PatrolInRange::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::PatrolInRange>();
			this->radius = otherTskT->radius;
			this->coord = otherTskT->coord;
		}
		PatrolInRange::PatrolInRange()
		{
			this->type = STSTaskType::PatrolInRange;
			this->submenu = Submenus::Sub_TaskSequence::PatrolInRange;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->radius = 12.0f;
		}
		void PatrolInRange::RunP(GTAped& ep)
		{
			ep.Task().WanderAround(this->coord.IsZero() ? ep.Position_get()/*Legacy/bugged PatrolInRange behaviour*/ : this->coord, this->radius);
		}

		WanderFreely::	WanderFreely()
		{
			this->type = STSTaskType::WanderFreely;
			this->submenu = Submenus::Sub_TaskSequence::WanderFreely;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void WanderFreely::RunP(GTAped& ep)
		{
			ep.Task().WanderAround();
		}

		void FleeFromCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodeOriginCoords = nodeTask.append_child("Origin");
			nodeOriginCoords.append_attribute("X") = this->originCoords.x;
			nodeOriginCoords.append_attribute("Y") = this->originCoords.y;
			nodeOriginCoords.append_attribute("Z") = this->originCoords.z;
		}
		void FleeFromCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodeOriginCoords = nodeTask.child("Origin");
			this->originCoords.x = nodeOriginCoords.attribute("X").as_float();
			this->originCoords.y = nodeOriginCoords.attribute("Y").as_float();
			this->originCoords.z = nodeOriginCoords.attribute("Z").as_float();
		}
		void FleeFromCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FleeFromCoord>();
			this->originCoords = otherTskT->originCoords;
		}
		FleeFromCoord::FleeFromCoord()
		{
			this->type = STSTaskType::FleeFromCoord;
			this->submenu = Submenus::Sub_TaskSequence::FleeFromCoord;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
		}
		void FleeFromCoord::RunP(GTAped& ep)
		{
			ep.Task().FleeFrom(this->originCoords, this->durationAfterLife > 0 ? -1 : this->duration);
		}

		void NearestAppropriateAction::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SearchRadius").text() = this->searchRadius;
			nodeTask.append_child("Warp").text() = this->warp;
		}
		void NearestAppropriateAction::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->searchRadius = nodeTask.child("SearchRadius").text().as_float();
			this->warp = nodeTask.child("Warp").text().as_bool();
		}
		void NearestAppropriateAction::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::NearestAppropriateAction>();
			this->searchRadius = otherTskT->searchRadius;
			this->warp = otherTskT->warp;
		}
		NearestAppropriateAction::NearestAppropriateAction()
		{
			this->type = STSTaskType::NearestAppropriateAction;
			this->submenu = Submenus::Sub_TaskSequence::NearestAppropriateAction;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->searchRadius = 4.0f;
			this->warp = true;
		}
		void NearestAppropriateAction::RunP(GTAped& ep)
		{
			ep.Task().UseNearestScenario(this->searchRadius, this->warp);
		}

		void ScenarioAction::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("ScenarioName").text() = this->scenarioName.c_str();
		}
		void ScenarioAction::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->scenarioName = nodeTask.child("ScenarioName").text().as_string();
		}
		void ScenarioAction::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ScenarioAction>();
			this->scenarioName = otherTskT->scenarioName;
		}
		ScenarioAction::ScenarioAction()
		{
			this->type = STSTaskType::ScenarioAction;
			this->submenu = Submenus::Sub_TaskSequence::ScenarioAction;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->scenarioName = "WORLD_HUMAN_CLIPBOARD";
		}
		void ScenarioAction::RunP(GTAped& ep)
		{
			//const PCHAR scen = (const PCHAR)AnimationSub_TaskScenarios::vNamedScenarios[scenarioArrIndex].label.c_str();
			//const PCHAR scen = (const PCHAR)this->scenarioName.c_str();
			//if (!IS_PED_USING_SCENARIO(ep.Handle(), scen))
			ep.Task().StartScenario(this->scenarioName);
		}

		void PlayAnimation::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("AnimDict").text() = this->animDict.c_str();
			nodeTask.append_child("AnimName").text() = this->animName.c_str();
			nodeTask.append_child("Speed").text() = this->speed;
			nodeTask.append_child("SpeedMultiplier").text() = this->speedMultiplier;
			nodeTask.append_child("Flag").text() = this->flag;
			nodeTask.append_child("LockPos").text() = this->lockPos;
			nodeTask.append_child("OverrideDurationToNormalSpeedAnimDuration").text() = this->durationToAnimDuration;
		}
		void PlayAnimation::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->animDict = nodeTask.child("AnimDict").text().as_string();
			this->animName = nodeTask.child("AnimName").text().as_string();
			this->speed = nodeTask.child("Speed").text().as_float();
			this->speedMultiplier = nodeTask.child("SpeedMultiplier").text().as_float();
			this->flag = nodeTask.child("Flag").text().as_int();
			this->lockPos = nodeTask.child("LockPos").text().as_bool();
			this->durationToAnimDuration = nodeTask.child("OverrideDurationToNormalSpeedAnimDuration").text().as_bool();
		}
		void PlayAnimation::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::PlayAnimation>();
			this->animDict = otherTskT->animDict;
			this->animName = otherTskT->animName;
			this->speed = otherTskT->speed;
			this->speedMultiplier = otherTskT->speedMultiplier;
			this->flag = otherTskT->flag;
			this->lockPos = otherTskT->lockPos;
			this->durationToAnimDuration = otherTskT->durationToAnimDuration;
		}
		PlayAnimation::PlayAnimation()
		{
			this->type = STSTaskType::PlayAnimation;
			this->submenu = Submenus::Sub_TaskSequence::PlayAnimation;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			this->animDict = "amb@world_human_leaning@female@wall@back@hand_up@base";
			this->animName = "base";
			this->speed = 4.0f;
			this->speedMultiplier = -4.0f;
			this->flag = AnimFlag::Loop;
			this->lockPos = false;
		}
		void PlayAnimation::RunP(GTAped& ep)
		{
			if (this->durationToAnimDuration)
				this->duration = GET_ENTITY_ANIM_TOTAL_TIME(ep.Handle(), const_cast<PCHAR>(this->animDict.c_str()), const_cast<PCHAR>(this->animName.c_str()));

			//if (IS_ENTITY_PLAYING_ANIM(ep.Handle, const_cast<PCHAR>(animDict.c_str()), const_cast<PCHAR>(animDict.c_str()), 3))
			ep.Task().PlayAnimation(this->animDict, this->animName, this->speed, this->speedMultiplier, this->durationAfterLife > 0 ? -1 : this->duration, this->flag, 0.0f, this->lockPos);
		}
		void PlayAnimation::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (HAS_ANIM_DICT_LOADED(const_cast<PCHAR>(this->animDict.c_str())))
				Game::RequestAnimDict(this->animDict, 1600);
		}

		void SetActiveWeapon::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("WeaponHash").text() = int_to_hexstring(weaponHash, true).c_str();
		}
		void SetActiveWeapon::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			weaponHash = nodeTask.child("WeaponHash").text().as_uint();
		}
		void SetActiveWeapon::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SetActiveWeapon>();
			this->weaponHash = otherTskT->weaponHash;
		}
		SetActiveWeapon::SetActiveWeapon()
		{
			this->type = STSTaskType::SetActiveWeapon;
			this->submenu = Submenus::Sub_TaskSequence::SetActiveWeapon;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			weaponHash = WEAPON_PISTOL;
		}
		void SetActiveWeapon::RunP(GTAped& ep)
		{
			//if(ep.Exists())
			auto pedHandle = ep.GetHandle();
			if (!HAS_PED_GOT_WEAPON(pedHandle, this->weaponHash, false))
			{
				GIVE_DELAYED_WEAPON_TO_PED(pedHandle, this->weaponHash, 1000, 0);
				int maxAmmo = 0;
				GET_MAX_AMMO(pedHandle, this->weaponHash, &maxAmmo);
				SET_AMMO_IN_CLIP(pedHandle, this->weaponHash, GET_MAX_AMMO_IN_CLIP(pedHandle, this->weaponHash, false));
				SET_PED_AMMO(pedHandle, this->weaponHash, maxAmmo, 0);
			}
			SET_CURRENT_PED_WEAPON(pedHandle, this->weaponHash, true);
			SET_PED_CAN_SWITCH_WEAPON(pedHandle, false);
		}

		void AimAtCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodePos = nodeTask.append_child("Position");
			nodePos.append_attribute("X") = this->coord.x;
			nodePos.append_attribute("Y") = this->coord.y;
			nodePos.append_attribute("Z") = this->coord.z;
		}
		void AimAtCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodePos = nodeTask.child("Position");
			this->coord.x = nodePos.attribute("X").as_float();
			this->coord.y = nodePos.attribute("Y").as_float();
			this->coord.z = nodePos.attribute("Z").as_float();
		}
		void AimAtCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AimAtCoord>();
			this->coord = otherTskT->coord;
		}
		AimAtCoord::AimAtCoord()
		{
			this->type = STSTaskType::AimAtCoord;
			this->submenu = Submenus::Sub_TaskSequence::AimAtCoord;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void AimAtCoord::RunP(GTAped& ep)
		{
			ep.Task().AimAt(this->coord, this->durationAfterLife > 0 ? -1 : this->duration);
		}

		void AimAtEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void AimAtEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void AimAtEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AimAtEntity>();
			this->targetEntity = otherTskT->targetEntity;
		}
		AimAtEntity::AimAtEntity()
		{
			this->type = STSTaskType::AimAtEntity;
			this->submenu = Submenus::Sub_TaskSequence::AimAtEntity;
			this->duration = 5000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			//this->targetEntity = 0;
		}
		void AimAtEntity::RunP(GTAped& ep)
		{
			ep.Task().AimAt(this->targetEntity, this->durationAfterLife > 0 ? -1 : this->duration);
		}
		void AimAtEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void ShootAtCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodePos = nodeTask.append_child("Position");
			nodePos.append_attribute("X") = this->coord.x;
			nodePos.append_attribute("Y") = this->coord.y;
			nodePos.append_attribute("Z") = this->coord.z;
		}
		void ShootAtCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodePos = nodeTask.child("Position");
			this->coord.x = nodePos.attribute("X").as_float();
			this->coord.y = nodePos.attribute("Y").as_float();
			this->coord.z = nodePos.attribute("Z").as_float();
		}
		void ShootAtCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ShootAtCoord>();
			this->coord = otherTskT->coord;
		}
		ShootAtCoord::ShootAtCoord()
		{
			this->type = STSTaskType::ShootAtCoord;
			this->submenu = Submenus::Sub_TaskSequence::ShootAtCoord;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void ShootAtCoord::RunP(GTAped& ep)
		{
			Hash currWeapon = ep.Weapon_get();
			ScrHandle pedHandle = ep.Handle();

			int ammo;
			GET_MAX_AMMO(pedHandle, currWeapon, &ammo);
			SET_PED_AMMO(pedHandle, currWeapon, ammo, 0);
			SET_AMMO_IN_CLIP(pedHandle, currWeapon, GET_MAX_AMMO_IN_CLIP(pedHandle, currWeapon, true));

			ep.Task().ShootAt(this->coord, this->durationAfterLife > 0 ? -1 : this->duration, FiringPattern::FullAuto);
		}

		void ShootAtEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void ShootAtEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void ShootAtEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ShootAtEntity>();
			this->targetEntity = otherTskT->targetEntity;
		}
		ShootAtEntity::ShootAtEntity()
		{
			this->type = STSTaskType::ShootAtEntity;
			this->submenu = Submenus::Sub_TaskSequence::ShootAtEntity;
			this->duration = 5000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			//this->targetEntity = 0;
		}
		void ShootAtEntity::RunP(GTAped& ep)
		{
			Hash currWeapon = ep.Weapon_get();
			ScrHandle pedHandle = ep.Handle();

			int ammo;
			GET_MAX_AMMO(pedHandle, currWeapon, &ammo);
			SET_PED_AMMO(pedHandle, currWeapon, ammo, 0);
			SET_AMMO_IN_CLIP(pedHandle, currWeapon, GET_MAX_AMMO_IN_CLIP(pedHandle, currWeapon, true));

			ep.Task().ShootAt(this->targetEntity, this->durationAfterLife > 0 ? -1 : this->duration, FiringPattern::FullAuto);
		}
		void ShootAtEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void FightHatedTargets::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Radius").text() = this->radius;
		}
		void FightHatedTargets::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->radius = nodeTask.child("Radius").text().as_float();
		}
		void FightHatedTargets::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FightHatedTargets>();
			this->radius = otherTskT->radius;
		}
		FightHatedTargets::FightHatedTargets()
		{
			this->type = STSTaskType::FightHatedTargets;
			this->submenu = Submenus::Sub_TaskSequence::FightHatedTargets;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->radius = 12.0f;
		}
		void FightHatedTargets::RunP(GTAped& ep)
		{
			std::vector<GTAped> pedHandles;
			//GTAmemory::GetPedHandles(pedHandles, ep.Position_get(), this->radius);
			World::GetNearbyPeds(pedHandles, ep.Position_get(), this->radius);

			TaskSequence squ;

			//ep.Task().FightAgainstHatedTargets(this->radius, this->durationAfterLife > 0 ? -1 : this->duration);
			squ.AddTask().FightAgainstHatedTargets(this->radius, this->durationAfterLife > 0 ? -1 : this->duration);

			for (auto& target : pedHandles)
			{
				switch (ep.GetRelationshipWithPed(target))
				{
				case PedRelationship::Hate:
				case PedRelationship::Dislike:
					squ.AddTask().FightAgainst(target, this->durationAfterLife > 0 ? -1 : this->duration);
					continue; break;
				}
				switch (World::GetRelationshipBetweenGroups(ep.RelationshipGroup_get(), target.RelationshipGroup_get()))
				{
				case PedRelationship::Hate:
				case PedRelationship::Dislike:
					squ.AddTask().FightAgainst(target, this->durationAfterLife > 0 ? -1 : this->duration);
					continue; break;
				}
			}
			squ.Close();
			squ.MakePedPerform(ep);
			squ.Clear();
		}

		void FightPed::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void FightPed::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void FightPed::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FightPed>();
			this->targetEntity = otherTskT->targetEntity;
		}
		FightPed::FightPed()
		{
			this->type = STSTaskType::FightPed;
			this->submenu = Submenus::Sub_TaskSequence::FightPed;
			this->duration = 10000;
			this->durationAfterLife = 0;
			this->isLoopedTask = false;
			//this->targetPed = 0;
		}
		void FightPed::RunP(GTAped& ep)
		{
			ep.Task().FightAgainst(this->targetEntity, this->durationAfterLife > 0 ? -1 : this->duration);
		}
		void FightPed::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void SpeakToPed::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void SpeakToPed::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void SpeakToPed::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SpeakToPed>();
			this->targetEntity = otherTskT->targetEntity;
		}
		SpeakToPed::SpeakToPed()
		{
			this->type = STSTaskType::SpeakToPed;
			this->submenu = Submenus::Sub_TaskSequence::SpeakToPed;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			//this->targetEntity = 0;
		}
		void SpeakToPed::RunP(GTAped& ep)
		{
			ep.Task().ChatTo(this->targetEntity);
		}
		void SpeakToPed::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void PlaySpeechWithVoice::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SpeechName").text() = this->speechName.c_str();
			nodeTask.append_child("VoiceName").text() = this->voiceName.c_str();
			nodeTask.append_child("ParamName").text() = this->paramName.c_str();
		}
		void PlaySpeechWithVoice::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speechName = nodeTask.child("SpeechName").text().as_string();
			this->voiceName = nodeTask.child("VoiceName").text().as_string();
			this->paramName = nodeTask.child("ParamName").text().as_string();
		}
		void PlaySpeechWithVoice::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::PlaySpeechWithVoice>();
			this->speechName = otherTskT->speechName;
			this->voiceName = otherTskT->voiceName;
			this->paramName = otherTskT->paramName;
		}
		PlaySpeechWithVoice::PlaySpeechWithVoice()
		{
			this->type = STSTaskType::PlaySpeechWithVoice;
			this->submenu = Submenus::Sub_TaskSequence::PlaySpeechWithVoice;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->paramName = "SPEECH_PARAMS_FORCE";

		}
		void PlaySpeechWithVoice::RunP(GTAped& ep)
		{
			ep.PlaySpeechWithVoice(this->speechName, this->voiceName, this->paramName);
		}

		void WarpIntoVehicle::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("VehicleInitHandle").text() = this->vehicleToEnter.GetHandle();
			if (this->seatIndex != -2) nodeTask.append_child("SeatIndex").text() = this->seatIndex;
		}
		void WarpIntoVehicle::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->vehicleToEnter.Handle() = nodeTask.child("VehicleInitHandle").text().as_int();
			this->seatIndex = nodeTask.child("SeatIndex").text().as_int(-2);
		}
		void WarpIntoVehicle::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::WarpIntoVehicle>();
			this->vehicleToEnter = otherTskT->vehicleToEnter;
			this->seatIndex = otherTskT->seatIndex;
		}
		WarpIntoVehicle::WarpIntoVehicle()
		{
			this->type = STSTaskType::WarpIntoVehicle;
			this->submenu = Submenus::Sub_TaskSequence::WarpIntoVehicle;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			//this->vehicleToEnter = 0;
			this->seatIndex = -2;
		}
		void WarpIntoVehicle::RunP(GTAped& ep)
		{
			ep.Task().WarpIntoVehicle(this->vehicleToEnter, this->seatIndex == -2 ? this->vehicleToEnter.FirstFreeSeat(SEAT_DRIVER) : (VehicleSeat)this->seatIndex);
		}
		void WarpIntoVehicle::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->vehicleToEnter == u_initHandle)
				this->vehicleToEnter = u_e_Handle;
		}

		void EnterVehicle::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("VehicleInitHandle").text() = this->vehicleToEnter.GetHandle();
			nodeTask.append_child("SeatIndex").text() = this->seatIndex;
		}
		void EnterVehicle::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->vehicleToEnter.Handle() = nodeTask.child("VehicleInitHandle").text().as_int();
			this->seatIndex = nodeTask.child("SeatIndex").text().as_int(-2);
		}
		void EnterVehicle::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::EnterVehicle>();
			this->vehicleToEnter = otherTskT->vehicleToEnter;
			this->seatIndex = otherTskT->seatIndex;
		}
		EnterVehicle::EnterVehicle()
		{
			this->type = STSTaskType::EnterVehicle;
			this->submenu = Submenus::Sub_TaskSequence::EnterVehicle;
			this->duration = 3000;
			this->durationAfterLife = 1;
			this->isLoopedTask = false;
			//this->vehicleToEnter = 0;
			this->seatIndex = -2;
		}
		void EnterVehicle::RunP(GTAped& ep)
		{
			ep.Task().EnterVehicle(this->vehicleToEnter, this->seatIndex == -2 ? this->vehicleToEnter.FirstFreeSeat(SEAT_DRIVER) : (VehicleSeat)this->seatIndex, this->durationAfterLife > 0 ? -1 : this->duration + 200);
		}
		void EnterVehicle::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->vehicleToEnter == u_initHandle)
				this->vehicleToEnter = u_e_Handle;
		}

		void ExitVehicle::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
		}
		void ExitVehicle::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
		}
		void ExitVehicle::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			//auto otherTskT = otherTsk->GetTypeTask<STSTasks::ExitVehicle>();
		}
		ExitVehicle::ExitVehicle()
		{
			this->type = STSTaskType::ExitVehicle;
			this->submenu = Submenus::Sub_TaskSequence::Nothing;
			this->duration = -1; // No settings
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void ExitVehicle::RunP(GTAped& ep)
		{
			ep.Task().LeaveVehicle();
		}

		void DriveWander::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SpeedInKmph").text() = this->speedInKmph;
			nodeTask.append_child("DrivingStyle").text() = this->drivingStyle;
		}
		void DriveWander::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speedInKmph = nodeTask.child("SpeedInKmph").text().as_float();
			this->drivingStyle = nodeTask.child("DrivingStyle").text().as_int();
		}
		void DriveWander::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::DriveWander>();
			this->speedInKmph = otherTskT->speedInKmph;
			this->drivingStyle = otherTskT->drivingStyle;
		}
		DriveWander::DriveWander()
		{
			this->type = STSTaskType::DriveWander;
			this->submenu = Submenus::Sub_TaskSequence::DriveWander;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->speedInKmph = 10.0f;
			this->drivingStyle = DrivingStyle::Normal;
		}
		void DriveWander::RunP(GTAped& ep)
		{
			float speedInMps = this->speedInKmph / 3.6f;
			ep.MaxDrivingSpeed_set(speedInMps + 1.0f);

			ep.Task().CruiseWithVehicle(ep.CurrentVehicle(), speedInMps, this->drivingStyle);
		}

		void DriveToCoord::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SpeedInKmph").text() = this->speedInKmph;
			nodeTask.append_child("DrivingStyle").text() = this->drivingStyle;

			auto& nodeDest = nodeTask.append_child("Destination");
			nodeDest.append_attribute("X") = this->destination.x;
			nodeDest.append_attribute("Y") = this->destination.y;
			nodeDest.append_attribute("Z") = this->destination.z;
		}
		void DriveToCoord::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speedInKmph = nodeTask.child("SpeedInKmph").text().as_float();
			this->drivingStyle = nodeTask.child("DrivingStyle").text().as_int();

			auto& nodeDest = nodeTask.child("Destination");
			this->destination.x = nodeDest.attribute("X").as_float();
			this->destination.y = nodeDest.attribute("Y").as_float();
			this->destination.z = nodeDest.attribute("Z").as_float();
		}
		void DriveToCoord::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::DriveToCoord>();
			this->speedInKmph = otherTskT->speedInKmph;
			this->drivingStyle = otherTskT->drivingStyle;
			this->destination = otherTskT->destination;
		}
		DriveToCoord::DriveToCoord()
		{
			this->type = STSTaskType::DriveToCoord;
			this->submenu = Submenus::Sub_TaskSequence::DriveToCoord;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->speedInKmph = 10.0f;
			this->drivingStyle = DrivingStyle::Normal;
		}
		void DriveToCoord::RunP(GTAped& ep)
		{
			float speedInMps = this->speedInKmph / 3.6f;
			ep.MaxDrivingSpeed_set(speedInMps + 1.0f);

			auto& veh = ep.CurrentVehicle();
			Model& vehModel = veh.Model();
			//ep.Task().DriveTo(ep.CurrentVehicle(), this->destination, 1.0f, speedInMps);

			TaskSequence tsk;
			if (vehModel.IsHeli())
			{
				TASK_HELI_MISSION(0, veh.Handle(), 0, 0, this->destination.x, this->destination.y, this->destination.z, 4, speedInMps, 50.0f, -1.0f, 10000, 100, -1082130432, 0);
			}
			else if (vehModel.IsPlane())
			{
				TASK_PLANE_MISSION(0, veh.Handle(), 0, 0, this->destination.x, this->destination.y, this->destination.z, 4, speedInMps, 50.0f, -1.0f, 100, 200, false);
			}
			else if (vehModel.IsBoat())
			{
				TASK_BOAT_MISSION(0, veh.Handle(), 0, 0, this->destination.x, this->destination.y, this->destination.z, 4, speedInMps, 786469, 10.0f, 1071);
			}
			else
			{
				TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(0, ep.CurrentVehicle().Handle(), this->destination.x, this->destination.y, this->destination.z, speedInMps, this->drivingStyle, 2.0f);
			}

			tsk.Close();
			tsk.MakePedPerform(ep);
			tsk.Clear();
		}

		void DriveFollowEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SpeedInKmph").text() = this->speedInKmph;
			nodeTask.append_child("DrivingStyle").text() = this->drivingStyle;
			nodeTask.append_child("MinDistance").text() = this->minDistance;

			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;
		}
		void DriveFollowEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speedInKmph = nodeTask.child("SpeedInKmph").text().as_float();
			this->drivingStyle = nodeTask.child("DrivingStyle").text().as_int();
			this->minDistance = nodeTask.child("MinDistance").text().as_float();

			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();
		}
		void DriveFollowEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::DriveFollowEntity>();
			this->speedInKmph = otherTskT->speedInKmph;
			this->drivingStyle = otherTskT->drivingStyle;
			this->minDistance = otherTskT->minDistance;
			this->targetEntity = otherTskT->targetEntity;
		}
		DriveFollowEntity::DriveFollowEntity()
		{
			this->type = STSTaskType::DriveFollowEntity;
			this->submenu = Submenus::Sub_TaskSequence::DriveFollowEntity;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->speedInKmph = 10.0f;
			this->drivingStyle = DrivingStyle::Normal;
			this->minDistance = 3.0f;
			//this->targetPed = 0;
		}
		void DriveFollowEntity::RunP(GTAped& ep)
		{
			//_TASK_VEHICLE_FOLLOW(ep.Handle(), ep.CurrentVehicle().Handle(), this->targetEntity.Handle(), this->drivingStyle, this->speedInKmph / 3.6f, this->minDistance);
			TASK_VEHICLE_ESCORT(ep.Handle(), ep.CurrentVehicle().Handle(), this->targetEntity.Handle(), -1, this->speedInKmph / 3.6f, this->drivingStyle, this->minDistance, 20, 0.0f);
		}
		void DriveFollowEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void DriveLandPlane::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			auto& nodeRunwayStart = nodeTask.append_child("RunwayStart");
			nodeRunwayStart.append_attribute("X") = this->runwayStart.x;
			nodeRunwayStart.append_attribute("Y") = this->runwayStart.y;
			nodeRunwayStart.append_attribute("Z") = this->runwayStart.z;

			auto& nodeRunwayEnd = nodeTask.append_child("RunwayEnd");
			nodeRunwayEnd.append_attribute("X") = this->runwayEnd.x;
			nodeRunwayEnd.append_attribute("Y") = this->runwayEnd.y;
			nodeRunwayEnd.append_attribute("Z") = this->runwayEnd.z;
		}
		void DriveLandPlane::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			auto& nodeRunwayStart = nodeTask.child("RunwayStart");
			this->runwayStart.x = nodeRunwayStart.attribute("X").as_float();
			this->runwayStart.y = nodeRunwayStart.attribute("Y").as_float();
			this->runwayStart.z = nodeRunwayStart.attribute("Z").as_float();

			auto& nodeRunwayEnd = nodeTask.child("RunwayEnd");
			this->runwayEnd.x = nodeRunwayEnd.attribute("X").as_float();
			this->runwayEnd.y = nodeRunwayEnd.attribute("Y").as_float();
			this->runwayEnd.z = nodeRunwayEnd.attribute("Z").as_float();
		}
		void DriveLandPlane::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::DriveLandPlane>();
			this->runwayStart = otherTskT->runwayStart;
			this->runwayEnd = otherTskT->runwayEnd;
		}
		DriveLandPlane::DriveLandPlane()
		{
			this->type = STSTaskType::DriveLandPlane;
			this->submenu = Submenus::Sub_TaskSequence::DriveLandPlane;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void DriveLandPlane::RunP(GTAped& ep)
		{
			TASK_PLANE_LAND(ep.Handle(), ep.CurrentVehicle().Handle(), this->runwayStart.x, this->runwayStart.y, this->runwayStart.z, this->runwayEnd.x, this->runwayEnd.y, this->runwayEnd.z);
		}

		void AchieveVehicleForwardSpeed::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("SpeedInKmph").text() = this->speedInKmph;
			nodeTask.append_child("OnGroundOnly").text() = this->onGroundOnly;
		}
		void AchieveVehicleForwardSpeed::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->speedInKmph = nodeTask.child("SpeedInKmph").text().as_float();
			this->onGroundOnly = nodeTask.child("OnGroundOnly").text().as_bool();
		}
		void AchieveVehicleForwardSpeed::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AchieveVehicleForwardSpeed>();
			this->onGroundOnly = otherTskT->onGroundOnly;
			this->speedInKmph = otherTskT->speedInKmph;
		}
		AchieveVehicleForwardSpeed::AchieveVehicleForwardSpeed()
		{
			this->type = STSTaskType::AchieveVehicleForwardSpeed;
			this->submenu = Submenus::Sub_TaskSequence::AchieveVehicleForwardSpeed;
			this->duration = 10000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = true;
			this->onGroundOnly = false;
			this->speedInKmph = 10.0f;
		}
		void AchieveVehicleForwardSpeed::RunP(GTAped& ep)
		{
			if (!this->onGroundOnly || IS_VEHICLE_ON_ALL_WHEELS(ep.Handle()))
				SET_VEHICLE_FORWARD_SPEED(ep.Handle(), this->speedInKmph / 3.6f);
		}

		EmptyVehicle::EmptyVehicle()
		{
			this->type = STSTaskType::EmptyVehicle;
			this->submenu = Submenus::Sub_TaskSequence::Nothing;
			this->duration = -1; // No settings
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void EmptyVehicle::RunP(GTAped& ep)
		{
			TASK_EVERYONE_LEAVE_VEHICLE(ep.Handle());
		}

		void ChangeTextureVariation::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("NewValue").text() = this->newValue;
		}
		void ChangeTextureVariation::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->newValue = nodeTask.child("NewValue").text().as_int();
		}
		void ChangeTextureVariation::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ChangeTextureVariation>();
			this->newValue = otherTskT->newValue;
		}
		ChangeTextureVariation::ChangeTextureVariation()
		{
			this->type = STSTaskType::ChangeTextureVariation;
			this->submenu = Submenus::Sub_TaskSequence::ChangeTextureVariation;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->newValue = 0;
		}
		void ChangeTextureVariation::RunP(GTAped& ep)
		{
			SET_OBJECT_TINT_INDEX(ep.GetHandle(), this->newValue);
		}

		void AchieveVelocity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("IsRelative").text() = this->isRelative;
			nodeTask.append_child("Heading").text() = this->heading;
			nodeTask.append_child("Pitch").text() = this->pitch;
			nodeTask.append_child("Magnitude").text() = this->magnitude;
		}
		void AchieveVelocity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->isRelative = nodeTask.child("IsRelative").text().as_bool();
			this->heading = nodeTask.child("Heading").text().as_float();
			this->pitch = nodeTask.child("Pitch").text().as_float();
			this->magnitude = nodeTask.child("Magnitude").text().as_float();
		}
		void AchieveVelocity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AchieveVelocity>();
			this->isRelative = otherTskT->isRelative;
			this->heading = otherTskT->heading;
			this->pitch = otherTskT->pitch;
			this->magnitude = otherTskT->magnitude;
		}
		AchieveVelocity::AchieveVelocity()
		{
			this->type = STSTaskType::AchieveVelocity;
			this->submenu = Submenus::Sub_TaskSequence::AchieveVelocity;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = true;
			this->isRelative = true;
			this->heading = 0.0f;
			this->pitch = 0.0f;
			this->magnitude = 1.0f;
		}
		void AchieveVelocity::RunP(GTAped& ep)
		{
			ep.Velocity_set(Vector3::RotationToDirection((this->isRelative ? ep.Rotation_get() : Vector3::Zero()) + Vector3(this->pitch, 0.0f, this->heading)) * this->magnitude);
		}

		void AchievePushForce::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("IsRelative").text() = this->isRelative;
			nodeTask.append_child("ForceType").text() = this->forceType;
			nodeTask.append_child("Heading").text() = this->heading;
			nodeTask.append_child("Pitch").text() = this->pitch;
			nodeTask.append_child("Magnitude").text() = this->magnitude;

			auto& nodeOffsetVector = nodeTask.append_child("OffsetVector");
			nodeOffsetVector.append_attribute("X") = this->offsetVector.x;
			nodeOffsetVector.append_attribute("Y") = this->offsetVector.y;
			nodeOffsetVector.append_attribute("Z") = this->offsetVector.z;
		}
		void AchievePushForce::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->isRelative = nodeTask.child("IsRelative").text().as_bool();
			this->forceType = nodeTask.child("ForceType").text().as_int();
			this->heading = nodeTask.child("Heading").text().as_float();
			this->pitch = nodeTask.child("Pitch").text().as_float();
			this->magnitude = nodeTask.child("Magnitude").text().as_float();

			auto& nodeOffsetVector = nodeTask.child("OffsetVector");
			this->offsetVector.x = nodeOffsetVector.attribute("X").as_float();
			this->offsetVector.y = nodeOffsetVector.attribute("Y").as_float();
			this->offsetVector.z = nodeOffsetVector.attribute("Z").as_float();
		}
		void AchievePushForce::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::AchievePushForce>();
			this->isRelative = otherTskT->isRelative;
			this->forceType = otherTskT->forceType;
			this->heading = otherTskT->heading;
			this->pitch = otherTskT->pitch;
			this->magnitude = otherTskT->magnitude;
			this->offsetVector = otherTskT->offsetVector;
		}
		AchievePushForce::AchievePushForce()
		{
			this->type = STSTaskType::AchievePushForce;
			this->submenu = Submenus::Sub_TaskSequence::AchievePushForce;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->isRelative = false;
			this->forceType = 1;
			this->heading = 0.0f;
			this->pitch = 0.0f;
			this->magnitude = 1.0f;
		}
		void AchievePushForce::RunP(GTAped& ep)
		{
			Vector3& dir = Vector3::RotationToDirection(Vector3(this->pitch, 0.0f, this->heading)) * this->magnitude;
			APPLY_FORCE_TO_ENTITY(ep.Handle(), this->forceType, dir.x, dir.y, dir.z, this->offsetVector.x, this->offsetVector.y, this->offsetVector.z, false, this->isRelative, true, true, false, true);
		}

		void OscillateToPoint::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("AngularFrequency").text() = this->angleFreq;
			nodeTask.append_child("DampRatio").text() = this->dampRatio;

			auto& nodeDest = nodeTask.append_child("Point");
			nodeDest.append_attribute("X") = this->destination.x;
			nodeDest.append_attribute("Y") = this->destination.y;
			nodeDest.append_attribute("Z") = this->destination.z;
		}
		void OscillateToPoint::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->angleFreq = nodeTask.child("AngularFrequency").text().as_float();
			this->dampRatio = nodeTask.child("DampRatio").text().as_float();

			auto& nodeDest = nodeTask.child("Point");
			this->destination.x = nodeDest.attribute("X").as_float();
			this->destination.y = nodeDest.attribute("Y").as_float();
			this->destination.z = nodeDest.attribute("Z").as_float();
		}
		void OscillateToPoint::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::OscillateToPoint>();
			this->angleFreq = otherTskT->angleFreq;
			this->dampRatio = otherTskT->dampRatio;
			this->destination = otherTskT->destination;
		}
		OscillateToPoint::OscillateToPoint()
		{
			this->type = STSTaskType::OscillateToPoint;
			this->submenu = Submenus::Sub_TaskSequence::OscillateToPoint;
			this->duration = 5000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = true;
			this->angleFreq = 0.4f;
			this->dampRatio = 0.1f;
		}
		void OscillateToPoint::RunP(GTAped& ep)
		{
			ep.Oscillate(this->destination, this->angleFreq, this->dampRatio);
		}

		void OscillateToEntity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("AngularFrequency").text() = this->angleFreq;
			nodeTask.append_child("DampRatio").text() = this->dampRatio;

			auto targetHandle = this->targetEntity.GetHandle();
			if (targetHandle == PLAYER_PED_ID())
				nodeTask.append_child("TargetInitHandle").text() = "PLAYER";
			else
				nodeTask.append_child("TargetInitHandle").text() = targetHandle;

			auto& nodeOffsetVector = nodeTask.append_child("OffsetVector");
			nodeOffsetVector.append_attribute("X") = this->offsetVector.x;
			nodeOffsetVector.append_attribute("Y") = this->offsetVector.y;
			nodeOffsetVector.append_attribute("Z") = this->offsetVector.z;
		}
		void OscillateToEntity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->angleFreq = nodeTask.child("AngularFrequency").text().as_float();
			this->dampRatio = nodeTask.child("DampRatio").text().as_float();

			if (strcmp(nodeTask.child("TargetInitHandle").text().as_string(), "PLAYER") == 0)
				this->targetEntity.Handle() = PLAYER_PED_ID();
			else
				this->targetEntity.Handle() = nodeTask.child("TargetInitHandle").text().as_int();

			auto& nodeOffsetVector = nodeTask.child("OffsetVector");
			this->offsetVector.x = nodeOffsetVector.attribute("X").as_float();
			this->offsetVector.y = nodeOffsetVector.attribute("Y").as_float();
			this->offsetVector.z = nodeOffsetVector.attribute("Z").as_float();
		}
		void OscillateToEntity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::OscillateToEntity>();
			this->angleFreq = otherTskT->angleFreq;
			this->dampRatio = otherTskT->dampRatio;
			this->targetEntity = otherTskT->targetEntity;
			this->offsetVector = otherTskT->offsetVector;
		}
		OscillateToEntity::OscillateToEntity()
		{
			this->type = STSTaskType::OscillateToEntity;
			this->submenu = Submenus::Sub_TaskSequence::OscillateToEntity;
			this->duration = 5000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = true;
			this->angleFreq = 0.4f;
			this->dampRatio = 0.1f;
			//this->targetPed = 0;
		}
		void OscillateToEntity::RunP(GTAped& ep)
		{
			if (this->targetEntity.Exists())
				ep.Oscillate(this->targetEntity.GetOffsetInWorldCoords(offsetVector), this->angleFreq, this->dampRatio);
		}
		void OscillateToEntity::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
		{
			if (this->targetEntity == u_initHandle && this->targetEntity != PLAYER_PED_ID())
				this->targetEntity = u_e_Handle;
		}

		void FreezeInPlace::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("FreezeType").text() = (int)this->freezeType;
		}
		void FreezeInPlace::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->freezeType = nodeTask.child("FreezeType").text().as_int();
		}
		void FreezeInPlace::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::FreezeInPlace>();
			this->freezeType = otherTskT->freezeType;
		}
		FreezeInPlace::FreezeInPlace()
		{
			this->type = STSTaskType::FreezeInPlace;
			this->submenu = Submenus::Sub_TaskSequence::FreezeInPlace;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->freezeType = FreezeInPlace::eFreezeType::FREEZETYPE_FREEZE;
		}
		void FreezeInPlace::RunP(GTAped& ep)
		{
			switch (this->freezeType)
			{
			case FreezeInPlace::eFreezeType::FREEZETYPE_FREEZE:
				ep.FreezePosition(true);
				break;
			case FreezeInPlace::eFreezeType::FREEZETYPE_UNFREEZE:
				ep.FreezePosition(false);
				break;
			case FreezeInPlace::eFreezeType::FREEZETYPE_RESETVELOCITY:
				ep.FreezePosition(true);
				ep.FreezePosition(false);
				//ep.Velocity_set(Vector3::Zero());
				break;
			}
		}

		void SetRotation::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("IsRelative").text() = this->isRelative;
			nodeTask.append_child("Pitch").text() = this->rotationValue.x;
			nodeTask.append_child("Roll").text() = this->rotationValue.y;
			nodeTask.append_child("Yaw").text() = this->rotationValue.z;
		}
		void SetRotation::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->isRelative = nodeTask.child("IsRelative").text().as_bool();
			this->rotationValue.x = nodeTask.child("Pitch").text().as_float();
			this->rotationValue.y = nodeTask.child("Roll").text().as_float();
			this->rotationValue.z = nodeTask.child("Yaw").text().as_float();
		}
		void SetRotation::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::SetRotation>();
			this->isRelative = otherTskT->isRelative;
			this->rotationValue = otherTskT->rotationValue;
		}
		SetRotation::SetRotation()
		{
			this->type = STSTaskType::SetRotation;
			this->submenu = Submenus::Sub_TaskSequence::SetRotation;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void SetRotation::Run(void* ve)
		{
			SpoonerEntity& e = *reinterpret_cast<SpoonerEntity*>(ve);
			GTAentity att;
			if (e.AttachmentArgs.isAttached && sub::Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(e.Handle, att))
				EntityManagement::AttachEntity(e, att, e.AttachmentArgs.boneIndex, e.AttachmentArgs.offset, (this->isRelative ? e.AttachmentArgs.rotation : Vector3()) + rotationValue);
			else
				e.Handle.Rotation_set((this->isRelative ? e.Handle.Rotation_get() : Vector3()) + rotationValue);
		}

		void ChangeOpacity::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("OpacityValue").text() = (int)this->opacityValue;
		}
		void ChangeOpacity::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->opacityValue = nodeTask.child("OpacityValue").text().as_int();
		}
		void ChangeOpacity::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::ChangeOpacity>();
			this->opacityValue = otherTskT->opacityValue;
		}
		ChangeOpacity::ChangeOpacity()
		{
			this->type = STSTaskType::ChangeOpacity;
			this->submenu = Submenus::Sub_TaskSequence::ChangeOpacity;
			this->duration = -2; // No duration setting
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
			this->opacityValue = 269;
		}
		void ChangeOpacity::RunP(GTAped& ep)
		{
			if (this->opacityValue == 269)
				ep.ResetAlpha();
			else
				ep.Alpha_set(this->opacityValue);
		}

		void TriggerFx::GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const
		{
			nodeTask.append_child("Delay").text() = this->delay;
			nodeTask.append_child("AssetName").text() = this->fx.GetFxData().asset.c_str();
			nodeTask.append_child("EffectName").text() = this->fx.GetFxData().effect.c_str();
			nodeTask.append_child("Scale").text() = this->scale;

			auto& nodeColour = nodeTask.append_child("Colour");
			nodeColour.append_attribute("R") = this->colour.R;
			nodeColour.append_attribute("G") = this->colour.G;
			nodeColour.append_attribute("B") = this->colour.B;
			nodeColour.append_attribute("A") = this->colour.A;

			auto& nodePos = nodeTask.append_child("RelativePosition");
			nodePos.append_attribute("X") = this->posOffset.x;
			nodePos.append_attribute("Y") = this->posOffset.y;
			nodePos.append_attribute("Z") = this->posOffset.z;

			auto& nodeRot = nodeTask.append_child("RelativeRotation");
			nodeRot.append_attribute("X") = this->rotOffset.x;
			nodeRot.append_attribute("Y") = this->rotOffset.y;
			nodeRot.append_attribute("Z") = this->rotOffset.z;
		}
		void TriggerFx::ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask)
		{
			this->delay = nodeTask.child("Delay").text().as_uint();
			this->fx = PTFX::NonLoopedPTFX(nodeTask.child("AssetName").text().as_string(), nodeTask.child("EffectName").text().as_string());
			this->scale = nodeTask.child("Scale").text().as_float();

			auto& nodeColour = nodeTask.child("Colour");
			this->colour.R = nodeColour.attribute("R").as_int();
			this->colour.G = nodeColour.attribute("G").as_int();
			this->colour.B = nodeColour.attribute("B").as_int();
			this->colour.A = nodeColour.attribute("A").as_int();

			auto& nodePos = nodeTask.child("RelativePosition");
			this->posOffset.x = nodePos.attribute("X").as_float();
			this->posOffset.y = nodePos.attribute("Y").as_float();
			this->posOffset.z = nodePos.attribute("Z").as_float();

			auto& nodeRot = nodeTask.child("RelativeRotation");
			this->rotOffset.x = nodeRot.attribute("X").as_float();
			this->rotOffset.y = nodeRot.attribute("Y").as_float();
			this->rotOffset.z = nodeRot.attribute("Z").as_float();
		}
		void TriggerFx::ImportTaskDataSpecific(STSTask* otherTsk)
		{
			auto otherTskT = otherTsk->GetTypeTask<STSTasks::TriggerFx>();
			this->timer = otherTskT->timer;
			this->delay = otherTskT->delay;
			this->fx = otherTskT->fx;
			this->posOffset = otherTskT->posOffset;
			this->rotOffset = otherTskT->rotOffset;
			this->scale = otherTskT->scale;
			this->colour = otherTskT->colour;
		}
		TriggerFx::TriggerFx()
		{
			this->type = STSTaskType::TriggerFx;
			this->submenu = Submenus::Sub_TaskSequence::TriggerFx;
			this->duration = 1000;
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = true;
			this->timer = 0U;
			this->delay = 500U;
			this->fx = PTFX::NonLoopedPTFX("scr_michael2", "scr_abattoir_ped_sliced");
			this->scale = 0.8f;
			this->colour = RGBA::AllWhite();
		}
		void TriggerFx::RunP(GTAped& ep)
		{
			if (this->duration == -2)
			{
				this->fx.LoadAsset(600);
				this->fx.Start(ep, this->scale, this->posOffset, this->rotOffset, this->colour);
			}
			else
			{
				if (this->fx.IsAssetLoaded())
				{
					if (GetTickCount() > timer)
					{
						this->fx.Start(ep, this->scale, this->posOffset, this->rotOffset, this->colour);
						this->timer = GetTickCount() + delay;
					}
				}
				else
				{
					this->fx.LoadAsset();
				}
			}
		}
		void TriggerFx::EndP(GTAped& ep)
		{
			timer = 0U;
		}

		EndSequence::EndSequence()
		{
			this->type = STSTaskType::EndSequence;
			this->submenu = Submenus::Sub_TaskSequence::Nothing;
			this->duration = -1; // No settings
			this->durationAfterLife = -2; // No durationAfterLife setting
			this->isLoopedTask = false;
		}
		void EndSequence::RunP(GTAped& ep)
		{
			if (ep.IsPed())
			{
				SnapTasks st;
				st.RunP(ep);
			}
		}
				
	}

}




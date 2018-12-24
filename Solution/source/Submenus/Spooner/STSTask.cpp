/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "STSTask.h"

#include "..\..\macros.h"

#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAped.h"

#include "Submenus_TaskSequence.h"

#include <string>
#include <vector>
#include <utility>
#include <pugixml\src\pugixml.hpp>

namespace sub::Spooner
{
	// maybe add namespace

	// Task type names

	std::vector<std::pair<STSTaskType, std::pair<std::string, EntityType>>> vSTSTaskTypeNames
		//std::unordered_map<STSTaskType, std::pair<std::string, EntityType>> vSTSTaskTypeNames
	{
		{ STSTaskType::Nothing,{ "Nothing", EntityType::ALL } },
		{ STSTaskType::SetHealth,{ "Set Health", EntityType::ALL } },
		{ STSTaskType::AddBlip,{ "Add Blip (If None Present)", EntityType::ALL } },
		{ STSTaskType::RemoveBlip,{ "Remove Blip", EntityType::ALL } },

		{ STSTaskType::Pause,{ "Pause", EntityType::PED } },
		{ STSTaskType::UsePhone,{ "Use Phone", EntityType::PED } },
		{ STSTaskType::ThrowProjectile,{ "Throw Projectile (If Holding One)", EntityType::PED } },
		{ STSTaskType::Writhe,{ "Writhe And Die", EntityType::PED } },
		{ STSTaskType::FaceDirection,{ "Face Direction", EntityType::PED } },
		{ STSTaskType::FaceEntity,{ "Face Entity", EntityType::PED } },
		{ STSTaskType::LookAtCoord,{ "Keep Looking At Position", EntityType::PED } },
		{ STSTaskType::LookAtEntity,{ "Keep Looking At Entity", EntityType::PED } },
		{ STSTaskType::TeleportToCoord,{ "Teleport To Position", EntityType::ALL } },
		{ STSTaskType::SeekCoverAtCoord,{ "Seek Cover At Position", EntityType::PED } },
		//{ STSTaskType::SlideToCoord, {"Slide To Position", EntityType::PED }},
		{ STSTaskType::GoToCoord,{ "Go To Position", EntityType::PED } },
		{ STSTaskType::FollowRoute,{ "Follow Route", EntityType::PED } },
		{ STSTaskType::FollowEntity,{ "Follow Entity", EntityType::PED } },
		{ STSTaskType::PatrolInRange,{ "Patrol In Range", EntityType::PED } },
		{ STSTaskType::WanderFreely,{ "Wander Freely", EntityType::PED } },
		{ STSTaskType::FleeFromCoord,{ "Flee From Position", EntityType::PED } },
		{ STSTaskType::NearestAppropriateAction,{ "Closest Appropriate Action", EntityType::PED } },
		{ STSTaskType::ScenarioAction,{ "Perform Scenario Action", EntityType::PED } },
		{ STSTaskType::PlayAnimation,{ "Play Animation", EntityType::PED } },
		{ STSTaskType::SetActiveWeapon,{ "Set Active Weapon", EntityType::PED } },
		{ STSTaskType::AimAtCoord,{ "Aim At Position", EntityType::PED } },
		{ STSTaskType::AimAtEntity,{ "Aim At Entity", EntityType::PED } },
		{ STSTaskType::ShootAtCoord,{ "Shoot At Position", EntityType::PED } },
		{ STSTaskType::ShootAtEntity,{ "Shoot At Entity", EntityType::PED } },
		{ STSTaskType::FightHatedTargets,{ "Fight Enemies (If Eligible & Provoked)", EntityType::PED } },
		{ STSTaskType::FightPed,{ "Fight Ped", EntityType::PED } },
		{ STSTaskType::SpeakToPed,{ "Speak To Ped (No Speech)", EntityType::PED } },
		{ STSTaskType::PlaySpeechWithVoice,{ "Play Speech", EntityType::PED } },
		{ STSTaskType::WarpIntoVehicle,{ "Warp Into Vehicle", EntityType::PED } },
		{ STSTaskType::EnterVehicle,{ "Enter Vehicle", EntityType::PED } },
		{ STSTaskType::ExitVehicle,{ "Exit Vehicle (If In One)", EntityType::PED } },
		{ STSTaskType::DriveWander,{ "Cruise (If In Vehicle)", EntityType::PED } },
		{ STSTaskType::DriveToCoord,{ "Drive To Position (If In Vehicle)", EntityType::PED } },
		{ STSTaskType::DriveFollowEntity,{ "Drive & Follow Entity (If In Vehicle)", EntityType::PED } },
		{ STSTaskType::DriveLandPlane,{ "Land Plane (If In One)", EntityType::PED } },

		{ STSTaskType::EmptyVehicle,{ "Empty Vehicle", EntityType::VEHICLE } },
		{ STSTaskType::AchieveVehicleForwardSpeed,{ "Achieve Vehicle Speed", EntityType::VEHICLE } },

		{ STSTaskType::ChangeTextureVariation,{ "Change Texture Variation", EntityType::PROP } },

		{ STSTaskType::AchieveVelocity,{ "Achieve Velocity", EntityType::ALL } },
		{ STSTaskType::AchievePushForce,{ "Achieve Push Force", EntityType::ALL } },
		{ STSTaskType::OscillateToPoint,{ "Oscillate To Point", EntityType::ALL } },
		{ STSTaskType::OscillateToEntity,{ "Oscillate To Entity", EntityType::ALL } },
		{ STSTaskType::FreezeInPlace,{ "Freeze In Place", EntityType::ALL } },
		{ STSTaskType::SetRotation,{ "Snap To Rotation", EntityType::ALL } },
		{ STSTaskType::ChangeOpacity,{ "Change Opacity", EntityType::ALL } },
		{ STSTaskType::TriggerFx,{ "TriggerFX", EntityType::ALL } },

		{ STSTaskType::SnapTasks,{ "Refresh (Snap & Stand)", EntityType::PED } },
		{ STSTaskType::EndSequence,{ "End Sequence", EntityType::ALL } },
	};

	// STSTask

	STSTask::STSTask()
		: type(STSTaskType::Nothing),
		submenu(Submenus::Sub_TaskSequence::Nothing),
		duration(1000),
		durationAfterLife(-2i8),
		isLoopedTask(false)
	{

	}

	void STSTask::Assign(STSTask* right)
	{
		if (right != nullptr)
		{
			if (this->type == right->type)
			{
				//this->type = right->type;
				this->duration = right->duration;
				this->durationAfterLife = right->durationAfterLife;
				this->isLoopedTask = right->isLoopedTask;
			}	this->ImportTaskDataSpecific(right);
		}
	}

	void STSTask::Run(void* ve) // Why can't I just make an overload for SpoonerEntity* smh me cba
	{
		RunP(GTAped(*reinterpret_cast<GTAentity*>(ve)));
	}
	void STSTask::End(void* ve)
	{
		EndP(GTAped(*reinterpret_cast<GTAentity*>(ve)));
	}
	void STSTask::RunP(GTAped& ep)
	{
	}
	void STSTask::EndP(GTAped& ep)
	{
	}

	void STSTask::GetXmlNode(pugi::xml_node& nodeTask) const
	{
		nodeTask.append_child("Type").text() = static_cast<UINT8>(this->type);
		nodeTask.append_child("Duration").text() = this->duration;
		nodeTask.append_child("KeepTaskRunningAfterTime").text() = (int)this->durationAfterLife;
		nodeTask.append_child("IsLoopedTask").text() = this->isLoopedTask;
		this->GetXmlNodeTaskSpecific(nodeTask);
	}
	pugi::xml_node STSTask::GetXmlNode() const
	{
		pugi::xml_node nodet;
		nodet.set_name("Task");
		this->GetXmlNode(nodet);
		return nodet;
	}
	void STSTask::ImportXmlNode(pugi::xml_node& nodeTask)
	{
		this->type = (STSTaskType)nodeTask.child("Type").text().as_uint();
		this->duration = nodeTask.child("Duration").text().as_int();
		this->durationAfterLife = nodeTask.child("KeepTaskRunningAfterTime").text().as_int();
		this->isLoopedTask = nodeTask.child("IsLoopedTask").text().as_bool();
		this->ImportXmlNodeTaskSpecific(nodeTask);
	}

	void STSTask::LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle)
	{
	}

}




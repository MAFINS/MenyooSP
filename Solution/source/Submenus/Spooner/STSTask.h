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
#include <vector>
#include <utility>
#include <algorithm>

typedef signed char INT8;
typedef unsigned char UINT8;
typedef int Entity;

enum class EntityType : UINT8;
class GTAped;
namespace pugi {
	class xml_node;
};

namespace sub::Spooner
{
	// maybe add namespace

	enum class STSTaskType : UINT8
	{
		// Type indices are fixed k
		SnapTasks = 0,
		EndSequence = 1,

		Nothing = 2,
		Pause = 3,
		UsePhone = 4,
		Writhe = 5,
		GoToCoord = 6,
		FollowRoute = 7,
		PatrolInRange = 8,
		WanderFreely = 9,
		ScenarioAction = 10,
		FightHatedTargets = 11,
		FightPed = 12,
		SpeakToPed = 13,
		PlayAnimation = 14,
		FleeFromCoord = 15,
		PlaySpeechWithVoice = 16,
		NearestAppropriateAction = 17,
		SlideToCoord = 18,
		SeekCoverAtCoord = 19,
		FaceDirection = 20,
		FaceEntity = 21,
		TeleportToCoord = 22,
		FollowEntity = 23,
		ThrowProjectile = 24,
		AchieveVelocity = 25,
		AchievePushForce = 26,
		OscillateToPoint = 27,
		FreezeInPlace = 28,
		AchieveVehicleForwardSpeed = 29,
		EnterVehicle = 30,
		ExitVehicle = 31,
		WarpIntoVehicle = 32,
		EmptyVehicle = 33,
		DriveWander = 34,
		DriveToCoord = 35,
		DriveFollowEntity = 36,
		DriveLandPlane = 37,
		ChangeOpacity = 38,
		TriggerFx = 39,
		LookAtCoord = 40,
		LookAtEntity = 41,
		ShootAtCoord = 42,
		ShootAtEntity = 43,
		ChangeTextureVariation = 44,
		SetHealth = 45,
		SetActiveWeapon = 46,
		SetRotation = 47,
		OscillateToEntity = 48,
		AimAtCoord = 49,
		AimAtEntity = 50,
		AddBlip = 51,
		RemoveBlip = 52
	};

	extern std::vector<std::pair<STSTaskType, std::pair<std::string, EntityType>>> vSTSTaskTypeNames;
	static inline std::vector<std::pair<STSTaskType, std::pair<std::string, EntityType>>>::const_iterator STSTaskGetName(const STSTaskType b)
	{
		return std::find_if(vSTSTaskTypeNames.cbegin(), vSTSTaskTypeNames.cend(),
			[&b](const std::pair<STSTaskType, std::pair<std::string, EntityType>>& a)->bool
		{
			return a.first == b;
		});
	}

	class STSTask abstract
	{
	private:
		virtual void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const {};
		virtual void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) {};
		virtual void ImportTaskDataSpecific(STSTask* otherTsk) {};
	public:
		STSTaskType type;// = STSTaskType::Nothing;
		void(*submenu)();// = Submenus::Sub_TaskSequence::Nothing;
		int duration;
		INT8 durationAfterLife;
		bool isLoopedTask;

		STSTask();

		template<typename R> inline R* GetTypeTask()
		{
			return reinterpret_cast<R*>(&*this);
		}

		void Assign(STSTask* right);

		virtual void Run(void* ve);
		virtual void End(void* ve);
		virtual void RunP(GTAped& ep);
		virtual void EndP(GTAped& ep);

		void GetXmlNode(pugi::xml_node& nodeTask) const;
		pugi::xml_node GetXmlNode() const;
		void ImportXmlNode(pugi::xml_node& nodeTask);

		virtual void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle);

		// virual ctor and dtor k
	};

}




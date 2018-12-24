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

#include "STSTask.h"

#include "..\..\Scripting\GTAblip.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAvehicle.h"
#include "..\..\Natives\types.h" //RGBA
#include "..\..\Scripting\PTFX.h"

#include <vector>
#include <string>

typedef signed char INT8;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT;
typedef int INT, Entity, Ped, Vehicle, Object, ScrHandle;
typedef unsigned long DWORD, Hash;

namespace sub::Spooner
{
	namespace STSTasks
	{
		class Nothing final : public STSTask
		{
		public:
			Nothing();
			void Run(void* ve) override;
		};

		class SnapTasks final : public STSTask
		{
		public:
			SnapTasks();
			void RunP(GTAped& ep) override;
		};

		class SetHealth final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			int healthValue;
			SetHealth();
			void Run(void* ve) override;
		};

		class AddBlip final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			//static struct AttachedBlip { GTAentity entity; GTAblip blip; };
			//static std::vector<AttachedBlip> vBlips;

			GTAblip blip;
			std::string label;
			int colour;
			uint8_t alpha;
			int icon;
			float scale;
			bool isFlashing;
			bool isFriendly;
			bool isShortRange;
			bool showRoute;
			int showNumber;
			AddBlip();
			void Run(void* ve) override;
		};

		class RemoveBlip final : public STSTask
		{
		public:
			RemoveBlip();
			void Run(void* ve) override;
		};

		class Pause final : public STSTask
		{
		public:
			Pause();
			void RunP(GTAped& ep) override;
		};

		class UsePhone final : public STSTask
		{
		public:
			UsePhone();
			void RunP(GTAped& ep) override;
		};

		class ThrowProjectile final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 targetPos;
			ThrowProjectile();
			void RunP(GTAped& ep) override;
		};

		class Writhe final : public STSTask
		{
		public:
			Writhe();
			void RunP(GTAped& ep) override;
		};

		class FaceDirection final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float heading;
			FaceDirection();
			void RunP(GTAped& ep) override;
		};

		class FaceEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			FaceEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};
		
		class LookAtCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 coord;
			LookAtCoord();
			void RunP(GTAped& ep) override;
			void EndP(GTAped& ep) override;
		};
		
		class LookAtEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			LookAtEntity();
			void RunP(GTAped& ep) override;
			void EndP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class TeleportToCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool takeVehicleToo;
			Vector3 destination;
			TeleportToCoord();
			void RunP(GTAped& ep) override;
		};

		class SeekCoverAtCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool canPeekInCover;
			Vector3 coverPos;
			SeekCoverAtCoord();
			void RunP(GTAped& ep) override;
		};

		class SlideToCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speed, heading;
			Vector3 destination;
			SlideToCoord();
			void RunP(GTAped& ep) override;
		};

		class GoToCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speed;
			Vector3 destination;
			GoToCoord();
			void RunP(GTAped& ep) override;
		};

		class FollowRoute final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speed;
			std::vector<Vector3> route;
			FollowRoute();
			void RunP(GTAped& ep) override;
		};

		class FollowEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speed;
			GTAentity targetEntity;
			FollowEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class PatrolInRange final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float radius;
			PatrolInRange();
			void RunP(GTAped& ep) override;
		};

		class WanderFreely final : public STSTask
		{
		public:
			WanderFreely();
			void RunP(GTAped& ep) override;
		};

		class FleeFromCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 originCoords;
			FleeFromCoord();
			void RunP(GTAped& ep) override;
		};

		class NearestAppropriateAction final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float searchRadius;
			bool warp;
			NearestAppropriateAction();
			void RunP(GTAped& ep) override;
		};

		class ScenarioAction final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			std::string scenarioName;
			ScenarioAction();
			void RunP(GTAped& ep) override;
		};

		class PlayAnimation final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			std::string animDict, animName;
			float speed, speedMultiplier;
			int flag;
			bool lockPos, durationToAnimDuration;
			PlayAnimation();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class SetActiveWeapon final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Hash weaponHash;
			SetActiveWeapon();
			void RunP(GTAped& ep) override;
		};

		class AimAtCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 coord;
			AimAtCoord();
			void RunP(GTAped& ep) override;
		};

		class AimAtEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			AimAtEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class ShootAtCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 coord;
			ShootAtCoord();
			void RunP(GTAped& ep) override;
		};

		class ShootAtEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			ShootAtEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class FightHatedTargets final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float radius;
			FightHatedTargets();
			void RunP(GTAped& ep) override;
		};

		class FightPed final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			FightPed();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class SpeakToPed final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAentity targetEntity;
			SpeakToPed();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class PlaySpeechWithVoice final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			std::string speechName, voiceName, paramName;
			PlaySpeechWithVoice();
			void RunP(GTAped& ep) override;
		};

		class WarpIntoVehicle final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAvehicle vehicleToEnter;
			INT8 seatIndex;
			WarpIntoVehicle();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class EnterVehicle final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			GTAvehicle vehicleToEnter;
			INT8 seatIndex;
			EnterVehicle();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class ExitVehicle final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			ExitVehicle();
			void RunP(GTAped& ep) override;
		};

		class DriveWander final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speedInKmph;
			int drivingStyle;
			DriveWander();
			void RunP(GTAped& ep) override;
		};

		class DriveToCoord final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speedInKmph;
			int drivingStyle;
			Vector3 destination;
			DriveToCoord();
			void RunP(GTAped& ep) override;
		};

		class DriveFollowEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float speedInKmph;
			int drivingStyle;
			float minDistance;
			GTAentity targetEntity;
			DriveFollowEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class DriveLandPlane final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			Vector3 runwayStart, runwayEnd;
			DriveLandPlane();
			void RunP(GTAped& ep) override;
		};

		class AchieveVehicleForwardSpeed final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool onGroundOnly;
			float speedInKmph;
			AchieveVehicleForwardSpeed();
			void RunP(GTAped& ep) override;
		};

		class EmptyVehicle final : public STSTask
		{
		public:
			EmptyVehicle();
			void RunP(GTAped& ep) override;
		};

		class ChangeTextureVariation final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			UINT8 newValue;
			ChangeTextureVariation();
			void RunP(GTAped& ep) override;
		};

		class AchieveVelocity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool isRelative;
			float heading, pitch, magnitude;
			AchieveVelocity();
			void RunP(GTAped& ep) override;
		};

		class AchievePushForce final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool isRelative;
			int forceType;
			float heading, pitch, magnitude;
			Vector3 offsetVector;
			AchievePushForce();
			void RunP(GTAped& ep) override;
		};

		class OscillateToPoint final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float angleFreq, dampRatio;
			Vector3 destination;
			OscillateToPoint();
			void RunP(GTAped& ep) override;
		};

		class OscillateToEntity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			float angleFreq, dampRatio;
			GTAentity targetEntity;
			Vector3 offsetVector;
			OscillateToEntity();
			void RunP(GTAped& ep) override;
			void LoadTargetingDressing(Entity u_initHandle, Entity u_e_Handle) override;
		};

		class FreezeInPlace final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			enum eFreezeType : UINT8 { FREEZETYPE_FREEZE, FREEZETYPE_UNFREEZE, FREEZETYPE_RESETVELOCITY };
			UINT8 freezeType;
			FreezeInPlace();
			void RunP(GTAped& ep) override;
		};

		class SetRotation final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			bool isRelative;
			Vector3 rotationValue;
			SetRotation();
			void Run(void* ve) override;
		};

		class ChangeOpacity final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			int opacityValue;
			ChangeOpacity();
			void RunP(GTAped& ep) override;
		};

		class TriggerFx final : public STSTask
		{
		private:
			void GetXmlNodeTaskSpecific(pugi::xml_node& nodeTask) const override;
			void ImportXmlNodeTaskSpecific(pugi::xml_node& nodeTask) override;
			void ImportTaskDataSpecific(STSTask* otherTsk) override;
		public:
			DWORD timer;
			UINT delay;
			PTFX::NonLoopedPTFX fx;
			Vector3 posOffset, rotOffset;
			float scale;
			RGBA colour;
			TriggerFx();
			void RunP(GTAped& ep) override;
			void EndP(GTAped& ep) override;
		};

		class EndSequence final : public STSTask
		{
		public:
			EndSequence();
			void RunP(GTAped& ep) override;
		};

	}

}




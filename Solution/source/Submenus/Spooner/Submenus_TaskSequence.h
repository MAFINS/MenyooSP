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

namespace sub::Spooner
{
	class STSTask;

	namespace Submenus
	{
		extern STSTask* _selectedSTST;

		namespace Sub_TaskSequence
		{
			void Nothing();
			void SetHealth();

			void AddBlip();
			void RemoveBlip();

			void Pause();
			void UsePhone();
			void ThrowProjectile();
			void Writhe();
			void FaceDirection();
			void FaceEntity();
			void LookAtCoord();
			void LookAtEntity();
			void TeleportToCoord();
			void SeekCoverAtCoord();
			void SlideToCoord();
			void GoToCoord();
			void FollowRoute();
			void FollowEntity();
			void PatrolInRange();
			void WanderFreely();
			void FleeFromCoord();
			void NearestAppropriateAction();
			void ScenarioAction();
			void ScenarioAction_list();
			void PlayAnimation();
			void PlayAnimation_settings();
			void PlayAnimation_allPedAnims();
			void PlayAnimation_allPedAnims_inDict();
			void SetActiveWeapon();
			void AimAtCoord();
			void AimAtEntity();
			void ShootAtCoord();
			void ShootAtEntity();
			void FightHatedTargets();
			void FightPed();
			void SpeakToPed();
			void PlaySpeechWithVoice();
			void PlaySpeechWithVoice_inVoice();

			void WarpIntoVehicle();
			void EnterVehicle();
			void DriveWander();
			void DriveToCoord();
			void DriveFollowEntity();
			void DriveLandPlane();

			void AchieveVehicleForwardSpeed();

			void ChangeTextureVariation();

			void AchieveVelocity();
			void AchievePushForce();
			void OscillateToPoint();
			void OscillateToEntity();
			void FreezeInPlace();
			void SetRotation();
			void ChangeOpacity();
			void TriggerFx();
		}
		void Sub_TaskSequence_TaskList();
		void Sub_TaskSequence_AddTask();
		void Sub_TaskSequence_InTask();

	}

}




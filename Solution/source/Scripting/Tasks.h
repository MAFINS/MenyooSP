/*
* Copyright (C) 2015 crosire
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#pragma once

#include "GTAentity.h"

#include <vector>

enum VehicleSeat : int;

class TaskSequence;

class Tasks
{
public:
	Tasks(GTAentity ped);
	Tasks(int pedHandle);
	Tasks(const Tasks& obj);

	Tasks& operator = (const Tasks& right);

	void AimAt(GTAentity target, int duration);
	void AimAt(const Vector3& target, int duration);
	void Arrest(GTAentity ped);
	void ChatTo(GTAentity ped);
	void Climb();
	void Cower(int duration);
	void CruiseWithVehicle(GTAentity vehicle, float speed);
	void CruiseWithVehicle(GTAentity vehicle, float speed, int drivingstyle);
	void DriveTo(GTAentity vehicle, Vector3 position, float radius, float speed);
	void DriveTo(GTAentity vehicle, Vector3 position, float radius, float speed, int drivingstyle);
	void EnterVehicle(GTAentity vehicle, VehicleSeat seat, int timeout = -1, float speed = 1.0f, int flag = 1);
	static void EveryoneLeaveVehicle(GTAentity vehicle);
	void FightAgainst(GTAentity target);
	void FightAgainst(GTAentity target, int duration);
	void FightAgainstHatedTargets(float radius);
	void FightAgainstHatedTargets(float radius, int duration);
	void ThrowProjectile(const Vector3& targetPos);
	void FleeFrom(GTAentity ped);
	void FleeFrom(GTAentity ped, int duration);
	void FleeFrom(const Vector3& position);
	void FleeFrom(const Vector3& position, int duration);
	template<typename... Args> void FollowPointRoute(float speed, Args&&... p);
	void FollowPointRoute(const std::vector<Vector3>& points, float speed = 1.0f);
	void FollowPointRoute(const std::initializer_list<Vector3>& points, float speed = 1.0f);
	void GoTo(GTAentity target);
	void GoTo(GTAentity target, const Vector3& offset);
	void GoTo(GTAentity target, const Vector3& offset, int timeout);
	void GoTo(const Vector3& position, bool ignorePaths = false, int timeout = -1);
	void GuardCurrentPosition();
	void HandsUp(int duration);
	void Jump();
	void LeaveVehicle();
	void LeaveVehicle(GTAentity vehicle, bool closeDoor);
	void LookAt(GTAentity target, int duration = -1);
	void LookAt(const Vector3& position, int duration = -1);
	void ParachuteTo(const Vector3& position);
	void ParkVehicle(GTAentity vehicle, const Vector3& position, float heading);
	void PerformSequence(TaskSequence& sequence);
	bool IsPlayingAnimation(const std::string& animDict, const std::string& animName);
	void PlayAnimation(const std::string& animDict, const std::string& animName);
	void PlayAnimation(const std::string& animDict, const std::string& animName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, bool lockPos = false);
	void PutAwayMobilePhone();
	void PutAwayParachute();
	void ReactAndFlee(GTAentity pedToFleeFrom);
	void ReloadWeapon();
	void RunTo(const Vector3& position, bool ignorePaths = false, int timeout = -1);
	void ShootAt(GTAentity target, int duration, int pattern);
	void ShootAt(const Vector3& position, int duration, int pattern);
	void ShuffleToNextVehicleSeat(GTAentity vehicle);
	void Skydive();
	void SlideTo(const Vector3& position, float heading);
	void StandStill(int duration);
	bool IsUsingScenario(const std::string& name);
	void StartScenario(const std::string& name, const Vector3& position, float heading);
	void StartScenario(const std::string& name, int unkDelay = -1, bool playEnterAnim = true);
	void UseNearestScenario(bool warp = false);
	void UseNearestScenario(float radius, bool warp = false);
	void UseNearestScenario(const Vector3& pos, float radius, bool warp = false);
	void SwapWeapon();
	void TurnTo(GTAentity target, int duration = -1);
	void TurnTo(const Vector3& position, int duration = -1);
	void UseMobilePhone();
	void UseMobilePhone(int duration);
	void UseParachute();
	void VehicleChase(GTAentity target);
	void VehicleShootAtPed(GTAentity target);
	void Wait(int duration);
	void WanderAround();
	void WanderAround(const Vector3& position, float radius);
	void WarpIntoVehicle(GTAentity vehicle, VehicleSeat seat);
	void WarpOutOfVehicle(GTAentity vehicle);

	void ClearAll();
	void ClearAllImmediately();
	void ClearLookAt();
	void ClearSecondary();
	void ClearAnimation(const std::string& animDict, const std::string& animName);

private:
	GTAentity _ped;
};

class TaskSequence
{
public:
	TaskSequence();
	TaskSequence(int handle);
	//~TaskSequence();

	int& Handle();

	int Count();

	Tasks AddTask();

	bool IsClosed();
	void Close(bool repeat = false);
	void Clear();

	void MakePedPerform(GTAentity ped);

private:
	int _handle, _count;
	bool _isClosed;
};



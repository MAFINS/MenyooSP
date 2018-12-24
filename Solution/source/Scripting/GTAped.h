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

//#include "Euphoria.h"
#include "GTAentity.h"
#include "Tasks.h"

#include <string>
#include <vector>

typedef unsigned long DWORD, Hash;
typedef int BOOL;

class GTAvehicle;
class Vector3;
enum class ParachuteState : int;
enum class PedSubTask : int;
enum class NMString : int;
enum VehicleSeat : int;
namespace FiringPattern {
	enum FiringPattern : DWORD;
}
class s_Weapon_Components_Tint;
//class GTAentity;
//class Tasks;

enum class Gender
{
	Male,
	Female
};
enum class FormationType
{
	Default = 0,
	Circle1 = 1,
	Circle2 = 2,
	Line = 3
};
enum class PedHeadOverlay : int
{
	SkinRash = 0,
	Beard = 1,
	Eyebrows = 2,
	Wrinkles = 3,
	Makeup = 4,
	Blush = 5,
	Pigment1 = 6,
	Pigment2 = 7,
	Lipstick = 8,
	Spots = 9,
	ChestHair = 10,
	Chest1 = 11,
	Chest2 = 12,
};
enum class PedFacialFeature
{
	NoseWidth = 0,
	NoseBottomHeight = 1,
	NoseTipLength = 2,
	NoseBridgeDepth = 3,
	NoseTipHeight = 4,
	NoseBroken = 5,
	BrowHeight = 6,
	BrowDepth = 7,
	CheekboneHeight = 8,
	CheekboneWidth = 9,
	CheekDepth = 10,
	EyeSize = 11,
	LipThickness = 12,
	JawWidth = 13,
	JawShape = 14,
	ChinHeight = 15,
	ChinDepth = 16,
	ChinWidth = 17,
	ChinIndent = 18,
	NeckWidth = 19,
};

class PedHeadBlendData
{
public:
	int shapeFirstID;
private:
	DWORD _padding0;
public:
	int shapeSecondID;
private:
	DWORD _padding1;
public:
	int shapeThirdID;
private:
	DWORD _padding2;
public:
	int skinFirstID;
private:
	DWORD _padding3;
public:
	int skinSecondID;
private:
	DWORD _padding4;
public:
	int skinThirdID;
private:
	DWORD _padding5;
public:
	float shapeMix;
private:
	DWORD _padding6;
public:
	float skinMix;
private:
	DWORD _padding7;
public:
	float thirdMix;
private:
	DWORD _padding8;
public:
	BOOL isParent;
private:
	DWORD _padding9;
};

class PedGroup
{
public:
	PedGroup();
	PedGroup(int handle);
	//~PedGroup();

	PedGroup operator =(const PedGroup& right);
	bool operator ==(const PedGroup& right) const;
	bool operator !=(const PedGroup& right) const;

	static PedGroup CreateNewGroup();

	int& Handle();
	int GetHandle() const;

	GTAentity Leader_get() const;
	void Leader_set(GTAentity ped);

	int MemberCount() const;

	void SeparationRange_set(float range);

	void FormationSpacing_set(float spacing);
	void ResetFormationSpacing();

	void FormationType_set(FormationType value);

	void Add(GTAentity ped, bool leader, bool teleportWithLeader = false);
	void Remove(GTAentity ped);

	bool Exists() const;
	static bool Exists(PedGroup pedGroup);

	GTAentity GetMember(int index) const;

	bool Contains(GTAentity ped) const;

	void ToVector(std::vector<GTAentity>& result, bool includeLeader) const;

private:
	int _handle;
};

namespace PedBloodDecals {
	extern const std::vector<std::string> vBloodDecals;
}
namespace PedDamageDecals {
	extern const std::vector<std::string> vDamageDecals;
}
namespace PedDamagePacks {
	extern const std::vector<std::string> vDamagePacks;
}

class GTAped : public GTAentity
{
public:
	GTAped();
	GTAped(int handle);
	GTAped(GTAentity handle);

	GTAped& operator = (const GTAped& value);
	friend bool operator == (const GTAped& left, const GTAped& right);

	void Delete(bool tele = false) override;

	int NetID() const override;

	void GiveNM(const NMString& messageid);

	GTAentity Clone(float heading, bool createNetH, bool createPedH);

	bool IsSubTaskActive(const PedSubTask& taskType);

	PedHeadBlendData HeadBlendData_get() const;
	void HeadBlendData_set(const PedHeadBlendData& blendData);

	void VoiceName_set(const std::string& value);

	int PedType() const;

	void PlaySpeechWithVoice(const std::string& speechName, const std::string& voiceName, const std::string& speechParam, bool unk = 0);

	Hash Weapon_get() const;
	void Weapon_set(Hash weaponHash);
	void RemoveAllWeapons();

	Vector3 LastWeaponImpactCoord() const;

	ParachuteState ParachuteState_get() const;
	
	int Accuracy_get() const;
	void Accuracy_set(int value);

	void AlwaysDiesWhenInjured_set(bool value);

	void AlwaysKeepTask_set(bool value);

	int Armour_get() const;
	void Armour_set(int value);

	void BlockPermanentEvents_set(bool value);

	bool CanRagdoll_get() const;
	void CanRagdoll_set(bool value);

	void CanSwitchWeapons_set(bool value);

	void CanSufferCriticalHits_set(bool value);

	bool CanFlyThroughWindscreen_get() const;
	void CanFlyThroughWindscreen_set(bool value);

	void CanBeKnockedOffBike_set(int state);

	void CanBeDraggedOutOfVehicle_set(bool value);

	void CanBeTargetted_set(bool value);

	void CanPlayGestures_set(bool value);

	bool IsInGroup() const;
	PedGroup CurrentPedGroup_get() const;
	void NeverLeavesGroup_set(bool value);
	void TeleportsWithGroupLeader_set(bool value, const PedGroup& grp = 0);

	void DiesInstantlyInWater_set(bool value);
	void DrownsInWater_set(bool value);
	void DrownsInSinkingVehicle_set(bool value);

	void DrivingSpeed_set(float value);
	void MaxDrivingSpeed_set(float value);

	void DrivingStyle_set(int value);

	//NaturalMotion::Euphoria Euphoria_get() const;

	void FiringPattern_set(FiringPattern::FiringPattern value);

	Gender Gender_get() const;

	bool IsAimingFromCover() const;

	bool IsBeingJacked() const;

	bool IsBeingStealthKilled() const;
	bool IsPerformingStealthKill() const;

	bool IsBeingStunned() const;

	bool IsDoingDriveBy() const;

	bool IsDucking() const;
	void SetDucking(bool value);

	void SetAsEnemy(bool value);

	bool IsHuman() const;

	bool IsIdle() const;

	bool IsProne() const;

	bool IsGettingUp() const;

	bool IsGettingIntoAVehicle() const;

	bool IsGoingIntoCover() const;

	bool IsInjured() const;

	bool IsInBoat() const;

	bool IsInCombat() const;
	bool IsInCombatWith(const GTAped& target) const;

	bool IsInCoverFacingLeft() const;

	bool IsInFlyingVehicle() const;

	bool IsInHeli() const;
	bool IsInPlane() const;
	bool IsInPoliceVehicle() const;
	bool IsInSub() const;
	bool IsInTrain() const;
	bool IsOnBike() const;
	bool IsOnFoot() const;

	bool IsInMeleeCombat() const;

	bool IsJacking() const;

	bool IsPlayer() const;

	void SetPriorityTargetForEnemies(bool value);

	bool IsRagdoll() const;

	bool IsWalking() const;
	bool IsRunning() const;
	bool IsSprinting() const;
	bool IsJumping() const;

	bool IsShooting() const;
	bool IsReloading() const;

	bool IsStopped() const;

	bool IsSwimming() const;
	bool IsSwimmingUnderWater() const;

	bool IsTryingToEnterALockedVehicle() const;

	int Money_get() const;
	void Money_set(int value);

	Hash RelationshipGroup_get() const;
	void RelationshipGroup_set(Hash grpHash);
	void RelationshipGroup_set(const std::string& grpName);

	void ShootRate_set(int value);

	void HasGravity_set(bool value) override;

	Tasks Task();
	int TaskSequenceProgress_get() const;
	bool IsPerformingAnyTaskSequence() const;

	bool WasKilledByStealth() const;
	bool WasKilledByTakedown() const;

	void WetnessHeight_set(float value);

	bool IsInVehicle() const;
	bool IsInVehicle(GTAvehicle vehicle) const;
	GTAvehicle CurrentVehicle() const;

	VehicleSeat CurrentVehicleSeat_get();

	int GetRelationshipWithPed(GTAentity otherPed) const;

	void SetIntoVehicle(GTAvehicle vehicle, VehicleSeat seat);

	bool IsInCover() const;
	bool IsInCover(bool expectUseWeapon) const;

	GTAentity GetJacker() const;
	GTAentity GetJackTarget() const;
	GTAentity GetSourceOfDeath() const;
	void Kill();
	void ExplodeHead(Hash weaponHash);

	void ResetVisibleDamage();
	void ClearBloodDamage();
	void ApplyDamage(int damageAmount);

	Vector3 GetBoneCoord(int boneID) const;
	Vector3 GetBoneCoord(int boneID, const Vector3& offset) const;
	int GetBoneIndex(int boneID) const;

	void ApplyBlood(const std::string& bloodDecalName, int boneID);
	void ApplyBlood(const std::string& bloodDecalName, int boneID, const Vector3& rotation);

	void ApplyDamageDecal(const std::string& damageDecalName, int boneID, const Vector3& rotation, float damageScale, float multiplier, int state, bool b1);
	void ApplyDamagePack(const std::string& damagePackName, float damageAmount, float multiplier);

	void StoreWeaponsInArray(std::vector<s_Weapon_Components_Tint>& result);
	void GiveWeaponsFromArray(const std::vector<s_Weapon_Components_Tint>& value);

private:
	Tasks _tasks;
	//NaturalMotion::Euphoria _euphoria;

};




/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GTAped.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "enums.h"
#include "..\Natives\natives2.h"
#include "GTAblip.h"
#include "GTAentity.h"
#include "Tasks.h"
#include "GTAvehicle.h"
#include "WeaponIndivs.h"

#include <string>
#include <vector>


PedGroup::PedGroup()
	: _handle(0)// _handle(CREATE_GROUP(0))
{
}
PedGroup::PedGroup(int handle)
	: _handle(handle)
{
}
/*PedGroup::~PedGroup()
{
REMOVE_GROUP(this->_handle);
}*/

PedGroup PedGroup::operator =(const PedGroup& right)
{
	return (this->_handle = right._handle);
}
bool PedGroup::operator ==(const PedGroup& right) const
{
	return (this->_handle == right._handle);
}
bool PedGroup::operator !=(const PedGroup& right) const
{
	return (this->_handle != right._handle);
}

PedGroup PedGroup::CreateNewGroup()
{
	return CREATE_GROUP(0);
}

int& PedGroup::Handle()
{
	return this->_handle;
}
int PedGroup::GetHandle() const
{
	return this->_handle;
}

GTAentity PedGroup::Leader_get() const
{
	return GET_PED_AS_GROUP_LEADER(this->_handle);
}
void PedGroup::Leader_set(GTAentity ped)
{
	SET_PED_AS_GROUP_LEADER(ped.Handle(), this->_handle);
}

int PedGroup::MemberCount() const
{
	Any val1;
	int count;
	GET_GROUP_SIZE(this->_handle, &val1, &count);
	return count;
}

void PedGroup::SeparationRange_set(float range)
{
	SET_GROUP_SEPARATION_RANGE(this->_handle, range);
}

void PedGroup::FormationSpacing_set(float spacing)
{
	SET_GROUP_FORMATION_SPACING(this->_handle, spacing, 0xbf800000, 0xbf800000);
}
void PedGroup::ResetFormationSpacing()
{
	RESET_GROUP_FORMATION_DEFAULT_SPACING(this->_handle);
}

void PedGroup::FormationType_set(FormationType value)
{
	SET_GROUP_FORMATION(this->_handle, static_cast<int>(value));
}

void PedGroup::Add(GTAentity ped, bool leader, bool teleportWithLeader)
{
	if (leader)
	{
		SET_PED_AS_GROUP_LEADER(ped.Handle(), this->_handle);
	}
	else
	{
		SET_PED_AS_GROUP_MEMBER(ped.Handle(), this->_handle);
		if (teleportWithLeader) SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(ped.Handle(), this->_handle, true);
	}
}
void PedGroup::Remove(GTAentity ped)
{
	REMOVE_PED_FROM_GROUP(ped.Handle());
	//SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(ped.Handle(), this->_handle, false);
}

bool PedGroup::Exists() const
{
	return DOES_GROUP_EXIST(this->_handle) != 0;
}
bool PedGroup::Exists(PedGroup pedGroup)
{
	return DOES_GROUP_EXIST(pedGroup.Handle()) != 0;
}

GTAentity PedGroup::GetMember(int index) const
{
	return GET_PED_AS_GROUP_MEMBER(this->_handle, index);
}

bool PedGroup::Contains(GTAentity ped) const
{
	return IS_PED_GROUP_MEMBER(ped.Handle(), this->_handle) != 0;
}

void PedGroup::ToVector(std::vector<GTAentity>& result, bool includeLeader) const
{
	if (includeLeader)
	{
		auto leader = this->Leader_get();

		if (leader.Exists())
		{
			result.push_back(leader);
		}
	}

	for (int i = 0; i < this->MemberCount(); i++)
	{
		const auto& ped = this->GetMember(i);

		if (ped.Exists())
		{
			result.push_back(ped);
		}
	}
}


namespace PedBloodDecals {
	const std::vector<std::string> vBloodDecals
	{
		{ "soak_splat" },
		{ "wound_sheet" },

		{ "BulletSmall" },
		{ "BulletLarge" },
		{ "ShotgunSmall" },
		{ "ShotgunSmallMonolithic" },
		{ "ShotgunLarge" },
		{ "ShotgunLargeMonolithic" },
		{ "NonFatalHeadshot" },
		{ "stab" },
		{ "BasicSlash" },
		{ "Scripted_Ped_Splash_Back" },
		{ "BackSplash" }
	};
}
namespace PedDamageDecals {
	const std::vector<std::string> vDamageDecals
	{
		{ "None" },
		{ "scars_bruise_damage" },
		{ "scars_bruise_damage_n" },
		{ "bullet_armour" },
		{ "herpes_n" },
		{ "dirt_sheet" },

		{ "scar" },
		{ "blushing" },
		{ "bruise" },
		{ "bruise_large" },
		{ "herpes" },
		{ "ArmorBullet" },
		{ "basic_dirt_cloth" },
		{ "basic_dirt_skin" },
		{ "cs_trev1_dirt" }
	};
}
namespace PedDamagePacks {
	const std::vector<std::string> vDamagePacks
	{
		//{ "None" },
		{ "Useful_Bits" },
		{ "Explosion_Med" },
		{ "Explosion_Large" },
		{ "Dirt_Dry" },
		{ "Dirt_Grass" },
		{ "Dirt_Mud" },
		{ "Burnt_Ped_Left_Arm" },
		{ "Burnt_Ped_Right_Arm" },
		{ "Burnt_Ped_Limbs" },
		{ "Burnt_Ped_Head_Torso" },
		{ "Burnt_Ped_0" },
		{ "Car_Crash_Light" },
		{ "Car_Crash_Heavy" },
		{ "Fall_Low" },
		{ "Fall" },
		{ "HitByVehicle" },
		{ "BigHitByVehicle" },
		{ "BigRunOverByVehicle" },
		{ "RunOverByVehicle" },
		{ "Splashback_Face_0" },
		{ "Splashback_Face_1" },
		{ "Splashback_Torso_0" },
		{ "Splashback_Torso_1" },
		{ "HOSPITAL_0" },
		{ "HOSPITAL_1" },
		{ "HOSPITAL_2" },
		{ "HOSPITAL_3" },
		{ "HOSPITAL_4" },
		{ "HOSPITAL_5" },
		{ "HOSPITAL_6" },
		{ "HOSPITAL_7" },
		{ "HOSPITAL_8" },
		{ "HOSPITAL_9" },
		{ "Skin_Melee_0" },
		{ "SCR_Dumpster" },
		{ "SCR_Cougar" },
		{ "SCR_DogAttack" },
		{ "SCR_TracySplash" },
		{ "SCR_Finale_Michael_Face" },
		{ "SCR_Finale_Michael" },
		{ "SCR_TrevorTreeBang" },
		{ "SCR_Shark" },
		{ "SCR_Torture" },
		{ "TD_KNIFE_FRONT" },
		{ "TD_KNIFE_FRONT_VA" },
		{ "TD_KNIFE_FRONT_VB" },
		{ "TD_KNIFE_REAR" },
		{ "TD_KNIFE_REAR_VA" },
		{ "TD_KNIFE_REAR_VB" },
		{ "TD_KNIFE_STEALTH" },
		{ "TD_MELEE_FRONT" },
		{ "TD_MELEE_REAR" },
		{ "TD_MELEE_STEALTH" },
		{ "TD_MELEE_BATWAIST" },
		{ "TD_melee_face_l" },
		{ "MTD_melee_face_r" },
		{ "MTD_melee_face_jaw" },
		{ "TD_PISTOL_FRONT" },
		{ "TD_PISTOL_FRONT_KILL" },
		{ "TD_PISTOL_REAR" },
		{ "TD_PISTOL_REAR_KILL" },
		{ "TD_RIFLE_FRONT_KILL" },
		{ "TD_RIFLE_NONLETHAL_FRONT" },
		{ "TD_RIFLE_NONLETHAL_REAR" },
		{ "TD_SHOTGUN_FRONT_KILL" },
		{ "TD_SHOTGUN_REAR_KILL" },
		{ "SCR_Franklin_finb" },
		{ "SCR_Franklin_finb2" }
	};
}


GTAped::GTAped() : GTAentity(), _tasks(0)//, _euphoria(NaturalMotion::Euphoria(0))
{
}
GTAped::GTAped(int handle) : GTAentity(handle), _tasks(Tasks(handle))//, _euphoria(NaturalMotion::Euphoria(handle))
{
}
GTAped::GTAped(GTAentity handle) : GTAentity(handle), _tasks(Tasks(handle))//, _euphoria(NaturalMotion::Euphoria(handle.Handle()))
{
}

GTAped& GTAped::operator = (const GTAped& value)
{
	this->mHandle = value.mHandle;
	this->_tasks = value._tasks;
	//this->_euphoria = value._euphoria;
	return *this;
}
bool operator == (const GTAped& left, const GTAped& right)
{
	return left.mHandle == right.mHandle;
}

void GTAped::Delete(bool tele)
{
	if (!this->Exists()) return;

	this->RequestControl();

	GTAblip blip = this->CurrentBlip();
	if (blip.Exists()) blip.Remove();

	this->MissionEntity_set(false);

	if (tele) SET_ENTITY_COORDS_NO_OFFSET(this->mHandle, 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0);

	DELETE_PED(&this->mHandle);
}

int GTAped::NetID() const
{
	return PED_TO_NET(this->mHandle);
}

void GTAped::GiveNM(const NMString& messageid)
{
	if (!CAN_PED_RAGDOLL(this->mHandle))
	{
		SET_PED_CAN_RAGDOLL(this->mHandle, true);
	}
	SET_PED_TO_RAGDOLL(this->mHandle, 5000, -1, 1, 1, 1, 0);
	CREATE_NM_MESSAGE(false, (int)messageid);
	GIVE_PED_NM_MESSAGE(this->mHandle);
}

GTAentity GTAped::Clone(float heading, bool createNetH, bool createPedH)
{
	return CLONE_PED(this->mHandle, heading, createNetH, createPedH);
}

bool GTAped::IsSubTaskActive(const PedSubTask& taskType)
{
	return GET_IS_TASK_ACTIVE(this->mHandle, static_cast<int>(taskType)) != 0;
}

PedHeadBlendData GTAped::HeadBlendData_get() const
{
	PedHeadBlendData blendData;
	GET_PED_HEAD_BLEND_DATA(this->mHandle, (Any*)&blendData);
	return blendData;
}
void GTAped::HeadBlendData_set(const PedHeadBlendData& blendData)
{
	SET_PED_HEAD_BLEND_DATA(this->mHandle, blendData.shapeFirstID, blendData.shapeSecondID, blendData.shapeThirdID,
		blendData.skinFirstID, blendData.skinSecondID, blendData.skinThirdID, blendData.shapeMix,
		blendData.skinMix, blendData.thirdMix, blendData.isParent);
}

void GTAped::VoiceName_set(const std::string& value)
{
	SET_AMBIENT_VOICE_NAME(this->mHandle, value.c_str());
}

int GTAped::PedType() const
{
	return GET_PED_TYPE(this->mHandle);
}

void GTAped::PlaySpeechWithVoice(const std::string& speechName, const std::string& voiceName, const std::string& speechParam, bool unk)
{
	PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(this->mHandle, (PCHAR)speechName.c_str(), (PCHAR)voiceName.c_str(), (PCHAR)speechParam.c_str(), unk);
}

Hash GTAped::Weapon_get() const
{
	Hash weap = 0;
	GET_CURRENT_PED_WEAPON(this->mHandle, &weap, true);
	return weap;
}
void GTAped::Weapon_set(Hash weaponHash)
{
	if (!HAS_PED_GOT_WEAPON(this->mHandle, weaponHash, false))
		GIVE_WEAPON_TO_PED(this->mHandle, weaponHash, 9999, true, false);
	SET_CURRENT_PED_WEAPON(this->mHandle, weaponHash, true);
}
void GTAped::RemoveAllWeapons()
{
	REMOVE_ALL_PED_WEAPONS(this->mHandle, true);
}

Vector3 GTAped::LastWeaponImpactCoord() const
{
	Vector3_t targetPos;
	if (GET_PED_LAST_WEAPON_IMPACT_COORD(this->mHandle, &targetPos))
		return targetPos;
	else return Vector3();
}

ParachuteState GTAped::ParachuteState_get() const
{
	return (ParachuteState)GET_PED_PARACHUTE_STATE(this->mHandle);
}

int GTAped::Accuracy_get() const
{
	return GET_PED_ACCURACY(this->mHandle);
}
void GTAped::Accuracy_set(int value)
{
	SET_PED_ACCURACY(this->mHandle, value);
}

void GTAped::AlwaysDiesWhenInjured_set(bool value)
{
	SET_PED_DIES_WHEN_INJURED(this->mHandle, value);
}

void GTAped::AlwaysKeepTask_set(bool value)
{
	SET_PED_KEEP_TASK(this->mHandle, value);
}

int GTAped::Armour_get() const
{
	return GET_PED_ARMOUR(this->mHandle);
}
void GTAped::Armour_set(int value)
{
	SET_PED_ARMOUR(this->mHandle, value);
}

void GTAped::BlockPermanentEvents_set(bool value)
{
	SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(this->mHandle, value);
}

bool GTAped::CanRagdoll_get() const
{
	return CAN_PED_RAGDOLL(this->mHandle) != 0;
}
void GTAped::CanRagdoll_set(bool value)
{
	SET_PED_CAN_RAGDOLL(this->mHandle, value);
}

void GTAped::CanSwitchWeapons_set(bool value)
{
	SET_PED_CAN_SWITCH_WEAPON(this->mHandle, value);
}

void GTAped::CanSufferCriticalHits_set(bool value)
{
	SET_PED_SUFFERS_CRITICAL_HITS(this->mHandle, value);
}

bool GTAped::CanFlyThroughWindscreen_get() const
{
	return GET_PED_CONFIG_FLAG(this->mHandle, ePedConfigFlags::WillFlyThruWindscreen, true) != 0;
}
void GTAped::CanFlyThroughWindscreen_set(bool value)
{
	SET_PED_CONFIG_FLAG(this->mHandle, ePedConfigFlags::WillFlyThruWindscreen, value);
}

void GTAped::CanBeKnockedOffBike_set(int state)
{
	SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(this->mHandle, state);
}

void GTAped::CanBeDraggedOutOfVehicle_set(bool value)
{
	SET_PED_CAN_BE_DRAGGED_OUT(this->mHandle, value);
}

void GTAped::CanBeTargetted_set(bool value)
{
	SET_PED_CAN_BE_TARGETTED(this->mHandle, value);
}

void GTAped::CanPlayGestures_set(bool value)
{
	SET_PED_CAN_PLAY_GESTURE_ANIMS(this->mHandle, value);
}

bool GTAped::IsInGroup() const
{
	return IS_PED_IN_GROUP(this->mHandle) != 0;
}
PedGroup GTAped::CurrentPedGroup_get() const
{
	return GET_PED_GROUP_INDEX(this->mHandle);
}
void GTAped::NeverLeavesGroup_set(bool value)
{
	SET_PED_NEVER_LEAVES_GROUP(this->mHandle, value);
}
void GTAped::TeleportsWithGroupLeader_set(bool value, const PedGroup& grp)
{
	SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(this->mHandle, grp.GetHandle() == 0 ? GET_PED_GROUP_INDEX(this->mHandle) : grp.GetHandle(), value);
}

void GTAped::DiesInstantlyInWater_set(bool value)
{
	SET_PED_DIES_INSTANTLY_IN_WATER(this->mHandle, value);
}
void GTAped::DrownsInWater_set(bool value)
{
	SET_PED_DIES_IN_WATER(this->mHandle, value);
}
void GTAped::DrownsInSinkingVehicle_set(bool value)
{
	SET_PED_DIES_IN_SINKING_VEHICLE(this->mHandle, value);
}

void GTAped::DrivingSpeed_set(float value)
{
	SET_DRIVE_TASK_CRUISE_SPEED(this->mHandle, value);
}
void GTAped::MaxDrivingSpeed_set(float value)
{
	SET_DRIVE_TASK_MAX_CRUISE_SPEED(this->mHandle, value);
}

void GTAped::DrivingStyle_set(int value)
{
	SET_DRIVE_TASK_DRIVING_STYLE(this->mHandle, value);
}

/*NaturalMotion::Euphoria GTAped::Euphoria_get() const
{
	return _euphoria;
}*/

void GTAped::FiringPattern_set(FiringPattern::FiringPattern value)
{
	SET_PED_FIRING_PATTERN(this->mHandle, value);
}

Gender GTAped::Gender_get() const
{
	return IS_PED_MALE(this->mHandle) ? Gender::Male : Gender::Female;
}

bool GTAped::IsAimingFromCover() const
{
	return IS_PED_AIMING_FROM_COVER(this->mHandle) != 0;
}

bool GTAped::IsBeingJacked() const
{
	return IS_PED_BEING_JACKED(this->mHandle) != 0;
}

bool GTAped::IsBeingStealthKilled() const
{
	return IS_PED_BEING_STEALTH_KILLED(this->mHandle) != 0;
}
bool GTAped::IsPerformingStealthKill() const
{
	return IS_PED_PERFORMING_STEALTH_KILL(this->mHandle) != 0;
}

bool GTAped::IsBeingStunned() const
{
	return IS_PED_BEING_STUNNED(this->mHandle, false) != 0;
}

bool GTAped::IsDoingDriveBy() const
{
	return IS_PED_DOING_DRIVEBY(this->mHandle) != 0;
}

bool GTAped::IsDucking() const
{
	return IS_PED_DUCKING(this->mHandle) != 0;
}
void GTAped::SetDucking(bool value)
{
	SET_PED_DUCKING(this->mHandle, value);
}

void GTAped::SetAsEnemy(bool value)
{
	SET_PED_AS_ENEMY(this->mHandle, value);
}

bool GTAped::IsHuman() const
{
	return IS_PED_HUMAN(this->mHandle) != 0;
}

bool GTAped::IsIdle() const
{
	return
		!this->IsInjured()
		&& !this->IsRagdoll()
		&& !this->IsInAir()
		&& !this->IsOnFire()
		&& !this->IsDucking()
		&& !this->IsGettingIntoAVehicle()
		&& !this->IsInCombat()
		&& !this->IsInMeleeCombat()
		&& !this->IsInVehicle();
}

bool GTAped::IsProne() const
{
	return IS_PED_PRONE(this->mHandle) != 0;
}

bool GTAped::IsGettingUp() const
{
	return IS_PED_GETTING_UP(this->mHandle) != 0;
}

bool GTAped::IsGettingIntoAVehicle() const
{
	return IS_PED_GETTING_INTO_A_VEHICLE(this->mHandle) != 0;
}

bool GTAped::IsGoingIntoCover() const
{
	return IS_PED_GOING_INTO_COVER(this->mHandle) != 0;
}

bool GTAped::IsInjured() const
{
	return IS_PED_INJURED(this->mHandle) != 0;
}

bool GTAped::IsInBoat() const
{
	return IS_PED_IN_ANY_BOAT(this->mHandle) != 0;
}

bool GTAped::IsInCombat() const
{
	return IS_PED_IN_COMBAT(this->mHandle, 0) != 0;
}
bool GTAped::IsInCombatWith(const GTAped& target) const
{
	return IS_PED_IN_COMBAT(this->mHandle, target.mHandle) != 0;
}

bool GTAped::IsInCoverFacingLeft() const
{
	return IS_PED_IN_COVER_FACING_LEFT(this->mHandle) != 0;
}

bool GTAped::IsInFlyingVehicle() const
{
	return IS_PED_IN_FLYING_VEHICLE(this->mHandle) != 0;
}

bool GTAped::IsInHeli() const
{
	return IS_PED_IN_ANY_HELI(this->mHandle) != 0;
}
bool GTAped::IsInPlane() const
{
	return IS_PED_IN_ANY_PLANE(this->mHandle) != 0;
}
bool GTAped::IsInPoliceVehicle() const
{
	return IS_PED_IN_ANY_POLICE_VEHICLE(this->mHandle) != 0;
}
bool GTAped::IsInSub() const
{
	return IS_PED_IN_ANY_SUB(this->mHandle) != 0;
}
bool GTAped::IsInTrain() const
{
	return IS_PED_IN_ANY_TRAIN(this->mHandle) != 0;
}
bool GTAped::IsOnBike() const
{
	return IS_PED_ON_ANY_BIKE(this->mHandle) != 0;
}
bool GTAped::IsOnFoot() const
{
	return IS_PED_ON_FOOT(this->mHandle) != 0;
}

bool GTAped::IsInMeleeCombat() const
{
	return IS_PED_IN_MELEE_COMBAT(this->mHandle) != 0;
}

bool GTAped::IsJacking() const
{
	return IS_PED_JACKING(this->mHandle) != 0;
}

bool GTAped::IsPlayer() const
{
	return IS_PED_A_PLAYER(this->mHandle) != 0;
}

void GTAped::SetPriorityTargetForEnemies(bool value)
{
	SET_ENTITY_IS_TARGET_PRIORITY(this->mHandle, value, 0.0f);
}

bool GTAped::IsRagdoll() const
{
	return IS_PED_RAGDOLL(this->mHandle) != 0;
}

bool GTAped::IsWalking() const
{
	return IS_PED_WALKING(this->mHandle) != 0;
}
bool GTAped::IsRunning() const
{
	return IS_PED_RUNNING(this->mHandle) != 0;
}
bool GTAped::IsSprinting() const
{
	return IS_PED_SPRINTING(this->mHandle) != 0;
}
bool GTAped::IsJumping() const
{
	return IS_PED_JUMPING(this->mHandle) != 0;
}

bool GTAped::IsShooting() const
{
	return IS_PED_SHOOTING(this->mHandle) != 0;
}
bool GTAped::IsReloading() const
{
	return IS_PED_RELOADING(this->mHandle) != 0;
}

bool GTAped::IsStopped() const
{
	return IS_PED_STOPPED(this->mHandle) != 0;
}

bool GTAped::IsSwimming() const
{
	return IS_PED_SWIMMING(this->mHandle) != 0;
}
bool GTAped::IsSwimmingUnderWater() const
{
	return IS_PED_SWIMMING_UNDER_WATER(this->mHandle) != 0;
}

bool GTAped::IsTryingToEnterALockedVehicle() const
{
	return IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(this->mHandle) != 0;
}

int GTAped::Money_get() const
{
	return GET_PED_MONEY(this->mHandle);
}
void GTAped::Money_set(int value)
{
	SET_PED_MONEY(this->mHandle, value);
}

Hash GTAped::RelationshipGroup_get() const
{
	return GET_PED_RELATIONSHIP_GROUP_HASH(this->mHandle);
}
void GTAped::RelationshipGroup_set(Hash grpHash)
{
	SET_PED_RELATIONSHIP_GROUP_HASH(this->mHandle, grpHash);
}
void GTAped::RelationshipGroup_set(const std::string& grpName)
{
	SET_PED_RELATIONSHIP_GROUP_HASH(this->mHandle, GET_HASH_KEY(grpName));
}

void GTAped::ShootRate_set(int value)
{
	SET_PED_SHOOT_RATE(this->mHandle, value);
}

void GTAped::HasGravity_set(bool value)
{
	SET_PED_GRAVITY(this->mHandle, value);
	GTAentity::HasGravity_set(value);
}

Tasks GTAped::Task()
{
	return _tasks;
}
int GTAped::TaskSequenceProgress_get() const
{
	return GET_SEQUENCE_PROGRESS(this->mHandle);
}
bool GTAped::IsPerformingAnyTaskSequence() const
{
	return GET_SEQUENCE_PROGRESS(this->mHandle) > -1;
}

bool GTAped::WasKilledByStealth() const
{
	return WAS_PED_KILLED_BY_STEALTH(this->mHandle) != 0;
}
bool GTAped::WasKilledByTakedown() const
{
	return WAS_PED_KILLED_BY_TAKEDOWN(this->mHandle) != 0;
}

void GTAped::WetnessHeight_set(float value)
{
	SET_PED_WETNESS_HEIGHT(this->mHandle, value);
}

bool GTAped::IsInVehicle() const
{
	//return IS_PED_SITTING_IN_ANY_VEHICLE(this->mHandle) != 0;
	return DOES_ENTITY_EXIST(GET_VEHICLE_PED_IS_USING(this->mHandle)) != 0;
}
bool GTAped::IsInVehicle(GTAvehicle vehicle) const
{
	//return IS_PED_SITTING_IN_VEHICLE(this->mHandle, vehicle.Handle()) != 0;
	return GET_VEHICLE_PED_IS_USING(this->mHandle) == vehicle.Handle();
}
GTAvehicle GTAped::CurrentVehicle() const
{
	return GET_VEHICLE_PED_IS_USING(this->mHandle);
}

VehicleSeat GTAped::CurrentVehicleSeat_get()
{
	if (this->IsInVehicle())
	{
		auto& vehHandle = this->CurrentVehicle().Handle();
		for (INT8 i = -1; i < GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehHandle) - 1; i++)
		{
			if (GET_PED_IN_VEHICLE_SEAT(vehHandle, i, 0) == this->mHandle)
				return (VehicleSeat)i;
		}
	}
	return VehicleSeat::SEAT_ANY;
}

int GTAped::GetRelationshipWithPed(GTAentity otherPed) const
{
	return GET_RELATIONSHIP_BETWEEN_PEDS(this->mHandle, otherPed.Handle());
}

void GTAped::SetIntoVehicle(GTAvehicle vehicle, VehicleSeat seat)
{
	SET_PED_INTO_VEHICLE(this->mHandle, vehicle.Handle(), (seat));
}

bool GTAped::IsInCover() const
{
	return this->IsInCover(false);
}
bool GTAped::IsInCover(bool expectUseWeapon) const
{
	return IS_PED_IN_COVER(this->mHandle, expectUseWeapon) != 0;
}

GTAentity GTAped::GetJacker() const
{
	return GET_PEDS_JACKER(this->mHandle);
}
GTAentity GTAped::GetJackTarget() const
{
	return GET_JACK_TARGET(this->mHandle);
}
GTAentity GTAped::GetSourceOfDeath() const
{
	return GET_PED_SOURCE_OF_DEATH(this->mHandle);
}
void GTAped::Kill()
{
	this->Health_set(0);
}
void GTAped::ExplodeHead(Hash weaponHash)
{
	EXPLODE_PED_HEAD(this->mHandle, weaponHash);
}

void GTAped::ResetVisibleDamage()
{
	RESET_PED_VISIBLE_DAMAGE(this->mHandle);
}
void GTAped::ClearBloodDamage()
{
	CLEAR_PED_BLOOD_DAMAGE(this->mHandle);
}
void GTAped::ApplyDamage(int damageAmount)
{
	APPLY_DAMAGE_TO_PED(this->mHandle, damageAmount, true, 0);
}

Vector3 GTAped::GetBoneCoord(int boneID) const
{
	return GET_PED_BONE_COORDS(this->mHandle, boneID, 0, 0, 0);
}
Vector3 GTAped::GetBoneCoord(int boneID, const Vector3& offset) const
{
	return GET_PED_BONE_COORDS(this->mHandle, boneID, offset.x, offset.y, offset.z);
}
int GTAped::GetBoneIndex(int boneID) const
{
	return GET_PED_BONE_INDEX(this->mHandle, boneID);
}

void GTAped::ApplyBlood(const std::string& bloodDecalName, int boneID)
{
	this->ApplyBlood(bloodDecalName, boneID, Vector3());
}
void GTAped::ApplyBlood(const std::string& bloodDecalName, int boneID, const Vector3& rotation)
{
	APPLY_PED_BLOOD(this->mHandle, boneID, rotation.x, rotation.y, rotation.z, (PCHAR)bloodDecalName.c_str());
}

void GTAped::ApplyDamageDecal(const std::string& damageDecalName, int boneID, const Vector3& rotation, float damageScale, float multiplier, int state, bool b1)
{
	APPLY_PED_DAMAGE_DECAL(this->mHandle, boneID, rotation.x, rotation.y, rotation.z, damageScale, multiplier, state, b1, (PCHAR)damageDecalName.c_str());
}
void GTAped::ApplyDamagePack(const std::string& damagePackName, float damageAmount, float multiplier)
{
	APPLY_PED_DAMAGE_PACK(this->mHandle, (PCHAR)damagePackName.c_str(), damageAmount, multiplier);
}

void GTAped::StoreWeaponsInArray(std::vector<s_Weapon_Components_Tint>& result)
{
	result.clear();

	s_Weapon_Components_Tint wct;
	for (auto& cc : WeaponIndivs::vAllWeapons)
	{
		for (auto& c : *cc)
		{
			if (HAS_PED_GOT_WEAPON(this->mHandle, c.weaponHash, false))
			{
				wct.componentHashes.clear();
				wct.weaponHash = c.weaponHash;
				for (const auto& comp : c.components)
				{
					if (HAS_PED_GOT_WEAPON_COMPONENT(this->mHandle, c.weaponHash, comp.hash))
					{
						wct.componentHashes.push_back({ comp.hash, GET_PED_WEAPON_COMPONENT_TINT_INDEX(this->mHandle, c.weaponHash, comp.hash) });
					}
				}
				wct.tint = GET_PED_WEAPON_TINT_INDEX(this->mHandle, c.weaponHash);

				result.push_back(wct);
			}
		}
	}
	if (HAS_PED_GOT_WEAPON(this->mHandle, GADGET_PARACHUTE, false))
	{
		wct.componentHashes.clear();
		wct.weaponHash = GADGET_PARACHUTE;
		result.push_back(wct);
	}
	// Armour??
}
void GTAped::GiveWeaponsFromArray(const std::vector<s_Weapon_Components_Tint>& value)
{
	bool bHasControl = this->HasControl();
	for (auto& cc : value)
	{
		if (cc.weaponHash)
		{
			bHasControl ?
				GIVE_WEAPON_TO_PED(this->mHandle, cc.weaponHash, 1, true, false) :
				GIVE_DELAYED_WEAPON_TO_PED(this->mHandle, cc.weaponHash, 1, false);

			for (auto& compHash : cc.componentHashes)
			{
				if (compHash.first)
				{
					GIVE_WEAPON_COMPONENT_TO_PED(this->mHandle, cc.weaponHash, compHash.first);
					if (compHash.second != -1)
						SET_PED_WEAPON_COMPONENT_TINT_INDEX(this->mHandle, cc.weaponHash, compHash.first, compHash.second);
				}
			}

			if (cc.weaponHash != GADGET_PARACHUTE)
			{
				int ammo;
				GET_MAX_AMMO(this->mHandle, cc.weaponHash, &ammo);
				SET_PED_AMMO(this->mHandle, cc.weaponHash, ammo, 0);
				SET_AMMO_IN_CLIP(this->mHandle, cc.weaponHash, GET_MAX_AMMO_IN_CLIP(this->mHandle, cc.weaponHash, true));
				SET_PED_WEAPON_TINT_INDEX(this->mHandle, cc.weaponHash, cc.tint);
			}
		}
	}
}







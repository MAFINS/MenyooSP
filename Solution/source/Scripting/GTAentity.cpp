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
#include "GTAentity.h"

#include "..\macros.h"

#include "enums.h"
#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "..\Memory\GTAmemory.h"
#include "GTAblip.h"
#include "Model.h"
#include "Raycast.h"

#include <string>

GTAentity& GTAentity::operator = (const GTAentity& value)
{
	this->mHandle = value.mHandle;
	return *this;
}
bool operator == (const GTAentity& left, const GTAentity& right)
{
	return left.mHandle == right.mHandle;
}
bool operator != (const GTAentity& left, const GTAentity& right)
{
	return left.mHandle != right.mHandle;
}
bool operator < (const GTAentity& left, const GTAentity& right)
{
	return left.mHandle < right.mHandle;
}
bool operator > (const GTAentity& left, const GTAentity& right)
{
	return left.mHandle > right.mHandle;
}

GTAentity::GTAentity()
	: mHandle(0)
{
}
GTAentity::GTAentity(int handle)
	: mHandle(handle)
{
}

int& GTAentity::Handle()
{
	return this->mHandle;
}
int GTAentity::GetHandle() const
{
	return this->mHandle;
}
//void GTAentity::SetHandle(Entity handle)
//{
//	this->mHandle = handle;
//}

UINT64 GTAentity::MemoryAddress() const
{
	return GTAmemory::GetEntityAddress(this->GetHandle());
}

int GTAentity::Type() const
{
	return GET_ENTITY_TYPE(this->mHandle);
}

GTAblip GTAentity::CurrentBlip() const
{
	return GET_BLIP_FROM_ENTITY(this->mHandle);
}

Vector3 GTAentity::ForwardVector() const
{
	//return GET_ENTITY_FORWARD_VECTOR(this->mHandle);
	return GTAmemory::ReadVector3(this->MemoryAddress() + 0x70);
}
Vector3 GTAentity::RightVector() const
{
	//return Vector3::Cross(ForwardVector(), Vector3::WorldUp());
	return GTAmemory::ReadVector3(this->MemoryAddress() + 0x60);
}
Vector3 GTAentity::UpVector() const
{
	//return Vector3::Cross(RightVector(), ForwardVector());
	return GTAmemory::ReadVector3(this->MemoryAddress() + 0x80);
}

bool GTAentity::IsPositionFrozen() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(this->MemoryAddress() + 0x2E), 1);
	}
	else return false;
}
void GTAentity::FreezePosition(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		SetClearBit(*(int*)(this->MemoryAddress() + 0x2E), 1, value);
	}
	FREEZE_ENTITY_POSITION(this->mHandle, value);
}

void GTAentity::Dynamic_set(bool value)
{
	SET_ENTITY_DYNAMIC(this->mHandle, value);
	if (value)
	{
		SET_ENTITY_VELOCITY(this->mHandle, 0.0f, 0.0f, 0.0f);
	}
}

float GTAentity::Heading_get() const
{
	return GET_ENTITY_HEADING(this->mHandle);
}
void GTAentity::Heading_set(float value)
{
	SET_ENTITY_HEADING(this->mHandle, value);
}

int GTAentity::Health_get() const
{
	return GET_ENTITY_HEALTH(this->mHandle);
}
void GTAentity::Health_set(int value)
{
	SET_ENTITY_HEALTH(this->mHandle, value);
}

float GTAentity::HeightAboveGround() const
{
	return GET_ENTITY_HEIGHT_ABOVE_GROUND(this->mHandle);
}
float GTAentity::GetGroundZ() const
{
	Vector3& pos = this->Position_get();
	GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, 1100.0f, &pos.z);
	return pos.z;
}
void GTAentity::PlaceOnGround()
{
	Vector3& pos = this->Position_get();

	RaycastResult& ray1 = RaycastResult::Raycast(pos, Vector3(0, 0, -1.0f), 10000.0f, IntersectOptions::Map);
	if (ray1.DidHitAnything())
	{
		this->Position_set(ray1.HitCoords() + Vector3(0, 0, this->Dim1().z));
		return;
	}
	RaycastResult& ray2 = RaycastResult::Raycast(pos, Vector3(0, 0, 1.0f), 10000.0f, IntersectOptions::Map);
	if (ray2.DidHitAnything())
	{
		this->Position_set(ray2.HitCoords() + Vector3(0, 0, this->Dim1().z));
		return;
	}

	pos.z = this->GetGroundZ() + this->Dim1().z;
	//NETWORK_REQUEST_CONTROL_OF_ENTITY(this->mHandle);
	SET_ENTITY_COORDS(this->mHandle, pos.x, pos.y, pos.z, 0, 0, 0, 1);
	PLACE_OBJECT_ON_GROUND_PROPERLY(this->mHandle);
}

bool GTAentity::IsAlive() const
{
	return !this->IsDead();
}
bool GTAentity::IsDead() const
{
	return IS_ENTITY_DEAD(this->mHandle) != 0;
}
bool GTAentity::IsInAir() const
{
	return IS_ENTITY_IN_AIR(this->mHandle) != 0;
}
bool GTAentity::IsInWater() const
{
	return IS_ENTITY_IN_WATER(this->mHandle) != 0;
}
bool GTAentity::IsSubmerged() const
{
	return GET_ENTITY_SUBMERGED_LEVEL(this->mHandle) != 0;
}
bool GTAentity::IsOccluded() const
{
	return IS_ENTITY_OCCLUDED(this->mHandle) != 0;
}
bool GTAentity::IsOnScreen() const
{
	return IS_ENTITY_ON_SCREEN(this->mHandle) != 0;
}

bool GTAentity::IsPed() const
{
	return IS_ENTITY_A_PED(this->mHandle) != 0;
}
bool GTAentity::IsVehicle() const
{
	return IS_ENTITY_A_VEHICLE(this->mHandle) != 0;
}
bool GTAentity::IsProp() const
{
	return IS_ENTITY_AN_OBJECT(this->mHandle) != 0;
}

//void GTAentity::SetInvincible(bool value)
//{
//	SET_ENTITY_INVINCIBLE(this->mHandle, value);
//}
void GTAentity::SetProofs(bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool unk1, bool unk2, bool drownProof)
{
	SET_ENTITY_PROOFS(this->mHandle, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, unk1, unk2, drownProof);
}

bool GTAentity::IsOnFire() const
{
	return IS_ENTITY_ON_FIRE(this->mHandle) != 0;
}
void GTAentity::SetOnFire(bool value)
{
	value ? START_ENTITY_FIRE(this->mHandle) : STOP_ENTITY_FIRE(this->mHandle);
}

bool GTAentity::MissionEntity_get() const
{
	return IS_ENTITY_A_MISSION_ENTITY(this->mHandle) != 0;
}
void GTAentity::MissionEntity_set(bool value)
{
	SET_ENTITY_AS_MISSION_ENTITY(this->mHandle, value, 1);
}

bool GTAentity::IsUpright() const
{
	return IS_ENTITY_UPRIGHT(this->mHandle, 0) != 0;
}
void GTAentity::SetUpright()
{
	SET_ENTITY_HEADING(this->mHandle, Heading_get() + 1.0f);
	SET_ENTITY_HEADING(this->mHandle, Heading_get() - 1.0f);
}

bool GTAentity::IsUpsideDown() const
{
	return IS_ENTITY_UPSIDEDOWN(this->mHandle) != 0;
}

bool GTAentity::IsVisible() const
{
	return IS_ENTITY_VISIBLE(this->mHandle) != 0;
}
void GTAentity::SetVisible(bool value)
{
	SET_ENTITY_VISIBLE(this->mHandle, value);
}

int GTAentity::MaxHealth_get() const
{
	return GET_ENTITY_MAX_HEALTH(this->mHandle);
}
void GTAentity::MaxHealth_set(int value)
{
	SET_ENTITY_MAX_HEALTH(this->mHandle, value);
}

GTAmodel::Model GTAentity::Model() const
{
	return GET_ENTITY_MODEL(this->mHandle);
}
GTAmodel::ModelDimensions GTAentity::ModelDimensions() const
{
	return this->Model().Dimensions();
}
void GTAentity::ModelDimensions(Vector3 &dim1, Vector3 &dim2) const
{
	this->Model().Dimensions(dim1, dim2);
}
Vector3 GTAentity::Dim1() const
{
	return this->Model().Dimensions().Dim1;
}
Vector3 GTAentity::Dim2() const
{
	return this->Model().Dimensions().Dim2;
}


Vector3 GTAentity::Position_get() const
{
	return GET_ENTITY_COORDS(this->mHandle, 1);
}
void GTAentity::Position_set(Vector3 value)
{
	SET_ENTITY_COORDS_NO_OFFSET(this->mHandle, value.x, value.y, value.z, 1, 1, 1);
}

Vector3 GTAentity::Rotation_get() const
{
	return GET_ENTITY_ROTATION(this->mHandle, 2);
}
void GTAentity::Rotation_set(Vector3 value)
{
	SET_ENTITY_ROTATION(this->mHandle, value.x, value.y, value.z, 2, 1);
}

Vector3 GTAentity::Direction_get() const
{
	return Vector3::RotationToDirection(GET_ENTITY_ROTATION(this->mHandle, 2));
}
void GTAentity::Direction_set(Vector3 value)
{
	value = Vector3::DirectionToRotation(value);
	SET_ENTITY_ROTATION(this->mHandle, value.x, value.y, value.z, 2, 1);
}


Vector3 GTAentity::Velocity_get() const
{
	return GET_ENTITY_VELOCITY(this->mHandle);
}
void GTAentity::Velocity_set(Vector3 value)
{
	SET_ENTITY_VELOCITY(this->mHandle, value.x, value.y, value.z);
}
Vector3 GTAentity::RotationVelocity_get() const
{
	return GET_ENTITY_ROTATION_VELOCITY(this->mHandle);
}
float GTAentity::Speed_get() const
{
	return GET_ENTITY_SPEED(this->mHandle);
}
void GTAentity::MaxSpeed_set(float value)
{
	SET_ENTITY_MAX_SPEED(this->mHandle, value);
}
Vector3 GTAentity::SpeedVector_get(bool relative)
{
	return GET_ENTITY_SPEED_VECTOR(this->mHandle, relative);
}

int GTAentity::Alpha_get() const
{
	return GET_ENTITY_ALPHA(this->mHandle);
}
void GTAentity::Alpha_set(int value)
{
	if(value == 255)
		RESET_ENTITY_ALPHA(this->mHandle);
	else
		SET_ENTITY_ALPHA(this->mHandle, value, 0);
}
void GTAentity::ResetAlpha()
{
	RESET_ENTITY_ALPHA(this->mHandle);
}

int GTAentity::LodDistance_get() const
{
	return GET_ENTITY_LOD_DIST(this->mHandle);
}
void GTAentity::LodDistance_set(int value)
{
	SET_ENTITY_LOD_DIST(this->mHandle, value);
}

bool GTAentity::HasGravity_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return !IsBitSet(*(int*)(memoryAddress + 26), 4);
	}
	else return true;
}
void GTAentity::HasGravity_set(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		SetClearBit(*(int*)(memoryAddress + 26), 4, !value);
	}
	SET_ENTITY_HAS_GRAVITY(this->mHandle, value);
}

Vector3 GTAentity::CollisionNormal() const
{
	return GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(this->mHandle);
}
bool GTAentity::HasCollided() const
{
	return HAS_ENTITY_COLLIDED_WITH_ANYTHING(this->mHandle) != 0;
}
void GTAentity::IsRecordingCollisions_set(bool value)
{
	SET_ENTITY_RECORDS_COLLISIONS(this->mHandle, value);
}
void GTAentity::HasCollisionWithEntity_set(const GTAentity& ent, bool value)
{
	SET_ENTITY_NO_COLLISION_ENTITY(this->mHandle, ent.mHandle, value);
}
bool GTAentity::IsCollisionEnabled_get() const
{
	return !_IS_ENTITY_COLLISON_DISABLED(this->mHandle);
}
void GTAentity::IsCollisionEnabled_set(bool value)
{
	SET_ENTITY_COLLISION(this->mHandle, value, false);
}


int GTAentity::NetID() const
{
	return NETWORK_GET_NETWORK_ID_FROM_ENTITY(this->mHandle);
}

bool GTAentity::IsInRangeOf(Vector3 position, float range) const
{
	return ((Vector3::Subtract(this->Position_get(), position).Length()) < range);
}
bool GTAentity::IsInArea(Vector3 pos1, Vector3 pos2) const
{
	return IsInArea(pos1, pos2, 0);
}
bool GTAentity::IsInArea(Vector3 pos1, Vector3 pos2, float angle) const
{
	return IS_ENTITY_IN_ANGLED_AREA(this->mHandle, pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, angle, true, true, true) != 0;
}
bool GTAentity::IsNearEntity(GTAentity entity, Vector3 distance) const
{
	return IS_ENTITY_AT_ENTITY(this->mHandle, entity.Handle(), distance.x, distance.y, distance.z, 0, 1, 0) != 0;
}
bool GTAentity::IsTouching(GTAentity entity) const
{
	return IS_ENTITY_TOUCHING_ENTITY(this->mHandle, entity.Handle()) != 0;
}
bool GTAentity::HasBeenDamagedBy(GTAentity entity) const
{
	return HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(this->mHandle, entity.Handle(), 1) != 0;
}
Vector3 GTAentity::GetOffsetInWorldCoords(Vector3 offset) const
{
	return GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(this->mHandle, offset.x, offset.y, offset.z);
}
Vector3 GTAentity::GetOffsetInWorldCoords(float X, float Y, float Z) const
{
	return GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(this->mHandle, X, Y, Z);
}
Vector3 GTAentity::GetOffsetGivenWorldCoords(Vector3 coord) const
{
	return GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(this->mHandle, coord.x, coord.y, coord.z);
}
int GTAentity::GetBoneIndex(const std::string& boneLabel) const
{
	if (boneLabel.length() == 0)
		return 0;
	return GET_ENTITY_BONE_INDEX_BY_NAME(this->mHandle, const_cast<PCHAR>(boneLabel.c_str()));
}
int GTAentity::GetBoneIndex(VBone::VBone value) const
{
	return GET_ENTITY_BONE_INDEX_BY_NAME(this->mHandle, const_cast<PCHAR>(VBone::vNames[value].c_str()));
}
Vector3 GTAentity::GetBoneCoords(int boneIndex) const
{
	return GET_WORLD_POSITION_OF_ENTITY_BONE(this->mHandle, boneIndex);
}
Vector3 GTAentity::GetBoneCoords(const std::string& boneLabel) const
{
	return GET_WORLD_POSITION_OF_ENTITY_BONE(this->mHandle, this->GetBoneIndex(boneLabel));
}
int GTAentity::GetBoneCount() const
{
	return GTAmemory::GetEntityBoneCount(this->mHandle);
}
UINT64 GTAentity::GetBoneMatrixAddress(int boneIndex) const
{
	return GTAmemory::GetEntityBoneMatrixAddress(this->mHandle, boneIndex);
}
Vector3 GTAentity::GetOffsetFromBoneInWorldCoords(int boneIndex, const Vector3& offset) const
{
	if (this->Exists())
	{
		auto addr = GTAmemory::GetEntityBoneMatrixAddress(this->mHandle, boneIndex);
		if (addr)
		{
			float* Addr = (float*)(addr);
			Vector3& right = Vector3(Addr[0], Addr[1], Addr[2]);
			Vector3& front = Vector3(Addr[4], Addr[5], Addr[6]);
			Vector3& up = Vector3(Addr[8], Addr[9], Addr[10]);
			Vector3& boneOff = Vector3(Addr[12], Addr[13], Addr[14]);
			Vector3& vehOffset = boneOff + right*offset.x + front*offset.y + up*offset.z;
			return this->GetOffsetInWorldCoords(vehOffset);
		}
	}
	return Vector3();
}
Vector3 GTAentity::GetOffsetFromBoneInWorldCoords(const std::string& boneLabel, const Vector3& offset) const
{
	return this->GetOffsetFromBoneInWorldCoords(this->GetBoneIndex(boneLabel), offset);
}
bool GTAentity::HasBone(const std::string& boneLabel) const
{
	return this->GetBoneIndex(boneLabel) != -1;
}
bool GTAentity::HasBone(VBone::VBone value) const
{
	return this->GetBoneIndex(VBone::vNames[value]) != -1;
}

bool GTAentity::IsAttached() const
{
	return IS_ENTITY_ATTACHED(this->mHandle) != 0;
}
bool GTAentity::IsAttachedTo(const GTAentity& to) const
{
	return IS_ENTITY_ATTACHED_TO_ENTITY(this->mHandle, to.mHandle) != 0;
}
void GTAentity::Detach()
{
	DETACH_ENTITY(this->mHandle, 1, 1);
}
void GTAentity::AttachTo(GTAentity entity, int boneIndex, bool collision)
{
	this->AttachTo(entity.Handle(), boneIndex, collision, Vector3(0, 0, 0), Vector3(0, 0, 0));
}
void GTAentity::AttachTo(GTAentity entity, int boneIndex, bool collision, Vector3 position, Vector3 rotation)
{
	ATTACH_ENTITY_TO_ENTITY(this->mHandle, entity.Handle(), boneIndex, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, FALSE, FALSE, collision, FALSE, 2, TRUE);
}
void GTAentity::AttachTo(GTAentity entity, int boneIndex, Vector3 position, Vector3 rotation, bool b9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot)
{
	ATTACH_ENTITY_TO_ENTITY(this->mHandle, entity.Handle(), boneIndex, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, b9, useSoftPinning, collision, isPed, vertexIndex, fixedRot);
}
void GTAentity::AttachPhysicallyTo(GTAentity entity, int boneIndexDoer, int boneIndexGetter, float forceToBreak)
{
	this->AttachPhysicallyTo(entity, boneIndexDoer, boneIndexGetter, forceToBreak, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0));
}
void GTAentity::AttachPhysicallyTo(GTAentity entity, int boneIndexDoer, int boneIndexGetter, float forceToBreak, Vector3 position1, Vector3 position2, Vector3 rotation)
{
	ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(this->mHandle, entity.Handle(), boneIndexDoer, boneIndexGetter, position1.x, position1.y, position1.z, position2.x, position2.y, position2.z, rotation.x, rotation.y, rotation.z, forceToBreak, 1, 1, 1, 1, 2);
}

GTAblip GTAentity::AddBlip()
{
	return ADD_BLIP_FOR_ENTITY(this->mHandle);
}

void GTAentity::SetMass(float mass)
{
	SET_OBJECT_PHYSICS_PARAMS(this->mHandle, mass, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}
void GTAentity::Oscillate(const Vector3& position, float angleFreq, float dampRatio)
{
	//Zorg93 - bring entity to position without lerp function using applyforce
	this->ApplyForce(((position - this->Position_get()) * (angleFreq * angleFreq)) -
		(2.0f * angleFreq * dampRatio * this->Velocity_get()) + Vector3(0.0f, 0.0f, 0.1f), ForceType::MaxForceRot2);
}
void OscillateEntity(GTAentity entity, const Vector3& position, float angleFreq, float dampRatio)
{
	entity.Oscillate(position, angleFreq, dampRatio);
}
void GTAentity::ApplyForce(Vector3 direction, ForceType forceType)
{
	this->ApplyForce(direction, Vector3(0, 0, 0), forceType);
	//APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(this->mHandle, forceType, direction.x, direction.y, direction.z, false, true, true, false);
}
void GTAentity::ApplyForce(Vector3 direction, Vector3 offset, ForceType forceType)
{
	APPLY_FORCE_TO_ENTITY(this->mHandle, static_cast<int>(forceType), direction.x, direction.y, direction.z, offset.x, offset.y, offset.z, false, false, true, true, false, true);
}
void GTAentity::ApplyForceRelative(Vector3 direction, ForceType forceType)
{
	this->ApplyForceRelative(direction, Vector3(0, 0, 0), forceType);
}
void GTAentity::ApplyForceRelative(Vector3 direction, Vector3 offset, ForceType forceType)
{
	APPLY_FORCE_TO_ENTITY(this->mHandle, static_cast<int>(forceType), direction.x, direction.y, direction.z, offset.x, offset.y, offset.z, false, true, true, true, false, true);
}
void GTAentity::ApplyForceCustom(Vector3 direction, Vector3 offset, ForceType forceType, bool unk1, bool isRel, bool ignoreUpVector, bool unk2, bool unk3, bool unk4)
{
	APPLY_FORCE_TO_ENTITY(this->mHandle, static_cast<int>(forceType), direction.x, direction.y, direction.z, offset.x, offset.y, offset.z, unk1, isRel, ignoreUpVector, unk2, unk3, unk4);
}


bool GTAentity::HasControl() const
{
	return NETWORK_HAS_CONTROL_OF_ENTITY(this->mHandle) != 0;
}
bool GTAentity::RequestControlOnce()
{
	if (!NETWORK_IS_IN_SESSION() || this->HasControl())
		return true;
	NETWORK::SET_NETWORK_ID_CAN_MIGRATE(this->NetID(), true);
	return NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(this->mHandle) != 0;
}
bool GTAentity::RequestControl()
{
	uint8_t tick = 0;

	while (!this->RequestControlOnce() && tick <= 12)
	{
		//WAIT(0); // Let's just not wait here ever again geez
		tick++;
	}
	return tick <= 12;
}
bool GTAentity::RequestControl(DWORD timeOut)
{
	for (timeOut += GetTickCount(); GetTickCount() < timeOut;)
	{
		if (this->RequestControlOnce())
			return true;
		WAIT(0);
	}
	return false;
}
void GTAentity::Delete(bool tele)
{
	if (!this->Exists()) return;

	this->RequestControl();

	GTAblip blip = this->CurrentBlip();
	if (blip.Exists()) blip.Remove();

	this->MissionEntity_set(false);

	if (tele) SET_ENTITY_COORDS_NO_OFFSET(this->mHandle, 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0);

	auto handle = this->mHandle;
	this->mHandle = 0;

	switch ((EntityType)this->Type())
	{
	case EntityType::PROP: DELETE_OBJECT(&handle); break;
	case EntityType::VEHICLE: DELETE_VEHICLE(&handle); break;
	case EntityType::PED: DELETE_PED(&handle); break;
	default: DELETE_ENTITY(&handle); break;
	}
}
bool GTAentity::Exists() const
{
	return DOES_ENTITY_EXIST(this->mHandle) != 0;
}
void GTAentity::NoLongerNeeded()
{
	SET_ENTITY_AS_NO_LONGER_NEEDED(&this->mHandle);
	//delete this;
}
bool GTAentity::Equals(int value) const
{
	return (this->mHandle == value);
}
bool GTAentity::Equals(GTAentity const& value) const
{
	return (this->mHandle == value.mHandle);
}


bool GTAentity::IsBulletProof() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 4);
	}
	else return false;
}
void GTAentity::SetBulletProof(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 4, value);
	}
}

//bool GTAentity::IsCollisionProof() const
//{
//	auto memoryAddress = this->MemoryAddress();
//	if (memoryAddress)
//	{
//		return IsBitSet(*(int*)(memoryAddress + 392), 6);
//	}
//	else return false;
//}
//void GTAentity::SetCollisionProof(bool value)
//{
//	auto memoryAddress = this->MemoryAddress();
//	if (memoryAddress)
//	{
//		return SetClearBit(*(int*)(memoryAddress + 392), 6, value);
//	}
//
//	SET_ENTITY_COLLISION(this->mHandle, !value, false);
//}

bool GTAentity::IsExplosionProof() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 11);
	}
	else return false;
}
void GTAentity::SetExplosionProof(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 11, value);
	}
}

bool GTAentity::IsFireProof() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 5);
	}
	else return false;
}
void GTAentity::SetFireProof(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 5, value);
	}
}

bool GTAentity::IsInvincible() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 8);
	}
	else return false;
}
void GTAentity::SetInvincible(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 8, value);
	}

	SET_ENTITY_INVINCIBLE(this->mHandle, value);
}

bool GTAentity::IsMeleeProof() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 7);
	}
	else return false;
}
void GTAentity::SetMeleeProof(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 7, value);
	}
}

bool GTAentity::IsOnlyDamagedByPlayer() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return IsBitSet(*(int*)(memoryAddress + 392), 9);
	}
	else return false;
}
void GTAentity::SetOnlyDamagedByPlayer(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		return SetClearBit(*(int*)(memoryAddress + 392), 9, value);
	}

	SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(this->mHandle, value);
}



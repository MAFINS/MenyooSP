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

#include <string>

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long DWORD;
typedef unsigned __int64 UINT64;
class Vector3;
class GTAblip;
namespace GTAmodel {
	class ModelDimensions;
	class Model;
}
namespace VBone {
	enum VBone : UINT16;
}

enum class EntityType : UINT8
{
	ALL/*Not really*/, PED, VEHICLE, PROP
};

enum class ForceType
{
	MinForce = 0,
	MaxForceRot = 1,
	MinForce2 = 2,
	MaxForceRot2 = 3,
	ForceNoRot = 4,
	ForceRotPlusForce = 5
};

class GTAentity
{
public:
	GTAentity& operator = (const GTAentity& value);
	friend bool operator == (const GTAentity& left, const GTAentity& right);
	friend bool operator != (const GTAentity& left, const GTAentity& right);
	friend bool operator < (const GTAentity& left, const GTAentity& right);
	friend bool operator > (const GTAentity& left, const GTAentity& right);

	GTAentity();
	GTAentity(int handle);
	//virtual ~GTAentity();

	int& Handle();
	int GetHandle() const;
	//void SetHandle(Entity newHandle);

	UINT64 MemoryAddress() const;

	int Type() const;

	GTAblip CurrentBlip() const;

	Vector3 ForwardVector() const;
	Vector3 RightVector() const;
	Vector3 UpVector() const;

	bool IsPositionFrozen() const;
	void FreezePosition(bool value);

	void Dynamic_set(bool value);

	float Heading_get() const;
	void Heading_set(float value);

	int Health_get() const;
	void Health_set(int value);

	float HeightAboveGround() const;
	float GetGroundZ() const;
	virtual void PlaceOnGround();

	bool IsAlive() const;
	bool IsDead() const;
	bool IsInAir() const;
	bool IsInWater() const;
	bool IsSubmerged() const;
	bool IsOccluded() const;
	bool IsOnScreen() const;

	bool IsPed() const;
	bool IsVehicle() const;
	bool IsProp() const;

	//virtual void SetInvincible(bool value);
	void SetProofs(bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool unk1, bool unk2, bool drownProof);

	bool IsOnFire() const;
	void SetOnFire(bool value);

	bool MissionEntity_get() const;
	void MissionEntity_set(bool value);

	bool IsUpright() const;
	void SetUpright();

	bool IsUpsideDown() const;

	bool IsVisible() const;
	void SetVisible(bool value);

	int MaxHealth_get() const;
	void MaxHealth_set(int value);

	GTAmodel::Model Model() const;
	GTAmodel::ModelDimensions ModelDimensions() const;
	void ModelDimensions(Vector3& dim1C, Vector3& dim2C) const;
	Vector3 Dim1() const;
	Vector3 Dim2() const;

	Vector3 Position_get() const;
	void Position_set(Vector3 value);

	Vector3 Rotation_get() const;
	void Rotation_set(Vector3 value);
	Vector3 Direction_get() const;
	void Direction_set(Vector3 value);

	Vector3 Velocity_get() const;
	void Velocity_set(Vector3 value);
	Vector3 RotationVelocity_get() const;
	float Speed_get() const;
	void MaxSpeed_set(float value);
	Vector3 SpeedVector_get(bool relative);


	int Alpha_get() const;
	void Alpha_set(int value);
	void ResetAlpha();

	int LodDistance_get() const;
	void LodDistance_set(int value);

	bool HasGravity_get() const;
	virtual void HasGravity_set(bool value);

	Vector3 CollisionNormal() const;
	bool HasCollided() const;
	void IsRecordingCollisions_set(bool value);
	void HasCollisionWithEntity_set(const GTAentity& ent, bool value);
	bool IsCollisionEnabled_get() const;
	void IsCollisionEnabled_set(bool value);

	virtual int NetID() const;

	bool IsInRangeOf(Vector3 position, float range) const;
	bool IsInArea(Vector3 pos1, Vector3 pos2) const;
	bool IsInArea(Vector3 pos1, Vector3 pos2, float angle) const;
	bool IsNearEntity(GTAentity entity, Vector3 distance) const;
	bool IsTouching(GTAentity entity) const;
	bool HasBeenDamagedBy(GTAentity entity) const;
	Vector3 GetOffsetInWorldCoords(Vector3 offset) const;
	Vector3 GetOffsetInWorldCoords(float X, float Y, float Z) const;
	Vector3 GetOffsetGivenWorldCoords(Vector3 coord) const;
	int GetBoneIndex(const std::string& boneLabel) const;
	int GetBoneIndex(VBone::VBone value) const;
	Vector3 GetBoneCoords(int boneIndex) const;
	Vector3 GetBoneCoords(const std::string& boneLabel) const;
	int GetBoneCount() const;
	UINT64 GetBoneMatrixAddress(int boneIndex) const;
	Vector3 GetOffsetFromBoneInWorldCoords(int boneLabel, const Vector3& offset) const;
	Vector3 GetOffsetFromBoneInWorldCoords(const std::string& boneLabel, const Vector3& offset) const;
	bool HasBone(const std::string& boneLabel) const;
	bool HasBone(VBone::VBone value) const;

	bool IsAttached() const;
	bool IsAttachedTo(const GTAentity& to) const;
	void AttachTo(GTAentity entity, int boneIndex, bool collision = false);
	void AttachTo(GTAentity entity, int boneIndex, bool collision, Vector3 position, Vector3 rotation);
	void AttachTo(GTAentity entity, int boneIndex, Vector3 position, Vector3 rotation, bool b9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot);
	void AttachPhysicallyTo(GTAentity entity, int boneIndexDoer, int boneIndexGetter, float forceToBreak);
	void AttachPhysicallyTo(GTAentity entity, int boneIndexDoer, int boneIndexGetter, float forceToBreak, Vector3 position1, Vector3 position2, Vector3 rotation);
	void Detach();

	GTAblip AddBlip();

	void SetMass(float mass);
	void Oscillate(const Vector3& position, float angleFreq, float dampRatio);
	friend void OscillateEntity(GTAentity entity, const Vector3& position, float angleFreq, float dampRatio);
	void ApplyForce(Vector3 direction, ForceType forceType = ForceType::MaxForceRot);
	void ApplyForce(Vector3 direction, Vector3 offset, ForceType forceType = ForceType::MaxForceRot);
	void ApplyForceRelative(Vector3 direction, ForceType forceType = ForceType::MaxForceRot);
	void ApplyForceRelative(Vector3 direction, Vector3 offset, ForceType forceType = ForceType::MaxForceRot);
	void ApplyForceCustom(Vector3 direction, Vector3 offset, ForceType forceType, bool unk1, bool isRel, bool ignoreUpVector, bool unk2, bool unk3, bool unk4);

	bool HasControl() const;
	bool RequestControlOnce();
	bool RequestControl();
	bool RequestControl(DWORD timeOut);

	virtual void Delete(bool tele = false);
	bool Exists() const;
	void NoLongerNeeded();
	bool Equals(int value) const;
	virtual bool Equals(GTAentity const& value) const;

	// Memry Hax
	bool IsBulletProof() const;
	void SetBulletProof(bool value);

	//bool IsCollisionProof() const;
	//void SetCollisionProof(bool value);

	bool IsExplosionProof() const;
	void SetExplosionProof(bool value);

	bool IsFireProof() const;
	void SetFireProof(bool value);

	bool IsInvincible() const;
	void SetInvincible(bool value);

	bool IsMeleeProof() const;
	void SetMeleeProof(bool value);

	bool IsOnlyDamagedByPlayer() const;
	void SetOnlyDamagedByPlayer(bool value);
	

protected:
	int mHandle;
	
};




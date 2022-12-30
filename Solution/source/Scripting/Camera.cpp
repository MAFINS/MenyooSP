/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Camera.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "GTAentity.h"
#include "GTAped.h"
#include "Raycast.h"

#include <string>
#include <vector>
#include <math.h>

const std::vector<std::string> CameraShakeNames{ "HAND_SHAKE", "SMALL_EXPLOSION_SHAKE", "MEDIUM_EXPLOSION_SHAKE", "LARGE_EXPLOSION_SHAKE", "JOLT_SHAKE", "VIBRATE_SHAKE", "ROAD_VIBRATION_SHAKE", "DRUNK_SHAKE", "SKY_DIVING_SHAKE", "FAMILY5_DRUG_TRIP_SHAKE", "DEATH_FAIL_IN_EFFECT_SHAKE" };

Camera::Camera() : mHandle(0), mShakeType(CameraShake::Hand), mShakeAmplitude(0.0f)
{
}
Camera::Camera(int handle) : mHandle(handle), mShakeType(CameraShake::Hand), mShakeAmplitude(0.0f)
{
}

bool operator == (const Camera& left, const Camera& right)
{
	return (left.mHandle == right.mHandle);
}
bool operator != (const Camera& left, const Camera& right)
{
	return (left.mHandle != right.mHandle);
}
Camera& Camera::operator = (const Camera& right)
{
	this->mHandle = right.mHandle;
	this->mShakeType = right.mShakeType;
	this->mShakeAmplitude = right.mShakeAmplitude;
	return *this;
}

int& Camera::Handle()
{
	return this->mHandle;
}
int Camera::GetHandle() const
{
	return this->mHandle;
}

void Camera::DepthOfFieldStrength_set(float value)
{
	SET_CAM_DOF_STRENGTH(this->mHandle, value);
}

float Camera::FieldOfView_get() const
{
	return GET_CAM_FOV(this->mHandle);
}
void Camera::FieldOfView_set(float value)
{
	SET_CAM_FOV(this->mHandle, value);
}

float Camera::FarClip_get() const
{
	return GET_CAM_FAR_CLIP(this->mHandle);
}
void Camera::FarClip_set(float value)
{
	SET_CAM_FAR_CLIP(this->mHandle, value);
}
float Camera::FarDepthOfField_get() const
{
	return GET_CAM_FAR_DOF(this->mHandle);
}
void Camera::FarDepthOfField_set(float value)
{
	SET_CAM_FAR_DOF(this->mHandle, value);
}

float Camera::NearClip_get() const
{
	return GET_CAM_NEAR_CLIP(this->mHandle);
}
void Camera::NearClip_set(float value)
{
	SET_CAM_NEAR_CLIP(this->mHandle, value);
}
void Camera::NearDepthOfField_set(float value)
{
	SET_CAM_NEAR_DOF(this->mHandle, value);
}

bool Camera::IsActive() const
{
	return IS_CAM_ACTIVE(this->mHandle) != 0;
}
void Camera::SetActive(bool value)
{
	SET_CAM_ACTIVE(this->mHandle, value);
}

bool Camera::IsInterpolating() const
{
	return IS_CAM_INTERPOLATING(this->mHandle) != 0;
}

bool Camera::IsShaking() const
{
	return IS_CAM_SHAKING(this->mHandle) != 0;
}

void Camera::SetShake(bool status)
{
	if (status)
	{
		SHAKE_CAM(this->mHandle, const_cast<PCHAR>(CameraShakeNames[static_cast<int>(this->mShakeType)].c_str()), this->mShakeAmplitude);
	}
	else
	{
		STOP_CAM_SHAKING(this->mHandle, true);
	}
}

void Camera::MotionBlurStrength_set(float value)
{
	SET_CAM_MOTION_BLUR_STRENGTH(this->mHandle, value);
}

Vector3 Camera::Position_get() const
{
	return GET_CAM_COORD(this->mHandle);
}
void Camera::Position_set(Vector3 coord)
{
	SET_CAM_COORD(this->mHandle, coord.x, coord.y, coord.z);
}
void Camera::Position_set(float X, float Y, float Z)
{
	SET_CAM_COORD(this->mHandle, X, Y, Z);
}

Vector3 Camera::Rotation_get(__int8 unk) const
{
	return GET_CAM_ROT(this->mHandle, unk);
}
void Camera::Rotation_set(const Vector3& rot, __int8 unk)
{
	SET_CAM_ROT(this->mHandle, rot.x, rot.y, rot.z, unk);
}
void Camera::Rotation_set(float X, float Y, float Z, __int8 unk)
{
	SET_CAM_ROT(this->mHandle, X, Y, Z, unk);
}


Vector3 Camera::Direction_get(__int8 unk) const
{
	return Vector3::RotationToDirection(GET_CAM_ROT(this->mHandle, unk));
}
void Camera::Direction_set(Vector3 dir, __int8 unk)
{
	dir = Vector3::DirectionToRotation(dir);
	SET_CAM_ROT(this->mHandle, dir.x, dir.y, dir.z, unk);
}
void Camera::Direction_set(float X, float Y, float Z, __int8 unk)
{
	auto& dir = Vector3::DirectionToRotation(Vector3(X, Y, Z));
	SET_CAM_ROT(this->mHandle, dir.x, dir.y, dir.z, unk);
}

float Camera::Heading_get() const
{
	return GET_CAM_ROT(this->mHandle, 2).z;
}
void Camera::Heading_set(float value)
{
	Vector3& oldRot = this->Rotation_get();
	SET_CAM_ROT(this->mHandle, oldRot.x, oldRot.y, value, 2);
}


Vector3 Camera::GetOffsetInWorldCoords(const Vector3& offset) const
{
	//return this->Position_get() + (this->Direction_get() * offset);
	Vector3& rotation = this->Rotation_get();
	Vector3& forward = Vector3::RotationToDirection(rotation);
	const double D2R = 0.01745329251994329576923690768489;
	double num1 = cos(rotation.y * D2R);
	double x = num1 * cos(-rotation.z  * D2R);
	double y = num1 * sin(rotation.z  * D2R);
	double z = sin(-rotation.y * D2R);
	Vector3& right = Vector3(x, y, z);
	Vector3& Up = Vector3::Cross(right, forward);
	return this->Position_get() + (right * offset.x) + (forward * offset.y) + (Up * offset.z);
}
Vector3 Camera::GetOffsetInWorldCoords(float X, float Y, float Z) const
{
	return this->GetOffsetInWorldCoords(Vector3(X, Y, Z));
}
Vector3 Camera::GetOffsetGivenWorldCoords(const Vector3& worldCoords) const
{
	//return this->Position_get() + (this->Direction_get() * Vector3(X, Y, Z));
	Vector3& rotation = this->Rotation_get();
	Vector3& forward = Vector3::RotationToDirection(rotation);
	const double D2R = 0.01745329251994329576923690768489;
	double num1 = cos(rotation.y * D2R);
	double x = num1 * cos(-rotation.z  * D2R);
	double y = num1 * sin(rotation.z  * D2R);
	double z = sin(-rotation.y * D2R);
	Vector3& right = Vector3(x, y, z);
	Vector3& up = Vector3::Cross(right, forward);
	Vector3& delta = worldCoords - this->Position_get();
	return Vector3(Vector3::Dot(right, delta), Vector3::Dot(forward, delta), Vector3::Dot(up, delta));
}
Vector3 Camera::GetOffsetGivenWorldCoords(float X, float Y, float Z) const
{
	return this->GetOffsetGivenWorldCoords(Vector3(X, Y, Z));
}

float Camera::ShakeAmplitude_get() const
{
	return this->mShakeAmplitude;
}
void Camera::ShakeAmplitude_set(float value)
{
	this->mShakeAmplitude = value;
	SET_CAM_SHAKE_AMPLITUDE(this->mHandle, value);
}

CameraShake Camera::ShakeType_get() const
{
	return this->mShakeType;
}
void Camera::ShakeType_set(CameraShake value)
{
	this->mShakeType = value;

	if (this->IsShaking())
	{
		SHAKE_CAM(this->mHandle, const_cast<PCHAR>(CameraShakeNames[static_cast<int>(this->mShakeType)].c_str()), this->mShakeAmplitude);
	}
}

void Camera::AttachTo(GTAentity entity, Vector3 offset)
{
	ATTACH_CAM_TO_ENTITY(this->mHandle, entity.Handle(), offset.x, offset.y, offset.z, true);
}
void Camera::AttachTo(GTAped ped, int boneIndex, Vector3 offset)
{
	ATTACH_CAM_TO_PED_BONE(this->mHandle, ped.Handle(), boneIndex, offset.x, offset.y, offset.z, true);
}
void Camera::Detach()
{
	DETACH_CAM(this->mHandle);
}

void Camera::InterpTo(Camera to, int duration, bool easePosition, bool easeRotation)
{
	SET_CAM_ACTIVE_WITH_INTERP(to.Handle(), this->mHandle, duration, easePosition, easeRotation);
}

void Camera::PointAt(Vector3 target)
{
	POINT_CAM_AT_COORD(this->mHandle, target.x, target.y, target.z);
}
void Camera::PointAt(GTAentity target)
{
	POINT_CAM_AT_ENTITY(this->mHandle, target.Handle(), 0.0f, 0.0f, 0.0f, true);
}
void Camera::PointAt(GTAentity target, Vector3 offset)
{
	POINT_CAM_AT_ENTITY(this->mHandle, target.Handle(), offset.x, offset.y, offset.z, true);
}
void Camera::PointAt(GTAped target, int boneIndex)
{
	POINT_CAM_AT_PED_BONE(this->mHandle, target.Handle(), boneIndex, 0.0f, 0.0f, 0.0f, true);
}
void Camera::PointAt(GTAped target, int boneIndex, Vector3 offset)
{
	POINT_CAM_AT_PED_BONE(this->mHandle, target.Handle(), boneIndex, offset.x, offset.y, offset.z, true);
}
void Camera::StopPointing()
{
	STOP_CAM_POINTING(this->mHandle);
}

bool Camera::Exists() const
{
	return DOES_CAM_EXIST(this->mHandle) != 0;
}

void Camera::Destroy()
{
	DESTROY_CAM(this->mHandle, false);
}
void Camera::DestroyAllCameras()
{
	DESTROY_ALL_CAMS(0);
}
void Camera::RenderScriptCams(bool render)
{
	RENDER_SCRIPT_CAMS(render, 0, 3000, 1, 0, 0);
}

Vector3 Camera::ScreenToWorld(const Vector2& screenCoord) const
{
	// Credit to Guadmaz
	Vector3& camRot = this->Rotation_get();
	Vector3& camPos = this->Position_get();

	Vector2 vector2;
	Vector2 vector21;
	Vector3& direction = Vector3::RotationToDirection(camRot);
	Vector3 vector3 = camRot + Vector3(10.f, 0.f, 0.f);
	Vector3 vector31 = camRot + Vector3(-10.f, 0.f, 0.f);
	Vector3 vector32 = camRot + Vector3(0.f, 0.f, -10.f);
	Vector3 direction1 = Vector3::RotationToDirection(camRot + Vector3(0.f, 0.f, 10.f)) - Vector3::RotationToDirection(vector32);
	Vector3 direction2 = Vector3::RotationToDirection(vector3) - Vector3::RotationToDirection(vector31);
	float rad = -DegreeToRadian(camRot.y);
	Vector3 vector33 = (direction1 * cos(rad)) - (direction2 * sin(rad));
	Vector3 vector34 = (direction1 * sin(rad)) + (direction2 * cos(rad));
	if (!WorldToScreenRel(((camPos + (direction * 10.f)) + vector33) + vector34, vector2))
	{
		return camPos + (direction * 10.f);
	}
	if (!WorldToScreenRel(camPos + (direction * 10.f), vector21))
	{
		return camPos + (direction * 10.f);
	}
	if (abs(vector2.x - vector21.x) < 0.001f || abs(vector2.y - vector21.y) < 0.001f)
	{
		return camPos + (direction * 10.f);
	}
	float x = (screenCoord.x - vector21.x) / (vector2.x - vector21.x);
	float y = (screenCoord.y - vector21.y) / (vector2.y - vector21.y);
	return ((camPos + (direction * 10.f)) + (vector33 * x)) + (vector34 * y);
}

GTAentity Camera::RaycastForEntity(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance) const
{
	// Credit to Guadmaz
	Vector3& world = this->ScreenToWorld(screenCoord);
	Vector3& vector3 = this->Position_get();
	Vector3& vector31 = world - vector3;
	vector31.Normalize();
	RaycastResult raycastResult = RaycastResult::Raycast(vector3 + (vector31 * 1.f), vector3 + (vector31 * maxDistance), IntersectOptions(287), ignoreEntity);
	return raycastResult.DidHitEntity() ? raycastResult.HitEntity() : 0;
}

Vector3 Camera::RaycastForCoord(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance, float failDistance) const
{
	// Credit to Guadmaz
	Vector3& position = this->Position_get();
	Vector3& world = this->ScreenToWorld(screenCoord);
	Vector3 vector3 = position;
	Vector3 vector31 = world - vector3;
	vector31.Normalize();
	RaycastResult raycastResult = RaycastResult::Raycast(vector3 + (vector31 * 1.f), vector3 + (vector31 * maxDistance), IntersectOptions(287), ignoreEntity);
	return raycastResult.DidHitAnything() ? raycastResult.HitCoords() : position + (vector31 * failDistance);
}

Vector3 Camera::DirectionFromScreenCentre_get() const
{
	Vector3& position = this->Position_get();
	Vector3& world = this->ScreenToWorld(Vector2(0.0f, 0.0f));
	return Vector3::Normalize(world - position);
}

bool Camera::WorldToScreenRel(const Vector3& worldCoords, Vector2& screenCoords)
{
	if (!GET_SCREEN_COORD_FROM_WORLD_COORD(worldCoords.x, worldCoords.y, worldCoords.z, &screenCoords.x, &screenCoords.y))
		return false;

	screenCoords.x = (screenCoords.x - 0.5f) * 2.0f;
	screenCoords.y = (screenCoords.y - 0.5f) * 2.0f;
	return true;
}


Vector3 get_coords_from_cam(int camid, float distance)
{
	Vector3 Rot = DegreeToRadian(GET_CAM_ROT(camid, 2));
	Vector3 Coord = GET_CAM_COORD(camid);

	Rot.y = distance * cos(Rot.x);
	Coord.x = Coord.x + Rot.y * sin(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cos(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sin(Rot.x);

	return Coord;
}



/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GameplayCamera.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "GTAentity.h"
#include "Raycast.h"
#include "Camera.h"

#include <math.h>

float GameplayCamera::FieldOfView_get()
{
	return GET_GAMEPLAY_CAM_FOV();
}
void GameplayCamera::FieldOfView_set(float value)
{
	SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(value);
}
bool GameplayCamera::IsAimCamActive()
{
	return IS_AIM_CAM_ACTIVE() != 0;
}
bool GameplayCamera::IsFirstPersonAimCamActive()
{
	return IS_FIRST_PERSON_AIM_CAM_ACTIVE() != 0;
}
bool GameplayCamera::IsLookingBehind()
{
	return IS_GAMEPLAY_CAM_LOOKING_BEHIND() != 0;
}
bool GameplayCamera::IsRendering()
{
	return IS_GAMEPLAY_CAM_RENDERING() != 0;
}
bool GameplayCamera::IsShaking()
{
	return IS_GAMEPLAY_CAM_SHAKING() != 0;
}
Vector3 GameplayCamera::Position_get()
{
	return GET_GAMEPLAY_CAM_COORD();
}
Vector3 GameplayCamera::GetOffsetInWorldCoords(const Vector3& offset)
{
	//return GameplayCamera::Position_get() + (GameplayCamera::Direction_get() * offset);
	const Vector3& rotation = GameplayCamera::Rotation_get();
	const Vector3& forward = Vector3::RotationToDirection(rotation);
	const double D2R = 0.01745329251994329576923690768489;
	double num1 = cos(rotation.y * D2R);
	double x = num1 * cos(-rotation.z  * D2R);
	double y = num1 * sin(rotation.z  * D2R);
	double z = sin(-rotation.y * D2R);
	const Vector3& right = Vector3(x, y, z);
	const Vector3& Up = Vector3::Cross(right, forward);
	return GameplayCamera::Position_get() + (right * offset.x) + (forward * offset.y) + (Up * offset.z);
}
Vector3 GameplayCamera::GetOffsetInWorldCoords(float X, float Y, float Z)
{
	return GameplayCamera::GetOffsetInWorldCoords(Vector3(X, Y, Z));
}
Vector3 GameplayCamera::GetOffsetGivenWorldCoords(const Vector3& worldCoords)
{
	//return GameplayCamera::Position_get() + (GameplayCamera::Direction_get() * Vector3(X, Y, Z));
	Vector3 rotation = GameplayCamera::Rotation_get();
	Vector3 forward = Vector3::RotationToDirection(rotation);
	const double D2R = 0.01745329251994329576923690768489;
	double num1 = cos(rotation.y * D2R);
	double x = num1 * cos(-rotation.z  * D2R);
	double y = num1 * sin(rotation.z  * D2R);
	double z = sin(-rotation.y * D2R);
	Vector3 right = Vector3(x, y, z);
	Vector3 up = Vector3::Cross(right, forward);
	Vector3 delta = worldCoords - GameplayCamera::Position_get();
	return Vector3(Vector3::Dot(right, delta), Vector3::Dot(forward, delta), Vector3::Dot(up, delta));
}
Vector3 GameplayCamera::GetOffsetGivenWorldCoords(float X, float Y, float Z)
{
	return GameplayCamera::GetOffsetGivenWorldCoords(Vector3(X, Y, Z));
}
float GameplayCamera::RelativeHeading_get()
{
	return GET_GAMEPLAY_CAM_RELATIVE_HEADING();
}
void GameplayCamera::RelativeHeading_set(float value)
{
	SET_GAMEPLAY_CAM_RELATIVE_HEADING(value);
}
float GameplayCamera::RelativePitch_get()
{
	return GET_GAMEPLAY_CAM_RELATIVE_PITCH();
}
void GameplayCamera::RelativePitch_set(float value)
{
	SET_GAMEPLAY_CAM_RELATIVE_PITCH(value, 0.0f);
}
Vector3 GameplayCamera::Rotation_get()
{
	return GET_GAMEPLAY_CAM_ROT(2);
}
Vector3 GameplayCamera::Direction_get()
{
	return Vector3::RotationToDirection(GET_GAMEPLAY_CAM_ROT(2));
}
float GameplayCamera::Zoom_get()
{
	return GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR();
}
void GameplayCamera::ShakeAmplitude_set(float value)
{
	SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(value);
}

void GameplayCamera::Shake(CameraShake shakeType, float amplitude)
{
	SHAKE_GAMEPLAY_CAM(CameraShakeNames[static_cast<int>(shakeType)].c_str(), amplitude);
}

void GameplayCamera::StopShaking(bool value)
{
	STOP_GAMEPLAY_CAM_SHAKING(value);
}

void GameplayCamera::ClampYaw(float min, float max)
{
	SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(min, max);
}

void GameplayCamera::ClampPitch(float min, float max)
{
	SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(min, max);
}

Vector3 GameplayCamera::ScreenToWorld(const Vector2& screenCoord)
{
	// Credit to Guadmaz
	const Vector3& camRot = GameplayCamera::Rotation_get();
	const Vector3& camPos = GameplayCamera::Position_get();

	Vector2 vector2;
	Vector2 vector21;
	Vector3 direction = Vector3::RotationToDirection(camRot);
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

GTAentity GameplayCamera::RaycastForEntity(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance)
{
	// Credit to Guadmaz
	const Vector3& world = ScreenToWorld(screenCoord);
	const Vector3& vector3 = GameplayCamera::Position_get();
	Vector3 vector31 = world - vector3;
	vector31.Normalize();
	RaycastResult raycastResult = RaycastResult::Raycast(vector3 + (vector31 * 1.f), vector3 + (vector31 * maxDistance), IntersectOptions(287), ignoreEntity);
	return raycastResult.DidHitEntity() ? raycastResult.HitEntity() : 0;
}

Vector3 GameplayCamera::RaycastForCoord(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance, float failDistance)
{
	// Credit to Guadmaz
	Vector3 position = GameplayCamera::Position_get();
	Vector3 world = ScreenToWorld(screenCoord);
	Vector3 vector3 = position;
	Vector3 vector31 = world - vector3;
	vector31.Normalize();
	RaycastResult raycastResult = RaycastResult::Raycast(vector3 + (vector31 * 1.f), vector3 + (vector31 * maxDistance), IntersectOptions(287), ignoreEntity);
	return raycastResult.DidHitAnything() ? raycastResult.HitCoords() : position + (vector31 * failDistance);
}

Vector3 GameplayCamera::DirectionFromScreenCentre_get()
{
	Vector3 position = GameplayCamera::Position_get();
	Vector3 world = GameplayCamera::ScreenToWorld(Vector2(0.0f, 0.0f));
	return Vector3::Normalize(world - position);
}

bool GameplayCamera::WorldToScreenRel(const Vector3& worldCoords, Vector2& screenCoords)
{
	if (!GET_SCREEN_COORD_FROM_WORLD_COORD(worldCoords.x, worldCoords.y, worldCoords.z, &screenCoords.x, &screenCoords.y))
		return false;

	screenCoords.x = (screenCoords.x - 0.5f) * 2.0f;
	screenCoords.y = (screenCoords.y - 0.5f) * 2.0f;
	return true;
}


Vector3 get_coords_from_cam(float distance)
{
	Vector3 Rot = DegreeToRadian(GET_GAMEPLAY_CAM_ROT(2));
	Vector3 Coord = GET_GAMEPLAY_CAM_COORD();

	Rot.y = distance * cos(Rot.x);
	Coord.x = Coord.x + Rot.y * sin(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cos(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sin(Rot.x);

	return Coord;
}



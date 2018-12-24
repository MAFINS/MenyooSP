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

#include <vector>
#include <string>

class Vector3;
class Vector2;
class GTAentity;
class GTAped;

enum class CameraShake : int
{
	Hand = 0,
	SmallExplosion,
	MediumExplosion,
	LargeExplosion,
	Jolt,
	Vibrate,
	RoadVibration,
	Drunk,
	SkyDiving,
	FamilyDrugTrip,
	DeathFail
};

extern const std::vector<std::string> CameraShakeNames;

class Camera
{
public:
	Camera();
	Camera(int handle);

	friend bool operator == (const Camera& left, const Camera& right);
	friend bool operator != (const Camera& left, const Camera& right);
	Camera& operator = (const Camera& right);

	int& Handle();
	int GetHandle() const;

	void DepthOfFieldStrength_set(float value);

	float FieldOfView_get() const;
	void FieldOfView_set(float value);

	float FarClip_get() const;
	void FarClip_set(float value);
	float FarDepthOfField_get() const;
	void FarDepthOfField_set(float value);

	float NearClip_get() const;
	void NearClip_set(float value);
	void NearDepthOfField_set(float value);

	bool IsActive() const;
	void SetActive(bool value);

	bool IsInterpolating() const;

	bool IsShaking() const;

	void SetShake(bool status);

	void MotionBlurStrength_set(float value);

	Vector3 Position_get() const;
	void Position_set(Vector3 coord);
	void Position_set(float X, float Y, float Z);

	Vector3 Rotation_get(__int8 unk = 2) const;
	void Rotation_set(const Vector3& rot, __int8 unk = 2);
	void Rotation_set(float X, float Y, float Z, __int8 unk = 2);


	Vector3 Direction_get(__int8 unk = 2) const;
	void Direction_set(Vector3 dir, __int8 unk = 2);
	void Direction_set(float X, float Y, float Z, __int8 unk = 2);
	
	float Heading_get() const;
	void Heading_set(float value);


	Vector3 GetOffsetInWorldCoords(const Vector3& offset) const;
	Vector3 GetOffsetInWorldCoords(float X, float Y, float Z) const;
	Vector3 GetOffsetGivenWorldCoords(const Vector3& worldCoords) const;
	Vector3 GetOffsetGivenWorldCoords(float X, float Y, float Z) const;

	float ShakeAmplitude_get() const;
	void ShakeAmplitude_set(float value);

	CameraShake ShakeType_get() const;
	void ShakeType_set(CameraShake value);

	void AttachTo(GTAentity entity, Vector3 offset);
	void AttachTo(GTAped ped, int boneIndex, Vector3 offset);
	void Detach();

	void InterpTo(Camera to, int duration, bool easePosition, bool easeRotation);

	void PointAt(Vector3 target);
	void PointAt(GTAentity target);
	void PointAt(GTAentity target, Vector3 offset);
	void PointAt(GTAped target, int boneIndex);
	void PointAt(GTAped target, int boneIndex, Vector3 offset);
	void StopPointing();

	bool Exists() const;

	void Destroy();
	static void DestroyAllCameras();
	static void RenderScriptCams(bool render);


	Vector3 ScreenToWorld(const Vector2& screenCoord) const;

	GTAentity RaycastForEntity(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance = 100.0f) const;

	Vector3 RaycastForCoord(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance = 100.0f, float failDistance = 100.0f) const;

	Vector3 DirectionFromScreenCentre_get() const;


private:
	int mHandle;
	float mShakeAmplitude;
	CameraShake mShakeType;

	static bool WorldToScreenRel(const Vector3& worldCoords, Vector2& screenCoords);
};


Vector3 get_coords_from_cam(int camid, float distance);


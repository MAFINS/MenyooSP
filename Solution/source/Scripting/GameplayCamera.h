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

class Vector3;
class Vector2;
class GTAentity;

enum class CameraShake : int;

class GameplayCamera final
{
public:
	static float FieldOfView_get();
	static void FieldOfView_set(float value);

	static bool IsAimCamActive();
	static bool IsFirstPersonAimCamActive();
	static bool IsLookingBehind();
	static bool IsRendering();
	static bool IsShaking();
	static Vector3 Position_get();
	static Vector3 GetOffsetInWorldCoords(const Vector3& offset);
	static Vector3 GetOffsetInWorldCoords(float X, float Y, float Z);
	static Vector3 GetOffsetGivenWorldCoords(const Vector3& worldCoords);
	static Vector3 GetOffsetGivenWorldCoords(float X, float Y, float Z);
	static float RelativeHeading_get();
	static void RelativeHeading_set(float value);
	static float RelativePitch_get();
	static void RelativePitch_set(float value);
	static Vector3 Rotation_get();
	static Vector3 Direction_get();
	static float Zoom_get();
	static void ShakeAmplitude_set(float value);

	static void Shake(CameraShake shakeType, float amplitude);

	static void StopShaking(bool value);

	static void ClampYaw(float min, float max);

	static void ClampPitch(float min, float max);

	static Vector3 ScreenToWorld(const Vector2& screenCoord);

	static GTAentity RaycastForEntity(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance = 100.0f);

	static Vector3 RaycastForCoord(const Vector2& screenCoord, GTAentity ignoreEntity, float maxDistance = 100.0f, float failDistance = 100.0f);

	static Vector3 DirectionFromScreenCentre_get();

private:

	static bool WorldToScreenRel(const Vector3& worldCoords, Vector2& screenCoords);
};


Vector3 get_coords_from_cam(float distance);
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

#include "..\Util\GTAmath.h"
#include "GTAentity.h"

enum class IntersectOptions : int
{
	Everything = -1,
	Map = 1,
	Mission_Entities = 2,
	Peds1 = 12,//4 and 8 both seem to be peds
	Objects = 16,
	Unk1 = 32,
	Unk2 = 64,
	Unk3 = 128,
	Vegetation = 256,
	Unk4 = 512
};

class RaycastResult
{
public:
	RaycastResult();
	RaycastResult(const RaycastResult& handle);
	RaycastResult(int handle);

	int Result();

	bool DidHitEntity();

	bool DidHitAnything();

	GTAentity HitEntity();

	Vector3 HitCoords();

	Vector3 SurfaceNormal();

	static RaycastResult Raycast(const Vector3& source, const Vector3& target, IntersectOptions options, GTAentity ignoreEntity = 0);
	static RaycastResult Raycast(const Vector3& source, const Vector3& direction, float maxDistance, IntersectOptions options, GTAentity ignoreEntity = 0);
	static RaycastResult RaycastCapsule(const Vector3& source, const Vector3& target, float radius, IntersectOptions options, GTAentity ignoreEntity = 0);
	static RaycastResult RaycastCapsule(const Vector3& source, const Vector3& direction, float maxDistance, float radius, IntersectOptions options, GTAentity ignoreEntity = 0);

private:
	int mResult;
	bool mDidHit;
	GTAentity mHitEntity;
	Vector3 mHitCoords;
	Vector3 mSurfaceNormal;
};



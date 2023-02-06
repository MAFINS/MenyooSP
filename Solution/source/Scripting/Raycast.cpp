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
#include "Raycast.h"

#include "..\macros.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "GTAentity.h"
//#include "GTAped.h"
//#include "GTAvehicle.h"

RaycastResult::RaycastResult()
	: mResult(0), mDidHit(false)
{
}

RaycastResult::RaycastResult(const RaycastResult& handle)
	: mResult(handle.mResult), mDidHit(handle.mDidHit), mHitEntity(handle.mHitEntity), mHitCoords(handle.mHitCoords), mSurfaceNormal(handle.mSurfaceNormal)
{
}

RaycastResult::RaycastResult(int handle)
{
	int hitsomething = 0;
	int enthandle = 0;
	Vector3_t hitCoords, surfaceNormal;

	this->mResult = GET_SHAPE_TEST_RESULT(handle, &hitsomething, &hitCoords, &surfaceNormal, &enthandle);

	this->mDidHit = hitsomething != 0;
	this->mHitCoords = hitCoords;
	this->mSurfaceNormal = surfaceNormal;

	if (DOES_ENTITY_EXIST(enthandle) && (IS_ENTITY_A_PED(enthandle) || IS_ENTITY_A_VEHICLE(enthandle) || IS_ENTITY_AN_OBJECT(enthandle)))
	{
		this->mHitEntity = enthandle;
	}
	else
	{
		this->mHitEntity = GTAentity();
		
	}
}


int RaycastResult::Result() const
{
	return this->mResult;
}
bool RaycastResult::DidHitEntity() const
{
	return mHitEntity.GetHandle() != 0;
}
bool RaycastResult::DidHitAnything() const
{
	return this->mDidHit;
}
GTAentity RaycastResult::HitEntity() const
{
	return this->mHitEntity;
}
Vector3 RaycastResult::HitCoords() const
{
	return this->mHitCoords;
}
Vector3 RaycastResult::SurfaceNormal() const
{
	return this->mSurfaceNormal;
}


RaycastResult RaycastResult::Raycast(const Vector3& source, const Vector3& target, IntersectOptions options, GTAentity ignoreEntity)
{
	return RaycastResult(START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(source.x, source.y, source.z, target.x, target.y, target.z, static_cast<int>(options), ignoreEntity.Handle(), 7));
}
RaycastResult RaycastResult::Raycast(const Vector3& source, const Vector3& direction, float maxDistance, IntersectOptions options, GTAentity ignoreEntity)
{
	const Vector3& target = source + (direction * maxDistance);
	return RaycastResult(START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(source.x, source.y, source.z, target.x, target.y, target.z, static_cast<int>(options), ignoreEntity.Handle(), 7));
}
RaycastResult RaycastResult::RaycastCapsule(const Vector3& source, const Vector3& target, float radius, IntersectOptions options, GTAentity ignoreEntity)
{
	return RaycastResult(START_SHAPE_TEST_CAPSULE(source.x, source.y, source.z, target.x, target.y, target.z, radius, static_cast<int>(options), ignoreEntity.Handle(), 7));
}
RaycastResult RaycastResult::RaycastCapsule(const Vector3& source, const Vector3& direction, float maxDistance, float radius, IntersectOptions options, GTAentity ignoreEntity)
{
	const Vector3& target = source + (direction * maxDistance);
	return RaycastResult(START_SHAPE_TEST_CAPSULE(source.x, source.y, source.z, target.x, target.y, target.z, radius, static_cast<int>(options), ignoreEntity.Handle(), 7));
}



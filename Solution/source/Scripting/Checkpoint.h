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

typedef unsigned char BYTE;
typedef unsigned __int64 UINT64;

class Vector3;
class RGBA;

enum class CheckpointIcon : int
{
	CylinderSingleArrow,
	CylinderDoubleArrow,
	CylinderTripleArrow,
	CylinderCycleArrow,
	CylinderCheckerboard,
	CylinderSingleArrow2,
	CylinderDoubleArrow2,
	CylinderTripleArrow2,
	CylinderCycleArrow2,
	CylinderCheckerboard2,
	RingSingleArrow,
	RingDoubleArrow,
	RingTripleArrow,
	RingCycleArrow,
	RingCheckerboard,
	SingleArrow,
	DoubleArrow,
	TripleArrow,
	CycleArrow,
	Checkerboard,
	CylinderSingleArrow3,
	CylinderDoubleArrow3,
	CylinderTripleArrow3,
	CylinderCycleArrow3,
	CylinderCheckerboard3,
	CylinderSingleArrow4,
	CylinderDoubleArrow4,
	CylinderTripleArrow4,
	CylinderCycleArrow4,
	CylinderCheckerboard4,
	CylinderSingleArrow5,
	CylinderDoubleArrow5,
	CylinderTripleArrow5,
	CylinderCycleArrow5,
	CylinderCheckerboard5,
	RingPlaneUp,
	RingPlaneLeft,
	RingPlaneRight,
	RingPlaneDown,
	Empty,
	Ring,
	Empty2,
	//CylinderCustomShape,
	//CylinderCustomShape2,
	//CylinderCustomShape3,
	Cyclinder = 45,
	Cyclinder2,
	Cyclinder3,
};

class Checkpoint
{
public:
	Checkpoint(int handle);
	Checkpoint();

	UINT64 MemoryAddress() const;

	Vector3 Position_get() const;
	void Position_set(const Vector3& value);

	Vector3 TargetPosition_get() const;
	void TargetPosition_set(const Vector3& value);

	CheckpointIcon Icon_get() const;
	void Icon_set(const CheckpointIcon& value);

	BYTE Reserved_get() const;
	void Reserved_set(BYTE value);

	float Radius_get() const;
	void Radius_set(float value);

	RGBA Colour_get() const;
	void Colour_set(const RGBA& value);
	RGBA IconColour_get() const;
	void IconColour_set(const RGBA& value);

	float CylinderNearHeight_get() const;
	void CylinderNearHeight_set(float value);

	float CylinderFarHeight_get() const;
	void CylinderFarHeight_set(float value);

	float CylinderRadius_get() const;
	void CylinderRadius_set(float value);

	void Delete();
	bool Exists();

	bool Equals(const Checkpoint& obj);

	friend bool operator == (const Checkpoint& left, const Checkpoint& right);
	friend bool operator != (const Checkpoint& left, const Checkpoint& right);

private:
	int mHandle;
};


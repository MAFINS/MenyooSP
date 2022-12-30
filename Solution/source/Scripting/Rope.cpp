/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Rope.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "GTAentity.h"

Rope::Rope()
	: mHandle(0)
{
}
Rope::Rope(const Rope& obj)
	: mHandle(obj.mHandle)
{
}
Rope::Rope(int handle)
	: mHandle(handle)
{
}

int Rope::Handle()
{
	return this->mHandle;
}
void Rope::SetHandle(int handle)
{
	this->mHandle = handle;
}
bool Rope::Exists()
{
	return DOES_ROPE_EXIST(&this->mHandle) != 0;
}

float Rope::Length()
{
	return ROPE_GET_DISTANCE_BETWEEN_ENDS(this->mHandle);
}
void Rope::SetLength(float value)
{
	ROPE_FORCE_LENGTH(this->mHandle, value);
}
int Rope::VertexCount()
{
	return GET_ROPE_VERTEX_COUNT(this->mHandle);
}

void Rope::ActivatePhysics()
{
	ACTIVATE_PHYSICS(this->mHandle);
}
void Rope::ResetLength(bool reset)
{
	ROPE_RESET_LENGTH(this->mHandle, reset);
}
void Rope::AttachEntities(const GTAentity& entityOne, const GTAentity& entityTwo, float length)
{
	this->AttachEntities(entityOne, Vector3(), entityTwo, Vector3(), length);
}
void Rope::AttachEntities(GTAentity entityOne, const Vector3& offsetOne, GTAentity entityTwo, const Vector3& offsetTwo, float length)
{
	ATTACH_ENTITIES_TO_ROPE(this->mHandle, entityOne.Handle(), entityTwo.Handle(), offsetOne.x, offsetOne.y, offsetOne.z, offsetTwo.x, offsetTwo.y, offsetTwo.z, length, 0, 0, 0, 0);
}
void Rope::AttachEntity(GTAentity entity)
{
	this->AttachEntity(entity, Vector3());
}
void Rope::AttachEntity(GTAentity entity, Vector3 position)
{
	ATTACH_ROPE_TO_ENTITY(this->mHandle, entity.Handle(), position.x, position.y, position.z, 0);
}
void Rope::DetachEntity(GTAentity entity)
{
	DETACH_ROPE_FROM_ENTITY(this->mHandle, entity.Handle());
}
void Rope::PinVertex(int vertex, Vector3 position)
{
	PIN_ROPE_VERTEX(this->mHandle, vertex, position.x, position.y, position.z);
}
void Rope::UnpinVertex(int vertex)
{
	UNPIN_ROPE_VERTEX(this->mHandle, vertex);
}
Vector3 Rope::GetVertexCoord(int vertex)
{
	return GET_ROPE_VERTEX_COORD(this->mHandle, vertex);
}

void Rope::Delete()
{
	if (DOES_ROPE_EXIST(&this->mHandle))
		DELETE_ROPE(&this->mHandle);
}


bool Rope::AreTexturesLoaded()
{
	return ROPE_ARE_TEXTURES_LOADED() != 0;
}
void Rope::LoadTextures()
{
	ROPE_LOAD_TEXTURES();
}
void Rope::UnloadTextures()
{
	ROPE_UNLOAD_TEXTURES();
}

Rope Rope::AddRope(RopeType type, const Vector3& position, const Vector3& rotation, float length, float minLength, bool breakable)
{
	ROPE_LOAD_TEXTURES();
	auto rope = ADD_ROPE(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, length, static_cast<int>(type), length, minLength, 0.5f, false, false, true, 1.0f, breakable, 0);
	return rope;
}



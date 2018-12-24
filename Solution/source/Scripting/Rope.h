/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#pragma once

class Vector3;
class GTAentity;

enum class RopeType : int
{
	Normal = 4,
	Thin = 5,
};

class Rope
{
public:

	Rope();
	Rope(const Rope& obj);
	Rope(int handle);

	int Handle();
	void SetHandle(int handle);
	bool Exists();

	float Length();
	void SetLength(float value);

	int VertexCount();


	void ActivatePhysics();
	void ResetLength(bool reset);
	void AttachEntities(const GTAentity& entityOne, const GTAentity& entityTwo, float length);
	void AttachEntities(GTAentity entityOne, const Vector3& offsetOne, GTAentity entityTwo, const Vector3& offsetTwo, float length);
	void AttachEntity(GTAentity entity);
	void AttachEntity(GTAentity entity, Vector3 position);
	void DetachEntity(GTAentity entity);
	void PinVertex(int vertex, Vector3 position);
	void UnpinVertex(int vertex);
	Vector3 GetVertexCoord(int vertex);

	void Delete();

	static bool AreTexturesLoaded();
	static void LoadTextures();
	static void UnloadTextures();

	static Rope AddRope(RopeType type, const Vector3& position, const Vector3& rotation, float length, float minLength, bool breakable);

private:
	int mHandle;
};

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

#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAentity.h"

#include "SpoonerTaskSequence.h"

#include <string>
#include <vector>

typedef unsigned char UINT8;
typedef int INT, ScrHandle;

namespace sub::Spooner
{
	class SpoonerEntity
	{
	public:
		struct Animation_t { std::string dict, name; };
		struct Attachment_t { bool isAttached; int boneIndex; Vector3 offset, rotation; };

		GTAentity Handle;
		EntityType Type;
		std::string HashName;
		bool Dynamic;
		//bool Door;
		SpoonerEntity::Animation_t LastAnimation;
		SpoonerEntity::Attachment_t AttachmentArgs;
		UINT8 TextureVariation;
		bool IsStill;
		//Hash RelationshipHash;
		SpoonerTaskSequence TaskSequence;

		std::string TypeName();

		SpoonerEntity();
		//const SpoonerEntity& operator = (const SpoonerEntity& right)
		SpoonerEntity(const SpoonerEntity& right);

		friend bool operator == (const SpoonerEntity& left, const SpoonerEntity& right);
		friend bool operator != (const SpoonerEntity& left, const SpoonerEntity& right);
		friend bool operator == (const SpoonerEntity& left, const GTAentity& right);
		friend bool operator != (const SpoonerEntity& left, const GTAentity& right);
		
	};

	class SpoonerEntityWithInitHandle
	{
	public:
		SpoonerEntity e;
		ScrHandle initHandle;
		ScrHandle attachedToHandle;
	};
	

	extern SpoonerEntity SelectedEntity;
	extern std::vector<SpoonerEntity> SelectedSpoonGroup;
}




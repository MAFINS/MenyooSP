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

#include "GenericLoopedMode.h"

#include "..\Scripting\Rope.h"
#include "..\Scripting\GTAentity.h"

#include <vector>

typedef unsigned __int8 UINT8;
typedef unsigned long Hash;

class Vector3;
class GTAprop;

namespace _RopeGun_
{
	class EntitiesAndRope
	{
	public:
		Rope rope;
		GTAentity e1;
		GTAentity e2;
		float initialDistance;

		EntitiesAndRope();
		EntitiesAndRope(const Rope& ropeP, const GTAentity& e1P, const GTAentity& e2P, float initialDistanceP);
		EntitiesAndRope(const EntitiesAndRope& obj);

		EntitiesAndRope& operator = (const EntitiesAndRope& right);
	};

	class RopeGun final : public GenericLoopedMode
	{
	private:
		const Hash whash;
		UINT8 shootCount;
		GTAentity _thing1, _thing2;
		std::vector<EntitiesAndRope> allRopes;
	public:
		RopeGun();

		void TurnOn() override;
		void TurnOff() override;

		void Tick() override;
		void DoRopeGunTick();
		void DoRopeEntitiesTick();

		void CreateRopeFor2(GTAentity& entity1, GTAentity& entity2);
		GTAprop CreateAFake(const Vector3& pos);

		void PrintGunInstructions();
		void PrintShootCountHelpText();

	};


	extern RopeGun g_ropeGun;

	void ToggleOnOff();
}



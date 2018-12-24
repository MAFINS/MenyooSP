/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "RopeGun.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Scripting\enums.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\GTAplayer.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAprop.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\World.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\CustomHelpText.h"
#include "..\Scripting\WeaponIndivs.h"

#include "..\Menu\Routine.h"

//#include <string>
//#include <sstream>

namespace _RopeGun_
{
	EntitiesAndRope::EntitiesAndRope()
		: rope(0), e1(0), e2(0), initialDistance(0.0f)
	{
	}
	EntitiesAndRope::EntitiesAndRope(const Rope& ropeP, const GTAentity& e1P, const GTAentity& e2P, float initialDistanceP)
		: rope(ropeP), e1(e1P), e2(e2P), initialDistance(initialDistanceP)
	{
	}
	EntitiesAndRope::EntitiesAndRope(const EntitiesAndRope& obj)
		: rope(obj.rope), e1(obj.e1), e2(obj.e2), initialDistance(obj.initialDistance)
	{
		//this->operator=(obj);
	}

	EntitiesAndRope& EntitiesAndRope::operator = (const EntitiesAndRope& right)
	{
		this->rope = right.rope;
		this->e1 = right.e1;
		this->e2 = right.e2;
		this->initialDistance = right.initialDistance;
		return *this;
	}


	RopeGun::RopeGun()
		: whash(WEAPON_HEAVYPISTOL),
		shootCount(0Ui8)
	{
	}

	void RopeGun::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		shootCount = 0;
		PrintGunInstructions();
	}
	void RopeGun::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		for (auto& r : allRopes)
		{
			r.rope.Delete();
			if (r.e1.Model().hash == 0x04B8A489)
				r.e1.Delete();
			if (r.e2.Model().hash == 0x04B8A489)
				r.e2.Delete();
		}
		allRopes.clear();

	}

	void RopeGun::Tick()
	{
		if (bEnabled)
		{
			DoRopeGunTick();
			DoRopeEntitiesTick();
		}
	}
	void RopeGun::DoRopeGunTick()
	{
		GTAplayer player = PLAYER_ID();
		Vector3 aimedCoords;
		GTAentity aimedThing;
		bool bNoTarget = false;

		if (g_myWeap == whash) // if (player.GetWeapon() == whash)
		{
			if (player.IsFreeAiming() || player.IsTargetingAnything())
			{
				aimedThing = player.AimedEntity();
				if (aimedThing.Handle() == 0)
				{
					aimedThing = World::EntityFromAimCamRay();
					if (aimedThing.Handle() == 0)
					{
						bNoTarget = true;
						float maxDistForRay = 1000.0f;
						aimedCoords = GameplayCamera::RaycastForCoord(Vector2(0.0f, 0.0f), 0, maxDistForRay, maxDistForRay + 200.0f);
						if (GameplayCamera::Position_get().DistanceTo(aimedCoords) > maxDistForRay + 100.0f)
							return;
					}
				}

				PrintShootCountHelpText();

				if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK))
				{
					shootCount++;

					switch (shootCount)
					{
					case 1:
						if (bNoTarget)
							_thing1 = CreateAFake(aimedCoords);
						else
							_thing1 = aimedThing;
						break;
					case 2:
						if (bNoTarget)
							_thing2 = CreateAFake(aimedCoords);
						else
							_thing2 = aimedThing;
						if (_thing1 == _thing2)
						{
							shootCount = 1;
						}
						else
						{
							CreateRopeFor2(_thing1, _thing2);
							shootCount = 0;
						}
						break;
					default:
						shootCount = 0;
						break;

					}
				}

			}
		}
		else
		{
			_thing1 = 0;
			_thing2 = 0;
			shootCount = 0;
		}
	}
	void RopeGun::DoRopeEntitiesTick()
	{
		for (auto rit = allRopes.begin(); rit != allRopes.end();)
		{
			auto& r = *rit;
			if (!r.e1.Exists() || !r.e2.Exists())
			{
				r.rope.Delete();
				if (r.e1.Model().hash == 0x04B8A489) r.e1.Delete();
				if (r.e2.Model().hash == 0x04B8A489) r.e2.Delete();
				rit = allRopes.erase(rit);
				continue;
			}

			Vector3& pos1 = r.e1.Position_get();
			Vector3& pos2 = r.e2.Position_get();
			float dist = pos1.DistanceTo(pos2);

			if (dist > r.initialDistance - 0.2f)
			{
				Vector3& forceDir = Vector3::Normalize(pos2 - pos1);
				EntityType e1Type = (EntityType)r.e1.Type();
				EntityType e2Type = (EntityType)r.e2.Type();

				bool e1IsSurface = r.e1.Model().hash == 0x04B8A489;
				bool e2IsSurface = r.e2.Model().hash == 0x04B8A489;

				bool e1IsVehicleWithDriver = e1Type == EntityType::VEHICLE && !GTAvehicle(r.e1).IsSeatFree(VehicleSeat::SEAT_DRIVER);
				bool e1IsPed = e1Type == EntityType::PED;
				bool e1IsProp = e1Type == EntityType::PROP;

				bool e2IsVehicleWithDriver = e2Type == EntityType::VEHICLE && !GTAvehicle(r.e2).IsSeatFree(VehicleSeat::SEAT_DRIVER);
				bool e2IsPed = e2Type == EntityType::PED;
				bool e2IsProp = e2Type == EntityType::PROP;

				bool e1IsMyVehicle = r.e1.Handle() == g_myVeh;
				bool e2IsMyVehicle = r.e2.Handle() == g_myVeh;

				if (!e1IsSurface && !e2IsSurface)
				{
					if (!e1IsMyVehicle && (!(e1IsVehicleWithDriver && e2IsPed) || e1IsPed || e1IsProp))
					{
						r.e1.RequestControlOnce();
						r.e1.ApplyForce(forceDir, ForceType::MaxForceRot2);
					}
					if (!e2IsMyVehicle && (!(e2IsVehicleWithDriver && e1IsPed) || e2IsPed || e2IsProp))
					{
						r.e2.RequestControlOnce();
						r.e2.ApplyForce(-forceDir, ForceType::MaxForceRot2);
					}
				}
				else if (e2IsSurface)
				{
					r.e1.RequestControlOnce();
					r.e1.ApplyForce(forceDir * 3.0f, ForceType::MaxForceRot2);
				}
				else if (e1IsSurface)
				{
					r.e2.RequestControlOnce();
					r.e2.ApplyForce(-forceDir * 3.0f, ForceType::MaxForceRot2);
				}
			}
			++rit;
		}
	}

	void RopeGun::CreateRopeFor2(GTAentity& entity1, GTAentity& entity2)
	{
		if (entity1 == entity2)
			return;

		entity1.RequestControl(500);
		entity2.RequestControl(500);

		//if (!entity1.HasControl() || !entity2.HasControl()) return;

		//GTAentity myPed = PLAYER_PED_ID();
		//Vector3& myPos = myPed.Position_get();
		Vector3& pos1 = entity1.Position_get();
		Vector3& pos2 = entity2.Position_get();
		float dist = pos1.DistanceTo(pos2);

		Rope::LoadTextures();
		Rope& newRope = Rope::AddRope(RopeType::Normal, pos1, Vector3(0, 0, 5.0f), dist, 0.0f, true);
		newRope.ActivatePhysics();
		//newRope.PinVertex(0, pos1);
		//newRope.PinVertex(newRope.VertexCount() - 1, pos2);
		//SET_DISABLE_BREAKING(newRope.Handle(), true);
		newRope.AttachEntities(entity1, entity2, dist);

		allRopes.push_back(EntitiesAndRope(newRope, entity1, entity2, dist));
	}
	GTAprop RopeGun::CreateAFake(const Vector3& pos)
	{
		auto& fake = World::CreateProp(0x3A49EBD1, pos, Vector3(), false, false); // p_car_keys_01
		fake.FreezePosition(true);
		WAIT(20);
		//fake.MissionEntity_set(true);
		//fake.IsCollisionEnabled_set(false);
		fake.SetVisible(false);
		fake.FreezePosition(true);
		return fake;
	}

	void RopeGun::PrintGunInstructions()
	{
		Game::Print::PrintBottomLeft(oss_ << "Use the ~b~" << get_weapon_label(whash, true) << "~s~ for hax.");
		Game::Print::PrintBottomLeft("Two bullet hits on two different entities or surfaces (WHILE AIMING) create a rope.");
	}
	void RopeGun::PrintShootCountHelpText()
	{
		switch (shootCount)
		{
		case 1:
			Game::CustomHelpText::ShowTimedText("~c~(Aim and)~s~ shoot another entity or surface using ~INPUT_ATTACK~ and a rope shall be born!", 100);
			break;
		}
	}


	RopeGun g_ropeGun;

	void ToggleOnOff()
	{
		g_ropeGun.Toggle();
	}
}



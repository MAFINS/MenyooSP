/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MeteorShower.h"

#include "..\macros.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\World.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\GTAprop.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Raycast.h"
#include "..\Scripting\PTFX.h"

#include <Windows.h> // GetTickCount
#include <string>
#include <vector>

namespace _MeteorShower_
{
	const std::vector<std::string> MeteorShower::rockModelNames{ "prop_asteroid_01", "prop_test_boulder_01", "prop_test_boulder_02", "prop_test_boulder_03", "prop_test_boulder_04" };
	Game::Sound::GameSound MeteorShower::crateLandSound = { "FBI_05_SOUNDS", "Crate_Land" };

	MeteorShower::MeteorShower()
		: timer1(0),
		timer2(0)
	{
	}

	void MeteorShower::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		timer1 = 0;
		timer2 = 0;

		if (rockModels.empty())
		{
			for (auto& name : rockModelNames)
			{
				rockModels.push_back(GET_HASH_KEY(name));
			}
		}
		for (auto& model : rockModels)
		{
			model.Load();
		}

		World::ClearWeatherOverride();
		World::SetWeatherOverTime(WeatherType::Thunder, 3000);
	}
	void MeteorShower::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		timer1 = 0;
		timer2 = 0;

		for (auto& model : rockModels)
		{
			if (model.IsLoaded())
				model.Unload();
		}
		for (auto& r : rockArray)
		{
			r.NoLongerNeeded();
		}
		rockArray.clear();

		World::SetWeatherOverTime(WeatherType::ExtraSunny, 3000);
	}

	void MeteorShower::Tick()
	{
		if (bEnabled)
		{
			DoMeteorShowerTick();
		}
	}
	inline void MeteorShower::DoMeteorShowerTick()
	{
		GTAped myPed = PLAYER_PED_ID();
		if (!myPed.Exists())
			return;

		if (GetTickCount() > timer1)
		{
			const Vector3& myPos = myPed.Position_get();

			float radius = GET_RANDOM_FLOAT_IN_RANGE(22.0f, 78.0f);
			float angle = GET_RANDOM_INT_IN_RANGE(0, 360);

			Vector3 pos = myPos.PointOnCircle(radius, angle) + Vector3(0, 0, 65.0f);

			Model model = rockModels[rand() % (int)rockModels.size()];


			GTAprop rock = CREATE_OBJECT(model.hash, pos.x, pos.y, pos.z, 1, 1, 1);
			SET_NETWORK_ID_CAN_MIGRATE(rock.NetID(), true);
			rock.Heading_set(GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f));
			rock.FreezePosition(false);
			SET_ENTITY_LOD_DIST(rock.Handle(), 1000000);
			rock.MissionEntity_set(true);

			rock.ApplyForce(Vector3(35.0f, 0, -57.0f));

			rockArray.push_back(rock);

			timer1 = GetTickCount() + 840;
		}

		for (auto& r : rockArray)
		{
			//r.ApplyForce(Vector3::WorldDown() * 2);
			if (r.Speed_get() > 0.55f)
			{
				const Vector3& rPos = r.Position_get();
				const auto& rayToGround = RaycastResult::Raycast(rPos, Vector3::WorldDown(), 1.4f, IntersectOptions::Map, r);

				if (r.IsInWater())
				{
					switch (r.Model().hash)
					{
					case 0xDF9841D7: // prop_asteroid_01
						PTFX::trigger_ptfx_1("scr_oddjobtraffickingair", "scr_ojdg4_water_exp", r, Vector3(), Vector3(), 1.2f);
						break;
					default:
						PTFX::trigger_ptfx_1("scr_oddjobtraffickingair", "scr_ojdg4_water_exp", r, Vector3(), Vector3(), 0.8f);
						break;
					}
				}
				else if (!rayToGround.DidHitAnything())
				{
					r.ApplyForce(Vector3(0.2f, 0, -2.0f));
					switch (r.Model().hash)
					{
					case 0xDF9841D7: // prop_asteroid_01
						PTFX::trigger_ptfx_1("scr_agencyheistb", "scr_agency3b_heli_expl", r, Vector3(), Vector3(), 1.2f);
						break;
					default:
						PTFX::trigger_ptfx_1("scr_agencyheistb", "scr_agency3b_heli_expl", r, Vector3(), Vector3(), 0.8f);
						break;
					}
				}
				else
				{
					switch (r.Model().hash)
					{
					case 0xDF9841D7: // prop_asteroid_01
									 //PTFX::trigger_ptfx_1("scr_exile1", "scr_ex1_cargo_engine_burst", r, Vector3(), Vector3(), 1.34f);
						GRAPHICS::ADD_DECAL((int)DecalType::Bang_concrete_bang, rayToGround.HitCoords().x, rayToGround.HitCoords().y, rayToGround.HitCoords().z, 0, 0, -1, 0, 1, 0, 6.0f, 6.0f, 0.1f, 0.3f, 0.6f, 0.5f, -1.0f, 0, 0, 0);
						break;
					default:
						//PTFX::trigger_ptfx_1("scr_exile1", "scr_ex1_cargo_engine_burst", r, Vector3(), Vector3(), 0.7f);
						GRAPHICS::ADD_DECAL((int)DecalType::Bang_concrete_bang, rayToGround.HitCoords().x, rayToGround.HitCoords().y, rayToGround.HitCoords().z, 0, 0, -1, 0, 1, 0, 3.0f, 3.0f, 0.1f, 0.3f, 0.6f, 0.5f, -1.0f, 0, 0, 0);
						break;
					}
					World::AddExplosion(rayToGround.HitCoords(), EXPLOSION::DIR_GAS_CANISTER, 0.0f, 0.017f, true, false);
					crateLandSound.Play(r); // Spammin'
				}
			}
		}

		if (GetTickCount() > timer2)
		{
			for (auto& r : rockArray)
			{
				r.NoLongerNeeded();
			} rockArray.clear();

			timer2 = GetTickCount() + 10500;
		}

		/*for (auto& r : rockArray)
		{
		if (r.IsInAir())
		{
		PTFX::LoopedPTFX ffx("scr_oddjobtraffickingair", "scr_ojdg4_water_exp");
		if (!ffx.IsAssetLoaded()) ffx.LoadAsset();
		PTFX::LoopedPTFX::RemoveInRange(r.Position_get(), 1.0f);
		ffx.Start(r, r.Dim1().x * 2.4f);
		}
		else
		{
		PTFX::LoopedPTFX::RemoveInRange(r.Position_get(), 1.0f);
		}
		}*/


		/*for (auto& ped : _nearbyPeds)
		{
		for (auto& r : rockArray)
		{
		if (IS_ENTITY_TOUCHING_ENTITY(ped, r.Handle()))
		{
		PTFX::trigger_ptfx_1("scr_solomon3", "scr_trev4_747_blood_impact", ped, Vector3(), Vector3(), 1.0f);
		}
		}
		NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
		SET_PED_FLEE_ATTRIBUTES(ped, 1, 1);
		TASK_REACT_AND_FLEE_PED(ped, myPed.Handle());
		}*/


	}
	

	MeteorShower g_meteorShower;

	void ToggleOnOff()
	{
		g_meteorShower.Toggle();
	}

}



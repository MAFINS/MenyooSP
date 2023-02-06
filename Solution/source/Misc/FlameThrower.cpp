/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FlameThrower.h"

#include "..\macros.h"

#include "..\Scripting\GTAplayer.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\Model.h"

#include <vector>

namespace _FlameThrower_ // Why have I made this for 'players' when this is sp and folks on mp/fivem probably can't even see these?
{
	Hash _whash = WEAPON_FIREEXTINGUISHER; // WEAPON_STUNGUN
	struct FlameThrowerPlayerAndFx { GTAplayer player; int fxHandle1; }; // , fxHandle2; };
	std::vector<FlameThrowerPlayerAndFx> _flameThrowerPlayerandFxArray;
	/*Game::Sound::GameSound fireSound;

	void TurnOn()
	{
		Game::Sound::GameSound::Load("FARMHOUSE_FIRE");
		Game::Sound::GameSound::Load("FARMHOUSE_FIRE_BG");
		Game::Sound::GameSound::Load("SCRIPT\\FBI_05_Chemical_Factory_01");
		Game::Sound::GameSound::Load("SCRIPT\\Underwater");

		fireSound = Game::Sound::GameSound("CHINESE2_SOUNDS", "FarmhouseFire_Ignite");

	}*/

	bool IsPlayerAdded(GTAplayer player)
	{
		auto& fts = _flameThrowerPlayerandFxArray;
		for (auto& ft : fts)
		{
			if (ft.player.Handle() == player.Handle())
			{
				return true;
			}
		}
		return false;
	}
	void RemovePlayer(GTAplayer player)
	{
		auto& fts = _flameThrowerPlayerandFxArray;
		for (auto it = fts.begin(); it != fts.end();)
		{
			if (it->player.Handle() == player.Handle())
			{
				it = fts.erase(it);
			}
			else ++it;
		}
	}
	void AddPlayer(GTAplayer player)
	{
		auto& fts = _flameThrowerPlayerandFxArray;
		FlameThrowerPlayerAndFx ft;
		ft.player = player;
		ft.fxHandle1 = 0;
		//ft.fxHandle2 = 0;
		RemovePlayer(player);
		fts.push_back(ft);

		//fireSound.Destroy();
		//TurnOn();
	}

	void RemoveSelf()
	{
		RemovePlayer(PLAYER_ID());
	}
	void AddSelf()
	{
		AddPlayer(PLAYER_ID());
	}

	void Tick()
	{
		if (_flameThrowerPlayerandFxArray.empty())
			return;

		GTAplayer myPlayer = PLAYER_ID();
		GTAped playerPed;
		GTAentity wobject;
		Hash whash;
		float scale;
		int gunBone;

		std::string fxAsset1 = "core";
		std::string fxName1 = "ent_sht_flame";

		//PCHAR fxAsset2 = "core";
		//PCHAR fxName2 = "ent_sht_flame";

		//PCHAR fxAsset2 = "scr_martin1";
		//PCHAR fxName2 = "scr_sol1_fire_trail";

		scale = 2.0f;

		if (!HAS_NAMED_PTFX_ASSET_LOADED(fxAsset1.c_str()))
		{
			REQUEST_NAMED_PTFX_ASSET(fxAsset1.c_str());
		}
		/*if (!HAS_NAMED_PTFX_ASSET_LOADED(fxAsset2.c_str()))
		{
		REQUEST_NAMED_PTFX_ASSET(fxAsset2.c_str());
		}*/

		auto& fts = _flameThrowerPlayerandFxArray;
		for (auto it = fts.begin(); it != fts.end();)
		{
			auto& ft = *it;
			auto& player = ft.player;

			if (!player.IsActive())
			{
				it = fts.erase(it);//RemovePlayer(player);
				continue;
			}

			playerPed = player.GetPed();
			auto& fxHandle1 = ft.fxHandle1;
			//auto& fxHandle2 = ft.fxHandle2;

			whash = playerPed.Weapon_get();

			//if (!IS_PED_SHOOTING(ped.Handle()) || whash != _whash
			if ((!player.IsFreeAiming() && !player.IsTargetingAnything()) || whash != _whash)
			{
				if (DOES_PARTICLE_FX_LOOPED_EXIST(fxHandle1))
					REMOVE_PARTICLE_FX(fxHandle1, false);
				//if (DOES_PARTICLE_FX_LOOPED_EXIST(fxHandle2))
				//REMOVE_PARTICLE_FX(fxHandle2, false);
				++it;
				continue;
				//fireSound.Stop();
			}

			if (player == myPlayer)
			{
				if (!IS_DISABLED_CONTROL_PRESSED(0, INPUT_ATTACK))
				{
					++it;
					continue;
				}
			}

			wobject = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed.Handle(), 0);
			Model wmodel = wobject.Model();
			gunBone = GET_ENTITY_BONE_INDEX_BY_NAME(wobject.Handle(), "Gun_Nuzzle");
			//ModelDimensions& wdim = wmodel.Dimensions();

			wobject.RequestControlOnce();

			if (!DOES_PARTICLE_FX_LOOPED_EXIST(fxHandle1))
			{
				USE_PARTICLE_FX_ASSET(fxAsset1.c_str());
				fxHandle1 = START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(fxName1.c_str(), wobject.Handle(), 0.0f, 0.0f, 0.04f, 89.5f, 0.0f, 90.0f, gunBone, scale, 0, 0, 0);
			}
			/*if (!DOES_PARTICLE_FX_LOOPED_EXIST(fxHandle2.c_str()))
			{
			USE_PARTICLE_FX_ASSET(fxAsset2.c_str());
			fxHandle2 = START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(fxName2.c_str(), wobject.Handle(), 0.0f, 2.33f, 0.04f, 89.5f, 0.0f, 90.0f, gunBone, scale, 0, 0, 0);
			}*/

			SET_PARTICLE_FX_LOOPED_EVOLUTION(fxHandle1, "flow", 1.0f, 0);
			SET_PARTICLE_FX_LOOPED_EVOLUTION(fxHandle1, "damage", 1.0f, 0);

			//fireSound.Play(wobject);

			++it;
		}


	}

}




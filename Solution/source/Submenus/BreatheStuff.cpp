/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "BreatheStuff.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\PTFX.h"
#include "..\Util\keyboard.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\Game.h"

#include <string>
#include <vector>
#include <utility>

namespace sub
{
	namespace BreatheStuff_catind
	{
		const std::vector<std::pair<std::string, BreathePtfxType>> vCaptions_breatheStuffs
		{
			{ "None", BreathePtfxType::None },
			{ "Bloody Puke", BreathePtfxType::Blood },
			{ "Fire", BreathePtfxType::Fire }
		};
		PTFX::LoopedPTFX _globalBreatheStuff_ptfx;
		BreathePtfxType loop_player_breatheStuff = BreathePtfxType::None;

		void set_self_breathe_ptfx(const BreathePtfxType& type)
		{
			PTFX::LoopedPTFX& ptfx = _globalBreatheStuff_ptfx;

			if (Menu::bit_controller ? !IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LS) : !IsKeyDown(VirtualKey::J))
			{
				if (ptfx.Exists())
					ptfx.Remove();
				return;
			}

			GTAped playerPed = PLAYER_PED_ID();
			float scale, X = 0.0f, Y = 0.0f, Z = 0.0f, aX = 0.0f, aY = 0.0f, aZ = 0.0f;

			switch (type)
			{
			case BreathePtfxType::Blood:
				ptfx.SetFxData({ "scr_solomon3", "scr_trev4_747_blood_impact" });
				scale = 0.16f;
				aX = -90.0f;
				aZ = -110.0f;
				break;
			case BreathePtfxType::Fire:default:
				ptfx.SetFxData({ "core", "ent_sht_flame" });
				scale = 1.0f;
				break;

			}

			if (!ptfx.IsAssetLoaded())
				ptfx.LoadAsset();

			if (playerPed.IsHuman())
			{
				X += -0.02;
				Y += 0.2;
				Z += 0.0;
				aX += 90.0;
				aY += 100.0;
				aZ += 90.0;
			}
			else
			{
				switch (playerPed.Model().hash)
				{
				default:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Chop:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Cow:
					X += 0.3;
					Y += 0.0;
					Z += -0.05;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Boar:
					X += 0.3;
					Y += 0.0;
					Z += -0.05;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Pig:
					X += 0.3;
					Y += 0.0;
					Z += -0.05;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Chimp:
					X += 0.0;
					Y += 0.0;
					Z += 0.0;
					aX += 90.0;
					aY += 90.0;
					aZ += 90.0;
					break;
				case PedHash::Rhesus:
					X += 0.0;
					Y += 0.0;
					Z += 0.0;
					aX += 90.0;
					aY += 90.0;
					aZ += 90.0;
					break;
				case PedHash::Husky:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Milton:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Retriever:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Shepherd:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Coyote:
					X += 0.2;
					Y += 0.0;
					Z += 0.0;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Cat:
					X += 0.1;
					Y += -0.06;
					Z += 0.0;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Deer:
					X += 0.2;
					Y += 0.0;
					Z += 0.0;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Hen:
					X += 0.13;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Rat:
					X += 0.13;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::ChickenHawk:
					X += 0.13;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Pigeon:
					X += 0.13;
					Y += 0.0;
					Z += 0.00;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Crow:
					X += 0.13;
					Y += 0.0;
					Z += -0.03;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Seagull:
					X += 0.13;
					Y += 0.0;
					Z += -0.03;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Cormorant:
					X += 0.13;
					Y += 0.0;
					Z += -0.03;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Dolphin:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::HammerShark:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Fish:
					X += 0.26;
					Y += 0.0;
					Z += -0.06;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::TigerShark:
					X += 0.4;
					Y += 0.0;
					Z += -0.2;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::KillerWhale:
					X += 0.4;
					Y += 0.0;
					Z += -0.2;
					aX += 0.0;
					aY += 90.0;
					aZ += 0.0;
					break;
				case PedHash::Humpback:
					X += 1.1;
					Y += -1.0;
					Z += 0.0;
					aX += 0.0;
					aY += 0.0;
					aZ += 0.0;
					break;
				}
			}

			if (!ptfx.Exists())
			{
				ptfx.Start(playerPed, scale, Vector3(X, Y, Z), Vector3(aX, aY, aZ), RGBA::AllWhite(), Bone::Head);
			}

			if (GET_GAME_TIMER() >= Menu::delayedTimer)
				ptfx.SetColour(RgbS::Random());

			/*Vector3& pos = GET_PED_BONE_COORDS(PLAYER_PED_ID(), Bone::SKEL_Head, 0.3f, 0.0f, 0.0f);

			std::vector<Hash> hey;
			hey.push_back(GET_HASH_KEY("EXP_VFXTAG_TREV3_TRAILER"));
			hey.push_back(GET_HASH_KEY("EXP_VFXTAG_FBI4_TRUCK_DOORS"));
			hey.push_back(0xdf6446b8);

			_ADD_SPECFX_EXPLOSION(pos.x, pos.y, pos.z, GET_RANDOM_INT_IN_RANGE(0, 41), hey[GET_RANDOM_INT_IN_RANGE(0, (int)hey.size() - 1)], 0.0f, TRUE, FALSE, 0x3f800000);
			//_ADD_SPECFX_EXPLOSION(pos.x, pos.y, pos.z, EXPLOSION::GRENADE, 12, 1.0f, TRUE, TRUE, 0x3f800000);*/
		}


		void __AddOption(const std::string& text, const BreathePtfxType& type)
		{
			null = 0;
			AddTickol(text, type == loop_player_breatheStuff, null, null); if (null)
			{
				if (loop_player_breatheStuff == BreathePtfxType::None && type != BreathePtfxType::None)
					Game::Print::PrintBottomLeft(oss_ << "Hold " << "~b~" << (Menu::bit_controller ? "LS" : "J") << "~s~" << " to breathe out stuff!");

				if (_globalBreatheStuff_ptfx.Exists())
					_globalBreatheStuff_ptfx.Remove();

				loop_player_breatheStuff = type;
			}
		}

		void BreatheStuffSub_()
		{
			AddTitle("Breathe StufF");
			for (auto& bsfxn : vCaptions_breatheStuffs)
			{
				__AddOption(bsfxn.first, bsfxn.second);
			}
		}

	}

}



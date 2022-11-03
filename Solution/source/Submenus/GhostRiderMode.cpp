/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "GhostRiderMode.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
//#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Util\ExePath.h"
#include "..\Misc\GenericLoopedMode.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\PTFX.h"
#include "..\Scripting\Game.h"

#include "..\Submenus\PedComponentChanger.h"
#include "..\Submenus\VehicleSpawner.h"

namespace sub
{
	namespace GhostRiderMode_catind
	{
		class GhostRiderMode final : public GenericLoopedMode
		{
		private:
			const PCHAR freakOut_dict;// = "ANIM@MP_PLAYER_INTUPPERFREAKOUT";
			const PCHAR freakOut_name;// = "EXIT_FP";
			GTAped playerPed;
			GTAvehicle playerVehicle;
			//bool justEnteredVehicle = false;
			PTFX::sFxData fxData_purpSmoke;// = { "scr_rcbarry2", "scr_clown_appears" }; // "scr_clown_death"
										   //PTFX::sFxData fxData_petrolFire = { "scr_finale1", "scr_fin_fire_petrol_trev" };
										   //PTFX::sFxData fxData_drugTrainExp = { "scr_oddjobtraffickingair", "scr_drug_grd_train_exp" };
			PTFX::sFxData fxData_fireTrail;// = { "scr_martin1", "scr_sol1_fire_trail" };
										   //PTFX::LoopedPTFX fx_head = { "core", "ent_sht_flame" };
			PTFX::NonLoopedPTFX fx_head2;// = fxData_purpSmoke;
			PTFX::NonLoopedPTFX fx_hand_left;// = fxData_purpSmoke;
			PTFX::NonLoopedPTFX fx_hand_right;// = fxData_purpSmoke;
			PTFX::LoopedPTFX fx_car_wheel_frontleft;// = fxData_fireTrail;
			PTFX::LoopedPTFX fx_car_wheel_frontright;// = fxData_fireTrail;
			PTFX::LoopedPTFX fx_car_wheel_rearleft;// = fxData_fireTrail;
			PTFX::LoopedPTFX fx_car_wheel_rearright;// = fxData_fireTrail;
		public:
			float tyreScale;// = -2.00f;
			float headScale;// = 0.075f;//-1.1f;
			float handScale;// = 0.045f;//-0.75f;
			Vector3 tyreRot;// = { -91.06, 0, -90.0f };
			Vector3 headRot;// = { -90.0f, 0, -90.0f };
			Vector3 handRot;// = { -90.0f, 0, -90.0f };

			GhostRiderMode();

			void TurnOn() override;
			void TurnOff() override;

			void Tick() override;
			inline void DoGhostRiderModeTick();
		};

		GhostRiderMode::GhostRiderMode()
			: freakOut_dict("ANIM@MP_PLAYER_INTUPPERFREAKOUT"),
			freakOut_name("EXIT_FP"),
			fxData_purpSmoke("scr_rcbarry2", "scr_clown_appears"),
			fxData_fireTrail("scr_martin1", "scr_sol1_fire_trail"),
			fx_head2(fxData_purpSmoke),
			fx_hand_left(fxData_purpSmoke),
			fx_hand_right(fxData_purpSmoke),
			fx_car_wheel_frontleft(fxData_fireTrail),
			fx_car_wheel_frontright(fxData_fireTrail),
			fx_car_wheel_rearleft(fxData_fireTrail),
			fx_car_wheel_rearright(fxData_fireTrail),

			tyreScale(-2.00f),
			headScale(0.075f),
			handScale(0.045f),
			tyreRot(-91.06, 0, -90.0f),
			headRot(-90.0f, 0, -90.0f),
			handRot(-90.0f, 0, -90.0f)
		{
		}

		void GhostRiderMode::TurnOn()
		{
			GenericLoopedMode::TurnOn();

			Game::Print::PrintBottomLeft("~b~Ghost Rider Mode~s~: I was short on actual fire so purple's the next best thing.");

			playerPed = PLAYER_PED_ID();
			playerPed.Task().PlayAnimation(freakOut_dict, freakOut_name, 4.0f, -4.0f, 2000, 1, 0.2f, false);
		}
		void GhostRiderMode::TurnOff()
		{
			GenericLoopedMode::TurnOff();

			if (playerPed.Exists())
			{
				playerPed.SetFireProof(false);
			}
			if (playerVehicle.Exists())
			{
				playerVehicle.SetFireProof(false);
			}

			fx_car_wheel_frontleft.Remove();
			fx_car_wheel_frontright.Remove();
			fx_car_wheel_rearleft.Remove();
			fx_car_wheel_rearright.Remove();
		}

		void GhostRiderMode::Tick()
		{
			if (bEnabled)
			{
				DoGhostRiderModeTick();
			}
		}
		inline void GhostRiderMode::DoGhostRiderModeTick()
		{
			playerPed = PLAYER_PED_ID();

			if (playerPed.Exists())
			{
				playerPed.SetFireProof(true);

				//fx_head.EasyStart(playerPed, headScale, Vector3(), headRot, Bone::SKEL_Head);
				fx_head2.EasyStart(playerPed, headScale, Vector3(), headRot, RGBA(RGBA::AllWhite(), 186), Bone::IK_Head);
				fx_hand_left.EasyStart(playerPed, handScale, Vector3(), handRot, RGBA(RGBA::AllWhite(), 186), Bone::IK_L_Hand);
				fx_hand_right.EasyStart(playerPed, handScale, Vector3(), handRot, RGBA(RGBA::AllWhite(), 186), Bone::IK_R_Hand);

				if (playerPed.IsInVehicle())
				{
					playerVehicle = playerPed.CurrentVehicle();
					auto& playerVehicleModel = playerVehicle.Model();
					playerVehicle.SetFireProof(true);

					if (playerVehicleModel.IsBicycle() || playerVehicleModel.IsBike())
					{
						fx_car_wheel_frontleft.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_lf));
						fx_car_wheel_frontright.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_lr));
					}
					else // isCar
					{
						fx_car_wheel_frontleft.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_lf));
						fx_car_wheel_frontright.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_rf));
						fx_car_wheel_rearleft.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_lr));
						fx_car_wheel_rearright.EasyStart(playerVehicle, tyreScale, Vector3(), tyreRot, RGBA::AllWhite(), playerVehicle.GetBoneIndex(VBone::wheel_rr));
					}
				}
				else
				{
					fx_car_wheel_frontleft.Remove();
					fx_car_wheel_frontright.Remove();
					fx_car_wheel_rearleft.Remove();
					fx_car_wheel_rearright.Remove();
				}

			}
		}

		GhostRiderMode g_ghostRiderMode;

		void ToggleOnOff()
		{
			g_ghostRiderMode.Toggle();
		}
		void Tick()
		{
			g_ghostRiderMode.Tick();
		}


		std::string outfitFileName = ("GhostRider");
		void ApplyGhostRiderOutfit()
		{
			sub::ComponentChanger_Outfit_catind::Apply(PLAYER_PED_ID(), GetPathffA(Pathff::Outfit, true) + outfitFileName, true, true, true, true, true, true);
		}
		void SpawnGhostRiderRide()
		{
			sub::VehicleSaver_catind::VehSaver_ReadFromFile(GetPathffA(Pathff::Vehicle, true) + outfitFileName, PLAYER_PED_ID());
		}


		void Sub_GhostRiderMode()
		{
			AddTitle("Ghost Rider Mode");

			AddLocal("Toggle", g_ghostRiderMode.Enabled(), ToggleOnOff, ToggleOnOff);
			AddOption("Apply Outfit (With Flames)", null, ApplyGhostRiderOutfit);
			AddOption("Spawn Ride (With Flames)", null, SpawnGhostRiderRide);
		}

	}

}





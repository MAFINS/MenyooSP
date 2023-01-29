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
			std::string freakOut_dict;// = "ANIM@MP_PLAYER_INTUPPERFREAKOUT";
			std::string freakOut_name;// = "EXIT_FP";
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

			////fx_head.Remove();
			//fx_head2.Remove();
			//fx_hand_left.Remove();
			//fx_hand_right.Remove();
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
					const auto& playerVehicleModel = playerVehicle.Model();
					playerVehicle.SetFireProof(true);

					//if (!justEnteredVehicle)
					//{
					//	justEnteredVehicle = true;
					//	Game::Sound::GameSound::LoadBank("TRAIN_HORN");
					//	Game::Sound::GameSound transformSound("TRAIN_HORN", "Warning_Once");
					//	transformSound.Play(playerVehicle);
					//	playerVehicle.PrimaryColour_set(COLOR_UTIL_BLACK);
					//	playerVehicle.DirtLevel_set(0.0f);
					//	SET_VEHICLE_ENVEFF_SCALE(playerVehicle.Handle(), 0.1f);
					//}

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
					//if (justEnteredVehicle)
					//{
					//	justEnteredVehicle = false;
					//}

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

			/*
			auto& tyreScale = g_ghostRiderMode.tyreScale;
			auto& headScale = g_ghostRiderMode.headScale;
			auto& handScale = g_ghostRiderMode.handScale;
			auto& tyreRot = g_ghostRiderMode.tyreRot;
			//auto& headPos = g_ghostRiderMode.headPos;
			auto& headRot = g_ghostRiderMode.headRot;
			auto& handRot = g_ghostRiderMode.handRot;

			bool tyre_x_plus = 0, tyre_x_minus = 0, tyre_y_plus = 0, tyre_y_minus = 0, tyre_z_plus = 0, tyre_z_minus = 0, tyre_scale_plus = 0, tyre_scale_minus = 0;
			AddBreak("Tyre Rot");
			AddNumber("Scale", tyreScale, 2, null, tyre_scale_plus, tyre_scale_minus); if (tyre_scale_plus) tyreScale += 0.01f; if (tyre_scale_minus) tyreScale -= 0.01f;
			AddNumber("X", tyreRot.x, 2, null, tyre_x_plus, tyre_x_minus); if (tyre_x_plus) tyreRot.x += 0.01f; if (tyre_x_minus) tyreRot.x -= 0.01f;
			AddNumber("Y", tyreRot.y, 2, null, tyre_y_plus, tyre_y_minus); if (tyre_y_plus) tyreRot.y += 0.01f; if (tyre_y_minus) tyreRot.y -= 0.01f;
			AddNumber("Z", tyreRot.z, 2, null, tyre_z_plus, tyre_z_minus); if (tyre_z_plus) tyreRot.z += 0.01f; if (tyre_z_minus) tyreRot.z -= 0.01f;

			bool head_x_plus = 0, head_x_minus = 0, head_y_plus = 0, head_y_minus = 0, head_z_plus = 0, head_z_minus = 0, head_scale_plus = 0, head_scale_minus = 0;
			AddBreak("Head Rot");
			AddNumber("Scale", headScale, 2, null, head_scale_plus, head_scale_minus); if (head_scale_plus) headScale += 0.01f; if (head_scale_minus) headScale -= 0.01f;
			AddNumber("X", headRot.x, 2, null, head_x_plus, head_x_minus); if (head_x_plus) headRot.x += 0.01f; if (head_x_minus) headRot.x -= 0.01f;
			AddNumber("Y", headRot.y, 2, null, head_y_plus, head_y_minus); if (head_y_plus) headRot.y += 0.01f; if (head_y_minus) headRot.y -= 0.01f;
			AddNumber("Z", headRot.z, 2, null, head_z_plus, head_z_minus); if (head_z_plus) headRot.z += 0.01f; if (head_z_minus) headRot.z -= 0.01f;

			//bool head_px_plus = 0, head_px_minus = 0, head_py_plus = 0, head_py_minus = 0, head_pz_plus = 0, head_pz_minus = 0;
			//AddBreak("Head Pos");
			//AddNumber("X", headPos.x, 2, null, head_px_plus, head_px_minus); if (head_px_plus) headPos.x += 0.01f; if (head_px_minus) headPos.x -= 0.01f;
			//AddNumber("Y", headPos.y, 2, null, head_py_plus, head_py_minus); if (head_py_plus) headPos.y += 0.01f; if (head_py_minus) headPos.y -= 0.01f;
			//AddNumber("Z", headPos.z, 2, null, head_pz_plus, head_pz_minus); if (head_pz_plus) headPos.z += 0.01f; if (head_pz_minus) headPos.z -= 0.01f;

			bool hand_x_plus = 0, hand_x_minus = 0, hand_y_plus = 0, hand_y_minus = 0, hand_z_plus = 0, hand_z_minus = 0, hand_scale_plus = 0, hand_scale_minus = 0;
			AddBreak("Hand Rot");
			AddNumber("Scale", handScale, 2, null, hand_scale_plus, hand_scale_minus); if (hand_scale_plus) handScale += 0.01f; if (hand_scale_minus) handScale -= 0.01f;
			AddNumber("X", handRot.x, 2, null, hand_x_plus, hand_x_minus); if (hand_x_plus) handRot.x += 0.01f; if (hand_x_minus) handRot.x -= 0.01f;
			AddNumber("Y", handRot.y, 2, null, hand_y_plus, hand_y_minus); if (hand_y_plus) handRot.y += 0.01f; if (hand_y_minus) handRot.y -= 0.01f;
			AddNumber("Z", handRot.z, 2, null, hand_z_plus, hand_z_minus); if (hand_z_plus) handRot.z += 0.01f; if (hand_z_minus) handRot.z -= 0.01f;
			*/

		}

	}

}





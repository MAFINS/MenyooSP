/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PtfxSubs.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"

#include "..\Submenus\WeaponOptions.h"

namespace sub
{
	namespace Ptfx_catind
	{
#pragma region ptfxvector
		const std::vector<PtfxS> vPTFX
		{
			{ "Starburst FW", "scr_indep_fireworks", "scr_indep_firework_starburst" },
			{ "Fountain FW", "scr_indep_fireworks", "scr_indep_firework_fountain" },
			{ "Shotburst FW", "scr_indep_fireworks", "scr_indep_firework_shotburst" },
			{ "Trailburst FW", "scr_indep_fireworks", "scr_indep_firework_trailburst" },
			{ "NYE FW", "proj_xmas_firework", "scr_firework_xmas_burst_rgw" },
			{ "Spiral FW", "proj_xmas_firework", "scr_firework_xmas_spiral_burst_rgw" },
			{ "Ring FW", "proj_xmas_firework", "scr_firework_xmas_ring_burst_rgw" },
			//{ "Flare Fuse", "core", "proj_flare_fuse" }, // Requires LOOPED_PTFX
			//{ "Flare", "scr_fbi5a", "scr_fbi5a_flare" },
			{ "Magical Flowers", "scr_rcbarry2", "scr_exp_clown" },
			//{ "Magical Stars", "scr_rcbarry2", "scr_clown_bull" },
			{ "Magical Smoke", "scr_rcbarry2", "scr_clown_appears" },
			{ "Magical Smoke 2", "scr_rcbarry2", "scr_clown_death" },
			{ "MoneySwap Smoke", "scr_tplaces", "scr_tplaces_team_swap" },
			{ "Firey Particles", "scr_rcbarry1", "scr_alien_teleport" },
			{ "Disintegration", "scr_rcbarry1", "scr_alien_disintegrate" },
			//{ "Charges", "scr_rcbarry1", "scr_alien_charging" },
			//{ "Beam", "scr_rcbarry1", "scr_alien_beam" },
			//{ "Impact", "scr_rcbarry1", "scr_alien_impact" },
			//{ "Door Heavy Stat", "scr_agencyheista", "scr_agency3a_door_hvy_stat" },
			//{ "Door Heavy Trigger", "scr_agencyheista", "scr_agency3a_door_hvy_trig" },
			//{ "Dry Ice", "scr_fbi5a", "scr_fbi5_dry_ice" },
			//{ "Blaze", "scr_agencyheist", "scr_fbi_ext_blaze" },
			{ "Mop Drips", "scr_agencyheist", "scr_fbi_mop_drips" },
			{ "Mop Squeeze", "scr_agencyheist", "scr_fbi_mop_squeeze" },
			//{ "Large Water Splash", "scr_exile3", "scr_ex3_water_dinghy_wash" },
			{ "Water Splash", "scr_fbi5a", "scr_fbi5_ped_water_splash" },
			//{ "Water Bubbles", "scr_fbi5a", "water_splash_ped_bubbles" },
			//{ "Puke", "scr_family5", "scr_trev_puke" },
			{ "Puke", "scr_familyscenem", "scr_trev_puke" },
			{ "Puke Ambient", "scr_familyscenem", "scr_trev_amb_puke" },
			//{ "Blood", "scr_finalec2", "scr_finale2_blood_entry" },
			//{ "Autopsy Blood", "scr_agencyheist", "scr_fbi_autopsy_blood" },
			{ "Blood Stab", "scr_michael2", "scr_mich2_blood_stab" },
			{ "Blood Impact", "scr_solomon3", "scr_trev4_747_blood_impact" },
			{ "Blood Spasm", "scr_michael2", "scr_abattoir_ped_sliced" },
			{ "Tyre Spiked", "scr_bigscore", "scr_bigscore_tyre_spiked" },
			{ "Tyre Smoke", "scr_mp_creator", "scr_mp_plane_landing_tyre_smoke" },
			//{ "Landing Tyre Smoke", "scr_fm_intro_cut_dev", "scr_mp_plane_landing_tyre_smoke" },
			{ "Gold Ball Trail", "scr_minigamegolf", "scr_golf_ball_trail" },
			{ "Sniper Impact", "scr_martin1", "scr_sol1_sniper_impact" },
			{ "Dirt Throw", "core_snow", "cs_mich1_spade_dirt_throw" },
			{ "Camera", "scr_rcpaparazzo1", "scr_rcpap1_camera" },
			//{ "Fire Ring", "scr_ie_export", "scr_ie_export_fire_ring" },
			{ "Meth Pipe Smoke", "scr_familyscenem", "scr_meth_pipe_smoke" },
			{ "Pipefall Debris", "scr_reconstructionaccident", "scr_reconstruct_pipefall_debris" },
			{ "Pipe Impact", "scr_reconstructionaccident", "scr_reconstruct_pipe_impact" },
			//{ "Sparking Generator", "scr_reconstructionaccident", "scr_sparking_generator" },
			{ "Burial Dirt", "scr_reburials", "scr_burial_dirt" },
			{ "Wheel Burnout", "scr_recartheft", "scr_wheel_burnout" },
			//{ "Rescue Fire", "scr_recrash_rescue", "scr_recrash_rescue_fire" },
			{ "Bank Notes", "scr_paletoscore", "scr_paleto_banknotes" },
			//{ "Blow Torch", "scr_paletoscore", "cs_paleto_blowtorch" },
			//{ "Trailer Splash", "scr_tevor1", "scr_trev1_trailer_splash" },
			//{ "Trailer Wires", "scr_tevor1", "scr_trev1_trailer_wires" },
			//{ "Crash Dust", "scr_tevor1", "scr_trev1_crash_dust" },
			//{ "Wheelspin Dirt", "scr_tevor1", "scr_trev1_wheelspin_dirt" },
			//{ "Train Sparks", "scr_oddjobtowtruck", "scr_ojtt_train_sparks" },
			//{ "Hotbox Trail", "scr_oddjobtaxi", "scr_ojtaxi_hotbox_trail" },
			{ "Engine Debris", "scr_solomon3", "scr_trev4_747_engine_debris" },
			{ "Car Impact", "scr_exile2", "scr_ex2_car_impact" },
			{ "Helicopter Explosion", "scr_agencyheistb", "scr_agency3b_heli_expl" },
			{ "Explosion Light", "scr_josh3", "scr_josh3_light_explosion" },
			{ "Building Story Explosion", "scr_agencyheist", "scr_fbi_exp_building" },
			{ "Drug Plane Explosion", "scr_oddjobtraffickingair", "scr_drug_grd_plane_exp" },
			{ "Drug Train Explosion", "scr_oddjobtraffickingair", "scr_drug_grd_train_exp" },
			{ "Water Explosion", "scr_oddjobtraffickingair", "scr_ojdg4_water_exp" },
			{ "Boat Explosion", "scr_oddjobtraffickingair", "scr_ojdg4_boat_exp" },
			//{ "Moving Cloud", "scr_exile1", "scr_ex1_moving_cloud" },
			//{ "Jeep Engine Fire", "scr_exile2", "scr_ex2_jeep_engine_fire" },
			//{ "Cargo Engine Trail", "scr_exile1", "scr_ex1_cargo_engine_trail" },
			{ "Cargo Engine Burst", "scr_exile1", "scr_ex1_cargo_engine_burst" },
			//{ "Cargo Smoke", "scr_exile1", "scr_ex1_cargo_smoke" },
			//{ "Cargo Fire", "scr_exile1", "cs_ex1_cargo_fire" },
			//{ "Cargo Debris", "scr_exile1", "scr_ex1_cargo_debris" },
			{ "Plane Explosion", "scr_exile1", "scr_ex1_plane_exp" },
			{ "Dust Impact", "scr_exile1", "scr_ex1_dust_impact" },
			{ "Car Impact Dust", "scr_finale1", "scr_fin_trev_car_impact" },
			//{ "Dust Settle", "scr_exile1", "scr_ex1_dust_settle" },
			//{ "Sparking Wires", "scr_exile1", "cs_ex1_sparking_wires_sm" },
			{ "Bike Burnout", "scr_jewelheist", "scr_jew_bike_burnout" },
			{ "Cab Smash", "scr_jewelheist", "scr_jewel_cab_smash" },
			{ "Wheel Burnout", "scr_carsteal4", "scr_carsteal4_wheel_burnout" },
			{ "Muzzle Flash", "scr_carsteal4", "scr_carsteal5_car_muzzle_flash" },
			{ "Flame", "core", "ent_sht_flame" },
			//{ "Fire Trail", "scr_martin1", "scr_sol1_fire_trail" },
			//{ "Falling Debris", "scr_agencyheist", "scr_fbi_falling_debris" },
			//{ "Building Smoke", "scr_agencyheistb", "scr_agency3b_blding_smoke" },
			{ "Breach Smoke", "scr_agencyheist", "scr_fbi_dd_breach_smoke" },
			{ "Electric Box Smoke", "scr_agencyheistb", "scr_agency3b_elec_box" },
			//{ "Shot Chopper", "scr_agencyheistb", "scr_agency3b_shot_chopper" },
			//{ "Wood Splinter", "scr_agencyheistb", "scr_agency3b_wood_splinter" },
			//{ "Rooftop Explosion", "scr_agencyheist", "scr_fbi_ext_rooftop" },
			{ "Explosion Fire Trail", "scr_agencyheistb", "scr_agency3b_heli_exp_trail" },
			//{ "RPG Trail", "scr_agencyheistb", "scr_agency3b_proj_rpg_trail" },
			//{ "Lighter Flame", "scr_mp_house", "scr_sh_lighter_flame" },
			{ "Petrol Fire", "scr_finale1", "scr_fin_fire_petrol_trev" },
			//{ "Petrol Fire 2", "ent_damage", "ent_sht_petrol_fire" },
			{ "Sparks", "scr_fbi4", "scr_fbi4_trucks_crash" },
			{ "Lighter Sparks", "scr_mp_house", "scr_sh_lighter_sparks" },
			{ "Blue Sparks", "scr_trevor1", "scr_trev1_trailer_boosh" },
			{ "Purplish Sparks", "scr_family4", "scr_fam4_trailer_sparks" },
			{ "Slipstream Formation", "scr_bike_adversary", "scr_adversary_slipstream_formation" },
			{ "Sodium Pour", "scr_bike_business", "scr_bike_meth_sodium_pour" },
			{ "Propylene Pour", "scr_bike_business", "scr_bike_meth_propylene_pour" },
			{ "Weed Smoke", "scr_bike_contraband", "scr_bike_truck_weed_smoke_cabin" },
			{ "", "","" },

		};
#pragma endregion

		std::vector<PtfxlopS> _fxlops;

		void AddEntityToPtfxLops(const PtfxS& effect, const GTAentity& entity)
		{
			for (auto it = _fxlops.begin(); it != _fxlops.end();)
			{
				if (it->entity.Equals(entity))
				{
					it = _fxlops.erase(it);
				}
				else ++it;
			}

			if (effect.fx.length() > 0)
			{
				PtfxlopS fxlop;
				fxlop.entity = entity;
				fxlop.asset = effect.asset;
				fxlop.fx = effect.fx;
				_fxlops.push_back(fxlop);
			}
		}

		void __AddOption_entity(const PtfxS& effect, GTAentity entity)
		{
			bool pressed = false;
			AddOption(effect.name, pressed); if (pressed)
			{
				PCHAR asset = (PCHAR)effect.asset.c_str();

				REQUEST_NAMED_PTFX_ASSET(asset);
				if (HAS_NAMED_PTFX_ASSET_LOADED(asset))
				{
					USE_PARTICLE_FX_ASSET(asset);
					SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1), GET_RANDOM_FLOAT_IN_RANGE(0, 1));
					if (GTAentity(entity).RequestControl())
					{
						START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY((PCHAR)effect.fx.c_str(), entity.GetHandle(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0);
					}
					else
					{
						Vector3& coord = GET_ENTITY_COORDS(entity.GetHandle(), 1);
						START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD((PCHAR)effect.fx.c_str(), coord.x, coord.y, coord.z, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0);
					}
				}
			}
		}
		void __AddOption_loopOnEntity(const PtfxS& effect, GTAentity entity)
		{
			bool found = false;
			bool tickolTrue = false;
			for (auto& fxlop : _fxlops)
			{
				if (fxlop.entity == entity)
				{
					found = true;
					if (fxlop.asset == effect.asset && fxlop.fx == effect.fx)
					{
						tickolTrue = true;
						break;
					}
				}
			}

			if (!found)
			{
				tickolTrue = !effect.asset.length() && !effect.fx.length();
			}

			bool pressed = false;
			AddTickol(effect.name, tickolTrue, pressed, pressed); if (pressed)
			{
				AddEntityToPtfxLops(effect, entity);
			}
		}

		void PTFXSub()
		{
			AddTitle("Special FX");

			//before the loop
			switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
			{
			case SUB::PLAYEROPS: case SUB::SPOONER_SELECTEDENTITYOPS:
				AddOption("Loop On Entity", null, nullFunc, SUB::PTFXSUB);
				break;
			case SUB::PTFXSUB:
			{
				bool bPressedClear = false;
				AddOption("Clear On All Entities", bPressedClear); if (bPressedClear)
					_fxlops.clear();
				PtfxS nonefx = { "None", "", "" };
				__AddOption_loopOnEntity(nonefx, local_ped_id);
				break; // subception
			}
			}


			for (const auto& current : vPTFX)
			{
				switch (Menu::currentsub_ar[Menu::currentsub_ar_index])
				{
				case SUB::PLAYEROPS: case SUB::SPOONER_SELECTEDENTITYOPS:
					__AddOption_entity(current, local_ped_id);
					break;
				case SUB::PTFXSUB:
					__AddOption_loopOnEntity(current, local_ped_id);
					break; // Subception
				case SUB::TRIGGERFXGUN:
					TriggerFxGun_catind::__AddOption_GunFx(current);
					break;
				}
			}

			//after the loop

		}

	}

}





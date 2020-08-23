/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Locations.h"

//#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

//#include "..\..\Natives\natives2.h"

#include "TeleLocation.h"

#include <string>
#include <vector>

namespace sub::TeleportLocations_catind
{
	namespace IplNames
	{
		const std::vector<std::string_view> vYacht_Smboat1
		{
			{ "smboat"_sv },
			{ "smboat_lod"_sv }
		};
		const std::vector<std::string_view> vYacht_Heist1
		{
			//{ "smboat_lod"_sv },
			{ "hei_yacht_heist"_sv },
			{ "hei_yacht_heist_enginrm"_sv },
			{ "hei_yacht_heist_Lounge"_sv },
			{ "hei_yacht_heist_Bridge"_sv },
			{ "hei_yacht_heist_Bar"_sv },
			{ "hei_yacht_heist_Bedrm"_sv },
			{ "hei_yacht_heist_DistantLights"_sv },
			{ "hei_yacht_heist_LODLights"_sv }
		};
		const std::vector<std::string_view> vYacht_Heist2
		{
			//{ "gr_grdlc_yacht_lod"_sv },
			//{ "gr_heist_yacht2_bar_lod"_sv },
			//{ "gr_heist_yacht2_bedrm_lod"_sv },
			//{ "gr_heist_yacht2_bridge_lod"_sv },
			//{ "gr_heist_yacht2_enginrm_lod"_sv },
			//{ "gr_heist_yacht2_lounge_lod"_sv },
			//{ "gr_grdlc_yacht_placement"_sv },
			{ "gr_heist_yacht2"_sv },
			{ "gr_heist_yacht2_bar"_sv },
			{ "gr_heist_yacht2_bedrm"_sv },
			{ "gr_heist_yacht2_bridge"_sv },
			{ "gr_heist_yacht2_enginrm"_sv },
			{ "gr_heist_yacht2_lounge"_sv },
			{ "gr_heist_yacht2_lod"_sv },
			{ "gr_heist_yacht2_slod"_sv }
		};
		const std::vector<std::string_view> vAircraftCarrier1
		{
			{ "hei_carrier"_sv },
			{ "hei_carrier_DistantLights"_sv },
			{ "hei_Carrier_int1"_sv },
			{ "hei_Carrier_int2"_sv },
			{ "hei_Carrier_int3"_sv },
			{ "hei_Carrier_int4"_sv },
			{ "hei_Carrier_int5"_sv },
			{ "hei_Carrier_int6"_sv },
			{ "hei_carrier_LODLights"_sv }
		};
		const std::vector<std::string_view> vNorthYankton
		{
			//{ "prologue_m2_door"_sv },
			//{ "prologue_m2_door_lod"_sv },
			//{ "prologue03_grv_cov"_sv },
			//{ "prologue03_grv_cov_lod"_sv },
			//{ "prologue03_grv_fun"_sv },
			{ "plg_01"_sv },
			{ "prologue01"_sv },
			{ "prologue01_lod"_sv },
			{ "prologue01c"_sv },
			{ "prologue01c_lod"_sv },
			{ "prologue01d"_sv },
			{ "prologue01d_lod"_sv },
			{ "prologue01e"_sv },
			{ "prologue01e_lod"_sv },
			{ "prologue01f"_sv },
			{ "prologue01f_lod"_sv },
			{ "prologue01g"_sv },
			{ "prologue01h"_sv },
			{ "prologue01h_lod"_sv },
			{ "prologue01i"_sv },
			{ "prologue01i_lod"_sv },
			{ "prologue01j"_sv },
			{ "prologue01j_lod"_sv },
			{ "prologue01k"_sv },
			{ "prologue01k_lod"_sv },
			{ "prologue01z"_sv },
			{ "prologue01z_lod"_sv },
			{ "plg_02"_sv },
			{ "prologue02"_sv },
			{ "prologue02_lod"_sv },
			{ "plg_03"_sv },
			{ "prologue03"_sv },
			{ "prologue03_lod"_sv },
			{ "prologue03b"_sv },
			{ "prologue03b_lod"_sv },
			{ "prologue03_grv_dug"_sv },
			{ "prologue03_grv_dug_lod"_sv },
			{ "prologue_grv_torch"_sv },
			{ "plg_04"_sv },
			{ "prologue04"_sv },
			{ "prologue04_lod"_sv },
			{ "prologue04b"_sv },
			{ "prologue04b_lod"_sv },
			{ "prologue04_cover"_sv },
			{ "des_protree_end"_sv },
			{ "des_protree_start"_sv },
			{ "des_protree_start_lod"_sv },
			{ "plg_05"_sv },
			{ "prologue05"_sv },
			{ "prologue05_lod"_sv },
			{ "prologue05b"_sv },
			{ "prologue05b_lod"_sv },
			{ "plg_06"_sv },
			{ "prologue06"_sv },
			{ "prologue06_lod"_sv },
			{ "prologue06b"_sv },
			{ "prologue06b_lod"_sv },
			{ "prologue06_int"_sv },
			{ "prologue06_int_lod"_sv },
			{ "prologue06_pannel"_sv },
			{ "prologue06_pannel_lod"_sv },
			{ "plg_occl_00"_sv },
			{ "prologue_occl"_sv },
			{ "plg_rd"_sv },
			{ "prologuerd"_sv },
			{ "prologuerdb"_sv },
			{ "prologuerd_lod"_sv }
		};
		const std::vector<std::string_view> vAllCustomisableApartments1
		{
			{ "apa_v_mp_h_01_a"_sv },
			{ "apa_v_mp_h_01_c"_sv },
			{ "apa_v_mp_h_01_b"_sv },
			{ "apa_v_mp_h_02_a"_sv },
			{ "apa_v_mp_h_02_c"_sv },
			{ "apa_v_mp_h_02_b"_sv },
			{ "apa_v_mp_h_03_a"_sv },
			{ "apa_v_mp_h_03_c"_sv },
			{ "apa_v_mp_h_03_b"_sv },
			{ "apa_v_mp_h_04_a"_sv },
			{ "apa_v_mp_h_04_c"_sv },
			{ "apa_v_mp_h_04_b"_sv },
			{ "apa_v_mp_h_05_a"_sv },
			{ "apa_v_mp_h_05_c"_sv },
			{ "apa_v_mp_h_05_b"_sv },
			{ "apa_v_mp_h_06_a"_sv },
			{ "apa_v_mp_h_06_c"_sv },
			{ "apa_v_mp_h_06_b"_sv },
			{ "apa_v_mp_h_07_a"_sv },
			{ "apa_v_mp_h_07_c"_sv },
			{ "apa_v_mp_h_07_b"_sv },
			{ "apa_v_mp_h_08_a"_sv },
			{ "apa_v_mp_h_08_c"_sv },
			{ "apa_v_mp_h_08_b"_sv }
		};
		const std::vector<std::string_view> vAllOffices1
		{
			{ "ex_dt1_02_office_01a"_sv },
			{ "ex_dt1_02_office_01b"_sv },
			{ "ex_dt1_02_office_01c"_sv },
			{ "ex_dt1_02_office_02a"_sv },
			{ "ex_dt1_02_office_02b"_sv },
			{ "ex_dt1_02_office_02c"_sv },
			{ "ex_dt1_02_office_03a"_sv },
			{ "ex_dt1_02_office_03b"_sv },
			{ "ex_dt1_02_office_03c"_sv },
			{ "ex_dt1_11_office_01a"_sv },
			{ "ex_dt1_11_office_01b"_sv },
			{ "ex_dt1_11_office_01c"_sv },
			{ "ex_dt1_11_office_02a"_sv },
			{ "ex_dt1_11_office_02b"_sv },
			{ "ex_dt1_11_office_02c"_sv },
			{ "ex_dt1_11_office_03a"_sv },
			{ "ex_dt1_11_office_03b"_sv },
			{ "ex_dt1_11_office_03c"_sv },
			{ "ex_sm_13_office_01a"_sv },
			{ "ex_sm_13_office_01b"_sv },
			{ "ex_sm_13_office_01c"_sv },
			{ "ex_sm_13_office_02a"_sv },
			{ "ex_sm_13_office_02b"_sv },
			{ "ex_sm_13_office_02c"_sv },
			{ "ex_sm_13_office_03a"_sv },
			{ "ex_sm_13_office_03b"_sv },
			{ "ex_sm_13_office_03c"_sv },
			{ "ex_sm_15_office_01a"_sv },
			{ "ex_sm_15_office_01b"_sv },
			{ "ex_sm_15_office_01c"_sv },
			{ "ex_sm_15_office_02a"_sv },
			{ "ex_sm_15_office_02b"_sv },
			{ "ex_sm_15_office_02c"_sv },
			{ "ex_sm_15_office_03a"_sv },
			{ "ex_sm_15_office_03b"_sv },
			{ "ex_sm_15_office_03c"_sv }
		};
		
		const std::vector<std::string_view> vAllOfficeGarages1
		{
			{ "imp_dt1_02_modgarage"_sv },
			{ "imp_dt1_02_cargarage_a"_sv },
			{ "imp_dt1_02_cargarage_b"_sv },
			{ "imp_dt1_02_cargarage_c"_sv },
			{ "imp_dt1_11_modgarage"_sv },
			{ "imp_dt1_11_cargarage_a"_sv },
			{ "imp_dt1_11_cargarage_b"_sv },
			{ "imp_dt1_11_cargarage_c"_sv },
			{ "imp_sm_13_modgarage"_sv },
			{ "imp_sm_13_cargarage_a"_sv },
			{ "imp_sm_13_cargarage_b"_sv },
			{ "imp_sm_13_cargarage_c"_sv },
			{ "imp_sm_15_modgarage"_sv },
			{ "imp_sm_15_cargarage_a"_sv },
			{ "imp_sm_15_cargarage_b"_sv },
			{ "imp_sm_15_cargarage_c"_sv }
		};
		

	}

	namespace Locations
	{

#pragma region safehouses
		const std::vector<TeleLocation> vSafeHouses
		{
			TeleLocation("Michael's House", -813.603f, 179.474f, 72.1548f),
			TeleLocation("Franklin's House (New)", 7.11903f, 536.615f, 176.028f,{ "v_franklinshouse"_sv, "unlocked"_sv },{ "locked"_sv}),
			TeleLocation("Franklin's House (Old)", -14.3803f, -1438.51f, 31.1073f),
			TeleLocation("Trevor's House", 1972.61f, 3817.04f, 33.4278f),
			TeleLocation("Trevor's House 2", -1151.77f, -1518.14f, 10.6327f),
			TeleLocation("Trevor's Office", 97.2707f, -1290.9940f, 29.2688f),
		};
#pragma endregion
#pragma region landmarks
		const std::vector<TeleLocation> vLandMarks
		{
			TeleLocation("Aircraft Carrier", 3084.7303f, -4770.709f, 15.2620f, IplNames::vAircraftCarrier1,{}, true),
			TeleLocation("Airport Entrance", -1034.6f, -2733.6f, 13.8f),
			TeleLocation("Airport Runway", -1336.0f, -3044.0f, 13.9f),
			TeleLocation("Altruist Cult Camp", -1170.841f, 4926.646f, 224.295f),
			TeleLocation("Calafia Train Bridge", -517.869f, 4425.284f, 89.795f),
			TeleLocation("Cargo Ship", 899.678f, -2882.191f, 19.013f),
			TeleLocation("Chumash Historic Family Pier", -3426.683f, 967.738f, 8.347f),
			TeleLocation("Del Perro Pier", -1850.127f, -1231.751f, 13.017f),
			TeleLocation("Devin Weston's House", -2639.872f, 1866.812f, 160.135f),
			TeleLocation("El Burro Heights", 1384.0f, -2057.1f, 52.0f),
			TeleLocation("Elysian Island", 338.2f, -2715.9f, 38.5f),
			TeleLocation("Far North San Andreas", 24.775f, 7644.102f, 19.055f),
			TeleLocation("Ferris Wheel", -1670.7f, -1125.0f, 13.0f),
			TeleLocation("Fort Zancudo (Opened)", -2047.4f, 3132.1f, 32.8f,{ "cs3_07_mpgates"_sv },{}),
			TeleLocation("Fort Zancudo Tower", -2358.132f, 3249.754f, 101.451f),
			TeleLocation("Jetsam", 760.4f, -2943.2f, 5.8f),
			TeleLocation("Jolene Cranley-Evans Ghost", 3059.620f, 5564.246f, 197.091f),
			TeleLocation("Kortz Center", -2243.810f, 264.048f, 174.615f),
			TeleLocation("Marlowe Vineyards", -1868.971f, 2095.674f, 139.115f),
			TeleLocation("McKenzie Airfield", 2121.7f, 4796.3f, 41.1f),
			TeleLocation("Merryweather Dock", 486.417f, -3339.692f, 6.070f),
			TeleLocation("Mineshaft", -595.342f, 2086.008f, 131.412f),
			TeleLocation("Mount Chiliad", 450.718f, 5566.614f, 806.183f),
			TeleLocation("Life Invader Building Roof", -1076.255f, -247.1436f, 57.9219f),
			TeleLocation("NOOSE Headquarters", 2535.243f, -383.799f, 92.993f),
			TeleLocation("Pacific Standard Bank", 235.046f, 216.434f, 106.287f),
			TeleLocation("Paleto Bay Pier", -275.522f, 6635.835f, 7.425f),
			TeleLocation("Playboy Mansion", -1475.234f, 167.088f, 55.841f),
			TeleLocation("Police Station", 436.491f, -982.172f, 30.699f),
			TeleLocation("Quarry", 2954.196f, 2783.410f, 41.004f),
			TeleLocation("Sandy Shores Airfield", 1747.0f, 3273.7f, 41.1f),
			TeleLocation("Satellite Dishes", 2062.123f, 2942.055f, 47.431f),
			TeleLocation("Sisyphus Theater Stage", 686.245f, 577.950f, 130.461f),
			TeleLocation("Meth Lab", 1391.773f, 3608.716f, 38.942f),
			TeleLocation("Weed Farm", 2208.777f, 5578.235f, 53.735f),
			TeleLocation("Wind Farm", 2354.0f, 1830.3f, 101.1f),
		};
#pragma endregion
#pragma region high locations
		const std::vector<TeleLocation> vHighLocations
		{
			TeleLocation("Crane Top", -119.879f, -977.357f, 304.249f),
			TeleLocation("FIB Building Roof", 150.126f, -754.591f, 262.865f),
			TeleLocation("Galileo Observatory Roof", -438.804f, 1076.097f, 352.411f),
			TeleLocation("IAA Building Roof", 134.085f, -637.859f, 262.851f),
			TeleLocation("Maze Bank Roof", -75.015f, -818.215f, 326.176f),
			TeleLocation("Palmer-Taylor Power Station Chimney", 2732.931f, 1577.540f, 83.671f),
			TeleLocation("Sandy Shores Building Site Crane", 1051.209f, 2280.452f, 89.727f),
			TeleLocation("Satellite Dish", 2034.988f, 2953.105f, 74.602f),
			TeleLocation("Sky High", -119.879f, -977.357f, 10000.0f),
			TeleLocation("UFO (Fort Zancudo)", -2052.000f, 3237.000f, 1456.973f,{ "ufo"_sv, "ufo_lod"_sv, "ufo_eye"_sv },{}),
			TeleLocation("Windmill Top", 2026.677f, 1842.684f, 133.313f),
		};
#pragma endregion
#pragma region underwater locations
		const std::vector<TeleLocation> vUnderwater
		{
			TeleLocation("Hatch", 4273.950f, 2975.714f, -170.746f),
			TeleLocation("Sea Monster", -3373.726f, 504.714f, -24.656f),
			TeleLocation("Sunken Body", -3161.078f, 3001.998f, -37.974f),
			TeleLocation("Sunken Cargo Ship", 3199.748f, -379.018f, -22.500f),
			TeleLocation("Sunken Plane", -942.350f, 6608.752f, -20.912f),
			TeleLocation("Tank", 4201.633f, 3643.821f, -39.016f),
			TeleLocation("Tunnel (Humane Labs)", 3838.47f, 3673.06f, -19.7281f,{},{ "chemgrill_grp1"_sv }),
			TeleLocation("UFO", 762.426f, 7380.371f, -111.377f),
		};
#pragma endregion
#pragma region online related locations
		const std::vector<TeleLocation> vOnlineRelated
		{
			TeleLocation("10 Car Garage", 229.3570f, -992.9106f, -98.9999f),
			//{ "10C Garage Wall", 220.5997f, -1006.7580f, -98.9999f },
			TeleLocation("2 Car Garage", 173.2904f, -1003.600f, -98.9999f, true),
			TeleLocation("6 Car Garage", 197.8153f, -1002.293f, -98.5503f, true),
			TeleLocation("Impound Lot", 391.4746f, -1637.9750f, 29.3153f),
			TeleLocation("LSPD Char Creator", 402.6675f, -1003.0000f, -99.0040f),
			TeleLocation("Mission Carpark", 405.9359f, -954.0912f, -99.0041f),
			TeleLocation("Mors Mutual Impound", -222.1977f, -1185.8500f, 23.0294f),
		};
#pragma endregion
#pragma region interiors
		const std::vector<TeleLocation> vInteriors
		{
			TeleLocation("Ammunation Gun Range", 22.153f, -1072.854f, 29.797f),
			TeleLocation("Bahama Mamas West", -1387.08f, -588.4f, 30.3195f,{ "sm_16_interior_v_bahama_milo_"_sv, "hei_sm_16_interior_v_bahama_milo_"_sv },{}, true, false, true),
			TeleLocation("Bank (Blaine County)", -109.299f, 6464.035f, 31.627f),
			TeleLocation("Bank (North Yankton)", 5309.519f, -5212.375f, 83.522f, IplNames::vNorthYankton,{}),
			TeleLocation("Bank Vault", 255.851f, 217.030f, 101.683f),
			TeleLocation("Car Showroom", -57.6615f, -1097.595f, 26.4224f,{ "shutter_open"_sv, "csr_inMission"_sv, "shr_int"_sv, "v_carshowroom"_sv },{ "shutter_closed"_sv, "fakeint"_sv }),
			TeleLocation("Cluckin' Bell Factory", -70.0624f, 6263.53f, 31.0909f,{ "CS1_02_cf_onmission1"_sv, "CS1_02_cf_onmission2"_sv, "CS1_02_cf_onmission3"_sv, "CS1_02_cf_onmission4"_sv },{ "CS1_02_cf_offmission"_sv }),
			TeleLocation("Darnell Bros. Garment Factory", 712.7159f, -962.9055f, 30.3953f,{ "id2_14_during1"_sv, "bnkheist_apt_norm"_sv, "bnkheist_apt_dest"_sv },{}), // both norm and dest?
			TeleLocation("East Los Santos Foundry", 1080.5678f, -1974.9805f, 31.4715f,{ "lr_id1_17_interior_v_foundry_milo_"_sv },{}, true, false, true),
			TeleLocation("Epsilon Storage Room", 243.3000f, 365.7000f, 105.7383f,{ "hei_hw1_01_interior_v_epsilonism_milo_"_sv },{}, true, false, true),
			TeleLocation("FIB Building Burnt", 159.553f, -738.851f, 246.152f),
			TeleLocation("FIB Building Floor 47", 134.573f, -766.486f, 234.152f),
			TeleLocation("FIB Building Floor 49", 134.635f, -765.831f, 242.152f),
			TeleLocation("FIB Building Lobby", 110.4f, -744.2f, 45.7f,{ "FIBlobby"_sv },{ "FIBlobbyfake"_sv }, false, false, true),
			TeleLocation("FIB Building Top Floor", 135.733f, -749.216f, 258.152f),
			TeleLocation("Garage (From Story Mode)", 195.1810f, -1024.9241f, -99.0000f),
			//{ "Hayes Autos", 478.5032f, -1316.4756f, 29.2040f, {}, {}, true ),
			TeleLocation("Hospital (Destroyed)", 302.651f, -586.293f, 43.3129f,{ "RC12B_Destroyed"_sv, "RC12B_HospitalInterior"_sv },{ "RC12B_Default"_sv, "RC12B_Fixed"_sv }),
			TeleLocation("Humane Labs Lower Level", 3525.495f, 3705.301f, 20.992f),
			TeleLocation("Humane Labs Upper Level", 3618.52f, 3755.76f, 28.6901f),
			TeleLocation("IAA Office", 117.220f, -620.938f, 206.047f),
			TeleLocation("Janitor's Apartment", -110.721f, -8.22095f, 70.5197f),
			TeleLocation("Jewel Store", -630.07f, -236.332f, 38.0571f,{ "post_hiest_unload"_sv },{ "jewel2fake"_sv, "bh1_16_refurb"_sv }),
			TeleLocation("Lester's House", 1273.898f, -1719.304f, 54.771f),
			TeleLocation("Life Invader Office", -1049.13f, -231.779f, 39.0144f,{ "LInvader"_sv, "facelobby"_sv },{ "facelobbyfake"_sv }),
			TeleLocation("Madrazo's Ranch", 1398.0800f, 1143.8001f, 114.3320f,{ "apa_ch2_03c_interior_v_ranch_milo_"_sv },{}, true, false, true),
			TeleLocation("Max Renda Shop", -583.1606f, -282.3967f, 35.394f,{ "refit_unload"_sv },{ "bh1_16_doors_shut"_sv }, false, false, true),
			TeleLocation("Meat Processing Factory", 976.1100f, -2184.4500f, 29.9779f,{ "lr_id1_10_interior_v_abattoir_milo_"_sv },{}, true, false, true),
			TeleLocation("Morgue", 275.446f, -1361.11f, 24.5378f,{ "coronertrash"_sv, "Coroner_Int_on"_sv },{ "coronertrash"_sv, "Coroner_Int_off"_sv }, false, false, true),
			TeleLocation("Motel Room", 152.2600f, -1004.4700f, -99.0000f),
			TeleLocation("Movie Theatre", -1427.3129f, -245.1729f, 16.8037f, false, false, true),
			TeleLocation("Omega's Garage", 2330.6196f, 2572.6108f, 46.6801f),
			TeleLocation("ONeil's Farm", 2454.78f, 4971.92f, 46.8103f,{ "farm"_sv, "farm_props"_sv, "farmint"_sv, "des_farmhs_start_occl"_sv, "des_farmhs_startimap"_sv },{ "farm_burnt"_sv, "farm_burnt_props"_sv, "farmint_cap"_sv, "des_farmhs_endimap"_sv, "des_farmhs_end_occl"_sv }),
			TeleLocation("ONeil's Farm (Burnt)", 2454.78f, 4971.92f, 46.8103f,{ "farm_burnt"_sv, "farm_burnt_props"_sv, "farmint"_sv, "des_farmhs_endimap"_sv, "des_farmhs_end_occl"_sv },{ "farmint_cap"_sv, "farm"_sv, "farm_props"_sv, "des_farmhs_start_occl"_sv, "des_farmhs_startimap"_sv }),
			TeleLocation("Psychiatrist's Office", -1908.0244f, -573.4244f, 19.0972f,{ "hei_sm_27_interior_v_psycheoffice_milo_"_sv },{}, false, false, true),
			TeleLocation("Solomon's Office", -1005.8400f, -478.9200f, 50.0284f,{ "hei_bh1_03_interior_v_58_sol_office_milo_"_sv },{}),
			TeleLocation("Split Sides Comedy Club", 377.0883f, -991.8690f, -98.6035,{ "apa_ss1_12_interior_v_comedy_milo_"_sv },{}),
			TeleLocation("Stadium", -248.4916f, -2010.509f, 34.5743f,{ "SP1_10_real_interior"_sv },{ "SP1_10_fake_interior"_sv }, false, false, true),
			TeleLocation("Strip Club, Behind Bar", 126.1211f, -1278.5130f, 29.2696f),
			TeleLocation("Tequi-la-la Bar", -556.1166f, 284.5194f, 82.1763f,{ "apa_ss1_11_interior_v_rockclub_milo_"_sv },{}),
			TeleLocation("Torture Room", 136.514f, -2203.15f, 7.30914f),
			TeleLocation("Trevor's Trailer (Clean)", 1975.5515f, 3820.5376f, 33.4363f,{ "TrevorsTrailerTidy"_sv },{ "TrevorsTrailerCollision"_sv, "TrevorsTrailer"_sv, "TrevorsMP"_sv }),
			TeleLocation("Trevor's Trailer (Dirty)", 1975.5515f, 3820.5376f, 33.4363f,{ "TrevorsTrailerCollision"_sv, "TrevorsTrailer"_sv, "TrevorsMP"_sv },{ "TrevorsTrailerTidy"_sv }),
			TeleLocation("Union Depository", 2.6968f, -667.0166f, 16.1306f,{ "FINBANK"_sv },{ "DT1_03_Shutter"_sv, "DT1_03_Gr_Closed"_sv }, false, false, true),
		};
#pragma endregion
#pragma region apartment interiors
		const std::vector<TeleLocation> vApartmentInteriors
		{
			TeleLocation(true, 260.5322f, -999.1339f, -99.0087f, "Low End Apartment"),
			TeleLocation(true, 343.8500f, -999.0800f, -99.1977f, "Mid Range Apartment"),
			TeleLocation(true, -262.46f, -951.89f, 75.83f, "3 Alta Street Apt 10"),
			TeleLocation(true, -280.74f, -961.50f, 91.11f, "3 Alta Street Apt 57"),
			TeleLocation(true, -895.85f, -433.90f, 94.06f, "Weazel Plaza Apt 26"),
			TeleLocation(true, -909.054f, -441.466f, 120.205f, "Weazel Plaza Apt 70"),
			TeleLocation(true, -884.301f, -454.515f, 125.132f, "Weazel Plaza Apt 101"),
			TeleLocation(true, -897.197f, -369.246f, 84.0779f, "Richard Majestic Apt 4"),
			TeleLocation(true, -932.29f, -385.88f, 108.03f, "Richard Majestic Apt 51"),
			TeleLocation(true, -575.305f, 42.3233f, 92.2236f, "Tinsel Towers Apt 29"),
			TeleLocation(true, -617.609f, 63.024f, 106.624f, "Tinsel Towers Apt 45"),
			TeleLocation(true, -795.04f, 342.37f, 206.22f, "Eclipse Towers Apt 5"),
			TeleLocation(true, -759.79f, 315.71f, 175.40f, "Eclipse Towers Apt 9"),
			TeleLocation(true, -797.095f, 335.069f, 158.599f, "Eclipse Towers Apt 31"),
			TeleLocation(true, -752.605f, 320.821f, 221.855f, "Eclipse Towers Apt 40"),
			TeleLocation(true, -37.41f, -582.82f, 88.71f, "4 Integrity Way Apt 30"),
			TeleLocation(true, -10.58f, -581.26f, 98.83f, "4 Integrity Way Apt 35"),
			TeleLocation(true, -1477.14f, -538.75f, 55.5264f, "Del Perro Heights Apt 7"),
			TeleLocation(true, -1474.17f, -528.124f, 68.1541f, "Del Perro Heights Apt 20"),
			TeleLocation(true, -14.7964f, -581.709f, 79.4307f, "4 Integrity Way Apt 28"),
			TeleLocation(true, -1468.14f, -541.815f, 73.4442f, "Del Perro Heights Apt 4"),
			TeleLocation(true, -915.811f, -379.432f, 113.675f, "Richard Majestic Apt 2"),
			TeleLocation(true, -614.86f, 40.6783f, 97.6001f, "Tinsel Towers Apt 42"),
			TeleLocation(true, -773.407f, 341.766f, 211.397f, "Eclipse Towers Apt 3"),
			TeleLocation(true, -172.983f, 494.033f, 137.654f, "3655 Wild Oats Drive"),
			TeleLocation(true, 340.941f, 437.18f, 149.39f, "2044 North Conker Avenue"),
			TeleLocation(true, 373.023f, 416.105f, 145.701f, "2045 North Conker Avenue"),
			TeleLocation(true, -676.127f, 588.612f, 145.17f, "2862 Hillcrest Avenue"),
			TeleLocation(true, -763.107f, 615.906f, 144.14f, "2868 Hillcrest Avenue"),
			TeleLocation(true, -857.798f, 682.563f, 152.653f, "2874 Hillcrest Avenue"),
			TeleLocation(true, 120.5f, 549.952f, 184.097f, "3677 Whispymound Drive"),
			TeleLocation(true, -1288.0f, 440.748f, 97.6946f, "2113 Mad Wayne Thunder"),
		};
#pragma endregion
#pragma region customisable apartment interiors
		const std::vector<TeleLocation> vCustomisableApartmentInteriors
		{
			TeleLocation("Modern 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_01_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Modern 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_01_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Modern 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_01_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Moody 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_02_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Moody 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_02_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Moody 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_02_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Vibrant 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_03_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Vibrant 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_03_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Vibrant 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_03_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Sharp 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_04_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Sharp 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_04_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Sharp 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_04_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Monochrome 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_05_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Monochrome 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_05_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Monochrome 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_05_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Seductive 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_06_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Seductive 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_06_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Seductive 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_06_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Regal 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_07_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Regal 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_07_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Regal 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_07_b"_sv }, IplNames::vAllCustomisableApartments1, true),

			TeleLocation("Aqua 1", -788.28f, 340.97f, 216.84f,{ "apa_v_mp_h_08_a"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Aqua 2", -786.73f, 342.81f, 187.11f,{ "apa_v_mp_h_08_c"_sv }, IplNames::vAllCustomisableApartments1, true),
			TeleLocation("Aqua 3", -773.425f, 332.380f, 196.086f,{ "apa_v_mp_h_08_b"_sv }, IplNames::vAllCustomisableApartments1, true),
		};
#pragma endregion
#pragma region shopping locations
		const std::vector<TeleLocation> vShopping
		{
			TeleLocation("Ammunation", 247.3652f, -45.8777f, 69.9411f),
			TeleLocation("Barber Shop", -1293.231f, -1117.002f, 6.6388f),
			TeleLocation("Benny's Motorworks", -205.3415f, -1305.809f, 30.6358f), // heading=180.1552f
			TeleLocation("LSC", -367.7338f, -130.8593f, 38.1165f), // heading=250.7382f
			TeleLocation("Ponsonbys Clothing", -159.2996f, -304.3292f, 39.7333f),
			TeleLocation("Tattoo Parlor", 319.7877f, 172.2311f, 103.7442f),
		};
#pragma endregion
#pragma region offices
		const std::vector<TeleLocation> vOffices_ArcadiusBusinessCentre
		{
			TeleLocation("Executive Rich", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_02b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Cool", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_02c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Contrast", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_02a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Warm", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_01a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Classical", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_01b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Vintage", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_01c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Ice", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_03a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Conservative", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_03b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Polished", -139.1000f, -631.8000f, 168.8000f,{ "ex_dt1_02_office_03c"_sv }, IplNames::vAllOffices1, true)
		};
		const std::vector<TeleLocation> vOffices_MazeBankBuilding
		{
			TeleLocation("Executive Rich", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_02b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Cool", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_02c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Contrast", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_02a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Warm", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_01a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Classical", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_01b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Vintage", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_01c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Ice", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_03a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Conservative", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_03b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Polished", -73.1000f, -816.8000f, 243.4000f,{ "ex_dt1_11_office_03c"_sv }, IplNames::vAllOffices1, true)
		};
		const std::vector<TeleLocation> vOffices_LombankWest
		{
			TeleLocation("Executive Rich", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_02b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Cool", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_02c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Contrast", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_02a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Warm", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_01a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Classical", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_01b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Vintage", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_01c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Ice", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_03a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Conservative", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_03b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Polished", -1573.1000f, -571.9000f, 108.5000f,{ "ex_sm_13_office_03c"_sv }, IplNames::vAllOffices1, true)
		};
		const std::vector<TeleLocation> vOffices_MazeBankWest
		{
			TeleLocation("Executive Rich", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_02b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Cool", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_02c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Executive Contrast", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_02a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Warm", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_01a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Classical", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_01b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Old Spice Vintage", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_01c"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Ice", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_03a"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Conservative", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_03b"_sv }, IplNames::vAllOffices1, true),
			TeleLocation("Power Broker Polished", -1382.3000f, -477.9000f, 72.0000f,{ "ex_sm_15_office_03c"_sv }, IplNames::vAllOffices1, true)
		};
		const std::vector<NamedTeleLocationList> vOffices
		{
			{ "Arcadius Business Centre", &vOffices_ArcadiusBusinessCentre, nullptr },
			{ "Maze Bank Building", &vOffices_MazeBankBuilding, nullptr },
			{ "Lombank West", &vOffices_LombankWest, nullptr },
			{ "Maze Bank West", &vOffices_MazeBankWest, nullptr },
		};
#pragma endregion
#pragma region biker interiors
		const std::vector<TeleLocation> vBikerInteriors
		{
			/*TeleLocation("Clubhouse 1", 1109.1124f, -3164.1536f, -37.5186f,{ "bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo_"_sv },{}, true, false, true),
			TeleLocation("Clubhouse 2", 998.3676f, -3164.6531f, -38.9073f,{ "bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo_"_sv },{}, true, false, true),
			TeleLocation("Business 1", 1009.5000f, -3196.6000f, -38.5000f,{ "bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo_"_sv },{}, true, false, true),
			TeleLocation("Business 2", 1049.6000f, -3196.6000f, -38.5000f,{ "bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo_"_sv },{},true, false, true),
			TeleLocation("Business 3", 1093.6000f, -3196.6000f, -38.5000f,{ "bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo_"_sv },{}, true, false, true),
			TeleLocation("Business 4", 1124.6000f, -3196.6000f, -38.5000f,{ "bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo_"_sv },{},true, false, true),
			TeleLocation("Business 5", 1165.0000f, -3196.6000f, -38.2000f,{ "bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo_"_sv },{}, true, false, true),*/
		};
#pragma endregion
#pragma region warehouses
		const std::vector<TeleLocation> vWarehouses
		{
			TeleLocation("Small", 1094.9880f, -3101.7760f, -40.0000f,{ "ex_exec_warehouse_placement_interior_1_int_warehouse_s_dlc_milo_"_sv },{}, true, false, true),
			TeleLocation("Medium", 1056.4860f, -3105.7240f, -40.0000f,{ "ex_exec_warehouse_placement_interior_0_int_warehouse_m_dlc_milo_"_sv },{}, true, false, true),
			TeleLocation("Large", 1007.1350f, -3102.0790f, -40.0000f,{ "ex_exec_warehouse_placement_interior_2_int_warehouse_l_dlc_milo_"_sv },{}, true, false, true),
		};
#pragma endregion
#pragma region others
		const std::vector<TeleLocation> vOthers
		{
			TeleLocation("Bridge (Train Crash Location)", -532.1309f, 4526.1870f, 88.7955f,{ "canyonriver01_traincrash"_sv, "railing_end"_sv },{ "canyonriver01"_sv, "railing_start"_sv }),
			TeleLocation("Cargo Ship (Normal)", -163.749f, -2377.94f, 9.3192f,{ "cargoship"_sv },{ "sunkcargoship"_sv, "SUNK_SHIP_FIRE"_sv }),
			TeleLocation("Cargo Ship (Sunken)", -162.8918f, -2365.769f, 0.0f,{ "sunkcargoship"_sv },{ "cargoship"_sv, "SUNK_SHIP_FIRE"_sv }),
			TeleLocation("Cargo Ship (Sunken & On Fire)", -162.8918f, -2365.769f, 0.0f,{ "sunkcargoship"_sv, "SUNK_SHIP_FIRE"_sv },{ "cargoship"_sv }),
			TeleLocation("North Yankton", 3217.697021f, -4834.826f, 111.8148f, IplNames::vNorthYankton,{}), // Angled roads and vehicle generators or nah?
			TeleLocation("Red Carpet (Movie Theatre)", 300.5927f, 199.7589f, 104.3776f,{ "redCarpet"_sv },{}, false, true),
			TeleLocation("Trench (Plane Crash Location)", 2814.7000f, 4758.5000f, 50.000f,{ "Plane_crash_trench"_sv },{}),
			TeleLocation("Tunnel Entrance (Maintenance)", 23.7318f, -647.2123, 37.9549f,{},{ "DT1_03_Gr_Closed"_sv }),
			TeleLocation("Wrecked Stilthouse (Vinewood)", -1020.5000f, 663.4099f, 154.7500f,{ "DES_StiltHouse_imapend"_sv },{ "DES_stilthouse_rebuild"_sv, "DES_StiltHouse_imapstart"_sv }),
		};
#pragma endregion

		const std::vector<NamedTeleLocationList> vAllCategories
		{
			//{ "Name", &LocationList, &NextLocationListVector|NextSubmenu
			{ "Shops", &vShopping, nullptr },
			{ "Safehouses", &vSafeHouses, nullptr },
			{ "Landmarks", &vLandMarks, nullptr },
			{ "High Altitude", &vHighLocations, nullptr },
			{ "Underwater", &vUnderwater, nullptr },
			{ "Online Related", &vOnlineRelated, nullptr },
			{ "Interiors", &vInteriors, nullptr },
			{ "Apartment Interiors", &vApartmentInteriors, nullptr },
			{ "Customisable Apartment Interiors", &vCustomisableApartmentInteriors, nullptr },
			{ "Office Interiors", nullptr, &vOffices },
			{ "Office Garages", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_OFFICEGARAGES },
			{ "Vehicle Warehouses", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_IEVEHICLEWAREHOUSES },
			//{ "Biker Interiors", &vBikerInteriors, nullptr },
			{ "Biker Clubhouses", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_BIKERCLUBHOUSES },
			{ "Biker Businesses", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_BUSINESSES },
			{ "Bunkers", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_BUNKERS },
			{ "MOCs (ALPHA)", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_MOC },
			{ "Company Warehouses", &vWarehouses, nullptr },
			{ "Hangars", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_HANGARS },
			{ "Heist Facilities", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_FACILITIES },
			{ "Nightclubs (ALPHA)", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_NIGHTCLUBS },
			{ "Arena War Locations (ALPHA)", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_ARENAWAR },
			{ "Yachts", nullptr, (const std::vector<NamedTeleLocationList>*)SUB::TELEPORTOPS_YACHTS },
			{ "Others", &vOthers, nullptr }
		};
	}

}




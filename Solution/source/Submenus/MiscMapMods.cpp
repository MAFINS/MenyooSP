/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MiscMapMods.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
//#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAprop.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\World.h"

#include "..\Submenus\Teleport\TeleMethods.h"

#include <string>
#include <vector>

namespace sub
{
	namespace MapMods_catind
	{
		class GTAmapmod
		{
		private:
			std::string name;
			Vector3 location;
			void(*loadptr)();
			std::vector<GTAentity> ohandles;
		public:
			GTAmapmod(const std::string& newName, Vector3 newLocation, void(&newLoad)())
				: name(newName), location(newLocation), loadptr(newLoad)
			{
			}
			void Tele()
			{
				teleport_net_ped(Game::PlayerPed(), location.x, location.y, location.z);
			}
			bool IsLoaded()
			{
				return !ohandles.empty();
			}
			void Load(bool showMsg = true)
			{
				mm_unloadAll();
				loadptr();
				if (showMsg)
					Game::Print::PrintBottomCentre(name + " ~b~loaded~s~.");
			}
			void Unload(bool showMsg = true)
			{
				for (auto& obj : ohandles)
				{
					obj.Delete(1);
				}
				ohandles.clear();

				if (showMsg)
					Game::Print::PrintBottomCentre(name + " ~p~unloaded~s~.");
			}
			std::vector<GTAentity>& Handles()
			{
				return ohandles;
			}
			void setHandles_pushback(GTAentity entity)
			{
				ohandles.push_back(entity);
			}
			const std::string& Name()
			{
				return name;
			}

		};

		GTAmapmod *currentMAPMODC;
		void HaxBy(const std::string& who)
		{
			Game::Print::PrintBottomLeft("Hax by ~b~" + who);
		}

		void mm_PlaceObject(Hash hash, float X, float Y, float Z, float pitch, float roll, float yaw, bool noLongerNeeded = false)
		{
			Model model(hash);
			GTAprop e = World::CreateProp(hash, Vector3(X, Y, Z), Vector3(pitch, roll, yaw), false, false);
			e.FreezePosition(true);
			SET_NETWORK_ID_CAN_MIGRATE(OBJ_TO_NET(e.Handle()), TRUE);
			e.LodDistance_set(1000000);
			e.MissionEntity_set(true);
			model.Unload();
			if (noLongerNeeded)
				SET_OBJECT_AS_NO_LONGER_NEEDED(&e.Handle());

			currentMAPMODC->setHandles_pushback(e.GetHandle());
		}

		void mmf_10cGarageTroll()
		{// No tym to change k.
			Object tempEntity = CREATE_OBJECT(-2124524821, 236.569f, -997.3225f, -98.9474f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 236.569f, -997.3225f, -98.9474f, 1, 0, 0, 1);
			SET_ENTITY_ROTATION(tempEntity, -0.0f, 0.0f, -87.0f, 2, 1);
			SET_ENTITY_HEADING(tempEntity, 237);
			SET_ENTITY_QUATERNION(tempEntity, 0.0f, 0.0f, -0.6884f, 0.7254f);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			tempEntity = CREATE_OBJECT(-28585071, 232.0699f, -1006.275f, -98.9999f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 232.0699f, -1006.275f, -98.9999f, 1, 0, 0, 1);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			tempEntity = CREATE_OBJECT(-28585071, 224.6781f, -1006.111f, -98.9999f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 224.6781f, -1006.111f, -98.9999f, 1, 0, 0, 1);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			tempEntity = CREATE_OBJECT(2118072208, 227.7707f, -993.9308f, -100.0116f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 227.7707f, -993.9308f, -100.0116f, 1, 0, 0, 1);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			tempEntity = CREATE_OBJECT(56956235, 231.5893f, -975.6108f, -100.0083f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 231.5893f, -975.6108f, -100.0083f, 1, 0, 0, 1);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			tempEntity = CREATE_OBJECT(1572208841, 236.4976f, -985.9178f, -100.0949f, 1, 1, 0);
			SET_ENTITY_COORDS(tempEntity, 236.4976f, -985.9178f, -100.0949f, 1, 0, 0, 1);
			SET_ENTITY_ROTATION(tempEntity, 0.0001f, 0.0001f, -179.0f, 2, 1);
			SET_ENTITY_HEADING(tempEntity, 181);
			SET_ENTITY_QUATERNION(tempEntity, 0.0f, 0.0f, 1.0f, -0.0087f);
			FREEZE_ENTITY_POSITION(tempEntity, 1);
			currentMAPMODC->setHandles_pushback(tempEntity);

			mm_PlaceObject(2124719729, 228.8643f, -979.0699f, -99.7999f, 38.2091f, 61.8766f, -84.0842f, false);
			mm_PlaceObject(2124719729, 230.0069f, -985.5955f, -99.00f, 38.2091f, 61.8766f, -84.0842f, false);
			mm_PlaceObject(2124719729, 224.8969f, -990.5674f, -99.00f, 38.2091f, 61.8766f, -84.0842f, false);
			// ADD ANOTHER ICON HERE FOR LIFT

			HaxBy("MAFINS");

		}
		void mmf_6cGarageTroll()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xbafbd223;
			X = 198.435;
			Y = -1007.52;
			Z = -99.9837;
			Pitch = 1.78814e-007;
			Roll = -2.08775e-006;
			Yaw = 179.153;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xe3ba450;
			X = 203.155;
			Y = -996.67;
			Z = -99.8329;
			Pitch = 0;
			Roll = 0;
			Yaw = 12.3472;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xe3ba450;
			X = 192.355;
			Y = -996.17;
			Z = -99.8329;
			Pitch = 0;
			Roll = 0;
			Yaw = 12.3472;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xa50dddd0;
			X = 206.302;
			Y = -999.104;
			Z = -98.9096;
			Pitch = 3.58516e-008;
			Roll = 1.11758e-007;
			Yaw = -87.0964;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0x13351f02;
			X = 197.584;
			Y = -997.428;
			Z = -100.024;
			Pitch = 0;
			Roll = -0;
			Yaw = -90.7766;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xc0d710bf;
			X = 205.617;
			Y = -996.548;
			Z = -100.012;
			Pitch = 0;
			Roll = -0;
			Yaw = -137.62;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0x922c2a43;
			X = 206.659;
			Y = -994.204;
			Z = -98.9349;
			Pitch = 4.59;
			Roll = -0.750039;
			Yaw = 136.812;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xf7fcf988;
			X = 193.069;
			Y = -1007.71;
			Z = -98.4741;
			Pitch = 0;
			Roll = 0;
			Yaw = -1.57148;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xf7fcf988;
			X = 200.369;
			Y = -1007.71;
			Z = -98.4741;
			Pitch = 0;
			Roll = 0;
			Yaw = -1.57148;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0x82bac591;
			X = 194.809;
			Y = -993.41;
			Z = -98.9314;
			Pitch = 89.8321;
			Roll = 1.04025;
			Yaw = -180;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xff78bcb;
			X = 193.465;
			Y = -1000.33;
			Z = -99.9813;
			Pitch = 0;
			Roll = -0;
			Yaw = -138.351;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xff78bcb;
			X = 201.266;
			Y = -1001.13;
			Z = -99.9813;
			Pitch = 0;
			Roll = -0;
			Yaw = 141.75;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0x9be9742e;
			X = 204.811;
			Y = -1003.86;
			Z = -99.9946;
			Pitch = 0;
			Roll = -0;
			Yaw = 165.008;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xcc179926;
			X = 198.31;
			Y = -1007.82;
			Z = -100.1;
			Pitch = 0;
			Roll = -0;
			Yaw = -179.767;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("R3ck17");
		}
		void mmf_2cGarageTroll()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xbafbd223;
			X = 172.818;
			Y = -1006.87;
			Z = -99.7836;
			Pitch = 79.7129;
			Roll = 5.01991e-005;
			Yaw = -174.868;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x2acf481a;
			X = 172.97;
			Y = -1000.37;
			Z = -100;
			Pitch = 0;
			Roll = 0;
			Yaw = 86.5597;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0x70ba7af2;
			X = 175.818;
			Y = -1001.37;
			Z = -99.9;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0x70ba7af2;
			X = 175.819;
			Y = -1003.47;
			Z = -99.9;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0x70ba7af2;
			X = 175.819;
			Y = -1002.37;
			Z = -98.5;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0x70ba7af2;
			X = 170.319;
			Y = -1000.97;
			Z = -100;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0x70ba7af2;
			X = 170.319;
			Y = -1005.77;
			Z = -100;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0x70ba7af2;
			X = 170.419;
			Y = -1003.37;
			Z = -100;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0x70ba7af2;
			X = 175.92;
			Y = -1005.58;
			Z = -100;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0x70ba7af2;
			X = 175.92;
			Y = -1004.58;
			Z = -98.5;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0x70ba7af2;
			X = 170.32;
			Y = -1002.18;
			Z = -98.5799;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0x70ba7af2;
			X = 170.329;
			Y = -1004.6;
			Z = -98.5799;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.194519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xb462ffae;
			X = 174.006;
			Y = -1000.12;
			Z = -99.9745;
			Pitch = 0;
			Roll = -0;
			Yaw = 165.049;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xb462ffae;
			X = 171.907;
			Y = -1000.52;
			Z = -99.9745;
			Pitch = 0;
			Roll = -0;
			Yaw = 165.049;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xb462ffae;
			X = 173.007;
			Y = -1001.52;
			Z = -99.9745;
			Pitch = 0;
			Roll = -0;
			Yaw = 165.049;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xc0d710bf;
			X = 174.68;
			Y = -1001.37;
			Z = -100.002;
			Pitch = -0;
			Roll = -0;
			Yaw = -74.2369;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xc0d710bf;
			X = 174.3;
			Y = -1002.11;
			Z = -100.002;
			Pitch = 0;
			Roll = 0;
			Yaw = -74.2369;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xc0d710bf;
			X = 173.789;
			Y = -1002.7;
			Z = -100.002;
			Pitch = 0;
			Roll = 0;
			Yaw = -74.2368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xc0d710bf;
			X = 173.089;
			Y = -1002.88;
			Z = -100.002;
			Pitch = 0;
			Roll = 0;
			Yaw = -74.2368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xc0d710bf;
			X = 172.308;
			Y = -1002.49;
			Z = -100.002;
			Pitch = 0;
			Roll = 0;
			Yaw = -74.2368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xc0d710bf;
			X = 171.787;
			Y = -1001.89;
			Z = -100.002;
			Pitch = 0;
			Roll = 0;
			Yaw = -74.2368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xc079b265;
			X = 172.987;
			Y = -999.884;
			Z = -100.378;
			Pitch = 0;
			Roll = -0;
			Yaw = -123.284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);


			HaxBy("R3ck17");
		}
		void mmf_ufoTower1()
		{
			float tempZ = 49.1342f;
			for (UINT i = 0; i < 75; i++)
			{
				tempZ += 8.1788f;
				//if (!DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(70.2592f, -674.0442f, tempZ, 3.0f, 3026699584, 0)) // p_spinning_anus_s
				mm_PlaceObject(3026699584, 70.2592f, -674.0442f, tempZ, 0.6600f, -0.9200f, -109.3099f, false);
			}
			HaxBy("RiNZLR ~s~&~b~ MAFINS");
		}
		void mmf_AirportDragStrip()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;

			//[3];
			Hash = 0xf5159d29;
			X = -950.961;
			Y = -3171.28;
			Z = 12.8247;
			Pitch = 0;
			Roll = 0;
			Yaw = 59.6612;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x25a7101d;
			X = -949.931;
			Y = -3172.87;
			Z = 12.9453;
			Pitch = 0;
			Roll = 0;
			Yaw = -29.058;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0x25a7101d;
			X = -949.22;
			Y = -3171.47;
			Z = 12.9453;
			Pitch = 0;
			Roll = 0;
			Yaw = -29.058;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			HaxBy("Outslider");
		}
		void mmf_AirportDriftTrack()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;

			//[3];
			Hash = 0xf5159d29;
			X = -938.583;
			Y = -3133.52;
			Z = 12.8947;
			Pitch = 0;
			Roll = 0;
			Yaw = -2.68574;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x5f5e76c9;
			X = -929.179;
			Y = -3126.14;
			Z = 12.9429;
			Pitch = 0;
			Roll = 0;
			Yaw = -6.26673;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0x5f5e76c9;
			X = -927.98;
			Y = -3117.33;
			Z = 12.9429;
			Pitch = 0;
			Roll = 0;
			Yaw = -6.26673;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0x5f5e76c9;
			X = -926.591;
			Y = -3107.53;
			Z = 12.9429;
			Pitch = 0;
			Roll = 0;
			Yaw = -6.26673;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0x5f5e76c9;
			X = -926.992;
			Y = -3095.72;
			Z = 12.9429;
			Pitch = 0;
			Roll = 0;
			Yaw = 11.6382;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0x5f5e76c9;
			X = -930.995;
			Y = -3085.5;
			Z = 12.943;
			Pitch = 0;
			Roll = 0;
			Yaw = 33.1241;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0x5f5e76c9;
			X = -939.999;
			Y = -3076.98;
			Z = 12.943;
			Pitch = 0;
			Roll = 0;
			Yaw = 59.0863;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0x5f5e76c9;
			X = -946.706;
			Y = -3125.02;
			Z = 12.9229;
			Pitch = 0;
			Roll = -0;
			Yaw = 179.049;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0x5f5e76c9;
			X = -946.596;
			Y = -3113.01;
			Z = 12.9229;
			Pitch = 0;
			Roll = -0;
			Yaw = 179.049;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0x5f5e76c9;
			X = -946.596;
			Y = -3092.83;
			Z = 12.9229;
			Pitch = 0;
			Roll = -0;
			Yaw = 179.049;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0x5f5e76c9;
			X = -946.596;
			Y = -3080.91;
			Z = 15.7229;
			Pitch = 0;
			Roll = -0;
			Yaw = 179.049;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0x5f5e76c9;
			X = -951.202;
			Y = -3074.23;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.4199;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0x5f5e76c9;
			X = -961.21;
			Y = -3094.66;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 160.249;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0x5f5e76c9;
			X = -957.29;
			Y = -3083.72;
			Z = 14.3129;
			Pitch = 12.5335;
			Roll = 4.37308e-007;
			Yaw = 160.249;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0x5f5e76c9;
			X = -939.999;
			Y = -3076.98;
			Z = 15.7531;
			Pitch = 0;
			Roll = 0;
			Yaw = 58.191;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0x5f5e76c9;
			X = -961.21;
			Y = -3094.66;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 160.249;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0x5f5e76c9;
			X = -962.419;
			Y = -3076.5;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 110.115;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0x5f5e76c9;
			X = -972.926;
			Y = -3083.07;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 133.392;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0x5f5e76c9;
			X = -980.331;
			Y = -3092.95;
			Z = 12.923;
			Pitch = 0;
			Roll = -0;
			Yaw = 151.297;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0x5f5e76c9;
			X = -978.933;
			Y = -3103.43;
			Z = 12.923;
			Pitch = 0;
			Roll = 0;
			Yaw = 47.4481;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0x5f5e76c9;
			X = -978.933;
			Y = -3103.43;
			Z = 12.923;
			Pitch = 0;
			Roll = 0;
			Yaw = 47.4481;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0x5f5e76c9;
			X = -971.237;
			Y = -3109.51;
			Z = 12.923;
			Pitch = 0;
			Roll = 0;
			Yaw = 57.2958;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0x5f5e76c9;
			X = -963.741;
			Y = -3119.17;
			Z = 12.923;
			Pitch = 0;
			Roll = 0;
			Yaw = 18.8002;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xf5159d29;
			X = -956.421;
			Y = -3132.05;
			Z = 12.8097;
			Pitch = 0;
			Roll = -0;
			Yaw = 176.364;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0x426a547c;
			X = -936.926;
			Y = -3108.23;
			Z = 13.397;
			Pitch = -0.00132612;
			Roll = -91.3706;
			Yaw = 2.79661;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0x5f5e76c9;
			X = -946.488;
			Y = -3102.35;
			Z = 15.6927;
			Pitch = 0;
			Roll = -0;
			Yaw = 179.049;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0x5f5e76c9;
			X = -951.202;
			Y = -3074.23;
			Z = 15.7551;
			Pitch = 0;
			Roll = 0;
			Yaw = 89.5247;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0x3a12a4ba;
			X = -946.606;
			Y = -3086.62;
			Z = 18.9766;
			Pitch = 0;
			Roll = 0;
			Yaw = -0.895247;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			HaxBy("Outslider");
		}
		void mmf_airportGateRamp1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash tempHash;
			tempHash = 2475986526; // ramp
			X = -1098.362f;
			Y = -2631.166f;
			Z = 19.0f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 152.6711f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1100.262f;
			Y = -2634.643f;
			Z = 21.1976f;
			Pitch = 16.2001f;
			Roll = 0.2f;
			Yaw = 150.3710f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1102.261f;
			Y = -2638.017f;
			Z = 25.01f;
			Pitch = 26.7002f;
			Roll = 0.2f;
			Yaw = 149.1709f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1103.961f;
			Y = -2640.907f;
			Z = 29.04f;
			Pitch = 28.3717f;
			Roll = 0.0f;
			Yaw = 146.8204f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);

			tempHash = 1952396163; // windmill
			X = -1119.607f;
			Y = -2670.960f;
			Z = -5.1250f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 150.5138f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1119.607f;
			Y = -2670.960f;
			Z = -5.1250f;
			Pitch = 0.0f;
			Roll = 0.0f;
			Yaw = 150.4014f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);

			tempHash = 3137065507;// starting line
			X = -1044.692f;
			Y = -2530.081f;
			Z = 20.4011f;
			Pitch = 85.1038f;
			Roll = -180.0f;
			Yaw = -32.2843f;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);

			HaxBy("RiNZLR");


		}
		void mmf_airportMiniRamp1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash tempHash;
			tempHash = 2475986526; // ramp
			X = -1242.076;
			Y = -2931.147;
			Z = 13.9924;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1247.110;
			Y = -2928.458;
			Z = 16.0130;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1251.585;
			Y = -2926.055;
			Z = 17.7865;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1254.688;
			Y = -2924.354;
			Z = 19.2500;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1258.351;
			Y = -2922.282;
			Z = 21.2135;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1261.825;
			Y = -2920.380;
			Z = 22.7670;
			Pitch = -0.1046;
			Roll = 0.0000;
			Yaw = 61.0607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);

			tempHash = 3966705493; // prop_container_03b
			X = -1270.249;
			Y = -2914.986;
			Z = 23.0137;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 60.8909;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1270.890;
			Y = -2916.217;
			Z = 23.0123;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 60.8909;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1272.111;
			Y = -2918.349;
			Z = 25.6708;
			Pitch = -0.4800;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1269.008;
			Y = -2912.644;
			Z = 22.9993;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1267.767;
			Y = -2910.371;
			Z = 22.9978;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1273.652;
			Y = -2907.108;
			Z = 22.9763;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1274.873;
			Y = -2909.400;
			Z = 23.0049;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1276.145;
			Y = -1911.713;
			Z = 23.0034;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1276.685;
			Y = -2912.994;
			Z = 23.0019;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1277.926;
			Y = -2915.136;
			Z = 25.60405;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1272.131;
			Y = -2918.329;
			Z = 28.4791;
			Pitch = -0.0000;
			Roll = 0.0500;
			Yaw = 60.9705;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1267.874;
			Y = -2915.438;
			Z = 28.3632;
			Pitch = 0.0000;
			Roll = 0.0000;
			Yaw = 147.2987;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1266.493;
			Y = -2908.077;
			Z = 22.9987;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -119.4622;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1272.368;
			Y = -2904.834;
			Z = 22.9972;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -119.4622;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1271.087;
			Y = -2902.582;
			Z = 23.0057;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -119.4622;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1265.151;
			Y = -2905.805;
			Z = 23.0042;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -119.4622;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1279.686;
			Y = -2909.851;
			Z = 25.6358;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -151.2388;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1279.686;
			Y = -2909.851;
			Z = 28.4844;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -151.2388;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1276.352;
			Y = -2903.905;
			Z = 28.4329;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -151.2388;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1276.352;
			Y = -2903.905;
			Z = 25.6214;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -151.2388;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1272.369;
			Y = -2900.957;
			Z = 25.6199;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.7608;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1272.369;
			Y = -2900.957;
			Z = 28.4385;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.7608;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1266.443;
			Y = -2905.210;
			Z = 28.4370;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.7608;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1266.443;
			Y = -2905.210;
			Z = 25.6255;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.7608;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1264.841;
			Y = -2905.141;
			Z = 25.6240;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.7608;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1265.172;
			Y = -2905.141;
			Z = 28.3426;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -118.8607;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1264.882;
			Y = -2910.660;
			Z = 25.6982;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -30.9603;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);
			X = -1265.663;
			Y = -2911.991;
			Z = 25.6968;
			Pitch = 0.0000;
			Roll = -0.0000;
			Yaw = -30.9603;
			mm_PlaceObject(tempHash, X, Y, Z, Pitch, Roll, Yaw, false);

			HaxBy("FBModderFresh");

		}
		void mmf_chilliadRamp1()
		{
			Hash tempHash = 3966705493; // prop_container_01a ... prop_container_03b
			mm_PlaceObject(tempHash, 509.8423f, 5589.2422f, 791.0656f, 0.1410f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 520.5002f, 5584.3774f, 790.5033f, 5.4410f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 531.0571f, 5579.5405f, 788.6912f, 12.4410f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 541.3253f, 5574.8403f, 785.4896f, 19.4409f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 551.0662f, 5570.3701f, 780.7990f, 27.5407f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 560.1738f, 5566.2046f, 774.6979f, 35.0403f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 568.6718f, 5562.3198f, 767.4281f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 576.9716f, 5558.5269f, 759.5663f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 585.2493f, 5554.7471f, 751.7451f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 593.5072f, 5550.9722f, 743.9170f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 601.7770f, 5547.1912f, 736.0764f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 610.0651f, 5543.3994f, 728.2167f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 618.3337f, 5539.6226f, 720.3861f, 40.7936f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 626.6017f, 5535.8477f, 712.5473f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 634.8616f, 5532.0669f, 704.7252f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 643.1213f, 5528.2861f, 696.8940f, 40.7936f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 651.3914f, 5524.5059f, 689.0526f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 659.6512f, 5520.7275f, 681.2211f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 667.9110f, 5516.9424f, 673.3893f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 676.1708f, 5513.1670f, 665.5580f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 684.4307f, 5509.3789f, 657.7266f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 692.6906f, 5505.6079f, 649.9052f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 700.9504f, 5501.8271f, 642.0737f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 709.2201f, 5498.0464f, 634.2426f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 717.4602f, 5494.2759f, 626.4309f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 725.7202f, 5490.4980f, 618.5996f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 733.9800f, 5486.7226f, 610.7783f, 40.7396f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 742.5997f, 5482.7764f, 603.1669f, 36.9395f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 751.8304f, 5478.5518f, 596.3347f, 31.0392f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 761.7103f, 5474.0220f, 590.6132f, 24.5989f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 772.0702f, 5469.2827f, 586.0803f, 18.9288f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 782.8400f, 5464.3433f, 582.8604f, 11.5788f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 793.8899f, 5459.2847f, 581.1174f, 5.0787f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 805.1001f, 5454.1479f, 580.8762f, -2.5212f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 816.1702f, 5449.0796f, 581.9746f, -7.6213f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 827.1907f, 5444.0405f, 584.5823f, -16.6212f, 0.0f, 65.3998f, false);
			mm_PlaceObject(tempHash, 837.6807f, 5439.2407f, 588.8990f, -24.4210f, 0.0f, 65.3998f, false);
			HaxBy("XBLToothpik");

		}
		void mmf_beechFerrisRamp1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash tempHash;
			float zoffset = 0.0f;

			tempHash = 2475986526;
			X = -1461.917;
			Y = -1216.876;
			Z = 2.5836;
			Pitch = -2.3048;
			Roll = 0.0000;
			Yaw = -154.8776;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1460.317;
			Y = -1219.975;
			Z = 4.3801;
			Pitch = 12.6953;
			Roll = 0.0000;
			Yaw = -154.8776;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1458.395;
			Y = -1223.774;
			Z = 7.9937;
			Pitch = 23.6001;
			Roll = -0.1000;
			Yaw = -154.8776;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1456.996;
			Y = -1226.673;
			Z = 11.8772;
			Pitch = 31.7229;
			Roll = 0.0000;
			Yaw = -154.3821;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1456.396;
			Y = -1228.273;
			Z = 14.9608;
			Pitch = 48.6740;
			Roll = 0.0000;
			Yaw = -153.9824;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1455.996;
			Y = -1229.073;
			Z = 19.7441;
			Pitch = 68.6628;
			Roll = 0.0000;
			Yaw = -153.9824;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1456.196;
			Y = -1228.473;
			Z = 24.8276;
			Pitch = 81.7043;
			Roll = 27.4173;
			Yaw = 179.9998;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1456.896;
			Y = -1226.473;
			Z = 28.9111;
			Pitch = 69.6993;
			Roll = -154.7411;
			Yaw = -1.1141;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1458.595;
			Y = -1223.374;
			Z = 31.5945;
			Pitch = 49.1567;
			Roll = -172.7567;
			Yaw = 19.4210;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1460.595;
			Y = -1218.375;
			Z = 33.5779;
			Pitch = 36.1556;
			Roll = -175.0982;
			Yaw = 24.5220;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1462.794;
			Y = -1214.276;
			Z = 34.1610;
			Pitch = 16.3516;
			Roll = -177.2038;
			Yaw = 23.4487;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1465.296;
			Y = -1209.779;
			Z = 32.5228;
			Pitch = -7.8127;
			Roll = -180.0000;
			Yaw = 27.8081;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1465.296;
			Y = -1209.779;
			Z = 32.5228;
			Pitch = -7.8127;
			Roll = -180.0000;
			Yaw = 27.8081;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1466.895;
			Y = -1205.680;
			Z = 29.0062;
			Pitch = -24.8223;
			Roll = 179.9999;
			Yaw = 26.9128;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1468.295;
			Y = -1202.980;
			Z = 24.1897;
			Pitch = -48.8897;
			Roll = 179.9999;
			Yaw = 26.9123;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1468.595;
			Y = -1202.680;
			Z = 19.3732;
			Pitch = -72.5705;
			Roll = 179.9999;
			Yaw = 26.9128;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1467.995;
			Y = -1203.880;
			Z = 13.5732;
			Pitch = -89.6205;
			Roll = -23.8147;
			Yaw = -179.6671;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2475986526;
			X = -1467.115;
			Y = -1205.676;
			Z = 10.7072;
			Pitch = -63.5491;
			Roll = 0.0000;
			Yaw = -156.5045;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 4109455646;
			X = -1465.050;
			Y = -1210.026;
			Z = 7.9503;
			Pitch = 9.5304;
			Roll = 1.3999;
			Yaw = 24.0288;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2975320548;
			X = -1463.047;
			Y = -1214.195;
			Z = 6.7879;
			Pitch = -6.5000;
			Roll = 1.4000;
			Yaw = 24.4236;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 2975320548;
			X = -1460.948;
			Y = -1218.794;
			Z = 7.6600;
			Pitch = -29.9322;
			Roll = -0.2000;
			Yaw = 24.6223;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 1952396163;
			X = -1497.757;
			Y = -1113.840;
			Z = -3.0800;
			Pitch = -90.0000;
			Roll = -165.7918;
			Yaw = 0.0000;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 3291218330;
			X = -1465.617;
			Y = -1217.644;
			Z = 18.0000;
			Pitch = 13.4841;
			Roll = 180.0000;
			Yaw = -155.8283;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			tempHash = 3291218330;
			X = -1458.885;
			Y = -1214.404;
			Z = 18.0000;
			Pitch = -38.4956;
			Roll = 0.0000;
			Yaw = -153.9824;
			mm_PlaceObject(tempHash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("R3ck17");
		}
		void mmf_mazeRoofMiniRamp1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			Hash = 1600026313;
			X = -79.2766;
			Y = -805.701;
			Z = 323.204;
			Pitch = -0.0461548;
			Roll = -89.934;
			Yaw = 109.364;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1600026313;
			X = -78.4864;
			Y = -807.943;
			Z = 323.202;
			Pitch = -0.0461548;
			Roll = -89.934;
			Yaw = 109.364;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1600026313;
			X = -79.8373;
			Y = -803.709;
			Z = 323.205;
			Pitch = -0.0461548;
			Roll = -89.934;
			Yaw = 109.364;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1600026313;
			X = -80.4295;
			Y = -801.947;
			Z = 323.207;
			Pitch = -0.0461548;
			Roll = -89.934;
			Yaw = 109.364;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -83.5429;
			Y = -795.106;
			Z = 322.073;
			Pitch = -63.5625;
			Roll = -0;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -84.2429;
			Y = -793.182;
			Z = 321.08;
			Pitch = -63.5625;
			Roll = -0;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -84.9429;
			Y = -791.108;
			Z = 319.956;
			Pitch = -62.6673;
			Roll = 1.85944e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -85.8122;
			Y = -788.585;
			Z = 318.638;
			Pitch = -63.5625;
			Roll = -0;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -89.1589;
			Y = -779.487;
			Z = 313.336;
			Pitch = -59.5389;
			Roll = 0.0799977;
			Yaw = -160.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -90.7065;
			Y = -774.863;
			Z = 310.09;
			Pitch = -57.4945;
			Roll = 0.601049;
			Yaw = -160.251;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -91.4887;
			Y = -772.564;
			Z = 308.403;
			Pitch = -55.1674;
			Roll = 0.671198;
			Yaw = -160.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -91.7565;
			Y = -771.74;
			Z = 307.844;
			Pitch = -56.4466;
			Roll = 0.0800507;
			Yaw = -160.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -93.6941;
			Y = -766.245;
			Z = 302.736;
			Pitch = -45.9996;
			Roll = 0.0800564;
			Yaw = -160.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -94.2969;
			Y = -764.648;
			Z = 301.067;
			Pitch = -44.7623;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -95.4855;
			Y = -761.334;
			Z = 296.406;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.0707;
			Y = -759.689;
			Z = 293.709;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.1606;
			Y = -759.499;
			Z = 294.259;
			Pitch = -42.0766;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.8807;
			Y = -757.391;
			Z = 292.506;
			Pitch = -51.0291;
			Roll = -1.35751e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -97.9597;
			Y = -754.358;
			Z = 290.78;
			Pitch = -62.6673;
			Roll = 1.85944e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -94.2969;
			Y = -764.648;
			Z = 301.067;
			Pitch = -44.7623;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -94.886;
			Y = -762.996;
			Z = 298.741;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -95.4855;
			Y = -761.334;
			Z = 296.406;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.0707;
			Y = -759.689;
			Z = 293.46;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -98.7192;
			Y = -752.356;
			Z = 290.042;
			Pitch = -69.9278;
			Roll = 9.20433e-005;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.0707;
			Y = -759.689;
			Z = 293.709;
			Pitch = -36.7051;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -96.8807;
			Y = -757.391;
			Z = 292.506;
			Pitch = -51.0291;
			Roll = -1.35751e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -97.3203;
			Y = -756.159;
			Z = 291.688;
			Pitch = -57.2958;
			Roll = -0;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -97.9597;
			Y = -754.358;
			Z = 290.78;
			Pitch = -62.6673;
			Roll = 1.85944e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -99.3223;
			Y = -750.534;
			Z = 290.479;
			Pitch = -90;
			Roll = 160.249;
			Yaw = 0;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -99.0244;
			Y = -751.684;
			Z = 290.499;
			Pitch = -90;
			Roll = 160.249;
			Yaw = 0;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -100.348;
			Y = -747.881;
			Z = 290.452;
			Pitch = -89.5256;
			Roll = -1.60983e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -100.26;
			Y = -748.154;
			Z = 290.462;
			Pitch = -76.096;
			Roll = 1.77651e-006;
			Yaw = 19.6954;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -100.687;
			Y = -747.053;
			Z = 290.731;
			Pitch = -62.6673;
			Roll = -0;
			Yaw = 20.5907;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -101.346;
			Y = -745.387;
			Z = 291.611;
			Pitch = -58.191;
			Roll = 1.61979e-006;
			Yaw = 19.6954;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -102.234;
			Y = -743.119;
			Z = 293.091;
			Pitch = -52.2249;
			Roll = 0.000834869;
			Yaw = 21.3433;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -103.071;
			Y = -741.047;
			Z = 294.832;
			Pitch = -48.0666;
			Roll = 0.000776778;
			Yaw = 21.3425;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1087520462;
			X = -103.75;
			Y = -739.405;
			Z = 296.413;
			Pitch = -45.1472;
			Roll = 0.000777162;
			Yaw = 21.3422;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = 1554.97;
			Y = -755.111;
			Z = 183.768;
			Pitch = -21.0846;
			Roll = -158.665;
			Yaw = 92.4315;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -183.6;
			Y = -2100.67;
			Z = 73.2043;
			Pitch = -4.66044;
			Roll = 0.0117322;
			Yaw = 173.901;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -90.3515;
			Y = -798.112;
			Z = 319.893;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -76.5616;
			Y = -793.191;
			Z = 319.493;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -79.5187;
			Y = -785.083;
			Z = 317.189;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -93.2293;
			Y = -790.348;
			Z = 317.189;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -95.3479;
			Y = -784.483;
			Z = 313.696;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -81.6733;
			Y = -779.348;
			Z = 313.696;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -84.0215;
			Y = -772.971;
			Z = 309.575;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -97.4731;
			Y = -778.557;
			Z = 308.877;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -100.01;
			Y = -771.31;
			Z = 304.367;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -86.2094;
			Y = -766.939;
			Z = 304.367;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -87.9094;
			Y = -762.07;
			Z = 299.666;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -101.829;
			Y = -766.277;
			Z = 299.666;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -103.318;
			Y = -762.175;
			Z = 293.966;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -89.9785;
			Y = -756.476;
			Z = 293.966;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -104.948;
			Y = -757.681;
			Z = 288.866;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -91.5378;
			Y = -752.285;
			Z = 288.866;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -94.7566;
			Y = -743.406;
			Z = 288.866;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -108.146;
			Y = -748.798;
			Z = 288.866;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -108.146;
			Y = -748.798;
			Z = 295.608;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -94.7458;
			Y = -743.402;
			Z = 295.608;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -108.225;
			Y = -748.694;
			Z = 302.608;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -101.483;
			Y = -746.044;
			Z = 305.602;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 4143853297;
			X = -94.7426;
			Y = -743.595;
			Z = 302.651;
			Pitch = 0;
			Roll = -0;
			Yaw = -159.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1157292806;
			X = -99.7732;
			Y = -750.516;
			Z = 309.575;
			Pitch = 0;
			Roll = 0;
			Yaw = 24.1761;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1998517203;
			X = -81.0993;
			Y = -790.139;
			Z = 326.57;
			Pitch = -0;
			Roll = -0;
			Yaw = -82.6177;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1998517203;
			X = -88.8988;
			Y = -792.911;
			Z = 326.95;
			Pitch = 0;
			Roll = 0;
			Yaw = -82.6177;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 2375650849;
			X = -102.454;
			Y = -742.6;
			Z = 309.309;
			Pitch = 0;
			Roll = 0;
			Yaw = 20.9393;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 3167053133;
			X = -103.451;
			Y = -740.541;
			Z = 307.317;
			Pitch = -0.900002;
			Roll = -1.2;
			Yaw = 20.8887;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1346941736;
			X = -104.453;
			Y = -740.557;
			Z = 307.456;
			Pitch = -8.56431e-015;
			Roll = -2.3697e-023;
			Yaw = -2.1134;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 1346941736;
			X = -100.153;
			Y = -739.459;
			Z = 307.445;
			Pitch = 1.3;
			Roll = 2.79996;
			Yaw = 21.6645;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 2475986526;
			X = -105.054;
			Y = -740.282;
			Z = 294.827;
			Pitch = 9.80001;
			Roll = 0.299996;
			Yaw = 18.7291;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 2475986526;
			X = -102.154;
			Y = -739.285;
			Z = 294.83;
			Pitch = 9.80001;
			Roll = 0.299996;
			Yaw = 18.7291;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 728636342;
			X = -107.33;
			Y = -741.864;
			Z = 307.461;
			Pitch = 4.04487e-015;
			Roll = -0;
			Yaw = 43.7729;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -81.0088;
			Y = -791.22;
			Z = 326.713;
			Pitch = 0;
			Roll = -0;
			Yaw = 100.953;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -79.0283;
			Y = -791.31;
			Z = 326.763;
			Pitch = 0;
			Roll = -0;
			Yaw = 100.953;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -76.8377;
			Y = -790.87;
			Z = 326.823;
			Pitch = 0;
			Roll = -0;
			Yaw = 100.953;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -88.3376;
			Y = -794.173;
			Z = 327.042;
			Pitch = 0;
			Roll = 0;
			Yaw = 31.5501;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -90.0376;
			Y = -795.174;
			Z = 327.262;
			Pitch = 0;
			Roll = 0;
			Yaw = 31.5501;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 803874239;
			X = -91.6375;
			Y = -796.175;
			Z = 327.482;
			Pitch = 0;
			Roll = 0;
			Yaw = 31.5501;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -83.5429;
			Y = -795.106;
			Z = 322.073;
			Pitch = -62.6673;
			Roll = -1.85944e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -82.7624;
			Y = -797.278;
			Z = 323.205;
			Pitch = -63.5625;
			Roll = -0;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -81.9619;
			Y = -799.69;
			Z = 324.517;
			Pitch = -90;
			Roll = 160.979;
			Yaw = 0;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -85.8122;
			Y = -788.585;
			Z = 318.638;
			Pitch = -62.6673;
			Roll = -1.85944e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -86.6914;
			Y = -786.173;
			Z = 317.344;
			Pitch = -63.4282;
			Roll = 9.54322e-006;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -87.6309;
			Y = -783.7;
			Z = 316.018;
			Pitch = -63.4282;
			Roll = 1.14519e-005;
			Yaw = -159.354;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -89.1589;
			Y = -779.487;
			Z = 313.336;
			Pitch = -59.0863;
			Roll = 1.66186e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -90.0154;
			Y = -777.115;
			Z = 311.729;
			Pitch = -57.5081;
			Roll = -7.9468e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -91.4887;
			Y = -772.564;
			Z = 308.403;
			Pitch = -54.61;
			Roll = 1.47421e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -92.4668;
			Y = -769.701;
			Z = 306.299;
			Pitch = -55.0202;
			Roll = 2.97852e-006;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = -93.1365;
			Y = -767.87;
			Z = 304.542;
			Pitch = -48.7327;
			Roll = 1.03555e-005;
			Yaw = -160.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);
			Hash = 0x40d23ece;
			X = 88.4401;
			Y = 781.8082;
			Z = 314.8009;
			Pitch = -61.0405;
			Roll = 0;
			Yaw = -159.3539;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("RiNZLR");

		}
		void mmf_mazeDerbyFerrisTree()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 2475986526;
			X = -85.3743;
			Y = -826.099;
			Z = 325.136;
			Pitch = -15.7025;
			Roll = 2.66061e-006;
			Yaw = 124.307;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 2475986526;
			X = -87.2815;
			Y = -822.239;
			Z = 325.126;
			Pitch = -15.6308;
			Roll = -4.4328e-007;
			Yaw = 100.311;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 2475986526;
			X = -87.7973;
			Y = -817.987;
			Z = 325.119;
			Pitch = -14.8468;
			Roll = -1.3801e-008;
			Yaw = 89.3982;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 2475986526;
			X = -86.5177;
			Y = -813.202;
			Z = 325.089;
			Pitch = -14.5267;
			Roll = 4.40985e-007;
			Yaw = 64.6634;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 2475986526;
			X = -83.8934;
			Y = -809.424;
			Z = 325.073;
			Pitch = -14.5264;
			Roll = -4.40984e-007;
			Yaw = 46.5132;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 2475986526;
			X = -79.8704;
			Y = -807.22;
			Z = 325.143;
			Pitch = -14.049;
			Roll = -0;
			Yaw = 21.4769;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 2475986526;
			X = -75.2243;
			Y = -806.286;
			Z = 325.164;
			Pitch = -12.0419;
			Roll = -0;
			Yaw = 1.55726;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 2475986526;
			X = -71.1526;
			Y = -807.598;
			Z = 325.153;
			Pitch = -12.0416;
			Roll = 8.72982e-007;
			Yaw = -28.0523;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 2475986526;
			X = -64.9883;
			Y = -811.439;
			Z = 325.107;
			Pitch = -14.4263;
			Roll = 1.76314e-006;
			Yaw = -52.8494;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 2475986526;
			X = -62.8694;
			Y = -815.926;
			Z = 325.118;
			Pitch = -14.4265;
			Roll = -4.40786e-007;
			Yaw = -76.5979;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 2475986526;
			X = -67.6253;
			Y = -820.244;
			Z = 323.793;
			Pitch = -14.4263;
			Roll = -8.81571e-007;
			Yaw = -100.02;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 2475986526;
			X = -64.2717;
			Y = -825.422;
			Z = 325.112;
			Pitch = -14.4263;
			Roll = -0;
			Yaw = -121.256;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 2475986526;
			X = -67.4174;
			Y = -829.035;
			Z = 325.097;
			Pitch = -14.4263;
			Roll = 4.40785e-007;
			Yaw = -140.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 2475986526;
			X = -71.9478;
			Y = -831.257;
			Z = 325.113;
			Pitch = -14.4264;
			Roll = -0;
			Yaw = -166.006;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 2475986526;
			X = -76.7563;
			Y = -831.549;
			Z = 325.123;
			Pitch = -14.4263;
			Roll = -0;
			Yaw = 171.818;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 2475986526;
			X = -80.9087;
			Y = -830.357;
			Z = 325.097;
			Pitch = -14.4264;
			Roll = -4.40785e-007;
			Yaw = 152.209;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 2475986526;
			X = -83.4737;
			Y = -828.611;
			Z = 325.076;
			Pitch = -15.0688;
			Roll = -8.84176e-007;
			Yaw = 132.538;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 2475986526;
			X = -86.7602;
			Y = -824.03;
			Z = 325.044;
			Pitch = -15.9224;
			Roll = -0;
			Yaw = 116.957;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 2475986526;
			X = -87.5801;
			Y = -821.034;
			Z = 325.059;
			Pitch = -14.8593;
			Roll = -0;
			Yaw = 95.4435;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 2475986526;
			X = -87.6645;
			Y = -815.707;
			Z = 325.059;
			Pitch = -14.8589;
			Roll = 4.41656e-007;
			Yaw = 73.157;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 2475986526;
			X = -85.2523;
			Y = -810.983;
			Z = 325.043;
			Pitch = -14.859;
			Roll = -0;
			Yaw = 53.5324;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 2475986526;
			X = -82.0222;
			Y = -807.83;
			Z = 325.036;
			Pitch = -14.1422;
			Roll = -0;
			Yaw = 32.7605;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 2475986526;
			X = -77.5757;
			Y = -806.312;
			Z = 325.088;
			Pitch = -14.1843;
			Roll = -2.20155e-007;
			Yaw = 12.6263;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 2475986526;
			X = -73.2853;
			Y = -806.628;
			Z = 325.151;
			Pitch = -11.7962;
			Roll = -2.18048e-007;
			Yaw = -19.1717;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 2475986526;
			X = -63.6142;
			Y = -813.68;
			Z = 325.112;
			Pitch = -14.3655;
			Roll = 8.81331e-007;
			Yaw = -66.7885;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 2475986526;
			X = -62.233;
			Y = -818.528;
			Z = 325.065;
			Pitch = -14.6184;
			Roll = -2.7573e-008;
			Yaw = -88.1861;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 2475986526;
			X = -63.2876;
			Y = -823.434;
			Z = 325.114;
			Pitch = -14.5345;
			Roll = -0;
			Yaw = -111.446;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 2475986526;
			X = -65.7121;
			Y = -827.409;
			Z = 325.068;
			Pitch = -14.3048;
			Roll = -8.81092e-007;
			Yaw = -130.667;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 2475986526;
			X = -69.5981;
			Y = -830.542;
			Z = 325.066;
			Pitch = -14.5918;
			Roll = -8.8223e-007;
			Yaw = -155.474;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 2475986526;
			X = -74.2595;
			Y = -831.691;
			Z = 325.09;
			Pitch = -14.2059;
			Roll = -0;
			Yaw = -176.517;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 2475986526;
			X = -79.2316;
			Y = -831.297;
			Z = 325.108;
			Pitch = -14.4054;
			Roll = 4.40744e-007;
			Yaw = 164.271;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 2475986526;
			X = -93.8716;
			Y = -817.904;
			Z = 325.988;
			Pitch = -13.4339;
			Roll = -0;
			Yaw = 88.8361;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 2475986526;
			X = -93.5166;
			Y = -813.963;
			Z = 325.942;
			Pitch = -13.4341;
			Roll = -0;
			Yaw = 73.0256;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 2475986526;
			X = -92.121;
			Y = -810.584;
			Z = 325.996;
			Pitch = -13.4339;
			Roll = -4.38896e-007;
			Yaw = 64.9353;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 2475986526;
			X = -90.167;
			Y = -807.318;
			Z = 325.946;
			Pitch = -13.0244;
			Roll = 4.38159e-007;
			Yaw = 53.178;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 2475986526;
			X = -87.5086;
			Y = -804.25;
			Z = 325.978;
			Pitch = -12.9432;
			Roll = -4.38016e-007;
			Yaw = 42.3279;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 2475986526;
			X = -83.6027;
			Y = -801.744;
			Z = 325.971;
			Pitch = -12.9433;
			Roll = -0;
			Yaw = 26.3052;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 2475986526;
			X = -79.2787;
			Y = -800.531;
			Z = 326.011;
			Pitch = -12.9433;
			Roll = 4.38016e-007;
			Yaw = 13.0054;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 2475986526;
			X = -75.3309;
			Y = -801.285;
			Z = 325.849;
			Pitch = -10.2407;
			Roll = -0;
			Yaw = 1.58401;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 2475986526;
			X = -70.9341;
			Y = -800.541;
			Z = 326.198;
			Pitch = -10.5317;
			Roll = 2.17101e-007;
			Yaw = -20.0064;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 2475986526;
			X = -67.5734;
			Y = -802.52;
			Z = 326.262;
			Pitch = -10.471;
			Roll = -8.68232e-007;
			Yaw = -31.2185;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 2475986526;
			X = -74.0222;
			Y = -799.865;
			Z = 326.177;
			Pitch = -10.7327;
			Roll = -0;
			Yaw = -5.98314;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 2475986526;
			X = -81.6721;
			Y = -801.017;
			Z = 325.9;
			Pitch = -12.4601;
			Roll = -0;
			Yaw = 17.3792;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 2475986526;
			X = -85.6586;
			Y = -802.789;
			Z = 325.95;
			Pitch = -12.8791;
			Roll = 8.75807e-007;
			Yaw = 32.5856;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 2475986526;
			X = -88.9923;
			Y = -805.73;
			Z = 325.89;
			Pitch = -11.9333;
			Roll = 4.36316e-007;
			Yaw = 46.0613;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 2475986526;
			X = -93.9931;
			Y = -815.866;
			Z = 325.924;
			Pitch = -13.0519;
			Roll = -2.19104e-007;
			Yaw = 79.5966;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 2475986526;
			X = -93.7912;
			Y = -821.777;
			Z = 325.946;
			Pitch = -13.6946;
			Roll = -2.74611e-008;
			Yaw = 91.1427;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 2475986526;
			X = -93.2951;
			Y = -823.554;
			Z = 325.966;
			Pitch = -13.157;
			Roll = -0;
			Yaw = 101.424;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 2475986526;
			X = -92.5757;
			Y = -827.033;
			Z = 325.87;
			Pitch = -13.5323;
			Roll = 2.19538e-007;
			Yaw = 104.668;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 2475986526;
			X = -91.53;
			Y = -828.342;
			Z = 325.842;
			Pitch = -14.1563;
			Roll = -0;
			Yaw = 120.328;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 2475986526;
			X = -90.5203;
			Y = -829.611;
			Z = 325.936;
			Pitch = -14.1563;
			Roll = 4.40256e-007;
			Yaw = 124.573;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 2475986526;
			X = -87.9554;
			Y = -832.877;
			Z = 325.894;
			Pitch = -14.1563;
			Roll = 4.40256e-007;
			Yaw = 132.995;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 2475986526;
			X = -89.3865;
			Y = -831.322;
			Z = 325.887;
			Pitch = -14.1562;
			Roll = -0;
			Yaw = 126.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 2475986526;
			X = -83.8118;
			Y = -835.765;
			Z = 326.063;
			Pitch = -12.243;
			Roll = 4.36821e-007;
			Yaw = 151.527;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 2475986526;
			X = -85.1736;
			Y = -833.789;
			Z = 325.653;
			Pitch = -14.4072;
			Roll = -4.40747e-007;
			Yaw = 145.777;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 2475986526;
			X = -86.4247;
			Y = -834.407;
			Z = 325.915;
			Pitch = -14.2701;
			Roll = -0;
			Yaw = 143.277;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 2475986526;
			X = -77.6428;
			Y = -837.649;
			Z = 326.163;
			Pitch = -10.8391;
			Roll = 1.0866e-007;
			Yaw = 171.297;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 2475986526;
			X = -80.7015;
			Y = -837.145;
			Z = 326.059;
			Pitch = -12.3172;
			Roll = -0;
			Yaw = 162.332;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 2475986526;
			X = -73.861;
			Y = -837.826;
			Z = 326.061;
			Pitch = -12.3173;
			Roll = 1.09236e-007;
			Yaw = -176.632;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 2475986526;
			X = -75.479;
			Y = -837.909;
			Z = 326.025;
			Pitch = -12.3172;
			Roll = -0;
			Yaw = 174.574;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 2475986526;
			X = -70.4799;
			Y = -837.265;
			Z = 326.09;
			Pitch = -12.3173;
			Roll = -0;
			Yaw = -166.182;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 2475986526;
			X = -67.0415;
			Y = -836.185;
			Z = 326.018;
			Pitch = -12.3171;
			Roll = -0;
			Yaw = -156.039;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 2475986526;
			X = -63.5702;
			Y = -833.725;
			Z = 326.1;
			Pitch = -11.2947;
			Roll = -0;
			Yaw = -140.961;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 2475986526;
			X = -64.8504;
			Y = -834.996;
			Z = 325.951;
			Pitch = -11.5263;
			Roll = -0;
			Yaw = -145.834;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 2475986526;
			X = -60.9992;
			Y = -831.419;
			Z = 326.075;
			Pitch = -11.5262;
			Roll = -0;
			Yaw = -130.963;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 2475986526;
			X = -58.9923;
			Y = -828.729;
			Z = 326.116;
			Pitch = -11.5262;
			Roll = -4.35673e-007;
			Yaw = -121.973;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 2475986526;
			X = -57.5045;
			Y = -825.626;
			Z = 326.114;
			Pitch = -11.5263;
			Roll = -0;
			Yaw = -110.959;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 2475986526;
			X = -62.4924;
			Y = -821.128;
			Z = 325.082;
			Pitch = -14.5467;
			Roll = 2.20512e-007;
			Yaw = -102.385;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 2475986526;
			X = -56.5533;
			Y = -822.397;
			Z = 326.08;
			Pitch = -11.1311;
			Roll = -2.17536e-007;
			Yaw = -102;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 2475986526;
			X = -56.0681;
			Y = -818.32;
			Z = 326.087;
			Pitch = -11.1312;
			Roll = -2.7192e-008;
			Yaw = -87.9469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 2475986526;
			X = -56.0911;
			Y = -820.05;
			Z = 326.049;
			Pitch = -11.0325;
			Roll = 2.17462e-007;
			Yaw = -100.794;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 2475986526;
			X = -56.8952;
			Y = -814.518;
			Z = 326.142;
			Pitch = -11.0324;
			Roll = -0;
			Yaw = -76.5476;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 2475986526;
			X = -56.2989;
			Y = -816.237;
			Z = 326.048;
			Pitch = -11.0324;
			Roll = 1.08731e-007;
			Yaw = -83.2139;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 2475986526;
			X = -58.1209;
			Y = -811.23;
			Z = 326.116;
			Pitch = -10.9697;
			Roll = -0;
			Yaw = -66.7674;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 2475986526;
			X = -60.096;
			Y = -807.639;
			Z = 326.119;
			Pitch = -11.5544;
			Roll = 4.35717e-007;
			Yaw = -52.7596;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 2475986526;
			X = -59.0622;
			Y = -809.17;
			Z = 326.095;
			Pitch = -11.0574;
			Roll = -0;
			Yaw = -62.782;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 2475986526;
			X = -64.1466;
			Y = -804.55;
			Z = 326.283;
			Pitch = -11.1035;
			Roll = -0;
			Yaw = -30.477;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 2475986526;
			X = -62.081;
			Y = -805.317;
			Z = 326.116;
			Pitch = -11.1035;
			Roll = -4.3503e-007;
			Yaw = -40.7682;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 2475986526;
			X = -66.5913;
			Y = -808.328;
			Z = 325.238;
			Pitch = -12.4517;
			Roll = 4.3717e-007;
			Yaw = -40.3246;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 2475986526;
			X = -68.2603;
			Y = -807.899;
			Z = 325.336;
			Pitch = -13.8689;
			Roll = 4.39706e-007;
			Yaw = -33.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 2475986526;
			X = -97.6945;
			Y = -807.971;
			Z = 327.174;
			Pitch = -9.63569;
			Roll = 4.32996e-007;
			Yaw = 64.7568;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 2475986526;
			X = -95.1453;
			Y = -803.637;
			Z = 327.147;
			Pitch = -9.63537;
			Roll = -8.6599e-007;
			Yaw = 53.6544;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 2475986526;
			X = -91.6251;
			Y = -799.702;
			Z = 327.176;
			Pitch = -9.63539;
			Roll = -0;
			Yaw = 42.2513;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 2475986526;
			X = -86.3087;
			Y = -796.203;
			Z = 327.177;
			Pitch = -9.63542;
			Roll = -4.32995e-007;
			Yaw = 25.9296;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 2475986526;
			X = -80.6908;
			Y = -794.505;
			Z = 327.217;
			Pitch = -9.63537;
			Roll = 2.16498e-007;
			Yaw = 13.0745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 2475986526;
			X = -75.6415;
			Y = -795.169;
			Z = 327.2;
			Pitch = -9.63555;
			Roll = -1.08249e-007;
			Yaw = 2.8097;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 2475986526;
			X = -68.8079;
			Y = -794.744;
			Z = 327.535;
			Pitch = -9.63558;
			Roll = -2.16498e-007;
			Yaw = -20.0341;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 2475986526;
			X = -64.37;
			Y = -797.284;
			Z = 327.603;
			Pitch = -9.6351;
			Roll = -4.32995e-007;
			Yaw = -31.6732;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 2475986526;
			X = -61.0278;
			Y = -799.404;
			Z = 327.549;
			Pitch = -9.63516;
			Roll = 4.32995e-007;
			Yaw = -31.016;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 2475986526;
			X = -57.9995;
			Y = -800.68;
			Z = 327.42;
			Pitch = -9.6353;
			Roll = 1.29899e-006;
			Yaw = -41.7027;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 2475986526;
			X = -55.2978;
			Y = -803.815;
			Z = 327.389;
			Pitch = -9.63524;
			Roll = -0;
			Yaw = -52.2107;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 2475986526;
			X = -53.4048;
			Y = -806.624;
			Z = 327.376;
			Pitch = -9.63526;
			Roll = -0;
			Yaw = -65.3971;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 2475986526;
			X = -52.0622;
			Y = -809.533;
			Z = 327.354;
			Pitch = -9.63541;
			Roll = -0;
			Yaw = -65.7624;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 2475986526;
			X = -50.9164;
			Y = -813.132;
			Z = 327.442;
			Pitch = -9.63524;
			Roll = 2.16497e-007;
			Yaw = -76.865;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 2475986526;
			X = -49.9295;
			Y = -818.102;
			Z = 327.381;
			Pitch = -9.63531;
			Roll = -5.41244e-008;
			Yaw = -88.2146;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 2475986526;
			X = -50.5468;
			Y = -823.622;
			Z = 327.378;
			Pitch = -9.63572;
			Roll = 4.32996e-007;
			Yaw = -101.598;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 2475986526;
			X = -51.7552;
			Y = -827.819;
			Z = 327.385;
			Pitch = -9.63569;
			Roll = 6.49493e-007;
			Yaw = -111.077;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 2475986526;
			X = -53.727;
			Y = -832.032;
			Z = 327.367;
			Pitch = -9.63521;
			Roll = -0;
			Yaw = -122.142;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 2475986526;
			X = -56.3494;
			Y = -835.471;
			Z = 327.34;
			Pitch = -9.63578;
			Roll = 4.32996e-007;
			Yaw = -131.675;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 2475986526;
			X = -59.7118;
			Y = -838.501;
			Z = 327.384;
			Pitch = -9.63533;
			Roll = -0;
			Yaw = -141.372;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 2475986526;
			X = -64.5693;
			Y = -841.792;
			Z = 327.24;
			Pitch = -9.63515;
			Roll = -2.16497e-007;
			Yaw = -156.16;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 2475986526;
			X = -69.036;
			Y = -843.266;
			Z = 327.309;
			Pitch = -9.63525;
			Roll = 2.16497e-007;
			Yaw = -166.686;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 2475986526;
			X = -73.5382;
			Y = -843.999;
			Z = 327.285;
			Pitch = -9.6355;
			Roll = -0;
			Yaw = -177.212;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 2475986526;
			X = -78.5619;
			Y = -843.703;
			Z = 327.458;
			Pitch = -9.63545;
			Roll = -1.08249e-007;
			Yaw = 171.015;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 2475986526;
			X = -82.595;
			Y = -843.001;
			Z = 327.277;
			Pitch = -9.6352;
			Roll = -2.16497e-007;
			Yaw = 161.654;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 2475986526;
			X = -86.7336;
			Y = -841.135;
			Z = 327.284;
			Pitch = -9.63566;
			Roll = -0;
			Yaw = 150.983;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 2475986526;
			X = -90.07;
			Y = -839.341;
			Z = 327.025;
			Pitch = -9.63574;
			Roll = 4.32996e-007;
			Yaw = 143.545;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 2475986526;
			X = -92.513;
			Y = -837.087;
			Z = 327.008;
			Pitch = -9.63523;
			Roll = -4.32995e-007;
			Yaw = 132.871;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 2475986526;
			X = -95.5355;
			Y = -833.068;
			Z = 327.049;
			Pitch = -9.63525;
			Roll = 8.6599e-007;
			Yaw = 124.512;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 2475986526;
			X = -98.5443;
			Y = -828.598;
			Z = 327.033;
			Pitch = -9.63553;
			Roll = 2.16498e-007;
			Yaw = 104.64;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 2475986526;
			X = -99.3358;
			Y = -824.801;
			Z = 327.138;
			Pitch = -9.63539;
			Roll = 2.16498e-007;
			Yaw = 101.678;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 2475986526;
			X = -99.969;
			Y = -821.91;
			Z = 327.11;
			Pitch = -9.63541;
			Roll = -2.70622e-008;
			Yaw = 91.5501;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 2475986526;
			X = -100.012;
			Y = -817.789;
			Z = 327.15;
			Pitch = -9.63535;
			Roll = -0;
			Yaw = 88.8234;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 2475986526;
			X = -99.394;
			Y = -812.176;
			Z = 327.105;
			Pitch = -9.63525;
			Roll = -4.32995e-007;
			Yaw = 73.0223;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 2475986526;
			X = -100.025;
			Y = -814.868;
			Z = 327.097;
			Pitch = -9.97277;
			Roll = 2.16718e-007;
			Yaw = 83.1537;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			Hash = 2475986526;
			X = -98.7075;
			Y = -809.885;
			Z = 327.026;
			Pitch = -8.13758;
			Roll = 2.15614e-007;
			Yaw = 67.8881;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[119];
			Hash = 2475986526;
			X = -96.5885;
			Y = -805.701;
			Z = 327.144;
			Pitch = -9.8947;
			Roll = -0;
			Yaw = 60.5096;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 2475986526;
			X = -93.5987;
			Y = -807.353;
			Z = 326.343;
			Pitch = -11.5713;
			Roll = -0;
			Yaw = 60.8753;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 2475986526;
			X = -93.414;
			Y = -801.299;
			Z = 327.124;
			Pitch = -9.92995;
			Roll = -0;
			Yaw = 48.7085;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 2475986526;
			X = -88.9655;
			Y = -797.634;
			Z = 327.118;
			Pitch = -9.92994;
			Roll = -4.33379e-007;
			Yaw = 33.0571;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 2475986526;
			X = -83.5673;
			Y = -795.148;
			Z = 327.101;
			Pitch = -9.92985;
			Roll = -0;
			Yaw = 17.5819;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 2475986526;
			X = -76.5167;
			Y = -797.998;
			Z = 326.32;
			Pitch = -12.4969;
			Roll = -2.73279e-008;
			Yaw = 1.58883;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 2475986526;
			X = -77.9613;
			Y = -794.235;
			Z = 327.223;
			Pitch = -8.9769;
			Roll = -0;
			Yaw = 4.53814;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 2475986526;
			X = -72.1225;
			Y = -793.825;
			Z = 327.497;
			Pitch = -9.57894;
			Roll = -2.16461e-007;
			Yaw = -12.2336;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 2475986526;
			X = -66.3998;
			Y = -795.965;
			Z = 327.526;
			Pitch = -9.42422;
			Roll = 8.65454e-007;
			Yaw = -29.018;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 2475986526;
			X = -67.9795;
			Y = -798.8;
			Z = 326.717;
			Pitch = -10.1561;
			Roll = -0;
			Yaw = -29.3495;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 2475986526;
			X = -56.5179;
			Y = -802.266;
			Z = 327.366;
			Pitch = -9.51013;
			Roll = 4.32835e-007;
			Yaw = -50.6537;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 2475986526;
			X = -50.1895;
			Y = -815.816;
			Z = 327.358;
			Pitch = -9.4734;
			Roll = -0;
			Yaw = -82.8649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 2475986526;
			X = -50.0992;
			Y = -820.896;
			Z = 327.345;
			Pitch = -9.47333;
			Roll = -1.08197e-007;
			Yaw = -95.7976;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 2475986526;
			X = -51.0061;
			Y = -825.839;
			Z = 327.369;
			Pitch = -9.37494;
			Roll = 4.32666e-007;
			Yaw = -107.054;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 2475986526;
			X = -52.5928;
			Y = -830.077;
			Z = 327.332;
			Pitch = -9.37496;
			Roll = -0;
			Yaw = -116.843;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 2475986526;
			X = -54.9387;
			Y = -833.93;
			Z = 327.334;
			Pitch = -9.37482;
			Roll = -0;
			Yaw = -127.887;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];
			Hash = 2475986526;
			X = -57.9491;
			Y = -837.16;
			Z = 327.309;
			Pitch = -9.37471;
			Roll = 4.32665e-007;
			Yaw = -135.839;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[136];
			Hash = 2475986526;
			X = -61.8874;
			Y = -840.436;
			Z = 327.231;
			Pitch = -9.37483;
			Roll = 4.32665e-007;
			Yaw = -146.534;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 2475986526;
			X = -66.7067;
			Y = -842.714;
			Z = 327.222;
			Pitch = -9.37501;
			Roll = -0;
			Yaw = -159.27;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 2475986526;
			X = -67.2981;
			Y = -840.996;
			Z = 326.756;
			Pitch = -9.37509;
			Roll = -0;
			Yaw = -159.014;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[139];
			Hash = 2475986526;
			X = -71.2047;
			Y = -843.988;
			Z = 327.3;
			Pitch = -9.36764;
			Roll = -1.08164e-007;
			Yaw = -172.013;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[140];
			Hash = 2475986526;
			X = -76.2479;
			Y = -844.026;
			Z = 327.261;
			Pitch = -9.36765;
			Roll = 1.08164e-007;
			Yaw = 175.986;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[141];
			Hash = 2475986526;
			X = -80.8027;
			Y = -843.618;
			Z = 327.263;
			Pitch = -9.36755;
			Roll = -4.32656e-007;
			Yaw = 165.215;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[142];
			Hash = 2475986526;
			X = -84.8343;
			Y = -842.167;
			Z = 327.254;
			Pitch = -9.36742;
			Roll = -4.32656e-007;
			Yaw = 152.377;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[143];
			Hash = 2475986526;
			X = -94.2445;
			Y = -835.1;
			Z = 326.976;
			Pitch = -9.27617;
			Roll = -4.32543e-007;
			Yaw = 128.396;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[144];
			Hash = 2475986526;
			X = -97.0896;
			Y = -831.054;
			Z = 326.937;
			Pitch = -10.0741;
			Roll = 8.67143e-007;
			Yaw = 118.72;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[145];
			Hash = 2475986526;
			X = -100.069;
			Y = -819.76;
			Z = 327.099;
			Pitch = -9.95297;
			Roll = -1.3544e-008;
			Yaw = 90.8729;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[146];
			Hash = 2475986526;
			X = -51.1585;
			Y = -811.568;
			Z = 327.373;
			Pitch = -9.58574;
			Roll = -0;
			Yaw = -69.3402;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[147];
			Hash = 2475986526;
			X = -103.09;
			Y = -805.421;
			Z = 328.718;
			Pitch = -5.79425;
			Roll = -0;
			Yaw = 64.506;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[148];
			Hash = 2475986526;
			X = -100.042;
			Y = -800.063;
			Z = 328.731;
			Pitch = -5.79425;
			Roll = 2.1454e-007;
			Yaw = 53.7039;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[149];
			Hash = 2475986526;
			X = -95.7282;
			Y = -795.2;
			Z = 328.764;
			Pitch = -5.79431;
			Roll = -0;
			Yaw = 41.8672;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[150];
			Hash = 2475986526;
			X = -92.3298;
			Y = -792.474;
			Z = 328.677;
			Pitch = -5.79412;
			Roll = 2.14539e-007;
			Yaw = 33.3113;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[151];
			Hash = 2475986526;
			X = -88.9795;
			Y = -790.697;
			Z = 328.76;
			Pitch = -5.79416;
			Roll = -0;
			Yaw = 25.9501;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[152];
			Hash = 2475986526;
			X = -85.4054;
			Y = -789.317;
			Z = 328.666;
			Pitch = -5.79433;
			Roll = -0;
			Yaw = 17.1877;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[153];
			Hash = 2475986526;
			X = -82.1189;
			Y = -788.558;
			Z = 328.793;
			Pitch = -5.9192;
			Roll = 1.07294e-007;
			Yaw = 12.7168;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[154];
			Hash = 2475986526;
			X = -78.4;
			Y = -788.132;
			Z = 328.83;
			Pitch = -5.91899;
			Roll = -0;
			Yaw = 3.75875;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[155];
			Hash = 2475986526;
			X = -75.8754;
			Y = -788.646;
			Z = 328.671;
			Pitch = -6.78921;
			Roll = -0;
			Yaw = 2.98721;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[156];
			Hash = 2475986526;
			X = -70.8259;
			Y = -787.837;
			Z = 329.128;
			Pitch = -5.04546;
			Roll = 1.07137e-007;
			Yaw = -12.2941;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[157];
			Hash = 2475986526;
			X = -66.7775;
			Y = -788.94;
			Z = 329.155;
			Pitch = -5.04558;
			Roll = -0;
			Yaw = -19.5666;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[158];
			Hash = 2475986526;
			X = -63.5163;
			Y = -790.736;
			Z = 329.085;
			Pitch = -5.04535;
			Roll = -4.28547e-007;
			Yaw = -29.2933;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[159];
			Hash = 2475986526;
			X = -61.0299;
			Y = -792.042;
			Z = 329.172;
			Pitch = -5.26389;
			Roll = -2.14347e-007;
			Yaw = -32.1174;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[160];
			Hash = 2475986526;
			X = -57.7537;
			Y = -794.2;
			Z = 329.16;
			Pitch = -5.26393;
			Roll = -0;
			Yaw = -32.2267;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[161];
			Hash = 2475986526;
			X = -53.8808;
			Y = -796.134;
			Z = 329.041;
			Pitch = -5.26389;
			Roll = -0;
			Yaw = -42.3308;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[162];
			Hash = 2475986526;
			X = -50.5092;
			Y = -800.141;
			Z = 328.99;
			Pitch = -5.26406;
			Roll = 2.14347e-007;
			Yaw = -52.4683;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[163];
			Hash = 2475986526;
			X = -47.9752;
			Y = -804.122;
			Z = 328.959;
			Pitch = -5.26398;
			Roll = -0;
			Yaw = -65.1505;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[164];
			Hash = 2475986526;
			X = -46.5685;
			Y = -807.149;
			Z = 328.929;
			Pitch = -5.26395;
			Roll = -0;
			Yaw = -66.9958;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[165];
			Hash = 2475986526;
			X = -45.0463;
			Y = -811.788;
			Z = 329.021;
			Pitch = -5.26392;
			Roll = -0;
			Yaw = -77.2513;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[166];
			Hash = 2475986526;
			X = -44.1983;
			Y = -815.072;
			Z = 328.956;
			Pitch = -5.26387;
			Roll = 5.35868e-008;
			Yaw = -82.8806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[167];
			Hash = 2475986526;
			X = -43.8673;
			Y = -817.92;
			Z = 328.98;
			Pitch = -5.26387;
			Roll = -2.67934e-008;
			Yaw = -88.1556;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[168];
			Hash = 2475986526;
			X = -44.0346;
			Y = -821.522;
			Z = 328.953;
			Pitch = -5.26387;
			Roll = 5.35868e-008;
			Yaw = -95.978;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[169];
			Hash = 2475986526;
			X = -44.5598;
			Y = -824.856;
			Z = 328.973;
			Pitch = -5.26387;
			Roll = -0;
			Yaw = -101.582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[170];
			Hash = 2475986526;
			X = -46.1092;
			Y = -830.019;
			Z = 328.985;
			Pitch = -5.26389;
			Roll = -0;
			Yaw = -111.097;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[171];
			Hash = 2475986526;
			X = -48.5833;
			Y = -835.261;
			Z = 328.968;
			Pitch = -5.26388;
			Roll = -0;
			Yaw = -122.598;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[172];
			Hash = 2475986526;
			X = -51.8013;
			Y = -839.526;
			Z = 328.926;
			Pitch = -5.26393;
			Roll = 2.14347e-007;
			Yaw = -131.788;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[173];
			Hash = 2475986526;
			X = -55.9339;
			Y = -843.258;
			Z = 328.987;
			Pitch = -5.26394;
			Roll = -0;
			Yaw = -141.8;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[174];
			Hash = 2475986526;
			X = -58.5152;
			Y = -845.543;
			Z = 328.833;
			Pitch = -5.26392;
			Roll = 8.5739e-007;
			Yaw = -147.129;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[175];
			Hash = 2475986526;
			X = -62.1086;
			Y = -847.355;
			Z = 328.837;
			Pitch = -5.26389;
			Roll = -0;
			Yaw = -156.346;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[176];
			Hash = 2475986526;
			X = -67.6252;
			Y = -849.166;
			Z = 328.911;
			Pitch = -5.26394;
			Roll = -0;
			Yaw = -166.741;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[177];
			Hash = 2475986526;
			X = -73.2336;
			Y = -850.06;
			Z = 328.883;
			Pitch = -5.26397;
			Roll = -2.67934e-008;
			Yaw = -177.431;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[178];
			Hash = 2475986526;
			X = -79.5282;
			Y = -849.717;
			Z = 329.046;
			Pitch = -5.26392;
			Roll = 5.35868e-008;
			Yaw = 170.517;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[179];
			Hash = 2475986526;
			X = -84.5215;
			Y = -848.802;
			Z = 328.867;
			Pitch = -5.26405;
			Roll = 4.28695e-007;
			Yaw = 161.164;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[180];
			Hash = 2475986526;
			X = -89.6061;
			Y = -846.328;
			Z = 328.851;
			Pitch = -5.26389;
			Roll = -0;
			Yaw = 150.62;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[181];
			Hash = 2475986526;
			X = -93.6584;
			Y = -844.231;
			Z = 328.606;
			Pitch = -5.26388;
			Roll = -0;
			Yaw = 143.429;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[182];
			Hash = 2475986526;
			X = -96.9401;
			Y = -841.184;
			Z = 328.589;
			Pitch = -5.26384;
			Roll = -2.14347e-007;
			Yaw = 132.615;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[183];
			Hash = 2475986526;
			X = -99.0448;
			Y = -838.912;
			Z = 328.589;
			Pitch = -5.26395;
			Roll = -2.14347e-007;
			Yaw = 128.175;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[184];
			Hash = 2475986526;
			X = -100.644;
			Y = -836.571;
			Z = 328.636;
			Pitch = -5.26398;
			Roll = -0;
			Yaw = 124.006;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[185];
			Hash = 2475986526;
			X = -102.435;
			Y = -833.952;
			Z = 328.506;
			Pitch = -5.26399;
			Roll = -0;
			Yaw = 118.502;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[186];
			Hash = 2475986526;
			X = -104.327;
			Y = -830.112;
			Z = 328.614;
			Pitch = -5.26391;
			Roll = -2.14347e-007;
			Yaw = 104.719;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[187];
			Hash = 2475986526;
			X = -105.28;
			Y = -826.029;
			Z = 328.734;
			Pitch = -5.26391;
			Roll = 2.14347e-007;
			Yaw = 101.615;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[188];
			Hash = 2475986526;
			X = -106.082;
			Y = -822.072;
			Z = 328.729;
			Pitch = -5.26387;
			Roll = -1.33967e-008;
			Yaw = 91.2972;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[189];
			Hash = 2475986526;
			X = -106.062;
			Y = -817.685;
			Z = 328.758;
			Pitch = -5.26388;
			Roll = 1.33967e-008;
			Yaw = 88.7458;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[190];
			Hash = 2475986526;
			X = -106.155;
			Y = -814.128;
			Z = 328.687;
			Pitch = -5.26388;
			Roll = -1.07174e-007;
			Yaw = 82.8157;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[191];
			Hash = 2475986526;
			X = -105.262;
			Y = -810.369;
			Z = 328.729;
			Pitch = -5.26384;
			Roll = 1.07174e-007;
			Yaw = 73.2414;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[192];
			Hash = 2475986526;
			X = -104.284;
			Y = -807.711;
			Z = 328.691;
			Pitch = -5.58488;
			Roll = -4.28923e-007;
			Yaw = 65.966;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[193];
			Hash = 2475986526;
			X = -101.884;
			Y = -802.718;
			Z = 328.706;
			Pitch = -5.5848;
			Roll = 2.14461e-007;
			Yaw = 60.3613;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[194];
			Hash = 2475986526;
			X = -97.9782;
			Y = -797.316;
			Z = 328.695;
			Pitch = -5.58488;
			Roll = 2.14461e-007;
			Yaw = 48.9171;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[195];
			Hash = 2475986526;
			X = -94.2322;
			Y = -793.73;
			Z = 328.669;
			Pitch = -5.58479;
			Roll = -2.14461e-007;
			Yaw = 37.4974;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[196];
			Hash = 2475986526;
			X = -90.9922;
			Y = -791.487;
			Z = 328.684;
			Pitch = -6.26149;
			Roll = -0;
			Yaw = 27.0819;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[197];
			Hash = 2475986526;
			X = -87.4651;
			Y = -789.98;
			Z = 328.647;
			Pitch = -5.63204;
			Roll = -0;
			Yaw = 20.2315;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[198];
			Hash = 2475986526;
			X = -80.5351;
			Y = -788.179;
			Z = 328.782;
			Pitch = -5.80051;
			Roll = -0;
			Yaw = 7.26539;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[199];
			Hash = 2475986526;
			X = -74.5572;
			Y = -787.022;
			Z = 329.08;
			Pitch = -4.61724;
			Roll = 5.35346e-008;
			Yaw = -10.7316;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[200];
			Hash = 2475986526;
			X = -75.3695;
			Y = -789.507;
			Z = 328.306;
			Pitch = -8.84722;
			Roll = -8.43803e-010;
			Yaw = -0.0879073;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[201];
			Hash = 2475986526;
			X = -68.6555;
			Y = -788.272;
			Z = 329.103;
			Pitch = -5.30654;
			Roll = 2.14362e-007;
			Yaw = -16.9146;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[202];
			Hash = 2475986526;
			X = -64.7324;
			Y = -789.882;
			Z = 329.081;
			Pitch = -4.987;
			Roll = -2.14254e-007;
			Yaw = -27.7917;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[203];
			Hash = 2475986526;
			X = -55.4375;
			Y = -794.682;
			Z = 329.045;
			Pitch = -5.32055;
			Roll = 2.14367e-007;
			Yaw = -37.3601;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[204];
			Hash = 2475986526;
			X = -52.041;
			Y = -798.134;
			Z = 329.001;
			Pitch = -5.31536;
			Roll = -2.14365e-007;
			Yaw = -49.2493;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[205];
			Hash = 2475986526;
			X = -49.0785;
			Y = -802.078;
			Z = 328.914;
			Pitch = -5.31539;
			Roll = 4.2873e-007;
			Yaw = -57.7224;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[206];
			Hash = 2475986526;
			X = -45.6154;
			Y = -809.566;
			Z = 328.95;
			Pitch = -5.25705;
			Roll = -1.07172e-007;
			Yaw = -72.2094;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[207];
			Hash = 2475986526;
			X = -45.2549;
			Y = -827.659;
			Z = 328.957;
			Pitch = -5.18353;
			Roll = -1.0716e-007;
			Yaw = -105.915;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[208];
			Hash = 2475986526;
			X = -47.1369;
			Y = -832.806;
			Z = 328.936;
			Pitch = -5.18352;
			Roll = 2.1432e-007;
			Yaw = -117.146;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[209];
			Hash = 2475986526;
			X = -49.9112;
			Y = -837.51;
			Z = 328.916;
			Pitch = -5.18352;
			Roll = -4.2864e-007;
			Yaw = -125.894;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[210];
			Hash = 2475986526;
			X = -53.6636;
			Y = -841.564;
			Z = 328.905;
			Pitch = -5.18348;
			Roll = -0;
			Yaw = -136.192;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[211];
			Hash = 2475986526;
			X = -60.2755;
			Y = -846.895;
			Z = 328.808;
			Pitch = -5.97307;
			Roll = -2.14609e-007;
			Yaw = -151.031;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[212];
			Hash = 2475986526;
			X = -64.6525;
			Y = -848.331;
			Z = 328.792;
			Pitch = -4.82267;
			Roll = -2.14202e-007;
			Yaw = -160.74;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[213];
			Hash = 2475986526;
			X = -70.4067;
			Y = -849.836;
			Z = 328.854;
			Pitch = -4.82287;
			Roll = -0;
			Yaw = -172.2;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[214];
			Hash = 2475986526;
			X = -76.7555;
			Y = -850.113;
			Z = 328.885;
			Pitch = -4.93224;
			Roll = 2.67796e-008;
			Yaw = 175.995;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[215];
			Hash = 2475986526;
			X = -81.9779;
			Y = -849.605;
			Z = 328.821;
			Pitch = -5.67769;
			Roll = 1.07248e-007;
			Yaw = 166.961;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[216];
			Hash = 2475986526;
			X = -87.5884;
			Y = -847.552;
			Z = 328.829;
			Pitch = -5.6777;
			Roll = 2.14496e-007;
			Yaw = 153.36;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[217];
			Hash = 2475986526;
			X = -92.1044;
			Y = -845.82;
			Z = 328.655;
			Pitch = -5.01307;
			Roll = -2.14263e-007;
			Yaw = 147.428;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[218];
			Hash = 2475986526;
			X = -90.0883;
			Y = -842.661;
			Z = 327.589;
			Pitch = -7.98782;
			Roll = -4.31069e-007;
			Yaw = 146.409;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[219];
			Hash = 2475986526;
			X = -95.4409;
			Y = -842.718;
			Z = 328.551;
			Pitch = -5.01006;
			Roll = -0;
			Yaw = 136.57;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[220];
			Hash = 2475986526;
			X = -103.536;
			Y = -831.932;
			Z = 328.513;
			Pitch = -5.42142;
			Roll = 2.14402e-007;
			Yaw = 111.099;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[221];
			Hash = 2475986526;
			X = -105.06;
			Y = -827.904;
			Z = 328.644;
			Pitch = -5.29978;
			Roll = 1.0718e-007;
			Yaw = 102.515;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[222];
			Hash = 2475986526;
			X = -105.911;
			Y = -823.815;
			Z = 328.7;
			Pitch = -5.52135;
			Roll = 5.36096e-008;
			Yaw = 99.4393;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[223];
			Hash = 2475986526;
			X = -106.154;
			Y = -819.723;
			Z = 328.716;
			Pitch = -5.25204;
			Roll = -0;
			Yaw = 90.1628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[224];
			Hash = 2475986526;
			X = -105.769;
			Y = -812.146;
			Z = 328.645;
			Pitch = -5.25205;
			Roll = -2.14343e-007;
			Yaw = 75.8091;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[225];
			Hash = 3291218330;
			X = -37.3907;
			Y = -848.122;
			Z = 327.717;
			Pitch = 0.0456718;
			Roll = 88.8805;
			Yaw = -18.5954;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[226];
			Hash = 3291218330;
			X = -26.1908;
			Y = -818.332;
			Z = 328.76;
			Pitch = 0.045655;
			Roll = 84.66;
			Yaw = -18.5954;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[227];
			Hash = 3291218330;
			X = -37.891;
			Y = -789.138;
			Z = 328.134;
			Pitch = 0.0456499;
			Roll = 87.6575;
			Yaw = 41.6028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[228];
			Hash = 3291218330;
			X = -63.492;
			Y = -772.044;
			Z = 327.866;
			Pitch = 0.0456535;
			Roll = 89.1569;
			Yaw = 41.6027;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[229];
			Hash = 3291218330;
			X = -93.4916;
			Y = -774.848;
			Z = 327.398;
			Pitch = 0.0456551;
			Roll = 89.0452;
			Yaw = 119.802;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[230];
			Hash = 3291218330;
			X = -115.991;
			Y = -795.259;
			Z = 327.27;
			Pitch = 0.045654;
			Roll = 89.2044;
			Yaw = 119.802;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[231];
			Hash = 3291218330;
			X = -122.551;
			Y = -825.074;
			Z = 327.213;
			Pitch = 0.0456593;
			Roll = 90.3928;
			Yaw = -169.099;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[232];
			Hash = 3291218330;
			X = -108.551;
			Y = -853.416;
			Z = 327.387;
			Pitch = 0.0456594;
			Roll = 89.1123;
			Yaw = -169.099;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[233];
			Hash = 3291218330;
			X = -80.2509;
			Y = -866.418;
			Z = 327.301;
			Pitch = 0.0456584;
			Roll = 89.3016;
			Yaw = 142.901;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[234];
			Hash = 3291218330;
			X = -55.8513;
			Y = -863.921;
			Z = 327.333;
			Pitch = 0.0456581;
			Roll = 89.6213;
			Yaw = 142.901;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[235];
			Hash = 118627012;
			X = -74.8438;
			Y = -819.617;
			Z = 323.685;
			Pitch = -0;
			Roll = -0;
			Yaw = -3.37511;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("Zyhn");

		}
		void mmf_city691()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdd9a1802;
			X = 173.831;
			Y = -806.272;
			Z = 30.3634;
			Pitch = -62.8002;
			Roll = -5.60348e-006;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdd9a1802;
			X = 172.332;
			Y = -810.465;
			Z = 32.5987;
			Pitch = -61.4634;
			Roll = -4.8254e-005;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdd9a1802;
			X = 170.248;
			Y = -816.021;
			Z = 35.8971;
			Pitch = -54.1072;
			Roll = -4.36884e-005;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdd9a1802;
			X = 168.105;
			Y = -821.404;
			Z = 39.9971;
			Pitch = -46.1988;
			Roll = -0;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdd9a1802;
			X = 167.448;
			Y = -826.063;
			Z = 44.8439;
			Pitch = -41.5992;
			Roll = -89.5478;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdd9a1802;
			X = 165.807;
			Y = -830.34;
			Z = 51.5459;
			Pitch = -26.9991;
			Roll = -89.5478;
			Yaw = 159.649;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdd9a1802;
			X = 162.54;
			Y = -823.933;
			Z = 45.473;
			Pitch = -33.1991;
			Roll = -85.3475;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdd9a1802;
			X = 160.136;
			Y = -827.668;
			Z = 52.1854;
			Pitch = -33.1991;
			Roll = -85.3475;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdd9a1802;
			X = 157.883;
			Y = -831.133;
			Z = 58.8374;
			Pitch = -29.1992;
			Roll = -85.3475;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdd9a1802;
			X = 131.606;
			Y = -869.958;
			Z = 109.627;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdd9a1802;
			X = 129.464;
			Y = -874.803;
			Z = 113.677;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdd9a1802;
			X = 127.203;
			Y = -879.768;
			Z = 117.849;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdd9a1802;
			X = 125.019;
			Y = -884.686;
			Z = 121.991;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xdd9a1802;
			X = 128.345;
			Y = -886.054;
			Z = 121.863;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xdd9a1802;
			X = 130.248;
			Y = -881.81;
			Z = 118.299;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xdd9a1802;
			X = 132.226;
			Y = -877.265;
			Z = 114.548;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdd9a1802;
			X = 134.011;
			Y = -872.338;
			Z = 110.487;
			Pitch = -52.3407;
			Roll = -90.5472;
			Yaw = 155.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdd9a1802;
			X = 127.072;
			Y = -889.645;
			Z = 124.633;
			Pitch = -65.4017;
			Roll = 2.19996;
			Yaw = 156.938;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdd9a1802;
			X = 124.984;
			Y = -896.32;
			Z = 127.075;
			Pitch = -74.8055;
			Roll = 90.3981;
			Yaw = 156.938;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0x8af58425;
			X = 116.013;
			Y = -905.442;
			Z = 126.356;
			Pitch = 2.57497;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0x8af58425;
			X = 96.3776;
			Y = -898.46;
			Z = 132.132;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0x8af58425;
			X = 77.6327;
			Y = -892.108;
			Z = 142.583;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0x8af58425;
			X = 58.7471;
			Y = -885.801;
			Z = 153.079;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0x8af58425;
			X = 39.9612;
			Y = -879.339;
			Z = 163.551;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0x8af58425;
			X = 21.2112;
			Y = -872.837;
			Z = 174.001;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0x8af58425;
			X = 2.45098;
			Y = -866.478;
			Z = 184.437;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0x8af58425;
			X = -16.2278;
			Y = -860.085;
			Z = 194.831;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0x8af58425;
			X = -33.6774;
			Y = -854.19;
			Z = 204.524;
			Pitch = 27.775;
			Roll = -179.075;
			Yaw = 71.3582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0x8af58425;
			X = -50.9596;
			Y = -844.484;
			Z = 211.272;
			Pitch = -0.0250624;
			Roll = -178.674;
			Yaw = -18.2426;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0x8af58425;
			X = -44.2562;
			Y = -824.163;
			Z = 215.2;
			Pitch = 19.975;
			Roll = -178.274;
			Yaw = -18.4423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0x8af58425;
			X = -37.8845;
			Y = -805.075;
			Z = 222.785;
			Pitch = 21.175;
			Roll = -178.274;
			Yaw = -18.4423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0x8af58425;
			X = -31.9013;
			Y = -787.013;
			Z = 230.158;
			Pitch = 21.175;
			Roll = -178.274;
			Yaw = -18.4423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0x8af58425;
			X = -25.3773;
			Y = -767.434;
			Z = 238.166;
			Pitch = 21.175;
			Roll = -178.274;
			Yaw = -18.4423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0x8af58425;
			X = -17.1481;
			Y = -742.878;
			Z = 248.162;
			Pitch = 21.175;
			Roll = -178.274;
			Yaw = -18.4423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0x8af58425;
			X = -7.04601;
			Y = -723.951;
			Z = 253.334;
			Pitch = 1.07097;
			Roll = -179.474;
			Yaw = 69.1569;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0x8af58425;
			X = 18.9526;
			Y = -733.825;
			Z = 257.839;
			Pitch = -19.3291;
			Roll = -179.474;
			Yaw = 69.1569;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0x8af58425;
			X = 46.3339;
			Y = -744.497;
			Z = 262.898;
			Pitch = -0.729083;
			Roll = -179.474;
			Yaw = 69.1569;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0x8af58425;
			X = 73.3067;
			Y = -754.753;
			Z = 263.337;
			Pitch = -0.729083;
			Roll = -179.474;
			Yaw = 69.1569;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0x8af58425;
			X = 97.4323;
			Y = -758.4;
			Z = 264.176;
			Pitch = -3.12907;
			Roll = -179.474;
			Yaw = 95.555;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0x8af58425;
			X = 63.0011;
			Y = -766.63;
			Z = 268.692;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0x8af58425;
			X = 39.1463;
			Y = -773.966;
			Z = 278.626;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0x8af58425;
			X = 13.4864;
			Y = -781.784;
			Z = 289.349;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0x8af58425;
			X = -34.7428;
			Y = -796.663;
			Z = 309.657;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0x8af58425;
			X = -11.1492;
			Y = -789.393;
			Z = 299.733;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0x8af58425;
			X = -78.4183;
			Y = -810.036;
			Z = 322.817;
			Pitch = 1.87088;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0x8af58425;
			X = -52.5345;
			Y = -802.124;
			Z = 317.042;
			Pitch = 21.8709;
			Roll = -179.474;
			Yaw = 107.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("mr Bean");
		}
		void mmf_eclipseTroll1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0x745f3383;
			X = -799.509;
			Y = 321.945;
			Z = 83.2365;
			Pitch = -89.5252;
			Roll = -0;
			Yaw = 147.716;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x745f3383;
			X = -796.812;
			Y = 323.744;
			Z = 91.0364;
			Pitch = 89.0126;
			Roll = 165.309;
			Yaw = 180;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0x745f3383;
			X = -824.01;
			Y = 266.744;
			Z = 81.6365;
			Pitch = -87.7342;
			Roll = -0;
			Yaw = -57.2958;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0x745f3383;
			X = -774.218;
			Y = 322.844;
			Z = 92.0364;
			Pitch = 89.5817;
			Roll = 180;
			Yaw = 165.676;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0x745f3383;
			X = -770.339;
			Y = 250.477;
			Z = 82.6458;
			Pitch = -89.5248;
			Roll = 8.03992e-007;
			Yaw = -10.743;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0x2413cee0;
			X = -735.716;
			Y = 282.664;
			Z = 83.7512;
			Pitch = -2.68443;
			Roll = 1.79246;
			Yaw = -87.6502;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0x2413cee0;
			X = -735.816;
			Y = 289.965;
			Z = 83.9512;
			Pitch = -2.68541;
			Roll = 0.896231;
			Yaw = -86.7969;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0x2413cee0;
			X = -736.017;
			Y = 297.265;
			Z = 84.1511;
			Pitch = -0.895247;
			Roll = -3.33546e-009;
			Yaw = -87.7342;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0x2413cee0;
			X = -797.308;
			Y = 261.564;
			Z = 83.1512;
			Pitch = 0;
			Roll = 0.895247;
			Yaw = -165.621;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0x2413cee0;
			X = -792.909;
			Y = 262.664;
			Z = 83.2512;
			Pitch = 0;
			Roll = 0.895247;
			Yaw = -165.621;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0x2413cee0;
			X = -835.511;
			Y = 311.265;
			Z = 83.7512;
			Pitch = 0;
			Roll = -0;
			Yaw = -150.401;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0x2413cee0;
			X = -842.11;
			Y = 307.765;
			Z = 83.7512;
			Pitch = 0;
			Roll = -0;
			Yaw = -151.297;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0x2413cee0;
			X = -848.816;
			Y = 303.764;
			Z = 83.7512;
			Pitch = 0;
			Roll = -0;
			Yaw = -151.297;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("R3ck17");
		}
		void mmf_MazeHalfPipes1()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdb69770d;
			X = -76.4792;
			Y = -809.083;
			Z = 325.029;
			Pitch = 0.600001;
			Roll = -4.819e-006;
			Yaw = -0.567961;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdb69770d;
			X = -76.3792;
			Y = -800.586;
			Z = 324.628;
			Pitch = -5.30001;
			Roll = -4.76281e-006;
			Yaw = -0.56796;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdb69770d;
			X = -76.329;
			Y = -791.41;
			Z = 323.429;
			Pitch = -8.9;
			Roll = -4.71922e-006;
			Yaw = -0.567959;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdb69770d;
			X = -76.249;
			Y = -782.312;
			Z = 321.67;
			Pitch = -11.81;
			Roll = -4.67465e-006;
			Yaw = -0.567957;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdb69770d;
			X = -76.1785;
			Y = -773.333;
			Z = 319.408;
			Pitch = -15.3102;
			Roll = -4.14932e-006;
			Yaw = -0.567951;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdb69770d;
			X = -76.0775;
			Y = -764.544;
			Z = 316.528;
			Pitch = -20.3204;
			Roll = -2.54637e-006;
			Yaw = -0.567938;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdb69770d;
			X = -75.9973;
			Y = -755.976;
			Z = 313.038;
			Pitch = -23.5905;
			Roll = -2.28541e-006;
			Yaw = -0.567933;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdb69770d;
			X = -75.9171;
			Y = -747.528;
			Z = 309.218;
			Pitch = -24.2005;
			Roll = -2.28159e-006;
			Yaw = -0.567932;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdb69770d;
			X = -75.8571;
			Y = -739.3;
			Z = 305.36;
			Pitch = -25.8806;
			Roll = -2.52064e-006;
			Yaw = -0.567929;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdb69770d;
			X = -74.8046;
			Y = -722.575;
			Z = 302.106;
			Pitch = -0.0703537;
			Roll = -0.600596;
			Yaw = -5.38472;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdb69770d;
			X = -75.5099;
			Y = -731.154;
			Z = 302.804;
			Pitch = -9.43054;
			Roll = -1.29127;
			Yaw = -4.26201;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdb69770d;
			X = -73.5645;
			Y = -714.103;
			Z = 302.106;
			Pitch = 0.229655;
			Roll = -0.80056;
			Yaw = -10.9645;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdb69770d;
			X = -71.7144;
			Y = -705.496;
			Z = 301.796;
			Pitch = -3.17035;
			Roll = -1.80054;
			Yaw = -12.0643;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xdb69770d;
			X = -70.1043;
			Y = -697.89;
			Z = 300.147;
			Pitch = -17.1704;
			Roll = -1.80054;
			Yaw = -12.0641;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xdb69770d;
			X = -66.4044;
			Y = -684.395;
			Z = 290.746;
			Pitch = 0.0295598;
			Roll = -1.80053;
			Yaw = -31.3637;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xdb69770d;
			X = -61.7049;
			Y = -678.007;
			Z = 290.747;
			Pitch = 0.529616;
			Roll = -1.50047;
			Yaw = -40.263;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdb69770d;
			X = -56.2352;
			Y = -672.648;
			Z = 290.747;
			Pitch = 0.529623;
			Roll = -1.50047;
			Yaw = -48.663;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdb69770d;
			X = -52.3064;
			Y = -669.803;
			Z = 290.587;
			Pitch = 0.429641;
			Roll = 0.399521;
			Yaw = -55.2216;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdb69770d;
			X = -45.9067;
			Y = -666.005;
			Z = 290.587;
			Pitch = 1.02964;
			Roll = 2.69951;
			Yaw = -63.5214;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xdb69770d;
			X = -38.9071;
			Y = -663.008;
			Z = 290.587;
			Pitch = 1.42965;
			Roll = 4.5995;
			Yaw = -69.921;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xdb69770d;
			X = -31.0073;
			Y = -660.916;
			Z = 290.828;
			Pitch = 2.09967;
			Roll = 4.79943;
			Yaw = -77.8201;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xdb69770d;
			X = -24.876;
			Y = -660.637;
			Z = 290.736;
			Pitch = -0.500334;
			Roll = 6.39932;
			Yaw = -89.417;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xdb69770d;
			X = -17.006;
			Y = -661.268;
			Z = 290.607;
			Pitch = -0.500336;
			Roll = 6.1993;
			Yaw = -99.1159;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xdb69770d;
			X = -10.2059;
			Y = -663.269;
			Z = 290.307;
			Pitch = -0.500337;
			Roll = 4.89926;
			Yaw = -108.113;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xdb69770d;
			X = -3.40595;
			Y = -666.47;
			Z = 290.217;
			Pitch = 0.499662;
			Roll = 3.29921;
			Yaw = -117.159;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xdb69770d;
			X = 2.22405;
			Y = -670.474;
			Z = 290.217;
			Pitch = 0.899669;
			Roll = 3.29915;
			Yaw = -127.681;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xdb69770d;
			X = 6.9241;
			Y = -675.181;
			Z = 290.217;
			Pitch = 0.899664;
			Roll = 3.29912;
			Yaw = -137.178;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xdb69770d;
			X = 17.3742;
			Y = -690.894;
			Z = 289.548;
			Pitch = 1.09966;
			Roll = 28.9987;
			Yaw = -163.573;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xdb69770d;
			X = 14.2842;
			Y = -682.244;
			Z = 289.298;
			Pitch = 1.42978;
			Roll = 27.6565;
			Yaw = -160.368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xdb69770d;
			X = 12.8842;
			Y = -674.347;
			Z = 290.198;
			Pitch = 0.729697;
			Roll = 36.7549;
			Yaw = -150.059;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xdb69770d;
			X = 19.3843;
			Y = -699.057;
			Z = 289.998;
			Pitch = 4.06968;
			Roll = 31.2034;
			Yaw = -171.653;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xdb69770d;
			X = 20.8843;
			Y = -708.062;
			Z = 290.598;
			Pitch = 4.06968;
			Roll = 31.2034;
			Yaw = -171.653;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xdb69770d;
			X = 22.3843;
			Y = -717.069;
			Z = 291.298;
			Pitch = 4.26968;
			Roll = 32.6027;
			Yaw = -171.653;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xdb69770d;
			X = 23.8843;
			Y = -726.175;
			Z = 292.098;
			Pitch = 4.26968;
			Roll = 34.3026;
			Yaw = -172.851;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xdb69770d;
			X = 24.9843;
			Y = -735.181;
			Z = 292.798;
			Pitch = 4.26968;
			Roll = 34.3026;
			Yaw = -172.851;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xdb69770d;
			X = 26.0843;
			Y = -744.287;
			Z = 293.498;
			Pitch = 4.26968;
			Roll = 34.3026;
			Yaw = -172.851;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xdb69770d;
			X = 27.2843;
			Y = -753.292;
			Z = 294.098;
			Pitch = 4.26968;
			Roll = 34.3026;
			Yaw = -172.851;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xdb69770d;
			X = 28.0843;
			Y = -762.498;
			Z = 294.498;
			Pitch = 3.16967;
			Roll = 34.3024;
			Yaw = -177.849;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xdb69770d;
			X = 28.2843;
			Y = -771.205;
			Z = 294.598;
			Pitch = 0.269656;
			Roll = 36.0023;
			Yaw = 178.552;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xdb69770d;
			X = 27.3843;
			Y = -780.311;
			Z = 294.398;
			Pitch = 1.46964;
			Roll = 33.5019;
			Yaw = 171.952;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xdb69770d;
			X = 25.3843;
			Y = -789.019;
			Z = 294.598;
			Pitch = 1.46964;
			Roll = 33.5019;
			Yaw = 163.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xdb69770d;
			X = 22.7843;
			Y = -796.125;
			Z = 294.598;
			Pitch = 1.46965;
			Roll = 33.5019;
			Yaw = 156.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xdb69770d;
			X = 18.9843;
			Y = -803.929;
			Z = 294.798;
			Pitch = 1.46966;
			Roll = 33.1018;
			Yaw = 150.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xdb69770d;
			X = 15.0843;
			Y = -809.837;
			Z = 294.898;
			Pitch = 1.46964;
			Roll = 33.1018;
			Yaw = 145.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xdb69770d;
			X = 10.0843;
			Y = -817.04;
			Z = 294.998;
			Pitch = 1.46964;
			Roll = 33.1018;
			Yaw = 145.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xdb69770d;
			X = 5.08435;
			Y = -824.443;
			Z = 295.398;
			Pitch = 1.46964;
			Roll = 33.1018;
			Yaw = 145.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xdb69770d;
			X = -0.315648;
			Y = -831.947;
			Z = 295.598;
			Pitch = 1.46965;
			Roll = 33.1018;
			Yaw = 144.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xdb69770d;
			X = -5.51565;
			Y = -838.85;
			Z = 295.798;
			Pitch = 1.46965;
			Roll = 33.1018;
			Yaw = 144.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xdb69770d;
			X = -10.8156;
			Y = -846.154;
			Z = 295.998;
			Pitch = 1.46965;
			Roll = 33.1018;
			Yaw = 144.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xdb69770d;
			X = -16.1156;
			Y = -853.661;
			Z = 295.998;
			Pitch = 1.46965;
			Roll = 33.1018;
			Yaw = 144.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xdb69770d;
			X = -20.9156;
			Y = -859.067;
			Z = 295.998;
			Pitch = 1.4696;
			Roll = 33.5012;
			Yaw = 135.45;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xdb69770d;
			X = -26.8156;
			Y = -864.074;
			Z = 296.098;
			Pitch = 2.06961;
			Roll = 33.5011;
			Yaw = 125.449;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xdb69770d;
			X = -31.2158;
			Y = -866.279;
			Z = 295.898;
			Pitch = 2.06963;
			Roll = 33.5011;
			Yaw = 112.048;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xdb69770d;
			X = -38.4165;
			Y = -868.789;
			Z = 296.198;
			Pitch = 2.06961;
			Roll = 35.3995;
			Yaw = 104.744;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xdb69770d;
			X = -46.1168;
			Y = -870.392;
			Z = 296.198;
			Pitch = 2.06961;
			Roll = 35.3995;
			Yaw = 98.2439;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xdb69770d;
			X = -54.3172;
			Y = -871.797;
			Z = 296.498;
			Pitch = 2.06962;
			Roll = 41.1978;
			Yaw = 94.3424;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xdb69770d;
			X = -62.6175;
			Y = -871.802;
			Z = 296.659;
			Pitch = 2.06962;
			Roll = 41.1978;
			Yaw = 85.742;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xdb69770d;
			X = -71.5763;
			Y = -871.663;
			Z = 297.259;
			Pitch = 2.06962;
			Roll = 45.697;
			Yaw = 85.742;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xdb69770d;
			X = -80.1746;
			Y = -871.09;
			Z = 297.74;
			Pitch = 2.47966;
			Roll = 54.1022;
			Yaw = 77.0416;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xdb69770d;
			X = -88.8744;
			Y = -868.396;
			Z = 297.84;
			Pitch = 2.47967;
			Roll = 50.9019;
			Yaw = 64.8408;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xdb69770d;
			X = -96.4743;
			Y = -864.202;
			Z = 297.84;
			Pitch = 2.47967;
			Roll = 51.5013;
			Yaw = 51.2396;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xdb69770d;
			X = -102.174;
			Y = -858.707;
			Z = 297.84;
			Pitch = 2.47967;
			Roll = 51.5011;
			Yaw = 38.7389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xdb69770d;
			X = -107.874;
			Y = -852.011;
			Z = 298.04;
			Pitch = 2.47967;
			Roll = 51.5011;
			Yaw = 38.7389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xdb69770d;
			X = -112.174;
			Y = -845.218;
			Z = 298.24;
			Pitch = 2.47961;
			Roll = 51.4003;
			Yaw = 23.438;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xdb69770d;
			X = -114.974;
			Y = -836.738;
			Z = 298.34;
			Pitch = 2.47963;
			Roll = 48.6971;
			Yaw = 15.5377;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xdb69770d;
			X = -116.974;
			Y = -827.342;
			Z = 298.34;
			Pitch = 2.47963;
			Roll = 48.697;
			Yaw = 0.237586;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xdb69770d;
			X = -116.774;
			Y = -818.547;
			Z = 298.24;
			Pitch = 2.47964;
			Roll = 48.697;
			Yaw = -14.3623;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 0xdb69770d;
			X = -114.274;
			Y = -810.355;
			Z = 298.14;
			Pitch = 3.37971;
			Roll = 42.3938;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xdb69770d;
			X = -109.474;
			Y = -800.263;
			Z = 295.84;
			Pitch = 3.37972;
			Roll = 21.7945;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xdb69770d;
			X = -106.474;
			Y = -792.567;
			Z = 295.84;
			Pitch = 3.37972;
			Roll = 16.3943;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xdb69770d;
			X = -103.174;
			Y = -783.87;
			Z = 295.84;
			Pitch = 3.37971;
			Roll = 12.7943;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xdb69770d;
			X = -99.4743;
			Y = -775.272;
			Z = 295.891;
			Pitch = 2.67971;
			Roll = 7.09425;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xdb69770d;
			X = -95.9743;
			Y = -766.775;
			Z = 295.891;
			Pitch = 2.67972;
			Roll = 2.49423;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xdb69770d;
			X = -92.8744;
			Y = -758.18;
			Z = 295.991;
			Pitch = 0.579712;
			Roll = 1.89422;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xdb69770d;
			X = -89.7744;
			Y = -750.183;
			Z = 295.871;
			Pitch = -0.120288;
			Roll = 1.89422;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xdb69770d;
			X = -86.7745;
			Y = -741.887;
			Z = 295.671;
			Pitch = -1.62029;
			Roll = 1.89421;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xdb69770d;
			X = -83.6745;
			Y = -733.19;
			Z = 294.871;
			Pitch = -5.92029;
			Roll = 1.8942;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xdb69770d;
			X = -80.8746;
			Y = -725.494;
			Z = 293.971;
			Pitch = -6.02029;
			Roll = 1.8942;
			Yaw = -20.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xdb69770d;
			X = -77.6746;
			Y = -716.798;
			Z = 292.771;
			Pitch = -6.0203;
			Roll = 1.8942;
			Yaw = -18.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xdb69770d;
			X = -74.9747;
			Y = -708.101;
			Z = 291.771;
			Pitch = -6.0203;
			Roll = 1.8942;
			Yaw = -18.162;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xdb69770d;
			X = -71.9747;
			Y = -699.005;
			Z = 290.871;
			Pitch = -1.52031;
			Roll = 1.8942;
			Yaw = -17.6619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xdb69770d;
			X = -69.7747;
			Y = -692.109;
			Z = 290.871;
			Pitch = 1.67968;
			Roll = 3.29414;
			Yaw = -18.8614;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0x6f5592c2;
			X = -83.4186;
			Y = -814.729;
			Z = 325.051;
			Pitch = -5.95437;
			Roll = -0;
			Yaw = 66.876;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0x6f5592c2;
			X = -84.0165;
			Y = -815.896;
			Z = 325.027;
			Pitch = -4.73181;
			Roll = -2.14173e-007;
			Yaw = 77.2514;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0x6f5592c2;
			X = -84.2659;
			Y = -817.118;
			Z = 325.044;
			Pitch = -4.73184;
			Roll = -2.67717e-008;
			Yaw = 87.5291;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0x6f5592c2;
			X = -84.3204;
			Y = -818.426;
			Z = 325.041;
			Pitch = -4.73188;
			Roll = -4.01575e-008;
			Yaw = 92.2071;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0x6f5592c2;
			X = -84.3588;
			Y = -819.697;
			Z = 325.041;
			Pitch = -4.73188;
			Roll = -0;
			Yaw = 99.6728;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0x6f5592c2;
			X = -84.256;
			Y = -820.95;
			Z = 325.025;
			Pitch = -4.7319;
			Roll = -0;
			Yaw = 104.112;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0x6f5592c2;
			X = -83.9906;
			Y = -822.066;
			Z = 325.017;
			Pitch = -4.73199;
			Roll = -0;
			Yaw = 110.567;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 0x6f5592c2;
			X = -83.5165;
			Y = -823.239;
			Z = 325.008;
			Pitch = -4.73198;
			Roll = -2.14173e-007;
			Yaw = 118.047;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 0x6f5592c2;
			X = -82.7856;
			Y = -824.317;
			Z = 325.008;
			Pitch = -4.73194;
			Roll = -0;
			Yaw = 129.694;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0x6f5592c2;
			X = -81.9082;
			Y = -825.226;
			Z = 325.004;
			Pitch = -4.73196;
			Roll = -0;
			Yaw = 138.198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0x6f5592c2;
			X = -80.902;
			Y = -826.11;
			Z = 325.005;
			Pitch = -4.73201;
			Roll = -2.14173e-007;
			Yaw = 147.491;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0x6f5592c2;
			X = -79.8088;
			Y = -826.882;
			Z = 325.023;
			Pitch = -4.73195;
			Roll = 2.14173e-007;
			Yaw = 154.142;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0x6f5592c2;
			X = -78.4603;
			Y = -827.375;
			Z = 325.03;
			Pitch = -4.73205;
			Roll = -0;
			Yaw = 163.382;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0x6f5592c2;
			X = -77.1067;
			Y = -827.752;
			Z = 325.03;
			Pitch = -4.73204;
			Roll = 1.07087e-007;
			Yaw = 168.42;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0x6f5592c2;
			X = -75.8202;
			Y = -827.756;
			Z = 325.061;
			Pitch = -4.73192;
			Roll = -1.33858e-008;
			Yaw = 178.535;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0x6f5592c2;
			X = -74.2363;
			Y = -827.424;
			Z = 325.07;
			Pitch = -5.59052;
			Roll = -2.68079e-008;
			Yaw = 2.93539;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0x6f5592c2;
			X = -72.9699;
			Y = -827.227;
			Z = 325.07;
			Pitch = -5.59045;
			Roll = -0;
			Yaw = 21.5742;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0x6f5592c2;
			X = -71.7793;
			Y = -826.666;
			Z = 325.07;
			Pitch = -2.43242;
			Roll = -2.13636e-007;
			Yaw = 30.6121;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0x6f5592c2;
			X = -70.7414;
			Y = -825.863;
			Z = 325.07;
			Pitch = -2.43231;
			Roll = 1.06818e-007;
			Yaw = 43.739;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0x6f5592c2;
			X = -69.7471;
			Y = -824.968;
			Z = 325.074;
			Pitch = -2.91772;
			Roll = -0;
			Yaw = 50.2053;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0x6f5592c2;
			X = -68.9131;
			Y = -823.914;
			Z = 325.076;
			Pitch = -2.65717;
			Roll = -1.06837e-007;
			Yaw = 57.3722;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0x6f5592c2;
			X = -68.1803;
			Y = -822.756;
			Z = 325.076;
			Pitch = -2.65719;
			Roll = -0;
			Yaw = 61.2724;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0x6f5592c2;
			X = -67.6377;
			Y = -821.57;
			Z = 325.076;
			Pitch = -2.65718;
			Roll = 1.06837e-007;
			Yaw = 72.9882;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0x6f5592c2;
			X = -67.2329;
			Y = -820.218;
			Z = 325.076;
			Pitch = -2.65722;
			Roll = -1.06837e-007;
			Yaw = 76.8139;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0x6f5592c2;
			X = -67.0068;
			Y = -819.007;
			Z = 325.076;
			Pitch = -2.65728;
			Roll = -1.33546e-008;
			Yaw = 85.3861;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0x6f5592c2;
			X = -66.9395;
			Y = -817.762;
			Z = 325.076;
			Pitch = -2.65727;
			Roll = -1.66932e-009;
			Yaw = 89.8377;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0x6f5592c2;
			X = -67.085;
			Y = -816.491;
			Z = 325.075;
			Pitch = -2.65718;
			Roll = -0;
			Yaw = 107.709;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0x6f5592c2;
			X = -67.6282;
			Y = -815.412;
			Z = 325.07;
			Pitch = -2.65716;
			Roll = -0;
			Yaw = 116.786;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0x6f5592c2;
			X = -68.2846;
			Y = -814.502;
			Z = 325.064;
			Pitch = -2.65728;
			Roll = -2.13673e-007;
			Yaw = 125.335;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0x753da1b5;
			X = -77.1757;
			Y = -810.013;
			Z = 330.475;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.25775;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0x9352dddf;
			X = -76.5091;
			Y = -809.96;
			Z = 330.467;
			Pitch = -0;
			Roll = -0;
			Yaw = -0.639378;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0x6adc3709;
			X = -68.7416;
			Y = -814.165;
			Z = 326.175;
			Pitch = 0;
			Roll = 0;
			Yaw = -47.04;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0x6adc3709;
			X = -83.4414;
			Y = -814.067;
			Z = 326.175;
			Pitch = 0;
			Roll = 0;
			Yaw = 43.96;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			/*Hash = 0x2b3ad141;
			X = -73.1119;
			Y = -813.716;
			Z = 325.032;
			Pitch = 0;
			Roll = -0;
			Yaw = -0.862971;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);*/

			//[119];
			Hash = 0x48aa9b6e;
			X = -68.1247;
			Y = -813.885;
			Z = 329.276;
			Pitch = 0;
			Roll = 0;
			Yaw = -1.83755;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 0x48aa9b6e;
			X = -85.2244;
			Y = -813.686;
			Z = 329.276;
			Pitch = 0;
			Roll = 0;
			Yaw = -1.83755;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 0xd4729f50;
			X = -68.8997;
			Y = -810.019;
			Z = 326.788;
			Pitch = 0;
			Roll = 0;
			Yaw = -2.15312;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 0x8d41c8bd;
			X = -68.0701;
			Y = -813.919;
			Z = 328.91;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.84837;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 0x1ea37333;
			X = -85.2688;
			Y = -813.677;
			Z = 329.041;
			Pitch = 0;
			Roll = 0;
			Yaw = 0.631643;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 0x997021a9;
			X = -76.0838;
			Y = -819.552;
			Z = 330.359;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.41037;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 0x997021a9;
			X = -76.0838;
			Y = -819.552;
			Z = 330.359;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.41037;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 0x997021a9;
			X = -76.0838;
			Y = -819.552;
			Z = 330.359;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.41037;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 0x997021a9;
			X = -76.0838;
			Y = -819.552;
			Z = 330.359;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.41037;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 0x997021a9;
			X = -76.0838;
			Y = -819.552;
			Z = 330.359;
			Pitch = 0;
			Roll = 0;
			Yaw = 9.41037;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 0x426f46e;
			X = -60.9298;
			Y = -818.849;
			Z = 320.999;
			Pitch = 0;
			Roll = 0;
			Yaw = 85.8291;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 0x7d96d65f;
			X = -59.4802;
			Y = -816.283;
			Z = 319.099;
			Pitch = 27.5392;
			Roll = -2.28682e-006;
			Yaw = 88.5152;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 0xdf8c1fd4;
			X = -85.798;
			Y = -814.783;
			Z = 324.027;
			Pitch = -4.22433;
			Roll = -0;
			Yaw = -25.302;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 0xdf8c1fd4;
			X = -86.8413;
			Y = -818.378;
			Z = 324.029;
			Pitch = -5.00984;
			Roll = -1.33914e-008;
			Yaw = -87.8302;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 0xdf8c1fd4;
			X = -85.7438;
			Y = -823.086;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 5.34648e-007;
			Yaw = -61.7321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 0xdf8c1fd4;
			X = -83.4439;
			Y = -827.289;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 5.34648e-007;
			Yaw = -61.7321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];
			Hash = 0xdf8c1fd4;
			X = -80.1439;
			Y = -829.39;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 5.34648e-007;
			Yaw = -61.7321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[136];
			Hash = 0xdf8c1fd4;
			X = -75.744;
			Y = -829.891;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 5.34648e-007;
			Yaw = -61.7321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 0xdf8c1fd4;
			X = -71.1441;
			Y = -829.493;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 1.0693e-007;
			Yaw = -121.731;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 0xdf8c1fd4;
			X = -67.5441;
			Y = -827.194;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -0;
			Yaw = -121.731;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[139];
			Hash = 0xdf8c1fd4;
			X = -64.8441;
			Y = -823.696;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -2.91383e-006;
			Yaw = -94.0298;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[140];
			Hash = 0xdf8c1fd4;
			X = -63.0442;
			Y = -820.597;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -8.55437e-007;
			Yaw = -69.8289;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[141];
			Hash = 0xdf8c1fd4;
			X = -63.9443;
			Y = -815.999;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -6.41578e-007;
			Yaw = -45.2284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[142];
			Hash = 0xdf8c1fd4;
			X = -66.1444;
			Y = -813.199;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -6.41578e-007;
			Yaw = -45.2284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[143];
			Hash = 0xdf8c1fd4;
			X = -67.0443;
			Y = -831.208;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -7.48507e-007;
			Yaw = -45.2284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[144];
			Hash = 0xdf8c1fd4;
			X = -70.7443;
			Y = -833.711;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -7.48507e-007;
			Yaw = -45.2284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[145];
			Hash = 0xdf8c1fd4;
			X = -75.5442;
			Y = -833.711;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -7.48507e-007;
			Yaw = -45.2284;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[146];
			Hash = 0xdf8c1fd4;
			X = -80.9441;
			Y = -833.611;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -1.92473e-006;
			Yaw = -39.3283;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[147];
			Hash = 0xdf8c1fd4;
			X = -85.6441;
			Y = -832.313;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = -1.49701e-006;
			Yaw = 13.6718;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[148];
			Hash = 0xdf8c1fd4;
			X = -88.444;
			Y = -828.216;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 6.41578e-007;
			Yaw = -38.1282;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[149];
			Hash = 0xdf8c1fd4;
			X = -89.744;
			Y = -823.018;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 6.41578e-007;
			Yaw = -38.1282;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[150];
			Hash = 0xdf8c1fd4;
			X = -91.244;
			Y = -818.219;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 5.34648e-007;
			Yaw = -38.1282;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[151];
			Hash = 0xdf8c1fd4;
			X = -90.344;
			Y = -813.021;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 8.55437e-007;
			Yaw = -75.128;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[152];
			Hash = 0xdf8c1fd4;
			X = -63.144;
			Y = -828.823;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 1.39008e-006;
			Yaw = -74.0268;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[153];
			Hash = 0xdf8c1fd4;
			X = -60.5441;
			Y = -824.825;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 1.49701e-006;
			Yaw = -74.0268;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[154];
			Hash = 0xdf8c1fd4;
			X = -58.5443;
			Y = -820.127;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 2.03166e-006;
			Yaw = -47.0266;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[155];
			Hash = 0xdf8c1fd4;
			X = -60.6444;
			Y = -812.83;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 2.03166e-006;
			Yaw = -47.0266;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[156];
			Hash = 0xdf8c1fd4;
			X = -63.7446;
			Y = -809.633;
			Z = 324.138;
			Pitch = -3.57369;
			Roll = 2.03166e-006;
			Yaw = -47.0266;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[157];
			Hash = 0xf246f3d4;
			X = -78.8832;
			Y = -830.892;
			Z = 329.484;
			Pitch = -0;
			Roll = -0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[158];
			Hash = 0xf246f3d4;
			X = -73.9833;
			Y = -830.892;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[159];
			Hash = 0xf246f3d4;
			X = -68.9834;
			Y = -831.099;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[160];
			Hash = 0xf246f3d4;
			X = -65.8834;
			Y = -829.402;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[161];
			Hash = 0xf246f3d4;
			X = -61.3835;
			Y = -823.106;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[162];
			Hash = 0xf246f3d4;
			X = -61.3835;
			Y = -823.106;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[163];
			Hash = 0xf246f3d4;
			X = -61.6836;
			Y = -812.509;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[164];
			Hash = 0xf246f3d4;
			X = -61.6836;
			Y = -812.509;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[165];
			Hash = 0xf246f3d4;
			X = -88.6836;
			Y = -814.212;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[166];
			Hash = 0xf246f3d4;
			X = -90.8835;
			Y = -819.519;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[167];
			Hash = 0xf246f3d4;
			X = -90.8835;
			Y = -819.519;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[168];
			Hash = 0xf246f3d4;
			X = -84.6836;
			Y = -827.124;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[169];
			Hash = 0xf246f3d4;
			X = -82.9837;
			Y = -830.426;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[170];
			Hash = 0xf246f3d4;
			X = -82.9837;
			Y = -830.426;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[171];
			Hash = 0xf246f3d4;
			X = -82.9837;
			Y = -830.426;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[172];
			Hash = 0xf246f3d4;
			X = -83.2837;
			Y = -810.233;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[173];
			Hash = 0xf246f3d4;
			X = -70.0839;
			Y = -810.233;
			Z = 329.484;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.5086;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);


			HaxBy("Zynh");
		}
		void mmf_MazeBankSpiral()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdb69770d;
			X = -78.4652;
			Y = -808.468;
			Z = 325.4;
			Pitch = 6.25703;
			Roll = 1.77989;
			Yaw = 8.92798;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdb69770d;
			X = -79.0448;
			Y = -803.994;
			Z = 326.049;
			Pitch = 10.5772;
			Roll = 5.26975;
			Yaw = -0.200697;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdb69770d;
			X = -76.6275;
			Y = -790.094;
			Z = 322.003;
			Pitch = -22.3938;
			Roll = 15.2996;
			Yaw = -33.6353;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdb69770d;
			X = -72.7276;
			Y = -784.293;
			Z = 318.903;
			Pitch = -22.3939;
			Roll = 16.0996;
			Yaw = -38.635;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdb69770d;
			X = -65.7476;
			Y = -777.1;
			Z = 315.203;
			Pitch = -21.0537;
			Roll = 25.7986;
			Yaw = -60.4345;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdb69770d;
			X = -72.5276;
			Y = -781.403;
			Z = 318.403;
			Pitch = -22.3938;
			Roll = 22.2984;
			Yaw = -60.4344;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdb69770d;
			X = -60.8278;
			Y = -775.108;
			Z = 313.203;
			Pitch = -13.7937;
			Roll = 26.2978;
			Yaw = -94.7321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdb69770d;
			X = -53.3281;
			Y = -776.011;
			Z = 311.563;
			Pitch = -11.5937;
			Roll = 28.2976;
			Yaw = -108.831;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdb69770d;
			X = -47.1284;
			Y = -778.436;
			Z = 310.253;
			Pitch = -11.5936;
			Roll = 33.1973;
			Yaw = -130.999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdb69770d;
			X = -42.3287;
			Y = -783.34;
			Z = 309.253;
			Pitch = -11.5936;
			Roll = 33.1973;
			Yaw = -153.494;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdb69770d;
			X = -38.9691;
			Y = -790.847;
			Z = 307.353;
			Pitch = -11.5936;
			Roll = 33.9972;
			Yaw = -162.592;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdb69770d;
			X = -37.0794;
			Y = -798.453;
			Z = 305.623;
			Pitch = -11.5936;
			Roll = 36.1467;
			Yaw = -176.09;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdb69770d;
			X = -36.9796;
			Y = -806.657;
			Z = 304.063;
			Pitch = -11.5936;
			Roll = 36.1465;
			Yaw = 172.811;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xdb69770d;
			X = -37.9797;
			Y = -815.061;
			Z = 302.363;
			Pitch = -11.5936;
			Roll = 36.1465;
			Yaw = 172.811;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xdb69770d;
			X = -39.65;
			Y = -822.667;
			Z = 300.794;
			Pitch = -11.5936;
			Roll = 36.1465;
			Yaw = 158.61;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xdb69770d;
			X = -42.9404;
			Y = -830.644;
			Z = 298.875;
			Pitch = -11.5936;
			Roll = 36.5465;
			Yaw = 152.91;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdb69770d;
			X = -47.1909;
			Y = -837.428;
			Z = 297.237;
			Pitch = -11.5937;
			Roll = 36.1456;
			Yaw = 140.21;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdb69770d;
			X = -52.6615;
			Y = -843.671;
			Z = 295.729;
			Pitch = -11.5936;
			Roll = 36.6249;
			Yaw = 132.409;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdb69770d;
			X = -58.2717;
			Y = -847.778;
			Z = 294.429;
			Pitch = -11.5936;
			Roll = 36.6248;
			Yaw = 114.808;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xdb69770d;
			X = -65.6016;
			Y = -850.375;
			Z = 292.949;
			Pitch = -11.5936;
			Roll = 36.6247;
			Yaw = 98.5066;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xdb69770d;
			X = -73.3015;
			Y = -850.778;
			Z = 291.419;
			Pitch = -11.5935;
			Roll = 36.5343;
			Yaw = 82.8058;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xdb69770d;
			X = -80.9302;
			Y = -849.091;
			Z = 289.921;
			Pitch = -11.5935;
			Roll = 36.5443;
			Yaw = 66.8052;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xdb69770d;
			X = -88.2899;
			Y = -845.413;
			Z = 288.292;
			Pitch = -11.5935;
			Roll = 36.5441;
			Yaw = 56.8046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xdb69770d;
			X = -95.1693;
			Y = -840.678;
			Z = 286.753;
			Pitch = -11.5934;
			Roll = 37.4325;
			Yaw = 48.3431;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xdb69770d;
			X = -101.919;
			Y = -834.701;
			Z = 284.963;
			Pitch = -11.5934;
			Roll = 38.0324;
			Yaw = 46.4429;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xdb69770d;
			X = -106.837;
			Y = -829.087;
			Z = 283.487;
			Pitch = -11.8534;
			Roll = 38.0322;
			Yaw = 30.6315;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xdb69770d;
			X = -109.457;
			Y = -822.764;
			Z = 282.257;
			Pitch = -11.8534;
			Roll = 38.032;
			Yaw = 4.73092;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xdb69770d;
			X = -109.595;
			Y = -814.768;
			Z = 280.557;
			Pitch = -11.8534;
			Roll = 39.7319;
			Yaw = -9.46904;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xdb69770d;
			X = -107.595;
			Y = -807.103;
			Z = 278.948;
			Pitch = -11.8534;
			Roll = 39.7317;
			Yaw = -24.4689;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xdb69770d;
			X = -103.844;
			Y = -799.818;
			Z = 277.249;
			Pitch = -11.8534;
			Roll = 41.3316;
			Yaw = -35.2688;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xdb69770d;
			X = -98.764;
			Y = -793.763;
			Z = 275.448;
			Pitch = -11.8534;
			Roll = 41.3316;
			Yaw = -49.7687;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xdb69770d;
			X = -92.4133;
			Y = -789.136;
			Z = 273.96;
			Pitch = -11.8534;
			Roll = 42.7315;
			Yaw = -65.2684;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xdb69770d;
			X = -85.3432;
			Y = -786.681;
			Z = 272.58;
			Pitch = -11.8534;
			Roll = 42.7314;
			Yaw = -82.2673;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xdb69770d;
			X = -76.9031;
			Y = -785.943;
			Z = 270.831;
			Pitch = -11.8534;
			Roll = 42.7314;
			Yaw = -90.1665;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xdb69770d;
			X = -68.973;
			Y = -786.634;
			Z = 269.251;
			Pitch = -11.8534;
			Roll = 43.4512;
			Yaw = -104.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xdb69770d;
			X = -61.6433;
			Y = -789.186;
			Z = 267.802;
			Pitch = -11.8534;
			Roll = 43.4512;
			Yaw = -118.563;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xdb69770d;
			X = -54.7435;
			Y = -793.61;
			Z = 266.122;
			Pitch = -11.8534;
			Roll = 43.4512;
			Yaw = -130.36;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xdb69770d;
			X = -48.9437;
			Y = -799.353;
			Z = 264.432;
			Pitch = -11.8534;
			Roll = 43.4512;
			Yaw = -142.558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xdb69770d;
			X = -44.784;
			Y = -806.06;
			Z = 262.812;
			Pitch = -11.8534;
			Roll = 43.4512;
			Yaw = -158.255;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xdb69770d;
			X = -42.3243;
			Y = -813.914;
			Z = 261.142;
			Pitch = -11.8535;
			Roll = 43.4511;
			Yaw = -171.053;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xdb69770d;
			X = -41.8348;
			Y = -821.86;
			Z = 259.483;
			Pitch = -11.8534;
			Roll = 43.4511;
			Yaw = 173.249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xdb69770d;
			X = -43.425;
			Y = -829.936;
			Z = 257.813;
			Pitch = -11.8534;
			Roll = 43.4511;
			Yaw = 159.948;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xdb69770d;
			X = -46.6754;
			Y = -837.662;
			Z = 256.064;
			Pitch = -11.8534;
			Roll = 43.851;
			Yaw = 151.248;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xdb69770d;
			X = -51.0458;
			Y = -844.669;
			Z = 254.245;
			Pitch = -12.5534;
			Roll = 43.8509;
			Yaw = 142.148;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xdb69770d;
			X = -56.4861;
			Y = -850.534;
			Z = 252.545;
			Pitch = -12.5533;
			Roll = 43.8509;
			Yaw = 127.247;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xdb69770d;
			X = -63.0865;
			Y = -854.638;
			Z = 250.905;
			Pitch = -12.9533;
			Roll = 43.8509;
			Yaw = 110.846;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xdb69770d;
			X = -70.8564;
			Y = -856.943;
			Z = 249.106;
			Pitch = -12.9533;
			Roll = 43.8509;
			Yaw = 97.7448;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xdb69770d;
			X = -78.9059;
			Y = -857.436;
			Z = 247.346;
			Pitch = -12.9533;
			Roll = 43.8509;
			Yaw = 84.8441;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xdb69770d;
			X = -87.0057;
			Y = -856.139;
			Z = 245.466;
			Pitch = -12.9533;
			Roll = 43.8508;
			Yaw = 73.3436;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xdb69770d;
			X = -94.8152;
			Y = -853.371;
			Z = 243.586;
			Pitch = -12.9533;
			Roll = 45.1506;
			Yaw = 62.243;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xdb69770d;
			X = -101.745;
			Y = -849.047;
			Z = 241.776;
			Pitch = -12.9532;
			Roll = 45.1505;
			Yaw = 49.5423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xdb69770d;
			X = -107.535;
			Y = -843.351;
			Z = 239.887;
			Pitch = -13.3832;
			Roll = 45.6401;
			Yaw = 36.3414;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xdb69770d;
			X = -111.904;
			Y = -836.406;
			Z = 237.937;
			Pitch = -13.3832;
			Roll = 45.64;
			Yaw = 23.9411;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xdb69770d;
			X = -114.904;
			Y = -828.61;
			Z = 236.117;
			Pitch = -13.3832;
			Roll = 46.14;
			Yaw = 12.9409;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xdb69770d;
			X = -116.274;
			Y = -820.476;
			Z = 234.207;
			Pitch = -13.3832;
			Roll = 47.0093;
			Yaw = 0.740853;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xdb69770d;
			X = -115.924;
			Y = -812.112;
			Z = 232.267;
			Pitch = -13.3832;
			Roll = 47.8091;
			Yaw = -10.4591;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xdb69770d;
			X = -114.083;
			Y = -803.888;
			Z = 230.348;
			Pitch = -13.3832;
			Roll = 49.6088;
			Yaw = -20.6589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xdb69770d;
			X = -110.633;
			Y = -796.543;
			Z = 228.548;
			Pitch = -13.3832;
			Roll = 50.4085;
			Yaw = -36.3587;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xdb69770d;
			X = -105.353;
			Y = -790.546;
			Z = 226.908;
			Pitch = -13.3831;
			Roll = 51.5083;
			Yaw = -54.1585;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xdb69770d;
			X = -98.3232;
			Y = -785.981;
			Z = 225.038;
			Pitch = -13.3831;
			Roll = 52.5081;
			Yaw = -64.7582;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xdb69770d;
			X = -90.5732;
			Y = -782.956;
			Z = 223.088;
			Pitch = -13.3831;
			Roll = 52.5078;
			Yaw = -76.0572;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xdb69770d;
			X = -82.2632;
			Y = -781.368;
			Z = 221.129;
			Pitch = -13.3831;
			Roll = 52.5078;
			Yaw = -85.2564;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xdb69770d;
			X = -73.7633;
			Y = -781.102;
			Z = 219.129;
			Pitch = -13.3831;
			Roll = 52.5074;
			Yaw = -93.9552;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xdb69770d;
			X = -65.3732;
			Y = -782.186;
			Z = 217.25;
			Pitch = -13.3831;
			Roll = 52.5073;
			Yaw = -104.554;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xdb69770d;
			X = -57.7137;
			Y = -784.958;
			Z = 215.47;
			Pitch = -13.3831;
			Roll = 52.5072;
			Yaw = -120.852;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xdb69770d;
			X = -50.614;
			Y = -789.693;
			Z = 213.48;
			Pitch = -13.3831;
			Roll = 52.507;
			Yaw = -129.252;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xdb69770d;
			X = -44.4263;
			Y = -795.386;
			Z = 211.54;
			Pitch = -13.3831;
			Roll = 52.5069;
			Yaw = -138.95;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 0xdb69770d;
			X = -39.7467;
			Y = -802.002;
			Z = 209.741;
			Pitch = -13.3831;
			Roll = 52.5066;
			Yaw = -156.646;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xdb69770d;
			X = -36.8271;
			Y = -810.015;
			Z = 207.81;
			Pitch = -13.3831;
			Roll = 52.5064;
			Yaw = -166.944;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xdb69770d;
			X = -35.6075;
			Y = -818.12;
			Z = 206.05;
			Pitch = -13.3831;
			Roll = 53.2251;
			Yaw = 177.959;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xdb69770d;
			X = -36.4288;
			Y = -826.596;
			Z = 204.101;
			Pitch = -13.3831;
			Roll = 53.2248;
			Yaw = 167.458;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xdb69770d;
			X = -38.7101;
			Y = -834.643;
			Z = 202.2;
			Pitch = -13.3831;
			Roll = 54.9245;
			Yaw = 154.558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xdb69770d;
			X = -42.8505;
			Y = -841.859;
			Z = 200.3;
			Pitch = -13.3831;
			Roll = 55.5241;
			Yaw = 140.158;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xdb69770d;
			X = -48.6409;
			Y = -848.033;
			Z = 198.44;
			Pitch = -13.3831;
			Roll = 56.2239;
			Yaw = 128.558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xdb69770d;
			X = -55.6412;
			Y = -852.858;
			Z = 196.471;
			Pitch = -13.3831;
			Roll = 56.2237;
			Yaw = 116.957;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xdb69770d;
			X = -63.4615;
			Y = -856.141;
			Z = 194.521;
			Pitch = -13.3831;
			Roll = 56.2233;
			Yaw = 104.655;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xdb69770d;
			X = -71.9107;
			Y = -857.894;
			Z = 192.49;
			Pitch = -13.3831;
			Roll = 56.7228;
			Yaw = 94.9544;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xdb69770d;
			X = -80.2302;
			Y = -857.814;
			Z = 190.64;
			Pitch = -13.3831;
			Roll = 56.7224;
			Yaw = 78.4537;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xdb69770d;
			X = -88.5596;
			Y = -855.746;
			Z = 188.7;
			Pitch = -13.3831;
			Roll = 58.4222;
			Yaw = 68.2533;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xdb69770d;
			X = -95.9392;
			Y = -852.155;
			Z = 186.91;
			Pitch = -14.6732;
			Roll = 60.7219;
			Yaw = 50.9519;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xdb69770d;
			X = -102.216;
			Y = -846.349;
			Z = 184.76;
			Pitch = -14.6732;
			Roll = 61.2218;
			Yaw = 38.7512;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xdb69770d;
			X = -107.165;
			Y = -839.353;
			Z = 182.66;
			Pitch = -14.6732;
			Roll = 61.8217;
			Yaw = 27.0503;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0xdb69770d;
			X = -110.165;
			Y = -831.609;
			Z = 180.73;
			Pitch = -14.6732;
			Roll = 62.4215;
			Yaw = 7.95005;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0xdb69770d;
			X = -110.895;
			Y = -822.94;
			Z = 178.649;
			Pitch = -14.6732;
			Roll = 62.7214;
			Yaw = -2.64989;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0xdb69770d;
			X = -109.945;
			Y = -814.393;
			Z = 176.549;
			Pitch = -14.6732;
			Roll = 62.9212;
			Yaw = -14.3498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0xdb69770d;
			X = -107.365;
			Y = -806.067;
			Z = 174.349;
			Pitch = -14.6732;
			Roll = 63.0211;
			Yaw = -23.2496;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0xdb69770d;
			X = -103.607;
			Y = -798.221;
			Z = 172.1;
			Pitch = -14.6732;
			Roll = 63.0212;
			Yaw = -30.3495;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0xdb69770d;
			X = -98.7469;
			Y = -791.173;
			Z = 170.04;
			Pitch = -14.6732;
			Roll = 63.0212;
			Yaw = -43.2494;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0xdb69770d;
			X = -92.4064;
			Y = -785.491;
			Z = 167.979;
			Pitch = -14.6731;
			Roll = 63.0212;
			Yaw = -58.3492;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 0xdb69770d;
			X = -84.7861;
			Y = -781.448;
			Z = 165.859;
			Pitch = -14.6731;
			Roll = 63.3211;
			Yaw = -70.2487;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 0xdb69770d;
			X = -76.476;
			Y = -779.037;
			Z = 163.799;
			Pitch = -14.6731;
			Roll = 63.321;
			Yaw = -81.4478;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0xdb69770d;
			X = -68.2258;
			Y = -778.832;
			Z = 161.899;
			Pitch = -14.6731;
			Roll = 63.3207;
			Yaw = -103.346;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0xdb69770d;
			X = -60.2064;
			Y = -781.504;
			Z = 159.759;
			Pitch = -14.6731;
			Roll = 63.3206;
			Yaw = -118.945;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0xdb69770d;
			X = -53.0267;
			Y = -786.157;
			Z = 157.549;
			Pitch = -14.6731;
			Roll = 63.3206;
			Yaw = -131.244;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0xdb69770d;
			X = -47.0573;
			Y = -792.285;
			Z = 155.659;
			Pitch = -14.6731;
			Roll = 63.3205;
			Yaw = -146.041;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0xdb69770d;
			X = -42.9582;
			Y = -799.66;
			Z = 153.698;
			Pitch = -14.6731;
			Roll = 64.1999;
			Yaw = -163.237;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0xdb69770d;
			X = -40.8885;
			Y = -808.084;
			Z = 151.698;
			Pitch = -14.6731;
			Roll = 65.6996;
			Yaw = -174.932;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0xdb69770d;
			X = -40.5681;
			Y = -816.823;
			Z = 149.577;
			Pitch = -14.6731;
			Roll = 65.6994;
			Yaw = 176.068;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0xdb69770d;
			X = -41.7788;
			Y = -825.387;
			Z = 147.487;
			Pitch = -14.6731;
			Roll = 65.6994;
			Yaw = 163.767;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0xdb69770d;
			X = -44.6091;
			Y = -833.703;
			Z = 145.287;
			Pitch = -14.6731;
			Roll = 65.6993;
			Yaw = 155.867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0xdb69770d;
			X = -48.6654;
			Y = -841.157;
			Z = 143.167;
			Pitch = -14.6731;
			Roll = 65.6992;
			Yaw = 142.867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0xdb69770d;
			X = -54.1979;
			Y = -847.802;
			Z = 140.937;
			Pitch = -14.6731;
			Roll = 65.6992;
			Yaw = 135.066;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0xdb69770d;
			X = -60.6785;
			Y = -853.495;
			Z = 138.787;
			Pitch = -14.6731;
			Roll = 65.6992;
			Yaw = 123.766;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0xdb69770d;
			X = -68.1026;
			Y = -857.438;
			Z = 136.717;
			Pitch = -14.6731;
			Roll = 66.2991;
			Yaw = 105.365;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0xdb69770d;
			X = -76.6025;
			Y = -859.104;
			Z = 134.617;
			Pitch = -14.6731;
			Roll = 66.2989;
			Yaw = 92.164;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0xdb69770d;
			X = -85.0122;
			Y = -858.507;
			Z = 132.517;
			Pitch = -14.6731;
			Roll = 66.2989;
			Yaw = 73.4632;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0xdb69770d;
			X = -92.5507;
			Y = -855.221;
			Z = 130.517;
			Pitch = -14.6731;
			Roll = 66.2988;
			Yaw = 52.362;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0xdb69770d;
			X = -99.2506;
			Y = -849.615;
			Z = 128.318;
			Pitch = -14.6731;
			Roll = 66.2988;
			Yaw = 45.5613;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0xdb69770d;
			X = -105.05;
			Y = -843.179;
			Z = 126.248;
			Pitch = -14.6731;
			Roll = 66.2988;
			Yaw = 35.0608;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0xdb69770d;
			X = -108.89;
			Y = -835.854;
			Z = 124.328;
			Pitch = -15.0931;
			Roll = 66.2988;
			Yaw = 12.7603;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0xdb69770d;
			X = -110.01;
			Y = -827.406;
			Z = 122.168;
			Pitch = -15.0931;
			Roll = 66.2988;
			Yaw = -3.23973;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0xdb69770d;
			X = -109.279;
			Y = -818.59;
			Z = 119.879;
			Pitch = -15.0932;
			Roll = 66.2987;
			Yaw = -8.33966;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0xdb69770d;
			X = -107.369;
			Y = -810.238;
			Z = 117.789;
			Pitch = -15.0932;
			Roll = 66.2986;
			Yaw = -22.1373;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0xdb69770d;
			X = -103.701;
			Y = -802.325;
			Z = 115.589;
			Pitch = -15.0932;
			Roll = 66.2986;
			Yaw = -30.5369;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0xdb69770d;
			X = -99.09;
			Y = -794.738;
			Z = 113.24;
			Pitch = -15.0932;
			Roll = 66.2986;
			Yaw = -32.9368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			Hash = 0xdb69770d;
			X = -93.8885;
			Y = -787.963;
			Z = 111.101;
			Pitch = -15.0932;
			Roll = 66.2986;
			Yaw = -46.6368;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[119];
			Hash = 0xdb69770d;
			X = -87.208;
			Y = -782.587;
			Z = 109.021;
			Pitch = -15.0932;
			Roll = 66.2985;
			Yaw = -60.4366;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 0xdb69770d;
			X = -79.4472;
			Y = -778.981;
			Z = 106.931;
			Pitch = -15.0932;
			Roll = 66.2984;
			Yaw = -74.2356;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 0xdb69770d;
			X = -71.0666;
			Y = -777.489;
			Z = 104.862;
			Pitch = -15.0932;
			Roll = 66.2982;
			Yaw = -91.8342;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 0xdb69770d;
			X = -62.8075;
			Y = -778.72;
			Z = 102.892;
			Pitch = -15.0932;
			Roll = 66.2982;
			Yaw = -111.832;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 0xdb69770d;
			X = -56.2184;
			Y = -782.965;
			Z = 100.464;
			Pitch = -15.0932;
			Roll = 56.6973;
			Yaw = -128.231;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 0xdb69770d;
			X = -50.3601;
			Y = -789.291;
			Z = 97.9058;
			Pitch = -10.3129;
			Roll = 47.5539;
			Yaw = -139.588;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 0xdb69770d;
			X = -45.1607;
			Y = -796.507;
			Z = 96.2556;
			Pitch = -8.41288;
			Roll = 40.7622;
			Yaw = -144.168;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 0xdb69770d;
			X = -40.7508;
			Y = -803.41;
			Z = 95.0657;
			Pitch = -8.41284;
			Roll = 35.7317;
			Yaw = -145.668;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 0xdb69770d;
			X = -36.561;
			Y = -810.615;
			Z = 93.9456;
			Pitch = -7.91276;
			Roll = 32.1427;
			Yaw = -153.167;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 0xdb69770d;
			X = -33.2219;
			Y = -818.711;
			Z = 92.5963;
			Pitch = -5.90268;
			Roll = 25.0189;
			Yaw = -156.866;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 0xdb69770d;
			X = -30.6813;
			Y = -827.114;
			Z = 91.896;
			Pitch = -4.24265;
			Roll = 19.3216;
			Yaw = -163.745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 0xdb69770d;
			X = -28.4213;
			Y = -835.978;
			Z = 91.2561;
			Pitch = -2.41276;
			Roll = 15.4014;
			Yaw = -163.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 0xdb69770d;
			X = -79.3652;
			Y = -794.677;
			Z = 323.624;
			Pitch = -24.1431;
			Roll = 13.8797;
			Yaw = -28.6609;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 0xdb69770d;
			X = -79.6652;
			Y = -797.981;
			Z = 326.855;
			Pitch = 7.06724;
			Roll = 11.8783;
			Yaw = -13.6898;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 0xdb69770d;
			X = -26.9613;
			Y = -843.577;
			Z = 91.0966;
			Pitch = -2.06276;
			Roll = 14.5604;
			Yaw = -176.762;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 0xdb69770d;
			X = -26.4813;
			Y = -851.781;
			Z = 90.547;
			Pitch = -6.16261;
			Roll = 14.5604;
			Yaw = -176.762;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];
			Hash = 0xdb69770d;
			X = -25.9913;
			Y = -860.826;
			Z = 89.997;
			Pitch = -1.76274;
			Roll = 14.5604;
			Yaw = -176.762;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[136];
			Hash = 0xdb69770d;
			X = -25.8013;
			Y = -869.823;
			Z = 90.2579;
			Pitch = 5.80742;
			Roll = 12.2601;
			Yaw = -178.212;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 0xdb69770d;
			X = -26.3713;
			Y = -878.417;
			Z = 91.849;
			Pitch = 15.5977;
			Roll = 10.2196;
			Yaw = 173.648;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 0xdb69770d;
			X = -28.3813;
			Y = -885.091;
			Z = 95.3375;
			Pitch = 40.8474;
			Roll = 5.75998;
			Yaw = 164.788;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[139];
			Hash = 0xdb69770d;
			X = -29.8213;
			Y = -890.497;
			Z = 101.507;
			Pitch = 52.3074;
			Roll = 5.75997;
			Yaw = 164.788;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[140];
			Hash = 0xdb69770d;
			X = -31.3313;
			Y = -895.152;
			Z = 108.807;
			Pitch = 61.6082;
			Roll = 5.75993;
			Yaw = 162.473;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[141];
			Hash = 0xdb69770d;
			X = -32.2819;
			Y = -896.089;
			Z = 116.238;
			Pitch = 77.632;
			Roll = 161.841;
			Yaw = 6.9756e-006;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[142];
			Hash = 0xdb69770d;
			X = -32.192;
			Y = -893.275;
			Z = 123.178;
			Pitch = 58.2452;
			Roll = 172.341;
			Yaw = -15.8996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[143];
			Hash = 0xdb69770d;
			X = -30.892;
			Y = -888.976;
			Z = 129.079;
			Pitch = 45.4451;
			Roll = 172.341;
			Yaw = -21.5994;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[144];
			Hash = 0xdb69770d;
			X = -28.592;
			Y = -883.38;
			Z = 133.38;
			Pitch = 23.8448;
			Roll = 171.74;
			Yaw = -25.5991;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[145];
			Hash = 0xdb69770d;
			X = -25.892;
			Y = -878.082;
			Z = 135.08;
			Pitch = -3.75519;
			Roll = 170.84;
			Yaw = -31.3986;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[146];
			Hash = 0xdb69770d;
			X = -22.592;
			Y = -873.184;
			Z = 133.91;
			Pitch = -32.7553;
			Roll = 170.84;
			Yaw = -34.1983;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[147];
			Hash = 0xdb69770d;
			X = -20.442;
			Y = -869.984;
			Z = 131.011;
			Pitch = -41.0563;
			Roll = 170.84;
			Yaw = -34.1983;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[148];
			Hash = 0xdb69770d;
			X = -17.132;
			Y = -865.056;
			Z = 124.922;
			Pitch = -50.2573;
			Roll = 170.84;
			Yaw = -34.1981;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[149];
			Hash = 0xdb69770d;
			X = -14.4319;
			Y = -861.26;
			Z = 118.522;
			Pitch = -57.6583;
			Roll = 172.54;
			Yaw = -35.998;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[150];
			Hash = 0xdb69770d;
			X = -12.4319;
			Y = -858.065;
			Z = 111.822;
			Pitch = -65.7618;
			Roll = 172.64;
			Yaw = -33.6977;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[151];
			Hash = 0xdb69770d;
			X = -10.2317;
			Y = -855.175;
			Z = 104.122;
			Pitch = -68.0667;
			Roll = 172.64;
			Yaw = -36.597;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[152];
			Hash = 0xdb69770d;
			X = -8.40166;
			Y = -854.461;
			Z = 95.4223;
			Pitch = -83.3198;
			Roll = 23.8325;
			Yaw = 165.093;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[153];
			Hash = 0xdb69770d;
			X = -9.20163;
			Y = -857.665;
			Z = 89.3224;
			Pitch = -44.0278;
			Roll = 11.0313;
			Yaw = 143.692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[154];
			Hash = 0xdb69770d;
			X = -13.2015;
			Y = -862.772;
			Z = 85.3027;
			Pitch = -18.9281;
			Roll = 10.031;
			Yaw = 131.392;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[155];
			Hash = 0xdb69770d;
			X = -19.3815;
			Y = -867.078;
			Z = 83.5729;
			Pitch = -3.62812;
			Roll = 10.031;
			Yaw = 116.191;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[156];
			Hash = 0xdb69770d;
			X = -27.6115;
			Y = -871.065;
			Z = 83.1232;
			Pitch = -1.62808;
			Roll = 10.031;
			Yaw = 115.589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[157];
			Hash = 0xdb69770d;
			X = -33.7519;
			Y = -874.712;
			Z = 83.4435;
			Pitch = 6.97197;
			Roll = 12.2309;
			Yaw = 120.689;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[158];
			Hash = 0xdb69770d;
			X = -40.8522;
			Y = -879.515;
			Z = 84.8434;
			Pitch = 12.872;
			Roll = 12.4307;
			Yaw = 126.188;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[159];
			Hash = 0xdb69770d;
			X = -46.2526;
			Y = -883.819;
			Z = 87.1434;
			Pitch = 22.672;
			Roll = 12.4306;
			Yaw = 130.488;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[160];
			Hash = 0xdb69770d;
			X = -49.6529;
			Y = -887.423;
			Z = 90.1434;
			Pitch = 43.872;
			Roll = 13.5303;
			Yaw = 138.288;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[161];
			Hash = 0xdb69770d;
			X = -51.553;
			Y = -890.025;
			Z = 94.6433;
			Pitch = 65.2731;
			Roll = 15.0299;
			Yaw = 144.587;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[162];
			Hash = 0xdb69770d;
			X = -51.7532;
			Y = -891.131;
			Z = 99.0432;
			Pitch = 83.8756;
			Roll = 15.0298;
			Yaw = 149.287;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[163];
			Hash = 0xdb69770d;
			X = -51.7532;
			Y = -890.434;
			Z = 106.043;
			Pitch = 69.3204;
			Roll = 164.317;
			Yaw = -4.9;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[164];
			Hash = 0xdb69770d;
			X = -52.0534;
			Y = -887.439;
			Z = 112.143;
			Pitch = 59.0208;
			Roll = 164.317;
			Yaw = -13.2999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[165];
			Hash = 0xdb69770d;
			X = -51.4534;
			Y = -883.241;
			Z = 117.643;
			Pitch = 47.4206;
			Roll = 164.317;
			Yaw = -19.1998;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[166];
			Hash = 0xdb69770d;
			X = -50.6535;
			Y = -880.543;
			Z = 120.743;
			Pitch = 41.1201;
			Roll = 164.317;
			Yaw = -19.1996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[167];
			Hash = 0xdb69770d;
			X = -50.2535;
			Y = -878.144;
			Z = 122.243;
			Pitch = 30.7198;
			Roll = 164.317;
			Yaw = -26.7994;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[168];
			Hash = 0xdb69770d;
			X = -48.8536;
			Y = -875.246;
			Z = 123.943;
			Pitch = 28.2198;
			Roll = 164.317;
			Yaw = -26.7994;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[169];
			Hash = 0xdb69770d;
			X = -46.0536;
			Y = -869.647;
			Z = 127.243;
			Pitch = 26.5198;
			Roll = 164.317;
			Yaw = -26.799;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[170];
			Hash = 0xdb69770d;
			X = -43.0537;
			Y = -863.749;
			Z = 129.943;
			Pitch = 19.0197;
			Roll = 164.317;
			Yaw = -33.9989;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[171];
			Hash = 0xdb69770d;
			X = -39.5538;
			Y = -858.45;
			Z = 131.244;
			Pitch = 1.5198;
			Roll = 163.017;
			Yaw = -36.0987;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[172];
			Hash = 0xdb69770d;
			X = -35.9539;
			Y = -854.354;
			Z = 131.244;
			Pitch = -8.98021;
			Roll = 163.017;
			Yaw = -47.4986;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[173];
			Hash = 0xdb69770d;
			X = -32.2539;
			Y = -851.255;
			Z = 129.944;
			Pitch = -23.1802;
			Roll = 163.017;
			Yaw = -54.1984;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[174];
			Hash = 0xdb69770d;
			X = -25.8539;
			Y = -847.158;
			Z = 126.344;
			Pitch = -28.6802;
			Roll = 163.017;
			Yaw = -62.1982;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[175];
			Hash = 0xdb69770d;
			X = -18.8539;
			Y = -844.565;
			Z = 122.144;
			Pitch = -33.0804;
			Roll = 163.017;
			Yaw = -70.8969;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[176];
			Hash = 0xdb69770d;
			X = -12.1538;
			Y = -842.769;
			Z = 116.644;
			Pitch = -46.1809;
			Roll = 163.017;
			Yaw = -74.5967;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[177];
			Hash = 0xdb69770d;
			X = -7.61381;
			Y = -841.464;
			Z = 110.444;
			Pitch = -63.7842;
			Roll = 164.116;
			Yaw = -80.996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[178];
			Hash = 0xdb69770d;
			X = -5.39381;
			Y = -841.525;
			Z = 102.224;
			Pitch = -86.2186;
			Roll = 162.568;
			Yaw = -88.7935;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[179];
			Hash = 0xdb69770d;
			X = -6.10921;
			Y = -842.197;
			Z = 95.3145;
			Pitch = 71.0817;
			Roll = 10.3993;
			Yaw = -89.2791;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[180];
			Hash = 0xdb69770d;
			X = -10.4592;
			Y = -841.732;
			Z = 87.6755;
			Pitch = 51.3046;
			Roll = 10.0893;
			Yaw = -86.6737;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[181];
			Hash = 0xdb69770d;
			X = -16.4592;
			Y = -842.637;
			Z = 82.9147;
			Pitch = 30.0027;
			Roll = 6.99941;
			Yaw = -87.2784;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[182];
			Hash = 0xdb69770d;
			X = -24.4592;
			Y = -843.242;
			Z = 79.9148;
			Pitch = 9.40273;
			Roll = 6.99925;
			Yaw = -77.8775;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[183];
			Hash = 0xdb69770d;
			X = -32.1693;
			Y = -845.047;
			Z = 78.5148;
			Pitch = 10.3028;
			Roll = 7.79919;
			Yaw = -68.6771;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[184];
			Hash = 0xdb69770d;
			X = -38.2695;
			Y = -848.351;
			Z = 76.915;
			Pitch = 13.8028;
			Roll = 3.99914;
			Yaw = -54.1764;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[185];
			Hash = 0xdb69770d;
			X = -44.5197;
			Y = -852.854;
			Z = 74.9651;
			Pitch = 14.0028;
			Roll = 3.99914;
			Yaw = -54.1763;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[186];
			Hash = 0xdb69770d;
			X = -51.3499;
			Y = -857.748;
			Z = 72.3955;
			Pitch = 18.8028;
			Roll = 5.0991;
			Yaw = -51.176;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[187];
			Hash = 0xdb69770d;
			X = -57.7501;
			Y = -863.052;
			Z = 69.3557;
			Pitch = 19.9028;
			Roll = 5.09907;
			Yaw = -45.2757;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[188];
			Hash = 0xdb69770d;
			X = -63.8103;
			Y = -869.157;
			Z = 66.006;
			Pitch = 20.4029;
			Roll = 5.09905;
			Yaw = -40.6754;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[189];
			Hash = 0xdb69770d;
			X = -69.3802;
			Y = -875.653;
			Z = 62.6458;
			Pitch = 21.8029;
			Roll = 5.09903;
			Yaw = -40.6754;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[190];
			Hash = 0xdb69770d;
			X = -75.0797;
			Y = -882.159;
			Z = 58.8356;
			Pitch = 23.903;
			Roll = 5.09895;
			Yaw = -39.0249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[191];
			Hash = 0xdb69770d;
			X = -80.5693;
			Y = -888.863;
			Z = 54.7355;
			Pitch = 24.9431;
			Roll = 5.09887;
			Yaw = -39.0247;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[192];
			Hash = 0xdb69770d;
			X = -85.7592;
			Y = -895.238;
			Z = 50.9353;
			Pitch = 24.9431;
			Roll = 5.09888;
			Yaw = -38.7746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[193];
			Hash = 0xdb69770d;
			X = -91.0591;
			Y = -901.744;
			Z = 46.8352;
			Pitch = 24.9431;
			Roll = 5.09887;
			Yaw = -38.0746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[194];
			Hash = 0xdb69770d;
			X = -96.259;
			Y = -908.351;
			Z = 42.6351;
			Pitch = 24.9431;
			Roll = 5.09887;
			Yaw = -38.0746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[195];
			Hash = 0xdb69770d;
			X = -101.308;
			Y = -914.855;
			Z = 38.835;
			Pitch = 24.9431;
			Roll = 5.09888;
			Yaw = -35.9345;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[196];
			Hash = 0xdb69770d;
			X = -106.018;
			Y = -921.611;
			Z = 35.4446;
			Pitch = 19.5033;
			Roll = 5.09881;
			Yaw = -32.6843;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[197];
			Hash = 0xdb69770d;
			X = -110.368;
			Y = -928.718;
			Z = 33.0144;
			Pitch = 12.4033;
			Roll = 5.09877;
			Yaw = -26.4837;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[198];
			Hash = 0xdb69770d;
			X = -114.268;
			Y = -936.721;
			Z = 31.1044;
			Pitch = 11.6033;
			Roll = 4.08874;
			Yaw = -24.6033;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[199];
			Hash = 0xdb69770d;
			X = -118.018;
			Y = -944.717;
			Z = 29.3144;
			Pitch = 11.1134;
			Roll = 3.48872;
			Yaw = -25.803;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[200];
			Hash = 0xdb69770d;
			X = -122.067;
			Y = -952.123;
			Z = 28.2244;
			Pitch = 4.14348;
			Roll = 3.48861;
			Yaw = -27.632;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[201];
			Hash = 0xdb69770d;
			X = -125.647;
			Y = -959.685;
			Z = 27.8544;
			Pitch = 0.673421;
			Roll = 3.48851;
			Yaw = -22.3615;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[202];
			Hash = 0xdb69770d;
			X = -129.187;
			Y = -968.11;
			Z = 27.6944;
			Pitch = 1.03343;
			Roll = 3.48845;
			Yaw = -22.3613;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[203];
			Hash = 0xdb69770d;
			X = -132.438;
			Y = -976.486;
			Z = 27.4944;
			Pitch = 1.03344;
			Roll = 3.48841;
			Yaw = -19.7106;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[204];
			Hash = 0xdb69770d;
			X = -135.598;
			Y = -985.23;
			Z = 27.2844;
			Pitch = 0.753435;
			Roll = 3.48841;
			Yaw = -19.7106;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[205];
			Hash = 0xdb69770d;
			X = -138.728;
			Y = -993.907;
			Z = 27.1544;
			Pitch = 0.753435;
			Roll = 3.48841;
			Yaw = -19.7106;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[206];
			Hash = 0xdb69770d;
			X = -141.817;
			Y = -1002.56;
			Z = 26.9944;
			Pitch = 0.753436;
			Roll = 2.87841;
			Yaw = -19.8305;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[207];
			Hash = 0xdb69770d;
			X = -144.947;
			Y = -1011.29;
			Z = 26.8144;
			Pitch = 0.623438;
			Roll = 2.87839;
			Yaw = -19.8305;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[208];
			Hash = 0xdb69770d;
			X = -148.037;
			Y = -1019.95;
			Z = 26.4543;
			Pitch = 3.83344;
			Roll = 2.07839;
			Yaw = -19.8303;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[209];
			/*Hash = 0x2b3ad141;
			X = -74.2863;
			Y = -811.933;
			Z = 325.046;
			Pitch = 0;
			Roll = 0;
			Yaw = 10.9977;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);*/

			HaxBy("Zynh");
		}
		void mmf_DowntownBobsled()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdb69770d;
			X = -144.101;
			Y = -601.324;
			Z = 210.665;
			Pitch = -3.66;
			Roll = 4.27759e-007;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdb69770d;
			X = -143.383;
			Y = -610.211;
			Z = 209.189;
			Pitch = -15.48;
			Roll = -5.42621e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdb69770d;
			X = -144.823;
			Y = -592.133;
			Z = 210.764;
			Pitch = 2.47198;
			Roll = 8.01158e-008;
			Yaw = -175.525;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdb69770d;
			X = -142.778;
			Y = -617.816;
			Z = 206.289;
			Pitch = -25.08;
			Roll = -4.47759e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdb69770d;
			X = -142.198;
			Y = -625.17;
			Z = 202.089;
			Pitch = -34.02;
			Roll = 2.83272e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdb69770d;
			X = -141.648;
			Y = -632.075;
			Z = 197.39;
			Pitch = -34.02;
			Roll = 2.83272e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdb69770d;
			X = -141.128;
			Y = -638.692;
			Z = 192.9;
			Pitch = -34.02;
			Roll = 3.09024e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdb69770d;
			X = -140.588;
			Y = -645.545;
			Z = 188.261;
			Pitch = -34.02;
			Roll = 3.34776e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdb69770d;
			X = -140.068;
			Y = -652.148;
			Z = 183.79;
			Pitch = -34.02;
			Roll = 3.8628e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdb69770d;
			X = -139.513;
			Y = -659.151;
			Z = 179.04;
			Pitch = -34.02;
			Roll = 4.12032e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdb69770d;
			X = -139.513;
			Y = -659.151;
			Z = 179.04;
			Pitch = -34.02;
			Roll = 4.37784e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdb69770d;
			X = -138.923;
			Y = -666.464;
			Z = 174.149;
			Pitch = -34.02;
			Roll = 4.63536e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdb69770d;
			X = -138.373;
			Y = -673.268;
			Z = 169.55;
			Pitch = -34.02;
			Roll = 5.1504e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xdb69770d;
			X = -137.823;
			Y = -680.171;
			Z = 164.86;
			Pitch = -34.02;
			Roll = 5.40792e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xdb69770d;
			X = -137.303;
			Y = -686.675;
			Z = 160.441;
			Pitch = -34.02;
			Roll = 5.66544e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xdb69770d;
			X = -136.803;
			Y = -693.277;
			Z = 155.942;
			Pitch = -34.02;
			Roll = 5.92296e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdb69770d;
			X = -136.303;
			Y = -699.579;
			Z = 151.672;
			Pitch = -34.02;
			Roll = 6.438e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdb69770d;
			X = -135.823;
			Y = -705.732;
			Z = 147.902;
			Pitch = -27.8699;
			Roll = 1.69014e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdb69770d;
			X = -135.163;
			Y = -713.835;
			Z = 144.833;
			Pitch = -13.5897;
			Roll = 4.72121e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xdb69770d;
			X = -134.493;
			Y = -722.239;
			Z = 143.293;
			Pitch = -6.78964;
			Roll = 2.8481e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xdb69770d;
			X = -133.863;
			Y = -730.132;
			Z = 142.763;
			Pitch = -0.139585;
			Roll = 5.20854e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xdb69770d;
			X = -133.233;
			Y = -738.037;
			Z = 143.213;
			Pitch = 7.64046;
			Roll = 1.77668e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xdb69770d;
			X = -132.533;
			Y = -746.831;
			Z = 144.953;
			Pitch = 14.8804;
			Roll = -3.31275e-007;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xdb69770d;
			X = -128.642;
			Y = -807.346;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xdb69770d;
			X = -128.062;
			Y = -814.549;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xdb69770d;
			X = -127.462;
			Y = -822.252;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xdb69770d;
			X = -126.862;
			Y = -829.754;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xdb69770d;
			X = -126.262;
			Y = -837.257;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xdb69770d;
			X = -125.662;
			Y = -844.86;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xdb69770d;
			X = -125.062;
			Y = -852.763;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xdb69770d;
			X = -124.462;
			Y = -860.567;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xdb69770d;
			X = -123.842;
			Y = -868.47;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xdb69770d;
			X = -123.242;
			Y = -875.773;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xdb69770d;
			X = -122.642;
			Y = -883.776;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xdb69770d;
			X = -122.042;
			Y = -891.578;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xdb69770d;
			X = -121.442;
			Y = -899.082;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xdb69770d;
			X = -120.782;
			Y = -907.285;
			Z = 149.765;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xdb69770d;
			X = -111.182;
			Y = -915.087;
			Z = 156.695;
			Pitch = 3.38;
			Roll = 80;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];


			//[42];
			Hash = 0xdb69770d;
			X = -110.892;
			Y = -918.563;
			Z = 156.666;
			Pitch = -1.44074e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xdb69770d;
			X = -110.282;
			Y = -926.366;
			Z = 156.666;
			Pitch = -1.33402e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xdb69770d;
			X = -109.582;
			Y = -935.069;
			Z = 156.666;
			Pitch = -1.28066e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xdb69770d;
			X = -108.882;
			Y = -943.573;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xdb69770d;
			X = -108.232;
			Y = -951.676;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xdb69770d;
			X = -107.632;
			Y = -959.378;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xdb69770d;
			X = -106.982;
			Y = -967.582;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xdb69770d;
			X = -106.352;
			Y = -975.486;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xdb69770d;
			X = -105.722;
			Y = -983.489;
			Z = 156.666;
			Pitch = -1.2273e-006;
			Roll = 80.3973;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xdb69770d;
			X = -105.422;
			Y = -992.092;
			Z = 156.666;
			Pitch = -2.41791e-007;
			Roll = 80.3973;
			Yaw = 179.834;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xdb69770d;
			X = -105.882;
			Y = -1001;
			Z = 156.666;
			Pitch = -5.33608e-007;
			Roll = 80.3973;
			Yaw = 174.432;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xdb69770d;
			X = -107.092;
			Y = -1009.4;
			Z = 156.666;
			Pitch = -5.33608e-007;
			Roll = 80.3973;
			Yaw = 169.732;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xdb69770d;
			X = -109.292;
			Y = -1017.8;
			Z = 156.666;
			Pitch = 2.98821e-006;
			Roll = 80.3973;
			Yaw = 161.532;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xdb69770d;
			X = -112.862;
			Y = -1026.21;
			Z = 156.666;
			Pitch = -2.13443e-006;
			Roll = 80.3973;
			Yaw = 152.632;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xdb69770d;
			X = -117.212;
			Y = -1033.11;
			Z = 156.666;
			Pitch = -8.53774e-007;
			Roll = 80.3973;
			Yaw = 144.031;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xdb69770d;
			X = -122.812;
			Y = -1039.51;
			Z = 156.666;
			Pitch = -1.70755e-006;
			Roll = 80.3973;
			Yaw = 134.231;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xdb69770d;
			X = -129.111;
			Y = -1044.91;
			Z = 156.666;
			Pitch = 1.70755e-006;
			Roll = 80.3973;
			Yaw = 127.131;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xdb69770d;
			X = -136.821;
			Y = -1049.5;
			Z = 156.666;
			Pitch = 2.13443e-006;
			Roll = 80.3972;
			Yaw = 114.179;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xdb69770d;
			X = -145.01;
			Y = -1052.05;
			Z = 156.666;
			Pitch = 1.60083e-006;
			Roll = 80.3972;
			Yaw = 99.9591;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xdb69770d;
			X = -152.509;
			Y = -1052.75;
			Z = 156.666;
			Pitch = 3.20165e-007;
			Roll = 80.3972;
			Yaw = 92.3588;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xdb69770d;
			X = -161.008;
			Y = -1052.45;
			Z = 156.666;
			Pitch = -1.28066e-006;
			Roll = 80.3972;
			Yaw = 84.4584;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xdb69770d;
			X = -169.707;
			Y = -1050.63;
			Z = 156.666;
			Pitch = -4.26887e-007;
			Roll = 80.3972;
			Yaw = 71.8578;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xdb69770d;
			X = -177.906;
			Y = -1047.41;
			Z = 156.666;
			Pitch = 2.13443e-007;
			Roll = 80.3972;
			Yaw = 65.3573;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xdb69770d;
			X = -185.505;
			Y = -1043.51;
			Z = 156.666;
			Pitch = -4.26887e-007;
			Roll = 80.3972;
			Yaw = 60.5568;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xdb69770d;
			X = -192.135;
			Y = -1038.43;
			Z = 157.176;
			Pitch = 6.00001;
			Roll = 81.997;
			Yaw = 45.0547;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xdb69770d;
			X = -198.025;
			Y = -1031.65;
			Z = 158.086;
			Pitch = 6.00005;
			Roll = 82.4865;
			Yaw = 37.0544;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xdb69770d;
			X = -202.565;
			Y = -1024.46;
			Z = 158.895;
			Pitch = 6.00008;
			Roll = 82.4865;
			Yaw = 28.1536;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xdb69770d;
			X = -205.714;
			Y = -1017.36;
			Z = 159.705;
			Pitch = 5.60007;
			Roll = 83.4462;
			Yaw = 20.6534;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 0xdb69770d;
			X = -207.453;
			Y = -1010.25;
			Z = 160.094;
			Pitch = 3.71008;
			Roll = 83.4462;
			Yaw = 6.60321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xdb69770d;
			X = -207.702;
			Y = -1001.65;
			Z = 160.604;
			Pitch = 3.60007;
			Roll = 83.4462;
			Yaw = -2.79681;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xdb69770d;
			X = -206.902;
			Y = -994.357;
			Z = 160.734;
			Pitch = 0.700068;
			Roll = 83.4462;
			Yaw = -10.3967;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xdb69770d;
			X = -205.052;
			Y = -986.41;
			Z = 160.854;
			Pitch = 0.700067;
			Roll = 83.4462;
			Yaw = -15.6967;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xdb69770d;
			X = -202.591;
			Y = -978.913;
			Z = 160.924;
			Pitch = 0.700066;
			Roll = 83.4462;
			Yaw = -20.0966;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xdb69770d;
			X = -199.227;
			Y = -971.175;
			Z = 160.966;
			Pitch = 6.5954e-005;
			Roll = 83.4462;
			Yaw = -26.5862;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xdb69770d;
			X = -158.448;
			Y = -897.464;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xdb69770d;
			X = -154.908;
			Y = -890.667;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xdb69770d;
			X = -151.357;
			Y = -883.869;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xdb69770d;
			X = -147.687;
			Y = -876.831;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xdb69770d;
			X = -143.986;
			Y = -869.733;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xdb69770d;
			X = -140.086;
			Y = -862.235;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xdb69770d;
			X = -136.015;
			Y = -854.438;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xdb69770d;
			X = -132.415;
			Y = -847.54;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xdb69770d;
			X = -128.864;
			Y = -840.743;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0xdb69770d;
			X = -125.364;
			Y = -834.044;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0xdb69770d;
			X = -121.604;
			Y = -826.846;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0xdb69770d;
			X = -117.734;
			Y = -819.448;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0xdb69770d;
			X = -113.834;
			Y = -811.95;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0xdb69770d;
			X = -109.564;
			Y = -803.752;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5508;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0xdb69770d;
			X = -105.964;
			Y = -796.855;
			Z = 140.81;
			Pitch = 0;
			Roll = 0;
			Yaw = -27.5907;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0xdb69770d;
			X = -109.064;
			Y = -785.959;
			Z = 148.291;
			Pitch = 4.89005;
			Roll = 84.8997;
			Yaw = -33.2803;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];


			//[93];
			Hash = 0xdb69770d;
			X = -105.764;
			Y = -781.072;
			Z = 148.841;
			Pitch = 6.74;
			Roll = 84.9188;
			Yaw = -34.6505;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0xdb69770d;
			X = -100.964;
			Y = -774.877;
			Z = 149.661;
			Pitch = 6.74;
			Roll = 84.9188;
			Yaw = -41.0505;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0xdb69770d;
			X = -95.2641;
			Y = -769.08;
			Z = 150.561;
			Pitch = 6.73999;
			Roll = 84.9188;
			Yaw = -48.4503;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0xdb69770d;
			X = -88.7642;
			Y = -763.934;
			Z = 151.461;
			Pitch = 6.74;
			Roll = 84.9188;
			Yaw = -54.9502;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0xdb69770d;
			X = -83.1643;
			Y = -760.535;
			Z = 152.161;
			Pitch = 6.74;
			Roll = 84.9188;
			Yaw = -65.0499;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0xdb69770d;
			X = -75.8644;
			Y = -758.039;
			Z = 152.961;
			Pitch = 6.74001;
			Roll = 86.4186;
			Yaw = -79.749;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0xdb69770d;
			X = -67.9645;
			Y = -757.242;
			Z = 153.861;
			Pitch = 6.74003;
			Roll = 87.3185;
			Yaw = -89.2483;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0xdb69770d;
			X = -59.8647;
			Y = -758.044;
			Z = 154.862;
			Pitch = 6.74004;
			Roll = 89.4183;
			Yaw = -102.647;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0xdb69770d;
			X = -52.1649;
			Y = -760.667;
			Z = 155.792;
			Pitch = 6.74004;
			Roll = 90.1181;
			Yaw = -115.246;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0xdb69770d;
			X = -44.3152;
			Y = -765.27;
			Z = 156.742;
			Pitch = 6.74003;
			Roll = 90.1181;
			Yaw = -124.645;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0xdb69770d;
			X = -37.3153;
			Y = -770.972;
			Z = 157.742;
			Pitch = 6.74003;
			Roll = 90.1181;
			Yaw = -133.644;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0xdb69770d;
			X = -31.8154;
			Y = -776.574;
			Z = 158.592;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = -138.643;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0xdb69770d;
			X = -27.4154;
			Y = -782.076;
			Z = 159.392;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = -146.241;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0xdb69770d;
			X = -23.4154;
			Y = -789.279;
			Z = 160.292;
			Pitch = 6.74002;
			Roll = 89.9178;
			Yaw = -156.439;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0xdb69770d;
			X = -21.0154;
			Y = -796.584;
			Z = 161.092;
			Pitch = 6.74002;
			Roll = 89.9178;
			Yaw = -168.637;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0xdb69770d;
			X = -20.0254;
			Y = -805.287;
			Z = 162.062;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = -178.735;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0xdb69770d;
			X = -20.6254;
			Y = -812.459;
			Z = 162.802;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = 169.365;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0xdb69770d;
			X = -22.8254;
			Y = -820.585;
			Z = 163.702;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = 160.864;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0xdb69770d;
			X = -26.2254;
			Y = -827.891;
			Z = 164.602;
			Pitch = 6.74002;
			Roll = 89.9178;
			Yaw = 149.564;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0xdb69770d;
			X = -31.4254;
			Y = -834.497;
			Z = 165.403;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 133.464;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0xdb69770d;
			X = -36.8255;
			Y = -839.4;
			Z = 166.243;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 131.153;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0xdb69770d;
			X = -42.6259;
			Y = -843.865;
			Z = 167.043;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 124.953;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0xdb69770d;
			X = -50.3061;
			Y = -848.239;
			Z = 167.993;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 113.631;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0xdb69770d;
			X = -57.8063;
			Y = -851.343;
			Z = 168.943;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 111.101;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0xdb69770d;
			X = -65.4064;
			Y = -854.045;
			Z = 169.873;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 108.001;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			Hash = 0xdb69770d;
			X = -74.2063;
			Y = -856.348;
			Z = 170.913;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 100.71;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[119];
			Hash = 0xdb69770d;
			X = -82.1062;
			Y = -857.05;
			Z = 171.713;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 88.9095;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 0xdb69770d;
			X = -90.2061;
			Y = -856.453;
			Z = 172.603;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 82.1092;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 0xdb69770d;
			X = -98.006;
			Y = -855.086;
			Z = 173.493;
			Pitch = 6.74;
			Roll = 89.9178;
			Yaw = 76.809;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 0xdb69770d;
			X = -105.506;
			Y = -852.688;
			Z = 174.332;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = 66.8087;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 0xdb69770d;
			X = -112.206;
			Y = -849.09;
			Z = 175.132;
			Pitch = 6.74003;
			Roll = 89.9178;
			Yaw = 58.1078;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 0xdb69770d;
			X = -161.806;
			Y = -816.048;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 0xdb69770d;
			X = -167.805;
			Y = -811.451;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 0xdb69770d;
			X = -174.304;
			Y = -806.453;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 0xdb69770d;
			X = -180.303;
			Y = -801.854;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 0xdb69770d;
			X = -186.294;
			Y = -797.284;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 0xdb69770d;
			X = -192.153;
			Y = -792.787;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 0xdb69770d;
			X = -198.952;
			Y = -787.591;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 0xdb69770d;
			X = -205.341;
			Y = -782.702;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 0xdb69770d;
			X = -211.741;
			Y = -777.803;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 0xdb69770d;
			X = -218.44;
			Y = -772.675;
			Z = 163.03;
			Pitch = 0;
			Roll = 0;
			Yaw = 52.5692;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 0xdb69770d;
			X = -227.709;
			Y = -775.676;
			Z = 170.48;
			Pitch = -0.460004;
			Roll = 88.5298;
			Yaw = 52.5687;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];


			//[136];
			Hash = 0xdb69770d;
			X = -233.009;
			Y = -771.271;
			Z = 170.652;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = 46.7382;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 0xdb69770d;
			X = -238.808;
			Y = -765.173;
			Z = 171.152;
			Pitch = 3.99998;
			Roll = 88.9994;
			Yaw = 40.1376;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 0xdb69770d;
			X = -243.908;
			Y = -758.174;
			Z = 171.752;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = 32.0372;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[139];
			Hash = 0xdb69770d;
			X = -247.707;
			Y = -750.977;
			Z = 172.252;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = 24.437;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[140];
			Hash = 0xdb69770d;
			X = -250.807;
			Y = -743.279;
			Z = 172.802;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = 19.9369;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[141];
			Hash = 0xdb69770d;
			X = -252.727;
			Y = -735.131;
			Z = 173.332;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = 6.63676;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[142];
			Hash = 0xdb69770d;
			X = -253.123;
			Y = -726.504;
			Z = 173.882;
			Pitch = 3.99997;
			Roll = 88.9994;
			Yaw = -1.35327;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[143];
			Hash = 0xdb69770d;
			X = -252.383;
			Y = -718.407;
			Z = 174.402;
			Pitch = 3.99998;
			Roll = 88.9993;
			Yaw = -8.88308;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[144];
			Hash = 0xdb69770d;
			X = -241.104;
			Y = -662.788;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[145];
			Hash = 0xdb69770d;
			X = -239.174;
			Y = -654.879;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[146];
			Hash = 0xdb69770d;
			X = -237.224;
			Y = -646.881;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[147];
			Hash = 0xdb69770d;
			X = -235.303;
			Y = -638.983;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[148];
			Hash = 0xdb69770d;
			X = -233.333;
			Y = -630.885;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[149];
			Hash = 0xdb69770d;
			X = -231.433;
			Y = -623.187;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[150];
			Hash = 0xdb69770d;
			X = -229.533;
			Y = -615.389;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[151];
			Hash = 0xdb69770d;
			X = -227.533;
			Y = -607.192;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[152];
			Hash = 0xdb69770d;
			X = -225.532;
			Y = -599.094;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[153];
			Hash = 0xdb69770d;
			X = -223.532;
			Y = -590.896;
			Z = 165.555;
			Pitch = 0;
			Roll = 0;
			Yaw = -13.6734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[154];
			Hash = 0xdb69770d;
			X = -230.742;
			Y = -585.497;
			Z = 172.595;
			Pitch = 0.850004;
			Roll = 83.4798;
			Yaw = -13.6733;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[155];


			//[156];
			Hash = 0xdb69770d;
			X = -228.43;
			Y = -578.604;
			Z = 172.588;
			Pitch = -1.06722e-006;
			Roll = 82.9996;
			Yaw = -22.7028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[157];
			Hash = 0xdb69770d;
			X = -224.479;
			Y = -570.805;
			Z = 172.588;
			Pitch = -1.92099e-006;
			Roll = 82.9996;
			Yaw = -31.6028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[158];
			Hash = 0xdb69770d;
			X = -219.469;
			Y = -563.449;
			Z = 172.588;
			Pitch = -1.70755e-006;
			Roll = 82.9996;
			Yaw = -36.9124;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[159];
			Hash = 0xdb69770d;
			X = -213.868;
			Y = -556.683;
			Z = 172.588;
			Pitch = 4.26887e-007;
			Roll = 82.9996;
			Yaw = -42.3027;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[160];
			Hash = 0xdb69770d;
			X = -207.366;
			Y = -550.626;
			Z = 172.588;
			Pitch = -1.92099e-006;
			Roll = 82.9996;
			Yaw = -51.7026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[161];
			Hash = 0xdb69770d;
			X = -199.897;
			Y = -545.617;
			Z = 172.588;
			Pitch = 8.53774e-007;
			Roll = 82.9996;
			Yaw = -60.9425;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[162];
			Hash = 0xdb69770d;
			X = -191.927;
			Y = -541.85;
			Z = 172.588;
			Pitch = 1.4941e-006;
			Roll = 82.9996;
			Yaw = -68.3024;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[163];
			Hash = 0xdb69770d;
			X = -183.466;
			Y = -538.759;
			Z = 172.588;
			Pitch = 1.70755e-006;
			Roll = 82.9996;
			Yaw = -71.3417;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[164];
			Hash = 0xdb69770d;
			X = -174.937;
			Y = -536.17;
			Z = 172.588;
			Pitch = 1.06722e-006;
			Roll = 82.9996;
			Yaw = -74.9003;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[165];
			Hash = 0xdb69770d;
			X = -166.065;
			Y = -534.469;
			Z = 172.597;
			Pitch = 3.41509e-006;
			Roll = 82.9996;
			Yaw = -83.3999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[166];
			Hash = 0xdb69770d;
			X = -157.744;
			Y = -533.783;
			Z = 172.597;
			Pitch = 2.7214e-006;
			Roll = 82.9996;
			Yaw = -87.5794;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[167];
			Hash = 0xdb69770d;
			X = -149.164;
			Y = -533.531;
			Z = 172.597;
			Pitch = 3.34839e-006;
			Roll = 82.9996;
			Yaw = -89.159;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[168];
			Hash = 0xdb69770d;
			X = -140.462;
			Y = -533.415;
			Z = 172.597;
			Pitch = 2.6547e-006;
			Roll = 82.9996;
			Yaw = -89.2997;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[169];
			Hash = 0xdb69770d;
			X = -132.383;
			Y = -533.595;
			Z = 172.597;
			Pitch = 1.73423e-006;
			Roll = 82.9996;
			Yaw = -93.4993;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[170];
			Hash = 0xdb69770d;
			X = -123.862;
			Y = -534.086;
			Z = 172.597;
			Pitch = 2.74808e-006;
			Roll = 82.9996;
			Yaw = -93.0992;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[171];
			Hash = 0xdb69770d;
			X = -129.313;
			Y = -799.138;
			Z = 149.775;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[172];
			Hash = 0xdb69770d;
			X = -115.132;
			Y = -534.806;
			Z = 172.597;
			Pitch = 1.76091e-006;
			Roll = 82.9996;
			Yaw = -96.1869;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[173];
			Hash = 0xdb69770d;
			X = -108.262;
			Y = -535.948;
			Z = 172.597;
			Pitch = 2.34788e-006;
			Roll = 82.9996;
			Yaw = -101.346;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[174];
			Hash = 0xdb69770d;
			X = -100.364;
			Y = -537.844;
			Z = 172.597;
			Pitch = 2.34788e-006;
			Roll = 82.9996;
			Yaw = -106.237;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[175];
			Hash = 0xdb69770d;
			X = -92.5625;
			Y = -540.525;
			Z = 172.597;
			Pitch = 6.4033e-007;
			Roll = 82.9996;
			Yaw = -111.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[176];
			Hash = 0xdb69770d;
			X = -84.8626;
			Y = -544.129;
			Z = 172.597;
			Pitch = 8.53774e-007;
			Roll = 82.9996;
			Yaw = -118.997;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[177];
			Hash = 0xdb69770d;
			X = -78.7627;
			Y = -548.033;
			Z = 172.597;
			Pitch = -4.26887e-006;
			Roll = 82.9996;
			Yaw = -125.897;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[178];
			Hash = 0xdb69770d;
			X = -72.0628;
			Y = -553.739;
			Z = 172.597;
			Pitch = -3.41509e-006;
			Roll = 82.9996;
			Yaw = -135.795;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[179];


			//[180];


			//[181];
			Hash = 0xdb69770d;
			X = -35.1696;
			Y = -594.412;
			Z = 162.049;
			Pitch = 4.5;
			Roll = -2.14103e-007;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[182];
			Hash = 0xdb69770d;
			X = -28.4697;
			Y = -600.205;
			Z = 162.749;
			Pitch = 4.5;
			Roll = -1.71283e-006;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[183];
			Hash = 0xdb69770d;
			X = -21.5696;
			Y = -606.157;
			Z = 163.449;
			Pitch = 4.5;
			Roll = -6.4231e-007;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[184];
			Hash = 0xdb69770d;
			X = -15.1696;
			Y = -611.662;
			Z = 164.149;
			Pitch = 4.5;
			Roll = 4.28207e-007;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[185];
			Hash = 0xdb69770d;
			X = -9.36957;
			Y = -616.666;
			Z = 164.749;
			Pitch = 4.5;
			Roll = -6.4231e-007;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[186];
			Hash = 0xdb69770d;
			X = -3.11957;
			Y = -622.069;
			Z = 165.335;
			Pitch = 3.52996;
			Roll = 2.45926e-006;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[187];
			Hash = 0xdb69770d;
			X = 3.02043;
			Y = -627.373;
			Z = 165.609;
			Pitch = 0.46;
			Roll = -5.60307e-007;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[188];
			Hash = 0xdb69770d;
			X = 8.92043;
			Y = -632.477;
			Z = 165.569;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[189];
			Hash = 0xdb69770d;
			X = 14.7205;
			Y = -637.48;
			Z = 165.529;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[190];
			Hash = 0xdb69770d;
			X = 20.6105;
			Y = -642.582;
			Z = 165.509;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[191];
			Hash = 0xdb69770d;
			X = 26.8605;
			Y = -647.987;
			Z = 165.489;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[192];
			Hash = 0xdb69770d;
			X = 33.2605;
			Y = -653.489;
			Z = 165.449;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[193];
			Hash = 0xdb69770d;
			X = 39.4204;
			Y = -658.793;
			Z = 165.449;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[194];
			Hash = 0xdb69770d;
			X = 45.2203;
			Y = -663.795;
			Z = 165.449;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[195];
			Hash = 0xdb69770d;
			X = 51.5901;
			Y = -669.297;
			Z = 165.449;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[196];
			Hash = 0xdb69770d;
			X = 57.4899;
			Y = -674.399;
			Z = 165.449;
			Pitch = 0;
			Roll = -0;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[197];
			Hash = 0xdb69770d;
			X = 56.4195;
			Y = -683.845;
			Z = 173.069;
			Pitch = -1.28066e-006;
			Roll = -86.6997;
			Yaw = -130.806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[198];


			//[199];
			Hash = 0xdb69770d;
			X = 60.3927;
			Y = -686.843;
			Z = 173.13;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -110.922;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[200];
			Hash = 0xdb69770d;
			X = 67.9425;
			Y = -689.544;
			Z = 173.68;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -108.622;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[201];
			Hash = 0xdb69770d;
			X = 75.2628;
			Y = -691.467;
			Z = 174.162;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -101.321;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[202];
			Hash = 0xdb69770d;
			X = 83.0228;
			Y = -692.568;
			Z = 174.681;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -95.0305;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[203];
			Hash = 0xdb69770d;
			X = 91.1928;
			Y = -692.991;
			Z = 175.221;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -90.7303;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[204];
			Hash = 0xdb69770d;
			X = 99.5227;
			Y = -692.77;
			Z = 175.761;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -85.8301;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[205];
			Hash = 0xdb69770d;
			X = 107.623;
			Y = -691.92;
			Z = 176.311;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -82.1996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[206];
			Hash = 0xdb69770d;
			X = 115.123;
			Y = -690.68;
			Z = 176.79;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -78.4995;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[207];
			Hash = 0xdb69770d;
			X = 123.022;
			Y = -688.791;
			Z = 177.334;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -74.3993;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[208];
			Hash = 0xdb69770d;
			X = 130.392;
			Y = -686.432;
			Z = 177.843;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -70.1991;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[209];
			Hash = 0xdb69770d;
			X = 137.293;
			Y = -683.633;
			Z = 178.343;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -66.0783;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[210];
			Hash = 0xdb69770d;
			X = 143.573;
			Y = -680.514;
			Z = 178.813;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -60.7783;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[211];
			Hash = 0xdb69770d;
			X = 151.233;
			Y = -675.725;
			Z = 179.42;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -55.0782;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[212];
			Hash = 0xdb69770d;
			X = 157.363;
			Y = -671.026;
			Z = 179.899;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -50.1782;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[213];
			Hash = 0xdb69770d;
			X = 163.642;
			Y = -665.206;
			Z = 180.469;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -43.7778;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[214];
			Hash = 0xdb69770d;
			X = 168.942;
			Y = -658.887;
			Z = 181.009;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -36.3777;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[215];
			Hash = 0xdb69770d;
			X = 173.443;
			Y = -651.79;
			Z = 181.549;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = -28.2775;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[216];
			Hash = 0xdb69770d;
			X = 177.053;
			Y = -643.854;
			Z = 182.118;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -20.5773;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[217];
			Hash = 0xdb69770d;
			X = 179.393;
			Y = -635.595;
			Z = 182.678;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -11.2771;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[218];
			Hash = 0xdb69770d;
			X = -130.033;
			Y = -790.34;
			Z = 149.775;
			Pitch = -2.0323e-006;
			Roll = 2.78815e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[219];
			Hash = 0xdb69770d;
			X = 180.352;
			Y = -627.047;
			Z = 183.232;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = -1.4771;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[220];
			Hash = 0xdb69770d;
			X = 179.778;
			Y = -618.287;
			Z = 183.791;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 9.02287;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[221];
			Hash = 0xdb69770d;
			X = 177.779;
			Y = -610.289;
			Z = 184.311;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 18.7228;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[222];
			Hash = 0xdb69770d;
			X = 174.88;
			Y = -603.691;
			Z = 184.711;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 27.8227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[223];
			Hash = 0xdb69770d;
			X = 170.61;
			Y = -596.88;
			Z = 185.221;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 36.7223;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[224];
			Hash = 0xdb69770d;
			X = 164.781;
			Y = -590.283;
			Z = 185.771;
			Pitch = 3.99998;
			Roll = -86.2995;
			Yaw = 46.3412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[225];
			Hash = 0xdb69770d;
			X = 158.472;
			Y = -585.174;
			Z = 186.32;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 56.6212;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[226];
			Hash = 0xdb69770d;
			X = 151.001;
			Y = -580.806;
			Z = 186.88;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = 63.3197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[227];
			Hash = 0xdb69770d;
			X = 143.021;
			Y = -577.689;
			Z = 187.4;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 73.8201;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[228];
			Hash = 0xdb69770d;
			X = 135.182;
			Y = -575.971;
			Z = 187.93;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = 82.1191;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[229];
			Hash = 0xdb69770d;
			X = 126.743;
			Y = -575.494;
			Z = 188.45;
			Pitch = 4;
			Roll = -86.2995;
			Yaw = 91.6184;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[230];
			Hash = 0xdb69770d;
			X = 117.946;
			Y = -576.323;
			Z = 189.024;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 99.4177;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[231];
			Hash = 0xdb69770d;
			X = 109.516;
			Y = -578.534;
			Z = 189.564;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 109.917;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[232];
			Hash = 0xdb69770d;
			X = 102.017;
			Y = -581.926;
			Z = 190.064;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 119.516;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[233];
			Hash = 0xdb69770d;
			X = 94.9566;
			Y = -586.609;
			Z = 190.614;
			Pitch = 3.99999;
			Roll = -86.2995;
			Yaw = 128.116;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[234];
			Hash = 0xdb69770d;
			X = 88.417;
			Y = -592.883;
			Z = 191.133;
			Pitch = 3.99999;
			Roll = -86.299;
			Yaw = 139.115;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[235];
			Hash = 0xdb69770d;
			X = 83.1474;
			Y = -600.187;
			Z = 191.713;
			Pitch = 3.99999;
			Roll = -86.299;
			Yaw = 149.015;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[236];
			Hash = 0xdb69770d;
			X = 79.1178;
			Y = -608.3;
			Z = 192.272;
			Pitch = 4;
			Roll = -86.299;
			Yaw = 158.815;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[237];
			Hash = 0xdb69770d;
			X = 76.7885;
			Y = -616.144;
			Z = 192.802;
			Pitch = 4;
			Roll = -86.299;
			Yaw = 168.515;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[238];
			Hash = 0xdb69770d;
			X = 75.8593;
			Y = -624.737;
			Z = 193.342;
			Pitch = 4;
			Roll = -86.299;
			Yaw = 179.514;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[239];
			Hash = 0xdb69770d;
			X = 75.8593;
			Y = -624.737;
			Z = 193.342;
			Pitch = 4;
			Roll = -86.299;
			Yaw = 179.514;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[240];
			Hash = 0xdb69770d;
			X = 76.5301;
			Y = -633.182;
			Z = 193.891;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -169.983;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[241];
			Hash = 0xdb69770d;
			X = 78.6904;
			Y = -641.645;
			Z = 194.491;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -161.382;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[242];
			Hash = 0xdb69770d;
			X = 82.0711;
			Y = -649.598;
			Z = 195.09;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -152.38;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[243];
			Hash = 0xdb69770d;
			X = 86.4713;
			Y = -656.602;
			Z = 195.62;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -142.877;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[244];
			Hash = 0xdb69770d;
			X = 92.0717;
			Y = -662.775;
			Z = 196.14;
			Pitch = 3.99999;
			Roll = -86.299;
			Yaw = -132.875;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[245];
			Hash = 0xdb69770d;
			X = 98.612;
			Y = -667.879;
			Z = 196.66;
			Pitch = 3.99999;
			Roll = -86.299;
			Yaw = -122.873;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[246];
			Hash = 0xdb69770d;
			X = 106.012;
			Y = -672.141;
			Z = 197.209;
			Pitch = 3.99999;
			Roll = -86.299;
			Yaw = -116.973;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[247];
			Hash = 0xdb69770d;
			X = 112.972;
			Y = -675.203;
			Z = 197.719;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -109.572;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[248];
			Hash = 0xdb69770d;
			X = 120.702;
			Y = -677.544;
			Z = 198.259;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -103.871;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[249];
			Hash = 0xdb69770d;
			X = 129.002;
			Y = -679.014;
			Z = 198.808;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -96.271;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[250];
			Hash = 0xdb69770d;
			X = 136.711;
			Y = -679.394;
			Z = 199.298;
			Pitch = 4;
			Roll = -86.299;
			Yaw = -88.2706;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[251];
			Hash = 0xdb69770d;
			X = 144.651;
			Y = -678.534;
			Z = 199.788;
			Pitch = 4;
			Roll = -86.2985;
			Yaw = -78.4797;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[252];
			Hash = 0xdb69770d;
			X = 152.71;
			Y = -676.064;
			Z = 200.327;
			Pitch = 4;
			Roll = -86.2985;
			Yaw = -66.7285;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[253];
			Hash = 0xdb69770d;
			X = 160.339;
			Y = -671.844;
			Z = 200.877;
			Pitch = 4;
			Roll = -86.2985;
			Yaw = -55.3283;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[254];
			Hash = 0xdb69770d;
			X = 166.919;
			Y = -666.324;
			Z = 201.407;
			Pitch = 3.99999;
			Roll = -86.2985;
			Yaw = -44.3282;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[255];
			Hash = 0xdb69770d;
			X = 172.549;
			Y = -659.344;
			Z = 201.967;
			Pitch = 4;
			Roll = -86.2985;
			Yaw = -33.7281;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[256];
			Hash = 0xdb69770d;
			X = 176.179;
			Y = -652.796;
			Z = 202.436;
			Pitch = 4.00001;
			Roll = -86.2985;
			Yaw = -23.1278;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[257];
			Hash = 0xdb69770d;
			X = 178.938;
			Y = -645.037;
			Z = 202.976;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = -16.0277;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[258];
			Hash = 0xdb69770d;
			X = 180.608;
			Y = -638.44;
			Z = 203.426;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = -10.9276;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[259];
			Hash = 0xdb69770d;
			X = 181.817;
			Y = -630.342;
			Z = 203.975;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = -5.92755;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[260];
			Hash = 0xdb69770d;
			X = 181.997;
			Y = -622.262;
			Z = 204.475;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = 3.67245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[261];
			Hash = 0xdb69770d;
			X = 181.137;
			Y = -615.364;
			Z = 204.884;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = 12.5724;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[262];
			Hash = 0xdb69770d;
			X = 178.817;
			Y = -607.606;
			Z = 205.404;
			Pitch = 4.00003;
			Roll = -86.2985;
			Yaw = 21.8723;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[263];
			Hash = 0xdb69770d;
			X = 175.448;
			Y = -600.608;
			Z = 205.884;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 30.4721;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[264];
			Hash = 0xdb69770d;
			X = 171.077;
			Y = -594.271;
			Z = 206.383;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 38.9718;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[265];
			Hash = 0xdb69770d;
			X = 165.338;
			Y = -588.574;
			Z = 206.873;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 52.0712;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[266];
			Hash = 0xdb69770d;
			X = 158.588;
			Y = -584.097;
			Z = 207.393;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 61.1707;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[267];
			Hash = 0xdb69770d;
			X = 152.349;
			Y = -580.66;
			Z = 207.892;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 61.1707;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[268];
			Hash = 0xdb69770d;
			X = 145.65;
			Y = -577.633;
			Z = 208.342;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 71.4701;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[269];
			Hash = 0xdb69770d;
			X = 137.53;
			Y = -575.607;
			Z = 208.872;
			Pitch = 4.00005;
			Roll = -86.2985;
			Yaw = 80.7695;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[270];
			Hash = 0xdb69770d;
			X = 129.441;
			Y = -574.939;
			Z = 209.381;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 90.1688;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[271];
			Hash = 0xdb69770d;
			X = 120.532;
			Y = -575.319;
			Z = 210.001;
			Pitch = 4.00005;
			Roll = -86.2985;
			Yaw = 94.6684;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[272];
			Hash = 0xdb69770d;
			X = 111.712;
			Y = -576.952;
			Z = 210.561;
			Pitch = 4.00005;
			Roll = -86.2985;
			Yaw = 105.677;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[273];
			Hash = 0xdb69770d;
			X = 103.972;
			Y = -579.693;
			Z = 211.091;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 113.776;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[274];
			Hash = 0xdb69770d;
			X = 97.0825;
			Y = -583.395;
			Z = 211.59;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 123.976;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[275];
			Hash = 0xdb69770d;
			X = 91.1827;
			Y = -588.036;
			Z = 212.09;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 133.475;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[276];
			Hash = 0xdb69770d;
			X = 86.2432;
			Y = -593.279;
			Z = 212.55;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 141.875;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[277];
			Hash = 0xdb69770d;
			X = 81.4239;
			Y = -600.243;
			Z = 213.099;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 148.775;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[278];
			Hash = 0xdb69770d;
			X = 77.8239;
			Y = -607.628;
			Z = 213.609;
			Pitch = 4.00004;
			Roll = -86.2985;
			Yaw = 159.375;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[279];
			Hash = 0xdb69770d;
			X = 75.5645;
			Y = -615.924;
			Z = 214.158;
			Pitch = 4.00008;
			Roll = -86.2985;
			Yaw = 170.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[280];
			Hash = 0xdb69770d;
			X = 74.8449;
			Y = -623.429;
			Z = 214.628;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -179.57;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[281];
			Hash = 0xdb69770d;
			X = 75.4351;
			Y = -631.233;
			Z = 215.128;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -170.868;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[282];
			Hash = 0xdb69770d;
			X = 77.1359;
			Y = -638.936;
			Z = 215.628;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -163.266;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[283];
			Hash = 0xdb69770d;
			X = 79.8962;
			Y = -646.139;
			Z = 216.108;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -153.364;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[284];
			Hash = 0xdb69770d;
			X = 83.5467;
			Y = -652.524;
			Z = 216.577;
			Pitch = 4.0001;
			Roll = -86.2985;
			Yaw = -146.473;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[285];
			Hash = 0xdb69770d;
			X = 88.5417;
			Y = -658.928;
			Z = 217.087;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -136.771;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[286];
			Hash = 0xdb69770d;
			X = 94.8823;
			Y = -664.49;
			Z = 217.616;
			Pitch = 4.00009;
			Roll = -86.2985;
			Yaw = -125.675;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[287];
			Hash = 0xdb69770d;
			X = 129.2;
			Y = -691.795;
			Z = 210.02;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[288];
			Hash = 0xdb69770d;
			X = 135.43;
			Y = -696.6;
			Z = 210.159;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[289];
			Hash = 0xdb69770d;
			X = 142.2;
			Y = -701.803;
			Z = 210.319;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[290];
			Hash = 0xdb69770d;
			X = 148.6;
			Y = -706.724;
			Z = 210.459;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[291];
			Hash = 0xdb69770d;
			X = 155.77;
			Y = -712.226;
			Z = 210.619;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[292];
			Hash = 0xdb69770d;
			X = 162.291;
			Y = -717.23;
			Z = 210.769;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[293];
			Hash = 0xdb69770d;
			X = 168.261;
			Y = -721.834;
			Z = 210.899;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[294];
			Hash = 0xdb69770d;
			X = 175.091;
			Y = -727.068;
			Z = 211.049;
			Pitch = 1;
			Roll = -0;
			Yaw = -127.576;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[295];
			Hash = 0xdb69770d;
			X = 184.956;
			Y = -724.969;
			Z = 218.875;
			Pitch = 3.03999;
			Roll = 89.9999;
			Yaw = -131.245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[296];


			//[297];
			Hash = 0xdb69770d;
			X = 189.772;
			Y = -730.173;
			Z = 219.039;
			Pitch = 9.13879e-007;
			Roll = 89.9999;
			Yaw = -142.883;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[298];
			Hash = 0xdb69770d;
			X = 194.522;
			Y = -737.648;
			Z = 219.039;
			Pitch = 9.13912e-007;
			Roll = 89.9999;
			Yaw = -152.18;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[299];
			Hash = 0xdb69770d;
			X = 197.731;
			Y = -745.251;
			Z = 219.039;
			Pitch = 9.13876e-007;
			Roll = 89.9999;
			Yaw = -161.778;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[300];
			Hash = 0xdb69770d;
			X = 199.661;
			Y = -753.664;
			Z = 219.039;
			Pitch = 9.13893e-007;
			Roll = 89.9999;
			Yaw = -172.075;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[301];
			Hash = 0xdb69770d;
			X = 200.1;
			Y = -762.058;
			Z = 219.039;
			Pitch = 9.13889e-007;
			Roll = 89.9999;
			Yaw = 178.428;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[302];
			Hash = 0xdb69770d;
			X = 199.07;
			Y = -770.461;
			Z = 219.039;
			Pitch = 9.13875e-007;
			Roll = 89.9999;
			Yaw = 167.928;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[303];
			Hash = 0xdb69770d;
			X = 196.59;
			Y = -778.374;
			Z = 219.039;
			Pitch = 9.13863e-007;
			Roll = 89.9999;
			Yaw = 157.528;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[304];
			Hash = 0xdb69770d;
			X = 192.4;
			Y = -786.198;
			Z = 219.039;
			Pitch = 9.13834e-007;
			Roll = 89.9999;
			Yaw = 145.928;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[305];
			Hash = 0xdb69770d;
			X = 186.719;
			Y = -792.862;
			Z = 219.039;
			Pitch = 9.13769e-007;
			Roll = 89.9999;
			Yaw = 133.127;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[306];
			Hash = 0xdb69770d;
			X = 179.959;
			Y = -798.053;
			Z = 219.039;
			Pitch = 9.13834e-007;
			Roll = 89.9999;
			Yaw = 122.127;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[307];
			Hash = 0xdb69770d;
			X = 172.44;
			Y = -801.844;
			Z = 219.039;
			Pitch = 9.1385e-007;
			Roll = 89.9999;
			Yaw = 111.126;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[308];
			Hash = 0xdb69770d;
			X = 164.379;
			Y = -804.226;
			Z = 219.035;
			Pitch = 9.13873e-007;
			Roll = 89.9999;
			Yaw = 101.925;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[309];
			Hash = 0xdb69770d;
			X = 155.659;
			Y = -805.135;
			Z = 219.035;
			Pitch = 9.13865e-007;
			Roll = 89.9999;
			Yaw = 90.1246;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[310];
			Hash = 0xdb69770d;
			X = 147.039;
			Y = -804.456;
			Z = 219.035;
			Pitch = 9.13858e-007;
			Roll = 89.9999;
			Yaw = 80.9242;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[311];
			Hash = 0xdb69770d;
			X = 138.879;
			Y = -802.416;
			Z = 219.045;
			Pitch = 9.13847e-007;
			Roll = 89.9999;
			Yaw = 71.3238;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[312];
			Hash = 0xdb69770d;
			X = 130.969;
			Y = -798.958;
			Z = 219.045;
			Pitch = 9.13814e-007;
			Roll = 89.9999;
			Yaw = 61.1232;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[313];
			Hash = 0xdb69770d;
			X = 124.33;
			Y = -794.53;
			Z = 219.045;
			Pitch = 9.13772e-007;
			Roll = 89.9999;
			Yaw = 52.0227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[314];
			Hash = 0xdb69770d;
			X = 118.23;
			Y = -788.903;
			Z = 219.045;
			Pitch = 9.13762e-007;
			Roll = 89.9999;
			Yaw = 42.6222;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[315];
			Hash = 0xdb69770d;
			X = 113.395;
			Y = -782.826;
			Z = 219.045;
			Pitch = 9.1398e-007;
			Roll = 89.9999;
			Yaw = 33.3001;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[316];
			Hash = 0xdb69770d;
			X = 80.5059;
			Y = -734.177;
			Z = 198.84;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[317];
			Hash = 0xdb69770d;
			X = 74.9861;
			Y = -726.98;
			Z = 199.01;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[318];
			Hash = 0xdb69770d;
			X = 70.0862;
			Y = -720.581;
			Z = 199.16;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[319];
			Hash = 0xdb69770d;
			X = 65.4063;
			Y = -714.485;
			Z = 199.29;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[320];
			Hash = 0xdb69770d;
			X = 60.6062;
			Y = -708.188;
			Z = 199.43;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[321];
			Hash = 0xdb69770d;
			X = 55.5061;
			Y = -701.491;
			Z = 199.57;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[322];
			Hash = 0xdb69770d;
			X = 50.606;
			Y = -695.095;
			Z = 199.72;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[323];
			Hash = 0xdb69770d;
			X = 45.4658;
			Y = -688.418;
			Z = 199.839;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[324];
			Hash = 0xdb69770d;
			X = 40.9856;
			Y = -682.591;
			Z = 199.969;
			Pitch = 1;
			Roll = 2.13476e-007;
			Yaw = 37.4617;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[325];


			//[326];


			//[327];
			Hash = 0xdb69770d;
			X = 34.7105;
			Y = -664.177;
			Z = 206.071;
			Pitch = -10;
			Roll = -90;
			Yaw = 55.4158;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[328];
			Hash = 0xdb69770d;
			X = 40.89;
			Y = -670.14;
			Z = 207.49;
			Pitch = -7.49995;
			Roll = -93.7861;
			Yaw = 36.2636;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[329];
			Hash = 0xdb69770d;
			X = 28.1502;
			Y = -660.551;
			Z = 204.89;
			Pitch = -10;
			Roll = -90;
			Yaw = 66.6352;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[330];
			Hash = 0xdb69770d;
			X = 20.4602;
			Y = -657.945;
			Z = 203.488;
			Pitch = -10;
			Roll = -87.5562;
			Yaw = 76.5343;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[331];
			Hash = 0xdb69770d;
			X = 12.0702;
			Y = -656.774;
			Z = 201.908;
			Pitch = -10;
			Roll = -85.0745;
			Yaw = 87.5334;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[332];
			Hash = 0xdb69770d;
			X = 3.77025;
			Y = -656.774;
			Z = 200.436;
			Pitch = -10;
			Roll = -84.4744;
			Yaw = 92.8627;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[333];
			Hash = 0xdb69770d;
			X = -4.58974;
			Y = -657.853;
			Z = 198.972;
			Pitch = -9.99997;
			Roll = -83.1433;
			Yaw = 101.662;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[334];
			Hash = 0xdb69770d;
			X = -12.7897;
			Y = -660.326;
			Z = 197.454;
			Pitch = -10;
			Roll = -81.4129;
			Yaw = 111.86;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[335];
			Hash = 0xdb69770d;
			X = -20.5297;
			Y = -664.108;
			Z = 196.062;
			Pitch = -10;
			Roll = -81.4129;
			Yaw = 121.059;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[336];
			Hash = 0xdb69770d;
			X = -27.3097;
			Y = -668.961;
			Z = 194.711;
			Pitch = -10;
			Roll = -81.4129;
			Yaw = 131.159;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[337];
			Hash = 0xdb69770d;
			X = -32.9198;
			Y = -674.784;
			Z = 193.41;
			Pitch = -10;
			Roll = -81.4129;
			Yaw = 141.659;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[338];
			Hash = 0xdb69770d;
			X = -37.9412;
			Y = -682.238;
			Z = 191.81;
			Pitch = -10;
			Roll = -79.6914;
			Yaw = 150.859;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[339];
			Hash = 0xdb69770d;
			X = -41.4807;
			Y = -690.162;
			Z = 190.296;
			Pitch = -10;
			Roll = -78.2302;
			Yaw = 160.658;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[340];
			Hash = 0xdb69770d;
			X = -43.6213;
			Y = -698.275;
			Z = 188.825;
			Pitch = -10;
			Roll = -77.0686;
			Yaw = 170.147;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[341];
			Hash = 0xdb69770d;
			X = -44.3419;
			Y = -707.199;
			Z = 187.153;
			Pitch = -10.0001;
			Roll = -74.3962;
			Yaw = -179.253;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[342];
			Hash = 0xdb69770d;
			X = -43.5822;
			Y = -715.562;
			Z = 185.671;
			Pitch = -10.02;
			Roll = -73.025;
			Yaw = -170.051;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[343];
			Hash = 0xdb69770d;
			X = -41.4429;
			Y = -723.926;
			Z = 184.09;
			Pitch = -10.0201;
			Roll = -71.1334;
			Yaw = -160.849;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[344];
			Hash = 0xdb69770d;
			X = -37.9136;
			Y = -731.839;
			Z = 182.548;
			Pitch = -10.0201;
			Roll = -69.3313;
			Yaw = -150.047;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[345];
			Hash = 0xdb69770d;
			X = -33.1142;
			Y = -738.942;
			Z = 181.017;
			Pitch = -10.0202;
			Roll = -67.8699;
			Yaw = -141.945;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[346];
			Hash = 0xdb69770d;
			X = -27.0742;
			Y = -745.356;
			Z = 179.415;
			Pitch = -10.0203;
			Roll = -65.6283;
			Yaw = -131.443;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[347];
			Hash = 0xdb69770d;
			X = -20.1042;
			Y = -750.578;
			Z = 177.833;
			Pitch = -10.0203;
			Roll = -63.8063;
			Yaw = -121.841;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[348];
			Hash = 0xdb69770d;
			X = -12.3641;
			Y = -754.459;
			Z = 176.231;
			Pitch = -10.0203;
			Roll = -61.5052;
			Yaw = -111.898;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[349];
			Hash = 0xdb69770d;
			X = -4.75405;
			Y = -757.232;
			Z = 174.841;
			Pitch = -10.0203;
			Roll = -61.1048;
			Yaw = -108.298;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[350];
			Hash = 0xdb69770d;
			X = 47.1275;
			Y = -775.577;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[351];
			Hash = 0xdb69770d;
			X = 55.4174;
			Y = -778.129;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[352];
			Hash = 0xdb69770d;
			X = 63.677;
			Y = -780.66;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[353];
			Hash = 0xdb69770d;
			X = 71.187;
			Y = -782.962;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[354];
			Hash = 0xdb69770d;
			X = 79.377;
			Y = -785.465;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[355];
			Hash = 0xdb69770d;
			X = 87.5369;
			Y = -787.968;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[356];
			Hash = 0xdb69770d;
			X = 96.3769;
			Y = -790.669;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[357];
			Hash = 0xdb69770d;
			X = 105.177;
			Y = -793.372;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[358];
			Hash = 0xdb69770d;
			X = 112.707;
			Y = -795.673;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[359];
			Hash = 0xdb69770d;
			X = 120.947;
			Y = -798.215;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[360];
			Hash = 0xdb69770d;
			X = 128.937;
			Y = -800.657;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[361];
			Hash = 0xdb69770d;
			X = 136.837;
			Y = -803.06;
			Z = 150.211;
			Pitch = 0;
			Roll = -0;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[362];
			Hash = 0xdb69770d;
			X = 146.767;
			Y = -797.771;
			Z = 157.831;
			Pitch = -2.13443e-007;
			Roll = 90;
			Yaw = -107.046;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[363];


			//[364];
			Hash = 0xdb69770d;
			X = 150.719;
			Y = -799.766;
			Z = 157.879;
			Pitch = -1.57207e-006;
			Roll = 90;
			Yaw = -118.024;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[365];
			Hash = 0xdb69770d;
			X = 157.299;
			Y = -803.949;
			Z = 157.588;
			Pitch = -3.99997;
			Roll = 90;
			Yaw = -126.123;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[366];
			Hash = 0xdb69770d;
			X = 163.139;
			Y = -808.963;
			Z = 157.098;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -134.431;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[367];
			Hash = 0xdb69770d;
			X = 169.116;
			Y = -815.779;
			Z = 156.518;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -142.829;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[368];
			Hash = 0xdb69770d;
			X = 173.266;
			Y = -822.203;
			Z = 156.027;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -150.327;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[369];
			Hash = 0xdb69770d;
			X = 176.996;
			Y = -829.998;
			Z = 155.456;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -158.325;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[370];
			Hash = 0xdb69770d;
			X = 179.386;
			Y = -837.632;
			Z = 154.926;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -166.324;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[371];
			Hash = 0xdb69770d;
			X = 180.545;
			Y = -845.045;
			Z = 154.455;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = -174.422;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[372];
			Hash = 0xdb69770d;
			X = 180.564;
			Y = -852.748;
			Z = 153.965;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 176.079;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[373];
			Hash = 0xdb69770d;
			X = 179.463;
			Y = -860.731;
			Z = 153.434;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 168.679;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[374];
			Hash = 0xdb69770d;
			X = 177.313;
			Y = -868.344;
			Z = 152.944;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 160.679;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[375];
			Hash = 0xdb69770d;
			X = 174.213;
			Y = -875.567;
			Z = 152.413;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 153.179;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[376];
			Hash = 0xdb69770d;
			X = 170.314;
			Y = -882.073;
			Z = 151.923;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 145.878;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[377];
			Hash = 0xdb69770d;
			X = 165.113;
			Y = -888.656;
			Z = 151.372;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 137.678;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[378];
			Hash = 0xdb69770d;
			X = 159.204;
			Y = -894.177;
			Z = 150.851;
			Pitch = -3.99995;
			Roll = 90;
			Yaw = 128.478;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[379];
			Hash = 0xdb69770d;
			X = 152.674;
			Y = -898.54;
			Z = 150.371;
			Pitch = -3.99995;
			Roll = 90;
			Yaw = 119.877;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[380];
			Hash = 0xdb69770d;
			X = 146.024;
			Y = -901.66;
			Z = 149.91;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 111.677;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[381];
			Hash = 0xdb69770d;
			X = 137.845;
			Y = -904.221;
			Z = 149.35;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 102.676;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[382];
			Hash = 0xdb69770d;
			X = 130.226;
			Y = -905.212;
			Z = 148.859;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 93.3758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[383];
			Hash = 0xdb69770d;
			X = 121.856;
			Y = -904.992;
			Z = 148.308;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 84.2754;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[384];
			Hash = 0xdb69770d;
			X = 113.907;
			Y = -903.823;
			Z = 147.778;
			Pitch = -3.99996;
			Roll = 90;
			Yaw = 79.1745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[385];
			Hash = 0xdb69770d;
			X = 57.4277;
			Y = -890.283;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[386];
			Hash = 0xdb69770d;
			X = 49.1275;
			Y = -887.985;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[387];
			Hash = 0xdb69770d;
			X = 40.5272;
			Y = -885.587;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[388];
			Hash = 0xdb69770d;
			X = 32.227;
			Y = -883.288;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[389];
			Hash = 0xdb69770d;
			X = 24.9269;
			Y = -881.29;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[390];
			Hash = 0xdb69770d;
			X = 17.4269;
			Y = -879.192;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[391];
			Hash = 0xdb69770d;
			X = 9.82692;
			Y = -877.092;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[392];
			Hash = 0xdb69770d;
			X = 2.22694;
			Y = -874.994;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[393];
			Hash = 0xdb69770d;
			X = -4.97307;
			Y = -872.995;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[394];
			Hash = 0xdb69770d;
			X = -11.873;
			Y = -871.095;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[395];
			Hash = 0xdb69770d;
			X = -20.173;
			Y = -868.797;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[396];
			Hash = 0xdb69770d;
			X = -27.3731;
			Y = -866.798;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[397];
			Hash = 0xdb69770d;
			X = -34.9731;
			Y = -864.699;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[398];
			Hash = 0xdb69770d;
			X = -42.5734;
			Y = -862.599;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[399];
			Hash = 0xdb69770d;
			X = -50.1735;
			Y = -860.501;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[400];
			Hash = 0xdb69770d;
			X = -57.8637;
			Y = -858.373;
			Z = 122.55;
			Pitch = 0;
			Roll = 0;
			Yaw = 74.5249;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[401];
			Hash = 0xdb69770d;
			X = -66.4732;
			Y = -864.177;
			Z = 130.27;
			Pitch = 1.58001;
			Roll = 89.9999;
			Yaw = 73.455;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[402];


			//[403];
			Hash = 0xdb69770d;
			X = -72.0559;
			Y = -862.171;
			Z = 130.343;
			Pitch = 0.450001;
			Roll = 90;
			Yaw = 68.7944;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[404];
			Hash = 0xdb69770d;
			X = -79.5156;
			Y = -859.032;
			Z = 130.383;
			Pitch = -2.97486e-009;
			Roll = 90;
			Yaw = 65.8943;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[405];
			Hash = 0xdb69770d;
			X = -86.0654;
			Y = -855.692;
			Z = 130.383;
			Pitch = -2.97537e-009;
			Roll = 90;
			Yaw = 60.4939;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[406];
			Hash = 0xdb69770d;
			X = -92.8651;
			Y = -851.495;
			Z = 130.383;
			Pitch = -2.97527e-009;
			Roll = 90;
			Yaw = 56.5937;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[407];
			Hash = 0xdb69770d;
			X = -99.2846;
			Y = -846.927;
			Z = 130.383;
			Pitch = -2.97507e-009;
			Roll = 90;
			Yaw = 52.6934;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[408];
			Hash = 0xdb69770d;
			X = -104.674;
			Y = -842.429;
			Z = 130.383;
			Pitch = -2.97466e-009;
			Roll = 90;
			Yaw = 48.4932;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[409];
			Hash = 0xdb69770d;
			X = -110.234;
			Y = -837.133;
			Z = 130.383;
			Pitch = -2.97445e-009;
			Roll = 90;
			Yaw = 44.693;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[410];
			Hash = 0xdb69770d;
			X = -115.573;
			Y = -830.636;
			Z = 130.383;
			Pitch = -2.97364e-009;
			Roll = 90;
			Yaw = 34.7926;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[411];
			Hash = 0xdb69770d;
			X = -119.723;
			Y = -823.739;
			Z = 130.383;
			Pitch = -2.97425e-009;
			Roll = 90;
			Yaw = 26.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[412];
			Hash = 0xdb69770d;
			X = -122.813;
			Y = -816.242;
			Z = 130.383;
			Pitch = -2.97405e-009;
			Roll = 90;
			Yaw = 17.9921;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[413];
			Hash = 0xdb69770d;
			X = -124.842;
			Y = -808.054;
			Z = 130.383;
			Pitch = -2.97443e-009;
			Roll = 90;
			Yaw = 9.79207;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[414];
			Hash = 0xdb69770d;
			X = -125.522;
			Y = -799.097;
			Z = 130.383;
			Pitch = -2.97411e-009;
			Roll = 90;
			Yaw = -1.10795;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[415];
			Hash = 0xdb69770d;
			X = -124.591;
			Y = -791.209;
			Z = 130.383;
			Pitch = -2.9743e-009;
			Roll = 90;
			Yaw = -11.0079;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[416];
			Hash = 0xdb69770d;
			X = -122.291;
			Y = -783.011;
			Z = 130.383;
			Pitch = -2.97471e-009;
			Roll = 90;
			Yaw = -20.6078;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[417];
			Hash = 0xdb69770d;
			X = -118.73;
			Y = -775.573;
			Z = 130.383;
			Pitch = -2.97486e-009;
			Roll = 90;
			Yaw = -30.3074;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[418];
			Hash = 0xdb69770d;
			X = -134.884;
			Y = -710.794;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[419];
			Hash = 0xdb69770d;
			X = -81.4766;
			Y = -728.63;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[420];
			Hash = 0xdb69770d;
			X = -75.7065;
			Y = -722.432;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[421];
			Hash = 0xdb69770d;
			X = -70.4066;
			Y = -716.733;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[422];
			Hash = 0xdb69770d;
			X = -64.3067;
			Y = -710.175;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[423];
			Hash = 0xdb69770d;
			X = -58.1569;
			Y = -703.567;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[424];
			Hash = 0xdb69770d;
			X = -52.387;
			Y = -697.369;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[425];
			Hash = 0xdb69770d;
			X = -46.9871;
			Y = -691.57;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[426];
			Hash = 0xdb69770d;
			X = -41.2872;
			Y = -685.442;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[427];
			Hash = 0xdb69770d;
			X = -35.7074;
			Y = -679.443;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[428];
			Hash = 0xdb69770d;
			X = -29.9575;
			Y = -673.245;
			Z = 113.497;
			Pitch = 0;
			Roll = 0;
			Yaw = -42.9245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[429];
			Hash = 0xdb69770d;
			X = -30.4475;
			Y = -662.148;
			Z = 121.197;
			Pitch = 1.51;
			Roll = 89.9999;
			Yaw = -43.4444;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[430];


			//[431];
			Hash = 0xdb69770d;
			X = -26.3504;
			Y = -658.354;
			Z = 121.625;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -49;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[432];
			Hash = 0xdb69770d;
			X = -19.3403;
			Y = -653.156;
			Z = 122.475;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -58;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[433];
			Hash = 0xdb69770d;
			X = -11.8503;
			Y = -649.148;
			Z = 123.295;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -65.9186;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[434];
			Hash = 0xdb69770d;
			X = -3.79021;
			Y = -646.349;
			Z = 124.136;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -75.9999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[435];
			Hash = 0xdb69770d;
			X = 4.15978;
			Y = -645.05;
			Z = 124.886;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -85.9996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[436];
			Hash = 0xdb69770d;
			X = 12.9398;
			Y = -645.12;
			Z = 125.716;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -94.9997;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[437];
			Hash = 0xdb69770d;
			X = 21.3498;
			Y = -646.49;
			Z = 126.536;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -104;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[438];
			Hash = 0xdb69770d;
			X = 29.4598;
			Y = -649.16;
			Z = 127.376;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -113;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[439];
			Hash = 0xdb69770d;
			X = 37.3796;
			Y = -653.274;
			Z = 128.246;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -122;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[440];
			Hash = 0xdb69770d;
			X = 44.5094;
			Y = -658.468;
			Z = 129.096;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -130.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[441];
			Hash = 0xdb69770d;
			X = 50.3781;
			Y = -664.325;
			Z = 129.886;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -139.458;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[442];
			Hash = 0xdb69770d;
			X = 55.1783;
			Y = -671.117;
			Z = 130.685;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -149.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[443];
			Hash = 0xdb69770d;
			X = 58.6285;
			Y = -678.182;
			Z = 131.456;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -158.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[444];
			Hash = 0xdb69770d;
			X = 60.9283;
			Y = -685.865;
			Z = 132.235;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -168.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[445];
			Hash = 0xdb69770d;
			X = 61.9081;
			Y = -694.068;
			Z = 133.035;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = -178.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[446];
			Hash = 0xdb69770d;
			X = 61.4879;
			Y = -701.571;
			Z = 133.744;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 171.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[447];
			Hash = 0xdb69770d;
			X = 59.5175;
			Y = -709.942;
			Z = 134.574;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 161.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[448];
			Hash = 0xdb69770d;
			X = 56.1473;
			Y = -717.785;
			Z = 135.403;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 151.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[449];
			Hash = 0xdb69770d;
			X = 51.7369;
			Y = -724.488;
			Z = 136.172;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 141.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[450];
			Hash = 0xdb69770d;
			X = 46.4467;
			Y = -730.192;
			Z = 136.912;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 131.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[451];
			Hash = 0xdb69770d;
			X = 39.4762;
			Y = -735.344;
			Z = 137.741;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 121.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[452];
			Hash = 0xdb69770d;
			X = 32.4759;
			Y = -738.835;
			Z = 138.481;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 111.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[453];
			Hash = 0xdb69770d;
			X = 24.3057;
			Y = -741.327;
			Z = 139.32;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 101.651;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[454];
			Hash = 0xdb69770d;
			X = 16.2957;
			Y = -742.247;
			Z = 140.09;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 91.6507;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[455];
			Hash = 0xdb69770d;
			X = 8.45573;
			Y = -741.807;
			Z = 140.77;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 80.9504;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[456];
			Hash = 0xdb69770d;
			X = -0.114249;
			Y = -740.277;
			Z = 141.68;
			Pitch = 6.00002;
			Roll = 90;
			Yaw = 77.8297;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[457];
			Hash = 0xdb69770d;
			X = -142.183;
			Y = -708.097;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[458];
			Hash = 0xdb69770d;
			X = -149.953;
			Y = -705.199;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[459];
			Hash = 0xdb69770d;
			X = -158.252;
			Y = -702.101;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[460];
			Hash = 0xdb69770d;
			X = -165.811;
			Y = -699.283;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[461];
			Hash = 0xdb69770d;
			X = -173.851;
			Y = -696.284;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[462];
			Hash = 0xdb69770d;
			X = -181.99;
			Y = -693.246;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[463];
			Hash = 0xdb69770d;
			X = -189.789;
			Y = -690.347;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[464];
			Hash = 0xdb69770d;
			X = -197.288;
			Y = -687.548;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[465];
			Hash = 0xdb69770d;
			X = -205.787;
			Y = -684.35;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[466];
			Hash = 0xdb69770d;
			X = -213.186;
			Y = -681.552;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[467];
			Hash = 0xdb69770d;
			X = -221.236;
			Y = -678.544;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[468];
			Hash = 0xdb69770d;
			X = -229.549;
			Y = -675.445;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[469];
			Hash = 0xdb69770d;
			X = -237.048;
			Y = -672.646;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[470];
			Hash = 0xdb69770d;
			X = -244.797;
			Y = -669.747;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[471];
			Hash = 0xdb69770d;
			X = -253.356;
			Y = -666.548;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[472];
			Hash = 0xdb69770d;
			X = -261.856;
			Y = -671.951;
			Z = 111.851;
			Pitch = 14.1;
			Roll = 80.5998;
			Yaw = 65.3194;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[473];


			//[474];
			Hash = 0xdb69770d;
			X = -265.047;
			Y = -670.504;
			Z = 111.191;
			Pitch = 15;
			Roll = 69.9999;
			Yaw = 60.8454;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[475];
			Hash = 0xdb69770d;
			X = -271.976;
			Y = -666.156;
			Z = 113.351;
			Pitch = 15;
			Roll = 71.1695;
			Yaw = 54.845;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[476];
			Hash = 0xdb69770d;
			X = -278.284;
			Y = -661.227;
			Z = 115.572;
			Pitch = 15;
			Roll = 73.0189;
			Yaw = 48.8443;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[477];
			Hash = 0xdb69770d;
			X = -283.902;
			Y = -655.83;
			Z = 117.652;
			Pitch = 15;
			Roll = 74.5883;
			Yaw = 42.8441;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[478];
			Hash = 0xdb69770d;
			X = -289.152;
			Y = -649.542;
			Z = 119.842;
			Pitch = 15;
			Roll = 76.2178;
			Yaw = 36.8438;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[479];
			Hash = 0xdb69770d;
			X = -293.55;
			Y = -643.055;
			Z = 121.922;
			Pitch = 15;
			Roll = 77.7272;
			Yaw = 30.8437;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[480];
			Hash = 0xdb69770d;
			X = -297.619;
			Y = -635.358;
			Z = 124.213;
			Pitch = 15.0001;
			Roll = 78.9668;
			Yaw = 24.8436;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[481];
			Hash = 0xdb69770d;
			X = -300.517;
			Y = -628.161;
			Z = 126.293;
			Pitch = 15.0001;
			Roll = 80.4263;
			Yaw = 18.8435;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[482];
			Hash = 0xdb69770d;
			X = -302.746;
			Y = -620.363;
			Z = 128.423;
			Pitch = 15.0001;
			Roll = 81.346;
			Yaw = 12.8435;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[483];
			Hash = 0xdb69770d;
			X = -304.126;
			Y = -612.865;
			Z = 130.453;
			Pitch = 15.0001;
			Roll = 82.7055;
			Yaw = 6.95342;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[484];
			Hash = 0xdb69770d;
			X = -304.684;
			Y = -604.686;
			Z = 132.613;
			Pitch = 15.0001;
			Roll = 83.7651;
			Yaw = 0.953418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[485];
			Hash = 0xdb69770d;
			X = -304.356;
			Y = -596.868;
			Z = 134.691;
			Pitch = 15.0002;
			Roll = 85.6244;
			Yaw = -6.64646;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[486];
			Hash = 0xdb69770d;
			X = -303.064;
			Y = -588.84;
			Z = 136.781;
			Pitch = 15.0002;
			Roll = 86.5737;
			Yaw = -11.6464;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[487];
			Hash = 0xdb69770d;
			X = -301.313;
			Y = -581.542;
			Z = 138.771;
			Pitch = 15.0002;
			Roll = 87.1634;
			Yaw = -15.6464;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[488];
			Hash = 0xdb69770d;
			X = -299.062;
			Y = -574.373;
			Z = 140.771;
			Pitch = 15.0002;
			Roll = 87.8932;
			Yaw = -19.6463;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[489];
			Hash = 0xdb69770d;
			X = -296.06;
			Y = -566.867;
			Z = 142.91;
			Pitch = 15.0002;
			Roll = 88.463;
			Yaw = -23.6462;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[490];
			Hash = 0xdb69770d;
			X = -292.759;
			Y = -559.941;
			Z = 144.94;
			Pitch = 15.0002;
			Roll = 89.1827;
			Yaw = -27.6461;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[491];
			Hash = 0xdb69770d;
			X = -288.466;
			Y = -553.004;
			Z = 147.14;
			Pitch = 15.0002;
			Roll = 91.3118;
			Yaw = -35.8459;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[492];
			Hash = 0xdb69770d;
			X = -227.935;
			Y = -476.679;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[493];
			Hash = 0xdb69770d;
			X = -114.76;
			Y = -769.675;
			Z = 130.383;
			Pitch = -2.97568e-009;
			Roll = 90;
			Yaw = -36.3771;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[494];
			Hash = 0xdb69770d;
			X = -222.234;
			Y = -469.479;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[495];
			Hash = 0xdb69770d;
			X = -216.764;
			Y = -462.578;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[496];
			Hash = 0xdb69770d;
			X = -211.363;
			Y = -455.778;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[497];
			Hash = 0xdb69770d;
			X = -205.823;
			Y = -448.777;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[498];
			Hash = 0xdb69770d;
			X = -200.832;
			Y = -442.477;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[499];
			Hash = 0xdb69770d;
			X = -195.592;
			Y = -435.876;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[500];
			Hash = 0xdb69770d;
			X = -190.202;
			Y = -429.076;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[501];
			Hash = 0xdb69770d;
			X = -184.961;
			Y = -422.476;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[502];
			Hash = 0xdb69770d;
			X = -179.661;
			Y = -415.775;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[503];
			Hash = 0xdb69770d;
			X = -174.551;
			Y = -409.335;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[504];
			Hash = 0xdb69770d;
			X = -168.921;
			Y = -402.234;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[505];
			Hash = 0xdb69770d;
			X = -163.85;
			Y = -395.834;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[506];
			Hash = 0xdb69770d;
			X = -158.62;
			Y = -389.233;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[507];
			Hash = 0xdb69770d;
			X = -153.709;
			Y = -383.033;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[508];
			Hash = 0xdb69770d;
			X = -148.878;
			Y = -376.933;
			Z = 145.183;
			Pitch = -8.19564e-008;
			Roll = 2.86815e-007;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[509];
			Hash = 0xdb69770d;
			X = -143.388;
			Y = -370.032;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[510];
			Hash = 0xdb69770d;
			X = -144.445;
			Y = -359.24;
			Z = 152.814;
			Pitch = 1.40667e-005;
			Roll = 89.9994;
			Yaw = -44.8178;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[511];
			Hash = 0xdb69770d;
			X = -144.445;
			Y = -359.24;
			Z = 152.814;
			Pitch = 1.40667e-005;
			Roll = 89.9994;
			Yaw = -44.8178;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[512];
			Hash = 0xdb69770d;
			X = -138.405;
			Y = -353.639;
			Z = 152.814;
			Pitch = 1.4067e-005;
			Roll = 89.9994;
			Yaw = -50.0177;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[513];
			Hash = 0xdb69770d;
			X = -131.955;
			Y = -348.639;
			Z = 152.814;
			Pitch = 1.4067e-005;
			Roll = 89.9994;
			Yaw = -54.4177;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[514];
			Hash = 0xdb69770d;
			X = -125.595;
			Y = -344.439;
			Z = 152.814;
			Pitch = 1.40669e-005;
			Roll = 89.9994;
			Yaw = -58.4176;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[515];
			Hash = 0xdb69770d;
			X = -119.125;
			Y = -340.439;
			Z = 152.814;
			Pitch = 1.40669e-005;
			Roll = 89.9994;
			Yaw = -58.4176;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[516];
			Hash = 0xdb69770d;
			X = -112.014;
			Y = -336.438;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -62.6175;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[517];
			Hash = 0xdb69770d;
			X = -105.214;
			Y = -333.238;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -66.5173;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[518];
			Hash = 0xdb69770d;
			X = -98.4144;
			Y = -330.638;
			Z = 152.814;
			Pitch = 1.40672e-005;
			Roll = 89.9994;
			Yaw = -71.017;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[519];
			Hash = 0xdb69770d;
			X = -90.4342;
			Y = -328.567;
			Z = 152.814;
			Pitch = 1.40672e-005;
			Roll = 89.9994;
			Yaw = -79.3165;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[520];
			Hash = 0xdb69770d;
			X = -82.1439;
			Y = -327.605;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -87.116;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[521];
			Hash = 0xdb69770d;
			X = -73.9839;
			Y = -327.863;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -95.7152;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[522];
			Hash = 0xdb69770d;
			X = -66.084;
			Y = -329.263;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -105.014;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[523];
			Hash = 0xdb69770d;
			X = -58.3243;
			Y = -332.182;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -115.614;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[524];
			Hash = 0xdb69770d;
			X = -50.6846;
			Y = -336.85;
			Z = 152.814;
			Pitch = 1.40672e-005;
			Roll = 89.9994;
			Yaw = -127.413;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[525];
			Hash = 0xdb69770d;
			X = -44.5348;
			Y = -342.659;
			Z = 152.814;
			Pitch = 1.40669e-005;
			Roll = 89.9994;
			Yaw = -139.611;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[526];
			Hash = 0xdb69770d;
			X = -39.895;
			Y = -349.359;
			Z = 152.814;
			Pitch = 1.4067e-005;
			Roll = 89.9994;
			Yaw = -151.109;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[527];
			Hash = 0xdb69770d;
			X = -36.8651;
			Y = -356.726;
			Z = 152.814;
			Pitch = 1.40672e-005;
			Roll = 89.9994;
			Yaw = -163.306;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[528];
			Hash = 0xdb69770d;
			X = -35.4053;
			Y = -364.727;
			Z = 152.814;
			Pitch = 1.40671e-005;
			Roll = 89.9994;
			Yaw = -175.404;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[529];
			Hash = 0xdb69770d;
			X = -35.5855;
			Y = -372.927;
			Z = 152.814;
			Pitch = 1.4067e-005;
			Roll = 89.9994;
			Yaw = 173.097;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[530];
			Hash = 0xdb69770d;
			X = -37.4157;
			Y = -380.828;
			Z = 152.814;
			Pitch = 1.4067e-005;
			Roll = 89.9994;
			Yaw = 161.697;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[531];
			Hash = 0xdb69770d;
			X = -41.0861;
			Y = -388.397;
			Z = 152.814;
			Pitch = 1.40672e-005;
			Roll = 89.9994;
			Yaw = 145.996;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[532];
			Hash = 0xdb69770d;
			X = -66.7677;
			Y = -417.633;
			Z = 139.204;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[533];
			Hash = 0xdb69770d;
			X = -70.8776;
			Y = -424.433;
			Z = 141.924;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[534];
			Hash = 0xdb69770d;
			X = -75.0974;
			Y = -431.434;
			Z = 144.744;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[535];
			Hash = 0xdb69770d;
			X = -79.1972;
			Y = -438.234;
			Z = 147.481;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[536];
			Hash = 0xdb69770d;
			X = -83.3569;
			Y = -445.123;
			Z = 150.254;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[537];
			Hash = 0xdb69770d;
			X = -87.1066;
			Y = -451.324;
			Z = 152.744;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[538];
			Hash = 0xdb69770d;
			X = -91.4153;
			Y = -458.464;
			Z = 155.618;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[539];
			Hash = 0xdb69770d;
			X = -95.775;
			Y = -465.664;
			Z = 158.518;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[540];
			Hash = 0xdb69770d;
			X = -100.245;
			Y = -473.065;
			Z = 161.498;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[541];
			Hash = 0xdb69770d;
			X = -103.875;
			Y = -479.065;
			Z = 163.908;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[542];
			Hash = 0xdb69770d;
			X = -108.218;
			Y = -486.266;
			Z = 166.803;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[543];
			Hash = 0xdb69770d;
			X = -112.202;
			Y = -492.866;
			Z = 169.449;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[544];
			Hash = 0xdb69770d;
			X = -116.251;
			Y = -499.566;
			Z = 172.138;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[545];
			Hash = 0xdb69770d;
			X = -120.665;
			Y = -506.867;
			Z = 175.074;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[546];
			Hash = 0xdb69770d;
			X = -124.707;
			Y = -513.569;
			Z = 177.767;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[547];
			Hash = 0xdb69770d;
			X = -128.027;
			Y = -519.071;
			Z = 179.971;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[548];
			Hash = 0xdb69770d;
			X = -131.828;
			Y = -525.373;
			Z = 182.511;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[549];
			Hash = 0xdb69770d;
			X = -135.386;
			Y = -531.275;
			Z = 184.883;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[550];
			Hash = 0xdb69770d;
			X = -139.235;
			Y = -537.647;
			Z = 187.44;
			Pitch = 19;
			Roll = -4.51484e-006;
			Yaw = 148.899;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[551];
			Hash = 0xdb69770d;
			X = -147.953;
			Y = -538.534;
			Z = 197.667;
			Pitch = 25;
			Roll = -89.9999;
			Yaw = 162.598;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[552];
			Hash = 0xdb69770d;
			X = -149.883;
			Y = -546.21;
			Z = 201.115;
			Pitch = 25;
			Roll = -90.5373;
			Yaw = 170.498;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[553];
			Hash = 0xdb69770d;
			X = -150.854;
			Y = -554.055;
			Z = 204.588;
			Pitch = 25;
			Roll = -90.5373;
			Yaw = 176.798;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[554];
			Hash = 0xdb69770d;
			X = -151.146;
			Y = -561.717;
			Z = 208.08;
			Pitch = 25.0001;
			Roll = -90.5373;
			Yaw = 179.245;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[555];
			Hash = 0xdb69770d;
			X = -150.946;
			Y = -568.924;
			Z = 211.19;
			Pitch = 25.0002;
			Roll = -90.5373;
			Yaw = -175.436;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[556];
			Hash = 0xdb69770d;
			X = -150.409;
			Y = -575.639;
			Z = 214.34;
			Pitch = 25.0002;
			Roll = -90.5373;
			Yaw = -175.436;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[557];
			Hash = 0xdb69770d;
			X = -130.703;
			Y = -782.043;
			Z = 149.509;
			Pitch = 4;
			Roll = 2.83503e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[558];
			Hash = 0xdb69770d;
			X = -131.344;
			Y = -773.904;
			Z = 148.936;
			Pitch = 4;
			Roll = 2.78154e-006;
			Yaw = -175.469;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[559];
			Hash = 0xdb69770d;
			X = -126.843;
			Y = -713.795;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[560];
			Hash = 0xdb69770d;
			X = -118.805;
			Y = -716.797;
			Z = 104.671;
			Pitch = 0;
			Roll = 0;
			Yaw = 69.5197;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[561];
			Hash = 0xdb69770d;
			X = -233.104;
			Y = -483.179;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[562];
			Hash = 0xdb69770d;
			X = -238.114;
			Y = -489.48;
			Z = 145.183;
			Pitch = 0;
			Roll = 0;
			Yaw = -38.418;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[563];
			Hash = 0xbafbd223;
			X = -144.097;
			Y = -604.22;
			Z = 210.722;
			Pitch = 0;
			Roll = -0;
			Yaw = -175.509;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[564];
			Hash = 0xb467c540;
			X = -133.784;
			Y = -742.899;
			Z = 241.084;
			Pitch = -2.66804e-008;
			Roll = -1.9;
			Yaw = -171.359;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[567];
			Hash = 0x7121ac4;
			X = -134.015;
			Y = -742.595;
			Z = 249.742;
			Pitch = 0;
			Roll = -0;
			Yaw = -174.849;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);


			HaxBy("Nadles");
		}
		void mmf_AroundEclipse()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdb69770d;
			X = -558.355;
			Y = -41.1361;
			Z = 42.6758;
			Pitch = 18.32;
			Roll = 1.39999;
			Yaw = -5.64607;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdb69770d;
			X = -557.457;
			Y = -32.5362;
			Z = 45.3758;
			Pitch = 17;
			Roll = 1.4;
			Yaw = -5.64611;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdb69770d;
			X = -556.659;
			Y = -23.9362;
			Z = 48.6157;
			Pitch = 24.82;
			Roll = 1.39999;
			Yaw = -5.64608;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdb69770d;
			X = -555.86;
			Y = -15.3362;
			Z = 52.6156;
			Pitch = 27.6201;
			Roll = 1.39999;
			Yaw = -4.84606;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdb69770d;
			X = -555.561;
			Y = -7.33615;
			Z = 57.4155;
			Pitch = 35.12;
			Roll = 1.39998;
			Yaw = -1.24604;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdb69770d;
			X = -555.262;
			Y = 0.163843;
			Z = 62.5154;
			Pitch = 35.12;
			Roll = 1.39998;
			Yaw = -1.94604;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdb69770d;
			X = -554.962;
			Y = 7.66386;
			Z = 67.7153;
			Pitch = 35.5199;
			Roll = 1.39998;
			Yaw = -1.94603;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdb69770d;
			X = -554.563;
			Y = 15.0639;
			Z = 73.0152;
			Pitch = 35.5199;
			Roll = 1.39998;
			Yaw = -1.94603;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdb69770d;
			X = -554.274;
			Y = 22.5639;
			Z = 78.4151;
			Pitch = 35.5199;
			Roll = 1.39998;
			Yaw = -1.94603;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdb69770d;
			X = -554.004;
			Y = 30.204;
			Z = 83.2951;
			Pitch = 29.1198;
			Roll = 1.39997;
			Yaw = -1.94602;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdb69770d;
			X = -554.305;
			Y = 37.5837;
			Z = 87.3552;
			Pitch = 30.6198;
			Roll = 1.39996;
			Yaw = 2.95395;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdb69770d;
			X = -555.406;
			Y = 45.1135;
			Z = 91.6551;
			Pitch = 31.0198;
			Roll = 1.59995;
			Yaw = 9.75393;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdb69770d;
			X = -556.809;
			Y = 50.8134;
			Z = 94.8551;
			Pitch = 28.2199;
			Roll = 1.59993;
			Yaw = 13.8539;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xdb69770d;
			X = -558.912;
			Y = 59.0532;
			Z = 97.3151;
			Pitch = 4.42004;
			Roll = 1.5999;
			Yaw = 14.7335;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xdb69770d;
			X = -561.333;
			Y = 67.9831;
			Z = 97.9852;
			Pitch = 4.42004;
			Roll = 1.5999;
			Yaw = 15.6535;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xdb69770d;
			X = -563.877;
			Y = 76.8131;
			Z = 98.4953;
			Pitch = 2.27006;
			Roll = 1.59988;
			Yaw = 17.093;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdb69770d;
			X = -566.802;
			Y = 84.613;
			Z = 98.8054;
			Pitch = 2.27006;
			Roll = 1.59988;
			Yaw = 22.9929;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdb69770d;
			X = -570.349;
			Y = 92.1129;
			Z = 99.1054;
			Pitch = 2.27006;
			Roll = 1.59987;
			Yaw = 26.7928;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdb69770d;
			X = -574.483;
			Y = 100.423;
			Z = 99.4255;
			Pitch = 2.27006;
			Roll = 1.59986;
			Yaw = 25.9924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xdb69770d;
			X = -578.489;
			Y = 108.723;
			Z = 99.7255;
			Pitch = 2.27006;
			Roll = 1.59986;
			Yaw = 25.9924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xdb69770d;
			X = -582.42;
			Y = 116.823;
			Z = 100.096;
			Pitch = 2.27006;
			Roll = 1.59986;
			Yaw = 25.9924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xdb69770d;
			X = -586.424;
			Y = 125.023;
			Z = 100.396;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xdb69770d;
			X = -590.428;
			Y = 133.323;
			Z = 100.696;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xdb69770d;
			X = -594.431;
			Y = 141.624;
			Z = 101.036;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xdb69770d;
			X = -598.354;
			Y = 149.724;
			Z = 101.376;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xdb69770d;
			X = -602.386;
			Y = 158.025;
			Z = 101.726;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xdb69770d;
			X = -606.372;
			Y = 166.226;
			Z = 102.066;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xdb69770d;
			X = -610.435;
			Y = 174.566;
			Z = 102.426;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xdb69770d;
			X = -614.49;
			Y = 182.916;
			Z = 102.777;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xdb69770d;
			X = -618.514;
			Y = 191.217;
			Z = 103.117;
			Pitch = 2.27005;
			Roll = 1.59986;
			Yaw = 25.8923;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xdb69770d;
			X = -622.448;
			Y = 198.918;
			Z = 103.367;
			Pitch = 2.27005;
			Roll = -0.500143;
			Yaw = 29.7922;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xdb69770d;
			X = -625.896;
			Y = 206.08;
			Z = 104.707;
			Pitch = 2.27004;
			Roll = -14.4999;
			Yaw = 33.4911;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xf4f1511e;
			X = -624.151;
			Y = 198.149;
			Z = 103.803;
			Pitch = -4.82988;
			Roll = -4.9986;
			Yaw = 34.301;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0x93948e5e;
			X = -620.587;
			Y = 199.998;
			Z = 103.754;
			Pitch = -5.89999;
			Roll = -8.99993;
			Yaw = 34.1727;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0x93948e5e;
			X = -618.254;
			Y = 202.142;
			Z = 104.519;
			Pitch = -3.92001;
			Roll = -18.9797;
			Yaw = 32.4426;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0x93948e5e;
			X = -616.607;
			Y = 202.955;
			Z = 105.683;
			Pitch = 4.20002;
			Roll = -53.8983;
			Yaw = 23.0371;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xdb69770d;
			X = -630.996;
			Y = 213.673;
			Z = 104.876;
			Pitch = 0.379961;
			Roll = -14.3097;
			Yaw = 34.7237;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xdb69770d;
			X = -636.29;
			Y = 220.774;
			Z = 104.936;
			Pitch = 0.379897;
			Roll = -14.3096;
			Yaw = 38.3529;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xdb69770d;
			X = -641.754;
			Y = 227.574;
			Z = 104.866;
			Pitch = 0.379861;
			Roll = -16.3096;
			Yaw = 40.9524;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xdb69770d;
			X = -647.636;
			Y = 234.484;
			Z = 104.926;
			Pitch = 0.379827;
			Roll = -17.5195;
			Yaw = 41.8219;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xdb69770d;
			X = -653.341;
			Y = 240.985;
			Z = 104.826;
			Pitch = 0.37983;
			Roll = -20.2194;
			Yaw = 42.8213;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xdb69770d;
			X = -659.546;
			Y = 247.586;
			Z = 104.826;
			Pitch = 0.379827;
			Roll = -22.0194;
			Yaw = 46.921;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xdb69770d;
			X = -666.051;
			Y = 253.787;
			Z = 104.826;
			Pitch = 0.37989;
			Roll = -22.9793;
			Yaw = 46.9207;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xdb69770d;
			X = -672.854;
			Y = 260.087;
			Z = 104.866;
			Pitch = 0.8799;
			Roll = -24.6791;
			Yaw = 49.6203;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xdb69770d;
			X = -679.517;
			Y = 266.018;
			Z = 104.866;
			Pitch = 0.879935;
			Roll = -27.8789;
			Yaw = 51.0199;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xdb69770d;
			X = -686.222;
			Y = 271.518;
			Z = 104.966;
			Pitch = 0.879958;
			Roll = -31.4788;
			Yaw = 56.0196;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xdb69770d;
			X = -693.726;
			Y = 276.318;
			Z = 104.966;
			Pitch = 0.879975;
			Roll = -33.8787;
			Yaw = 64.0184;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xdb69770d;
			X = -701.219;
			Y = 280.018;
			Z = 104.966;
			Pitch = 0.879975;
			Roll = -37.6786;
			Yaw = 68.8181;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xdb69770d;
			X = -709.323;
			Y = 283.219;
			Z = 105.187;
			Pitch = 0.87997;
			Roll = -38.9785;
			Yaw = 70.6175;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xdb69770d;
			X = -718.038;
			Y = 286.019;
			Z = 105.187;
			Pitch = 0.879967;
			Roll = -39.7783;
			Yaw = 76.5269;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xdb69770d;
			X = -726.941;
			Y = 288.119;
			Z = 105.187;
			Pitch = 0.97996;
			Roll = -42.3783;
			Yaw = 82.0263;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xdb69770d;
			X = -735.746;
			Y = 289.019;
			Z = 105.187;
			Pitch = 0.979961;
			Roll = -43.3783;
			Yaw = 89.0255;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xdb69770d;
			X = -744.432;
			Y = 288.74;
			Z = 105.187;
			Pitch = 0.979971;
			Roll = -45.6782;
			Yaw = 99.2542;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xdb69770d;
			X = -753.527;
			Y = 287.191;
			Z = 105.367;
			Pitch = 0.979966;
			Roll = -45.9782;
			Yaw = 101.154;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xdb69770d;
			X = -762.522;
			Y = 285.422;
			Z = 105.497;
			Pitch = 0.979965;
			Roll = -47.0782;
			Yaw = 103.553;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xdb69770d;
			X = -771.125;
			Y = 283.092;
			Z = 105.497;
			Pitch = 0.979962;
			Roll = -47.0782;
			Yaw = 108.353;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xdb69770d;
			X = -779.8;
			Y = 280.283;
			Z = 105.627;
			Pitch = 0.979939;
			Roll = -49.4279;
			Yaw = 111.352;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xdb69770d;
			X = -787.604;
			Y = 276.613;
			Z = 105.627;
			Pitch = 0.979952;
			Roll = -52.7279;
			Yaw = 124.551;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xdb69770d;
			X = -794.607;
			Y = 271.313;
			Z = 105.627;
			Pitch = 0.979961;
			Roll = -54.8276;
			Yaw = 134.45;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xdb69770d;
			X = -799.342;
			Y = 264.625;
			Z = 105.627;
			Pitch = 0.979954;
			Roll = -54.8276;
			Yaw = 155.55;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xdb69770d;
			X = -801.745;
			Y = 256.525;
			Z = 105.727;
			Pitch = 0.979971;
			Roll = -54.8274;
			Yaw = 171.349;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xdb69770d;
			X = -801.476;
			Y = 248.376;
			Z = 105.727;
			Pitch = 1.17997;
			Roll = -55.3573;
			Yaw = -166.188;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xdb69770d;
			X = -798.588;
			Y = 240.245;
			Z = 105.817;
			Pitch = 1.18002;
			Roll = -57.737;
			Yaw = -148.423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xdb69770d;
			X = -793.16;
			Y = 233.745;
			Z = 106.017;
			Pitch = 1.18001;
			Roll = -58.627;
			Yaw = -130.819;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xdb69770d;
			X = -786.122;
			Y = 228.555;
			Z = 106.147;
			Pitch = 1.17996;
			Roll = -59.8467;
			Yaw = -118.118;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xdb69770d;
			X = -778.025;
			Y = 225.396;
			Z = 106.347;
			Pitch = 1.17995;
			Roll = -59.8467;
			Yaw = -104.217;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xdb69770d;
			X = -769.029;
			Y = 224.497;
			Z = 106.747;
			Pitch = 5.97998;
			Roll = -51.1461;
			Yaw = -87.6161;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 0xdb69770d;
			X = -759.753;
			Y = 225.398;
			Z = 107.347;
			Pitch = 7.77998;
			Roll = -40.9458;
			Yaw = -87.6161;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xdb69770d;
			X = -750.656;
			Y = 225.898;
			Z = 108.447;
			Pitch = 6.27997;
			Roll = -38.1458;
			Yaw = -81.4158;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xdb69770d;
			X = -741.261;
			Y = 227.698;
			Z = 109.747;
			Pitch = 11.28;
			Roll = -38.1457;
			Yaw = -75.4155;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xdb69770d;
			X = -732.666;
			Y = 229.999;
			Z = 111.747;
			Pitch = 14.08;
			Roll = -37.7456;
			Yaw = -69.1153;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xdb69770d;
			X = -724.77;
			Y = 233.299;
			Z = 113.747;
			Pitch = 12.2799;
			Roll = -37.7454;
			Yaw = -61.715;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xdb69770d;
			X = -719.276;
			Y = 237.4;
			Z = 115.247;
			Pitch = 12.28;
			Roll = -40.8452;
			Yaw = -46.7148;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xdb69770d;
			X = -714.221;
			Y = 243.63;
			Z = 116.947;
			Pitch = 12.28;
			Roll = -40.8452;
			Yaw = -31.2145;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xdb69770d;
			X = -709.524;
			Y = 251.231;
			Z = 118.947;
			Pitch = 12.2799;
			Roll = -41.3451;
			Yaw = -31.2145;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xdb69770d;
			X = -707.63;
			Y = 257.712;
			Z = 120.447;
			Pitch = 13.0799;
			Roll = -47.3451;
			Yaw = -2.3141;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xdb69770d;
			X = -708.332;
			Y = 265.512;
			Z = 122.247;
			Pitch = 13.0799;
			Roll = -53.7448;
			Yaw = 17.9858;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xdb69770d;
			X = -712.038;
			Y = 272.413;
			Z = 124.247;
			Pitch = 9.77995;
			Roll = -53.7442;
			Yaw = 38.4853;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xdb69770d;
			X = -718.044;
			Y = 279.213;
			Z = 125.647;
			Pitch = 9.77995;
			Roll = -53.944;
			Yaw = 47.5849;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xdb69770d;
			X = -724.647;
			Y = 284.914;
			Z = 127.246;
			Pitch = 9.77995;
			Roll = -53.944;
			Yaw = 53.2846;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xdb69770d;
			X = -731.752;
			Y = 289.414;
			Z = 128.847;
			Pitch = 9.77995;
			Roll = -57.8438;
			Yaw = 65.9839;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xdb69770d;
			X = -745.975;
			Y = 289.994;
			Z = 131.373;
			Pitch = -2.59998;
			Roll = 6.35492;
			Yaw = 82.8157;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0xdb69770d;
			X = -754.958;
			Y = 290.56;
			Z = 130.954;
			Pitch = 3.37055;
			Roll = -10.135;
			Yaw = -95.4539;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0xdb69770d;
			X = -763.922;
			Y = 291.365;
			Z = 131.107;
			Pitch = 5.67999;
			Roll = 10.9575;
			Yaw = 85.7806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0xdb69770d;
			X = -772.817;
			Y = 291.815;
			Z = 132.077;
			Pitch = 5.67999;
			Roll = 13.0575;
			Yaw = 86.6802;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0xdb69770d;
			X = -782.325;
			Y = 292.195;
			Z = 132.987;
			Pitch = 4.71002;
			Roll = 17.4574;
			Yaw = 82.3797;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0xdb69770d;
			X = -791.189;
			Y = 292.724;
			Z = 133.587;
			Pitch = 4.71002;
			Roll = 23.5573;
			Yaw = 79.9794;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0xdb69770d;
			X = -799.594;
			Y = 294.375;
			Z = 134.057;
			Pitch = 3.31002;
			Roll = 26.8571;
			Yaw = 73.9786;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0xdb69770d;
			X = -807.168;
			Y = 297.275;
			Z = 134.347;
			Pitch = 2.41005;
			Roll = 26.8568;
			Yaw = 64.7879;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 0xdb69770d;
			X = -813.774;
			Y = 301.475;
			Z = 134.747;
			Pitch = 3.01004;
			Roll = 27.6564;
			Yaw = 50.1863;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 0xdb69770d;
			X = -819.078;
			Y = 307.175;
			Z = 135.247;
			Pitch = 7.11006;
			Roll = 28.6561;
			Yaw = 35.3853;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0xdb69770d;
			X = -823.982;
			Y = 314.676;
			Z = 136.848;
			Pitch = 13.8101;
			Roll = 28.656;
			Yaw = 30.9849;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0xdb69770d;
			X = -827.186;
			Y = 322.076;
			Z = 139.148;
			Pitch = 17.9101;
			Roll = 31.3558;
			Yaw = 16.6844;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0xdb69770d;
			X = -828.591;
			Y = 330.077;
			Z = 142.048;
			Pitch = 23.9101;
			Roll = 33.1556;
			Yaw = 4.48433;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0xdb69770d;
			X = -827.594;
			Y = 336.877;
			Z = 145.149;
			Pitch = 24.9102;
			Roll = 40.955;
			Yaw = -19.2155;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0xdb69770d;
			X = -823.897;
			Y = 343.278;
			Z = 148.349;
			Pitch = 25.8101;
			Roll = 44.1545;
			Yaw = -37.5151;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0xdb69770d;
			X = -819.2;
			Y = 349.168;
			Z = 151.949;
			Pitch = 25.4101;
			Roll = 48.5543;
			Yaw = -42.6151;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0xdb69770d;
			X = -813.106;
			Y = 354.969;
			Z = 155.85;
			Pitch = 24.3102;
			Roll = 51.9536;
			Yaw = -56.5146;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0xdb69770d;
			X = -806.109;
			Y = 359.669;
			Z = 159.55;
			Pitch = 24.3102;
			Roll = 51.9535;
			Yaw = -59.0145;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0xdb69770d;
			X = -798.613;
			Y = 364.069;
			Z = 163.35;
			Pitch = 24.3102;
			Roll = 51.9534;
			Yaw = -61.4145;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0xdb69770d;
			X = -790.618;
			Y = 367.169;
			Z = 166.551;
			Pitch = 18.6101;
			Roll = 51.853;
			Yaw = -80.8133;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0xdb69770d;
			X = -781.822;
			Y = 368.669;
			Z = 169.521;
			Pitch = 17.8702;
			Roll = 49.8524;
			Yaw = -83.7809;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0xdb69770d;
			X = -773.125;
			Y = 369.469;
			Z = 172.221;
			Pitch = 17.8702;
			Roll = 50.8523;
			Yaw = -87.1806;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0xdb69770d;
			X = -764.93;
			Y = 369.169;
			Z = 175.021;
			Pitch = 17.8702;
			Roll = 51.6521;
			Yaw = -98.2793;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0xdb69770d;
			X = -756.934;
			Y = 367.169;
			Z = 177.721;
			Pitch = 17.4702;
			Roll = 54.4513;
			Yaw = -109.078;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0xdb69770d;
			X = -748.739;
			Y = 364.269;
			Z = 180.422;
			Pitch = 17.4702;
			Roll = 54.4513;
			Yaw = -110.278;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0xdb69770d;
			X = -741.143;
			Y = 360.469;
			Z = 182.922;
			Pitch = 17.4702;
			Roll = 56.2508;
			Yaw = -123.077;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0xdb69770d;
			X = -733.746;
			Y = 355.669;
			Z = 185.722;
			Pitch = 17.4702;
			Roll = 56.2506;
			Yaw = -124.776;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0xdb69770d;
			X = -727.751;
			Y = 350.168;
			Z = 188.323;
			Pitch = 17.4702;
			Roll = 58.3502;
			Yaw = -141.873;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0xdb69770d;
			X = -723.755;
			Y = 343.168;
			Z = 190.923;
			Pitch = 17.4702;
			Roll = 63.2498;
			Yaw = -160.069;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0xdb69770d;
			X = -722.059;
			Y = 335.067;
			Z = 193.523;
			Pitch = 17.4702;
			Roll = 65.7495;
			Yaw = -176.565;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0xdb69770d;
			X = -722.561;
			Y = 326.667;
			Z = 196.224;
			Pitch = 17.4702;
			Roll = 68.0492;
			Yaw = 169.536;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0xdb69770d;
			X = -724.863;
			Y = 318.366;
			Z = 198.924;
			Pitch = 17.4702;
			Roll = 69.2491;
			Yaw = 158.336;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0xdb69770d;
			X = -728.066;
			Y = 310.266;
			Z = 201.724;
			Pitch = 17.4702;
			Roll = 69.2491;
			Yaw = 158.336;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0xdb69770d;
			X = -732.068;
			Y = 302.565;
			Z = 204.425;
			Pitch = 17.4702;
			Roll = 69.649;
			Yaw = 145.936;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			Hash = 0xdb69770d;
			X = -737.17;
			Y = 295.565;
			Z = 207.225;
			Pitch = 17.4702;
			Roll = 69.649;
			Yaw = 138.835;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[119];
			Hash = 0xdb69770d;
			X = -743.244;
			Y = 289.356;
			Z = 209.925;
			Pitch = 17.4702;
			Roll = 69.649;
			Yaw = 131.435;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 0xdb69770d;
			X = -750.151;
			Y = 284.555;
			Z = 212.626;
			Pitch = 17.4702;
			Roll = 69.649;
			Yaw = 118.034;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 0xdb69770d;
			X = -758.156;
			Y = 281.618;
			Z = 215.405;
			Pitch = 17.4702;
			Roll = 68.9488;
			Yaw = 99.8633;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 0xdb69770d;
			X = -766.961;
			Y = 280.618;
			Z = 218.205;
			Pitch = 17.4702;
			Roll = 67.8488;
			Yaw = 89.5627;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 0xdb69770d;
			X = -782.667;
			Y = 282.118;
			Z = 217.506;
			Pitch = 12.7701;
			Roll = 2.3467;
			Yaw = 83.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 0xdb69770d;
			X = -791.468;
			Y = 283.198;
			Z = 219.466;
			Pitch = 12.2702;
			Roll = 2.34669;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 0xdb69770d;
			X = -800.453;
			Y = 284.289;
			Z = 221.416;
			Pitch = 12.2702;
			Roll = 2.34669;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 0xdb69770d;
			X = -809.258;
			Y = 285.389;
			Z = 223.316;
			Pitch = 12.5702;
			Roll = 2.34668;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 0xdb69770d;
			X = -818.062;
			Y = 286.489;
			Z = 225.516;
			Pitch = 14.9702;
			Roll = 2.34668;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 0xdb69770d;
			X = -826.967;
			Y = 287.569;
			Z = 227.837;
			Pitch = 14.9702;
			Roll = 2.34668;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 0xdb69770d;
			X = -835.673;
			Y = 288.639;
			Z = 230.177;
			Pitch = 14.9702;
			Roll = 2.34668;
			Yaw = 83.0619;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 0xdb69770d;
			X = -843.982;
			Y = 290.139;
			Z = 231.377;
			Pitch = 6.27024;
			Roll = 2.64658;
			Yaw = 74.66;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 0xdb69770d;
			X = -849.487;
			Y = 293.139;
			Z = 231.677;
			Pitch = 5.07022;
			Roll = 2.64657;
			Yaw = 50.6587;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 0xdb69770d;
			X = -854.791;
			Y = 298.54;
			Z = 231.677;
			Pitch = 1.17022;
			Roll = 2.54651;
			Yaw = 32.5573;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 0xdb69770d;
			X = -857.895;
			Y = 305.14;
			Z = 231.677;
			Pitch = 1.17021;
			Roll = 2.14651;
			Yaw = 18.657;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 0xdb69770d;
			X = -859.198;
			Y = 311.941;
			Z = 231.777;
			Pitch = 1.17021;
			Roll = 2.0465;
			Yaw = 0.956847;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];
			Hash = 0xdb69770d;
			X = -858.299;
			Y = 318.341;
			Z = 231.877;
			Pitch = 1.17021;
			Roll = 2.0465;
			Yaw = -20.9429;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[136];
			Hash = 0xdb69770d;
			X = -855.301;
			Y = 325.641;
			Z = 231.877;
			Pitch = 1.17021;
			Roll = 2.0465;
			Yaw = -35.6427;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 0xdb69770d;
			X = -850.004;
			Y = 332.142;
			Z = 232.027;
			Pitch = 1.17021;
			Roll = 2.0465;
			Yaw = -41.1427;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 0xdb69770d;
			X = -845.008;
			Y = 336.242;
			Z = 232.027;
			Pitch = 1.17023;
			Roll = 2.04647;
			Yaw = -63.9423;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[139];
			Hash = 0xdb69770d;
			X = -838.012;
			Y = 338.742;
			Z = 231.927;
			Pitch = 1.17024;
			Roll = 2.04646;
			Yaw = -82.0411;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[140];
			Hash = 0xdb69770d;
			X = -828.965;
			Y = 340.002;
			Z = 231.827;
			Pitch = -1.52976;
			Roll = 2.04646;
			Yaw = -82.0411;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[141];
			Hash = 0xdb69770d;
			X = -820.369;
			Y = 341.202;
			Z = 231.607;
			Pitch = -1.52977;
			Roll = 2.04646;
			Yaw = -82.0411;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[142];
			Hash = 0xdb69770d;
			X = -806.776;
			Y = 341.402;
			Z = 230.428;
			Pitch = -12.9397;
			Roll = -0.193569;
			Yaw = -90.3589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[143];
			Hash = 0xdb69770d;
			X = -812.58;
			Y = 341.533;
			Z = 231.228;
			Pitch = -6.56968;
			Roll = -0.193566;
			Yaw = -90.3589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[144];
			/*Hash = 0x2b3ad141;
			X = -800.808;
			Y = 345.779;
			Z = 229.418;
			Pitch = 0;
			Roll = -0;
			Yaw = 92.9412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);*/

			//[145];
			Hash = 0xdf8c1fd4;
			X = -798.614;
			Y = 348.962;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[146];
			Hash = 0xdf8c1fd4;
			X = -794.125;
			Y = 348.952;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[147];
			Hash = 0xdf8c1fd4;
			X = -789.626;
			Y = 348.952;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[148];
			Hash = 0xdf8c1fd4;
			X = -785.127;
			Y = 348.952;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[149];
			Hash = 0xdf8c1fd4;
			X = -780.628;
			Y = 348.952;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[150];
			Hash = 0xdf8c1fd4;
			X = -776.129;
			Y = 348.952;
			Z = 229.683;
			Pitch = 0;
			Roll = -0;
			Yaw = 90.1482;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[151];
			Hash = 0xf246f3d4;
			X = -798.692;
			Y = 342.964;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[152];
			Hash = 0xf246f3d4;
			X = -802.095;
			Y = 336.064;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[153];
			Hash = 0xf246f3d4;
			X = -800.899;
			Y = 348.765;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[154];
			Hash = 0xf246f3d4;
			X = -793.603;
			Y = 348.765;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[155];
			Hash = 0xf246f3d4;
			X = -786.206;
			Y = 348.765;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[156];
			Hash = 0xf246f3d4;
			X = -778.41;
			Y = 348.765;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[157];
			Hash = 0xf246f3d4;
			X = -793.72;
			Y = 338.764;
			Z = 233.254;
			Pitch = 0;
			Roll = 0;
			Yaw = 79.0558;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[158];
			Hash = 0x333332ed;
			X = -794.007;
			Y = 334.713;
			Z = 229.613;
			Pitch = 0;
			Roll = -0;
			Yaw = -177.297;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[159];
			/*Hash = 0x2b3ad141;
			X = -554.88;
			Y = -46.1038;
			Z = 41.1869;
			Pitch = 0;
			Roll = -0;
			Yaw = -2.85531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);*/

			//[160];
			Hash = 0xa4d4093e;
			X = -558.444;
			Y = -45.7522;
			Z = 47.2007;
			Pitch = -0;
			Roll = -0;
			Yaw = -11.8898;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[161];
			Hash = 0xf246f3d4;
			X = -566.393;
			Y = -49.1439;
			Z = 44.1008;
			Pitch = -0;
			Roll = -0;
			Yaw = -4.4589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[162];
			Hash = 0xf246f3d4;
			X = -551.098;
			Y = -49.1439;
			Z = 44.1008;
			Pitch = 0;
			Roll = 0;
			Yaw = -4.4589;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[163];
			Hash = 0x7121ac4;
			X = -727.526;
			Y = 271.215;
			Z = 131.191;
			Pitch = 0;
			Roll = 0;
			Yaw = 78.6674;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[164];
			Hash = 0x7121ac4;
			X = -807.327;
			Y = 328.915;
			Z = 231.892;
			Pitch = 0;
			Roll = 0;
			Yaw = 78.6674;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("Zynh");
		}
		void mmf_AirportWallRide()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0x93948e5e;
			X = -988.153;
			Y = -2560.78;
			Z = 36.0355;
			Pitch = -4.9;
			Roll = -0;
			Yaw = -73.8877;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x93948e5e;
			X = -983.555;
			Y = -2559.37;
			Z = 37.5354;
			Pitch = -4.9;
			Roll = -2.14226e-007;
			Yaw = -73.8877;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xe40a0f8e;
			X = -978.807;
			Y = -2558.13;
			Z = 37.4697;
			Pitch = 7.43714e-007;
			Roll = -7.22704e-007;
			Yaw = -71.1749;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xe40a0f8e;
			X = -975.408;
			Y = -2557.22;
			Z = 37.4697;
			Pitch = 8.17085e-007;
			Roll = -2.33203e-006;
			Yaw = -78.5743;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xe40a0f8e;
			X = -972.109;
			Y = -2556.82;
			Z = 37.4697;
			Pitch = 8.17082e-007;
			Roll = -2.33203e-006;
			Yaw = -89.2734;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xaeb63c4b;
			X = -965.147;
			Y = -2557.71;
			Z = 34.8298;
			Pitch = 12.2;
			Roll = -0;
			Yaw = 79.7268;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xaeb63c4b;
			X = -954.25;
			Y = -2559.69;
			Z = 32.4397;
			Pitch = 12.2;
			Roll = -0;
			Yaw = 79.7268;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xaeb63c4b;
			X = -944.002;
			Y = -2561.19;
			Z = 30.6397;
			Pitch = 7.10001;
			Roll = 0.199998;
			Yaw = 84.1264;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xaeb63c4b;
			X = -932.605;
			Y = -2561.88;
			Z = 28.5797;
			Pitch = 13.3103;
			Roll = 0.0199324;
			Yaw = 89.1258;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xaeb63c4b;
			X = -921.147;
			Y = -2562.07;
			Z = 25.5596;
			Pitch = 16.3102;
			Roll = 0.0899236;
			Yaw = 89.1258;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xaeb63c4b;
			X = -909.568;
			Y = -2562.05;
			Z = 22.1796;
			Pitch = 16.3102;
			Roll = 0.0899234;
			Yaw = 92.8949;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xaeb63c4b;
			X = -907.516;
			Y = -2561.56;
			Z = 22.5196;
			Pitch = 0.000293928;
			Roll = 0.0899181;
			Yaw = 103.924;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xaeb63c4b;
			X = -899.354;
			Y = -2559.71;
			Z = 22.6496;
			Pitch = -1.40953;
			Roll = 9.01882;
			Yaw = 115.223;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xaeb63c4b;
			X = -887.657;
			Y = -2555.59;
			Z = 23.6496;
			Pitch = 1.29054;
			Roll = 31.3185;
			Yaw = 129.722;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xaeb63c4b;
			X = -888.857;
			Y = -2553.59;
			Z = 22.7496;
			Pitch = 0.190472;
			Roll = 9.01876;
			Yaw = 125.622;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xaeb63c4b;
			X = -882.561;
			Y = -2547.48;
			Z = 22.5496;
			Pitch = 0.19046;
			Roll = 9.01876;
			Yaw = 142.121;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xaeb63c4b;
			X = -879.563;
			Y = -2548.78;
			Z = 24.0496;
			Pitch = -0.709555;
			Roll = 42.5179;
			Yaw = 137.622;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xaeb63c4b;
			X = -872.965;
			Y = -2539.36;
			Z = 24.4496;
			Pitch = -0.109446;
			Roll = 51.0171;
			Yaw = 155.821;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xaeb63c4b;
			X = -870.068;
			Y = -2529.85;
			Z = 25.3496;
			Pitch = -0.109427;
			Roll = 68.716;
			Yaw = 175.121;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xaeb63c4b;
			X = -869.871;
			Y = -2522.43;
			Z = 26.7496;
			Pitch = 1.29059;
			Roll = 91.0137;
			Yaw = -172.276;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xaeb63c4b;
			X = -871.374;
			Y = -2515.12;
			Z = 26.6496;
			Pitch = 1.29059;
			Roll = 91.0137;
			Yaw = -165.774;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xaeb63c4b;
			X = -873.577;
			Y = -2507.61;
			Z = 26.8496;
			Pitch = 1.59059;
			Roll = 96.6128;
			Yaw = -161.573;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xaeb63c4b;
			X = -871.084;
			Y = -2520.48;
			Z = 24.2496;
			Pitch = 0.0905913;
			Roll = 97.5117;
			Yaw = -174.17;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xaeb63c4b;
			X = -871.185;
			Y = -2527.35;
			Z = 24.2496;
			Pitch = -1.10941;
			Roll = 97.5117;
			Yaw = 178.732;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xaeb63c4b;
			X = -872.488;
			Y = -2531.34;
			Z = 24.2496;
			Pitch = -1.10941;
			Roll = 97.5117;
			Yaw = 168.332;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xaeb63c4b;
			X = -875.691;
			Y = -2539.83;
			Z = 23.9496;
			Pitch = -1.10941;
			Roll = 97.5117;
			Yaw = 162.332;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xaeb63c4b;
			X = -891.337;
			Y = -2483.32;
			Z = 23.9496;
			Pitch = -0.00940597;
			Roll = 90.0112;
			Yaw = -119.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xaeb63c4b;
			X = -891.337;
			Y = -2483.32;
			Z = 21.4595;
			Pitch = -0.00940597;
			Roll = 90.0112;
			Yaw = -119.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xaeb63c4b;
			X = -891.337;
			Y = -2483.32;
			Z = 18.8795;
			Pitch = -0.00940597;
			Roll = 90.0112;
			Yaw = -119.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xaeb63c4b;
			X = -891.337;
			Y = -2483.32;
			Z = 17.3895;
			Pitch = -0.00940597;
			Roll = 90.0112;
			Yaw = -119.965;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xaeb63c4b;
			X = -952.885;
			Y = -2498.2;
			Z = 24.3895;
			Pitch = -0.00940596;
			Roll = 90.0112;
			Yaw = -28.7643;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xaeb63c4b;
			X = -952.885;
			Y = -2498.2;
			Z = 21.8495;
			Pitch = -0.00940596;
			Roll = 90.0112;
			Yaw = -28.7642;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xaeb63c4b;
			X = -952.885;
			Y = -2498.2;
			Z = 19.4494;
			Pitch = -0.00940596;
			Roll = 90.0112;
			Yaw = -28.7642;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xaeb63c4b;
			X = -952.885;
			Y = -2498.2;
			Z = 17.8494;
			Pitch = -0.00940596;
			Roll = 90.0112;
			Yaw = -28.7642;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xaeb63c4b;
			X = -944.485;
			Y = -2552.1;
			Z = 24.0494;
			Pitch = -0.00940583;
			Roll = 90.0112;
			Yaw = 43.1254;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xaeb63c4b;
			X = -941.686;
			Y = -2554.09;
			Z = 24.0494;
			Pitch = -0.00940578;
			Roll = 90.0112;
			Yaw = 51.625;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xaeb63c4b;
			X = -944.485;
			Y = -2552.1;
			Z = 21.6494;
			Pitch = -0.00940583;
			Roll = 90.0112;
			Yaw = 43.1254;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xaeb63c4b;
			X = -944.485;
			Y = -2552.1;
			Z = 19.1494;
			Pitch = -0.00940583;
			Roll = 90.0112;
			Yaw = 43.1254;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xaeb63c4b;
			X = -944.485;
			Y = -2552.1;
			Z = 17.2494;
			Pitch = -0.00940583;
			Roll = 90.0112;
			Yaw = 43.1254;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xaeb63c4b;
			X = -941.686;
			Y = -2554.09;
			Z = 21.4494;
			Pitch = -0.00940578;
			Roll = 90.0112;
			Yaw = 51.625;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xaeb63c4b;
			X = -941.686;
			Y = -2554.09;
			Z = 19.0494;
			Pitch = -0.00940578;
			Roll = 90.0112;
			Yaw = 51.625;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xaeb63c4b;
			X = -935.058;
			Y = -2558.41;
			Z = 24.0494;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 59.9412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xaeb63c4b;
			X = -935.058;
			Y = -2558.41;
			Z = 21.5594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 59.9412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xaeb63c4b;
			X = -935.058;
			Y = -2558.41;
			Z = 19.0594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 59.9412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xaeb63c4b;
			X = -935.058;
			Y = -2558.41;
			Z = 17.4594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 59.9412;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xaeb63c4b;
			X = -941.686;
			Y = -2554.09;
			Z = 17.2494;
			Pitch = -0.00940578;
			Roll = 90.0112;
			Yaw = 51.625;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xaeb63c4b;
			X = -929.663;
			Y = -2560.89;
			Z = 17.4594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 73.6403;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xaeb63c4b;
			X = -929.663;
			Y = -2560.89;
			Z = 19.8594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 73.6403;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xaeb63c4b;
			X = -929.663;
			Y = -2560.89;
			Z = 22.3594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 73.6403;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xaeb63c4b;
			X = -929.663;
			Y = -2560.89;
			Z = 24.0594;
			Pitch = -0.00940577;
			Roll = 90.0112;
			Yaw = 73.6403;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xaeb63c4b;
			X = -880.215;
			Y = -2540.64;
			Z = 23.6294;
			Pitch = -0.00940537;
			Roll = 90.0107;
			Yaw = -30.5389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xaeb63c4b;
			X = -880.215;
			Y = -2540.64;
			Z = 21.0594;
			Pitch = -0.00940537;
			Roll = 90.0107;
			Yaw = -30.5389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xaeb63c4b;
			X = -880.215;
			Y = -2540.64;
			Z = 18.4594;
			Pitch = -0.00940537;
			Roll = 90.0107;
			Yaw = -30.5389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xaeb63c4b;
			X = -880.215;
			Y = -2540.64;
			Z = 17.7594;
			Pitch = -0.00940537;
			Roll = 90.0107;
			Yaw = -30.5389;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 24.6238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 25.8238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 27.0238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 28.3238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 29.6238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 30.9238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 32.2238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xb467c540;
			X = -915.649;
			Y = -2520.41;
			Z = 33.5238;
			Pitch = 0;
			Roll = 0;
			Yaw = 22.2198;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xaeb63c4b;
			X = -926.96;
			Y = -2561.67;
			Z = 14.9494;
			Pitch = -0.00940576;
			Roll = 90.0112;
			Yaw = 73.6398;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0x93948e5e;
			X = -930.332;
			Y = -2554.97;
			Z = 12.9877;
			Pitch = 0;
			Roll = -29.6998;
			Yaw = -168.829;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0x93948e5e;
			X = -928.332;
			Y = -2557.96;
			Z = 14.4877;
			Pitch = 24;
			Roll = -55.8987;
			Yaw = -149.122;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("Loyalty Gaming");
		}
		void mmf_MazeBankPieceTrack()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xdb69770d;
			X = -77.8202;
			Y = -807.626;
			Z = 325.107;
			Pitch = 1.773;
			Roll = -1.06773e-007;
			Yaw = 16.517;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xdb69770d;
			X = -80.1098;
			Y = -799.819;
			Z = 324.108;
			Pitch = -13.88;
			Roll = 3.95754e-006;
			Yaw = 16.517;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xdb69770d;
			X = -82.5692;
			Y = -791.56;
			Z = 321.319;
			Pitch = -22;
			Roll = -9.20824e-007;
			Yaw = 16.5168;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xdb69770d;
			X = -84.659;
			Y = -784.425;
			Z = 317.483;
			Pitch = -31.4708;
			Roll = 1.30132e-005;
			Yaw = 16.5165;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xdb69770d;
			X = -86.5286;
			Y = -778.117;
			Z = 313.073;
			Pitch = -35.4309;
			Roll = -0;
			Yaw = 16.5167;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xdb69770d;
			X = -88.4379;
			Y = -771.668;
			Z = 308.201;
			Pitch = -36.7305;
			Roll = 1.06528e-006;
			Yaw = 16.5167;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xdb69770d;
			X = -90.3901;
			Y = -764.98;
			Z = 302.828;
			Pitch = -38.3282;
			Roll = 1.08834e-006;
			Yaw = 16.5166;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xdb69770d;
			X = -92.16;
			Y = -759.058;
			Z = 297.938;
			Pitch = -38.3282;
			Roll = 1.08834e-006;
			Yaw = 16.5166;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xdb69770d;
			X = -93.7199;
			Y = -753.761;
			Z = 293.838;
			Pitch = -33.8083;
			Roll = 1.02752e-006;
			Yaw = 16.5166;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xdb69770d;
			X = -95.7199;
			Y = -747.062;
			Z = 289.558;
			Pitch = -27.3082;
			Roll = 4.8043e-006;
			Yaw = 16.5166;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xdb69770d;
			X = -97.7398;
			Y = -740.274;
			Z = 286.258;
			Pitch = -22.5082;
			Roll = 6.00712e-006;
			Yaw = 16.5165;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xdb69770d;
			X = -99.5997;
			Y = -734.076;
			Z = 284.028;
			Pitch = -13.7282;
			Roll = -0;
			Yaw = 16.5165;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xdb69770d;
			X = -142.382;
			Y = -598.801;
			Z = 211.853;
			Pitch = 0;
			Roll = -0;
			Yaw = -163.282;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xdb69770d;
			X = -66.5627;
			Y = -659.022;
			Z = 138.996;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xdb69770d;
			X = -72.5726;
			Y = -669.027;
			Z = 136.096;
			Pitch = -5.01989;
			Roll = -60.3732;
			Yaw = -155.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xdb69770d;
			X = -68.6726;
			Y = -675.927;
			Z = 135.496;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xdb69770d;
			X = -64.6717;
			Y = -681.629;
			Z = 134.888;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xdb69770d;
			X = -60.1718;
			Y = -688.134;
			Z = 134.218;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xdb69770d;
			X = -56.042;
			Y = -694.077;
			Z = 133.588;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xdb69770d;
			X = -51.9025;
			Y = -700.01;
			Z = 132.938;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xdb69770d;
			X = -47.5026;
			Y = -706.513;
			Z = 132.378;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xdb69770d;
			X = -43.273;
			Y = -712.697;
			Z = 131.868;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xdb69770d;
			X = -39.1831;
			Y = -718.6;
			Z = 131.238;
			Pitch = -5.01988;
			Roll = -60.3731;
			Yaw = -145.227;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xdb69770d;
			X = -35.3831;
			Y = -723.202;
			Z = 130.538;
			Pitch = -5.01986;
			Roll = -56.973;
			Yaw = -138.425;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xdb69770d;
			X = -30.1833;
			Y = -728.005;
			Z = 129.638;
			Pitch = -5.01983;
			Roll = -53.4729;
			Yaw = -131.824;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xdb69770d;
			X = -25.1833;
			Y = -731.808;
			Z = 129.038;
			Pitch = -5.01983;
			Roll = -49.0726;
			Yaw = -125.323;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xdb69770d;
			X = -19.6833;
			Y = -735.911;
			Z = 128.238;
			Pitch = -5.01984;
			Roll = -45.8724;
			Yaw = -129.023;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xdb69770d;
			X = -15.1833;
			Y = -739.013;
			Z = 127.739;
			Pitch = -8.91987;
			Roll = -44.0724;
			Yaw = -121.322;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xdb69770d;
			X = -10.0832;
			Y = -741.514;
			Z = 126.639;
			Pitch = -8.91984;
			Roll = -40.0723;
			Yaw = -114.221;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xdb69770d;
			X = -4.08323;
			Y = -743.697;
			Z = 125.619;
			Pitch = -8.91983;
			Roll = -36.0722;
			Yaw = -108.221;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xdb69770d;
			X = 2.91677;
			Y = -750.697;
			Z = 118.619;
			Pitch = 3.0802;
			Roll = -1.07209;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xdb69770d;
			X = 9.48677;
			Y = -752.742;
			Z = 119.009;
			Pitch = 3.0802;
			Roll = -1.07209;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xdb69770d;
			X = 16.6868;
			Y = -754.946;
			Z = 119.409;
			Pitch = 3.0802;
			Roll = -1.07209;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xdb69770d;
			X = 24.9868;
			Y = -757.548;
			Z = 119.449;
			Pitch = -1.81981;
			Roll = -1.07209;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xdb69770d;
			X = 32.3869;
			Y = -759.87;
			Z = 118.809;
			Pitch = -6.51981;
			Roll = -1.07208;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xdb69770d;
			X = 40.4867;
			Y = -762.372;
			Z = 117.009;
			Pitch = -17.0198;
			Roll = -1.07208;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xdb69770d;
			X = 47.6866;
			Y = -764.575;
			Z = 114.509;
			Pitch = -18.2198;
			Roll = -1.07208;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xdb69770d;
			X = 53.8864;
			Y = -766.477;
			Z = 111.909;
			Pitch = -21.1198;
			Roll = -1.07208;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xdb69770d;
			X = 61.7302;
			Y = -768.918;
			Z = 108.749;
			Pitch = -21.1198;
			Roll = -1.07208;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xdb69770d;
			X = 68.5301;
			Y = -770.699;
			Z = 105.779;
			Pitch = -21.1198;
			Roll = 3.4079;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xdb69770d;
			X = 74.1301;
			Y = -771.801;
			Z = 103.179;
			Pitch = -21.1198;
			Roll = 11.1078;
			Yaw = -107.22;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xdb69770d;
			X = 80.63;
			Y = -773.005;
			Z = 100.179;
			Pitch = -21.1198;
			Roll = 19.5077;
			Yaw = -109.02;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xdb69770d;
			X = 88.4299;
			Y = -775.009;
			Z = 96.7795;
			Pitch = -21.1198;
			Roll = 25.2077;
			Yaw = -115.419;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xdb69770d;
			X = 95.4298;
			Y = -778.012;
			Z = 93.7796;
			Pitch = -21.1198;
			Roll = 28.6075;
			Yaw = -119.719;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xdb69770d;
			X = 101.73;
			Y = -780.456;
			Z = 91.2796;
			Pitch = -21.1198;
			Roll = 36.9072;
			Yaw = -121.618;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xdb69770d;
			X = 107.13;
			Y = -783.468;
			Z = 89.0797;
			Pitch = -21.0199;
			Roll = 41.3052;
			Yaw = -134.316;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xdb69770d;
			X = 112.73;
			Y = -788.771;
			Z = 86.3797;
			Pitch = -21.0199;
			Roll = 43.7051;
			Yaw = -138.516;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xdb69770d;
			X = 117.429;
			Y = -794.788;
			Z = 83.5797;
			Pitch = -16.0197;
			Roll = 36.4022;
			Yaw = -141.212;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xdb69770d;
			X = 122.629;
			Y = -799.792;
			Z = 81.0798;
			Pitch = -16.0196;
			Roll = 36.4022;
			Yaw = -130.81;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xdb69770d;
			X = 126.929;
			Y = -803.395;
			Z = 79.1199;
			Pitch = -16.0196;
			Roll = 36.4022;
			Yaw = -125.709;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xdb69770d;
			X = 132.93;
			Y = -806.998;
			Z = 76.6199;
			Pitch = -16.0196;
			Roll = 36.4022;
			Yaw = -118.509;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xdb69770d;
			X = 137.53;
			Y = -809.503;
			Z = 75.1001;
			Pitch = -16.0196;
			Roll = 36.4022;
			Yaw = -119.598;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xdb69770d;
			X = 143.531;
			Y = -812.807;
			Z = 73.1702;
			Pitch = -15.3197;
			Roll = 37.8019;
			Yaw = -121.596;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xdb69770d;
			X = 149.431;
			Y = -816.811;
			Z = 71.2703;
			Pitch = -15.3196;
			Roll = 37.8017;
			Yaw = -132.694;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xdb69770d;
			X = 154.032;
			Y = -821.416;
			Z = 69.4703;
			Pitch = -15.3196;
			Roll = 37.8014;
			Yaw = -146.192;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xdb69770d;
			X = 157.833;
			Y = -828.22;
			Z = 67.3703;
			Pitch = -11.9195;
			Roll = 37.8014;
			Yaw = -162.687;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xdb69770d;
			X = 159.733;
			Y = -834.825;
			Z = 65.6703;
			Pitch = -11.9195;
			Roll = 37.8014;
			Yaw = -171.685;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xdb69770d;
			X = 160.684;
			Y = -840.229;
			Z = 64.4804;
			Pitch = -11.9195;
			Roll = 38.4607;
			Yaw = 178.717;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xdb69770d;
			X = 160.884;
			Y = -844.13;
			Z = 63.8804;
			Pitch = -11.9195;
			Roll = 38.4605;
			Yaw = 166.317;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xdb69770d;
			X = 159.585;
			Y = -850.134;
			Z = 62.7804;
			Pitch = -11.8194;
			Roll = 39.2602;
			Yaw = 162.317;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xdb69770d;
			X = 157.835;
			Y = -854.997;
			Z = 61.4502;
			Pitch = -11.2194;
			Roll = 35.4796;
			Yaw = 160.703;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xdb69770d;
			X = 155.106;
			Y = -862.904;
			Z = 59.5501;
			Pitch = -16.0195;
			Roll = 34.279;
			Yaw = 160.703;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xdb69770d;
			X = 152.707;
			Y = -870.207;
			Z = 57.2501;
			Pitch = -16.0194;
			Roll = 32.8784;
			Yaw = 160.703;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xdb69770d;
			X = 150.409;
			Y = -876.913;
			Z = 55.2499;
			Pitch = -8.61942;
			Roll = 29.678;
			Yaw = 162.703;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xdb69770d;
			X = -139.638;
			Y = -606.997;
			Z = 211.772;
			Pitch = 0.600001;
			Roll = -7.31084e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xdb69770d;
			X = -137.337;
			Y = -614.703;
			Z = 211.772;
			Pitch = 0.600001;
			Roll = -7.31084e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xdb69770d;
			X = -134.935;
			Y = -622.806;
			Z = 211.772;
			Pitch = 0.600001;
			Roll = -7.28416e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xdb69770d;
			X = -132.835;
			Y = -629.91;
			Z = 211.772;
			Pitch = 0.600001;
			Roll = -7.28416e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xdb69770d;
			X = -130.835;
			Y = -636.913;
			Z = 211.772;
			Pitch = 0.600001;
			Roll = -7.27082e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xdb69770d;
			X = -128.535;
			Y = -644.616;
			Z = 212.472;
			Pitch = -9.59997;
			Roll = -9.74137e-006;
			Yaw = 16.5318;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xdb69770d;
			X = -126.095;
			Y = -652.82;
			Z = 214.372;
			Pitch = -14.67;
			Roll = -1.63271e-005;
			Yaw = 16.5318;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xdb69770d;
			X = -124.295;
			Y = -658.722;
			Z = 216.472;
			Pitch = -20.77;
			Roll = -1.68926e-005;
			Yaw = 16.5317;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xdb69770d;
			X = -144.517;
			Y = -590.601;
			Z = 211.9;
			Pitch = 0.600001;
			Roll = -7.31084e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xdb69770d;
			X = -146.707;
			Y = -583.204;
			Z = 211.72;
			Pitch = -2.6;
			Roll = -7.31797e-006;
			Yaw = 16.5319;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xdb69770d;
			X = -148.836;
			Y = -576.007;
			Z = 211.2;
			Pitch = -4.57;
			Roll = -7.49435e-006;
			Yaw = 16.5318;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xdb69770d;
			X = -151.416;
			Y = -567.329;
			Z = 210.139;
			Pitch = -8.86;
			Roll = -5.40053e-006;
			Yaw = 16.5318;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xdb69770d;
			X = -153.815;
			Y = -559.332;
			Z = 208.309;
			Pitch = -15.4;
			Roll = -3.14377e-005;
			Yaw = 16.5317;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xdb69770d;
			X = -156.145;
			Y = -551.434;
			Z = 205.319;
			Pitch = -24.04;
			Roll = -2.52413e-005;
			Yaw = 16.5316;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0xdb69770d;
			X = -158.424;
			Y = -543.736;
			Z = 200.919;
			Pitch = -33;
			Roll = -1.67971e-005;
			Yaw = 16.5316;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0xdb69770d;
			X = -165.154;
			Y = -533.041;
			Z = 193.372;
			Pitch = -19.3002;
			Roll = 51.5388;
			Yaw = -8.95866;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0xdb69770d;
			X = -163.751;
			Y = -526.498;
			Z = 191.074;
			Pitch = -16.5002;
			Roll = 48.8383;
			Yaw = -17.0585;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0xdb69770d;
			X = -161.412;
			Y = -520.902;
			Z = 189.443;
			Pitch = -15.1002;
			Roll = 47.355;
			Yaw = -33.6874;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0xdb69770d;
			X = -158.011;
			Y = -515.903;
			Z = 187.944;
			Pitch = -15.1001;
			Roll = 47.355;
			Yaw = -45.2874;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0xdb69770d;
			X = -153.571;
			Y = -511.793;
			Z = 186.264;
			Pitch = -15.1001;
			Roll = 46.3548;
			Yaw = -56.7471;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0xdb69770d;
			X = -146.691;
			Y = -507.791;
			Z = 184.184;
			Pitch = -15.1001;
			Roll = 46.3546;
			Yaw = -67.4163;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 0xdb69770d;
			X = -140.373;
			Y = -505.607;
			Z = 182.104;
			Pitch = -16.7901;
			Roll = 46.3546;
			Yaw = -78.8075;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 0xdb69770d;
			X = -133.612;
			Y = -504.307;
			Z = 179.863;
			Pitch = -16.7901;
			Roll = 46.8136;
			Yaw = -88.1931;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0xdb69770d;
			X = -126.664;
			Y = -504.634;
			Z = 177.793;
			Pitch = -15.4901;
			Roll = 45.6132;
			Yaw = -103.886;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0xdb69770d;
			X = -120.413;
			Y = -506.334;
			Z = 175.894;
			Pitch = -15.4901;
			Roll = 45.6132;
			Yaw = -113.885;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0xdb69770d;
			X = -114.083;
			Y = -509.834;
			Z = 173.763;
			Pitch = -15.4901;
			Roll = 43.9624;
			Yaw = -128.684;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0xdb69770d;
			X = -108.513;
			Y = -515.035;
			Z = 171.643;
			Pitch = -15.49;
			Roll = 43.0017;
			Yaw = -140.882;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0xdb69770d;
			X = -103.953;
			Y = -520.738;
			Z = 169.623;
			Pitch = -15.49;
			Roll = 43.0017;
			Yaw = -140.882;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0xdb69770d;
			X = -99.5526;
			Y = -526.222;
			Z = 167.703;
			Pitch = -15.49;
			Roll = 43.0017;
			Yaw = -140.882;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0xdb69770d;
			X = -95.4527;
			Y = -531.225;
			Z = 165.903;
			Pitch = -15.49;
			Roll = 43.0017;
			Yaw = -140.882;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0xdb69770d;
			X = -90.5528;
			Y = -536.929;
			Z = 163.904;
			Pitch = -15.49;
			Roll = 43.0017;
			Yaw = -139.982;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0xdb69770d;
			X = -86.9528;
			Y = -541.333;
			Z = 162.304;
			Pitch = -11.6899;
			Roll = 43.301;
			Yaw = -150.477;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0xdb69770d;
			X = -82.7529;
			Y = -548.138;
			Z = 160.805;
			Pitch = -9.18988;
			Roll = 46.7008;
			Yaw = -151.874;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0xdb69770d;
			X = -79.0327;
			Y = -555.221;
			Z = 159.575;
			Pitch = -9.18985;
			Roll = 52.2603;
			Yaw = -163.174;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0xdb69770d;
			X = -166.23;
			Y = -538.227;
			Z = 194.876;
			Pitch = -16.5901;
			Roll = 54.1586;
			Yaw = -6.2731;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0xdb69770d;
			X = -76.1328;
			Y = -563.425;
			Z = 158.375;
			Pitch = -9.18985;
			Roll = 56.4602;
			Yaw = -163.174;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0xdb69770d;
			X = -74.0726;
			Y = -571.92;
			Z = 156.935;
			Pitch = -9.18986;
			Roll = 57.109;
			Yaw = -171.912;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0xdb69770d;
			X = -72.732;
			Y = -579.846;
			Z = 155.795;
			Pitch = -9.08984;
			Roll = 59.4567;
			Yaw = -171.912;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0xdb69770d;
			X = -71.5727;
			Y = -588.629;
			Z = 154.736;
			Pitch = -9.18986;
			Roll = 62.0073;
			Yaw = -176.811;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0xdb69770d;
			X = -70.6527;
			Y = -596.003;
			Z = 153.605;
			Pitch = -9.01986;
			Roll = 65.6268;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0xdb69770d;
			X = -68.4528;
			Y = -617.003;
			Z = 145.605;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0xdb69770d;
			X = -68.8228;
			Y = -608.565;
			Z = 146.905;
			Pitch = -8.13984;
			Roll = 2.51628;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0xdb69770d;
			X = -68.0528;
			Y = -625.607;
			Z = 144.236;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0xdb69770d;
			X = -67.6529;
			Y = -634.712;
			Z = 142.836;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0xdb69770d;
			X = -67.3228;
			Y = -642.215;
			Z = 141.636;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0xdb69770d;
			X = -66.9228;
			Y = -650.919;
			Z = 140.266;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0xdb69770d;
			X = -66.5627;
			Y = -659.022;
			Z = 138.996;
			Pitch = -9.01989;
			Roll = 2.62632;
			Yaw = -177.531;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("Nadles");
		}
		void mmf_lscTroll()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;
			float zoffset = 0.0f;

			//[3];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 40.6761;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 43.4459;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 46.2759;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 49.0254;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 51.7654;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xaeb63c4b;
			X = -411.645;
			Y = -80.6875;
			Z = 52.5952;
			Pitch = 6.28494e-006;
			Roll = -3.28251e-005;
			Yaw = -49.6867;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xaeb63c4b;
			X = -407.224;
			Y = -82.5072;
			Z = 55.3149;
			Pitch = 6.28491e-006;
			Roll = -3.28251e-005;
			Yaw = 29.7131;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xaeb63c4b;
			X = -407.224;
			Y = -82.5072;
			Z = 58.1149;
			Pitch = 6.28491e-006;
			Roll = -3.28251e-005;
			Yaw = 29.7131;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xaeb63c4b;
			X = -403.583;
			Y = -88.917;
			Z = 55.3148;
			Pitch = 6.28491e-006;
			Roll = -3.28251e-005;
			Yaw = 29.7131;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0xaeb63c4b;
			X = -403.583;
			Y = -88.917;
			Z = 58.1148;
			Pitch = 6.28491e-006;
			Roll = -3.28251e-005;
			Yaw = 29.7131;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0xaeb63c4b;
			X = -395.47;
			Y = -94.4367;
			Z = 55.2846;
			Pitch = 6.28489e-006;
			Roll = -3.28251e-005;
			Yaw = 80.9028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0xaeb63c4b;
			X = -395.47;
			Y = -94.4367;
			Z = 58.0845;
			Pitch = 6.28489e-006;
			Roll = -3.28251e-005;
			Yaw = 80.9028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0xaeb63c4b;
			X = -388.939;
			Y = -95.4957;
			Z = 55.3845;
			Pitch = 6.28489e-006;
			Roll = -3.28251e-005;
			Yaw = 80.9028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0xaeb63c4b;
			X = -388.939;
			Y = -95.4957;
			Z = 58.1844;
			Pitch = 6.28489e-006;
			Roll = -3.28251e-005;
			Yaw = 80.9028;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0xaeb63c4b;
			X = -382.376;
			Y = -91.5649;
			Z = 55.2743;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0xaeb63c4b;
			X = -382.376;
			Y = -91.5649;
			Z = 58.1842;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0xaeb63c4b;
			X = -378.645;
			Y = -81.285;
			Z = 58.1842;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[20];
			Hash = 0xaeb63c4b;
			X = -378.645;
			Y = -81.285;
			Z = 55.3841;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[21];
			Hash = 0xaeb63c4b;
			X = -376.045;
			Y = -74.0851;
			Z = 55.3841;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[22];
			Hash = 0xaeb63c4b;
			X = -376.045;
			Y = -74.0851;
			Z = 58.184;
			Pitch = 6.28472e-006;
			Roll = -3.2825e-005;
			Yaw = 160.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[23];
			Hash = 0xaeb63c4b;
			X = -367.624;
			Y = -69.4441;
			Z = 55.3836;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[24];
			Hash = 0xaeb63c4b;
			X = -367.624;
			Y = -69.4441;
			Z = 58.1835;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[25];
			Hash = 0xaeb63c4b;
			X = -357.224;
			Y = -73.0441;
			Z = 58.1835;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[26];
			Hash = 0xaeb63c4b;
			X = -357.224;
			Y = -73.0441;
			Z = 55.3835;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[27];
			Hash = 0xaeb63c4b;
			X = -346.223;
			Y = -76.8439;
			Z = 55.3835;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[28];
			Hash = 0xaeb63c4b;
			X = -346.223;
			Y = -76.8439;
			Z = 58.1733;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[29];
			Hash = 0xaeb63c4b;
			X = -335.422;
			Y = -80.5438;
			Z = 58.1733;
			Pitch = 6.28466e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[30];
			Hash = 0xaeb63c4b;
			X = -335.422;
			Y = -80.5438;
			Z = 55.3732;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[31];
			Hash = 0xaeb63c4b;
			X = -325.022;
			Y = -84.1438;
			Z = 55.3732;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[32];
			Hash = 0xaeb63c4b;
			X = -325.022;
			Y = -84.1438;
			Z = 58.1731;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[33];
			Hash = 0xaeb63c4b;
			X = -314.721;
			Y = -87.7437;
			Z = 58.1731;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[34];
			Hash = 0xaeb63c4b;
			X = -314.721;
			Y = -87.7437;
			Z = 55.3731;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[35];
			Hash = 0xaeb63c4b;
			X = -311.28;
			Y = -88.9335;
			Z = 55.3731;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[36];
			Hash = 0xaeb63c4b;
			X = -311.28;
			Y = -88.9335;
			Z = 58.173;
			Pitch = 6.28465e-006;
			Roll = -3.2825e-005;
			Yaw = -109.026;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[37];
			Hash = 0xaeb63c4b;
			X = -304.577;
			Y = -84.1331;
			Z = 55.3724;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[38];
			Hash = 0xaeb63c4b;
			X = -304.577;
			Y = -84.1331;
			Z = 58.1724;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[39];
			Hash = 0xaeb63c4b;
			X = -300.877;
			Y = -73.3333;
			Z = 58.1724;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[40];
			Hash = 0xaeb63c4b;
			X = -300.877;
			Y = -73.3333;
			Z = 55.4023;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[41];
			Hash = 0xaeb63c4b;
			X = -297.903;
			Y = -64.6937;
			Z = 55.4023;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[42];
			Hash = 0xaeb63c4b;
			X = -297.903;
			Y = -64.6937;
			Z = 58.1722;
			Pitch = 6.28461e-006;
			Roll = -3.2825e-005;
			Yaw = -19.0758;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[43];
			Hash = 0xaeb63c4b;
			X = -301.003;
			Y = -58.6039;
			Z = 55.3319;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[44];
			Hash = 0xaeb63c4b;
			X = -301.003;
			Y = -58.6039;
			Z = 58.1814;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[45];
			Hash = 0xaeb63c4b;
			X = -311.704;
			Y = -55.0041;
			Z = 58.1814;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[46];
			Hash = 0xaeb63c4b;
			X = -311.704;
			Y = -55.0041;
			Z = 55.3814;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[47];
			Hash = 0xaeb63c4b;
			X = -321.905;
			Y = -51.6041;
			Z = 55.3814;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[48];
			Hash = 0xaeb63c4b;
			X = -321.905;
			Y = -51.6041;
			Z = 58.1813;
			Pitch = 6.28449e-006;
			Roll = -3.28249e-005;
			Yaw = 71.4833;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[49];
			Hash = 0xaeb63c4b;
			X = -412.233;
			Y = -89.197;
			Z = 40.6761;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[50];
			Hash = 0xaeb63c4b;
			X = -412.233;
			Y = -89.197;
			Z = 43.4656;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[51];
			Hash = 0xaeb63c4b;
			X = -412.233;
			Y = -89.197;
			Z = 46.2651;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[52];
			Hash = 0xaeb63c4b;
			X = -406.462;
			Y = -99.6265;
			Z = 40.6761;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[53];
			Hash = 0xaeb63c4b;
			X = -406.462;
			Y = -99.6265;
			Z = 43.4654;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[54];
			Hash = 0xaeb63c4b;
			X = -406.462;
			Y = -99.6265;
			Z = 46.2549;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[55];
			Hash = 0xaeb63c4b;
			X = -400.561;
			Y = -110.226;
			Z = 40.6761;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[56];
			Hash = 0xaeb63c4b;
			X = -400.561;
			Y = -110.226;
			Z = 43.476;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[57];
			Hash = 0xaeb63c4b;
			X = -400.561;
			Y = -110.226;
			Z = 46.276;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[58];
			Hash = 0xaeb63c4b;
			X = -395;
			Y = -120.226;
			Z = 40.6761;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[59];
			Hash = 0xaeb63c4b;
			X = -395;
			Y = -120.226;
			Z = 43.4456;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[60];
			Hash = 0xaeb63c4b;
			X = -395;
			Y = -120.226;
			Z = 46.2551;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[61];
			Hash = 0xaeb63c4b;
			X = -389.31;
			Y = -130.526;
			Z = 40.6761;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[62];
			Hash = 0xaeb63c4b;
			X = -389.31;
			Y = -130.526;
			Z = 43.4156;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[63];
			Hash = 0xaeb63c4b;
			X = -389.31;
			Y = -130.526;
			Z = 46.2551;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[64];
			Hash = 0xaeb63c4b;
			X = -383.979;
			Y = -140.135;
			Z = 40.676;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[65];
			Hash = 0xaeb63c4b;
			X = -383.979;
			Y = -140.135;
			Z = 43.3955;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[66];
			Hash = 0xaeb63c4b;
			X = -383.979;
			Y = -140.135;
			Z = 46.2351;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[67];
			Hash = 0xaeb63c4b;
			X = -378.518;
			Y = -149.934;
			Z = 40.6659;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[68];
			Hash = 0xaeb63c4b;
			X = -378.518;
			Y = -149.934;
			Z = 43.4354;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[69];
			Hash = 0xaeb63c4b;
			X = -378.518;
			Y = -149.934;
			Z = 46.1849;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[70];
			Hash = 0xaeb63c4b;
			X = -372.697;
			Y = -160.433;
			Z = 37.8653;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[71];
			Hash = 0xaeb63c4b;
			X = -372.697;
			Y = -160.433;
			Z = 40.6148;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[72];
			Hash = 0xaeb63c4b;
			X = -372.697;
			Y = -160.433;
			Z = 43.4143;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[73];
			Hash = 0xaeb63c4b;
			X = -372.697;
			Y = -160.433;
			Z = 46.1338;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[74];
			Hash = 0xaeb63c4b;
			X = -375.537;
			Y = -155.303;
			Z = 37.8653;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[75];
			Hash = 0xaeb63c4b;
			X = -366.797;
			Y = -171.032;
			Z = 37.8653;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[76];
			Hash = 0xaeb63c4b;
			X = -366.797;
			Y = -171.032;
			Z = 40.5848;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[77];
			Hash = 0xaeb63c4b;
			X = -366.797;
			Y = -171.032;
			Z = 43.3443;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[78];
			Hash = 0xaeb63c4b;
			X = -366.797;
			Y = -171.032;
			Z = 46.1339;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[79];
			Hash = 0xaeb63c4b;
			X = -362.576;
			Y = -178.561;
			Z = 37.8653;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[80];
			Hash = 0xaeb63c4b;
			X = -362.576;
			Y = -178.561;
			Z = 40.5748;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[81];
			Hash = 0xaeb63c4b;
			X = -362.576;
			Y = -178.561;
			Z = 43.3144;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[82];
			Hash = 0xaeb63c4b;
			X = -362.576;
			Y = -178.561;
			Z = 46.1239;
			Pitch = 6.28488e-006;
			Roll = -3.28251e-005;
			Yaw = 29.0628;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[83];
			Hash = 0xaeb63c4b;
			X = -354.376;
			Y = -179.261;
			Z = 35.0345;
			Pitch = 6.28484e-006;
			Roll = -3.28251e-005;
			Yaw = 121.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[84];
			Hash = 0xaeb63c4b;
			X = -354.376;
			Y = -179.261;
			Z = 37.834;
			Pitch = 6.28484e-006;
			Roll = -3.28251e-005;
			Yaw = 121.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[85];
			Hash = 0xaeb63c4b;
			X = -354.376;
			Y = -179.261;
			Z = 40.6235;
			Pitch = 6.28484e-006;
			Roll = -3.28251e-005;
			Yaw = 121.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[86];
			Hash = 0xaeb63c4b;
			X = -354.376;
			Y = -179.261;
			Z = 43.403;
			Pitch = 6.28484e-006;
			Roll = -3.28251e-005;
			Yaw = 121.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[87];
			Hash = 0xaeb63c4b;
			X = -354.376;
			Y = -179.261;
			Z = 46.1526;
			Pitch = 6.28484e-006;
			Roll = -3.28251e-005;
			Yaw = 121.062;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[88];
			Hash = 0xaeb63c4b;
			X = -406.093;
			Y = -74.5773;
			Z = 55.3149;
			Pitch = 6.2849e-006;
			Roll = -3.28251e-005;
			Yaw = 134.172;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[89];
			Hash = 0xaeb63c4b;
			X = -406.093;
			Y = -74.5773;
			Z = 58.0845;
			Pitch = 6.2849e-006;
			Roll = -3.28251e-005;
			Yaw = 134.172;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[90];
			Hash = 0xaeb63c4b;
			X = -397.682;
			Y = -66.3774;
			Z = 55.3149;
			Pitch = 6.2849e-006;
			Roll = -3.28251e-005;
			Yaw = 134.172;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[91];
			Hash = 0xaeb63c4b;
			X = -397.682;
			Y = -66.3774;
			Z = 58.0944;
			Pitch = 6.2849e-006;
			Roll = -3.28251e-005;
			Yaw = 134.172;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[92];
			Hash = 0xaeb63c4b;
			X = -391.161;
			Y = -56.1776;
			Z = 55.3149;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[93];
			Hash = 0xaeb63c4b;
			X = -391.161;
			Y = -56.1776;
			Z = 58.1045;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[94];
			Hash = 0xaeb63c4b;
			X = -387.26;
			Y = -44.9778;
			Z = 55.3149;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[95];
			Hash = 0xaeb63c4b;
			X = -387.26;
			Y = -44.9778;
			Z = 58.1045;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[96];
			Hash = 0xaeb63c4b;
			X = -383.828;
			Y = -34.9883;
			Z = 55.3149;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[97];
			Hash = 0xaeb63c4b;
			X = -383.828;
			Y = -34.9883;
			Z = 58.1045;
			Pitch = 6.28476e-006;
			Roll = -3.2825e-005;
			Yaw = 160.857;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[98];
			Hash = 0xaeb63c4b;
			X = -377.428;
			Y = -32.1685;
			Z = 55.3149;
			Pitch = 6.2847e-006;
			Roll = -3.2825e-005;
			Yaw = -109.042;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[99];
			Hash = 0xaeb63c4b;
			X = -377.428;
			Y = -32.1685;
			Z = 58.0945;
			Pitch = 6.2847e-006;
			Roll = -3.2825e-005;
			Yaw = -109.042;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[100];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 43.3968;
			Pitch = 0.293143;
			Roll = -0.000225326;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[101];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 43.3968;
			Pitch = 0.293143;
			Roll = -0.000225326;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[102];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 44.2467;
			Pitch = 0.293143;
			Roll = -0.000225326;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[103];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 45.1366;
			Pitch = 0.293143;
			Roll = -0.000225332;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[104];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 46.0264;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[105];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 46.8962;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[106];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 47.756;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[107];
			Hash = 0x18c49531;
			X = -396.142;
			Y = -66.6631;
			Z = 48.6559;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[108];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 44.2466;
			Pitch = 0.293143;
			Roll = -0.000225326;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[109];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 45.1465;
			Pitch = 0.293143;
			Roll = -0.000225326;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[110];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 46.0363;
			Pitch = 0.293143;
			Roll = -0.000225332;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[111];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 46.9062;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[112];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 47.756;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[113];
			Hash = 0x18c49531;
			X = -395.242;
			Y = -64.2631;
			Z = 48.6559;
			Pitch = 0.293143;
			Roll = -0.000225339;
			Yaw = 68.9746;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[114];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 37.7333;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[115];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 38.5832;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[116];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 39.463;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[117];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 40.3428;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[118];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 41.2127;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[119];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 42.0825;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[120];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 42.9723;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[121];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 43.8721;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[122];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 44.722;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[123];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 45.5918;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[124];
			Hash = 0xb6cacc47;
			X = -381.935;
			Y = -98.142;
			Z = 46.5117;
			Pitch = 0;
			Roll = 0;
			Yaw = -18.8999;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[125];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 46.0758;
			Pitch = 0.293143;
			Roll = -0.000225392;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[126];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 46.8955;
			Pitch = 0.293143;
			Roll = -0.000225392;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[127];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 47.6953;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[128];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 48.5152;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[129];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 49.365;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[130];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 50.2449;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[131];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 51.1047;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[132];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 51.8845;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[133];
			Hash = 0x18c49531;
			X = -295.442;
			Y = -98.2632;
			Z = 52.6543;
			Pitch = 0.293143;
			Roll = -0.000225386;
			Yaw = 70.8745;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[134];
			Hash = 0x745f3383;
			X = -337.219;
			Y = -139.611;
			Z = 36.453;
			Pitch = -89.0414;
			Roll = 115.935;
			Yaw = 180;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[135];
			Hash = 0x745f3383;
			X = -337.219;
			Y = -139.611;
			Z = 53.9525;
			Pitch = 89.4088;
			Roll = -86.8646;
			Yaw = 4.60465;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[137];
			Hash = 0x745f3383;
			X = -353.219;
			Y = -125.611;
			Z = 36.553;
			Pitch = -89.0414;
			Roll = 115.935;
			Yaw = 180;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			//[138];
			Hash = 0x745f3383;
			X = -376.219;
			Y = -65.6114;
			Z = 52.1523;
			Pitch = 89.4304;
			Roll = -43.8644;
			Yaw = 4.60464;
			mm_PlaceObject(Hash, X, Y, Z - zoffset, Pitch, Roll, Yaw, false);

			HaxBy("Nadles");
		}
		void mmf_lscSkatePark()
		{
			float X, Y, Z, Pitch, Roll, Yaw; Hash Hash;

			//[3];
			Hash = 0xdb69770d;
			X = -364.402;
			Y = -77.4748;
			Z = 44.558;
			Pitch = 0;
			Roll = -0;
			Yaw = 159.354;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[4];
			Hash = 0x8e53ed9f;
			X = -354.244;
			Y = -105.123;
			Z = 44.6484;
			Pitch = 0;
			Roll = -0;
			Yaw = 158.459;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[5];
			Hash = 0x517dd010;
			X = -343.17;
			Y = -96.8912;
			Z = 46.193;
			Pitch = 3.58099;
			Roll = -0;
			Yaw = -108.325;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[6];
			Hash = 0x93948e5e;
			X = -376.891;
			Y = -73.7823;
			Z = 45.3405;
			Pitch = 0;
			Roll = -0;
			Yaw = -167.411;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[7];
			Hash = 0x762f9508;
			X = -352.024;
			Y = -79.8566;
			Z = 47.8551;
			Pitch = 0;
			Roll = 0;
			Yaw = 68.934;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[8];
			Hash = 0xf4f1511e;
			X = -345.813;
			Y = -80.9801;
			Z = 47.0978;
			Pitch = 0;
			Roll = 0;
			Yaw = 68.934;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[9];
			Hash = 0xf4f1511e;
			X = -346.542;
			Y = -82.9782;
			Z = 47.0978;
			Pitch = 0;
			Roll = 0;
			Yaw = 68.934;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[10];
			Hash = 0xf4f1511e;
			X = -340.917;
			Y = -82.818;
			Z = 45.6775;
			Pitch = 0;
			Roll = 0;
			Yaw = 68.934;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[11];
			Hash = 0xf4f1511e;
			X = -341.476;
			Y = -84.9369;
			Z = 45.6274;
			Pitch = 0;
			Roll = 0;
			Yaw = 68.934;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[12];
			Hash = 0x762f9508;
			X = -372.151;
			Y = -98.5481;
			Z = 44.6552;
			Pitch = 0;
			Roll = -0;
			Yaw = 159.354;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[13];
			Hash = 0x93948e5e;
			X = -361.927;
			Y = -100.46;
			Z = 45.443;
			Pitch = 0;
			Roll = -0;
			Yaw = -170.097;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[14];
			Hash = 0x93948e5e;
			X = -361.327;
			Y = -104.65;
			Z = 47.2727;
			Pitch = 0;
			Roll = -0;
			Yaw = -170.097;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[15];
			Hash = 0x93948e5e;
			X = -360.376;
			Y = -110.017;
			Z = 49.6323;
			Pitch = 0;
			Roll = -0;
			Yaw = -169.202;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[16];
			Hash = 0x93948e5e;
			X = -359.354;
			Y = -115.404;
			Z = 52.0096;
			Pitch = 0;
			Roll = -0;
			Yaw = -168.306;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[17];
			Hash = 0x93948e5e;
			X = -358.224;
			Y = -120.714;
			Z = 54.3796;
			Pitch = 0;
			Roll = -0;
			Yaw = -167.411;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[18];
			Hash = 0x93948e5e;
			X = -357.144;
			Y = -125.793;
			Z = 56.6293;
			Pitch = 0;
			Roll = -0;
			Yaw = -167.411;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			//[19];
			Hash = 0x93948e5e;
			X = -355.962;
			Y = -131.115;
			Z = 58.9889;
			Pitch = 0;
			Roll = -0;
			Yaw = -167.411;
			mm_PlaceObject(Hash, X, Y, Z, Pitch, Roll, Yaw, false);

			HaxBy("Outslider");
		}

		std::vector<GTAmapmod> vAllMapMods
		{
			GTAmapmod("10C Garage Troll",{ 229.3570f, -992.9106f, -98.9999f }, mmf_10cGarageTroll),
			GTAmapmod("6C Garage Troll",{ 197.8153f, -1002.293f, -98.5503f }, mmf_6cGarageTroll),
			GTAmapmod("2C Garage Troll",{ 173.0831f, -1004.005f, -98.2410f }, mmf_2cGarageTroll),
			GTAmapmod("UFO Tower With FIB Building",{ 70.9744f, -674.3677f, 679.3784f }, mmf_ufoTower1),
			GTAmapmod("Airport Drag Strip",{ -940.6546f, -3178.347f, 13.9444f }, mmf_AirportDragStrip),
			GTAmapmod("Airport Drift Track",{ -946.1713f, -3084.833f, 19.5450f }, mmf_AirportDriftTrack),
			GTAmapmod("Airport Gate Ramp",{ -1045.602f, -2536.369f, 20.2124f }, mmf_airportGateRamp1),
			GTAmapmod("Airport Mini-Ramp",{ -1066.148f, -3029.479f, 13.9451f }, mmf_airportMiniRamp1),
			GTAmapmod("Mount Chilliad Ramp",{ 500.3041f, 5593.8394f, 795.5292f }, mmf_chilliadRamp1),
			GTAmapmod("Beach Ferris Loop",{ -1505.678f, -1194.213f, 4.3786f }, mmf_beechFerrisRamp1),
			GTAmapmod("Maze Bank Roof-Ramp",{ -74.9424f, -818.63446f, 326.1743f }, mmf_mazeRoofMiniRamp1),
			GTAmapmod("Maze Bank Demo Derby",{ -78.9328f, -822.7497f, 326.1751f }, mmf_mazeDerbyFerrisTree),
			GTAmapmod("Maze Bank City-Ramp",{ -78.9328f, -822.7497f, 326.1751f }, mmf_city691),
			GTAmapmod("Maze Bank Halfpipes",{ -74.9424f, -818.63446f, 326.1743f }, mmf_MazeHalfPipes1),
			GTAmapmod("Maze Bank Spiral",{ -74.9424f, -818.6345f, 326.1743f }, mmf_MazeBankSpiral),
			GTAmapmod("Maze Bank Piece Track",{ -74.9424f, -818.6345f, 326.1743f }, mmf_MazeBankPieceTrack),
			GTAmapmod("Downtown Bobsled",{ -144.823f, -592.133f, 210.764f }, mmf_DowntownBobsled),
			GTAmapmod("Around Eclipse Halfpipes",{ -790.1778f, 342.4632f, 230.6370f }, mmf_AroundEclipse),
			GTAmapmod("Eclipse Towers Troll",{ -774.5000f, 302.5000f, 92.0000f }, mmf_eclipseTroll1),
			GTAmapmod("Airport WallRide",{ -994.7432f, -2562.467f, 36.1194f }, mmf_AirportWallRide),
			GTAmapmod("LSC Troll",{ -347.8090f, -155.7320f, 60.4215f }, mmf_lscTroll),
			GTAmapmod("LSC Skatepark",{ -371.7577f, -84.0345f, 45.6634f }, mmf_lscSkatePark)
		};

		void mm_unloadAll()
		{
			for (GTAmapmod& mm : vAllMapMods)
				mm.Unload(false);
		}

		void __AddpointOption(GTAmapmod &mm)
		{
			bool pressed = false;
			AddOption(mm.Name(), pressed, nullFunc, SUB::MAPMODS2, false); if (pressed)
			{
				currentMAPMODC = &mm;
			}
		}

		void MapMods_()
		{

			AddTitle("Map Mods");

			for (auto& mm : vAllMapMods)
				__AddpointOption(mm);

		}
		void MapMods2_()
		{

			bool cmmtele = 0, cmmload = 0, cmmunload = 0;

			AddTitle(currentMAPMODC->Name());

			AddOption("Teleport", cmmtele);
			AddLocal("Load", currentMAPMODC->IsLoaded(), cmmload, cmmunload);
			//AddOption("Load", cmmload);
			//AddOption("Unload", cmmunload);

			if (cmmtele) currentMAPMODC->Tele();

			if (cmmload) currentMAPMODC->Load();

			if (cmmunload) currentMAPMODC->Unload();



		}

	}

}




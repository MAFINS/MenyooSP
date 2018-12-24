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

#include "PtfxSubs.h" //PtfxS

#include <string>

typedef unsigned __int8 UINT8;
typedef int INT, Entity, Ped, Vehicle, Object, ScrHandle;
typedef unsigned long DWORD, Hash;
typedef float FLOAT;
typedef char *PCHAR;

class RGBA;
class GTAped;
namespace GTAmodel {
	class Model;
}

namespace sub
{
	void Weaponops();

	void ForgeGun_();

	namespace GravityGun_catind
	{

		void Tick();
		bool& Enabled();
		float& ShootForce();

		void Sub_GravityGun();

	}

	namespace TriggerFxGun_catind
	{
		void __AddOption_GunFx(const sub::Ptfx_catind::PtfxS& fx);

		void Sub_GunMain();
	}

	void AddkgunOption_(const std::string& text, Hash newHash, bool *extra_option_code = nullptr, bool gxt = false);
	void KaboomGun_();

	void AddbgunOption_(const std::string& text, Hash hash, bool *extra_option_code = nullptr);
	void BulletGun_();

	void AddpgunOption_(const std::string& text, GTAmodel::Model newModel, bool *extra_option_code = nullptr);
	void PedGun_();
	void PedGun_AllPeds();

	void AddogunOption_(const std::string& text, GTAmodel::Model newModel, bool *extra_option_code = nullptr, bool gxt = false);
	void ObjectGun_();

	void List_VehicleCats_Sub();

	namespace WeaponFavourites_catind
	{
		//extern std::string xmlFavouriteWeapons;
		bool PopulateFavouritesInfo();
		bool IsWeaponAFavourite(Hash whash);
		bool AddWeaponToFavourites(Hash whash, const std::string& customName);
		bool RemoveWeaponFromFavourites(Hash whash);

		void Sub_WeaponFavourites();
	}

	namespace WeaponIndivs_catind
	{

		//extern INT& selectedCategory;
		//extern INT& selectedWeapon;


		// THESE SUBMENUS NEED THE AMMU NATION BANNER
		void Sub_CategoriesList();
		void Sub_InCategory();
		void Sub_InItem();
		void Sub_InItem_Mods();
		void Sub_Parachute();

	}

	namespace WeaponsLoadouts_catind
	{

		bool Create(GTAped ped, const std::string& filePath);
		bool Apply(GTAped ped, const std::string& filePath);

		void Sub_Loadouts();
		void Sub_Loadouts_InItem();
	}

	namespace LaserSight_catind
	{
		extern bool bEnabled;
		extern RGBA _colour;

		inline void DoSight();
		void Tick();

		void Sub_LaserSight();
	}

	void ObjectSpawner_objs();

}




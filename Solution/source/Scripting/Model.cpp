/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Model.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\enums.h"
#include "..\Memory\GTAmemory.h"
#include "..\Util\StringManip.h"

#include <string>
#include <Windows.h> //GetTickCount

namespace GTAmodel
{
	ModelDimensions::ModelDimensions()
	{
	}
	ModelDimensions::ModelDimensions(const Vector3& d1, const Vector3& d2) : Dim1(d1), Dim2(d2)
	{
	}


	Model::Model() : hash(0)
	{
	}
	Model::Model(const std::string& name) : hash(GET_HASH_KEY(name))
	{
	}
	Model::Model(Hash newHash) : hash(newHash)
	{
	}
	Model::Model(VehicleHash newHash) : hash(newHash)
	{
	}

	bool operator == (const Model& left, const Model& right)
	{
		return (left.hash == right.hash);
	}
	bool operator != (const Model& left, const Model& right)
	{
		return (left.hash != right.hash);
	}
	bool Model::Equals(const Model& right) const
	{
		return (this->hash == right.hash);
	}
	Model& Model::operator = (const Model& right)
	{
		this->hash = right.hash;
		return *this;
	}

	// Zorg93
	UINT64 Model::MemoryAddress() const
	{
		static UINT64 _gtaModelMemoryAddressAddr = MemryScan::PatternScanner::FindPattern("\x80\xF9\x05\x75\x08\x48\x05\x00\x00\x00\x00", "xxxxxxx????");
		if (_gtaModelMemoryAddressAddr)
		{
			static UINT64(*_gtaModelGetInfo)(int, __int64) = (UINT64(*)(int, __int64))(*(int*)(_gtaModelMemoryAddressAddr - 0x12) + _gtaModelMemoryAddressAddr - 0x12 + 0x4);

			int data = 0xFFFF;
			return _gtaModelGetInfo(this->hash, (__int64)&data);
		}
		return NULL;
	}

	std::string Model::VehicleDisplayName(bool properName) const
	{
		static UINT64 _gtaModelMemoryAddressAddr = MemryScan::PatternScanner::FindPattern("\x80\xF9\x05\x75\x08\x48\x05\x00\x00\x00\x00", "xxxxxxx????");
		if (_gtaModelMemoryAddressAddr)
		{
			static UINT64(*_gtaModelGetInfo)(int, __int64) = (UINT64(*)(int, __int64))(*(int*)(_gtaModelMemoryAddressAddr - 0x12) + _gtaModelMemoryAddressAddr - 0x12 + 0x4);
			static int _gtaModelDisplayNameOffset = *(int*)(_gtaModelMemoryAddressAddr + 0x7);

			int data = 0xFFFF;
			__int64 addr = _gtaModelGetInfo(this->hash, (__int64)&data);
			if (addr && (*(unsigned char*)(addr + 157) & 0x1F) == 5)//make sure model is valid and is a car
			{
				return properName ?
					(DOES_TEXT_LABEL_EXIST((char*)(addr + _gtaModelDisplayNameOffset)) ? GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)(addr + _gtaModelDisplayNameOffset)) : (char*)(addr + _gtaModelDisplayNameOffset))
					: (char*)(addr + _gtaModelDisplayNameOffset);
			}
		}
		else
		{
			const char* name = GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(this->hash);
			return properName ?
				(DOES_TEXT_LABEL_EXIST(name) ? GET_FILENAME_FOR_AUDIO_CONVERSATION(name) : name)
				: name;
		}
		return "CARNOTFOUND";
	}

	std::string Model::VehicleModelName() const
	{
		return GTAmemory::GetVehicleModelName(this->hash);
	}

	ModelDimensions Model::Dimensions() const
	{
		ModelDimensions dims;
		this->Dimensions(dims.Dim1, dims.Dim2);
		return dims;
	}
	void Model::Dimensions(Vector3& dim1C, Vector3& dim2C) const
	{
		/*Vector3_t dim1, dim2;
		GET_MODEL_DIMENSIONS(this->hash, &dim1, &dim2);
		dim1.x = abs(dim1.x); dim2.x = abs(dim2.x);
		dim1.y = abs(dim1.y); dim2.y = abs(dim2.y);
		dim1.z = abs(dim1.z); dim2.z = abs(dim2.z);
		dim1C = dim1;
		dim2C = dim2;*/
		Vector3_t dim1, dim2;
		UINT64 modelInfo = this->MemoryAddress();
		if (modelInfo)
		{
			auto darr = reinterpret_cast<float*>(modelInfo + 48);
			dim1.x = abs(darr[0]); dim2.x = abs(darr[4]);
			dim1.y = abs(darr[1]); dim2.y = abs(darr[5]);
			dim1.z = abs(darr[2]); dim2.z = abs(darr[6]);
		}
		else
		{
			GET_MODEL_DIMENSIONS(this->hash, &dim1, &dim2);
			dim1.x = abs(dim1.x); dim2.x = abs(dim2.x);
			dim1.y = abs(dim1.y); dim2.y = abs(dim2.y);
			dim1.z = abs(dim1.z); dim2.z = abs(dim2.z);
		}
		dim1C = dim1;
		dim2C = dim2;
	}
	void Model::Dimensions(Vector3_t& dim1, Vector3_t& dim2) const
	{
		/*GET_MODEL_DIMENSIONS(this->hash, &dim1, &dim2);
		dim1.x = abs(dim1.x); dim2.x = abs(dim2.x);
		dim1.y = abs(dim1.y); dim2.y = abs(dim2.y);
		dim1.z = abs(dim1.z); dim2.z = abs(dim2.z);*/
		UINT64 modelInfo = this->MemoryAddress();
		if (modelInfo)
		{
			auto darr = reinterpret_cast<float*>(modelInfo + 48);
			dim1.x = abs(darr[0]); dim2.x = abs(darr[4]);
			dim1.y = abs(darr[1]); dim2.y = abs(darr[5]);
			dim1.z = abs(darr[2]); dim2.z = abs(darr[6]);
		}
		else
		{
			GET_MODEL_DIMENSIONS(this->hash, &dim1, &dim2);
			dim1.x = abs(dim1.x); dim2.x = abs(dim2.x);
			dim1.y = abs(dim1.y); dim2.y = abs(dim2.y);
			dim1.z = abs(dim1.z); dim2.z = abs(dim2.z);
		}
	}
	Vector3 Model::Dim1() const
	{
		Vector3_t dim1, dim2;
		this->Dimensions(dim1, dim2);
		return dim1;
	}
	Vector3 Model::Dim2() const
	{
		Vector3_t dim1, dim2;
		this->Dimensions(dim1, dim2);
		return dim2;
	}

	bool Model::IsBicycle() const
	{
		return IS_THIS_MODEL_A_BICYCLE(this->hash) != 0;
	}
	bool Model::IsBike() const
	{
		return IS_THIS_MODEL_A_BIKE(this->hash) || this->hash == VEHICLE_CHIMERA;
	}
	bool Model::IsQuadbike() const
	{
		return IS_THIS_MODEL_A_QUADBIKE(this->hash) != 0;
	}
	bool Model::IsBoat() const
	{
		return IS_THIS_MODEL_A_BOAT(this->hash) != 0;
	}
	bool Model::IsCar() const
	{
		return IS_THIS_MODEL_A_CAR(this->hash) != 0;
	}
	bool Model::IsHeli() const
	{
		return IS_THIS_MODEL_A_HELI(this->hash) != 0;
	}
	bool Model::IsPlane() const
	{
		return IS_THIS_MODEL_A_PLANE(this->hash) != 0;
	}
	bool Model::IsTrain() const
	{
		return IS_THIS_MODEL_A_TRAIN(this->hash) != 0;
	}
	bool Model::IsFastBoat() const
	{
		return IS_THIS_MODEL_A_JETSKI(this->hash) != 0;
	}
	bool Model::IsCargobob() const
	{
		switch (this->hash)
		{
		case VEHICLE_CARGOBOB:
		case VEHICLE_CARGOBOB2:
		case VEHICLE_CARGOBOB3:
		case VEHICLE_CARGOBOB4:
			return true;
		}
		return false;
	}
	bool Model::IsBus() const
	{
		//if (boost::to_upper_copy(this->VehicleDisplayName(false)).find("BUS") != std::string::npos) return true; return false;

		switch (this->hash)
		{
		case VEHICLE_BUS:
		case VEHICLE_RENTALBUS:
		case VEHICLE_AIRBUS:
		case VEHICLE_PBUS:
		case VEHICLE_TOURBUS:
			return true;
		}
		return false;
	}
	bool Model::IsPoliceVehicle() const
	{
		switch (this->hash)
		{
		case VEHICLE_POLICEOLD2:
		case VEHICLE_FBI:
		case VEHICLE_RIOT:
		case VEHICLE_FBI2:
		case VEHICLE_PRANGER:
		case VEHICLE_POLICEOLD1:
		case VEHICLE_POLICET:
		case VEHICLE_SHERIFF2:
		case VEHICLE_PBUS:
		case VEHICLE_POLICE2:
		case VEHICLE_POLICE:
		case VEHICLE_POLICE3:
		case VEHICLE_SHERIFF:
		case VEHICLE_POLICE4:
		case VEHICLE_POLICEB:
			return true;
		}
		return false;
	}
	bool Model::HasSiren() const
	{
		if (this->IsPoliceVehicle()) return true;

		switch (this->hash)
		{
		case VEHICLE_FIRETRUK:
		case VEHICLE_AMBULANCE:
			return true;
		}
		return false;
	}
	bool Model::IsWheelChangingSupportedVehicle() const
	{
		//if (boost::to_upper_copy(this->VehicleDisplayName(false)).find("BUS") != std::string::npos) return true; return false;

		if (this->IsBus() || this->IsBicycle()) return false;

		switch (this->hash)
		{
		case VEHICLE_DUMP:
		case VEHICLE_FLATBED:
		case VEHICLE_FIRETRUK:
		case VEHICLE_RIPLEY:
		case VEHICLE_PHANTOM:
		case VEHICLE_AMBULANCE:
		//case VEHICLE_TYRUS:
		case VEHICLE_CARGOPLANE:
		case VEHICLE_RIOT:
		case VEHICLE_BUS:
		case VEHICLE_AIRBUS:
		//case VEHICLE_TAMPA:
		//case VEHICLE_TROHPYTRUCK:			//why were these 3 vehicles included?
		case VEHICLE_CADDY3:
			return false;
		}
		return true;
	}
	bool Model::IsBennySupportedVehicle()
	{
		switch (this->hash)
		{
		case VEHICLE_BUCCANEER2:
		case VEHICLE_CHINO2:
		case VEHICLE_FACTION:
		case VEHICLE_FACTION2:
		case VEHICLE_MOONBEAM:
		case VEHICLE_MOONBEAM2:
		case VEHICLE_PRIMO2:
		case VEHICLE_VOODOO:
		case VEHICLE_BTYPE2:
		case VEHICLE_LURCHER:
			// And many others
			return true;
		}
		return false;
	}

	bool Model::IsVehicle() const
	{
		return IS_MODEL_A_VEHICLE(this->hash) != 0;
	}
	bool Model::IsPed() const
	{
		return GTAmemory::IsModelAPed(this->hash);
	}

	void Model::Load() const
	{
		REQUEST_MODEL(this->hash);
	}
	bool Model::Load(DWORD timeOut) const
	{
		if (HAS_MODEL_LOADED(this->hash)) return true;
		else
		{
			REQUEST_MODEL(this->hash);

			for (timeOut += GetTickCount(); GetTickCount() < timeOut;)
			{
				if (HAS_MODEL_LOADED(this->hash))
					return true;
				WAIT(0);
			}
			return false;
		}
	}
	void Model::LoadAndWait() const
	{
		this->Load(7500);
	}
	bool Model::IsLoaded() const
	{
		return HAS_MODEL_LOADED(this->hash) != 0;
	}
	void Model::Unload() const
	{
		if (HAS_MODEL_LOADED(this->hash))
			SET_MODEL_AS_NO_LONGER_NEEDED(this->hash);
	}

	void Model::LoadCollision() const
	{
		REQUEST_COLLISION_FOR_MODEL(this->hash);
	}
	bool Model::LoadCollision(DWORD timeOut) const
	{
		REQUEST_COLLISION_FOR_MODEL(this->hash);

		for (timeOut += GetTickCount(); GetTickCount() < timeOut;)
		{
			if (HAS_COLLISION_FOR_MODEL_LOADED(this->hash)) return true;
			WAIT(0);
		}
		return false;
	}
	bool Model::IsCollisionLoaded() const
	{
		return HAS_COLLISION_FOR_MODEL_LOADED(this->hash) != 0;
	}
	void Model::LoadCollisionAndWait() const
	{
		this->LoadCollision(4000);
	}


	bool Model::IsValid() const
	{
		return IS_MODEL_VALID(this->hash) != 0;
	}
	bool Model::IsInCdImage() const
	{
		return IS_MODEL_IN_CDIMAGE(this->hash) != 0;
	}
	bool Model::Exists() const
	{
		return IS_MODEL_VALID(this->hash) && IS_MODEL_IN_CDIMAGE(this->hash);
	}

}




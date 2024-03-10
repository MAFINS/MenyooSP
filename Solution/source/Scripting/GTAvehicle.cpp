/*
* Copyright (C) 2015 crosire
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#include "GTAvehicle.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\types.h"
#include "enums.h"
#include "..\Natives\natives2.h"
#include "Model.h"
#include "..\Memory\GTAmemory.h"
#include "GTAblip.h"

#include "World.h"
#include "..\Menu\Routine.h"

#include <string>
#include <vector>
#include <map>

#pragma region vehicle mod slot names
const std::vector<std::string> vValues_HornNames
{
	"CMOD_HRN_TRK",
	"CMOD_HRN_COP",
	"CMOD_HRN_CLO",
	"CMOD_HRN_MUS1",
	"CMOD_HRN_MUS2",
	"CMOD_HRN_MUS3",
	"CMOD_HRN_MUS4",
	"CMOD_HRN_MUS5",
	"CMOD_HRN_SAD", 
	"HORN_CLAS1", 
	"HORN_CLAS2", 
	"HORN_CLAS3",
	"HORN_CLAS4",
	"HORN_CLAS5",
	"HORN_CLAS6",
	"HORN_CLAS7",
	"HORN_CNOTE_C0",
	"HORN_CNOTE_D0",
	"HORN_CNOTE_E0",
	"HORN_CNOTE_F0",
	"HORN_CNOTE_G0",
	"HORN_CNOTE_A0",
	"HORN_CNOTE_B0",
	"HORN_CNOTE_C1",
	"HORN_HIPS1",
	"HORN_HIPS2",
	"HORN_HIPS3",
	"HORN_HIPS4",
	"HORN_INDI_1",
	"HORN_INDI_2",
	"HORN_INDI_3",
	"HORN_INDI_4",
	"HORN_LUXE1",
	"HORN_LUXE2",
	"HORN_LUXE3",
	"",
	"",
	"",
	"HORN_HWEEN1",
	"",
	"HORN_HWEEN2",
	"",
	"HORN_LOWRDER1",
	"",
	"HORN_LOWRDER2",
	"",
	"HORN_XM15_1",
	"",
	"HORN_XM15_2",
	"",
	"HORN_XM15_3",
	"",
	"CMOD_AIRHORN_01",
	"",
	"CMOD_AIRHORN_02",
	"",
	"CMOD_AIRHORN_03",
	""
};

const std::vector<std::string> vValues_ModSlotNames
{
	"CMOD_MOD_SPO",
	"CMOD_BUM_1",
	"CMOD_BUM_4",
	"CMOD_MOD_SKI",
	"CMOD_MOD_MUF",
	"CMOD_MOD_CHA",
	"CMOD_MOD_GRL",
	"CMOD_MOD_HOD",
	"CMOD_MOD_FEN",
	"CMOD_MOD_FEN",
	"CMOD_MOD_ROF",
	"CMOD_MOD_ENG",
	"CMOD_MOD_BRA",
	"CMOD_MOD_TRN",
	"CMOD_MOD_HRN",
	"CMOD_MOD_SUS",
	"CMOD_MOD_ARM",
	"Unknown 17",
	"CMOD_MOD_TUR",
	"Unknown 19",
	"Tyre Smoke",
	"Unknown 21",
	"CMOD_MOD_LGT",
	"CMOD_MOD_WHEM",
	"CMOD_WHE0_1",


	/*"VEM_SUPERMOD_0",
	"VEM_SUPERMOD_1",
	"VEM_SUPERMOD_2",
	"VEM_SUPERMOD_3",
	"VEM_SUPERMOD_4",
	"VEM_SUPERMOD_5",
	"VEM_SUPERMOD_6",
	"VEM_SUPERMOD_7",
	"VEM_SUPERMOD_8",
	"VEM_SUPERMOD_9",
	"VEM_SUPERMOD_10",
	"VEM_SUPERMOD_11",
	"VEM_SUPERMOD_12",
	"VEM_SUPERMOD_13",
	"VEM_SUPERMOD_14",
	"VEM_SUPERMOD_15",
	"VEM_SUPERMOD_16",
	"VEM_SUPERMOD_17",
	"VEM_SUPERMOD_18",
	"VEM_SUPERMOD_19",
	"VEM_SUPERMOD_20",
	"VEM_SUPERMOD_21",
	"VEM_SUPERMOD_22",
	"VEM_SUPERMOD_23",*/
	"CMM_MOD_S0",//"Plateholder",
	"CMM_MOD_S1",//"Vanity Plate",
	"CMM_MOD_S2",//"Trim Design",
	"CMM_MOD_S3",//"Ornament",
	"CMM_MOD_S4",//"Dash",
	"CMM_MOD_S5",//"Dial Design",
	"CMM_MOD_S6",//"Doorcards",
	"CMM_MOD_S7",//"Leather Seats",
	"CMM_MOD_S8",//"Steering Wheel",
	"CMM_MOD_S9",//"Column Shifter Lever",
	"CMM_MOD_S10",//"Plaque",
	"CMM_MOD_S11",//"Speakers",
	"CMM_MOD_S12",//"Trunk",
	"CMM_MOD_S13",//"Hydraulics",
	"CMM_MOD_S14",//"Engine Block",
	"CMM_MOD_S15",//"Air Filter",
	"CMM_MOD_S16",//"Struts",
	"CMM_MOD_S17",//"Arch Cover",
	"CMM_MOD_S18",//"Aerials",
	"CMM_MOD_S19",//"Trim",
	"CMM_MOD_S20",//"Tank",
	"CMM_MOD_S21",//"Windows",
	"CMM_MOD_S22",//"Unknown 47",
	"CMM_MOD_S23",//"Livery",
};
#pragma endregion
std::string get_mod_slot_name(Vehicle vehicle, INT modType, bool gxt)
{
	//switch (modType) {
	//case 3:
	//	return "CMOD_MOD_0_D";
	//	break;
	//case 4:
	//	return "CMOD_MOD_ARM";
	//	break;
	//case 5:
	//	return "CMOD_MOD_BRA";
	//	break;
	//case 8:
	//	return "CMOD_MOD_BUM";
	//	break;
	//case 9:
	//	return "CMOD_MOD_CHA";
	//	break;
	//case 38:
	//	return "CMOD_MOD_COL";
	//	break;
	//case 10:
	//	return "CMOD_MOD_ENG";
	//	break;
	//case 13:
	//	return "CMOD_MOD_EXP";
	//	break;
	//case 21:
	//	return "CMOD_MOD_GLD";
	//	break;
	//case 22:
	//	return "CMOD_MOD_GLD2";
	//	break;
	//case 23:
	//	return "CMOD_MOD_GRL";
	//	break;
	//case 26:
	//	return "CMOD_MOD_HOD";
	//	break;
	//case 27:
	//	return "CMOD_MOD_HRN";
	//	break;
	//case 31:
	//	return "CMOD_MOD_LTP";
	//	break;
	//case 28:
	//	return "CMOD_MOD_LGT";
	//	break;
	//case 29:
	//	return "CMOD_MOD_LGT_H";
	//	break;
	//case 30:
	//	return "CMOD_MOD_LGT_N";
	//	break;
	//case 12:
	//	return "CMOD_MOD_MUF";
	//	break;
	//case 33:
	//	return "CMOD_MOD_PLA";
	//	break;
	//case 40:
	//	return "CMOD_MOD_ROF";
	//	break;
	//case 42:
	//	return "CMOD_MOD_SEL";
	//	break;
	//case 54:
	//	return "CMOD_MOD_VIN";
	//	break;
	//case 44:
	//	return "CMOD_MOD_SKI";
	//	break;
	//case 46:
	//	return "CMOD_MOD_SPO";
	//	break;
	//case 47:
	//	return "CMOD_MOD_SUS";
	//	break;
	//case 58:
	//	return "CMOD_MOD_TYR";
	//	break;
	//case 57:
	//	return "CMOD_MOD_WCL";
	//	break;
	//case 48:
	//	return "CMOD_MOD_TGT";
	//	break;
	//case 50:
	//	return "CMOD_MOD_TRN";
	//	break;
	//case 53:
	//	return "CMOD_MOD_TUR";
	//	break;
	//case 55:
	//	return "CMOD_MOD_WHEM";
	//	break;
	//case 56:
	//	return "CMOD_MOD_WHE";
	//	break;
	//case 60:
	//	return "CMOD_MOD_WIN";
	//	break;
	//case 15:
	//	return "CMOD_MOD_FEN";
	//	break;
	//case 2:
	//	return "CMM_MOD INVALID";
	//	break;
	//default:
	//	//return GET_MOD_SLOT_NAME(vehicle, modType
	//	return "CMM_MOD INVALID";
	//	break;
	//}
	//return "";
	std::string name;
	if (modType >= 0 && modType < vValues_ModSlotNames.size())
	{
		//switch (modType)
		//{
		//default: Return = "UNK"; break;
		//case 0: Return = "CMOD_MOD_SPO"; break;
		//case 1: Return = "CMOD_BUM_1"; break;
		//case 2: Return = "CMOD_BUM_4"; break;
		//case 3: Return = "CMOD_MOD_SKI"; break;
		//case 4: Return = "CMOD_MOD_MUF"; break;
		//case 5: Return = "CMOD_MOD_CHA"; break;
		//case 6: Return = "CMOD_MOD_GRL"; break;
		//case 7: Return = "CMOD_MOD_HOD"; break;
		//case 8: Return = "CMOD_MOD_FEN"; break;
		//case 9: Return = "CMOD_MOD_FEN"; break;
		//case 10: Return = IS_VEHICLE_MODEL(vehicle, VEHICLE_BAGGER) ? "Saddle Bags" : "CMOD_MOD_ROF"; break;
		//case 11: Return = "CMOD_MOD_ENG"; break;
		//case 12: Return = "CMOD_MOD_BRA"; break;
		//case 13: Return = "CMOD_MOD_TRN"; break;
		//case 14: Return = "CMOD_MOD_HRN"; break;
		//case 15: Return = "CMOD_MOD_SUS"; break;
		//case 16: Return = "CMOD_MOD_ARM"; break;
		//case 17: Return = "Unknown 17"; break;
		//case 18: Return = "CMOD_MOD_TUR"; break;
		//case 19: Return = "Unknown 19"; break;
		//case 20: Return = "Tyre Smoke"; break;
		//case 21: Return = "Unknown 21"; break;
		//case 22: Return = "CMOD_MOD_LGT"; break;
		//case 23: Return = "CMOD_MOD_WHEM"; break; //is_model_a_bikes(GET_ENTITY_MODEL(vehicle)) ? "CMOD_WHE0_0" : "CMOD_MOD_WHEM"; break;
		//case 24: Return = "CMOD_WHE0_1"; break;
		////case 25: Return = "CMOD_TYR_2"; break;
		////case 26: Return = "CMOD_TYR_1"; break;
		////case 27: Return = "CMOD_GLD2_2"; break;
		//case 25: Return = "Plate Holder"; break;
		//case 26: Return = "Vanity Plates"; break;
		//case 27: Return = "Trim Design"; break;
		//case 28: Return = "Ornaments"; break;
		//case 29: Return = "Unknown 29"; break;
		//case 30: Return = "Dial"; break;
		//case 31: Return = "Speakers (Door)"; break;
		//case 32: Return = "Leather Seats"; break;
		//case 33: Return = "Steering Wheels"; break;
		//case 34: Return = "Column Shifter Levers"; break;
		//case 35: Return = "Plaques"; break;
		//case 36: Return = "Speakers"; break;
		//case 37: Return = "Speakers (Trunk)"; break;
		//case 38: Return = "Hydraulics"; break;
		//case 39: Return = "Engine Block"; break;
		//case 40: Return = "Air Filters"; break;
		//case 41: Return = "Unknown 41"; break;
		//case 42: Return = "Arch Covers"; break;
		//case 43: Return = "Aerials"; break;
		//case 44: Return = "Trim"; break;
		//case 45: Return = "Tank"; break;
		//case 46: Return = "Unknown 46"; break;
		//case 47: Return = "Unknown 47"; break;
		//case 48: Return = "Liveries 9"; break;
		//}
		Model vehModel = GET_ENTITY_MODEL(vehicle);
		REQUEST_ADDITIONAL_TEXT("mod_mnu", 19);
		while (!HAS_ADDITIONAL_TEXT_LOADED(19)) {
			WAIT(0);
		}
		if (GET_MOD_SLOT_NAME(vehicle, modType) == nullptr || std::strlen(GET_MOD_SLOT_NAME(vehicle, modType)) < 2)
			name = vValues_ModSlotNames[modType];
		else
			name = GET_MOD_SLOT_NAME(vehicle, modType);

		/*switch (modType)
		{
		default: name = vValues_ModSlotNames[modType]; break;
		case VehicleMod::SideSkirt: name = (vehModel.hash == VEHICLE_FAGGIO3) ? "TOP_ARCHCOVER" : vehModel.IsBike() ? "CMM_MOD_S15" : vValues_ModSlotNames[modType]; break;// Air filter for bikes
		case VehicleMod::Roof: name = (vehModel.hash == VEHICLE_BAGGER) ? "CMOD_SB_T" : "CMOD_MOD_ROF"; break; // Saddle bags for bagger
		case VehicleMod::AirFilter: if (vehModel.hash == VEHICLE_SULTANRS) name = "CMM_MOD_S15b"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Struts: if (vehModel.hash == VEHICLE_SULTANRS || vehModel.hash == VEHICLE_BANSHEE2) name = "CMM_MOD_S16b"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::ArchCover: if (vehModel.hash == VEHICLE_SULTANRS) name = "CMM_MOD_S17b"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Aerials: if (vehModel.hash == VEHICLE_SULTANRS) name = "CMM_MOD_S18b"; else if (vehModel.hash == VEHICLE_BTYPE3) name = "CMM_MOD_S18c"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Trim: if (vehModel.hash == VEHICLE_SULTANRS) name = "CMM_MOD_S19b"; else if (vehModel.hash == VEHICLE_BTYPE3) name = "CMM_MOD_S19c"; else if (vehModel.hash == VEHICLE_VIRGO2) name = "CMM_MOD_S19d"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Tank: if (vehModel.hash == VEHICLE_SLAMVAN3) name = "CMM_MOD_S27"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Windows: if (vehModel.hash == VEHICLE_BTYPE3) name = "CMM_MOD_S21b"; else name = vValues_ModSlotNames[modType];
		case VehicleMod::Unknown47: if (vehModel.hash == VEHICLE_SLAMVAN3) name = "SLVAN3_RDOOR"; else name = vValues_ModSlotNames[modType];
		}*/
	}
	else
	{
		name = "CMM_MOD INVALID";
	}

	if (gxt)
	{
		return DOES_TEXT_LABEL_EXIST(name.c_str()) ? GET_FILENAME_FOR_AUDIO_CONVERSATION(name.c_str()) : name;
	}

	return name;
}
std::string get_mod_text_label(Vehicle vehicle, INT modType, INT modValue, bool gxt)
{
	if (modValue < 0)
	{
		switch (modType)
		{
		case VehicleMod::FrontBumper: return GET_FILENAME_FOR_AUDIO_CONVERSATION("CMOD_BUM_0"); break;
		case VehicleMod::RearBumper: return GET_FILENAME_FOR_AUDIO_CONVERSATION("CMOD_BUM_3"); break;
		}
		return ((std::string)"Stock " + get_mod_slot_name(vehicle, modType, true));
	}

	std::vector<std::string> armournames{ "CMOD_ARM_1", "CMOD_ARM_2", "CMOD_ARM_3", "CMOD_ARM_4", "CMOD_ARM_5" };
	std::vector<std::string> suspensionnames{ "Lowered ", "Street ", "Sport ", "Competition ", "Race " };
	std::vector<std::string> brakenames{ "Street ", "Sport ", "Race ", "Super " };

	switch (modType)
	{
	case VehicleMod::Engine:
		return "EMS Upgrade " +  std::to_string(modValue + 1); break;
	case VehicleMod::Brakes: case VehicleMod::Transmission:
		return modValue >= brakenames.size() ? get_mod_slot_name(vehicle, modType, true) + std::to_string(modValue) : brakenames[modValue] + get_mod_slot_name(vehicle, modType, true); break;
	case VehicleMod::Horns:
		return modValue >= vValues_HornNames.size() ? get_mod_slot_name(vehicle, modType, true) + std::to_string(modValue) : (gxt && DOES_TEXT_LABEL_EXIST((PCHAR)vValues_HornNames[modValue].c_str()) ? GET_FILENAME_FOR_AUDIO_CONVERSATION((PCHAR)vValues_HornNames[modValue].c_str()) : vValues_HornNames[modValue]); break;
	case VehicleMod::Suspension:
		return modValue >= suspensionnames.size() ? get_mod_slot_name(vehicle, modType, true) + std::to_string(modValue) : suspensionnames[modValue] + get_mod_slot_name(vehicle, modType, true); break;
	case VehicleMod::Armor:
		return modValue >= armournames.size() ? "Armour Upgrade " + std::to_string((modValue + 1) * 20) + "%" : (gxt && DOES_TEXT_LABEL_EXIST((PCHAR)armournames[modValue].c_str()) ? GET_FILENAME_FOR_AUDIO_CONVERSATION((PCHAR)armournames[modValue].c_str()) : armournames[modValue]); break;
	}

	const char* modName = GET_MOD_TEXT_LABEL(vehicle, modType, modValue);
	if (strlen(modName) > 3) return DOES_TEXT_LABEL_EXIST(modName) && gxt ? GET_FILENAME_FOR_AUDIO_CONVERSATION(modName) : modName;


	// If all else fails
	return get_mod_slot_name(vehicle, modType, true) + " " + std::to_string(modValue + 1);

}


GTAvehicle::GTAvehicle()
	: GTAentity()
{
}
GTAvehicle::GTAvehicle(int handle)
	: GTAentity(handle)
{
}
GTAvehicle::GTAvehicle(const GTAentity& obj)
	: GTAentity(obj)
{
}

GTAvehicle& GTAvehicle::operator = (const GTAvehicle& value)
{
	this->mHandle = value.mHandle;
	return *this;
}
bool operator == (const GTAvehicle& left, const GTAvehicle& right)
{
	return left.mHandle == right.mHandle;
}

void GTAvehicle::Delete(bool tele)
{
	if (!this->Exists()) return;

	this->RequestControl();

	GTAblip blip = this->CurrentBlip();
	if (blip.Exists())
		blip.Remove();

	this->MissionEntity_set(false);

	if (tele)
		SET_ENTITY_COORDS_NO_OFFSET(this->mHandle, 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0);

	DELETE_VEHICLE(&this->mHandle);
}

int GTAvehicle::NetID() const
{
	return VEH_TO_NET(this->mHandle);
}

bool GTAvehicle::IsDamaged() const
{
	return GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(this->mHandle) != 0;
}
void GTAvehicle::Fix()
{
	SET_VEHICLE_FIXED(this->mHandle);
}
void GTAvehicle::Repair(bool checkIfDamaged)
{
	if (!checkIfDamaged || GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(this->mHandle))
	{
		SET_VEHICLE_FIXED(this->mHandle);
		SET_VEHICLE_DIRT_LEVEL(this->mHandle, 0);
		SET_VEHICLE_ENGINE_CAN_DEGRADE(this->mHandle, 0);
		SET_VEHICLE_ENGINE_HEALTH(this->mHandle, 2000.0f);
		SET_VEHICLE_PETROL_TANK_HEALTH(this->mHandle, 2000.0f);
		SET_VEHICLE_BODY_HEALTH(this->mHandle, 2000.0f);
		SET_VEHICLE_UNDRIVEABLE(this->mHandle, 0);
		SET_VEHICLE_ENGINE_ON(this->mHandle, 1, 1, 0);
	}
}

void GTAvehicle::EngineSound_set(const std::string& vehName)
{
	FORCE_USE_AUDIO_GAME_OBJECT(this->mHandle, vehName.c_str());
}

void GTAvehicle::SetFrictionOverride(float value)
{
	SET_VEHICLE_FRICTION_OVERRIDE(this->mHandle, value);
}

bool GTAvehicle::HasRoof() const
{
	return DOES_VEHICLE_HAVE_ROOF(this->mHandle) != 0;
}

int GTAvehicle::MaxPassengers() const
{
	return GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(this->mHandle);
}

GTAentity GTAvehicle::GetPedOnSeat(VehicleSeat seat) const
{
	return GET_PED_IN_VEHICLE_SEAT(this->mHandle, (seat), 0);
}
bool GTAvehicle::IsSeatFree(VehicleSeat seat) const
{
	return IS_VEHICLE_SEAT_FREE(this->mHandle, (seat), 0) != 0;
}
GTAentity GTAvehicle::Driver_get() const
{
	return this->GetPedOnSeat(VehicleSeat::SEAT_DRIVER);
}
std::vector<GTAentity> GTAvehicle::Occupants_get(bool bIncludeDriver) const
{
	std::vector<GTAentity> pedArray;

	GTAentity driver = this->Driver_get();
	if (bIncludeDriver && driver.Exists())
		pedArray.push_back(driver);

	const int maxPassengers = this->MaxPassengers();

	for (int i = 0; i < maxPassengers; i++)
	{
		GTAentity ped = this->GetPedOnSeat(static_cast<VehicleSeat>(i));
		if (ped.Exists())
		{
			pedArray.push_back(ped);
		}
	}

	return pedArray;
}
VehicleSeat GTAvehicle::FirstFreeSeat(VehicleSeat defaultReturn) const
{
	int maxPass = GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(this->mHandle);// - 2;
	for (int i = -1; i <= maxPass; i++)
	{
		if (IS_VEHICLE_SEAT_FREE(this->mHandle, i, 0))
			return (VehicleSeat)i;
	}
	return defaultReturn;
}

std::string GTAvehicle::NumberPlateText_get() const
{
	return GET_VEHICLE_NUMBER_PLATE_TEXT(this->mHandle);
}
void GTAvehicle::NumberPlateText_set(const std::string& value)
{
	SET_VEHICLE_NUMBER_PLATE_TEXT(this->mHandle, value.c_str());
}
int GTAvehicle::NumberPlateTextIndex_get() const
{
	return GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(this->mHandle);
}
void GTAvehicle::NumberPlateTextIndex_set(int value)
{
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(this->mHandle, value);
}

bool GTAvehicle::IsConvertible() const
{
	return IS_VEHICLE_A_CONVERTIBLE(this->mHandle, false) != 0;
}

bool GTAvehicle::Stolen_get() const
{
	return IS_VEHICLE_STOLEN(this->mHandle) != 0;
}
void GTAvehicle::Stolen_set(bool value)
{
	SET_VEHICLE_IS_STOLEN(this->mHandle, value);
}

bool GTAvehicle::Driveable_get() const
{
	return IS_VEHICLE_DRIVEABLE(this->mHandle, false) != 0;
}
void GTAvehicle::Driveable_set(bool value)
{
	SET_VEHICLE_UNDRIVEABLE(this->mHandle, !value);
}

bool GTAvehicle::IsStopped() const
{
	return IS_VEHICLE_STOPPED(this->mHandle) != 0;
}
bool GTAvehicle::IsStoppedAtTrafficLights() const
{
	return IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(this->mHandle) != 0;
}
void GTAvehicle::StopImmediately()
{
	SET_VEHICLE_FORWARD_SPEED(this->mHandle, 0.0f);
}

float GTAvehicle::MaxBraking_get() const
{
	return GET_VEHICLE_MAX_BRAKING(this->mHandle);
}
float GTAvehicle::MaxTraction_get() const
{
	return GET_VEHICLE_MAX_TRACTION(this->mHandle);
}

bool GTAvehicle::IsOnAllWheels() const
{
	return IS_VEHICLE_ON_ALL_WHEELS(this->mHandle) != 0;
}

void GTAvehicle::Speed_set(float value)
{
	if (this->Model().IsTrain())
	{
		SET_TRAIN_SPEED(this->mHandle, value);
		SET_TRAIN_CRUISE_SPEED(this->mHandle, value);
	}
	else
	{
		SET_VEHICLE_FORWARD_SPEED(this->mHandle, value);
	}
}
void GTAvehicle::SetForwardSpeed(float value)
{
	SET_VEHICLE_FORWARD_SPEED(this->mHandle, value);
}

void GTAvehicle::MaxSpeed_set(float value)
{
	SET_VEHICLE_MAX_SPEED(this->mHandle, value);
}

float GTAvehicle::DirtLevel_get() const
{
	return GET_VEHICLE_DIRT_LEVEL(this->mHandle);
}
void GTAvehicle::DirtLevel_set(float value)
{
	SET_VEHICLE_DIRT_LEVEL(this->mHandle, value);
}
float GTAvehicle::PaintFade_get() const
{
	return GET_VEHICLE_ENVEFF_SCALE(this->mHandle);
}
void GTAvehicle::PaintFade_set(float value)
{
	SET_VEHICLE_ENVEFF_SCALE(this->mHandle, value);
}

VehicleRoofState GTAvehicle::RoofState_get() const
{
	if (IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(this->mHandle))
		return static_cast<VehicleRoofState>(1);
	else
		return static_cast<VehicleRoofState>(GET_CONVERTIBLE_ROOF_STATE(this->mHandle));
}
void GTAvehicle::RoofState_set(VehicleRoofState value)
{
	switch (value)
	{
	case VehicleRoofState::Opened:
	case VehicleRoofState::Opening:
		RAISE_CONVERTIBLE_ROOF(this->mHandle, value == VehicleRoofState::Opened);
		break;
	case VehicleRoofState::Closed:
	case VehicleRoofState::Closing:
		LOWER_CONVERTIBLE_ROOF(this->mHandle, value == VehicleRoofState::Closed);
		break;
	}
}

float GTAvehicle::BodyHealth_get() const
{
	return GET_VEHICLE_BODY_HEALTH(this->mHandle);
}
void GTAvehicle::BodyHealth_set(float value)
{
	SET_VEHICLE_BODY_HEALTH(this->mHandle, value);
}

float GTAvehicle::EngineHealth_get() const
{
	return GET_VEHICLE_ENGINE_HEALTH(this->mHandle);
}
void GTAvehicle::EngineHealth_set(float value)
{
	SET_VEHICLE_ENGINE_HEALTH(this->mHandle, value);
}

float GTAvehicle::PetrolTankHealth_get() const
{
	return GET_VEHICLE_PETROL_TANK_HEALTH(this->mHandle);
}
void GTAvehicle::PetrolTankHealth_set(float value)
{
	SET_VEHICLE_PETROL_TANK_HEALTH(this->mHandle, value);
}

bool GTAvehicle::SirenActive_get() const
{
	return IS_VEHICLE_SIREN_ON(this->mHandle) != 0;
}
void GTAvehicle::SirenActive_set(bool value)
{
	SET_VEHICLE_SIREN(this->mHandle, value);
}

bool GTAvehicle::LoudRadioActive_get() const
{
	return CAN_VEHICLE_RECEIVE_CB_RADIO(this->mHandle) != 0;
}
void GTAvehicle::LoudRadioActive_set(bool value)
{
	SET_VEHICLE_RADIO_LOUD(this->mHandle, value);
}

int GTAvehicle::PrimaryColour_get() const
{
	int colour1, colour2;
	GET_VEHICLE_COLOURS(this->mHandle, &colour1, &colour2);
	return colour1;
}
void GTAvehicle::PrimaryColour_set(int value)
{
	int colour1, colour2;
	GET_VEHICLE_COLOURS(this->mHandle, &colour1, &colour2);
	SET_VEHICLE_COLOURS(this->mHandle, value, colour2);
}

int GTAvehicle::SecondaryColour_get() const
{
	int colour1, colour2;
	GET_VEHICLE_COLOURS(this->mHandle, &colour1, &colour2);
	return colour2;
}
void GTAvehicle::SecondaryColour_set(int value)
{
	int colour1, colour2;
	GET_VEHICLE_COLOURS(this->mHandle, &colour1, &colour2);
	SET_VEHICLE_COLOURS(this->mHandle, colour1, value);
}

int GTAvehicle::RimColour_get() const
{
	int colour1, colour2;
	GET_VEHICLE_EXTRA_COLOURS(this->mHandle, &colour1, &colour2);
	return colour2;
}
void GTAvehicle::RimColour_set(int value)
{
	int colour1, colour2;
	GET_VEHICLE_EXTRA_COLOURS(this->mHandle, &colour1, &colour2);
	SET_VEHICLE_EXTRA_COLOURS(this->mHandle, colour1, value);
}

int GTAvehicle::PearlescentColour_get() const
{
	int colour1, colour2;
	GET_VEHICLE_EXTRA_COLOURS(this->mHandle, &colour1, &colour2);
	return colour1;
}
void GTAvehicle::PearlescentColour_set(int value)
{
	int colour1, colour2;
	GET_VEHICLE_EXTRA_COLOURS(this->mHandle, &colour1, &colour2);
	SET_VEHICLE_EXTRA_COLOURS(this->mHandle, value, colour2);
}

// For Benny's supported vehicles
int GTAvehicle::InteriorColour_get() const
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_877_1_STEAM)
		return 0;
	int col;
	GET_VEHICLE_EXTRA_COLOUR_5(this->mHandle, &col);
	return col;
}
void GTAvehicle::InteriorColour_set(int value)
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_877_1_STEAM)
		return;
	SET_VEHICLE_EXTRA_COLOUR_5(this->mHandle, value);
}
int GTAvehicle::DashboardColour_get() const
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_877_1_STEAM)
		return 0;
	int col;
	GET_VEHICLE_EXTRA_COLOUR_6(this->mHandle, &col);
	return col;
}
void GTAvehicle::DashboardColour_set(int value)
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_877_1_STEAM)
		return;
	SET_VEHICLE_EXTRA_COLOUR_6(this->mHandle, value);
}

// b1604
int GTAvehicle::HeadlightColour_get() const
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_1604_0_STEAM)
		return 0;
	return GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(this->mHandle);
}
void GTAvehicle::HeadlightColour_set(int value)
{
	if (GTAmemory::GetGameVersion() < eGameVersion::VER_1_0_1604_0_STEAM)
		return;
	SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(this->mHandle, value);
}

int GTAvehicle::WheelType_get() const
{
	return GET_VEHICLE_WHEEL_TYPE(this->mHandle);
}
void GTAvehicle::WheelType_set(int value)
{
	SET_VEHICLE_WHEEL_TYPE(this->mHandle, value);
}

int GTAvehicle::WindowTint_get() const
{
	return GET_VEHICLE_WINDOW_TINT(this->mHandle);
}
void GTAvehicle::WindowTint_set(int value)
{
	SET_VEHICLE_WINDOW_TINT(this->mHandle, value);
}

bool GTAvehicle::IsPrimaryColorCustom() const
{
	return GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(this->mHandle) != 0;
}
bool GTAvehicle::IsSecondaryColorCustom() const
{
	return GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(this->mHandle) != 0;
}

void GTAvehicle::Wanted_set(bool value)
{
	SET_VEHICLE_IS_WANTED(this->mHandle, value);
}

void GTAvehicle::HasGravity_set(bool value)
{
	SET_VEHICLE_GRAVITY(this->mHandle, value);
	GTAentity::HasGravity_set(value);
}

bool GTAvehicle::EngineRunning_get() const
{
	return GET_IS_VEHICLE_ENGINE_RUNNING(this->mHandle) != 0;
}
void GTAvehicle::EngineRunning_set(bool value)
{
	SET_VEHICLE_ENGINE_ON(this->mHandle, value, true, true);
}

void GTAvehicle::EnginePowerMultiplier_set(float value)
{
	MODIFY_VEHICLE_TOP_SPEED(this->mHandle, value);
}
void GTAvehicle::EngineTorqueMultiplier_set(float value)
{
	SET_VEHICLE_CHEAT_POWER_INCREASE(this->mHandle, value);
}

void GTAvehicle::EngineCanDegrade_set(bool value)
{
	SET_VEHICLE_ENGINE_CAN_DEGRADE(this->mHandle, value);
}

bool GTAvehicle::LightsOn_get() const
{
	int lightState1, lightState2;
	GET_VEHICLE_LIGHTS_STATE(this->mHandle, &lightState1, &lightState2);
	return lightState1 == 1;
}
void GTAvehicle::LightsOn_set(bool value)
{
	SET_VEHICLE_LIGHTS(this->mHandle, value ? 3 : 4);
}

bool GTAvehicle::HighBeamsOn_get() const
{
	int lightState1, lightState2;
	GET_VEHICLE_LIGHTS_STATE(this->mHandle, &lightState1, &lightState2);
	return lightState2 == 1;
}

void GTAvehicle::LightsMultiplier_set(float value)
{
	SET_VEHICLE_LIGHT_MULTIPLIER(this->mHandle, value);
}

bool GTAvehicle::LeftHeadLightBroken_get() const
{
	return GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(this->mHandle) != 0;
}
void GTAvehicle::LeftHeadLightBroken_set(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x77C : 0x76C);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x79C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7BC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7CC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x7EC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x80C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x84C : offset);

		SetClearBit(*(int*)(memoryAddress + offset), 0, value);
	}
}

bool GTAvehicle::RightHeadLightBroken_get() const
{
	return GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(this->mHandle) != 0;
}
void GTAvehicle::RightHeadLightBroken_set(bool value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x77C : 0x76C);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x79C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7BC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7CC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x7EC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x80C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x84C : offset);

		SetClearBit(*(int*)(memoryAddress + offset), 1, value);
	}
}

bool GTAvehicle::IsFrontBumperBrokenOff_get() const
{
	return IS_VEHICLE_BUMPER_BROKEN_OFF(this->mHandle, true) != 0;
}
bool GTAvehicle::IsRearBumperBrokenOff_get() const
{
	return IS_VEHICLE_BUMPER_BROKEN_OFF(this->mHandle, false) != 0;
}

void GTAvehicle::BrakeLightsOn_set(bool value)
{
	SET_VEHICLE_BRAKE_LIGHTS(this->mHandle, value);
}

void GTAvehicle::HandbrakeOn_set(bool value)
{
	SET_VEHICLE_HANDBRAKE(this->mHandle, value);
}

void GTAvehicle::LeftIndicatorLightOn_set(bool value)
{
	SET_VEHICLE_INDICATOR_LIGHTS(this->mHandle, 1, value);
}
void GTAvehicle::RightIndicatorLightOn_set(bool value)
{
	SET_VEHICLE_INDICATOR_LIGHTS(this->mHandle, 0, value);
}

void GTAvehicle::InteriorLightOn_set(bool value)
{
	SET_VEHICLE_INTERIORLIGHT(this->mHandle, value);
}

bool GTAvehicle::TaxiLightOn_get() const
{
	return IS_TAXI_LIGHT_ON(this->mHandle) != 0;
}
void GTAvehicle::TaxiLightOn_set(bool value)
{
	SET_TAXI_LIGHTS(this->mHandle, value);
}

bool GTAvehicle::SearchLightOn_get() const
{
	return IS_VEHICLE_SEARCHLIGHT_ON(this->mHandle) != 0;
}
void GTAvehicle::SearchLightOn_set(bool value)
{
	SET_VEHICLE_SEARCHLIGHT(this->mHandle, value, false);
}

bool GTAvehicle::NeedsToBeHotwired_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x844 : 0x834);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x864 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x88C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x89C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x8BC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x8DC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x92C : offset);

		return IsBitSet(*(int*)(memoryAddress + offset), 2);
	}
	return false;
}
void GTAvehicle::NeedsToBeHotwired_set(bool value)
{
	SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(this->mHandle, value);
}

bool GTAvehicle::CanTyresBurst_get() const
{
	return GET_VEHICLE_TYRES_CAN_BURST(this->mHandle) != 0;
}
void GTAvehicle::CanTyresBurst_set(bool value)
{
	SET_VEHICLE_TYRES_CAN_BURST(this->mHandle, value);
}

bool GTAvehicle::CanTyresDrift_get() const
{
	return GET_DRIFT_TYRES_SET(this->mHandle) != 0;
}
void GTAvehicle::CanTyresDrift_set(bool value)
{
	SET_DRIFT_TYRES(this->mHandle, value);
}

void GTAvehicle::CanBeVisiblyDamaged_set(bool value)
{
	SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(this->mHandle, value);
}

bool GTAvehicle::PreviouslyOwnedByPlayer_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x844 : 0x834);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x864 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x88C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x89C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x8BC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x8DC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x92C : offset);

		return IsBitSet(*(int*)(memoryAddress + offset), 1);
	}
	return false;
}
void GTAvehicle::PreviouslyOwnedByPlayer_set(bool value)
{
	SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(this->mHandle, value);
}

RgbS GTAvehicle::CustomPrimaryColour_get() const
{
	int r, g, b;
	GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(this->mHandle, &r, &g, &b);
	return RgbS(r, g, b);
}
void GTAvehicle::CustomPrimaryColour_set(RgbS value)
{
	SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(this->mHandle, value.R, value.G, value.B);
}
void GTAvehicle::CustomPrimaryColour_set(BYTE r, BYTE g, BYTE b)
{
	SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(this->mHandle, r, g, b);
}

RgbS GTAvehicle::CustomSecondaryColour_get() const
{
	int r, g, b;
	GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(this->mHandle, &r, &g, &b);
	return RgbS(r, g, b);
}
void GTAvehicle::CustomSecondaryColour_set(RgbS value)
{
	SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(this->mHandle, value.R, value.G, value.B);
}
void GTAvehicle::CustomSecondaryColour_set(BYTE r, BYTE g, BYTE b)
{
	SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(this->mHandle, r, g, b);
}

RgbS GTAvehicle::NeonLightsColour_get() const
{
	int r, g, b;
	GET_VEHICLE_NEON_COLOUR(this->mHandle, &r, &g, &b);
	return RgbS(r, g, b);
}
void GTAvehicle::NeonLightsColour_set(RgbS value)
{
	SET_VEHICLE_NEON_COLOUR(this->mHandle, value.R, value.G, value.B);
}
void GTAvehicle::NeonLightsColour_set(BYTE r, BYTE g, BYTE b)
{
	SET_VEHICLE_NEON_COLOUR(this->mHandle, r, g, b);
}

RgbS GTAvehicle::TyreSmokeColour_get() const
{
	int r, g, b;
	GET_VEHICLE_TYRE_SMOKE_COLOR(this->mHandle, &r, &g, &b);
	return RgbS(r, g, b);
}
void GTAvehicle::TyreSmokeColour_set(RgbS value)
{
	SET_VEHICLE_TYRE_SMOKE_COLOR(this->mHandle, value.R, value.G, value.B);
}
void GTAvehicle::TyreSmokeColour_set(BYTE r, BYTE g, BYTE b)
{
	SET_VEHICLE_TYRE_SMOKE_COLOR(this->mHandle, r, g, b);
}

int GTAvehicle::Livery_get() const
{
	return GET_VEHICLE_LIVERY(this->mHandle);
}
void GTAvehicle::Livery_set(int liveryIndex)
{
	SET_VEHICLE_LIVERY(this->mHandle, liveryIndex);
}
int GTAvehicle::LiveryCount() const
{
	return GET_VEHICLE_LIVERY_COUNT(this->mHandle);
}

bool GTAvehicle::AlarmActive_get() const
{
	return IS_VEHICLE_ALARM_ACTIVATED(this->mHandle) != 0;
}
void GTAvehicle::AlarmActive_set(bool value)
{
	SET_VEHICLE_ALARM(this->mHandle, value);
}

int GTAvehicle::CurrentGear_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7A0 : 0x790);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x7C0 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7E0 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7F0 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x810 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x830 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x870 : offset);

		return GTAmemory::ReadByte(memoryAddress + offset);
	}
	return 0;
}
int GTAvehicle::HighGear_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7A6 : 0x796);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x7C6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7E6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7F6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x816 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x836 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x876 : offset);

		return GTAmemory::ReadByte(memoryAddress + offset);
	}
	return 0;
}
void GTAvehicle::HighGear_set(UINT8 value)
{
	if (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM)
	{
		if (value < 0 || value > 10)
			return;
	}
	else if (value < 0 || value > 7)
	{
			return;
	}
	
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7A6 : 0x796);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x7C6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7E6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7F6 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x816 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x836 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x876 : offset);

		GTAmemory::WriteByte(memoryAddress + offset, value);
	}
}
float GTAvehicle::FuelLevel_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x768 : 0x758);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x788 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7A8 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7B8 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x7D4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x7F4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x834 : offset);

		return GTAmemory::ReadFloat(memoryAddress + offset);
	}
	return 0.0f;
}
void GTAvehicle::FuelLevel_set(float value) // Uh...
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x768 : 0x758);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x788 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x7A8 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x7B8 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x7D4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x7F4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x834 : offset);

		GTAmemory::WriteFloat(memoryAddress + offset, value);
	}
}
float GTAvehicle::CurrentRPM_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7D4 : 0x7C4);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x7F4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x814 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x824 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x844 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x864 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x8B4 : offset);

		return GTAmemory::ReadFloat(memoryAddress + offset);
	}
	return 0.0f;
}
void GTAvehicle::CurrentRPM_set(float value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7D4 : 0x7C4);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x7F4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x814 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x824 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x844 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x864 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x8B4 : offset);

		GTAmemory::WriteFloat(memoryAddress + offset, value);
	}
}
float GTAvehicle::Acceleration_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x7E4 : 0x7D4);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x804 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x824 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x834 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x854 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x874 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x8C4 : offset);

		return GTAmemory::ReadFloat(memoryAddress + offset);
	}
	return 0.0f;
}
float GTAvehicle::WheelSpeed_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x9A4 : 0x994);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x9C4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x9F0 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0xA00 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0xA10 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0xA30 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0xA80 : offset);

		return GTAmemory::ReadFloat(memoryAddress + offset);
	}
	return 0.0f;
}
float GTAvehicle::SteeringAngle_get(bool inDegrees) const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x8AC : 0x89C);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x8CC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x8F4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x904 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x924 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x944 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x994 : offset);

		float steeringRadian = GTAmemory::ReadFloat(memoryAddress + offset);
		return inDegrees ? RadianToDegree(steeringRadian) : steeringRadian;
	}
	return 0.0f;
}
float GTAvehicle::SteeringScale_get() const
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x8A4 : 0x894);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x8C4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x8EC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x8FC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x91C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x93C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x98C : offset);

		return GTAmemory::ReadFloat(memoryAddress + offset);
	}
	return 0.0f;
}
void GTAvehicle::SteeringScale_set(float value)
{
	auto memoryAddress = this->MemoryAddress();
	if (memoryAddress)
	{
		int offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_372_2_STEAM ? 0x8A4 : 0x894);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_877_1_STEAM ? 0x8C4 : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_944_2_STEAM ? 0x8EC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1103_2_STEAM ? 0x8FC : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1180_2_STEAM ? 0x91C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM ? 0x93C : offset);
		offset = (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1604_0_STEAM ? 0x98C : offset);

		return GTAmemory::WriteFloat(memoryAddress + offset, value);
	}
}

//Unknown Modder
void GTAvehicle::FixDoor(VehicleDoor door)
{
	static const std::array<int32_t, 6> _vehDoorIds = { 3, 5, 4, 6, 53, 54 };
	if (static_cast<uint32_t>(door) < _vehDoorIds.size())
	{
		int32_t doorId = _vehDoorIds[static_cast<uint32_t>(door)];

		typedef void CVehicle;
		typedef void CVehicleDoor;
		// EB 03 49 8B C0 0F BF 40 0C - 0x25
		typedef CVehicleDoor*(__thiscall * tCVehicle__GetDoorByID)(CVehicle* This, uint32_t doorId);
		static tCVehicle__GetDoorByID CVehicle__GetDoorByID = (tCVehicle__GetDoorByID)(MemryScan::PatternScanner::FindPattern("EB 03 49 8B C0 0F BF 40 0C") - 0x25);
		// C1 E8 14 A8 01 0F 85 ? ? ? ? 33 DB - 0x1A
		typedef void(__thiscall * tCVehicleDoor__Fix)(CVehicleDoor* This, CVehicle* veh);
		static tCVehicleDoor__Fix CVehicleDoor__Fix = (tCVehicleDoor__Fix)(MemryScan::PatternScanner::FindPattern("C1 E8 14 A8 01 0F 85 ? ? ? ? 33 DB") - 0x1A);

		CVehicle* veh = (CVehicle*)this->MemoryAddress();
		CVehicleDoor* vehDoor = CVehicle__GetDoorByID(veh, doorId);
		CVehicleDoor__Fix(vehDoor, veh);
	}
}
void GTAvehicle::FixAllDoors()
{
	for (auto& index : this->Doors_get())
		this->FixDoor(index);
}

void GTAvehicle::RadioStation_set(int value)
{
	if (value == RadioStation::Off)
	{
		SET_VEH_RADIO_STATION(this->mHandle, "OFF");
	}
	else if (value <= GET_NUM_UNLOCKED_RADIO_STATIONS())
	{
		SET_VEH_RADIO_STATION(this->mHandle, GET_RADIO_STATION_NAME(value));
	}
}

VehicleClass GTAvehicle::ClassType_get()
{
	return static_cast<VehicleClass>(GET_VEHICLE_CLASS(this->mHandle));
}

VehicleLockStatus GTAvehicle::LockStatus_get() const
{
	return static_cast<VehicleLockStatus>(GET_VEHICLE_DOOR_LOCK_STATUS(this->mHandle));
}
void GTAvehicle::LockStatus_set(const VehicleLockStatus& value)
{
	SET_VEHICLE_DOORS_LOCKED(this->mHandle, static_cast<int>(value));
}

int GTAvehicle::GetMod(int modType) const
{
	return GET_VEHICLE_MOD(this->mHandle, modType);
}
void GTAvehicle::SetMod(int modType, int modIndex, int variation)
{
	SET_VEHICLE_MOD(this->mHandle, modType, modIndex, variation);
}
int GTAvehicle::GetModVariation(int modType) const
{
	return GET_VEHICLE_MOD_VARIATION(this->mHandle, modType);
}
void GTAvehicle::SetModVariation(int modType, bool variation)
{
	SET_VEHICLE_MOD(this->mHandle, modType, this->GetMod(modType), variation);
}
void GTAvehicle::ToggleMod(int modType, bool toggle)
{
	TOGGLE_VEHICLE_MOD(this->mHandle, modType, toggle);
}
bool GTAvehicle::IsToggleModOn(int modType) const
{
	return IS_TOGGLE_MOD_ON(this->mHandle, modType) != 0;
}
void GTAvehicle::RemoveMod(int modType)
{
	REMOVE_VEHICLE_MOD(this->mHandle, modType);
}

std::string GTAvehicle::GetModSlotName(int modType, bool getProperName) const
{
	return get_mod_slot_name(this->mHandle, modType, getProperName);
}
std::string GTAvehicle::GetModName(int modType, int modIndex, bool getProperName) const
{
	return get_mod_text_label(this->mHandle, modType, modIndex, getProperName);
}

void GTAvehicle::ClearCustomPrimaryColour()
{
	CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(this->mHandle);
}
void GTAvehicle::ClearCustomSecondaryColour()
{
	CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(this->mHandle);
}

void GTAvehicle::Explode(bool audible, bool visible)
{
	EXPLODE_VEHICLE(this->mHandle, audible, !visible);
}

bool GTAvehicle::PlaceOnGroundProperly()
{
	return SET_VEHICLE_ON_GROUND_PROPERLY(this->mHandle, 0.0f) != 0;
}
void GTAvehicle::PlaceOnNextStreet()
{
	const Vector3 pos = this->Position_get();
	Vector3_t newPos;

	float heading;
	int val;

	for (UINT8 i = 1; i < 40; i++)
	{
		GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(pos.x, pos.y, pos.z, i, &newPos, &heading, &val, 1, 3.0f, 0.0f);

		if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(newPos.x, newPos.y, newPos.z, 5.0f, 5.0f, 5.0f, 0))
		{
			this->Position_set(newPos);
			PlaceOnGround();
			this->Heading_set(heading);
			break;
		}
	}
}

std::vector<VehicleDoor> GTAvehicle::Doors_get() const
{
	std::vector<VehicleDoor> doors;
	if (this->HasBone(VBone::door_dside_f))
		doors.push_back(VehicleDoor::FrontLeftDoor);
	if (this->HasBone(VBone::door_pside_f))
		doors.push_back(VehicleDoor::FrontRightDoor);
	if (this->HasBone(VBone::door_dside_r))
		doors.push_back(VehicleDoor::BackLeftDoor);
	if (this->HasBone(VBone::door_pside_r))
		doors.push_back(VehicleDoor::BackRightDoor);
	if (this->HasBone(VBone::bonnet))
		doors.push_back(VehicleDoor::Hood);
	if (this->HasBone(VBone::boot))
		doors.push_back(VehicleDoor::Trunk);
	return doors;
}
bool GTAvehicle::HasBombBay_get() const
{
	return this->HasBone(VBone::door_hatch_l) && this->HasBone(VBone::door_hatch_r);
}
bool GTAvehicle::HasForks_get() const
{
	return HasBone(VBone::forks);
}
bool GTAvehicle::HasSiren_get() const
{
	return HasBone(VBone::siren1);
}
bool GTAvehicle::HasTowArm_get() const
{
	return HasBone(VBone::tow_arm);
}

void GTAvehicle::OpenDoor(VehicleDoor door, bool loose, bool instantly, bool playSound)
{
	SET_VEHICLE_DOOR_OPEN(this->mHandle, static_cast<int>(door), loose, instantly);
	if (playSound) PLAY_VEHICLE_DOOR_OPEN_SOUND(this->mHandle, 1);
}
void GTAvehicle::CloseDoor(VehicleDoor door, bool instantly, bool playSound)
{
	SET_VEHICLE_DOOR_SHUT(this->mHandle, static_cast<int>(door), instantly);
	if (playSound) PLAY_VEHICLE_DOOR_CLOSE_SOUND(this->mHandle, 1);
}
void GTAvehicle::CloseAllDoors(bool instantly)
{
	SET_VEHICLE_DOORS_SHUT(this->mHandle, instantly);
}
void GTAvehicle::BreakDoor(VehicleDoor door, bool instant)
{
	SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(this->mHandle, static_cast<int>(door), true);
	SET_VEHICLE_DOOR_BROKEN(this->mHandle, static_cast<int>(door), instant);
}
void GTAvehicle::BreakAllDoors(bool instant)
{
	for (int door = 0; door <= 6; door++)
	{
		SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(this->mHandle, (door), true);
		SET_VEHICLE_DOOR_BROKEN(this->mHandle, door, instant);
	}
}
float GTAvehicle::GetDoorAngleRatio(VehicleDoor door) const
{
	return GET_VEHICLE_DOOR_ANGLE_RATIO(this->mHandle, static_cast<int>(door));
}
bool GTAvehicle::IsDoorOpen(VehicleDoor door) const
{
	return GET_VEHICLE_DOOR_ANGLE_RATIO(this->mHandle, static_cast<int>(door)) > 0.0f;
}
bool GTAvehicle::IsDoorFullyOpen(VehicleDoor door) const
{
	return IS_VEHICLE_DOOR_FULLY_OPEN(this->mHandle, static_cast<int>(door)) != 0;
}
bool GTAvehicle::IsDoorBroken(VehicleDoor door) const
{
	return IS_VEHICLE_DOOR_DAMAGED(this->mHandle, static_cast<int>(door)) != 0;
}
void GTAvehicle::SetDoorBreakable(VehicleDoor door, bool isBreakable)
{
	SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(this->mHandle, static_cast<int>(door), isBreakable);
}

void GTAvehicle::OpenBombBay()
{
	if (this->HasBombBay_get())
		OPEN_BOMB_BAY_DOORS(this->mHandle);
}
void GTAvehicle::CloseBombBay()
{
	if (this->HasBombBay_get())
		CLOSE_BOMB_BAY_DOORS(this->mHandle);
}

bool GTAvehicle::IsWindowIntact(VehicleWindow window)
{
	return IS_VEHICLE_WINDOW_INTACT(this->mHandle, static_cast<int>(window));
}
void GTAvehicle::FixWindow(VehicleWindow window)
{
	FIX_VEHICLE_WINDOW(this->mHandle, static_cast<int>(window));
}
void GTAvehicle::SmashWindow(VehicleWindow window)
{
	SMASH_VEHICLE_WINDOW(this->mHandle, static_cast<int>(window));
}
void GTAvehicle::RollUpWindow(VehicleWindow window)
{
	ROLL_UP_WINDOW(this->mHandle, static_cast<int>(window));
}
void GTAvehicle::RollDownWindow(VehicleWindow window)
{
	ROLL_DOWN_WINDOW(this->mHandle, static_cast<int>(window));
}
void GTAvehicle::RollDownWindows()
{
	ROLL_DOWN_WINDOWS(this->mHandle);
}
void GTAvehicle::RemoveWindow(VehicleWindow window)
{
	REMOVE_VEHICLE_WINDOW(this->mHandle, static_cast<int>(window));
}

bool GTAvehicle::IsNeonLightOn(VehicleNeonLight light) const
{
	return GET_VEHICLE_NEON_ENABLED(this->mHandle, static_cast<int>(light)) != 0;
}
void GTAvehicle::SetNeonLightOn(VehicleNeonLight light, bool on)
{
	SET_VEHICLE_NEON_ENABLED(this->mHandle, static_cast<int>(light), on);
}

bool GTAvehicle::DoesExtraExist(int extraId) const
{
	return DOES_EXTRA_EXIST(this->mHandle, extraId) != 0;
}
bool GTAvehicle::ExtraOn_get(int extraId) const
{
	return IS_VEHICLE_EXTRA_TURNED_ON(this->mHandle, extraId) != 0;
}
void GTAvehicle::ExtraOn_set(int extraId, bool value)
{
	SET_VEHICLE_EXTRA(this->mHandle, extraId, !value); // Opposite for some reason
}

void GTAvehicle::SoundHorn(int duration)
{
	START_VEHICLE_HORN(this->mHandle, duration, 0x839504CB, 0); // HELDDOWN = 0x839504CB
}

void GTAvehicle::SetHeliYawPitchRollMult(float value)
{
	if (this->Model().IsHeli())
	{
		if (value >= 0.0f && value <= 1.0f)
		{
			SET_HELI_CONTROL_LAGGING_RATE_SCALAR(this->mHandle, value);
		}
	}
}

void GTAvehicle::DropCargobobHook(CargobobHook hookType)
{
	if (this->Model().IsCargobob())
	{
		CREATE_PICK_UP_ROPE_FOR_CARGOBOB(this->mHandle, static_cast<int>(hookType));
	}
}
bool GTAvehicle::IsCargobobHookActive() const
{
	if (this->Model().IsCargobob())
	{
		return DOES_CARGOBOB_HAVE_PICK_UP_ROPE(this->mHandle) || DOES_CARGOBOB_HAVE_PICKUP_MAGNET(this->mHandle);
	}
	return false;
}
bool GTAvehicle::IsCargobobHookActive(CargobobHook hookType) const
{
	if (this->Model().IsCargobob())
	{
		switch (hookType)
		{
		case CargobobHook::Hook:
			return DOES_CARGOBOB_HAVE_PICK_UP_ROPE(this->mHandle) != 0;
		case CargobobHook::Magnet:
			return DOES_CARGOBOB_HAVE_PICKUP_MAGNET(this->mHandle) != 0;
		}
	}
	return false;
}
void GTAvehicle::RetractCargobobHook()
{
	if (this->Model().IsCargobob())
	{
		REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(this->mHandle);
	}
}
void GTAvehicle::CargoBobMagnetGrabVehicle()
{
	if (this->IsCargobobHookActive(CargobobHook::Magnet))
	{
		SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(this->mHandle, true);
	}
}
void GTAvehicle::CargoBobMagnetReleaseVehicle()
{
	if (this->IsCargobobHookActive(CargobobHook::Magnet))
	{
		SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(this->mHandle, false);
	}
}

bool GTAvehicle::IsBoatAnchored()
{
	return IS_BOAT_ANCHORED(this->mHandle);
}

bool GTAvehicle::CanBoatAnchorHere()
{
	return CAN_ANCHOR_BOAT_HERE(this->mHandle);
}

void GTAvehicle::AnchorBoat(bool anchored)
{
	if (this->CanBoatAnchorHere())
	{
		SET_BOAT_ANCHOR(this->mHandle, anchored);
		SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(this->mHandle, anchored);
	}
}

bool GTAvehicle::IsTyreBursted(int wheel, bool completely) const
{
	return IS_VEHICLE_TYRE_BURST(this->mHandle, wheel, completely) != 0;
}
void GTAvehicle::BurstTyre(int wheel)
{
	if (!GET_VEHICLE_TYRES_CAN_BURST(this->mHandle)) SET_VEHICLE_TYRES_CAN_BURST(this->mHandle, true);
	SET_VEHICLE_TYRE_BURST(this->mHandle, wheel, 1, 0x447a0000); // 1000.0f
}
void GTAvehicle::FixTyre(int wheel)
{
	SET_VEHICLE_TYRE_FIXED(this->mHandle, wheel);
}
bool GTAvehicle::IsInBurnout() const
{
	return IS_VEHICLE_IN_BURNOUT(this->mHandle) != 0;
}
void GTAvehicle::ForceBurnout_set(bool value)
{
	SET_VEHICLE_BURNOUT(this->mHandle, value);
}

void GTAvehicle::StartAlarm()
{
	START_VEHICLE_ALARM(this->mHandle);
}

void GTAvehicle::ApplyDamage(Vector3 loc, float damageAmount, float radius)
{
	SET_VEHICLE_DAMAGE(this->mHandle, loc.x, loc.y, loc.z, damageAmount, radius, true);
}

GTAentity GTAvehicle::CreatePedOnSeat(VehicleSeat seat, GTAmodel::Model model)
{
	if (!model.IsInCdImage() || !model.Load(3000))
	{
		return 0;
	}
	return CREATE_PED_INSIDE_VEHICLE(this->mHandle, 26, model.hash, (seat), 1, 1);
}
GTAentity GTAvehicle::CreateRandomPedOnSeat(VehicleSeat seat)
{
	if (seat == VehicleSeat::SEAT_DRIVER)
	{
		return CREATE_RANDOM_PED_AS_DRIVER(this->mHandle, true);
	}
	else
	{
		GTAentity ped = CREATE_RANDOM_PED(0.0f, 0.0f, 0.0f);
		SET_PED_INTO_VEHICLE(ped.Handle(), this->mHandle, static_cast<int>(seat));
		return ped;
	}
}



// Vehicle - Emblem
inline bool get_vehicle_info_for_emblem_pos(Model vehicleModel, Vector3& x, Vector3& y, Vector3& z, float& scale)
{
	switch (vehicleModel.hash)
	{
	default:
		x = { -1, 0, 0.295f };
		y = { 1, 0, 0 };
		z = { 0, 0, -1 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DOMINATOR:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_FELTZER2:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ADDER:
		x = { 0, 1.54f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_AKUMA:
		x = { 0, 0.06f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.18f;
		return true;
		break;
	case VEHICLE_ASEA:
		x = { 0, 1.5f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ASTEROPE:
		x = { 0, 1.7f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BAGGER:
		x = { -1, 0.16f, 0.283f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.09f;
		return true;
		break;
	case VEHICLE_BALLER:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BALLER2:
		x = { 0, 1.55f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BANSHEE:
		x = { 0, 0.94f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4;
		return true;
		break;
	case VEHICLE_BATI:
		x = { 0, 0.2f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_BATI2:
		x = { 0, 0.2f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_BFINJECTION:
		x = { -1, 0.08f, 0.19f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5;
		return true;
		break;
	case VEHICLE_BISON:
		x = { 0, 1.99f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BJXL:
		x = { 0, 1.2f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_BLISTA:
		x = { 0, 1.49f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.29f;
		return true;
		break;
	case VEHICLE_BOBCATXL:
		x = { 0, 1.68f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.65f;
		return true;
		break;
	case VEHICLE_BODHI2:
		x = { 0, 1.95f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BUCCANEER:
		x = { 0, 2.01f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.37f;
		return true;
		break;
	case VEHICLE_BUFFALO:
		x = { 0, 1.6f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BUFFALO2:
		x = { 0, 2.24f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_BULLET:
		x = { -1.57f, 0.07f, 0.16f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_CARBONRS:
		x = { 0, 0.09f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.18f;
		return true;
		break;
	case VEHICLE_CARBONIZZARE:
		x = { 0, 1.45f, 1 };
		y = { 0, -0.11f, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_CAVALCADE:
		x = { 0, 1.51f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.55f;
		return true;
		break;
	case VEHICLE_CAVALCADE2:
		x = { 0, 1.59f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_CHEETAH:
		x = { -1.61f, 0.26f, 0.17f };
		y = { 0.9f, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_COGCABRIO:
		x = { 0, 1.42f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_COMET2:
		x = { 0, 1.35f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_COQUETTE:
		x = { 0, 0.96f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.22f;
		return true;
		break;
	case VEHICLE_DAEMON:
		x = { 0, 0.06f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_DILETTANTE:
		x = { 0, 1.59f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DLOADER:
		x = { 0, 1.52f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DOUBLE:
		x = { 0, 0.08f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_DUBSTA:
		x = { -1.71f, 0.31f, 0.27f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DUBSTA2:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.75f;
		return true;
		break;
	case VEHICLE_ELEGY2:
		x = { 0, 1.14f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_EMPEROR:
		x = { 0, 1.31f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_EMPEROR2:
		x = { 0, 1.31f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ENTITYXF:
		x = { -1.52f, 0.41f, 0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_EXEMPLAR:
		x = { 0, 1.32f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_F620:
		x = { 0, 1.28f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_FAGGIO2:
		x = { -1, -0.48f, -0.11f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_FELON:
		x = { 0, 1.24f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_FELON2:
		x = { 0, 1.24f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_FQ2:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_FUGITIVE:
		x = { 0, 1.62f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_FUSILADE:
		x = { 0, 0.98f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_FUTO:
		x = { 0, 1.28f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_GAUNTLET:
		x = { 0, 1.735f, 1.05f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.33f;
		return true;
		break;
	case VEHICLE_GRANGER:
		x = { 0, 2.07f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_GRESLEY:
		x = { 0, 1.75f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_HABANERO:
		x = { 0, 1.69f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_HEXER:
		x = { 0, -0.46f, 1 };
		y = { 0, 1, -1 };
		z = { -1, 0, 0 };
		scale = 0.14f;
		return true;
		break;
	case VEHICLE_HOTKNIFE:
		x = { -1.43f, -0.14f, 0.18f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_INFERNUS:
		x = { -1, 0.33f, 0.08f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0.06f };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_INGOT:
		x = { 0, 1.58f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_INTRUDER:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ISSI2:
		x = { 0, 1.21f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_JACKAL:
		x = { 0, 1.36f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_JB700:
		x = { 0, 1.2f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.37f;
		return true;
		break;
	case VEHICLE_KHAMELION:
		x = { 0, 1.46f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.475f;
		return true;
		break;
	case VEHICLE_LANDSTALKER:
		x = { 0, 1.83f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_MANANA:
		x = { 0, 0.86f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.37f;
		return true;
		break;
	case VEHICLE_MESA:
		x = { 0, 1.47f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_MESA3:
		x = { 0, 1.47f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_MINIVAN:
		x = { 0, 1.95f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_MONROE:
		x = { 0, 1.23f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.43f;
		return true;
		break;
	case VEHICLE_NEMESIS:
		x = { 0, 0.14f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_NINEF:
		x = { 0, 1.7f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_NINEF2:
		x = { 0, 1.7f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ORACLE:
		x = { 0, 1.6f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ORACLE2:
		x = { 0, 1.7f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PATRIOT:
		x = { 0, 1.75f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PCJ:
		x = { 0, 0.02f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_PENUMBRA:
		x = { 0, 1.46f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PEYOTE:
		x = { -1, -0.36f, 0.2125f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PHOENIX:
		x = { 0, 1.833f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.44f;
		return true;
		break;
	case VEHICLE_PICADOR:
		x = { 0, 1.43f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.515f;
		return true;
		break;
	case VEHICLE_PRAIRIE:
		x = { 0, 1.41f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.31f;
		return true;
		break;
	case VEHICLE_PREMIER:
		x = { 0, 1.6f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PRIMO:
		x = { 0, 1.62f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RADI:
		x = { 0, 1.74f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RANCHERXL:
		x = { 0, 1.54f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RAPIDGT:
		x = { 0, 1.263f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RAPIDGT2:
		x = { 0, 1.263f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RATLOADER:
		x = { -1.78f, 0.52f, 0.52f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_REBEL:
		x = { -1.22f, 0.6f, 0.44f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_REBEL2:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_REGINA:
		x = { 0, 1.473f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ROCOTO:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ROMERO:
		x = { 0, 1.83f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_RUFFIAN:
		x = { 0, -0.02f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.19f;
		return true;
		break;
	case VEHICLE_RUINER:
		x = { 0, 1.34f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SABREGT:
		x = { -1, 0, 0.14f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0.015f };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_SADLER:
		x = { 0, 2.26f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SANDKING:
		x = { 0, 2.496f, 1.55f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SANDKING2:
		x = { 0, 2.286f, 1.55f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SCHAFTER2:
		x = { 0, 1.56f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_SCHWARZER:
		x = { 0, 1.43f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_SEMINOLE:
		x = { 0, 1.45f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SENTINEL:
		x = { 0, 1.52f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SENTINEL2:
		x = { 0, 1.52f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SERRANO:
		x = { 0, 1.68f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.49f;
		return true;
		break;
	case VEHICLE_STANIER:
		x = { 0, 1.55f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_STINGER:
		x = { 0, 1.3f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_STINGERGT:
		x = { -1, -0.17f, 0.12f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_STRATUM:
		x = { 0, 1.52f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SULTAN:
		x = { 0, 1.77f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.33f;
		return true;
		break;
	case VEHICLE_SUPERD:
		x = { 0, 1.62f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SURANO:
		x = { 0, 1.38f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SURFER:
		x = { 0, 2.48f, 0.26f };
		y = { 0, -1, -0.212f };
		z = { -1, 0, 0 };
		scale = 0.32f;
		return true;
		break;
	case VEHICLE_SURFER2:
		x = { 0, 2.48f, 0.26f };
		y = { 0, -1, -0.212f };
		z = { -1, 0, 0 };
		scale = 0.32f;
		return true;
		break;
	case VEHICLE_SURGE:
		x = { 0, 1.69f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_TAILGATER:
		x = { 0, 1.783f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_TORNADO:
		x = { -1.23f, 0.11f, -0.21f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_TORNADO2:
		x = { 0, 1.44f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_TORNADO3:
		x = { 0, 1.44f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_VACCA:
		x = { 0, 1.76f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_VADER:
		x = { 0, 0.08f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_VIGERO:
		x = { -1, 0.11f, -0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_VOLTIC:
		x = { 0, 1.763f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.29f;
		return true;
		break;
	case VEHICLE_VOODOO2:
		x = { 0, 1.48f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_WASHINGTON:
		x = { 0, 1.61f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_YOUGA:
		x = { 0, 2.352f, 1.003f };
		y = { 0, -1, -1 };
		z = { -1, 0, 0 };
		scale = 0.175f;
		return true;
		break;
	case VEHICLE_ZION:
		x = { 0, 1.48f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_ZION2:
		x = { 0, 1.48f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_ZTYPE:
		x = { -0.96f, -0.69f, 0.35f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_KALAHARI:
		x = { -1, 0.18f, 0.1f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PARADISE:
		x = { 0, 2.23f, 1 };
		y = { 0, -0.22f, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_ALPHA:
		x = { -1, 0.18f, -0.05f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_HUNTLEY:
		x = { 0, 1.52f, 0.99f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_ZENTORNO:
		x = { -1.24f, 0.42f, -0.14f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0.035f };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_JESTER:
		x = { -1, 0.17f, 0.22f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0.05f };
		scale = 0.33f;
		return true;
		break;
	case VEHICLE_MASSACRO:
		x = { 0, 1.37f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.33f;
		return true;
		break;
	case VEHICLE_TURISMOR:
		x = { -1, 0.3f, 0.27f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_THRUST:
		x = { -1, 0.405f, 0.4625f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1625f;
		return true;
		break;
	case VEHICLE_BTYPE:
		x = { 0, 1.143f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.7125f;
		return true;
		break;
	case VEHICLE_RHAPSODY:
		x = { -1, -0.47f, -0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.2625f;
		return true;
		break;
	case VEHICLE_GLENDALE:
		x = { 0, 1.683f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.775f;
		return true;
		break;
	case VEHICLE_WARRENER:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.775f;
		return true;
		break;
	case VEHICLE_BLADE:
		x = { -1, 0.445f, 0.2075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.325f;
		return true;
		break;
	case VEHICLE_PANTO:
		x = { -1, 0, 0.335f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DUBSTA3:
		x = { -1, 0.34f, 0.2975f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PIGALLE:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_COQUETTE2:
		x = { -1, -0.1775f, 0.195f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_INNOVATION:
		x = { 0, 0.15f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.18f;
		return true;
		break;
	case VEHICLE_HAKUCHOU:
		x = { 0, 0.27f, 0.845f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.16f;
		return true;
		break;
	case VEHICLE_FUROREGT:
		x = { -1, 0, 0.2075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_RATLOADER2:
		x = { -1.78f, 0.52f, 0.52f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_SLAMVAN:
		x = { -1, 0.275f, 0.195f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_DUKES2:
		x = { -1, 0, 0 };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.375f;
		return true;
		break;
	case VEHICLE_DUKES:
		x = { -1, 0, 0.0375f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3875f;
		return true;
		break;
	case VEHICLE_STALION:
		x = { -1, 0, 0.0925f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4375f;
		return true;
		break;
	case VEHICLE_BLISTA2:
		x = { -1, 0.5325f, 0.245f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.2875f;
		return true;
		break;
	case VEHICLE_CASCO:
		x = { 0, 0.94f, 1.03f };
		y = { 0, -0.03f, -1 };
		z = { -1, 0, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_ENDURO:
		x = { 0, -0.17f, 1 };
		y = { 0, 0.34f, -0.786f };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_GBURRITO2:
		x = { 0, 2.32f, 0.94f };
		y = { 0, -0.182f, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_GUARDIAN:
		x = { -1.94f, 1.07f, 0.38f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_KURUMA:
	case VEHICLE_KURUMA2:
		x = { -1, 0.2475f, -0.175f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.435f;
		return true;
		break;
	case VEHICLE_LECTRO:
		x = { 0, 0.3f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.09f;
		return true;
		break;
	case VEHICLE_FELTZER3:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_OSIRIS:
		x = { -1, 0.27f, -0.03f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_VIRGO:
		x = { -1.05f, 0, 0.075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_WINDSOR:
		x = { -1.2f, -0.39f, 0.12f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.55f;
		return true;
		break;
	case VEHICLE_BRAWLER:
		x = { -1, -0.21f, 0 };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_CHINO:
		x = { -1.05f, 0, 0.075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_COQUETTE3:
		x = { -1, -0.1775f, 0.195f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_T20:
		x = { -1, 0.4f, -0.12f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_VINDICATOR:
		x = { -1, 0.21f, 0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_FACTION:
		x = { -1, 0, 0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_FACTION2:
		x = { -1, 0, 0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BUCCANEER2:
		x = { 0, 2.01f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.37f;
		return true;
		break;
	case VEHICLE_CHINO2:
		x = { -1.05f, 0, 0.075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_MOONBEAM:
		x = { 0, 1.713f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_MOONBEAM2:
		x = { 0, 1.713f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_PRIMO2:
		x = { -1, 0.42f, 0 };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_VOODOO:
		x = { -1.12f, 0, 0 };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_FACTION3:
		x = { -1, 0, 0.5f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SABREGT2:
		x = { -1, 0, 0.14f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0.015f };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_TORNADO5:
		x = { -1, 0.15f, -0.09f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_VIRGO2:
		x = { -1, 0, 0.1225f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.375f;
		return true;
		break;
	case VEHICLE_VIRGO3:
		x = { -1, 0, 0.1225f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.375f;
		return true;
		break;
	case VEHICLE_MINIVAN2:
		x = { 0, 1.95f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_SLAMVAN3:
		x = { -1, 0.275f, 0.195f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BTYPE2:
		x = { -1, -0.1f, 0.4f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_LURCHER:
		x = { -1, 0, 0.3f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_BALLER3:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BALLER4:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BALLER5:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BALLER6:
		x = { 0, 1.4f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_COG55:
		x = { -1, 0.37f, 0.13f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_COG552:
		x = { -1, 0.37f, 0.13f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_COGNOSCENTI:
		x = { -1, 0.37f, 0.13f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_COGNOSCENTI2:
		x = { -1, 0.37f, 0.13f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_MAMBA:
		x = { -1, -0.18f, 0.21f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_NIGHTSHADE:
		x = { -1, -0.2f, 0.17f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_SCHAFTER3:
		x = { 0, 1.56f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_SCHAFTER4:
		x = { 0, 1.56f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_SCHAFTER5:
		x = { 0, 1.56f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_SCHAFTER6:
		x = { 0, 1.56f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.28f;
		return true;
		break;
	case VEHICLE_VERLIERER2:
		x = { -1, -0.21f, 0.03f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_TAMPA:
		x = { -1, 0, 0.12f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_BANSHEE2:
		x = { -1, -0.4f, 0.075f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_SULTANRS:
		x = { 0, 1.77f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.33f;
		return true;
		break;
	case VEHICLE_BTYPE3:
		x = { -1, -0.1f, 0.4f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_BESTIAGTS:
		x = { -1, -0.06f, 0.4f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_SEVEN70:
		x = { -1, -0.21f, 0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_FMJ:
		x = { -1, -0.06f, 0.21f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_PFISTER811:
		x = { -1, 0.06f, 0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_PROTOTIPO:
		x = { -1, 0.3f, 0.27f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_REAPER:
		x = { -1, 0.48f, 0 };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_RUMPO3:
		x = { 0, 2.103f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_WINDSOR2:
		x = { -1.2f, 0.03f, 0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.55f;
		return true;
		break;
	case VEHICLE_XLS:
		x = { -1, 0.36f, -0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_XLS2:
		x = { -1, 0.36f, -0.15f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_BRIOSO:
		x = { -1, -0.06f, 0.565f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_CONTENDER:
		x = { 0, 2.33f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_LE7B:
		x = { -1, -0.12f, 0.235f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_OMNIS:
		x = { -1, 0.03f, 0.18f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_TROPOS:
		x = { -1, 0, 0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_AVARUS:
		x = { -1, 0.27f, 0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_DAEMON2:
		x = { -1, 0.27f, 0.29f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_DEFILER:
		x = { -1, 0, 0.34f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.125f;
		return true;
		break;
	case VEHICLE_ESSKEY:
		x = { -1, 0.335f, 0.31f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.09f;
		return true;
		break;
	case VEHICLE_HAKUCHOU2:
		x = { 0, 0.27f, 0.845f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_NIGHTBLADE:
		x = { 0, -0.133f, 0.61f };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.125f;
		return true;
		break;
	case VEHICLE_RATBIKE:
		x = { -1, 0.31f, 0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_SHOTARO:
		x = { -1, 0.06f, 0.325f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_ZOMBIEA:
		x = { -1, 0.3f, 0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_ZOMBIEB:
		x = { -1, 0.2f, 0.25f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_VORTEX:
		x = { -1, 0.18f, 0.37f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.095f;
		return true;
		break;
	case VEHICLE_TORNADO6:
		x = { -1, -0.03f, -0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_YOUGA2:
		x = { 0, 2.352f, 0.253f };
		y = { 0, -1, -0.256f };
		z = { -1, 0, 0 };
		scale = 0.175f;
		return true;
		break;
	case VEHICLE_WOLFSBANE:
		x = { -1, 0.33f, 0.24f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_FAGGIO3:
		x = { -1, -0.54f, -0.11f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_FAGGIO:
		x = { -0.9875f, -0.0175f, -0.01f };
		y = { 0.8975f, -0.26f, -0.0725f };
		z = { 0, -1, 0 };
		scale = 0.1625f;
		return true;
		break;
	case VEHICLE_COMET3:
		x = { -1, 0, 0.295f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_DIABLOUS:
		x = { -1, 0.006f, 0.382f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_DIABLOUS2:
		x = { -1, 0.225f, 0.541f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_ELEGY:
		x = { 0, 1.14f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_FCR:
		x = { -1, 0.234f, 0.376f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_FCR2:
		x = { -1, 0.234f, 0.376f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_ITALIGTB:
		x = { -1, -0.024f, 0.187f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_ITALIGTB2:
		x = { -1, -0.024f, 0.187f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_NERO:
		x = { -1, 0.237f, 0.09f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_NERO2:
		x = { -1, 0.237f, 0.09f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_PENETRATOR:
		x = { -1, 0.153f, 0.295f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_RUINER2:
		x = { 0.363f, 1.34f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_RUINER3:
		x = { 0.363f, 1.34f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.4f;
		return true;
		break;
	case VEHICLE_SPECTER:
		x = { -1, -0.273f, -0.02f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_SPECTER2:
		x = { -1, -0.273f, 0.286f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_TECHNICAL2:
		x = { 0, 1.623f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.5f;
		return true;
		break;
	case VEHICLE_TEMPESTA:
		x = { -1, 0, 0.253f };
		y = { 1, 0, 0 };
		z = { 0, -1, 0 };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_VOLTIC2:
		x = { 0, 1.763f, 1 };
		y = { 0, 0, -1 };
		z = { -1, 0, 0 };
		scale = 0.29f;
		return true;
		break;
	case VEHICLE_INFERNUS2:
		x = { -1.0f, 0.33f, 0.06f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.06f };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_RUSTON:
		x = { -1.0f, -0.273f, 0.084f };
		y = { 1.0f, 0.0f, .00f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_TURISMO2:
		x = { -1.0f, 0.159f, -0.193f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_ARDENT:
		x = { -1.0f, 0.309f, 0.276f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_CHEETAH2:
		x = { -1.0f, 0.159f, 0.127f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_HALFTRACK:
		x = { -1.0f, 0.501f, 0.531f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
		break;
	case VEHICLE_NIGHTSHARK:
		x = { -1.5f, 0.42f, 0.584f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_OPPRESSOR:
		x = { -1.0f, 0.306f, 0.355f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.8f;
		return true;
		break;
	case VEHICLE_TAMPA3:
		x = { 0.0f, 1.515f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.275f;
		return true;
		break;
	case VEHICLE_TECHNICAL3:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.43f;
		return true;
		break;
	case VEHICLE_TORERO:
		x = { -1.0f, 0.201f, 0.114f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
		break;
	case VEHICLE_VAGNER:
		x = { -1.5f, 0.906f, 0.071f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.1f;
		return true;
		break;
	case VEHICLE_XA21:
		x = { -1.0f, 0.441f, 0.13f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.25f;
		return true;
		break;
	case VEHICLE_PHANTOM3:
		x = { -1.3f, 2.045f, 0.802f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_HAULER2:
		x = { -1.627f, 2.456f, 0.745f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
		break;
	case VEHICLE_CYCLONE:
		x = { -1.0f, 0.186f, 0.382f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2f;
		return true;
		break;
	case VEHICLE_VISIONE:
		x = { -1.0f, 0.432f, 0.031f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.15f;
		return true;
		break;
	case VEHICLE_VIGILANTE:
		x = { -1.0f, 0.232f, 0.24f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.175f;
		return true;
		break;
	case VEHICLE_RAPIDGT3:
		x = { 0.0f, 1.972f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
		break;
	}

	/// sjaak327
	//typedef std::tuple<LPCSTR, Hash, float, float, float, float, float, float, float, float, float, float> embleminfo_t;
	struct embleminfo_t { LPCSTR vehName; Hash vehHash; float x1, x2, x3; float y1, y2, y3; float z1, z2, z3; float scale; }; //sjaak327
	for (auto& i : std::vector<embleminfo_t>{
		{ "AVENGER", (Hash)2176659152, -2.02f, 6.45f, -0.716f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.35f },
		{ "AVENGER2",(Hash)408970549, -2.02f, 6.45f, -0.716f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.35f },
		{ "DELUXO",(Hash)1483171323, -1.0f, -0.291f, 0.247f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.2f },
		{ "STROMBERG",(Hash)886810209,-1.0f, 0.23f, 0.247f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.2f },
		{ "RIOT2", (Hash)-1693015116,-1.891f, 2.144f, 0.657f,1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.35f },
		{ "CHERNOBOG",(Hash)-692292317,-2.127f, 5.413f, 1.132f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.34f },
		{ "KHANJALI",(Hash)-1435527158, -0.897f, 1.391f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.4f },
		{ "BARRAGE",(Hash)-212993243, -1.51f, 0.71f, 0.451f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.25f },
		{ "COMET4",(Hash)1561920505,-1.0f, 0.298f, 0.257f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.36f },
		{ "NEON",(Hash)-1848994066,-1.0f, 0.181f, -0.066f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.3f },
		{ "STREITER",(Hash)1741861769,-1.0f, 0.301f, 0.295f,1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "SENTINEL3",(Hash)1104234922, 0.0f, 1.52f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.5f },
		{ "YOSEMITE",(Hash)1871995513, -1.0f, 0.252f, 0.201f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.3f },
		{ "SC1",(Hash)1352136073,-1.f, 0.616f, -0.131f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.25f },
		{ "AUTARCH",(Hash)-313185164, -1.0f, 0.0f, 0.116f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.25f },
		{ "GT500",(Hash)-2079788230, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f,  0.f, -1.f, 0.f,  0.25f },
		{ "HUSTLER",(Hash)600450546,-1.f, -0.228f, 0.321f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.4f },
		{ "REVOLTER", (Hash)-410205223,-1.f, 0.203f, 0.126f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.45f },
		{ "PARIAH",(Hash)867799010, -1.f, -0.126f, 0.208f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.35f },
		{ "RAIDEN",(Hash)-1529242755, -1.f, 0.252f, -0.095f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.35f },
		{ "SAVESTRA",(Hash)903794909, -1.f, 0.f, 0.25f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.35f },
		{ "RIATA",(Hash)-1532697517, -1.3f, 0.18f, 0.511f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.3f },
		{ "HERMES",(Hash)15219735, -1.f, -0.134f, 0.158f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.4f },
		{ "COMET5",(Hash)661493923, -1.f, 0.002f, 0.031f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.35f },
		{ "Z190",(Hash)838982985, -1.f, -0.175f, 0.242f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.4f },
		{ "VISERIS",(Hash)-391595372,  -1.f, 0.f, 0.244f,  1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.275f },
		{ "KAMACHO",(Hash)-121446169, -1.315f, 0.507f, 0.518f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f,  0.25f },

		{ "GB200",(Hash)1909189272, -1.0f, 0.0f, 0.407f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.225f },
		{ "FAGALOA",(Hash)1617472902, -1.0f, 0.0f, 0.225f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "ELLIE", (Hash)-1267543371,-1.0f, 0.441f, -0.128f,1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.35f },
		{ "ISSI3", (Hash)931280609, -1.0f, 0.195f, 0.246f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "MICHELLI",(Hash)1046206681,-1.0f, 0.0f, 0.0805f,1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f, 0.35f },
		{ "FLASHGT",(Hash)-1259134696, 0.0f, 1.592f, 1.0f, 0.0f, 0.0f, -1.0f,-1.0f, 0.0f, 0.0f,0.25f },
		{ "HOTRING",(Hash)1115909093, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.5f },
		{ "TEZERACT",(Hash)1031562256,-1.0f, 0.679f, 0.514f, 1.0f, 0.0f, -0.75f, 0.0f, -1.0f, 0.0f,0.175f },
		{ "TYRANT",(Hash)-376434238, -1.588f, 0.315f, 0.337f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.3f },
		{ "DOMINATOR3",(Hash)-986944621,-1.0f, 0.0f, 0.221f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.5f },
		{ "TAIPAN", (Hash)-1134706562, -1.0f, 0.0f, 0.219f,1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.4f },
		{ "ENTITY2",(Hash)-2120700196,-1.52f, 0.41f, 0.15f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.3f },
		{ "JESTER3",(Hash)-214906006,-1.0f, 0.0f, 0.297f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.4f },
		{ "CHEBUREK",(Hash)-988501280,-1.0f, 0.393f, 0.162f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.375f },
		{ "CARACARA",(Hash)1254014755,-1.0f, 1.266f, 0.4115f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.4f },

		{ "MENACER",(Hash)2044532910, -1.73f, 0.159f, 0.61f , 1.0f, 0.12f, 0.f , 0.0f, -1.0f, 0.0f , 0.4f },
		{ "SCRAMJET",(Hash)-638562243, -1.0f, -0.188f, 0.0f , 1.0f, 0.0f, 0.0f , 0.0f, -1.0f, 0.0f ,0.25f },
		{ "PATRIOT2",(Hash)-420911112,-1.213f, 1.546f, 0.511f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.3f },
		{ "STAFFORD",(Hash)321186144, -1.0f, 0.036f, 0.096f,1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,0.4f },
		{ "FREECRAWLER",(Hash)-54332285,-1.0f, 0.249f, 0.511f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "OPPRESSOR2",(Hash)2069146067,-1.0f, 0.306f, 0.355f,1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.08f },
		{ "TERBYTE",(Hash)-1988428699,-1.73f, 3.397f, 0.724f, 1.0f, 0.12f, 0.0f,0.0f, -1.0f, 0.0f, 0.25f },

		{ "BRUISER", (Hash)668439077, 0.0f, 2.12f, 1.241f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.084f, 0.775f },
		{ "BRUISER2",(Hash)-1694081890, 0.0f, 2.12f, 1.241f, 0.0f, 0.0f, -1.0f ,-1.0f, 0.0f, 0.084f, 0.775f },
		{ "BRUISER3",(Hash)-2042350822, 0.0f, 2.12f, 1.241f, 0.0f, 0.0f, -1.0f,-1.0f, 0.0f, 0.084f,0.775f },
		{ "BRUTUS", (Hash)2139203625, -1.0f, 0.446f, 0.247f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "BRUTUS2", (Hash)-1890996696,-1.0f, 0.446f, 0.247f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "BRUTUS3", (Hash)2038858402,-1.0f, 0.446f, 0.247f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.4f },
		{ "CERBERUS",(Hash)-801550069,-1.432f, 1.443f, 1.292f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f },
		{ "CERBERUS2",(Hash)679453769,-1.432f, 1.443f, 1.292f,	1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f },
		{ "CERBERUS3",(Hash)1909700336,-1.432f, 1.443f, 1.292f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f },
		{ "CLIQUE",(Hash)-1566607184, -1.0f, 0.167f, 0.159f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "DEVESTE",(Hash)1591739866,-1.5f, 1.066f, 0.13f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.15f },
		{ "DEVIANT",(Hash)1279262537, -1.0f, 0.111f, 0.123f,1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,  0.45f },
		{ "DOMINATOR4",(Hash)-688189648,-1.0f, 0.0f, 0.417f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  0.4f },
		{ "DOMINATOR5",(Hash)-1375060657,-1.0f, 0.0f, 0.417f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "DOMINATOR6",(Hash)-1293924613, -1.0f, 0.0f, 0.417f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,0.4f },
		{ "IMPALER",(Hash)-2096690334,-1.0f, 0.0f, 0.137f,1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.35f },
		{ "IMPALER2",(Hash)1009171724,-1.0f, 0.0f, 0.137f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.35f },
		{ "IMPALER3",(Hash)-1924800695,-1.0f, 0.0f, 0.137f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.35f },
		{ "IMPALER4",(Hash)-1744505657,-1.0f, 0.0f, 0.137f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.35f },
		{ "IMPERATOR",(Hash)444994115,-1.0f, 0.0f, 0.295f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "IMPERATOR2",(Hash)1637620610,-1.0f, 0.0f, 0.295f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "IMPERATOR3",(Hash)-755532233,-1.0f, 0.0f, 0.295f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "ISSI4",(Hash)628003514,-1.0f, 0.195f, 0.246f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "ISSI5", (Hash)1537277726,-1.0f, 0.195f, 0.246f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "ISSI6", (Hash)1239571361,  -1.0f, 0.195f, 0.246f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "ITALIGTO",(Hash)-331467772, -1.0f, -0.091f, 0.207f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.25f },
		{ "MONSTER3", (Hash)1721676810,-1.78f, 0.445f, 0.81f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.45f },
		{ "MONSTER4", (Hash)840387324,  -1.78f, 0.445f, 0.81f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.45f },
		{ "MONSTER5", (Hash)-715746948,-1.78f, 0.445f, 0.81f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.45f },
		{ "SCHLAGEN",(Hash)-507495760,-1.0f, -0.105f, 0.262f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "SLAMVAN4",(Hash)-2061049099,-1.0f, 0.152f, 0.537f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.5f },
		{ "SLAMVAN5", (Hash)373261600,-1.0f, 0.152f, 0.537f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.5f },
		{ "SLAMVAN6", (Hash)1742022738,-1.0f, 0.152f, 0.537f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.5f },
		{ "TOROS",(Hash)-1168952148,-1.0f, 0.415f, 0.394f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "TULIP",(Hash)1456744817,-1.0f, 0.171f, 0.223f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.35f },
		{ "VAMOS",(Hash)-49115651, -1.0f, 0.0f, 0.163f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.4f },
		{ "ZR380",(Hash)540101442,-1.0f, 0.0f, 0.286f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.45f },
		{ "ZR3802", (Hash)-1106120762,-1.0f, 0.0f, 0.286f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,0.45f },
		{ "ZR3803", (Hash)-1478704292,-1.0f, 0.0f, 0.286f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.45f },

		// 1.0.1868.0?
		{ "slamvan2",(Hash)833469436,-1.0f, 0.35f, 0.456f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.25f },
		{ "rebla",(Hash)83136452, 0.0f, 1.9002f, 1.0f, 0.f, 0.f, -1.f,-1.0f, 0.0f, 0.0f,0.3f },
		{ "asbo",(Hash)1118611807,-1.0f, 0.104f, 0.339f,1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.3f },
		{ "Sugoi",(Hash)987469656, -1.0f, 0.104f, 0.223f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.4f },
		{ "komoda",(Hash)3460613305, -1.0f, 0.104f, 0.155f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.4f },
		{ "vstr", (Hash)1456336509, -1.0f, 0.104f, 0.155f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.4f },
		{ "sultan2", (Hash)872704284, -1.0f, 0.313f, 0.16f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.35f },
		{ "kanjo", (Hash)409049982,-1.0f, 0.313f, 0.16f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.35f },
		{ "jb7002", (Hash)394110044, 0.0f, 1.2f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f,0.37f },
		{ "yosemite2", (Hash)1693751655, -1.0f, 0.252f, 0.201f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.3f },
		{ "retinue2", (Hash)2031587082,-1.0f, -0.018f, 0.253f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,0.3f },
		{ "furia", (Hash)960812448, -1.0f, 0.0965f, 0.149f, 1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.5f },
		{ "everon", (Hash)2538945576, 0.0f, 2.019f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f,0.5f },
		{ "imorgon", (Hash)3162245632,-1.5f, 0.42f, -0.2f, 1.0f, -0.0997f, 0.0415f, 0.0f, -1.0f, 0.0f,0.45f },
		{ "zhaba", (Hash)1284356689, -1.202f, 0.034f, 0.6635f, 1.0f, -0.002f, 0.f,0.0f, -0.7398f, 0.0f, 0.4f },


	}) {
		if (vehicleModel.hash == i.vehHash) {
			x = { i.x1, i.x2, i.x3 };
			y = { i.y1, i.y2, i.y3 };
			z = { i.z1, i.z2, i.z3 };
			scale = i.scale;
			return true;
			break;
		}
	}

	return false;
}
void add_emblem_to_vehicle(GTAvehicle vehicle, GTAentity playerPed)
{
	Vector3 x, y, z;
	float scale;
	const Model& model = vehicle.Model();
	if (get_vehicle_info_for_emblem_pos(model, x, y, z, scale))
	{
		int alpha = 200;
		if (model.hash == VEHICLE_WINDSOR)
			alpha = 255;
		vehicle.RequestControlOnce();
		ADD_VEHICLE_CREW_EMBLEM(vehicle.GetHandle(), playerPed.GetHandle(), vehicle.GetBoneIndex("chassis_dummy"),
			x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
	}
}

// Vehicle - clone
GTAvehicle clone_vehicle(GTAvehicle vehicle, GTAentity pedForEmblem)
{
	if (!vehicle.Exists())
		return GTAvehicle();

	Vector3 Pos = vehicle.Position_get();
	Vector3 Rot = vehicle.Rotation_get();

	Model vehicleModel = vehicle.Model();

	GTAvehicle newVeh = World::CreateVehicle(vehicleModel, Pos, Rot, false);
	WAIT(40);

	newVeh.PrimaryColour_set(vehicle.PrimaryColour_get());
	newVeh.SecondaryColour_set(vehicle.SecondaryColour_get());
	if (vehicle.IsPrimaryColorCustom())
	{
		newVeh.CustomPrimaryColour_set(vehicle.CustomPrimaryColour_get());
	}
	if (vehicle.IsSecondaryColorCustom())
	{
		newVeh.CustomSecondaryColour_set(vehicle.CustomSecondaryColour_get());
	}

	SET_VEHICLE_MOD_KIT(newVeh.Handle(), 0);

	newVeh.WheelType_set(vehicle.WheelType_get());

	for (int i = 0; i < vValues_ModSlotNames.size(); i++)
	{
		if (i >= 17 && i <= 22)
			newVeh.ToggleMod(i, vehicle.IsToggleModOn(i));
		else
			newVeh.SetMod(i, vehicle.GetMod(i), vehicle.GetModVariation(i));
	}

	newVeh.CanTyresBurst_set(vehicle.CanTyresBurst_get());
	newVeh.TyreSmokeColour_set(vehicle.TyreSmokeColour_get());
	newVeh.NumberPlateTextIndex_set(vehicle.NumberPlateTextIndex_get());
	newVeh.NumberPlateText_set(vehicle.NumberPlateText_get());
	newVeh.PearlescentColour_set(vehicle.PearlescentColour_get());
	newVeh.RimColour_set(vehicle.RimColour_get());

	if (newVeh.IsConvertible())
	{
		newVeh.RoofState_set(vehicle.RoofState_get());
	}

	for (VehicleNeonLight i : { VehicleNeonLight::Left, VehicleNeonLight::Right, VehicleNeonLight::Front, VehicleNeonLight::Back})
	{
		newVeh.SetNeonLightOn(i, vehicle.IsNeonLightOn(i));
	}

	for (int i = 0; i <= 60; i++)
	{
		if (newVeh.DoesExtraExist(i))
			newVeh.ExtraOn_set(i, vehicle.ExtraOn_get(i));
	}

	if (newVeh.LiveryCount() > 1 && newVeh.Livery_get() >= 0)
	{
		newVeh.Livery_set(vehicle.Livery_get());
	}

	newVeh.NeonLightsColour_set(vehicle.NeonLightsColour_get());

	newVeh.WindowTint_set(vehicle.WindowTint_get());

	newVeh.DirtLevel_set(vehicle.DirtLevel_get());

	newVeh.EngineRunning_set(true);

	if (DOES_VEHICLE_HAVE_CREW_EMBLEM(vehicle.Handle(), 0) && pedForEmblem.Exists())
	{
		add_emblem_to_vehicle(newVeh, pedForEmblem);
	}

	newVeh.InteriorColour_set(vehicle.InteriorColour_get());
	newVeh.DashboardColour_set(vehicle.DashboardColour_get());
	newVeh.HeadlightColour_set(vehicle.HeadlightColour_get());

	// Burst tyres
	for (int i = 0; i <= 8; i++)
	{
		if (vehicle.IsTyreBursted(i))
			newVeh.BurstTyre(i);
	}

	// Apply multipliers
	auto rpmMultIt = g_multList_rpm.find(vehicle.Handle());
	if (rpmMultIt != g_multList_rpm.end())
	{
		g_multList_rpm[newVeh.Handle()] = rpmMultIt->second;
		newVeh.EnginePowerMultiplier_set(rpmMultIt->second);
	}
	auto torqueMultIt = g_multList_torque.find(vehicle.Handle());
	if (torqueMultIt != g_multList_torque.end())
	{
		g_multList_torque[newVeh.Handle()] = torqueMultIt->second;
		newVeh.EngineTorqueMultiplier_set(torqueMultIt->second);
	}
	auto maxSpeedMultIt = g_multList_maxSpeed.find(vehicle.Handle());
	if (maxSpeedMultIt != g_multList_maxSpeed.end())
	{
		g_multList_maxSpeed[newVeh.Handle()] = maxSpeedMultIt->second;
		newVeh.MaxSpeed_set(maxSpeedMultIt->second);
	}
	auto headlightsMultIt = g_multList_headlights.find(vehicle.Handle());
	if (headlightsMultIt != g_multList_headlights.end())
	{
		g_multList_headlights[newVeh.Handle()] = headlightsMultIt->second;
		newVeh.LightsMultiplier_set(headlightsMultIt->second);
	}

	// Engine sound
	auto engineSoundIt = g_vehList_engSound.find(vehicle.Handle());
	if (engineSoundIt != g_vehList_engSound.end())
	{
		g_vehList_engSound[newVeh.Handle()] = engineSoundIt->second;
		newVeh.EngineSound_set(engineSoundIt->second);
	}

	vehicleModel.Unload();

	return newVeh;
}




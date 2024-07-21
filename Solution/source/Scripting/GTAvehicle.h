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
#pragma once

#include "GTAentity.h"

#include <vector>
#include <string>
#include <map>

typedef unsigned long DWORD, Hash;
typedef unsigned char BYTE, UINT8;
typedef int INT, Ped, Vehicle, Entity;
typedef char *PCHAR;
typedef const char *LPCSTR;

enum VehicleSeat : int;
enum class CargobobHook : int;
enum class VehicleLockStatus: int;
enum class VehicleRoofState : int;
enum class VehicleDoor : int;
enum class VehicleWindow : int;
enum class VehicleNeonLight : int;
enum class VehicleClass : int;
namespace GTAmodel {
	class Model;
}
class RgbS;

extern const std::vector<std::string> vValues_HornNames;
extern const std::vector<std::string> vValues_ModSlotNames;
std::string get_mod_slot_name(Vehicle vehicle, INT modType, bool gxt);
std::string get_mod_text_label(Vehicle vehicle, INT modType, INT modValue, bool gxt);


class GTAvehicle : public GTAentity
{
public:
	GTAvehicle();
	GTAvehicle(int handle);
	GTAvehicle(const GTAentity& obj);

	GTAvehicle& operator = (const GTAvehicle& value);
	friend bool operator == (const GTAvehicle& left, const GTAvehicle& right);

	void Delete(bool tele = false) override;

	int NetID() const override;

	bool IsDamaged() const;
	void Fix();
	void Repair(bool checkIfDamaged = true);

	void EngineSound_set(const std::string& vehName);

	void SetFrictionOverride(float value);

	bool HasRoof() const;

	int MaxPassengers() const;

	GTAentity GetPedOnSeat(VehicleSeat seat) const;
	bool IsSeatFree(VehicleSeat seat) const;
	GTAentity Driver_get() const;
	std::vector<GTAentity> Occupants_get(bool bIncludeDriver = true) const;
	VehicleSeat FirstFreeSeat(VehicleSeat defaultReturn) const;

	std::string NumberPlateText_get() const;
	void NumberPlateText_set(const std::string& value);
	int NumberPlateTextIndex_get() const;
	void NumberPlateTextIndex_set(int value);

	bool IsConvertible() const;

	bool Stolen_get() const;
	void Stolen_set(bool value);

	bool Driveable_get() const;
	void Driveable_set(bool value);

	bool IsStopped() const;
	bool IsStoppedAtTrafficLights() const;
	void StopImmediately();

	float MaxBraking_get() const;
	float MaxTraction_get() const;

	bool IsOnAllWheels() const;

	void Speed_set(float value);
	void SetForwardSpeed(float value);

	void MaxSpeed_set(float value);

	float DirtLevel_get() const;
	void DirtLevel_set(float value);
	float PaintFade_get() const;
	void PaintFade_set(float value);

	VehicleRoofState RoofState_get() const;
	void RoofState_set(VehicleRoofState value);

	float BodyHealth_get() const;
	void BodyHealth_set(float value);

	float EngineHealth_get() const;
	void EngineHealth_set(float value);

	float PetrolTankHealth_get() const;
	void PetrolTankHealth_set(float value);

	bool SirenActive_get() const;
	void SirenActive_set(bool value);

	bool LoudRadioActive_get() const;
	void LoudRadioActive_set(bool value);

	int PrimaryColour_get() const;
	void PrimaryColour_set(int value);

	int SecondaryColour_get() const;
	void SecondaryColour_set(int value);

	int RimColour_get() const;
	void RimColour_set(int value);

	int PearlescentColour_get() const;
	void PearlescentColour_set(int value);

	// For Benny's supported vehicles
	int InteriorColour_get() const;
	void InteriorColour_set(int value);
	int DashboardColour_get() const;
	void DashboardColour_set(int value);
	
	// b1604
	int HeadlightColour_get() const;
	void HeadlightColour_set(int value);

	int WheelType_get() const;
	void WheelType_set(int value);

	int WindowTint_get() const;
	void WindowTint_set(int value);
	;
	bool IsPrimaryColorCustom() const;
	bool IsSecondaryColorCustom() const;

	void Wanted_set(bool value);

	void HasGravity_set(bool value) override;

	bool EngineRunning_get() const;
	void EngineRunning_set(bool value);

	void EnginePowerMultiplier_set(float value);
	void EngineTorqueMultiplier_set(float value);

	void EngineCanDegrade_set(bool value);

	bool LightsOn_get() const;
	void LightsOn_set(bool value);

	bool HighBeamsOn_get() const;

	void LightsMultiplier_set(float value);

	bool LeftHeadLightBroken_get() const;
	void LeftHeadLightBroken_set(bool value);
	bool RightHeadLightBroken_get() const;
	void RightHeadLightBroken_set(bool value);

	bool IsFrontBumperBrokenOff_get() const;
	bool IsRearBumperBrokenOff_get() const;

	void BrakeLightsOn_set(bool value);

	void HandbrakeOn_set(bool value);

	void LeftIndicatorLightOn_set(bool value);
	void RightIndicatorLightOn_set(bool value);

	void InteriorLightOn_set(bool value);

	bool TaxiLightOn_get() const;
	void TaxiLightOn_set(bool value);

	bool SearchLightOn_get() const;
	void SearchLightOn_set(bool value);

	bool NeedsToBeHotwired_get() const;
	void NeedsToBeHotwired_set(bool value);

	bool CanTyresBurst_get() const;
	void CanTyresBurst_set(bool value);

	bool CanTyresDrift_get() const;
	void CanTyresDrift_set(bool value);

	void CanBeVisiblyDamaged_set(bool value);

	bool PreviouslyOwnedByPlayer_get() const;
	void PreviouslyOwnedByPlayer_set(bool value);

	RgbS CustomPrimaryColour_get() const;
	void CustomPrimaryColour_set(RgbS value);
	void CustomPrimaryColour_set(BYTE r, BYTE g, BYTE b);

	RgbS CustomSecondaryColour_get() const;
	void CustomSecondaryColour_set(RgbS value);
	void CustomSecondaryColour_set(BYTE r, BYTE g, BYTE b);

	RgbS NeonLightsColour_get() const;
	void NeonLightsColour_set(RgbS value);
	void NeonLightsColour_set(BYTE r, BYTE g, BYTE b);

	RgbS TyreSmokeColour_get() const;
	void TyreSmokeColour_set(RgbS value);
	void TyreSmokeColour_set(BYTE r, BYTE g, BYTE b);

	int Livery_get() const;
	void Livery_set(int liveryIndex);
	int LiveryCount() const;

	bool AlarmActive_get() const;
	void AlarmActive_set(bool value);

	int CurrentGear_get() const;
	int HighGear_get() const;
	void HighGear_set(UINT8 value);
	float FuelLevel_get() const;
	void FuelLevel_set(float value);
	float CurrentRPM_get() const;
	void CurrentRPM_set(float value);
	float Acceleration_get() const;
	float WheelSpeed_get() const;
	float SteeringAngle_get(bool inDegrees=true) const;
	float SteeringScale_get() const;
	void SteeringScale_set(float value);

	void FixDoor(VehicleDoor door);
	void FixAllDoors();

	void RadioStation_set(int value);

	VehicleClass ClassType_get();

	VehicleLockStatus LockStatus_get() const;
	void LockStatus_set(const VehicleLockStatus& value);

	int GetMod(int modType) const;
	void SetMod(int modType, int modIndex, int variation);
	int GetModVariation(int modType) const;
	void SetModVariation(int modType, bool variation);
	void ToggleMod(int modType, bool toggle);
	bool IsToggleModOn(int modType) const;
	void RemoveMod(int modType);

	std::string GetModSlotName(int modType, bool getProperName) const;
	std::string GetModName(int modType, int modIndex, bool getProperName) const;

	void ClearCustomPrimaryColour();
	void ClearCustomSecondaryColour();

	void Explode(bool audible = true, bool visible = true);

	bool PlaceOnGroundProperly();
	void PlaceOnNextStreet();

	std::vector<VehicleDoor> Doors_get() const;
	bool HasBombBay_get() const;
	bool HasForks_get() const;
	bool HasSiren_get() const;
	bool HasTowArm_get() const;

	void OpenDoor(VehicleDoor door, bool loose, bool instantly, bool playSound = true);
	void CloseDoor(VehicleDoor door, bool instantly, bool playSound = true);
	void CloseAllDoors(bool instantly);
	void BreakDoor(VehicleDoor door, bool instant);
	void BreakAllDoors(bool instant);
	float GetDoorAngleRatio(VehicleDoor door) const;
	bool IsDoorOpen(VehicleDoor door) const;
	bool IsDoorFullyOpen(VehicleDoor door) const;
	bool IsDoorBroken(VehicleDoor door) const;
	void SetDoorBreakable(VehicleDoor door, bool isBreakable);

	void OpenBombBay();
	void CloseBombBay();

	bool IsWindowIntact(VehicleWindow window);
	void FixWindow(VehicleWindow window);
	void SmashWindow(VehicleWindow window);
	void RollUpWindow(VehicleWindow window);
	void RollDownWindow(VehicleWindow window);
	void RollDownWindows();
	void RemoveWindow(VehicleWindow window);

	bool IsNeonLightOn(VehicleNeonLight light) const;
	void SetNeonLightOn(VehicleNeonLight light, bool on);

	bool DoesExtraExist(int extraId) const;
	bool ExtraOn_get(int extraId) const;
	void ExtraOn_set(int extraId, bool value);

	void SoundHorn(int duration);

	void SetHeliYawPitchRollMult(float value);

	void DropCargobobHook(CargobobHook hookType);
	bool IsCargobobHookActive() const;
	bool IsCargobobHookActive(CargobobHook hookType) const;
	void RetractCargobobHook();
	void CargoBobMagnetGrabVehicle();
	void CargoBobMagnetReleaseVehicle();
	
	bool IsBoatAnchored();
	bool CanBoatAnchorHere();
	void AnchorBoat(bool anchored);

	bool IsTyreBursted(int wheel, bool completely = false) const;
	void BurstTyre(int wheel);
	void FixTyre(int wheel);
	bool IsInBurnout() const;
	void ForceBurnout_set(bool value);

	void StartAlarm();

	void ApplyDamage(Vector3 loc, float damageAmount, float radius);

	GTAentity CreatePedOnSeat(VehicleSeat seat, GTAmodel::Model model);
	GTAentity CreateRandomPedOnSeat(VehicleSeat seat);

};



// Vehicle - Emblem
//inline bool get_vehicle_info_for_emblem_pos(Model vehicleModel, Vector3& x, Vector3& y, Vector3& z, float& scale);
void add_emblem_to_vehicle(GTAvehicle vehicle, GTAentity playerPed);

// Vehicle - clone
GTAvehicle clone_vehicle(GTAvehicle vehicle, GTAentity pedForEmblem = GTAentity());




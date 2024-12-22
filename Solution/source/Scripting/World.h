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

#include <vector>
#include <string>

typedef unsigned long DWORD, Hash;
typedef unsigned __int8 UINT8, BYTE;
typedef int Entity;

enum class EntityType : UINT8;
enum class WeatherType : int;
enum class RopeType : int;
enum class CheckpointIcon : int;
enum VehicleSeat : int;
namespace EXPLOSION {
	enum EXPLOSION : UINT8;
}
class RGBA;
class RgbS;
class Vector3;
class Vector2;
class Camera;
class GTAblip;
class Checkpoint;
namespace GTAmodel {
	class Model;
}
class GTAentity;
class GTAped;
class GTAvehicle;
class GTAprop;
class Rope;
namespace PedRelationship {
	enum PedRelationship : int;
}

extern std::vector<Entity> _nearbyPeds, _nearbyVehicles, _worldPeds, _worldVehicles, _worldObjects, _worldEntities;

namespace World
{
	extern const std::vector<std::pair<std::string, std::string>> sWeatherNames;
	
	void GravityLevel_set(int value);

	Camera RenderingCamera_get();
	void RenderingCamera_set(Camera newCamera, bool ease = false);

	void Weather_set(WeatherType weather);
	void Weather_set(const std::string& weatherName);
	void SetWeatherOverTime(WeatherType weather, DWORD ms);
	void SetWeatherOverTime(const std::string& weatherName, DWORD ms);
	void SetWeatherOverride(WeatherType weather);
	void SetWeatherOverride(const std::string& weatherName);
	void ClearWeatherOverride();
	void SetWeatherTransition(WeatherType from, WeatherType to, DWORD ms);
	void GetWeatherTransition(WeatherType& from, WeatherType& to, DWORD& time);
	WeatherType Weather_get();
	WeatherType Weather_get(const std::string& weatherName);
	std::string WeatherName_get();
	std::string WeatherName_get(const WeatherType& weatherType);

	void GetActiveCheckpoints(std::vector<Checkpoint>& result);


	void GetNearbyPeds(std::vector<GTAped>& result, GTAped ped, float radius);
	void GetNearbyPeds(std::vector<GTAped>& result, GTAped ped, float radius, int maxAmount);
	void GetNearbyPeds(std::vector<GTAped>& result, const Vector3& position, float radius);

	void GetNearbyVehicles(std::vector<GTAvehicle>& result, GTAped ped, float radius);
	void GetNearbyVehicles(std::vector<GTAvehicle>& result, GTAped ped, float radius, int maxAmount);
	void GetNearbyVehicles(std::vector<GTAvehicle>& result, const Vector3& position, float radius);

	void GetNearbyProps(std::vector<GTAprop>& result, GTAped ped, float radius);
	void GetNearbyProps(std::vector<GTAprop>& result, const Vector3& position, float radius);

	GTAprop GetClosestPropOfType(const Vector3& position, float radius, const GTAmodel::Model& model, bool isMissionEntity = false);
	GTAped GetClosestPed(const Vector3& position, float radius);
	GTAvehicle GetClosestVehicle(const Vector3& position, float radius);

	float GetDistance(const Vector3& origin, const Vector3& destination);

	float GetGroundHeight(const Vector2& position);
	float GetGroundHeight(const Vector3& position);
	Vector3 GetNextPositionOnStreet(const Vector3& position);

	std::string GetZoneName(const Vector3& position, bool properName);
	std::string GetStreetName(const Vector3& position);

	void GetActiveBlips(std::vector<GTAblip>& result);
	GTAblip CreateBlip(Vector3 position);
	GTAblip CreateBlip(Vector3 position, float radius);

	Camera CreateCamera();
	Camera CreateCamera(const Vector3& position, const Vector3& rotation, float fov);
	void DestroyAllCameras();

	GTAped CreatePed(GTAmodel::Model model, Vector3 position, float heading, bool placeOnGround);
	GTAped CreatePed(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool placeOnGround);
	GTAped CreateRandomPed(const Vector3& position);
	GTAped CreatePedInsideVehicle(const GTAmodel::Model& model, const GTAvehicle& vehicle, const VehicleSeat& seat);

	GTAvehicle CreateVehicle(GTAmodel::Model model, Vector3 position, float heading, bool placeOnGround);
	GTAvehicle CreateVehicle(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool placeOnGround);

	GTAprop CreateProp(GTAmodel::Model model, Vector3 position, bool dynamic, bool placeOnGround);
	GTAprop CreateProp(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool dynamic, bool placeOnGround);

	void ShootBullet(const Vector3& sourcePosition, const Vector3& targetPosition, GTAentity owner, Hash weaponHash, int damage, float speed, bool audible, bool visible);
	void AddExplosion(const Vector3& position, EXPLOSION::EXPLOSION type, float radius, float cameraShake, bool audible = true, bool visible = true);
	void AddOwnedExplosion(GTAentity owner, const Vector3& position, EXPLOSION::EXPLOSION type, float radius, float cameraShake, bool audible = true, bool visible = true);
	
	Checkpoint CreateCheckpoint(const CheckpointIcon& icon, const Vector3& position, const Vector3& pointTo, float radius, const RGBA& colour, BYTE reserved = 0);

	inline Rope AddRope(RopeType type, const Vector3& position, Vector3 rotation, float length, float minLength, bool breakable);
	
	void SetBlackout(bool enable);

	Hash AddRelationshipGroup(const std::string& groupName);
	void RemoveRelationshipGroup(Hash groupHash);
	void RemoveRelationshipGroup(const std::string& group);
	int GetRelationshipBetweenGroups(Hash group1, Hash group2);
	int GetRelationshipBetweenGroups(const std::string& group1, const std::string& group2);
	void SetRelationshipBetweenGroups(int relationship, Hash group1, Hash group2);
	void SetRelationshipBetweenGroups(int relationship, const std::string& group1, const std::string& group2);
	void ClearRelationshipBetweenGroups(int relationship, Hash group1, Hash group2);
	void ClearRelationshipBetweenGroups(int relationship, const std::string& group1, const std::string& group2);

	bool WorldToScreen(const Vector3& worldCoords, Vector2& screenCoords);

	//RaycastResult Raycast(Vector3 source, Vector3 target, IntersectOptions options);
	//RaycastResult Raycast(Vector3 source, Vector3 target, IntersectOptions options, GTAentity entity);
	GTAentity EntityFromAimCamRay();

	void DrawMarker(int type, const Vector3& pos, const Vector3& dir, const Vector3& rot, const Vector3& scale, const RGBA& colour);
	void DrawMarker(int type, const Vector3& pos, const Vector3& dir, const Vector3& rot, const Vector3& scale, const RGBA& colour, 
		bool bobUpAndDown, bool faceCamY, int unk2, bool rotateY, const std::string& textureDict, const std::string& textureName, bool drawOnEnt);

	void DrawLine(const Vector3& startPos, const Vector3& endPos, const RGBA& colour);
	void DrawPoly(const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const RGBA& colour);
	void DrawLightWithRange(const Vector3& position, const RgbS& colour, float range, float intensity);
	void DrawSpotLight(const Vector3& pos, const Vector3& dir, const RgbS& colour, float distance, float brightness, float roundness, float radius, float fadeout);
	void DrawSpotLightWithShadow(const Vector3& pos, const Vector3& dir, const RgbS& colour, float distance, float brightness, float roundness, float radius, float fadeout, float shadowUnk);


	// World - Relationships - nearby
	void KillNearbyPeds(GTAped originPed, float range, PedRelationship::PedRelationship relationshipWithOriginPed);
	void KillMyEnemies();

}


// World - clear area
void clear_area_of_entities(const EntityType& type, const Vector3& coords, float radius, const std::vector<GTAentity>& excludes);
void clear_area_of_vehicles_around_entity(Entity entity, float radius, bool memry = true);
void clear_area_of_peds_around_entity(Entity entity, float radius, bool memry = true);
void clear_attachments_off_entity(const GTAentity& entity, const EntityType& entType);




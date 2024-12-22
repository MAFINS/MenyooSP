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
#include "World.h"

#include "..\macros.h"

#include "..\Natives\types.h" // RGBA/RgbS
#include "..\Scripting\enums.h"
#include "..\Natives\natives2.h"
#include "..\Memory\GTAmemory.h"
#include "GTAblip.h"
#include "Checkpoint.h"
#include "Camera.h"
#include "GameplayCamera.h"
#include "Model.h"
#include "GTAentity.h"
#include "GTAvehicle.h"
#include "GTAped.h"
#include "GTAprop.h"
#include "GTAplayer.h"
#include "Raycast.h"
#include "Rope.h"

#include "..\Menu\Routine.h"

#include "..\Submenus\Spooner\EntityManagement.h"

#include <string>
#include <vector>

std::vector<Entity> _nearbyPeds, _nearbyVehicles, _worldPeds, _worldVehicles, _worldObjects, _worldEntities;

namespace World
{
	//const std::vector<std::string> World::sWeatherNames{ "ExtraSunny", "Clear", "Clouds", "Smog", "Foggy", "Overcast", "Rain", "Thunder", "Clearing", "Neutral", "Snow", "Blizzard", "SnowLight", "Christmas", "Halloween", "Halloween Snow", "Halloween Rain"};
	const std::vector<std::pair<std::string, std::string>> World::sWeatherNames{
	{"ExtraSunny", "ExtraSunny"},
	{"Clear", "Clear"},
	{"Clouds", "Clouds"},
	{"Smog", "Smog"},
	{"Foggy", "Foggy"},
	{"Overcast", "Overcast"},
	{"Rain", "Rain"},
	{"Thunder", "Thunder"},
	{"Clearing", "Clearing"},
	{"Neutral", "Neutral"},
	{"Snow", "Snow"},
	{"Blizzard", "Blizzard"},
	{"SnowLight", "SnowLight"},
	//{"Christmas", "XMAS"},          // Still not working for some reason
	{"Halloween", "Halloween"},
	{"Halloween Snow", "SNOW_HALLOWEEN"},  // Different internal name
	{"Halloween Rain", "RAIN_HALLOWEEN"}   // Different internal name
	};

	void GravityLevel_set(int value)
	{
		SET_GRAVITY_LEVEL(value);
	}

	Camera RenderingCamera_get()
	{
		if (IS_GAMEPLAY_CAM_RENDERING()) return 0;
		return GET_RENDERING_CAM();
	}
	void RenderingCamera_set(Camera newCamera, bool ease)
	{
		if (newCamera.Handle() == 0)
		{
			RENDER_SCRIPT_CAMS(false, ease, 3000, 1, 0, 0);
		}
		else
		{
			newCamera.SetActive(true);
			RENDER_SCRIPT_CAMS(true, ease, 3000, 1, 0, 0);
		}
	}

	void Weather_set(WeatherType weather)
	{
		CLEAR_OVERRIDE_WEATHER();
		SET_WEATHER_TYPE_NOW((PCHAR)sWeatherNames[static_cast<int>(weather)].second.c_str());
	}
	void Weather_set(const std::string& weatherName)
	{
		CLEAR_OVERRIDE_WEATHER();
		SET_WEATHER_TYPE_NOW(weatherName.c_str());
	}
	void SetWeatherOverTime(WeatherType weather, DWORD ms)
	{
		SET_WEATHER_TYPE_OVERTIME_PERSIST((PCHAR)sWeatherNames[static_cast<int>(weather)].second.c_str(), float(ms) / 1000.0f);
	}
	void SetWeatherOverTime(const std::string& weatherName, DWORD ms)
	{
		SET_WEATHER_TYPE_OVERTIME_PERSIST(weatherName.c_str(), float(ms) / 1000.0f);
	}
	void SetWeatherOverride(WeatherType weather)
	{
		SET_OVERRIDE_WEATHER(sWeatherNames[static_cast<int>(weather)].second.c_str());
		//SET_WEATHER_TYPE_NOW(sWeatherNames[static_cast<int>(weather)].c_str());
	}
	void SetWeatherOverride(const std::string& weatherName)
	{
		SET_OVERRIDE_WEATHER(weatherName.c_str());
		//SET_WEATHER_TYPE_NOW(weatherName);
	}
	void ClearWeatherOverride()
	{
		CLEAR_OVERRIDE_WEATHER();
	}
	void SetWeatherTransition(WeatherType from, WeatherType to, DWORD ms)
	{
		SET_CURR_WEATHER_STATE(GET_HASH_KEY(sWeatherNames[static_cast<int>(from)].second), GET_HASH_KEY(sWeatherNames[static_cast<int>(to)].second), float(ms) / 1000.0f);
	}
	void GetWeatherTransition(WeatherType& from, WeatherType& to, DWORD& time)
	{
		Hash fr, t;
		float ti;
		GET_CURR_WEATHER_STATE(&fr, &t, &ti);

		time = (ti * 1000);

		for (UINT8 i = 0; i < sWeatherNames.size(); i++)
		{
			if (fr == GET_HASH_KEY(sWeatherNames[i].second))
			{
				from = (WeatherType)i;
			}
			if (t == GET_HASH_KEY(sWeatherNames[i].second))
			{
				to = (WeatherType)i;
			}
		}
	}
	WeatherType Weather_get()
	{
		Hash currentWeatherHash = GET_PREV_WEATHER_TYPE_HASH_NAME();
		for (int i = 0; i < sWeatherNames.size(); i++)
		{
			if (currentWeatherHash == GET_HASH_KEY(sWeatherNames[i].second))
			{
				return static_cast<WeatherType>(i);
			}
		}
		return WeatherType::Unknown;
	}
	WeatherType Weather_get(const std::string& weatherName)
	{
		for (int i = 0; i < sWeatherNames.size(); i++)
		{
			if (weatherName.compare(sWeatherNames[i].second) == 0)
			{
				return static_cast<WeatherType>(i);
			}
		}
		return WeatherType::Unknown;
	}
	std::string WeatherName_get()
	{
		Hash currentWeatherHash = GET_PREV_WEATHER_TYPE_HASH_NAME();
		for (auto& weatherName : sWeatherNames)
		{
			if (currentWeatherHash == GET_HASH_KEY(weatherName.second))
			{
				return weatherName.first;
			}
		}
		return std::string();
	}
	std::string WeatherName_get(const WeatherType& weatherType)
	{
		auto weatherTypeInt = static_cast<int>(weatherType);
		if (weatherTypeInt >= 0 && weatherTypeInt < sWeatherNames.size())
			return sWeatherNames[weatherTypeInt].first;
		else return std::string();
	}

	void GetActiveCheckpoints(std::vector<Checkpoint>& result)
	{
		UINT64 addr = GTAmemory::CheckpointBaseAddr();
		UINT8 count = 0;
		for (UINT64 i = *(UINT64*)(addr + 48); i && count < 64; i = *(UINT64*)(i + 24))
		{
			result.push_back(*(int*)(i + 12));
		}
	}


	void GetNearbyPeds(std::vector<GTAped>& result, GTAped ped, float radius)
	{
		return GetNearbyPeds(result, ped, radius, 10000);
	}
	void GetNearbyPeds(std::vector<GTAped>& result, GTAped ped, float radius, int maxAmount)
	{
		const Vector3 position = ped.Position_get();
		int *handles = new int[maxAmount * 2 + 2];

		handles[0] = maxAmount;

		const int amount = GET_PED_NEARBY_PEDS(ped.Handle(), (Any*)handles, -1);

		int index;
		int* currped;

		for (int i = 0; i < amount; ++i)
		{
			index = i * 2 + 2;

			if (handles[index] != 0 && DOES_ENTITY_EXIST(handles[index]))
			{
				currped = &handles[index];

				if (Vector3::Subtract(position, GET_ENTITY_COORDS(*currped, 1)).LengthSquared() < radius * radius)
				{
					result.push_back(*currped);
				}
			}
		}

		delete[] handles;
	}
	void GetNearbyPeds(std::vector<GTAped>& result, const Vector3& position, float radius)
	{
		//std::vector<Entity> handles;
		//GTAmemory::GetPedHandles(handles);
		auto& handles = _worldPeds;

		for (auto& currped : handles)
		{
			if (position.DistanceTo(GET_ENTITY_COORDS(currped, 1)) <= radius)
				result.push_back(currped);
		}
	}

	void GetNearbyVehicles(std::vector<GTAvehicle>& result, GTAped ped, float radius)
	{
		return GetNearbyVehicles(result, ped, radius, 10000);
	}
	void GetNearbyVehicles(std::vector<GTAvehicle>& result, GTAped ped, float radius, int maxAmount)
	{
		const Vector3 position = ped.Position_get();
		int *handles = new int[maxAmount * 2 + 2];

		handles[0] = maxAmount;

		const int amount = GET_PED_NEARBY_VEHICLES(ped.Handle(), (Any*)handles);

		int index;
		GTAvehicle currveh;

		for (int i = 0; i < amount; ++i)
		{
			index = i * 2 + 2;

			if (handles[index] != 0 && DOES_ENTITY_EXIST(handles[index]))
			{
				currveh.Handle() = handles[index];

				if (Vector3::Subtract(position, currveh.Position_get()).LengthSquared() < radius * radius)
				{
					result.push_back(currveh);
				}
			}
		}

		delete[] handles;
	}
	void GetNearbyVehicles(std::vector<GTAvehicle>& result, const Vector3& position, float radius)
	{
		//std::vector<Entity> handles;
		//GTAmemory::GetVehicleHandles(handles);
		auto& handles = _worldVehicles;

		for (auto& currveh : handles)
		{
			if (position.DistanceTo(GET_ENTITY_COORDS(currveh, 1)) <= radius)
				result.push_back(currveh);
		}
	}

	void GetNearbyProps(std::vector<GTAprop>& result, GTAped ped, float radius)
	{
		GetNearbyProps(result, ped.Position_get(), radius);
	}
	void GetNearbyProps(std::vector<GTAprop>& result, const Vector3& position, float radius)
	{
		//std::vector<Entity> handles;
		//GTAmemory::GetPropHandles(handles);
		auto& handles = _worldObjects;

		for (auto& currprop : handles)
		{
			if (position.DistanceTo(GET_ENTITY_COORDS(currprop, 1)) <= radius)
				result.push_back(currprop);
		}
	}

	GTAprop GetClosestPropOfType(const Vector3& position, float radius, const GTAmodel::Model& model, bool isMissionEntity)
	{
		return GET_CLOSEST_OBJECT_OF_TYPE(position.x, position.y, position.z, radius, model.hash, isMissionEntity, false, true);
	}
	GTAped GetClosestPed(const Vector3& position, float radius)
	{
		int handle = 0;

		GET_CLOSEST_PED(position.x, position.y, position.z, radius, true, true, &handle, false, false, -1);

		return handle;
	}
	GTAvehicle GetClosestVehicle(const Vector3& position, float radius)
	{
		return GET_CLOSEST_VEHICLE(position.x, position.y, position.z, radius, 0, 70);
	}

	float GetDistance(const Vector3& origin, const Vector3& destination)
	{
		return GET_DISTANCE_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1);
	}

	float GetGroundHeight(const Vector2& position)
	{
		float height = 0.0f;
		GET_GROUND_Z_FOR_3D_COORD(position.x, position.y, 1000.0f, &height, 0, 0);

		return height;
	}
	float GetGroundHeight(const Vector3& position)
	{
		float height = 0.0f;
		GET_GROUND_Z_FOR_3D_COORD(position.x, position.y, 1000.0f, &height, 0, 0);

		return height;
	}
	Vector3 GetNextPositionOnStreet(const Vector3& position)
	{
		Vector3_t outPos;

		for (int i = 1; i < 40; i++)
		{
			GET_NTH_CLOSEST_VEHICLE_NODE(position.x, position.y, position.z, i, &outPos, 1, 0x40400000, 0);

			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(outPos.x, outPos.y, outPos.z, 2.0f, 2.0f, 2.0f, 0))
			{
				return outPos;
			}
		}
		return Vector3();
	}

	std::string GetZoneName(const Vector3& position, bool properName)
	{
		const char* name = GET_NAME_OF_ZONE(position.x, position.y, position.z);
		return properName ? (GET_FILENAME_FOR_AUDIO_CONVERSATION(name)) : name;
	}
	std::string GetStreetName(const Vector3& position)
	{
		Hash streetName, crossingRoad;
		GET_STREET_NAME_AT_COORD(position.x, position.y, position.z, &streetName, &crossingRoad);
		return GET_STREET_NAME_FROM_HASH_KEY(streetName);
	}

	void GetActiveBlips(std::vector<GTAblip>& result)
	{
		/*BlipList* blipList = MemoryPatch::GetBlipList();
		for (UINT16 i = 0; i <= 1000; i++)
		{
		Blipx* blip = blipList->m_Blips[i];
		if (blip) result.push_back(GTAblip(blip->iID));
		}*/
		for (int i = 0; i <= 521; i++)
		{
			GTAblip blip = GET_FIRST_BLIP_INFO_ID(i);
			while (blip.Exists())
			{
				result.push_back(blip);
				blip = GET_NEXT_BLIP_INFO_ID(i);
			}
		}
	}
	GTAblip CreateBlip(Vector3 position)
	{
		return ADD_BLIP_FOR_COORD(position.x, position.y, position.z);
	}
	GTAblip CreateBlip(Vector3 position, float radius)
	{
		return ADD_BLIP_FOR_RADIUS(position.x, position.y, position.z, radius);
	}

	Camera CreateCamera()
	{
		return CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
	}
	Camera CreateCamera(const Vector3& position, const Vector3& rotation, float fov)
	{
		//Camera cam =  CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, fov, 1, 2);
		//cam.SetActive(false);
		//return cam;

		Camera cam = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
		cam.Position_set(position);
		cam.Rotation_set(rotation);
		cam.FieldOfView_set(fov);
		return cam;
	}
	void DestroyAllCameras()
	{
		Camera::DestroyAllCameras();
	}

	GTAped CreatePed(GTAmodel::Model model, Vector3 position, float heading, bool placeOnGround)
	{
		if (!model.IsInCdImage()) return 0;

		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}

		model.Load(3000);

		GTAentity ped = CREATE_PED(26, model.hash, position.x, position.y, position.z, heading, 1, 1);
		if (placeOnGround) ped.PlaceOnGround();
		return ped;
	}
	GTAped CreatePed(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool placeOnGround)
	{
		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}
		auto ped = CreatePed(model, position, rotation.z, false);
		ped.Position_set(position); // More accurate position
		if (placeOnGround) ped.PlaceOnGround();
		ped.Rotation_set((rotation)); // Rotation
		return ped;
	}
	GTAped CreateRandomPed(const Vector3& position)
	{
		return CREATE_RANDOM_PED(position.x, position.y, position.z);
	}
	GTAped CreatePedInsideVehicle(const GTAmodel::Model& model, const GTAvehicle& vehicle, const VehicleSeat& seat)
	{
		if (!model.IsInCdImage()) return 0;

		model.Load(3000);

		return CREATE_PED_INSIDE_VEHICLE(vehicle.GetHandle(), PedType::Human, model.hash, static_cast<int>(seat), TRUE, TRUE);
	}

	GTAvehicle CreateVehicle(GTAmodel::Model model, Vector3 position, float heading, bool placeOnGround)
	{
		if (!model.IsVehicle() || !model.IsInCdImage())
		{
			return 0;
		}

		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}

		model.Load(3000);

		GTAentity vehicle = CREATE_VEHICLE(model.hash, position.x, position.y, position.z, heading, 1, 1, 0);
		if (placeOnGround) vehicle.PlaceOnGround();
		return vehicle;
	}
	GTAvehicle CreateVehicle(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool placeOnGround)
	{
		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}
		auto vehicle = CreateVehicle(model, position, rotation.z, false);
		vehicle.Position_set(position); // More accurate position
		if (placeOnGround) vehicle.PlaceOnGround();
		vehicle.Rotation_set(rotation); // Rotation
		return vehicle;
	}

	GTAprop CreateProp(GTAmodel::Model model, Vector3 position, bool dynamic, bool placeOnGround)
	{
		if (!model.IsInCdImage()) return 0;

		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}

		model.Load(3000);

		GTAentity prop = CREATE_OBJECT(model.hash, position.x, position.y, position.z, 1, 1, dynamic);
		if (placeOnGround) prop.PlaceOnGround();
		return prop;
	}
	GTAprop CreateProp(GTAmodel::Model model, Vector3 position, const Vector3& rotation, bool dynamic, bool placeOnGround)
	{
		if (placeOnGround)
		{
			position.z = World::GetGroundHeight(position) + model.Dim1().z;//model.Dim2().z;
		}
		GTAprop prop = CreateProp(model, position, dynamic, false);
		prop.Position_set(position); // More accurate position
		if (placeOnGround) prop.PlaceOnGround();
		prop.Rotation_set(rotation); // Rotation

		return prop;
	}

	void ShootBullet(const Vector3& sourcePosition, const Vector3& targetPosition, GTAentity owner, Hash weaponHash, int damage, float speed, bool audible, bool visible)
	{
		SHOOT_SINGLE_BULLET_BETWEEN_COORDS(sourcePosition.x, sourcePosition.y, sourcePosition.z, targetPosition.x, targetPosition.y, targetPosition.z, damage, 1, weaponHash, owner.Handle(), audible, !visible, speed);
	}
	void AddExplosion(const Vector3& position, EXPLOSION::EXPLOSION type, float radius, float cameraShake, bool audible, bool visible)
	{
		ADD_EXPLOSION(position.x, position.y, position.z, static_cast<int>(type), radius, audible, !visible, cameraShake, 0);
	}
	void AddOwnedExplosion(GTAentity owner, const Vector3& position, EXPLOSION::EXPLOSION type, float radius, float cameraShake, bool audible, bool visible)
	{
		ADD_OWNED_EXPLOSION(owner.Handle(), position.x, position.y, position.z, static_cast<int>(type), radius, audible, !visible, cameraShake);
	}

	Checkpoint CreateCheckpoint(const CheckpointIcon& icon, const Vector3& position, const Vector3& pointTo, float radius, const RGBA& colour, BYTE reserved)
	{
		return CREATE_CHECKPOINT(static_cast<int>(icon), position.x, position.y, position.z, pointTo.x, pointTo.y, pointTo.z, radius, colour.R, colour.G, colour.B, colour.A, reserved);
	}

	Rope AddRope(RopeType type, const Vector3& position, Vector3 rotation, float length, float minLength, bool breakable)
	{
		return Rope::AddRope(type, position, rotation, length, minLength, breakable);
	}

	void SetBlackout(bool enable)
	{
		SET_ARTIFICIAL_LIGHTS_STATE(enable);
	}

	Hash AddRelationshipGroup(const std::string& groupName)
	{
		Hash hash = 0;
		ADD_RELATIONSHIP_GROUP((PCHAR)groupName.c_str(), &hash);

		return hash;
	}
	void RemoveRelationshipGroup(Hash groupHash)
	{
		REMOVE_RELATIONSHIP_GROUP(groupHash);
	}
	void RemoveRelationshipGroup(const std::string& group)
	{
		REMOVE_RELATIONSHIP_GROUP(GET_HASH_KEY(group));
	}
	int GetRelationshipBetweenGroups(Hash group1, Hash group2)
	{
		return (GET_RELATIONSHIP_BETWEEN_GROUPS(group1, group2));
	}
	int GetRelationshipBetweenGroups(const std::string& group1, const std::string& group2)
	{
		Hash group1h = GET_HASH_KEY(group1);
		Hash group2h = GET_HASH_KEY(group2);

		return (GET_RELATIONSHIP_BETWEEN_GROUPS(group1h, group2h));
	}
	void SetRelationshipBetweenGroups(int relationship, Hash group1, Hash group2)
	{
		SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1, group2);
		SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, group2, group1);
	}
	void SetRelationshipBetweenGroups(int relationship, const std::string& group1, const std::string& group2)
	{
		Hash group1h = GET_HASH_KEY(group1);
		Hash group2h = GET_HASH_KEY(group2);

		SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1h, group2h);
		SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, group2h, group1h);
	}
	void ClearRelationshipBetweenGroups(int relationship, Hash group1, Hash group2)
	{
		CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1, group2);
		CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, group2, group1);
	}
	void ClearRelationshipBetweenGroups(int relationship, const std::string& group1, const std::string& group2)
	{
		Hash group1h = GET_HASH_KEY(group1);
		Hash group2h = GET_HASH_KEY(group2);

		CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1h, group2h);
		CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, group2h, group1h);
	}

	bool WorldToScreen(const Vector3& worldCoords, Vector2& screenCoords)
	{
		return (GET_SCREEN_COORD_FROM_WORLD_COORD(worldCoords.x, worldCoords.y, worldCoords.z, &screenCoords.x, &screenCoords.y)) != 0;
	}

	/*RaycastResult Raycast(Vector3 source, Vector3 target, IntersectOptions options)
	{
	return RaycastResult::Raycast(source, target, options);
	}
	RaycastResult Raycast(Vector3 source, Vector3 target, IntersectOptions options, GTAentity entity)
	{
	return RaycastResult::Raycast(source, target, options, entity);
	}*/
	GTAentity EntityFromAimCamRay()
	{
		GTAplayer myPlayer = PLAYER_ID();
		GTAentity myPed = PLAYER_PED_ID();
		//GTAentity myWeapEnt = GET_CURRENT_PED_WEAPON_ENTITY_INDEX(myPed.Handle());

		GTAentity aimedEntity = myPlayer.AimedEntity();
		if (aimedEntity.Handle())
			return aimedEntity;

		const Vector3& camCoord = GameplayCamera::Position_get();
		const Vector3& hitCoord = (GameplayCamera::DirectionFromScreenCentre_get() * 1000.0f) + camCoord;

		const RaycastResult& ray = RaycastResult::Raycast(camCoord, hitCoord, IntersectOptions::Everything, myPed);

		return ray.DidHitEntity() ? ray.HitEntity() : 0;
	}

	void DrawMarker(int type, const Vector3& pos, const Vector3& dir, const Vector3& rot, const Vector3& scale, const RGBA& colour)
	{
		DrawMarker(type, pos, dir, rot, scale, colour, false, false, 2, false, std::string(), std::string(), false);
	}
	void DrawMarker(int type, const Vector3& pos, const Vector3& dir, const Vector3& rot, const Vector3& scale, const RGBA& colour,
		bool bobUpAndDown, bool faceCamY, int unk2, bool rotateY, const std::string& textureDict, const std::string& textureName, bool drawOnEnt)
	{
		PCHAR dict = 0;
		PCHAR name = 0;
		if (textureDict.length() > 0 && textureName.length() > 0)
		{
			dict = (PCHAR)textureDict.c_str();
			name = (PCHAR)textureName.c_str();
		}
		DRAW_MARKER(type, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, rot.x, rot.y, rot.z, scale.x, scale.y, scale.z, colour.R, colour.G, colour.B, colour.A, bobUpAndDown, faceCamY, unk2, rotateY, dict, name, drawOnEnt);
	}

	void DrawLine(const Vector3& startPos, const Vector3& endPos, const RGBA& colour)
	{
		DRAW_LINE(startPos.x, startPos.y, startPos.z, endPos.x, endPos.y, endPos.z, colour.R, colour.G, colour.B, colour.A);
	}
	void DrawPoly(const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const RGBA& colour)
	{
		DRAW_POLY(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, pos3.x, pos3.y, pos3.z, colour.R, colour.G, colour.B, colour.A);
	}
	void DrawLightWithRange(const Vector3& position, const RgbS& colour, float range, float intensity)
	{
		DRAW_LIGHT_WITH_RANGE(position.x, position.y, position.z, colour.R, colour.G, colour.B, range, intensity);
	}
	void DrawSpotLight(const Vector3& pos, const Vector3& dir, const RgbS& colour, float distance, float brightness, float roundness, float radius, float fadeout)
	{
		DRAW_SPOT_LIGHT(pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, colour.R, colour.G, colour.B, distance, brightness, roundness, radius, fadeout);
	}
	void DrawSpotLightWithShadow(const Vector3& pos, const Vector3& dir, const RgbS& colour, float distance, float brightness, float roundness, float radius, float fadeout, float shadowUnk)
	{
		DRAW_SHADOWED_SPOT_LIGHT(pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, colour.R, colour.G, colour.B, distance, brightness, roundness, radius, fadeout, shadowUnk);
	}


	// World - Relationships - nearby
	void KillNearbyPeds(GTAped originPed, float range, PedRelationship::PedRelationship relationshipWithOriginPed)
	{
		if (!originPed.Exists())
			return;

		INT i, j;
		GTAped ped;

		const Vector3& originCoord = originPed.Position_get();

		Ped *peds = new Ped[140 * 2 + 2]; // Five minutes into doubled stack size and chill and it gives you that ped handle
		peds[0] = 140;
		INT found = GET_PED_NEARBY_PEDS(originPed.Handle(), (Any*)peds, -1);
		for (i = 0; i < found; i++)
		{
			j = i * 2 + 2;

			ped.Handle() = peds[j];
			if (!ped.Exists())
				continue;

			if (!ped.IsInRangeOf(originCoord, range))
				continue;

			//if (relationshipWithOriginPed == PedRelationship::Hate || relationshipWithOriginPed == PedRelationship::Dislike)
			//{
			//if (!IS_PED_IN_COMBAT(ped.Handle(), originPed.Handle())) continue;
			//}
			//else

			if (relationshipWithOriginPed != PedRelationship::MinusOneWat)
			{
				if (GET_RELATIONSHIP_BETWEEN_PEDS(ped.Handle(), originPed.Handle()) != relationshipWithOriginPed)
					continue;
			}

			ped.RequestControl();
			ped.Kill();
			EXPLODE_PED_HEAD(ped.Handle(), WEAPON_HEAVYSNIPER);

		}
		delete[] peds;

		/*bool originPedExists = originPed.Exists();

		for (auto& ped : allPeds)
		{
		if (!DOES_ENTITY_EXIST(ped)) continue;
		if (coord.DistanceTo(GET_ENTITY_COORDS(ped, 1)) > radius) continue;

		if (originPedExists) { if (GET_RELATIONSHIP_BETWEEN_PEDS(originPed.Handle(), ped) != relationshipWithOriginPed) continue; }

		RequestControlOfEnt(ped);
		EXPLODE_PED_HEAD(ped, WEAPON_HEAVYSNIPER);
		}*/

	}
	void KillMyEnemies()
	{
		std::vector<GTAblip> vBlips;
		World::GetActiveBlips(vBlips);
		GTAentity myPed = PLAYER_PED_ID();

		for (auto& blip : vBlips)
		{
			auto colour = blip.Colour();
			if (colour != BlipColour::Blue) // Don't hit friendlies
			{
				auto icon = blip.Icon();
				if (icon == BlipIcon::PoliceOfficer || icon == BlipIcon::Enemy || (icon == BlipIcon::Standard && colour == BlipColour::Red) || icon == BlipIcon::EnemyHelicopter || icon == BlipIcon::PoliceHelicopter || icon == BlipIcon::PoliceHelicopterAnimated)
				{
					World::AddExplosion(blip.Position_get(), EXPLOSION::BARREL, 5.0f, 0.0f, false, false);
				}
			}
		}
	}

}



// World - clear area
void clear_area_of_entities(const EntityType& type, const Vector3& coords, float radius, const std::vector<GTAentity>& excludes)
{

	//LOAD_ALL_OBJECTS_NOW();
	//LOAD_SCENE(coords.x, coords.y, coords.z);
	//SET_STREAMING(TRUE);

	std::vector<Entity> entities;
	switch (type)
	{
	case EntityType::ALL:		GTAmemory::GetEntityHandles(entities, coords, radius); break;
	case EntityType::PED:		GTAmemory::GetPedHandles(entities, coords, radius); break;
	case EntityType::VEHICLE:	GTAmemory::GetVehicleHandles(entities, coords, radius); break;
	case EntityType::PROP:		GTAmemory::GetPropHandles(entities, coords, radius); break;
	default: return; break;
	}

	GTAentity myPed = PLAYER_PED_ID();
	for (GTAentity ent : entities)
	{
		const auto& excit = std::find(excludes.begin(), excludes.end(), ent);
		if (excit == excludes.end()) // Not found in excludes
		{
			ent.Delete(ent != myPed);
		}
	}
	WAIT(0);
	sub::Spooner::EntityManagement::DeleteInvalidEntitiesInDb();

	update_nearby_stuff_arrays_tick();

	/*switch (type)
	{
	case EntityType::ALL:
	CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, radius, 0);
	CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, radius, 0, 0, 1, 1, 0);
	CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, radius, 0);
	break;
	case EntityType::PED:		CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, radius, 0); break;
	case EntityType::VEHICLE:	CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, radius, 0, 0, 1, 1, 0); break;
	case EntityType::PROP:	CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, radius, 0); break;
	}*/

	//SET_STREAMING(FALSE);
}
void clear_area_of_vehicles_around_entity(Entity entity, float radius, bool memry)
{

	Vector3 Pos = GET_ENTITY_COORDS(entity, 1);

	if (!memry)
	{
		if (IS_ENTITY_A_PED(entity))
		{
			INT i, offsettedID, found;

			Vehicle oldcar = 0;
			if (IS_PED_SITTING_IN_ANY_VEHICLE(entity))
				oldcar = GET_VEHICLE_PED_IS_IN(entity, 0);

			Vehicle *vehicles = new Vehicle[160 * 2 + 2];
			vehicles[0] = 160;
			found = GET_PED_NEARBY_VEHICLES(entity, (Any*)vehicles);
			for (i = 0; i < found; i++)
			{
				offsettedID = i * 2 + 2;

				if (!DOES_ENTITY_EXIST(vehicles[offsettedID]))
					continue;

				// clear area
				if (vehicles[offsettedID] == oldcar || Pos.DistanceTo(GET_ENTITY_COORDS(vehicles[offsettedID], 1)) > radius)
					continue;

				NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicles[offsettedID]);
				SET_ENTITY_AS_MISSION_ENTITY(vehicles[offsettedID], 0, 1);
				SET_ENTITY_COORDS(vehicles[offsettedID], 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0, 1);
				DELETE_VEHICLE(&vehicles[offsettedID]);

				CLEAR_AREA_OF_VEHICLES(Pos.x, Pos.y, Pos.z, radius, 0, 0, 1, 1, 0, 0, 0);
			}
			delete[] vehicles;
		}
	}

	else
	{
		if (IS_ENTITY_A_PED(entity))
			clear_area_of_entities(EntityType::VEHICLE, Pos, radius, { GET_VEHICLE_PED_IS_USING(entity) });
		else clear_area_of_entities(EntityType::VEHICLE, Pos, radius, {});
	}



}
void clear_area_of_peds_around_entity(Entity entity, float radius, bool memry)
{

	Vector3 Pos = GET_ENTITY_COORDS(entity, 1);

	if (!memry)
	{
		if (IS_ENTITY_A_PED(entity))
		{
			INT i, offsettedID, found;

			Ped *peds = new Ped[160 * 2 + 2];
			peds[0] = 160;
			found = GET_PED_NEARBY_PEDS(entity, (Any*)peds, -1);
			for (i = 0; i < found; i++)
			{
				offsettedID = i * 2 + 2;

				if (!DOES_ENTITY_EXIST(peds[offsettedID]) || Pos.DistanceTo(GET_ENTITY_COORDS(peds[offsettedID], 1)) > radius)
					continue;

				// clear area
				if (IS_PED_A_PLAYER(peds[offsettedID]))
					continue;
				SET_ENTITY_AS_MISSION_ENTITY(peds[offsettedID], 0, 1);
				SET_ENTITY_COORDS(peds[offsettedID], 32.2653f, 7683.5249f, 0.5696f, 0, 0, 0, 1);
				DELETE_PED(&peds[offsettedID]);

				CLEAR_AREA_OF_PEDS(Pos.x, Pos.y, Pos.z, radius, 0);
			}
			delete[] peds;
		}
	}

	else
	{
		if (IS_ENTITY_A_PED(entity))
			clear_area_of_entities(EntityType::PED, Pos, radius, { entity });
		else clear_area_of_entities(EntityType::PED, Pos, radius, {});
	}

}
void clear_attachments_off_entity(const GTAentity& entity, const EntityType& entType)
{
	auto* handles = &_worldEntities;
	switch (entType)
	{
	case EntityType::PED: handles = &_worldPeds; break;
	case EntityType::VEHICLE: handles = &_worldVehicles; break;
	case EntityType::PROP: handles = &_worldObjects; break;
	}
	for (GTAentity e : *handles)
	{
		if (e.IsAttachedTo(entity))
		{
			/*if (entity.Handle() == PLAYER_PED_ID() && IS_PED_A_PLAYER(e.Handle()))
			{
			std::string ofn("_reserved");
			sub::ComponentChanger_Outfit_catind::Create(entity.Handle(), ofn);
			if (sub::ComponentChanger_Outfit_catind::Exists(ofn))
			{
			WAIT(40);
			sub::ComponentChanger_Outfit_catind::Apply(entity, ofn, true, true, true, true);
			}
			}
			else*/
			{
				e.RequestControl();
				e.Detach();
				e.Delete(true);
			}
		}
	}
}


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

#include "..\Natives\types.h" // RGBA, RgbS

#include <string>

//class RGBA;
//class RgbS;
class Vector3;
class GTAentity;

typedef unsigned long DWORD;
typedef unsigned short UINT16;

namespace PTFX
{
	class sFxData
	{
	public:
		std::string asset; std::string effect;
		sFxData()
		{
		}
		sFxData(const std::string& a, const std::string& e)
			: asset(a), effect(e)
		{
		}
	};

	class LoopedPTFX
	{
	protected:
		float scale;
		int mHandle;
		std::string asset;
		std::string effect;
	public:
		int& Handle();

		LoopedPTFX();
		LoopedPTFX(const std::string& assetName, const std::string& fxName);
		LoopedPTFX(const sFxData& newFxData);

		void operator = (const LoopedPTFX& right);

		sFxData GetFxData() const;
		void SetFxData(const sFxData& d);

		bool Exists() const;
		bool IsAssetLoaded() const;
		void LoadAsset();
		void UnloadAsset();

		// bone does not require GetBoneIndex for peds.
		void Start(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col = { 255, 255, 255, 255 }, int bone = -1);
		// bone does not require GetBoneIndex for peds.
		void EasyStart(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col = { 255, 255, 255, 255 }, int bone = -1);

		void Start(GTAentity entity, float scale);
		void EasyStart(GTAentity entity, float scale);

		void Start(const Vector3& position, float scale, const Vector3& rotation);
		void EasyStart(const Vector3& position, float scale, const Vector3& rotation);

		void Start(const Vector3& position, float scale);
		void EasyStart(const Vector3& position, float scale);

		void SetOffsets(const Vector3& offset, const Vector3& rotOffset);
		void SetScale(float value);
		void SetAlpha(UINT8 value);
		void SetColour(const RgbS& value);

		void Remove();
		static void RemoveInRange(const Vector3& position, float radius);
	};

	class NonLoopedPTFX
	{
	protected:
		std::string asset;
		std::string effect;
	public:
		NonLoopedPTFX();
		NonLoopedPTFX(const std::string& assetName, const std::string& fxName);
		NonLoopedPTFX(const sFxData& newFxData);

		sFxData GetFxData() const;
		void SetFxData(const sFxData& d);

		void operator = (const NonLoopedPTFX& right);

		bool IsAssetLoaded() const;
		void LoadAsset();
		bool LoadAsset(DWORD timeOut);
		void UnloadAsset();

		// pedBone does not require GetBoneIndex for peds.
		void Start(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col = { 255, 255, 255, 255 }, int pedBone = -1);
		// pedBone does not require GetBoneIndex for peds.
		void EasyStart(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col = { 255, 255, 255, 255 }, int pedBone = -1);

		void Start(GTAentity entity, float scale);
		void EasyStart(GTAentity entity, float scale);

		void Start(const Vector3& position, float scale, const Vector3& rotation);
		void EasyStart(const Vector3& position, float scale, const Vector3& rotation);

		void Start(const Vector3& position, float scale);
		void EasyStart(const Vector3& position, float scale);

		static void SetColour(const RgbS& value);
		static void SetAlpha(UINT8 value);
	};

	void trigger_ptfx_1(const std::string& asset2, const std::string& name2, GTAentity entity, Vector3 position, Vector3 rotation, float scale, int pedBone = -1);

}


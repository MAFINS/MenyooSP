/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PTFX.h"

#include "..\macros.h"

#include "..\Natives\types.h" // RGBA, RgbS
#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "GTAentity.h"

#include <string>

namespace PTFX
{
#pragma region LoopedPTFX
	int& LoopedPTFX::Handle()
	{
		return this->mHandle;
	}

	LoopedPTFX::LoopedPTFX() :
		mHandle(-1)
	{
	}
	LoopedPTFX::LoopedPTFX(const std::string& assetName, const std::string& fxName) :
		mHandle(-1),
		asset(assetName),
		effect(fxName)
	{
	}
	LoopedPTFX::LoopedPTFX(const sFxData& newFxData) :
		mHandle(-1),
		asset(newFxData.asset),
		effect(newFxData.effect)
	{
	}

	void LoopedPTFX::operator = (const LoopedPTFX& right)
	{
		this->scale = right.scale;
		this->mHandle = right.mHandle;
		this->asset = right.asset;
		this->effect = right.effect;
	}

	sFxData LoopedPTFX::GetFxData() const
	{
		sFxData dat;
		dat.asset = this->asset;
		dat.effect = this->effect;
		return dat;
	}
	void LoopedPTFX::SetFxData(const sFxData& d)
	{
		this->asset = d.asset;
		this->effect = d.effect;
	}

	bool LoopedPTFX::Exists() const
	{
		return this->mHandle == -1 ? false : DOES_PARTICLE_FX_LOOPED_EXIST(this->mHandle) != 0;
	}
	bool LoopedPTFX::IsAssetLoaded() const
	{
		return HAS_NAMED_PTFX_ASSET_LOADED((PCHAR)this->asset.c_str()) != 0;
	}
	void LoopedPTFX::LoadAsset()
	{
		REQUEST_NAMED_PTFX_ASSET((PCHAR)this->asset.c_str());
	}
	void LoopedPTFX::UnloadAsset()
	{
		if (this->IsAssetLoaded())
		{
			REMOVE_NAMED_PTFX_ASSET((PCHAR)this->asset.c_str());
		}
	}

	// bone does not require GetBoneIndex for peds.
	void LoopedPTFX::Start(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col, int bone)
	{
		//if (this->Exists()) return;

		this->scale = scale;

		USE_PARTICLE_FX_ASSET((PCHAR)this->asset.c_str());

		if (bone == -1)
		{
			this->mHandle = START_PARTICLE_FX_LOOPED_ON_ENTITY((PCHAR)this->effect.c_str(), entity.Handle(), offset.x, offset.y, offset.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0);
		}
		else
		{
			if (entity.IsPed())
				bone = GET_PED_BONE_INDEX(entity.Handle(), bone);
			this->mHandle = START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE((PCHAR)this->effect.c_str(), entity.Handle(), offset.x, offset.y, offset.z, rotation.x, rotation.y, rotation.z, bone, scale, 0, 0, 0);
		}

		this->SetColour(RgbS(col.R, col.G, col.B));
		this->SetAlpha(col.A);
	}
	// bone does not require GetBoneIndex for peds.
	void LoopedPTFX::EasyStart(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col, int bone)
	{
		if (!this->Exists())
		{
			if (!this->IsAssetLoaded())
			{
				this->LoadAsset();
				WAIT(15);
			}
			this->Start(entity, scale, offset, rotation, col, bone);
		}
	}

	void LoopedPTFX::Start(GTAentity entity, float scale)
	{
		this->Start(entity, scale, Vector3(), Vector3());
	}
	void LoopedPTFX::EasyStart(GTAentity entity, float scale)
	{
		if (!this->Exists())
		{
			if (!this->IsAssetLoaded())
			{
				this->LoadAsset();
				WAIT(15);
			}
			this->Start(entity, scale, Vector3(), Vector3());
		}
	}

	void LoopedPTFX::Start(const Vector3& position, float scale, const Vector3& rotation)
	{
		//if (this->Exists()) return;

		this->scale = scale;

		USE_PARTICLE_FX_ASSET((PCHAR)this->asset.c_str());

		this->mHandle = START_PARTICLE_FX_LOOPED_AT_COORD((PCHAR)this->effect.c_str(),
			position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0, 0);
	}
	void LoopedPTFX::EasyStart(const Vector3& position, float scale, const Vector3& rotation)
	{
		if (!this->Exists())
		{
			if (!this->IsAssetLoaded())
			{
				this->LoadAsset();
				WAIT(15);
			}
			this->Start(position, scale, rotation);
		}
	}

	void LoopedPTFX::Start(const Vector3& position, float scale)
	{
		Start(position, scale, Vector3());
	}
	void LoopedPTFX::EasyStart(const Vector3& position, float scale)
	{
		if (!this->Exists())
		{
			if (!this->IsAssetLoaded())
			{
				this->LoadAsset();
				WAIT(15);
			}
			this->Start(position, scale, Vector3());
		}
	}

	void LoopedPTFX::SetOffsets(const Vector3& offset, const Vector3& rotOffset)
	{
		SET_PARTICLE_FX_LOOPED_OFFSETS(this->mHandle, offset.x, offset.y, offset.z, rotOffset.x, rotOffset.y, rotOffset.z);
	}
	void LoopedPTFX::SetScale(float value)
	{
		SET_PARTICLE_FX_LOOPED_SCALE(this->mHandle, value);
	}
	void LoopedPTFX::SetAlpha(UINT8 value)
	{
		SET_PARTICLE_FX_LOOPED_ALPHA(this->mHandle, (float)value/255);
	}
	void LoopedPTFX::SetColour(const RgbS& value)
	{
		SET_PARTICLE_FX_LOOPED_COLOUR(this->mHandle, (float)value.R/255, (float)value.G/255, (float)value.B/255, false);
	}

	void LoopedPTFX::Remove()
	{
		//if (!this->Exists()) return;

		//STOP_PARTICLE_FX_LOOPED(this->mHandle, false);

		REMOVE_PARTICLE_FX(this->mHandle, false);
		this->mHandle = -1;
	}
	void LoopedPTFX::RemoveInRange(const Vector3& position, float radius)
	{
		REMOVE_PARTICLE_FX_IN_RANGE(position.x, position.y, position.z, radius);
	}
#pragma endregion

#pragma region NonLoopedPTFX
	NonLoopedPTFX::NonLoopedPTFX()
	{
	}
	NonLoopedPTFX::NonLoopedPTFX(const std::string& assetName, const std::string& fxName) :
		asset(assetName),
		effect(fxName)
	{
	}
	NonLoopedPTFX::NonLoopedPTFX(const sFxData& newFxData) :
		asset(newFxData.asset),
		effect(newFxData.effect)
	{
	}

	sFxData NonLoopedPTFX::GetFxData() const
	{
		sFxData dat;
		dat.asset = this->asset;
		dat.effect = this->effect;
		return dat;
	}
	void NonLoopedPTFX::SetFxData(const sFxData& d)
	{
		this->asset = d.asset;
		this->effect = d.effect;
	}

	void NonLoopedPTFX::operator = (const NonLoopedPTFX& right)
	{
		this->asset = right.asset;
		this->effect = right.effect;
	}

	bool NonLoopedPTFX::IsAssetLoaded() const
	{
		return HAS_NAMED_PTFX_ASSET_LOADED((PCHAR)this->asset.c_str()) != 0;
	}
	void NonLoopedPTFX::LoadAsset()
	{
		REQUEST_NAMED_PTFX_ASSET((PCHAR)this->asset.c_str());
	}
	bool NonLoopedPTFX::LoadAsset(DWORD timeOut)
	{
		if (HAS_NAMED_PTFX_ASSET_LOADED(asset.c_str())) return true;
		else
		{
			REQUEST_NAMED_PTFX_ASSET(asset.c_str());

			for (timeOut += GetTickCount(); GetTickCount() < timeOut;)
			{
				if (HAS_NAMED_PTFX_ASSET_LOADED(asset.c_str())) return true;
				WAIT(0);
			}
			return false;
		}
	}
	void NonLoopedPTFX::UnloadAsset()
	{
		if (this->IsAssetLoaded())
		{
			REMOVE_NAMED_PTFX_ASSET((PCHAR)this->asset.c_str());
		}
	}

	// pedBone does not require GetBoneIndex for peds.
	void NonLoopedPTFX::Start(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col, int pedBone)
	{
		USE_PARTICLE_FX_ASSET((PCHAR)this->asset.c_str());

		NonLoopedPTFX::SetColour(RgbS(col.R, col.G, col.B));
		NonLoopedPTFX::SetAlpha(col.B);

		if (pedBone == -1)
		{
			START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY((PCHAR)this->effect.c_str(), entity.Handle(), offset.x, offset.y, offset.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0);
		}
		else
		{
			START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE((PCHAR)this->effect.c_str(), entity.Handle(), offset.x, offset.y, offset.z, rotation.x, rotation.y, rotation.z, pedBone, scale, 0, 0, 0);
		}
	}
	// pedBone does not require GetBoneIndex for peds.
	void NonLoopedPTFX::EasyStart(GTAentity entity, float scale, const Vector3& offset, const Vector3& rotation, RGBA col, int pedBone)
	{
		if (!this->IsAssetLoaded())
		{
			this->LoadAsset();
			WAIT(15);
		}
		this->Start(entity, scale, offset, rotation, col, pedBone);
	}

	void NonLoopedPTFX::Start(GTAentity entity, float scale)
	{
		this->Start(entity, scale, Vector3(), Vector3());
	}
	void NonLoopedPTFX::EasyStart(GTAentity entity, float scale)
	{
		if (!this->IsAssetLoaded())
		{
			this->LoadAsset();
			WAIT(15);
		}
		this->Start(entity, scale, Vector3(), Vector3());
	}

	void NonLoopedPTFX::Start(const Vector3& position, float scale, const Vector3& rotation)
	{
		USE_PARTICLE_FX_ASSET((PCHAR)this->asset.c_str());

		START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD((PCHAR)this->effect.c_str(),
			position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0, false);
	}
	void NonLoopedPTFX::EasyStart(const Vector3& position, float scale, const Vector3& rotation)
	{
		if (!this->IsAssetLoaded())
		{
			this->LoadAsset();
			WAIT(15);
		}
		this->Start(position, scale, rotation);
	}

	void NonLoopedPTFX::Start(const Vector3& position, float scale)
	{
		Start(position, scale, Vector3());
	}
	void NonLoopedPTFX::EasyStart(const Vector3& position, float scale)
	{
		if (!this->IsAssetLoaded())
		{
			this->LoadAsset();
			WAIT(15);
		}
		this->Start(position, scale, Vector3());
	}

	void NonLoopedPTFX::SetColour(const RgbS& value)
	{
		SET_PARTICLE_FX_NON_LOOPED_COLOUR((float)value.R / 255, (float)value.G / 255, (float)value.B / 255);
	}
	void NonLoopedPTFX::SetAlpha(UINT8 value)
	{
		SET_PARTICLE_FX_NON_LOOPED_ALPHA((float)value/255);
	}
#pragma endregion

	void trigger_ptfx_1(const std::string& asset, const std::string& name, GTAentity entity, Vector3 position, Vector3 rotation, float scale, int pedBone)
	{

		REQUEST_NAMED_PTFX_ASSET(asset.c_str());
		if (HAS_NAMED_PTFX_ASSET_LOADED(asset.c_str()))
		{
			USE_PARTICLE_FX_ASSET(asset.c_str());
			SET_PARTICLE_FX_NON_LOOPED_COLOUR(GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f), GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f));
			if (entity.Handle() == 0)
				START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(name.c_str(), position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0, false);
			else
			{
				if (entity.Exists())
				{
					//entity.RequestControlOnce();
					if (pedBone != -1)
					{
						START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name.c_str(), entity.Handle(), position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, pedBone, scale, 0, 0, 0);
					}
					else
					{
						START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(name.c_str(), entity.Handle(), position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale, 0, 0, 0);
					}
				}
			}
		}
	}

}


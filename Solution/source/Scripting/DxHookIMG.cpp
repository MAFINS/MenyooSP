/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "DxHookIMG.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "..\Util\FileLogger.h"

#include "..\Util\ExePath.h"

#include "..\Submenus\VehicleOptions.h"
#include "..\Submenus\TimeOptions.h"

namespace DxHookIMG
{
	int DxTexture::globalDrawOrder = -9999;

	bool DxTexture::operator == (const DxTexture& right)
	{
		return (this->id == right.id);
	}
	DxTexture& DxTexture::operator = (const DxTexture& right)
	{
		this->id = right.id;
		return *this;
	}

	DxTexture::DxTexture() : id(0)//, instanceIndex(0)
	{
	}

	DxTexture::DxTexture(int iD) : id(iD)//, instanceIndex(0)
	{
	}

	DxTexture::DxTexture(const std::string& file)
	{
		this->Load(file);
	}

	void DxTexture::Load(const std::string& file)
	{
		if (does_file_exist(file))
		{
			ige::myLog << ige::LogType::LOG_INFO << "[DX-HOOK] Loading texture: " << file;
			this->id = createTexture(file.c_str());

			/*auto slashPos = file.rfind("\\");
			if (slashPos == std::string::npos) slashPos = file.rfind("//");
			if (slashPos == std::string::npos) slashPos = 0;
			this->name = file.substr(slashPos, file.rfind(".") - slashPos);*/
		}
		else
		{
			ige::myLog << ige::LogType::LOG_ERROR << "[DX-HOOK] Unable to find: " << file;
			this->id = 0;
		}
	}

	bool DxTexture::Exists()
	{
		return this->id != 0;
	}

	int& DxTexture::GlobalDrawOrderRef()
	{
		return DxTexture::globalDrawOrder;
	}

	int& DxTexture::ID()
	{
		return this->id;
	}

	void DxTexture::Draw(UINT8 index, const Vector2& position, const Vector2& size, float rotationOutOf360, const RGBA& colour)
	{
		drawTexture(this->id, index, DxTexture::globalDrawOrder, 55, size.x, size.y, 0.5f, 0.5f, position.x, position.y, rotationOutOf360 / 360.0f, GRAPHICS::GET_ASPECT_RATIO(false), (float)(colour.R) / 255.0f, (float)(colour.G) / 255.0f, (float)(colour.B) / 255.0f, (float)(colour.A) / 255.0f);
		DxTexture::globalDrawOrder++;
	}
	void DxTexture::DrawAdvanced(UINT8 index, int level, int time, const Vector2& centrePos, const Vector2& position, const Vector2& size, float rotationOutOf360, const RGBA& colour)
	{
		drawTexture(this->id, index, level, time, size.x, size.y, centrePos.x, centrePos.y, position.x, position.y, rotationOutOf360 / 360.0f, GRAPHICS::GET_ASPECT_RATIO(false), (float)(colour.R) / 255.0f, (float)(colour.G) / 255.0f, (float)(colour.B) / 255.0f, (float)(colour.A) / 255.0f);
	}

	//DxTexture titleui_spooner;
	DxTexture teleToWpBoxIconKeyboard;
	DxTexture teleToWpBoxIconGamepad;
	void LoadAllMenyooTexturesInit()
	{
		sub::Speedo_catind::LoadSpeedoImages();
		sub::Clock_catind::LoadClockImages();
		//DxHookIMG::titleui_spooner.Load(GetPathffA(Pathff::Graphics, true) + "titleui_spooner.png");
		DxHookIMG::teleToWpBoxIconKeyboard.Load(GetPathffA(Pathff::Graphics, true) + "teleportToWaypointBoxKeyboard.png");
		DxHookIMG::teleToWpBoxIconGamepad.Load(GetPathffA(Pathff::Graphics, true) + "teleportToWaypointBoxGamepad.png");

	}
}




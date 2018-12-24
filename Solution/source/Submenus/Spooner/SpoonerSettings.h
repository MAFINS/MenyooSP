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

#include <string>
#include <vector>

typedef unsigned char UINT8;

namespace sub::Spooner
{
	enum class eSpoonerModeMode : UINT8 { GroundEase, Precision };
	extern const std::vector<std::string> vSpoonerModeMode;

	namespace Settings
	{
#define GTA_MAX_ENTITIES 2048

		extern float CameraMovementSensitivityKeyboard;
		extern float CameraRotationSensitivityMouse;
		extern float CameraMovementSensitivityGamepad;
		extern float CameraRotationSensitivityGamepad;

		extern eSpoonerModeMode SpoonerModeMode;

		extern bool bShowModelPreviews;
		extern bool bShowBoxAroundSelectedEntity;
		extern bool bSpawnDynamicProps;
		extern bool bSpawnDynamicPeds;
		extern bool bSpawnDynamicVehicles;
		extern bool bFreezeEntityWhenMovingIt;
		extern bool bSpawnInvincibleEntities;
		extern bool bSpawnStillPeds;
		extern bool bAddToDbAsMissionEntities;
		extern bool bKeepPositionWhenAttaching;

		extern bool bTeleportToReferenceWhenLoadingFile;
	}

}




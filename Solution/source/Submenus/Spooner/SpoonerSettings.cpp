/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "SpoonerSettings.h"

#include "..\..\macros.h"

//#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

//#include "..\..\Natives\natives2.h"

#include <string>
#include <vector>

namespace sub::Spooner
{
	//enum class eSpoonerModeMode : UINT8 { GroundEase, Precision };
	const std::vector<std::string> vSpoonerModeMode{ "Surface Ease", "Precision" };

	namespace Settings
	{
//#define GTA_MAX_ENTITIES 2048

		float CameraMovementSensitivityKeyboard = 0.33f;
		float CameraRotationSensitivityMouse = 6.5f;
		float CameraMovementSensitivityGamepad = 0.9f;
		float CameraRotationSensitivityGamepad = 1.4f;

		eSpoonerModeMode SpoonerModeMode = eSpoonerModeMode::GroundEase;

		bool bShowModelPreviews = true;
		bool bShowBoxAroundSelectedEntity = false;
		bool bSpawnDynamicProps = false;
		bool bSpawnDynamicPeds = true;
		bool bSpawnDynamicVehicles = true;
		bool bFreezeEntityWhenMovingIt = false;
		bool bSpawnInvincibleEntities = false;
		bool bSpawnStillPeds = true;
		bool bAddToDbAsMissionEntities = true;
		bool bKeepPositionWhenAttaching = false;

		bool bTeleportToReferenceWhenLoadingFile = true;
	}

}




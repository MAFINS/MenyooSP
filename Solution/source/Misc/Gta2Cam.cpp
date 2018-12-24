/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Gta2Cam.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"
#include "..\Scripting\Camera.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAvehicle.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\World.h"
#include "..\Scripting\GameplayCamera.h"

namespace _Gta2Cam_
{
	// Not using these as class members because I feel like it
	Camera gmCam2;
	Camera mainCam;
	Vector3 mainCamRelativePos;

	const Camera& Gta2Cam::MainCam()
	{
		return mainCam;
	}

	void Gta2Cam::CreateMainCam(GTAentity myPed)
	{
		if (myPed.Exists())
		{
			if (mainCam.Exists())
			{
				mainCam.SetActive(false);
				mainCam.Destroy();
			}
			Vector3& myPos = myPed.Position_get();
			mainCamRelativePos = Vector3(0.0f, -0.5f, 19.0f);
			Vector3& mainCamPos = myPos + mainCamRelativePos;
			Vector3& mainCamRot = Vector3(-89.5, 0.0f, 0.0f);
			mainCam = World::CreateCamera(mainCamPos, mainCamRot, 45.0f);
		}
	}

	void Gta2Cam::TurnOn()
	{
		GenericLoopedMode::TurnOn();

		if (gmCam2.Exists())
		{
			gmCam2.SetActive(false);
			gmCam2.Destroy();
		}

		GTAentity myPed = PLAYER_PED_ID();

		Vector3& gmCamPos = GameplayCamera::Position_get();
		Vector3& gmCamRot = GameplayCamera::Rotation_get();
		float gmCamFov = GameplayCamera::FieldOfView_get();
		gmCam2 = World::CreateCamera(gmCamPos, gmCamRot, gmCamFov);

		CreateMainCam(myPed);

		gmCam2.InterpTo(mainCam, 2500, true, true); // Wait for interp?

		Camera::RenderScriptCams(true);

		if (gmCam2.Exists())
			gmCam2.Destroy();
	}
	void Gta2Cam::TurnOff()
	{
		GenericLoopedMode::TurnOff();

		if (gmCam2.Exists())
		{
			gmCam2.SetActive(false);
			gmCam2.Destroy();
		}
		if (mainCam.Exists())
		{
			mainCam.SetActive(false);
			mainCam.Destroy();
		}
		Camera::RenderScriptCams(false);
	}

	void Gta2Cam::Tick()
	{
		if (bEnabled)
		{
			DoGta2CamTick();
		}
	}
	inline void Gta2Cam::DoGta2CamTick()
	{
		GTAped myPed = PLAYER_PED_ID();

		if (mainCam.Exists())
		{
			if (mainCam.IsActive())
			{
				Vector3& myPos = myPed.Position_get();

				mainCam.Position_set(myPos + mainCamRelativePos);
				//mainCam.Rotation_set(-89.5f, 0.0f, 0.0f);

				//_CLAMP_GAMEPLAY_CAM_PITCH(-90.0f, -90.0f);
				_CLAMP_GAMEPLAY_CAM_PITCH(0.0f, 0.0f);
				_CLAMP_GAMEPLAY_CAM_YAW(0.0f, 0.0f);

				GTAvehicle myVeh = myPed.CurrentVehicle();

				if (myPed.IsOnFoot())
				{
					bool bSprinting = myPed.IsSprinting();
					if (bSprinting)
					{
						if (mainCamRelativePos.z < 22.0f)
							mainCamRelativePos.z += 0.14f;
					}
					else
					{
						if (mainCamRelativePos.z > 19.0f)
							mainCamRelativePos.z -= 0.14f;
					}
					//if (IS_CONTROL_PRESSED(0, INPUT_AIM))
					//{
					//}
					//else //if (IS_CONTROL_JUST_RELEASED(0, INPUT_AIM))
					//{
					//}
				}
				else if (myVeh.Exists())
				{
					float mySpeed = myVeh.Speed_get() * 3.6f;
					if (mySpeed > 30.0f)
					{
						if (mainCamRelativePos.z < 26.0f)
							mainCamRelativePos.z += 0.14f;
					}
					else
					{
						if (mainCamRelativePos.z > 19.0f)
							mainCamRelativePos.z -= 0.14f;
					}
				}
			}
			else // Cam isn't active
			{
				mainCam.SetActive(true);
				Camera::RenderScriptCams(true);
				//mainCamRelativePos = Vector3(0.0f, -0.5f, 19.0f);
			}
		}
		else // Cam doesn't exist
		{
			CreateMainCam(myPed);
		}
	}


	Gta2Cam g_gta2Cam;

	void ToggleOnOff()
	{
		g_gta2Cam.Toggle();
	}

}




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

#include "GenericLoopedMode.h"

//#include "..\Util\GTAmath.h"
//#include "..\Scripting\Camera.h"

class GTAentity;
class Camera;

namespace _Gta2Cam_
{
	class Gta2Cam final : public GenericLoopedMode
	{
	private:
		//Camera gmCam2;
		//Camera mainCam;
		//Vector3 mainCamRelativePos;
	public:
		const Camera& MainCam();

		void CreateMainCam(GTAentity myPed);

		void TurnOn() override;
		void TurnOff() override;

		void Tick() override;
		inline void DoGta2CamTick();

	};


	extern Gta2Cam g_gta2Cam;

	void ToggleOnOff();
}







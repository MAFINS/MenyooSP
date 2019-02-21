/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FpsCounter.h"

#include "..\macros.h"

#include "..\Scripting\enums.h"
#include "..\Scripting\Game.h"
#include "..\Util\GTAmath.h"

#include <Windows.h> // GetTickCount
#include <string>

namespace _FpsCounter_
{
	FpsCounter::FpsCounter()
		: fpsValue(0), frameCounter(0), timer(GetTickCount())
	{
	}

	DWORD FpsCounter::Get() const
	{
		return fpsValue;
	}

	std::string FpsCounter::GetString() const
	{
		return std::to_string(fpsValue);
	}

	void FpsCounter::Tick()
	{
		frameCounter++;

		if (GetTickCount() - timer > 500) //0.5sec
		{
			// store frame count to fpsValue
			fpsValue = frameCounter * 2;

			// reset
			frameCounter = 0;
			timer = GetTickCount();
		}
	}

	FpsCounter g_fpsCounter;

	void DisplayFps()
	{
		g_fpsCounter.Tick();
		Game::Print::setupdraw(GTAfont::Impact, Vector2(0.4f, 0.4f), false, false, false);
		Game::Print::drawstring("~y~" + g_fpsCounter.GetString() + " FPS", 0.945f, 0.034f);
	}

	void DisplayFpsTick()
	{

	}

	bool bDisplayFps = false;

}




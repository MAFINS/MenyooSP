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

//#include "GenericLoopedMode.h"

#include <string>

typedef unsigned long DWORD;

namespace _FpsCounter_
{
	class FpsCounter final
	{
	protected:
		DWORD fpsValue;
		DWORD frameCounter;
		DWORD timer;

	public:
		FpsCounter();

		DWORD Get() const;

		std::string GetString() const;

		void Tick();
	};
	extern FpsCounter g_fpsCounter;


	void DisplayFps();

	void DisplayFpsTick();

	extern bool bDisplayFps;
}







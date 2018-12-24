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

// nts: This is so useless with the way it's used
class GenericLoopedMode abstract
{
public:
	static void TickAll();

protected:
	bool bEnabled;
public:
	GenericLoopedMode();

	bool& Enabled();

	virtual void Toggle();
	virtual void TurnOn();
	virtual void TurnOff();

	virtual void Tick() = 0;
};





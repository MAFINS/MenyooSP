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

#include <vector>
#include <utility>
#include <string>

namespace TimecycleModification
{
	extern std::vector<std::pair<std::string, std::string>> vTimecycles; // pair<value, caption>

	bool PopulateTimecycleNames();

	bool IsModActive();
	int GetModId();
	void SetMod(const std::string& value);
	void SetMod(const std::string& value, float transition);
	void SetModStrength(float value);
	void ClearMod();
}
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

typedef signed char INT8;
typedef unsigned char UINT8;

class RGBA;

namespace sub
{
	void Settings();

	void SettingsMenuPos_();

	//extern RGBA* _g_settings_rgba;
	//extern int*_g_settings_rgba2;
	//extern int* _g_settings_font;
	extern UINT8 settings_hud_c;

	void AddsettingscolOption(const std::string& text, RGBA& feature);
	void SettingsColours();
	void SettingsColours2();

	void AddsettingsfonOption(const std::string& text, int font_index, INT8& feature);
	void SettingsFonts();
	void SettingsFonts2();

	namespace SettingsThemes_catind
	{
		void Sub_Main();

	}

}





/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MainMenu.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"
#include "..\Menu\MenuConfig.h"
#include "..\Menu\Language.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Natives\types.h" // RGBA
#include "..\Scripting\enums.h"
#include "..\Scripting\Game.h"

#include <string>
//#include <cstdlib>
#include <math.h>

namespace sub
{
	void Settings()
	{
		auto& bSyncWithConfig = MenuConfig::bSaveAtIntervals;

		AddTitle("Settings");

		bool bChangeLangPressed = false;
		AddTexter("Language", 0, { Language::GetSelectedLangTitle() }, bChangeLangPressed); if (bChangeLangPressed)
			Menu::SetSub_delayed = SUB::SETTINGS_LANGUAGE;

		AddOption("Themes", null, nullFunc, SUB::SETTINGS_THEMES);
		AddOption("Menu Colours", null, nullFunc, SUB::SETTINGS_COLOURS);
		AddOption("Menu Fonts", null, nullFunc, SUB::SETTINGS_FONTS);
		AddOption("Menu Position", null, nullFunc, SUB::SETTINGS_MENUPOS);
		//AddToggle("Mouse Support (ALPHA)", Menu::bit_mouse);
		AddToggle("Gradients", Menu::gradients);
		AddToggle("Titlebox Globe", Menu::bit_glare_test);
		AddToggle("Centre Title", Menu::bit_centre_title);
		AddToggle("Centre Options", Menu::bit_centre_options);
		AddToggle("Centre Breaks", Menu::bit_centre_breaks);
		AddToggle("Reset Player Model Upon Death (SP)", loop_Check_self_death_model);
		AddToggle("Sync Menyoo With Config File", bSyncWithConfig, MenuConfig::ConfigSave, MenuConfig::ConfigSave);
		AddOption("Reset Toggles (Most Of Them)", null, MenuConfig::ConfigResetHaxValues);

	}

	void SettingsMenuPos_()
	{
		bool settings_xpos_plus = 0, settings_xpos_minus = 0,
			settings_ypos_plus = 0, settings_ypos_minus = 0;

		AddTitle("Menu Position");
		AddNumber("Offset X", menuPos.x * 100 + 6.0, 2, null, settings_xpos_plus, settings_xpos_minus);
		AddNumber("Offset Y", menuPos.y * 100 + 7.4, 2, null, settings_ypos_plus, settings_ypos_minus);


		if (settings_xpos_plus) {
			if (menuPos.x < 0.7397f) menuPos.x += 0.002f;
			//MenuConfig::iniFile.SetDoubleValue("settings", "menuPosX", (menuPos.x + 0.0598) * 100);
			return;
		}
		else if (settings_xpos_minus) {
			if (menuPos.x > -0.0598f) menuPos.x -= 0.002f;
			if (menuPos.x < -0.0598f) menuPos.x = -0.0598f;
			//MenuConfig::iniFile.SetDoubleValue("settings", "menuPosX", (menuPos.x + 0.0598) * 100);
			return;
		}

		if (settings_ypos_plus) {
			if (menuPos.y < 0.85f) menuPos.y += 0.002f;
			//MenuConfig::iniFile.SetDoubleValue("settings", "menuPosY", (menuPos.x + 0.074) * 100);
			return;
		}
		else if (settings_ypos_minus) {
			if (menuPos.y > -0.074f) menuPos.y -= 0.002f;
			if (menuPos.y < -0.074f) menuPos.y = -0.074f;
			//MenuConfig::iniFile.SetDoubleValue("settings", "menuPosY", (menuPos.x + 0.074) * 100);
			return;
		}


	}

	RGBA* _g_settings_rgba;
	int*_g_settings_rgba2;
	INT8* _g_settings_font;
	UINT8 settings_hud_c = 0ui8;

	void AddsettingscolOption(const std::string& text, RGBA& feature)
	{
		auto& settings_rgba = _g_settings_rgba;
		
		bool pressed = false;
		AddOption(text, pressed, nullFunc, SUB::SETTINGS_COLOURS2);

		if (*Menu::currentopATM == Menu::printingop)
			Add_preset_colour_options_previews(feature);

		if (pressed)
			settings_rgba = &feature;
	}
	void SettingsColours()
	{
		AddTitle("Menu Colours");
		AddsettingscolOption("Title Box", titlebox);
		AddsettingscolOption("Background", BG);
		AddsettingscolOption("Title Text", titletext);
		AddsettingscolOption("Option Text", optiontext);
		AddsettingscolOption("Selected Text", selectedtext);
		AddsettingscolOption("Option Breaks", optionbreaks);
		AddsettingscolOption("Option Count", optioncount);
		AddsettingscolOption("Selection Box", selectionhi);
		AddsettingscolOption("Ped Trackers", _globalPedTrackers_Col);
		AddToggle("Rainbow", loop_RainbowBoxes);
	}
	void SettingsColours2()
	{
		bool settings_r_input = 0, settings_r_plus = 0, settings_r_minus = 0, settings_hud_c_apply = 0, settings_hud_c_plus = 0, settings_hud_c_minus = 0;

		auto& settings_rgba = _g_settings_rgba;
		auto& settings_rgba2 = _g_settings_rgba2;

		AddTitle("Set Colour");
		AddNumber("Red", settings_rgba->R, 0, settings_r_input, settings_r_plus, settings_r_minus);

		switch (*Menu::currentopATM)
		{
		case 1:case 2:case 3:
			Add_preset_colour_options_previews(settings_rgba->R, settings_rgba->G, settings_rgba->B);
			break;
		}

		AddNumber("Green", settings_rgba->G, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddNumber("Blue", settings_rgba->B, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddNumber("Opacity", settings_rgba->A, 0, settings_r_input, settings_r_plus, settings_r_minus);
		AddTexter("HUD Colour", settings_hud_c, HudColour::vHudColours, settings_hud_c_apply, settings_hud_c_plus, settings_hud_c_minus);
		AddBreak("---Presets---");
		Add_preset_colour_options(settings_rgba->R, settings_rgba->G, settings_rgba->B);

		switch (*Menu::currentopATM)
		{
		case 1: settings_rgba2 = &settings_rgba->R; break;
		case 2: settings_rgba2 = &settings_rgba->G; break;
		case 3: settings_rgba2 = &settings_rgba->B; break;
		case 4: settings_rgba2 = &settings_rgba->A; break;
		}

		if (settings_r_input) {
			int tempHash = *settings_rgba2;
			try {
				tempHash = abs(std::stoi(Game::InputBox(std::to_string(*settings_rgba2), 4U, "", std::to_string(*settings_rgba2))));
			}
			catch (...) { Game::Print::PrintError_InvalidInput(); }
			if (!(tempHash >= 0 && tempHash <= 255)) Game::Print::PrintError_InvalidInput();
			else *settings_rgba2 = tempHash;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SettingsRgba, std::to_string(*settings_rgba2), 3U, "", std::to_string(*settings_rgba2));
			return;
		}

		if (settings_r_plus) {
			if (*settings_rgba2 < 255)
				(*settings_rgba2)++;
			else *settings_rgba2 = 0;
			return;
		}
		else if (settings_r_minus) {
			if (*settings_rgba2 > 0)
				(*settings_rgba2)--;
			else *settings_rgba2 = 255;
			return;
		}

		if (settings_hud_c_plus) { if (settings_hud_c < HudColour::vHudColours.size() - 1) settings_hud_c++; else settings_hud_c = 0; return; }
		if (settings_hud_c_minus) { if (settings_hud_c > 0) settings_hud_c--; else settings_hud_c = 180; return; }
		if (settings_hud_c_apply) { GET_HUD_COLOUR(settings_hud_c, &settings_rgba->R, &settings_rgba->G, &settings_rgba->B, &inull);  return; }

	}

	void AddsettingsfonOption(const std::string& text, int font_index, INT8& feature)
	{
		auto& settings_font = _g_settings_font;

		bool bit_changefont = false;
		bool bit_setfeature = false;

		if (font_index == -1)
			AddOption(text, bit_setfeature, nullFunc, SUB::SETTINGS_FONTS2);
		else
			AddOption(text, bit_changefont);

		if (bit_setfeature)
			settings_font = &feature;
		else if (bit_changefont)
			*settings_font = font_index;
	}
	void SettingsFonts()
	{
		AddTitle("Menu Fonts");
		AddsettingsfonOption("Title", -1, font_title);
		AddsettingsfonOption("Options", -1, font_options);
		AddsettingsfonOption("Selected Option", -1, font_selection);
		AddsettingsfonOption("Option Breaks", -1, font_breaks);
		AddsettingsfonOption("XYZH Coords", -1, font_xyzh);
		AddsettingsfonOption("Speedo Text", -1, font_speedo);
	}
	void SettingsFonts2()
	{
		auto& settings_font = _g_settings_font;

		bool fonts2_input = false;

		INT8 dummyfeature;

		AddTitle("Set Font");
		AddsettingsfonOption("Normalish", GTAfont::Arial, dummyfeature);
		AddsettingsfonOption("Impactish", GTAfont::Impact, dummyfeature);
		AddsettingsfonOption("Italic", GTAfont::Italic, dummyfeature);
		AddsettingsfonOption("Pricedown", GTAfont::Pricedown, dummyfeature);
		AddsettingsfonOption("Caps", GTAfont::Caps, dummyfeature);
		AddOption("Input Index", fonts2_input);

		if (fonts2_input)
		{
			std::string inputStr = Game::InputBox(std::to_string(*settings_font), 7U, "", std::to_string(*settings_font));
			auto& settings_font = _g_settings_font;
			int tempHash = *settings_font;
			try { tempHash = abs(stoi(inputStr)); }
			catch (...) { Game::Print::PrintError_InvalidInput(); }
			*settings_font = tempHash;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SettingsFont, std::to_string(*settings_font), 6U, "", std::to_string(*settings_font));
		}
	}

	void SettingsLanguage()
	{
		AddTitle("Language");
		
		AddTickol("English", Language::selectedLang == nullptr, Language::ResetSelectedLang, Language::ResetSelectedLang);

		for (auto& l : Language::allLangs)
		{
			bool bPressed = false;
			AddTickol(l.GetName(), Language::selectedLang == &l, bPressed, bPressed); if (bPressed)
			{
				Language::SetSelectedLang(&l);
			}
		}

		AddTickol("Reload Language Files", true, *reinterpret_cast<void(*)()>(&Language::Init), *reinterpret_cast<void(*)()>(&Language::Init), TICKOL::CROSS);

	}

	namespace SettingsThemes_catind
	{
		class MenyooTheme
		{
		private:
			bool grads;
			bool rainbow;
			bool thinLineOverFooter;

			RGBA ttbox;
			RGBA bgbox;
			RGBA tttext;
			RGBA optext;
			RGBA seltext;
			RGBA opbreak;
			RGBA opcount;
			RGBA selhi;
			RGBA pedtrackers;

			INT8 f_title;
			INT8 f_options;
			INT8 f_selection;
			INT8 f_breaks;
			INT8 f_xyzh;
			INT8 f_speedo;
		public:
			MenyooTheme()
			{
			}
			MenyooTheme(bool _grads, bool _rainbow, bool _thinLineOverFooter,
				RGBA _ttbox, RGBA _bgbox, RGBA _tttext, RGBA _optext, RGBA _seltext, RGBA _opbreak, RGBA _opcount, RGBA _selhi, RGBA _pedtrackers,
				INT8 _f_title, INT8 _f_options, INT8 _f_selection, INT8 _f_breaks, INT8 _f_xyzh, INT8 _f_speedo)
			{
				grads = _grads;
				rainbow = _rainbow;
				thinLineOverFooter = _thinLineOverFooter;

				ttbox = _ttbox;
				bgbox = _bgbox;
				tttext = _tttext;
				optext = _optext;
				seltext = _seltext;
				opbreak = _opbreak;
				opcount = _opcount;
				selhi = _selhi;
				pedtrackers = _pedtrackers;

				f_title = _f_title;
				f_options = _f_options;
				f_selection = _f_selection;
				f_breaks = _f_breaks;
				f_xyzh = _f_xyzh;
				f_speedo = _f_speedo;
			}

			void SetActive()
			{
				Menu::gradients = grads;
				loop_RainbowBoxes = rainbow;
				Menu::thin_line_over_screct = thinLineOverFooter;

				titlebox = ttbox;
				BG = bgbox;
				titletext = tttext;
				optiontext = optext;
				selectedtext = seltext;
				optionbreaks = opbreak;
				optioncount = opcount;
				selectionhi = selhi;
				_globalPedTrackers_Col = pedtrackers;

				font_title = f_title;
				font_options = f_options;
				font_selection = f_selection;
				font_breaks = f_breaks;
				font_xyzh = f_xyzh;
				font_speedo = f_speedo;
			}
			bool IsActive()
			{
				return
					Menu::gradients == grads &&
					loop_RainbowBoxes == rainbow &&
					Menu::thin_line_over_screct == thinLineOverFooter &&

					titlebox == ttbox &&
					BG == bgbox &&
					titletext == tttext &&
					optiontext == optext &&
					selectedtext == seltext &&
					optionbreaks == opbreak &&
					optioncount == opcount &&
					selectionhi == selhi &&
					_globalPedTrackers_Col == pedtrackers &&

					font_title == f_title &&
					font_options == f_options &&
					font_selection == f_selection &&
					font_breaks == f_breaks &&
					font_xyzh == f_xyzh &&
					font_speedo == f_speedo;
			}

			static MenyooTheme CurrentlyActiveTheme()
			{
				MenyooTheme curr;

				curr.grads = Menu::gradients;
				curr.rainbow = loop_RainbowBoxes;
				curr.thinLineOverFooter = Menu::thin_line_over_screct;

				curr.ttbox = titlebox;
				curr.bgbox = BG;
				curr.tttext = titletext;
				curr.optext = optiontext;
				curr.seltext = selectedtext;
				curr.opbreak = optionbreaks;
				curr.opcount = optioncount;
				curr.selhi = selectionhi;
				curr.pedtrackers = _globalPedTrackers_Col;

				curr.f_title = font_title;
				curr.f_options = font_options;
				curr.f_selection = font_selection;
				curr.f_breaks = font_breaks;
				curr.f_xyzh = font_xyzh;
				curr.f_speedo = font_speedo;

				return curr;
			}

			bool operator ==(const MenyooTheme& value2) const
			{
				const MenyooTheme& value1 = *this;

				return
					value1.grads == value2.grads &&
					value1.rainbow == value2.rainbow &&
					value1.thinLineOverFooter == value2.thinLineOverFooter &&

					value1.ttbox == value2.ttbox &&
					value1.bgbox == value2.bgbox &&
					value1.tttext == value2.tttext &&
					value1.optext == value2.optext &&
					value1.seltext == value2.seltext &&
					value1.opbreak == value2.opbreak &&
					value1.opcount == value2.opcount &&
					value1.selhi == value2.selhi &&
					value1.pedtrackers == value2.pedtrackers &&

					value1.f_title == value2.f_title &&
					value1.f_options == value2.f_options &&
					value1.f_selection == value2.f_selection &&
					value1.f_breaks == value2.f_breaks &&
					value1.f_xyzh == value2.f_xyzh &&
					value1.f_speedo == value2.f_speedo;
			}
			bool Equals(MenyooTheme const& value2)
			{
				return (this->operator==(value2));
			}

		};
		class MenyooThemeNamed
		{
		public:
			std::string name;
			MenyooTheme theme;

			MenyooThemeNamed(const std::string& newName, const MenyooTheme& newTheme)
			{
				this->name = newName;
				this->theme = newTheme;
			}
		};

#pragma region themevector
		std::vector<MenyooThemeNamed> vValues_MenyooThemes
		{
			{ "Black & Green", MenyooTheme(true, false, false, RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 100), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 255), RGBA(255, 255, 255, 255), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "Black & Teal", MenyooTheme(true, false, false, RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 150), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 150), RGBA(0, 255, 255, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "Black & Red", MenyooTheme(true, false, false, RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 175), RGBA(255, 0, 0, 255), RGBA(255, 0, 0, 255), RGBA(255, 255, 255, 255), RGBA(255, 0, 0, 255), RGBA(255, 0, 0, 255), RGBA(255, 0, 0, 100), RGBA(255, 0, 0, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "Black & White", MenyooTheme(true, false, false, RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 50), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 150), RGBA(255, 255, 255, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "Black & Yellow", MenyooTheme(true, false, false, RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 100), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 125), RGBA(255, 255, 100, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },

			{ "White & Green", MenyooTheme(true, false, false, RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 100), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 255), RGBA(255, 255, 255, 255), RGBA(0, 255, 100, 255), RGBA(0, 255, 100, 255), RGBA(0, 255, 125, 150), RGBA(0, 255, 100, 255), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "White & Teal", MenyooTheme(true, false, false, RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 100), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 255), RGBA(0, 255, 255, 150), RGBA(0, 255, 255, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "White & Red", MenyooTheme(true, false, false, RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 175), RGBA(255, 0, 0, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(255, 0, 0, 255), RGBA(255, 0, 0, 255), RGBA(255, 0, 0, 150), RGBA(255, 0, 0, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "White & Black", MenyooTheme(true, false, false, RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 150), RGBA(0, 0, 0, 255), RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 255), RGBA(0, 0, 0, 255), RGBA(255, 255, 255, 150), RGBA(255, 255, 255, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "White & Yellow", MenyooTheme(true, false, false, RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 100), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 255), RGBA(255, 255, 100, 125), RGBA(255, 255, 100, 205), GTAfont::Italic, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },

			{ "Halloween", MenyooTheme(true, false, false, RGBA(22, 161, 18, 255), RGBA(96, 62, 148, 170), RGBA(255, 51, 0, 255), RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 255), RGBA(255, 255, 255, 255), RGBA(255, 51, 0, 255), RGBA(255, 51, 0, 150), RGBA(22, 161, 18, 205), GTAfont::Pricedown, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
			{ "Elegant Purple", MenyooTheme(true, false, true, RGBA(102, 0, 204, 255), RGBA(10, 10, 10, 255), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 255), RGBA(255, 255, 255, 240), RGBA(255, 255, 255, 255), RGBA(255, 255, 255, 211), RGBA(153, 51, 255, 205), GTAfont::Pricedown, GTAfont::Impact, GTAfont::Impact, GTAfont::Italic, GTAfont::Arial, GTAfont::Pricedown) },
		};
		//MenyooTheme g_menyooTheme_temp;
#pragma endregion

		void Sub_Main()
		{
			AddTitle("Themes");

			bool pressed = false;
			for (auto& them : vValues_MenyooThemes)
			{
				pressed = false;
				BOOL isActive = (them.theme == MenyooTheme::CurrentlyActiveTheme()) ? TRUE : FALSE;
				AddTickol(them.name, isActive, pressed, pressed, TICKOL::MAKEUPTHING, TICKOL::NONE, false);
				if (pressed)
				{
					them.theme.SetActive();
				}
			}
		}

	}

}





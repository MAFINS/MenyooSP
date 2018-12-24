/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "TimeOptions.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\DxHookIMG.h"
#include "..\Scripting\Game.h"
#include "..\Util\ExePath.h"

#include <string>
#include <time.h>
#include <stdio.h>

namespace sub
{
	void TimeOps_()
	{
		bool WeatherOps_pause_clock_toggle = 0,
			WeatherOps_hour_plus = 0,
			WeatherOps_hour_minus = 0,
			WeatherOps_minute_plus = 0,
			WeatherOps_minute_minus = 0,
			timescale_plus = 0,
			timescale_minus = 0;

		int WeatherOps_hour = GET_CLOCK_HOURS();
		int WeatherOps_minute = GET_CLOCK_MINUTES();

		AddTitle("Time");
		AddOption("Clock (System Time)", null, nullFunc, SUB::CLOCK);
		AddToggle("Pause Clock Time", loop_pause_clock, WeatherOps_pause_clock_toggle);
		AddToggle("Sync With System Time", loop_sync_clock);
		AddNumber("Hour", WeatherOps_hour, 0, null, WeatherOps_hour_plus, WeatherOps_hour_minus);
		AddNumber("Minute", WeatherOps_minute, 0, null, WeatherOps_minute_plus, WeatherOps_minute_minus);
		AddNumber("World Speed", current_timescale, 1, null, timescale_plus, timescale_minus);

		if (WeatherOps_hour_plus) {
			if ((WeatherOps_hour + 1) == 24)
			{
				if (GET_CLOCK_MONTH() + 1 == 12 && GET_CLOCK_DAY_OF_MONTH() + 1 == 30)
					SET_CLOCK_DATE(1, 0, GET_CLOCK_YEAR() + 1);
				else if (GET_CLOCK_DAY_OF_MONTH() + 1 == 30)
					SET_CLOCK_DATE(1, GET_CLOCK_MONTH() + 1, GET_CLOCK_YEAR());
				else
					SET_CLOCK_DATE(GET_CLOCK_DAY_OF_MONTH() + 1, GET_CLOCK_MONTH(), GET_CLOCK_YEAR());
				NETWORK_OVERRIDE_CLOCK_TIME(0, WeatherOps_minute, GET_CLOCK_SECONDS());
			}
			else
				NETWORK_OVERRIDE_CLOCK_TIME((WeatherOps_hour + 1), WeatherOps_minute, GET_CLOCK_SECONDS());
			return;
		}
		if (WeatherOps_hour_minus) {
			if ((WeatherOps_hour - 1) == -1)
			{
				if (GET_CLOCK_MONTH() - 1 == -1 && GET_CLOCK_DAY_OF_MONTH() - 1 == 0)
					SET_CLOCK_DATE(28, 11, GET_CLOCK_YEAR() - 1);
				else if (GET_CLOCK_DAY_OF_MONTH() - 1 == 0)
					SET_CLOCK_DATE(28, GET_CLOCK_MONTH() - 1, GET_CLOCK_YEAR());
				else
					SET_CLOCK_DATE(GET_CLOCK_DAY_OF_MONTH() - 1, GET_CLOCK_MONTH(), GET_CLOCK_YEAR());
				NETWORK_OVERRIDE_CLOCK_TIME(23, WeatherOps_minute, GET_CLOCK_SECONDS());
			}
			else
				NETWORK_OVERRIDE_CLOCK_TIME((WeatherOps_hour - 1), WeatherOps_minute, GET_CLOCK_SECONDS());
			return;
		}

		if (WeatherOps_minute_plus) {
			if ((WeatherOps_minute + 1) == 61)
			{
				if (WeatherOps_hour + 1 == 24)
				{
					if (GET_CLOCK_DAY_OF_MONTH() + 1 == 30)
						SET_CLOCK_DATE(1, GET_CLOCK_MONTH() + 1, GET_CLOCK_YEAR());
					else
						SET_CLOCK_DATE(GET_CLOCK_DAY_OF_MONTH() + 1, GET_CLOCK_MONTH(), GET_CLOCK_YEAR());
					NETWORK_OVERRIDE_CLOCK_TIME(0, 0, GET_CLOCK_SECONDS());
				}
				else
					NETWORK_OVERRIDE_CLOCK_TIME(WeatherOps_hour + 1, 0, GET_CLOCK_SECONDS());
			}
			else
				NETWORK_OVERRIDE_CLOCK_TIME(WeatherOps_hour, WeatherOps_minute + 1, GET_CLOCK_SECONDS());
			return;
		}
		if (WeatherOps_minute_minus) {
			if ((WeatherOps_minute - 1) == -1)
			{
				if (WeatherOps_hour - 1 == -1)
				{
					if (GET_CLOCK_DAY_OF_MONTH() - 1 == 0)
						SET_CLOCK_DATE(29, GET_CLOCK_MONTH() - 1, GET_CLOCK_YEAR());
					else
						SET_CLOCK_DATE(GET_CLOCK_DAY_OF_MONTH() - 1, GET_CLOCK_MONTH(), GET_CLOCK_YEAR());
					NETWORK_OVERRIDE_CLOCK_TIME(23, 60, GET_CLOCK_SECONDS());
				}
				else
					NETWORK_OVERRIDE_CLOCK_TIME(WeatherOps_hour - 1, 60, GET_CLOCK_SECONDS());
			}
			else
				NETWORK_OVERRIDE_CLOCK_TIME(WeatherOps_hour, WeatherOps_minute - 1, GET_CLOCK_SECONDS());
			return;
		}

		if (timescale_plus && current_timescale < 1.1f) { current_timescale += 0.1f; SET_TIME_SCALE(current_timescale); return; }
		if (timescale_minus && current_timescale > 0.0f) { current_timescale -= 0.1f; SET_TIME_SCALE(current_timescale); return; }

		if (WeatherOps_pause_clock_toggle) { pause_clock_H = GET_CLOCK_HOURS(); pause_clock_M = GET_CLOCK_MINUTES(); return; }


	}

	namespace Clock_catind
	{
		UINT8 loop_clock = 0;
		UINT8 _analogueClockIndex = 0;
		Vector2 _analogueClockPos = { 0.931f, 0.126f };//{ 0.5f, 0.1168f };

		const std::string vWeekDayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		inline void DisplayClockDigital()
		{
			time_t now = time(0);
			tm t;
			localtime_s(&t, &now);

			char mintBuff[3];
			sprintf_s(mintBuff, "%02d", t.tm_min);

			Game::Print::setupdraw(GTAfont::Arial, Vector2(0.3f, 0.3f), true, false, true, RGBA(255, 255, 255, 210));
			Game::Print::drawstring(oss_ << vWeekDayNames[t.tm_wday] << " - " << (t.tm_hour < 13 ? t.tm_hour : t.tm_hour - 12) << ':' << mintBuff << (t.tm_hour < 12 ? " am" : " pm"), 0.5f, 0.007f);//0.01f, 0.8f);
		}

		//struct sClockImage { std::string name; DxHookIMG::DxTexture faceId, hourId, minuteId; };
		std::vector<sClockImage> vClockImages;

		void LoadClockImages()
		{
			std::vector<std::string> results;
			get_all_filenames_with_extension(GetPathffA(Pathff::Graphics, true) + "Clock", ".png", results, false);
			for (auto sit = results.begin(); sit != results.end();)
			{
				if (sit->back() == 'e') // ..._face
				{
					std::string& fullNameWithoutExtension = sit->substr(0, sit->rfind('_'));
					std::string& faceName = *sit + ".png";//fullNameWithoutExtension + "_face.png";
					std::string& handhName = fullNameWithoutExtension + "_handh.png";
					std::string& handmName = fullNameWithoutExtension + "_handm.png";

					DxHookIMG::DxTexture faceId = GetPathffA(Pathff::Graphics, true) + "Clock\\" + faceName;
					DxHookIMG::DxTexture hourId = GetPathffA(Pathff::Graphics, true) + "Clock\\" + handhName;
					DxHookIMG::DxTexture minuteId = GetPathffA(Pathff::Graphics, true) + "Clock\\" + handmName;

					sClockImage cmg = { fullNameWithoutExtension, faceId, hourId, minuteId };
					vClockImages.push_back(cmg);
				}
				++sit;
			}
		}
		inline void DisplayClockAnalogue()
		{
			time_t now = time(0);
			tm t;
			localtime_s(&t, &now);

			auto& cmg = vClockImages[_analogueClockIndex];

			Vector2& size = Vector2(0.1540f, 0.164f) * 0.7f;
			Vector2& pos = _analogueClockPos;

			cmg.faceId.Draw(0, pos, size, 0.0f, RGBA::AllWhite());
			cmg.hourId.Draw(0, pos, size, (30.0f * t.tm_hour) + (0.5f * t.tm_min), RGBA::AllWhite());
			cmg.minuteId.Draw(0, pos, size, (6.0f * t.tm_min), RGBA::AllWhite());
		}

		void DisplayClock()
		{
			//auto& mode = loop_clock;

			switch (loop_clock)
			{
			case 1: DisplayClockDigital(); break; // Digital
			case 2: DisplayClockAnalogue(); break; // Analogue
			}
		}

		void Sub_Clock()
		{
			AddTitle("Clock");

			auto& mode = loop_clock;

			UINT min_clockt = 0;
			UINT8 max_clockt = 2;
			bool bClockt_plus = false, bClockt_minus = false;
			AddTexter("Clock", mode, std::vector<std::string>{"Off", "Digital", "Analogue"}, null, bClockt_plus, bClockt_minus);
			if (bClockt_plus) { if (mode < max_clockt) mode++; }
			if (bClockt_minus) { if (mode > min_clockt) mode--; }

			if (mode == 2) // If analogue
			{
				AddBreak("---Themes---");
				for (UINT i = 0; i < vClockImages.size(); i++)
				{
					bool bAcmgPressed = false;
					AddTickol(vClockImages[i].name, vClockImages[_analogueClockIndex].faceId == vClockImages[i].faceId, bAcmgPressed, bAcmgPressed); if (bAcmgPressed)
					{
						_analogueClockIndex = i;
					}
				}

				AddBreak("---Position---");

				bool acposX_plus = false, acposX_minus = false;
				bool acposY_plus = false, acposY_minus = false;
				AddNumber("X", _analogueClockPos.x, 3, null, acposX_plus, acposX_minus);
				AddNumber("Y", _analogueClockPos.y, 3, null, acposY_plus, acposY_minus);

				if (acposX_plus) _analogueClockPos.x += 0.005f;
				else if (acposX_minus) _analogueClockPos.x -= 0.005f;
				if (acposY_plus) _analogueClockPos.y += 0.005f;
				else if (acposY_minus) _analogueClockPos.y -= 0.005f;
			}
		}
	}

}



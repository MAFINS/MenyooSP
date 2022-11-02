/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "WeatherOptions.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\World.h"

#include <string>
#include <map>
#include <array>

namespace sub
{
	void WeatherOps_()
	{
		bool windSpeed_plus = 0, windSpeed_minus = 0,
			rainfxi_plus = 0, rainfxi_minus = 0,
			wavesHeight_plus = 0, wavesHeight_minus = 0,
			gravityLevel_plus = 0, gravityLevel_minus = 0,
			bClearWeatherOverride = 0;

		//std::vector<std::string>{"Earth", "Mercury", "Earth's Moon", "Pluto"};
		std::map<float, std::string> v0gravities
		{
			{ 0.0f, "Zero 0.0" },
			{ 0.6f, "Pluto 0.6" },
			{ 1.6f, "Earth's Moon 1.6" },
			{ 3.7f, "Mercury/Mars 3.7" },
			{ 8.9f, "Venus/Uranus 8.9" },
			{ 9.8f, "Earth 9.8" },
			{ 10.4f, "Saturn 10.4" },
			{ 11.2f, "Neptune 11.2" },
			{ 24.9f, "Jupiter 24.9" },
			{ 274.0f, "Sun 274.0" }
		};
		float mult_0_gravity = GTAmemory::WorldGravity_get();

		float windSpeed = GAMEPLAY::GET_WIND_SPEED();
		float wavesHeight = WATER::_GET_WAVES_HEIGHT();

		AddTitle("Weather");
		AddTickol("Reset Weather", true, bClearWeatherOverride, bClearWeatherOverride, TICKOL::CROSS); if (bClearWeatherOverride)
		{
			World::ClearWeatherOverride();
		}
		for (auto& weatherName : World::sWeatherNames)
		{
			bool bWeatherPressed = false;
			AddTickol(weatherName, _GET_CURRENT_WEATHER_TYPE() == GET_HASH_KEY(weatherName), bWeatherPressed, bWeatherPressed); if (bWeatherPressed)
			{
				World::SetWeatherOverride(weatherName);
			}
		}
		
		AddNumber("Wind Speed", windSpeed, 2, null, windSpeed_plus, windSpeed_minus);
		AddNumber("Ocean Wave Strength", wavesHeight, 2, null, wavesHeight_plus, wavesHeight_minus);
		AddNumber("Rain Puddles Multiplier", _globalRainFXIntensity, 2, null, rainfxi_plus, rainfxi_minus);
		AddTexter("Gravity Level", 0, std::vector<std::string>{v0gravities[mult_0_gravity]}, null, gravityLevel_plus, gravityLevel_minus);
		AddOption("Clouds", null, nullFunc, SUB::CLOUDOPS);
		AddOption("Water Hack (For Waves At Beaches)", null, nullFunc, SUB::WATERHACK);

		if (windSpeed_plus)
		{
			windSpeed += 0.1f;
			GAMEPLAY::SET_WIND_SPEED(windSpeed);
		}
		if (windSpeed_minus)
		{
			windSpeed -= 0.1f;
			GAMEPLAY::SET_WIND_SPEED(windSpeed);
		}

		if (wavesHeight_plus)
		{
			wavesHeight += 0.1f;
			WATER::_SET_WAVES_HEIGHT(wavesHeight);
		}
		if (wavesHeight_minus)
		{
			wavesHeight -= 0.1f;
			WATER::_SET_WAVES_HEIGHT(wavesHeight);
		}

		if (rainfxi_plus)
		{
			if (_globalRainFXIntensity < 45.0f) _globalRainFXIntensity += 0.1f;
			_SET_RAIN_FX_INTENSITY(_globalRainFXIntensity);
		}
		if (rainfxi_minus)
		{
			if (_globalRainFXIntensity > 0.0f) _globalRainFXIntensity -= 0.1f;
			_SET_RAIN_FX_INTENSITY(_globalRainFXIntensity);
		}

		if (gravityLevel_plus)
		{
			auto git = v0gravities.find(mult_0_gravity);
			git++;
			if (git != v0gravities.end())
			{
				mult_0_gravity = git->first;
				GTAmemory::WorldGravity_set(mult_0_gravity);
			}
		}
		if (gravityLevel_minus)
		{
			auto git = std::map<float, std::string>::reverse_iterator(v0gravities.find(mult_0_gravity));
			git++;
			if (git != v0gravities.rend())
			{
				mult_0_gravity = git->first;
				GTAmemory::WorldGravity_set(mult_0_gravity);
			}
		}
		
		//if (gravityLevel_plus && mult_0_gravity < 3){ mult_0_gravity++; SET_GRAVITY_LEVEL(mult_0_gravity); return; }
		//if (gravityLevel_minus && mult_0_gravity > 0){ mult_0_gravity--; SET_GRAVITY_LEVEL(mult_0_gravity); return; }

	}

	namespace WeatherClouds_catind
	{
		const std::array<std::string, 20> vCloudNames
		{ {
			{ "Altostratus" },
			{ "Cirrocumulus" },
			{ "Cirrus" },
			{ "Clear 01" },
			{ "Cloudy 01" },
			{ "Contrails" },
			{ "Horizonband1" },
			{ "Horizonband2" },
			{ "Horizonband3" },
			{ "Horsey" },
			{ "Nimbus" },
			{ "NoClouds" },
			{ "Puffs" },
			{ "Rain" },
			{ "Shower" },
			{ "Snowy 01" },
			{ "Stormy 01" },
			{ "Stratoscumulus" },
			{ "Stripey" },
			{ "Wispy" }
			} };

		void sub_CloudOps()
		{
			AddTitle("Clouds");

			bool bResetPressed = false;
			AddTickol("Reset", true, bResetPressed, bResetPressed, TICKOL::CROSS); if (bResetPressed)
			{
				_CLEAR_CLOUD_HAT();
			}

			for (auto& name : vCloudNames)
			{
				bool bPressed = false;
				AddOption(name, bPressed); if (bPressed)
				{
					_SET_CLOUD_HAT_TRANSITION(const_cast<PCHAR>(name.c_str()), 0.5f);
				}
			}
		}

	}

}



/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Game.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
//#include "..\Scripting\enums.h"
#include "..\Natives\natives2.h"
#include "..\Memory\GTAmemory.h"
#include "GTAentity.h"
#include "GTAped.h"
#include "GTAplayer.h"

#include <string>
#include <sstream>
#include <Windows.h>

std::ostream& operator<<(std::ostream& stream, std::wstring& text)
{
	stream << std::string(text.begin(), text.end());
	return stream;
}
std::wostream& operator<<(std::wostream& stream, std::string& text)
{
	stream << std::wstring(text.begin(), text.end());
	return stream;
}

namespace Game
{
	const std::pair<int, int> defaultScreenRes = { 1280, 720 };

	// Request asset
	bool RequestControlOfId(int netid)
	{
		NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		for (DWORD timeOut = GetTickCount() + 200; GetTickCount() < timeOut;)
		{
			if (NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid))
				return true;
			WAIT(0);
		}
		return false;
	}
	bool RequestAnimDict(const std::string& anim_dict, DWORD timeOutms)
	{
		REQUEST_ANIM_DICT(anim_dict.c_str());
		for (DWORD timeOut = GetTickCount() + timeOutms; GetTickCount() < timeOut;)
		{
			if (HAS_ANIM_DICT_LOADED(anim_dict.c_str()))
				return true;
			WAIT(0);
		}
		return false;
	}
	bool RequestAnimSet(const std::string& anim_set, DWORD timeOutms)
	{
		REQUEST_ANIM_SET(anim_set.c_str());
		for (DWORD timeOut = GetTickCount() + timeOutms; GetTickCount() < timeOut;)
		{
			if (HAS_ANIM_SET_LOADED(anim_set.c_str()))
				return true;
			WAIT(0);
		}
		return false;
	}
	void RequestScript(const std::string& scriptName, int stackSize)
	{
		if (GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(GET_HASH_KEY(scriptName)) == 0 && DOES_SCRIPT_EXIST(scriptName.c_str()))
		{
			REQUEST_SCRIPT(scriptName.c_str());

			for (DWORD timeOut = GetTickCount() + 5000; GetTickCount() < timeOut;)
			{
				if (HAS_SCRIPT_LOADED(scriptName.c_str()))
					break;
				WAIT(0);
			}
			//while (!HAS_SCRIPT_LOADED(scriptName.c_str())) WAIT(0);

			START_NEW_SCRIPT(scriptName.c_str(), stackSize); // 1024 on console
			SET_SCRIPT_AS_NO_LONGER_NEEDED(scriptName.c_str());
		}
	}

	// GXT
	inline bool DoesGXTEntryExist(const std::string& entry)
	{
		return DOES_TEXT_LABEL_EXIST(entry.c_str()) != 0;
	}
	std::string GetGXTEntry(const std::string& entry, const std::string& fallback)
	{
		if (DoesGXTEntryExist(entry))
		{
			return GET_FILENAME_FOR_AUDIO_CONVERSATION(entry.c_str());
		}
		return fallback.empty() ? entry : fallback;
	}
	std::string GetGXTEntry(Hash entry, const std::string& fallback)
	{
		auto result = GTAmemory::GetGXTEntry(entry);
		return result == nullptr ? fallback : result;
	}

	namespace Sound
	{
		GameSound::GameSound()
			: active(false),
			soundID(-1)
		{
		}
		GameSound::GameSound(const std::string& nsoundSet, const std::string& nsound)
			: active(false),
			sound(nsound),
			soundSet(nsoundSet),
			soundID(-1)

		{
		}

		bool GameSound::LoadBank(const std::string& audioBank)
		{
			return REQUEST_SCRIPT_AUDIO_BANK((PCHAR)audioBank.c_str(), false, 0) != 0;
		}
		void GameSound::UnloadBank(const std::string& audioBank)
		{
			RELEASE_NAMED_SCRIPT_AUDIO_BANK((PCHAR)audioBank.c_str());
		}

		void GameSound::Play(GTAentity entity)
		{
			soundID = GET_SOUND_ID();
			PLAY_SOUND_FROM_ENTITY(soundID, (PCHAR)sound.c_str(), entity.Handle(), (PCHAR)soundSet.c_str(), 0, 0);
			active = true;
		}

		void GameSound::Stop()
		{
			if (soundID == -1 || !active) return;
			STOP_SOUND(soundID);
			active = false;
		}

		void GameSound::Destroy()
		{
			if (soundID == -1 || !active) return;
			RELEASE_SOUND_ID(soundID);
			soundID = -1;
			active = false;
		}

		void PlayFrontend(const std::string& sound_dict, const std::string& sound_name)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name.c_str(), sound_dict.c_str(), FALSE);
		}
		void PlayFrontend_default(const std::string& sound_name)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name.c_str(), "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
		}
	}

	namespace Print
	{
		// Game - Print/draw
		void setupdraw()
		{
			SET_TEXT_FONT(0);
			SET_TEXT_SCALE(0.4f, 0.4f);
			SET_TEXT_COLOUR(255, 255, 255, 255);
			SET_TEXT_WRAP(0.0f, 1.0f);
			SET_TEXT_CENTRE(0);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_EDGE(0, 0, 0, 0, 0);
			//SET_TEXT_OUTLINE();
		}
		void setupdraw(INT8 font, const Vector2& scale, bool centred, bool right_justified, bool outline, RGBA colour, Vector2 wrap)
		{
			SET_TEXT_FONT(font);
			SET_TEXT_SCALE(scale.x, scale.y);
			SET_TEXT_COLOUR(colour.R, colour.G, colour.B, colour.A);
			SET_TEXT_WRAP(wrap.x, wrap.y);
			SET_TEXT_RIGHT_JUSTIFY(right_justified);
			SET_TEXT_CENTRE(centred);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_EDGE(0, 0, 0, 0, 0);
			if (outline) SET_TEXT_OUTLINE();
		}
		void drawstring(const std::string& s, float X, float Y)
		{
			if (s.length() < 100)
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(s.c_str());
			}
			else
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");
				add_text_component_long_string(s);
			}
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}
		void drawstring(std::ostream& os, float X, float Y)
		{
			const std::string& s = dynamic_cast<std::ostringstream&>(os).str();
			if (s.length() < 100)
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(s.c_str());
			}
			else
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");
				add_text_component_long_string(s);
			}
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}
		void drawstringGXT(const std::string& s, float X, float Y)
		{
			if (DOES_TEXT_LABEL_EXIST(s.c_str()))
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT(s.c_str());
				BEGIN_TEXT_COMMAND_SCALEFORM_STRING(s.c_str());
				END_TEXT_COMMAND_SCALEFORM_STRING();
			}
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(s.c_str());
				}
				else
				{
					BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");
					add_text_component_long_string(s);
				}
			}
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}
		void drawstringGXT(std::ostream& os, float X, float Y)
		{
			const std::string& s = dynamic_cast<std::ostringstream&>(os).str();
			char* text = (char*)s.c_str();

			if (DOES_TEXT_LABEL_EXIST(text))
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT(text);
				BEGIN_TEXT_COMMAND_SCALEFORM_STRING(text);
				END_TEXT_COMMAND_SCALEFORM_STRING();
			}
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				}
				else
				{
					BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");
					add_text_component_long_string(s);
				}
			}
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}
		void drawinteger(int text, float X, float Y)
		{
			BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_INTEGER(text);
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}
		void drawfloat(float text, UINT8 decimal_places, float X, float Y)
		{
			BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_FLOAT(text, decimal_places);
			END_TEXT_COMMAND_DISPLAY_TEXT(X, Y, 0);
		}

		void PrintBottomCentre(const std::string& s, int time)
		{
			PCHAR text = (PCHAR)s.c_str();

			if (DOES_TEXT_LABEL_EXIST(text))
			{
				BEGIN_TEXT_COMMAND_PRINT(text);
			}
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_PRINT("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				}
				else
				{
					BEGIN_TEXT_COMMAND_PRINT("jamyfafi");
					add_text_component_long_string(s);
				}
			}
			END_TEXT_COMMAND_PRINT(time, 1);
		}
		void PrintBottomCentre(std::ostream& s, int time)
		{
			PrintBottomCentre(dynamic_cast<std::ostringstream&>(s).str(), time);
		}
		void PrintBottomCentre(std::wostream& s, int time)
		{
			std::wstring wtext2 = (dynamic_cast<std::wostringstream&>(s).str());
			PrintBottomCentre(std::string(wtext2.begin(), wtext2.end()), time);
		}

		void Notification::Hide()
		{
			THEFEED_REMOVE_ITEM(this->mHandle);
		}
		Notification PrintBottomLeft(const std::string& s, bool gxt)
		{
			PCHAR text = (PCHAR)s.c_str();

			if (gxt && DOES_TEXT_LABEL_EXIST(text))
				BEGIN_TEXT_COMMAND_THEFEED_POST(text);
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				}
				else
				{
					BEGIN_TEXT_COMMAND_THEFEED_POST("jamyfafi");
					add_text_component_long_string(s);
				}
			}

			Game::Sound::PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

			//END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(0, 1);
			return END_TEXT_COMMAND_THEFEED_POST_TICKER(0, 0);
		}
		Notification PrintBottomLeft(std::ostream& s, bool gxt)
		{
			return PrintBottomLeft((dynamic_cast<std::ostringstream&>(s).str()), gxt);
		}
		Notification PrintBottomLeft(std::wostream& s, bool gxt)
		{
			std::wstring wtext = (dynamic_cast<std::wostringstream&>(s).str());
			return PrintBottomLeft(std::string(wtext.begin(), wtext.end()), gxt);
		}
		Notification PrintBottomLeft(const std::string& s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt)
		{
			PCHAR text = (PCHAR)s.c_str();

			if (gxt && DOES_TEXT_LABEL_EXIST(text))
				BEGIN_TEXT_COMMAND_THEFEED_POST(text);
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				}
				else
				{
					BEGIN_TEXT_COMMAND_THEFEED_POST("jamyfafi");
					add_text_component_long_string(s);
				}
			}

			END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT((PCHAR)picName.c_str(), (PCHAR)picName.c_str(), flash, iconType, (PCHAR)sender.c_str(), (PCHAR)subject.c_str());

			Game::Sound::PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

			return END_TEXT_COMMAND_THEFEED_POST_TICKER(0, 0);
		}
		Notification PrintBottomLeft(std::ostream& s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt)
		{
			return PrintBottomLeft((dynamic_cast<std::ostringstream&>(s).str()), sender, subject, picName, iconType, flash, gxt);
		}
		Notification PrintBottomLeft(std::wostream& s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt)
		{
			std::wstring wtext = (dynamic_cast<std::wostringstream&>(s).str());
			return PrintBottomLeft(std::string(wtext.begin(), wtext.end()), sender, subject, picName, iconType, flash, gxt);
		}

		// Messages - Errors
		void PrintError_InvalidInput()
		{
			Game::Print::PrintBottomCentre("~r~Error:~s~ Invalid Input.");
		}
		void PrintError_InvalidModel()
		{
			Game::Print::PrintBottomCentre("~r~Error:~s~ Invalid Model.");
		}

		// Text width
		float GetTextWidth(const std::string& s, bool gxt)
		{
			if (gxt)
				BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(s.c_str());
			else
			{
				if (s.length() < 100)
				{
					BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("STRING");
					ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(s.c_str());
				}
				else
				{
					BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("jamyfafi");
					add_text_component_long_string(s);
				}
			}
			return END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(1);
		}
		float GetTextWidth(int inumber)
		{
			BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_INTEGER(inumber);
			return END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(1);
		}
		float GetTextWidth(float fnumber, UINT8 decimal_places)
		{
			BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("NUMBER");
			ADD_TEXT_COMPONENT_FLOAT(fnumber, decimal_places);
			return END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(1);
		}
	}

	//On screen keyboard
	std::string InputBox(const std::string& escReturn, int maxChars, const std::string& titlegxt, std::string preText)
	{
		preText = preText.substr(0, maxChars);

		//CustomKeyboardText ckt;
		DISPLAY_ONSCREEN_KEYBOARD(true, "", "", preText.c_str(), "", "", "", maxChars);

		while (UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			SET_TEXT_FONT(/*GTAfont::Arial*/0);
			SET_TEXT_SCALE(0.34f, 0.34f);
			SET_TEXT_COLOUR(255, 255, 255, 255);
			SET_TEXT_WRAP(0.0f, 1.0f);
			SET_TEXT_RIGHT_JUSTIFY(FALSE);
			SET_TEXT_CENTRE(TRUE);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_EDGE(0, 0, 0, 0, 0);
			SET_TEXT_OUTLINE();

			if (DOES_TEXT_LABEL_EXIST(titlegxt.c_str()))
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT(titlegxt.c_str());
			}
			else if (titlegxt.length() < 100)
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(titlegxt.c_str());
			}
			else
			{
				BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");
				add_text_component_long_string(titlegxt);
			}
			END_TEXT_COMMAND_DISPLAY_TEXT(0.5f, 0.37f, 0);
			WAIT(0);
		}
		if (UPDATE_ONSCREEN_KEYBOARD() == 2)
		{
			return escReturn;
		}

		return GET_ONSCREEN_KEYBOARD_RESULT();
	}

	//PLAYER_PED_ID()
	GTAplayer Player()
	{
		return PLAYER::PLAYER_ID();
	}
	GTAplayer Player(int index)
	{
		return GTAplayer(index);
	}
	GTAped PlayerPed()
	{
		return PLAYER::PLAYER_PED_ID();
	}
	GTAped PlayerPed(int index)
	{
		return PLAYER::GET_PLAYER_PED(index);
	}
}
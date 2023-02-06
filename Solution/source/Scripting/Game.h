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

#include "..\Natives\types.h" //RGBA
#include "..\Util\GTAmath.h" //Vector2

#include <string>
#include <sstream>

typedef unsigned long DWORD, Hash;
typedef signed char INT8;
typedef unsigned char UINT8;

typedef char *PCHAR;

class GTAentity;
class GTAped;
class GTAplayer;

// Stringstream
std::ostream& operator<<(std::ostream& stream, std::wstring& text);
std::wostream& operator<<(std::wostream& stream, std::string& text);
#define oss_ std::ostringstream().flush() << ""
#define woss_ std::wostringstream().flush() << ""

namespace Game
{
	extern const std::pair<int, int> defaultScreenRes;

	// Request asset
	bool RequestControlOfId(int netid);
	bool RequestAnimDict(const std::string& anim_dict, DWORD timeOut = 1800);
	bool RequestAnimSet(const std::string& anim_set, DWORD timeOut = 1800);
	void RequestScript(const std::string& scriptName, int stackSize = 14000);

	// GXT
	inline bool DoesGXTEntryExist(const std::string& entry);
	std::string GetGXTEntry(const std::string& entry, const std::string& fallback = std::string());
	std::string GetGXTEntry(Hash entry, const std::string& fallback = std::string());

	namespace Sound
	{
		class GameSound
		{
		private:
			std::string soundSet;
			std::string sound;
			int soundID;

		public:
			bool active;

			GameSound();
			GameSound(const std::string& nsoundSet, const std::string& nsound);

			static bool LoadBank(const std::string& audioBank);
			static void UnloadBank(const std::string& audioBank);

			void Play(GTAentity entity);

			void Stop();

			void Destroy();
		};

		void PlayFrontend(const std::string& sound_dict, const std::string& sound_name);
		void PlayFrontend_default(const std::string& sound_name);
	}

	namespace Print
	{
		// Game - Print/draw
		void setupdraw();
		void setupdraw(INT8 font, const Vector2& scale, bool centred, bool right_justified, bool outline, RGBA colour = { 255, 255, 255, 255 }, Vector2 wrap = { 0, 1 });
		void drawstring(const std::string& s, float X, float Y);
		void drawstring(std::ostream& os, float X, float Y);
		void drawstringGXT(const std::string& s, float X, float Y);
		void drawstringGXT(std::ostream& os, float X, float Y);
		void drawinteger(int text, float X, float Y);
		void drawfloat(float text, UINT8 decimal_places, float X, float Y);
		
		void PrintBottomCentre(std::string s, int time = 2500);
		void PrintBottomCentre(std::ostream& s, int time = 2500);
		void PrintBottomCentre(std::wostream& s, int time = 2500);

		class Notification
		{
		public:
			Notification(int newHandle) : mHandle(newHandle)
			{
			}
			int& Handle()
			{
				return mHandle;
			}

			void Hide();

		private:
			int mHandle;
		};
		Notification PrintBottomLeft(std::string s, bool gxt = false);
		Notification PrintBottomLeft(std::ostream& s, bool gxt = 0);
		Notification PrintBottomLeft(std::wostream& s, bool gxt = 0);
		Notification PrintBottomLeft(std::string s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt);
		Notification PrintBottomLeft(std::ostream& s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt);
		Notification PrintBottomLeft(std::wostream& s, const std::string& sender, const std::string& subject, const std::string& picName, int iconType, bool flash, bool gxt);

		// Messages - Errors
		void PrintError_InvalidInput();
		void PrintError_InvalidModel();

		// Text width
		float GetTextWidth(const std::string& s, bool gxt = false);
		float GetTextWidth(int inumber);
		float GetTextWidth(float fnumber, UINT8 decimal_places);
	}

	//On screen keyboard
	std::string InputBox(const std::string& escReturn = "", int maxChars = 64U, std::string titlegxt = "", std::string preText = "");

	//PLAYER_PED_ID()
	GTAplayer Player();
	GTAplayer Player(int index);
	GTAped PlayerPed();
	GTAped PlayerPed(int index);

}


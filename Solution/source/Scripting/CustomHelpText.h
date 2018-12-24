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
#include <sstream>

typedef unsigned long DWORD;

//Also defined in Scripting\Game.h
#define oss_ std::ostringstream().flush() << ""
#define woss_ std::wostringstream().flush() << ""

namespace Game
{
	class CustomHelpText final
	{
	private:
		static DWORD _timer;
		static std::string _tag;
		static std::string _text;

		static bool Drawing();

	public:
		static void SetTag(const std::string& newTag);

		static void SetText(const std::string& newText);

		static void ShowThisFrame(const std::string& textToShow);
		static void ShowThisFrame(std::ostream& s);
		static void ShowThisFrame(std::wostream& s);
		static void ShowThisFrame();

		static void End();

		static void Tick();

		static void ShowTimedText(const std::string& text, DWORD how_many_ms);
		static void ShowTimedText(std::ostream& s, DWORD how_many_ms);
		static void ShowTimedText(std::wostream& s, DWORD how_many_ms);
	};

}


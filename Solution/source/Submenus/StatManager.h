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

typedef unsigned __int8 UINT8;

namespace sub
{
	namespace SpStatManager_catind
	{
		enum class StatDataType_t : UINT8
		{
			UNKNOWN,
			BOOL,
			INT,
			FLOAT
		};
		struct CharStat_t { std::string name, caption; StatDataType_t type; float min, max; };
		//struct NamedCharStatList_t { std::string title; std::vector<CharStat_t> list; };

		// Setters/Getters
		int StatGetInt(const std::string& name);
		bool StatGetBool(const std::string& name);
		float StatGetFloat(const std::string& name);
		std::string StatGetString(const std::string& name);
		void StatSetInt(const std::string& name, int value);
		void StatSetBool(const std::string& name, bool value);
		void StatSetFloat(const std::string& name, float value);
		void StatSetString(const std::string& name, const std::string& value);

		void __AddOption(const CharStat_t& stat);

		void Sub_SpStatManager();
		void Sub_InChar();
		void Sub_InChar_InList();

	}

}




/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "TimecycleModification.h"

#include "..\macros.h"

#include "..\Util\ExePath.h"
#include "..\Natives\natives2.h"

#include <string>
#include <vector>
#include <utility>
#include <pugixml\src\pugixml.hpp>

namespace TimecycleModification
{
	std::vector<std::pair<std::string, std::string>> vTimecycles;

	bool PopulateTimecycleNames()
	{
		std::string xmlTimecycModifiers = "TimecycModifiers.xml";
		pugi::xml_document doc;
		if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + xmlTimecycModifiers).c_str()).status != pugi::status_ok)
		{
			/*doc.reset();
			auto& nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";
			auto& nodeRoot = doc.append_child("TimecycModifiers");
			doc.save_file((const char*)(GetPathffA(Pathff::Main, true) + xmlTimecycModifiers).c_str());*/
			return false;
		}
		else
		{
			vTimecycles.clear();
			pugi::xml_node nodeRoot = doc.child("TimecycModifiers");
			for (auto nodeMod = nodeRoot.child("Mod"); nodeMod; nodeMod = nodeMod.next_sibling("Mod"))
			{
				const pugi::char_t* modCaption = nodeMod.attribute("caption").as_string();
				const pugi::char_t* modName = nodeMod.attribute("name").as_string();
				vTimecycles.push_back(std::make_pair(modName, modCaption));
			}
			return true;
		}
	}

	bool IsModActive()
	{
		return GRAPHICS::GET_TIMECYCLE_MODIFIER_INDEX() != -1;
	}
	int GetModId()
	{
		return GRAPHICS::GET_TIMECYCLE_MODIFIER_INDEX();
	}
	void SetMod(const std::string& value)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER(const_cast<PCHAR>(value.c_str()));
	}
	void SetMod(const std::string& value, float transition)
	{
		GRAPHICS::SET_TRANSITION_TIMECYCLE_MODIFIER(const_cast<PCHAR>(value.c_str()), transition);
	}
	void SetModStrength(float value)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(value);
	}
	void ClearMod()
	{
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
	}
}



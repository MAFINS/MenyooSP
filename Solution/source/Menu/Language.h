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
#include <map>
#include <vector>

namespace Language
{
	class Lang
	{
	private:
		std::string filepath;
		std::string name;
		std::map<std::string, std::string> pairs;
	public:
		Lang(std::string aName, std::string afilePath);
		inline const std::string& GetName() const { return this->name; }
		inline const std::string& GetFilePath() const { return this->filepath; }
		inline decltype(pairs)& Dictionary() { return this->pairs; }

		std::string Translate(std::string text);
	};


	extern std::vector<Lang> allLangs;
	extern Lang* selectedLang;
	extern std::string configLangName;

	std::string TranslateToSelected(std::string text);

	int Init();

	std::string GetSelectedLangTitle();
	int SetSelectedLangFromConfig();
	int SetSelectedLangFromString(std::string aName);
	void SetSelectedLang(Lang* ptr);
	void ResetSelectedLang();

}

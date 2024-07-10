/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Language.h"

#include "..\Util\ExePath.h"
#include "..\Util\FileLogger.h"
#include "..\Menu\Menu.h"

#include <fstream>
#include <json\single_include\nlohmann\json.hpp>
using Json = nlohmann::json;

namespace Language
{
	std::vector<Lang> allLangs;
	Lang* selectedLang = nullptr;
	std::string configLangName = std::string();


	Lang::Lang(std::string aName, std::string aFilePath)
	{
		this->filepath = aFilePath;
		this->name = aName;
		this->pairs.clear();
	}

	std::string Lang::Translate(std::string text)
	{
		try
		{
			auto& ret = this->pairs.at(text);
			return ret;
		}
		catch (std::out_of_range)
		{
			addlog(ige::LogType::LOG_ERROR, "Translate string out of range: " + text, __FILENAME__);
			return text;
		}
	}

	std::string TranslateToSelected(std::string text)
	{
		if (selectedLang != nullptr)
			return selectedLang->Translate(text);
		else
		{
			return text;
		}
	}

	int Init()
	{
		allLangs.clear();
		selectedLang = nullptr;

		const std::string& dirpath = GetPathffA(Pathff::Language, false);
		std::vector<std::string> allFiles;
		const std::string& ext = ".json";
		get_all_filenames_with_extension(dirpath, ext, allFiles, false);

		for (const std::string& fn : allFiles)
		{
			const std::string& filePath = dirpath + "\\" + fn + ext;

			Lang lang(fn, filePath);
			//std::ifstream stream(filePath);
			//Json doc = Json::parse(stream);
			//lang.Dictionary() = doc;
			allLangs.push_back(lang);
		}

		SetSelectedLangFromConfig();

		return 0;
	}

	std::string GetSelectedLangTitle()
	{
		return configLangName.empty() ? "English" : configLangName;
	}
	int SetSelectedLangFromConfig()
	{
		std::for_each(allLangs.begin(), allLangs.end(), [](Lang& l) { l.Dictionary().clear(); });

		if (configLangName.empty())
		{
			selectedLang = nullptr;
			return 0;
		}
		for (auto& lang : allLangs)
		{
			if (lang.GetName() == configLangName)
			{
				selectedLang = &lang;
				std::ifstream stream(lang.GetFilePath());
				try
				{
					Json doc = Json::parse(stream);
					lang.Dictionary() = doc;
					addlog(ige::LogType::LOG_INFO,  "Loaded language file " + lang.GetFilePath(), __FILENAME__);
				}
				catch (...)
				{
					addlog(ige::LogType::LOG_ERROR,  "Unable to load language file " + lang.GetFilePath(), __FILENAME__);
					return -1;
				}

				return 0;
			}
		}

		addlog(ige::LogType::LOG_ERROR,  "Cannot find selected language in memory. Resetting to default", __FILENAME__);
		ResetSelectedLang();
		return -1;
	}
	int SetSelectedLangFromString(std::string aName)
	{
		configLangName = aName;
		return SetSelectedLangFromConfig();
	}
	void SetSelectedLang(Lang* ptr)
	{
		configLangName.clear();
		selectedLang = ptr;
		if (ptr != nullptr)
			configLangName = selectedLang->GetName();
		SetSelectedLangFromConfig();
	}
	void ResetSelectedLang()
	{
		configLangName.clear();
		selectedLang = nullptr;
	}

}

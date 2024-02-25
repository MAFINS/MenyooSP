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

#include <fstream>
//namespace std {
//	class ofstream;
//}

// One time use only
namespace ige
{
	enum class LogType { LOG_INIT = -1, LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG, LOG_TRACE };
	class FileLogger
	{
	public:
		std::ofstream myFile;

		explicit FileLogger(std::string fname);

		~FileLogger();

		// Basically what inheriting from sf::NonCopyable would be like
		FileLogger(const FileLogger&) = delete;
		FileLogger& operator= (const FileLogger&) = delete;
	};

	extern ige::FileLogger menyooLogObject;
	extern std::ofstream& myLog;
	extern void addlog(int loglevel, ige::LogType logType, std::string message);

}

std::ofstream& operator << (std::ofstream& stream, ige::LogType logType);

